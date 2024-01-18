// commit message FFmpeg@83c285f880 (target=1, prob=0.7541873, correct=True): wtv: Add more sanity checks for a length read from the file
/*0  */ static AVIOContext * wtvfile_open2(AVFormatContext *s, const uint8_t *buf, int buf_size, const uint8_t *filename, int filename_size)  // (0) 0.08594
/*2  */ {                                                                                                                                     // (22) 0.001955
/*4  */     const uint8_t *buf_end = buf + buf_size;                                                                                          // (12) 0.03711
/*8  */     while(buf + 48 <= buf_end) {                                                                                                      // (16) 0.02734
/*10 */         int dir_length, name_size, first_sector, depth;                                                                               // (8) 0.04297
/*12 */         uint64_t file_length;                                                                                                         // (15) 0.0293
/*14 */         const uint8_t *name;                                                                                                          // (14) 0.0293
/*16 */         if (ff_guidcmp(buf, dir_entry_guid)) {                                                                                        // (5) 0.04883
/*18 */             av_log(s, AV_LOG_ERROR, "unknown guid "FF_PRI_GUID", expected dir_entry_guid; "                                           // (1) 0.08594
/*20 */                    "remaining directory entries ignored\n", FF_ARG_GUID(buf));                                                        // (2) 0.07226
/*22 */             break;                                                                                                                    // (19) 0.02539
/*24 */         }                                                                                                                             // (21) 0.01562
/*26 */         dir_length  = AV_RL16(buf + 16);                                                                                              // (10) 0.04102
/*28 */         file_length = AV_RL64(buf + 24);                                                                                              // (11) 0.03906
/*30 */         name_size   = 2 * AV_RL32(buf + 32);                                                                                          // (7) 0.04687
/*32 */         if (buf + 48 + name_size > buf_end) {                                                                                         // (9) 0.04297
/*34 */             av_log(s, AV_LOG_ERROR, "filename exceeds buffer size; remaining directory entries ignored\n");                           // (3) 0.07031
/*36 */             break;                                                                                                                    // (18) 0.02539
/*38 */         }                                                                                                                             // (20) 0.01562
/*40 */         first_sector = AV_RL32(buf + 40 + name_size);                                                                                 // (6) 0.04687
/*42 */         depth        = AV_RL32(buf + 44 + name_size);                                                                                 // (4) 0.05664
/*46 */         /* compare file name; test optional null terminator */                                                                        // (13) 0.03516
/*48 */         name = buf + 40;                                                                                                              // (17) 0.02539
/*50 */         if (name_size >= filename_size &&                                                                                             // 0.0
/*52 */             !memcmp(name, filename, filename_size) &&                                                                                 // 0.0
/*54 */             (name_size < filename_size + 2 || !AV_RN16(name + filename_size)))                                                        // 0.0
/*56 */             return wtvfile_open_sector(first_sector, file_length, depth, s);                                                          // 0.0
/*60 */         buf += dir_length;                                                                                                            // 0.0
/*62 */     }                                                                                                                                 // 0.0
/*64 */     return 0;                                                                                                                         // 0.0
/*66 */ }                                                                                                                                     // 0.0
