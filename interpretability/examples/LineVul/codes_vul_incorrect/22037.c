// commit message FFmpeg@0424e052f8 (target=1, prob=0.45915437, correct=False):     Merge remote-tracking branch 'ffmpeg-mt/master'
/*0   */ static void decode_postinit(H264Context *h){                                                                             // (18) 0.02535
/*2   */     MpegEncContext * const s = &h->s;                                                                                    // (14) 0.03104
/*4   */     Picture *out = s->current_picture_ptr;                                                                               // (17) 0.02911
/*6   */     Picture *cur = s->current_picture_ptr;                                                                               // (15) 0.02912
/*8   */     int i, pics, out_of_order, out_idx;                                                                                  // (10) 0.03688
/*12  */     s->current_picture_ptr->qscale_type= FF_QSCALE_TYPE_H264;                                                            // (3) 0.05245
/*14  */     s->current_picture_ptr->pict_type= s->pict_type;                                                                     // (7) 0.04074
/*18  */     if (h->next_output_pic) return;                                                                                      // (16) 0.02911
/*22  */     if (cur->field_poc[0]==INT_MAX || cur->field_poc[1]==INT_MAX) {                                                      // (0) 0.0661
/*24  */         //FIXME this allows the next thread to start once we encounter the first field of a PAFF packet                  // (1) 0.05639
/*26  */         //This works if the next packet contains the second field. It does not work if both fields are                   // (2) 0.05507
/*28  */         //in the same packet.                                                                                            // (19) 0.02528
/*30  */         //ff_thread_finish_setup(s->avctx);                                                                              // (4) 0.04282
/*32  */         return;                                                                                                          // (24) 0.01746
/*34  */     }                                                                                                                    // (26) 0.007789
/*38  */     cur->interlaced_frame = 0;                                                                                           // (20) 0.02522
/*40  */     cur->repeat_pict = 0;                                                                                                // (23) 0.02135
/*44  */     /* Signal interlacing information externally. */                                                                     // (22) 0.02348
/*46  */     /* Prioritize picture timing SEI information over used decoding process if it exists. */                             // (6) 0.04093
/*50  */     if(h->sps.pic_struct_present_flag){                                                                                  // (12) 0.03492
/*52  */         switch (h->sei_pic_struct)                                                                                       // (13) 0.03298
/*54  */         {                                                                                                                // (25) 0.01553
/*56  */         case SEI_PIC_STRUCT_FRAME:                                                                                       // (11) 0.03687
/*58  */             break;                                                                                                       // (21) 0.02522
/*60  */         case SEI_PIC_STRUCT_TOP_FIELD:                                                                                   // (9) 0.0388
/*62  */         case SEI_PIC_STRUCT_BOTTOM_FIELD:                                                                                // (5) 0.04268
/*64  */             cur->interlaced_frame = 1;                                                                                   // (8) 0.04073
/*66  */             break;                                                                                                       // 0.0
/*68  */         case SEI_PIC_STRUCT_TOP_BOTTOM:                                                                                  // 0.0
/*70  */         case SEI_PIC_STRUCT_BOTTOM_TOP:                                                                                  // 0.0
/*72  */             if (FIELD_OR_MBAFF_PICTURE)                                                                                  // 0.0
/*74  */                 cur->interlaced_frame = 1;                                                                               // 0.0
/*76  */             else                                                                                                         // 0.0
/*78  */                 // try to flag soft telecine progressive                                                                 // 0.0
/*80  */                 cur->interlaced_frame = h->prev_interlaced_frame;                                                        // 0.0
/*82  */             break;                                                                                                       // 0.0
/*84  */         case SEI_PIC_STRUCT_TOP_BOTTOM_TOP:                                                                              // 0.0
/*86  */         case SEI_PIC_STRUCT_BOTTOM_TOP_BOTTOM:                                                                           // 0.0
/*88  */             // Signal the possibility of telecined film externally (pic_struct 5,6)                                      // 0.0
/*90  */             // From these hints, let the applications decide if they apply deinterlacing.                                // 0.0
/*92  */             cur->repeat_pict = 1;                                                                                        // 0.0
/*94  */             break;                                                                                                       // 0.0
/*96  */         case SEI_PIC_STRUCT_FRAME_DOUBLING:                                                                              // 0.0
/*98  */             // Force progressive here, as doubling interlaced frame is a bad idea.                                       // 0.0
/*100 */             cur->repeat_pict = 2;                                                                                        // 0.0
/*102 */             break;                                                                                                       // 0.0
/*104 */         case SEI_PIC_STRUCT_FRAME_TRIPLING:                                                                              // 0.0
/*106 */             cur->repeat_pict = 4;                                                                                        // 0.0
/*108 */             break;                                                                                                       // 0.0
/*110 */         }                                                                                                                // 0.0
/*114 */         if ((h->sei_ct_type & 3) && h->sei_pic_struct <= SEI_PIC_STRUCT_BOTTOM_TOP)                                      // 0.0
/*116 */             cur->interlaced_frame = (h->sei_ct_type & (1<<1)) != 0;                                                      // 0.0
/*118 */     }else{                                                                                                               // 0.0
/*120 */         /* Derive interlacing flag from used decoding process. */                                                        // 0.0
/*122 */         cur->interlaced_frame = FIELD_OR_MBAFF_PICTURE;                                                                  // 0.0
/*124 */     }                                                                                                                    // 0.0
/*126 */     h->prev_interlaced_frame = cur->interlaced_frame;                                                                    // 0.0
/*130 */     if (cur->field_poc[0] != cur->field_poc[1]){                                                                         // 0.0
/*132 */         /* Derive top_field_first from field pocs. */                                                                    // 0.0
/*134 */         cur->top_field_first = cur->field_poc[0] < cur->field_poc[1];                                                    // 0.0
/*136 */     }else{                                                                                                               // 0.0
/*138 */         if(cur->interlaced_frame || h->sps.pic_struct_present_flag){                                                     // 0.0
/*140 */             /* Use picture timing SEI information. Even if it is a information of a past frame, better than nothing. */  // 0.0
/*142 */             if(h->sei_pic_struct == SEI_PIC_STRUCT_TOP_BOTTOM                                                            // 0.0
/*144 */               || h->sei_pic_struct == SEI_PIC_STRUCT_TOP_BOTTOM_TOP)                                                     // 0.0
/*146 */                 cur->top_field_first = 1;                                                                                // 0.0
/*148 */             else                                                                                                         // 0.0
/*150 */                 cur->top_field_first = 0;                                                                                // 0.0
/*152 */         }else{                                                                                                           // 0.0
/*154 */             /* Most likely progressive */                                                                                // 0.0
/*156 */             cur->top_field_first = 0;                                                                                    // 0.0
/*158 */         }                                                                                                                // 0.0
/*160 */     }                                                                                                                    // 0.0
/*164 */     //FIXME do something with unavailable reference frames                                                               // 0.0
/*168 */     /* Sort B-frames into display order */                                                                               // 0.0
/*172 */     if(h->sps.bitstream_restriction_flag                                                                                 // 0.0
/*174 */        && s->avctx->has_b_frames < h->sps.num_reorder_frames){                                                           // 0.0
/*176 */         s->avctx->has_b_frames = h->sps.num_reorder_frames;                                                              // 0.0
/*178 */         s->low_delay = 0;                                                                                                // 0.0
/*180 */     }                                                                                                                    // 0.0
/*184 */     if(   s->avctx->strict_std_compliance >= FF_COMPLIANCE_STRICT                                                        // 0.0
/*186 */        && !h->sps.bitstream_restriction_flag){                                                                           // 0.0
/*188 */         s->avctx->has_b_frames= MAX_DELAYED_PIC_COUNT;                                                                   // 0.0
/*190 */         s->low_delay= 0;                                                                                                 // 0.0
/*192 */     }                                                                                                                    // 0.0
/*196 */     pics = 0;                                                                                                            // 0.0
/*198 */     while(h->delayed_pic[pics]) pics++;                                                                                  // 0.0
/*202 */     assert(pics <= MAX_DELAYED_PIC_COUNT);                                                                               // 0.0
/*206 */     h->delayed_pic[pics++] = cur;                                                                                        // 0.0
/*208 */     if(cur->reference == 0)                                                                                              // 0.0
/*210 */         cur->reference = DELAYED_PIC_REF;                                                                                // 0.0
/*214 */     out = h->delayed_pic[0];                                                                                             // 0.0
/*216 */     out_idx = 0;                                                                                                         // 0.0
/*218 */     for(i=1; h->delayed_pic[i] && !h->delayed_pic[i]->key_frame && !h->delayed_pic[i]->mmco_reset; i++)                  // 0.0
/*220 */         if(h->delayed_pic[i]->poc < out->poc){                                                                           // 0.0
/*222 */             out = h->delayed_pic[i];                                                                                     // 0.0
/*224 */             out_idx = i;                                                                                                 // 0.0
/*226 */         }                                                                                                                // 0.0
/*228 */     if(s->avctx->has_b_frames == 0 && (h->delayed_pic[0]->key_frame || h->delayed_pic[0]->mmco_reset))                   // 0.0
/*230 */         h->next_outputed_poc= INT_MIN;                                                                                   // 0.0
/*232 */     out_of_order = out->poc < h->next_outputed_poc;                                                                      // 0.0
/*236 */     if(h->sps.bitstream_restriction_flag && s->avctx->has_b_frames >= h->sps.num_reorder_frames)                         // 0.0
/*238 */         { }                                                                                                              // 0.0
/*240 */     else if((out_of_order && pics-1 == s->avctx->has_b_frames && s->avctx->has_b_frames < MAX_DELAYED_PIC_COUNT)         // 0.0
/*242 */        || (s->low_delay &&                                                                                               // 0.0
/*244 */         ((h->next_outputed_poc != INT_MIN && out->poc > h->next_outputed_poc + 2)                                        // 0.0
/*246 */          || cur->pict_type == AV_PICTURE_TYPE_B)))                                                                       // 0.0
/*248 */     {                                                                                                                    // 0.0
/*250 */         s->low_delay = 0;                                                                                                // 0.0
/*252 */         s->avctx->has_b_frames++;                                                                                        // 0.0
/*254 */     }                                                                                                                    // 0.0
/*258 */     if(out_of_order || pics > s->avctx->has_b_frames){                                                                   // 0.0
/*260 */         out->reference &= ~DELAYED_PIC_REF;                                                                              // 0.0
/*262 */         out->owner2 = s; // for frame threading, the owner must be the second field's thread                             // 0.0
/*264 */                          // or else the first thread can release the picture and reuse it unsafely                       // 0.0
/*266 */         for(i=out_idx; h->delayed_pic[i]; i++)                                                                           // 0.0
/*268 */             h->delayed_pic[i] = h->delayed_pic[i+1];                                                                     // 0.0
/*270 */     }                                                                                                                    // 0.0
/*272 */     if(!out_of_order && pics > s->avctx->has_b_frames){                                                                  // 0.0
/*274 */         h->next_output_pic = out;                                                                                        // 0.0
/*276 */         if(out_idx==0 && h->delayed_pic[0] && (h->delayed_pic[0]->key_frame || h->delayed_pic[0]->mmco_reset)) {         // 0.0
/*278 */             h->next_outputed_poc = INT_MIN;                                                                              // 0.0
/*280 */         } else                                                                                                           // 0.0
/*282 */             h->next_outputed_poc = out->poc;                                                                             // 0.0
/*284 */     }else{                                                                                                               // 0.0
/*286 */         av_log(s->avctx, AV_LOG_DEBUG, "no picture\n");                                                                  // 0.0
/*288 */     }                                                                                                                    // 0.0
/*292 */     ff_thread_finish_setup(s->avctx);                                                                                    // 0.0
/*294 */ }                                                                                                                        // 0.0
