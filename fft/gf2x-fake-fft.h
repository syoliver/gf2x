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

#ifndef GF2X_FAKE_FFT_H_
#define GF2X_FAKE_FFT_H_

#include <stdlib.h>
#include <string.h>

#include "gf2x/gf2x-config-export.h"
#include "gf2x/gf2x-impl-export.h"
#include "gf2x/gf2x-thresholds.h"

#ifndef GF2X_EXPORTED
#define GF2X_EXPORTED
#endif

/* This file is a placeholder for the typical requirements of an FFT
 * interface. Of course, there is nothing interesting being done here.
 * It's just an E-X-A-M-P-L-E. See also the .c file.
 */

/* The section below is automatically generated */
/* inline: init_empty clear copy compatible order */

#ifndef GF2X_FFT_EXPORTED
#define GF2X_FFT_EXPORTED
#endif

struct gf2x_fake_fft_info;
// gf2x_fake_fft_info_t is defined after the struct fields.
// typedef struct gf2x_fake_fft_info gf2x_fake_fft_info_t[1];
typedef struct gf2x_fake_fft_info * gf2x_fake_fft_info_ptr;
typedef const struct gf2x_fake_fft_info * gf2x_fake_fft_info_srcptr;

/* gf2x_fake_fft_info is an implementation-defined structure that holds important
 * auxiliary data, used for dealing with transforms. This structure may
 * or may not consist of plain-old datatypes only, so that it only
 * possible to copy it with care (see below).  
 * 
 * C code should use gf2x_fake_fft_info_t preferrably, as it provides transparent
 * conversion to a pointer, and yet defines storage as well (à la GMP).
 *
 * C++ code should use gf2x_fake_fft_info.  When the header is included from C++
 * code, the api below is also exported as member functions of gf2x_fake_fft_info.
 * The info type is default-constructible in all cases, but not always
 * trivially copyable.
 *
 * gf2x_fake_fft_info_ptr and gf2x_fake_fft_info_srcptr are auxiliary types used in C
 * prototypes. C++ code should prefer references and const references to
 * gf2x_fake_fft_info.
 */

#ifdef __cplusplus
extern "C" {
#endif

extern int GF2X_FFT_EXPORTED gf2x_fake_fft_info_init(
        gf2x_fake_fft_info_ptr p,
        size_t bits_a,
        size_t bits_b,
        ...); 
/* Basic constructor. Used to multiply polynomials with the given number
 * of bits. Extra (stdarg) arguments may be passed for implementations
 * that have a use for it.
 *
 * Returns 0 if everything went well, and a negative number on error
 * (maybe if the extra arguments were incorrect)
 *
 */

extern int GF2X_FFT_EXPORTED gf2x_fake_fft_info_init_mp(
        gf2x_fake_fft_info_ptr p,
        size_t bits_a,
        size_t bits_b,
        ...); 
/* Used to compute middle products of polynomials with the given number
 * of bits. That is, the result MP(a, b) consists of coefficients of
 * degrees MIN(bits_a, bits_b)-1 to MAX(bits_a, bits_b)-1 (inclusive),
 * forming a result with MAX(bits_a, bits_b)-MIN(bits_a, bits_b)+1
 * coefficients.  Extra (stdarg) arguments may be passed for
 * implementations that have a use for it.
 *
 * Returns 0 if everything went well, and a negative number on error
 * (maybe if the extra arguments were incorrect)
 *
 */

static inline void gf2x_fake_fft_info_init_empty(
        gf2x_fake_fft_info_ptr p);
/* This is not really a constructor. Most often we expect this function
 * to be a noop, or at most an inline. It is just meant to provide some
 * default-initialization, so that info_clear does not choke.
 */

static inline void gf2x_fake_fft_info_clear(
        gf2x_fake_fft_info_ptr p);
/* Destructor for the info type. */

static inline int gf2x_fake_fft_info_copy(
        gf2x_fake_fft_info_ptr p,
        gf2x_fake_fft_info_srcptr other);
/* Copy constructor. Returns 0 on success or GF2X_ERROR_OUT_OF_MEMORY.*/

extern int GF2X_FFT_EXPORTED gf2x_fake_fft_info_init_similar(
        gf2x_fake_fft_info_ptr p,
        gf2x_fake_fft_info_srcptr other,
        size_t bits_a,
        size_t bits_b);
/* Init a transform info type meant to multiply polynomials with the
 * given number of bits, but with the constraint that the transforms
 * obtained this way will be "compatible" with transforms obtained with
 * the other transform info type, in the sense that with appropriate
 * truncation, transforms can meaningfully be composed together.
 * Unfortunately, the API to deal with these is truncation (decimation)
 * operations not complete.
 * Returns 0 on success or GF2X_ERROR_OUT_OF_MEMORY.*/

static inline int gf2x_fake_fft_info_compatible(
        gf2x_fake_fft_info_srcptr p,
        gf2x_fake_fft_info_srcptr other);
/* Tell whether two info types are compatible in the above sense. */

static inline int gf2x_fake_fft_info_order(
        gf2x_fake_fft_info_srcptr p);
/* Return the "order", whatever that means for the underlying info type.  */

extern void GF2X_FFT_EXPORTED gf2x_fake_fft_info_get_alloc_sizes(
        gf2x_fake_fft_info_srcptr p,
        size_t sizes[3]);
/* Fill the sizes array with three byte counts:
 *     sizes[0] : equivalent to gf2x_fake_fft_transform_size(p) * sizeof(gf2x_fake_fft_t)
 *     sizes[1] : number of bytes of temp space that must be passed to each
 *                gf2x_fake_fft_dft or gf2x_fake_fft_ift call.
 *     sizes[2] : number of bytes of temp space that must be passed to each
 *                gf2x_fake_fft_compose, gf2x_fake_fft_addcompose, or gf2x_fake_fft_addcompose_n call.
 *                Note that the addcompose variants need two temp
 *                buffers, of sizes sizes[2] and sizes[1], respectively.
 */

#ifdef __cplusplus
}
#endif

