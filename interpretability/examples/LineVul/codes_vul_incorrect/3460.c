// commit message FFmpeg@f6774f905f (target=1, prob=0.3854479, correct=False): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0  */ static int vdpau_mpeg_start_frame(AVCodecContext *avctx,                   // (11) 0.03907
/*2  */                                   const uint8_t *buffer, uint32_t size)    // (0) 0.0918
/*4  */ {                                                                          // (23) 0.001954
/*6  */     MpegEncContext * const s = avctx->priv_data;                           // (12) 0.03516
/*8  */     Picture *pic             = s->current_picture_ptr;                     // (3) 0.05273
/*10 */     struct vdpau_picture_context *pic_ctx = pic->hwaccel_picture_private;  // (4) 0.05078
/*12 */     VdpPictureInfoMPEG1Or2 *info = &pic_ctx->info.mpeg;                    // (7) 0.04687
/*14 */     VdpVideoSurface ref;                                                   // (20) 0.01953
/*16 */     int i;                                                                 // (21) 0.01172
/*20 */     /* fill VdpPictureInfoMPEG1Or2 struct */                               // (13) 0.03125
/*22 */     info->forward_reference  = VDP_INVALID_HANDLE;                         // (10) 0.04102
/*24 */     info->backward_reference = VDP_INVALID_HANDLE;                         // (9) 0.04102
/*28 */     switch (s->pict_type) {                                                // (19) 0.02344
/*30 */     case AV_PICTURE_TYPE_B:                                                // (17) 0.02734
/*32 */         ref = ff_vdpau_get_surface_id(&s->next_picture.f);                 // (1) 0.05664
/*34 */         assert(ref != VDP_INVALID_HANDLE);                                 // (8) 0.04297
/*36 */         info->backward_reference = ref;                                    // (15) 0.03125
/*38 */         /* fall through to forward prediction */                           // (16) 0.02734
/*40 */     case AV_PICTURE_TYPE_P:                                                // (18) 0.02734
/*42 */         ref = ff_vdpau_get_surface_id(&s->last_picture.f);                 // (2) 0.05664
/*44 */         info->forward_reference  = ref;                                    // (14) 0.03125
/*46 */     }                                                                      // (22) 0.007812
/*50 */     info->slice_count                = 0;                                  // (5) 0.05078
/*52 */     info->picture_structure          = s->picture_structure;               // (6) 0.05078
/*54 */     info->picture_coding_type        = s->pict_type;                       // 0.0
/*56 */     info->intra_dc_precision         = s->intra_dc_precision;              // 0.0
/*58 */     info->frame_pred_frame_dct       = s->frame_pred_frame_dct;            // 0.0
/*60 */     info->concealment_motion_vectors = s->concealment_motion_vectors;      // 0.0
/*62 */     info->intra_vlc_format           = s->intra_vlc_format;                // 0.0
/*64 */     info->alternate_scan             = s->alternate_scan;                  // 0.0
/*66 */     info->q_scale_type               = s->q_scale_type;                    // 0.0
/*68 */     info->top_field_first            = s->top_field_first;                 // 0.0
/*70 */     // Both for MPEG-1 only, zero for MPEG-2:                              // 0.0
/*72 */     info->full_pel_forward_vector    = s->full_pel[0];                     // 0.0
/*74 */     info->full_pel_backward_vector   = s->full_pel[1];                     // 0.0
/*76 */     // For MPEG-1 fill both horizontal & vertical:                         // 0.0
/*78 */     info->f_code[0][0]               = s->mpeg_f_code[0][0];               // 0.0
/*80 */     info->f_code[0][1]               = s->mpeg_f_code[0][1];               // 0.0
/*82 */     info->f_code[1][0]               = s->mpeg_f_code[1][0];               // 0.0
/*84 */     info->f_code[1][1]               = s->mpeg_f_code[1][1];               // 0.0
/*86 */     for (i = 0; i < 64; ++i) {                                             // 0.0
/*88 */         info->intra_quantizer_matrix[i]     = s->intra_matrix[i];          // 0.0
/*90 */         info->non_intra_quantizer_matrix[i] = s->inter_matrix[i];          // 0.0
/*92 */     }                                                                      // 0.0
/*96 */     return ff_vdpau_common_start_frame(pic_ctx, buffer, size);             // 0.0
/*98 */ }                                                                          // 0.0
