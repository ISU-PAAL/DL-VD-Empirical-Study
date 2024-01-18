// commit message FFmpeg@b164d66e35 (target=0, prob=0.27339956, correct=True): ape: make version-dependent decoding functions called via pointers
/*0  */ static void predictor_decode_mono(APEContext *ctx, int count)         // (7) 0.03906
/*2  */ {                                                                     // (17) 0.001953
/*4  */     APEPredictor *p = &ctx->predictor;                                // (11) 0.0332
/*6  */     int32_t *decoded0 = ctx->decoded[0];                              // (8) 0.03906
/*8  */     int32_t predictionA, currentA, A, sign;                           // (12) 0.0332
/*12 */     currentA = p->lastA[0];                                           // (15) 0.02539
/*16 */     while (count--) {                                                 // (16) 0.01758
/*18 */         A = *decoded0;                                                // (14) 0.02734
/*22 */         p->buf[YDELAYA] = currentA;                                   // (9) 0.03906
/*24 */         p->buf[YDELAYA - 1] = p->buf[YDELAYA] - p->buf[YDELAYA - 1];  // (4) 0.07812
/*28 */         predictionA = p->buf[YDELAYA    ] * p->coeffsA[0][0] +        // (6) 0.06836
/*30 */                       p->buf[YDELAYA - 1] * p->coeffsA[0][1] +        // (0) 0.08789
/*32 */                       p->buf[YDELAYA - 2] * p->coeffsA[0][2] +        // (1) 0.08789
/*34 */                       p->buf[YDELAYA - 3] * p->coeffsA[0][3];         // (2) 0.08594
/*38 */         currentA = A + (predictionA >> 10);                           // (10) 0.03711
/*42 */         p->buf[YADAPTCOEFFSA]     = APESIGN(p->buf[YDELAYA    ]);     // (3) 0.08008
/*44 */         p->buf[YADAPTCOEFFSA - 1] = APESIGN(p->buf[YDELAYA - 1]);     // (5) 0.07227
/*48 */         sign = APESIGN(A);                                            // (13) 0.0293
/*50 */         p->coeffsA[0][0] += p->buf[YADAPTCOEFFSA    ] * sign;         // 0.0
/*52 */         p->coeffsA[0][1] += p->buf[YADAPTCOEFFSA - 1] * sign;         // 0.0
/*54 */         p->coeffsA[0][2] += p->buf[YADAPTCOEFFSA - 2] * sign;         // 0.0
/*56 */         p->coeffsA[0][3] += p->buf[YADAPTCOEFFSA - 3] * sign;         // 0.0
/*60 */         p->buf++;                                                     // 0.0
/*64 */         /* Have we filled the history buffer? */                      // 0.0
/*66 */         if (p->buf == p->historybuffer + HISTORY_SIZE) {              // 0.0
/*68 */             memmove(p->historybuffer, p->buf,                         // 0.0
/*70 */                     PREDICTOR_SIZE * sizeof(*p->historybuffer));      // 0.0
/*72 */             p->buf = p->historybuffer;                                // 0.0
/*74 */         }                                                             // 0.0
/*78 */         p->filterA[0] = currentA + ((p->filterA[0] * 31) >> 5);       // 0.0
/*80 */         *(decoded0++) = p->filterA[0];                                // 0.0
/*82 */     }                                                                 // 0.0
/*86 */     p->lastA[0] = currentA;                                           // 0.0
/*88 */ }                                                                     // 0.0
