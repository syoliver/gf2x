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
/* An implementation of Cantor's algorithm for multiplication of
   Copyright 2007 Pierrick Gaudry.
   Copyright 2008,2009,2010,2012 Emmanuel Thomé.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or (at
   your option) any later version.
   
   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with CADO-NFS; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GF2X_FFT_CANTOR_H_
#define GF2X_FFT_CANTOR_H_

#include <stdint.h>
#include <stdlib.h>

#include "gf2x.h"
#include "gf2x/gf2x-config-export.h"
#include "gf2x/gf2x-thresholds.h"       /* GF2X_WORDSIZE */

// we must implement some sort of fallback on the fake_fft thing when the
// polynomials are too small, or something like this. The gf2x-fft
// interface requires that any size can be used.

#if !defined(GF2X_WORDSIZE) || (GF2X_WORDSIZE != 32 && GF2X_WORDSIZE != 64)
#error  "define GF2X_WORDSIZE to either 32 or 64"
#endif

#if !defined(CANTOR_BASE_FIELD_SIZE) || (CANTOR_BASE_FIELD_SIZE != 64 && CANTOR_BASE_FIELD_SIZE != 128)
#error  "Define CANTOR_BASE_FIELD_SIZE to 64 or 128"
#endif

/* The section below is automatically generated */
/* inline: clear order copy */

struct gf2x_cantor_fft_info;
// gf2x_cantor_fft_info_t is defined after the struct fields.
// typedef struct gf2x_cantor_fft_info gf2x_cantor_fft_info_t[1];
typedef struct gf2x_cantor_fft_info * gf2x_cantor_fft_info_ptr;
typedef const struct gf2x_cantor_fft_info * gf2x_cantor_fft_info_srcptr;

/* gf2x_cantor_fft_info is an implementation-defined structure that holds important
 * auxiliary data, used for dealing with transforms. This structure may
 * or may not consist of plain-old datatypes only, so that it only
 * possible to copy it with care (see below).  
 * 
 * C code should use gf2x_cantor_fft_info_t preferrably, as it provides transparent
 * conversion to a pointer, and yet defines storage as well (à la GMP).
 *
 * C++ code should use gf2x_cantor_fft_info.  When the header is included from C++
 * code, the api below is also exported as member functions of gf2x_cantor_fft_info.
 * The info type is default-constructible in all cases, but not always
 * trivially copyable.
 *
 * gf2x_cantor_fft_info_ptr and gf2x_cantor_fft_info_srcptr are auxiliary types used in C
 * prototypes. C++ code should prefer references and const references to
 * gf2x_cantor_fft_info.
 */

#ifdef __cplusplus
extern "C" {
#endif

extern void GF2X_EXPORTED gf2x_cantor_fft_info_init(
        gf2x_cantor_fft_info_ptr p,
        size_t bits_a,
        size_t bits_b,
        ...); 
/* Basic constructor. Used to multiply polynomials with the given number
 * of bits. Extra (stdarg) arguments may be passed for implementations
 * that have a use for it.  */

static inline void gf2x_cantor_fft_info_clear(
        gf2x_cantor_fft_info_ptr p);
/* Destructor for the info type. */

static inline void gf2x_cantor_fft_info_copy(
        gf2x_cantor_fft_info_ptr p,
        gf2x_cantor_fft_info_srcptr other);
/* Copy constructor. */

extern void GF2X_EXPORTED gf2x_cantor_fft_info_init_similar(
        gf2x_cantor_fft_info_ptr p,
        gf2x_cantor_fft_info_srcptr other,
        size_t bits_a,
        size_t bits_b);
/* Init a transform info type meant to multiply polynomials with the
 * given number of bits, but with the constraint that the transforms
 * obtained this way will be "compatible" with transforms obtained with
 * the other transform info type, in the sense that with appropriate
 * truncation, transforms can meaningfully be composed together.
 * Unfortunately, the API to deal with these is truncation (decimation)
 * operations not complete. */

extern int GF2X_EXPORTED gf2x_cantor_fft_info_compatible(
        gf2x_cantor_fft_info_srcptr p,
        gf2x_cantor_fft_info_srcptr other);
/* Tell whether two info types are compatible in the above sense. */

static inline int gf2x_cantor_fft_info_order(
        gf2x_cantor_fft_info_srcptr p);
/* Return the "order", whatever that means for the underlying info type.  */

extern void GF2X_EXPORTED gf2x_cantor_fft_info_get_alloc_sizes(
        gf2x_cantor_fft_info_srcptr p,
        size_t sizes[3]);
/* Fill the sizes array with three byte counts:
 *     sizes[0] : equivalent to gf2x_cantor_fft_transform_size(p) * sizeof(gf2x_cantor_fft_t)
 *     sizes[1] : number of bytes of temp space that must be passed to each
 *                gf2x_cantor_fft_dft or gf2x_cantor_fft_ift call.
 *     sizes[2] : number of bytes of temp space that must be passed to each
 *                gf2x_cantor_fft_compose, gf2x_cantor_fft_addcompose, or gf2x_cantor_fft_addcompose_n call.
 */

#ifdef __cplusplus
}
#endif

