#include <cstdlib>

/* This file is not a C header file. It is used to query-replace the FFT
 * api into the gf2x-*-fft.h header files.
 */

/* BEGIN SECTION 1: the typical interface for XXX_info */

struct XXX_info;
// XXX_info_t is defined after the struct fields.
// typedef struct XXX_info XXX_info_t[1];
typedef struct XXX_info * XXX_info_ptr;
typedef const struct XXX_info * XXX_info_srcptr;

/* XXX_info is an implementation-defined structure that holds important
 * auxiliary data, used for dealing with transforms. This structure may
 * or may not consist of plain-old datatypes only, so that it only
 * possible to copy it with care (see below).  
 * 
 * C code should use XXX_info_t preferrably, as it provides transparent
 * conversion to a pointer, and yet defines storage as well (à la GMP).
 *
 * C++ code should use XXX_info.  When the header is included from C++
 * code, the api below is also exported as member functions of XXX_info.
 * The info type is default-constructible in all cases, but not always
 * trivially copyable.
 *
 * XXX_info_ptr and XXX_info_srcptr are auxiliary types used in C
 * prototypes. C++ code should prefer references and const references to
 * XXX_info.
 */

#ifdef __cplusplus
extern "C" {
#endif

void XXX_info_init(
        XXX_info_ptr p,
        size_t bits_a,
        size_t bits_b,
        ...); 
/* Basic constructor. Used to multiply polynomials with the given number
 * of bits. Extra (stdarg) arguments may be passed for implementations
 * that have a use for it.  */

void XXX_info_clear(
        XXX_info_ptr p);
/* Destructor for the info type. */

void XXX_info_copy(
        XXX_info_ptr p,
        XXX_info_srcptr other);
/* Copy constructor. */

void XXX_info_init_similar(
        XXX_info_ptr p,
        XXX_info_srcptr other,
        size_t bits_a,
        size_t bits_b);
/* Init a transform info type meant to multiply polynomials with the
 * given number of bits, but with the constraint that the transforms
 * obtained this way will be "compatible" with transforms obtained with
 * the other transform info type, in the sense that with appropriate
 * truncation, transforms can meaningfully be composed together.
 * Unfortunately, the API to deal with these is truncation (decimation)
 * operations not complete. */

int XXX_info_compatible(
        XXX_info_srcptr p,
        XXX_info_srcptr other);
/* Tell whether two info types are compatible in the above sense. */

int XXX_info_order(
        XXX_info_srcptr p);
/* Return the "order", whatever that means for the underlying info type.  */

void XXX_info_get_alloc_sizes(
        XXX_info_srcptr p,
        size_t sizes[3]);
/* Fill the sizes array with three byte counts:
 *     sizes[0] : equivalent to XXX_transform_size(p) * sizeof(XXX_t)
 *     sizes[1] : number of bytes of temp space that must be passed to each
 *                XXX_dft or XXX_ift call.
 *     sizes[2] : number of bytes of temp space that must be passed to each
 *                XXX_compose, XXX_addcompose, or XXX_addcompose_n call.
 *                Note that the addcompose variants need two temp
 *                buffers, of sizes sizes[2] and sizes[1], respectively.
 */

#ifdef __cplusplus
}
#endif

/* END SECTION 1 */

typedef int /* implementation-defined */ XXX_t;

/* BEGIN SECTION 2: the typical interface for transforms that use XXX_info */

typedef XXX_t * XXX_ptr;
typedef const XXX_t * XXX_srcptr;
/* A transform has type XXX_ptr. It is made of a series of XXX_t
 * objects. */

