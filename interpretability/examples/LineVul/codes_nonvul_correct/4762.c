// commit message FFmpeg@7631f14bb3 (target=0, prob=0.37913, correct=True): avformat/matroskaenc: check packet side data for AAC extradata updates
/*0   */ static int mkv_write_codecprivate(AVFormatContext *s, AVIOContext *pb,                                                              // (6) 0.04492
/*2   */                                   AVCodecParameters *par,                                                                           // (4) 0.07813
/*4   */                                   int native_id, int qt_id)                                                                         // (2) 0.08594
/*6   */ {                                                                                                                                   // (17) 0.001953
/*8   */     AVIOContext *dyn_cp;                                                                                                            // (12) 0.02344
/*10  */     uint8_t *codecpriv;                                                                                                             // (11) 0.02344
/*12  */     int ret, codecpriv_size;                                                                                                        // (13) 0.02148
/*16  */     ret = avio_open_dyn_buf(&dyn_cp);                                                                                               // (8) 0.03906
/*18  */     if (ret < 0)                                                                                                                    // (16) 0.01758
/*20  */         return ret;                                                                                                                 // (14) 0.01953
/*24  */     if (native_id) {                                                                                                                // (15) 0.01953
/*26  */         ret = mkv_write_native_codecprivate(s, par, dyn_cp);                                                                        // (5) 0.05469
/*28  */     } else if (par->codec_type == AVMEDIA_TYPE_VIDEO) {                                                                             // (7) 0.04492
/*30  */         if (qt_id) {                                                                                                                // (10) 0.02734
/*32  */             if (!par->codec_tag)                                                                                                    // (9) 0.03906
/*34  */                 par->codec_tag = ff_codec_get_tag(ff_codec_movvideo_tags,                                                           // (3) 0.08203
/*36  */                                                     par->codec_id);                                                                 // (0) 0.1133
/*38  */             if (   ff_codec_get_id(ff_codec_movvideo_tags, par->codec_tag) == par->codec_id                                         // (1) 0.0957
/*40  */                 && (!par->extradata_size || ff_codec_get_id(ff_codec_movvideo_tags, AV_RL32(par->extradata + 4)) != par->codec_id)  // 0.0
/*42  */             ) {                                                                                                                     // 0.0
/*44  */                 int i;                                                                                                              // 0.0
/*46  */                 avio_wb32(dyn_cp, 0x5a + par->extradata_size);                                                                      // 0.0
/*48  */                 avio_wl32(dyn_cp, par->codec_tag);                                                                                  // 0.0
/*50  */                 for(i = 0; i < 0x5a - 8; i++)                                                                                       // 0.0
/*52  */                     avio_w8(dyn_cp, 0);                                                                                             // 0.0
/*54  */             }                                                                                                                       // 0.0
/*56  */             avio_write(dyn_cp, par->extradata, par->extradata_size);                                                                // 0.0
/*58  */         } else {                                                                                                                    // 0.0
/*60  */             if (!ff_codec_get_tag(ff_codec_bmp_tags, par->codec_id))                                                                // 0.0
/*62  */                 av_log(s, AV_LOG_WARNING, "codec %s is not supported by this format\n",                                             // 0.0
/*64  */                        avcodec_get_name(par->codec_id));                                                                            // 0.0
/*68  */             if (!par->codec_tag)                                                                                                    // 0.0
/*70  */                 par->codec_tag = ff_codec_get_tag(ff_codec_bmp_tags,                                                                // 0.0
/*72  */                                                   par->codec_id);                                                                   // 0.0
/*74  */             if (!par->codec_tag && par->codec_id != AV_CODEC_ID_RAWVIDEO) {                                                         // 0.0
/*76  */                 av_log(s, AV_LOG_ERROR, "No bmp codec tag found for codec %s\n",                                                    // 0.0
/*78  */                        avcodec_get_name(par->codec_id));                                                                            // 0.0
/*80  */                 ret = AVERROR(EINVAL);                                                                                              // 0.0
/*82  */             }                                                                                                                       // 0.0
/*86  */             ff_put_bmp_header(dyn_cp, par, ff_codec_bmp_tags, 0, 0);                                                                // 0.0
/*88  */         }                                                                                                                           // 0.0
/*90  */     } else if (par->codec_type == AVMEDIA_TYPE_AUDIO) {                                                                             // 0.0
/*92  */         unsigned int tag;                                                                                                           // 0.0
/*94  */         tag = ff_codec_get_tag(ff_codec_wav_tags, par->codec_id);                                                                   // 0.0
/*96  */         if (!tag) {                                                                                                                 // 0.0
/*98  */             av_log(s, AV_LOG_ERROR, "No wav codec tag found for codec %s\n",                                                        // 0.0
/*100 */                    avcodec_get_name(par->codec_id));                                                                                // 0.0
/*102 */             ret = AVERROR(EINVAL);                                                                                                  // 0.0
/*104 */         }                                                                                                                           // 0.0
/*106 */         if (!par->codec_tag)                                                                                                        // 0.0
/*108 */             par->codec_tag = tag;                                                                                                   // 0.0
/*112 */         ff_put_wav_header(s, dyn_cp, par, FF_PUT_WAV_HEADER_FORCE_WAVEFORMATEX);                                                    // 0.0
/*114 */     }                                                                                                                               // 0.0
/*118 */     codecpriv_size = avio_close_dyn_buf(dyn_cp, &codecpriv);                                                                        // 0.0
/*120 */     if (codecpriv_size)                                                                                                             // 0.0
/*122 */         put_ebml_binary(pb, MATROSKA_ID_CODECPRIVATE, codecpriv,                                                                    // 0.0
/*124 */                         codecpriv_size);                                                                                            // 0.0
/*126 */     av_free(codecpriv);                                                                                                             // 0.0
/*128 */     return ret;                                                                                                                     // 0.0
/*130 */ }                                                                                                                                   // 0.0