/* End of automatically generated section */

/* define mpfq_2_XXX_elt, but do not include mpfq as it is not part of
 * the set of exported headers.
 */
#if CANTOR_BASE_FIELD_SIZE == 128
#if GF2X_WORDSIZE == 64
typedef unsigned long mpfq_2_128_elt[2];
#else
typedef unsigned long mpfq_2_128_elt[4];
#endif
typedef mpfq_2_128_elt gf2x_cantor_fft_base_field_elt;
#else
#if GF2X_WORDSIZE == 64
typedef unsigned long mpfq_2_64_elt[1];
#else
typedef unsigned long mpfq_2_64_elt[2];
#endif
typedef mpfq_2_64_elt gf2x_cantor_fft_base_field_elt;
#endif
typedef gf2x_cantor_fft_base_field_elt gf2x_cantor_fft_t;
/* The section below is automatically generated */

typedef gf2x_cantor_fft_t * gf2x_cantor_fft_ptr;
typedef const gf2x_cantor_fft_t * gf2x_cantor_fft_srcptr;
/* A transform has type gf2x_cantor_fft_ptr. It is made of a series of gf2x_cantor_fft_t
 * objects. */

#ifdef __cplusplus
extern "C" {
#endif

extern size_t GF2X_EXPORTED gf2x_cantor_fft_transform_size(
        gf2x_cantor_fft_info_srcptr o);
/* Number of gf2x_cantor_fft_t objects it takes to allocate one transform. */

extern gf2x_cantor_fft_ptr GF2X_EXPORTED gf2x_cantor_fft_alloc(
        gf2x_cantor_fft_info_srcptr o,
        size_t n);
/* Allocate space for n transforms. Equivalent to (gf2x_cantor_fft_ptr) malloc(n *
 * gf2x_cantor_fft_transform_size(p) * sizeof(gf2x_cantor_fft_t)); */

extern void GF2X_EXPORTED gf2x_cantor_fft_free(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr ptr,
        size_t n);
/* Free space for n transforms. */

extern gf2x_cantor_fft_ptr GF2X_EXPORTED gf2x_cantor_fft_get(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr ptr,
        size_t k);
/* Get the k-th transform. */

extern gf2x_cantor_fft_srcptr GF2X_EXPORTED gf2x_cantor_fft_get_const(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_srcptr ptr,
        size_t k);
/* Get the k-th transform. */

extern void GF2X_EXPORTED gf2x_cantor_fft_zero(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr ptr,
        size_t n);
/* Zero n consecutive transforms. */

extern void GF2X_EXPORTED gf2x_cantor_fft_cpy(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr y,
        gf2x_cantor_fft_srcptr x,
        size_t n);
/* Copy n consecutive transforms (named "cpy" by analogy to memcpy)/ */

extern void GF2X_EXPORTED gf2x_cantor_fft_add(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr tc,
        gf2x_cantor_fft_srcptr ta,
        gf2x_cantor_fft_srcptr tb);
/* Add two transforms to tc. tc==ta or tc==tb are allowed. */

extern void GF2X_EXPORTED gf2x_cantor_fft_dft(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr tr,
        const unsigned long * a,
        size_t bits_a,
        gf2x_cantor_fft_t * temp1);
/* Compute the dft of the polynomial pointed to by a. Attention: the size
 * is given in number of *bits*, not in number of unsigned longs.  temp1
 * must point to storage of size sizes[1], with sizes[] filled as in the
 * gf2x_cantor_fft_info_get_alloc_sizes call. */

extern void GF2X_EXPORTED gf2x_cantor_fft_ift(
        gf2x_cantor_fft_info_srcptr o,
        unsigned long * c,
        size_t bits_c,
        gf2x_cantor_fft_ptr tr,
        gf2x_cantor_fft_t * temp1);
/* Compute the ift of the transform tr, to polynomial pointed to by c.
 * Attention: the size is given in number of *bits*, not in number of
 * unsigned longs.  temp1 must point to storage of size sizes[1], with
 * sizes[] filled as in the gf2x_cantor_fft_info_get_alloc_sizes call. */

extern void GF2X_EXPORTED gf2x_cantor_fft_compose(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr tc,
        gf2x_cantor_fft_srcptr ta,
        gf2x_cantor_fft_srcptr tb,
        gf2x_cantor_fft_t * temp2);
/* Compose two DFTs.  temp2 must point to storage of size sizes[2], with
 * sizes[] filled as in the gf2x_cantor_fft_info_get_alloc_sizes call. */

extern void GF2X_EXPORTED gf2x_cantor_fft_addcompose_n(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr tc,
        gf2x_cantor_fft_srcptr * ta,
        gf2x_cantor_fft_srcptr * tb,
        size_t n,
        gf2x_cantor_fft_t * temp2);
/* Compose 2n DFTs, and add the result to tc.  temp2 must point to
 * storage of size sizes[2], with sizes[] filled as in the
 * gf2x_cantor_fft_info_get_alloc_sizes call. */

extern void GF2X_EXPORTED gf2x_cantor_fft_addcompose(
        gf2x_cantor_fft_info_srcptr o,
        gf2x_cantor_fft_ptr tc,
        gf2x_cantor_fft_srcptr ta,
        gf2x_cantor_fft_srcptr tb,
        gf2x_cantor_fft_t * temp2);
/* Compose 2 DFTs, and add the result to tc.  temp2 must point to storage
 * of size sizes[2], with sizes[] filled as in the
 * gf2x_cantor_fft_info_get_alloc_sizes call. */

#ifdef __cplusplus
}
#endif

