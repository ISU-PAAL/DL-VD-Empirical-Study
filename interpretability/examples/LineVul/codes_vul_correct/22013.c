// commit message FFmpeg@caa7a3914f (target=1, prob=0.63566583, correct=True): avformat/mov: check atom nesting depth
/*0   */ static int mov_read_default(MOVContext *c, AVIOContext *pb, MOVAtom atom)                      // (7) 0.04883
/*2   */ {                                                                                              // (22) 0.001956
/*4   */     int64_t total_size = 0;                                                                    // (17) 0.02539
/*6   */     MOVAtom a;                                                                                 // (20) 0.01562
/*8   */     int i;                                                                                     // (21) 0.01172
/*12  */     if (atom.size < 0)                                                                         // (19) 0.02148
/*14  */         atom.size = INT64_MAX;                                                                 // (14) 0.03125
/*16  */     while (total_size + 8 <= atom.size && !avio_feof(pb)) {                                    // (8) 0.04883
/*18  */         int (*parse)(MOVContext*, AVIOContext*, MOVAtom) = NULL;                               // (5) 0.05078
/*20  */         a.size = atom.size;                                                                    // (16) 0.0293
/*22  */         a.type=0;                                                                              // (18) 0.02539
/*24  */         if (atom.size >= 8) {                                                                  // (15) 0.03125
/*26  */             a.size = avio_rb32(pb);                                                            // (10) 0.04492
/*28  */             a.type = avio_rl32(pb);                                                            // (12) 0.04492
/*30  */             if (a.type == MKTAG('f','r','e','e') &&                                            // (4) 0.05664
/*32  */                 a.size >= 8 &&                                                                 // (13) 0.04102
/*34  */                 c->moov_retry) {                                                               // (9) 0.04687
/*36  */                 uint8_t buf[8];                                                                // (11) 0.04492
/*38  */                 uint32_t *type = (uint32_t *)buf + 1;                                          // (1) 0.0625
/*40  */                 avio_read(pb, buf, 8);                                                         // (6) 0.05078
/*42  */                 avio_seek(pb, -8, SEEK_CUR);                                                   // (3) 0.06055
/*44  */                 if (*type == MKTAG('m','v','h','d') ||                                         // (2) 0.06055
/*46  */                     *type == MKTAG('c','m','o','v')) {                                         // (0) 0.06836
/*48  */                     av_log(c->fc, AV_LOG_ERROR, "Detected moov in a free atom.\n");            // 0.0
/*50  */                     a.type = MKTAG('m','o','o','v');                                           // 0.0
/*52  */                 }                                                                              // 0.0
/*54  */             }                                                                                  // 0.0
/*56  */             if (atom.type != MKTAG('r','o','o','t') &&                                         // 0.0
/*58  */                 atom.type != MKTAG('m','o','o','v'))                                           // 0.0
/*60  */             {                                                                                  // 0.0
/*62  */                 if (a.type == MKTAG('t','r','a','k') || a.type == MKTAG('m','d','a','t'))      // 0.0
/*64  */                 {                                                                              // 0.0
/*66  */                     av_log(c->fc, AV_LOG_ERROR, "Broken file, trak/mdat not at top-level\n");  // 0.0
/*68  */                     avio_skip(pb, -8);                                                         // 0.0
/*70  */                     return 0;                                                                  // 0.0
/*72  */                 }                                                                              // 0.0
/*74  */             }                                                                                  // 0.0
/*76  */             total_size += 8;                                                                   // 0.0
/*78  */             if (a.size == 1) { /* 64 bit extended size */                                      // 0.0
/*80  */                 a.size = avio_rb64(pb) - 8;                                                    // 0.0
/*82  */                 total_size += 8;                                                               // 0.0
/*84  */             }                                                                                  // 0.0
/*86  */         }                                                                                      // 0.0
/*88  */         av_dlog(c->fc, "type: %08x '%.4s' parent:'%.4s' sz: %"PRId64" %"PRId64" %"PRId64"\n",  // 0.0
/*90  */                 a.type, (char*)&a.type, (char*)&atom.type, a.size, total_size, atom.size);     // 0.0
/*92  */         if (a.size == 0) {                                                                     // 0.0
/*94  */             a.size = atom.size - total_size + 8;                                               // 0.0
/*96  */         }                                                                                      // 0.0
/*98  */         a.size -= 8;                                                                           // 0.0
/*100 */         if (a.size < 0)                                                                        // 0.0
/*102 */             break;                                                                             // 0.0
/*104 */         a.size = FFMIN(a.size, atom.size - total_size);                                        // 0.0
/*108 */         for (i = 0; mov_default_parse_table[i].type; i++)                                      // 0.0
/*110 */             if (mov_default_parse_table[i].type == a.type) {                                   // 0.0
/*112 */                 parse = mov_default_parse_table[i].parse;                                      // 0.0
/*114 */                 break;                                                                         // 0.0
/*116 */             }                                                                                  // 0.0
/*120 */         // container is user data                                                              // 0.0
/*122 */         if (!parse && (atom.type == MKTAG('u','d','t','a') ||                                  // 0.0
/*124 */                        atom.type == MKTAG('i','l','s','t')))                                   // 0.0
/*126 */             parse = mov_read_udta_string;                                                      // 0.0
/*130 */         if (!parse) { /* skip leaf atoms data */                                               // 0.0
/*132 */             avio_skip(pb, a.size);                                                             // 0.0
/*134 */         } else {                                                                               // 0.0
/*136 */             int64_t start_pos = avio_tell(pb);                                                 // 0.0
/*138 */             int64_t left;                                                                      // 0.0
/*140 */             int err = parse(c, pb, a);                                                         // 0.0
/*142 */             if (err < 0)                                                                       // 0.0
/*144 */                 return err;                                                                    // 0.0
/*146 */             if (c->found_moov && c->found_mdat &&                                              // 0.0
/*148 */                 ((!pb->seekable || c->fc->flags & AVFMT_FLAG_IGNIDX) ||                        // 0.0
/*150 */                  start_pos + a.size == avio_size(pb))) {                                       // 0.0
/*152 */                 if (!pb->seekable || c->fc->flags & AVFMT_FLAG_IGNIDX)                         // 0.0
/*154 */                     c->next_root_atom = start_pos + a.size;                                    // 0.0
/*156 */                 return 0;                                                                      // 0.0
/*158 */             }                                                                                  // 0.0
/*160 */             left = a.size - avio_tell(pb) + start_pos;                                         // 0.0
/*162 */             if (left > 0) /* skip garbage at atom end */                                       // 0.0
/*164 */                 avio_skip(pb, left);                                                           // 0.0
/*166 */             else if (left < 0) {                                                               // 0.0
/*168 */                 av_log(c->fc, AV_LOG_WARNING,                                                  // 0.0
/*170 */                        "overread end of atom '%.4s' by %"PRId64" bytes\n",                     // 0.0
/*172 */                        (char*)&a.type, -left);                                                 // 0.0
/*174 */                 avio_seek(pb, left, SEEK_CUR);                                                 // 0.0
/*176 */             }                                                                                  // 0.0
/*178 */         }                                                                                      // 0.0
/*182 */         total_size += a.size;                                                                  // 0.0
/*184 */     }                                                                                          // 0.0
/*188 */     if (total_size < atom.size && atom.size < 0x7ffff)                                         // 0.0
/*190 */         avio_skip(pb, atom.size - total_size);                                                 // 0.0
/*194 */     return 0;                                                                                  // 0.0
/*196 */ }                                                                                              // 0.0
