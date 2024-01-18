// commit message FFmpeg@14f3f3a1ad (target=1, prob=0.85579747, correct=True): Off-by-one error fix
/*0   */ static int decode_sequence_header_adv(VC1Context *v, GetBitContext *gb)                               // (7) 0.04297
/*2   */ {                                                                                                     // (28) 0.001953
/*4   */     v->res_rtm_flag = 1;                                                                              // (17) 0.02734
/*6   */     v->level = get_bits(gb, 3);                                                                       // (13) 0.0293
/*8   */     if(v->level >= 5)                                                                                 // (19) 0.02148
/*10  */     {                                                                                                 // (23) 0.007812
/*12  */         av_log(v->s.avctx, AV_LOG_ERROR, "Reserved LEVEL %i\n",v->level);                             // (0) 0.07227
/*14  */     }                                                                                                 // (24) 0.007812
/*16  */     v->chromaformat = get_bits(gb, 2);                                                                // (11) 0.0332
/*18  */     if (v->chromaformat != 1)                                                                         // (18) 0.02539
/*20  */     {                                                                                                 // (25) 0.007812
/*22  */         av_log(v->s.avctx, AV_LOG_ERROR,                                                              // (5) 0.04688
/*24  */                "Only 4:2:0 chroma format supported\n");                                               // (4) 0.05469
/*26  */         return -1;                                                                                    // (20) 0.02148
/*28  */     }                                                                                                 // (26) 0.007812
/*32  */     // (fps-2)/4 (->30)                                                                               // (16) 0.02734
/*34  */     v->frmrtq_postproc = get_bits(gb, 3); //common                                                    // (6) 0.04492
/*36  */     // (bitrate-32kbps)/64kbps                                                                        // (12) 0.0293
/*38  */     v->bitrtq_postproc = get_bits(gb, 5); //common                                                    // (8) 0.04297
/*40  */     v->postprocflag = get_bits(gb, 1); //common                                                       // (9) 0.03711
/*44  */     v->s.avctx->coded_width = (get_bits(gb, 12) + 1) << 1;                                            // (2) 0.05664
/*46  */     v->s.avctx->coded_height = (get_bits(gb, 12) + 1) << 1;                                           // (3) 0.05664
/*48  */     v->broadcast = get_bits1(gb);                                                                     // (14) 0.0293
/*50  */     v->interlace = get_bits1(gb);                                                                     // (15) 0.0293
/*52  */     if(v->interlace){                                                                                 // (22) 0.01953
/*54  */         av_log(v->s.avctx, AV_LOG_ERROR, "Interlaced mode not supported (yet)\n");                    // (1) 0.07031
/*56  */         return -1;                                                                                    // (21) 0.02148
/*58  */     }                                                                                                 // (27) 0.007812
/*60  */     v->tfcntrflag = get_bits1(gb);                                                                    // (10) 0.03516
/*62  */     v->finterpflag = get_bits1(gb);                                                                   // 0.0
/*64  */     get_bits1(gb); // reserved                                                                        // 0.0
/*66  */     v->psf = get_bits1(gb);                                                                           // 0.0
/*68  */     if(v->psf) { //PsF, 6.1.13                                                                        // 0.0
/*70  */         av_log(v->s.avctx, AV_LOG_ERROR, "Progressive Segmented Frame mode: not supported (yet)\n");  // 0.0
/*72  */         return -1;                                                                                    // 0.0
/*74  */     }                                                                                                 // 0.0
/*76  */     if(get_bits1(gb)) { //Display Info - decoding is not affected by it                               // 0.0
/*78  */         int w, h, ar = 0;                                                                             // 0.0
/*80  */         av_log(v->s.avctx, AV_LOG_INFO, "Display extended info:\n");                                  // 0.0
/*82  */         w = get_bits(gb, 14);                                                                         // 0.0
/*84  */         h = get_bits(gb, 14);                                                                         // 0.0
/*86  */         av_log(v->s.avctx, AV_LOG_INFO, "Display dimensions: %ix%i\n", w, h);                         // 0.0
/*88  */         //TODO: store aspect ratio in AVCodecContext                                                  // 0.0
/*90  */         if(get_bits1(gb))                                                                             // 0.0
/*92  */             ar = get_bits(gb, 4);                                                                     // 0.0
/*94  */         if(ar == 15) {                                                                                // 0.0
/*96  */             w = get_bits(gb, 8);                                                                      // 0.0
/*98  */             h = get_bits(gb, 8);                                                                      // 0.0
/*100 */         }                                                                                             // 0.0
/*104 */         if(get_bits1(gb)){ //framerate stuff                                                          // 0.0
/*106 */             if(get_bits1(gb)) {                                                                       // 0.0
/*108 */                 get_bits(gb, 16);                                                                     // 0.0
/*110 */             } else {                                                                                  // 0.0
/*112 */                 get_bits(gb, 8);                                                                      // 0.0
/*114 */                 get_bits(gb, 4);                                                                      // 0.0
/*116 */             }                                                                                         // 0.0
/*118 */         }                                                                                             // 0.0
/*122 */         if(get_bits1(gb)){                                                                            // 0.0
/*124 */             v->color_prim = get_bits(gb, 8);                                                          // 0.0
/*126 */             v->transfer_char = get_bits(gb, 8);                                                       // 0.0
/*128 */             v->matrix_coef = get_bits(gb, 8);                                                         // 0.0
/*130 */         }                                                                                             // 0.0
/*132 */     }                                                                                                 // 0.0
/*136 */     v->hrd_param_flag = get_bits1(gb);                                                                // 0.0
/*138 */     if(v->hrd_param_flag) {                                                                           // 0.0
/*140 */         int i;                                                                                        // 0.0
/*142 */         v->hrd_num_leaky_buckets = get_bits(gb, 5);                                                   // 0.0
/*144 */         get_bits(gb, 4); //bitrate exponent                                                           // 0.0
/*146 */         get_bits(gb, 4); //buffer size exponent                                                       // 0.0
/*148 */         for(i = 0; i < v->hrd_num_leaky_buckets; i++) {                                               // 0.0
/*150 */             get_bits(gb, 16); //hrd_rate[n]                                                           // 0.0
/*152 */             get_bits(gb, 16); //hrd_buffer[n]                                                         // 0.0
/*154 */         }                                                                                             // 0.0
/*156 */     }                                                                                                 // 0.0
/*158 */     return 0;                                                                                         // 0.0
/*160 */ }                                                                                                     // 0.0
