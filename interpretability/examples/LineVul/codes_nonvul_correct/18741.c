// commit message qemu@891fb2cd45 (target=0, prob=0.4082484, correct=True): usb: claim port at device initialization time.
/*0  */ static void ohci_reset(void *opaque)                     // (16) 0.02344
/*2  */ {                                                        // (34) 0.001953
/*4  */     OHCIState *ohci = opaque;                            // (12) 0.02539
/*6  */     OHCIPort *port;                                      // (26) 0.01953
/*8  */     int i;                                               // (31) 0.01172
/*12 */     ohci_bus_stop(ohci);                                 // (13) 0.02539
/*14 */     ohci->ctl = 0;                                       // (27) 0.01953
/*16 */     ohci->old_ctl = 0;                                   // (19) 0.02344
/*18 */     ohci->status = 0;                                    // (28) 0.01953
/*20 */     ohci->intr_status = 0;                               // (15) 0.02539
/*22 */     ohci->intr = OHCI_INTR_MIE;                          // (5) 0.03711
/*26 */     ohci->hcca = 0;                                      // (22) 0.02148
/*28 */     ohci->ctrl_head = ohci->ctrl_cur = 0;                // (6) 0.03711
/*30 */     ohci->bulk_head = ohci->bulk_cur = 0;                // (2) 0.04102
/*32 */     ohci->per_cur = 0;                                   // (20) 0.02344
/*34 */     ohci->done = 0;                                      // (29) 0.01953
/*36 */     ohci->done_count = 7;                                // (17) 0.02344
/*40 */     /* FSMPS is marked TBD in OCHI 1.0, what gives ffs?  // (1) 0.04492
/*42 */      * I took the value linux sets ...                   // (21) 0.02344
/*44 */      */                                                  // (33) 0.009766
/*46 */     ohci->fsmps = 0x2778;                                // (10) 0.0293
/*48 */     ohci->fi = 0x2edf;                                   // (11) 0.02734
/*50 */     ohci->fit = 0;                                       // (30) 0.01953
/*52 */     ohci->frt = 0;                                       // (23) 0.02148
/*54 */     ohci->frame_number = 0;                              // (18) 0.02344
/*56 */     ohci->pstart = 0;                                    // (24) 0.02148
/*58 */     ohci->lst = OHCI_LS_THRESH;                          // (7) 0.03711
/*62 */     ohci->rhdesc_a = OHCI_RHA_NPS | ohci->num_ports;     // (0) 0.05469
/*64 */     ohci->rhdesc_b = 0x0; /* Impl. specific */           // (4) 0.03906
/*66 */     ohci->rhstatus = 0;                                  // (25) 0.02148
/*70 */     for (i = 0; i < ohci->num_ports; i++)                // (3) 0.03906
/*72 */       {                                                  // (32) 0.01172
/*74 */         port = &ohci->rhport[i];                         // (8) 0.03516
/*76 */         port->ctrl = 0;                                  // (14) 0.02539
/*78 */         if (port->port.dev) {                            // (9) 0.03125
/*80 */             usb_attach(&port->port, port->port.dev);     // 0.0
/*82 */         }                                                // 0.0
/*84 */       }                                                  // 0.0
/*86 */     if (ohci->async_td) {                                // 0.0
/*88 */         usb_cancel_packet(&ohci->usb_packet);            // 0.0
/*90 */         ohci->async_td = 0;                              // 0.0
/*92 */     }                                                    // 0.0
/*94 */     DPRINTF("usb-ohci: Reset %s\n", ohci->name);         // 0.0
/*96 */ }                                                        // 0.0
