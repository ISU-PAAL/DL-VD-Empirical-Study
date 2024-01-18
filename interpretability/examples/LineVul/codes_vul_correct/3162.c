// commit message qemu@45bbbb466c (target=1, prob=0.99708027, correct=True): added overflow exceptions in divisions
/*0 */ uint32_t div32(uint32_t *q_ptr, uint64_t num, uint32_t den)  // (0) 0.4747
/*2 */ {                                                            // (3) 0.01694
/*4 */     *q_ptr = num / den;                                      // (1) 0.2034
/*6 */     return num % den;                                        // (2) 0.1355
/*8 */ }                                                            // (4) 0.01693
