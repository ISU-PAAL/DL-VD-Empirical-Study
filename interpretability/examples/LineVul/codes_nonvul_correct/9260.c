// commit message qemu@fc19f8a02e (target=0, prob=0.09826115, correct=True): nbd: consistently check for <0 or >=0
/*0  */ static int nbd_co_readv_1(BlockDriverState *bs, int64_t sector_num,    // (4) 0.07903
/*2  */                           int nb_sectors, QEMUIOVector *qiov,          // (0) 0.1246
/*4  */                           int offset)                                  // (2) 0.08511
/*6  */ {                                                                      // (18) 0.00304
/*8  */     BDRVNBDState *s = bs->opaque;                                      // (5) 0.05471
/*10 */     struct nbd_request request;                                        // (12) 0.0304
/*12 */     struct nbd_reply reply;                                            // (13) 0.0304
/*16 */     request.type = NBD_CMD_READ;                                       // (8) 0.04559
/*18 */     request.from = sector_num * 512;                                   // (11) 0.03951
/*20 */     request.len = nb_sectors * 512;                                    // (9) 0.04559
/*24 */     nbd_coroutine_start(s, &request);                                  // (6) 0.04863
/*26 */     if (nbd_co_send_request(s, &request, NULL, 0) == -1) {             // (3) 0.08511
/*28 */         reply.error = errno;                                           // (10) 0.04255
/*30 */     } else {                                                           // (15) 0.01824
/*32 */         nbd_co_receive_reply(s, &request, &reply, qiov->iov, offset);  // (1) 0.09726
/*34 */     }                                                                  // (16) 0.01216
/*36 */     nbd_coroutine_end(s, &request);                                    // (7) 0.04863
/*38 */     return -reply.error;                                               // (14) 0.02736
/*42 */ }                                                                      // (17) 0.00304
