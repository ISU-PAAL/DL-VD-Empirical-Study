// commit message qemu@4be746345f (target=0, prob=0.22767107, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static int virtio_blk_handle_rw_error(VirtIOBlockReq *req, int error,               // (3) 0.08814
/*2  */     bool is_read)                                                                   // (12) 0.02712
/*4  */ {                                                                                   // (14) 0.00339
/*6  */     BlockErrorAction action = bdrv_get_error_action(req->dev->bs, is_read, error);  // (2) 0.1017
/*8  */     VirtIOBlock *s = req->dev;                                                      // (11) 0.04407
/*12 */     if (action == BLOCK_ERROR_ACTION_STOP) {                                        // (7) 0.06102
/*14 */         req->next = s->rq;                                                          // (8) 0.05424
/*16 */         s->rq = req;                                                                // (10) 0.04746
/*18 */     } else if (action == BLOCK_ERROR_ACTION_REPORT) {                               // (5) 0.0678
/*20 */         virtio_blk_req_complete(req, VIRTIO_BLK_S_IOERR);                           // (0) 0.1085
/*22 */         block_acct_done(bdrv_get_stats(s->bs), &req->acct);                         // (1) 0.1085
/*24 */         virtio_blk_free_request(req);                                               // (6) 0.06441
/*26 */     }                                                                               // (13) 0.01356
/*30 */     bdrv_error_action(s->bs, action, is_read, error);                               // (4) 0.07797
/*32 */     return action != BLOCK_ERROR_ACTION_IGNORE;                                     // (9) 0.05424
/*34 */ }                                                                                   // (15) 0.00339
