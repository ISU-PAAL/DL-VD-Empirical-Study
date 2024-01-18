// commit message FFmpeg@24130234cd (target=0, prob=0.93266404, correct=False): rtpdec_mpeg4: validate fmtp fields
/*0  */ static int parse_fmtp(AVFormatContext *s,                             // (13) 0.02734
/*2  */                       AVStream *stream, PayloadContext *data,         // (4) 0.0625
/*4  */                       const char *attr, const char *value)            // (5) 0.06055
/*6  */ {                                                                     // (21) 0.001953
/*8  */     AVCodecParameters *par = stream->codecpar;                        // (12) 0.03125
/*10 */     int res, i;                                                       // (19) 0.01562
/*14 */     if (!strcmp(attr, "config")) {                                    // (14) 0.02734
/*16 */         res = parse_fmtp_config(par, value);                          // (11) 0.04102
/*20 */         if (res < 0)                                                  // (17) 0.02539
/*22 */             return res;                                               // (15) 0.02734
/*24 */     }                                                                 // (20) 0.007812
/*28 */     if (par->codec_id == AV_CODEC_ID_AAC) {                           // (10) 0.04688
/*30 */         /* Looking for a known attribute */                           // (16) 0.02734
/*32 */         for (i = 0; attr_names[i].str; ++i) {                         // (9) 0.05078
/*34 */             if (!av_strcasecmp(attr, attr_names[i].str)) {            // (6) 0.06055
/*36 */                 if (attr_names[i].type == ATTR_NAME_TYPE_INT) {       // (3) 0.06836
/*38 */                     *(int *)((char *)data+                            // (7) 0.05664
/*40 */                         attr_names[i].offset) = atoi(value);          // (1) 0.07422
/*42 */                 } else if (attr_names[i].type == ATTR_NAME_TYPE_STR)  // (2) 0.07031
/*44 */                     *(char **)((char *)data+                          // (8) 0.05664
/*46 */                         attr_names[i].offset) = av_strdup(value);     // (0) 0.08008
/*48 */             }                                                         // (18) 0.02344
/*50 */         }                                                             // 0.0
/*52 */     }                                                                 // 0.0
/*54 */     return 0;                                                         // 0.0
/*56 */ }                                                                     // 0.0
