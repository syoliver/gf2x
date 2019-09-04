#ifndef GF2X_FFT_IMPL_UTILS_H_
#define GF2X_FFT_IMPL_UTILS_H_

/* Assume wordlength  WLEN is 32 or 64 */

#include <stddef.h>

#define WLEN GF2X_WORDSIZE
/* Don't define MIN, MAX, ABS as inlines, as they're already quite
 *
 * customarily defined as macros */
#ifndef MAX
#define MAX(h,i) ((h) > (i) ? (h) : (i))
#endif
#ifndef MIN
#define MIN(h,i) ((h) < (i) ? (h) : (i))
#endif
#ifndef ABS
#define ABS(h) ((h) < 0 ? -(h) : (h))
#endif


/** Some support functions. **/

/* CEIL(a,b) = ceiling(a/b) */
static inline size_t CEIL(size_t a, size_t b)
{
    return ((a)+(b)-1)/(b);
}

/* W(b) is the number of words needed to store b bits */
static inline size_t W(size_t b)
{
    return CEIL(b, WLEN);
}

/* I(b) is the index word of bit b, assuming bits 0..WLEN-1
   have index 0 */
static inline size_t I(size_t b)
{
    return b / WLEN;
}

static inline size_t R(size_t b)
{
    return b % WLEN;
}

static inline size_t R2(size_t b)       /* remaining bits */
{
    return (-b) % WLEN;
}

static inline unsigned long MASK(size_t x)
{
    ASSERT(x < WLEN);
    return ((1UL << (x)) - 1UL);
}

/* GETBIT(a,i)   gets the i-th bit of the bit-array starting at a[0],
   XORBIT(a,i,x) xors this bit with the bit x, where x = 0 or 1.   */
static inline unsigned long GETBIT(unsigned long *a, size_t i)
{
    return (a[I(i)] >> R(i)) & 1UL;
}

static inline void XORBIT(unsigned long *a, size_t i, unsigned long x)
{
    ASSERT((x & ~1UL) == 0);
    a[I(i)] ^= x << R(i);
}

static inline void * malloc_or_die(size_t size)
{
    void *res = malloc(size);
    if (res == NULL)
	abort();
    return res;
}

static inline void Copy(unsigned long *a, const unsigned long *b, size_t n)
{
    memcpy(a, b, n * sizeof(unsigned long));
}

static inline void Zero(unsigned long *a, size_t n)
{
    memset(a, 0, n * sizeof(unsigned long));
}

static inline void Clear(unsigned long *a, size_t low, size_t high)
{
    if (high > low)
       memset (a + low, 0, (high - low) * sizeof(unsigned long));
}

/** Now the specific things */

/* a <- b + c */

static inline void AddMod(unsigned long *a, unsigned long *b, unsigned long *c,
		   size_t n)
{
    for (size_t i = 0; i < n; i++)
       a[i] = b[i] ^ c[i];
}

/* a <- b + c + d */
static inline void
AddMod3 (unsigned long *a, unsigned long *b, unsigned long *c,
         unsigned long *d, size_t n)
{
  for (size_t i = 0; i < n; i++)
    a[i] = b[i] ^ c[i] ^ d[i];
}

/* c <- a * x^k, return carry out, 0 <= k < WLEN */
static inline unsigned long
Lsh (unsigned long *c, unsigned long *a, size_t n, size_t k)
{
    if (k == 0) {
	if (c != a)
	    Copy(c, a, n);
	return 0;
    }

    /* {c, n} and {a, n} should not overlap */
    ASSERT(c <= a || a + n <= c);
    ASSERT(k > 0);

    unsigned long t, cy = 0;
    for (size_t i = 0; i < n; i++) {
	t = (a[i] << k) | cy;
	cy = a[i] >> (WLEN - k);
	c[i] = t;
    }
    return cy;
}

/* c <- c + a * x^k, return carry out, 0 <= k < WLEN */

static inline unsigned long AddLsh(unsigned long *c, unsigned long *a, size_t n,
			    size_t k)
{
    unsigned long t, cy = 0;

    if (k == 0) {
	AddMod(c, c, a, n);
	return 0;
    }

    /* {c, n} and {a, n} should not overlap */
    ASSERT(c <= a || a + n <= c);

    ASSERT(k > 0);

    for (size_t i = 0; i < n; i++) {
	t = (a[i] << k) | cy;
	cy = a[i] >> (WLEN - k);
	c[i] ^= t;
    }
    return cy;
}

/* c <- a / x^k, return carry out, 0 <= k < WLEN */
static inline unsigned long
Rsh (unsigned long *c, const unsigned long *a, size_t n, size_t k)
{
    if (k == 0) {
	if (c != a)
	    Copy(c, a, n);
	return 0;
    }

    ASSERT(k > 0);

    unsigned long t, cy = 0;
    for (size_t i = n; i-- ; ) {
	t = (a[i] >> k) | cy;
	cy = a[i] << (WLEN - k);
	c[i] = t;
    }
    return cy;
}

/* c <- c + a / x^k, return carry out, 0 <= k < WLEN */

static inline unsigned long AddRsh(unsigned long *c, unsigned long *a, size_t n,
			    size_t k)
{
    unsigned long t, cy = 0;

    if (k == 0) {
	AddMod(c, c, a, n);
	return 0;
    }

    ASSERT(k > 0);

    for (size_t i = n ; i-- ; ) {
	t = (a[i] >> k) | cy;
	cy = a[i] << (WLEN - k);
	c[i] ^= t;
    }
    return cy;
}


#endif	/* GF2X_FFT_IMPL_UTILS_H_ */
