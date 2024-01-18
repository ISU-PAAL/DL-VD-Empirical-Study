// commit message FFmpeg@f6687bf5f8 (target=0, prob=0.6550345, correct=False): xtea: invert branch and loop precedence
/*0  */ void av_xtea_crypt(AVXTEA *ctx, uint8_t *dst, const uint8_t *src, int count,  // (0) 0.06836
/*2  */                    uint8_t *iv, int decrypt)                                  // (6) 0.05469
/*4  */ {                                                                             // (24) 0.001953
/*6  */     int i;                                                                    // (23) 0.01172
/*10 */     while (count > 0) {                                                       // (20) 0.01953
/*12 */         if (decrypt) {                                                        // (14) 0.02539
/*14 */             xtea_crypt_ecb(ctx, dst, src, decrypt);                           // (5) 0.05469
/*18 */             if (iv) {                                                         // (11) 0.03125
/*20 */                 for (i = 0; i < 8; i++)                                       // (7) 0.05273
/*22 */                     dst[i] = dst[i] ^ iv[i];                                  // (1) 0.06445
/*24 */                 memcpy(iv, src, 8);                                           // (9) 0.04883
/*26 */             }                                                                 // (17) 0.02344
/*28 */         } else {                                                              // (21) 0.01953
/*30 */             if (iv) {                                                         // (12) 0.03125
/*32 */                 for (i = 0; i < 8; i++)                                       // (8) 0.05273
/*34 */                     dst[i] = src[i] ^ iv[i];                                  // (2) 0.06445
/*36 */                 xtea_crypt_ecb(ctx, dst, dst, decrypt);                       // (4) 0.0625
/*38 */                 memcpy(iv, dst, 8);                                           // (10) 0.04883
/*40 */             } else {                                                          // (13) 0.02734
/*42 */                 xtea_crypt_ecb(ctx, dst, src, decrypt);                       // (3) 0.0625
/*44 */             }                                                                 // (18) 0.02344
/*46 */         }                                                                     // (22) 0.01562
/*50 */         src   += 8;                                                           // (16) 0.02539
/*52 */         dst   += 8;                                                           // (15) 0.02539
/*54 */         count -= 8;                                                           // (19) 0.02148
/*56 */     }                                                                         // 0.0
/*58 */ }                                                                             // 0.0
