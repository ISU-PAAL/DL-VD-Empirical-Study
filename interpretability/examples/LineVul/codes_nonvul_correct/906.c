// commit message qemu@dfd100f242 (target=0, prob=0.046133094, correct=True): sockets: Rename SocketAddress to SocketAddressLegacy
/*0  */ static int vnc_display_listen(VncDisplay *vd,           // (12) 0.03125
/*2  */                               SocketAddress **saddr,    // (6) 0.06836
/*4  */                               size_t nsaddr,            // (7) 0.06836
/*6  */                               SocketAddress **wsaddr,   // (8) 0.06836
/*8  */                               size_t nwsaddr,           // (5) 0.07031
/*10 */                               Error **errp)             // (9) 0.06641
/*12 */ {                                                       // (17) 0.001953
/*14 */     size_t i;                                           // (14) 0.01562
/*18 */     for (i = 0; i < nsaddr; i++) {                      // (11) 0.0332
/*20 */         if (vnc_display_listen_addr(vd, saddr[i],       // (10) 0.05078
/*22 */                                     "vnc-listen",       // (1) 0.08203
/*24 */                                     &vd->lsock,         // (4) 0.08008
/*26 */                                     &vd->lsock_tag,     // (0) 0.08398
/*28 */                                     &vd->nlsock,        // (2) 0.08203
/*30 */                                     errp) < 0) {        // (3) 0.08203
/*32 */             return -1;                                  // (13) 0.0293
/*34 */         }                                               // (15) 0.01562
/*36 */     }                                                   // (16) 0.007812
/*38 */     for (i = 0; i < nwsaddr; i++) {                     // 0.0
/*40 */         if (vnc_display_listen_addr(vd, wsaddr[i],      // 0.0
/*42 */                                     "vnc-ws-listen",    // 0.0
/*44 */                                     &vd->lwebsock,      // 0.0
/*46 */                                     &vd->lwebsock_tag,  // 0.0
/*48 */                                     &vd->nlwebsock,     // 0.0
/*50 */                                     errp) < 0) {        // 0.0
/*52 */             return -1;                                  // 0.0
/*54 */         }                                               // 0.0
/*56 */     }                                                   // 0.0
/*60 */     return 0;                                           // 0.0
/*62 */ }                                                       // 0.0
