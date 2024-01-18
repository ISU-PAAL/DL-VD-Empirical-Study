// commit message FFmpeg@8542f9c4f1 (target=1, prob=0.32177433, correct=False): replaygain: correctly parse peak values
/*0  */ static int32_t parse_gain(const char *gain)       // (6) 0.04403
/*2  */ {                                                 // (23) 0.003145
/*4  */     char *fraction;                               // (17) 0.02516
/*6  */     int  scale = 10000;                           // (16) 0.0283
/*8  */     int32_t mb = 0;                               // (13) 0.03774
/*10 */     int sign   = 1;                               // (14) 0.03145
/*12 */     int db;                                       // (20) 0.01887
/*16 */     if (!gain)                                    // (19) 0.02201
/*18 */         return INT32_MIN;                         // (11) 0.04088
/*22 */     gain += strspn(gain, " \t");                  // (5) 0.04717
/*26 */     if (*gain == '-')                             // (15) 0.03145
/*28 */         sign = -1;                                // (12) 0.03774
/*32 */     db = strtol(gain, &fraction, 0);              // (3) 0.05346
/*34 */     if (*fraction++ == '.') {                     // (8) 0.04088
/*36 */         while (av_isdigit(*fraction) && scale) {  // (2) 0.06918
/*38 */             mb += scale * (*fraction - '0');      // (1) 0.07233
/*40 */             scale /= 10;                          // (4) 0.05031
/*42 */             fraction++;                           // (9) 0.04088
/*44 */         }                                         // (18) 0.02516
/*46 */     }                                             // (21) 0.01258
/*50 */     if (abs(db) > (INT32_MAX - mb) / 100000)      // (0) 0.07233
/*52 */         return INT32_MIN;                         // (10) 0.04088
/*56 */     return db * 100000 + sign * mb;               // (7) 0.04403
/*58 */ }                                                 // (22) 0.003145
