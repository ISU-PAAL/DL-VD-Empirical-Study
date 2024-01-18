// commit message FFmpeg@83548fe894 (target=0, prob=0.61459464, correct=False): lavf: fix usage of AVIOContext.seekable
/*0   */ static int avi_write_packet(AVFormatContext *s, AVPacket *pkt)                  // (8) 0.0449
/*2   */ {                                                                               // (24) 0.001953
/*4   */     unsigned char tag[5];                                                       // (21) 0.01757
/*6   */     unsigned int flags = 0;                                                     // (22) 0.01757
/*8   */     const int stream_index = pkt->stream_index;                                 // (16) 0.03125
/*10  */     int size               = pkt->size;                                         // (4) 0.0488
/*12  */     AVIContext *avi     = s->priv_data;                                         // (12) 0.03904
/*14  */     AVIOContext *pb     = s->pb;                                                // (15) 0.03318
/*16  */     AVIStream *avist    = s->streams[stream_index]->priv_data;                  // (2) 0.0527
/*18  */     AVCodecParameters *par = s->streams[stream_index]->codecpar;                // (5) 0.04685
/*22  */     while (par->block_align == 0 && pkt->dts != AV_NOPTS_VALUE &&               // (1) 0.05271
/*24  */            pkt->dts > avist->packet_count) {                                    // (3) 0.0488
/*26  */         AVPacket empty_packet;                                                  // (18) 0.02928
/*30  */         av_init_packet(&empty_packet);                                          // (14) 0.03709
/*32  */         empty_packet.size         = 0;                                          // (7) 0.04685
/*34  */         empty_packet.data         = NULL;                                       // (6) 0.04685
/*36  */         empty_packet.stream_index = stream_index;                               // (13) 0.03904
/*38  */         avi_write_packet(s, &empty_packet);                                     // (10) 0.0449
/*40  */     }                                                                           // (23) 0.007815
/*42  */     avist->packet_count++;                                                      // (19) 0.02158
/*46  */     // Make sure to put an OpenDML chunk when the file size exceeds the limits  // (11) 0.0394
/*48  */     if (pb->seekable &&                                                         // (20) 0.01954
/*50  */         (avio_tell(pb) - avi->riff_start > AVI_MAX_RIFF_SIZE)) {                // (0) 0.06832
/*52  */         avi_write_ix(s);                                                        // (17) 0.03123
/*54  */         ff_end_tag(pb, avi->movi_list);                                         // (9) 0.0449
/*58  */         if (avi->riff_id == 1)                                                  // 0.0
/*60  */             avi_write_idx1(s);                                                  // 0.0
/*64  */         ff_end_tag(pb, avi->riff_start);                                        // 0.0
/*66  */         avi->movi_list = avi_start_new_riff(s, pb, "AVIX", "movi");             // 0.0
/*68  */     }                                                                           // 0.0
/*72  */     avi_stream2fourcc(tag, stream_index, par->codec_type);                      // 0.0
/*74  */     if (pkt->flags & AV_PKT_FLAG_KEY)                                           // 0.0
/*76  */         flags = 0x10;                                                           // 0.0
/*78  */     if (par->codec_type == AVMEDIA_TYPE_AUDIO)                                  // 0.0
/*80  */         avist->audio_strm_length += size;                                       // 0.0
/*84  */     if (s->pb->seekable) {                                                      // 0.0
/*86  */         int err;                                                                // 0.0
/*88  */         AVIIndex *idx = &avist->indexes;                                        // 0.0
/*90  */         int cl = idx->entry / AVI_INDEX_CLUSTER_SIZE;                           // 0.0
/*92  */         int id = idx->entry % AVI_INDEX_CLUSTER_SIZE;                           // 0.0
/*94  */         if (idx->ents_allocated <= idx->entry) {                                // 0.0
/*96  */             if ((err = av_reallocp(&idx->cluster,                               // 0.0
/*98  */                                    (cl + 1) * sizeof(*idx->cluster))) < 0) {    // 0.0
/*100 */                 idx->ents_allocated = 0;                                        // 0.0
/*102 */                 idx->entry          = 0;                                        // 0.0
/*104 */                 return err;                                                     // 0.0
/*106 */             }                                                                   // 0.0
/*108 */             idx->cluster[cl] =                                                  // 0.0
/*110 */                 av_malloc(AVI_INDEX_CLUSTER_SIZE * sizeof(AVIIentry));          // 0.0
/*112 */             if (!idx->cluster[cl])                                              // 0.0
/*114 */                 return -1;                                                      // 0.0
/*116 */             idx->ents_allocated += AVI_INDEX_CLUSTER_SIZE;                      // 0.0
/*118 */         }                                                                       // 0.0
/*122 */         idx->cluster[cl][id].flags = flags;                                     // 0.0
/*124 */         idx->cluster[cl][id].pos   = avio_tell(pb) - avi->movi_list;            // 0.0
/*126 */         idx->cluster[cl][id].len   = size;                                      // 0.0
/*128 */         idx->entry++;                                                           // 0.0
/*130 */     }                                                                           // 0.0
/*134 */     avio_write(pb, tag, 4);                                                     // 0.0
/*136 */     avio_wl32(pb, size);                                                        // 0.0
/*138 */     avio_write(pb, pkt->data, size);                                            // 0.0
/*140 */     if (size & 1)                                                               // 0.0
/*142 */         avio_w8(pb, 0);                                                         // 0.0
/*146 */     return 0;                                                                   // 0.0
/*148 */ }                                                                               // 0.0
