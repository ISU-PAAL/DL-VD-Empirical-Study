// commit message FFmpeg@544286b3d3 (target=1, prob=0.29403445, correct=False): Moved some H.263+ variables to MpegEncContext to be thread-safe. Increase video_buffer on ffmpeg to avoid buffer overrun on big pictures.
/*0   */ int h263_decode_picture_header(MpegEncContext *s)                                            // (8) 0.03516
/*2   */ {                                                                                            // (28) 0.001953
/*4   */     int format, width, height;                                                               // (24) 0.01953
/*8   */     /* picture header */                                                                     // (26) 0.01367
/*10  */     if (get_bits(&s->gb, 22) != 0x20)                                                        // (6) 0.03906
/*12  */         return -1;                                                                           // (22) 0.02148
/*14  */     skip_bits(&s->gb, 8); /* picture timestamp */                                            // (13) 0.0332
/*18  */     if (get_bits1(&s->gb) != 1)                                                              // (15) 0.0332
/*20  */         return -1;	/* marker */                                                              // (18) 0.0293
/*22  */     if (get_bits1(&s->gb) != 0)                                                              // (16) 0.0332
/*24  */         return -1;	/* h263 id */                                                             // (14) 0.0332
/*26  */     skip_bits1(&s->gb);	/* split screen off */                                               // (12) 0.03516
/*28  */     skip_bits1(&s->gb);	/* camera  off */                                                    // (11) 0.03516
/*30  */     skip_bits1(&s->gb);	/* freeze picture release off */                                     // (7) 0.03711
/*34  */     format = get_bits(&s->gb, 3);                                                            // (19) 0.0293
/*38  */     if (format != 7) {                                                                       // (25) 0.01953
/*40  */         s->h263_plus = 0;                                                                    // (17) 0.03125
/*42  */         /* H.263v1 */                                                                        // (21) 0.02734
/*44  */         width = h263_format[format][0];                                                      // (9) 0.03516
/*46  */         height = h263_format[format][1];                                                     // (10) 0.03516
/*48  */         if (!width)                                                                          // (23) 0.02148
/*50  */             return -1;                                                                       // (20) 0.0293
/*54  */         s->pict_type = I_TYPE + get_bits1(&s->gb);                                           // (0) 0.05078
/*58  */         s->unrestricted_mv = get_bits1(&s->gb);                                              // (2) 0.04883
/*60  */         s->h263_long_vectors = s->unrestricted_mv;                                           // (1) 0.04883
/*64  */         if (get_bits1(&s->gb) != 0)                                                          // (4) 0.04102
/*66  */             return -1;	/* SAC: off */                                                        // (3) 0.04297
/*68  */         if (get_bits1(&s->gb) != 0)                                                          // (5) 0.04102
/*70  */             return -1;	/* advanced prediction mode: off */                                   // 0.0
/*72  */         if (get_bits1(&s->gb) != 0)                                                          // 0.0
/*74  */             return -1;	/* not PB frame */                                                    // 0.0
/*78  */         s->qscale = get_bits(&s->gb, 5);                                                     // 0.0
/*80  */         skip_bits1(&s->gb);	/* Continuous Presence Multipoint mode: off */                   // 0.0
/*82  */     } else {                                                                                 // 0.0
/*84  */         s->h263_plus = 1;                                                                    // 0.0
/*86  */         /* H.263v2 */                                                                        // 0.0
/*88  */         /* OPPTYPE */                                                                        // 0.0
/*90  */                                                                                              // (27) 0.009766
/*92  */         if (get_bits(&s->gb, 3) != 1) /* Update Full Extended PTYPE */                       // 0.0
/*94  */             return -1;                                                                       // 0.0
/*96  */         format = get_bits(&s->gb, 3);                                                        // 0.0
/*98  */                                                                                              // 0.0
/*100 */         skip_bits(&s->gb,1); /* Custom PCF */                                                // 0.0
/*102 */         umvplus_dec = get_bits(&s->gb, 1); /* Unrestricted Motion Vector */                  // 0.0
/*104 */         skip_bits(&s->gb, 10);                                                               // 0.0
/*106 */         skip_bits(&s->gb, 3); /* Reserved */                                                 // 0.0
/*108 */                                                                                              // 0.0
/*110 */         /* MPPTYPE */                                                                        // 0.0
/*112 */         s->pict_type = get_bits(&s->gb, 3) + 1;                                              // 0.0
/*114 */         if (s->pict_type != I_TYPE &&                                                        // 0.0
/*116 */             s->pict_type != P_TYPE)                                                          // 0.0
/*118 */             return -1;                                                                       // 0.0
/*120 */         skip_bits(&s->gb, 7);                                                                // 0.0
/*122 */                                                                                              // 0.0
/*124 */         /* Get the picture dimensions */                                                     // 0.0
/*126 */         if (format == 6) {                                                                   // 0.0
/*128 */             /* Custom Picture Format (CPFMT) */                                              // 0.0
/*130 */             skip_bits(&s->gb, 4); /* aspect ratio */                                         // 0.0
/*132 */             width = (get_bits(&s->gb, 9) + 1) * 4;                                           // 0.0
/*134 */             skip_bits1(&s->gb);                                                              // 0.0
/*136 */             height = get_bits(&s->gb, 9) * 4;                                                // 0.0
/*138 */ #ifdef DEBUG                                                                                 // 0.0
/*140 */             fprintf(stderr,"\nH.263+ Custom picture: %dx%d\n",width,height);                 // 0.0
/*142 */ #endif                                                                                       // 0.0
/*144 */         }                                                                                    // 0.0
/*146 */         else {                                                                               // 0.0
/*148 */             width = h263_format[format][0];                                                  // 0.0
/*150 */             height = h263_format[format][1];                                                 // 0.0
/*152 */         }                                                                                    // 0.0
/*154 */                                                                                              // 0.0
/*156 */         if ((width == 0) || (height == 0))                                                   // 0.0
/*158 */             return -1;                                                                       // 0.0
/*160 */                                                                                              // 0.0
/*162 */         if (umvplus_dec) {                                                                   // 0.0
/*164 */             skip_bits1(&s->gb); /* Unlimited Unrestricted Motion Vectors Indicator (UUI) */  // 0.0
/*166 */         }                                                                                    // 0.0
/*168 */                                                                                              // 0.0
/*170 */         s->qscale = get_bits(&s->gb, 5);                                                     // 0.0
/*172 */     }                                                                                        // 0.0
/*174 */     /* PEI */                                                                                // 0.0
/*176 */     while (get_bits1(&s->gb) != 0) {                                                         // 0.0
/*178 */         skip_bits(&s->gb, 8);                                                                // 0.0
/*180 */     }                                                                                        // 0.0
/*182 */     s->f_code = 1;                                                                           // 0.0
/*184 */     s->width = width;                                                                        // 0.0
/*186 */     s->height = height;                                                                      // 0.0
/*188 */     return 0;                                                                                // 0.0
/*190 */ }                                                                                            // 0.0
