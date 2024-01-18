// commit message FFmpeg@d58a6d8537 (target=1, prob=0.40096188, correct=False): put the warning to the right place to avoid crashes
/*0   */ static int encode_frame(AVCodecContext *avctx, unsigned char *buf, int buf_size, void *data){                                              // (3) 0.05469
/*2   */     FFV1Context *f = avctx->priv_data;                                                                                                     // (9) 0.0332
/*4   */     CABACContext * const c= &f->c;                                                                                                         // (10) 0.03125
/*6   */     AVFrame *pict = data;                                                                                                                  // (21) 0.01953
/*8   */     const int width= f->width;                                                                                                             // (18) 0.02148
/*10  */     const int height= f->height;                                                                                                           // (20) 0.02148
/*12  */     AVFrame * const p= &f->picture;                                                                                                        // (15) 0.02734
/*14  */     int used_count= 0;                                                                                                                     // (22) 0.01953
/*18  */     if(avctx->strict_std_compliance >= 0){                                                                                                 // (8) 0.0332
/*20  */         av_log(avctx, AV_LOG_ERROR, "this codec is under development, files encoded with it wont be decodeable with future versions!!!\n"  // (1) 0.08203
/*22  */                "use vstrict=-1 to use it anyway\n");                                                                                       // (4) 0.05469
/*24  */         return -1;                                                                                                                         // (19) 0.02148
/*26  */     }                                                                                                                                      // (26) 0.007813
/*28  */                                                                                                                                            // (24) 0.01562
/*30  */     ff_init_cabac_encoder(c, buf, buf_size);                                                                                               // (5) 0.04297
/*32  */     ff_init_cabac_states(c, ff_h264_lps_range, ff_h264_mps_state, ff_h264_lps_state, 64);                                                  // (0) 0.0918
/*34  */     c->lps_state[2] = 1;                                                                                                                   // (14) 0.0293
/*36  */     c->lps_state[3] = 0;                                                                                                                   // (13) 0.0293
/*38  */                                                                                                                                            // (28) 0.007812
/*40  */     *p = *pict;                                                                                                                            // (23) 0.01758
/*42  */     p->pict_type= FF_I_TYPE;                                                                                                               // (11) 0.0293
/*44  */                                                                                                                                            // (29) 0.007812
/*46  */     if(avctx->gop_size==0 || f->picture_number % avctx->gop_size == 0){                                                                    // (2) 0.06055
/*48  */         put_cabac_bypass(c, 1);                                                                                                            // (7) 0.03906
/*50  */         p->key_frame= 1;                                                                                                                   // (12) 0.0293
/*52  */         write_header(f);                                                                                                                   // (17) 0.02539
/*54  */         clear_state(f);                                                                                                                    // (16) 0.02539
/*56  */     }else{                                                                                                                                 // (25) 0.01172
/*58  */         put_cabac_bypass(c, 0);                                                                                                            // (6) 0.03906
/*60  */         p->key_frame= 0;                                                                                                                   // 0.0
/*62  */     }                                                                                                                                      // 0.0
/*66  */     if(!f->ac){                                                                                                                            // 0.0
/*68  */         used_count += put_cabac_terminate(c, 1);                                                                                           // 0.0
/*70  */ //printf("pos=%d\n", used_count);                                                                                                          // 0.0
/*72  */         init_put_bits(&f->pb, buf + used_count, buf_size - used_count);                                                                    // 0.0
/*74  */     }                                                                                                                                      // 0.0
/*76  */                                                                                                                                            // (27) 0.007813
/*78  */     if(f->colorspace==0){                                                                                                                  // 0.0
/*80  */         const int chroma_width = -((-width )>>f->chroma_h_shift);                                                                          // 0.0
/*82  */         const int chroma_height= -((-height)>>f->chroma_v_shift);                                                                          // 0.0
/*86  */         encode_plane(f, p->data[0], width, height, p->linesize[0], 0);                                                                     // 0.0
/*90  */         encode_plane(f, p->data[1], chroma_width, chroma_height, p->linesize[1], 1);                                                       // 0.0
/*92  */         encode_plane(f, p->data[2], chroma_width, chroma_height, p->linesize[2], 1);                                                       // 0.0
/*94  */     }else{                                                                                                                                 // 0.0
/*96  */         encode_rgb_frame(f, (uint32_t*)(p->data[0]), width, height, p->linesize[0]/4);                                                     // 0.0
/*98  */     }                                                                                                                                      // 0.0
/*100 */     emms_c();                                                                                                                              // 0.0
/*102 */                                                                                                                                            // 0.0
/*104 */     f->picture_number++;                                                                                                                   // 0.0
/*108 */     if(f->ac){                                                                                                                             // 0.0
/*110 */         return put_cabac_terminate(c, 1);                                                                                                  // 0.0
/*112 */     }else{                                                                                                                                 // 0.0
/*114 */         flush_put_bits(&f->pb); //nicer padding FIXME                                                                                      // 0.0
/*116 */         return used_count + (put_bits_count(&f->pb)+7)/8;                                                                                  // 0.0
/*118 */     }                                                                                                                                      // 0.0
/*120 */ }                                                                                                                                          // 0.0
