// commit message qemu@68d553587c (target=0, prob=0.41653287, correct=True): usb-ehci: Use PCI DMA stub functions
/*0   */ static EHCIQueue *ehci_state_fetchqh(EHCIState *ehci, int async)                    // (3) 0.05273
/*2   */ {                                                                                   // (28) 0.001954
/*4   */     uint32_t entry;                                                                 // (22) 0.01758
/*6   */     EHCIQueue *q;                                                                   // (18) 0.01953
/*8   */     int reload;                                                                     // (24) 0.01173
/*12  */     entry = ehci_get_fetch_addr(ehci, async);                                       // (11) 0.03906
/*14  */     q = ehci_find_queue_by_qh(ehci, entry);                                         // (8) 0.04297
/*16  */     if (NULL == q) {                                                                // (20) 0.01953
/*18  */         q = ehci_alloc_queue(ehci, async);                                          // (10) 0.04102
/*20  */     }                                                                               // (26) 0.007812
/*22  */     q->qhaddr = entry;                                                              // (16) 0.02148
/*24  */     q->seen++;                                                                      // (23) 0.01367
/*28  */     if (q->seen > 1) {                                                              // (15) 0.02344
/*30  */         /* we are going in circles -- stop processing */                            // (13) 0.0332
/*32  */         ehci_set_state(ehci, async, EST_ACTIVE);                                    // (6) 0.04687
/*34  */         q = NULL;                                                                   // (17) 0.02148
/*36  */         goto out;                                                                   // (19) 0.01953
/*38  */     }                                                                               // (27) 0.007812
/*42  */     get_dwords(NLPTR_GET(q->qhaddr), (uint32_t *) &q->qh, sizeof(EHCIqh) >> 2);     // (0) 0.08398
/*44  */     ehci_trace_qh(q, NLPTR_GET(q->qhaddr), &q->qh);                                 // (1) 0.06055
/*48  */     if (q->async == EHCI_ASYNC_INFLIGHT) {                                          // (7) 0.04297
/*50  */         /* I/O still in progress -- skip queue */                                   // (12) 0.03516
/*52  */         ehci_set_state(ehci, async, EST_HORIZONTALQH);                              // (2) 0.05664
/*54  */         goto out;                                                                   // (21) 0.01953
/*56  */     }                                                                               // (25) 0.007812
/*58  */     if (q->async == EHCI_ASYNC_FINISHED) {                                          // (9) 0.04297
/*60  */         /* I/O finished -- continue processing queue */                             // (14) 0.0332
/*62  */         trace_usb_ehci_queue_action(q, "resume");                                   // (5) 0.04687
/*64  */         ehci_set_state(ehci, async, EST_EXECUTING);                                 // (4) 0.05078
/*66  */         goto out;                                                                   // 0.0
/*68  */     }                                                                               // 0.0
/*72  */     if (async && (q->qh.epchar & QH_EPCHAR_H)) {                                    // 0.0
/*76  */         /*  EHCI spec version 1.0 Section 4.8.3 & 4.10.1 */                         // 0.0
/*78  */         if (ehci->usbsts & USBSTS_REC) {                                            // 0.0
/*80  */             ehci_clear_usbsts(ehci, USBSTS_REC);                                    // 0.0
/*82  */         } else {                                                                    // 0.0
/*84  */             DPRINTF("FETCHQH:  QH 0x%08x. H-bit set, reclamation status reset"      // 0.0
/*86  */                        " - done processing\n", q->qhaddr);                          // 0.0
/*88  */             ehci_set_state(ehci, async, EST_ACTIVE);                                // 0.0
/*90  */             q = NULL;                                                               // 0.0
/*92  */             goto out;                                                               // 0.0
/*94  */         }                                                                           // 0.0
/*96  */     }                                                                               // 0.0
/*100 */ #if EHCI_DEBUG                                                                      // 0.0
/*102 */     if (q->qhaddr != q->qh.next) {                                                  // 0.0
/*104 */     DPRINTF("FETCHQH:  QH 0x%08x (h %x halt %x active %x) next 0x%08x\n",           // 0.0
/*106 */                q->qhaddr,                                                           // 0.0
/*108 */                q->qh.epchar & QH_EPCHAR_H,                                          // 0.0
/*110 */                q->qh.token & QTD_TOKEN_HALT,                                        // 0.0
/*112 */                q->qh.token & QTD_TOKEN_ACTIVE,                                      // 0.0
/*114 */                q->qh.next);                                                         // 0.0
/*116 */     }                                                                               // 0.0
/*118 */ #endif                                                                              // 0.0
/*122 */     reload = get_field(q->qh.epchar, QH_EPCHAR_RL);                                 // 0.0
/*124 */     if (reload) {                                                                   // 0.0
/*126 */         set_field(&q->qh.altnext_qtd, reload, QH_ALTNEXT_NAKCNT);                   // 0.0
/*128 */     }                                                                               // 0.0
/*132 */     if (q->qh.token & QTD_TOKEN_HALT) {                                             // 0.0
/*134 */         ehci_set_state(ehci, async, EST_HORIZONTALQH);                              // 0.0
/*138 */     } else if ((q->qh.token & QTD_TOKEN_ACTIVE) && (q->qh.current_qtd > 0x1000)) {  // 0.0
/*140 */         q->qtdaddr = q->qh.current_qtd;                                             // 0.0
/*142 */         ehci_set_state(ehci, async, EST_FETCHQTD);                                  // 0.0
/*146 */     } else {                                                                        // 0.0
/*148 */         /*  EHCI spec version 1.0 Section 4.10.2 */                                 // 0.0
/*150 */         ehci_set_state(ehci, async, EST_ADVANCEQUEUE);                              // 0.0
/*152 */     }                                                                               // 0.0
/*156 */ out:                                                                                // 0.0
/*158 */     return q;                                                                       // 0.0
/*160 */ }                                                                                   // 0.0
