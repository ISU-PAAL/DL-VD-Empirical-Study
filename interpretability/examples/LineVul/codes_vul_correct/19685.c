// commit message qemu@2b3de6ada5 (target=1, prob=0.99905425, correct=True): ehci: writeback_async_complete_packet: verify qh and qtd
/*0 */ static void ehci_writeback_async_complete_packet(EHCIPacket *p)  // (0) 0.1337
/*1 */ {                                                                // (9) 0.005814
/*2 */     EHCIQueue *q = p->queue;                                     // (6) 0.0814
/*3 */     int state;                                                   // (8) 0.03488
/*4 */     state = ehci_get_state(q->ehci, q->async);                   // (2) 0.1279
/*5 */     ehci_state_executing(q);                                     // (7) 0.07558
/*6 */     ehci_state_writeback(q); /* Frees the packet! */             // (4) 0.1163
/*7 */     if (!(q->qh.token & QTD_TOKEN_HALT)) {                       // (1) 0.1337
/*8 */         ehci_state_advqueue(q);                                  // (5) 0.09884
/*9 */     ehci_set_state(q->ehci, q->async, state);                    // (3) 0.1279
