// commit message FFmpeg@50cbe09d8c (target=0, prob=0.6949757, correct=False): smacker: check smacker_decode_tree() return value
/*0   */ static int smacker_decode_header_tree(SmackVContext *smk, GetBitContext *gb, int **recodes, int *last, int size)  // (0) 0.07418
/*2   */ {                                                                                                                 // (29) 0.001955
/*4   */     int res;                                                                                                      // (27) 0.01171
/*6   */     HuffContext huff;                                                                                             // (26) 0.01562
/*8   */     HuffContext tmp1, tmp2;                                                                                       // (16) 0.02147
/*10  */     VLC vlc[2] = { { 0 } };                                                                                       // (13) 0.0313
/*12  */     int escapes[3];                                                                                               // (24) 0.01606
/*14  */     DBCtx ctx;                                                                                                    // (23) 0.01757
/*16  */     int err = 0;                                                                                                  // (25) 0.01562
/*20  */     if(size >= UINT_MAX>>4){ // (((size + 3) >> 2) + 3) << 2 must not overflow                                    // (2) 0.06247
/*22  */         av_log(smk->avctx, AV_LOG_ERROR, "size too large\n");                                                     // (3) 0.05856
/*24  */         return AVERROR_INVALIDDATA;                                                                               // (11) 0.03318
/*26  */     }                                                                                                             // (28) 0.007808
/*30  */     tmp1.length = 256;                                                                                            // (19) 0.01952
/*32  */     tmp1.maxlength = 0;                                                                                           // (17) 0.02147
/*34  */     tmp1.current = 0;                                                                                             // (20) 0.01952
/*36  */     tmp1.bits = av_mallocz(256 * 4);                                                                              // (9) 0.03514
/*38  */     tmp1.lengths = av_mallocz(256 * sizeof(int));                                                                 // (5) 0.04099
/*40  */     tmp1.values = av_mallocz(256 * sizeof(int));                                                                  // (8) 0.03904
/*44  */     tmp2.length = 256;                                                                                            // (21) 0.01952
/*46  */     tmp2.maxlength = 0;                                                                                           // (18) 0.02147
/*48  */     tmp2.current = 0;                                                                                             // (22) 0.01952
/*50  */     tmp2.bits = av_mallocz(256 * 4);                                                                              // (10) 0.03514
/*52  */     tmp2.lengths = av_mallocz(256 * sizeof(int));                                                                 // (6) 0.04099
/*54  */     tmp2.values = av_mallocz(256 * sizeof(int));                                                                  // (7) 0.03904
/*58  */     if(get_bits1(gb)) {                                                                                           // (15) 0.02538
/*60  */         smacker_decode_tree(gb, &tmp1, 0, 0);                                                                     // (4) 0.0488
/*62  */         skip_bits1(gb);                                                                                           // (14) 0.02733
/*64  */         if(tmp1.current > 1) {                                                                                    // (12) 0.03318
/*66  */             res = init_vlc(&vlc[0], SMKTREE_BITS, tmp1.length,                                                    // (1) 0.06832
/*68  */                         tmp1.lengths, sizeof(int), sizeof(int),                                                   // 0.0
/*70  */                         tmp1.bits, sizeof(uint32_t), sizeof(uint32_t), INIT_VLC_LE);                              // 0.0
/*72  */             if(res < 0) {                                                                                         // 0.0
/*74  */                 av_log(smk->avctx, AV_LOG_ERROR, "Cannot build VLC table\n");                                     // 0.0
/*76  */                 return AVERROR_INVALIDDATA;                                                                       // 0.0
/*78  */             }                                                                                                     // 0.0
/*80  */         }                                                                                                         // 0.0
/*82  */     }                                                                                                             // 0.0
/*84  */     if (!vlc[0].table) {                                                                                          // 0.0
/*86  */         av_log(smk->avctx, AV_LOG_ERROR, "Skipping low bytes tree\n");                                            // 0.0
/*88  */     }                                                                                                             // 0.0
/*90  */     if(get_bits1(gb)){                                                                                            // 0.0
/*92  */         smacker_decode_tree(gb, &tmp2, 0, 0);                                                                     // 0.0
/*94  */         skip_bits1(gb);                                                                                           // 0.0
/*96  */         if(tmp2.current > 1) {                                                                                    // 0.0
/*98  */             res = init_vlc(&vlc[1], SMKTREE_BITS, tmp2.length,                                                    // 0.0
/*100 */                         tmp2.lengths, sizeof(int), sizeof(int),                                                   // 0.0
/*102 */                         tmp2.bits, sizeof(uint32_t), sizeof(uint32_t), INIT_VLC_LE);                              // 0.0
/*104 */             if(res < 0) {                                                                                         // 0.0
/*106 */                 av_log(smk->avctx, AV_LOG_ERROR, "Cannot build VLC table\n");                                     // 0.0
/*108 */                 return AVERROR_INVALIDDATA;                                                                       // 0.0
/*110 */             }                                                                                                     // 0.0
/*112 */         }                                                                                                         // 0.0
/*114 */     }                                                                                                             // 0.0
/*116 */     if (!vlc[1].table) {                                                                                          // 0.0
/*118 */         av_log(smk->avctx, AV_LOG_ERROR, "Skipping high bytes tree\n");                                           // 0.0
/*120 */     }                                                                                                             // 0.0
/*124 */     escapes[0]  = get_bits(gb, 16);                                                                               // 0.0
/*126 */     escapes[1]  = get_bits(gb, 16);                                                                               // 0.0
/*128 */     escapes[2]  = get_bits(gb, 16);                                                                               // 0.0
/*132 */     last[0] = last[1] = last[2] = -1;                                                                             // 0.0
/*136 */     ctx.escapes[0] = escapes[0];                                                                                  // 0.0
/*138 */     ctx.escapes[1] = escapes[1];                                                                                  // 0.0
/*140 */     ctx.escapes[2] = escapes[2];                                                                                  // 0.0
/*142 */     ctx.v1 = &vlc[0];                                                                                             // 0.0
/*144 */     ctx.v2 = &vlc[1];                                                                                             // 0.0
/*146 */     ctx.recode1 = tmp1.values;                                                                                    // 0.0
/*148 */     ctx.recode2 = tmp2.values;                                                                                    // 0.0
/*150 */     ctx.last = last;                                                                                              // 0.0
/*154 */     huff.length = ((size + 3) >> 2) + 3;                                                                          // 0.0
/*156 */     huff.maxlength = 0;                                                                                           // 0.0
/*158 */     huff.current = 0;                                                                                             // 0.0
/*160 */     huff.values = av_mallocz(huff.length * sizeof(int));                                                          // 0.0
/*164 */     if (smacker_decode_bigtree(gb, &huff, &ctx) < 0)                                                              // 0.0
/*166 */         err = -1;                                                                                                 // 0.0
/*168 */     skip_bits1(gb);                                                                                               // 0.0
/*170 */     if(ctx.last[0] == -1) ctx.last[0] = huff.current++;                                                           // 0.0
/*172 */     if(ctx.last[1] == -1) ctx.last[1] = huff.current++;                                                           // 0.0
/*174 */     if(ctx.last[2] == -1) ctx.last[2] = huff.current++;                                                           // 0.0
/*176 */     if(huff.current > huff.length){                                                                               // 0.0
/*178 */         ctx.last[0] = ctx.last[1] = ctx.last[2] = 1;                                                              // 0.0
/*180 */         av_log(smk->avctx, AV_LOG_ERROR, "bigtree damaged\n");                                                    // 0.0
/*182 */         return AVERROR_INVALIDDATA;                                                                               // 0.0
/*184 */     }                                                                                                             // 0.0
/*188 */     *recodes = huff.values;                                                                                       // 0.0
/*192 */     if(vlc[0].table)                                                                                              // 0.0
/*194 */         ff_free_vlc(&vlc[0]);                                                                                     // 0.0
/*196 */     if(vlc[1].table)                                                                                              // 0.0
/*198 */         ff_free_vlc(&vlc[1]);                                                                                     // 0.0
/*200 */     av_free(tmp1.bits);                                                                                           // 0.0
/*202 */     av_free(tmp1.lengths);                                                                                        // 0.0
/*204 */     av_free(tmp1.values);                                                                                         // 0.0
/*206 */     av_free(tmp2.bits);                                                                                           // 0.0
/*208 */     av_free(tmp2.lengths);                                                                                        // 0.0
/*210 */     av_free(tmp2.values);                                                                                         // 0.0
/*214 */     return err;                                                                                                   // 0.0
/*216 */ }                                                                                                                 // 0.0
