// commit message FFmpeg@a744064c41 (target=1, prob=0.97079945, correct=True): avcodec/tiff: reset geotag_count in free_geotags()
/*0  */ static void free_geotags(TiffContext *const s)  // (3) 0.125
/*2  */ {                                               // (7) 0.008333
/*4  */     int i;                                      // (5) 0.05
/*6  */     for (i = 0; i < s->geotag_count; i++) {     // (1) 0.1833
/*8  */         if (s->geotags[i].val)                  // (2) 0.1583
/*10 */             av_freep(&s->geotags[i].val);       // (0) 0.2167
/*12 */     }                                           // (6) 0.03333
/*14 */     av_freep(&s->geotags);                      // (4) 0.1167
/*17 */ }                                               // (8) 0.008333
