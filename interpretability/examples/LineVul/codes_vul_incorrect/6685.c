// commit message qemu@fa1298c2d6 (target=1, prob=0.18220124, correct=False): ohci: allocate timer only once.
/*0  */ static int ohci_bus_start(OHCIState *ohci)                // (5) 0.05797
/*2  */ {                                                         // (16) 0.003623
/*4  */     ohci->eof_timer = timer_new_ns(QEMU_CLOCK_VIRTUAL,    // (1) 0.1014
/*6  */                     ohci_frame_boundary,                  // (2) 0.09783
/*8  */                     ohci);                                // (3) 0.07971
/*12 */     if (ohci->eof_timer == NULL) {                        // (6) 0.05797
/*14 */         trace_usb_ohci_bus_eof_timer_failed(ohci->name);  // (0) 0.1014
/*16 */         ohci_die(ohci);                                   // (8) 0.05435
/*18 */         return 0;                                         // (11) 0.03623
/*20 */     }                                                     // (15) 0.01449
/*24 */     trace_usb_ohci_start(ohci->name);                     // (4) 0.06159
/*28 */     /* Delay the first SOF event by one frame time as     // (7) 0.05435
/*30 */      * linux driver is not ready to receive it and        // (9) 0.05072
/*32 */      * can meet some race conditions                      // (12) 0.03623
/*34 */      */                                                   // (14) 0.01812
/*38 */     ohci_eof_timer(ohci);                                 // (10) 0.05072
/*42 */     return 1;                                             // (13) 0.02174
/*44 */ }                                                         // (17) 0.003623
