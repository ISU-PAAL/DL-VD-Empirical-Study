// commit message FFmpeg@a38758a97e (target=1, prob=0.57680416, correct=True): avcodec/h264_refs: fix null pointer dereference with -DTRACE
/*0   */ int ff_h264_fill_default_ref_list(H264Context *h, H264SliceContext *sl)                                     // (6) 0.05469
/*2   */ {                                                                                                           // (17) 0.001953
/*4   */     int i, len;                                                                                             // (15) 0.01562
/*8   */     if (sl->slice_type_nos == AV_PICTURE_TYPE_B) {                                                          // (8) 0.04688
/*10  */         H264Picture *sorted[32];                                                                            // (12) 0.03125
/*12  */         int cur_poc, list;                                                                                  // (13) 0.0293
/*14  */         int lens[2];                                                                                        // (14) 0.02344
/*18  */         if (FIELD_PICTURE(h))                                                                               // (11) 0.0332
/*20  */             cur_poc = h->cur_pic_ptr->field_poc[h->picture_structure == PICT_BOTTOM_FIELD];                 // (4) 0.08789
/*22  */         else                                                                                                // (16) 0.01562
/*24  */             cur_poc = h->cur_pic_ptr->poc;                                                                  // (7) 0.05273
/*28  */         for (list = 0; list < 2; list++) {                                                                  // (10) 0.03906
/*30  */             len  = add_sorted(sorted,       h->short_ref, h->short_ref_count, cur_poc, 1 ^ list);           // (0) 0.09961
/*32  */             len += add_sorted(sorted + len, h->short_ref, h->short_ref_count, cur_poc, 0 ^ list);           // (2) 0.08984
/*34  */             av_assert0(len <= 32);                                                                          // (9) 0.03906
/*38  */             len  = build_def_list(h->default_ref_list[list], FF_ARRAY_ELEMS(h->default_ref_list[0]),        // (1) 0.0957
/*40  */                                   sorted, len, 0, h->picture_structure);                                    // (3) 0.08984
/*42  */             len += build_def_list(h->default_ref_list[list] + len,                                          // (5) 0.0625
/*44  */                                   FF_ARRAY_ELEMS(h->default_ref_list[0]) - len,                             // 0.0
/*46  */                                   h->long_ref, 16, 1, h->picture_structure);                                // 0.0
/*48  */             av_assert0(len <= 32);                                                                          // 0.0
/*52  */             if (len < sl->ref_count[list])                                                                  // 0.0
/*54  */                 memset(&h->default_ref_list[list][len], 0, sizeof(H264Ref) * (sl->ref_count[list] - len));  // 0.0
/*56  */             lens[list] = len;                                                                               // 0.0
/*58  */         }                                                                                                   // 0.0
/*62  */         if (lens[0] == lens[1] && lens[1] > 1) {                                                            // 0.0
/*64  */             for (i = 0; i < lens[0] &&                                                                      // 0.0
/*66  */                         h->default_ref_list[0][i].parent->f.buf[0]->buffer ==                               // 0.0
/*68  */                         h->default_ref_list[1][i].parent->f.buf[0]->buffer; i++);                           // 0.0
/*70  */             if (i == lens[0]) {                                                                             // 0.0
/*72  */                 FFSWAP(H264Ref, h->default_ref_list[1][0], h->default_ref_list[1][1]);                      // 0.0
/*74  */             }                                                                                               // 0.0
/*76  */         }                                                                                                   // 0.0
/*78  */     } else {                                                                                                // 0.0
/*80  */         len  = build_def_list(h->default_ref_list[0], FF_ARRAY_ELEMS(h->default_ref_list[0]),               // 0.0
/*82  */                               h->short_ref, h->short_ref_count, 0, h->picture_structure);                   // 0.0
/*84  */         len += build_def_list(h->default_ref_list[0] + len,                                                 // 0.0
/*86  */                               FF_ARRAY_ELEMS(h->default_ref_list[0]) - len,                                 // 0.0
/*88  */                               h-> long_ref, 16, 1, h->picture_structure);                                   // 0.0
/*90  */         av_assert0(len <= 32);                                                                              // 0.0
/*94  */         if (len < sl->ref_count[0])                                                                         // 0.0
/*96  */             memset(&h->default_ref_list[0][len], 0, sizeof(H264Ref) * (sl->ref_count[0] - len));            // 0.0
/*98  */     }                                                                                                       // 0.0
/*100 */ #ifdef TRACE                                                                                                // 0.0
/*102 */     for (i = 0; i < sl->ref_count[0]; i++) {                                                                // 0.0
/*104 */         tprintf(h->avctx, "List0: %s fn:%d 0x%p\n",                                                         // 0.0
/*106 */                 (h->default_ref_list[0][i].parent->long_ref ? "LT" : "ST"),                                 // 0.0
/*108 */                 h->default_ref_list[0][i].pic_id,                                                           // 0.0
/*110 */                 h->default_ref_list[0][i].parent->f.data[0]);                                               // 0.0
/*112 */     }                                                                                                       // 0.0
/*114 */     if (sl->slice_type_nos == AV_PICTURE_TYPE_B) {                                                          // 0.0
/*116 */         for (i = 0; i < sl->ref_count[1]; i++) {                                                            // 0.0
/*118 */             tprintf(h->avctx, "List1: %s fn:%d 0x%p\n",                                                     // 0.0
/*120 */                     (h->default_ref_list[1][i].parent->long_ref ? "LT" : "ST"),                             // 0.0
/*122 */                     h->default_ref_list[1][i].pic_id,                                                       // 0.0
/*124 */                     h->default_ref_list[1][i].parent->f.data[0]);                                           // 0.0
/*126 */         }                                                                                                   // 0.0
/*128 */     }                                                                                                       // 0.0
/*130 */ #endif                                                                                                      // 0.0
/*132 */     return 0;                                                                                               // 0.0
/*134 */ }                                                                                                           // 0.0
