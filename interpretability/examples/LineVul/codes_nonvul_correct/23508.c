// commit message FFmpeg@83548fe894 (target=0, prob=0.40310308, correct=True): lavf: fix usage of AVIOContext.seekable
/*0   */ static int avi_write_trailer(AVFormatContext *s)                                      // (13) 0.03125
/*2   */ {                                                                                     // (21) 0.001953
/*4   */     AVIContext *avi = s->priv_data;                                                   // (14) 0.03125
/*6   */     AVIOContext *pb = s->pb;                                                          // (16) 0.02539
/*8   */     int res = 0;                                                                      // (20) 0.01562
/*10  */     int i, j, n, nb_frames;                                                           // (15) 0.0293
/*12  */     int64_t file_size;                                                                // (17) 0.02148
/*16  */     if (pb->seekable) {                                                               // (18) 0.02148
/*18  */         if (avi->riff_id == 1) {                                                      // (12) 0.03711
/*20  */             ff_end_tag(pb, avi->movi_list);                                           // (4) 0.05273
/*22  */             res = avi_write_idx1(s);                                                  // (8) 0.04688
/*24  */             ff_end_tag(pb, avi->riff_start);                                          // (5) 0.05273
/*26  */         } else {                                                                      // (19) 0.01953
/*28  */             avi_write_ix(s);                                                          // (10) 0.03906
/*30  */             ff_end_tag(pb, avi->movi_list);                                           // (6) 0.05273
/*32  */             ff_end_tag(pb, avi->riff_start);                                          // (7) 0.05273
/*36  */             file_size = avio_tell(pb);                                                // (9) 0.04297
/*38  */             avio_seek(pb, avi->odml_list - 8, SEEK_SET);                              // (2) 0.06445
/*40  */             ffio_wfourcc(pb, "LIST"); /* Making this AVI OpenDML one */               // (3) 0.06445
/*42  */             avio_skip(pb, 16);                                                        // (11) 0.03906
/*46  */             for (n = nb_frames = 0; n < s->nb_streams; n++) {                         // (0) 0.06641
/*48  */                 AVCodecParameters *par = s->streams[n]->codecpar;                     // (1) 0.06641
/*50  */                 AVIStream *avist       = s->streams[n]->priv_data;                    // 0.0
/*54  */                 if (par->codec_type == AVMEDIA_TYPE_VIDEO) {                          // 0.0
/*56  */                     if (nb_frames < avist->packet_count)                              // 0.0
/*58  */                         nb_frames = avist->packet_count;                              // 0.0
/*60  */                 } else {                                                              // 0.0
/*62  */                     if (par->codec_id == AV_CODEC_ID_MP2 ||                           // 0.0
/*64  */                         par->codec_id == AV_CODEC_ID_MP3)                             // 0.0
/*66  */                         nb_frames += avist->packet_count;                             // 0.0
/*68  */                 }                                                                     // 0.0
/*70  */             }                                                                         // 0.0
/*72  */             avio_wl32(pb, nb_frames);                                                 // 0.0
/*74  */             avio_seek(pb, file_size, SEEK_SET);                                       // 0.0
/*78  */             avi_write_counters(s, avi->riff_id);                                      // 0.0
/*80  */         }                                                                             // 0.0
/*82  */     }                                                                                 // 0.0
/*86  */     for (i = 0; i < s->nb_streams; i++) {                                             // 0.0
/*88  */         AVIStream *avist = s->streams[i]->priv_data;                                  // 0.0
/*90  */         for (j = 0; j < avist->indexes.ents_allocated / AVI_INDEX_CLUSTER_SIZE; j++)  // 0.0
/*92  */             av_free(avist->indexes.cluster[j]);                                       // 0.0
/*94  */         av_freep(&avist->indexes.cluster);                                            // 0.0
/*96  */         avist->indexes.ents_allocated = avist->indexes.entry = 0;                     // 0.0
/*98  */     }                                                                                 // 0.0
/*102 */     return res;                                                                       // 0.0
/*104 */ }                                                                                     // 0.0
