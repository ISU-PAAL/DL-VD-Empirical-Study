// commit message FFmpeg@4691a77db4 (target=1, prob=0.008568528, correct=False): Add support for streams with different chroma_qp_index_offset for Cr and Cb Patch by Andreas Öman % andreas A olebyn P nu % Original thread: Date: Jun 26, 2007 8:48 PM subject: [FFmpeg-devel] Color corruption and seeking errors with H264 disc sources
/*0 */ static inline int get_chroma_qp(H264Context *h, int qscale){  // (1) 0.42
/*2 */     return h->pps.chroma_qp_table[qscale & 0xff];             // (0) 0.44
/*4 */ }                                                             // (2) 0.02
