// commit message FFmpeg@de6df46120 (target=1, prob=0.9990829, correct=True): avcodec/h264: Setup decoder to have matching reference to the EC code
/*0  */ int ff_h264_field_end(H264Context *h, int in_setup)                            // (12) 0.04102
/*1  */ {                                                                              // (22) 0.001953
/*2  */     AVCodecContext *const avctx = h->avctx;                                    // (14) 0.0332
/*3  */     int err = 0;                                                               // (18) 0.01562
/*4  */     h->mb_y = 0;                                                               // (17) 0.02148
/*5  */     if (CONFIG_H264_VDPAU_DECODER &&                                           // (13) 0.03711
/*6  */         h->avctx->codec->capabilities & CODEC_CAP_HWACCEL_VDPAU)               // (2) 0.06445
/*7  */         ff_vdpau_h264_set_reference_frames(h);                                 // (10) 0.04688
/*8  */     if (in_setup || !(avctx->active_thread_type & FF_THREAD_FRAME)) {          // (4) 0.05664
/*9  */         if (!h->droppable) {                                                   // (15) 0.03125
/*10 */             err = ff_h264_execute_ref_pic_marking(h, h->mmco, h->mmco_index);  // (0) 0.08008
/*11 */             h->prev_poc_msb = h->poc_msb;                                      // (6) 0.05664
/*12 */             h->prev_poc_lsb = h->poc_lsb;                                      // (5) 0.05664
/*13 */         }                                                                      // (19) 0.01562
/*14 */         h->prev_frame_num_offset = h->frame_num_offset;                        // (9) 0.04883
/*15 */         h->prev_frame_num        = h->frame_num;                               // (7) 0.05469
/*16 */         h->outputed_poc          = h->next_outputed_poc;                       // (1) 0.06641
/*17 */     }                                                                          // (21) 0.007812
/*18 */     if (avctx->hwaccel) {                                                      // (16) 0.02539
/*19 */         if (avctx->hwaccel->end_frame(avctx) < 0)                              // (8) 0.05078
/*20 */             av_log(avctx, AV_LOG_ERROR,                                        // (11) 0.04687
/*21 */                    "hardware accelerator failed to decode picture\n");         // (3) 0.05664
/*22 */     }                                                                          // (20) 0.007812
/*23 */     if (CONFIG_H264_VDPAU_DECODER &&                                           // 0.0
/*24 */         h->avctx->codec->capabilities & CODEC_CAP_HWACCEL_VDPAU)               // 0.0
/*25 */         ff_vdpau_h264_picture_complete(h);                                     // 0.0
/*26 */ #if CONFIG_ERROR_RESILIENCE                                                    // 0.0
/*27 */     /*                                                                         // 0.0
/*28 */      * FIXME: Error handling code does not seem to support interlaced          // 0.0
/*29 */      * when slices span multiple rows                                          // 0.0
/*30 */      * The ff_er_add_slice calls don't work right for bottom                   // 0.0
/*31 */      * fields; they cause massive erroneous error concealing                   // 0.0
/*32 */      * Error marking covers both fields (top and bottom).                      // 0.0
/*33 */      * This causes a mismatched s->error_count                                 // 0.0
/*34 */      * and a bad error table. Further, the error count goes to                 // 0.0
/*35 */      * INT_MAX when called for bottom field, because mb_y is                   // 0.0
/*36 */      * past end by one (callers fault) and resync_mb_y != 0                    // 0.0
/*37 */      * causes problems for the first MB line, too.                             // 0.0
/*38 */      */                                                                        // 0.0
/*39 */     if (!FIELD_PICTURE(h) && h->current_slice && !h->sps.new) {                // 0.0
/*40 */         ff_h264_set_erpic(&h->er.cur_pic, h->cur_pic_ptr);                     // 0.0
/*41 */         ff_er_frame_end(&h->er);                                               // 0.0
/*42 */     }                                                                          // 0.0
/*43 */ #endif /* CONFIG_ERROR_RESILIENCE */                                           // 0.0
/*44 */     if (!in_setup && !h->droppable)                                            // 0.0
/*45 */         ff_thread_report_progress(&h->cur_pic_ptr->tf, INT_MAX,                // 0.0
/*46 */                                   h->picture_structure == PICT_BOTTOM_FIELD);  // 0.0
/*47 */     emms_c();                                                                  // 0.0
/*48 */     h->current_slice = 0;                                                      // 0.0
/*49 */     return err;                                                                // 0.0
/*50 */ }                                                                              // 0.0
