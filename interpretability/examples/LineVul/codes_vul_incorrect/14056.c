// commit message FFmpeg@0ecca7a49f (target=1, prob=0.34869188, correct=False): various security fixes and precautionary checks
/*0   */ static int pnm_decode_header(AVCodecContext *avctx, PNMContext * const s){           // (7) 0.04883
/*2   */     char buf1[32], tuple_type[32];                                                   // (16) 0.0293
/*4   */     int h, w, depth, maxval;;                                                        // (17) 0.02539
/*8   */     pnm_get(s, buf1, sizeof(buf1));                                                  // (10) 0.03516
/*10  */     if (!strcmp(buf1, "P4")) {                                                       // (15) 0.03125
/*12  */         avctx->pix_fmt = PIX_FMT_MONOWHITE;                                          // (5) 0.05273
/*14  */     } else if (!strcmp(buf1, "P5")) {                                                // (12) 0.03516
/*16  */         if (avctx->codec_id == CODEC_ID_PGMYUV)                                      // (3) 0.05469
/*18  */             avctx->pix_fmt = PIX_FMT_YUV420P;                                        // (0) 0.06055
/*20  */         else                                                                         // (23) 0.01562
/*22  */             avctx->pix_fmt = PIX_FMT_GRAY8;                                          // (2) 0.05859
/*24  */     } else if (!strcmp(buf1, "P6")) {                                                // (14) 0.03516
/*26  */         avctx->pix_fmt = PIX_FMT_RGB24;                                              // (8) 0.04883
/*28  */     } else if (!strcmp(buf1, "P7")) {                                                // (13) 0.03516
/*30  */         w = -1;                                                                      // (21) 0.02344
/*32  */         h = -1;                                                                      // (22) 0.02344
/*34  */         maxval = -1;                                                                 // (18) 0.02539
/*36  */         depth = -1;                                                                  // (20) 0.02344
/*38  */         tuple_type[0] = '\0';                                                        // (11) 0.03516
/*40  */         for(;;) {                                                                    // (19) 0.02344
/*42  */             pnm_get(s, buf1, sizeof(buf1));                                          // (6) 0.05078
/*44  */             if (!strcmp(buf1, "WIDTH")) {                                            // (9) 0.04883
/*46  */                 pnm_get(s, buf1, sizeof(buf1));                                      // (1) 0.05859
/*48  */                 w = strtol(buf1, NULL, 10);                                          // (4) 0.05469
/*50  */             } else if (!strcmp(buf1, "HEIGHT")) {                                    // 0.0
/*52  */                 pnm_get(s, buf1, sizeof(buf1));                                      // 0.0
/*54  */                 h = strtol(buf1, NULL, 10);                                          // 0.0
/*56  */             } else if (!strcmp(buf1, "DEPTH")) {                                     // 0.0
/*58  */                 pnm_get(s, buf1, sizeof(buf1));                                      // 0.0
/*60  */                 depth = strtol(buf1, NULL, 10);                                      // 0.0
/*62  */             } else if (!strcmp(buf1, "MAXVAL")) {                                    // 0.0
/*64  */                 pnm_get(s, buf1, sizeof(buf1));                                      // 0.0
/*66  */                 maxval = strtol(buf1, NULL, 10);                                     // 0.0
/*68  */             } else if (!strcmp(buf1, "TUPLETYPE")) {                                 // 0.0
/*70  */                 pnm_get(s, tuple_type, sizeof(tuple_type));                          // 0.0
/*72  */             } else if (!strcmp(buf1, "ENDHDR")) {                                    // 0.0
/*74  */                 break;                                                               // 0.0
/*76  */             } else {                                                                 // 0.0
/*78  */                 return -1;                                                           // 0.0
/*80  */             }                                                                        // 0.0
/*82  */         }                                                                            // 0.0
/*84  */         /* check that all tags are present */                                        // 0.0
/*86  */         if (w <= 0 || h <= 0 || maxval <= 0 || depth <= 0 || tuple_type[0] == '\0')  // 0.0
/*88  */             return -1;                                                               // 0.0
/*90  */         avctx->width = w;                                                            // 0.0
/*92  */         avctx->height = h;                                                           // 0.0
/*94  */         if (depth == 1) {                                                            // 0.0
/*96  */             if (maxval == 1)                                                         // 0.0
/*98  */                 avctx->pix_fmt = PIX_FMT_MONOWHITE;                                  // 0.0
/*100 */             else                                                                     // 0.0
/*102 */                 avctx->pix_fmt = PIX_FMT_GRAY8;                                      // 0.0
/*104 */         } else if (depth == 3) {                                                     // 0.0
/*106 */             avctx->pix_fmt = PIX_FMT_RGB24;                                          // 0.0
/*108 */         } else if (depth == 4) {                                                     // 0.0
/*110 */             avctx->pix_fmt = PIX_FMT_RGBA32;                                         // 0.0
/*112 */         } else {                                                                     // 0.0
/*114 */             return -1;                                                               // 0.0
/*116 */         }                                                                            // 0.0
/*118 */         return 0;                                                                    // 0.0
/*120 */     } else {                                                                         // 0.0
/*122 */         return -1;                                                                   // 0.0
/*124 */     }                                                                                // 0.0
/*126 */     pnm_get(s, buf1, sizeof(buf1));                                                  // 0.0
/*128 */     avctx->width = atoi(buf1);                                                       // 0.0
/*130 */     if (avctx->width <= 0)                                                           // 0.0
/*132 */         return -1;                                                                   // 0.0
/*134 */     pnm_get(s, buf1, sizeof(buf1));                                                  // 0.0
/*136 */     avctx->height = atoi(buf1);                                                      // 0.0
/*138 */     if (avctx->height <= 0)                                                          // 0.0
/*140 */         return -1;                                                                   // 0.0
/*142 */     if (avctx->pix_fmt != PIX_FMT_MONOWHITE) {                                       // 0.0
/*144 */         pnm_get(s, buf1, sizeof(buf1));                                              // 0.0
/*146 */     }                                                                                // 0.0
/*150 */     /* more check if YUV420 */                                                       // 0.0
/*152 */     if (avctx->pix_fmt == PIX_FMT_YUV420P) {                                         // 0.0
/*154 */         if ((avctx->width & 1) != 0)                                                 // 0.0
/*156 */             return -1;                                                               // 0.0
/*158 */         h = (avctx->height * 2);                                                     // 0.0
/*160 */         if ((h % 3) != 0)                                                            // 0.0
/*162 */             return -1;                                                               // 0.0
/*164 */         h /= 3;                                                                      // 0.0
/*166 */         avctx->height = h;                                                           // 0.0
/*168 */     }                                                                                // 0.0
/*170 */     return 0;                                                                        // 0.0
/*172 */ }                                                                                    // 0.0
