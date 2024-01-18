// commit message FFmpeg@14a90c9ef0 (target=1, prob=0.99903345, correct=True): mmaldec: limit internal buffering
/*0  */ static av_cold int ffmmal_init_decoder(AVCodecContext *avctx)                                   // (5) 0.04298
/*1  */ {                                                                                               // (27) 0.001953
/*2  */     MMALDecodeContext *ctx = avctx->priv_data;                                                  // (9) 0.03516
/*3  */     MMAL_STATUS_T status;                                                                       // (20) 0.02344
/*4  */     MMAL_ES_FORMAT_T *format_in;                                                                // (11) 0.0332
/*5  */     MMAL_COMPONENT_T *decoder;                                                                  // (14) 0.03125
/*6  */     char tmp[32];                                                                               // (26) 0.01562
/*7  */     int ret = 0;                                                                                // (25) 0.01562
/*8  */     bcm_host_init();                                                                            // (22) 0.01953
/*9  */     if (mmal_vc_init()) {                                                                       // (17) 0.02539
/*10 */         av_log(avctx, AV_LOG_ERROR, "Cannot initialize MMAL VC driver!\n");                     // (1) 0.0625
/*11 */         return AVERROR(ENOSYS);                                                                 // (13) 0.03125
/*12 */     if ((ret = ff_get_format(avctx, avctx->codec->pix_fmts)) < 0)                               // (2) 0.06055
/*13 */         return ret;                                                                             // (24) 0.01953
/*14 */     avctx->pix_fmt = ret;                                                                       // (15) 0.02734
/*15 */     if ((status = mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_DECODER, &ctx->decoder)))  // (0) 0.07226
/*16 */         goto fail;                                                                              // (23) 0.01953
/*17 */     decoder = ctx->decoder;                                                                     // (21) 0.02344
/*18 */     format_in = decoder->input[0]->format;                                                      // (12) 0.0332
/*19 */     format_in->type = MMAL_ES_TYPE_VIDEO;                                                       // (10) 0.03516
/*20 */     switch (avctx->codec_id) {                                                                  // (16) 0.02734
/*21 */         case AV_CODEC_ID_MPEG2VIDEO:                                                            // (6) 0.04101
/*22 */             format_in->encoding = MMAL_ENCODING_MP2V;                                           // (4) 0.05664
/*23 */             break;                                                                              // (19) 0.02539
/*24 */         case AV_CODEC_ID_MPEG4:                                                                 // (7) 0.03906
/*25 */             format_in->encoding = MMAL_ENCODING_MP4V;                                           // (3) 0.05664
/*26 */             break;                                                                              // (18) 0.02539
/*27 */         case AV_CODEC_ID_VC1:                                                                   // (8) 0.03711
/*28 */             format_in->encoding = MMAL_ENCODING_WVC1;                                           // 0.0
/*29 */             break;                                                                              // 0.0
/*30 */         case AV_CODEC_ID_H264:                                                                  // 0.0
/*31 */         default:                                                                                // 0.0
/*32 */             format_in->encoding = MMAL_ENCODING_H264;                                           // 0.0
/*33 */             break;                                                                              // 0.0
/*34 */     format_in->es->video.width = FFALIGN(avctx->width, 32);                                     // 0.0
/*35 */     format_in->es->video.height = FFALIGN(avctx->height, 16);                                   // 0.0
/*36 */     format_in->es->video.crop.width = avctx->width;                                             // 0.0
/*37 */     format_in->es->video.crop.height = avctx->height;                                           // 0.0
/*38 */     format_in->es->video.frame_rate.num = 24000;                                                // 0.0
/*39 */     format_in->es->video.frame_rate.den = 1001;                                                 // 0.0
/*40 */     format_in->es->video.par.num = avctx->sample_aspect_ratio.num;                              // 0.0
/*41 */     format_in->es->video.par.den = avctx->sample_aspect_ratio.den;                              // 0.0
/*42 */     format_in->flags = MMAL_ES_FORMAT_FLAG_FRAMED;                                              // 0.0
/*43 */     av_get_codec_tag_string(tmp, sizeof(tmp), format_in->encoding);                             // 0.0
/*44 */     av_log(avctx, AV_LOG_DEBUG, "Using MMAL %s encoding.\n", tmp);                              // 0.0
/*45 */     if ((status = mmal_port_format_commit(decoder->input[0])))                                  // 0.0
/*46 */         goto fail;                                                                              // 0.0
/*47 */     decoder->input[0]->buffer_num =                                                             // 0.0
/*48 */         FFMAX(decoder->input[0]->buffer_num_min, 20);                                           // 0.0
/*49 */     decoder->input[0]->buffer_size =                                                            // 0.0
/*50 */         FFMAX(decoder->input[0]->buffer_size_min, 512 * 1024);                                  // 0.0
/*51 */     ctx->pool_in = mmal_pool_create(decoder->input[0]->buffer_num, 0);                          // 0.0
/*52 */     if (!ctx->pool_in) {                                                                        // 0.0
/*53 */         ret = AVERROR(ENOMEM);                                                                  // 0.0
/*54 */         goto fail;                                                                              // 0.0
/*55 */     if ((ret = ffmal_update_format(avctx)) < 0)                                                 // 0.0
/*56 */         goto fail;                                                                              // 0.0
/*57 */     ctx->queue_decoded_frames = mmal_queue_create();                                            // 0.0
/*58 */     if (!ctx->queue_decoded_frames)                                                             // 0.0
/*59 */         goto fail;                                                                              // 0.0
/*60 */     decoder->input[0]->userdata = (void*)avctx;                                                 // 0.0
/*61 */     decoder->output[0]->userdata = (void*)avctx;                                                // 0.0
/*62 */     decoder->control->userdata = (void*)avctx;                                                  // 0.0
/*63 */     if ((status = mmal_port_enable(decoder->control, control_port_cb)))                         // 0.0
/*64 */         goto fail;                                                                              // 0.0
/*65 */     if ((status = mmal_port_enable(decoder->input[0], input_callback)))                         // 0.0
/*66 */         goto fail;                                                                              // 0.0
/*67 */     if ((status = mmal_port_enable(decoder->output[0], output_callback)))                       // 0.0
/*68 */         goto fail;                                                                              // 0.0
/*69 */     if ((status = mmal_component_enable(decoder)))                                              // 0.0
/*70 */         goto fail;                                                                              // 0.0
/*71 */     return 0;                                                                                   // 0.0
/*72 */ fail:                                                                                           // 0.0
/*73 */     ffmmal_close_decoder(avctx);                                                                // 0.0
/*74 */     return ret < 0 ? ret : AVERROR_UNKNOWN;                                                     // 0.0
