// commit message FFmpeg@af8aa846fa (target=0, prob=0.36284623, correct=True): check MPV_frame_start() return value
/*0  */ static void frame_start(H264Context *h){                                                                                    // (16) 0.02344
/*2  */     MpegEncContext * const s = &h->s;                                                                                       // (12) 0.03125
/*4  */     int i;                                                                                                                  // (17) 0.01172
/*8  */     MPV_frame_start(s, s->avctx);                                                                                           // (8) 0.0332
/*10 */     ff_er_frame_start(s);                                                                                                   // (15) 0.02539
/*14 */     assert(s->linesize && s->uvlinesize);                                                                                   // (11) 0.03125
/*18 */     for(i=0; i<16; i++){                                                                                                    // (10) 0.03125
/*20 */         h->block_offset[i]= 4*((scan8[i] - scan8[0])&7) + 4*s->linesize*((scan8[i] - scan8[0])>>3);                         // (3) 0.1074
/*22 */         h->block_offset[24+i]= 4*((scan8[i] - scan8[0])&7) + 8*s->linesize*((scan8[i] - scan8[0])>>3);                      // (2) 0.1113
/*24 */     }                                                                                                                       // (19) 0.007812
/*26 */     for(i=0; i<4; i++){                                                                                                     // (13) 0.03125
/*28 */         h->block_offset[16+i]=                                                                                              // (9) 0.0332
/*30 */         h->block_offset[20+i]= 4*((scan8[i] - scan8[0])&7) + 4*s->uvlinesize*((scan8[i] - scan8[0])>>3);                    // (1) 0.1133
/*32 */         h->block_offset[24+16+i]=                                                                                           // (7) 0.03711
/*34 */         h->block_offset[24+20+i]= 4*((scan8[i] - scan8[0])&7) + 8*s->uvlinesize*((scan8[i] - scan8[0])>>3);                 // (0) 0.1172
/*36 */     }                                                                                                                       // (18) 0.007813
/*40 */     /* can't be in alloc_tables because linesize isn't known there.                                                         // (6) 0.03906
/*42 */      * FIXME: redo bipred weight to not require extra buffer? */                                                            // (5) 0.03906
/*44 */     if(!s->obmc_scratchpad)                                                                                                 // (14) 0.0293
/*46 */         s->obmc_scratchpad = av_malloc(16*s->linesize + 2*8*s->uvlinesize);                                                 // (4) 0.07422
/*50 */ //    s->decode= (s->flags&CODEC_FLAG_PSNR) || !s->encoding || s->current_picture.reference /*|| h->contains_intra*/ || 1;  // 0.0
/*52 */ }                                                                                                                           // 0.0
