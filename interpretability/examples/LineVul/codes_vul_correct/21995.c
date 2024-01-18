// commit message qemu@7d91ddd25e (target=1, prob=0.9992526, correct=True): net: fix unbounded NetQueue
/*0  */ static void qemu_net_queue_append(NetQueue *queue,          // (9) 0.04261
/*2  */                                   NetClientState *sender,   // (2) 0.1003
/*4  */                                   unsigned flags,           // (4) 0.09023
/*6  */                                   const uint8_t *buf,       // (1) 0.1028
/*8  */                                   size_t size,              // (3) 0.09524
/*10 */                                   NetPacketSent *sent_cb)   // (0) 0.1053
/*12 */ {                                                           // (17) 0.002506
/*14 */     NetPacket *packet;                                      // (12) 0.02506
/*18 */     if (queue->nq_count >= queue->nq_maxlen && !sent_cb) {  // (5) 0.06516
/*20 */         return; /* drop if queue full and no callback */    // (8) 0.04511
/*22 */     }                                                       // (16) 0.01003
/*24 */     packet = g_malloc(sizeof(NetPacket) + size);            // (7) 0.05013
/*26 */     packet->sender = sender;                                // (13) 0.02506
/*28 */     packet->flags = flags;                                  // (14) 0.02256
/*30 */     packet->size = size;                                    // (15) 0.02256
/*32 */     packet->sent_cb = sent_cb;                              // (11) 0.03258
/*34 */     memcpy(packet->data, buf, size);                        // (10) 0.0401
/*39 */     QTAILQ_INSERT_TAIL(&queue->packets, packet, entry);     // (6) 0.05764
/*41 */ }                                                           // (18) 0.002506
