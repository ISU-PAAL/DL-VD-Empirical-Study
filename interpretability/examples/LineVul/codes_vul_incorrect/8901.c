// commit message FFmpeg@4f00519d95 (target=1, prob=0.27252895, correct=False): Fix VC-1 width/height handling.
/*0   */ int vc1_decode_sequence_header(AVCodecContext *avctx, VC1Context *v, GetBitContext *gb)  // (2) 0.0625
/*2   */ {                                                                                        // (26) 0.001953
/*4   */     av_log(avctx, AV_LOG_DEBUG, "Header: %0X\n", show_bits(gb, 32));                     // (0) 0.06445
/*6   */     v->profile = get_bits(gb, 2);                                                        // (15) 0.0293
/*8   */     if (v->profile == PROFILE_COMPLEX)                                                   // (16) 0.0293
/*10  */     {                                                                                    // (20) 0.007812
/*12  */         av_log(avctx, AV_LOG_WARNING, "WMV3 Complex Profile is not fully supported\n");  // (1) 0.06445
/*14  */     }                                                                                    // (21) 0.007812
/*18  */     if (v->profile == PROFILE_ADVANCED)                                                  // (12) 0.0332
/*20  */     {                                                                                    // (22) 0.007812
/*22  */         v->zz_8x4 = ff_vc1_adv_progressive_8x4_zz;                                       // (3) 0.06055
/*24  */         v->zz_4x8 = ff_vc1_adv_progressive_4x8_zz;                                       // (4) 0.06055
/*26  */         return decode_sequence_header_adv(v, gb);                                        // (10) 0.04102
/*28  */     }                                                                                    // (23) 0.007812
/*30  */     else                                                                                 // (24) 0.007812
/*32  */     {                                                                                    // (25) 0.007812
/*34  */         v->zz_8x4 = wmv2_scantableA;                                                     // (6) 0.04883
/*36  */         v->zz_4x8 = wmv2_scantableB;                                                     // (7) 0.04883
/*38  */         v->res_y411   = get_bits1(gb);                                                   // (9) 0.04492
/*40  */         v->res_sprite = get_bits1(gb);                                                   // (11) 0.04102
/*42  */         if (v->res_y411)                                                                 // (14) 0.03125
/*44  */         {                                                                                // (18) 0.01562
/*46  */             av_log(avctx, AV_LOG_ERROR,                                                  // (8) 0.04688
/*48  */                    "Old interlaced mode is not supported\n");                            // (5) 0.05859
/*50  */             return -1;                                                                   // (17) 0.0293
/*52  */         }                                                                                // (19) 0.01562
/*54  */         if (v->res_sprite) {                                                             // (13) 0.0332
/*56  */             av_log(avctx, AV_LOG_ERROR, "WMVP is not fully supported\n");                // 0.0
/*58  */         }                                                                                // 0.0
/*60  */     }                                                                                    // 0.0
/*64  */     // (fps-2)/4 (->30)                                                                  // 0.0
/*66  */     v->frmrtq_postproc = get_bits(gb, 3); //common                                       // 0.0
/*68  */     // (bitrate-32kbps)/64kbps                                                           // 0.0
/*70  */     v->bitrtq_postproc = get_bits(gb, 5); //common                                       // 0.0
/*72  */     v->s.loop_filter = get_bits1(gb); //common                                           // 0.0
/*74  */     if(v->s.loop_filter == 1 && v->profile == PROFILE_SIMPLE)                            // 0.0
/*76  */     {                                                                                    // 0.0
/*78  */         av_log(avctx, AV_LOG_ERROR,                                                      // 0.0
/*80  */                "LOOPFILTER shall not be enabled in Simple Profile\n");                   // 0.0
/*82  */     }                                                                                    // 0.0
/*84  */     if(v->s.avctx->skip_loop_filter >= AVDISCARD_ALL)                                    // 0.0
/*86  */         v->s.loop_filter = 0;                                                            // 0.0
/*90  */     v->res_x8 = get_bits1(gb); //reserved                                                // 0.0
/*92  */     v->multires = get_bits1(gb);                                                         // 0.0
/*94  */     v->res_fasttx = get_bits1(gb);                                                       // 0.0
/*96  */     if (!v->res_fasttx)                                                                  // 0.0
/*98  */     {                                                                                    // 0.0
/*100 */         v->vc1dsp.vc1_inv_trans_8x8 = ff_simple_idct_8;                                  // 0.0
/*102 */         v->vc1dsp.vc1_inv_trans_8x4 = ff_simple_idct84_add;                              // 0.0
/*104 */         v->vc1dsp.vc1_inv_trans_4x8 = ff_simple_idct48_add;                              // 0.0
/*106 */         v->vc1dsp.vc1_inv_trans_4x4 = ff_simple_idct44_add;                              // 0.0
/*108 */         v->vc1dsp.vc1_inv_trans_8x8_dc = ff_simple_idct_add_8;                           // 0.0
/*110 */         v->vc1dsp.vc1_inv_trans_8x4_dc = ff_simple_idct84_add;                           // 0.0
/*112 */         v->vc1dsp.vc1_inv_trans_4x8_dc = ff_simple_idct48_add;                           // 0.0
/*114 */         v->vc1dsp.vc1_inv_trans_4x4_dc = ff_simple_idct44_add;                           // 0.0
/*116 */     }                                                                                    // 0.0
/*120 */     v->fastuvmc =  get_bits1(gb); //common                                               // 0.0
/*122 */     if (!v->profile && !v->fastuvmc)                                                     // 0.0
/*124 */     {                                                                                    // 0.0
/*126 */         av_log(avctx, AV_LOG_ERROR,                                                      // 0.0
/*128 */                "FASTUVMC unavailable in Simple Profile\n");                              // 0.0
/*130 */         return -1;                                                                       // 0.0
/*132 */     }                                                                                    // 0.0
/*134 */     v->extended_mv =  get_bits1(gb); //common                                            // 0.0
/*136 */     if (!v->profile && v->extended_mv)                                                   // 0.0
/*138 */     {                                                                                    // 0.0
/*140 */         av_log(avctx, AV_LOG_ERROR,                                                      // 0.0
/*142 */                "Extended MVs unavailable in Simple Profile\n");                          // 0.0
/*144 */         return -1;                                                                       // 0.0
/*146 */     }                                                                                    // 0.0
/*148 */     v->dquant =  get_bits(gb, 2); //common                                               // 0.0
/*150 */     v->vstransform =  get_bits1(gb); //common                                            // 0.0
/*154 */     v->res_transtab = get_bits1(gb);                                                     // 0.0
/*156 */     if (v->res_transtab)                                                                 // 0.0
/*158 */     {                                                                                    // 0.0
/*160 */         av_log(avctx, AV_LOG_ERROR,                                                      // 0.0
/*162 */                "1 for reserved RES_TRANSTAB is forbidden\n");                            // 0.0
/*164 */         return -1;                                                                       // 0.0
/*166 */     }                                                                                    // 0.0
/*170 */     v->overlap = get_bits1(gb); //common                                                 // 0.0
/*174 */     v->s.resync_marker = get_bits1(gb);                                                  // 0.0
/*176 */     v->rangered = get_bits1(gb);                                                         // 0.0
/*178 */     if (v->rangered && v->profile == PROFILE_SIMPLE)                                     // 0.0
/*180 */     {                                                                                    // 0.0
/*182 */         av_log(avctx, AV_LOG_INFO,                                                       // 0.0
/*184 */                "RANGERED should be set to 0 in Simple Profile\n");                       // 0.0
/*186 */     }                                                                                    // 0.0
/*190 */     v->s.max_b_frames = avctx->max_b_frames = get_bits(gb, 3); //common                  // 0.0
/*192 */     v->quantizer_mode = get_bits(gb, 2); //common                                        // 0.0
/*196 */     v->finterpflag = get_bits1(gb); //common                                             // 0.0
/*200 */     if (v->res_sprite) {                                                                 // 0.0
/*202 */         v->s.avctx->width  = v->s.avctx->coded_width  = get_bits(gb, 11);                // 0.0
/*204 */         v->s.avctx->height = v->s.avctx->coded_height = get_bits(gb, 11);                // 0.0
/*206 */         skip_bits(gb, 5); //frame rate                                                   // 0.0
/*208 */         v->res_x8 = get_bits1(gb);                                                       // 0.0
/*210 */         if (get_bits1(gb)) { // something to do with DC VLC selection                    // 0.0
/*212 */             av_log(avctx, AV_LOG_ERROR, "Unsupported sprite feature\n");                 // 0.0
/*214 */             return -1;                                                                   // 0.0
/*216 */         }                                                                                // 0.0
/*218 */         skip_bits(gb, 3); //slice code                                                   // 0.0
/*220 */         v->res_rtm_flag = 0;                                                             // 0.0
/*222 */     } else {                                                                             // 0.0
/*224 */         v->res_rtm_flag = get_bits1(gb); //reserved                                      // 0.0
/*226 */     }                                                                                    // 0.0
/*228 */     if (!v->res_rtm_flag)                                                                // 0.0
/*230 */     {                                                                                    // 0.0
/*232 */ //            av_log(avctx, AV_LOG_ERROR,                                                // 0.0
/*234 */ //                   "0 for reserved RES_RTM_FLAG is forbidden\n");                      // 0.0
/*236 */         av_log(avctx, AV_LOG_ERROR,                                                      // 0.0
/*238 */                "Old WMV3 version detected, some frames may be decoded incorrectly\n");   // 0.0
/*240 */         //return -1;                                                                     // 0.0
/*242 */     }                                                                                    // 0.0
/*244 */     //TODO: figure out what they mean (always 0x402F)                                    // 0.0
/*246 */     if(!v->res_fasttx) skip_bits(gb, 16);                                                // 0.0
/*248 */     av_log(avctx, AV_LOG_DEBUG,                                                          // 0.0
/*250 */                "Profile %i:\nfrmrtq_postproc=%i, bitrtq_postproc=%i\n"                   // 0.0
/*252 */                "LoopFilter=%i, MultiRes=%i, FastUVMC=%i, Extended MV=%i\n"               // 0.0
/*254 */                "Rangered=%i, VSTransform=%i, Overlap=%i, SyncMarker=%i\n"                // 0.0
/*256 */                "DQuant=%i, Quantizer mode=%i, Max B frames=%i\n",                        // 0.0
/*258 */                v->profile, v->frmrtq_postproc, v->bitrtq_postproc,                       // 0.0
/*260 */                v->s.loop_filter, v->multires, v->fastuvmc, v->extended_mv,               // 0.0
/*262 */                v->rangered, v->vstransform, v->overlap, v->s.resync_marker,              // 0.0
/*264 */                v->dquant, v->quantizer_mode, avctx->max_b_frames                         // 0.0
/*266 */                );                                                                        // 0.0
/*268 */     return 0;                                                                            // 0.0
/*270 */ }                                                                                        // 0.0