/* End of automatically generated section */

typedef unsigned long gf2x_fake_fft_t;

/* The section below is automatically generated */
/* inline: transform_size alloc free get get_const zero cpy */
/* inline: export import prepare check */

typedef gf2x_fake_fft_t * gf2x_fake_fft_ptr;
typedef const gf2x_fake_fft_t * gf2x_fake_fft_srcptr;
/* A transform has type gf2x_fake_fft_ptr. It is made of a series of gf2x_fake_fft_t
 * objects. */

#ifdef __cplusplus
extern "C" {
#endif

static inline size_t gf2x_fake_fft_transform_size(
        gf2x_fake_fft_info_srcptr o);
/* Number of gf2x_fake_fft_t objects it takes to allocate one transform. */

static inline gf2x_fake_fft_ptr gf2x_fake_fft_alloc(
        gf2x_fake_fft_info_srcptr o,
        size_t n);
/* Allocate space for n transforms. Equivalent to (gf2x_fake_fft_ptr) malloc(n *
 * gf2x_fake_fft_transform_size(p) * sizeof(gf2x_fake_fft_t)); */

static inline void gf2x_fake_fft_free(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr ptr,
        size_t n);
/* Free space for n transforms. */

static inline gf2x_fake_fft_ptr gf2x_fake_fft_get(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr ptr,
        size_t k);
/* Get the k-th transform. */

static inline gf2x_fake_fft_srcptr gf2x_fake_fft_get_const(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_srcptr ptr,
        size_t k);
/* Get the k-th transform. */

static inline void gf2x_fake_fft_zero(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr ptr,
        size_t n);
/* Zero n consecutive transforms. */

static inline void gf2x_fake_fft_cpy(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr y,
        gf2x_fake_fft_srcptr x,
        size_t n);
/* Copy n consecutive transforms (named "cpy" by analogy to memcpy)/ */

static inline void gf2x_fake_fft_export(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr ptr,
        size_t n);
/* Export (serialize) n consecutive transforms in place. This is a noop
 * if the transforms are free of any pointers, which is always the case
 * with gf2x. */

static inline void gf2x_fake_fft_import(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr ptr,
        size_t n);
/* Import (deserialize) n consecutive transforms in place. This is a noop
 * if the transforms are free of any pointers, which is always the case
 * with gf2x. */

static inline void gf2x_fake_fft_prepare(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr ptr,
        size_t n);
/* Prepare n consecutive transforms in place so that they're
 * pointer-correct, but do not set any of the internal data. It is
 * conceivably simpler than gf2x_fake_fft_zero. This is a noop if the transforms
 * are free of any pointers, which is always the case with gf2x. */

static inline int gf2x_fake_fft_check(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_srcptr ptr,
        size_t n,
        int printf_diagnostics);
/* Checks that the n consecutive transforms are valid (in particular,
 * pointer-correct if relevant). This might be a noop if the transforms
 * are free of any pointers, which is always the case with gf2x. */

#if 0 && defined(__GNU_MP__) /* we don't want a gmp dependency... */
extern void GF2X_FFT_EXPORTED gf2x_fake_fft_fill_random(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr ptr,
        size_t n,
        gmp_randstate_t rstate);
/* fill n consecutive transforms with random data from the provided
 * random state.
 */
#endif

extern void GF2X_FFT_EXPORTED gf2x_fake_fft_add(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr tc,
        gf2x_fake_fft_srcptr ta,
        gf2x_fake_fft_srcptr tb);
/* Add two transforms to tc. tc==ta or tc==tb are allowed. */

extern int GF2X_FFT_EXPORTED gf2x_fake_fft_dft(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr tr,
        const unsigned long * a,
        size_t bits_a,
        gf2x_fake_fft_ptr temp1);
/* Compute the dft of the polynomial pointed to by a. Attention: the size
 * is given in number of *bits*, not in number of unsigned longs.  temp1
 * must point to storage of size sizes[1], with sizes[] filled as in the
 * gf2x_fake_fft_info_get_alloc_sizes call.
 *
 * Returns 0 on success or GF2X_ERROR_OUT_OF_MEMORY (only minor extra
 * allocation is needed by some implementations).
 */

extern int GF2X_FFT_EXPORTED gf2x_fake_fft_ift(
        gf2x_fake_fft_info_srcptr o,
        unsigned long * c,
        size_t bits_c,
        gf2x_fake_fft_ptr tr,
        gf2x_fake_fft_ptr temp1);
/* Compute the ift of the transform tr, to polynomial pointed to by c.
 * Attention: the size is given in number of *bits*, not in number of
 * unsigned longs.  temp1 must point to storage of size sizes[1], with
 * sizes[] filled as in the gf2x_fake_fft_info_get_alloc_sizes call.
 *
 * Returns 0 on success or GF2X_ERROR_OUT_OF_MEMORY (only minor extra
 * allocation is needed by some implementations).
 */

extern int GF2X_FFT_EXPORTED gf2x_fake_fft_compose(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr tc,
        gf2x_fake_fft_srcptr ta,
        gf2x_fake_fft_srcptr tb,
        gf2x_fake_fft_ptr temp2);
/* Compose two DFTs.  temp2 must point to storage of size sizes[2], with
 * sizes[] filled as in the gf2x_fake_fft_info_get_alloc_sizes call.
 *
 * Returns 0 on success or GF2X_ERROR_OUT_OF_MEMORY (only minor extra
 * allocation is needed by some implementations).
 */

extern int GF2X_FFT_EXPORTED gf2x_fake_fft_addcompose_n(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr tc,
        gf2x_fake_fft_srcptr * ta,
        gf2x_fake_fft_srcptr * tb,
        size_t n,
        gf2x_fake_fft_ptr temp2,
        gf2x_fake_fft_ptr temp1);
/* Compose 2n DFTs, and add the result to tc. temp1 and temp2 must point to
 * storage of size sizes[1] and sizes[2], respectively, with sizes[]
 * filled as in the gf2x_fake_fft_info_get_alloc_sizes call.
 *
 * Returns 0 on success or GF2X_ERROR_OUT_OF_MEMORY (only minor extra
 * allocation is needed by some implementations).
 */

extern int GF2X_FFT_EXPORTED gf2x_fake_fft_addcompose(
        gf2x_fake_fft_info_srcptr o,
        gf2x_fake_fft_ptr tc,
        gf2x_fake_fft_srcptr ta,
        gf2x_fake_fft_srcptr tb,
        gf2x_fake_fft_ptr temp2,
        gf2x_fake_fft_ptr temp1);
/* Compose 2 DFTs, and add the result to tc. temp1 and temp2 must point to
 * storage of size sizes[1] and sizes[2], respectively, with sizes[]
 * filled as in the gf2x_fake_fft_info_get_alloc_sizes call.
 *
 * Returns 0 on success or GF2X_ERROR_OUT_OF_MEMORY (only minor extra
 * allocation is needed by some implementations).
 */

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <exception>
#endif

/* End of automatically generated section */


struct gf2x_fake_fft_info {
    size_t n1,n2,n3;
    size_t size;
    size_t mp_shift;

    /* The section below is automatically generated */
    /* pod: yes */
#ifdef __cplusplus

    class ctor_fails: public std::exception
    {
      virtual const char* what() const throw() {
        return "contructor failed for gf2x_fake_fft";
      }
    };

    typedef gf2x_fake_fft_ptr ptr;
    typedef gf2x_fake_fft_srcptr srcptr;

    inline gf2x_fake_fft_info() = default;
    inline gf2x_fake_fft_info(size_t nF, size_t nG)
    {
        if (gf2x_fake_fft_info_init(this, nF, nG) < 0)
            throw ctor_fails();
    }
    inline ~gf2x_fake_fft_info() = default;
    inline gf2x_fake_fft_info(gf2x_fake_fft_info const &) = default;
    inline gf2x_fake_fft_info& operator=(gf2x_fake_fft_info const &) = default;
    inline gf2x_fake_fft_info(gf2x_fake_fft_info const & other, size_t nF, size_t nG)
    {
        if (gf2x_fake_fft_info_init_similar(this, &other, nF, nG) < 0)
            throw ctor_fails();
    }
    /* Use named constructor idiom for the variants */
    inline static gf2x_fake_fft_info mul_info(size_t nF, size_t nG) {
        gf2x_fake_fft_info a;
        if (gf2x_fake_fft_info_init(&a, nF, nG) < 0)
            throw ctor_fails();
        return a;
    }
    inline static gf2x_fake_fft_info mp_info(size_t nF, size_t nG) {
        gf2x_fake_fft_info a;
        if (gf2x_fake_fft_info_init_mp(&a, nF, nG) < 0)
            throw ctor_fails();
        return a;
    }
    inline bool compatible(gf2x_fake_fft_info const & other) const {
        return gf2x_fake_fft_info_compatible(this, &other);
    }
    inline int order() const {
        return gf2x_fake_fft_info_order(this);
    }
    inline void get_alloc_sizes(size_t sizes[3]) const {
        gf2x_fake_fft_info_get_alloc_sizes(this, sizes);
    }
    inline size_t transform_size() const { return gf2x_fake_fft_transform_size(this); }
    inline ptr alloc(size_t n = 1) const { return gf2x_fake_fft_alloc(this, n); }
    inline void free(ptr x, size_t n = 1) const { gf2x_fake_fft_free(this, x, n); }
    inline ptr get(ptr x, size_t k) const { return gf2x_fake_fft_get(this, x, k); }
    inline srcptr get(srcptr x, size_t k) const { return gf2x_fake_fft_get_const(this, x, k); }
    inline void zero(ptr x, size_t n = 1) const { gf2x_fake_fft_zero(this, x, n); }
    inline void to_export(ptr x, size_t n = 1) const { gf2x_fake_fft_export(this, x, n); }
    inline void to_import(ptr x, size_t n = 1) const { gf2x_fake_fft_import(this, x, n); }
    inline void prepare(ptr x, size_t n = 1) const { gf2x_fake_fft_prepare(this, x, n); }
    inline bool check(srcptr x, size_t n, bool printf_diagnostics) const { return gf2x_fake_fft_check(this, x, n, printf_diagnostics); }
    inline bool check(srcptr x, bool printf_diagnostics) const { return gf2x_fake_fft_check(this, x, 1, printf_diagnostics); }
#if 0 && defined(__GNU_MP__) /* we don't want a gmp dependency... */
    inline void fill_random(ptr x, size_t n, gmp_randstate_t rstate) const {
        gf2x_fake_fft_fill_random(x, n, rstate);
    }
    inline void fill_random(ptr x, gmp_randstate_t rstate) const {
        gf2x_fake_fft_fill_random(x, 1, rstate);
    }
#endif

    inline int dft(ptr x, const unsigned long * F, size_t nF, ptr temp1) const {
        return gf2x_fake_fft_dft(this, x, F, nF, temp1);
    }
    inline int compose(ptr y, srcptr x1, srcptr x2, ptr temp2) const
    {
        return gf2x_fake_fft_compose(this, y, x1, x2, temp2);
    }
    inline int addcompose(ptr y, srcptr x1, srcptr x2, ptr temp2, ptr temp1) const
    {
        return gf2x_fake_fft_addcompose(this, y, x1, x2, temp2, temp1);
    }
    inline int addcompose_n(ptr y, srcptr * x1, srcptr * x2, size_t n, ptr temp2, ptr temp1) const
    {
        return gf2x_fake_fft_addcompose_n(this, y, x1, x2, n, temp2, temp1);
    }
    inline void add(ptr y, srcptr x1, srcptr x2) const
    {
        gf2x_fake_fft_add(this, y, x1, x2);
    }
    inline void cpy(ptr y, srcptr x, size_t n) const
    {
        gf2x_fake_fft_cpy(this, y, x, n);
    }
    inline int ift(unsigned long * H, size_t Hl, ptr h, ptr temp1) const
    {
        return gf2x_fake_fft_ift(this, H, Hl, h, temp1);
    }
#endif

    /* End of automatically generated section */
};
/* The section below is automatically generated */
/* Now that gf2x_fake_fft_info is declared completely, we may declare the 1-sized
 * array */
typedef struct gf2x_fake_fft_info gf2x_fake_fft_info_t[1];
/* End of automatically generated section */

#ifdef __cplusplus
extern "C" {
#endif

static inline void gf2x_fake_fft_info_clear(
        gf2x_fake_fft_info_ptr p GF2X_MAYBE_UNUSED)
{}
static inline void gf2x_fake_fft_info_init_empty(
        gf2x_fake_fft_info_ptr p)
{
    p->n1 = p->n2 = p->n3 = p->size = 0;
}
static inline int gf2x_fake_fft_info_copy(
        gf2x_fake_fft_info_ptr o,
        gf2x_fake_fft_info_srcptr other)
{
        memcpy(o, other, sizeof(struct gf2x_fake_fft_info));
        return 0;
}
static inline int gf2x_fake_fft_info_compatible(
        gf2x_fake_fft_info_srcptr o1 GF2X_MAYBE_UNUSED,
        gf2x_fake_fft_info_srcptr o2 GF2X_MAYBE_UNUSED)
{
        return 1;
}
static inline int gf2x_fake_fft_info_order(
        gf2x_fake_fft_info_srcptr o GF2X_MAYBE_UNUSED)
{
        return 0;
}


static inline size_t gf2x_fake_fft_transform_size(gf2x_fake_fft_info_srcptr p)
{
        return p->size;
}

static inline gf2x_fake_fft_ptr gf2x_fake_fft_alloc(
        gf2x_fake_fft_info_srcptr p,
        size_t n)
{
        return (gf2x_fake_fft_ptr) malloc(n * gf2x_fake_fft_transform_size(p) * sizeof(gf2x_fake_fft_t));
}

static inline void gf2x_fake_fft_free(
        gf2x_fake_fft_info_srcptr p GF2X_MAYBE_UNUSED,
        gf2x_fake_fft_ptr x,
        size_t n GF2X_MAYBE_UNUSED)
{
        free(x);
}
static inline gf2x_fake_fft_ptr gf2x_fake_fft_get(gf2x_fake_fft_info_srcptr p, gf2x_fake_fft_ptr x, size_t k)
{
        return x + k * gf2x_fake_fft_transform_size(p);
}
static inline gf2x_fake_fft_srcptr gf2x_fake_fft_get_const(gf2x_fake_fft_info_srcptr p, gf2x_fake_fft_srcptr x, size_t k)
{
        return x + k * gf2x_fake_fft_transform_size(p);
}
static inline void gf2x_fake_fft_zero(gf2x_fake_fft_info_srcptr p, gf2x_fake_fft_ptr x, size_t n)
{
        memset(x, 0, n * gf2x_fake_fft_transform_size(p) * sizeof(gf2x_fake_fft_t));
}
static inline void gf2x_fake_fft_cpy(gf2x_fake_fft_info_srcptr p, gf2x_fake_fft_ptr y, gf2x_fake_fft_srcptr x, size_t n)
{
    memcpy(y, x, n * gf2x_fake_fft_transform_size(p) * sizeof(gf2x_fake_fft_t));
}

static inline void gf2x_fake_fft_export(
        gf2x_fake_fft_info_srcptr o GF2X_MAYBE_UNUSED,
        gf2x_fake_fft_ptr ptr GF2X_MAYBE_UNUSED,
        size_t n GF2X_MAYBE_UNUSED) {}
static inline void gf2x_fake_fft_import(
        gf2x_fake_fft_info_srcptr o GF2X_MAYBE_UNUSED,
        gf2x_fake_fft_ptr ptr GF2X_MAYBE_UNUSED,
        size_t n GF2X_MAYBE_UNUSED) {}
static inline void gf2x_fake_fft_prepare(
        gf2x_fake_fft_info_srcptr o GF2X_MAYBE_UNUSED,
        gf2x_fake_fft_ptr ptr GF2X_MAYBE_UNUSED,
        size_t n GF2X_MAYBE_UNUSED) {}
static inline int gf2x_fake_fft_check(
        gf2x_fake_fft_info_srcptr o GF2X_MAYBE_UNUSED,
        gf2x_fake_fft_srcptr ptr GF2X_MAYBE_UNUSED,
        size_t n GF2X_MAYBE_UNUSED,
        int printf_diagnostics GF2X_MAYBE_UNUSED) { return 1; }

#ifdef __cplusplus
}
#endif

#endif	/* GF2X_FAKE_FFT_H_ */
/* vim: set sw=4 sta et: */
