// commit message qemu@b1b27b6426 (target=1, prob=0.2499176, correct=False): nbd: avoid uninitialized warnings
/*0  */ int nbd_client_session_co_flush(NbdClientSession *client)         // (5) 0.0574
/*2  */ {                                                                 // (22) 0.003021
/*4  */     struct nbd_request request;                                   // (10) 0.03021
/*6  */     struct nbd_reply reply;                                       // (11) 0.03021
/*8  */     ssize_t ret;                                                  // (14) 0.02719
/*12 */     if (!(client->nbdflags & NBD_FLAG_SEND_FLUSH)) {              // (1) 0.07251
/*14 */         return 0;                                                 // (12) 0.03021
/*16 */     }                                                             // (19) 0.01208
/*20 */     request.type = NBD_CMD_FLUSH;                                 // (6) 0.04834
/*22 */     if (client->nbdflags & NBD_FLAG_SEND_FUA) {                   // (2) 0.06949
/*24 */         request.type |= NBD_CMD_FLAG_FUA;                         // (3) 0.06949
/*26 */     }                                                             // (20) 0.01208
/*30 */     request.from = 0;                                             // (15) 0.02719
/*32 */     request.len = 0;                                              // (16) 0.02719
/*36 */     nbd_coroutine_start(client, &request);                        // (7) 0.04834
/*38 */     ret = nbd_co_send_request(client, &request, NULL, 0);         // (4) 0.06949
/*40 */     if (ret < 0) {                                                // (13) 0.03021
/*42 */         reply.error = -ret;                                       // (9) 0.0423
/*44 */     } else {                                                      // (18) 0.01813
/*46 */         nbd_co_receive_reply(client, &request, &reply, NULL, 0);  // (0) 0.08761
/*48 */     }                                                             // (21) 0.01208
/*50 */     nbd_coroutine_end(client, &request);                          // (8) 0.04834
/*52 */     return -reply.error;                                          // (17) 0.02719
/*54 */ }                                                                 // (23) 0.003021
