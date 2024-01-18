// commit message FFmpeg@40cf1bbacc (target=0, prob=0.5332239, correct=False): Deprecate avctx.coded_frame
/*0   */ static int libschroedinger_encode_frame(AVCodecContext *avctx, AVPacket *pkt,                // (2) 0.05469
/*2   */                                         const AVFrame *frame, int *got_packet)               // (0) 0.1016
/*4   */ {                                                                                            // (27) 0.001953
/*6   */     int enc_size = 0;                                                                        // (19) 0.01953
/*8   */     SchroEncoderParams *p_schro_params = avctx->priv_data;                                   // (6) 0.04492
/*10  */     SchroEncoder *encoder = p_schro_params->encoder;                                         // (9) 0.03906
/*12  */     struct FFSchroEncodedFrame *p_frame_output = NULL;                                       // (8) 0.03906
/*14  */     int go = 1;                                                                              // (22) 0.01562
/*16  */     SchroBuffer *enc_buf;                                                                    // (18) 0.01953
/*18  */     int presentation_frame;                                                                  // (21) 0.01563
/*20  */     int parse_code;                                                                          // (20) 0.01566
/*22  */     int last_frame_in_sequence = 0;                                                          // (14) 0.02734
/*24  */     int pkt_size, ret;                                                                       // (17) 0.02148
/*28  */     if (!frame) {                                                                            // (23) 0.01562
/*30  */         /* Push end of sequence if not already signalled. */                                 // (11) 0.03711
/*32  */         if (!p_schro_params->eos_signalled) {                                                // (7) 0.04492
/*34  */             schro_encoder_end_of_stream(encoder);                                            // (3) 0.05078
/*36  */             p_schro_params->eos_signalled = 1;                                               // (4) 0.05078
/*38  */         }                                                                                    // (24) 0.01562
/*40  */     } else {                                                                                 // (25) 0.01172
/*42  */         /* Allocate frame data to schro input buffer. */                                     // (12) 0.03711
/*44  */         SchroFrame *in_frame = libschroedinger_frame_from_data(avctx, frame);                // (1) 0.06054
/*46  */         if (!in_frame)                                                                       // (16) 0.02539
/*48  */             return AVERROR(ENOMEM);                                                          // (10) 0.03906
/*50  */         /* Load next frame. */                                                               // (15) 0.02539
/*52  */         schro_encoder_push_frame(encoder, in_frame);                                         // (5) 0.04687
/*54  */     }                                                                                        // (26) 0.007812
/*58  */     if (p_schro_params->eos_pulled)                                                          // (13) 0.03515
/*60  */         go = 0;                                                                              // 0.0
/*64  */     /* Now check to see if we have any output from the encoder. */                           // 0.0
/*66  */     while (go) {                                                                             // 0.0
/*68  */         int err;                                                                             // 0.0
/*70  */         SchroStateEnum state;                                                                // 0.0
/*72  */         state = schro_encoder_wait(encoder);                                                 // 0.0
/*74  */         switch (state) {                                                                     // 0.0
/*76  */         case SCHRO_STATE_HAVE_BUFFER:                                                        // 0.0
/*78  */         case SCHRO_STATE_END_OF_STREAM:                                                      // 0.0
/*80  */             enc_buf = schro_encoder_pull(encoder, &presentation_frame);                      // 0.0
/*82  */             if (enc_buf->length <= 0)                                                        // 0.0
/*84  */                 return AVERROR_BUG;                                                          // 0.0
/*86  */             parse_code = enc_buf->data[4];                                                   // 0.0
/*90  */             /* All non-frame data is prepended to actual frame data to                       // 0.0
/*92  */              * be able to set the pts correctly. So we don't write data                      // 0.0
/*94  */              * to the frame output queue until we actually have a frame                      // 0.0
/*96  */              */                                                                              // 0.0
/*98  */             if ((err = av_reallocp(&p_schro_params->enc_buf,                                 // 0.0
/*100 */                                    p_schro_params->enc_buf_size +                            // 0.0
/*102 */                                    enc_buf->length)) < 0) {                                  // 0.0
/*104 */                 p_schro_params->enc_buf_size = 0;                                            // 0.0
/*106 */                 return err;                                                                  // 0.0
/*108 */             }                                                                                // 0.0
/*112 */             memcpy(p_schro_params->enc_buf + p_schro_params->enc_buf_size,                   // 0.0
/*114 */                    enc_buf->data, enc_buf->length);                                          // 0.0
/*116 */             p_schro_params->enc_buf_size += enc_buf->length;                                 // 0.0
/*122 */             if (state == SCHRO_STATE_END_OF_STREAM) {                                        // 0.0
/*124 */                 p_schro_params->eos_pulled = 1;                                              // 0.0
/*126 */                 go = 0;                                                                      // 0.0
/*128 */             }                                                                                // 0.0
/*132 */             if (!SCHRO_PARSE_CODE_IS_PICTURE(parse_code)) {                                  // 0.0
/*134 */                 schro_buffer_unref(enc_buf);                                                 // 0.0
/*136 */                 break;                                                                       // 0.0
/*138 */             }                                                                                // 0.0
/*142 */             /* Create output frame. */                                                       // 0.0
/*144 */             p_frame_output = av_mallocz(sizeof(FFSchroEncodedFrame));                        // 0.0
/*146 */             if (!p_frame_output)                                                             // 0.0
/*148 */                 return AVERROR(ENOMEM);                                                      // 0.0
/*150 */             /* Set output data. */                                                           // 0.0
/*152 */             p_frame_output->size     = p_schro_params->enc_buf_size;                         // 0.0
/*154 */             p_frame_output->p_encbuf = p_schro_params->enc_buf;                              // 0.0
/*156 */             if (SCHRO_PARSE_CODE_IS_INTRA(parse_code) &&                                     // 0.0
/*158 */                 SCHRO_PARSE_CODE_IS_REFERENCE(parse_code))                                   // 0.0
/*160 */                 p_frame_output->key_frame = 1;                                               // 0.0
/*164 */             /* Parse the coded frame number from the bitstream. Bytes 14                     // 0.0
/*166 */              * through 17 represesent the frame number. */                                   // 0.0
/*168 */             p_frame_output->frame_num = AV_RB32(enc_buf->data + 13);                         // 0.0
/*172 */             ff_schro_queue_push_back(&p_schro_params->enc_frame_queue,                       // 0.0
/*174 */                                      p_frame_output);                                        // 0.0
/*176 */             p_schro_params->enc_buf_size = 0;                                                // 0.0
/*178 */             p_schro_params->enc_buf      = NULL;                                             // 0.0
/*182 */             schro_buffer_unref(enc_buf);                                                     // 0.0
/*186 */             break;                                                                           // 0.0
/*190 */         case SCHRO_STATE_NEED_FRAME:                                                         // 0.0
/*192 */             go = 0;                                                                          // 0.0
/*194 */             break;                                                                           // 0.0
/*198 */         case SCHRO_STATE_AGAIN:                                                              // 0.0
/*200 */             break;                                                                           // 0.0
/*204 */         default:                                                                             // 0.0
/*206 */             av_log(avctx, AV_LOG_ERROR, "Unknown Schro Encoder state\n");                    // 0.0
/*208 */             return -1;                                                                       // 0.0
/*210 */         }                                                                                    // 0.0
/*212 */     }                                                                                        // 0.0
/*216 */     /* Copy 'next' frame in queue. */                                                        // 0.0
/*220 */     if (p_schro_params->enc_frame_queue.size == 1 &&                                         // 0.0
/*222 */         p_schro_params->eos_pulled)                                                          // 0.0
/*224 */         last_frame_in_sequence = 1;                                                          // 0.0
/*228 */     p_frame_output = ff_schro_queue_pop(&p_schro_params->enc_frame_queue);                   // 0.0
/*232 */     if (!p_frame_output)                                                                     // 0.0
/*234 */         return 0;                                                                            // 0.0
/*238 */     pkt_size = p_frame_output->size;                                                         // 0.0
/*240 */     if (last_frame_in_sequence && p_schro_params->enc_buf_size > 0)                          // 0.0
/*242 */         pkt_size += p_schro_params->enc_buf_size;                                            // 0.0
/*244 */     if ((ret = ff_alloc_packet(pkt, pkt_size)) < 0) {                                        // 0.0
/*246 */         av_log(avctx, AV_LOG_ERROR, "Error getting output packet of size %d.\n", pkt_size);  // 0.0
/*248 */         goto error;                                                                          // 0.0
/*250 */     }                                                                                        // 0.0
/*254 */     memcpy(pkt->data, p_frame_output->p_encbuf, p_frame_output->size);                       // 0.0
/*256 */     avctx->coded_frame->key_frame = p_frame_output->key_frame;                               // 0.0
/*258 */     /* Use the frame number of the encoded frame as the pts. It is OK to                     // 0.0
/*260 */      * do so since Dirac is a constant frame rate codec. It expects input                    // 0.0
/*262 */      * to be of constant frame rate. */                                                      // 0.0
/*264 */     pkt->pts =                                                                               // 0.0
/*266 */     avctx->coded_frame->pts = p_frame_output->frame_num;                                     // 0.0
/*268 */     pkt->dts = p_schro_params->dts++;                                                        // 0.0
/*270 */     enc_size = p_frame_output->size;                                                         // 0.0
/*274 */     /* Append the end of sequence information to the last frame in the                       // 0.0
/*276 */      * sequence. */                                                                          // 0.0
/*278 */     if (last_frame_in_sequence && p_schro_params->enc_buf_size > 0) {                        // 0.0
/*280 */         memcpy(pkt->data + enc_size, p_schro_params->enc_buf,                                // 0.0
/*282 */                p_schro_params->enc_buf_size);                                                // 0.0
/*284 */         enc_size += p_schro_params->enc_buf_size;                                            // 0.0
/*286 */         av_freep(&p_schro_params->enc_buf);                                                  // 0.0
/*288 */         p_schro_params->enc_buf_size = 0;                                                    // 0.0
/*290 */     }                                                                                        // 0.0
/*294 */     if (p_frame_output->key_frame)                                                           // 0.0
/*296 */         pkt->flags |= AV_PKT_FLAG_KEY;                                                       // 0.0
/*298 */     *got_packet = 1;                                                                         // 0.0
/*302 */ error:                                                                                       // 0.0
/*304 */     /* free frame */                                                                         // 0.0
/*306 */     libschroedinger_free_frame(p_frame_output);                                              // 0.0
/*308 */     return ret;                                                                              // 0.0
/*310 */ }                                                                                            // 0.0
