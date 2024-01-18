// commit message FFmpeg@fe7547d69e (target=0, prob=0.45013297, correct=True): lavf/utils.c Protect against accessing entries[nb_entries]
/*0  */ int ff_index_search_timestamp(const AVIndexEntry *entries, int nb_entries,  // (3) 0.04883
/*2  */                               int64_t wanted_timestamp, int flags)          // (0) 0.08008
/*4  */ {                                                                           // (27) 0.001953
/*6  */     int a, b, m;                                                            // (22) 0.01953
/*8  */     int64_t timestamp;                                                      // (23) 0.01758
/*12 */     a = -1;                                                                 // (24) 0.01562
/*14 */     b = nb_entries;                                                         // (21) 0.02148
/*18 */     // Optimize appending index entries at the end.                         // (16) 0.02734
/*20 */     if (b && entries[b - 1].timestamp < wanted_timestamp)                   // (6) 0.04102
/*22 */         a = b - 1;                                                          // (17) 0.02539
/*26 */     while (b - a > 1) {                                                     // (19) 0.02344
/*28 */         m         = (a + b) >> 1;                                           // (4) 0.04883
/*32 */         // Search for the next non-discarded packet.                        // (8) 0.03516
/*34 */         while ((entries[m].flags & AVINDEX_DISCARD_FRAME) && m < b) {       // (1) 0.06445
/*36 */             m++;                                                            // (18) 0.02539
/*38 */             if (m == b && entries[m].timestamp >= wanted_timestamp) {       // (2) 0.05859
/*40 */                 m = b - 1;                                                  // (7) 0.04102
/*42 */                 break;                                                      // (10) 0.0332
/*44 */             }                                                               // (20) 0.02344
/*46 */         }                                                                   // (25) 0.01562
/*50 */         timestamp = entries[m].timestamp;                                   // (13) 0.03125
/*52 */         if (timestamp >= wanted_timestamp)                                  // (11) 0.0332
/*54 */             b = m;                                                          // (15) 0.0293
/*56 */         if (timestamp <= wanted_timestamp)                                  // (9) 0.0332
/*58 */             a = m;                                                          // (14) 0.0293
/*60 */     }                                                                       // (26) 0.007812
/*62 */     m = (flags & AVSEEK_FLAG_BACKWARD) ? a : b;                             // (5) 0.04297
/*66 */     if (!(flags & AVSEEK_FLAG_ANY))                                         // (12) 0.03125
/*68 */         while (m >= 0 && m < nb_entries &&                                  // 0.0
/*70 */                !(entries[m].flags & AVINDEX_KEYFRAME))                      // 0.0
/*72 */             m += (flags & AVSEEK_FLAG_BACKWARD) ? -1 : 1;                   // 0.0
/*76 */     if (m == nb_entries)                                                    // 0.0
/*78 */         return -1;                                                          // 0.0
/*80 */     return m;                                                               // 0.0
/*82 */ }                                                                           // 0.0
