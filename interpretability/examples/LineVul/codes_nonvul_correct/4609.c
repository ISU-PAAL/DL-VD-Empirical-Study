// commit message qemu@8ec1440202 (target=0, prob=0.38224512, correct=True): colo-compare: compare the packet in a specified Connection
/*0  */ static int packet_enqueue(CompareState *s, int mode)                   // (12) 0.0293
/*2  */ {                                                                      // (27) 0.001953
/*4  */     ConnectionKey key;                                                 // (22) 0.01367
/*6  */     Packet *pkt = NULL;                                                // (18) 0.02148
/*8  */     Connection *conn;                                                  // (21) 0.01367
/*12 */     if (mode == PRIMARY_IN) {                                          // (14) 0.02734
/*14 */         pkt = packet_new(s->pri_rs.buf,                                // (7) 0.04297
/*16 */                          s->pri_rs.packet_len,                         // (2) 0.06836
/*18 */                          s->pri_rs.vnet_hdr_len);                      // (0) 0.07422
/*20 */     } else {                                                           // (23) 0.01172
/*22 */         pkt = packet_new(s->sec_rs.buf,                                // (8) 0.04297
/*24 */                          s->sec_rs.packet_len,                         // (3) 0.06836
/*26 */                          s->sec_rs.vnet_hdr_len);                      // (1) 0.07422
/*28 */     }                                                                  // (24) 0.007812
/*32 */     if (parse_packet_early(pkt)) {                                     // (11) 0.03125
/*34 */         packet_destroy(pkt, NULL);                                     // (10) 0.03125
/*36 */         pkt = NULL;                                                    // (17) 0.02344
/*38 */         return -1;                                                     // (19) 0.02148
/*40 */     }                                                                  // (25) 0.007812
/*42 */     fill_connection_key(pkt, &key);                                    // (13) 0.0293
/*46 */     conn = connection_get(s->connection_track_table,                   // (9) 0.0332
/*48 */                           &key,                                        // (5) 0.05469
/*50 */                           &s->conn_list);                              // (4) 0.0625
/*54 */     if (!conn->processing) {                                           // (20) 0.01953
/*56 */         g_queue_push_tail(&s->conn_list, conn);                        // (6) 0.04492
/*58 */         conn->processing = true;                                       // (16) 0.02539
/*60 */     }                                                                  // (26) 0.007812
/*64 */     if (mode == PRIMARY_IN) {                                          // (15) 0.02734
/*66 */         if (!colo_insert_packet(&conn->primary_list, pkt)) {           // 0.0
/*68 */             error_report("colo compare primary queue size too big,"    // 0.0
/*70 */                          "drop packet");                               // 0.0
/*72 */         }                                                              // 0.0
/*74 */     } else {                                                           // 0.0
/*76 */         if (!colo_insert_packet(&conn->secondary_list, pkt)) {         // 0.0
/*78 */             error_report("colo compare secondary queue size too big,"  // 0.0
/*80 */                          "drop packet");                               // 0.0
/*82 */         }                                                              // 0.0
/*84 */     }                                                                  // 0.0
/*88 */     return 0;                                                          // 0.0
/*90 */ }                                                                      // 0.0
