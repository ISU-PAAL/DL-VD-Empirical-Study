// commit message FFmpeg@d7da4d47a6 (target=1, prob=0.4876698, correct=False): mxfdec: avoid double free and leaks.
/*0   */ static int mxf_read_header(AVFormatContext *s)                                                                                 // (16) 0.0293
/*2   */ {                                                                                                                              // (25) 0.001953
/*4   */     MXFContext *mxf = s->priv_data;                                                                                            // (15) 0.03125
/*6   */     KLVPacket klv;                                                                                                             // (21) 0.01758
/*8   */     int64_t essence_offset = 0;                                                                                                // (18) 0.02539
/*10  */     int ret;                                                                                                                   // (23) 0.01172
/*14  */     mxf->last_forward_tell = INT64_MAX;                                                                                        // (10) 0.0332
/*16  */     mxf->edit_units_per_packet = 1;                                                                                            // (11) 0.0332
/*20  */     if (!mxf_read_sync(s->pb, mxf_header_partition_pack_key, 14)) {                                                            // (2) 0.06055
/*22  */         av_log(s, AV_LOG_ERROR, "could not find header partition pack key\n");                                                 // (3) 0.05859
/*24  */         return AVERROR_INVALIDDATA;                                                                                            // (12) 0.0332
/*26  */     }                                                                                                                          // (24) 0.007812
/*28  */     avio_seek(s->pb, -14, SEEK_CUR);                                                                                           // (7) 0.04102
/*30  */     mxf->fc = s;                                                                                                               // (20) 0.01953
/*32  */     mxf->run_in = avio_tell(s->pb);                                                                                            // (8) 0.03711
/*36  */     while (!url_feof(s->pb)) {                                                                                                 // (17) 0.0293
/*38  */         const MXFMetadataReadTableEntry *metadata;                                                                             // (9) 0.03516
/*42  */         if (klv_read_packet(&klv, s->pb) < 0) {                                                                                // (4) 0.05469
/*44  */             /* EOF - seek to previous partition or stop */                                                                     // (6) 0.04297
/*46  */             if(mxf_parse_handle_partition_or_eof(mxf) <= 0)                                                                    // (1) 0.06641
/*48  */                 break;                                                                                                         // (13) 0.0332
/*50  */             else                                                                                                               // (19) 0.02344
/*52  */                 continue;                                                                                                      // (14) 0.0332
/*54  */         }                                                                                                                      // (22) 0.01562
/*58  */         PRINT_KEY(s, "read header", klv.key);                                                                                  // (5) 0.04492
/*60  */         av_dlog(s, "size %"PRIu64" offset %#"PRIx64"\n", klv.length, klv.offset);                                              // (0) 0.08789
/*62  */         if (IS_KLV_KEY(klv.key, mxf_encrypted_triplet_key) ||                                                                  // 0.0
/*64  */             IS_KLV_KEY(klv.key, mxf_essence_element_key) ||                                                                    // 0.0
/*66  */             IS_KLV_KEY(klv.key, mxf_avid_essence_element_key) ||                                                               // 0.0
/*68  */             IS_KLV_KEY(klv.key, mxf_system_item_key)) {                                                                        // 0.0
/*72  */             if (!mxf->current_partition) {                                                                                     // 0.0
/*74  */                 av_log(mxf->fc, AV_LOG_ERROR, "found essence prior to first PartitionPack\n");                                 // 0.0
/*76  */                 return AVERROR_INVALIDDATA;                                                                                    // 0.0
/*78  */             }                                                                                                                  // 0.0
/*82  */             if (!mxf->current_partition->essence_offset) {                                                                     // 0.0
/*84  */                 /* for OP1a we compute essence_offset                                                                          // 0.0
/*86  */                  * for OPAtom we point essence_offset after the KL (usually op1a_essence_offset + 20 or 25)                    // 0.0
/*88  */                  * TODO: for OP1a we could eliminate this entire if statement, always stopping parsing at op1a_essence_offset  // 0.0
/*90  */                  *       for OPAtom we still need the actual essence_offset though (the KL's length can vary)                  // 0.0
/*92  */                  */                                                                                                            // 0.0
/*94  */                 int64_t op1a_essence_offset =                                                                                  // 0.0
/*96  */                     round_to_kag(mxf->current_partition->this_partition +                                                      // 0.0
/*98  */                                  mxf->current_partition->pack_length,       mxf->current_partition->kag_size) +                // 0.0
/*100 */                     round_to_kag(mxf->current_partition->header_byte_count, mxf->current_partition->kag_size) +                // 0.0
/*102 */                     round_to_kag(mxf->current_partition->index_byte_count,  mxf->current_partition->kag_size);                 // 0.0
/*106 */                 if (mxf->op == OPAtom) {                                                                                       // 0.0
/*108 */                     /* point essence_offset to the actual data                                                                 // 0.0
/*110 */                     * OPAtom has all the essence in one big KLV                                                                // 0.0
/*112 */                     */                                                                                                         // 0.0
/*114 */                     mxf->current_partition->essence_offset = avio_tell(s->pb);                                                 // 0.0
/*116 */                     mxf->current_partition->essence_length = klv.length;                                                       // 0.0
/*118 */                 } else {                                                                                                       // 0.0
/*120 */                     /* NOTE: op1a_essence_offset may be less than to klv.offset (C0023S01.mxf)  */                             // 0.0
/*122 */                     mxf->current_partition->essence_offset = op1a_essence_offset;                                              // 0.0
/*124 */                 }                                                                                                              // 0.0
/*126 */             }                                                                                                                  // 0.0
/*130 */             if (!essence_offset)                                                                                               // 0.0
/*132 */                 essence_offset = klv.offset;                                                                                   // 0.0
/*136 */             /* seek to footer, previous partition or stop */                                                                   // 0.0
/*138 */             if (mxf_parse_handle_essence(mxf) <= 0)                                                                            // 0.0
/*140 */                 break;                                                                                                         // 0.0
/*142 */             continue;                                                                                                          // 0.0
/*144 */         } else if (!memcmp(klv.key, mxf_header_partition_pack_key, 13) &&                                                      // 0.0
/*146 */                    klv.key[13] >= 2 && klv.key[13] <= 4 && mxf->current_partition) {                                           // 0.0
/*148 */             /* next partition pack - keep going, seek to previous partition or stop */                                         // 0.0
/*150 */             if(mxf_parse_handle_partition_or_eof(mxf) <= 0)                                                                    // 0.0
/*152 */                 break;                                                                                                         // 0.0
/*154 */             else if (mxf->parsing_backward)                                                                                    // 0.0
/*156 */                 continue;                                                                                                      // 0.0
/*158 */             /* we're still parsing forward. proceed to parsing this partition pack */                                          // 0.0
/*160 */         }                                                                                                                      // 0.0
/*164 */         for (metadata = mxf_metadata_read_table; metadata->read; metadata++) {                                                 // 0.0
/*166 */             if (IS_KLV_KEY(klv.key, metadata->key)) {                                                                          // 0.0
/*168 */                 int res;                                                                                                       // 0.0
/*170 */                 if (klv.key[5] == 0x53) {                                                                                      // 0.0
/*172 */                     res = mxf_read_local_tags(mxf, &klv, metadata->read, metadata->ctx_size, metadata->type);                  // 0.0
/*174 */                 } else {                                                                                                       // 0.0
/*176 */                     uint64_t next = avio_tell(s->pb) + klv.length;                                                             // 0.0
/*178 */                     res = metadata->read(mxf, s->pb, 0, klv.length, klv.key, klv.offset);                                      // 0.0
/*182 */                     /* only seek forward, else this can loop for a long time */                                                // 0.0
/*184 */                     if (avio_tell(s->pb) > next) {                                                                             // 0.0
/*186 */                         av_log(s, AV_LOG_ERROR, "read past end of KLV @ %#"PRIx64"\n",                                         // 0.0
/*188 */                                klv.offset);                                                                                    // 0.0
/*190 */                         return AVERROR_INVALIDDATA;                                                                            // 0.0
/*192 */                     }                                                                                                          // 0.0
/*196 */                     avio_seek(s->pb, next, SEEK_SET);                                                                          // 0.0
/*198 */                 }                                                                                                              // 0.0
/*200 */                 if (res < 0) {                                                                                                 // 0.0
/*202 */                     av_log(s, AV_LOG_ERROR, "error reading header metadata\n");                                                // 0.0
/*204 */                     return res;                                                                                                // 0.0
/*206 */                 }                                                                                                              // 0.0
/*208 */                 break;                                                                                                         // 0.0
/*210 */             }                                                                                                                  // 0.0
/*212 */         }                                                                                                                      // 0.0
/*214 */         if (!metadata->read)                                                                                                   // 0.0
/*216 */             avio_skip(s->pb, klv.length);                                                                                      // 0.0
/*218 */     }                                                                                                                          // 0.0
/*220 */     /* FIXME avoid seek */                                                                                                     // 0.0
/*222 */     if (!essence_offset)  {                                                                                                    // 0.0
/*224 */         av_log(s, AV_LOG_ERROR, "no essence\n");                                                                               // 0.0
/*226 */         return AVERROR_INVALIDDATA;                                                                                            // 0.0
/*228 */     }                                                                                                                          // 0.0
/*230 */     avio_seek(s->pb, essence_offset, SEEK_SET);                                                                                // 0.0
/*234 */     mxf_compute_essence_containers(mxf);                                                                                       // 0.0
/*238 */     /* we need to do this before computing the index tables                                                                    // 0.0
/*240 */      * to be able to fill in zero IndexDurations with st->duration */                                                          // 0.0
/*242 */     if ((ret = mxf_parse_structural_metadata(mxf)) < 0)                                                                        // 0.0
/*244 */         return ret;                                                                                                            // 0.0
/*248 */     if ((ret = mxf_compute_index_tables(mxf)) < 0)                                                                             // 0.0
/*250 */         return ret;                                                                                                            // 0.0
/*254 */     if (mxf->nb_index_tables > 1) {                                                                                            // 0.0
/*256 */         /* TODO: look up which IndexSID to use via EssenceContainerData */                                                     // 0.0
/*258 */         av_log(mxf->fc, AV_LOG_INFO, "got %i index tables - only the first one (IndexSID %i) will be used\n",                  // 0.0
/*260 */                mxf->nb_index_tables, mxf->index_tables[0].index_sid);                                                          // 0.0
/*262 */     } else if (mxf->nb_index_tables == 0 && mxf->op == OPAtom) {                                                               // 0.0
/*264 */         av_log(mxf->fc, AV_LOG_ERROR, "cannot demux OPAtom without an index\n");                                               // 0.0
/*266 */         return AVERROR_INVALIDDATA;                                                                                            // 0.0
/*268 */     }                                                                                                                          // 0.0
/*272 */     mxf_handle_small_eubc(s);                                                                                                  // 0.0
/*276 */     return 0;                                                                                                                  // 0.0
/*278 */ }                                                                                                                              // 0.0
