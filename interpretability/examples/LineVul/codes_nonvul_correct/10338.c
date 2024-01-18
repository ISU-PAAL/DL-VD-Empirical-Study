// commit message qemu@b2bedb2144 (target=0, prob=0.291645, correct=True): Remove blanks before \n in output strings
/*0  */ void test_fcmp(double a, double b)                                       // (22) 0.02344
/*2  */ {                                                                        // (26) 0.001953
/*4  */     long eflags, fpus;                                                   // (23) 0.02148
/*8  */     fpu_clear_exceptions();                                              // (24) 0.02148
/*10 */     asm("fcom %2\n"                                                      // (19) 0.02539
/*12 */         "fstsw %%ax\n"                                                   // (15) 0.03125
/*14 */         : "=a" (fpus)                                                    // (14) 0.03125
/*16 */         : "t" (a), "u" (b));                                             // (6) 0.03906
/*18 */     printf("fcom(%f %f)=%04lx \n",                                       // (7) 0.03906
/*20 */            a, b, fpus & (0x4500 | FPUS_EMASK));                          // (0) 0.06055
/*22 */     fpu_clear_exceptions();                                              // (25) 0.02148
/*24 */     asm("fucom %2\n"                                                     // (20) 0.02539
/*26 */         "fstsw %%ax\n"                                                   // (16) 0.03125
/*28 */         : "=a" (fpus)                                                    // (17) 0.03125
/*30 */         : "t" (a), "u" (b));                                             // (8) 0.03906
/*32 */     printf("fucom(%f %f)=%04lx\n",                                       // (9) 0.03906
/*34 */            a, b, fpus & (0x4500 | FPUS_EMASK));                          // (1) 0.06055
/*36 */     if (TEST_FCOMI) {                                                    // (21) 0.02539
/*38 */         /* test f(u)comi instruction */                                  // (12) 0.0332
/*40 */         fpu_clear_exceptions();                                          // (18) 0.0293
/*42 */         asm("fcomi %3, %2\n"                                             // (5) 0.04102
/*44 */             "fstsw %%ax\n"                                               // (10) 0.03906
/*46 */             "pushf\n"                                                    // (13) 0.0332
/*48 */             "pop %0\n"                                                   // (11) 0.03516
/*50 */             : "=r" (eflags), "=a" (fpus)                                 // (3) 0.05664
/*52 */             : "t" (a), "u" (b));                                         // (4) 0.04688
/*54 */         printf("fcomi(%f %f)=%04lx %02lx\n",                             // (2) 0.05664
/*56 */                a, b, fpus & FPUS_EMASK, eflags & (CC_Z | CC_P | CC_C));  // 0.0
/*58 */         fpu_clear_exceptions();                                          // 0.0
/*60 */         asm("fucomi %3, %2\n"                                            // 0.0
/*62 */             "fstsw %%ax\n"                                               // 0.0
/*64 */             "pushf\n"                                                    // 0.0
/*66 */             "pop %0\n"                                                   // 0.0
/*68 */             : "=r" (eflags), "=a" (fpus)                                 // 0.0
/*70 */             : "t" (a), "u" (b));                                         // 0.0
/*72 */         printf("fucomi(%f %f)=%04lx %02lx\n",                            // 0.0
/*74 */                a, b, fpus & FPUS_EMASK, eflags & (CC_Z | CC_P | CC_C));  // 0.0
/*76 */     }                                                                    // 0.0
/*78 */     fpu_clear_exceptions();                                              // 0.0
/*80 */     asm volatile("fxam\n"                                                // 0.0
/*82 */                  "fstsw %%ax\n"                                          // 0.0
/*84 */                  : "=a" (fpus)                                           // 0.0
/*86 */                  : "t" (a));                                             // 0.0
/*88 */     printf("fxam(%f)=%04lx\n", a, fpus & 0x4700);                        // 0.0
/*90 */     fpu_clear_exceptions();                                              // 0.0
/*92 */ }                                                                        // 0.0
