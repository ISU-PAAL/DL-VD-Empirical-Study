// commit message FFmpeg@66f0c958bf (target=1, prob=0.83593875, correct=True): avcodec/exr: fix undefined shift in pxr24_uncompress()
/*0   */ static int pxr24_uncompress(EXRContext *s, const uint8_t *src,                                            // (8) 0.04883
/*2   */                             int compressed_size, int uncompressed_size,                                   // (1) 0.07422
/*4   */                             EXRThreadData *td)                                                            // (2) 0.06641
/*6   */ {                                                                                                         // (24) 0.001953
/*8   */     unsigned long dest_len, expected_len = 0;                                                             // (15) 0.0293
/*10  */     const uint8_t *in = td->tmp;                                                                          // (14) 0.0293
/*12  */     uint8_t *out;                                                                                         // (20) 0.01953
/*14  */     int c, i, j;                                                                                          // (19) 0.01953
/*18  */     for (i = 0; i < s->nb_channels; i++) {                                                                // (9) 0.04102
/*20  */         if (s->channels[i].pixel_type == EXR_FLOAT) {                                                     // (5) 0.05469
/*22  */             expected_len += (td->xsize * td->ysize * 3);/* PRX 24 store float in 24 bit instead of 32 */  // (0) 0.08008
/*24  */         } else if (s->channels[i].pixel_type == EXR_HALF) {                                               // (4) 0.05859
/*26  */             expected_len += (td->xsize * td->ysize * 2);                                                  // (6) 0.05469
/*28  */         } else {//UINT 32                                                                                 // (16) 0.02734
/*30  */             expected_len += (td->xsize * td->ysize * 4);                                                  // (7) 0.05469
/*32  */         }                                                                                                 // (21) 0.01562
/*34  */     }                                                                                                     // (22) 0.007812
/*38  */     dest_len = expected_len;                                                                              // (18) 0.02148
/*42  */     if (uncompress(td->tmp, &dest_len, src, compressed_size) != Z_OK) {                                   // (3) 0.05859
/*44  */         return AVERROR_INVALIDDATA;                                                                       // (11) 0.0332
/*46  */     } else if (dest_len != expected_len) {                                                                // (13) 0.03125
/*48  */         return AVERROR_INVALIDDATA;                                                                       // (12) 0.0332
/*50  */     }                                                                                                     // (23) 0.007812
/*54  */     out = td->uncompressed_data;                                                                          // (17) 0.02539
/*56  */     for (i = 0; i < td->ysize; i++)                                                                       // (10) 0.03516
/*58  */         for (c = 0; c < s->nb_channels; c++) {                                                            // 0.0
/*60  */             EXRChannel *channel = &s->channels[c];                                                        // 0.0
/*62  */             const uint8_t *ptr[4];                                                                        // 0.0
/*64  */             uint32_t pixel = 0;                                                                           // 0.0
/*68  */             switch (channel->pixel_type) {                                                                // 0.0
/*70  */             case EXR_FLOAT:                                                                               // 0.0
/*72  */                 ptr[0] = in;                                                                              // 0.0
/*74  */                 ptr[1] = ptr[0] + td->xsize;                                                              // 0.0
/*76  */                 ptr[2] = ptr[1] + td->xsize;                                                              // 0.0
/*78  */                 in     = ptr[2] + td->xsize;                                                              // 0.0
/*82  */                 for (j = 0; j < td->xsize; ++j) {                                                         // 0.0
/*84  */                     uint32_t diff = (*(ptr[0]++) << 24) |                                                 // 0.0
/*86  */                                     (*(ptr[1]++) << 16) |                                                 // 0.0
/*88  */                                     (*(ptr[2]++) << 8);                                                   // 0.0
/*90  */                     pixel += diff;                                                                        // 0.0
/*92  */                     bytestream_put_le32(&out, pixel);                                                     // 0.0
/*94  */                 }                                                                                         // 0.0
/*96  */                 break;                                                                                    // 0.0
/*98  */             case EXR_HALF:                                                                                // 0.0
/*100 */                 ptr[0] = in;                                                                              // 0.0
/*102 */                 ptr[1] = ptr[0] + td->xsize;                                                              // 0.0
/*104 */                 in     = ptr[1] + td->xsize;                                                              // 0.0
/*106 */                 for (j = 0; j < td->xsize; j++) {                                                         // 0.0
/*108 */                     uint32_t diff = (*(ptr[0]++) << 8) | *(ptr[1]++);                                     // 0.0
/*112 */                     pixel += diff;                                                                        // 0.0
/*114 */                     bytestream_put_le16(&out, pixel);                                                     // 0.0
/*116 */                 }                                                                                         // 0.0
/*118 */                 break;                                                                                    // 0.0
/*120 */             case EXR_UINT:                                                                                // 0.0
/*122 */                 ptr[0] = in;                                                                              // 0.0
/*124 */                 ptr[1] = ptr[0] + s->xdelta;                                                              // 0.0
/*126 */                 ptr[2] = ptr[1] + s->xdelta;                                                              // 0.0
/*128 */                 ptr[3] = ptr[2] + s->xdelta;                                                              // 0.0
/*130 */                 in     = ptr[3] + s->xdelta;                                                              // 0.0
/*134 */                 for (j = 0; j < s->xdelta; ++j) {                                                         // 0.0
/*136 */                     uint32_t diff = (*(ptr[0]++) << 24) |                                                 // 0.0
/*138 */                     (*(ptr[1]++) << 16) |                                                                 // 0.0
/*140 */                     (*(ptr[2]++) << 8 ) |                                                                 // 0.0
/*142 */                     (*(ptr[3]++));                                                                        // 0.0
/*144 */                     pixel += diff;                                                                        // 0.0
/*146 */                     bytestream_put_le32(&out, pixel);                                                     // 0.0
/*148 */                 }                                                                                         // 0.0
/*150 */                 break;                                                                                    // 0.0
/*152 */             default:                                                                                      // 0.0
/*154 */                 return AVERROR_INVALIDDATA;                                                               // 0.0
/*156 */             }                                                                                             // 0.0
/*158 */         }                                                                                                 // 0.0
/*162 */     return 0;                                                                                             // 0.0
/*164 */ }                                                                                                         // 0.0
