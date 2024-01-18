// commit message qemu@ea6c5f8ffe (target=0, prob=0.6969179, correct=False): xen: Adds a cap to the number of map cache entries.
/*0 */ static inline int test_bit(unsigned int bit, const unsigned long *map)           // (1) 0.2616
/*2 */ {                                                                                // (2) 0.01538
/*4 */     return !!((map)[(bit) / BITS_PER_LONG] & (1UL << ((bit) % BITS_PER_LONG)));  // (0) 0.5846
/*6 */ }                                                                                // (3) 0.01538
