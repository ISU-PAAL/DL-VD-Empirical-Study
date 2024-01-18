// commit message qemu@dfd100f242 (target=0, prob=0.007248552, correct=True): sockets: Rename SocketAddress to SocketAddressLegacy
/*0  */ static SocketAddress *tcp_build_address(const char *host_port, Error **errp)  // (0) 0.1211
/*2  */ {                                                                             // (12) 0.005263
/*4  */     InetSocketAddress *iaddr = g_new(InetSocketAddress, 1);                   // (1) 0.1158
/*6  */     SocketAddress *saddr;                                                     // (8) 0.04737
/*10 */     if (inet_parse(iaddr, host_port, errp)) {                                 // (3) 0.1053
/*12 */         qapi_free_InetSocketAddress(iaddr);                                   // (4) 0.1053
/*14 */         return NULL;                                                          // (7) 0.05263
/*16 */     }                                                                         // (10) 0.02105
/*20 */     saddr = g_new0(SocketAddress, 1);                                         // (5) 0.08421
/*22 */     saddr->type = SOCKET_ADDRESS_KIND_INET;                                   // (2) 0.1158
/*24 */     saddr->u.inet.data = iaddr;                                               // (6) 0.07895
/*28 */     return saddr;                                                             // (9) 0.03684
/*30 */ }                                                                             // (11) 0.005263
