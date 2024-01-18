// commit message qemu@44bc910794 (target=0, prob=0.18889083, correct=True): target-ppc: Rework get_physical_address()
/*0   */ static int get_physical_address(CPUPPCState *env, mmu_ctx_t *ctx,                // (9) 0.04688
/*2   */                                 target_ulong eaddr, int rw, int access_type)     // (2) 0.0918
/*4   */ {                                                                                // (18) 0.001953
/*6   */     int ret;                                                                     // (15) 0.01172
/*10  */ #if 0                                                                            // (16) 0.005859
/*12  */     qemu_log("%s\n", __func__);                                                  // (12) 0.03516
/*14  */ #endif                                                                           // (17) 0.003906
/*16  */     if ((access_type == ACCESS_CODE && msr_ir == 0) ||                           // (11) 0.04492
/*18  */         (access_type != ACCESS_CODE && msr_dr == 0)) {                           // (7) 0.05078
/*20  */         if (env->mmu_model == POWERPC_MMU_BOOKE) {                               // (6) 0.05273
/*22  */             /* The BookE MMU always performs address translation. The            // (10) 0.04492
/*24  */                IS and DS bits only affect the address space.  */                 // (8) 0.05078
/*26  */             ret = mmubooke_get_physical_address(env, ctx, eaddr,                 // (4) 0.0625
/*28  */                                                 rw, access_type);                // (0) 0.1055
/*30  */         } else if (env->mmu_model == POWERPC_MMU_BOOKE206) {                     // (5) 0.05859
/*32  */             ret = mmubooke206_get_physical_address(env, ctx, eaddr, rw,          // (3) 0.07031
/*34  */                                                    access_type);                 // (1) 0.1055
/*36  */         } else {                                                                 // (14) 0.01953
/*38  */             /* No address translation.  */                                       // (13) 0.03516
/*40  */             ret = check_physical(env, ctx, eaddr, rw);                           // 0.0
/*42  */         }                                                                        // 0.0
/*44  */     } else {                                                                     // 0.0
/*46  */         ret = -1;                                                                // 0.0
/*48  */         switch (env->mmu_model) {                                                // 0.0
/*50  */         case POWERPC_MMU_32B:                                                    // 0.0
/*52  */         case POWERPC_MMU_601:                                                    // 0.0
/*54  */             /* Try to find a BAT */                                              // 0.0
/*56  */             if (env->nb_BATs != 0) {                                             // 0.0
/*58  */                 ret = get_bat(env, ctx, eaddr, rw, access_type);                 // 0.0
/*60  */             }                                                                    // 0.0
/*62  */             if (ret < 0) {                                                       // 0.0
/*64  */                 /* We didn't match any BAT entry or don't have BATs */           // 0.0
/*66  */                 ret = get_segment32(env, ctx, eaddr, rw, access_type);           // 0.0
/*68  */             }                                                                    // 0.0
/*70  */             break;                                                               // 0.0
/*74  */         case POWERPC_MMU_SOFT_6xx:                                               // 0.0
/*76  */         case POWERPC_MMU_SOFT_74xx:                                              // 0.0
/*78  */             /* Try to find a BAT */                                              // 0.0
/*80  */             if (env->nb_BATs != 0) {                                             // 0.0
/*82  */                 ret = get_bat(env, ctx, eaddr, rw, access_type);                 // 0.0
/*84  */             }                                                                    // 0.0
/*86  */             if (ret < 0) {                                                       // 0.0
/*88  */                 /* We didn't match any BAT entry or don't have BATs */           // 0.0
/*90  */                 ret = get_segment_6xx_tlb(env, ctx, eaddr, rw, access_type);     // 0.0
/*92  */             }                                                                    // 0.0
/*94  */             break;                                                               // 0.0
/*98  */ #if defined(TARGET_PPC64)                                                        // 0.0
/*100 */         case POWERPC_MMU_64B:                                                    // 0.0
/*102 */         case POWERPC_MMU_2_06:                                                   // 0.0
/*104 */         case POWERPC_MMU_2_06d:                                                  // 0.0
/*106 */             ret = get_segment64(env, ctx, eaddr, rw, access_type);               // 0.0
/*108 */             break;                                                               // 0.0
/*110 */ #endif                                                                           // 0.0
/*114 */         case POWERPC_MMU_SOFT_4xx:                                               // 0.0
/*116 */         case POWERPC_MMU_SOFT_4xx_Z:                                             // 0.0
/*118 */             ret = mmu40x_get_physical_address(env, ctx, eaddr,                   // 0.0
/*120 */                                               rw, access_type);                  // 0.0
/*122 */             break;                                                               // 0.0
/*124 */         case POWERPC_MMU_BOOKE:                                                  // 0.0
/*126 */             ret = mmubooke_get_physical_address(env, ctx, eaddr,                 // 0.0
/*128 */                                                 rw, access_type);                // 0.0
/*130 */             break;                                                               // 0.0
/*132 */         case POWERPC_MMU_BOOKE206:                                               // 0.0
/*134 */             ret = mmubooke206_get_physical_address(env, ctx, eaddr, rw,          // 0.0
/*136 */                                                access_type);                     // 0.0
/*138 */             break;                                                               // 0.0
/*140 */         case POWERPC_MMU_MPC8xx:                                                 // 0.0
/*142 */             /* XXX: TODO */                                                      // 0.0
/*144 */             cpu_abort(env, "MPC8xx MMU model is not implemented\n");             // 0.0
/*146 */             break;                                                               // 0.0
/*148 */         case POWERPC_MMU_REAL:                                                   // 0.0
/*150 */             cpu_abort(env, "PowerPC in real mode do not do any translation\n");  // 0.0
/*152 */             return -1;                                                           // 0.0
/*154 */         default:                                                                 // 0.0
/*156 */             cpu_abort(env, "Unknown or invalid MMU model\n");                    // 0.0
/*158 */             return -1;                                                           // 0.0
/*160 */         }                                                                        // 0.0
/*162 */     }                                                                            // 0.0
/*164 */ #if 0                                                                            // 0.0
/*166 */     qemu_log("%s address " TARGET_FMT_lx " => %d " TARGET_FMT_plx "\n",          // 0.0
/*168 */              __func__, eaddr, ret, ctx->raddr);                                  // 0.0
/*170 */ #endif                                                                           // 0.0
/*174 */     return ret;                                                                  // 0.0
/*176 */ }                                                                                // 0.0
