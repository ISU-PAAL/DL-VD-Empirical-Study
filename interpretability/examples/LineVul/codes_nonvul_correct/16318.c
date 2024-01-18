// commit message qemu@babfa20ca4 (target=0, prob=0.06614458, correct=True): i386: hvf: implement vga dirty page tracking
/*0  */ static bool ept_emulation_fault(uint64_t ept_qual)                     // (5) 0.0597
/*2  */ {                                                                      // (22) 0.002985
/*4  */     int read, write;                                                   // (14) 0.02388
/*8  */     /* EPT fault on an instruction fetch doesn't make sense here */    // (7) 0.05075
/*10 */     if (ept_qual & EPT_VIOLATION_INST_FETCH) {                         // (4) 0.06866
/*12 */         return false;                                                  // (11) 0.02985
/*14 */     }                                                                  // (18) 0.01194
/*18 */     /* EPT fault must be a read fault or a write fault */              // (8) 0.05075
/*20 */     read = ept_qual & EPT_VIOLATION_DATA_READ ? 1 : 0;                 // (2) 0.07463
/*22 */     write = ept_qual & EPT_VIOLATION_DATA_WRITE ? 1 : 0;               // (1) 0.07761
/*24 */     if ((read | write) == 0) {                                         // (10) 0.03881
/*26 */         return false;                                                  // (12) 0.02985
/*28 */     }                                                                  // (19) 0.01194
/*32 */     /*                                                                 // (20) 0.01194
/*34 */      * The EPT violation must have been caused by accessing a          // (9) 0.04776
/*36 */      * guest-physical address that is a translation of a guest-linear  // (6) 0.05373
/*38 */      * address.                                                        // (15) 0.0209
/*40 */      */                                                                // (17) 0.01493
/*42 */     if ((ept_qual & EPT_VIOLATION_GLA_VALID) == 0 ||                   // (3) 0.07463
/*44 */         (ept_qual & EPT_VIOLATION_XLAT_VALID) == 0) {                  // (0) 0.08657
/*46 */         return false;                                                  // (13) 0.02985
/*48 */     }                                                                  // (21) 0.01194
/*52 */     return true;                                                       // (16) 0.01791
/*54 */ }                                                                      // (23) 0.002985
