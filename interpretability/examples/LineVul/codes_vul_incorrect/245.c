// commit message FFmpeg@7bf3f38046 (target=1, prob=0.25192082, correct=False): cbs: Add padding to slice data allocations
/*0   */ static int cbs_h265_read_nal_unit(CodedBitstreamContext *ctx,                     // (6) 0.04492
/*2   */                                   CodedBitstreamUnit *unit)                       // (0) 0.08008
/*4   */ {                                                                                 // (27) 0.001953
/*6   */     BitstreamContext bc;                                                          // (22) 0.01562
/*8   */     int err;                                                                      // (26) 0.01172
/*12  */     err = bitstream_init(&bc, unit->data, 8 * unit->data_size);                   // (4) 0.04687
/*14  */     if (err < 0)                                                                  // (21) 0.01758
/*16  */         return err;                                                               // (19) 0.01953
/*20  */     switch (unit->type) {                                                         // (18) 0.01953
/*22  */     case HEVC_NAL_VPS:                                                            // (16) 0.02539
/*24  */         {                                                                         // (25) 0.01562
/*26  */             H265RawVPS *vps;                                                      // (9) 0.03906
/*30  */             vps = av_mallocz(sizeof(*vps));                                       // (3) 0.05078
/*32  */             if (!vps)                                                             // (14) 0.03125
/*34  */                 return AVERROR(ENOMEM);                                           // (5) 0.04687
/*36  */             err = cbs_h265_read_vps(ctx, &bc, vps);                               // (2) 0.0625
/*38  */             if (err >= 0)                                                         // (13) 0.0332
/*40  */                 err = cbs_h265_replace_vps(ctx, vps);                             // (1) 0.06445
/*42  */             if (err < 0) {                                                        // (11) 0.03516
/*44  */                 av_free(vps);                                                     // (7) 0.04297
/*46  */                 return err;                                                       // (12) 0.03516
/*48  */             }                                                                     // (17) 0.02344
/*52  */             unit->content = vps;                                                  // (10) 0.03516
/*54  */         }                                                                         // (24) 0.01562
/*56  */         break;                                                                    // (20) 0.01758
/*58  */     case HEVC_NAL_SPS:                                                            // (15) 0.02539
/*60  */         {                                                                         // (23) 0.01562
/*62  */             H265RawSPS *sps;                                                      // (8) 0.03906
/*66  */             sps = av_mallocz(sizeof(*sps));                                       // 0.0
/*68  */             if (!sps)                                                             // 0.0
/*70  */                 return AVERROR(ENOMEM);                                           // 0.0
/*72  */             err = cbs_h265_read_sps(ctx, &bc, sps);                               // 0.0
/*74  */             if (err >= 0)                                                         // 0.0
/*76  */                 err = cbs_h265_replace_sps(ctx, sps);                             // 0.0
/*78  */             if (err < 0) {                                                        // 0.0
/*80  */                 av_free(sps);                                                     // 0.0
/*82  */                 return err;                                                       // 0.0
/*84  */             }                                                                     // 0.0
/*88  */             unit->content = sps;                                                  // 0.0
/*90  */         }                                                                         // 0.0
/*92  */         break;                                                                    // 0.0
/*96  */     case HEVC_NAL_PPS:                                                            // 0.0
/*98  */         {                                                                         // 0.0
/*100 */             H265RawPPS *pps;                                                      // 0.0
/*104 */             pps = av_mallocz(sizeof(*pps));                                       // 0.0
/*106 */             if (!pps)                                                             // 0.0
/*108 */                 return AVERROR(ENOMEM);                                           // 0.0
/*110 */             err = cbs_h265_read_pps(ctx, &bc, pps);                               // 0.0
/*112 */             if (err >= 0)                                                         // 0.0
/*114 */                 err = cbs_h265_replace_pps(ctx, pps);                             // 0.0
/*116 */             if (err < 0) {                                                        // 0.0
/*118 */                 av_free(pps);                                                     // 0.0
/*120 */                 return err;                                                       // 0.0
/*122 */             }                                                                     // 0.0
/*126 */             unit->content = pps;                                                  // 0.0
/*128 */         }                                                                         // 0.0
/*130 */         break;                                                                    // 0.0
/*134 */     case HEVC_NAL_TRAIL_N:                                                        // 0.0
/*136 */     case HEVC_NAL_TRAIL_R:                                                        // 0.0
/*138 */     case HEVC_NAL_TSA_N:                                                          // 0.0
/*140 */     case HEVC_NAL_TSA_R:                                                          // 0.0
/*142 */     case HEVC_NAL_STSA_N:                                                         // 0.0
/*144 */     case HEVC_NAL_STSA_R:                                                         // 0.0
/*146 */     case HEVC_NAL_RADL_N:                                                         // 0.0
/*148 */     case HEVC_NAL_RADL_R:                                                         // 0.0
/*150 */     case HEVC_NAL_RASL_N:                                                         // 0.0
/*152 */     case HEVC_NAL_RASL_R:                                                         // 0.0
/*154 */     case HEVC_NAL_BLA_W_LP:                                                       // 0.0
/*156 */     case HEVC_NAL_BLA_W_RADL:                                                     // 0.0
/*158 */     case HEVC_NAL_BLA_N_LP:                                                       // 0.0
/*160 */     case HEVC_NAL_IDR_W_RADL:                                                     // 0.0
/*162 */     case HEVC_NAL_IDR_N_LP:                                                       // 0.0
/*164 */     case HEVC_NAL_CRA_NUT:                                                        // 0.0
/*166 */         {                                                                         // 0.0
/*168 */             H265RawSlice *slice;                                                  // 0.0
/*170 */             int pos, len;                                                         // 0.0
/*174 */             slice = av_mallocz(sizeof(*slice));                                   // 0.0
/*176 */             if (!slice)                                                           // 0.0
/*178 */                 return AVERROR(ENOMEM);                                           // 0.0
/*180 */             err = cbs_h265_read_slice_segment_header(ctx, &bc, &slice->header);   // 0.0
/*182 */             if (err < 0) {                                                        // 0.0
/*184 */                 av_free(slice);                                                   // 0.0
/*186 */                 return err;                                                       // 0.0
/*188 */             }                                                                     // 0.0
/*192 */             pos = bitstream_tell(&bc);                                            // 0.0
/*194 */             len = unit->data_size;                                                // 0.0
/*196 */             if (!unit->data[len - 1]) {                                           // 0.0
/*198 */                 int z;                                                            // 0.0
/*200 */                 for (z = 0; z < len && !unit->data[len - z - 1]; z++);            // 0.0
/*202 */                 av_log(ctx->log_ctx, AV_LOG_DEBUG, "Deleted %d trailing zeroes "  // 0.0
/*204 */                        "from slice data.\n", z);                                  // 0.0
/*206 */                 len -= z;                                                         // 0.0
/*208 */             }                                                                     // 0.0
/*212 */             slice->data_size = len - pos / 8;                                     // 0.0
/*214 */             slice->data = av_malloc(slice->data_size);                            // 0.0
/*216 */             if (!slice->data) {                                                   // 0.0
/*218 */                 av_free(slice);                                                   // 0.0
/*220 */                 return AVERROR(ENOMEM);                                           // 0.0
/*222 */             }                                                                     // 0.0
/*224 */             memcpy(slice->data,                                                   // 0.0
/*226 */                    unit->data + pos / 8, slice->data_size);                       // 0.0
/*228 */             slice->data_bit_start = pos % 8;                                      // 0.0
/*232 */             unit->content = slice;                                                // 0.0
/*234 */         }                                                                         // 0.0
/*236 */         break;                                                                    // 0.0
/*240 */     case HEVC_NAL_AUD:                                                            // 0.0
/*242 */         {                                                                         // 0.0
/*244 */             H265RawAUD *aud;                                                      // 0.0
/*248 */             aud = av_mallocz(sizeof(*aud));                                       // 0.0
/*250 */             if (!aud)                                                             // 0.0
/*252 */                 return AVERROR(ENOMEM);                                           // 0.0
/*254 */             err = cbs_h265_read_aud(ctx, &bc, aud);                               // 0.0
/*256 */             if (err < 0) {                                                        // 0.0
/*258 */                 av_free(aud);                                                     // 0.0
/*260 */                 return err;                                                       // 0.0
/*262 */             }                                                                     // 0.0
/*266 */             unit->content = aud;                                                  // 0.0
/*268 */         }                                                                         // 0.0
/*270 */         break;                                                                    // 0.0
/*274 */     default:                                                                      // 0.0
/*276 */         return AVERROR(ENOSYS);                                                   // 0.0
/*278 */     }                                                                             // 0.0
/*282 */     return 0;                                                                     // 0.0
/*284 */ }                                                                                 // 0.0
