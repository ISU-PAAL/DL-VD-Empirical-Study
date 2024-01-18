// commit message qemu@d99598cc99 (target=1, prob=0.4515587, correct=False): Coverity: Fix failure path for qemu_accept in migration
/*0  */ static void tcp_accept_incoming_migration(void *opaque)              // (6) 0.04762
/*2  */ {                                                                    // (25) 0.002801
/*4  */     struct sockaddr_in addr;                                         // (13) 0.02801
/*6  */     socklen_t addrlen = sizeof(addr);                                // (8) 0.03922
/*8  */     int s = (intptr_t)opaque;                                        // (7) 0.04202
/*10 */     QEMUFile *f;                                                     // (12) 0.02801
/*12 */     int c;                                                           // (19) 0.01681
/*16 */     do {                                                             // (20) 0.01401
/*18 */         c = qemu_accept(s, (struct sockaddr *)&addr, &addrlen);      // (0) 0.08123
/*20 */     } while (c == -1 && socket_error() == EINTR);                    // (4) 0.05602
/*22 */     qemu_set_fd_handler2(s, NULL, NULL, NULL, NULL);                 // (2) 0.06723
/*24 */     closesocket(s);                                                  // (17) 0.02241
/*28 */     DPRINTF("accepted migration\n");                                 // (9) 0.03641
/*32 */     if (c == -1) {                                                   // (11) 0.03081
/*34 */         fprintf(stderr, "could not accept migration connection\n");  // (3) 0.06443
/*36 */         goto out;                                                    // (14) 0.02801
/*38 */     }                                                                // (22) 0.0112
/*42 */     f = qemu_fopen_socket(c, "rb");                                  // (5) 0.05322
/*44 */     if (f == NULL) {                                                 // (15) 0.02801
/*46 */         fprintf(stderr, "could not qemu_fopen socket\n");            // (1) 0.07563
/*48 */         goto out;                                                    // (16) 0.02801
/*50 */     }                                                                // (23) 0.0112
/*54 */     process_incoming_migration(f);                                   // (10) 0.03641
/*56 */     return;                                                          // (21) 0.01401
/*60 */ out:                                                                 // (24) 0.005602
/*62 */     closesocket(c);                                                  // (18) 0.02241
/*64 */ }                                                                    // (26) 0.002801
