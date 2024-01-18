// commit message qemu@2a0c46da96 (target=0, prob=0.5087171, correct=False): vscclient: use glib thread primitives not qemu
/*0  */ send_msg(                                                                        // (17) 0.01242
/*2  */     VSCMsgType type,                                                             // (13) 0.02795
/*4  */     uint32_t reader_id,                                                          // (12) 0.03416
/*6  */     const void *msg,                                                             // (14) 0.02484
/*8  */     unsigned int length                                                          // (15) 0.01863
/*10 */ ) {                                                                              // (19) 0.006213
/*12 */     VSCMsgHeader mhHeader;                                                       // (11) 0.03416
/*16 */     qemu_mutex_lock(&socket_to_send_lock);                                       // (5) 0.06211
/*20 */     if (verbose > 10) {                                                          // (10) 0.03416
/*22 */         printf("sending type=%d id=%u, len =%u (0x%x)\n",                        // (1) 0.09938
/*24 */                type, reader_id, length, length);                                 // (3) 0.07453
/*26 */     }                                                                            // (18) 0.01242
/*30 */     mhHeader.type = htonl(type);                                                 // (7) 0.04658
/*32 */     mhHeader.reader_id = 0;                                                      // (9) 0.04037
/*34 */     mhHeader.length = htonl(length);                                             // (8) 0.04658
/*36 */     g_byte_array_append(socket_to_send, (guint8 *)&mhHeader, sizeof(mhHeader));  // (0) 0.1025
/*38 */     g_byte_array_append(socket_to_send, (guint8 *)msg, length);                  // (2) 0.08074
/*40 */     g_idle_add(socket_prepare_sending, NULL);                                    // (6) 0.06211
/*44 */     qemu_mutex_unlock(&socket_to_send_lock);                                     // (4) 0.06522
/*48 */     return 0;                                                                    // (16) 0.01863
/*50 */ }                                                                                // (20) 0.003106
