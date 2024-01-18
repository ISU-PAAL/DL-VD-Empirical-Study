// commit message FFmpeg@fd1588919d (target=1, prob=0.32981324, correct=False): avcodec/h264: remove list_count and ref_count clearing
/*0  */ void ff_h264_flush_change(H264Context *h)                 // (11) 0.03931
/*2  */ {                                                         // (22) 0.002457
/*4  */     int i, j;                                             // (19) 0.01966
/*8  */     h->next_outputed_poc = INT_MIN;                       // (9) 0.04177
/*10 */     h->prev_interlaced_frame = 1;                         // (12) 0.03686
/*12 */     idr(h);                                               // (20) 0.01966
/*16 */     h->poc.prev_frame_num = -1;                           // (10) 0.04177
/*18 */     if (h->cur_pic_ptr) {                                 // (13) 0.0344
/*20 */         h->cur_pic_ptr->reference = 0;                    // (6) 0.04668
/*22 */         for (j=i=0; h->delayed_pic[i]; i++)               // (3) 0.06388
/*24 */             if (h->delayed_pic[i] != h->cur_pic_ptr)      // (1) 0.07617
/*26 */                 h->delayed_pic[j++] = h->delayed_pic[i];  // (0) 0.086
/*28 */         h->delayed_pic[j] = NULL;                         // (7) 0.04668
/*30 */     }                                                     // (21) 0.009828
/*32 */     ff_h264_unref_picture(h, &h->last_pic_for_ec);        // (2) 0.06388
/*36 */     h->first_field = 0;                                   // (17) 0.02703
/*38 */     ff_h264_sei_uninit(&h->sei);                          // (8) 0.04177
/*40 */     h->recovery_frame = -1;                               // (14) 0.0344
/*42 */     h->frame_recovered = 0;                               // (15) 0.02948
/*44 */     h->current_slice = 0;                                 // (18) 0.02703
/*46 */     h->mmco_reset = 1;                                    // (16) 0.02948
/*48 */     for (i = 0; i < h->nb_slice_ctx; i++)                 // (4) 0.0516
/*50 */         h->slice_ctx[i].list_count = 0;                   // (5) 0.0516
/*52 */ }                                                         // (23) 0.002457
