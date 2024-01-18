// commit message qemu@c1bf3531ae (target=1, prob=0.16407876, correct=False): vhost-user: fix use after free
/*0  */ static int net_vhost_user_init(NetClientState *peer, const char *device,        // (7) 0.06044
/*2  */                                const char *name, CharDriverState *chr,          // (0) 0.1154
/*4  */                                int queues)                                      // (4) 0.09066
/*6  */ {                                                                               // (16) 0.002747
/*8  */     NetClientState *nc;                                                         // (12) 0.02473
/*10 */     VhostUserState *s;                                                          // (11) 0.02747
/*12 */     int i;                                                                      // (14) 0.01648
/*16 */     for (i = 0; i < queues; i++) {                                              // (8) 0.04396
/*18 */         nc = qemu_new_net_client(&net_vhost_user_info, peer, device, name);     // (2) 0.09615
/*22 */         snprintf(nc->info_str, sizeof(nc->info_str), "vhost-user%d to %s",      // (3) 0.09615
/*24 */                  i, chr->label);                                                // (6) 0.06319
/*28 */         nc->queue_index = i;                                                    // (9) 0.04396
/*32 */         s = DO_UPCAST(VhostUserState, nc, nc);                                  // (5) 0.07143
/*34 */         s->chr = chr;                                                           // (10) 0.04121
/*36 */     }                                                                           // (15) 0.01099
/*40 */     qemu_chr_add_handlers(chr, NULL, NULL, net_vhost_user_event, (void*)name);  // (1) 0.0989
/*44 */     return 0;                                                                   // (13) 0.01648
/*46 */ }                                                                               // (17) 0.002747
