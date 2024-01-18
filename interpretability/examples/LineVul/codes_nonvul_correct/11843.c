// commit message qemu@a369da5f31 (target=0, prob=0.189115, correct=True): vga: improve VGA logic
/*0  */ void alpha_pci_vga_setup(PCIBus *pci_bus)                                // (4) 0.06369
/*2  */ {                                                                        // (21) 0.003185
/*4  */     switch (vga_interface_type) {                                        // (8) 0.0414
/*6  */ #ifdef CONFIG_SPICE                                                      // (17) 0.02229
/*8  */     case VGA_QXL:                                                        // (12) 0.03185
/*10 */         pci_create_simple(pci_bus, -1, "qxl-vga");                       // (0) 0.09236
/*12 */         return;                                                          // (13) 0.02866
/*14 */ #endif                                                                   // (20) 0.006369
/*16 */     case VGA_CIRRUS:                                                     // (10) 0.03822
/*18 */         pci_cirrus_vga_init(pci_bus);                                    // (2) 0.07325
/*20 */         return;                                                          // (14) 0.02866
/*22 */     case VGA_VMWARE:                                                     // (11) 0.03503
/*24 */         if (pci_vmsvga_init(pci_bus)) {                                  // (1) 0.07962
/*26 */             return;                                                      // (9) 0.0414
/*28 */         }                                                                // (16) 0.02548
/*30 */         break;                                                           // (15) 0.02866
/*32 */     }                                                                    // (18) 0.01274
/*34 */     /* If VGA is enabled at all, and one of the above didn't work, then  // (3) 0.07006
/*36 */        fallback to Standard VGA.  */                                     // (7) 0.04777
/*38 */     if (vga_interface_type != VGA_NONE) {                                // (5) 0.06051
/*40 */         pci_vga_init(pci_bus);                                           // (6) 0.06051
/*42 */     }                                                                    // (19) 0.01274
/*44 */ }                                                                        // (22) 0.003185
