// commit message FFmpeg@3a83b2461e (target=1, prob=0.64167506, correct=True): dnxhdenc: fix signed overflows
/*0   */ static int dnxhd_encode_rdo(AVCodecContext *avctx, DNXHDEncContext *ctx)                                       // (4) 0.05664
/*2   */ {                                                                                                              // (23) 0.001953
/*4   */     int lambda, up_step, down_step;                                                                            // (14) 0.02734
/*6   */     int last_lower = INT_MAX, last_higher = 0;                                                                 // (11) 0.03516
/*8   */     int x, y, q;                                                                                               // (18) 0.01953
/*12  */     for (q = 1; q < avctx->qmax; q++) {                                                                        // (10) 0.03906
/*14  */         ctx->qscale = q;                                                                                       // (13) 0.0293
/*16  */         avctx->execute2(avctx, dnxhd_calc_bits_thread, NULL, NULL, ctx->m.mb_height);                          // (0) 0.08008
/*18  */     }                                                                                                          // (22) 0.007812
/*20  */     up_step = down_step = 2<<LAMBDA_FRAC_BITS;                                                                 // (7) 0.04688
/*22  */     lambda = ctx->lambda;                                                                                      // (19) 0.01953
/*26  */     for (;;) {                                                                                                 // (20) 0.01562
/*28  */         int bits = 0;                                                                                          // (16) 0.02344
/*30  */         int end = 0;                                                                                           // (17) 0.02344
/*32  */         if (lambda == last_higher) {                                                                           // (12) 0.03125
/*34  */             lambda++;                                                                                          // (15) 0.02539
/*36  */             end = 1; // need to set final qscales/bits                                                         // (6) 0.04883
/*38  */         }                                                                                                      // (21) 0.01562
/*40  */         for (y = 0; y < ctx->m.mb_height; y++) {                                                               // (5) 0.05273
/*42  */             for (x = 0; x < ctx->m.mb_width; x++) {                                                            // (2) 0.06055
/*44  */                 unsigned min = UINT_MAX;                                                                       // (8) 0.04492
/*46  */                 int qscale = 1;                                                                                // (9) 0.04102
/*48  */                 int mb = y*ctx->m.mb_width+x;                                                                  // (3) 0.06055
/*50  */                 for (q = 1; q < avctx->qmax; q++) {                                                            // (1) 0.0625
/*52  */                     unsigned score = ctx->mb_rc[q][mb].bits*lambda+(ctx->mb_rc[q][mb].ssd<<LAMBDA_FRAC_BITS);  // 0.0
/*54  */                     if (score < min) {                                                                         // 0.0
/*56  */                         min = score;                                                                           // 0.0
/*58  */                         qscale = q;                                                                            // 0.0
/*60  */                     }                                                                                          // 0.0
/*62  */                 }                                                                                              // 0.0
/*64  */                 bits += ctx->mb_rc[qscale][mb].bits;                                                           // 0.0
/*66  */                 ctx->mb_qscale[mb] = qscale;                                                                   // 0.0
/*68  */                 ctx->mb_bits[mb] = ctx->mb_rc[qscale][mb].bits;                                                // 0.0
/*70  */             }                                                                                                  // 0.0
/*72  */             bits = (bits+31)&~31; // padding                                                                   // 0.0
/*74  */             if (bits > ctx->frame_bits)                                                                        // 0.0
/*76  */                 break;                                                                                         // 0.0
/*78  */         }                                                                                                      // 0.0
/*80  */         //av_dlog(ctx->m.avctx, "lambda %d, up %u, down %u, bits %d, frame %d\n",                              // 0.0
/*82  */         //        lambda, last_higher, last_lower, bits, ctx->frame_bits);                                     // 0.0
/*84  */         if (end) {                                                                                             // 0.0
/*86  */             if (bits > ctx->frame_bits)                                                                        // 0.0
/*88  */                 return -1;                                                                                     // 0.0
/*90  */             break;                                                                                             // 0.0
/*92  */         }                                                                                                      // 0.0
/*94  */         if (bits < ctx->frame_bits) {                                                                          // 0.0
/*96  */             last_lower = FFMIN(lambda, last_lower);                                                            // 0.0
/*98  */             if (last_higher != 0)                                                                              // 0.0
/*100 */                 lambda = (lambda+last_higher)>>1;                                                              // 0.0
/*102 */             else                                                                                               // 0.0
/*104 */                 lambda -= down_step;                                                                           // 0.0
/*106 */             down_step *= 5; // XXX tune ?                                                                      // 0.0
/*108 */             up_step = 1<<LAMBDA_FRAC_BITS;                                                                     // 0.0
/*110 */             lambda = FFMAX(1, lambda);                                                                         // 0.0
/*112 */             if (lambda == last_lower)                                                                          // 0.0
/*114 */                 break;                                                                                         // 0.0
/*116 */         } else {                                                                                               // 0.0
/*118 */             last_higher = FFMAX(lambda, last_higher);                                                          // 0.0
/*120 */             if (last_lower != INT_MAX)                                                                         // 0.0
/*122 */                 lambda = (lambda+last_lower)>>1;                                                               // 0.0
/*124 */             else if ((int64_t)lambda + up_step > INT_MAX)                                                      // 0.0
/*126 */                 return -1;                                                                                     // 0.0
/*128 */             else                                                                                               // 0.0
/*130 */                 lambda += up_step;                                                                             // 0.0
/*132 */             up_step = FFMIN((int64_t)up_step*5, INT_MAX);                                                      // 0.0
/*134 */             down_step = 1<<LAMBDA_FRAC_BITS;                                                                   // 0.0
/*136 */         }                                                                                                      // 0.0
/*138 */     }                                                                                                          // 0.0
/*140 */     //av_dlog(ctx->m.avctx, "out lambda %d\n", lambda);                                                        // 0.0
/*142 */     ctx->lambda = lambda;                                                                                      // 0.0
/*144 */     return 0;                                                                                                  // 0.0
/*146 */ }                                                                                                              // 0.0
