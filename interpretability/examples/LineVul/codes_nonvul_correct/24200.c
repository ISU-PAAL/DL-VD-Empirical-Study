// commit message qemu@95ed56939e (target=0, prob=0.46853942, correct=True): usb: ohci: limit the number of link eds
/*0   */ static int ohci_service_ed_list(OHCIState *ohci, uint32_t head, int completion)  // (4) 0.05273
/*2   */ {                                                                                // (23) 0.001953
/*4   */     struct ohci_ed ed;                                                           // (16) 0.01953
/*6   */     uint32_t next_ed;                                                            // (15) 0.02148
/*8   */     uint32_t cur;                                                                // (18) 0.01758
/*10  */     int active;                                                                  // (22) 0.01172
/*14  */     active = 0;                                                                  // (21) 0.01367
/*18  */     if (head == 0)                                                               // (19) 0.01758
/*20  */         return 0;                                                                // (17) 0.01953
/*24  */     for (cur = head; cur; cur = next_ed) {                                       // (12) 0.03516
/*26  */         if (ohci_read_ed(ohci, cur, &ed)) {                                      // (7) 0.04883
/*28  */             trace_usb_ohci_ed_read_error(cur);                                   // (6) 0.05078
/*30  */             ohci_die(ohci);                                                      // (11) 0.03711
/*32  */             return 0;                                                            // (14) 0.02734
/*34  */         }                                                                        // (20) 0.01562
/*38  */         next_ed = ed.next & OHCI_DPTR_MASK;                                      // (8) 0.04883
/*42  */         if ((ed.head & OHCI_ED_H) || (ed.flags & OHCI_ED_K)) {                   // (0) 0.07031
/*44  */             uint32_t addr;                                                       // (13) 0.0332
/*46  */             /* Cancel pending packets for ED that have been paused.  */          // (10) 0.04688
/*48  */             addr = ed.head & OHCI_DPTR_MASK;                                     // (5) 0.05273
/*50  */             if (ohci->async_td && addr == ohci->async_td) {                      // (2) 0.0625
/*52  */                 usb_cancel_packet(&ohci->usb_packet);                            // (3) 0.06055
/*54  */                 ohci->async_td = 0;                                              // (9) 0.04883
/*56  */                 usb_device_ep_stopped(ohci->usb_packet.ep->dev,                  // (1) 0.07031
/*58  */                                       ohci->usb_packet.ep);                      // 0.0
/*60  */             }                                                                    // 0.0
/*62  */             continue;                                                            // 0.0
/*64  */         }                                                                        // 0.0
/*68  */         while ((ed.head & OHCI_DPTR_MASK) != ed.tail) {                          // 0.0
/*70  */             trace_usb_ohci_ed_pkt(cur, (ed.head & OHCI_ED_H) != 0,               // 0.0
/*72  */                     (ed.head & OHCI_ED_C) != 0, ed.head & OHCI_DPTR_MASK,        // 0.0
/*74  */                     ed.tail & OHCI_DPTR_MASK, ed.next & OHCI_DPTR_MASK);         // 0.0
/*76  */             trace_usb_ohci_ed_pkt_flags(                                         // 0.0
/*78  */                     OHCI_BM(ed.flags, ED_FA), OHCI_BM(ed.flags, ED_EN),          // 0.0
/*80  */                     OHCI_BM(ed.flags, ED_D), (ed.flags & OHCI_ED_S)!= 0,         // 0.0
/*82  */                     (ed.flags & OHCI_ED_K) != 0, (ed.flags & OHCI_ED_F) != 0,    // 0.0
/*84  */                     OHCI_BM(ed.flags, ED_MPS));                                  // 0.0
/*88  */             active = 1;                                                          // 0.0
/*92  */             if ((ed.flags & OHCI_ED_F) == 0) {                                   // 0.0
/*94  */                 if (ohci_service_td(ohci, &ed))                                  // 0.0
/*96  */                     break;                                                       // 0.0
/*98  */             } else {                                                             // 0.0
/*100 */                 /* Handle isochronous endpoints */                               // 0.0
/*102 */                 if (ohci_service_iso_td(ohci, &ed, completion))                  // 0.0
/*104 */                     break;                                                       // 0.0
/*106 */             }                                                                    // 0.0
/*108 */         }                                                                        // 0.0
/*112 */         if (ohci_put_ed(ohci, cur, &ed)) {                                       // 0.0
/*114 */             ohci_die(ohci);                                                      // 0.0
/*116 */             return 0;                                                            // 0.0
/*118 */         }                                                                        // 0.0
/*120 */     }                                                                            // 0.0
/*124 */     return active;                                                               // 0.0
/*126 */ }                                                                                // 0.0
