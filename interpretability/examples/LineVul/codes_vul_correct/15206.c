// commit message FFmpeg@c571424c7f (target=1, prob=0.634811, correct=True): asfdec: prevent memory leaks found with Coverity Scan
/*0   */ static int asf_read_picture(AVFormatContext *s, int len)                             // (9) 0.03516
/*2   */ {                                                                                    // (28) 0.001953
/*4   */     ASFContext *asf       = s->priv_data;                                            // (6) 0.04297
/*6   */     AVPacket pkt          = { 0 };                                                   // (8) 0.04102
/*8   */     const CodecMime *mime = ff_id3v2_mime_tags;                                      // (5) 0.04492
/*10  */     enum  AVCodecID id    = AV_CODEC_ID_NONE;                                        // (4) 0.04883
/*12  */     char mimetype[64];                                                               // (20) 0.01953
/*14  */     uint8_t  *desc = NULL;                                                           // (16) 0.02539
/*16  */     AVStream   *st = NULL;                                                           // (17) 0.02344
/*18  */     int ret, type, picsize, desc_len;                                                // (13) 0.0293
/*20  */     ASFStream *asf_st;                                                               // (18) 0.02344
/*24  */     /* type + picsize + mime + desc */                                               // (15) 0.02734
/*26  */     if (len < 1 + 4 + 2 + 2) {                                                       // (12) 0.03125
/*28  */         av_log(s, AV_LOG_ERROR, "Invalid attached picture size: %d.\n", len);        // (2) 0.06445
/*30  */         return AVERROR_INVALIDDATA;                                                  // (10) 0.0332
/*32  */     }                                                                                // (26) 0.007812
/*36  */     /* picture type */                                                               // (24) 0.01367
/*38  */     type = avio_r8(s->pb);                                                           // (14) 0.0293
/*40  */     len--;                                                                           // (25) 0.01172
/*42  */     if (type >= FF_ARRAY_ELEMS(ff_id3v2_picture_types) || type < 0) {                // (0) 0.06445
/*44  */         av_log(s, AV_LOG_WARNING, "Unknown attached picture type: %d.\n", type);     // (1) 0.06445
/*46  */         type = 0;                                                                    // (19) 0.02148
/*48  */     }                                                                                // (27) 0.007812
/*52  */     /* picture data size */                                                          // (23) 0.01562
/*54  */     picsize = avio_rl32(s->pb);                                                      // (11) 0.03125
/*56  */     len    -= 4;                                                                     // (21) 0.01953
/*60  */     /* picture MIME type */                                                          // (22) 0.01758
/*62  */     len -= avio_get_str16le(s->pb, len, mimetype, sizeof(mimetype));                 // (3) 0.06055
/*64  */     while (mime->id != AV_CODEC_ID_NONE) {                                           // (7) 0.04297
/*66  */         if (!strncmp(mime->str, mimetype, sizeof(mimetype))) {                       // 0.0
/*68  */             id = mime->id;                                                           // 0.0
/*70  */             break;                                                                   // 0.0
/*72  */         }                                                                            // 0.0
/*74  */         mime++;                                                                      // 0.0
/*76  */     }                                                                                // 0.0
/*78  */     if (id == AV_CODEC_ID_NONE) {                                                    // 0.0
/*80  */         av_log(s, AV_LOG_ERROR, "Unknown attached picture mimetype: %s.\n",          // 0.0
/*82  */                mimetype);                                                            // 0.0
/*84  */         return 0;                                                                    // 0.0
/*86  */     }                                                                                // 0.0
/*90  */     if (picsize >= len) {                                                            // 0.0
/*92  */         av_log(s, AV_LOG_ERROR, "Invalid attached picture data size: %d >= %d.\n",   // 0.0
/*94  */                picsize, len);                                                        // 0.0
/*96  */         return AVERROR_INVALIDDATA;                                                  // 0.0
/*98  */     }                                                                                // 0.0
/*102 */     /* picture description */                                                        // 0.0
/*104 */     desc_len = (len - picsize) * 2 + 1;                                              // 0.0
/*106 */     desc     = av_malloc(desc_len);                                                  // 0.0
/*108 */     if (!desc)                                                                       // 0.0
/*110 */         return AVERROR(ENOMEM);                                                      // 0.0
/*112 */     len -= avio_get_str16le(s->pb, len - picsize, desc, desc_len);                   // 0.0
/*116 */     ret = av_get_packet(s->pb, &pkt, picsize);                                       // 0.0
/*118 */     if (ret < 0)                                                                     // 0.0
/*120 */         goto fail;                                                                   // 0.0
/*124 */     st  = avformat_new_stream(s, NULL);                                              // 0.0
/*126 */     if (!st) {                                                                       // 0.0
/*128 */         ret = AVERROR(ENOMEM);                                                       // 0.0
/*130 */         goto fail;                                                                   // 0.0
/*132 */     }                                                                                // 0.0
/*134 */     asf->asf_st[asf->nb_streams] = av_mallocz(sizeof(*asf_st));                      // 0.0
/*136 */     asf_st = asf->asf_st[asf->nb_streams];                                           // 0.0
/*138 */     if (!asf_st)                                                                     // 0.0
/*140 */         return AVERROR(ENOMEM);                                                      // 0.0
/*144 */     st->disposition              |= AV_DISPOSITION_ATTACHED_PIC;                     // 0.0
/*146 */     st->codec->codec_type         = asf_st->type = AVMEDIA_TYPE_VIDEO;               // 0.0
/*148 */     st->codec->codec_id           = id;                                              // 0.0
/*150 */     st->attached_pic              = pkt;                                             // 0.0
/*152 */     st->attached_pic.stream_index = asf_st->index = st->index;                       // 0.0
/*154 */     st->attached_pic.flags       |= AV_PKT_FLAG_KEY;                                 // 0.0
/*158 */     asf->nb_streams++;                                                               // 0.0
/*162 */     if (*desc) {                                                                     // 0.0
/*164 */         if (av_dict_set(&st->metadata, "title", desc, AV_DICT_DONT_STRDUP_VAL) < 0)  // 0.0
/*166 */             av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");                      // 0.0
/*168 */     } else                                                                           // 0.0
/*170 */         av_freep(&desc);                                                             // 0.0
/*174 */     if (av_dict_set(&st->metadata, "comment", ff_id3v2_picture_types[type], 0) < 0)  // 0.0
/*176 */         av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");                          // 0.0
/*180 */     return 0;                                                                        // 0.0
/*184 */ fail:                                                                                // 0.0
/*186 */     av_freep(&desc);                                                                 // 0.0
/*188 */     av_free_packet(&pkt);                                                            // 0.0
/*190 */     return ret;                                                                      // 0.0
/*192 */ }                                                                                    // 0.0
