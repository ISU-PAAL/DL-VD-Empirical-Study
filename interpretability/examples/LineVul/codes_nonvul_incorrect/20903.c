// commit message FFmpeg@ca16618b01 (target=0, prob=0.9965519, correct=False): tinfoil patch: no array is written to in bulk before counts are validated; do not free frames that are not allocated; removed all of the output modes that no one uses and only PAL8 remains
/*0  */ static int xan_huffman_decode(unsigned char *dest, unsigned char *src)  // (1) 0.06769
/*2  */ {                                                                       // (22) 0.003077
/*4  */     unsigned char byte = *src++;                                        // (14) 0.03077
/*6  */     unsigned char ival = byte + 0x16;                                   // (11) 0.04308
/*8  */     unsigned char * ptr = src + byte*2;                                 // (10) 0.04308
/*10 */     unsigned char val = ival;                                           // (15) 0.03077
/*12 */     int counter = 0;                                                    // (16) 0.02462
/*16 */     unsigned char bits = *ptr++;                                        // (13) 0.03077
/*20 */     while ( val != 0x16 ) {                                             // (12) 0.03692
/*22 */         if ( (1 << counter) & bits )                                    // (4) 0.05231
/*24 */             val = src[byte + val - 0x17];                               // (0) 0.07077
/*26 */         else                                                            // (19) 0.02462
/*28 */             val = src[val - 0x17];                                      // (2) 0.06462
/*32 */         if ( val < 0x16 ) {                                             // (6) 0.04923
/*34 */             *dest++ = val;                                              // (3) 0.05231
/*36 */             val = ival;                                                 // (7) 0.04923
/*38 */         }                                                               // (17) 0.02462
/*42 */         if (counter++ == 7) {                                           // (8) 0.04615
/*44 */             counter = 0;                                                // (9) 0.04615
/*46 */             bits = *ptr++;                                              // (5) 0.04923
/*48 */         }                                                               // (18) 0.02462
/*50 */     }                                                                   // (21) 0.01231
/*54 */     return 0;                                                           // (20) 0.01846
/*56 */ }                                                                       // (23) 0.003077
