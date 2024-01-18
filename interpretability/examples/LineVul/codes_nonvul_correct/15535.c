// commit message qemu@47445c80fb (target=0, prob=0.05433656, correct=True): sPAPR: Revert don't enable EEH on emulated PCI devices
/*0  */ static void rtas_ibm_set_eeh_option(PowerPCCPU *cpu,                   // (6) 0.04494
/*2  */                                     sPAPRMachineState *spapr,          // (2) 0.08979
/*4  */                                     uint32_t token, uint32_t nargs,    // (0) 0.09419
/*6  */                                     target_ulong args, uint32_t nret,  // (1) 0.0937
/*8  */                                     target_ulong rets)                 // (3) 0.08198
/*10 */ {                                                                      // (22) 0.001952
/*12 */     sPAPRPHBState *sphb;                                               // (11) 0.02928
/*14 */     sPAPRPHBClass *spc;                                                // (12) 0.02733
/*16 */     PCIDevice *pdev;                                                   // (16) 0.02148
/*18 */     uint32_t addr, option;                                             // (15) 0.02149
/*20 */     uint64_t buid;                                                     // (17) 0.01952
/*22 */     int ret;                                                           // (19) 0.01171
/*26 */     if ((nargs != 4) || (nret != 1)) {                                 // (7) 0.03514
/*28 */         goto param_error_exit;                                         // (13) 0.02733
/*30 */     }                                                                  // (20) 0.007808
/*34 */     buid = rtas_ldq(args, 1);                                          // (8) 0.03318
/*36 */     addr = rtas_ld(args, 0);                                           // (10) 0.02928
/*38 */     option = rtas_ld(args, 3);                                         // (9) 0.02928
/*42 */     sphb = spapr_pci_find_phb(spapr, buid);                            // (5) 0.05075
/*44 */     if (!sphb) {                                                       // (18) 0.01952
/*46 */         goto param_error_exit;                                         // (14) 0.02733
/*48 */     }                                                                  // (21) 0.007808
/*52 */     pdev = pci_find_device(PCI_HOST_BRIDGE(sphb)->bus,                 // (4) 0.05663
/*54 */                            (addr >> 16) & 0xFF, (addr >> 8) & 0xFF);   // 0.0
/*56 */     if (!pdev || !object_dynamic_cast(OBJECT(pdev), "vfio-pci")) {     // 0.0
/*58 */         goto param_error_exit;                                         // 0.0
/*60 */     }                                                                  // 0.0
/*64 */     spc = SPAPR_PCI_HOST_BRIDGE_GET_CLASS(sphb);                       // 0.0
/*66 */     if (!spc->eeh_set_option) {                                        // 0.0
/*68 */         goto param_error_exit;                                         // 0.0
/*70 */     }                                                                  // 0.0
/*74 */     ret = spc->eeh_set_option(sphb, addr, option);                     // 0.0
/*76 */     rtas_st(rets, 0, ret);                                             // 0.0
/*78 */     return;                                                            // 0.0
/*82 */ param_error_exit:                                                      // 0.0
/*84 */     rtas_st(rets, 0, RTAS_OUT_PARAM_ERROR);                            // 0.0
/*86 */ }                                                                      // 0.0
