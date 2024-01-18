// commit message qemu@72cf2d4f0e (target=0, prob=0.007946086, correct=True): Fix sys-queue.h conflict for good
/*0  */ static void rndis_clear_responsequeue(USBNetState *s)  // (2) 0.1518
/*2  */ {                                                      // (6) 0.008929
/*4  */     struct rndis_response *r;                          // (4) 0.1071
/*8  */     while ((r = s->rndis_resp.tqh_first)) {            // (1) 0.1964
/*10 */         TAILQ_REMOVE(&s->rndis_resp, r, entries);      // (0) 0.2411
/*12 */         qemu_free(r);                                  // (3) 0.1339
/*14 */     }                                                  // (5) 0.03571
/*16 */ }                                                      // (7) 0.008929
