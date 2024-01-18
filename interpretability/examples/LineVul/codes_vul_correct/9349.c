// commit message FFmpeg@aaf78e4d14 (target=1, prob=0.572433, correct=True): vf_mp: fix null ptr deref in case of ENOMEM
/*0   */ mp_image_t* vf_get_image(vf_instance_t* vf, unsigned int outfmt, int mp_imgtype, int mp_imgflag, int w, int h){                    // (1) 0.08998
/*2   */     MPContext *m= (MPContext*)(((uint8_t*)vf) - offsetof(MPContext, next_vf));                                                     // (4) 0.06542
/*4   */   mp_image_t* mpi=NULL;                                                                                                            // (17) 0.02338
/*6   */   int w2;                                                                                                                          // (21) 0.009607
/*8   */   int number = mp_imgtype >> 16;                                                                                                   // (20) 0.02108
/*12  */   av_assert0(vf->next == NULL); // all existing filters call this just on next                                                     // (6) 0.04294
/*16  */   //vf_dint needs these as it calls vf_get_image() before configuring the output                                                   // (5) 0.05142
/*18  */   if(vf->w==0 && w>0) vf->w=w;                                                                                                     // (8) 0.04018
/*20  */   if(vf->h==0 && h>0) vf->h=h;                                                                                                     // (9) 0.03998
/*24  */   av_assert0(w == -1 || w >= vf->w);                                                                                               // (10) 0.03428
/*26  */   av_assert0(h == -1 || h >= vf->h);                                                                                               // (11) 0.03426
/*28  */   av_assert0(vf->w > 0);                                                                                                           // (16) 0.02474
/*30  */   av_assert0(vf->h > 0);                                                                                                           // (15) 0.02476
/*34  */   av_log(m->avfctx, AV_LOG_DEBUG, "get_image: %d:%d, vf: %d:%d\n", w,h,vf->w,vf->h);                                               // (0) 0.1011
/*38  */   if (w == -1) w = vf->w;                                                                                                          // (12) 0.02864
/*40  */   if (h == -1) h = vf->h;                                                                                                          // (13) 0.02858
/*44  */   w2=(mp_imgflag&MP_IMGFLAG_ACCEPT_ALIGNED_STRIDE)?((w+15)&(~15)):w;                                                               // (3) 0.07333
/*48  */   // Note: we should call libvo first to check if it supports direct rendering                                                     // (7) 0.04209
/*50  */   // and if not, then fallback to software buffers:                                                                                // (14) 0.02597
/*52  */   switch(mp_imgtype & 0xff){                                                                                                       // (19) 0.02151
/*54  */   case MP_IMGTYPE_EXPORT:                                                                                                          // (18) 0.02174
/*56  */     if(!vf->imgctx.export_images[0]) vf->imgctx.export_images[0]=new_mp_image(w2,h);                                               // (2) 0.07815
/*58  */     mpi=vf->imgctx.export_images[0];                                                                                               // 0.0
/*60  */     break;                                                                                                                         // 0.0
/*62  */   case MP_IMGTYPE_STATIC:                                                                                                          // 0.0
/*64  */     if(!vf->imgctx.static_images[0]) vf->imgctx.static_images[0]=new_mp_image(w2,h);                                               // 0.0
/*66  */     mpi=vf->imgctx.static_images[0];                                                                                               // 0.0
/*68  */     break;                                                                                                                         // 0.0
/*70  */   case MP_IMGTYPE_TEMP:                                                                                                            // 0.0
/*72  */     if(!vf->imgctx.temp_images[0]) vf->imgctx.temp_images[0]=new_mp_image(w2,h);                                                   // 0.0
/*74  */     mpi=vf->imgctx.temp_images[0];                                                                                                 // 0.0
/*76  */     break;                                                                                                                         // 0.0
/*78  */   case MP_IMGTYPE_IPB:                                                                                                             // 0.0
/*80  */     if(!(mp_imgflag&MP_IMGFLAG_READABLE)){ // B frame:                                                                             // 0.0
/*82  */       if(!vf->imgctx.temp_images[0]) vf->imgctx.temp_images[0]=new_mp_image(w2,h);                                                 // 0.0
/*84  */       mpi=vf->imgctx.temp_images[0];                                                                                               // 0.0
/*86  */       break;                                                                                                                       // 0.0
/*88  */     }                                                                                                                              // 0.0
/*90  */   case MP_IMGTYPE_IP:                                                                                                              // 0.0
/*92  */     if(!vf->imgctx.static_images[vf->imgctx.static_idx]) vf->imgctx.static_images[vf->imgctx.static_idx]=new_mp_image(w2,h);       // 0.0
/*94  */     mpi=vf->imgctx.static_images[vf->imgctx.static_idx];                                                                           // 0.0
/*96  */     vf->imgctx.static_idx^=1;                                                                                                      // 0.0
/*98  */     break;                                                                                                                         // 0.0
/*100 */   case MP_IMGTYPE_NUMBERED:                                                                                                        // 0.0
/*102 */     if (number == -1) {                                                                                                            // 0.0
/*104 */       int i;                                                                                                                       // 0.0
/*106 */       for (i = 0; i < NUM_NUMBERED_MPI; i++)                                                                                       // 0.0
/*108 */         if (!vf->imgctx.numbered_images[i] || !vf->imgctx.numbered_images[i]->usage_count)                                         // 0.0
/*110 */           break;                                                                                                                   // 0.0
/*112 */       number = i;                                                                                                                  // 0.0
/*114 */     }                                                                                                                              // 0.0
/*116 */     if (number < 0 || number >= NUM_NUMBERED_MPI) return NULL;                                                                     // 0.0
/*118 */     if (!vf->imgctx.numbered_images[number]) vf->imgctx.numbered_images[number] = new_mp_image(w2,h);                              // 0.0
/*120 */     mpi = vf->imgctx.numbered_images[number];                                                                                      // 0.0
/*122 */     mpi->number = number;                                                                                                          // 0.0
/*124 */     break;                                                                                                                         // 0.0
/*126 */   }                                                                                                                                // 0.0
/*128 */   if(mpi){                                                                                                                         // 0.0
/*130 */     mpi->type=mp_imgtype;                                                                                                          // 0.0
/*132 */     mpi->w=vf->w; mpi->h=vf->h;                                                                                                    // 0.0
/*134 */     // keep buffer allocation status & color flags only:                                                                           // 0.0
/*136 */ //    mpi->flags&=~(MP_IMGFLAG_PRESERVE|MP_IMGFLAG_READABLE|MP_IMGFLAG_DIRECT);                                                    // 0.0
/*138 */     mpi->flags&=MP_IMGFLAG_ALLOCATED|MP_IMGFLAG_TYPE_DISPLAYED|MP_IMGFLAGMASK_COLORS;                                              // 0.0
/*140 */     // accept restrictions, draw_slice and palette flags only:                                                                     // 0.0
/*142 */     mpi->flags|=mp_imgflag&(MP_IMGFLAGMASK_RESTRICTIONS|MP_IMGFLAG_DRAW_CALLBACK|MP_IMGFLAG_RGB_PALETTE);                          // 0.0
/*144 */     if(!vf->draw_slice) mpi->flags&=~MP_IMGFLAG_DRAW_CALLBACK;                                                                     // 0.0
/*146 */     if(mpi->width!=w2 || mpi->height!=h){                                                                                          // 0.0
/*148 */ //      printf("vf.c: MPI parameters changed!  %dx%d -> %dx%d   \n", mpi->width,mpi->height,w2,h);                                 // 0.0
/*150 */         if(mpi->flags&MP_IMGFLAG_ALLOCATED){                                                                                       // 0.0
/*152 */             if(mpi->width<w2 || mpi->height<h){                                                                                    // 0.0
/*154 */                 // need to re-allocate buffer memory:                                                                              // 0.0
/*156 */                 av_free(mpi->planes[0]);                                                                                           // 0.0
/*158 */                 mpi->flags&=~MP_IMGFLAG_ALLOCATED;                                                                                 // 0.0
/*160 */                 mp_msg(MSGT_VFILTER,MSGL_V,"vf.c: have to REALLOCATE buffer memory :(\n");                                         // 0.0
/*162 */             }                                                                                                                      // 0.0
/*164 */ //      } else {                                                                                                                   // 0.0
/*166 */         } {                                                                                                                        // 0.0
/*168 */             mpi->width=w2; mpi->chroma_width=(w2 + (1<<mpi->chroma_x_shift) - 1)>>mpi->chroma_x_shift;                             // 0.0
/*170 */             mpi->height=h; mpi->chroma_height=(h + (1<<mpi->chroma_y_shift) - 1)>>mpi->chroma_y_shift;                             // 0.0
/*172 */         }                                                                                                                          // 0.0
/*174 */     }                                                                                                                              // 0.0
/*176 */     if(!mpi->bpp) mp_image_setfmt(mpi,outfmt);                                                                                     // 0.0
/*178 */     if(!(mpi->flags&MP_IMGFLAG_ALLOCATED) && mpi->type>MP_IMGTYPE_EXPORT){                                                         // 0.0
/*182 */         av_assert0(!vf->get_image);                                                                                                // 0.0
/*184 */         // check libvo first!                                                                                                      // 0.0
/*186 */         if(vf->get_image) vf->get_image(vf,mpi);                                                                                   // 0.0
/*190 */         if(!(mpi->flags&MP_IMGFLAG_DIRECT)){                                                                                       // 0.0
/*192 */           // non-direct and not yet allocated image. allocate it!                                                                  // 0.0
/*194 */           if (!mpi->bpp) { // no way we can allocate this                                                                          // 0.0
/*196 */               mp_msg(MSGT_DECVIDEO, MSGL_FATAL,                                                                                    // 0.0
/*198 */                      "vf_get_image: Tried to allocate a format that can not be allocated!\n");                                     // 0.0
/*200 */               return NULL;                                                                                                         // 0.0
/*202 */           }                                                                                                                        // 0.0
/*206 */           // check if codec prefer aligned stride:                                                                                 // 0.0
/*208 */           if(mp_imgflag&MP_IMGFLAG_PREFER_ALIGNED_STRIDE){                                                                         // 0.0
/*210 */               int align=(mpi->flags&MP_IMGFLAG_PLANAR &&                                                                           // 0.0
/*212 */                          mpi->flags&MP_IMGFLAG_YUV) ?                                                                              // 0.0
/*214 */                          (8<<mpi->chroma_x_shift)-1 : 15; // -- maybe FIXME                                                        // 0.0
/*216 */               w2=((w+align)&(~align));                                                                                             // 0.0
/*218 */               if(mpi->width!=w2){                                                                                                  // 0.0
/*220 */ #if 0                                                                                                                              // 0.0
/*222 */                   // we have to change width... check if we CAN co it:                                                             // 0.0
/*224 */                   int flags=vf->query_format(vf,outfmt); // should not fail                                                        // 0.0
/*226 */                   if(!(flags&3)) mp_msg(MSGT_DECVIDEO,MSGL_WARN,"??? vf_get_image{vf->query_format(outfmt)} failed!\n");           // 0.0
/*228 */ //                printf("query -> 0x%X    \n",flags);                                                                             // 0.0
/*230 */                   if(flags&VFCAP_ACCEPT_STRIDE){                                                                                   // 0.0
/*232 */ #endif                                                                                                                             // 0.0
/*234 */                       mpi->width=w2;                                                                                               // 0.0
/*236 */                       mpi->chroma_width=(w2 + (1<<mpi->chroma_x_shift) - 1)>>mpi->chroma_x_shift;                                  // 0.0
/*238 */ //                  }                                                                                                              // 0.0
/*240 */               }                                                                                                                    // 0.0
/*242 */           }                                                                                                                        // 0.0
/*246 */           mp_image_alloc_planes(mpi);                                                                                              // 0.0
/*248 */ //        printf("clearing img!\n");                                                                                               // 0.0
/*250 */           vf_mpi_clear(mpi,0,0,mpi->width,mpi->height);                                                                            // 0.0
/*252 */         }                                                                                                                          // 0.0
/*254 */     }                                                                                                                              // 0.0
/*256 */     av_assert0(!vf->start_slice);                                                                                                  // 0.0
/*258 */     if(mpi->flags&MP_IMGFLAG_DRAW_CALLBACK)                                                                                        // 0.0
/*260 */         if(vf->start_slice) vf->start_slice(vf,mpi);                                                                               // 0.0
/*262 */     if(!(mpi->flags&MP_IMGFLAG_TYPE_DISPLAYED)){                                                                                   // 0.0
/*264 */             mp_msg(MSGT_DECVIDEO,MSGL_V,"*** [%s] %s%s mp_image_t, %dx%dx%dbpp %s %s, %d bytes\n",                                 // 0.0
/*266 */                   "NULL"/*vf->info->name*/,                                                                                        // 0.0
/*268 */                   (mpi->type==MP_IMGTYPE_EXPORT)?"Exporting":                                                                      // 0.0
/*270 */                   ((mpi->flags&MP_IMGFLAG_DIRECT)?"Direct Rendering":"Allocating"),                                                // 0.0
/*272 */                   (mpi->flags&MP_IMGFLAG_DRAW_CALLBACK)?" (slices)":"",                                                            // 0.0
/*274 */                   mpi->width,mpi->height,mpi->bpp,                                                                                 // 0.0
/*276 */                   (mpi->flags&MP_IMGFLAG_YUV)?"YUV":((mpi->flags&MP_IMGFLAG_SWAPPED)?"BGR":"RGB"),                                 // 0.0
/*278 */                   (mpi->flags&MP_IMGFLAG_PLANAR)?"planar":"packed",                                                                // 0.0
/*280 */                   mpi->bpp*mpi->width*mpi->height/8);                                                                              // 0.0
/*282 */             mp_msg(MSGT_DECVIDEO,MSGL_DBG2,"(imgfmt: %x, planes: %p,%p,%p strides: %d,%d,%d, chroma: %dx%d, shift: h:%d,v:%d)\n",  // 0.0
/*284 */                 mpi->imgfmt, mpi->planes[0], mpi->planes[1], mpi->planes[2],                                                       // 0.0
/*286 */                 mpi->stride[0], mpi->stride[1], mpi->stride[2],                                                                    // 0.0
/*288 */                 mpi->chroma_width, mpi->chroma_height, mpi->chroma_x_shift, mpi->chroma_y_shift);                                  // 0.0
/*290 */             mpi->flags|=MP_IMGFLAG_TYPE_DISPLAYED;                                                                                 // 0.0
/*292 */     }                                                                                                                              // 0.0
/*296 */   mpi->qscale = NULL;                                                                                                              // 0.0
/*298 */   }                                                                                                                                // 0.0
/*300 */   mpi->usage_count++;                                                                                                              // 0.0
/*302 */ //    printf("\rVF_MPI: %p %p %p %d %d %d    \n",                                                                                  // 0.0
/*304 */ //      mpi->planes[0],mpi->planes[1],mpi->planes[2],                                                                              // 0.0
/*306 */ //      mpi->stride[0],mpi->stride[1],mpi->stride[2]);                                                                             // 0.0
/*308 */   return mpi;                                                                                                                      // 0.0
/*310 */ }                                                                                                                                  // 0.0
