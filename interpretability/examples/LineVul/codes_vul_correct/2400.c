// commit message FFmpeg@1cb4ef526d (target=1, prob=0.65017223, correct=True): avcodec/hevc_refs: Check nb_refs in add_candidate_ref()
/*0  */ static int add_candidate_ref(HEVCContext *s, RefPicList *list,  // (2) 0.07955
/*2  */                              int poc, int ref_flag)             // (0) 0.1402
/*4  */ {                                                               // (15) 0.003788
/*6  */     HEVCFrame *ref = find_ref_idx(s, poc);                      // (1) 0.07955
/*10 */     if (ref == s->ref)                                          // (9) 0.04167
/*12 */         return AVERROR_INVALIDDATA;                             // (7) 0.06439
/*16 */     if (!ref) {                                                 // (12) 0.0303
/*18 */         ref = generate_missing_ref(s, poc);                     // (3) 0.07576
/*20 */         if (!ref)                                               // (10) 0.04167
/*22 */             return AVERROR(ENOMEM);                             // (4) 0.07576
/*24 */     }                                                           // (14) 0.01515
/*28 */     list->list[list->nb_refs] = ref->poc;                       // (5) 0.07576
/*30 */     list->ref[list->nb_refs]  = ref;                            // (6) 0.06818
/*32 */     list->nb_refs++;                                            // (11) 0.03788
/*36 */     mark_ref(ref, ref_flag);                                    // (8) 0.04924
/*38 */     return 0;                                                   // (13) 0.02273
/*40 */ }                                                               // (16) 0.003788
