// commit message qemu@bd269ebc82 (target=0, prob=0.0070302556, correct=True): sockets: Limit SocketAddressLegacy to external interfaces
/*0  */ static SocketAddressLegacy *tcp_build_address(const char *host_port, Error **errp)  // (1) 0.125
/*2  */ {                                                                                   // (11) 0.005
/*4  */     InetSocketAddress *iaddr = g_new(InetSocketAddress, 1);                         // (2) 0.11
/*6  */     SocketAddressLegacy *saddr;                                                     // (7) 0.055
/*10 */     if (inet_parse(iaddr, host_port, errp)) {                                       // (3) 0.1
/*12 */         qapi_free_InetSocketAddress(iaddr);                                         // (4) 0.1
/*14 */         return NULL;                                                                // (8) 0.05
/*16 */     }                                                                               // (10) 0.02
/*20 */     saddr = g_new0(SocketAddressLegacy, 1);                                         // (5) 0.09
/*22 */     saddr->type = SOCKET_ADDRESS_LEGACY_KIND_INET;                                  // (0) 0.13
/*24 */     saddr->u.inet.data = iaddr;                                                     // (6) 0.075
/*28 */     return saddr;                                                                   // (9) 0.035
/*30 */ }                                                                                   // (12) 0.005
