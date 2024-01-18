// commit message qemu@0c9390d978 (target=1, prob=0.2367031, correct=False): nbd: Fix regression on resiliency to port scan
/*0  */ static void nbd_client_closed(NBDClient *client)           // (1) 0.1456
/*2  */ {                                                          // (7) 0.009709
/*4  */     nb_fds--;                                              // (5) 0.09709
/*6  */     if (nb_fds == 0 && !persistent && state == RUNNING) {  // (0) 0.2136
/*8  */         state = TERMINATE;                                 // (2) 0.1262
/*10 */     }                                                      // (6) 0.03883
/*12 */     nbd_update_server_watch();                             // (3) 0.1165
/*14 */     nbd_client_put(client);                                // (4) 0.1165
/*16 */ }                                                          // (8) 0.009709
