// commit message qemu@4a1418e07b (target=0, prob=0.019163074, correct=True): Unbreak large mem support by removing kqemu
/*0  */ static void save_native_fp_fsave(CPUState *env)               // (9) 0.04244
/*2  */ {                                                             // (21) 0.002653
/*4  */     int fptag, i, j;                                          // (15) 0.03183
/*6  */     uint16_t fpuc;                                            // (17) 0.02918
/*8  */     struct fpstate fp1, *fp = &fp1;                           // (7) 0.04775
/*12 */     asm volatile ("fsave %0" : : "m" (*fp));                  // (4) 0.05305
/*14 */     env->fpuc = fp->fpuc;                                     // (12) 0.03714
/*16 */     env->fpstt = (fp->fpus >> 11) & 7;                        // (5) 0.05305
/*18 */     env->fpus = fp->fpus & ~0x3800;                           // (6) 0.05305
/*20 */     fptag = fp->fptag;                                        // (13) 0.03714
/*22 */     for(i = 0;i < 8; i++) {                                   // (10) 0.04244
/*24 */         env->fptags[i] = ((fptag & 3) == 3);                  // (1) 0.06897
/*26 */         fptag >>= 2;                                          // (14) 0.03714
/*28 */     }                                                         // (19) 0.01061
/*30 */     j = env->fpstt;                                           // (18) 0.02918
/*32 */     for(i = 0;i < 8; i++) {                                   // (11) 0.04244
/*34 */         memcpy(&env->fpregs[j].d, &fp->fpregs1[i * 10], 10);  // (0) 0.09284
/*36 */         j = (j + 1) & 7;                                      // (8) 0.04509
/*38 */     }                                                         // (20) 0.01061
/*40 */     /* we must restore the default rounding state */          // (16) 0.03183
/*42 */     fpuc = 0x037f | (env->fpuc & (3 << 10));                  // (2) 0.06366
/*44 */     asm volatile("fldcw %0" : : "m" (fpuc));                  // (3) 0.06101
/*46 */ }                                                             // (22) 0.002653
