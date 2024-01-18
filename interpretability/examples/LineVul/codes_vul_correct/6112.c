// commit message FFmpeg@5c720657c2 (target=1, prob=0.71203774, correct=True): mov: always check avio_read return value
/*0  */ static int mov_read_cmov(MOVContext *c, AVIOContext *pb, MOVAtom atom)                             // (2) 0.05078
/*2  */ {                                                                                                  // (28) 0.001953
/*4  */ #if CONFIG_ZLIB                                                                                    // (25) 0.01172
/*6  */     AVIOContext ctx;                                                                               // (23) 0.01758
/*8  */     uint8_t *cmov_data;                                                                            // (20) 0.02539
/*10 */     uint8_t *moov_data; /* uncompressed data */                                                    // (7) 0.03516
/*12 */     long cmov_len, moov_len;                                                                       // (19) 0.02734
/*14 */     int ret = -1;                                                                                  // (24) 0.01758
/*18 */     avio_rb32(pb); /* dcom atom */                                                                 // (13) 0.03125
/*20 */     if (avio_rl32(pb) != MKTAG('d','c','o','m'))                                                   // (3) 0.05078
/*22 */         return AVERROR_INVALIDDATA;                                                                // (10) 0.0332
/*24 */     if (avio_rl32(pb) != MKTAG('z','l','i','b')) {                                                 // (1) 0.05273
/*26 */         av_log(c->fc, AV_LOG_ERROR, "unknown compression for cmov atom !");                        // (0) 0.06055
/*28 */         return AVERROR_INVALIDDATA;                                                                // (11) 0.0332
/*30 */     }                                                                                              // (27) 0.007812
/*32 */     avio_rb32(pb); /* cmvd atom */                                                                 // (15) 0.03125
/*34 */     if (avio_rl32(pb) != MKTAG('c','m','v','d'))                                                   // (4) 0.05078
/*36 */         return AVERROR_INVALIDDATA;                                                                // (12) 0.0332
/*38 */     moov_len = avio_rb32(pb); /* uncompressed size */                                              // (5) 0.04102
/*40 */     cmov_len = atom.size - 6 * 4;                                                                  // (14) 0.03125
/*44 */     cmov_data = av_malloc(cmov_len);                                                               // (8) 0.03516
/*46 */     if (!cmov_data)                                                                                // (22) 0.01953
/*48 */         return AVERROR(ENOMEM);                                                                    // (18) 0.03125
/*50 */     moov_data = av_malloc(moov_len);                                                               // (9) 0.03516
/*52 */     if (!moov_data) {                                                                              // (21) 0.02148
/*54 */         av_free(cmov_data);                                                                        // (16) 0.03125
/*56 */         return AVERROR(ENOMEM);                                                                    // (17) 0.03125
/*58 */     }                                                                                              // (26) 0.007812
/*60 */     avio_read(pb, cmov_data, cmov_len);                                                            // (6) 0.03906
/*62 */     if (uncompress (moov_data, (uLongf *) &moov_len, (const Bytef *)cmov_data, cmov_len) != Z_OK)  // 0.0
/*64 */         goto free_and_return;                                                                      // 0.0
/*66 */     if (ffio_init_context(&ctx, moov_data, moov_len, 0, NULL, NULL, NULL, NULL) != 0)              // 0.0
/*68 */         goto free_and_return;                                                                      // 0.0
/*70 */     atom.type = MKTAG('m','o','o','v');                                                            // 0.0
/*72 */     atom.size = moov_len;                                                                          // 0.0
/*74 */     ret = mov_read_default(c, &ctx, atom);                                                         // 0.0
/*76 */ free_and_return:                                                                                   // 0.0
/*78 */     av_free(moov_data);                                                                            // 0.0
/*80 */     av_free(cmov_data);                                                                            // 0.0
/*82 */     return ret;                                                                                    // 0.0
/*84 */ #else                                                                                              // 0.0
/*86 */     av_log(c->fc, AV_LOG_ERROR, "this file requires zlib support compiled in\n");                  // 0.0
/*88 */     return AVERROR(ENOSYS);                                                                        // 0.0
/*90 */ #endif                                                                                             // 0.0
/*92 */ }                                                                                                  // 0.0
