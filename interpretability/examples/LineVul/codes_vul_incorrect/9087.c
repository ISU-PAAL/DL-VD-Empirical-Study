// commit message qemu@f140e30003 (target=1, prob=0.26726353, correct=False): nbd: Minimal structured read for client
/*0  */ static int nbd_co_request(BlockDriverState *bs,                                   // (10) 0.03676
/*2  */                           NBDRequest *request,                                    // (5) 0.07598
/*4  */                           QEMUIOVector *qiov)                                     // (2) 0.08333
/*6  */ {                                                                                 // (18) 0.002451
/*8  */     NBDClientSession *client = nbd_get_client_session(bs);                        // (7) 0.05147
/*10 */     int ret;                                                                      // (14) 0.01471
/*14 */     if (qiov) {                                                                   // (13) 0.02206
/*16 */         assert(request->type == NBD_CMD_WRITE || request->type == NBD_CMD_READ);  // (3) 0.08333
/*18 */         assert(request->len == iov_size(qiov->iov, qiov->niov));                  // (6) 0.07108
/*20 */     } else {                                                                      // (15) 0.01471
/*22 */         assert(request->type != NBD_CMD_WRITE && request->type != NBD_CMD_READ);  // (4) 0.08333
/*24 */     }                                                                             // (16) 0.009804
/*26 */     ret = nbd_co_send_request(bs, request,                                        // (9) 0.04412
/*28 */                               request->type == NBD_CMD_WRITE ? qiov : NULL);      // (1) 0.1152
/*30 */     if (ret < 0) {                                                                // (11) 0.02451
/*32 */         return ret;                                                               // (12) 0.02451
/*34 */     }                                                                             // (17) 0.009804
/*38 */     return nbd_co_receive_reply(client, request->handle,                          // (8) 0.04902
/*40 */                                 request->type == NBD_CMD_READ ? qiov : NULL);     // (0) 0.1176
/*42 */ }                                                                                 // (19) 0.002451
