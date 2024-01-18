// commit message FFmpeg@aacc6615f8 (target=1, prob=0.4155584, correct=False): sanity checks
/*0   */ static inline int check_input_motion(MpegEncContext * s, int mb_x, int mb_y, int p_type){                        // (1) 0.06445
/*2   */     MotionEstContext * const c= &s->me;                                                                          // (16) 0.0293
/*4   */     Picture *p= s->current_picture_ptr;                                                                          // (15) 0.0293
/*6   */     int mb_xy= mb_x + mb_y*s->mb_stride;                                                                         // (5) 0.05078
/*8   */     int xy= 2*mb_x + 2*mb_y*s->b8_stride;                                                                        // (3) 0.05273
/*10  */     int mb_type= s->current_picture.mb_type[mb_xy];                                                              // (8) 0.04492
/*12  */     int flags= c->flags;                                                                                         // (20) 0.01953
/*14  */     int shift= (flags&FLAG_QPEL) + 1;                                                                            // (12) 0.03516
/*16  */     int mask= (1<<shift)-1;                                                                                      // (18) 0.02539
/*18  */     int x, y, i;                                                                                                 // (19) 0.01953
/*20  */     int d=0;                                                                                                     // (21) 0.01562
/*22  */     me_cmp_func cmpf= s->dsp.sse[0];                                                                             // (10) 0.04297
/*24  */     me_cmp_func chroma_cmpf= s->dsp.sse[1];                                                                      // (6) 0.04687
/*26  */                                                                                                                  // (24) 0.007812
/*28  */     assert(p_type==0 || !USES_LIST(mb_type, 1));                                                                 // (9) 0.04492
/*30  */     assert(IS_INTRA(mb_type) || USES_LIST(mb_type,0) || USES_LIST(mb_type,1));                                   // (0) 0.07422
/*32  */                                                                                                                  // (23) 0.007812
/*34  */     if(IS_INTERLACED(mb_type)){                                                                                  // (13) 0.0332
/*36  */         int xy2= xy  + s->b8_stride;                                                                             // (7) 0.04687
/*38  */         s->mb_type[mb_xy]=CANDIDATE_MB_TYPE_INTRA;                                                               // (2) 0.05664
/*40  */         c->stride<<=1;                                                                                           // (17) 0.0293
/*42  */         c->uvstride<<=1;                                                                                         // (14) 0.03125
/*44  */         init_interlaced_ref(s, 2);                                                                               // (11) 0.03711
/*46  */                                                                                                                  // (22) 0.01562
/*48  */         assert(s->flags & CODEC_FLAG_INTERLACED_ME);                                                             // (4) 0.05078
/*52  */         if(USES_LIST(mb_type, 0)){                                                                               // 0.0
/*54  */             int field_select0= p->ref_index[0][xy ];                                                             // 0.0
/*56  */             int field_select1= p->ref_index[0][xy2];                                                             // 0.0
/*58  */             assert(field_select0==0 ||field_select0==1);                                                         // 0.0
/*60  */             assert(field_select1==0 ||field_select1==1);                                                         // 0.0
/*62  */             if(p_type){                                                                                          // 0.0
/*64  */                 s->p_field_select_table[0][mb_xy]= field_select0;                                                // 0.0
/*66  */                 s->p_field_select_table[1][mb_xy]= field_select1;                                                // 0.0
/*68  */                 *(uint32_t*)s->p_field_mv_table[0][field_select0][mb_xy]= *(uint32_t*)p->motion_val[0][xy ];     // 0.0
/*70  */                 *(uint32_t*)s->p_field_mv_table[1][field_select1][mb_xy]= *(uint32_t*)p->motion_val[0][xy2];     // 0.0
/*72  */                 s->mb_type[mb_xy]=CANDIDATE_MB_TYPE_INTER_I;                                                     // 0.0
/*74  */             }else{                                                                                               // 0.0
/*76  */                 s->b_field_select_table[0][0][mb_xy]= field_select0;                                             // 0.0
/*78  */                 s->b_field_select_table[0][1][mb_xy]= field_select1;                                             // 0.0
/*80  */                 *(uint32_t*)s->b_field_mv_table[0][0][field_select0][mb_xy]= *(uint32_t*)p->motion_val[0][xy ];  // 0.0
/*82  */                 *(uint32_t*)s->b_field_mv_table[0][1][field_select1][mb_xy]= *(uint32_t*)p->motion_val[0][xy2];  // 0.0
/*84  */                 s->mb_type[mb_xy]= CANDIDATE_MB_TYPE_FORWARD_I;                                                  // 0.0
/*86  */             }                                                                                                    // 0.0
/*90  */             x= p->motion_val[0][xy ][0];                                                                         // 0.0
/*92  */             y= p->motion_val[0][xy ][1];                                                                         // 0.0
/*94  */             d = cmp(s, x>>shift, y>>shift, x&mask, y&mask, 0, 8, field_select0, 0, cmpf, chroma_cmpf, flags);    // 0.0
/*96  */             x= p->motion_val[0][xy2][0];                                                                         // 0.0
/*98  */             y= p->motion_val[0][xy2][1];                                                                         // 0.0
/*100 */             d+= cmp(s, x>>shift, y>>shift, x&mask, y&mask, 0, 8, field_select1, 1, cmpf, chroma_cmpf, flags);    // 0.0
/*102 */         }                                                                                                        // 0.0
/*104 */         if(USES_LIST(mb_type, 1)){                                                                               // 0.0
/*106 */             int field_select0= p->ref_index[1][xy ];                                                             // 0.0
/*108 */             int field_select1= p->ref_index[1][xy2];                                                             // 0.0
/*110 */             assert(field_select0==0 ||field_select0==1);                                                         // 0.0
/*112 */             assert(field_select1==0 ||field_select1==1);                                                         // 0.0
/*114 */             s->b_field_select_table[1][0][mb_xy]= field_select0;                                                 // 0.0
/*116 */             s->b_field_select_table[1][1][mb_xy]= field_select1;                                                 // 0.0
/*118 */             *(uint32_t*)s->b_field_mv_table[1][0][field_select0][mb_xy]= *(uint32_t*)p->motion_val[1][xy ];      // 0.0
/*120 */             *(uint32_t*)s->b_field_mv_table[1][1][field_select1][mb_xy]= *(uint32_t*)p->motion_val[1][xy2];      // 0.0
/*122 */             if(USES_LIST(mb_type, 0)){                                                                           // 0.0
/*124 */                 s->mb_type[mb_xy]= CANDIDATE_MB_TYPE_BIDIR_I;                                                    // 0.0
/*126 */             }else{                                                                                               // 0.0
/*128 */                 s->mb_type[mb_xy]= CANDIDATE_MB_TYPE_BACKWARD_I;                                                 // 0.0
/*130 */             }                                                                                                    // 0.0
/*134 */             x= p->motion_val[1][xy ][0];                                                                         // 0.0
/*136 */             y= p->motion_val[1][xy ][1];                                                                         // 0.0
/*138 */             d = cmp(s, x>>shift, y>>shift, x&mask, y&mask, 0, 8, field_select0+2, 0, cmpf, chroma_cmpf, flags);  // 0.0
/*140 */             x= p->motion_val[1][xy2][0];                                                                         // 0.0
/*142 */             y= p->motion_val[1][xy2][1];                                                                         // 0.0
/*144 */             d+= cmp(s, x>>shift, y>>shift, x&mask, y&mask, 0, 8, field_select1+2, 1, cmpf, chroma_cmpf, flags);  // 0.0
/*146 */             //FIXME bidir scores                                                                                 // 0.0
/*148 */         }                                                                                                        // 0.0
/*150 */         c->stride>>=1;                                                                                           // 0.0
/*152 */         c->uvstride>>=1;                                                                                         // 0.0
/*154 */     }else if(IS_8X8(mb_type)){                                                                                   // 0.0
/*157 */         cmpf= s->dsp.sse[1];                                                                                     // 0.0
/*159 */         chroma_cmpf= s->dsp.sse[1];                                                                              // 0.0
/*161 */         init_mv4_ref(s);                                                                                         // 0.0
/*163 */         for(i=0; i<4; i++){                                                                                      // 0.0
/*165 */             xy= s->block_index[i];                                                                               // 0.0
/*167 */             x= p->motion_val[0][xy][0];                                                                          // 0.0
/*169 */             y= p->motion_val[0][xy][1];                                                                          // 0.0
/*171 */             d+= cmp(s, x>>shift, y>>shift, x&mask, y&mask, 1, 8, i, i, cmpf, chroma_cmpf, flags);                // 0.0
/*173 */         }                                                                                                        // 0.0
/*175 */         s->mb_type[mb_xy]=CANDIDATE_MB_TYPE_INTER4V;                                                             // 0.0
/*177 */     }else{                                                                                                       // 0.0
/*179 */         if(USES_LIST(mb_type, 0)){                                                                               // 0.0
/*181 */             if(p_type){                                                                                          // 0.0
/*183 */                 *(uint32_t*)s->p_mv_table[mb_xy]= *(uint32_t*)p->motion_val[0][xy];                              // 0.0
/*185 */                 s->mb_type[mb_xy]=CANDIDATE_MB_TYPE_INTER;                                                       // 0.0
/*187 */             }else if(USES_LIST(mb_type, 1)){                                                                     // 0.0
/*189 */                 *(uint32_t*)s->b_bidir_forw_mv_table[mb_xy]= *(uint32_t*)p->motion_val[0][xy];                   // 0.0
/*191 */                 *(uint32_t*)s->b_bidir_back_mv_table[mb_xy]= *(uint32_t*)p->motion_val[1][xy];                   // 0.0
/*193 */                 s->mb_type[mb_xy]=CANDIDATE_MB_TYPE_BIDIR;                                                       // 0.0
/*195 */             }else{                                                                                               // 0.0
/*197 */                 *(uint32_t*)s->b_forw_mv_table[mb_xy]= *(uint32_t*)p->motion_val[0][xy];                         // 0.0
/*199 */                 s->mb_type[mb_xy]=CANDIDATE_MB_TYPE_FORWARD;                                                     // 0.0
/*201 */             }                                                                                                    // 0.0
/*203 */             x= p->motion_val[0][xy][0];                                                                          // 0.0
/*205 */             y= p->motion_val[0][xy][1];                                                                          // 0.0
/*207 */             d = cmp(s, x>>shift, y>>shift, x&mask, y&mask, 0, 16, 0, 0, cmpf, chroma_cmpf, flags);               // 0.0
/*209 */         }else if(USES_LIST(mb_type, 1)){                                                                         // 0.0
/*211 */             *(uint32_t*)s->b_back_mv_table[mb_xy]= *(uint32_t*)p->motion_val[1][xy];                             // 0.0
/*213 */             s->mb_type[mb_xy]=CANDIDATE_MB_TYPE_BACKWARD;                                                        // 0.0
/*215 */                                                                                                                  // 0.0
/*217 */             x= p->motion_val[1][xy][0];                                                                          // 0.0
/*219 */             y= p->motion_val[1][xy][1];                                                                          // 0.0
/*221 */             d = cmp(s, x>>shift, y>>shift, x&mask, y&mask, 0, 16, 2, 0, cmpf, chroma_cmpf, flags);               // 0.0
/*223 */         }else                                                                                                    // 0.0
/*225 */             s->mb_type[mb_xy]=CANDIDATE_MB_TYPE_INTRA;                                                           // 0.0
/*227 */     }                                                                                                            // 0.0
/*229 */     return d;                                                                                                    // 0.0
/*231 */ }                                                                                                                // 0.0
