// commit message FFmpeg@ac4b32df71 (target=1, prob=0.023522517, correct=False): On2 VP7 decoder
/*0   */ DECLARE_LOOP_FILTER(mmxext)                                                                    // (12) 0.02889
/*2   */ DECLARE_LOOP_FILTER(sse2)                                                                      // (11) 0.03084
/*4   */ DECLARE_LOOP_FILTER(ssse3)                                                                     // (7) 0.045
/*6   */ DECLARE_LOOP_FILTER(sse4)                                                                      // (10) 0.03212
/*10  */ #endif /* HAVE_YASM */                                                                         // (13) 0.02792
/*14  */ #define VP8_LUMA_MC_FUNC(IDX, SIZE, OPT) \                                                     // (8) 0.04162
/*16  */     c->put_vp8_epel_pixels_tab[IDX][0][2] = ff_put_vp8_epel ## SIZE ## _h6_ ## OPT; \          // (3) 0.08558
/*18  */     c->put_vp8_epel_pixels_tab[IDX][2][0] = ff_put_vp8_epel ## SIZE ## _v6_ ## OPT; \          // (2) 0.08559
/*20  */     c->put_vp8_epel_pixels_tab[IDX][2][2] = ff_put_vp8_epel ## SIZE ## _h6v6_ ## OPT           // (5) 0.08548
/*24  */ #define VP8_MC_FUNC(IDX, SIZE, OPT) \                                                          // (9) 0.03525
/*26  */     c->put_vp8_epel_pixels_tab[IDX][0][1] = ff_put_vp8_epel ## SIZE ## _h4_ ## OPT; \          // (4) 0.08552
/*28  */     c->put_vp8_epel_pixels_tab[IDX][1][0] = ff_put_vp8_epel ## SIZE ## _v4_ ## OPT; \          // (6) 0.08547
/*30  */     c->put_vp8_epel_pixels_tab[IDX][1][1] = ff_put_vp8_epel ## SIZE ## _h4v4_ ## OPT; \        // (1) 0.08915
/*32  */     c->put_vp8_epel_pixels_tab[IDX][1][2] = ff_put_vp8_epel ## SIZE ## _h6v4_ ## OPT; \        // (0) 0.08923
/*34  */     c->put_vp8_epel_pixels_tab[IDX][2][1] = ff_put_vp8_epel ## SIZE ## _h4v6_ ## OPT; \        // 0.0
/*36  */     VP8_LUMA_MC_FUNC(IDX, SIZE, OPT)                                                           // 0.0
/*40  */ #define VP8_BILINEAR_MC_FUNC(IDX, SIZE, OPT) \                                                 // 0.0
/*42  */     c->put_vp8_bilinear_pixels_tab[IDX][0][1] = ff_put_vp8_bilinear ## SIZE ## _h_ ## OPT; \   // 0.0
/*44  */     c->put_vp8_bilinear_pixels_tab[IDX][0][2] = ff_put_vp8_bilinear ## SIZE ## _h_ ## OPT; \   // 0.0
/*46  */     c->put_vp8_bilinear_pixels_tab[IDX][1][0] = ff_put_vp8_bilinear ## SIZE ## _v_ ## OPT; \   // 0.0
/*48  */     c->put_vp8_bilinear_pixels_tab[IDX][1][1] = ff_put_vp8_bilinear ## SIZE ## _hv_ ## OPT; \  // 0.0
/*50  */     c->put_vp8_bilinear_pixels_tab[IDX][1][2] = ff_put_vp8_bilinear ## SIZE ## _hv_ ## OPT; \  // 0.0
/*52  */     c->put_vp8_bilinear_pixels_tab[IDX][2][0] = ff_put_vp8_bilinear ## SIZE ## _v_ ## OPT; \   // 0.0
/*54  */     c->put_vp8_bilinear_pixels_tab[IDX][2][1] = ff_put_vp8_bilinear ## SIZE ## _hv_ ## OPT; \  // 0.0
/*56  */     c->put_vp8_bilinear_pixels_tab[IDX][2][2] = ff_put_vp8_bilinear ## SIZE ## _hv_ ## OPT     // 0.0
/*62  */ av_cold void ff_vp8dsp_init_x86(VP8DSPContext* c)                                              // 0.0
/*64  */ {                                                                                              // 0.0
/*66  */ #if HAVE_YASM                                                                                  // 0.0
/*68  */     int cpu_flags = av_get_cpu_flags();                                                        // 0.0
/*72  */     if (EXTERNAL_MMX(cpu_flags)) {                                                             // 0.0
/*74  */         c->vp8_idct_dc_add    = ff_vp8_idct_dc_add_mmx;                                        // 0.0
/*76  */         c->vp8_idct_dc_add4uv = ff_vp8_idct_dc_add4uv_mmx;                                     // 0.0
/*78  */ #if ARCH_X86_32                                                                                // 0.0
/*80  */         c->vp8_idct_dc_add4y  = ff_vp8_idct_dc_add4y_mmx;                                      // 0.0
/*82  */         c->vp8_idct_add       = ff_vp8_idct_add_mmx;                                           // 0.0
/*84  */         c->vp8_luma_dc_wht    = ff_vp8_luma_dc_wht_mmx;                                        // 0.0
/*86  */         c->put_vp8_epel_pixels_tab[0][0][0]     =                                              // 0.0
/*88  */         c->put_vp8_bilinear_pixels_tab[0][0][0] = ff_put_vp8_pixels16_mmx;                     // 0.0
/*90  */ #endif                                                                                         // 0.0
/*92  */         c->put_vp8_epel_pixels_tab[1][0][0]     =                                              // 0.0
/*94  */         c->put_vp8_bilinear_pixels_tab[1][0][0] = ff_put_vp8_pixels8_mmx;                      // 0.0
/*98  */ #if ARCH_X86_32                                                                                // 0.0
/*100 */         c->vp8_v_loop_filter_simple = ff_vp8_v_loop_filter_simple_mmx;                         // 0.0
/*102 */         c->vp8_h_loop_filter_simple = ff_vp8_h_loop_filter_simple_mmx;                         // 0.0
/*106 */         c->vp8_v_loop_filter16y_inner = ff_vp8_v_loop_filter16y_inner_mmx;                     // 0.0
/*108 */         c->vp8_h_loop_filter16y_inner = ff_vp8_h_loop_filter16y_inner_mmx;                     // 0.0
/*110 */         c->vp8_v_loop_filter8uv_inner = ff_vp8_v_loop_filter8uv_inner_mmx;                     // 0.0
/*112 */         c->vp8_h_loop_filter8uv_inner = ff_vp8_h_loop_filter8uv_inner_mmx;                     // 0.0
/*116 */         c->vp8_v_loop_filter16y       = ff_vp8_v_loop_filter16y_mbedge_mmx;                    // 0.0
/*118 */         c->vp8_h_loop_filter16y       = ff_vp8_h_loop_filter16y_mbedge_mmx;                    // 0.0
/*120 */         c->vp8_v_loop_filter8uv       = ff_vp8_v_loop_filter8uv_mbedge_mmx;                    // 0.0
/*122 */         c->vp8_h_loop_filter8uv       = ff_vp8_h_loop_filter8uv_mbedge_mmx;                    // 0.0
/*124 */ #endif                                                                                         // 0.0
/*126 */     }                                                                                          // 0.0
/*130 */     /* note that 4-tap width=16 functions are missing because w=16                             // 0.0
/*132 */      * is only used for luma, and luma is always a copy or sixtap. */                          // 0.0
/*134 */     if (EXTERNAL_MMXEXT(cpu_flags)) {                                                          // 0.0
/*136 */         VP8_MC_FUNC(2, 4, mmxext);                                                             // 0.0
/*138 */         VP8_BILINEAR_MC_FUNC(2, 4, mmxext);                                                    // 0.0
/*140 */ #if ARCH_X86_32                                                                                // 0.0
/*142 */         VP8_LUMA_MC_FUNC(0, 16, mmxext);                                                       // 0.0
/*144 */         VP8_MC_FUNC(1, 8, mmxext);                                                             // 0.0
/*146 */         VP8_BILINEAR_MC_FUNC(0, 16, mmxext);                                                   // 0.0
/*148 */         VP8_BILINEAR_MC_FUNC(1,  8, mmxext);                                                   // 0.0
/*152 */         c->vp8_v_loop_filter_simple   = ff_vp8_v_loop_filter_simple_mmxext;                    // 0.0
/*154 */         c->vp8_h_loop_filter_simple   = ff_vp8_h_loop_filter_simple_mmxext;                    // 0.0
/*158 */         c->vp8_v_loop_filter16y_inner = ff_vp8_v_loop_filter16y_inner_mmxext;                  // 0.0
/*160 */         c->vp8_h_loop_filter16y_inner = ff_vp8_h_loop_filter16y_inner_mmxext;                  // 0.0
/*162 */         c->vp8_v_loop_filter8uv_inner = ff_vp8_v_loop_filter8uv_inner_mmxext;                  // 0.0
/*164 */         c->vp8_h_loop_filter8uv_inner = ff_vp8_h_loop_filter8uv_inner_mmxext;                  // 0.0
/*168 */         c->vp8_v_loop_filter16y       = ff_vp8_v_loop_filter16y_mbedge_mmxext;                 // 0.0
/*170 */         c->vp8_h_loop_filter16y       = ff_vp8_h_loop_filter16y_mbedge_mmxext;                 // 0.0
/*172 */         c->vp8_v_loop_filter8uv       = ff_vp8_v_loop_filter8uv_mbedge_mmxext;                 // 0.0
/*174 */         c->vp8_h_loop_filter8uv       = ff_vp8_h_loop_filter8uv_mbedge_mmxext;                 // 0.0
/*176 */ #endif                                                                                         // 0.0
/*178 */     }                                                                                          // 0.0
/*182 */     if (EXTERNAL_SSE(cpu_flags)) {                                                             // 0.0
/*184 */         c->vp8_idct_add                         = ff_vp8_idct_add_sse;                         // 0.0
/*186 */         c->vp8_luma_dc_wht                      = ff_vp8_luma_dc_wht_sse;                      // 0.0
/*188 */         c->put_vp8_epel_pixels_tab[0][0][0]     =                                              // 0.0
/*190 */         c->put_vp8_bilinear_pixels_tab[0][0][0] = ff_put_vp8_pixels16_sse;                     // 0.0
/*192 */     }                                                                                          // 0.0
/*196 */     if (EXTERNAL_SSE2(cpu_flags) && (cpu_flags & AV_CPU_FLAG_SSE2SLOW)) {                      // 0.0
/*198 */         VP8_LUMA_MC_FUNC(0, 16, sse2);                                                         // 0.0
/*200 */         VP8_MC_FUNC(1, 8, sse2);                                                               // 0.0
/*202 */         VP8_BILINEAR_MC_FUNC(0, 16, sse2);                                                     // 0.0
/*204 */         VP8_BILINEAR_MC_FUNC(1, 8, sse2);                                                      // 0.0
/*208 */         c->vp8_v_loop_filter_simple = ff_vp8_v_loop_filter_simple_sse2;                        // 0.0
/*212 */         c->vp8_v_loop_filter16y_inner = ff_vp8_v_loop_filter16y_inner_sse2;                    // 0.0
/*214 */         c->vp8_v_loop_filter8uv_inner = ff_vp8_v_loop_filter8uv_inner_sse2;                    // 0.0
/*218 */         c->vp8_v_loop_filter16y       = ff_vp8_v_loop_filter16y_mbedge_sse2;                   // 0.0
/*220 */         c->vp8_v_loop_filter8uv       = ff_vp8_v_loop_filter8uv_mbedge_sse2;                   // 0.0
/*222 */     }                                                                                          // 0.0
/*226 */     if (EXTERNAL_SSE2(cpu_flags)) {                                                            // 0.0
/*228 */         c->vp8_idct_dc_add4y          = ff_vp8_idct_dc_add4y_sse2;                             // 0.0
/*232 */         c->vp8_h_loop_filter_simple = ff_vp8_h_loop_filter_simple_sse2;                        // 0.0
/*236 */         c->vp8_h_loop_filter16y_inner = ff_vp8_h_loop_filter16y_inner_sse2;                    // 0.0
/*238 */         c->vp8_h_loop_filter8uv_inner = ff_vp8_h_loop_filter8uv_inner_sse2;                    // 0.0
/*242 */         c->vp8_h_loop_filter16y       = ff_vp8_h_loop_filter16y_mbedge_sse2;                   // 0.0
/*244 */         c->vp8_h_loop_filter8uv       = ff_vp8_h_loop_filter8uv_mbedge_sse2;                   // 0.0
/*246 */     }                                                                                          // 0.0
/*250 */     if (EXTERNAL_SSSE3(cpu_flags)) {                                                           // 0.0
/*252 */         VP8_LUMA_MC_FUNC(0, 16, ssse3);                                                        // 0.0
/*254 */         VP8_MC_FUNC(1, 8, ssse3);                                                              // 0.0
/*256 */         VP8_MC_FUNC(2, 4, ssse3);                                                              // 0.0
/*258 */         VP8_BILINEAR_MC_FUNC(0, 16, ssse3);                                                    // 0.0
/*260 */         VP8_BILINEAR_MC_FUNC(1, 8, ssse3);                                                     // 0.0
/*262 */         VP8_BILINEAR_MC_FUNC(2, 4, ssse3);                                                     // 0.0
/*266 */         c->vp8_v_loop_filter_simple = ff_vp8_v_loop_filter_simple_ssse3;                       // 0.0
/*268 */         c->vp8_h_loop_filter_simple = ff_vp8_h_loop_filter_simple_ssse3;                       // 0.0
/*272 */         c->vp8_v_loop_filter16y_inner = ff_vp8_v_loop_filter16y_inner_ssse3;                   // 0.0
/*274 */         c->vp8_h_loop_filter16y_inner = ff_vp8_h_loop_filter16y_inner_ssse3;                   // 0.0
/*276 */         c->vp8_v_loop_filter8uv_inner = ff_vp8_v_loop_filter8uv_inner_ssse3;                   // 0.0
/*278 */         c->vp8_h_loop_filter8uv_inner = ff_vp8_h_loop_filter8uv_inner_ssse3;                   // 0.0
/*282 */         c->vp8_v_loop_filter16y       = ff_vp8_v_loop_filter16y_mbedge_ssse3;                  // 0.0
/*284 */         c->vp8_h_loop_filter16y       = ff_vp8_h_loop_filter16y_mbedge_ssse3;                  // 0.0
/*286 */         c->vp8_v_loop_filter8uv       = ff_vp8_v_loop_filter8uv_mbedge_ssse3;                  // 0.0
/*288 */         c->vp8_h_loop_filter8uv       = ff_vp8_h_loop_filter8uv_mbedge_ssse3;                  // 0.0
/*290 */     }                                                                                          // 0.0
/*294 */     if (EXTERNAL_SSE4(cpu_flags)) {                                                            // 0.0
/*296 */         c->vp8_idct_dc_add                  = ff_vp8_idct_dc_add_sse4;                         // 0.0
/*300 */         c->vp8_h_loop_filter_simple   = ff_vp8_h_loop_filter_simple_sse4;                      // 0.0
/*302 */         c->vp8_h_loop_filter16y       = ff_vp8_h_loop_filter16y_mbedge_sse4;                   // 0.0
/*304 */         c->vp8_h_loop_filter8uv       = ff_vp8_h_loop_filter8uv_mbedge_sse4;                   // 0.0
/*306 */     }                                                                                          // 0.0
/*308 */ #endif /* HAVE_YASM */                                                                         // 0.0
/*310 */ }                                                                                              // 0.0
