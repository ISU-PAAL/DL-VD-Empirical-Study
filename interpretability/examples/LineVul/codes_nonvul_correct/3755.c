// commit message qemu@1ea879e558 (target=0, prob=0.12626705, correct=True): Make audio violate POSIX less
/*0  */ void audio_pcm_init_info (struct audio_pcm_info *info, audsettings_t *as)  // (1) 0.06667
/*2  */ {                                                                          // (28) 0.002469
/*4  */     int bits = 8, sign = 0, shift = 0;                                     // (5) 0.03951
/*8  */     switch (as->fmt) {                                                     // (14) 0.02716
/*10 */     case AUD_FMT_S8:                                                       // (8) 0.02963
/*12 */         sign = 1;                                                          // (15) 0.02716
/*14 */     case AUD_FMT_U8:                                                       // (10) 0.02963
/*16 */         break;                                                             // (22) 0.02222
/*20 */     case AUD_FMT_S16:                                                      // (9) 0.02963
/*22 */         sign = 1;                                                          // (16) 0.02716
/*24 */     case AUD_FMT_U16:                                                      // (11) 0.02963
/*26 */         bits = 16;                                                         // (17) 0.02716
/*28 */         shift = 1;                                                         // (18) 0.02716
/*30 */         break;                                                             // (23) 0.02222
/*34 */     case AUD_FMT_S32:                                                      // (12) 0.02963
/*36 */         sign = 1;                                                          // (19) 0.02716
/*38 */     case AUD_FMT_U32:                                                      // (13) 0.02963
/*40 */         bits = 32;                                                         // (20) 0.02716
/*42 */         shift = 2;                                                         // (21) 0.02716
/*44 */         break;                                                             // (24) 0.02222
/*46 */     }                                                                      // (27) 0.009877
/*50 */     info->freq = as->freq;                                                 // (7) 0.0321
/*52 */     info->bits = bits;                                                     // (25) 0.02222
/*54 */     info->sign = sign;                                                     // (26) 0.02222
/*56 */     info->nchannels = as->nchannels;                                       // (6) 0.03704
/*58 */     info->shift = (as->nchannels == 2) + shift;                            // (3) 0.04691
/*60 */     info->align = (1 << info->shift) - 1;                                  // (4) 0.04198
/*62 */     info->bytes_per_second = info->freq << info->shift;                    // (2) 0.04938
/*64 */     info->swap_endianness = (as->endianness != AUDIO_HOST_ENDIANNESS);     // (0) 0.0716
/*66 */ }                                                                          // (29) 0.002469
