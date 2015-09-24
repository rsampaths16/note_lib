int __builtin_types_compatible_p (type1, type2)
__LINE__
__FUNCTION__
__FILE__
__attribute__((packed))
int __builtin_clz (unsigned int x)
int __builtin_clz (unsigned int x)
int __builtin_ctz (unsigned int x)
int __builtin_clrsb (int x)
int __builtin_popcount (unsigned int x)
int __builtin_parity (unsigned int x)
uint16_t __builtin_bswap16 (uint16_t x)
uint32_t __builtin_bswap32 (uint32_t x)
uint64_t __builtin_bswap64 (uint64_t x)
int __builtin_ffs (int x)


/* Common bit arthmetics //
   X with i'th bit 0        x & ~(1 << i)
   X with i'th bit 1        x | (1 << i)
   X with i'th bit inverted x ^ (1 << i)
   i'th bit of X            (x >> i) & 1
   get first i bits of X    x & (1 << i) – 1
   First 1 to 0             x & (x – 1)
   First 0 to 1             x | (x + 1)
   get 2^(1st 1)            x & -x
   get 2^(1st 0)            ~x & (x + 1)
   first continous 0 to 1   x | (x – 1)
   first continous 1 to 0   (x | (x – 1)) + 1) & x
   First i bits set to 0    x & (-1 << i)
   First i bits set to 1    t = (1 << i) - 1, x = (x + t) & ~t
// Also note, the comparison operation less than a shift, but higher than the bit operation or operations with */


// index to Gray-code
inline int index_to_gray(int mask){
    return mask^mask>>1;
}

// gray-code to index
inline int gray_to_index(int mask){
    mask^=mask >> 16;
    mask^=mask >> 8;
    mask^=mask >> 4;
    mask^=mask >> 2;
    return mask^mask>>1;
}
