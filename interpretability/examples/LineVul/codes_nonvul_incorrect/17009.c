// commit message FFmpeg@1e901ffc61 (target=0, prob=0.80158246, correct=False): wrap_timestamp: remove unneeded check
/*0  */ static int64_t wrap_timestamp(AVStream *st, int64_t timestamp)                      // (8) 0.0742
/*2  */ {                                                                                   // (11) 0.003534
/*4  */     if (st->pts_wrap_behavior != AV_PTS_WRAP_IGNORE && st->pts_wrap_bits < 64 &&    // (0) 0.1272
/*6  */         st->pts_wrap_reference != AV_NOPTS_VALUE && timestamp != AV_NOPTS_VALUE) {  // (1) 0.1237
/*8  */         if (st->pts_wrap_behavior == AV_PTS_WRAP_ADD_OFFSET &&                      // (3) 0.1095
/*10 */             timestamp < st->pts_wrap_reference)                                     // (6) 0.07774
/*12 */             return timestamp + (1ULL<<st->pts_wrap_bits);                           // (4) 0.09541
/*14 */         else if (st->pts_wrap_behavior == AV_PTS_WRAP_SUB_OFFSET &&                 // (2) 0.1166
/*16 */             timestamp >= st->pts_wrap_reference)                                    // (7) 0.07774
/*18 */             return timestamp - (1ULL<<st->pts_wrap_bits);                           // (5) 0.09541
/*20 */     }                                                                               // (10) 0.01413
/*22 */     return timestamp;                                                               // (9) 0.0212
/*24 */ }                                                                                   // (12) 0.003534
