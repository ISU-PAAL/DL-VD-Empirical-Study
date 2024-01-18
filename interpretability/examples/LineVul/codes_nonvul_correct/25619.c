// commit message qemu@46c5874e9c (target=0, prob=0.028294455, correct=True): spapr_pci: Make find_phb()/find_dev() public
/*0  */ static void rtas_ibm_read_slot_reset_state2(PowerPCCPU *cpu,                   // (6) 0.04883
/*2  */                                             sPAPREnvironment *spapr,           // (2) 0.1055
/*4  */                                             uint32_t token, uint32_t nargs,    // (0) 0.1094
/*6  */                                             target_ulong args, uint32_t nret,  // (1) 0.1094
/*8  */                                             target_ulong rets)                 // (3) 0.09765
/*10 */ {                                                                              // (21) 0.001953
/*12 */     sPAPRPHBState *sphb;                                                       // (10) 0.0293
/*14 */     sPAPRPHBClass *spc;                                                        // (11) 0.02734
/*16 */     uint64_t buid;                                                             // (15) 0.01953
/*18 */     int state, ret;                                                            // (17) 0.01562
/*22 */     if ((nargs != 3) || (nret != 4 && nret != 5)) {                            // (7) 0.04492
/*24 */         goto param_error_exit;                                                 // (12) 0.02734
/*26 */     }                                                                          // (20) 0.007812
/*30 */     buid = ((uint64_t)rtas_ld(args, 1) << 32) | rtas_ld(args, 2);              // (4) 0.06836
/*32 */     sphb = find_phb(spapr, buid);                                              // (8) 0.03711
/*34 */     if (!sphb) {                                                               // (16) 0.01953
/*36 */         goto param_error_exit;                                                 // (13) 0.02734
/*38 */     }                                                                          // (19) 0.007812
/*42 */     spc = SPAPR_PCI_HOST_BRIDGE_GET_CLASS(sphb);                               // (5) 0.05469
/*44 */     if (!spc->eeh_get_state) {                                                 // (9) 0.03125
/*46 */         goto param_error_exit;                                                 // (14) 0.02734
/*48 */     }                                                                          // (18) 0.007812
/*52 */     ret = spc->eeh_get_state(sphb, &state);                                    // 0.0
/*54 */     rtas_st(rets, 0, ret);                                                     // 0.0
/*56 */     if (ret != RTAS_OUT_SUCCESS) {                                             // 0.0
/*58 */         return;                                                                // 0.0
/*60 */     }                                                                          // 0.0
/*64 */     rtas_st(rets, 1, state);                                                   // 0.0
/*66 */     rtas_st(rets, 2, RTAS_EEH_SUPPORT);                                        // 0.0
/*68 */     rtas_st(rets, 3, RTAS_EEH_PE_UNAVAIL_INFO);                                // 0.0
/*70 */     if (nret >= 5) {                                                           // 0.0
/*72 */         rtas_st(rets, 4, RTAS_EEH_PE_RECOVER_INFO);                            // 0.0
/*74 */     }                                                                          // 0.0
/*76 */     return;                                                                    // 0.0
/*80 */ param_error_exit:                                                              // 0.0
/*82 */     rtas_st(rets, 0, RTAS_OUT_PARAM_ERROR);                                    // 0.0
/*84 */ }                                                                              // 0.0
