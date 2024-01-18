// commit message qemu@e4d2edc9d0 (target=0, prob=0.0072355927, correct=True): io: bind to loopback IP addrs in test suite
/*0  */ static void test_io_channel_ipv4(bool async)                  // (12) 0.04688
/*2  */ {                                                             // (15) 0.003125
/*4  */     SocketAddress *listen_addr = g_new0(SocketAddress, 1);    // (6) 0.06563
/*6  */     SocketAddress *connect_addr = g_new0(SocketAddress, 1);   // (8) 0.0625
/*10 */     listen_addr->type = SOCKET_ADDRESS_KIND_INET;             // (3) 0.07188
/*12 */     listen_addr->u.inet = g_new0(InetSocketAddress, 1);       // (2) 0.07188
/*14 */     listen_addr->u.inet->host = g_strdup("0.0.0.0");          // (0) 0.08438
/*16 */     listen_addr->u.inet->port = NULL; /* Auto-select */       // (9) 0.0625
/*20 */     connect_addr->type = SOCKET_ADDRESS_KIND_INET;            // (4) 0.07188
/*22 */     connect_addr->u.inet = g_new0(InetSocketAddress, 1);      // (5) 0.07188
/*24 */     connect_addr->u.inet->host = g_strdup("127.0.0.1");       // (1) 0.08438
/*26 */     connect_addr->u.inet->port = NULL; /* Filled in later */  // (7) 0.06563
/*30 */     test_io_channel(async, listen_addr, connect_addr);        // (10) 0.0625
/*34 */     qapi_free_SocketAddress(listen_addr);                     // (11) 0.05
/*36 */     qapi_free_SocketAddress(connect_addr);                    // (13) 0.04688
/*38 */ }                                                             // (14) 0.003125
