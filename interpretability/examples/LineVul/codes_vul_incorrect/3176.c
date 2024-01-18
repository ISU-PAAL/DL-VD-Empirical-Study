// commit message FFmpeg@69ee915e1c (target=1, prob=0.45612326, correct=False): avcodec/parser: add fuzzy mode to ff_fetch_timestamp()
/*0  */ void ff_fetch_timestamp(AVCodecParserContext *s, int off, int remove)              // (12) 0.04492
/*2  */ {                                                                                  // (22) 0.001953
/*4  */     int i;                                                                         // (20) 0.01172
/*8  */     s->dts    =                                                                    // (17) 0.02148
/*10 */     s->pts    = AV_NOPTS_VALUE;                                                    // (13) 0.03711
/*12 */     s->pos    = -1;                                                                // (16) 0.02539
/*14 */     s->offset = 0;                                                                 // (18) 0.01758
/*16 */     for (i = 0; i < AV_PARSER_PTS_NB; i++) {                                       // (11) 0.04688
/*18 */         if (s->cur_offset + off >= s->cur_frame_offset[i] &&                       // (8) 0.05469
/*20 */             (s->frame_offset < s->cur_frame_offset[i] ||                           // (7) 0.05664
/*22 */              (!s->frame_offset && !s->next_frame_offset)) && // first field/frame  // (1) 0.06641
/*24 */             // check disabled since MPEG-TS does not send complete PES packets     // (10) 0.04883
/*26 */             /*s->next_frame_offset + off <*/  s->cur_frame_end[i]){                // (0) 0.06836
/*30 */             s->dts    = s->cur_frame_dts[i];                                       // (5) 0.05859
/*32 */             s->pts    = s->cur_frame_pts[i];                                       // (6) 0.05859
/*34 */             s->pos    = s->cur_frame_pos[i];                                       // (9) 0.05469
/*36 */             s->offset = s->next_frame_offset - s->cur_frame_offset[i];             // (2) 0.06445
/*38 */             if (remove)                                                            // (15) 0.0293
/*40 */                 s->cur_frame_offset[i] = INT64_MAX;                                // (3) 0.06055
/*42 */             if (s->cur_offset + off < s->cur_frame_end[i])                         // (4) 0.06055
/*44 */                 break;                                                             // (14) 0.0332
/*46 */         }                                                                          // (19) 0.01562
/*48 */     }                                                                              // (21) 0.007812
/*50 */ }                                                                                  // 0.0
