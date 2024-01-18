// commit message FFmpeg@5a2645cafe (target=1, prob=0.6066145, correct=True): nutdec: Prevent leaks on memory error
/*0   */ static int find_and_decode_index(NUTContext *nut)                                       // (11) 0.0332
/*2   */ {                                                                                       // (26) 0.001953
/*4   */     AVFormatContext *s = nut->avf;                                                      // (17) 0.02734
/*6   */     AVIOContext *bc    = s->pb;                                                         // (14) 0.03125
/*8   */     uint64_t tmp, end;                                                                  // (23) 0.02148
/*10  */     int i, j, syncpoint_count;                                                          // (20) 0.02539
/*12  */     int64_t filesize = avio_size(bc);                                                   // (13) 0.0332
/*14  */     int64_t *syncpoints;                                                                // (22) 0.02148
/*16  */     int8_t *has_keyframe;                                                               // (19) 0.02539
/*18  */     int ret = AVERROR_INVALIDDATA;                                                      // (16) 0.0293
/*22  */     avio_seek(bc, filesize - 12, SEEK_SET);                                             // (8) 0.03906
/*24  */     avio_seek(bc, filesize - avio_rb64(bc), SEEK_SET);                                  // (3) 0.05078
/*26  */     if (avio_rb64(bc) != INDEX_STARTCODE) {                                             // (7) 0.04297
/*28  */         av_log(s, AV_LOG_ERROR, "no index at the end\n");                               // (1) 0.05469
/*30  */         return ret;                                                                     // (24) 0.01953
/*32  */     }                                                                                   // (25) 0.007812
/*36  */     end  = get_packetheader(nut, bc, 1, INDEX_STARTCODE);                               // (4) 0.04883
/*38  */     end += avio_tell(bc);                                                               // (21) 0.02344
/*42  */     ffio_read_varlen(bc); // max_pts                                                    // (10) 0.03711
/*44  */     GET_V(syncpoint_count, tmp < INT_MAX / 8 && tmp > 0);                               // (5) 0.04687
/*46  */     syncpoints   = av_malloc(sizeof(int64_t) *  syncpoint_count);                       // (2) 0.05469
/*48  */     has_keyframe = av_malloc(sizeof(int8_t)  * (syncpoint_count + 1));                  // (0) 0.06055
/*50  */     if (!syncpoints || !has_keyframe)                                                   // (18) 0.02734
/*52  */         return AVERROR(ENOMEM);                                                         // (15) 0.03125
/*54  */     for (i = 0; i < syncpoint_count; i++) {                                             // (9) 0.03711
/*56  */         syncpoints[i] = ffio_read_varlen(bc);                                           // (6) 0.04687
/*58  */         if (syncpoints[i] <= 0)                                                         // (12) 0.0332
/*60  */             goto fail;                                                                  // 0.0
/*62  */         if (i)                                                                          // 0.0
/*64  */             syncpoints[i] += syncpoints[i - 1];                                         // 0.0
/*66  */     }                                                                                   // 0.0
/*70  */     for (i = 0; i < s->nb_streams; i++) {                                               // 0.0
/*72  */         int64_t last_pts = -1;                                                          // 0.0
/*74  */         for (j = 0; j < syncpoint_count;) {                                             // 0.0
/*76  */             uint64_t x = ffio_read_varlen(bc);                                          // 0.0
/*78  */             int type   = x & 1;                                                         // 0.0
/*80  */             int n      = j;                                                             // 0.0
/*82  */             x >>= 1;                                                                    // 0.0
/*84  */             if (type) {                                                                 // 0.0
/*86  */                 int flag = x & 1;                                                       // 0.0
/*88  */                 x >>= 1;                                                                // 0.0
/*90  */                 if (n + x >= syncpoint_count + 1) {                                     // 0.0
/*92  */                     av_log(s, AV_LOG_ERROR, "index overflow A\n");                      // 0.0
/*94  */                     goto fail;                                                          // 0.0
/*96  */                 }                                                                       // 0.0
/*98  */                 while (x--)                                                             // 0.0
/*100 */                     has_keyframe[n++] = flag;                                           // 0.0
/*102 */                 has_keyframe[n++] = !flag;                                              // 0.0
/*104 */             } else {                                                                    // 0.0
/*106 */                 while (x != 1) {                                                        // 0.0
/*108 */                     if (n >= syncpoint_count + 1) {                                     // 0.0
/*110 */                         av_log(s, AV_LOG_ERROR, "index overflow B\n");                  // 0.0
/*112 */                         goto fail;                                                      // 0.0
/*114 */                     }                                                                   // 0.0
/*116 */                     has_keyframe[n++] = x & 1;                                          // 0.0
/*118 */                     x >>= 1;                                                            // 0.0
/*120 */                 }                                                                       // 0.0
/*122 */             }                                                                           // 0.0
/*124 */             if (has_keyframe[0]) {                                                      // 0.0
/*126 */                 av_log(s, AV_LOG_ERROR, "keyframe before first syncpoint in index\n");  // 0.0
/*128 */                 goto fail;                                                              // 0.0
/*130 */             }                                                                           // 0.0
/*132 */             assert(n <= syncpoint_count + 1);                                           // 0.0
/*134 */             for (; j < n && j < syncpoint_count; j++) {                                 // 0.0
/*136 */                 if (has_keyframe[j]) {                                                  // 0.0
/*138 */                     uint64_t B, A = ffio_read_varlen(bc);                               // 0.0
/*140 */                     if (!A) {                                                           // 0.0
/*142 */                         A = ffio_read_varlen(bc);                                       // 0.0
/*144 */                         B = ffio_read_varlen(bc);                                       // 0.0
/*146 */                         // eor_pts[j][i] = last_pts + A + B                             // 0.0
/*148 */                     } else                                                              // 0.0
/*150 */                         B = 0;                                                          // 0.0
/*152 */                     av_add_index_entry(s->streams[i], 16 * syncpoints[j - 1],           // 0.0
/*154 */                                        last_pts + A, 0, 0, AVINDEX_KEYFRAME);           // 0.0
/*156 */                     last_pts += A + B;                                                  // 0.0
/*158 */                 }                                                                       // 0.0
/*160 */             }                                                                           // 0.0
/*162 */         }                                                                               // 0.0
/*164 */     }                                                                                   // 0.0
/*168 */     if (skip_reserved(bc, end) || ffio_get_checksum(bc)) {                              // 0.0
/*170 */         av_log(s, AV_LOG_ERROR, "index checksum mismatch\n");                           // 0.0
/*172 */         goto fail;                                                                      // 0.0
/*174 */     }                                                                                   // 0.0
/*176 */     ret = 0;                                                                            // 0.0
/*180 */ fail:                                                                                   // 0.0
/*182 */     av_free(syncpoints);                                                                // 0.0
/*184 */     av_free(has_keyframe);                                                              // 0.0
/*186 */     return ret;                                                                         // 0.0
/*188 */ }                                                                                       // 0.0
