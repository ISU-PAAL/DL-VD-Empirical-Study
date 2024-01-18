// commit message FFmpeg@bb6f51aeab (target=1, prob=0.104215905, correct=False): avoid overflow of picturenumber*fps*10000 bug found by Lennert Buytenhek <buytenh@gnu.org>
/*0   */ static void mpeg1_encode_sequence_header(MpegEncContext *s)                      // (11) 0.03906
/*2   */ {                                                                                // (23) 0.001953
/*4   */         unsigned int vbv_buffer_size;                                            // (13) 0.0332
/*6   */         unsigned int fps, v;                                                     // (17) 0.02539
/*8   */         int n;                                                                   // (21) 0.01953
/*10  */         UINT64 time_code;                                                        // (16) 0.02734
/*12  */                                                                                  // (22) 0.01562
/*14  */         if ((s->picture_number % s->gop_size) == 0) {                            // (5) 0.05078
/*16  */             /* mpeg1 header repeated every gop */                                // (10) 0.04102
/*18  */             put_header(s, SEQ_START_CODE);                                       // (6) 0.05078
/*20  */                                                                                  // (20) 0.02344
/*22  */             /* search closest frame rate */                                      // (14) 0.0332
/*24  */             {                                                                    // (19) 0.02344
/*26  */                 int i, dmin, d;                                                  // (9) 0.04492
/*28  */                 s->frame_rate_index = 0;                                         // (7) 0.04883
/*30  */                 dmin = 0x7fffffff;                                               // (8) 0.04687
/*32  */                 for(i=1;i<9;i++) {                                               // (3) 0.05469
/*34  */                     d = abs(s->frame_rate - frame_rate_tab[i]);                  // (0) 0.07227
/*36  */                     if (d < dmin) {                                              // (4) 0.05273
/*38  */                         dmin = d;                                                // (2) 0.05469
/*40  */                         s->frame_rate_index = i;                                 // (1) 0.06445
/*42  */                     }                                                            // (12) 0.03906
/*44  */                 }                                                                // (15) 0.03125
/*46  */             }                                                                    // (18) 0.02344
/*48  */                                                                                  // (24) 0.001953
/*50  */             put_bits(&s->pb, 12, s->width);                                      // 0.0
/*52  */             put_bits(&s->pb, 12, s->height);                                     // 0.0
/*54  */             put_bits(&s->pb, 4, 1); /* 1/1 aspect ratio */                       // 0.0
/*56  */             put_bits(&s->pb, 4, s->frame_rate_index);                            // 0.0
/*58  */             v = s->bit_rate / 400;                                               // 0.0
/*60  */             if (v > 0x3ffff)                                                     // 0.0
/*62  */                 v = 0x3ffff;                                                     // 0.0
/*64  */             put_bits(&s->pb, 18, v);                                             // 0.0
/*66  */             put_bits(&s->pb, 1, 1); /* marker */                                 // 0.0
/*68  */             /* vbv buffer size: slightly greater than an I frame. We add         // 0.0
/*70  */                some margin just in case */                                       // 0.0
/*72  */             vbv_buffer_size = (3 * s->I_frame_bits) / (2 * 8);                   // 0.0
/*74  */             put_bits(&s->pb, 10, (vbv_buffer_size + 16383) / 16384);             // 0.0
/*76  */             put_bits(&s->pb, 1, 1); /* constrained parameter flag */             // 0.0
/*78  */             put_bits(&s->pb, 1, 0); /* no custom intra matrix */                 // 0.0
/*80  */             put_bits(&s->pb, 1, 0); /* no custom non intra matrix */             // 0.0
/*84  */             put_header(s, GOP_START_CODE);                                       // 0.0
/*86  */             put_bits(&s->pb, 1, 0); /* do drop frame */                          // 0.0
/*88  */             /* time code : we must convert from the real frame rate to a         // 0.0
/*90  */                fake mpeg frame rate in case of low frame rate */                 // 0.0
/*92  */             fps = frame_rate_tab[s->frame_rate_index];                           // 0.0
/*94  */             time_code = s->fake_picture_number * FRAME_RATE_BASE;                // 0.0
/*96  */             s->gop_picture_number = s->fake_picture_number;                      // 0.0
/*98  */             put_bits(&s->pb, 5, (UINT32)((time_code / (fps * 3600)) % 24));      // 0.0
/*100 */             put_bits(&s->pb, 6, (UINT32)((time_code / (fps * 60)) % 60));        // 0.0
/*102 */             put_bits(&s->pb, 1, 1);                                              // 0.0
/*104 */             put_bits(&s->pb, 6, (UINT32)((time_code / fps) % 60));               // 0.0
/*106 */             put_bits(&s->pb, 6, (UINT32)((time_code % fps) / FRAME_RATE_BASE));  // 0.0
/*108 */             put_bits(&s->pb, 1, 1); /* closed gop */                             // 0.0
/*110 */             put_bits(&s->pb, 1, 0); /* broken link */                            // 0.0
/*112 */         }                                                                        // 0.0
/*116 */         if (s->frame_rate < (24 * FRAME_RATE_BASE) && s->picture_number > 0) {   // 0.0
/*118 */             /* insert empty P pictures to slow down to the desired               // 0.0
/*120 */                frame rate. Each fake pictures takes about 20 bytes */            // 0.0
/*122 */             fps = frame_rate_tab[s->frame_rate_index];                           // 0.0
/*124 */             n = ((s->picture_number * fps) / s->frame_rate) - 1;                 // 0.0
/*126 */             while (s->fake_picture_number < n) {                                 // 0.0
/*128 */                 mpeg1_skip_picture(s, s->fake_picture_number -                   // 0.0
/*130 */                                    s->gop_picture_number);                       // 0.0
/*132 */                 s->fake_picture_number++;                                        // 0.0
/*134 */             }                                                                    // 0.0
/*138 */         }                                                                        // 0.0
/*140 */         s->fake_picture_number++;                                                // 0.0
/*142 */ }                                                                                // 0.0
