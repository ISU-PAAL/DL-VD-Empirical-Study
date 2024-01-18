// commit message qemu@f53a829bb9 (target=0, prob=0.37872928, correct=True): nbd: Drop BDS backpointer
/*0  */ static void nbd_reply_ready(void *opaque)                                // (13) 0.02972
/*2  */ {                                                                        // (31) 0.002123
/*4  */     NbdClientSession *s = opaque;                                        // (19) 0.02548
/*6  */     uint64_t i;                                                          // (21) 0.01911
/*8  */     int ret;                                                             // (26) 0.01274
/*12 */     if (s->reply.handle == 0) {                                          // (14) 0.02972
/*14 */         /* No reply already in flight.  Fetch a header.  It is possible  // (2) 0.05096
/*16 */          * that another thread has done the same thing in parallel, so   // (4) 0.04459
/*18 */          * the socket is not readable anymore.                           // (10) 0.03397
/*20 */          */                                                              // (22) 0.01911
/*22 */         ret = nbd_receive_reply(s->sock, &s->reply);                     // (1) 0.05732
/*24 */         if (ret == -EAGAIN) {                                            // (8) 0.03609
/*26 */             return;                                                      // (18) 0.0276
/*28 */         }                                                                // (24) 0.01699
/*30 */         if (ret < 0) {                                                   // (15) 0.02972
/*32 */             s->reply.handle = 0;                                         // (5) 0.04034
/*34 */             goto fail;                                                   // (16) 0.02972
/*36 */         }                                                                // (25) 0.01699
/*38 */     }                                                                    // (27) 0.008493
/*42 */     /* There's no need for a mutex on the receive side, because the      // (6) 0.04034
/*44 */      * handler acts as a synchronization point and ensures that only     // (12) 0.03185
/*46 */      * one coroutine is called until the reply finishes.  */             // (9) 0.03609
/*48 */     i = HANDLE_TO_INDEX(s, s->reply.handle);                             // (3) 0.04671
/*50 */     if (i >= MAX_NBD_REQUESTS) {                                         // (7) 0.03822
/*52 */         goto fail;                                                       // (20) 0.02123
/*54 */     }                                                                    // (28) 0.008493
/*58 */     if (s->recv_coroutine[i]) {                                          // (11) 0.03397
/*60 */         qemu_coroutine_enter(s->recv_coroutine[i], NULL);                // (0) 0.05945
/*62 */         return;                                                          // (23) 0.01911
/*64 */     }                                                                    // (29) 0.008493
/*68 */ fail:                                                                    // (30) 0.004246
/*70 */     nbd_teardown_connection(s);                                          // (17) 0.02972
/*72 */ }                                                                        // (32) 0.002123
