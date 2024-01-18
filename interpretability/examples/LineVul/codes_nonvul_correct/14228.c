// commit message qemu@72cf2d4f0e (target=0, prob=0.008648485, correct=True): Fix sys-queue.h conflict for good
/*0  */ void qemu_flush_queued_packets(VLANClientState *vc)                             // (7) 0.06309
/*2  */ {                                                                               // (16) 0.003155
/*4  */     while (!TAILQ_EMPTY(&vc->vlan->send_queue)) {                               // (5) 0.0694
/*6  */         VLANPacket *packet;                                                     // (10) 0.04732
/*8  */         int ret;                                                                // (12) 0.03155
/*12 */         packet = TAILQ_FIRST(&vc->vlan->send_queue);                            // (3) 0.07886
/*14 */         TAILQ_REMOVE(&vc->vlan->send_queue, packet, entry);                     // (2) 0.08833
/*18 */         ret = qemu_deliver_packet(packet->sender, packet->data, packet->size);  // (0) 0.1041
/*20 */         if (ret == 0 && packet->sent_cb != NULL) {                              // (6) 0.0694
/*22 */             TAILQ_INSERT_HEAD(&vc->vlan->send_queue, packet, entry);            // (1) 0.1041
/*24 */             break;                                                              // (11) 0.04101
/*26 */         }                                                                       // (13) 0.02524
/*30 */         if (packet->sent_cb)                                                    // (8) 0.05047
/*32 */             packet->sent_cb(packet->sender, ret);                               // (4) 0.07886
/*36 */         qemu_free(packet);                                                      // (9) 0.05047
/*38 */     }                                                                           // (14) 0.01262
/*40 */ }                                                                               // (15) 0.003155
