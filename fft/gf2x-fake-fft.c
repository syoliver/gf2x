/* This file is part of the gf2x library.

   Copyright 2007, 2008, 2009, 2010, 2013, 2014, 2015
   Richard Brent, Pierrick Gaudry, Emmanuel Thome', Paul Zimmermann

   This program is free software; you can redistribute it and/or modify it
   under the terms of either:
    - If the archive contains a file named toom-gpl.c (not a trivial
    placeholder), the GNU General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.
    - If the archive contains a file named toom-gpl.c which is a trivial
    placeholder, the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
   
   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the license text for more details.
   
   You should have received a copy of the GNU General Public License as
   well as the GNU Lesser General Public License along with this program;
   see the files COPYING and COPYING.LIB.  If not, write to the Free
   Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#define _GNU_SOURCE
#include "gf2x.h"
#include "gf2x/gf2x-config.h"
#include "gf2x/gf2x-impl.h"

#include "gf2x-fake-fft.h"
#include "gf2x-fft-impl-utils.h"

/* nF, nG : number of coefficients */
void gf2x_fake_fft_info_init(gf2x_fake_fft_info_ptr p, size_t nF, size_t nG, ...)
{
    p->n1 = nF;
    p->n2 = nG;
    p->mp_shift = 0;
    size_t nc = 0;
    if (p->n1 > nc) nc = p->n1;
    if (p->n2 > nc) nc = p->n2;
    p->size = 2 * W(nc);
}

void gf2x_fake_fft_info_init_mp(gf2x_fake_fft_info_ptr p, size_t nF, size_t nG, ...)
{
    p->n1 = nF;
    p->n2 = nG;
    p->mp_shift = MIN(nF, nG) - 1;
    size_t nc = 0;
    if (p->n1 > nc) nc = p->n1;
    if (p->n2 > nc) nc = p->n2;
    p->size = 2 * W(nc);
}

void gf2x_fake_fft_info_init_similar(gf2x_fake_fft_info_ptr o, gf2x_fake_fft_info_srcptr other GF2X_MAYBE_UNUSED, size_t bits_a, size_t bits_b)
{
    gf2x_fake_fft_info_init(o, bits_a, bits_b);
}

int gf2x_fake_fft_compatible(gf2x_fake_fft_info_srcptr o1 GF2X_MAYBE_UNUSED, gf2x_fake_fft_info_srcptr o2 GF2X_MAYBE_UNUSED)
{
    return 1;
}

void gf2x_fake_fft_info_get_alloc_sizes(
        gf2x_fake_fft_info_srcptr o,
        size_t sizes[3])
{
    sizes[0] = o->size * sizeof(gf2x_fake_fft_t);
    sizes[1] = 0;
    sizes[2] = 0;
}

/* n is a number of coefficients ! */
void gf2x_fake_fft_dft(gf2x_fake_fft_info_srcptr p GF2X_MAYBE_UNUSED, gf2x_fake_fft_ptr dst, const unsigned long * src, size_t n, gf2x_fake_fft_ptr temp1 GF2X_MAYBE_UNUSED) {
    ASSERT(n <= p->n1 || n <= p->n2);
    size_t s = W(n);
    memcpy(dst, src, s * sizeof(unsigned long));
    if (R(n)) {
        /* Just as we are computing this assertion, we could easily mask out
         * the bits ourselves. However, our interface mandates that the high
         * bits be cleared in any case. So make sure we properly enforce this
         * constraint.
         */
        ASSERT((src[s-1] & ~MASK(R(n))) == 0);
    }
    memset(dst + s, 0, (p->size - s) * sizeof(unsigned long));
}

/* n is a number of coefficients ! -- requiring less than the compute size is
 * okay, as long as it's understood as a means for truncating the data. So we
 * don't do checking for zero high bits.
 */
void gf2x_fake_fft_ift(gf2x_fake_fft_info_srcptr p GF2X_MAYBE_UNUSED, unsigned long * dst, size_t n, gf2x_fake_fft_ptr src, gf2x_fake_fft_ptr temp1 GF2X_MAYBE_UNUSED) {
    ASSERT(n + p->mp_shift <= p->n1 + p->n2 - 1);
    size_t t = W(n);
    if (p->mp_shift == 0) {
        memcpy(dst, src, t * sizeof(unsigned long));
    } else {
        size_t words_full = W(n + p->mp_shift);
        size_t pick = I(p->mp_shift);
        size_t cnt = R(p->mp_shift);
        size_t tnc = WLEN - cnt;
        Rsh(dst, src + pick, t, cnt);
        /* words_full - pick - t is either 0 or 1 */
        if (words_full - pick == t + 1)
            dst[t - 1] |= src[pick + t] << tnc;
        if (R(n))
            dst[I(n)] &= MASK(R(n));
    }
}

void gf2x_fake_fft_compose(gf2x_fake_fft_info_srcptr p GF2X_MAYBE_UNUSED, gf2x_fake_fft_ptr dst, gf2x_fake_fft_srcptr s1, gf2x_fake_fft_srcptr s2, gf2x_fake_fft_ptr temp2 GF2X_MAYBE_UNUSED) {
    size_t n1 = W(p->n1);
    size_t n2 = W(p->n2);
    gf2x_mul(dst, s1, n1, s2, n2);
}
void gf2x_fake_fft_addcompose_n(gf2x_fake_fft_info_srcptr p GF2X_MAYBE_UNUSED, gf2x_fake_fft_ptr dst, gf2x_fake_fft_srcptr * s1, gf2x_fake_fft_srcptr * s2, size_t n, gf2x_fake_fft_ptr temp2 GF2X_MAYBE_UNUSED, gf2x_fake_fft_ptr temp1 GF2X_MAYBE_UNUSED) {
    size_t n1 = W(p->n1);
    size_t n2 = W(p->n2);
    unsigned long * h = malloc(p->size * sizeof(unsigned long));
    /* lacking addmul in gf2x, we do some extra allocation */
    memset(h, 0, p->size * sizeof(unsigned long));
    for(size_t k = 0 ; k < n ; k++) {
        gf2x_mul(h, s1[k], n1, s2[k], n2);
        for(unsigned int i = 0 ; i < p->size ; i++) {
            dst[i] ^= h[i];
        }
    }
    free(h);
}
void gf2x_fake_fft_addcompose(gf2x_fake_fft_info_srcptr p, gf2x_fake_fft_ptr dst, gf2x_fake_fft_srcptr s1, gf2x_fake_fft_srcptr s2, gf2x_fake_fft_ptr temp2, gf2x_fake_fft_ptr temp1) {
    gf2x_fake_fft_addcompose_n(p, dst, &s1, &s2, 1, temp2, temp1);
}
void gf2x_fake_fft_add(gf2x_fake_fft_info_srcptr p GF2X_MAYBE_UNUSED, gf2x_fake_fft_ptr dst, gf2x_fake_fft_srcptr s1, gf2x_fake_fft_srcptr s2) {
    size_t i;
    for(i = 0 ; i < p->size ; i++) {
        dst[i] = s1[i] ^ s2[i];
    }
}

/* vim: set sw=4 sta et: */
