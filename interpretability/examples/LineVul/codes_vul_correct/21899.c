// commit message FFmpeg@c81185a183 (target=1, prob=0.53016555, correct=True): Make sure mpeg2 has its height rounded up to 32 as that is needed for interlaced stuff. This might have been exploitable when emu edge was not set though note this bug has been introduced just a few days ago.
/*0   */ void avcodec_align_dimensions(AVCodecContext *s, int *width, int *height){           // (2) 0.04883
/*2   */     int w_align= 1;                                                                  // (25) 0.01953
/*4   */     int h_align= 1;                                                                  // (26) 0.01953
/*8   */     switch(s->pix_fmt){                                                              // (20) 0.02539
/*10  */     case PIX_FMT_YUV420P:                                                            // (14) 0.0293
/*12  */     case PIX_FMT_YUYV422:                                                            // (11) 0.03125
/*14  */     case PIX_FMT_UYVY422:                                                            // (6) 0.03125
/*16  */     case PIX_FMT_YUV422P:                                                            // (16) 0.0293
/*18  */     case PIX_FMT_YUV444P:                                                            // (17) 0.0293
/*20  */     case PIX_FMT_GRAY8:                                                              // (19) 0.02734
/*22  */     case PIX_FMT_GRAY16BE:                                                           // (15) 0.0293
/*24  */     case PIX_FMT_GRAY16LE:                                                           // (18) 0.0293
/*26  */     case PIX_FMT_YUVJ420P:                                                           // (8) 0.03125
/*28  */     case PIX_FMT_YUVJ422P:                                                           // (9) 0.03125
/*30  */     case PIX_FMT_YUVJ444P:                                                           // (10) 0.03125
/*32  */     case PIX_FMT_YUVA420P:                                                           // (7) 0.03125
/*34  */         w_align= 16; //FIXME check for non mpeg style codecs and use less alignment  // (0) 0.05469
/*36  */         h_align= 16;                                                                 // (21) 0.02539
/*40  */         break;                                                                       // (27) 0.01758
/*42  */     case PIX_FMT_YUV411P:                                                            // (12) 0.0293
/*44  */     case PIX_FMT_UYYVYY411:                                                          // (5) 0.03125
/*46  */         w_align=32;                                                                  // (23) 0.02539
/*48  */         h_align=8;                                                                   // (24) 0.02539
/*50  */         break;                                                                       // (28) 0.01758
/*52  */     case PIX_FMT_YUV410P:                                                            // (13) 0.0293
/*54  */         if(s->codec_id == CODEC_ID_SVQ1){                                            // (1) 0.05273
/*56  */             w_align=64;                                                              // (4) 0.0332
/*58  */             h_align=64;                                                              // (3) 0.0332
/*60  */         }                                                                            // (29) 0.01562
/*62  */     case PIX_FMT_RGB555:                                                             // (22) 0.02539
/*64  */         if(s->codec_id == CODEC_ID_RPZA){                                            // 0.0
/*66  */             w_align=4;                                                               // 0.0
/*68  */             h_align=4;                                                               // 0.0
/*70  */         }                                                                            // 0.0
/*72  */     case PIX_FMT_PAL8:                                                               // 0.0
/*74  */     case PIX_FMT_BGR8:                                                               // 0.0
/*76  */     case PIX_FMT_RGB8:                                                               // 0.0
/*78  */         if(s->codec_id == CODEC_ID_SMC){                                             // 0.0
/*80  */             w_align=4;                                                               // 0.0
/*82  */             h_align=4;                                                               // 0.0
/*84  */         }                                                                            // 0.0
/*86  */         break;                                                                       // 0.0
/*88  */     case PIX_FMT_BGR24:                                                              // 0.0
/*90  */         if((s->codec_id == CODEC_ID_MSZH) || (s->codec_id == CODEC_ID_ZLIB)){        // 0.0
/*92  */             w_align=4;                                                               // 0.0
/*94  */             h_align=4;                                                               // 0.0
/*96  */         }                                                                            // 0.0
/*98  */         break;                                                                       // 0.0
/*100 */     default:                                                                         // 0.0
/*102 */         w_align= 1;                                                                  // 0.0
/*104 */         h_align= 1;                                                                  // 0.0
/*106 */         break;                                                                       // 0.0
/*108 */     }                                                                                // 0.0
/*112 */     *width = ALIGN(*width , w_align);                                                // 0.0
/*114 */     *height= ALIGN(*height, h_align);                                                // 0.0
/*116 */     if(s->codec_id == CODEC_ID_H264)                                                 // 0.0
/*118 */         *height+=2; // some of the optimized chroma MC reads one line too much       // 0.0
/*120 */ }                                                                                    // 0.0
