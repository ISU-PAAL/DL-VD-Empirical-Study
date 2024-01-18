// commit message FFmpeg@92e483f8ed (target=1, prob=0.05136951, correct=False): all: use FFDIFFSIGN to resolve possible undefined behavior in comparators
/*0  */ static int compare_codec_desc(const void *a, const void *b)          // (2) 0.1583
/*2  */ {                                                                    // (5) 0.008333
/*4  */     const AVCodecDescriptor * const *da = a;                         // (3) 0.1417
/*6  */     const AVCodecDescriptor * const *db = b;                         // (4) 0.1417
/*10 */     return (*da)->type != (*db)->type ? (*da)->type - (*db)->type :  // (0) 0.2333
/*12 */            strcmp((*da)->name, (*db)->name);                         // (1) 0.2083
/*14 */ }                                                                    // (6) 0.008333