#ifdef __cplusplus
extern "C" {
#endif

size_t XXX_transform_size(
        XXX_info_srcptr o);
/* Number of XXX_t objects it takes to allocate one transform. */

XXX_ptr XXX_alloc(
        XXX_info_srcptr o,
        size_t n);
/* Allocate space for n transforms. Equivalent to (XXX_ptr) malloc(n *
 * XXX_transform_size(p) * sizeof(XXX_t)); */

void XXX_free(
        XXX_info_srcptr o,
        XXX_ptr ptr,
        size_t n);
/* Free space for n transforms. */

XXX_ptr XXX_get(
        XXX_info_srcptr o,
        XXX_ptr ptr,
        size_t k);
/* Get the k-th transform. */

XXX_srcptr XXX_get_const(
        XXX_info_srcptr o,
        XXX_srcptr ptr,
        size_t k);
/* Get the k-th transform. */

void XXX_zero(
        XXX_info_srcptr o,
        XXX_ptr ptr,
        size_t n);
/* Zero n consecutive transforms. */

void XXX_cpy(
        XXX_info_srcptr o,
        XXX_ptr y,
        XXX_srcptr x,
        size_t n);
/* Copy n consecutive transforms (named "cpy" by analogy to memcpy)/ */

void XXX_export(
        XXX_info_srcptr o,
        XXX_ptr ptr,
        size_t n);
/* Export (serialize) n consecutive transforms in place. This is a noop
 * if the transforms are free of any pointers, which is always the case
 * with gf2x. */

void XXX_import(
        XXX_info_srcptr o,
        XXX_ptr ptr,
        size_t n);
/* Import (deserialize) n consecutive transforms in place. This is a noop
 * if the transforms are free of any pointers, which is always the case
 * with gf2x. */

void XXX_prepare(
        XXX_info_srcptr o,
        XXX_ptr ptr,
        size_t n);
/* Prepare n consecutive transforms in place so that they're
 * pointer-correct, but do not set any of the internal data. It is
 * conceivably simpler than XXX_zero. This is a noop if the transforms
 * are free of any pointers, which is always the case with gf2x. */

int XXX_check(
        XXX_info_srcptr o,
        XXX_srcptr ptr,
        size_t n,
        int printf_diagnostics);
/* Checks that the n consecutive transforms are valid (in particular,
 * pointer-correct if relevant). This might be a noop if the transforms
 * are free of any pointers, which is always the case with gf2x. */

#if 0 && defined(__GNU_MP__) /* we don't want a gmp dependency... */
void XXX_fill_random(
        XXX_info_srcptr o,
        XXX_ptr ptr,
        size_t n,
        gmp_randstate_t rstate);
/* fill n consecutive transforms with random data from the provided
 * random state.
 */
#endif

void XXX_add(
        XXX_info_srcptr o,
        XXX_ptr tc,
        XXX_srcptr ta,
        XXX_srcptr tb);
/* Add two transforms to tc. tc==ta or tc==tb are allowed. */

void XXX_dft(
        XXX_info_srcptr o,
        XXX_ptr tr,
        const unsigned long * a,
        size_t bits_a,
        XXX_ptr temp1);
/* Compute the dft of the polynomial pointed to by a. Attention: the size
 * is given in number of *bits*, not in number of unsigned longs.  temp1
 * must point to storage of size sizes[1], with sizes[] filled as in the
 * XXX_info_get_alloc_sizes call. */

void XXX_ift(
        XXX_info_srcptr o,
        unsigned long * c,
        size_t bits_c,
        XXX_ptr tr,
        XXX_ptr temp1);
/* Compute the ift of the transform tr, to polynomial pointed to by c.
 * Attention: the size is given in number of *bits*, not in number of
 * unsigned longs.  temp1 must point to storage of size sizes[1], with
 * sizes[] filled as in the XXX_info_get_alloc_sizes call. */

void XXX_compose(
        XXX_info_srcptr o,
        XXX_ptr tc,
        XXX_srcptr ta,
        XXX_srcptr tb,
        XXX_ptr temp2);
/* Compose two DFTs.  temp2 must point to storage of size sizes[2], with
 * sizes[] filled as in the XXX_info_get_alloc_sizes call. */

void XXX_addcompose_n(
        XXX_info_srcptr o,
        XXX_ptr tc,
        XXX_srcptr * ta,
        XXX_srcptr * tb,
        size_t n,
        XXX_ptr temp2,
        XXX_ptr temp1);
/* Compose 2n DFTs, and add the result to tc. temp1 and temp2 must point to
 * storage of size sizes[1] and sizes[2], respectively, with sizes[]
 * filled as in the XXX_info_get_alloc_sizes call. */

void XXX_addcompose(
        XXX_info_srcptr o,
        XXX_ptr tc,
        XXX_srcptr ta,
        XXX_srcptr tb,
        XXX_ptr temp2,
        XXX_ptr temp1);
/* Compose 2 DFTs, and add the result to tc. temp1 and temp2 must point to
 * storage of size sizes[1] and sizes[2], respectively, with sizes[]
 * filled as in the XXX_info_get_alloc_sizes call. */

#ifdef __cplusplus
}
#endif

