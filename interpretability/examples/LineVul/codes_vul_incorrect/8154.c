// commit message qemu@25e6a11832 (target=1, prob=0.099377334, correct=False): ppc: switch to constants within BUILD_BUG_ON
/*0  */ static void spapr_phb_placement(sPAPRMachineState *spapr, uint32_t index,                 // (4) 0.05664
/*2  */                                 uint64_t *buid, hwaddr *pio,                              // (2) 0.08984
/*4  */                                 hwaddr *mmio32, hwaddr *mmio64,                           // (1) 0.0918
/*6  */                                 unsigned n_dma, uint32_t *liobns, Error **errp)           // (0) 0.09961
/*8  */ {                                                                                         // (21) 0.001953
/*10 */     /*                                                                                    // (20) 0.007813
/*12 */      * New-style PHB window placement.                                                    // (13) 0.02539
/*14 */      *                                                                                    // (17) 0.009766
/*16 */      * Goals: Gives large (1TiB), naturally aligned 64-bit MMIO window                    // (9) 0.04688
/*18 */      * for each PHB, in addition to 2GiB 32-bit MMIO and 64kiB PIO                        // (7) 0.05469
/*20 */      * windows.                                                                           // (15) 0.01367
/*22 */      *                                                                                    // (18) 0.009766
/*24 */      * Some guest kernels can't work with MMIO windows above 1<<46                        // (11) 0.03906
/*26 */      * (64TiB), so we place up to 31 PHBs in the area 32TiB..64TiB                        // (6) 0.05469
/*28 */      *                                                                                    // (19) 0.009766
/*30 */      * 32TiB..(33TiB+1984kiB) contains the 64kiB PIO windows for each                     // (8) 0.05469
/*32 */      * PHB stacked together.  (32TiB+2GiB)..(32TiB+64GiB) contains the                    // (3) 0.0625
/*34 */      * 2GiB 32-bit MMIO windows for each PHB.  Then 33..64TiB has the                     // (5) 0.05664
/*36 */      * 1TiB 64-bit MMIO windows for each PHB.                                             // (12) 0.03906
/*38 */      */                                                                                   // (16) 0.009766
/*40 */     const uint64_t base_buid = 0x800000020000000ULL;                                      // (10) 0.04102
/*42 */     const int max_phbs =                                                                  // (14) 0.01953
/*44 */         (SPAPR_PCI_LIMIT - SPAPR_PCI_BASE) / SPAPR_PCI_MEM64_WIN_SIZE - 1;                // 0.0
/*46 */     int i;                                                                                // 0.0
/*50 */     /* Sanity check natural alignments */                                                 // 0.0
/*52 */     QEMU_BUILD_BUG_ON((SPAPR_PCI_BASE % SPAPR_PCI_MEM64_WIN_SIZE) != 0);                  // 0.0
/*54 */     QEMU_BUILD_BUG_ON((SPAPR_PCI_LIMIT % SPAPR_PCI_MEM64_WIN_SIZE) != 0);                 // 0.0
/*56 */     QEMU_BUILD_BUG_ON((SPAPR_PCI_MEM64_WIN_SIZE % SPAPR_PCI_MEM32_WIN_SIZE) != 0);        // 0.0
/*58 */     QEMU_BUILD_BUG_ON((SPAPR_PCI_MEM32_WIN_SIZE % SPAPR_PCI_IO_WIN_SIZE) != 0);           // 0.0
/*60 */     /* Sanity check bounds */                                                             // 0.0
/*62 */     QEMU_BUILD_BUG_ON((max_phbs * SPAPR_PCI_IO_WIN_SIZE) > SPAPR_PCI_MEM32_WIN_SIZE);     // 0.0
/*64 */     QEMU_BUILD_BUG_ON((max_phbs * SPAPR_PCI_MEM32_WIN_SIZE) > SPAPR_PCI_MEM64_WIN_SIZE);  // 0.0
/*68 */     if (index >= max_phbs) {                                                              // 0.0
/*70 */         error_setg(errp, "\"index\" for PAPR PHB is too large (max %u)",                  // 0.0
/*72 */                    max_phbs - 1);                                                         // 0.0
/*74 */         return;                                                                           // 0.0
/*76 */     }                                                                                     // 0.0
/*80 */     *buid = base_buid + index;                                                            // 0.0
/*82 */     for (i = 0; i < n_dma; ++i) {                                                         // 0.0
/*84 */         liobns[i] = SPAPR_PCI_LIOBN(index, i);                                            // 0.0
/*86 */     }                                                                                     // 0.0
/*90 */     *pio = SPAPR_PCI_BASE + index * SPAPR_PCI_IO_WIN_SIZE;                                // 0.0
/*92 */     *mmio32 = SPAPR_PCI_BASE + (index + 1) * SPAPR_PCI_MEM32_WIN_SIZE;                    // 0.0
/*94 */     *mmio64 = SPAPR_PCI_BASE + (index + 1) * SPAPR_PCI_MEM64_WIN_SIZE;                    // 0.0
/*96 */ }                                                                                         // 0.0
