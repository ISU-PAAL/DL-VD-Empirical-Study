// commit message qemu@a8170e5e97 (target=0, prob=0.0045560417, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint64_t eepro100_read(void *opaque, target_phys_addr_t addr,  // (1) 0.1585
/*2  */                               unsigned size)                          // (0) 0.1951
/*4  */ {                                                                     // (9) 0.006098
/*6  */     EEPRO100State *s = opaque;                                        // (5) 0.07317
/*10 */     switch (size) {                                                   // (6) 0.04878
/*12 */     case 1: return eepro100_read1(s, addr);                           // (2) 0.1159
/*14 */     case 2: return eepro100_read2(s, addr);                           // (3) 0.1159
/*16 */     case 4: return eepro100_read4(s, addr);                           // (4) 0.1159
/*18 */     default: abort();                                                 // (7) 0.04268
/*20 */     }                                                                 // (8) 0.02439
/*22 */ }                                                                     // (10) 0.006098
