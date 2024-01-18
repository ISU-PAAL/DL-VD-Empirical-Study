// commit message FFmpeg@5602a464c9 (target=0, prob=0.6699174, correct=False): avcodec: add a Vorbis parser to get packet duration
/*0   */ static av_cold int vorbis_decode_init(AVCodecContext *avccontext)                                     // (7) 0.04688
/*2   */ {                                                                                                     // (26) 0.001953
/*4   */     vorbis_context *vc = avccontext->priv_data;                                                       // (12) 0.03906
/*6   */     uint8_t *headers   = avccontext->extradata;                                                       // (9) 0.04102
/*8   */     int headers_len    = avccontext->extradata_size;                                                  // (8) 0.04297
/*10  */     uint8_t *header_start[3];                                                                         // (17) 0.02734
/*12  */     int header_len[3];                                                                                // (20) 0.01953
/*14  */     GetBitContext *gb = &vc->gb;                                                                      // (16) 0.02734
/*16  */     int hdr_type, ret;                                                                                // (18) 0.02149
/*20  */     vc->avccontext = avccontext;                                                                      // (15) 0.03125
/*22  */     ff_dsputil_init(&vc->dsp, avccontext);                                                            // (10) 0.04102
/*24  */     ff_fmt_convert_init(&vc->fmt_conv, avccontext);                                                   // (6) 0.04883
/*28  */     if (avccontext->request_sample_fmt == AV_SAMPLE_FMT_FLT) {                                        // (3) 0.05664
/*30  */         avccontext->sample_fmt = AV_SAMPLE_FMT_FLT;                                                   // (5) 0.05469
/*32  */         vc->scale_bias = 1.0f;                                                                        // (13) 0.03906
/*34  */     } else {                                                                                          // (22) 0.01172
/*36  */         avccontext->sample_fmt = AV_SAMPLE_FMT_S16;                                                   // (4) 0.05469
/*38  */         vc->scale_bias = 32768.0f;                                                                    // (11) 0.04102
/*40  */     }                                                                                                 // (25) 0.007812
/*44  */     if (!headers_len) {                                                                               // (21) 0.01953
/*46  */         av_log(avccontext, AV_LOG_ERROR, "Extradata missing.\n");                                     // (1) 0.06055
/*48  */         return AVERROR_INVALIDDATA;                                                                   // (14) 0.0332
/*50  */     }                                                                                                 // (24) 0.007812
/*54  */     if ((ret = avpriv_split_xiph_headers(headers, headers_len, 30, header_start, header_len)) < 0) {  // (0) 0.07227
/*56  */         av_log(avccontext, AV_LOG_ERROR, "Extradata corrupt.\n");                                     // (2) 0.06055
/*58  */         return ret;                                                                                   // (19) 0.01953
/*60  */     }                                                                                                 // (23) 0.007812
/*64  */     init_get_bits(gb, header_start[0], header_len[0]*8);                                              // 0.0
/*66  */     hdr_type = get_bits(gb, 8);                                                                       // 0.0
/*68  */     if (hdr_type != 1) {                                                                              // 0.0
/*70  */         av_log(avccontext, AV_LOG_ERROR, "First header is not the id header.\n");                     // 0.0
/*72  */         return AVERROR_INVALIDDATA;                                                                   // 0.0
/*74  */     }                                                                                                 // 0.0
/*76  */     if ((ret = vorbis_parse_id_hdr(vc))) {                                                            // 0.0
/*78  */         av_log(avccontext, AV_LOG_ERROR, "Id header corrupt.\n");                                     // 0.0
/*80  */         vorbis_free(vc);                                                                              // 0.0
/*82  */         return ret;                                                                                   // 0.0
/*84  */     }                                                                                                 // 0.0
/*88  */     init_get_bits(gb, header_start[2], header_len[2]*8);                                              // 0.0
/*90  */     hdr_type = get_bits(gb, 8);                                                                       // 0.0
/*92  */     if (hdr_type != 5) {                                                                              // 0.0
/*94  */         av_log(avccontext, AV_LOG_ERROR, "Third header is not the setup header.\n");                  // 0.0
/*96  */         vorbis_free(vc);                                                                              // 0.0
/*98  */         return AVERROR_INVALIDDATA;                                                                   // 0.0
/*100 */     }                                                                                                 // 0.0
/*102 */     if ((ret = vorbis_parse_setup_hdr(vc))) {                                                         // 0.0
/*104 */         av_log(avccontext, AV_LOG_ERROR, "Setup header corrupt.\n");                                  // 0.0
/*106 */         vorbis_free(vc);                                                                              // 0.0
/*108 */         return ret;                                                                                   // 0.0
/*110 */     }                                                                                                 // 0.0
/*114 */     if (vc->audio_channels > 8)                                                                       // 0.0
/*116 */         avccontext->channel_layout = 0;                                                               // 0.0
/*118 */     else                                                                                              // 0.0
/*120 */         avccontext->channel_layout = ff_vorbis_channel_layouts[vc->audio_channels - 1];               // 0.0
/*124 */     avccontext->channels    = vc->audio_channels;                                                     // 0.0
/*126 */     avccontext->sample_rate = vc->audio_samplerate;                                                   // 0.0
/*128 */     avccontext->frame_size  = FFMIN(vc->blocksize[0], vc->blocksize[1]) >> 2;                         // 0.0
/*132 */     avcodec_get_frame_defaults(&vc->frame);                                                           // 0.0
/*134 */     avccontext->coded_frame = &vc->frame;                                                             // 0.0
/*138 */     return 0;                                                                                         // 0.0
/*140 */ }                                                                                                     // 0.0
