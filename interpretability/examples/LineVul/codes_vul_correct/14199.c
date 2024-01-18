// commit message FFmpeg@4641ae352e (target=1, prob=0.58669645, correct=True): avformat: Add and use ff_copy_whitelists()
/*0   */ static int libquvi_read_header(AVFormatContext *s)                                            // (10) 0.03125
/*2   */ {                                                                                             // (26) 0.001953
/*4   */     int i, ret;                                                                               // (24) 0.01562
/*6   */     quvi_t q;                                                                                 // (23) 0.01758
/*8   */     quvi_media_t m;                                                                           // (20) 0.02148
/*10  */     QUVIcode rc;                                                                              // (25) 0.01562
/*12  */     LibQuviContext *qc = s->priv_data;                                                        // (9) 0.0332
/*14  */     char *media_url, *pagetitle;                                                              // (11) 0.0293
/*18  */     rc = quvi_init(&q);                                                                       // (15) 0.02344
/*20  */     if (rc != QUVI_OK)                                                                        // (16) 0.02344
/*22  */         goto quvi_fail;                                                                       // (12) 0.02539
/*26  */     quvi_setopt(q, QUVIOPT_FORMAT, qc->format);                                               // (7) 0.04687
/*30  */     rc = quvi_parse(q, s->filename, &m);                                                      // (8) 0.03711
/*32  */     if (rc != QUVI_OK)                                                                        // (18) 0.02344
/*34  */         goto quvi_fail;                                                                       // (14) 0.02539
/*38  */     rc = quvi_getprop(m, QUVIPROP_MEDIAURL, &media_url);                                      // (4) 0.05469
/*40  */     if (rc != QUVI_OK)                                                                        // (19) 0.02344
/*42  */         goto quvi_fail;                                                                       // (13) 0.02539
/*46  */     av_assert0(!qc->fmtctx->codec_whitelist && !qc->fmtctx->format_whitelist);                // (0) 0.07227
/*48  */     qc->fmtctx-> codec_whitelist = av_strdup(s->codec_whitelist);                             // (1) 0.06055
/*50  */     qc->fmtctx->format_whitelist = av_strdup(s->format_whitelist);                            // (3) 0.05859
/*54  */     ret = avformat_open_input(&qc->fmtctx, media_url, NULL, NULL);                            // (5) 0.05273
/*56  */     if (ret < 0)                                                                              // (22) 0.01758
/*58  */         goto end;                                                                             // (21) 0.01953
/*62  */     rc = quvi_getprop(m, QUVIPROP_PAGETITLE, &pagetitle);                                     // (2) 0.05859
/*64  */     if (rc == QUVI_OK)                                                                        // (17) 0.02344
/*66  */         av_dict_set(&s->metadata, "title", pagetitle, 0);                                     // (6) 0.05078
/*70  */     for (i = 0; i < qc->fmtctx->nb_streams; i++) {                                            // 0.0
/*72  */         AVStream *st = avformat_new_stream(s, NULL);                                          // 0.0
/*74  */         AVStream *ist = qc->fmtctx->streams[i];                                               // 0.0
/*76  */         if (!st) {                                                                            // 0.0
/*78  */             ret = AVERROR(ENOMEM);                                                            // 0.0
/*80  */             goto end;                                                                         // 0.0
/*82  */         }                                                                                     // 0.0
/*84  */         avpriv_set_pts_info(st, ist->pts_wrap_bits, ist->time_base.num, ist->time_base.den);  // 0.0
/*86  */         avcodec_copy_context(st->codec, qc->fmtctx->streams[i]->codec);                       // 0.0
/*88  */     }                                                                                         // 0.0
/*92  */     return 0;                                                                                 // 0.0
/*96  */ quvi_fail:                                                                                    // 0.0
/*98  */     av_log(s, AV_LOG_ERROR, "%s\n", quvi_strerror(q, rc));                                    // 0.0
/*100 */     ret = AVERROR_EXTERNAL;                                                                   // 0.0
/*104 */ end:                                                                                          // 0.0
/*106 */     quvi_parse_close(&m);                                                                     // 0.0
/*108 */     quvi_close(&q);                                                                           // 0.0
/*110 */     return ret;                                                                               // 0.0
/*112 */ }                                                                                             // 0.0
