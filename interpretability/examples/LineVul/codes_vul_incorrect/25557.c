// commit message FFmpeg@f57b00e897 (target=1, prob=0.17813355, correct=False): Fixed NULL pointer dereference in id3v2 parser.
/*0  */ static const ID3v2EMFunc *get_extra_meta_func(const char *tag, int isv34)  // (3) 0.1004
/*2  */ {                                                                          // (12) 0.003584
/*4  */     int i = 0;                                                             // (9) 0.02867
/*6  */     while (ff_id3v2_extra_meta_funcs[i].tag3) {                            // (5) 0.08961
/*8  */         if (!memcmp(tag,                                                   // (7) 0.05018
/*10 */                     (isv34 ?                                               // (6) 0.08602
/*12 */                         ff_id3v2_extra_meta_funcs[i].tag4 :                // (0) 0.1505
/*14 */                         ff_id3v2_extra_meta_funcs[i].tag3),                // (1) 0.1505
/*16 */                     (isv34 ? 4 : 3)))                                      // (4) 0.1004
/*18 */             return &ff_id3v2_extra_meta_funcs[i];                          // (2) 0.1039
/*20 */         i++;                                                               // (8) 0.03226
/*22 */     }                                                                      // (11) 0.01434
/*24 */     return NULL;                                                           // (10) 0.02151
/*26 */ }                                                                          // (13) 0.003584
