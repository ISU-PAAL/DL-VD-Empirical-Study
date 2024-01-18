// commit message qemu@12de9a396a (target=1, prob=0.0927768, correct=False): Full implementation of PowerPC 64 MMU, just missing support for 1 TB   memory segments. Remove the PowerPC 64 "bridge" MMU model and implement segment registers   emulation using SLB entries instead. Make SLB area size implementation dependant. Improve TLB & SLB search debug traces. Temporary hack to make PowerPC 970 boot from ROM instead of RAM.
/*0   */ static int check_physical (CPUState *env, mmu_ctx_t *ctx,                 // (3) 0.03906
/*2   */                            target_ulong eaddr, int rw)                    // (0) 0.07227
/*4   */ {                                                                         // (30) 0.001953
/*6   */     int in_plb, ret;                                                      // (24) 0.02148
/*10  */     ctx->raddr = eaddr;                                                   // (23) 0.02344
/*12  */     ctx->prot = PAGE_READ;                                                // (21) 0.02344
/*14  */     ret = 0;                                                              // (28) 0.01367
/*16  */     switch (env->mmu_model) {                                             // (17) 0.02539
/*18  */     case POWERPC_MMU_32B:                                                 // (18) 0.02539
/*20  */     case POWERPC_MMU_SOFT_6xx:                                            // (11) 0.03125
/*22  */     case POWERPC_MMU_SOFT_74xx:                                           // (10) 0.03125
/*24  */     case POWERPC_MMU_601:                                                 // (22) 0.02344
/*26  */     case POWERPC_MMU_SOFT_4xx:                                            // (13) 0.03125
/*28  */     case POWERPC_MMU_REAL_4xx:                                            // (12) 0.03125
/*30  */     case POWERPC_MMU_BOOKE:                                               // (16) 0.02734
/*32  */         ctx->prot |= PAGE_WRITE;                                          // (7) 0.03516
/*34  */         break;                                                            // (26) 0.01758
/*36  */ #if defined(TARGET_PPC64)                                                 // (25) 0.02148
/*38  */     case POWERPC_MMU_64B:                                                 // (20) 0.02539
/*40  */     case POWERPC_MMU_64BRIDGE:                                            // (14) 0.0293
/*42  */         /* Real address are 60 bits long */                               // (15) 0.0293
/*44  */         ctx->raddr &= 0x0FFFFFFFFFFFFFFFULL;                              // (2) 0.04687
/*46  */         ctx->prot |= PAGE_WRITE;                                          // (8) 0.03516
/*48  */         break;                                                            // (27) 0.01758
/*50  */ #endif                                                                    // (29) 0.003906
/*52  */     case POWERPC_MMU_SOFT_4xx_Z:                                          // (6) 0.03516
/*54  */         if (unlikely(msr_pe != 0)) {                                      // (4) 0.03906
/*56  */             /* 403 family add some particular protections,                // (5) 0.03711
/*58  */              * using PBL/PBU registers for accesses with no translation.  // (1) 0.05273
/*60  */              */                                                           // (19) 0.02539
/*62  */             in_plb =                                                      // (9) 0.03125
/*64  */                 /* Check PLB validity */                                  // 0.0
/*66  */                 (env->pb[0] < env->pb[1] &&                               // 0.0
/*68  */                  /* and address in plb area */                            // 0.0
/*70  */                  eaddr >= env->pb[0] && eaddr < env->pb[1]) ||            // 0.0
/*72  */                 (env->pb[2] < env->pb[3] &&                               // 0.0
/*74  */                  eaddr >= env->pb[2] && eaddr < env->pb[3]) ? 1 : 0;      // 0.0
/*76  */             if (in_plb ^ msr_px) {                                        // 0.0
/*78  */                 /* Access in protected area */                            // 0.0
/*80  */                 if (rw == 1) {                                            // 0.0
/*82  */                     /* Access is not allowed */                           // 0.0
/*84  */                     ret = -2;                                             // 0.0
/*86  */                 }                                                         // 0.0
/*88  */             } else {                                                      // 0.0
/*90  */                 /* Read-write access is allowed */                        // 0.0
/*92  */                 ctx->prot |= PAGE_WRITE;                                  // 0.0
/*94  */             }                                                             // 0.0
/*96  */         }                                                                 // 0.0
/*98  */         break;                                                            // 0.0
/*100 */     case POWERPC_MMU_BOOKE_FSL:                                           // 0.0
/*102 */         /* XXX: TODO */                                                   // 0.0
/*104 */         cpu_abort(env, "BookE FSL MMU model not implemented\n");          // 0.0
/*106 */         break;                                                            // 0.0
/*108 */     default:                                                              // 0.0
/*110 */         cpu_abort(env, "Unknown or invalid MMU model\n");                 // 0.0
/*112 */         return -1;                                                        // 0.0
/*114 */     }                                                                     // 0.0
/*118 */     return ret;                                                           // 0.0
/*120 */ }                                                                         // 0.0