/* END SECTION 2 */

struct XXX_info {
    /* implementation-defined fields */

    /* BEGIN SECTION 3: member function proxies for the XXX_info type */
#ifdef __cplusplus

    typedef XXX_ptr ptr;
    typedef XXX_srcptr srcptr;

    inline XXX_info(size_t nF, size_t nG)
    {
        XXX_info_init(this, nF, nG);
    }
    ~XXX_info() {
        XXX_info_clear(this);
    }
    XXX_info(XXX_info const & o) {
        XXX_info_copy(this, &o);
    }
    inline XXX_info(XXX_info const & other, size_t nF, size_t nG)
    {
        XXX_info_init_similar(this, &other, nF, nG);
    }
    inline bool compatible(XXX_info const & other) const {
        return XXX_info_compatible(this, &other);
    }
    inline int order() const {
        return XXX_info_order(this);
    }
    inline void get_alloc_sizes(size_t sizes[3]) const {
        XXX_info_get_alloc_sizes(this, sizes);
    }
    inline size_t transform_size() const { return XXX_transform_size(this); }
    inline ptr alloc(size_t n = 1) const { return XXX_alloc(this, n); }
    inline void free(ptr x, size_t n = 1) const { XXX_free(this, x, n); }
    inline ptr get(ptr x, size_t k) const { return XXX_get(this, x, k); }
    inline srcptr get(srcptr x, size_t k) const { return XXX_get_const(this, x, k); }
    inline void zero(ptr x, size_t n = 1) const { XXX_zero(this, x, n); }
    inline void to_export(ptr x, size_t n = 1) const { XXX_export(this, x, n); }
    inline void to_import(ptr x, size_t n = 1) const { XXX_import(this, x, n); }
    inline void prepare(ptr x, size_t n = 1) const { XXX_prepare(this, x, n); }
    inline bool check(srcptr x, size_t n, bool printf_diagnostics) const { return XXX_check(this, x, n, printf_diagnostics); }
    inline bool check(srcptr x, bool printf_diagnostics) const { return XXX_check(this, x, 1, printf_diagnostics); }
#if 0 && defined(__GNU_MP__) /* we don't want a gmp dependency... */
    inline void fill_random(ptr x, size_t n, gmp_randstate_t rstate) const {
        XXX_fill_random(x, n, rstate);
    }
    inline void fill_random(ptr x, gmp_randstate_t rstate) const {
        XXX_fill_random(x, 1, rstate);
    }
#endif

    inline void dft(ptr x, const unsigned long * F, size_t nF, ptr temp1) const {
        XXX_dft(this, x, F, nF, temp1);
    }
    inline void compose(ptr y, srcptr x1, srcptr x2, ptr temp2) const
    {
        XXX_compose(this, y, x1, x2, temp2);
    }
    inline void addcompose(ptr y, srcptr x1, srcptr x2, ptr temp2, ptr temp1) const
    {
        XXX_addcompose(this, y, x1, x2, temp2, temp1);
    }
    inline void addcompose_n(ptr y, srcptr * x1, srcptr * x2, size_t n, ptr temp2, ptr temp1) const
    {
        XXX_addcompose_n(this, y, x1, x2, n, temp2, temp1);
    }
    inline void add(ptr y, srcptr x1, srcptr x2) const
    {
        XXX_add(this, y, x1, x2);
    }
    inline void cpy(ptr y, srcptr x, size_t n) const
    {
        XXX_cpy(this, y, x, n);
    }
    inline void ift(unsigned long * H, size_t Hl, ptr h, ptr temp1) const
    {
        XXX_ift(this, H, Hl, h, temp1);
    }
#endif

    /* END SECTION 3 */
};

/* BEGIN SECTION 4: tweaks */
/* Now that XXX_info is declared completely, we may declare the 1-sized
 * array */
typedef struct XXX_info XXX_info_t[1];
/* END SECTION 4 */
