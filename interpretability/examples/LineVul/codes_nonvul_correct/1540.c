// commit message FFmpeg@5c2fb561d9 (target=0, prob=0.13661276, correct=True): h264: add H264_ prefix to the NAL unit types
/*0   */ int ff_h264_decode_ref_pic_marking(const H264Context *h, H264SliceContext *sl,    // (3) 0.06055
/*2   */                                    GetBitContext *gb)                             // (1) 0.07812
/*4   */ {                                                                                 // (21) 0.001953
/*6   */     int i;                                                                        // (19) 0.01172
/*8   */     MMCO *mmco = sl->mmco;                                                        // (16) 0.02734
/*10  */     int nb_mmco = 0;                                                              // (17) 0.02344
/*14  */     if (h->nal_unit_type == NAL_IDR_SLICE) { // FIXME fields                      // (6) 0.05469
/*16  */         skip_bits1(gb); // broken_link                                            // (14) 0.03516
/*18  */         if (get_bits1(gb)) {                                                      // (15) 0.0332
/*20  */             mmco[0].opcode   = MMCO_LONG;                                         // (8) 0.05273
/*22  */             mmco[0].long_arg = 0;                                                 // (11) 0.04297
/*24  */             nb_mmco          = 1;                                                 // (7) 0.05469
/*26  */         }                                                                         // (18) 0.01562
/*28  */         sl->explicit_ref_marking = 1;                                             // (13) 0.03711
/*30  */     } else {                                                                      // (20) 0.01172
/*32  */         sl->explicit_ref_marking = get_bits1(gb);                                 // (10) 0.04688
/*34  */         if (sl->explicit_ref_marking) {                                           // (12) 0.03906
/*36  */             for (i = 0; i < MAX_MMCO_COUNT; i++) {                                // (4) 0.05859
/*38  */                 MMCOOpcode opcode = get_ue_golomb_31(gb);                         // (2) 0.06836
/*42  */                 mmco[i].opcode = opcode;                                          // (9) 0.05078
/*44  */                 if (opcode == MMCO_SHORT2UNUSED || opcode == MMCO_SHORT2LONG) {   // (0) 0.08398
/*46  */                     mmco[i].short_pic_num =                                       // (5) 0.05859
/*48  */                         (sl->curr_pic_num - get_ue_golomb(gb) - 1) &              // 0.0
/*50  */                             (sl->max_pic_num - 1);                                // 0.0
/*52  */ #if 0                                                                             // 0.0
/*54  */                     if (mmco[i].short_pic_num >= h->short_ref_count ||            // 0.0
/*56  */                         !h->short_ref[mmco[i].short_pic_num]) {                   // 0.0
/*58  */                         av_log(s->avctx, AV_LOG_ERROR,                            // 0.0
/*60  */                                "illegal short ref in memory management control "  // 0.0
/*62  */                                "operation %d\n", mmco);                           // 0.0
/*64  */                         return -1;                                                // 0.0
/*66  */                     }                                                             // 0.0
/*68  */ #endif                                                                            // 0.0
/*70  */                 }                                                                 // 0.0
/*72  */                 if (opcode == MMCO_SHORT2LONG || opcode == MMCO_LONG2UNUSED ||    // 0.0
/*74  */                     opcode == MMCO_LONG || opcode == MMCO_SET_MAX_LONG) {         // 0.0
/*76  */                     unsigned int long_arg = get_ue_golomb_31(gb);                 // 0.0
/*78  */                     if (long_arg >= 32 ||                                         // 0.0
/*80  */                         (long_arg >= 16 && !(opcode == MMCO_SET_MAX_LONG &&       // 0.0
/*82  */                                              long_arg == 16) &&                   // 0.0
/*84  */                          !(opcode == MMCO_LONG2UNUSED && FIELD_PICTURE(h)))) {    // 0.0
/*86  */                         av_log(h->avctx, AV_LOG_ERROR,                            // 0.0
/*88  */                                "illegal long ref in memory management control "   // 0.0
/*90  */                                "operation %d\n", opcode);                         // 0.0
/*92  */                         return -1;                                                // 0.0
/*94  */                     }                                                             // 0.0
/*96  */                     mmco[i].long_arg = long_arg;                                  // 0.0
/*98  */                 }                                                                 // 0.0
/*102 */                 if (opcode > (unsigned) MMCO_LONG) {                              // 0.0
/*104 */                     av_log(h->avctx, AV_LOG_ERROR,                                // 0.0
/*106 */                            "illegal memory management control operation %d\n",    // 0.0
/*108 */                            opcode);                                               // 0.0
/*110 */                     return -1;                                                    // 0.0
/*112 */                 }                                                                 // 0.0
/*114 */                 if (opcode == MMCO_END)                                           // 0.0
/*116 */                     break;                                                        // 0.0
/*118 */             }                                                                     // 0.0
/*120 */             nb_mmco = i;                                                          // 0.0
/*122 */         }                                                                         // 0.0
/*124 */     }                                                                             // 0.0
/*128 */     sl->nb_mmco = nb_mmco;                                                        // 0.0
/*132 */     return 0;                                                                     // 0.0
/*134 */ }                                                                                 // 0.0
