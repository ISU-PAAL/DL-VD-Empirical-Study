// commit message FFmpeg@73e8e8dbf9 (target=1, prob=0.9990933, correct=True): lavf: Add an option to discard corrupted frames
/*0  */ int av_read_packet(AVFormatContext *s, AVPacket *pkt)                                                   // (12) 0.04102
/*1  */ {                                                                                                       // (20) 0.001953
/*2  */     int ret, i;                                                                                         // (18) 0.01563
/*3  */     AVStream *st;                                                                                       // (17) 0.01563
/*4  */     for(;;){                                                                                            // (19) 0.01367
/*5  */         AVPacketList *pktl = s->raw_packet_buffer;                                                      // (6) 0.04883
/*6  */         if (pktl) {                                                                                     // (16) 0.02734
/*7  */             *pkt = pktl->pkt;                                                                           // (11) 0.04297
/*8  */             if(s->streams[pkt->stream_index]->codec->codec_id != CODEC_ID_PROBE ||                      // (0) 0.08594
/*9  */                !s->streams[pkt->stream_index]->probe_packets ||                                         // (3) 0.06641
/*10 */                s->raw_packet_buffer_remaining_size < pkt->size){                                        // (4) 0.06445
/*11 */                 AVProbeData *pd = &s->streams[pkt->stream_index]->probe_data;                           // (1) 0.08008
/*12 */                 av_freep(&pd->buf);                                                                     // (8) 0.04687
/*13 */                 pd->buf_size = 0;                                                                       // (9) 0.04687
/*14 */                 s->raw_packet_buffer = pktl->next;                                                      // (5) 0.05859
/*15 */                 s->raw_packet_buffer_remaining_size += pkt->size;                                       // (2) 0.06641
/*16 */                 av_free(pktl);                                                                          // (10) 0.04492
/*17 */                 return 0;                                                                               // (13) 0.03516
/*18 */         av_init_packet(pkt);                                                                            // (14) 0.0332
/*19 */         ret= s->iformat->read_packet(s, pkt);                                                           // (7) 0.04688
/*20 */         if (ret < 0) {                                                                                  // (15) 0.02734
/*21 */             if (!pktl || ret == AVERROR(EAGAIN))                                                        // 0.0
/*22 */                 return ret;                                                                             // 0.0
/*23 */             for (i = 0; i < s->nb_streams; i++)                                                         // 0.0
/*24 */                 s->streams[i]->probe_packets = 0;                                                       // 0.0
/*25 */         st= s->streams[pkt->stream_index];                                                              // 0.0
/*26 */         switch(st->codec->codec_type){                                                                  // 0.0
/*27 */         case AVMEDIA_TYPE_VIDEO:                                                                        // 0.0
/*28 */             if(s->video_codec_id)   st->codec->codec_id= s->video_codec_id;                             // 0.0
/*29 */             break;                                                                                      // 0.0
/*30 */         case AVMEDIA_TYPE_AUDIO:                                                                        // 0.0
/*31 */             if(s->audio_codec_id)   st->codec->codec_id= s->audio_codec_id;                             // 0.0
/*32 */             break;                                                                                      // 0.0
/*33 */         case AVMEDIA_TYPE_SUBTITLE:                                                                     // 0.0
/*34 */             if(s->subtitle_codec_id)st->codec->codec_id= s->subtitle_codec_id;                          // 0.0
/*35 */             break;                                                                                      // 0.0
/*36 */         if(!pktl && (st->codec->codec_id != CODEC_ID_PROBE ||                                           // 0.0
/*37 */                      !st->probe_packets))                                                               // 0.0
/*38 */             return ret;                                                                                 // 0.0
/*39 */         add_to_pktbuf(&s->raw_packet_buffer, pkt, &s->raw_packet_buffer_end);                           // 0.0
/*40 */         s->raw_packet_buffer_remaining_size -= pkt->size;                                               // 0.0
/*41 */         if(st->codec->codec_id == CODEC_ID_PROBE){                                                      // 0.0
/*42 */             AVProbeData *pd = &st->probe_data;                                                          // 0.0
/*43 */             av_log(s, AV_LOG_DEBUG, "probing stream %d\n", st->index);                                  // 0.0
/*44 */             --st->probe_packets;                                                                        // 0.0
/*45 */             pd->buf = av_realloc(pd->buf, pd->buf_size+pkt->size+AVPROBE_PADDING_SIZE);                 // 0.0
/*46 */             memcpy(pd->buf+pd->buf_size, pkt->data, pkt->size);                                         // 0.0
/*47 */             pd->buf_size += pkt->size;                                                                  // 0.0
/*48 */             memset(pd->buf+pd->buf_size, 0, AVPROBE_PADDING_SIZE);                                      // 0.0
/*49 */             if(av_log2(pd->buf_size) != av_log2(pd->buf_size - pkt->size)){                             // 0.0
/*50 */                 //FIXME we dont reduce score to 0 for the case of running out of buffer space in bytes  // 0.0
/*51 */                 set_codec_from_probe_data(s, st, pd, st->probe_packets > 0 ? AVPROBE_SCORE_MAX/4 : 0);  // 0.0
/*52 */                 if(st->codec->codec_id != CODEC_ID_PROBE){                                              // 0.0
/*53 */                     pd->buf_size=0;                                                                     // 0.0
/*54 */                     av_freep(&pd->buf);                                                                 // 0.0
/*55 */                     av_log(s, AV_LOG_DEBUG, "probed stream %d\n", st->index);                           // 0.0
