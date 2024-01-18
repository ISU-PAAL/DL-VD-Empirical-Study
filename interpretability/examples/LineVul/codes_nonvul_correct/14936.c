// commit message qemu@b769d8fef6 (target=0, prob=0.04043687, correct=True): removed access_type hack
/*0   */ int cpu_ppc_handle_mmu_fault (CPUState *env, uint32_t address, int rw,  // (2) 0.05664
/*2   */                               int is_user, int is_softmmu)              // (0) 0.08008
/*4   */ {                                                                       // (32) 0.001953
/*6   */     uint32_t physical;                                                  // (23) 0.01758
/*8   */     int prot;                                                           // (28) 0.01172
/*10  */     int exception = 0, error_code = 0;                                  // (12) 0.02734
/*12  */     int access_type;                                                    // (27) 0.01562
/*14  */     int ret = 0;                                                        // (26) 0.01562
/*18  */ //    printf("%s 0\n", __func__);                                       // (10) 0.03125
/*20  */     access_type = env->access_type;                                     // (16) 0.02539
/*22  */     if (env->user_mode_only) {                                          // (13) 0.02734
/*24  */         /* user mode only emulation */                                  // (15) 0.02539
/*26  */         ret = -2;                                                       // (18) 0.02344
/*28  */         goto do_fault;                                                  // (14) 0.02539
/*30  */     }                                                                   // (29) 0.007812
/*32  */     /* NASTY BUG workaround */                                          // (19) 0.01953
/*34  */     if (access_type == ACCESS_CODE && rw) {                             // (8) 0.03711
/*36  */ 	printf("%s: ERROR WRITE CODE ACCESS\n", __func__);                     // (9) 0.03516
/*38  */ 	access_type = ACCESS_INT;                                              // (20) 0.01953
/*40  */     }                                                                   // (30) 0.007812
/*42  */     ret = get_physical_address(env, &physical, &prot,                   // (7) 0.03711
/*44  */                                address, rw, access_type);               // (1) 0.07617
/*46  */     if (ret == 0) {                                                     // (21) 0.01953
/*48  */ 	ret = tlb_set_page(env, address & ~0xFFF, physical, prot,              // (3) 0.04688
/*50  */ 			   is_user, is_softmmu);                                             // (11) 0.0293
/*52  */     } else if (ret < 0) {                                               // (17) 0.02344
/*54  */     do_fault:                                                           // (25) 0.01563
/*56  */ #if defined (DEBUG_MMU)                                                 // (22) 0.01758
/*58  */ 	if (loglevel > 0)                                                      // (24) 0.01758
/*60  */ 	    cpu_ppc_dump_state(env, logfile, 0);                               // (4) 0.03906
/*62  */ #endif                                                                  // (31) 0.003906
/*64  */         if (access_type == ACCESS_CODE) {                               // (5) 0.03906
/*66  */             exception = EXCP_ISI;                                       // (6) 0.03711
/*68  */             switch (ret) {                                              // 0.0
/*70  */             case -1:                                                    // 0.0
/*72  */                 /* No matches in page tables */                         // 0.0
/*74  */                 error_code = EXCP_ISI_TRANSLATE;                        // 0.0
/*76  */                 break;                                                  // 0.0
/*78  */             case -2:                                                    // 0.0
/*80  */                 /* Access rights violation */                           // 0.0
/*82  */                 error_code = EXCP_ISI_PROT;                             // 0.0
/*84  */                 break;                                                  // 0.0
/*86  */             case -3:                                                    // 0.0
/*88  */ 		/* No execute protection violation */                                 // 0.0
/*90  */                 error_code = EXCP_ISI_NOEXEC;                           // 0.0
/*92  */                 break;                                                  // 0.0
/*94  */             case -4:                                                    // 0.0
/*96  */                 /* Direct store exception */                            // 0.0
/*98  */                 /* No code fetch is allowed in direct-store areas */    // 0.0
/*100 */                 error_code = EXCP_ISI_DIRECT;                           // 0.0
/*102 */                 break;                                                  // 0.0
/*104 */             }                                                           // 0.0
/*106 */         } else {                                                        // 0.0
/*108 */             exception = EXCP_DSI;                                       // 0.0
/*110 */             switch (ret) {                                              // 0.0
/*112 */             case -1:                                                    // 0.0
/*114 */                 /* No matches in page tables */                         // 0.0
/*116 */                 error_code = EXCP_DSI_TRANSLATE;                        // 0.0
/*118 */                 break;                                                  // 0.0
/*120 */             case -2:                                                    // 0.0
/*122 */                 /* Access rights violation */                           // 0.0
/*124 */                 error_code = EXCP_DSI_PROT;                             // 0.0
/*126 */                 break;                                                  // 0.0
/*128 */             case -4:                                                    // 0.0
/*130 */                 /* Direct store exception */                            // 0.0
/*132 */                 switch (access_type) {                                  // 0.0
/*134 */                 case ACCESS_FLOAT:                                      // 0.0
/*136 */                     /* Floating point load/store */                     // 0.0
/*138 */                     exception = EXCP_ALIGN;                             // 0.0
/*140 */                     error_code = EXCP_ALIGN_FP;                         // 0.0
/*142 */                     break;                                              // 0.0
/*144 */                 case ACCESS_RES:                                        // 0.0
/*146 */                     /* lwarx, ldarx or srwcx. */                        // 0.0
/*148 */                     exception = EXCP_DSI;                               // 0.0
/*150 */                     error_code = EXCP_DSI_NOTSUP | EXCP_DSI_DIRECT;     // 0.0
/*152 */                     break;                                              // 0.0
/*154 */                 case ACCESS_EXT:                                        // 0.0
/*156 */                     /* eciwx or ecowx */                                // 0.0
/*158 */                     exception = EXCP_DSI;                               // 0.0
/*160 */                     error_code = EXCP_DSI_NOTSUP | EXCP_DSI_DIRECT |    // 0.0
/*162 */ 			EXCP_DSI_ECXW;                                                       // 0.0
/*164 */                     break;                                              // 0.0
/*166 */                 default:                                                // 0.0
/*168 */ 		    printf("DSI: invalid exception (%d)\n", ret);                     // 0.0
/*170 */                     exception = EXCP_PROGRAM;                           // 0.0
/*172 */                     error_code = EXCP_INVAL | EXCP_INVAL_INVAL;         // 0.0
/*174 */                     break;                                              // 0.0
/*176 */                 }                                                       // 0.0
/*178 */             }                                                           // 0.0
/*180 */             if (rw)                                                     // 0.0
/*182 */                 error_code |= EXCP_DSI_STORE;                           // 0.0
/*184 */ 	    /* Store fault address */                                          // 0.0
/*186 */ 	    env->spr[DAR] = address;                                           // 0.0
/*188 */         }                                                               // 0.0
/*190 */ #if 0                                                                   // 0.0
/*192 */         printf("%s: set exception to %d %02x\n",                        // 0.0
/*194 */                __func__, exception, error_code);                        // 0.0
/*196 */ #endif                                                                  // 0.0
/*198 */         env->exception_index = exception;                               // 0.0
/*200 */         env->error_code = error_code;                                   // 0.0
/*202 */         ret = 1;                                                        // 0.0
/*204 */     }                                                                   // 0.0
/*208 */     return ret;                                                         // 0.0
/*210 */ }                                                                       // 0.0
