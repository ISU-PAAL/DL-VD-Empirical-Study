// commit message qemu@9359a58b12 (target=0, prob=0.33272606, correct=True): ehci: Use uframe precision for interrupt threshold checking (v2)
/*0  */ static void ehci_update_frindex(EHCIState *ehci, int frames)  // (5) 0.05753
/*2  */ {                                                             // (20) 0.00274
/*4  */     int i;                                                    // (17) 0.01644
/*8  */     if (!ehci_enabled(ehci)) {                                // (11) 0.03836
/*10 */         return;                                               // (14) 0.02466
/*12 */     }                                                         // (18) 0.01096
/*16 */     for (i = 0; i < frames; i++) {                            // (9) 0.04384
/*18 */         ehci->frindex += 8;                                   // (10) 0.0411
/*22 */         if (ehci->frindex == 0x00002000) {                    // (6) 0.05753
/*24 */             ehci_raise_irq(ehci, USBSTS_FLR);                 // (0) 0.07945
/*26 */         }                                                     // (15) 0.02192
/*30 */         if (ehci->frindex == 0x00004000) {                    // (7) 0.05753
/*32 */             ehci_raise_irq(ehci, USBSTS_FLR);                 // (2) 0.07945
/*34 */             ehci->frindex = 0;                                // (8) 0.05205
/*36 */             if (ehci->usbsts_frindex >= 0x00004000) {         // (3) 0.07671
/*38 */                 ehci->usbsts_frindex -= 0x00004000;           // (1) 0.07945
/*40 */             } else {                                          // (12) 0.03836
/*42 */                 ehci->usbsts_frindex = 0;                     // (4) 0.07123
/*44 */             }                                                 // (13) 0.03288
/*46 */         }                                                     // (16) 0.02192
/*48 */     }                                                         // (19) 0.01096
/*50 */ }                                                             // (21) 0.00274
