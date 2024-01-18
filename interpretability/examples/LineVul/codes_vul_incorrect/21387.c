// commit message qemu@4656e1f012 (target=1, prob=0.04134401, correct=False): ppc64: Rudimentary Support for extra page sizes on server CPUs
/*0   */ int cpu_ppc_handle_mmu_fault(CPUPPCState *env, target_ulong address, int rw,    // (3) 0.06055
/*2   */                              int mmu_idx)                                       // (1) 0.06836
/*4   */ {                                                                               // (26) 0.001953
/*6   */     mmu_ctx_t ctx;                                                              // (14) 0.02344
/*8   */     int access_type;                                                            // (22) 0.01562
/*10  */     int ret = 0;                                                                // (23) 0.01562
/*14  */     if (rw == 2) {                                                              // (20) 0.01953
/*16  */         /* code access */                                                       // (17) 0.02148
/*18  */         rw = 0;                                                                 // (16) 0.02344
/*20  */         access_type = ACCESS_CODE;                                              // (10) 0.0332
/*22  */     } else {                                                                    // (24) 0.01172
/*24  */         /* data access */                                                       // (18) 0.02148
/*26  */         access_type = env->access_type;                                         // (9) 0.0332
/*28  */     }                                                                           // (25) 0.007812
/*30  */     ret = get_physical_address(env, &ctx, address, rw, access_type);            // (7) 0.04883
/*32  */     if (ret == 0) {                                                             // (21) 0.01953
/*34  */         tlb_set_page(env, address & TARGET_PAGE_MASK,                           // (4) 0.05273
/*36  */                      ctx.raddr & TARGET_PAGE_MASK, ctx.prot,                    // (0) 0.07812
/*38  */                      mmu_idx, TARGET_PAGE_SIZE);                                // (2) 0.06641
/*40  */         ret = 0;                                                                // (19) 0.02148
/*42  */     } else if (ret < 0) {                                                       // (15) 0.02344
/*44  */         LOG_MMU_STATE(env);                                                     // (11) 0.03125
/*46  */         if (access_type == ACCESS_CODE) {                                       // (8) 0.03906
/*48  */             switch (ret) {                                                      // (12) 0.03125
/*50  */             case -1:                                                            // (13) 0.0293
/*52  */                 /* No matches in page tables or TLB */                          // (5) 0.04883
/*54  */                 switch (env->mmu_model) {                                       // (6) 0.04883
/*56  */                 case POWERPC_MMU_SOFT_6xx:                                      // 0.0
/*58  */                     env->exception_index = POWERPC_EXCP_IFTLB;                  // 0.0
/*60  */                     env->error_code = 1 << 18;                                  // 0.0
/*62  */                     env->spr[SPR_IMISS] = address;                              // 0.0
/*64  */                     env->spr[SPR_ICMP] = 0x80000000 | ctx.ptem;                 // 0.0
/*66  */                     goto tlb_miss;                                              // 0.0
/*68  */                 case POWERPC_MMU_SOFT_74xx:                                     // 0.0
/*70  */                     env->exception_index = POWERPC_EXCP_IFTLB;                  // 0.0
/*72  */                     goto tlb_miss_74xx;                                         // 0.0
/*74  */                 case POWERPC_MMU_SOFT_4xx:                                      // 0.0
/*76  */                 case POWERPC_MMU_SOFT_4xx_Z:                                    // 0.0
/*78  */                     env->exception_index = POWERPC_EXCP_ITLB;                   // 0.0
/*80  */                     env->error_code = 0;                                        // 0.0
/*82  */                     env->spr[SPR_40x_DEAR] = address;                           // 0.0
/*84  */                     env->spr[SPR_40x_ESR] = 0x00000000;                         // 0.0
/*86  */                     break;                                                      // 0.0
/*88  */                 case POWERPC_MMU_32B:                                           // 0.0
/*90  */                 case POWERPC_MMU_601:                                           // 0.0
/*92  */ #if defined(TARGET_PPC64)                                                       // 0.0
/*94  */                 case POWERPC_MMU_620:                                           // 0.0
/*96  */                 case POWERPC_MMU_64B:                                           // 0.0
/*98  */                 case POWERPC_MMU_2_06:                                          // 0.0
/*101 */ #endif                                                                          // 0.0
/*103 */                     env->exception_index = POWERPC_EXCP_ISI;                    // 0.0
/*105 */                     env->error_code = 0x40000000;                               // 0.0
/*107 */                     break;                                                      // 0.0
/*109 */                 case POWERPC_MMU_BOOKE206:                                      // 0.0
/*111 */                     booke206_update_mas_tlb_miss(env, address, rw);             // 0.0
/*113 */                     /* fall through */                                          // 0.0
/*115 */                 case POWERPC_MMU_BOOKE:                                         // 0.0
/*117 */                     env->exception_index = POWERPC_EXCP_ITLB;                   // 0.0
/*119 */                     env->error_code = 0;                                        // 0.0
/*121 */                     env->spr[SPR_BOOKE_DEAR] = address;                         // 0.0
/*123 */                     return -1;                                                  // 0.0
/*125 */                 case POWERPC_MMU_MPC8xx:                                        // 0.0
/*127 */                     /* XXX: TODO */                                             // 0.0
/*129 */                     cpu_abort(env, "MPC8xx MMU model is not implemented\n");    // 0.0
/*131 */                     break;                                                      // 0.0
/*133 */                 case POWERPC_MMU_REAL:                                          // 0.0
/*135 */                     cpu_abort(env, "PowerPC in real mode should never raise "   // 0.0
/*137 */                               "any MMU exceptions\n");                          // 0.0
/*139 */                     return -1;                                                  // 0.0
/*141 */                 default:                                                        // 0.0
/*143 */                     cpu_abort(env, "Unknown or invalid MMU model\n");           // 0.0
/*145 */                     return -1;                                                  // 0.0
/*147 */                 }                                                               // 0.0
/*149 */                 break;                                                          // 0.0
/*151 */             case -2:                                                            // 0.0
/*153 */                 /* Access rights violation */                                   // 0.0
/*155 */                 env->exception_index = POWERPC_EXCP_ISI;                        // 0.0
/*157 */                 env->error_code = 0x08000000;                                   // 0.0
/*159 */                 break;                                                          // 0.0
/*161 */             case -3:                                                            // 0.0
/*163 */                 /* No execute protection violation */                           // 0.0
/*165 */                 if ((env->mmu_model == POWERPC_MMU_BOOKE) ||                    // 0.0
/*167 */                     (env->mmu_model == POWERPC_MMU_BOOKE206)) {                 // 0.0
/*169 */                     env->spr[SPR_BOOKE_ESR] = 0x00000000;                       // 0.0
/*171 */                 }                                                               // 0.0
/*173 */                 env->exception_index = POWERPC_EXCP_ISI;                        // 0.0
/*175 */                 env->error_code = 0x10000000;                                   // 0.0
/*177 */                 break;                                                          // 0.0
/*179 */             case -4:                                                            // 0.0
/*181 */                 /* Direct store exception */                                    // 0.0
/*183 */                 /* No code fetch is allowed in direct-store areas */            // 0.0
/*185 */                 env->exception_index = POWERPC_EXCP_ISI;                        // 0.0
/*187 */                 env->error_code = 0x10000000;                                   // 0.0
/*189 */                 break;                                                          // 0.0
/*191 */ #if defined(TARGET_PPC64)                                                       // 0.0
/*193 */             case -5:                                                            // 0.0
/*195 */                 /* No match in segment table */                                 // 0.0
/*197 */                 if (env->mmu_model == POWERPC_MMU_620) {                        // 0.0
/*199 */                     env->exception_index = POWERPC_EXCP_ISI;                    // 0.0
/*201 */                     /* XXX: this might be incorrect */                          // 0.0
/*203 */                     env->error_code = 0x40000000;                               // 0.0
/*205 */                 } else {                                                        // 0.0
/*207 */                     env->exception_index = POWERPC_EXCP_ISEG;                   // 0.0
/*209 */                     env->error_code = 0;                                        // 0.0
/*211 */                 }                                                               // 0.0
/*213 */                 break;                                                          // 0.0
/*215 */ #endif                                                                          // 0.0
/*217 */             }                                                                   // 0.0
/*219 */         } else {                                                                // 0.0
/*221 */             switch (ret) {                                                      // 0.0
/*223 */             case -1:                                                            // 0.0
/*225 */                 /* No matches in page tables or TLB */                          // 0.0
/*227 */                 switch (env->mmu_model) {                                       // 0.0
/*229 */                 case POWERPC_MMU_SOFT_6xx:                                      // 0.0
/*231 */                     if (rw == 1) {                                              // 0.0
/*233 */                         env->exception_index = POWERPC_EXCP_DSTLB;              // 0.0
/*235 */                         env->error_code = 1 << 16;                              // 0.0
/*237 */                     } else {                                                    // 0.0
/*239 */                         env->exception_index = POWERPC_EXCP_DLTLB;              // 0.0
/*241 */                         env->error_code = 0;                                    // 0.0
/*243 */                     }                                                           // 0.0
/*245 */                     env->spr[SPR_DMISS] = address;                              // 0.0
/*247 */                     env->spr[SPR_DCMP] = 0x80000000 | ctx.ptem;                 // 0.0
/*249 */                 tlb_miss:                                                       // 0.0
/*251 */                     env->error_code |= ctx.key << 19;                           // 0.0
/*253 */                     env->spr[SPR_HASH1] = env->htab_base +                      // 0.0
/*255 */                         get_pteg_offset(env, ctx.hash[0], HASH_PTE_SIZE_32);    // 0.0
/*257 */                     env->spr[SPR_HASH2] = env->htab_base +                      // 0.0
/*259 */                         get_pteg_offset(env, ctx.hash[1], HASH_PTE_SIZE_32);    // 0.0
/*261 */                     break;                                                      // 0.0
/*263 */                 case POWERPC_MMU_SOFT_74xx:                                     // 0.0
/*265 */                     if (rw == 1) {                                              // 0.0
/*267 */                         env->exception_index = POWERPC_EXCP_DSTLB;              // 0.0
/*269 */                     } else {                                                    // 0.0
/*271 */                         env->exception_index = POWERPC_EXCP_DLTLB;              // 0.0
/*273 */                     }                                                           // 0.0
/*275 */                 tlb_miss_74xx:                                                  // 0.0
/*277 */                     /* Implement LRU algorithm */                               // 0.0
/*279 */                     env->error_code = ctx.key << 19;                            // 0.0
/*281 */                     env->spr[SPR_TLBMISS] = (address & ~((target_ulong)0x3)) |  // 0.0
/*283 */                         ((env->last_way + 1) & (env->nb_ways - 1));             // 0.0
/*285 */                     env->spr[SPR_PTEHI] = 0x80000000 | ctx.ptem;                // 0.0
/*287 */                     break;                                                      // 0.0
/*289 */                 case POWERPC_MMU_SOFT_4xx:                                      // 0.0
/*291 */                 case POWERPC_MMU_SOFT_4xx_Z:                                    // 0.0
/*293 */                     env->exception_index = POWERPC_EXCP_DTLB;                   // 0.0
/*295 */                     env->error_code = 0;                                        // 0.0
/*297 */                     env->spr[SPR_40x_DEAR] = address;                           // 0.0
/*299 */                     if (rw) {                                                   // 0.0
/*301 */                         env->spr[SPR_40x_ESR] = 0x00800000;                     // 0.0
/*303 */                     } else {                                                    // 0.0
/*305 */                         env->spr[SPR_40x_ESR] = 0x00000000;                     // 0.0
/*307 */                     }                                                           // 0.0
/*309 */                     break;                                                      // 0.0
/*311 */                 case POWERPC_MMU_32B:                                           // 0.0
/*313 */                 case POWERPC_MMU_601:                                           // 0.0
/*315 */ #if defined(TARGET_PPC64)                                                       // 0.0
/*317 */                 case POWERPC_MMU_620:                                           // 0.0
/*319 */                 case POWERPC_MMU_64B:                                           // 0.0
/*321 */                 case POWERPC_MMU_2_06:                                          // 0.0
/*324 */ #endif                                                                          // 0.0
/*326 */                     env->exception_index = POWERPC_EXCP_DSI;                    // 0.0
/*328 */                     env->error_code = 0;                                        // 0.0
/*330 */                     env->spr[SPR_DAR] = address;                                // 0.0
/*332 */                     if (rw == 1) {                                              // 0.0
/*334 */                         env->spr[SPR_DSISR] = 0x42000000;                       // 0.0
/*336 */                     } else {                                                    // 0.0
/*338 */                         env->spr[SPR_DSISR] = 0x40000000;                       // 0.0
/*340 */                     }                                                           // 0.0
/*342 */                     break;                                                      // 0.0
/*344 */                 case POWERPC_MMU_MPC8xx:                                        // 0.0
/*346 */                     /* XXX: TODO */                                             // 0.0
/*348 */                     cpu_abort(env, "MPC8xx MMU model is not implemented\n");    // 0.0
/*350 */                     break;                                                      // 0.0
/*352 */                 case POWERPC_MMU_BOOKE206:                                      // 0.0
/*354 */                     booke206_update_mas_tlb_miss(env, address, rw);             // 0.0
/*356 */                     /* fall through */                                          // 0.0
/*358 */                 case POWERPC_MMU_BOOKE:                                         // 0.0
/*360 */                     env->exception_index = POWERPC_EXCP_DTLB;                   // 0.0
/*362 */                     env->error_code = 0;                                        // 0.0
/*364 */                     env->spr[SPR_BOOKE_DEAR] = address;                         // 0.0
/*366 */                     env->spr[SPR_BOOKE_ESR] = rw ? ESR_ST : 0;                  // 0.0
/*368 */                     return -1;                                                  // 0.0
/*370 */                 case POWERPC_MMU_REAL:                                          // 0.0
/*372 */                     cpu_abort(env, "PowerPC in real mode should never raise "   // 0.0
/*374 */                               "any MMU exceptions\n");                          // 0.0
/*376 */                     return -1;                                                  // 0.0
/*378 */                 default:                                                        // 0.0
/*380 */                     cpu_abort(env, "Unknown or invalid MMU model\n");           // 0.0
/*382 */                     return -1;                                                  // 0.0
/*384 */                 }                                                               // 0.0
/*386 */                 break;                                                          // 0.0
/*388 */             case -2:                                                            // 0.0
/*390 */                 /* Access rights violation */                                   // 0.0
/*392 */                 env->exception_index = POWERPC_EXCP_DSI;                        // 0.0
/*394 */                 env->error_code = 0;                                            // 0.0
/*396 */                 if (env->mmu_model == POWERPC_MMU_SOFT_4xx                      // 0.0
/*398 */                     || env->mmu_model == POWERPC_MMU_SOFT_4xx_Z) {              // 0.0
/*400 */                     env->spr[SPR_40x_DEAR] = address;                           // 0.0
/*402 */                     if (rw) {                                                   // 0.0
/*404 */                         env->spr[SPR_40x_ESR] |= 0x00800000;                    // 0.0
/*406 */                     }                                                           // 0.0
/*408 */                 } else if ((env->mmu_model == POWERPC_MMU_BOOKE) ||             // 0.0
/*410 */                            (env->mmu_model == POWERPC_MMU_BOOKE206)) {          // 0.0
/*412 */                     env->spr[SPR_BOOKE_DEAR] = address;                         // 0.0
/*414 */                     env->spr[SPR_BOOKE_ESR] = rw ? ESR_ST : 0;                  // 0.0
/*416 */                 } else {                                                        // 0.0
/*418 */                     env->spr[SPR_DAR] = address;                                // 0.0
/*420 */                     if (rw == 1) {                                              // 0.0
/*422 */                         env->spr[SPR_DSISR] = 0x0A000000;                       // 0.0
/*424 */                     } else {                                                    // 0.0
/*426 */                         env->spr[SPR_DSISR] = 0x08000000;                       // 0.0
/*428 */                     }                                                           // 0.0
/*430 */                 }                                                               // 0.0
/*432 */                 break;                                                          // 0.0
/*434 */             case -4:                                                            // 0.0
/*436 */                 /* Direct store exception */                                    // 0.0
/*438 */                 switch (access_type) {                                          // 0.0
/*440 */                 case ACCESS_FLOAT:                                              // 0.0
/*442 */                     /* Floating point load/store */                             // 0.0
/*444 */                     env->exception_index = POWERPC_EXCP_ALIGN;                  // 0.0
/*446 */                     env->error_code = POWERPC_EXCP_ALIGN_FP;                    // 0.0
/*448 */                     env->spr[SPR_DAR] = address;                                // 0.0
/*450 */                     break;                                                      // 0.0
/*452 */                 case ACCESS_RES:                                                // 0.0
/*454 */                     /* lwarx, ldarx or stwcx. */                                // 0.0
/*456 */                     env->exception_index = POWERPC_EXCP_DSI;                    // 0.0
/*458 */                     env->error_code = 0;                                        // 0.0
/*460 */                     env->spr[SPR_DAR] = address;                                // 0.0
/*462 */                     if (rw == 1) {                                              // 0.0
/*464 */                         env->spr[SPR_DSISR] = 0x06000000;                       // 0.0
/*466 */                     } else {                                                    // 0.0
/*468 */                         env->spr[SPR_DSISR] = 0x04000000;                       // 0.0
/*470 */                     }                                                           // 0.0
/*472 */                     break;                                                      // 0.0
/*474 */                 case ACCESS_EXT:                                                // 0.0
/*476 */                     /* eciwx or ecowx */                                        // 0.0
/*478 */                     env->exception_index = POWERPC_EXCP_DSI;                    // 0.0
/*480 */                     env->error_code = 0;                                        // 0.0
/*482 */                     env->spr[SPR_DAR] = address;                                // 0.0
/*484 */                     if (rw == 1) {                                              // 0.0
/*486 */                         env->spr[SPR_DSISR] = 0x06100000;                       // 0.0
/*488 */                     } else {                                                    // 0.0
/*490 */                         env->spr[SPR_DSISR] = 0x04100000;                       // 0.0
/*492 */                     }                                                           // 0.0
/*494 */                     break;                                                      // 0.0
/*496 */                 default:                                                        // 0.0
/*498 */                     printf("DSI: invalid exception (%d)\n", ret);               // 0.0
/*500 */                     env->exception_index = POWERPC_EXCP_PROGRAM;                // 0.0
/*502 */                     env->error_code =                                           // 0.0
/*504 */                         POWERPC_EXCP_INVAL | POWERPC_EXCP_INVAL_INVAL;          // 0.0
/*506 */                     env->spr[SPR_DAR] = address;                                // 0.0
/*508 */                     break;                                                      // 0.0
/*510 */                 }                                                               // 0.0
/*512 */                 break;                                                          // 0.0
/*514 */ #if defined(TARGET_PPC64)                                                       // 0.0
/*516 */             case -5:                                                            // 0.0
/*518 */                 /* No match in segment table */                                 // 0.0
/*520 */                 if (env->mmu_model == POWERPC_MMU_620) {                        // 0.0
/*522 */                     env->exception_index = POWERPC_EXCP_DSI;                    // 0.0
/*524 */                     env->error_code = 0;                                        // 0.0
/*526 */                     env->spr[SPR_DAR] = address;                                // 0.0
/*528 */                     /* XXX: this might be incorrect */                          // 0.0
/*530 */                     if (rw == 1) {                                              // 0.0
/*532 */                         env->spr[SPR_DSISR] = 0x42000000;                       // 0.0
/*534 */                     } else {                                                    // 0.0
/*536 */                         env->spr[SPR_DSISR] = 0x40000000;                       // 0.0
/*538 */                     }                                                           // 0.0
/*540 */                 } else {                                                        // 0.0
/*542 */                     env->exception_index = POWERPC_EXCP_DSEG;                   // 0.0
/*544 */                     env->error_code = 0;                                        // 0.0
/*546 */                     env->spr[SPR_DAR] = address;                                // 0.0
/*548 */                 }                                                               // 0.0
/*550 */                 break;                                                          // 0.0
/*552 */ #endif                                                                          // 0.0
/*554 */             }                                                                   // 0.0
/*556 */         }                                                                       // 0.0
/*558 */ #if 0                                                                           // 0.0
/*560 */         printf("%s: set exception to %d %02x\n", __func__,                      // 0.0
/*562 */                env->exception, env->error_code);                                // 0.0
/*564 */ #endif                                                                          // 0.0
/*566 */         ret = 1;                                                                // 0.0
/*568 */     }                                                                           // 0.0
/*572 */     return ret;                                                                 // 0.0
/*574 */ }                                                                               // 0.0
