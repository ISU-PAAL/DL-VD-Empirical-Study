// commit message FFmpeg@4ffe5e2aa5 (target=1, prob=0.47335073, correct=False): huffyuv: add padding to classic (v1) huffman tables.
/*0  */ static int read_old_huffman_tables(HYuvContext *s){                                 // (12) 0.03711
/*2  */ #if 1                                                                               // (22) 0.005859
/*4  */     GetBitContext gb;                                                               // (18) 0.01758
/*6  */     int i;                                                                          // (19) 0.01172
/*10 */     init_get_bits(&gb, classic_shift_luma, sizeof(classic_shift_luma)*8);           // (6) 0.05664
/*12 */     if(read_len_table(s->len[0], &gb)<0)                                            // (10) 0.04492
/*14 */         return -1;                                                                  // (17) 0.02148
/*16 */     init_get_bits(&gb, classic_shift_chroma, sizeof(classic_shift_chroma)*8);       // (7) 0.05664
/*18 */     if(read_len_table(s->len[1], &gb)<0)                                            // (9) 0.04492
/*20 */         return -1;                                                                  // (16) 0.02148
/*24 */     for(i=0; i<256; i++) s->bits[0][i] = classic_add_luma  [i];                     // (1) 0.06641
/*26 */     for(i=0; i<256; i++) s->bits[1][i] = classic_add_chroma[i];                     // (3) 0.06445
/*30 */     if(s->bitstream_bpp >= 24){                                                     // (14) 0.0293
/*32 */         memcpy(s->bits[1], s->bits[0], 256*sizeof(uint32_t));                       // (4) 0.06445
/*34 */         memcpy(s->len[1] , s->len [0], 256*sizeof(uint8_t));                        // (2) 0.06641
/*36 */     }                                                                               // (21) 0.007812
/*38 */     memcpy(s->bits[2], s->bits[1], 256*sizeof(uint32_t));                           // (8) 0.05664
/*40 */     memcpy(s->len[2] , s->len [1], 256*sizeof(uint8_t));                            // (5) 0.05859
/*44 */     for(i=0; i<3; i++){                                                             // (13) 0.03125
/*46 */         ff_free_vlc(&s->vlc[i]);                                                    // (11) 0.04102
/*48 */         init_vlc(&s->vlc[i], VLC_BITS, 256, s->len[i], 1, 1, s->bits[i], 4, 4, 0);  // (0) 0.0957
/*50 */     }                                                                               // (20) 0.007813
/*54 */     generate_joint_tables(s);                                                       // (15) 0.02539
/*58 */     return 0;                                                                       // 0.0
/*60 */ #else                                                                               // 0.0
/*62 */     av_log(s->avctx, AV_LOG_DEBUG, "v1 huffyuv is not supported \n");               // 0.0
/*64 */     return -1;                                                                      // 0.0
/*66 */ #endif                                                                              // 0.0
/*68 */ }                                                                                   // 0.0
