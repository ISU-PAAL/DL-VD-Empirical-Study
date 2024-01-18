// commit message FFmpeg@611b356274 (target=1, prob=0.32496572, correct=False): avcodec/dnxhd_parser: Do not return invalid value from dnxhd_find_frame_end() on error
/*0   */ static int dnxhd_find_frame_end(DNXHDParserContext *dctx,                                 // (3) 0.04492
/*2   */                                 const uint8_t *buf, int buf_size)                         // (0) 0.08594
/*4   */ {                                                                                         // (25) 0.001953
/*6   */     ParseContext *pc = &dctx->pc;                                                         // (17) 0.0293
/*8   */     uint64_t state = pc->state64;                                                         // (18) 0.02734
/*10  */     int pic_found = pc->frame_start_found;                                                // (16) 0.03125
/*12  */     int i = 0;                                                                            // (22) 0.01562
/*16  */     if (!pic_found) {                                                                     // (21) 0.01953
/*18  */         for (i = 0; i < buf_size; i++) {                                                  // (9) 0.04297
/*20  */             state = (state << 8) | buf[i];                                                // (5) 0.04492
/*22  */             if (ff_dnxhd_check_header_prefix(state & 0xffffffffff00LL) != 0) {            // (1) 0.07617
/*24  */                 i++;                                                                      // (15) 0.0332
/*26  */                 pic_found = 1;                                                            // (10) 0.04102
/*28  */                 dctx->cur_byte = 0;                                                       // (2) 0.04687
/*30  */                 dctx->remaining = 0;                                                      // (4) 0.04492
/*32  */                 break;                                                                    // (14) 0.0332
/*34  */             }                                                                             // (20) 0.02344
/*36  */         }                                                                                 // (23) 0.01562
/*38  */     }                                                                                     // (24) 0.007812
/*42  */     if (pic_found && !dctx->remaining) {                                                  // (13) 0.0332
/*44  */         if (!buf_size) /* EOF considered as end of frame */                               // (8) 0.04297
/*46  */             return 0;                                                                     // (19) 0.02734
/*48  */         for (; i < buf_size; i++) {                                                       // (11) 0.03711
/*50  */             dctx->cur_byte++;                                                             // (12) 0.03516
/*52  */             state = (state << 8) | buf[i];                                                // (6) 0.04492
/*56  */             if (dctx->cur_byte == 24) {                                                   // (7) 0.04492
/*58  */                 dctx->h = (state >> 32) & 0xFFFF;                                         // 0.0
/*60  */             } else if (dctx->cur_byte == 26) {                                            // 0.0
/*62  */                 dctx->w = (state >> 32) & 0xFFFF;                                         // 0.0
/*64  */             } else if (dctx->cur_byte == 42) {                                            // 0.0
/*66  */                 int cid = (state >> 32) & 0xFFFFFFFF;                                     // 0.0
/*70  */                 if (cid <= 0)                                                             // 0.0
/*72  */                     continue;                                                             // 0.0
/*76  */                 dctx->remaining = avpriv_dnxhd_get_frame_size(cid);                       // 0.0
/*78  */                 if (dctx->remaining <= 0) {                                               // 0.0
/*80  */                     dctx->remaining = ff_dnxhd_get_hr_frame_size(cid, dctx->w, dctx->h);  // 0.0
/*82  */                     if (dctx->remaining <= 0)                                             // 0.0
/*84  */                         return dctx->remaining;                                           // 0.0
/*86  */                 }                                                                         // 0.0
/*88  */                 if (buf_size - i + 47 >= dctx->remaining) {                               // 0.0
/*90  */                     int remaining = dctx->remaining;                                      // 0.0
/*94  */                     pc->frame_start_found = 0;                                            // 0.0
/*96  */                     pc->state64 = -1;                                                     // 0.0
/*98  */                     dctx->cur_byte = 0;                                                   // 0.0
/*100 */                     dctx->remaining = 0;                                                  // 0.0
/*102 */                     return remaining;                                                     // 0.0
/*104 */                 } else {                                                                  // 0.0
/*106 */                     dctx->remaining -= buf_size;                                          // 0.0
/*108 */                 }                                                                         // 0.0
/*110 */             }                                                                             // 0.0
/*112 */         }                                                                                 // 0.0
/*114 */     } else if (pic_found) {                                                               // 0.0
/*116 */         if (dctx->remaining > buf_size) {                                                 // 0.0
/*118 */             dctx->remaining -= buf_size;                                                  // 0.0
/*120 */         } else {                                                                          // 0.0
/*122 */             int remaining = dctx->remaining;                                              // 0.0
/*126 */             pc->frame_start_found = 0;                                                    // 0.0
/*128 */             pc->state64 = -1;                                                             // 0.0
/*130 */             dctx->cur_byte = 0;                                                           // 0.0
/*132 */             dctx->remaining = 0;                                                          // 0.0
/*134 */             return remaining;                                                             // 0.0
/*136 */         }                                                                                 // 0.0
/*138 */     }                                                                                     // 0.0
/*140 */     pc->frame_start_found = pic_found;                                                    // 0.0
/*142 */     pc->state64 = state;                                                                  // 0.0
/*144 */     return END_NOT_FOUND;                                                                 // 0.0
/*146 */ }                                                                                         // 0.0
