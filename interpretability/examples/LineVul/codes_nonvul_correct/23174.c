// commit message qemu@e3e09d87c6 (target=0, prob=0.43043387, correct=True): s390x/mmu: Skip exceptions properly when translating addresses for debug
/*0   */ int mmu_translate(CPUS390XState *env, target_ulong vaddr, int rw, uint64_t asc,  // (3) 0.0625
/*2   */                   target_ulong *raddr, int *flags)                               // (5) 0.05664
/*4   */ {                                                                                // (27) 0.001953
/*6   */     int r = -1;                                                                  // (21) 0.01758
/*8   */     uint8_t *sk;                                                                 // (18) 0.01953
/*12  */     *flags = PAGE_READ | PAGE_WRITE | PAGE_EXEC;                                 // (8) 0.03906
/*14  */     vaddr &= TARGET_PAGE_MASK;                                                   // (9) 0.03125
/*18  */     if (!(env->psw.mask & PSW_MASK_DAT)) {                                       // (7) 0.04492
/*20  */         *raddr = vaddr;                                                          // (11) 0.02734
/*22  */         r = 0;                                                                   // (17) 0.02148
/*24  */         goto out;                                                                // (19) 0.01953
/*26  */     }                                                                            // (26) 0.007812
/*30  */     switch (asc) {                                                               // (24) 0.01562
/*32  */     case PSW_ASC_PRIMARY:                                                        // (12) 0.02539
/*34  */     case PSW_ASC_HOME:                                                           // (16) 0.02148
/*36  */         r = mmu_translate_asc(env, vaddr, asc, raddr, flags, rw);                // (4) 0.0625
/*38  */         break;                                                                   // (22) 0.01758
/*40  */     case PSW_ASC_SECONDARY:                                                      // (13) 0.02539
/*42  */         /*                                                                       // (25) 0.01562
/*44  */          * Instruction: Primary                                                  // (14) 0.02344
/*46  */          * Data: Secondary                                                       // (15) 0.02344
/*48  */          */                                                                      // (23) 0.01758
/*50  */         if (rw == 2) {                                                           // (10) 0.02734
/*52  */             r = mmu_translate_asc(env, vaddr, PSW_ASC_PRIMARY, raddr, flags,     // (1) 0.07812
/*54  */                                   rw);                                           // (2) 0.07031
/*56  */             *flags &= ~(PAGE_READ | PAGE_WRITE);                                 // (6) 0.05273
/*58  */         } else {                                                                 // (20) 0.01953
/*60  */             r = mmu_translate_asc(env, vaddr, PSW_ASC_SECONDARY, raddr, flags,   // (0) 0.07812
/*62  */                                   rw);                                           // 0.0
/*64  */             *flags &= ~(PAGE_EXEC);                                              // 0.0
/*66  */         }                                                                        // 0.0
/*68  */         break;                                                                   // 0.0
/*70  */     case PSW_ASC_ACCREG:                                                         // 0.0
/*72  */     default:                                                                     // 0.0
/*74  */         hw_error("guest switched to unknown asc mode\n");                        // 0.0
/*76  */         break;                                                                   // 0.0
/*78  */     }                                                                            // 0.0
/*82  */  out:                                                                            // 0.0
/*84  */     /* Convert real address -> absolute address */                               // 0.0
/*86  */     *raddr = mmu_real2abs(env, *raddr);                                          // 0.0
/*90  */     if (*raddr <= ram_size) {                                                    // 0.0
/*92  */         sk = &env->storage_keys[*raddr / TARGET_PAGE_SIZE];                      // 0.0
/*94  */         if (*flags & PAGE_READ) {                                                // 0.0
/*96  */             *sk |= SK_R;                                                         // 0.0
/*98  */         }                                                                        // 0.0
/*102 */         if (*flags & PAGE_WRITE) {                                               // 0.0
/*104 */             *sk |= SK_C;                                                         // 0.0
/*106 */         }                                                                        // 0.0
/*108 */     }                                                                            // 0.0
/*112 */     return r;                                                                    // 0.0
/*114 */ }                                                                                // 0.0
