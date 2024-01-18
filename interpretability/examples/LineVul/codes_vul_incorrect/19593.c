// commit message FFmpeg@7b6a51f59c (target=1, prob=0.08996098, correct=False): avcodec/shorten: Check k in get_uint()
/*0  */ static inline unsigned int get_uint(ShortenContext *s, int k)  // (2) 0.191
/*2  */ {                                                              // (4) 0.01124
/*4  */     if (s->version != 0)                                       // (3) 0.1236
/*6  */         k = get_ur_golomb_shorten(&s->gb, ULONGSIZE);          // (0) 0.3146
/*8  */     return get_ur_golomb_shorten(&s->gb, k);                   // (1) 0.236
/*10 */ }                                                              // (5) 0.01124
