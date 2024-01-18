// commit message FFmpeg@c0bc8b9afb (target=1, prob=0.015556764, correct=False): x86: disable SSE functions using stack when stack is not aligned
/*0   */ LF_FUNC (h,  luma,         sse2)                                                        // (4) 0.04687
/*2   */ LF_IFUNC(h,  luma_intra,   sse2)                                                        // (6) 0.04297
/*4   */ LF_FUNC (v,  luma,         sse2)                                                        // (3) 0.04688
/*6   */ LF_IFUNC(v,  luma_intra,   sse2)                                                        // (5) 0.04297
/*10  */ /***********************************/                                                   // (23) 0.007813
/*12  */ /* weighted prediction */                                                               // (24) 0.007813
/*16  */ #define H264_WEIGHT(W, H, OPT) \                                                        // (20) 0.0293
/*18  */ void ff_h264_weight_ ## W ## x ## H ## _ ## OPT(uint8_t *dst, \                         // (1) 0.05469
/*20  */     int stride, int log2_denom, int weight, int offset);                                // (9) 0.03711
/*24  */ #define H264_BIWEIGHT(W, H, OPT) \                                                      // (17) 0.03125
/*26  */ void ff_h264_biweight_ ## W ## x ## H ## _ ## OPT(uint8_t *dst, \                       // (0) 0.05664
/*28  */     uint8_t *src, int stride, int log2_denom, int weightd, \                            // (2) 0.04883
/*30  */     int weights, int offset);                                                           // (22) 0.01758
/*34  */ #define H264_BIWEIGHT_MMX(W,H) \                                                        // (14) 0.0332
/*36  */ H264_WEIGHT  (W, H, mmx2) \                                                             // (18) 0.03125
/*38  */ H264_BIWEIGHT(W, H, mmx2)                                                               // (19) 0.0293
/*42  */ #define H264_BIWEIGHT_MMX_SSE(W,H) \                                                    // (7) 0.03906
/*44  */ H264_BIWEIGHT_MMX(W, H) \                                                               // (21) 0.0293
/*46  */ H264_WEIGHT      (W, H, sse2) \                                                         // (8) 0.03906
/*48  */ H264_BIWEIGHT    (W, H, sse2) \                                                         // (10) 0.03711
/*50  */ H264_BIWEIGHT    (W, H, ssse3)                                                          // (11) 0.03516
/*54  */ H264_BIWEIGHT_MMX_SSE(16, 16)                                                           // (15) 0.0332
/*56  */ H264_BIWEIGHT_MMX_SSE(16,  8)                                                           // (12) 0.03516
/*58  */ H264_BIWEIGHT_MMX_SSE( 8, 16)                                                           // (16) 0.0332
/*60  */ H264_BIWEIGHT_MMX_SSE( 8,  8)                                                           // (13) 0.03516
/*62  */ H264_BIWEIGHT_MMX_SSE( 8,  4)                                                           // 0.0
/*64  */ H264_BIWEIGHT_MMX    ( 4,  8)                                                           // 0.0
/*66  */ H264_BIWEIGHT_MMX    ( 4,  4)                                                           // 0.0
/*68  */ H264_BIWEIGHT_MMX    ( 4,  2)                                                           // 0.0
/*72  */ void ff_h264dsp_init_x86(H264DSPContext *c)                                             // 0.0
/*74  */ {                                                                                       // 0.0
/*76  */     int mm_flags = av_get_cpu_flags();                                                  // 0.0
/*80  */     if (mm_flags & AV_CPU_FLAG_MMX2) {                                                  // 0.0
/*82  */         c->h264_loop_filter_strength= h264_loop_filter_strength_mmx2;                   // 0.0
/*84  */     }                                                                                   // 0.0
/*86  */ #if HAVE_YASM                                                                           // 0.0
/*88  */     if (mm_flags & AV_CPU_FLAG_MMX) {                                                   // 0.0
/*90  */         c->h264_idct_dc_add=                                                            // 0.0
/*92  */         c->h264_idct_add= ff_h264_idct_add_mmx;                                         // 0.0
/*94  */         c->h264_idct8_dc_add=                                                           // 0.0
/*96  */         c->h264_idct8_add= ff_h264_idct8_add_mmx;                                       // 0.0
/*100 */         c->h264_idct_add16     = ff_h264_idct_add16_mmx;                                // 0.0
/*102 */         c->h264_idct8_add4     = ff_h264_idct8_add4_mmx;                                // 0.0
/*104 */         c->h264_idct_add8      = ff_h264_idct_add8_mmx;                                 // 0.0
/*106 */         c->h264_idct_add16intra= ff_h264_idct_add16intra_mmx;                           // 0.0
/*110 */         if (mm_flags & AV_CPU_FLAG_MMX2) {                                              // 0.0
/*112 */             c->h264_idct_dc_add= ff_h264_idct_dc_add_mmx2;                              // 0.0
/*114 */             c->h264_idct8_dc_add= ff_h264_idct8_dc_add_mmx2;                            // 0.0
/*116 */             c->h264_idct_add16     = ff_h264_idct_add16_mmx2;                           // 0.0
/*118 */             c->h264_idct8_add4     = ff_h264_idct8_add4_mmx2;                           // 0.0
/*120 */             c->h264_idct_add8      = ff_h264_idct_add8_mmx2;                            // 0.0
/*122 */             c->h264_idct_add16intra= ff_h264_idct_add16intra_mmx2;                      // 0.0
/*126 */             c->h264_v_loop_filter_chroma= ff_x264_deblock_v_chroma_mmxext;              // 0.0
/*128 */             c->h264_h_loop_filter_chroma= ff_x264_deblock_h_chroma_mmxext;              // 0.0
/*130 */             c->h264_v_loop_filter_chroma_intra= ff_x264_deblock_v_chroma_intra_mmxext;  // 0.0
/*132 */             c->h264_h_loop_filter_chroma_intra= ff_x264_deblock_h_chroma_intra_mmxext;  // 0.0
/*134 */ #if ARCH_X86_32                                                                         // 0.0
/*136 */             c->h264_v_loop_filter_luma= ff_x264_deblock_v_luma_mmxext;                  // 0.0
/*138 */             c->h264_h_loop_filter_luma= ff_x264_deblock_h_luma_mmxext;                  // 0.0
/*140 */             c->h264_v_loop_filter_luma_intra = ff_x264_deblock_v_luma_intra_mmxext;     // 0.0
/*142 */             c->h264_h_loop_filter_luma_intra = ff_x264_deblock_h_luma_intra_mmxext;     // 0.0
/*145 */             c->weight_h264_pixels_tab[0]= ff_h264_weight_16x16_mmx2;                    // 0.0
/*147 */             c->weight_h264_pixels_tab[1]= ff_h264_weight_16x8_mmx2;                     // 0.0
/*149 */             c->weight_h264_pixels_tab[2]= ff_h264_weight_8x16_mmx2;                     // 0.0
/*151 */             c->weight_h264_pixels_tab[3]= ff_h264_weight_8x8_mmx2;                      // 0.0
/*153 */             c->weight_h264_pixels_tab[4]= ff_h264_weight_8x4_mmx2;                      // 0.0
/*155 */             c->weight_h264_pixels_tab[5]= ff_h264_weight_4x8_mmx2;                      // 0.0
/*157 */             c->weight_h264_pixels_tab[6]= ff_h264_weight_4x4_mmx2;                      // 0.0
/*159 */             c->weight_h264_pixels_tab[7]= ff_h264_weight_4x2_mmx2;                      // 0.0
/*163 */             c->biweight_h264_pixels_tab[0]= ff_h264_biweight_16x16_mmx2;                // 0.0
/*165 */             c->biweight_h264_pixels_tab[1]= ff_h264_biweight_16x8_mmx2;                 // 0.0
/*167 */             c->biweight_h264_pixels_tab[2]= ff_h264_biweight_8x16_mmx2;                 // 0.0
/*169 */             c->biweight_h264_pixels_tab[3]= ff_h264_biweight_8x8_mmx2;                  // 0.0
/*171 */             c->biweight_h264_pixels_tab[4]= ff_h264_biweight_8x4_mmx2;                  // 0.0
/*173 */             c->biweight_h264_pixels_tab[5]= ff_h264_biweight_4x8_mmx2;                  // 0.0
/*175 */             c->biweight_h264_pixels_tab[6]= ff_h264_biweight_4x4_mmx2;                  // 0.0
/*177 */             c->biweight_h264_pixels_tab[7]= ff_h264_biweight_4x2_mmx2;                  // 0.0
/*181 */             if (mm_flags&AV_CPU_FLAG_SSE2) {                                            // 0.0
/*183 */                 c->h264_idct8_add = ff_h264_idct8_add_sse2;                             // 0.0
/*185 */                 c->h264_idct8_add4= ff_h264_idct8_add4_sse2;                            // 0.0
/*189 */                 c->weight_h264_pixels_tab[0]= ff_h264_weight_16x16_sse2;                // 0.0
/*191 */                 c->weight_h264_pixels_tab[1]= ff_h264_weight_16x8_sse2;                 // 0.0
/*193 */                 c->weight_h264_pixels_tab[2]= ff_h264_weight_8x16_sse2;                 // 0.0
/*195 */                 c->weight_h264_pixels_tab[3]= ff_h264_weight_8x8_sse2;                  // 0.0
/*197 */                 c->weight_h264_pixels_tab[4]= ff_h264_weight_8x4_sse2;                  // 0.0
/*201 */                 c->biweight_h264_pixels_tab[0]= ff_h264_biweight_16x16_sse2;            // 0.0
/*203 */                 c->biweight_h264_pixels_tab[1]= ff_h264_biweight_16x8_sse2;             // 0.0
/*205 */                 c->biweight_h264_pixels_tab[2]= ff_h264_biweight_8x16_sse2;             // 0.0
/*207 */                 c->biweight_h264_pixels_tab[3]= ff_h264_biweight_8x8_sse2;              // 0.0
/*209 */                 c->biweight_h264_pixels_tab[4]= ff_h264_biweight_8x4_sse2;              // 0.0
/*214 */                 c->h264_v_loop_filter_luma = ff_x264_deblock_v_luma_sse2;               // 0.0
/*216 */                 c->h264_h_loop_filter_luma = ff_x264_deblock_h_luma_sse2;               // 0.0
/*218 */                 c->h264_v_loop_filter_luma_intra = ff_x264_deblock_v_luma_intra_sse2;   // 0.0
/*220 */                 c->h264_h_loop_filter_luma_intra = ff_x264_deblock_h_luma_intra_sse2;   // 0.0
/*225 */                 c->h264_idct_add16 = ff_h264_idct_add16_sse2;                           // 0.0
/*227 */                 c->h264_idct_add8  = ff_h264_idct_add8_sse2;                            // 0.0
/*229 */                 c->h264_idct_add16intra = ff_h264_idct_add16intra_sse2;                 // 0.0
/*231 */             }                                                                           // 0.0
/*233 */             if (mm_flags&AV_CPU_FLAG_SSSE3) {                                           // 0.0
/*235 */                 c->biweight_h264_pixels_tab[0]= ff_h264_biweight_16x16_ssse3;           // 0.0
/*237 */                 c->biweight_h264_pixels_tab[1]= ff_h264_biweight_16x8_ssse3;            // 0.0
/*239 */                 c->biweight_h264_pixels_tab[2]= ff_h264_biweight_8x16_ssse3;            // 0.0
/*241 */                 c->biweight_h264_pixels_tab[3]= ff_h264_biweight_8x8_ssse3;             // 0.0
/*243 */                 c->biweight_h264_pixels_tab[4]= ff_h264_biweight_8x4_ssse3;             // 0.0
/*245 */             }                                                                           // 0.0
/*247 */         }                                                                               // 0.0
/*249 */     }                                                                                   // 0.0
/*252 */ }                                                                                       // 0.0
