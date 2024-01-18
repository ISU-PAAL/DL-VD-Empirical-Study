// commit message qemu@1f01e50b83 (target=0, prob=0.35840964, correct=True): qed: protect table cache with CoMutex
/*0  */ static void coroutine_fn qed_aio_complete(QEDAIOCB *acb)                        // (6) 0.04792
/*2  */ {                                                                               // (24) 0.002083
/*4  */     BDRVQEDState *s = acb_to_s(acb);                                            // (8) 0.04583
/*8  */     /* Free resources */                                                        // (20) 0.01458
/*10 */     qemu_iovec_destroy(&acb->cur_qiov);                                         // (9) 0.04375
/*12 */     qed_unref_l2_cache_entry(acb->request.l2_table);                            // (4) 0.05417
/*16 */     /* Free the buffer we may have allocated for zero writes */                 // (18) 0.03125
/*18 */     if (acb->flags & QED_AIOCB_ZERO) {                                          // (10) 0.04375
/*20 */         qemu_vfree(acb->qiov->iov[0].iov_base);                                 // (2) 0.05833
/*22 */         acb->qiov->iov[0].iov_base = NULL;                                      // (7) 0.04792
/*24 */     }                                                                           // (22) 0.008333
/*28 */     /* Start next allocating write request waiting behind this one.  Note that  // (12) 0.0375
/*30 */      * requests enqueue themselves when they first hit an unallocated cluster   // (13) 0.0375
/*32 */      * but they wait until the entire request is finished before waking up the  // (14) 0.0375
/*34 */      * next request in the queue.  This ensures that we don't cycle through     // (11) 0.04167
/*36 */      * requests multiple times but rather finish one at a time completely.      // (15) 0.03542
/*38 */      */                                                                         // (21) 0.01042
/*40 */     if (acb == s->allocating_acb) {                                             // (16) 0.03542
/*42 */         s->allocating_acb = NULL;                                               // (17) 0.03542
/*44 */         if (!qemu_co_queue_empty(&s->allocating_write_reqs)) {                  // (1) 0.0625
/*46 */             qemu_co_enter_next(&s->allocating_write_reqs);                      // (0) 0.06458
/*48 */         } else if (s->header.features & QED_F_NEED_CHECK) {                     // (3) 0.05833
/*50 */             qed_start_need_check_timer(s);                                      // (5) 0.05
/*52 */         }                                                                       // (19) 0.01667
/*54 */     }                                                                           // (23) 0.008333
/*56 */ }                                                                               // (25) 0.002083
