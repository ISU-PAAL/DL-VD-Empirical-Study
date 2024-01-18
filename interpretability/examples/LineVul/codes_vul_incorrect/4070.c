// commit message FFmpeg@969267482d (target=1, prob=0.40805462, correct=False): ffmpeg: Allocate new buffer for bitstream filter when buffer shifted
/*0   */ static void write_frame(AVFormatContext *s, AVPacket *pkt, OutputStream *ost)                                                                          // (10) 0.04688
/*2   */ {                                                                                                                                                      // (18) 0.001953
/*4   */     AVBitStreamFilterContext *bsfc = ost->bitstream_filters;                                                                                           // (12) 0.03906
/*6   */     AVCodecContext          *avctx = ost->st->codec;                                                                                                   // (6) 0.05273
/*8   */     int ret;                                                                                                                                           // (16) 0.01172
/*12  */     if ((avctx->codec_type == AVMEDIA_TYPE_VIDEO && video_sync_method == VSYNC_DROP) ||                                                                // (4) 0.06836
/*14  */         (avctx->codec_type == AVMEDIA_TYPE_AUDIO && audio_sync_method < 0))                                                                            // (5) 0.06445
/*16  */         pkt->pts = pkt->dts = AV_NOPTS_VALUE;                                                                                                          // (7) 0.05273
/*20  */     if (avctx->codec_type == AVMEDIA_TYPE_AUDIO && pkt->dts != AV_NOPTS_VALUE) {                                                                       // (3) 0.07226
/*22  */         int64_t max = ost->st->cur_dts + !(s->oformat->flags & AVFMT_TS_NONSTRICT);                                                                    // (2) 0.08203
/*24  */         if (ost->st->cur_dts && ost->st->cur_dts != AV_NOPTS_VALUE &&  max > pkt->dts) {                                                               // (1) 0.08789
/*26  */             av_log(s, max - pkt->dts > 2 ? AV_LOG_WARNING : AV_LOG_DEBUG, "Audio timestamp %"PRId64" < %"PRId64" invalid, cliping\n", pkt->dts, max);  // (0) 0.1367
/*28  */             pkt->pts = pkt->dts = max;                                                                                                                 // (8) 0.04883
/*34  */     /*                                                                                                                                                 // (17) 0.007813
/*36  */      * Audio encoders may split the packets --  #frames in != #packets out.                                                                            // (9) 0.04688
/*38  */      * But there is no reordering, so we can limit the number of output packets                                                                        // (11) 0.04102
/*40  */      * by simply dropping them here.                                                                                                                   // (15) 0.02148
/*42  */      * Counting encoded video frames needs to be done separately because of                                                                            // (13) 0.0332
/*44  */      * reordering, see do_video_out()                                                                                                                  // (14) 0.0293
/*46  */      */                                                                                                                                                // 0.0
/*48  */     if (!(avctx->codec_type == AVMEDIA_TYPE_VIDEO && avctx->codec)) {                                                                                  // 0.0
/*50  */         if (ost->frame_number >= ost->max_frames) {                                                                                                    // 0.0
/*52  */             av_free_packet(pkt);                                                                                                                       // 0.0
/*54  */             return;                                                                                                                                    // 0.0
/*57  */         ost->frame_number++;                                                                                                                           // 0.0
/*62  */     while (bsfc) {                                                                                                                                     // 0.0
/*64  */         AVPacket new_pkt = *pkt;                                                                                                                       // 0.0
/*66  */         int a = av_bitstream_filter_filter(bsfc, avctx, NULL,                                                                                          // 0.0
/*68  */                                            &new_pkt.data, &new_pkt.size,                                                                               // 0.0
/*70  */                                            pkt->data, pkt->size,                                                                                       // 0.0
/*72  */                                            pkt->flags & AV_PKT_FLAG_KEY);                                                                              // 0.0
/*84  */         if (a > 0) {                                                                                                                                   // 0.0
/*86  */             av_free_packet(pkt);                                                                                                                       // 0.0
/*88  */             new_pkt.destruct = av_destruct_packet;                                                                                                     // 0.0
/*90  */         } else if (a < 0) {                                                                                                                            // 0.0
/*92  */             av_log(NULL, AV_LOG_ERROR, "Failed to open bitstream filter %s for stream %d with codec %s",                                               // 0.0
/*94  */                    bsfc->filter->name, pkt->stream_index,                                                                                              // 0.0
/*96  */                    avctx->codec ? avctx->codec->name : "copy");                                                                                        // 0.0
/*98  */             print_error("", a);                                                                                                                        // 0.0
/*100 */             if (exit_on_error)                                                                                                                         // 0.0
/*102 */                 exit_program(1);                                                                                                                       // 0.0
/*105 */         *pkt = new_pkt;                                                                                                                                // 0.0
/*109 */         bsfc = bsfc->next;                                                                                                                             // 0.0
/*114 */     pkt->stream_index = ost->index;                                                                                                                    // 0.0
/*116 */     ret = av_interleaved_write_frame(s, pkt);                                                                                                          // 0.0
/*118 */     if (ret < 0) {                                                                                                                                     // 0.0
/*120 */         print_error("av_interleaved_write_frame()", ret);                                                                                              // 0.0
/*122 */         exit_program(1);                                                                                                                               // 0.0
