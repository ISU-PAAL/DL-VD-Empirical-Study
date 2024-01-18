// commit message FFmpeg@13705b69eb (target=1, prob=0.99726653, correct=True): mem corruption fix
/*0  */ static void spatial_decompose53i(DWTELEM *buffer, int width, int height, int stride){  // (6) 0.06437
/*2  */     int y;                                                                             // (16) 0.01484
/*4  */     DWTELEM *b0= buffer + mirror(-2-1, height-1)*stride;                               // (7) 0.06433
/*6  */     DWTELEM *b1= buffer + mirror(-2  , height-1)*stride;                               // (8) 0.06186
/*10 */     for(y=-2; y<height; y+=2){                                                         // (11) 0.04209
/*12 */         DWTELEM *b2= buffer + mirror(y+1, height-1)*stride;                            // (3) 0.07422
/*14 */         DWTELEM *b3= buffer + mirror(y+2, height-1)*stride;                            // (4) 0.07422
/*18 */ {START_TIMER                                                                           // (14) 0.01744
/*20 */         if(b1 <= b3)     horizontal_decompose53i(b2, width);                           // (2) 0.07919
/*22 */         if(y+2 < height) horizontal_decompose53i(b3, width);                           // (5) 0.06932
/*24 */ STOP_TIMER("horizontal_decompose53i")}                                                 // (10) 0.04242
/*28 */ {START_TIMER                                                                           // (15) 0.01737
/*30 */         if(b1 <= b3) vertical_decompose53iH0(b1, b2, b3, width);                       // (1) 0.08912
/*32 */         if(b0 <= b2) vertical_decompose53iL0(b0, b1, b2, width);                       // (0) 0.08929
/*34 */ STOP_TIMER("vertical_decompose53i*")}                                                  // (9) 0.0459
/*38 */         b0=b2;                                                                         // (12) 0.03219
/*40 */         b1=b3;                                                                         // (13) 0.03218
/*42 */     }                                                                                  // (17) 0.01007
/*44 */ }                                                                                      // (18) 0.002482
