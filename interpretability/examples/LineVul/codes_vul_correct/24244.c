// commit message FFmpeg@ddfa3751c0 (target=1, prob=0.68425333, correct=True): j2kdec: convert to bytestream2 API
/*0   */ static int decode_codestream(J2kDecoderContext *s)                                                                              // (14) 0.0332
/*2   */ {                                                                                                                               // (24) 0.001953
/*4   */     J2kCodingStyle *codsty = s->codsty;                                                                                         // (11) 0.03516
/*6   */     J2kQuantStyle  *qntsty = s->qntsty;                                                                                         // (8) 0.03906
/*8   */     uint8_t *properties = s->properties;                                                                                        // (17) 0.02734
/*12  */     for (;;){                                                                                                                   // (23) 0.01367
/*14  */         int marker, len, ret = 0;                                                                                               // (15) 0.03125
/*16  */         const uint8_t *oldbuf;                                                                                                  // (16) 0.03125
/*18  */         if (s->buf_end - s->buf < 2){                                                                                           // (7) 0.04102
/*20  */             av_log(s->avctx, AV_LOG_ERROR, "Missing EOC\n");                                                                    // (1) 0.06445
/*22  */             break;                                                                                                              // (19) 0.02539
/*24  */         }                                                                                                                       // (21) 0.01562
/*28  */         marker = bytestream_get_be16(&s->buf);                                                                                  // (6) 0.04297
/*30  */         if(s->avctx->debug & FF_DEBUG_STARTCODE)                                                                                // (4) 0.04687
/*32  */             av_log(s->avctx, AV_LOG_DEBUG, "marker 0x%.4X at pos 0x%tx\n", marker, s->buf - s->buf_start - 4);                  // (0) 0.1113
/*34  */         oldbuf = s->buf;                                                                                                        // (18) 0.02734
/*38  */         if (marker == J2K_SOD){                                                                                                 // (10) 0.03711
/*40  */             J2kTile *tile = s->tile + s->curtileno;                                                                             // (2) 0.05664
/*42  */             if (ret = init_tile(s, s->curtileno))                                                                               // (3) 0.05469
/*44  */                 return ret;                                                                                                     // (12) 0.03516
/*46  */             if (ret = decode_packets(s, tile))                                                                                  // (5) 0.04687
/*48  */                 return ret;                                                                                                     // (13) 0.03516
/*50  */             continue;                                                                                                           // (20) 0.02539
/*52  */         }                                                                                                                       // (22) 0.01562
/*54  */         if (marker == J2K_EOC)                                                                                                  // (9) 0.03711
/*56  */             break;                                                                                                              // 0.0
/*60  */         if (s->buf_end - s->buf < 2)                                                                                            // 0.0
/*62  */             return AVERROR(EINVAL);                                                                                             // 0.0
/*64  */         len = bytestream_get_be16(&s->buf);                                                                                     // 0.0
/*66  */         switch(marker){                                                                                                         // 0.0
/*68  */             case J2K_SIZ:                                                                                                       // 0.0
/*70  */                 ret = get_siz(s); break;                                                                                        // 0.0
/*72  */             case J2K_COC:                                                                                                       // 0.0
/*74  */                 ret = get_coc(s, codsty, properties); break;                                                                    // 0.0
/*76  */             case J2K_COD:                                                                                                       // 0.0
/*78  */                 ret = get_cod(s, codsty, properties); break;                                                                    // 0.0
/*80  */             case J2K_QCC:                                                                                                       // 0.0
/*82  */                 ret = get_qcc(s, len, qntsty, properties); break;                                                               // 0.0
/*84  */             case J2K_QCD:                                                                                                       // 0.0
/*86  */                 ret = get_qcd(s, len, qntsty, properties); break;                                                               // 0.0
/*88  */             case J2K_SOT:                                                                                                       // 0.0
/*90  */                 if (!(ret = get_sot(s))){                                                                                       // 0.0
/*92  */                     codsty = s->tile[s->curtileno].codsty;                                                                      // 0.0
/*94  */                     qntsty = s->tile[s->curtileno].qntsty;                                                                      // 0.0
/*96  */                     properties = s->tile[s->curtileno].properties;                                                              // 0.0
/*98  */                 }                                                                                                               // 0.0
/*100 */                 break;                                                                                                          // 0.0
/*102 */             case J2K_COM:                                                                                                       // 0.0
/*104 */                 // the comment is ignored                                                                                       // 0.0
/*106 */                 s->buf += len - 2; break;                                                                                       // 0.0
/*108 */             default:                                                                                                            // 0.0
/*110 */                 av_log(s->avctx, AV_LOG_ERROR, "unsupported marker 0x%.4X at pos 0x%tx\n", marker, s->buf - s->buf_start - 4);  // 0.0
/*112 */                 s->buf += len - 2; break;                                                                                       // 0.0
/*114 */         }                                                                                                                       // 0.0
/*116 */         if (s->buf - oldbuf != len || ret){                                                                                     // 0.0
/*118 */             av_log(s->avctx, AV_LOG_ERROR, "error during processing marker segment %.4x\n", marker);                            // 0.0
/*120 */             return ret ? ret : -1;                                                                                              // 0.0
/*122 */         }                                                                                                                       // 0.0
/*124 */     }                                                                                                                           // 0.0
/*126 */     return 0;                                                                                                                   // 0.0
/*128 */ }                                                                                                                               // 0.0
