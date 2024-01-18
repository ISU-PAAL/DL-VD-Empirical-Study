// commit message qemu@c3fecea50d (target=1, prob=0.56718934, correct=True): sheepdog: Avoid deadlock in error path
/*0   */ static int coroutine_fn add_aio_request(BDRVSheepdogState *s, AIOReq *aio_req,  // (2) 0.0625
/*2   */                            struct iovec *iov, int niov, int create,             // (0) 0.07812
/*4   */                            enum AIOCBState aiocb_type)                          // (1) 0.07422
/*6   */ {                                                                               // (27) 0.001953
/*8   */     int nr_copies = s->inode.nr_copies;                                         // (8) 0.03906
/*10  */     SheepdogObjReq hdr;                                                         // (20) 0.02148
/*12  */     unsigned int wlen;                                                          // (23) 0.01562
/*14  */     int ret;                                                                    // (24) 0.01172
/*16  */     uint64_t oid = aio_req->oid;                                                // (11) 0.0332
/*18  */     unsigned int datalen = aio_req->data_len;                                   // (10) 0.03516
/*20  */     uint64_t offset = aio_req->offset;                                          // (14) 0.03125
/*22  */     uint8_t flags = aio_req->flags;                                             // (13) 0.03125
/*24  */     uint64_t old_oid = aio_req->base_oid;                                       // (9) 0.03906
/*28  */     if (!nr_copies) {                                                           // (21) 0.02148
/*30  */         error_report("bug");                                                    // (18) 0.02539
/*32  */     }                                                                           // (26) 0.007812
/*36  */     memset(&hdr, 0, sizeof(hdr));                                               // (12) 0.03125
/*40  */     if (aiocb_type == AIOCB_READ_UDATA) {                                       // (7) 0.04102
/*42  */         wlen = 0;                                                               // (19) 0.02344
/*44  */         hdr.opcode = SD_OP_READ_OBJ;                                            // (6) 0.04297
/*46  */         hdr.flags = flags;                                                      // (15) 0.02734
/*48  */     } else if (create) {                                                        // (22) 0.01953
/*50  */         wlen = datalen;                                                         // (16) 0.02734
/*52  */         hdr.opcode = SD_OP_CREATE_AND_WRITE_OBJ;                                // (3) 0.05469
/*54  */         hdr.flags = SD_FLAG_CMD_WRITE | flags;                                  // (4) 0.04687
/*56  */     } else {                                                                    // (25) 0.01172
/*58  */         wlen = datalen;                                                         // (17) 0.02734
/*60  */         hdr.opcode = SD_OP_WRITE_OBJ;                                           // (5) 0.04492
/*62  */         hdr.flags = SD_FLAG_CMD_WRITE | flags;                                  // 0.0
/*64  */     }                                                                           // 0.0
/*68  */     hdr.oid = oid;                                                              // 0.0
/*70  */     hdr.cow_oid = old_oid;                                                      // 0.0
/*72  */     hdr.copies = s->inode.nr_copies;                                            // 0.0
/*76  */     hdr.data_length = datalen;                                                  // 0.0
/*78  */     hdr.offset = offset;                                                        // 0.0
/*82  */     hdr.id = aio_req->id;                                                       // 0.0
/*86  */     qemu_co_mutex_lock(&s->lock);                                               // 0.0
/*88  */     s->co_send = qemu_coroutine_self();                                         // 0.0
/*90  */     qemu_aio_set_fd_handler(s->fd, co_read_response, co_write_request,          // 0.0
/*92  */                             aio_flush_request, NULL, s);                        // 0.0
/*94  */     set_cork(s->fd, 1);                                                         // 0.0
/*98  */     /* send a header */                                                         // 0.0
/*100 */     ret = do_write(s->fd, &hdr, sizeof(hdr));                                   // 0.0
/*102 */     if (ret) {                                                                  // 0.0
/*105 */         error_report("failed to send a req, %s", strerror(errno));              // 0.0
/*107 */         return -EIO;                                                            // 0.0
/*109 */     }                                                                           // 0.0
/*113 */     if (wlen) {                                                                 // 0.0
/*115 */         ret = do_writev(s->fd, iov, wlen, aio_req->iov_offset);                 // 0.0
/*117 */         if (ret) {                                                              // 0.0
/*120 */             error_report("failed to send a data, %s", strerror(errno));         // 0.0
/*122 */             return -EIO;                                                        // 0.0
/*124 */         }                                                                       // 0.0
/*126 */     }                                                                           // 0.0
/*130 */     set_cork(s->fd, 0);                                                         // 0.0
/*132 */     qemu_aio_set_fd_handler(s->fd, co_read_response, NULL,                      // 0.0
/*134 */                             aio_flush_request, NULL, s);                        // 0.0
/*139 */     return 0;                                                                   // 0.0
/*141 */ }                                                                               // 0.0
