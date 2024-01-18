// commit message FFmpeg@2f6ec9fdd7 (target=1, prob=0.655954, correct=True): diracdec: Test mctmp and mcscratch for malloc failure.
/*0  */ static int alloc_sequence_buffers(DiracContext *s)                                                  // (15) 0.0293
/*2  */ {                                                                                                   // (18) 0.001955
/*4  */     int sbwidth  = DIVRNDUP(s->source.width,  4);                                                   // (10) 0.04687
/*6  */     int sbheight = DIVRNDUP(s->source.height, 4);                                                   // (11) 0.04297
/*8  */     int i, w, h, top_padding;                                                                       // (16) 0.02734
/*12 */     /* todo: think more about this / use or set Plane here */                                       // (13) 0.03516
/*14 */     for (i = 0; i < 3; i++) {                                                                       // (14) 0.03125
/*16 */         int max_xblen = MAX_BLOCKSIZE >> (i ? s->chroma_x_shift : 0);                               // (2) 0.06641
/*18 */         int max_yblen = MAX_BLOCKSIZE >> (i ? s->chroma_y_shift : 0);                               // (3) 0.06641
/*20 */         w = s->source.width  >> (i ? s->chroma_x_shift : 0);                                        // (6) 0.05859
/*22 */         h = s->source.height >> (i ? s->chroma_y_shift : 0);                                        // (7) 0.05664
/*26 */         /* we allocate the max we support here since num decompositions can                         // (12) 0.04102
/*28 */          * change from frame to frame. Stride is aligned to 16 for SIMD, and                        // (9) 0.05078
/*30 */          * 1<<MAX_DWT_LEVELS top padding to avoid if(y>0) in arith decoding                         // (5) 0.06445
/*32 */          * MAX_BLOCKSIZE padding for MC: blocks can spill up to half of that                        // (8) 0.05078
/*34 */          * on each side */                                                                          // (17) 0.02539
/*36 */         top_padding = FFMAX(1<<MAX_DWT_LEVELS, max_yblen/2);                                        // (4) 0.06445
/*38 */         w = FFALIGN(CALC_PADDING(w, MAX_DWT_LEVELS), 8); /* FIXME: Should this be 16 for SSE??? */  // (0) 0.0918
/*40 */         h = top_padding + CALC_PADDING(h, MAX_DWT_LEVELS) + max_yblen/2;                            // (1) 0.07812
/*44 */         s->plane[i].idwt_buf_base = av_mallocz((w+max_xblen)*h * sizeof(IDWTELEM));                 // 0.0
/*46 */         s->plane[i].idwt_tmp      = av_malloc((w+16) * sizeof(IDWTELEM));                           // 0.0
/*48 */         s->plane[i].idwt_buf      = s->plane[i].idwt_buf_base + top_padding*w;                      // 0.0
/*50 */         if (!s->plane[i].idwt_buf_base || !s->plane[i].idwt_tmp)                                    // 0.0
/*52 */             return AVERROR(ENOMEM);                                                                 // 0.0
/*54 */     }                                                                                               // 0.0
/*58 */     w = s->source.width;                                                                            // 0.0
/*60 */     h = s->source.height;                                                                           // 0.0
/*64 */     /* fixme: allocate using real stride here */                                                    // 0.0
/*66 */     s->sbsplit  = av_malloc(sbwidth * sbheight);                                                    // 0.0
/*68 */     s->blmotion = av_malloc(sbwidth * sbheight * 16 * sizeof(*s->blmotion));                        // 0.0
/*70 */     s->edge_emu_buffer_base = av_malloc((w+64)*MAX_BLOCKSIZE);                                      // 0.0
/*74 */     s->mctmp     = av_malloc((w+64+MAX_BLOCKSIZE) * (h*MAX_BLOCKSIZE) * sizeof(*s->mctmp));         // 0.0
/*76 */     s->mcscratch = av_malloc((w+64)*MAX_BLOCKSIZE);                                                 // 0.0
/*80 */     if (!s->sbsplit || !s->blmotion)                                                                // 0.0
/*82 */         return AVERROR(ENOMEM);                                                                     // 0.0
/*84 */     return 0;                                                                                       // 0.0
/*86 */ }                                                                                                   // 0.0
