// commit message FFmpeg@7684a36113 (target=0, prob=0.56463045, correct=False): mxfenc: switch to av_reallocp_array() and check allocation errors
/*0   */ static int mxf_write_packet(AVFormatContext *s, AVPacket *pkt)                           // (8) 0.04492
/*2   */ {                                                                                        // (23) 0.001953
/*4   */     MXFContext *mxf = s->priv_data;                                                      // (13) 0.03125
/*6   */     AVIOContext *pb = s->pb;                                                             // (16) 0.02539
/*8   */     AVStream *st = s->streams[pkt->stream_index];                                        // (10) 0.03906
/*10  */     MXFStreamContext *sc = st->priv_data;                                                // (12) 0.03125
/*12  */     MXFIndexEntry ie = {0};                                                              // (18) 0.02344
/*16  */     if (!mxf->edit_unit_byte_count && !(mxf->edit_units_count % EDIT_UNITS_PER_BODY)) {  // (1) 0.07422
/*18  */         mxf->index_entries = av_realloc(mxf->index_entries,                              // (7) 0.05469
/*20  */             (mxf->edit_units_count + EDIT_UNITS_PER_BODY)*sizeof(*mxf->index_entries));  // (0) 0.08203
/*22  */         if (!mxf->index_entries) {                                                       // (11) 0.03516
/*24  */             av_log(s, AV_LOG_ERROR, "could not allocate index entries\n");               // (4) 0.0625
/*26  */             return -1;                                                                   // (14) 0.0293
/*28  */         }                                                                                // (19) 0.01563
/*30  */     }                                                                                    // (22) 0.007813
/*34  */     if (st->codec->codec_id == AV_CODEC_ID_MPEG2VIDEO) {                                 // (6) 0.05664
/*36  */         if (!mxf_parse_mpeg2_frame(s, st, pkt, &ie)) {                                   // (5) 0.05859
/*38  */             av_log(s, AV_LOG_ERROR, "could not get mpeg2 profile and level\n");          // (2) 0.07031
/*40  */             return -1;                                                                   // (15) 0.0293
/*42  */         }                                                                                // (20) 0.01563
/*44  */     }                                                                                    // (21) 0.007813
/*48  */     if (!mxf->header_written) {                                                          // (17) 0.02539
/*50  */         if (mxf->edit_unit_byte_count) {                                                 // (9) 0.04102
/*52  */             mxf_write_partition(s, 1, 2, header_open_partition_key, 1);                  // (3) 0.07031
/*54  */             mxf_write_klv_fill(s);                                                       // 0.0
/*56  */             mxf_write_index_table_segment(s);                                            // 0.0
/*58  */         } else {                                                                         // 0.0
/*60  */             mxf_write_partition(s, 0, 0, header_open_partition_key, 1);                  // 0.0
/*62  */         }                                                                                // 0.0
/*64  */         mxf->header_written = 1;                                                         // 0.0
/*66  */     }                                                                                    // 0.0
/*70  */     if (st->index == 0) {                                                                // 0.0
/*72  */         if (!mxf->edit_unit_byte_count &&                                                // 0.0
/*74  */             (!mxf->edit_units_count || mxf->edit_units_count > EDIT_UNITS_PER_BODY) &&   // 0.0
/*76  */             !(ie.flags & 0x33)) { // I frame, Gop start                                  // 0.0
/*78  */             mxf_write_klv_fill(s);                                                       // 0.0
/*80  */             mxf_write_partition(s, 1, 2, body_partition_key, 0);                         // 0.0
/*84  */             mxf_write_klv_fill(s);                                                       // 0.0
/*86  */             mxf_write_index_table_segment(s);                                            // 0.0
/*88  */         }                                                                                // 0.0
/*92  */         mxf_write_klv_fill(s);                                                           // 0.0
/*94  */         mxf_write_system_item(s);                                                        // 0.0
/*98  */         if (!mxf->edit_unit_byte_count) {                                                // 0.0
/*100 */             mxf->index_entries[mxf->edit_units_count].offset = mxf->body_offset;         // 0.0
/*102 */             mxf->index_entries[mxf->edit_units_count].flags = ie.flags;                  // 0.0
/*104 */             mxf->index_entries[mxf->edit_units_count].temporal_ref = ie.temporal_ref;    // 0.0
/*106 */             mxf->body_offset += KAG_SIZE; // size of system element                      // 0.0
/*108 */         }                                                                                // 0.0
/*110 */         mxf->edit_units_count++;                                                         // 0.0
/*112 */     } else if (!mxf->edit_unit_byte_count && st->index == 1) {                           // 0.0
/*114 */         mxf->index_entries[mxf->edit_units_count-1].slice_offset =                       // 0.0
/*116 */             mxf->body_offset - mxf->index_entries[mxf->edit_units_count-1].offset;       // 0.0
/*118 */     }                                                                                    // 0.0
/*122 */     mxf_write_klv_fill(s);                                                               // 0.0
/*124 */     avio_write(pb, sc->track_essence_element_key, 16); // write key                      // 0.0
/*126 */     if (s->oformat == &ff_mxf_d10_muxer) {                                               // 0.0
/*128 */         if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO)                                 // 0.0
/*130 */             mxf_write_d10_video_packet(s, st, pkt);                                      // 0.0
/*132 */         else                                                                             // 0.0
/*134 */             mxf_write_d10_audio_packet(s, st, pkt);                                      // 0.0
/*136 */     } else {                                                                             // 0.0
/*138 */         klv_encode_ber4_length(pb, pkt->size); // write length                           // 0.0
/*140 */         avio_write(pb, pkt->data, pkt->size);                                            // 0.0
/*142 */         mxf->body_offset += 16+4+pkt->size + klv_fill_size(16+4+pkt->size);              // 0.0
/*144 */     }                                                                                    // 0.0
/*148 */     avio_flush(pb);                                                                      // 0.0
/*152 */     return 0;                                                                            // 0.0
/*154 */ }                                                                                        // 0.0
