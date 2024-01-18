// commit message qemu@f53a829bb9 (target=0, prob=0.3938018, correct=True): nbd: Drop BDS backpointer
/*0  */ void nbd_client_close(NBDClient *client)                                // (3) 0.08284
/*2  */ {                                                                       // (13) 0.005917
/*4  */     if (client->closing) {                                              // (6) 0.06509
/*6  */         return;                                                         // (9) 0.05325
/*8  */     }                                                                   // (11) 0.02367
/*12 */     client->closing = true;                                             // (7) 0.05917
/*16 */     /* Force requests to finish.  They will drop their own references,  // (2) 0.1006
/*18 */      * then we'll close the socket and free the NBDClient.              // (0) 0.1065
/*20 */      */                                                                 // (10) 0.02959
/*22 */     shutdown(client->sock, 2);                                          // (5) 0.07101
/*26 */     /* Also tell the client, so that they release their reference.  */  // (1) 0.1065
/*28 */     if (client->close) {                                                // (8) 0.05917
/*30 */         client->close(client);                                          // (4) 0.07692
/*32 */     }                                                                   // (12) 0.02367
/*34 */ }                                                                       // (14) 0.005917
