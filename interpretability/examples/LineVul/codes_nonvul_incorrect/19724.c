// commit message FFmpeg@ecb14b8af7 (target=0, prob=0.5842698, correct=False): h264: add forgotten \n to "Invalid mix of idr and non-idr slices" Signed-off-by: Michael Niedermayer <michaelni@gmx.at>
/*0   */ static int decode_nal_units(H264Context *h, const uint8_t *buf, int buf_size){                                                                                      // (1) 0.05469
/*2   */     MpegEncContext * const s = &h->s;                                                                                                                               // (10) 0.03125
/*4   */     AVCodecContext * const avctx= s->avctx;                                                                                                                         // (8) 0.0332
/*6   */     H264Context *hx; ///< thread context                                                                                                                            // (14) 0.02734
/*8   */     int buf_index;                                                                                                                                                  // (25) 0.01562
/*10  */     int context_count;                                                                                                                                              // (26) 0.01562
/*12  */     int next_avc;                                                                                                                                                   // (24) 0.01758
/*14  */     int pass = !(avctx->active_thread_type & FF_THREAD_FRAME);                                                                                                      // (3) 0.04882
/*16  */     int nals_needed=0; ///< number of NALs that need decoding before the next frame thread starts                                                                   // (2) 0.05273
/*18  */     int nal_index;                                                                                                                                                  // (23) 0.01758
/*22  */     h->nal_unit_type= 0;                                                                                                                                            // (13) 0.02734
/*26  */     h->max_contexts = (HAVE_THREADS && (s->avctx->active_thread_type&FF_THREAD_SLICE)) ? avctx->thread_count : 1;                                                   // (0) 0.09374
/*28  */     if(!(s->flags2 & CODEC_FLAG2_CHUNKS)){                                                                                                                          // (5) 0.04687
/*30  */         h->current_slice = 0;                                                                                                                                       // (12) 0.02929
/*32  */         if (!s->first_field)                                                                                                                                        // (11) 0.02929
/*34  */             s->current_picture_ptr= NULL;                                                                                                                           // (6) 0.04101
/*36  */         ff_h264_reset_sei(h);                                                                                                                                       // (7) 0.03516
/*38  */     }                                                                                                                                                               // (28) 0.007814
/*42  */     for(;pass <= 1;pass++){                                                                                                                                         // (17) 0.02539
/*44  */         buf_index = 0;                                                                                                                                              // (18) 0.02539
/*46  */         context_count = 0;                                                                                                                                          // (19) 0.02539
/*48  */         next_avc = h->is_avc ? 0 : buf_size;                                                                                                                        // (4) 0.04882
/*50  */         nal_index = 0;                                                                                                                                              // (16) 0.02734
/*52  */     for(;;){                                                                                                                                                        // (27) 0.01367
/*54  */         int consumed;                                                                                                                                               // (22) 0.01953
/*56  */         int dst_length;                                                                                                                                             // (21) 0.02344
/*58  */         int bit_length;                                                                                                                                             // (20) 0.02344
/*60  */         uint8_t *ptr;                                                                                                                                               // (15) 0.02734
/*62  */         int i, nalsize = 0;                                                                                                                                         // (9) 0.03125
/*64  */         int err;                                                                                                                                                    // 0.0
/*68  */         if(buf_index >= next_avc) {                                                                                                                                 // 0.0
/*70  */             if (buf_index >= buf_size - h->nal_length_size) break;                                                                                                  // 0.0
/*72  */             nalsize = 0;                                                                                                                                            // 0.0
/*74  */             for(i = 0; i < h->nal_length_size; i++)                                                                                                                 // 0.0
/*76  */                 nalsize = (nalsize << 8) | buf[buf_index++];                                                                                                        // 0.0
/*78  */             if(nalsize <= 0 || nalsize > buf_size - buf_index){                                                                                                     // 0.0
/*80  */                 av_log(h->s.avctx, AV_LOG_ERROR, "AVC: nal size %d\n", nalsize);                                                                                    // 0.0
/*82  */                 break;                                                                                                                                              // 0.0
/*84  */             }                                                                                                                                                       // 0.0
/*86  */             next_avc= buf_index + nalsize;                                                                                                                          // 0.0
/*88  */         } else {                                                                                                                                                    // 0.0
/*90  */             // start code prefix search                                                                                                                             // 0.0
/*92  */             for(; buf_index + 3 < next_avc; buf_index++){                                                                                                           // 0.0
/*94  */                 // This should always succeed in the first iteration.                                                                                               // 0.0
/*96  */                 if(buf[buf_index] == 0 && buf[buf_index+1] == 0 && buf[buf_index+2] == 1)                                                                           // 0.0
/*98  */                     break;                                                                                                                                          // 0.0
/*100 */             }                                                                                                                                                       // 0.0
/*104 */             if(buf_index+3 >= buf_size) break;                                                                                                                      // 0.0
/*108 */             buf_index+=3;                                                                                                                                           // 0.0
/*110 */             if(buf_index >= next_avc) continue;                                                                                                                     // 0.0
/*112 */         }                                                                                                                                                           // 0.0
/*116 */         hx = h->thread_context[context_count];                                                                                                                      // 0.0
/*120 */         ptr= ff_h264_decode_nal(hx, buf + buf_index, &dst_length, &consumed, next_avc - buf_index);                                                                 // 0.0
/*122 */         if (ptr==NULL || dst_length < 0){                                                                                                                           // 0.0
/*124 */             return -1;                                                                                                                                              // 0.0
/*126 */         }                                                                                                                                                           // 0.0
/*128 */         i= buf_index + consumed;                                                                                                                                    // 0.0
/*130 */         if((s->workaround_bugs & FF_BUG_AUTODETECT) && i+3<next_avc &&                                                                                              // 0.0
/*132 */            buf[i]==0x00 && buf[i+1]==0x00 && buf[i+2]==0x01 && buf[i+3]==0xE0)                                                                                      // 0.0
/*134 */             s->workaround_bugs |= FF_BUG_TRUNCATED;                                                                                                                 // 0.0
/*138 */         if(!(s->workaround_bugs & FF_BUG_TRUNCATED)){                                                                                                               // 0.0
/*140 */         while(dst_length > 0 && ptr[dst_length - 1] == 0)                                                                                                           // 0.0
/*142 */             dst_length--;                                                                                                                                           // 0.0
/*144 */         }                                                                                                                                                           // 0.0
/*146 */         bit_length= !dst_length ? 0 : (8*dst_length - ff_h264_decode_rbsp_trailing(h, ptr + dst_length - 1));                                                       // 0.0
/*150 */         if(s->avctx->debug&FF_DEBUG_STARTCODE){                                                                                                                     // 0.0
/*152 */             av_log(h->s.avctx, AV_LOG_DEBUG, "NAL %d/%d at %d/%d length %d pass %d\n", hx->nal_unit_type, hx->nal_ref_idc, buf_index, buf_size, dst_length, pass);  // 0.0
/*154 */         }                                                                                                                                                           // 0.0
/*158 */         if (h->is_avc && (nalsize != consumed) && nalsize){                                                                                                         // 0.0
/*160 */             av_log(h->s.avctx, AV_LOG_DEBUG, "AVC: Consumed only %d bytes instead of %d\n", consumed, nalsize);                                                     // 0.0
/*162 */         }                                                                                                                                                           // 0.0
/*166 */         buf_index += consumed;                                                                                                                                      // 0.0
/*168 */         nal_index++;                                                                                                                                                // 0.0
/*172 */         if(pass == 0) {                                                                                                                                             // 0.0
/*174 */             // packets can sometimes contain multiple PPS/SPS                                                                                                       // 0.0
/*176 */             // e.g. two PAFF field pictures in one packet, or a demuxer which splits NALs strangely                                                                 // 0.0
/*178 */             // if so, when frame threading we can't start the next thread until we've read all of them                                                              // 0.0
/*180 */             switch (hx->nal_unit_type) {                                                                                                                            // 0.0
/*182 */                 case NAL_SPS:                                                                                                                                       // 0.0
/*184 */                 case NAL_PPS:                                                                                                                                       // 0.0
/*186 */                     nals_needed = nal_index;                                                                                                                        // 0.0
/*188 */                     break;                                                                                                                                          // 0.0
/*190 */                 case NAL_IDR_SLICE:                                                                                                                                 // 0.0
/*192 */                 case NAL_SLICE:                                                                                                                                     // 0.0
/*194 */                     init_get_bits(&hx->s.gb, ptr, bit_length);                                                                                                      // 0.0
/*196 */                     if (!get_ue_golomb(&hx->s.gb))                                                                                                                  // 0.0
/*198 */                         nals_needed = nal_index;                                                                                                                    // 0.0
/*200 */             }                                                                                                                                                       // 0.0
/*202 */             continue;                                                                                                                                               // 0.0
/*204 */         }                                                                                                                                                           // 0.0
/*208 */         //FIXME do not discard SEI id                                                                                                                               // 0.0
/*210 */         if(avctx->skip_frame >= AVDISCARD_NONREF && h->nal_ref_idc  == 0)                                                                                           // 0.0
/*212 */             continue;                                                                                                                                               // 0.0
/*216 */       again:                                                                                                                                                        // 0.0
/*218 */         err = 0;                                                                                                                                                    // 0.0
/*220 */         switch(hx->nal_unit_type){                                                                                                                                  // 0.0
/*222 */         case NAL_IDR_SLICE:                                                                                                                                         // 0.0
/*224 */             if (h->nal_unit_type != NAL_IDR_SLICE) {                                                                                                                // 0.0
/*226 */                 av_log(h->s.avctx, AV_LOG_ERROR, "Invalid mix of idr and non-idr slices");                                                                          // 0.0
/*228 */                 return -1;                                                                                                                                          // 0.0
/*230 */             }                                                                                                                                                       // 0.0
/*232 */             idr(h); // FIXME ensure we don't lose some frames if there is reordering                                                                                // 0.0
/*234 */         case NAL_SLICE:                                                                                                                                             // 0.0
/*236 */             init_get_bits(&hx->s.gb, ptr, bit_length);                                                                                                              // 0.0
/*238 */             hx->intra_gb_ptr=                                                                                                                                       // 0.0
/*240 */             hx->inter_gb_ptr= &hx->s.gb;                                                                                                                            // 0.0
/*242 */             hx->s.data_partitioning = 0;                                                                                                                            // 0.0
/*246 */             if((err = decode_slice_header(hx, h)))                                                                                                                  // 0.0
/*248 */                break;                                                                                                                                               // 0.0
/*252 */             if (   h->sei_recovery_frame_cnt >= 0                                                                                                                   // 0.0
/*254 */                 && ((h->recovery_frame - h->frame_num) & ((1 << h->sps.log2_max_frame_num)-1)) > h->sei_recovery_frame_cnt) {                                       // 0.0
/*256 */                 h->recovery_frame = (h->frame_num + h->sei_recovery_frame_cnt) %                                                                                    // 0.0
/*258 */                                     (1 << h->sps.log2_max_frame_num);                                                                                               // 0.0
/*260 */             }                                                                                                                                                       // 0.0
/*264 */             s->current_picture_ptr->f.key_frame |=                                                                                                                  // 0.0
/*266 */                     (hx->nal_unit_type == NAL_IDR_SLICE);                                                                                                           // 0.0
/*270 */             if (h->recovery_frame == h->frame_num) {                                                                                                                // 0.0
/*272 */                 h->sync |= 1;                                                                                                                                       // 0.0
/*274 */                 h->recovery_frame = -1;                                                                                                                             // 0.0
/*276 */             }                                                                                                                                                       // 0.0
/*280 */             h->sync |= !!s->current_picture_ptr->f.key_frame;                                                                                                       // 0.0
/*282 */             h->sync |= 3*!!(s->flags2 & CODEC_FLAG2_SHOW_ALL);                                                                                                      // 0.0
/*284 */             s->current_picture_ptr->sync = h->sync;                                                                                                                 // 0.0
/*288 */             if (h->current_slice == 1) {                                                                                                                            // 0.0
/*290 */                 if(!(s->flags2 & CODEC_FLAG2_CHUNKS)) {                                                                                                             // 0.0
/*292 */                     decode_postinit(h, nal_index >= nals_needed);                                                                                                   // 0.0
/*294 */                 }                                                                                                                                                   // 0.0
/*298 */                 if (s->avctx->hwaccel && s->avctx->hwaccel->start_frame(s->avctx, NULL, 0) < 0)                                                                     // 0.0
/*300 */                     return -1;                                                                                                                                      // 0.0
/*302 */                 if(CONFIG_H264_VDPAU_DECODER && s->avctx->codec->capabilities&CODEC_CAP_HWACCEL_VDPAU)                                                              // 0.0
/*304 */                     ff_vdpau_h264_picture_start(s);                                                                                                                 // 0.0
/*306 */             }                                                                                                                                                       // 0.0
/*310 */             if(hx->redundant_pic_count==0                                                                                                                           // 0.0
/*312 */                && (avctx->skip_frame < AVDISCARD_NONREF || hx->nal_ref_idc)                                                                                         // 0.0
/*314 */                && (avctx->skip_frame < AVDISCARD_BIDIR  || hx->slice_type_nos!=AV_PICTURE_TYPE_B)                                                                   // 0.0
/*316 */                && (avctx->skip_frame < AVDISCARD_NONKEY || hx->slice_type_nos==AV_PICTURE_TYPE_I)                                                                   // 0.0
/*318 */                && avctx->skip_frame < AVDISCARD_ALL){                                                                                                               // 0.0
/*320 */                 if(avctx->hwaccel) {                                                                                                                                // 0.0
/*322 */                     if (avctx->hwaccel->decode_slice(avctx, &buf[buf_index - consumed], consumed) < 0)                                                              // 0.0
/*324 */                         return -1;                                                                                                                                  // 0.0
/*326 */                 }else                                                                                                                                               // 0.0
/*328 */                 if(CONFIG_H264_VDPAU_DECODER && s->avctx->codec->capabilities&CODEC_CAP_HWACCEL_VDPAU){                                                             // 0.0
/*330 */                     static const uint8_t start_code[] = {0x00, 0x00, 0x01};                                                                                         // 0.0
/*332 */                     ff_vdpau_add_data_chunk(s, start_code, sizeof(start_code));                                                                                     // 0.0
/*334 */                     ff_vdpau_add_data_chunk(s, &buf[buf_index - consumed], consumed );                                                                              // 0.0
/*336 */                 }else                                                                                                                                               // 0.0
/*338 */                     context_count++;                                                                                                                                // 0.0
/*340 */             }                                                                                                                                                       // 0.0
/*342 */             break;                                                                                                                                                  // 0.0
/*344 */         case NAL_DPA:                                                                                                                                               // 0.0
/*346 */             init_get_bits(&hx->s.gb, ptr, bit_length);                                                                                                              // 0.0
/*348 */             hx->intra_gb_ptr=                                                                                                                                       // 0.0
/*350 */             hx->inter_gb_ptr= NULL;                                                                                                                                 // 0.0
/*354 */             if ((err = decode_slice_header(hx, h)) < 0)                                                                                                             // 0.0
/*356 */                 break;                                                                                                                                              // 0.0
/*360 */             hx->s.data_partitioning = 1;                                                                                                                            // 0.0
/*364 */             break;                                                                                                                                                  // 0.0
/*366 */         case NAL_DPB:                                                                                                                                               // 0.0
/*368 */             init_get_bits(&hx->intra_gb, ptr, bit_length);                                                                                                          // 0.0
/*370 */             hx->intra_gb_ptr= &hx->intra_gb;                                                                                                                        // 0.0
/*372 */             break;                                                                                                                                                  // 0.0
/*374 */         case NAL_DPC:                                                                                                                                               // 0.0
/*376 */             init_get_bits(&hx->inter_gb, ptr, bit_length);                                                                                                          // 0.0
/*378 */             hx->inter_gb_ptr= &hx->inter_gb;                                                                                                                        // 0.0
/*382 */             if(hx->redundant_pic_count==0 && hx->intra_gb_ptr && hx->s.data_partitioning                                                                            // 0.0
/*384 */                && s->context_initialized                                                                                                                            // 0.0
/*386 */                && (avctx->skip_frame < AVDISCARD_NONREF || hx->nal_ref_idc)                                                                                         // 0.0
/*388 */                && (avctx->skip_frame < AVDISCARD_BIDIR  || hx->slice_type_nos!=AV_PICTURE_TYPE_B)                                                                   // 0.0
/*390 */                && (avctx->skip_frame < AVDISCARD_NONKEY || hx->slice_type_nos==AV_PICTURE_TYPE_I)                                                                   // 0.0
/*392 */                && avctx->skip_frame < AVDISCARD_ALL)                                                                                                                // 0.0
/*394 */                 context_count++;                                                                                                                                    // 0.0
/*396 */             break;                                                                                                                                                  // 0.0
/*398 */         case NAL_SEI:                                                                                                                                               // 0.0
/*400 */             init_get_bits(&s->gb, ptr, bit_length);                                                                                                                 // 0.0
/*402 */             ff_h264_decode_sei(h);                                                                                                                                  // 0.0
/*404 */             break;                                                                                                                                                  // 0.0
/*406 */         case NAL_SPS:                                                                                                                                               // 0.0
/*408 */             init_get_bits(&s->gb, ptr, bit_length);                                                                                                                 // 0.0
/*410 */             if(ff_h264_decode_seq_parameter_set(h) < 0 && (h->is_avc ? (nalsize != consumed) && nalsize : 1)){                                                      // 0.0
/*412 */                 av_log(h->s.avctx, AV_LOG_DEBUG, "SPS decoding failure, trying alternative mode\n");                                                                // 0.0
/*414 */                 if(h->is_avc) av_assert0(next_avc - buf_index + consumed == nalsize);                                                                               // 0.0
/*416 */                 init_get_bits(&s->gb, &buf[buf_index + 1 - consumed], 8*(next_avc - buf_index + consumed));                                                         // 0.0
/*418 */                 ff_h264_decode_seq_parameter_set(h);                                                                                                                // 0.0
/*420 */             }                                                                                                                                                       // 0.0
/*424 */             if (s->flags& CODEC_FLAG_LOW_DELAY ||                                                                                                                   // 0.0
/*426 */                 (h->sps.bitstream_restriction_flag && !h->sps.num_reorder_frames))                                                                                  // 0.0
/*428 */                 s->low_delay=1;                                                                                                                                     // 0.0
/*432 */             if(avctx->has_b_frames < 2)                                                                                                                             // 0.0
/*434 */                 avctx->has_b_frames= !s->low_delay;                                                                                                                 // 0.0
/*436 */             break;                                                                                                                                                  // 0.0
/*438 */         case NAL_PPS:                                                                                                                                               // 0.0
/*440 */             init_get_bits(&s->gb, ptr, bit_length);                                                                                                                 // 0.0
/*444 */             ff_h264_decode_picture_parameter_set(h, bit_length);                                                                                                    // 0.0
/*448 */             break;                                                                                                                                                  // 0.0
/*450 */         case NAL_AUD:                                                                                                                                               // 0.0
/*452 */         case NAL_END_SEQUENCE:                                                                                                                                      // 0.0
/*454 */         case NAL_END_STREAM:                                                                                                                                        // 0.0
/*456 */         case NAL_FILLER_DATA:                                                                                                                                       // 0.0
/*458 */         case NAL_SPS_EXT:                                                                                                                                           // 0.0
/*460 */         case NAL_AUXILIARY_SLICE:                                                                                                                                   // 0.0
/*462 */             break;                                                                                                                                                  // 0.0
/*464 */         default:                                                                                                                                                    // 0.0
/*466 */             av_log(avctx, AV_LOG_DEBUG, "Unknown NAL code: %d (%d bits)\n", hx->nal_unit_type, bit_length);                                                         // 0.0
/*468 */         }                                                                                                                                                           // 0.0
/*472 */         if(context_count == h->max_contexts) {                                                                                                                      // 0.0
/*474 */             execute_decode_slices(h, context_count);                                                                                                                // 0.0
/*476 */             context_count = 0;                                                                                                                                      // 0.0
/*478 */         }                                                                                                                                                           // 0.0
/*482 */         if (err < 0)                                                                                                                                                // 0.0
/*484 */             av_log(h->s.avctx, AV_LOG_ERROR, "decode_slice_header error\n");                                                                                        // 0.0
/*486 */         else if(err == 1) {                                                                                                                                         // 0.0
/*488 */             /* Slice could not be decoded in parallel mode, copy down                                                                                               // 0.0
/*490 */              * NAL unit stuff to context 0 and restart. Note that                                                                                                   // 0.0
/*492 */              * rbsp_buffer is not transferred, but since we no longer                                                                                               // 0.0
/*494 */              * run in parallel mode this should not be an issue. */                                                                                                 // 0.0
/*496 */             h->nal_unit_type = hx->nal_unit_type;                                                                                                                   // 0.0
/*498 */             h->nal_ref_idc   = hx->nal_ref_idc;                                                                                                                     // 0.0
/*500 */             hx = h;                                                                                                                                                 // 0.0
/*502 */             goto again;                                                                                                                                             // 0.0
/*504 */         }                                                                                                                                                           // 0.0
/*506 */     }                                                                                                                                                               // 0.0
/*508 */     }                                                                                                                                                               // 0.0
/*510 */     if(context_count)                                                                                                                                               // 0.0
/*512 */         execute_decode_slices(h, context_count);                                                                                                                    // 0.0
/*514 */     return buf_index;                                                                                                                                               // 0.0
/*516 */ }                                                                                                                                                                   // 0.0
