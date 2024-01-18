// commit message qemu@1466cef32d (target=0, prob=0.62905425, correct=False): pc: fix regression for 64 bit PCI memory
/*0  */ static int mch_init(PCIDevice *d)                                                           // (12) 0.02734
/*2  */ {                                                                                           // (15) 0.001953
/*4  */     int i;                                                                                  // (14) 0.01172
/*6  */     MCHPCIState *mch = MCH_PCI_DEVICE(d);                                                   // (11) 0.04492
/*10 */     /* setup pci memory regions */                                                          // (13) 0.01758
/*12 */     memory_region_init_alias(&mch->pci_hole, OBJECT(mch), "pci-hole",                       // (9) 0.06055
/*14 */                              mch->pci_address_space,                                        // (5) 0.07422
/*16 */                              mch->below_4g_mem_size,                                        // (3) 0.07812
/*18 */                              0x100000000ULL - mch->below_4g_mem_size);                      // (0) 0.08984
/*20 */     memory_region_add_subregion(mch->system_memory, mch->below_4g_mem_size,                 // (10) 0.06055
/*22 */                                 &mch->pci_hole);                                            // (2) 0.07813
/*26 */     pc_init_pci64_hole(&mch->pci_info, 0x100000000ULL + mch->above_4g_mem_size,             // (4) 0.07617
/*28 */                        mch->pci_hole64_size);                                               // (8) 0.06445
/*30 */     memory_region_init_alias(&mch->pci_hole_64bit, OBJECT(mch), "pci-hole64",               // (7) 0.06836
/*32 */                              mch->pci_address_space,                                        // (6) 0.07422
/*34 */                              mch->pci_info.w64.begin,                                       // (1) 0.08008
/*36 */                              mch->pci_hole64_size);                                         // 0.0
/*38 */     if (mch->pci_hole64_size) {                                                             // 0.0
/*40 */         memory_region_add_subregion(mch->system_memory,                                     // 0.0
/*42 */                                     mch->pci_info.w64.begin,                                // 0.0
/*44 */                                     &mch->pci_hole_64bit);                                  // 0.0
/*46 */     }                                                                                       // 0.0
/*48 */     /* smram */                                                                             // 0.0
/*50 */     cpu_smm_register(&mch_set_smm, mch);                                                    // 0.0
/*52 */     memory_region_init_alias(&mch->smram_region, OBJECT(mch), "smram-region",               // 0.0
/*54 */                              mch->pci_address_space, 0xa0000, 0x20000);                     // 0.0
/*56 */     memory_region_add_subregion_overlap(mch->system_memory, 0xa0000,                        // 0.0
/*58 */                                         &mch->smram_region, 1);                             // 0.0
/*60 */     memory_region_set_enabled(&mch->smram_region, false);                                   // 0.0
/*62 */     init_pam(DEVICE(mch), mch->ram_memory, mch->system_memory, mch->pci_address_space,      // 0.0
/*64 */              &mch->pam_regions[0], PAM_BIOS_BASE, PAM_BIOS_SIZE);                           // 0.0
/*66 */     for (i = 0; i < 12; ++i) {                                                              // 0.0
/*68 */         init_pam(DEVICE(mch), mch->ram_memory, mch->system_memory, mch->pci_address_space,  // 0.0
/*70 */                  &mch->pam_regions[i+1], PAM_EXPAN_BASE + i * PAM_EXPAN_SIZE,               // 0.0
/*72 */                  PAM_EXPAN_SIZE);                                                           // 0.0
/*74 */     }                                                                                       // 0.0
/*76 */     return 0;                                                                               // 0.0
/*78 */ }                                                                                           // 0.0
