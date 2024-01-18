// commit message FFmpeg@3dea28cc2e (target=0, prob=0.4521333, correct=True): h264: Fix concealment regression introduced by babf4fe01a808327d53977ba319c113a930180b1 Limit the new case to when the decoder is flushed instead of at each idr frame
/*0  */ static void idr(H264Context *h){                 // (7) 0.07006
/*2  */     int i;                                       // (8) 0.03822
/*4  */     ff_h264_remove_all_refs(h);                  // (2) 0.1083
/*6  */     h->prev_frame_num= -1;                       // (6) 0.08917
/*8  */     h->prev_frame_num_offset= 0;                 // (4) 0.09554
/*10 */     h->prev_poc_msb= 1<<16;                      // (3) 0.1083
/*12 */     h->prev_poc_lsb= 0;                          // (5) 0.09554
/*14 */     for (i = 0; i < MAX_DELAYED_PIC_COUNT; i++)  // (0) 0.1656
/*16 */         h->last_pocs[i] = INT_MIN;               // (1) 0.1401
/*18 */ }                                                // (9) 0.006369