/* End of automatically generated section */

struct gf2x_cantor_fft_info {
    unsigned int k;
    size_t n;
    /* The section below is automatically generated */
    /* pod: yes */
#ifdef __cplusplus

    typedef gf2x_cantor_fft_ptr ptr;
    typedef gf2x_cantor_fft_srcptr srcptr;

    inline gf2x_cantor_fft_info(size_t nF, size_t nG)
    {
        gf2x_cantor_fft_info_init(this, nF, nG);
    }
    ~gf2x_cantor_fft_info() = default;
    gf2x_cantor_fft_info(gf2x_cantor_fft_info const &) = default;
    inline gf2x_cantor_fft_info(gf2x_cantor_fft_info const & other, size_t nF, size_t nG)
    {
        gf2x_cantor_fft_info_init_similar(this, &other, nF, nG);
    }
    inline bool compatible(gf2x_cantor_fft_info const & other) const {
        return gf2x_cantor_fft_info_compatible(this, &other);
    }
    inline int order() const {
        return gf2x_cantor_fft_info_order(this);
    }
    inline void get_alloc_sizes(size_t sizes[3]) {
        gf2x_cantor_fft_info_get_alloc_sizes(this, sizes);
    }
    inline size_t transform_size() const { return gf2x_cantor_fft_transform_size(this); }
    inline ptr alloc(size_t n = 1) { return gf2x_cantor_fft_alloc(this, n); }
    inline void free(ptr x, size_t n = 1) { gf2x_cantor_fft_free(this, x, n); }
    inline ptr get(ptr x, size_t k) const { return gf2x_cantor_fft_get(this, x, k); }
    inline srcptr get(srcptr x, size_t k) const { return gf2x_cantor_fft_get_const(this, x, k); }
    inline void zero(ptr x, size_t n = 1) { gf2x_cantor_fft_zero(this, x, n); }
    inline void dft(ptr x,
            const unsigned long * F,
            size_t nF,
            gf2x_cantor_fft_t * temp1)
    {
        gf2x_cantor_fft_dft(this, x, F, nF, temp1);
    }
    inline void compose(
            ptr y,
            srcptr x1,
            srcptr x2,
            gf2x_cantor_fft_t * temp2)
    {
        gf2x_cantor_fft_compose(this, y, x1, x2, temp2);
    }
    inline void addcompose(
            ptr y,
            srcptr x1,
            srcptr x2,
            gf2x_cantor_fft_t * temp2)
    {
        gf2x_cantor_fft_addcompose(this, y, x1, x2, temp2);
    }
    inline void addcompose_n(
            ptr y,
            srcptr * x1,
            srcptr * x2,
            size_t n,
            gf2x_cantor_fft_t * temp2)
    {
        gf2x_cantor_fft_addcompose_n(this, y, x1, x2, n, temp2);
    }
    inline void add(
            ptr y,
            srcptr x1,
            srcptr x2)
    {
        gf2x_cantor_fft_add(this, y, x1, x2);
    }
    inline void cpy(
            ptr y,
            srcptr x,
            size_t n)
    {
        gf2x_cantor_fft_cpy(this, y, x, n);
    }
    inline void ift(
            unsigned long * H,
            size_t Hl,
            ptr h,
            gf2x_cantor_fft_t * temp1)
    {
        gf2x_cantor_fft_ift(this, H, Hl, h, temp1);
    }
#endif

    /* End of automatically generated section */
};
/* The section below is automatically generated */
/* Now that gf2x_cantor_fft_info is declared completely, we may declare the 1-sized
 * array */
typedef struct gf2x_cantor_fft_info gf2x_cantor_fft_info_t[1];
/* End of automatically generated section */

#ifdef __cplusplus
extern "C" {
#endif

static inline void gf2x_cantor_fft_info_clear(gf2x_cantor_fft_info_t p)
{
    memset(p, 0, sizeof(gf2x_cantor_fft_info_t));
}

static inline void gf2x_cantor_fft_info_copy(
        gf2x_cantor_fft_info_ptr o,
        gf2x_cantor_fft_info_srcptr other)
{
        memcpy(o, other, sizeof(struct gf2x_cantor_fft_info));
}
static inline int gf2x_cantor_fft_info_order(gf2x_cantor_fft_info_srcptr o) { return o->k; }

#ifdef __cplusplus
}
#endif

#endif	/* GF2X_FFT_CANTOR_H_ */
