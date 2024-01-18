// commit message qemu@384acbf46b (target=0, prob=0.14255077, correct=True): async: Remove AsyncContext
/*0  */ BlockDriverAIOCB *paio_submit(BlockDriverState *bs, int fd,        // (7) 0.04751
/*2  */         int64_t sector_num, QEMUIOVector *qiov, int nb_sectors,    // (0) 0.07363
/*4  */         BlockDriverCompletionFunc *cb, void *opaque, int type)     // (3) 0.05701
/*6  */ {                                                                  // (22) 0.002375
/*8  */     struct qemu_paiocb *acb;                                       // (14) 0.03563
/*12 */     acb = qemu_aio_get(&raw_aio_pool, bs, cb, opaque);             // (1) 0.07126
/*14 */     if (!acb)                                                      // (20) 0.019
/*16 */         return NULL;                                               // (17) 0.02375
/*18 */     acb->aio_type = type;                                          // (16) 0.03088
/*20 */     acb->aio_fildes = fd;                                          // (12) 0.038
/*22 */     acb->ev_signo = SIGUSR2;                                       // (13) 0.038
/*24 */     acb->async_context_id = get_async_context_id();                // (4) 0.05226
/*28 */     if (qiov) {                                                    // (19) 0.02138
/*30 */         acb->aio_iov = qiov->iov;                                  // (8) 0.04751
/*32 */         acb->aio_niov = qiov->niov;                                // (5) 0.05226
/*34 */     }                                                              // (21) 0.009501
/*36 */     acb->aio_nbytes = nb_sectors * 512;                            // (9) 0.04751
/*38 */     acb->aio_offset = sector_num * 512;                            // (11) 0.04038
/*42 */     acb->next = posix_aio_state->first_aio;                        // (6) 0.04988
/*44 */     posix_aio_state->first_aio = acb;                              // (10) 0.04513
/*48 */     trace_paio_submit(acb, opaque, sector_num, nb_sectors, type);  // (2) 0.06176
/*50 */     qemu_paio_submit(acb);                                         // (15) 0.03325
/*52 */     return &acb->common;                                           // (18) 0.02375
/*54 */ }                                                                  // (23) 0.002375
