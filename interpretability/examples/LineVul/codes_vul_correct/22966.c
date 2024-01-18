// commit message FFmpeg@984f50deb2 (target=1, prob=0.51248544, correct=True): diracdec: prevent overflow in data_unit_size check
/*0   */ static int dirac_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *pkt)                                    // (3) 0.06836
/*2   */ {                                                                                                                                  // (23) 0.001957
/*4   */     DiracContext *s     = avctx->priv_data;                                                                                        // (9) 0.03906
/*6   */     AVFrame *picture    = data;                                                                                                    // (15) 0.02539
/*8   */     uint8_t *buf        = pkt->data;                                                                                               // (8) 0.04297
/*10  */     int buf_size        = pkt->size;                                                                                               // (10) 0.03906
/*12  */     int i, data_unit_size, buf_idx = 0;                                                                                            // (11) 0.03711
/*14  */     int ret;                                                                                                                       // (22) 0.01172
/*18  */     /* release unused frames */                                                                                                    // (19) 0.01562
/*20  */     for (i = 0; i < MAX_FRAMES; i++)                                                                                               // (12) 0.03515
/*22  */         if (s->all_frames[i].avframe->data[0] && !s->all_frames[i].avframe->reference) {                                           // (1) 0.07812
/*24  */             av_frame_unref(s->all_frames[i].avframe);                                                                              // (5) 0.05664
/*26  */             memset(s->all_frames[i].interpolated, 0, sizeof(s->all_frames[i].interpolated));                                       // (0) 0.08203
/*28  */         }                                                                                                                          // (21) 0.01562
/*32  */     s->current_picture = NULL;                                                                                                     // (16) 0.02148
/*34  */     *got_frame = 0;                                                                                                                // (18) 0.01953
/*38  */     /* end of stream, so flush delayed pics */                                                                                     // (14) 0.02539
/*40  */     if (buf_size == 0)                                                                                                             // (17) 0.02148
/*42  */         return get_delayed_pic(s, (AVFrame *)data, got_frame);                                                                     // (7) 0.05273
/*46  */     for (;;) {                                                                                                                     // (20) 0.01562
/*48  */         /*[DIRAC_STD] Here starts the code from parse_info() defined in 9.6                                                        // (6) 0.05468
/*50  */           [DIRAC_STD] PARSE_INFO_PREFIX = "BBCD" as defined in ISO/IEC 646                                                         // (2) 0.07226
/*52  */           BBCD start code search */                                                                                                // (13) 0.0293
/*54  */         for (; buf_idx + DATA_UNIT_HEADER_SIZE < buf_size; buf_idx++) {                                                            // (4) 0.06836
/*56  */             if (buf[buf_idx  ] == 'B' && buf[buf_idx+1] == 'B' &&                                                                  // 0.0
/*58  */                 buf[buf_idx+2] == 'C' && buf[buf_idx+3] == 'D')                                                                    // 0.0
/*60  */                 break;                                                                                                             // 0.0
/*62  */         }                                                                                                                          // 0.0
/*64  */         /* BBCD found or end of data */                                                                                            // 0.0
/*66  */         if (buf_idx + DATA_UNIT_HEADER_SIZE >= buf_size)                                                                           // 0.0
/*68  */             break;                                                                                                                 // 0.0
/*72  */         data_unit_size = AV_RB32(buf+buf_idx+5);                                                                                   // 0.0
/*74  */         if (buf_idx + data_unit_size > buf_size || !data_unit_size) {                                                              // 0.0
/*76  */             if(buf_idx + data_unit_size > buf_size)                                                                                // 0.0
/*78  */             av_log(s->avctx, AV_LOG_ERROR,                                                                                         // 0.0
/*80  */                    "Data unit with size %d is larger than input buffer, discarding\n",                                             // 0.0
/*82  */                    data_unit_size);                                                                                                // 0.0
/*84  */             buf_idx += 4;                                                                                                          // 0.0
/*86  */             continue;                                                                                                              // 0.0
/*88  */         }                                                                                                                          // 0.0
/*90  */         /* [DIRAC_STD] dirac_decode_data_unit makes reference to the while defined in 9.3 inside the function parse_sequence() */  // 0.0
/*92  */         if (dirac_decode_data_unit(avctx, buf+buf_idx, data_unit_size))                                                            // 0.0
/*94  */         {                                                                                                                          // 0.0
/*96  */             av_log(s->avctx, AV_LOG_ERROR,"Error in dirac_decode_data_unit\n");                                                    // 0.0
/*98  */             return -1;                                                                                                             // 0.0
/*100 */         }                                                                                                                          // 0.0
/*102 */         buf_idx += data_unit_size;                                                                                                 // 0.0
/*104 */     }                                                                                                                              // 0.0
/*108 */     if (!s->current_picture)                                                                                                       // 0.0
/*110 */         return buf_size;                                                                                                           // 0.0
/*114 */     if (s->current_picture->avframe->display_picture_number > s->frame_number) {                                                   // 0.0
/*116 */         DiracFrame *delayed_frame = remove_frame(s->delay_frames, s->frame_number);                                                // 0.0
/*120 */         s->current_picture->avframe->reference |= DELAYED_PIC_REF;                                                                 // 0.0
/*124 */         if (add_frame(s->delay_frames, MAX_DELAY, s->current_picture)) {                                                           // 0.0
/*126 */             int min_num = s->delay_frames[0]->avframe->display_picture_number;                                                     // 0.0
/*128 */             /* Too many delayed frames, so we display the frame with the lowest pts */                                             // 0.0
/*130 */             av_log(avctx, AV_LOG_ERROR, "Delay frame overflow\n");                                                                 // 0.0
/*134 */             for (i = 1; s->delay_frames[i]; i++)                                                                                   // 0.0
/*136 */                 if (s->delay_frames[i]->avframe->display_picture_number < min_num)                                                 // 0.0
/*138 */                     min_num = s->delay_frames[i]->avframe->display_picture_number;                                                 // 0.0
/*142 */             delayed_frame = remove_frame(s->delay_frames, min_num);                                                                // 0.0
/*144 */             add_frame(s->delay_frames, MAX_DELAY, s->current_picture);                                                             // 0.0
/*146 */         }                                                                                                                          // 0.0
/*150 */         if (delayed_frame) {                                                                                                       // 0.0
/*152 */             delayed_frame->avframe->reference ^= DELAYED_PIC_REF;                                                                  // 0.0
/*154 */             if((ret=av_frame_ref(data, delayed_frame->avframe)) < 0)                                                               // 0.0
/*156 */                 return ret;                                                                                                        // 0.0
/*158 */             *got_frame = 1;                                                                                                        // 0.0
/*160 */         }                                                                                                                          // 0.0
/*162 */     } else if (s->current_picture->avframe->display_picture_number == s->frame_number) {                                           // 0.0
/*164 */         /* The right frame at the right time :-) */                                                                                // 0.0
/*166 */         if((ret=av_frame_ref(data, s->current_picture->avframe)) < 0)                                                              // 0.0
/*168 */             return ret;                                                                                                            // 0.0
/*170 */         *got_frame = 1;                                                                                                            // 0.0
/*172 */     }                                                                                                                              // 0.0
/*176 */     if (*got_frame)                                                                                                                // 0.0
/*178 */         s->frame_number = picture->display_picture_number + 1;                                                                     // 0.0
/*182 */     return buf_idx;                                                                                                                // 0.0
/*184 */ }                                                                                                                                  // 0.0
