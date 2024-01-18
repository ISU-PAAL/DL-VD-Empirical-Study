// commit message FFmpeg@c9c55a5699 (target=0, prob=0.008684751, correct=True): simplify by checking min matching len
/*0  */ static const MXFCodecUL *mxf_get_codec_ul(const MXFCodecUL *uls, UID *uid)  // (0) 0.25
/*2  */ {                                                                           // (8) 0.008064
/*4  */     while (uls->id != CODEC_ID_NONE) {                                      // (2) 0.1532
/*6  */         if(mxf_match_uid(uls->uid, *uid, 16))                               // (1) 0.2016
/*8  */             break;                                                          // (3) 0.1048
/*10 */         uls++;                                                              // (4) 0.08064
/*12 */     }                                                                       // (6) 0.03226
/*14 */     return uls;                                                             // (5) 0.05645
/*16 */ }                                                                           // (7) 0.008064
