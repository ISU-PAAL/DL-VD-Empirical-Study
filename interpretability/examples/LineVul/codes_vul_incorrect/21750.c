// commit message FFmpeg@17269bdfcd (target=1, prob=0.3450861, correct=False): fixed double free - fixed probe function
/*0  */ static int swf_write_trailer(AVFormatContext *s)                // (10) 0.03874
/*2  */ {                                                               // (25) 0.002421
/*4  */     SWFContext *swf = s->priv_data;                             // (11) 0.03874
/*6  */     ByteIOContext *pb = &s->pb;                                 // (15) 0.0339
/*8  */     AVCodecContext *enc, *video_enc;                            // (13) 0.03632
/*10 */     int file_size, i;                                           // (18) 0.02421
/*14 */     video_enc = NULL;                                           // (20) 0.02179
/*16 */     for(i=0;i<s->nb_streams;i++) {                              // (4) 0.05085
/*18 */         enc = &s->streams[i]->codec;                            // (5) 0.05085
/*20 */         if (enc->codec_type == CODEC_TYPE_VIDEO)                // (1) 0.05811
/*22 */             video_enc = enc;                                    // (9) 0.04116
/*24 */     }                                                           // (22) 0.009685
/*28 */     put_swf_tag(s, TAG_END);                                    // (12) 0.03874
/*30 */     put_swf_end_tag(s);                                         // (16) 0.0339
/*32 */                                                                 // (23) 0.009685
/*34 */     put_flush_packet(&s->pb);                                   // (17) 0.0339
/*38 */     /* patch file size and number of frames if not streamed */  // (14) 0.03632
/*40 */     if (!url_is_streamed(&s->pb) && video_enc) {                // (2) 0.05327
/*42 */         file_size = url_ftell(pb);                              // (7) 0.04358
/*44 */         url_fseek(pb, 4, SEEK_SET);                             // (6) 0.05085
/*46 */         put_le32(pb, file_size);                                // (8) 0.04358
/*48 */         url_fseek(pb, swf->duration_pos, SEEK_SET);             // (0) 0.06295
/*50 */         put_le16(pb, video_enc->frame_number);                  // (3) 0.05327
/*52 */     }                                                           // (24) 0.009685
/*54 */     av_free(swf);                                               // (19) 0.02421
/*56 */     return 0;                                                   // (21) 0.01453
/*58 */ }                                                               // (26) 0.002421
