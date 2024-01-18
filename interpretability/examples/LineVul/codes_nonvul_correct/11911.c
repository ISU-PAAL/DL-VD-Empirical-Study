// commit message qemu@e69a17f65e (target=0, prob=0.0071133818, correct=True): openpic: use standard bitmap operations
/*0 */ static inline int test_bit(uint32_t *field, int bit)    // (1) 0.3272
/*2 */ {                                                       // (2) 0.01922
/*4 */     return (field[bit >> 5] & 1 << (bit & 0x1F)) != 0;  // (0) 0.4806
/*6 */ }                                                       // (3) 0.01922
