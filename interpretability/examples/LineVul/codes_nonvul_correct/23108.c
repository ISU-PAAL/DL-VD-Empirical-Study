// commit message qemu@bd269ebc82 (target=0, prob=0.019436268, correct=True): sockets: Limit SocketAddressLegacy to external interfaces
/*0  */ int qio_dns_resolver_lookup_sync(QIODNSResolver *resolver,      // (9) 0.04883
/*2  */                                  SocketAddressLegacy *addr,     // (6) 0.07617
/*4  */                                  size_t *naddrs,                // (5) 0.07813
/*6  */                                  SocketAddressLegacy ***addrs,  // (4) 0.07813
/*8  */                                  Error **errp)                  // (7) 0.07227
/*10 */ {                                                               // (14) 0.001953
/*12 */     switch (addr->type) {                                       // (13) 0.01953
/*14 */     case SOCKET_ADDRESS_LEGACY_KIND_INET:                       // (12) 0.04297
/*16 */         return qio_dns_resolver_lookup_sync_inet(resolver,      // (8) 0.05273
/*18 */                                                  addr,          // (3) 0.09766
/*20 */                                                  naddrs,        // (0) 0.1016
/*22 */                                                  addrs,         // (2) 0.09961
/*24 */                                                  errp);         // (1) 0.09961
/*28 */     case SOCKET_ADDRESS_LEGACY_KIND_UNIX:                       // (11) 0.04297
/*30 */     case SOCKET_ADDRESS_LEGACY_KIND_VSOCK:                      // (10) 0.04297
/*32 */     case SOCKET_ADDRESS_LEGACY_KIND_FD:                         // 0.0
/*34 */         return qio_dns_resolver_lookup_sync_nop(resolver,       // 0.0
/*36 */                                                 addr,           // 0.0
/*38 */                                                 naddrs,         // 0.0
/*40 */                                                 addrs,          // 0.0
/*42 */                                                 errp);          // 0.0
/*46 */     default:                                                    // 0.0
/*48 */         abort();                                                // 0.0
/*50 */     }                                                           // 0.0
/*52 */ }                                                               // 0.0
