// commit message FFmpeg@ccff9da62a (target=0, prob=0.22573149, correct=True): H261 fixing and cleaning:  -corrected wrong value in mv data  -set correct mb_type after adjusting index  -don't use H263 loop filter when the loop filter flag is set but when   using the H261 encoder  -use the same unquantizer as H263 (which is optimized btw)  -removed unused members in H261Context patch by (Maarten Daniels <maarten.daniels >at< luc >dot< ac >dot< be>)
/*0   */ static int h261_find_frame_end(ParseContext *pc, AVCodecContext* avctx, const uint8_t *buf, int buf_size){             // (1) 0.07422
/*2   */     int vop_found, i, j, bits_left, last_bits;                                                                         // (7) 0.04102
/*4   */     uint32_t state;                                                                                                    // (19) 0.01758
/*8   */     H261Context *h = avctx->priv_data;                                                                                 // (13) 0.03125
/*12  */     if(h){                                                                                                             // (21) 0.01367
/*14  */         bits_left = h->bits_left;                                                                                      // (11) 0.0332
/*16  */         last_bits = h->last_bits;                                                                                      // (12) 0.0332
/*18  */     }                                                                                                                  // (25) 0.007813
/*20  */     else{                                                                                                              // (23) 0.009766
/*22  */         bits_left = 0;                                                                                                 // (17) 0.02539
/*24  */         last_bits = 0;                                                                                                 // (16) 0.02539
/*26  */     }                                                                                                                  // (24) 0.007813
/*30  */     vop_found= pc->frame_start_found;                                                                                  // (14) 0.03125
/*32  */     state= pc->state;                                                                                                  // (20) 0.01758
/*34  */     if(bits_left!=0 && !vop_found)                                                                                     // (10) 0.03516
/*36  */         state = state << (8-bits_left) | last_bits;                                                                    // (5) 0.04492
/*38  */     i=0;                                                                                                               // (22) 0.01367
/*40  */     if(!vop_found){                                                                                                    // (18) 0.02148
/*42  */         for(i=0; i<buf_size; i++){                                                                                     // (6) 0.04297
/*44  */             state= (state<<8) | buf[i];                                                                                // (4) 0.04492
/*46  */             for(j=0; j<8; j++){                                                                                        // (3) 0.04687
/*48  */                 if(( (  (state<<j)  |  (buf[i]>>(8-j))  )>>(32-20) == 0x10 )&&(((state >> (17-j)) & 0x4000) == 0x0)){  // (0) 0.1406
/*50  */                     i++;                                                                                               // (8) 0.04102
/*52  */                     vop_found=1;                                                                                       // (2) 0.05078
/*54  */                     break;                                                                                             // (9) 0.04102
/*56  */                 }                                                                                                      // (15) 0.03125
/*58  */             }                                                                                                          // 0.0
/*60  */             if(vop_found)                                                                                              // 0.0
/*62  */                     break;                                                                                             // 0.0
/*64  */         }                                                                                                              // 0.0
/*66  */     }                                                                                                                  // 0.0
/*68  */     if(vop_found){                                                                                                     // 0.0
/*70  */         for(; i<buf_size; i++){                                                                                        // 0.0
/*72  */             if(avctx->flags & CODEC_FLAG_TRUNCATED)//XXX ffplay workaround, someone a better solution?                 // 0.0
/*74  */                 state= (state<<8) | buf[i];                                                                            // 0.0
/*76  */             for(j=0; j<8; j++){                                                                                        // 0.0
/*78  */                 if(( (  (state<<j)  |  (buf[i]>>(8-j))  )>>(32-20) == 0x10 )&&(((state >> (17-j)) & 0x4000) == 0x0)){  // 0.0
/*80  */                     pc->frame_start_found=0;                                                                           // 0.0
/*82  */                     pc->state=-1;                                                                                      // 0.0
/*84  */                     return i-3;                                                                                        // 0.0
/*86  */                 }                                                                                                      // 0.0
/*88  */             }                                                                                                          // 0.0
/*90  */         }                                                                                                              // 0.0
/*92  */     }                                                                                                                  // 0.0
/*96  */     pc->frame_start_found= vop_found;                                                                                  // 0.0
/*98  */     pc->state= state;                                                                                                  // 0.0
/*100 */     return END_NOT_FOUND;                                                                                              // 0.0
/*102 */ }                                                                                                                      // 0.0
