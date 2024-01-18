// commit message qemu@72cf2d4f0e (target=0, prob=0.07551802, correct=True): Fix sys-queue.h conflict for good
/*0  */ static void blk_send_response_all(struct XenBlkDev *blkdev)  // (1) 0.1273
/*2  */ {                                                            // (10) 0.006061
/*4  */     struct ioreq *ioreq;                                     // (5) 0.07273
/*6  */     int send_notify = 0;                                     // (7) 0.06667
/*10 */     while (!LIST_EMPTY(&blkdev->finished)) {                 // (4) 0.103
/*12 */         ioreq = LIST_FIRST(&blkdev->finished);               // (0) 0.1333
/*14 */ 	send_notify += blk_send_response_one(ioreq);                // (3) 0.1152
/*16 */ 	ioreq_release(ioreq);                                       // (6) 0.06667
/*18 */     }                                                        // (9) 0.02424
/*20 */     if (send_notify)                                         // (8) 0.06061
/*22 */ 	xen_be_send_notify(&blkdev->xendev);                        // (2) 0.1152
/*24 */ }                                                            // (11) 0.006061
