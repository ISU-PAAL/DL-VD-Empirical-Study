// commit message qemu@f69a8bde29 (target=1, prob=0.6129462, correct=True): io: send proper HTTP response for websocket errors
/*0  */ static int qio_channel_websock_handshake_send_response(QIOChannelWebsock *ioc,   // (8) 0.05469
/*2  */                                                        const char *key,          // (1) 0.1152
/*4  */                                                        Error **errp)             // (0) 0.1152
/*6  */ {                                                                                // (15) 0.001953
/*8  */     char combined_key[QIO_CHANNEL_WEBSOCK_CLIENT_KEY_LEN +                       // (11) 0.05273
/*10 */                       QIO_CHANNEL_WEBSOCK_GUID_LEN + 1];                         // (3) 0.07812
/*12 */     char *accept = NULL, *response = NULL;                                       // (12) 0.02734
/*14 */     size_t responselen;                                                          // (13) 0.02148
/*18 */     g_strlcpy(combined_key, key, QIO_CHANNEL_WEBSOCK_CLIENT_KEY_LEN + 1);        // (4) 0.07227
/*20 */     g_strlcat(combined_key, QIO_CHANNEL_WEBSOCK_GUID,                            // (10) 0.05469
/*22 */               QIO_CHANNEL_WEBSOCK_CLIENT_KEY_LEN +                               // (6) 0.0625
/*24 */               QIO_CHANNEL_WEBSOCK_GUID_LEN + 1);                                 // (5) 0.0625
/*28 */     /* hash and encode it */                                                     // (14) 0.01758
/*30 */     if (qcrypto_hash_base64(QCRYPTO_HASH_ALG_SHA1,                               // (9) 0.05469
/*32 */                             combined_key,                                        // (7) 0.06055
/*34 */                             QIO_CHANNEL_WEBSOCK_CLIENT_KEY_LEN +                 // (2) 0.08984
/*36 */                             QIO_CHANNEL_WEBSOCK_GUID_LEN,                        // 0.0
/*38 */                             &accept,                                             // 0.0
/*40 */                             errp) < 0) {                                         // 0.0
/*42 */         return -1;                                                               // 0.0
/*44 */     }                                                                            // 0.0
/*48 */     response = g_strdup_printf(QIO_CHANNEL_WEBSOCK_HANDSHAKE_RESPONSE, accept);  // 0.0
/*50 */     responselen = strlen(response);                                              // 0.0
/*52 */     buffer_reserve(&ioc->encoutput, responselen);                                // 0.0
/*54 */     buffer_append(&ioc->encoutput, response, responselen);                       // 0.0
/*58 */     g_free(accept);                                                              // 0.0
/*60 */     g_free(response);                                                            // 0.0
/*64 */     return 0;                                                                    // 0.0
/*66 */ }                                                                                // 0.0
