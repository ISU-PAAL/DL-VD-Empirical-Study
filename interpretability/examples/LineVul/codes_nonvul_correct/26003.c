// commit message qemu@bd269ebc82 (target=0, prob=0.017984204, correct=True): sockets: Limit SocketAddressLegacy to external interfaces
/*0  */ static void vnc_display_print_local_addr(VncDisplay *vd)              // (5) 0.06032
/*2  */ {                                                                     // (18) 0.003175
/*4  */     SocketAddressLegacy *addr;                                        // (9) 0.03175
/*6  */     Error *err = NULL;                                                // (10) 0.02857
/*10 */     if (!vd->nlsock) {                                                // (8) 0.0381
/*12 */         return;                                                       // (11) 0.02857
/*14 */     }                                                                 // (15) 0.0127
/*18 */     addr = qio_channel_socket_get_local_address(vd->lsock[0], &err);  // (2) 0.08889
/*20 */     if (!addr) {                                                      // (14) 0.0254
/*22 */         return;                                                       // (12) 0.02857
/*24 */     }                                                                 // (16) 0.0127
/*28 */     if (addr->type != SOCKET_ADDRESS_LEGACY_KIND_INET) {              // (3) 0.08889
/*30 */         qapi_free_SocketAddressLegacy(addr);                          // (6) 0.06032
/*32 */         return;                                                       // (13) 0.02857
/*34 */     }                                                                 // (17) 0.0127
/*36 */     error_printf_unless_qmp("VNC server running on %s:%s\n",          // (4) 0.07937
/*38 */                             addr->u.inet.data->host,                  // (0) 0.1175
/*40 */                             addr->u.inet.data->port);                 // (1) 0.1175
/*42 */     qapi_free_SocketAddressLegacy(addr);                              // (7) 0.04762
/*44 */ }                                                                     // (19) 0.003175
