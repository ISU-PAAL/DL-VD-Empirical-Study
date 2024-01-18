// commit message qemu@36778660d7 (target=0, prob=0.1842403, correct=True): target/ppc: Eliminate htab_base and htab_mask variables
/*0   */ static inline int get_segment_6xx_tlb(CPUPPCState *env, mmu_ctx_t *ctx,        // (6) 0.05859
/*2   */                                       target_ulong eaddr, int rw, int type)    // (0) 0.09961
/*4   */ {                                                                              // (21) 0.001953
/*6   */     hwaddr hash;                                                               // (19) 0.01562
/*8   */     target_ulong vsid;                                                         // (17) 0.01953
/*10  */     int ds, pr, target_page_bits;                                              // (12) 0.0293
/*12  */     int ret;                                                                   // (20) 0.01172
/*14  */     target_ulong sr, pgidx;                                                    // (15) 0.02539
/*18  */     pr = msr_pr;                                                               // (18) 0.01953
/*20  */     ctx->eaddr = eaddr;                                                        // (16) 0.02344
/*24  */     sr = env->sr[eaddr >> 28];                                                 // (13) 0.02734
/*26  */     ctx->key = (((sr & 0x20000000) && (pr != 0)) ||                            // (7) 0.04687
/*28  */                 ((sr & 0x40000000) && (pr == 0))) ? 1 : 0;                     // (4) 0.06641
/*30  */     ds = sr & 0x80000000 ? 1 : 0;                                              // (11) 0.0332
/*32  */     ctx->nx = sr & 0x10000000 ? 1 : 0;                                         // (8) 0.03906
/*34  */     vsid = sr & 0x00FFFFFF;                                                    // (14) 0.02734
/*36  */     target_page_bits = TARGET_PAGE_BITS;                                       // (10) 0.03516
/*38  */     qemu_log_mask(CPU_LOG_MMU,                                                 // (9) 0.03516
/*40  */             "Check segment v=" TARGET_FMT_lx " %d " TARGET_FMT_lx              // (2) 0.07031
/*42  */             " nip=" TARGET_FMT_lx " lr=" TARGET_FMT_lx                         // (3) 0.06836
/*44  */             " ir=%d dr=%d pr=%d %d t=%d\n",                                    // (5) 0.06445
/*46  */             eaddr, (int)(eaddr >> 28), sr, env->nip, env->lr, (int)msr_ir,     // (1) 0.08008
/*48  */             (int)msr_dr, pr != 0 ? 1 : 0, rw, type);                           // 0.0
/*50  */     pgidx = (eaddr & ~SEGMENT_MASK_256M) >> target_page_bits;                  // 0.0
/*52  */     hash = vsid ^ pgidx;                                                       // 0.0
/*54  */     ctx->ptem = (vsid << 7) | (pgidx >> 10);                                   // 0.0
/*58  */     qemu_log_mask(CPU_LOG_MMU,                                                 // 0.0
/*60  */             "pte segment: key=%d ds %d nx %d vsid " TARGET_FMT_lx "\n",        // 0.0
/*62  */             ctx->key, ds, ctx->nx, vsid);                                      // 0.0
/*64  */     ret = -1;                                                                  // 0.0
/*66  */     if (!ds) {                                                                 // 0.0
/*68  */         /* Check if instruction fetch is allowed, if needed */                 // 0.0
/*70  */         if (type != ACCESS_CODE || ctx->nx == 0) {                             // 0.0
/*72  */             /* Page address translation */                                     // 0.0
/*74  */             qemu_log_mask(CPU_LOG_MMU, "htab_base " TARGET_FMT_plx             // 0.0
/*76  */                     " htab_mask " TARGET_FMT_plx                               // 0.0
/*78  */                     " hash " TARGET_FMT_plx "\n",                              // 0.0
/*80  */                     env->htab_base, env->htab_mask, hash);                     // 0.0
/*82  */             ctx->hash[0] = hash;                                               // 0.0
/*84  */             ctx->hash[1] = ~hash;                                              // 0.0
/*88  */             /* Initialize real address with an invalid value */                // 0.0
/*90  */             ctx->raddr = (hwaddr)-1ULL;                                        // 0.0
/*92  */             /* Software TLB search */                                          // 0.0
/*94  */             ret = ppc6xx_tlb_check(env, ctx, eaddr, rw, type);                 // 0.0
/*96  */ #if defined(DUMP_PAGE_TABLES)                                                  // 0.0
/*98  */             if (qemu_loglevel_mask(CPU_LOG_MMU)) {                             // 0.0
/*100 */                 CPUState *cs = ENV_GET_CPU(env);                               // 0.0
/*102 */                 hwaddr curaddr;                                                // 0.0
/*104 */                 uint32_t a0, a1, a2, a3;                                       // 0.0
/*108 */                 qemu_log("Page table: " TARGET_FMT_plx " len " TARGET_FMT_plx  // 0.0
/*110 */                          "\n", env->htab_base, env->htab_mask + 0x80);         // 0.0
/*112 */                 for (curaddr = env->htab_base;                                 // 0.0
/*114 */                      curaddr < (env->htab_base + env->htab_mask + 0x80);       // 0.0
/*116 */                      curaddr += 16) {                                          // 0.0
/*118 */                     a0 = ldl_phys(cs->as, curaddr);                            // 0.0
/*120 */                     a1 = ldl_phys(cs->as, curaddr + 4);                        // 0.0
/*122 */                     a2 = ldl_phys(cs->as, curaddr + 8);                        // 0.0
/*124 */                     a3 = ldl_phys(cs->as, curaddr + 12);                       // 0.0
/*126 */                     if (a0 != 0 || a1 != 0 || a2 != 0 || a3 != 0) {            // 0.0
/*128 */                         qemu_log(TARGET_FMT_plx ": %08x %08x %08x %08x\n",     // 0.0
/*130 */                                  curaddr, a0, a1, a2, a3);                     // 0.0
/*132 */                     }                                                          // 0.0
/*134 */                 }                                                              // 0.0
/*136 */             }                                                                  // 0.0
/*138 */ #endif                                                                         // 0.0
/*140 */         } else {                                                               // 0.0
/*142 */             qemu_log_mask(CPU_LOG_MMU, "No access allowed\n");                 // 0.0
/*144 */             ret = -3;                                                          // 0.0
/*146 */         }                                                                      // 0.0
/*148 */     } else {                                                                   // 0.0
/*150 */         target_ulong sr;                                                       // 0.0
/*154 */         qemu_log_mask(CPU_LOG_MMU, "direct store...\n");                       // 0.0
/*156 */         /* Direct-store segment : absolutely *BUGGY* for now */                // 0.0
/*160 */         /* Direct-store implies a 32-bit MMU.                                  // 0.0
/*162 */          * Check the Segment Register's bus unit ID (BUID).                    // 0.0
/*164 */          */                                                                    // 0.0
/*166 */         sr = env->sr[eaddr >> 28];                                             // 0.0
/*168 */         if ((sr & 0x1FF00000) >> 20 == 0x07f) {                                // 0.0
/*170 */             /* Memory-forced I/O controller interface access */                // 0.0
/*172 */             /* If T=1 and BUID=x'07F', the 601 performs a memory access        // 0.0
/*174 */              * to SR[28-31] LA[4-31], bypassing all protection mechanisms.     // 0.0
/*176 */              */                                                                // 0.0
/*178 */             ctx->raddr = ((sr & 0xF) << 28) | (eaddr & 0x0FFFFFFF);            // 0.0
/*180 */             ctx->prot = PAGE_READ | PAGE_WRITE | PAGE_EXEC;                    // 0.0
/*182 */             return 0;                                                          // 0.0
/*184 */         }                                                                      // 0.0
/*188 */         switch (type) {                                                        // 0.0
/*190 */         case ACCESS_INT:                                                       // 0.0
/*192 */             /* Integer load/store : only access allowed */                     // 0.0
/*194 */             break;                                                             // 0.0
/*196 */         case ACCESS_CODE:                                                      // 0.0
/*198 */             /* No code fetch is allowed in direct-store areas */               // 0.0
/*200 */             return -4;                                                         // 0.0
/*202 */         case ACCESS_FLOAT:                                                     // 0.0
/*204 */             /* Floating point load/store */                                    // 0.0
/*206 */             return -4;                                                         // 0.0
/*208 */         case ACCESS_RES:                                                       // 0.0
/*210 */             /* lwarx, ldarx or srwcx. */                                       // 0.0
/*212 */             return -4;                                                         // 0.0
/*214 */         case ACCESS_CACHE:                                                     // 0.0
/*216 */             /* dcba, dcbt, dcbtst, dcbf, dcbi, dcbst, dcbz, or icbi */         // 0.0
/*218 */             /* Should make the instruction do no-op.                           // 0.0
/*220 */              * As it already do no-op, it's quite easy :-)                     // 0.0
/*222 */              */                                                                // 0.0
/*224 */             ctx->raddr = eaddr;                                                // 0.0
/*226 */             return 0;                                                          // 0.0
/*228 */         case ACCESS_EXT:                                                       // 0.0
/*230 */             /* eciwx or ecowx */                                               // 0.0
/*232 */             return -4;                                                         // 0.0
/*234 */         default:                                                               // 0.0
/*236 */             qemu_log_mask(CPU_LOG_MMU, "ERROR: instruction should not need "   // 0.0
/*238 */                           "address translation\n");                            // 0.0
/*240 */             return -4;                                                         // 0.0
/*242 */         }                                                                      // 0.0
/*244 */         if ((rw == 1 || ctx->key != 1) && (rw == 0 || ctx->key != 0)) {        // 0.0
/*246 */             ctx->raddr = eaddr;                                                // 0.0
/*248 */             ret = 2;                                                           // 0.0
/*250 */         } else {                                                               // 0.0
/*252 */             ret = -2;                                                          // 0.0
/*254 */         }                                                                      // 0.0
/*256 */     }                                                                          // 0.0
/*260 */     return ret;                                                                // 0.0
/*262 */ }                                                                              // 0.0
