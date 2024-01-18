// commit message qemu@b1b27b6426 (target=1, prob=0.1016834, correct=False): nbd: avoid uninitialized warnings
/*0  */ static int nbd_co_readv_1(NbdClientSession *client, int64_t sector_num,  // (3) 0.08308
/*2  */                           int nb_sectors, QEMUIOVector *qiov,            // (0) 0.1262
/*4  */                           int offset)                                    // (2) 0.08615
/*6  */ {                                                                        // (18) 0.003077
/*8  */     struct nbd_request request;                                          // (11) 0.03077
/*10 */     struct nbd_reply reply;                                              // (12) 0.03077
/*12 */     ssize_t ret;                                                         // (14) 0.02769
/*16 */     request.type = NBD_CMD_READ;                                         // (8) 0.04615
/*18 */     request.from = sector_num * 512;                                     // (10) 0.04
/*20 */     request.len = nb_sectors * 512;                                      // (7) 0.04615
/*24 */     nbd_coroutine_start(client, &request);                               // (5) 0.04923
/*26 */     ret = nbd_co_send_request(client, &request, NULL, 0);                // (4) 0.07077
/*28 */     if (ret < 0) {                                                       // (13) 0.03077
/*30 */         reply.error = -ret;                                              // (9) 0.04308
/*32 */     } else {                                                             // (16) 0.01846
/*34 */         nbd_co_receive_reply(client, &request, &reply, qiov, offset);    // (1) 0.09231
/*36 */     }                                                                    // (17) 0.01231
/*38 */     nbd_coroutine_end(client, &request);                                 // (6) 0.04923
/*40 */     return -reply.error;                                                 // (15) 0.02769
/*44 */ }                                                                        // (19) 0.003077
