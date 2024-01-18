// commit message qemu@7d91ddd25e (target=1, prob=0.9990565, correct=True): net: fix unbounded NetQueue
/*0  */ void qemu_net_queue_purge(NetQueue *queue, NetClientState *from)  // (2) 0.1456
/*2  */ {                                                                 // (8) 0.006329
/*4  */     NetPacket *packet, *next;                                     // (5) 0.08228
/*8  */     QTAILQ_FOREACH_SAFE(packet, &queue->packets, entry, next) {   // (1) 0.1772
/*10 */         if (packet->sender == from) {                             // (4) 0.1139
/*12 */             QTAILQ_REMOVE(&queue->packets, packet, entry);        // (0) 0.1835
/*15 */             g_free(packet);                                       // (3) 0.1139
/*17 */         }                                                         // (6) 0.05063
/*19 */     }                                                             // (7) 0.02532
/*21 */ }                                                                 // (9) 0.006329
