// commit message FFmpeg@1169f0d0af (target=0, prob=0.022643115, correct=True): x86: more specific checks for availability of required assembly capabilities
/*0  */ void ff_dnxhdenc_init_x86(DNXHDEncContext *ctx)                 // (2) 0.1467
/*2  */ {                                                               // (7) 0.006667
/*4  */ #if HAVE_INLINE_ASM                                             // (5) 0.06
/*6  */     if (av_get_cpu_flags() & AV_CPU_FLAG_SSE2) {                // (1) 0.1667
/*8  */         if (ctx->cid_table->bit_depth == 8)                     // (3) 0.1467
/*10 */             ctx->get_pixels_8x4_sym = get_pixels_8x4_sym_sse2;  // (0) 0.2667
/*12 */     }                                                           // (6) 0.02667
/*14 */ #endif /* HAVE_INLINE_ASM */                                    // (4) 0.07333
/*16 */ }                                                               // (8) 0.006667
