// commit message qemu@61007b316c (target=0, prob=0.31574035, correct=True): block: move I/O request processing to block/io.c
/*0  */ static void tracked_request_end(BdrvTrackedRequest *req)  // (2) 0.1667
/*2  */ {                                                         // (6) 0.009804
/*4  */     if (req->serialising) {                               // (4) 0.1078
/*6  */         req->bs->serialising_in_flight--;                 // (1) 0.1863
/*8  */     }                                                     // (5) 0.03922
/*12 */     QLIST_REMOVE(req, list);                              // (3) 0.1373
/*14 */     qemu_co_queue_restart_all(&req->wait_queue);          // (0) 0.2157
/*16 */ }                                                         // (7) 0.009804
