// commit message FFmpeg@ebbcdc9ac0 (target=0, prob=0.13320243, correct=True): user specified motion estimation range limit h263 me range fixed (was smaller then needed)
/*0  */ void ff_fix_long_b_mvs(MpegEncContext * s, int16_t (*mv_table)[2], int f_code, int type)                       // (1) 0.07617
/*2  */ {                                                                                                              // (19) 0.001953
/*4  */     int y;                                                                                                     // (18) 0.01172
/*6  */     uint8_t * fcode_tab= s->fcode_tab;                                                                         // (8) 0.03906
/*10 */     // RAL: 8 in MPEG-1, 16 in MPEG-4                                                                          // (12) 0.03516
/*12 */     int range = (((s->codec_id == CODEC_ID_MPEG1VIDEO) ? 8 : 16) << f_code);                                   // (4) 0.07031
/*16 */     /* clip / convert to intra 16x16 type MVs */                                                               // (14) 0.03125
/*18 */     for(y=0; y<s->mb_height; y++){                                                                             // (9) 0.03906
/*20 */         int x;                                                                                                 // (17) 0.01953
/*22 */         int xy= (y+1)* (s->mb_width+2)+1;                                                                      // (6) 0.05273
/*24 */         int i= y*s->mb_width;                                                                                  // (13) 0.03516
/*26 */         for(x=0; x<s->mb_width; x++)                                                                           // (7) 0.04492
/*28 */             {                                                                                                  // (16) 0.02344
/*30 */             if (s->mb_type[i] & type)    // RAL: "type" test added...                                          // (2) 0.07227
/*32 */                 {                                                                                              // (15) 0.03125
/*34 */                 if (fcode_tab[mv_table[xy][0] + MAX_MV] > f_code || fcode_tab[mv_table[xy][0] + MAX_MV] == 0)  // (0) 0.127
/*36 */                     {                                                                                          // (11) 0.03906
/*38 */                     if(mv_table[xy][0]>0)                                                                      // (5) 0.06641
/*40 */                         mv_table[xy][0]=  range-1;                                                             // (3) 0.07227
/*42 */                     else                                                                                       // (10) 0.03906
/*44 */                         mv_table[xy][0]= -range;                                                               // 0.0
/*46 */                     }                                                                                          // 0.0
/*48 */                 if (fcode_tab[mv_table[xy][1] + MAX_MV] > f_code || fcode_tab[mv_table[xy][1] + MAX_MV] == 0)  // 0.0
/*50 */                     {                                                                                          // 0.0
/*52 */                     if(mv_table[xy][1]>0)                                                                      // 0.0
/*54 */                         mv_table[xy][1]=  range-1;                                                             // 0.0
/*56 */                     else                                                                                       // 0.0
/*58 */                         mv_table[xy][1]= -range;                                                               // 0.0
/*60 */             }                                                                                                  // 0.0
/*62 */             }                                                                                                  // 0.0
/*64 */             xy++;                                                                                              // 0.0
/*66 */             i++;                                                                                               // 0.0
/*68 */         }                                                                                                      // 0.0
/*70 */     }                                                                                                          // 0.0
/*72 */ }                                                                                                              // 0.0
