// commit message qemu@496272a701 (target=0, prob=0.3288499, correct=True): target-ppc: Disentangle hash mmu helper functions
/*0   */ static int find_pte32(CPUPPCState *env, mmu_ctx_t *ctx, int h,              // (9) 0.05273
/*2   */                       int rw, int type, int target_page_bits)               // (6) 0.06836
/*4   */ {                                                                           // (19) 0.001953
/*6   */     hwaddr pteg_off;                                                        // (14) 0.02344
/*8   */     target_ulong pte0, pte1;                                                // (12) 0.0293
/*10  */     int i, good = -1;                                                       // (15) 0.02148
/*12  */     int ret, r;                                                             // (17) 0.01563
/*16  */     ret = -1; /* No entry found */                                          // (13) 0.02539
/*18  */     pteg_off = get_pteg_offset(env, ctx->hash[h], HASH_PTE_SIZE_32);        // (7) 0.06836
/*20  */     for (i = 0; i < 8; i++) {                                               // (11) 0.03125
/*22  */         if (env->external_htab) {                                           // (10) 0.0332
/*24  */             pte0 = ldl_p(env->external_htab + pteg_off + (i * 8));          // (5) 0.07422
/*26  */             pte1 = ldl_p(env->external_htab + pteg_off + (i * 8) + 4);      // (1) 0.08008
/*28  */         } else {                                                            // (16) 0.01953
/*30  */             pte0 = ldl_phys(env->htab_base + pteg_off + (i * 8));           // (4) 0.07422
/*32  */             pte1 = ldl_phys(env->htab_base + pteg_off + (i * 8) + 4);       // (2) 0.08008
/*34  */         }                                                                   // (18) 0.01562
/*36  */         r = pte_check_hash32(ctx, pte0, pte1, h, rw, type);                 // (8) 0.06641
/*38  */         LOG_MMU("Load pte from %08" HWADDR_PRIx " => " TARGET_FMT_lx " "    // (3) 0.07617
/*40  */                 TARGET_FMT_lx " %d %d %d " TARGET_FMT_lx "\n",              // (0) 0.08203
/*42  */                 pteg_off + (i * 8), pte0, pte1, (int)(pte0 >> 31), h,       // 0.0
/*44  */                 (int)((pte0 >> 6) & 1), ctx->ptem);                         // 0.0
/*46  */         switch (r) {                                                        // 0.0
/*48  */         case -3:                                                            // 0.0
/*50  */             /* PTE inconsistency */                                         // 0.0
/*52  */             return -1;                                                      // 0.0
/*54  */         case -2:                                                            // 0.0
/*56  */             /* Access violation */                                          // 0.0
/*58  */             ret = -2;                                                       // 0.0
/*60  */             good = i;                                                       // 0.0
/*62  */             break;                                                          // 0.0
/*64  */         case -1:                                                            // 0.0
/*66  */         default:                                                            // 0.0
/*68  */             /* No PTE match */                                              // 0.0
/*70  */             break;                                                          // 0.0
/*72  */         case 0:                                                             // 0.0
/*74  */             /* access granted */                                            // 0.0
/*76  */             /* XXX: we should go on looping to check all PTEs consistency   // 0.0
/*78  */              *      but if we can speed-up the whole thing as the           // 0.0
/*80  */              *      result would be undefined if PTEs are not consistent.   // 0.0
/*82  */              */                                                             // 0.0
/*84  */             ret = 0;                                                        // 0.0
/*86  */             good = i;                                                       // 0.0
/*88  */             goto done;                                                      // 0.0
/*90  */         }                                                                   // 0.0
/*92  */     }                                                                       // 0.0
/*94  */     if (good != -1) {                                                       // 0.0
/*96  */     done:                                                                   // 0.0
/*98  */         LOG_MMU("found PTE at addr %08" HWADDR_PRIx " prot=%01x ret=%d\n",  // 0.0
/*100 */                 ctx->raddr, ctx->prot, ret);                                // 0.0
/*102 */         /* Update page flags */                                             // 0.0
/*104 */         pte1 = ctx->raddr;                                                  // 0.0
/*106 */         if (pte_update_flags(ctx, &pte1, ret, rw) == 1) {                   // 0.0
/*108 */             if (env->external_htab) {                                       // 0.0
/*110 */                 stl_p(env->external_htab + pteg_off + (good * 8) + 4,       // 0.0
/*112 */                       pte1);                                                // 0.0
/*114 */             } else {                                                        // 0.0
/*116 */                 stl_phys_notdirty(env->htab_base + pteg_off +               // 0.0
/*118 */                                   (good * 8) + 4, pte1);                    // 0.0
/*120 */             }                                                               // 0.0
/*122 */         }                                                                   // 0.0
/*124 */     }                                                                       // 0.0
/*128 */     /* We have a TLB that saves 4K pages, so let's                          // 0.0
/*130 */      * split a huge page to 4k chunks */                                    // 0.0
/*132 */     if (target_page_bits != TARGET_PAGE_BITS) {                             // 0.0
/*134 */         ctx->raddr |= (ctx->eaddr & ((1 << target_page_bits) - 1))          // 0.0
/*136 */                       & TARGET_PAGE_MASK;                                   // 0.0
/*138 */     }                                                                       // 0.0
/*140 */     return ret;                                                             // 0.0
/*142 */ }                                                                           // 0.0
