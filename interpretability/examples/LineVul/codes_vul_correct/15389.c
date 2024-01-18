// commit message qemu@fedf0d35aa (target=1, prob=0.52691466, correct=True): ui: Use g_new() & friends where that makes obvious sense
/*0   */ static void vnc_connect(VncDisplay *vd, int csock,                             // (13) 0.0332
/*2   */                         bool skipauth, bool websocket)                         // (2) 0.06055
/*4   */ {                                                                              // (26) 0.001953
/*6   */     VncState *vs = g_malloc0(sizeof(VncState));                                // (8) 0.04297
/*8   */     int i;                                                                     // (22) 0.01172
/*12  */     vs->csock = csock;                                                         // (17) 0.02148
/*14  */     vs->vd = vd;                                                               // (18) 0.01953
/*18  */     if (skipauth) {                                                            // (20) 0.01758
/*20  */ 	vs->auth = VNC_AUTH_NONE;                                                     // (16) 0.02734
/*22  */ 	vs->subauth = VNC_AUTH_INVALID;                                               // (14) 0.03125
/*24  */     } else {                                                                   // (23) 0.01172
/*26  */         if (websocket) {                                                       // (15) 0.02734
/*28  */             vs->auth = vd->ws_auth;                                            // (9) 0.04297
/*30  */             vs->subauth = VNC_AUTH_INVALID;                                    // (6) 0.05078
/*32  */         } else {                                                               // (19) 0.01953
/*34  */             vs->auth = vd->auth;                                               // (12) 0.03906
/*36  */             vs->subauth = vd->subauth;                                         // (10) 0.04297
/*38  */         }                                                                      // (21) 0.01562
/*40  */     }                                                                          // (25) 0.007812
/*42  */     VNC_DEBUG("Client sock=%d ws=%d auth=%d subauth=%d\n",                     // (3) 0.05859
/*44  */               csock, websocket, vs->auth, vs->subauth);                        // (5) 0.05469
/*48  */     vs->lossy_rect = g_malloc0(VNC_STAT_ROWS * sizeof (*vs->lossy_rect));      // (1) 0.06445
/*50  */     for (i = 0; i < VNC_STAT_ROWS; ++i) {                                      // (7) 0.04492
/*52  */         vs->lossy_rect[i] = g_malloc0(VNC_STAT_COLS * sizeof (uint8_t));       // (0) 0.07422
/*54  */     }                                                                          // (24) 0.007812
/*58  */     VNC_DEBUG("New client on socket %d\n", csock);                             // (11) 0.03906
/*60  */     update_displaychangelistener(&vd->dcl, VNC_REFRESH_INTERVAL_BASE);         // (4) 0.05664
/*62  */     qemu_set_nonblock(vs->csock);                                              // 0.0
/*64  */     if (websocket) {                                                           // 0.0
/*66  */         vs->websocket = 1;                                                     // 0.0
/*68  */         if (vd->ws_tls) {                                                      // 0.0
/*70  */             qemu_set_fd_handler(vs->csock, vncws_tls_handshake_io, NULL, vs);  // 0.0
/*72  */         } else {                                                               // 0.0
/*74  */             qemu_set_fd_handler(vs->csock, vncws_handshake_read, NULL, vs);    // 0.0
/*76  */         }                                                                      // 0.0
/*78  */     } else                                                                     // 0.0
/*80  */     {                                                                          // 0.0
/*82  */         qemu_set_fd_handler(vs->csock, vnc_client_read, NULL, vs);             // 0.0
/*84  */     }                                                                          // 0.0
/*88  */     vnc_client_cache_addr(vs);                                                 // 0.0
/*90  */     vnc_qmp_event(vs, QAPI_EVENT_VNC_CONNECTED);                               // 0.0
/*92  */     vnc_set_share_mode(vs, VNC_SHARE_MODE_CONNECTING);                         // 0.0
/*96  */     if (!vs->websocket) {                                                      // 0.0
/*98  */         vnc_init_state(vs);                                                    // 0.0
/*100 */     }                                                                          // 0.0
/*104 */     if (vd->num_connecting > vd->connections_limit) {                          // 0.0
/*106 */         QTAILQ_FOREACH(vs, &vd->clients, next) {                               // 0.0
/*108 */             if (vs->share_mode == VNC_SHARE_MODE_CONNECTING) {                 // 0.0
/*110 */                 vnc_disconnect_start(vs);                                      // 0.0
/*112 */                 return;                                                        // 0.0
/*114 */             }                                                                  // 0.0
/*116 */         }                                                                      // 0.0
/*118 */     }                                                                          // 0.0
/*120 */ }                                                                              // 0.0
