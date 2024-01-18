// commit message FFmpeg@fa2a34cd40 (target=0, prob=0.03482066, correct=True): lavfi: change the filter registering system to match the other libraries
/*0  */ int avfilter_register(AVFilter *filter)                               // (2) 0.1183
/*2  */ {                                                                     // (5) 0.01075
/*4  */     if (next_registered_avfilter_idx == MAX_REGISTERED_AVFILTERS_NB)  // (0) 0.3011
/*6  */         return -1;                                                    // (3) 0.1183
/*10 */     registered_avfilters[next_registered_avfilter_idx++] = filter;    // (1) 0.2473
/*12 */     return 0;                                                         // (4) 0.06452
/*14 */ }                                                                     // (6) 0.01075
