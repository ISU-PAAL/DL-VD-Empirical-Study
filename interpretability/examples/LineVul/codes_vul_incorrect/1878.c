// commit message FFmpeg@f028d4d1c3 (target=1, prob=0.47400147, correct=False): mxfdec: hybrid demuxing/seeking solution
/*0   */ static int mxf_read_header(AVFormatContext *s, AVFormatParameters *ap)                                         // (7) 0.04102
/*2   */ {                                                                                                              // (23) 0.001953
/*4   */     MXFContext *mxf = s->priv_data;                                                                            // (15) 0.03125
/*6   */     KLVPacket klv;                                                                                             // (20) 0.01758
/*8   */     int64_t essence_offset = 0;                                                                                // (17) 0.02539
/*12  */     mxf->last_forward_tell = INT64_MAX;                                                                        // (11) 0.0332
/*16  */     if (!mxf_read_sync(s->pb, mxf_header_partition_pack_key, 14)) {                                            // (2) 0.06055
/*18  */         av_log(s, AV_LOG_ERROR, "could not find header partition pack key\n");                                 // (3) 0.05859
/*20  */         return AVERROR_INVALIDDATA;                                                                            // (12) 0.0332
/*22  */     }                                                                                                          // (22) 0.007812
/*24  */     avio_seek(s->pb, -14, SEEK_CUR);                                                                           // (8) 0.04102
/*26  */     mxf->fc = s;                                                                                               // (19) 0.01953
/*28  */     mxf->run_in = avio_tell(s->pb);                                                                            // (9) 0.03711
/*32  */     while (!s->pb->eof_reached) {                                                                              // (16) 0.03125
/*34  */         const MXFMetadataReadTableEntry *metadata;                                                             // (10) 0.03516
/*38  */         if (klv_read_packet(&klv, s->pb) < 0) {                                                                // (4) 0.05469
/*40  */             /* EOF - seek to previous partition or stop */                                                     // (6) 0.04297
/*42  */             if(mxf_parse_handle_partition_or_eof(mxf) <= 0)                                                    // (1) 0.06641
/*44  */                 break;                                                                                         // (13) 0.0332
/*46  */             else                                                                                               // (18) 0.02344
/*48  */                 continue;                                                                                      // (14) 0.0332
/*50  */         }                                                                                                      // (21) 0.01562
/*54  */         PRINT_KEY(s, "read header", klv.key);                                                                  // (5) 0.04492
/*56  */         av_dlog(s, "size %"PRIu64" offset %#"PRIx64"\n", klv.length, klv.offset);                              // (0) 0.08789
/*58  */         if (IS_KLV_KEY(klv.key, mxf_encrypted_triplet_key) ||                                                  // 0.0
/*60  */             IS_KLV_KEY(klv.key, mxf_essence_element_key) ||                                                    // 0.0
/*62  */             IS_KLV_KEY(klv.key, mxf_avid_essence_element_key) ||                                               // 0.0
/*64  */             IS_KLV_KEY(klv.key, mxf_system_item_key)) {                                                        // 0.0
/*66  */             if (!mxf->current_partition->essence_offset) {                                                     // 0.0
/*68  */                 compute_partition_essence_offset(s, mxf, &klv);                                                // 0.0
/*70  */             }                                                                                                  // 0.0
/*74  */             if (!essence_offset)                                                                               // 0.0
/*76  */                 essence_offset = klv.offset;                                                                   // 0.0
/*80  */             /* seek to footer, previous partition or stop */                                                   // 0.0
/*82  */             if (mxf_parse_handle_essence(mxf) <= 0)                                                            // 0.0
/*84  */                 break;                                                                                         // 0.0
/*86  */             continue;                                                                                          // 0.0
/*88  */         } else if (!memcmp(klv.key, mxf_header_partition_pack_key, 13) &&                                      // 0.0
/*90  */                    klv.key[13] >= 2 && klv.key[13] <= 4 && mxf->current_partition) {                           // 0.0
/*92  */             /* next partition pack - keep going, seek to previous partition or stop */                         // 0.0
/*94  */             if(mxf_parse_handle_partition_or_eof(mxf) <= 0)                                                    // 0.0
/*96  */                 break;                                                                                         // 0.0
/*98  */         }                                                                                                      // 0.0
/*102 */         for (metadata = mxf_metadata_read_table; metadata->read; metadata++) {                                 // 0.0
/*104 */             if (IS_KLV_KEY(klv.key, metadata->key)) {                                                          // 0.0
/*106 */                 int res;                                                                                       // 0.0
/*108 */                 if (klv.key[5] == 0x53) {                                                                      // 0.0
/*110 */                     res = mxf_read_local_tags(mxf, &klv, metadata->read, metadata->ctx_size, metadata->type);  // 0.0
/*112 */                 } else {                                                                                       // 0.0
/*114 */                     uint64_t next = avio_tell(s->pb) + klv.length;                                             // 0.0
/*116 */                     res = metadata->read(mxf, s->pb, 0, klv.length, klv.key, klv.offset);                      // 0.0
/*118 */                     avio_seek(s->pb, next, SEEK_SET);                                                          // 0.0
/*120 */                 }                                                                                              // 0.0
/*122 */                 if (res < 0) {                                                                                 // 0.0
/*124 */                     av_log(s, AV_LOG_ERROR, "error reading header metadata\n");                                // 0.0
/*126 */                     return res;                                                                                // 0.0
/*128 */                 }                                                                                              // 0.0
/*130 */                 break;                                                                                         // 0.0
/*132 */             }                                                                                                  // 0.0
/*134 */         }                                                                                                      // 0.0
/*136 */         if (!metadata->read)                                                                                   // 0.0
/*138 */             avio_skip(s->pb, klv.length);                                                                      // 0.0
/*140 */     }                                                                                                          // 0.0
/*142 */     /* FIXME avoid seek */                                                                                     // 0.0
/*144 */     if (!essence_offset)  {                                                                                    // 0.0
/*146 */         av_log(s, AV_LOG_ERROR, "no essence\n");                                                               // 0.0
/*148 */         return AVERROR_INVALIDDATA;                                                                            // 0.0
/*150 */     }                                                                                                          // 0.0
/*152 */     avio_seek(s->pb, essence_offset, SEEK_SET);                                                                // 0.0
/*156 */     mxf_compute_essence_containers(mxf);                                                                       // 0.0
/*160 */     return mxf_parse_structural_metadata(mxf);                                                                 // 0.0
/*162 */ }                                                                                                              // 0.0
