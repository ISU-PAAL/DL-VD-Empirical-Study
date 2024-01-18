// commit message FFmpeg@69c1fe7c9c (target=0, prob=0.58781713, correct=False): mkv: Validate ASS Start and End fields
/*0  */ static int mkv_write_ass_blocks(AVFormatContext *s, AVIOContext *pb,             // (7) 0.04492
/*2  */                                 AVPacket *pkt)                                   // (0) 0.07422
/*4  */ {                                                                                // (20) 0.001953
/*6  */     MatroskaMuxContext *mkv = s->priv_data;                                      // (13) 0.03711
/*8  */     int i, layer = 0, max_duration = 0, size, line_size, data_size = pkt->size;  // (4) 0.06055
/*10 */     uint8_t *start, *end, *data = pkt->data;                                     // (10) 0.04102
/*12 */     ebml_master blockgroup;                                                      // (17) 0.01953
/*14 */     char buffer[2048];                                                           // (19) 0.01758
/*18 */     while (data_size) {                                                          // (18) 0.01953
/*20 */         int duration = ass_get_duration(data);                                   // (14) 0.03516
/*22 */         max_duration = FFMAX(duration, max_duration);                            // (11) 0.03906
/*24 */         end          = memchr(data, '\n', data_size);                            // (3) 0.0625
/*26 */         size         = line_size = end ? end - data + 1 : data_size;             // (2) 0.06445
/*28 */         size        -= end ? (end[-1] == '\r') + 1 : 0;                          // (1) 0.06641
/*30 */         start        = data;                                                     // (15) 0.03516
/*32 */         for (i = 0; i < 3; i++, start++)                                         // (9) 0.04297
/*34 */             if (!(start = memchr(start, ',', size - (start - data))))            // (5) 0.06055
/*36 */                 return max_duration;                                             // (12) 0.03906
/*38 */         size -= start - data;                                                    // (16) 0.02539
/*40 */         sscanf(data, "Dialogue: %d,", &layer);                                   // (8) 0.04492
/*42 */         i = snprintf(buffer, sizeof(buffer), "%" PRId64 ",%d,",                  // (6) 0.05469
/*44 */                      s->streams[pkt->stream_index]->nb_frames, layer);           // 0.0
/*46 */         size = FFMIN(i + size, sizeof(buffer));                                  // 0.0
/*48 */         memcpy(buffer + i, start, size - i);                                     // 0.0
/*52 */         av_log(s, AV_LOG_DEBUG,                                                  // 0.0
/*54 */                "Writing block at offset %" PRIu64 ", size %d, "                  // 0.0
/*56 */                "pts %" PRId64 ", duration %d\n",                                 // 0.0
/*58 */                avio_tell(pb), size, pkt->pts, duration);                         // 0.0
/*60 */         blockgroup = start_ebml_master(pb, MATROSKA_ID_BLOCKGROUP,               // 0.0
/*62 */                                        mkv_blockgroup_size(size));               // 0.0
/*64 */         put_ebml_id(pb, MATROSKA_ID_BLOCK);                                      // 0.0
/*66 */         put_ebml_num(pb, size + 4, 0);                                           // 0.0
/*68 */         // this assumes stream_index is less than 126                            // 0.0
/*70 */         avio_w8(pb, 0x80 | (pkt->stream_index + 1));                             // 0.0
/*72 */         avio_wb16(pb, pkt->pts - mkv->cluster_pts);                              // 0.0
/*74 */         avio_w8(pb, 0);                                                          // 0.0
/*76 */         avio_write(pb, buffer, size);                                            // 0.0
/*78 */         put_ebml_uint(pb, MATROSKA_ID_BLOCKDURATION, duration);                  // 0.0
/*80 */         end_ebml_master(pb, blockgroup);                                         // 0.0
/*84 */         data      += line_size;                                                  // 0.0
/*86 */         data_size -= line_size;                                                  // 0.0
/*88 */     }                                                                            // 0.0
/*92 */     return max_duration;                                                         // 0.0
/*94 */ }                                                                                // 0.0
