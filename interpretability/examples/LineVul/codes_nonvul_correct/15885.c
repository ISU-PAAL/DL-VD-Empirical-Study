// commit message qemu@fd56e0612b (target=0, prob=0.02513513, correct=True): pci: Eliminate redundant PCIDevice::bus pointer
/*0   */ static void rtas_ibm_get_config_addr_info2(PowerPCCPU *cpu,                   // (5) 0.04906
/*2   */                                            sPAPRMachineState *spapr,          // (2) 0.1034
/*4   */                                            uint32_t token, uint32_t nargs,    // (0) 0.1083
/*6   */                                            target_ulong args, uint32_t nret,  // (1) 0.1073
/*8   */                                            target_ulong rets)                 // (3) 0.09556
/*10  */ {                                                                             // (24) 0.001957
/*12  */     sPAPRPHBState *sphb;                                                      // (11) 0.02926
/*14  */     PCIDevice *pdev;                                                          // (16) 0.02146
/*16  */     uint32_t addr, option;                                                    // (15) 0.02147
/*18  */     uint64_t buid;                                                            // (17) 0.0195
/*22  */     if ((nargs != 4) || (nret != 2)) {                                        // (8) 0.03511
/*24  */         goto param_error_exit;                                                // (12) 0.0273
/*26  */     }                                                                         // (22) 0.007801
/*30  */     buid = rtas_ldq(args, 1);                                                 // (9) 0.03316
/*32  */     sphb = spapr_pci_find_phb(spapr, buid);                                   // (4) 0.0507
/*34  */     if (!sphb) {                                                              // (18) 0.0195
/*36  */         goto param_error_exit;                                                // (13) 0.0273
/*38  */     }                                                                         // (23) 0.007801
/*42  */     if (!spapr_phb_eeh_available(sphb)) {                                     // (6) 0.04291
/*44  */         goto param_error_exit;                                                // (14) 0.0273
/*46  */     }                                                                         // (20) 0.007802
/*50  */     /*                                                                        // (21) 0.007802
/*52  */      * We always have PE address of form "00BB0001". "BB"                     // (7) 0.03902
/*54  */      * represents the bus number of PE's primary bus.                         // (10) 0.0293
/*56  */      */                                                                       // (19) 0.009751
/*58  */     option = rtas_ld(args, 3);                                                // 0.0
/*60  */     switch (option) {                                                         // 0.0
/*62  */     case RTAS_GET_PE_ADDR:                                                    // 0.0
/*64  */         addr = rtas_ld(args, 0);                                              // 0.0
/*66  */         pdev = spapr_pci_find_dev(spapr, buid, addr);                         // 0.0
/*68  */         if (!pdev) {                                                          // 0.0
/*70  */             goto param_error_exit;                                            // 0.0
/*72  */         }                                                                     // 0.0
/*76  */         rtas_st(rets, 1, (pci_bus_num(pdev->bus) << 16) + 1);                 // 0.0
/*78  */         break;                                                                // 0.0
/*80  */     case RTAS_GET_PE_MODE:                                                    // 0.0
/*82  */         rtas_st(rets, 1, RTAS_PE_MODE_SHARED);                                // 0.0
/*84  */         break;                                                                // 0.0
/*86  */     default:                                                                  // 0.0
/*88  */         goto param_error_exit;                                                // 0.0
/*90  */     }                                                                         // 0.0
/*94  */     rtas_st(rets, 0, RTAS_OUT_SUCCESS);                                       // 0.0
/*96  */     return;                                                                   // 0.0
/*100 */ param_error_exit:                                                             // 0.0
/*102 */     rtas_st(rets, 0, RTAS_OUT_PARAM_ERROR);                                   // 0.0
/*104 */ }                                                                             // 0.0
