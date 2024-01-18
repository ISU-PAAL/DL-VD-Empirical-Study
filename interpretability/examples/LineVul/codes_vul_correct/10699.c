// commit message FFmpeg@15ccaa344c (target=1, prob=0.64587295, correct=True): avcodec/mpegaudiodec: Eliminate many undefined operations
/*0   */ void dct32(INTFLOAT *out, const INTFLOAT *tab)                        // (4) 0.03906
/*2   */ {                                                                     // (27) 0.001953
/*4   */     INTFLOAT tmp0, tmp1;                                              // (19) 0.02539
/*8   */     INTFLOAT val0 , val1 , val2 , val3 , val4 , val5 , val6 , val7 ,  // (3) 0.06055
/*10  */              val8 , val9 , val10, val11, val12, val13, val14, val15,  // (0) 0.07031
/*12  */              val16, val17, val18, val19, val20, val21, val22, val23,  // (1) 0.07031
/*14  */              val24, val25, val26, val27, val28, val29, val30, val31;  // (2) 0.07031
/*18  */     /* pass 1 */                                                      // (21) 0.01367
/*20  */     BF0( 0, 31, COS0_0 , 1);                                          // (10) 0.03516
/*22  */     BF0(15, 16, COS0_15, 5);                                          // (5) 0.03516
/*24  */     /* pass 2 */                                                      // (23) 0.01367
/*26  */     BF( 0, 15, COS1_0 , 1);                                           // (18) 0.0332
/*28  */     BF(16, 31,-COS1_0 , 1);                                           // (16) 0.0332
/*30  */     /* pass 1 */                                                      // (20) 0.01367
/*32  */     BF0( 7, 24, COS0_7 , 1);                                          // (11) 0.03516
/*34  */     BF0( 8, 23, COS0_8 , 1);                                          // (7) 0.03516
/*36  */     /* pass 2 */                                                      // (24) 0.01367
/*38  */     BF( 7,  8, COS1_7 , 4);                                           // (8) 0.03516
/*40  */     BF(23, 24,-COS1_7 , 4);                                           // (14) 0.0332
/*42  */     /* pass 3 */                                                      // (25) 0.01367
/*44  */     BF( 0,  7, COS2_0 , 1);                                           // (6) 0.03516
/*46  */     BF( 8, 15,-COS2_0 , 1);                                           // (13) 0.0332
/*48  */     BF(16, 23, COS2_0 , 1);                                           // (17) 0.0332
/*50  */     BF(24, 31,-COS2_0 , 1);                                           // (15) 0.0332
/*52  */     /* pass 1 */                                                      // (26) 0.01367
/*54  */     BF0( 3, 28, COS0_3 , 1);                                          // (12) 0.03516
/*56  */     BF0(12, 19, COS0_12, 2);                                          // (9) 0.03516
/*58  */     /* pass 2 */                                                      // (22) 0.01367
/*60  */     BF( 3, 12, COS1_3 , 1);                                           // 0.0
/*62  */     BF(19, 28,-COS1_3 , 1);                                           // 0.0
/*64  */     /* pass 1 */                                                      // 0.0
/*66  */     BF0( 4, 27, COS0_4 , 1);                                          // 0.0
/*68  */     BF0(11, 20, COS0_11, 2);                                          // 0.0
/*70  */     /* pass 2 */                                                      // 0.0
/*72  */     BF( 4, 11, COS1_4 , 1);                                           // 0.0
/*74  */     BF(20, 27,-COS1_4 , 1);                                           // 0.0
/*76  */     /* pass 3 */                                                      // 0.0
/*78  */     BF( 3,  4, COS2_3 , 3);                                           // 0.0
/*80  */     BF(11, 12,-COS2_3 , 3);                                           // 0.0
/*82  */     BF(19, 20, COS2_3 , 3);                                           // 0.0
/*84  */     BF(27, 28,-COS2_3 , 3);                                           // 0.0
/*86  */     /* pass 4 */                                                      // 0.0
/*88  */     BF( 0,  3, COS3_0 , 1);                                           // 0.0
/*90  */     BF( 4,  7,-COS3_0 , 1);                                           // 0.0
/*92  */     BF( 8, 11, COS3_0 , 1);                                           // 0.0
/*94  */     BF(12, 15,-COS3_0 , 1);                                           // 0.0
/*96  */     BF(16, 19, COS3_0 , 1);                                           // 0.0
/*98  */     BF(20, 23,-COS3_0 , 1);                                           // 0.0
/*100 */     BF(24, 27, COS3_0 , 1);                                           // 0.0
/*102 */     BF(28, 31,-COS3_0 , 1);                                           // 0.0
/*110 */     /* pass 1 */                                                      // 0.0
/*112 */     BF0( 1, 30, COS0_1 , 1);                                          // 0.0
/*114 */     BF0(14, 17, COS0_14, 3);                                          // 0.0
/*116 */     /* pass 2 */                                                      // 0.0
/*118 */     BF( 1, 14, COS1_1 , 1);                                           // 0.0
/*120 */     BF(17, 30,-COS1_1 , 1);                                           // 0.0
/*122 */     /* pass 1 */                                                      // 0.0
/*124 */     BF0( 6, 25, COS0_6 , 1);                                          // 0.0
/*126 */     BF0( 9, 22, COS0_9 , 1);                                          // 0.0
/*128 */     /* pass 2 */                                                      // 0.0
/*130 */     BF( 6,  9, COS1_6 , 2);                                           // 0.0
/*132 */     BF(22, 25,-COS1_6 , 2);                                           // 0.0
/*134 */     /* pass 3 */                                                      // 0.0
/*136 */     BF( 1,  6, COS2_1 , 1);                                           // 0.0
/*138 */     BF( 9, 14,-COS2_1 , 1);                                           // 0.0
/*140 */     BF(17, 22, COS2_1 , 1);                                           // 0.0
/*142 */     BF(25, 30,-COS2_1 , 1);                                           // 0.0
/*146 */     /* pass 1 */                                                      // 0.0
/*148 */     BF0( 2, 29, COS0_2 , 1);                                          // 0.0
/*150 */     BF0(13, 18, COS0_13, 3);                                          // 0.0
/*152 */     /* pass 2 */                                                      // 0.0
/*154 */     BF( 2, 13, COS1_2 , 1);                                           // 0.0
/*156 */     BF(18, 29,-COS1_2 , 1);                                           // 0.0
/*158 */     /* pass 1 */                                                      // 0.0
/*160 */     BF0( 5, 26, COS0_5 , 1);                                          // 0.0
/*162 */     BF0(10, 21, COS0_10, 1);                                          // 0.0
/*164 */     /* pass 2 */                                                      // 0.0
/*166 */     BF( 5, 10, COS1_5 , 2);                                           // 0.0
/*168 */     BF(21, 26,-COS1_5 , 2);                                           // 0.0
/*170 */     /* pass 3 */                                                      // 0.0
/*172 */     BF( 2,  5, COS2_2 , 1);                                           // 0.0
/*174 */     BF(10, 13,-COS2_2 , 1);                                           // 0.0
/*176 */     BF(18, 21, COS2_2 , 1);                                           // 0.0
/*178 */     BF(26, 29,-COS2_2 , 1);                                           // 0.0
/*180 */     /* pass 4 */                                                      // 0.0
/*182 */     BF( 1,  2, COS3_1 , 2);                                           // 0.0
/*184 */     BF( 5,  6,-COS3_1 , 2);                                           // 0.0
/*186 */     BF( 9, 10, COS3_1 , 2);                                           // 0.0
/*188 */     BF(13, 14,-COS3_1 , 2);                                           // 0.0
/*190 */     BF(17, 18, COS3_1 , 2);                                           // 0.0
/*192 */     BF(21, 22,-COS3_1 , 2);                                           // 0.0
/*194 */     BF(25, 26, COS3_1 , 2);                                           // 0.0
/*196 */     BF(29, 30,-COS3_1 , 2);                                           // 0.0
/*200 */     /* pass 5 */                                                      // 0.0
/*202 */     BF1( 0,  1,  2,  3);                                              // 0.0
/*204 */     BF2( 4,  5,  6,  7);                                              // 0.0
/*206 */     BF1( 8,  9, 10, 11);                                              // 0.0
/*208 */     BF2(12, 13, 14, 15);                                              // 0.0
/*210 */     BF1(16, 17, 18, 19);                                              // 0.0
/*212 */     BF2(20, 21, 22, 23);                                              // 0.0
/*214 */     BF1(24, 25, 26, 27);                                              // 0.0
/*216 */     BF2(28, 29, 30, 31);                                              // 0.0
/*220 */     /* pass 6 */                                                      // 0.0
/*224 */     ADD( 8, 12);                                                      // 0.0
/*226 */     ADD(12, 10);                                                      // 0.0
/*228 */     ADD(10, 14);                                                      // 0.0
/*230 */     ADD(14,  9);                                                      // 0.0
/*232 */     ADD( 9, 13);                                                      // 0.0
/*234 */     ADD(13, 11);                                                      // 0.0
/*236 */     ADD(11, 15);                                                      // 0.0
/*240 */     out[ 0] = val0;                                                   // 0.0
/*242 */     out[16] = val1;                                                   // 0.0
/*244 */     out[ 8] = val2;                                                   // 0.0
/*246 */     out[24] = val3;                                                   // 0.0
/*248 */     out[ 4] = val4;                                                   // 0.0
/*250 */     out[20] = val5;                                                   // 0.0
/*252 */     out[12] = val6;                                                   // 0.0
/*254 */     out[28] = val7;                                                   // 0.0
/*256 */     out[ 2] = val8;                                                   // 0.0
/*258 */     out[18] = val9;                                                   // 0.0
/*260 */     out[10] = val10;                                                  // 0.0
/*262 */     out[26] = val11;                                                  // 0.0
/*264 */     out[ 6] = val12;                                                  // 0.0
/*266 */     out[22] = val13;                                                  // 0.0
/*268 */     out[14] = val14;                                                  // 0.0
/*270 */     out[30] = val15;                                                  // 0.0
/*274 */     ADD(24, 28);                                                      // 0.0
/*276 */     ADD(28, 26);                                                      // 0.0
/*278 */     ADD(26, 30);                                                      // 0.0
/*280 */     ADD(30, 25);                                                      // 0.0
/*282 */     ADD(25, 29);                                                      // 0.0
/*284 */     ADD(29, 27);                                                      // 0.0
/*286 */     ADD(27, 31);                                                      // 0.0
/*290 */     out[ 1] = val16 + val24;                                          // 0.0
/*292 */     out[17] = val17 + val25;                                          // 0.0
/*294 */     out[ 9] = val18 + val26;                                          // 0.0
/*296 */     out[25] = val19 + val27;                                          // 0.0
/*298 */     out[ 5] = val20 + val28;                                          // 0.0
/*300 */     out[21] = val21 + val29;                                          // 0.0
/*302 */     out[13] = val22 + val30;                                          // 0.0
/*304 */     out[29] = val23 + val31;                                          // 0.0
/*306 */     out[ 3] = val24 + val20;                                          // 0.0
/*308 */     out[19] = val25 + val21;                                          // 0.0
/*310 */     out[11] = val26 + val22;                                          // 0.0
/*312 */     out[27] = val27 + val23;                                          // 0.0
/*314 */     out[ 7] = val28 + val18;                                          // 0.0
/*316 */     out[23] = val29 + val19;                                          // 0.0
/*318 */     out[15] = val30 + val17;                                          // 0.0
/*320 */     out[31] = val31;                                                  // 0.0
/*322 */ }                                                                     // 0.0
