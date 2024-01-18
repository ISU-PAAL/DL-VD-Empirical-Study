// commit message qemu@91cda45b69 (target=0, prob=0.04301919, correct=True): mmu-hash*: Reduce use of access_type
/*0   */ static int get_segment64(CPUPPCState *env, struct mmu_ctx_hash64 *ctx,    // (6) 0.05078
/*2   */                          target_ulong eaddr, int rw, int type)            // (1) 0.07422
/*4   */ {                                                                         // (27) 0.001953
/*6   */     hwaddr hash;                                                          // (22) 0.01562
/*8   */     target_ulong vsid;                                                    // (19) 0.01953
/*10  */     int pr, target_page_bits;                                             // (14) 0.02344
/*12  */     int ret, ret2;                                                        // (20) 0.01758
/*16  */     pr = msr_pr;                                                          // (17) 0.01953
/*18  */     ctx->eaddr = eaddr;                                                   // (15) 0.02344
/*20  */     ppc_slb_t *slb;                                                       // (11) 0.02734
/*22  */     target_ulong pageaddr;                                                // (18) 0.01953
/*24  */     int segment_bits;                                                     // (23) 0.01562
/*28  */     LOG_MMU("Check SLBs\n");                                              // (10) 0.02734
/*30  */     slb = slb_lookup(env, eaddr);                                         // (9) 0.0332
/*32  */     if (!slb) {                                                           // (21) 0.01758
/*34  */         return -5;                                                        // (16) 0.02148
/*36  */     }                                                                     // (25) 0.007812
/*40  */     if (slb->vsid & SLB_VSID_B) {                                         // (8) 0.03906
/*42  */         vsid = (slb->vsid & SLB_VSID_VSID) >> SLB_VSID_SHIFT_1T;          // (0) 0.07617
/*44  */         segment_bits = 40;                                                // (13) 0.02539
/*46  */     } else {                                                              // (24) 0.01172
/*48  */         vsid = (slb->vsid & SLB_VSID_VSID) >> SLB_VSID_SHIFT;             // (2) 0.07031
/*50  */         segment_bits = 28;                                                // (12) 0.02539
/*52  */     }                                                                     // (26) 0.007812
/*56  */     target_page_bits = (slb->vsid & SLB_VSID_L)                           // (7) 0.04687
/*58  */         ? TARGET_PAGE_BITS_16M : TARGET_PAGE_BITS;                        // (4) 0.05664
/*60  */     ctx->key = !!(pr ? (slb->vsid & SLB_VSID_KP)                          // (5) 0.05469
/*62  */                   : (slb->vsid & SLB_VSID_KS));                           // (3) 0.06445
/*64  */     ctx->nx = !!(slb->vsid & SLB_VSID_N);                                 // 0.0
/*68  */     pageaddr = eaddr & ((1ULL << segment_bits)                            // 0.0
/*70  */                             - (1ULL << target_page_bits));                // 0.0
/*72  */     if (slb->vsid & SLB_VSID_B) {                                         // 0.0
/*74  */         hash = vsid ^ (vsid << 25) ^ (pageaddr >> target_page_bits);      // 0.0
/*76  */     } else {                                                              // 0.0
/*78  */         hash = vsid ^ (pageaddr >> target_page_bits);                     // 0.0
/*80  */     }                                                                     // 0.0
/*82  */     /* Only 5 bits of the page index are used in the AVPN */              // 0.0
/*84  */     ctx->ptem = (slb->vsid & SLB_VSID_PTEM) |                             // 0.0
/*86  */         ((pageaddr >> 16) & ((1ULL << segment_bits) - 0x80));             // 0.0
/*90  */     LOG_MMU("pte segment: key=%d nx %d vsid " TARGET_FMT_lx "\n",         // 0.0
/*92  */             ctx->key, ctx->nx, vsid);                                     // 0.0
/*94  */     ret = -1;                                                             // 0.0
/*98  */     /* Check if instruction fetch is allowed, if needed */                // 0.0
/*100 */     if (type != ACCESS_CODE || ctx->nx == 0) {                            // 0.0
/*102 */         /* Page address translation */                                    // 0.0
/*104 */         LOG_MMU("htab_base " TARGET_FMT_plx " htab_mask " TARGET_FMT_plx  // 0.0
/*106 */                 " hash " TARGET_FMT_plx "\n",                             // 0.0
/*108 */                 env->htab_base, env->htab_mask, hash);                    // 0.0
/*110 */         ctx->hash[0] = hash;                                              // 0.0
/*112 */         ctx->hash[1] = ~hash;                                             // 0.0
/*116 */         /* Initialize real address with an invalid value */               // 0.0
/*118 */         ctx->raddr = (hwaddr)-1ULL;                                       // 0.0
/*120 */         LOG_MMU("0 htab=" TARGET_FMT_plx "/" TARGET_FMT_plx               // 0.0
/*122 */                 " vsid=" TARGET_FMT_lx " ptem=" TARGET_FMT_lx             // 0.0
/*124 */                 " hash=" TARGET_FMT_plx "\n",                             // 0.0
/*126 */                 env->htab_base, env->htab_mask, vsid, ctx->ptem,          // 0.0
/*128 */                 ctx->hash[0]);                                            // 0.0
/*130 */         /* Primary table lookup */                                        // 0.0
/*132 */         ret = find_pte64(env, ctx, 0, rw, type, target_page_bits);        // 0.0
/*134 */         if (ret < 0) {                                                    // 0.0
/*136 */             /* Secondary table lookup */                                  // 0.0
/*138 */             LOG_MMU("1 htab=" TARGET_FMT_plx "/" TARGET_FMT_plx           // 0.0
/*140 */                     " vsid=" TARGET_FMT_lx " api=" TARGET_FMT_lx          // 0.0
/*142 */                     " hash=" TARGET_FMT_plx "\n", env->htab_base,         // 0.0
/*144 */                     env->htab_mask, vsid, ctx->ptem, ctx->hash[1]);       // 0.0
/*146 */             ret2 = find_pte64(env, ctx, 1, rw, type, target_page_bits);   // 0.0
/*148 */             if (ret2 != -1) {                                             // 0.0
/*150 */                 ret = ret2;                                               // 0.0
/*152 */             }                                                             // 0.0
/*154 */         }                                                                 // 0.0
/*156 */     } else {                                                              // 0.0
/*158 */         LOG_MMU("No access allowed\n");                                   // 0.0
/*160 */         ret = -3;                                                         // 0.0
/*162 */     }                                                                     // 0.0
/*166 */     return ret;                                                           // 0.0
/*168 */ }                                                                         // 0.0
