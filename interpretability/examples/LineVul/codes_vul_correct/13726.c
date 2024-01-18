// commit message qemu@9e0ff75e51 (target=1, prob=0.9989812, correct=True): vnc: fix coverity warning
/*0  */ char *vnc_display_local_addr(const char *id)           // (2) 0.2286
/*2  */ {                                                      // (4) 0.01429
/*4  */     VncDisplay *vs = vnc_display_find(id);             // (1) 0.2571
/*9  */     return vnc_socket_local_addr("%s:%s", vs->lsock);  // (0) 0.3429
/*11 */ }                                                      // (3) 0.01429
