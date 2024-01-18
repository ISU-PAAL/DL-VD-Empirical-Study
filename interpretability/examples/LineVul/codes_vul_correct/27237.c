// commit message FFmpeg@afa982fdae (target=1, prob=0.7531759, correct=True): corrected mpeg audio encoding overflows - now it should give correct quality even for very high volumes
/*0   */ static void filter(MpegAudioContext *s, int ch, short *samples, int incr)  // (7) 0.04492
/*2   */ {                                                                          // (26) 0.001953
/*4   */     short *p, *q;                                                          // (20) 0.01953
/*6   */     int sum, offset, i, j, norm, n;                                        // (13) 0.03125
/*8   */     short tmp[64];                                                         // (23) 0.01562
/*10  */     int tmp1[32];                                                          // (22) 0.01758
/*12  */     int *out;                                                              // (25) 0.01367
/*16  */     //    print_pow1(samples, 1152);                                       // (12) 0.03711
/*20  */     offset = s->samples_offset[ch];                                        // (16) 0.02734
/*22  */     out = &s->sb_samples[ch][0][0][0];                                     // (8) 0.04102
/*24  */     for(j=0;j<36;j++) {                                                    // (15) 0.03125
/*26  */         /* 32 samples at once */                                           // (19) 0.02539
/*28  */         for(i=0;i<32;i++) {                                                // (10) 0.03906
/*30  */             s->samples_buf[ch][offset + (31 - i)] = samples[0];            // (0) 0.0625
/*32  */             samples += incr;                                               // (14) 0.03125
/*34  */         }                                                                  // (24) 0.01562
/*38  */         /* filter */                                                       // (21) 0.01953
/*40  */         p = s->samples_buf[ch] + offset;                                   // (9) 0.04102
/*42  */         q = filter_bank;                                                   // (18) 0.02539
/*44  */         /* maxsum = 23169 */                                               // (17) 0.02734
/*46  */         for(i=0;i<64;i++) {                                                // (11) 0.03906
/*48  */             sum = p[0*64] * q[0*64];                                       // (2) 0.05078
/*50  */             sum += p[1*64] * q[1*64];                                      // (3) 0.05078
/*52  */             sum += p[2*64] * q[2*64];                                      // (4) 0.05078
/*54  */             sum += p[3*64] * q[3*64];                                      // (5) 0.05078
/*56  */             sum += p[4*64] * q[4*64];                                      // (1) 0.05078
/*58  */             sum += p[5*64] * q[5*64];                                      // (6) 0.05078
/*60  */             sum += p[6*64] * q[6*64];                                      // 0.0
/*62  */             sum += p[7*64] * q[7*64];                                      // 0.0
/*64  */             tmp[i] = sum >> 14;                                            // 0.0
/*66  */             p++;                                                           // 0.0
/*68  */             q++;                                                           // 0.0
/*70  */         }                                                                  // 0.0
/*72  */         tmp1[0] = tmp[16];                                                 // 0.0
/*74  */         for( i=1; i<=16; i++ ) tmp1[i] = tmp[i+16]+tmp[16-i];              // 0.0
/*76  */         for( i=17; i<=31; i++ ) tmp1[i] = tmp[i+16]-tmp[80-i];             // 0.0
/*80  */         /* integer IDCT 32 with normalization. XXX: There may be some      // 0.0
/*82  */            overflow left */                                                // 0.0
/*84  */         norm = 0;                                                          // 0.0
/*86  */         for(i=0;i<32;i++) {                                                // 0.0
/*88  */             norm |= abs(tmp1[i]);                                          // 0.0
/*90  */         }                                                                  // 0.0
/*92  */         n = av_log2(norm) - 12;                                            // 0.0
/*94  */         if (n > 0) {                                                       // 0.0
/*96  */             for(i=0;i<32;i++)                                              // 0.0
/*98  */                 tmp1[i] >>= n;                                             // 0.0
/*100 */         } else {                                                           // 0.0
/*102 */             n = 0;                                                         // 0.0
/*104 */         }                                                                  // 0.0
/*108 */         idct32(out, tmp1, s->sblimit, n);                                  // 0.0
/*112 */         /* advance of 32 samples */                                        // 0.0
/*114 */         offset -= 32;                                                      // 0.0
/*116 */         out += 32;                                                         // 0.0
/*118 */         /* handle the wrap around */                                       // 0.0
/*120 */         if (offset < 0) {                                                  // 0.0
/*122 */             memmove(s->samples_buf[ch] + SAMPLES_BUF_SIZE - (512 - 32),    // 0.0
/*124 */                     s->samples_buf[ch], (512 - 32) * 2);                   // 0.0
/*126 */             offset = SAMPLES_BUF_SIZE - 512;                               // 0.0
/*128 */         }                                                                  // 0.0
/*130 */     }                                                                      // 0.0
/*132 */     s->samples_offset[ch] = offset;                                        // 0.0
/*136 */     //    print_pow(s->sb_samples, 1152);                                  // 0.0
/*138 */ }                                                                          // 0.0
