// commit message FFmpeg@4a023d5b53 (target=0, prob=0.3528212, correct=True): vda_h264_dec: remove check_format
/*0  */ static av_cold int check_format(AVCodecContext *avctx)                         // (9) 0.03366
/*2  */ {                                                                              // (35) 0.00198
/*4  */     AVCodecParserContext *parser;                                              // (13) 0.02178
/*6  */     uint8_t *pout;                                                             // (14) 0.02178
/*8  */     int psize;                                                                 // (25) 0.01386
/*10 */     int index;                                                                 // (26) 0.01188
/*12 */     H264Context *h;                                                            // (20) 0.01782
/*14 */     int ret = -1;                                                              // (21) 0.01782
/*18 */     /* init parser & parse file */                                             // (17) 0.0198
/*20 */     parser = av_parser_init(avctx->codec->id);                                 // (6) 0.03762
/*22 */     if (!parser) {                                                             // (22) 0.01584
/*24 */         av_log(avctx, AV_LOG_ERROR, "Failed to open H.264 parser.\n");         // (1) 0.06535
/*26 */         goto final;                                                            // (18) 0.0198
/*28 */     }                                                                          // (30) 0.007921
/*30 */     parser->flags = PARSER_FLAG_COMPLETE_FRAMES;                               // (7) 0.03762
/*32 */     index = av_parser_parse2(parser, avctx, &pout, &psize, NULL, 0, 0, 0, 0);  // (0) 0.06931
/*34 */     if (index < 0) {                                                           // (19) 0.0198
/*36 */         av_log(avctx, AV_LOG_ERROR, "Failed to parse this file.\n");           // (2) 0.06139
/*38 */         goto release_parser;                                                   // (12) 0.02376
/*40 */     }                                                                          // (31) 0.007921
/*44 */     /* check if support */                                                     // (23) 0.01584
/*46 */     h = parser->priv_data;                                                     // (15) 0.02178
/*48 */     switch (h->sps.bit_depth_luma) {                                           // (8) 0.03564
/*50 */     case 8:                                                                    // (27) 0.01188
/*52 */         if (!CHROMA444(h) && !CHROMA422(h)) {                                  // (4) 0.05149
/*54 */             // only this will H.264 decoder switch to hwaccel                  // (5) 0.05149
/*56 */             ret = 0;                                                           // (10) 0.0297
/*58 */             break;                                                             // (11) 0.02574
/*60 */         }                                                                      // (24) 0.01584
/*62 */     default:                                                                   // (29) 0.009901
/*64 */         av_log(avctx, AV_LOG_ERROR, "Unsupported file.\n");                    // (3) 0.05545
/*66 */     }                                                                          // (32) 0.007921
/*70 */ release_parser:                                                                // (33) 0.007921
/*72 */     av_parser_close(parser);                                                   // (16) 0.02178
/*76 */ final:                                                                         // (34) 0.00396
/*78 */     return ret;                                                                // (28) 0.01188
/*80 */ }                                                                              // (36) 0.00198
