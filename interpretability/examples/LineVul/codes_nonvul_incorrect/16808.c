// commit message FFmpeg@6241e8a382 (target=0, prob=0.7944085, correct=False): id2v2: check the return value of decode_str()
/*0  */ static void read_chapter(AVFormatContext *s, AVIOContext *pb, int len, char *ttag, ID3v2ExtraMeta **extra_meta)  // (0) 0.07227
/*2  */ {                                                                                                                // (32) 0.001953
/*4  */     AVRational time_base = {1, 1000};                                                                            // (10) 0.0293
/*6  */     uint32_t start, end;                                                                                         // (18) 0.02148
/*8  */     AVChapter *chapter;                                                                                          // (24) 0.01563
/*10 */     uint8_t *dst = NULL;                                                                                         // (14) 0.02539
/*12 */     int taglen;                                                                                                  // (29) 0.01367
/*14 */     char tag[5];                                                                                                 // (26) 0.01562
/*18 */     decode_str(s, pb, 0, &dst, &len);                                                                            // (3) 0.04102
/*20 */     if (len < 16)                                                                                                // (21) 0.01758
/*22 */         return;                                                                                                  // (22) 0.01758
/*26 */     start = avio_rb32(pb);                                                                                       // (15) 0.02539
/*28 */     end   = avio_rb32(pb);                                                                                       // (11) 0.0293
/*30 */     avio_skip(pb, 8);                                                                                            // (17) 0.02344
/*34 */     chapter = avpriv_new_chapter(s, s->nb_chapters + 1, time_base, start, end, dst);                             // (1) 0.06445
/*36 */     if (!chapter) {                                                                                              // (25) 0.01563
/*38 */         av_free(dst);                                                                                            // (12) 0.02734
/*40 */         return;                                                                                                  // (23) 0.01758
/*42 */     }                                                                                                            // (31) 0.007812
/*46 */     len -= 16;                                                                                                   // (30) 0.01367
/*48 */     while (len > 10) {                                                                                           // (20) 0.01953
/*50 */         avio_read(pb, tag, 4);                                                                                   // (6) 0.03516
/*52 */         tag[4] = 0;                                                                                              // (13) 0.02734
/*54 */         taglen = avio_rb32(pb);                                                                                  // (7) 0.03516
/*56 */         avio_skip(pb, 2);                                                                                        // (9) 0.03125
/*58 */         len -= 10;                                                                                               // (19) 0.02148
/*60 */         if (taglen < 0 || taglen > len) {                                                                        // (4) 0.03906
/*62 */             av_free(dst);                                                                                        // (5) 0.03516
/*64 */             return;                                                                                              // (16) 0.02539
/*66 */         }                                                                                                        // (27) 0.01562
/*68 */         if (tag[0] == 'T')                                                                                       // (8) 0.0332
/*70 */             read_ttag(s, pb, taglen, &chapter->metadata, tag);                                                   // (2) 0.06055
/*72 */         else                                                                                                     // (28) 0.01562
/*74 */             avio_skip(pb, taglen);                                                                               // 0.0
/*76 */         len -= taglen;                                                                                           // 0.0
/*78 */     }                                                                                                            // 0.0
/*82 */     ff_metadata_conv(&chapter->metadata, NULL, ff_id3v2_34_metadata_conv);                                       // 0.0
/*84 */     ff_metadata_conv(&chapter->metadata, NULL, ff_id3v2_4_metadata_conv);                                        // 0.0
/*86 */     av_free(dst);                                                                                                // 0.0
/*88 */ }                                                                                                                // 0.0
