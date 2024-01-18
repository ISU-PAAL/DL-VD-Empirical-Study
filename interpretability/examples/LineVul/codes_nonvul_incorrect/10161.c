// commit message FFmpeg@e8c4db0d4d (target=0, prob=0.6556651, correct=False): xcbgrab: Validate the capture area
/*0  */ static int create_stream(AVFormatContext *s)                              // (17) 0.02344
/*2  */ {                                                                         // (24) 0.001953
/*4  */     XCBGrabContext *c = s->priv_data;                                     // (14) 0.03125
/*6  */     AVStream *st      = avformat_new_stream(s, NULL);                     // (7) 0.04688
/*8  */     xcb_get_geometry_cookie_t gc;                                         // (13) 0.0332
/*10 */     xcb_get_geometry_reply_t *geo;                                        // (12) 0.03516
/*12 */     int ret;                                                              // (23) 0.01172
/*16 */     if (!st)                                                              // (22) 0.01367
/*18 */         return AVERROR(ENOMEM);                                           // (15) 0.03125
/*22 */     ret = av_parse_video_size(&c->width, &c->height, c->video_size);      // (1) 0.05469
/*24 */     if (ret < 0)                                                          // (21) 0.01758
/*26 */         return ret;                                                       // (19) 0.01953
/*30 */     ret = av_parse_video_rate(&st->avg_frame_rate, c->framerate);         // (2) 0.05273
/*32 */     if (ret < 0)                                                          // (20) 0.01758
/*34 */         return ret;                                                       // (18) 0.01953
/*38 */     avpriv_set_pts_info(st, 64, 1, 1000000);                              // (10) 0.04297
/*42 */     gc  = xcb_get_geometry(c->conn, c->screen->root);                     // (5) 0.04883
/*44 */     geo = xcb_get_geometry_reply(c->conn, gc, NULL);                      // (8) 0.04687
/*48 */     c->width      = FFMIN(geo->width, c->width);                          // (6) 0.04688
/*50 */     c->height     = FFMIN(geo->height, c->height);                        // (9) 0.04492
/*52 */     c->time_base  = (AVRational){ st->avg_frame_rate.den,                 // (3) 0.05078
/*54 */                                   st->avg_frame_rate.num };               // (0) 0.08594
/*56 */     c->time_frame = av_gettime();                                         // (16) 0.02734
/*60 */     st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                           // (11) 0.04102
/*62 */     st->codec->codec_id   = AV_CODEC_ID_RAWVIDEO;                         // (4) 0.05078
/*64 */     st->codec->width      = c->width;                                     // 0.0
/*66 */     st->codec->height     = c->height;                                    // 0.0
/*68 */     st->codec->time_base  = c->time_base;                                 // 0.0
/*72 */     ret = pixfmt_from_pixmap_format(s, geo->depth, &st->codec->pix_fmt);  // 0.0
/*76 */     free(geo);                                                            // 0.0
/*80 */     return ret;                                                           // 0.0
/*82 */ }                                                                         // 0.0
