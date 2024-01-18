// commit message FFmpeg@7e3e653618 (target=1, prob=0.8187759, correct=True): avformat/bintext: protect against potential overflow of chars_per_frame
/*0  */ static AVStream * init_stream(AVFormatContext *s)                                   // (8) 0.05166
/*2  */ {                                                                                   // (15) 0.00369
/*4  */     BinDemuxContext *bin = s->priv_data;                                            // (7) 0.05904
/*6  */     AVStream *st = avformat_new_stream(s, NULL);                                    // (4) 0.07011
/*8  */     if (!st)                                                                        // (12) 0.02583
/*10 */         return NULL;                                                                // (9) 0.0369
/*12 */     st->codec->codec_tag   = 0;                                                     // (6) 0.06273
/*14 */     st->codec->codec_type  = AVMEDIA_TYPE_VIDEO;                                    // (2) 0.08118
/*18 */     if (!bin->width) {                                                              // (10) 0.0369
/*20 */         st->codec->width  = (80<<3);                                                // (3) 0.0738
/*22 */         st->codec->height = (25<<4);                                                // (5) 0.07011
/*24 */     }                                                                               // (14) 0.01476
/*28 */     avpriv_set_pts_info(st, 60, bin->framerate.den, bin->framerate.num);            // (1) 0.1144
/*32 */     /* simulate tty display speed */                                                // (11) 0.0369
/*34 */     bin->chars_per_frame = FFMAX(av_q2d(st->time_base) * bin->chars_per_frame, 1);  // (0) 0.1439
/*38 */     return st;                                                                      // (13) 0.02214
/*40 */ }                                                                                   // (16) 0.00369
