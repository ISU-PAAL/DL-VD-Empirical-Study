// commit message FFmpeg@36583d23bd (target=0, prob=0.4523309, correct=True): audio_frame_que: simplify
/*0  */ void ff_af_queue_close(AudioFrameQueue *afq)  // (0) 0.1905
/*2  */ {                                             // (5) 0.01191
/*4  */     /* remove/free any remaining frames */    // (4) 0.131
/*6  */     while (afq->frame_queue)                  // (3) 0.1429
/*8  */         delete_next_frame(afq);               // (1) 0.1905
/*10 */     memset(afq, 0, sizeof(*afq));             // (2) 0.1905
/*12 */ }                                             // (6) 0.0119
