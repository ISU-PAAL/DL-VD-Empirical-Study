// commit message FFmpeg@7fffc87979 (target=0, prob=0.67458075, correct=False): 1000l _reserved  (found by checktree.sh)
/*0   */ static int wc3_read_header(AVFormatContext *s,                                                    // (10) 0.03125
/*2   */                            AVFormatParameters *ap)                                                // (0) 0.0625
/*4   */ {                                                                                                 // (32) 0.001953
/*6   */     Wc3DemuxContext *wc3 = s->priv_data;                                                          // (4) 0.03906
/*8   */     ByteIOContext *pb = s->pb;                                                                    // (17) 0.02539
/*10  */     unsigned int fourcc_tag;                                                                      // (24) 0.01953
/*12  */     unsigned int size;                                                                            // (29) 0.01367
/*14  */     AVStream *st;                                                                                 // (25) 0.01563
/*16  */     unsigned char preamble[WC3_PREAMBLE_SIZE];                                                    // (7) 0.03516
/*18  */     int ret = 0;                                                                                  // (27) 0.01562
/*20  */     int current_palette = 0;                                                                      // (22) 0.02148
/*22  */     int bytes_to_read;                                                                            // (23) 0.01953
/*24  */     int i;                                                                                        // (30) 0.01172
/*26  */     unsigned char rotate;                                                                         // (28) 0.01367
/*30  */     /* default context members */                                                                 // (26) 0.01562
/*32  */     wc3->width = WC3_DEFAULT_WIDTH;                                                               // (6) 0.03711
/*34  */     wc3->height = WC3_DEFAULT_HEIGHT;                                                             // (9) 0.03516
/*36  */     wc3->palettes = NULL;                                                                         // (19) 0.02344
/*38  */     wc3->palette_count = 0;                                                                       // (15) 0.02734
/*40  */     wc3->pts = 0;                                                                                 // (20) 0.02344
/*42  */     wc3->video_stream_index = wc3->audio_stream_index = 0;                                        // (2) 0.04883
/*46  */     /* skip the first 3 32-bit numbers */                                                         // (16) 0.02539
/*48  */     url_fseek(pb, 12, SEEK_CUR);                                                                  // (8) 0.03516
/*52  */     /* traverse through the chunks and load the header information before                         // (14) 0.02734
/*54  */      * the first BRCH tag */                                                                      // (21) 0.02148
/*56  */     if ((ret = get_buffer(pb, preamble, WC3_PREAMBLE_SIZE)) !=                                    // (1) 0.05273
/*58  */         WC3_PREAMBLE_SIZE)                                                                        // (11) 0.03125
/*60  */         return AVERROR(EIO);                                                                      // (12) 0.0293
/*62  */     fourcc_tag = AV_RL32(&preamble[0]);                                                           // (5) 0.03711
/*64  */     size = (AV_RB32(&preamble[4]) + 1) & (~1);                                                    // (3) 0.04687
/*68  */     do {                                                                                          // (31) 0.009766
/*70  */         switch (fourcc_tag) {                                                                     // (13) 0.0293
/*74  */         case SOND_TAG:                                                                            // (18) 0.02539
/*76  */         case INDX_TAG:                                                                            // 0.0
/*78  */             /* SOND unknown, INDX unnecessary; ignore both */                                     // 0.0
/*80  */             url_fseek(pb, size, SEEK_CUR);                                                        // 0.0
/*82  */             break;                                                                                // 0.0
/*86  */         case _PC__TAG:                                                                            // 0.0
/*88  */             /* need the number of palettes */                                                     // 0.0
/*90  */             url_fseek(pb, 8, SEEK_CUR);                                                           // 0.0
/*92  */             if ((ret = get_buffer(pb, preamble, 4)) != 4)                                         // 0.0
/*94  */                 return AVERROR(EIO);                                                              // 0.0
/*96  */             wc3->palette_count = AV_RL32(&preamble[0]);                                           // 0.0
/*98  */             if((unsigned)wc3->palette_count >= UINT_MAX / PALETTE_SIZE){                          // 0.0
/*100 */                 wc3->palette_count= 0;                                                            // 0.0
/*102 */                 return -1;                                                                        // 0.0
/*104 */             }                                                                                     // 0.0
/*106 */             wc3->palettes = av_malloc(wc3->palette_count * PALETTE_SIZE);                         // 0.0
/*108 */             break;                                                                                // 0.0
/*112 */         case BNAM_TAG:                                                                            // 0.0
/*114 */             /* load up the name */                                                                // 0.0
/*116 */             if ((unsigned)size < 512)                                                             // 0.0
/*118 */                 bytes_to_read = size;                                                             // 0.0
/*120 */             else                                                                                  // 0.0
/*122 */                 bytes_to_read = 512;                                                              // 0.0
/*124 */             if ((ret = get_buffer(pb, s->title, bytes_to_read)) != bytes_to_read)                 // 0.0
/*126 */                 return AVERROR(EIO);                                                              // 0.0
/*128 */             break;                                                                                // 0.0
/*132 */         case SIZE_TAG:                                                                            // 0.0
/*134 */             /* video resolution override */                                                       // 0.0
/*136 */             if ((ret = get_buffer(pb, preamble, WC3_PREAMBLE_SIZE)) !=                            // 0.0
/*138 */                 WC3_PREAMBLE_SIZE)                                                                // 0.0
/*140 */                 return AVERROR(EIO);                                                              // 0.0
/*142 */             wc3->width = AV_RL32(&preamble[0]);                                                   // 0.0
/*144 */             wc3->height = AV_RL32(&preamble[4]);                                                  // 0.0
/*146 */             break;                                                                                // 0.0
/*150 */         case PALT_TAG:                                                                            // 0.0
/*152 */             /* one of several palettes */                                                         // 0.0
/*154 */             if ((unsigned)current_palette >= wc3->palette_count)                                  // 0.0
/*156 */                 return AVERROR_INVALIDDATA;                                                       // 0.0
/*158 */             if ((ret = get_buffer(pb,                                                             // 0.0
/*160 */                 &wc3->palettes[current_palette * PALETTE_SIZE],                                   // 0.0
/*162 */                 PALETTE_SIZE)) != PALETTE_SIZE)                                                   // 0.0
/*164 */                 return AVERROR(EIO);                                                              // 0.0
/*168 */             /* transform the current palette in place */                                          // 0.0
/*170 */             for (i = current_palette * PALETTE_SIZE;                                              // 0.0
/*172 */                  i < (current_palette + 1) * PALETTE_SIZE; i++) {                                 // 0.0
/*174 */                 /* rotate each palette component left by 2 and use the result                     // 0.0
/*176 */                  * as an index into the color component table */                                  // 0.0
/*178 */                 rotate = ((wc3->palettes[i] << 2) & 0xFF) |                                       // 0.0
/*180 */                          ((wc3->palettes[i] >> 6) & 0xFF);                                        // 0.0
/*182 */                 wc3->palettes[i] = wc3_pal_lookup[rotate];                                        // 0.0
/*184 */             }                                                                                     // 0.0
/*186 */             current_palette++;                                                                    // 0.0
/*188 */             break;                                                                                // 0.0
/*192 */         default:                                                                                  // 0.0
/*194 */             av_log(s, AV_LOG_ERROR, "  unrecognized WC3 chunk: %c%c%c%c (0x%02X%02X%02X%02X)\n",  // 0.0
/*196 */                 preamble[0], preamble[1], preamble[2], preamble[3],                               // 0.0
/*198 */                 preamble[0], preamble[1], preamble[2], preamble[3]);                              // 0.0
/*200 */             return AVERROR_INVALIDDATA;                                                           // 0.0
/*202 */             break;                                                                                // 0.0
/*204 */         }                                                                                         // 0.0
/*208 */         if ((ret = get_buffer(pb, preamble, WC3_PREAMBLE_SIZE)) !=                                // 0.0
/*210 */             WC3_PREAMBLE_SIZE)                                                                    // 0.0
/*212 */             return AVERROR(EIO);                                                                  // 0.0
/*214 */         fourcc_tag = AV_RL32(&preamble[0]);                                                       // 0.0
/*216 */         /* chunk sizes are 16-bit aligned */                                                      // 0.0
/*218 */         size = (AV_RB32(&preamble[4]) + 1) & (~1);                                                // 0.0
/*222 */     } while (fourcc_tag != BRCH_TAG);                                                             // 0.0
/*226 */     /* initialize the decoder streams */                                                          // 0.0
/*228 */     st = av_new_stream(s, 0);                                                                     // 0.0
/*230 */     if (!st)                                                                                      // 0.0
/*232 */         return AVERROR(ENOMEM);                                                                   // 0.0
/*234 */     av_set_pts_info(st, 33, 1, 90000);                                                            // 0.0
/*236 */     wc3->video_stream_index = st->index;                                                          // 0.0
/*238 */     st->codec->codec_type = CODEC_TYPE_VIDEO;                                                     // 0.0
/*240 */     st->codec->codec_id = CODEC_ID_XAN_WC3;                                                       // 0.0
/*242 */     st->codec->codec_tag = 0;  /* no fourcc */                                                    // 0.0
/*244 */     st->codec->width = wc3->width;                                                                // 0.0
/*246 */     st->codec->height = wc3->height;                                                              // 0.0
/*250 */     /* palette considerations */                                                                  // 0.0
/*252 */     st->codec->palctrl = &wc3->palette_control;                                                   // 0.0
/*256 */     st = av_new_stream(s, 0);                                                                     // 0.0
/*258 */     if (!st)                                                                                      // 0.0
/*260 */         return AVERROR(ENOMEM);                                                                   // 0.0
/*262 */     av_set_pts_info(st, 33, 1, 90000);                                                            // 0.0
/*264 */     wc3->audio_stream_index = st->index;                                                          // 0.0
/*266 */     st->codec->codec_type = CODEC_TYPE_AUDIO;                                                     // 0.0
/*268 */     st->codec->codec_id = CODEC_ID_PCM_S16LE;                                                     // 0.0
/*270 */     st->codec->codec_tag = 1;                                                                     // 0.0
/*272 */     st->codec->channels = WC3_AUDIO_CHANNELS;                                                     // 0.0
/*274 */     st->codec->bits_per_sample = WC3_AUDIO_BITS;                                                  // 0.0
/*276 */     st->codec->sample_rate = WC3_SAMPLE_RATE;                                                     // 0.0
/*278 */     st->codec->bit_rate = st->codec->channels * st->codec->sample_rate *                          // 0.0
/*280 */         st->codec->bits_per_sample;                                                               // 0.0
/*282 */     st->codec->block_align = WC3_AUDIO_BITS * WC3_AUDIO_CHANNELS;                                 // 0.0
/*286 */     return 0;                                                                                     // 0.0
/*288 */ }                                                                                                 // 0.0
