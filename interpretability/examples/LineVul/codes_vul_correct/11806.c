// commit message FFmpeg@8089b7fa8c (target=1, prob=0.9065643, correct=True): avoptions: Check the return value from av_get_number
/*0  */ int64_t av_get_int(void *obj, const char *name, const AVOption **o_out)  // (0) 0.25
/*2  */ {                                                                        // (6) 0.009259
/*4  */     int64_t intnum=1;                                                    // (2) 0.1111
/*6  */     double num=1;                                                        // (4) 0.07407
/*8  */     int den=1;                                                           // (5) 0.07407
/*12 */     av_get_number(obj, name, o_out, &num, &den, &intnum);                // (1) 0.25
/*14 */     return num*intnum/den;                                               // (3) 0.1019
/*16 */ }                                                                        // (7) 0.009259
