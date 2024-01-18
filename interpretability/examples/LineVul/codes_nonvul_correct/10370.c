// commit message qemu@ddf2190896 (target=0, prob=0.24777521, correct=True): qapi: Unbox base members
/*0  */ static void vnc_client_cache_addr(VncState *client)                          // (5) 0.07692
/*2  */ {                                                                            // (11) 0.004525
/*4  */     Error *err = NULL;                                                       // (8) 0.04072
/*8  */     client->info = g_malloc0(sizeof(*client->info));                         // (4) 0.0905
/*10 */     client->info->base = g_malloc0(sizeof(*client->info->base));             // (2) 0.1086
/*12 */     vnc_init_basic_info_from_remote_addr(client->csock, client->info->base,  // (1) 0.1312
/*14 */                                          &err);                              // (0) 0.1946
/*16 */     if (err) {                                                               // (9) 0.0362
/*18 */         qapi_free_VncClientInfo(client->info);                               // (3) 0.09502
/*20 */         client->info = NULL;                                                 // (6) 0.05882
/*22 */         error_free(err);                                                     // (7) 0.05882
/*24 */     }                                                                        // (10) 0.0181
/*26 */ }                                                                            // (12) 0.004525
