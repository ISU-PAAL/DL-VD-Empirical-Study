// commit message FFmpeg@b754978a3b (target=0, prob=0.8954226, correct=False): caching of timestamps for mpeg-ps so seeking is faster move (av_)find_stream_index() to utils.c as its usefull outside mpeg.c assert checking enabled, to find bugs quicker, should obviously be disabled later (av_)add_index_entry() inserts new entries so that the list stays ordered and updates entries if already in it (av_)index_search_timestamp() cleanup (kill ugly goto) and shorter
/*0  */ static void add_index_entry(AVStream *st,                               // (8) 0.03988
/*2  */                             int64_t pos, int64_t timestamp, int flags)  // (1) 0.1288
/*4  */ {                                                                       // (15) 0.003067
/*6  */     AVIndexEntry *entries, *ie;                                         // (9) 0.03988
/*8  */                                                                         // (13) 0.01227
/*10 */     entries = av_fast_realloc(st->index_entries,                        // (5) 0.05828
/*12 */                               &st->index_entries_allocated_size,        // (2) 0.1288
/*14 */                               (st->nb_index_entries + 1) *              // (0) 0.1319
/*16 */                               sizeof(AVIndexEntry));                    // (3) 0.1074
/*18 */     if (entries) {                                                      // (12) 0.02761
/*20 */         st->index_entries = entries;                                    // (6) 0.04908
/*22 */         ie = &entries[st->nb_index_entries++];                          // (4) 0.07055
/*24 */         ie->pos = pos;                                                  // (10) 0.03988
/*26 */         ie->timestamp = timestamp;                                      // (7) 0.04294
/*28 */         ie->flags = flags;                                              // (11) 0.03988
/*30 */     }                                                                   // (14) 0.01227
/*32 */ }                                                                       // (16) 0.003067
