// commit message qemu@eefa3d8ef6 (target=1, prob=0.5155764, correct=True): io: Small updates in preparation for websocket changes
/*0  */ qio_channel_websock_source_dispatch(GSource *source,                         // (7) 0.05605
/*2  */                                     GSourceFunc callback,                    // (0) 0.1209
/*4  */                                     gpointer user_data)                      // (1) 0.1209
/*6  */ {                                                                            // (15) 0.00295
/*8  */     QIOChannelFunc func = (QIOChannelFunc)callback;                          // (8) 0.05605
/*10 */     QIOChannelWebsockSource *wsource = (QIOChannelWebsockSource *)source;    // (4) 0.07375
/*12 */     GIOCondition cond = 0;                                                   // (12) 0.03245
/*16 */     if (wsource->wioc->rawinput.offset) {                                    // (9) 0.05015
/*18 */         cond |= G_IO_IN;                                                     // (10) 0.0472
/*20 */     }                                                                        // (13) 0.0118
/*22 */     if (wsource->wioc->rawoutput.offset < QIO_CHANNEL_WEBSOCK_MAX_BUFFER) {  // (2) 0.09735
/*24 */         cond |= G_IO_OUT;                                                    // (11) 0.0472
/*26 */     }                                                                        // (14) 0.0118
/*30 */     return (*func)(QIO_CHANNEL(wsource->wioc),                               // (6) 0.059
/*32 */                    (cond & wsource->condition),                              // (3) 0.0767
/*34 */                    user_data);                                               // (5) 0.0649
/*36 */ }                                                                            // (16) 0.00295
