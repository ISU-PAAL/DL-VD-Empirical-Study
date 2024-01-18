// commit message qemu@4b63a0df3b (target=1, prob=0.99915886, correct=True): ehci: Properly report completed but not yet processed packets to the guest
/*0  */ static void ehci_free_packet(EHCIPacket *p)             // (6) 0.08543
/*2  */ {                                                       // (9) 0.005025
/*4  */     trace_usb_ehci_packet_action(p->queue, p, "free");  // (1) 0.1206
/*6  */     if (p->async == EHCI_ASYNC_INFLIGHT) {              // (4) 0.1106
/*8  */         usb_cancel_packet(&p->packet);                  // (5) 0.1005
/*10 */         usb_packet_unmap(&p->packet, &p->sgl);          // (0) 0.1307
/*12 */         qemu_sglist_destroy(&p->sgl);                   // (3) 0.1106
/*25 */     QTAILQ_REMOVE(&p->queue->packets, p, next);         // (2) 0.1156
/*27 */     usb_packet_cleanup(&p->packet);                     // (7) 0.0804
/*29 */     g_free(p);                                          // (8) 0.04523
