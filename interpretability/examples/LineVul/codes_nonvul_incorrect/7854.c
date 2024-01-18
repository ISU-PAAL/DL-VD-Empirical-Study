// commit message FFmpeg@d85aa76115 (target=0, prob=0.78965455, correct=False): avcodec/hevc: allocate entries unconditionally
/*0   */ static int hls_slice_data_wpp(HEVCContext *s, const HEVCNAL *nal)                                             // (7) 0.05602
/*2   */ {                                                                                                             // (24) 0.003082
/*4   */     const uint8_t *data = nal->data;                                                                          // (11) 0.03074
/*6   */     int length          = nal->size;                                                                          // (9) 0.03833
/*8   */     HEVCLocalContext *lc = s->HEVClc;                                                                         // (10) 0.03455
/*10  */     int *ret = av_malloc_array(s->sh.num_entry_point_offsets + 1, sizeof(int));                               // (3) 0.06368
/*12  */     int *arg = av_malloc_array(s->sh.num_entry_point_offsets + 1, sizeof(int));                               // (4) 0.06361
/*14  */     int64_t offset;                                                                                           // (20) 0.0175
/*16  */     int startheader, cmpt = 0;                                                                                // (13) 0.0294
/*18  */     int i, j, res = 0;                                                                                        // (18) 0.02325
/*22  */     if (!ret || !arg) {                                                                                       // (19) 0.02195
/*24  */         av_free(ret);                                                                                         // (15) 0.02576
/*26  */         av_free(arg);                                                                                         // (16) 0.02514
/*28  */         return AVERROR(ENOMEM);                                                                               // (12) 0.03066
/*30  */     }                                                                                                         // (23) 0.007712
/*36  */     if (!s->sList[1]) {                                                                                       // (17) 0.02496
/*38  */         ff_alloc_entries(s->avctx, s->sh.num_entry_point_offsets + 1);                                        // (1) 0.06529
/*44  */         for (i = 1; i < s->threads_number; i++) {                                                             // (8) 0.04803
/*46  */             s->sList[i] = av_malloc(sizeof(HEVCContext));                                                     // (5) 0.05934
/*48  */             memcpy(s->sList[i], s, sizeof(HEVCContext));                                                      // (6) 0.05748
/*50  */             s->HEVClcList[i] = av_mallocz(sizeof(HEVCLocalContext));                                          // (0) 0.07078
/*52  */             s->sList[i]->HEVClc = s->HEVClcList[i];                                                           // (2) 0.06501
/*54  */         }                                                                                                     // (21) 0.01531
/*56  */     }                                                                                                         // (22) 0.007787
/*60  */     offset = (lc->gb.index >> 3);                                                                             // (14) 0.0269
/*64  */     for (j = 0, cmpt = 0, startheader = offset + s->sh.entry_point_offset[0]; j < nal->skipped_bytes; j++) {  // 0.0
/*66  */         if (nal->skipped_bytes_pos[j] >= offset && nal->skipped_bytes_pos[j] < startheader) {                 // 0.0
/*68  */             startheader--;                                                                                    // 0.0
/*70  */             cmpt++;                                                                                           // 0.0
/*72  */         }                                                                                                     // 0.0
/*74  */     }                                                                                                         // 0.0
/*78  */     for (i = 1; i < s->sh.num_entry_point_offsets; i++) {                                                     // 0.0
/*80  */         offset += (s->sh.entry_point_offset[i - 1] - cmpt);                                                   // 0.0
/*82  */         for (j = 0, cmpt = 0, startheader = offset                                                            // 0.0
/*84  */              + s->sh.entry_point_offset[i]; j < nal->skipped_bytes; j++) {                                    // 0.0
/*86  */             if (nal->skipped_bytes_pos[j] >= offset && nal->skipped_bytes_pos[j] < startheader) {             // 0.0
/*88  */                 startheader--;                                                                                // 0.0
/*90  */                 cmpt++;                                                                                       // 0.0
/*92  */             }                                                                                                 // 0.0
/*94  */         }                                                                                                     // 0.0
/*96  */         s->sh.size[i - 1] = s->sh.entry_point_offset[i] - cmpt;                                               // 0.0
/*98  */         s->sh.offset[i - 1] = offset;                                                                         // 0.0
/*102 */     }                                                                                                         // 0.0
/*104 */     if (s->sh.num_entry_point_offsets != 0) {                                                                 // 0.0
/*106 */         offset += s->sh.entry_point_offset[s->sh.num_entry_point_offsets - 1] - cmpt;                         // 0.0
/*108 */         if (length < offset) {                                                                                // 0.0
/*110 */             av_log(s->avctx, AV_LOG_ERROR, "entry_point_offset table is corrupted\n");                        // 0.0
/*112 */             res = AVERROR_INVALIDDATA;                                                                        // 0.0
/*114 */             goto error;                                                                                       // 0.0
/*116 */         }                                                                                                     // 0.0
/*118 */         s->sh.size[s->sh.num_entry_point_offsets - 1] = length - offset;                                      // 0.0
/*120 */         s->sh.offset[s->sh.num_entry_point_offsets - 1] = offset;                                             // 0.0
/*124 */     }                                                                                                         // 0.0
/*126 */     s->data = data;                                                                                           // 0.0
/*130 */     for (i = 1; i < s->threads_number; i++) {                                                                 // 0.0
/*132 */         s->sList[i]->HEVClc->first_qp_group = 1;                                                              // 0.0
/*134 */         s->sList[i]->HEVClc->qp_y = s->sList[0]->HEVClc->qp_y;                                                // 0.0
/*136 */         memcpy(s->sList[i], s, sizeof(HEVCContext));                                                          // 0.0
/*138 */         s->sList[i]->HEVClc = s->HEVClcList[i];                                                               // 0.0
/*140 */     }                                                                                                         // 0.0
/*144 */     avpriv_atomic_int_set(&s->wpp_err, 0);                                                                    // 0.0
/*146 */     ff_reset_entries(s->avctx);                                                                               // 0.0
/*150 */     for (i = 0; i <= s->sh.num_entry_point_offsets; i++) {                                                    // 0.0
/*152 */         arg[i] = i;                                                                                           // 0.0
/*154 */         ret[i] = 0;                                                                                           // 0.0
/*156 */     }                                                                                                         // 0.0
/*160 */     if (s->ps.pps->entropy_coding_sync_enabled_flag)                                                          // 0.0
/*162 */         s->avctx->execute2(s->avctx, hls_decode_entry_wpp, arg, ret, s->sh.num_entry_point_offsets + 1);      // 0.0
/*166 */     for (i = 0; i <= s->sh.num_entry_point_offsets; i++)                                                      // 0.0
/*168 */         res += ret[i];                                                                                        // 0.0
/*170 */ error:                                                                                                        // 0.0
/*172 */     av_free(ret);                                                                                             // 0.0
/*174 */     av_free(arg);                                                                                             // 0.0
/*176 */     return res;                                                                                               // 0.0
/*178 */ }                                                                                                             // 0.0
