// commit message FFmpeg@919d13d238 (target=0, prob=0.5897403, correct=False): avformat/http: Fix null check on allocated value
/*0  */ static int cookie_string(AVDictionary *dict, char **cookies)       // (4) 0.05822
/*2  */ {                                                                  // (16) 0.003425
/*4  */     AVDictionaryEntry *e = NULL;                                   // (10) 0.0411
/*6  */     int len = 1;                                                   // (13) 0.0274
/*10 */     // determine how much memory is needed for the cookies string  // (7) 0.04795
/*12 */     while (e = av_dict_get(dict, "", e, AV_DICT_IGNORE_SUFFIX))    // (1) 0.1062
/*14 */         len += strlen(e->key) + strlen(e->value) + 1;              // (3) 0.09247
/*18 */     // reallocate the cookies                                      // (11) 0.03082
/*20 */     e = NULL;                                                      // (14) 0.02397
/*22 */     if (*cookies) av_free(*cookies);                               // (6) 0.05137
/*24 */     *cookies = av_malloc(len);                                     // (9) 0.04795
/*26 */     if (!cookies) return AVERROR(ENOMEM);                          // (5) 0.05822
/*28 */     *cookies[0] = '\0';                                            // (8) 0.04795
/*32 */     // write out the cookies                                       // (12) 0.0274
/*34 */     while (e = av_dict_get(dict, "", e, AV_DICT_IGNORE_SUFFIX))    // (2) 0.1062
/*36 */         av_strlcatf(*cookies, len, "%s%s\n", e->key, e->value);    // (0) 0.1164
/*40 */     return 0;                                                      // (15) 0.02055
/*42 */ }                                                                  // (17) 0.003425
