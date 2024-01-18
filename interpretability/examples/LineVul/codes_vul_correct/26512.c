// commit message FFmpeg@44d854a518 (target=1, prob=0.9992611, correct=True): atrac3: return an error if extradata_size is not a specific known size
/*0   */ static av_cold int atrac3_decode_init(AVCodecContext *avctx)                      // (9) 0.043
/*2   */ {                                                                                 // (19) 0.001955
/*4   */     int i, ret;                                                                   // (17) 0.01563
/*6   */     int version, delay, samples_per_frame, frame_factor;                          // (12) 0.0352
/*8   */     const uint8_t *edata_ptr = avctx->extradata;                                  // (11) 0.04101
/*10  */     ATRAC3Context *q = avctx->priv_data;                                          // (13) 0.03515
/*14  */     if (avctx->channels <= 0 || avctx->channels > 2) {                            // (10) 0.04297
/*16  */         av_log(avctx, AV_LOG_ERROR, "Channel configuration error!\n");            // (8) 0.05468
/*19  */     }                                                                             // (18) 0.007812
/*23  */     /* Take care of the codec-specific extradata. */                              // (16) 0.02929
/*25  */     if (avctx->extradata_size == 14) {                                            // (15) 0.0332
/*27  */         /* Parse the extradata, WAV format */                                     // (14) 0.03515
/*29  */         av_log(avctx, AV_LOG_DEBUG, "[0-1] %d\n",                                 // (5) 0.05859
/*31  */                bytestream_get_le16(&edata_ptr));  // Unknown value always 1       // (2) 0.0664
/*33  */         edata_ptr += 4;                             // samples per channel        // (0) 0.08983
/*35  */         q->coding_mode = bytestream_get_le16(&edata_ptr);                         // (7) 0.05468
/*37  */         av_log(avctx, AV_LOG_DEBUG,"[8-9] %d\n",                                  // (6) 0.05859
/*39  */                bytestream_get_le16(&edata_ptr));  //Dupe of coding mode           // (1) 0.06835
/*41  */         frame_factor = bytestream_get_le16(&edata_ptr);  // Unknown always 1      // (3) 0.05859
/*43  */         av_log(avctx, AV_LOG_DEBUG,"[12-13] %d\n",                                // (4) 0.05859
/*45  */                bytestream_get_le16(&edata_ptr));  // Unknown always 0             // 0.0
/*49  */         /* setup */                                                               // 0.0
/*51  */         samples_per_frame    = SAMPLES_PER_FRAME * avctx->channels;               // 0.0
/*53  */         version              = 4;                                                 // 0.0
/*55  */         delay                = 0x88E;                                             // 0.0
/*57  */         q->coding_mode       = q->coding_mode ? JOINT_STEREO : STEREO;            // 0.0
/*59  */         q->scrambled_stream  = 0;                                                 // 0.0
/*63  */         if (avctx->block_align !=  96 * avctx->channels * frame_factor &&         // 0.0
/*65  */             avctx->block_align != 152 * avctx->channels * frame_factor &&         // 0.0
/*67  */             avctx->block_align != 192 * avctx->channels * frame_factor) {         // 0.0
/*69  */             av_log(avctx, AV_LOG_ERROR, "Unknown frame/channel/frame_factor "     // 0.0
/*71  */                    "configuration %d/%d/%d\n", avctx->block_align,                // 0.0
/*73  */                    avctx->channels, frame_factor);                                // 0.0
/*75  */             return AVERROR_INVALIDDATA;                                           // 0.0
/*77  */         }                                                                         // 0.0
/*79  */     } else if (avctx->extradata_size == 10) {                                     // 0.0
/*81  */         /* Parse the extradata, RM format. */                                     // 0.0
/*83  */         version                = bytestream_get_be32(&edata_ptr);                 // 0.0
/*85  */         samples_per_frame      = bytestream_get_be16(&edata_ptr);                 // 0.0
/*87  */         delay                  = bytestream_get_be16(&edata_ptr);                 // 0.0
/*89  */         q->coding_mode         = bytestream_get_be16(&edata_ptr);                 // 0.0
/*91  */         q->scrambled_stream    = 1;                                               // 0.0
/*95  */     } else {                                                                      // 0.0
/*97  */         av_log(NULL, AV_LOG_ERROR, "Unknown extradata size %d.\n",                // 0.0
/*99  */                avctx->extradata_size);                                            // 0.0
/*102 */     }                                                                             // 0.0
/*106 */     /* Check the extradata */                                                     // 0.0
/*110 */     if (version != 4) {                                                           // 0.0
/*112 */         av_log(avctx, AV_LOG_ERROR, "Version %d != 4.\n", version);               // 0.0
/*114 */         return AVERROR_INVALIDDATA;                                               // 0.0
/*116 */     }                                                                             // 0.0
/*120 */     if (samples_per_frame != SAMPLES_PER_FRAME &&                                 // 0.0
/*122 */         samples_per_frame != SAMPLES_PER_FRAME * 2) {                             // 0.0
/*124 */         av_log(avctx, AV_LOG_ERROR, "Unknown amount of samples per frame %d.\n",  // 0.0
/*126 */                samples_per_frame);                                                // 0.0
/*128 */         return AVERROR_INVALIDDATA;                                               // 0.0
/*130 */     }                                                                             // 0.0
/*134 */     if (delay != 0x88E) {                                                         // 0.0
/*136 */         av_log(avctx, AV_LOG_ERROR, "Unknown amount of delay %x != 0x88E.\n",     // 0.0
/*138 */                delay);                                                            // 0.0
/*140 */         return AVERROR_INVALIDDATA;                                               // 0.0
/*142 */     }                                                                             // 0.0
/*146 */     if (q->coding_mode == STEREO)                                                 // 0.0
/*148 */         av_log(avctx, AV_LOG_DEBUG, "Normal stereo detected.\n");                 // 0.0
/*150 */     else if (q->coding_mode == JOINT_STEREO)                                      // 0.0
/*152 */         av_log(avctx, AV_LOG_DEBUG, "Joint stereo detected.\n");                  // 0.0
/*154 */     else {                                                                        // 0.0
/*156 */         av_log(avctx, AV_LOG_ERROR, "Unknown channel coding mode %x!\n",          // 0.0
/*158 */                q->coding_mode);                                                   // 0.0
/*160 */         return AVERROR_INVALIDDATA;                                               // 0.0
/*162 */     }                                                                             // 0.0
/*166 */     if (avctx->block_align >= UINT_MAX / 2)                                       // 0.0
/*171 */     q->decoded_bytes_buffer = av_mallocz(FFALIGN(avctx->block_align, 4) +         // 0.0
/*173 */                                          FF_INPUT_BUFFER_PADDING_SIZE);           // 0.0
/*175 */     if (q->decoded_bytes_buffer == NULL)                                          // 0.0
/*177 */         return AVERROR(ENOMEM);                                                   // 0.0
/*181 */     avctx->sample_fmt = AV_SAMPLE_FMT_FLTP;                                       // 0.0
/*185 */     /* initialize the MDCT transform */                                           // 0.0
/*187 */     if ((ret = ff_mdct_init(&q->mdct_ctx, 9, 1, 1.0 / 32768)) < 0) {              // 0.0
/*189 */         av_log(avctx, AV_LOG_ERROR, "Error initializing MDCT\n");                 // 0.0
/*191 */         av_freep(&q->decoded_bytes_buffer);                                       // 0.0
/*193 */         return ret;                                                               // 0.0
/*195 */     }                                                                             // 0.0
/*199 */     /* init the joint-stereo decoding data */                                     // 0.0
/*201 */     q->weighting_delay[0] = 0;                                                    // 0.0
/*203 */     q->weighting_delay[1] = 7;                                                    // 0.0
/*205 */     q->weighting_delay[2] = 0;                                                    // 0.0
/*207 */     q->weighting_delay[3] = 7;                                                    // 0.0
/*209 */     q->weighting_delay[4] = 0;                                                    // 0.0
/*211 */     q->weighting_delay[5] = 7;                                                    // 0.0
/*215 */     for (i = 0; i < 4; i++) {                                                     // 0.0
/*217 */         q->matrix_coeff_index_prev[i] = 3;                                        // 0.0
/*219 */         q->matrix_coeff_index_now[i]  = 3;                                        // 0.0
/*221 */         q->matrix_coeff_index_next[i] = 3;                                        // 0.0
/*223 */     }                                                                             // 0.0
/*227 */     avpriv_float_dsp_init(&q->fdsp, avctx->flags & CODEC_FLAG_BITEXACT);          // 0.0
/*229 */     ff_fmt_convert_init(&q->fmt_conv, avctx);                                     // 0.0
/*233 */     q->units = av_mallocz(sizeof(*q->units) * avctx->channels);                   // 0.0
/*235 */     if (!q->units) {                                                              // 0.0
/*237 */         atrac3_decode_close(avctx);                                               // 0.0
/*239 */         return AVERROR(ENOMEM);                                                   // 0.0
/*241 */     }                                                                             // 0.0
/*245 */     avcodec_get_frame_defaults(&q->frame);                                        // 0.0
/*247 */     avctx->coded_frame = &q->frame;                                               // 0.0
/*251 */     return 0;                                                                     // 0.0
/*253 */ }                                                                                 // 0.0
