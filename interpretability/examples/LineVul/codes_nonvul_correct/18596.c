// commit message qemu@72cf2d4f0e (target=0, prob=0.008741817, correct=True): Fix sys-queue.h conflict for good
/*0  */ static void qemu_enqueue_packet(VLANClientState *sender,          // (4) 0.08658
/*2  */                                 const uint8_t *buf, int size,     // (0) 0.1818
/*4  */                                 NetPacketSent *sent_cb)           // (1) 0.1732
/*6  */ {                                                                 // (10) 0.004329
/*8  */     VLANPacket *packet;                                           // (7) 0.04762
/*12 */     packet = qemu_malloc(sizeof(VLANPacket) + size);              // (3) 0.09957
/*14 */     packet->sender = sender;                                      // (8) 0.04329
/*16 */     packet->size = size;                                          // (9) 0.03896
/*18 */     packet->sent_cb = sent_cb;                                    // (6) 0.05628
/*20 */     memcpy(packet->data, buf, size);                              // (5) 0.06926
/*24 */     TAILQ_INSERT_TAIL(&sender->vlan->send_queue, packet, entry);  // (2) 0.1169
/*26 */ }                                                                 // (11) 0.004329
