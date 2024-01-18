// commit message qemu@937470bb54 (target=1, prob=0.14380349, correct=False): io: stop incrementing reference in qio_task_get_source
/*0  */ static gboolean qio_channel_tls_handshake_io(QIOChannel *ioc,         // (2) 0.09756
/*2  */                                              GIOCondition condition,  // (1) 0.2033
/*4  */                                              gpointer user_data)      // (0) 0.2033
/*6  */ {                                                                     // (10) 0.004065
/*8  */     QIOTask *task = user_data;                                        // (6) 0.05691
/*10 */     QIOChannelTLS *tioc = QIO_CHANNEL_TLS(                            // (3) 0.08943
/*12 */         qio_task_get_source(task));                                   // (4) 0.07317
/*16 */     qio_channel_tls_handshake_task(                                   // (5) 0.06504
/*18 */        tioc, task);                                                   // (8) 0.04472
/*22 */     object_unref(OBJECT(tioc));                                       // (7) 0.05691
/*26 */     return FALSE;                                                     // (9) 0.02439
/*28 */ }                                                                     // (11) 0.004065
