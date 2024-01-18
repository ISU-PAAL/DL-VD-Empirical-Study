// commit message FFmpeg@ec3b22326d (target=1, prob=0.53014344, correct=True): * Add support for time-limiting a live stream. (Some guy streamed one of   my pondcam streams for 24 hours! I'll bet he wasn't watching. * Add code to allocate the priv_data so that the ffm header can be   parsed again. [Fix crash]
/*0   */ static int http_prepare_data(HTTPContext *c)                                                                                                 // (15) 0.02734
/*2   */ {                                                                                                                                            // (22) 0.001953
/*4   */     int i;                                                                                                                                   // (21) 0.01172
/*8   */     switch(c->state) {                                                                                                                       // (17) 0.01953
/*10  */     case HTTPSTATE_SEND_DATA_HEADER:                                                                                                         // (14) 0.0293
/*12  */         memset(&c->fmt_ctx, 0, sizeof(c->fmt_ctx));                                                                                          // (7) 0.05469
/*14  */         if (c->stream->feed) {                                                                                                               // (12) 0.03125
/*16  */             /* open output stream by using specified codecs */                                                                               // (10) 0.04102
/*18  */             c->fmt_ctx.oformat = c->stream->fmt;                                                                                             // (8) 0.05469
/*20  */             c->fmt_ctx.nb_streams = c->stream->nb_streams;                                                                                   // (4) 0.0625
/*22  */             for(i=0;i<c->fmt_ctx.nb_streams;i++) {                                                                                           // (2) 0.06641
/*24  */                 AVStream *st;                                                                                                                // (11) 0.03906
/*26  */                 st = av_mallocz(sizeof(AVStream));                                                                                           // (6) 0.05664
/*28  */                 c->fmt_ctx.streams[i] = st;                                                                                                  // (5) 0.05859
/*30  */                 if (c->stream->feed == c->stream)                                                                                            // (9) 0.05273
/*32  */                     memcpy(st, c->stream->streams[i], sizeof(AVStream));                                                                     // (1) 0.07617
/*34  */                 else                                                                                                                         // (13) 0.03125
/*36  */                     memcpy(st, c->stream->feed->streams[c->stream->feed_streams[i]], sizeof(AVStream));                                      // (0) 0.09961
/*40  */                 st->codec.frame_number = 0; /* XXX: should be done in                                                                        // (3) 0.06445
/*42  */                                                AVStream, not in codec */                                                                     // 0.0
/*44  */             }                                                                                                                                // 0.0
/*46  */             c->got_key_frame = 0;                                                                                                            // 0.0
/*48  */         } else {                                                                                                                             // 0.0
/*50  */             /* open output stream by using codecs in specified file */                                                                       // 0.0
/*52  */             c->fmt_ctx.oformat = c->stream->fmt;                                                                                             // 0.0
/*54  */             c->fmt_ctx.nb_streams = c->fmt_in->nb_streams;                                                                                   // 0.0
/*56  */             for(i=0;i<c->fmt_ctx.nb_streams;i++) {                                                                                           // 0.0
/*58  */                 AVStream *st;                                                                                                                // 0.0
/*60  */                 st = av_mallocz(sizeof(AVStream));                                                                                           // 0.0
/*62  */                 c->fmt_ctx.streams[i] = st;                                                                                                  // 0.0
/*64  */                 memcpy(st, c->fmt_in->streams[i], sizeof(AVStream));                                                                         // 0.0
/*66  */                 st->codec.frame_number = 0; /* XXX: should be done in                                                                        // 0.0
/*68  */                                                AVStream, not in codec */                                                                     // 0.0
/*70  */             }                                                                                                                                // 0.0
/*72  */             c->got_key_frame = 0;                                                                                                            // 0.0
/*74  */         }                                                                                                                                    // 0.0
/*76  */         init_put_byte(&c->fmt_ctx.pb, c->pbuffer, PACKET_MAX_SIZE,                                                                           // 0.0
/*78  */                       1, c, NULL, http_write_packet, NULL);                                                                                  // 0.0
/*80  */         c->fmt_ctx.pb.is_streamed = 1;                                                                                                       // 0.0
/*82  */         /* prepare header */                                                                                                                 // 0.0
/*84  */         av_write_header(&c->fmt_ctx);                                                                                                        // 0.0
/*86  */         c->state = HTTPSTATE_SEND_DATA;                                                                                                      // 0.0
/*88  */         c->last_packet_sent = 0;                                                                                                             // 0.0
/*90  */         break;                                                                                                                               // 0.0
/*92  */     case HTTPSTATE_SEND_DATA:                                                                                                                // 0.0
/*94  */         /* find a new packet */                                                                                                              // 0.0
/*96  */ #if 0                                                                                                                                        // 0.0
/*98  */         fifo_total_size = http_fifo_write_count - c->last_http_fifo_write_count;                                                             // 0.0
/*100 */         if (fifo_total_size >= ((3 * FIFO_MAX_SIZE) / 4)) {                                                                                  // 0.0
/*102 */             /* overflow : resync. We suppose that wptr is at this                                                                            // 0.0
/*104 */                point a pointer to a valid packet */                                                                                          // 0.0
/*106 */             c->rptr = http_fifo.wptr;                                                                                                        // 0.0
/*108 */             c->got_key_frame = 0;                                                                                                            // 0.0
/*110 */         }                                                                                                                                    // 0.0
/*112 */                                                                                                                                              // (18) 0.01562
/*114 */         start_rptr = c->rptr;                                                                                                                // 0.0
/*116 */         if (fifo_read(&http_fifo, (UINT8 *)&hdr, sizeof(hdr), &c->rptr) < 0)                                                                 // 0.0
/*118 */             return 0;                                                                                                                        // 0.0
/*120 */         payload_size = ntohs(hdr.payload_size);                                                                                              // 0.0
/*122 */         payload = av_malloc(payload_size);                                                                                                   // 0.0
/*124 */         if (fifo_read(&http_fifo, payload, payload_size, &c->rptr) < 0) {                                                                    // 0.0
/*126 */             /* cannot read all the payload */                                                                                                // 0.0
/*128 */             av_free(payload);                                                                                                                // 0.0
/*130 */             c->rptr = start_rptr;                                                                                                            // 0.0
/*132 */             return 0;                                                                                                                        // 0.0
/*134 */         }                                                                                                                                    // 0.0
/*136 */                                                                                                                                              // (19) 0.01562
/*138 */         c->last_http_fifo_write_count = http_fifo_write_count -                                                                              // 0.0
/*140 */             fifo_size(&http_fifo, c->rptr);                                                                                                  // 0.0
/*142 */                                                                                                                                              // (20) 0.01562
/*144 */         if (c->stream->stream_type != STREAM_TYPE_MASTER) {                                                                                  // 0.0
/*146 */             /* test if the packet can be handled by this format */                                                                           // 0.0
/*148 */             ret = 0;                                                                                                                         // 0.0
/*150 */             for(i=0;i<c->fmt_ctx.nb_streams;i++) {                                                                                           // 0.0
/*152 */                 AVStream *st = c->fmt_ctx.streams[i];                                                                                        // 0.0
/*154 */                 if (test_header(&hdr, &st->codec)) {                                                                                         // 0.0
/*156 */                     /* only begin sending when got a key frame */                                                                            // 0.0
/*158 */                     if (st->codec.key_frame)                                                                                                 // 0.0
/*160 */                         c->got_key_frame |= 1 << i;                                                                                          // 0.0
/*162 */                     if (c->got_key_frame & (1 << i)) {                                                                                       // 0.0
/*164 */                         ret = c->fmt_ctx.format->write_packet(&c->fmt_ctx, i,                                                                // 0.0
/*166 */                                                                    payload, payload_size);                                                   // 0.0
/*168 */                     }                                                                                                                        // 0.0
/*170 */                     break;                                                                                                                   // 0.0
/*172 */                 }                                                                                                                            // 0.0
/*174 */             }                                                                                                                                // 0.0
/*176 */             if (ret) {                                                                                                                       // 0.0
/*178 */                 /* must send trailer now */                                                                                                  // 0.0
/*180 */                 c->state = HTTPSTATE_SEND_DATA_TRAILER;                                                                                      // 0.0
/*182 */             }                                                                                                                                // 0.0
/*184 */         } else {                                                                                                                             // 0.0
/*186 */             /* master case : send everything */                                                                                              // 0.0
/*188 */             char *q;                                                                                                                         // 0.0
/*190 */             q = c->buffer;                                                                                                                   // 0.0
/*192 */             memcpy(q, &hdr, sizeof(hdr));                                                                                                    // 0.0
/*194 */             q += sizeof(hdr);                                                                                                                // 0.0
/*196 */             memcpy(q, payload, payload_size);                                                                                                // 0.0
/*198 */             q += payload_size;                                                                                                               // 0.0
/*200 */             c->buffer_ptr = c->buffer;                                                                                                       // 0.0
/*202 */             c->buffer_end = q;                                                                                                               // 0.0
/*204 */         }                                                                                                                                    // 0.0
/*206 */         av_free(payload);                                                                                                                    // 0.0
/*208 */ #endif                                                                                                                                       // 0.0
/*210 */         {                                                                                                                                    // 0.0
/*212 */             AVPacket pkt;                                                                                                                    // 0.0
/*216 */             /* read a packet from the input stream */                                                                                        // 0.0
/*218 */             if (c->stream->feed) {                                                                                                           // 0.0
/*220 */                 ffm_set_write_index(c->fmt_in,                                                                                               // 0.0
/*222 */                                     c->stream->feed->feed_write_index,                                                                       // 0.0
/*224 */                                     c->stream->feed->feed_size);                                                                             // 0.0
/*226 */             }                                                                                                                                // 0.0
/*228 */                                                                                                                                              // (16) 0.02344
/*230 */             if (av_read_packet(c->fmt_in, &pkt) < 0) {                                                                                       // 0.0
/*232 */                 if (c->stream->feed && c->stream->feed->feed_opened) {                                                                       // 0.0
/*234 */                     /* if coming from feed, it means we reached the end of the                                                               // 0.0
/*236 */                        ffm file, so must wait for more data */                                                                               // 0.0
/*238 */                     c->state = HTTPSTATE_WAIT_FEED;                                                                                          // 0.0
/*240 */                     return 1; /* state changed */                                                                                            // 0.0
/*242 */                 } else {                                                                                                                     // 0.0
/*244 */                     /* must send trailer now because eof or error */                                                                         // 0.0
/*246 */                     c->state = HTTPSTATE_SEND_DATA_TRAILER;                                                                                  // 0.0
/*248 */                 }                                                                                                                            // 0.0
/*250 */             } else {                                                                                                                         // 0.0
/*252 */                 /* send it to the appropriate stream */                                                                                      // 0.0
/*254 */                 if (c->stream->feed) {                                                                                                       // 0.0
/*256 */                     /* if coming from a feed, select the right stream */                                                                     // 0.0
/*258 */                     for(i=0;i<c->stream->nb_streams;i++) {                                                                                   // 0.0
/*260 */                         if (c->stream->feed_streams[i] == pkt.stream_index) {                                                                // 0.0
/*262 */                             pkt.stream_index = i;                                                                                            // 0.0
/*264 */                             if (pkt.flags & PKT_FLAG_KEY) {                                                                                  // 0.0
/*266 */                                 c->got_key_frame |= 1 << i;                                                                                  // 0.0
/*268 */                             }                                                                                                                // 0.0
/*270 */                             /* See if we have all the key frames, then                                                                       // 0.0
/*272 */                              * we start to send. This logic is not quite                                                                     // 0.0
/*274 */                              * right, but it works for the case of a                                                                         // 0.0
/*276 */                              * single video stream with one or more                                                                          // 0.0
/*278 */                              * audio streams (for which every frame is                                                                       // 0.0
/*280 */                              * typically a key frame).                                                                                       // 0.0
/*282 */                              */                                                                                                              // 0.0
/*284 */                             if (!c->stream->send_on_key || ((c->got_key_frame + 1) >> c->stream->nb_streams)) {                              // 0.0
/*286 */                                 goto send_it;                                                                                                // 0.0
/*288 */                             }                                                                                                                // 0.0
/*290 */                         }                                                                                                                    // 0.0
/*292 */                     }                                                                                                                        // 0.0
/*294 */                 } else {                                                                                                                     // 0.0
/*296 */                     AVCodecContext *codec;                                                                                                   // 0.0
/*298 */                 send_it:                                                                                                                     // 0.0
/*300 */                     /* Fudge here */                                                                                                         // 0.0
/*302 */                     codec = &c->fmt_ctx.streams[pkt.stream_index]->codec;                                                                    // 0.0
/*306 */                     codec->key_frame = ((pkt.flags & PKT_FLAG_KEY) != 0);                                                                    // 0.0
/*310 */ #ifdef PJSG                                                                                                                                  // 0.0
/*312 */                     if (codec->codec_type == CODEC_TYPE_AUDIO) {                                                                             // 0.0
/*314 */                         codec->frame_size = (codec->sample_rate * pkt.duration + 500000) / 1000000;                                          // 0.0
/*316 */                         /* printf("Calculated size %d, from sr %d, duration %d\n", codec->frame_size, codec->sample_rate, pkt.duration); */  // 0.0
/*318 */                     }                                                                                                                        // 0.0
/*320 */ #endif                                                                                                                                       // 0.0
/*324 */                     if (av_write_packet(&c->fmt_ctx, &pkt, 0))                                                                               // 0.0
/*326 */                         c->state = HTTPSTATE_SEND_DATA_TRAILER;                                                                              // 0.0
/*330 */                     codec->frame_number++;                                                                                                   // 0.0
/*332 */                 }                                                                                                                            // 0.0
/*336 */                 av_free_packet(&pkt);                                                                                                        // 0.0
/*338 */             }                                                                                                                                // 0.0
/*340 */         }                                                                                                                                    // 0.0
/*342 */         break;                                                                                                                               // 0.0
/*344 */     default:                                                                                                                                 // 0.0
/*346 */     case HTTPSTATE_SEND_DATA_TRAILER:                                                                                                        // 0.0
/*348 */         /* last packet test ? */                                                                                                             // 0.0
/*350 */         if (c->last_packet_sent)                                                                                                             // 0.0
/*352 */             return -1;                                                                                                                       // 0.0
/*354 */         /* prepare header */                                                                                                                 // 0.0
/*356 */         av_write_trailer(&c->fmt_ctx);                                                                                                       // 0.0
/*358 */         c->last_packet_sent = 1;                                                                                                             // 0.0
/*360 */         break;                                                                                                                               // 0.0
/*362 */     }                                                                                                                                        // 0.0
/*364 */     return 0;                                                                                                                                // 0.0
/*366 */ }                                                                                                                                            // 0.0
