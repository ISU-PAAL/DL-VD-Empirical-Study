// commit message FFmpeg@082cf97106 (target=0, prob=0.009630355, correct=True): Split h264 loop filter off h264.c. No meassureable speed difference on pentium dual & cathedral sample.
/*0 */ static inline int get_chroma_qp(H264Context *h, int t, int qscale){  // (0) 0.4615
/*2 */     return h->pps.chroma_qp_table[t][qscale];                        // (1) 0.4038
/*4 */ }                                                                    // (2) 0.01923
