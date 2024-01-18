// commit message FFmpeg@8c013a9e55 (target=0, prob=0.7451162, correct=False): avformat/avidec: Check avio_read() return before using the results for meta-data
/*0  */ static int avi_read_tag(AVFormatContext *s, AVStream *st, uint32_t tag,  // (2) 0.08874
/*2  */                         uint32_t size)                                   // (1) 0.09898
/*4  */ {                                                                        // (16) 0.003413
/*6  */     AVIOContext *pb = s->pb;                                             // (9) 0.04437
/*8  */     char key[5]     = { 0 };                                             // (4) 0.05461
/*10 */     char *value;                                                         // (14) 0.02389
/*14 */     size += (size & 1);                                                  // (12) 0.03413
/*18 */     if (size == UINT_MAX)                                                // (11) 0.04096
/*20 */         return AVERROR(EINVAL);                                          // (5) 0.05461
/*22 */     value = av_malloc(size + 1);                                         // (7) 0.04778
/*24 */     if (!value)                                                          // (15) 0.02389
/*26 */         return AVERROR(ENOMEM);                                          // (6) 0.05461
/*28 */     avio_read(pb, value, size);                                          // (8) 0.04778
/*30 */     value[size] = 0;                                                     // (13) 0.03413
/*34 */     AV_WL32(key, tag);                                                   // (10) 0.04437
/*38 */     return av_dict_set(st ? &st->metadata : &s->metadata, key, value,    // (3) 0.08874
/*40 */                        AV_DICT_DONT_STRDUP_VAL);                         // (0) 0.1229
/*42 */ }                                                                        // (17) 0.003413
