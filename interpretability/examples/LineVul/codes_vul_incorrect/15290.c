// commit message FFmpeg@00b3ca3c7a (target=1, prob=0.42319694, correct=False): Add missing memory check in parse_inputs(), and fix possible (yet very unlikely) crash.
/*0  */ static int parse_inputs(const char **buf, AVFilterInOut **curr_inputs,   // (3) 0.05336
/*2  */                         AVFilterInOut **open_outputs, AVClass *log_ctx)  // (0) 0.09281
/*4  */ {                                                                        // (23) 0.00232
/*6  */     int pad = 0;                                                         // (19) 0.01856
/*10 */     while (**buf == '[') {                                               // (15) 0.02552
/*12 */         char *name = parse_link_name(buf, log_ctx);                      // (4) 0.05336
/*14 */         AVFilterInOut *match;                                            // (13) 0.03248
/*18 */         if (!name)                                                       // (16) 0.02552
/*20 */             return AVERROR(EINVAL);                                      // (8) 0.0464
/*24 */         /* First check if the label is not in the open_outputs list */   // (5) 0.05336
/*26 */         match = extract_inout(name, open_outputs);                       // (7) 0.04872
/*30 */         if (match) {                                                     // (14) 0.02784
/*32 */             av_free(name);                                               // (12) 0.03944
/*34 */         } else {                                                         // (17) 0.0232
/*36 */             /* Not in the list, so add it as an input */                 // (2) 0.05568
/*38 */             match = av_mallocz(sizeof(AVFilterInOut));                   // (1) 0.06265
/*40 */             match->name    = name;                                       // (9) 0.0464
/*42 */             match->pad_idx = pad;                                        // (10) 0.0464
/*44 */         }                                                                // (20) 0.01856
/*48 */         insert_inout(curr_inputs, match);                                // (11) 0.0464
/*52 */         *buf += strspn(*buf, WHITESPACES);                               // (6) 0.05104
/*54 */         pad++;                                                           // (18) 0.02088
/*56 */     }                                                                    // (22) 0.009281
/*60 */     return pad;                                                          // (21) 0.01392
/*62 */ }                                                                        // (24) 0.00232
