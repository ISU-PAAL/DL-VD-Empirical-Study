// commit message FFmpeg@7a4f74eed5 (target=0, prob=0.42273173, correct=True): h264: embed the DPB in the context
/*0  */ av_cold void ff_h264_free_context(H264Context *h)     // (8) 0.05689
/*2  */ {                                                     // (17) 0.002994
/*4  */     int i;                                            // (15) 0.01796
/*8  */     ff_h264_free_tables(h);                           // (10) 0.04491
/*12 */     if (h->DPB) {                                     // (14) 0.03293
/*14 */         for (i = 0; i < H264_MAX_PICTURE_COUNT; i++)  // (1) 0.08683
/*16 */             ff_h264_unref_picture(h, &h->DPB[i]);     // (0) 0.09281
/*18 */         av_freep(&h->DPB);                            // (9) 0.0509
/*20 */     }                                                 // (16) 0.01198
/*24 */     h->cur_pic_ptr = NULL;                            // (12) 0.03892
/*28 */     for (i = 0; i < h->nb_slice_ctx; i++)             // (4) 0.06287
/*30 */         av_freep(&h->slice_ctx[i].rbsp_buffer);       // (2) 0.07485
/*32 */     av_freep(&h->slice_ctx);                          // (11) 0.04192
/*34 */     h->nb_slice_ctx = 0;                              // (13) 0.03892
/*38 */     for (i = 0; i < MAX_SPS_COUNT; i++)               // (5) 0.06287
/*40 */         av_freep(h->sps_buffers + i);                 // (3) 0.06587
/*44 */     for (i = 0; i < MAX_PPS_COUNT; i++)               // (6) 0.06287
/*46 */         av_freep(h->pps_buffers + i);                 // (7) 0.06287
/*48 */ }                                                     // (18) 0.002994
