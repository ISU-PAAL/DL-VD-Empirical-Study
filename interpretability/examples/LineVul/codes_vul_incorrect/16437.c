// commit message FFmpeg@f6774f905f (target=1, prob=0.18076526, correct=False): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0  */ void ff_xvmc_field_end(MpegEncContext *s)                                              // (2) 0.1488
/*2  */ {                                                                                      // (5) 0.008264
/*4  */     struct xvmc_pix_fmt *render = (struct xvmc_pix_fmt*)s->current_picture.f.data[2];  // (0) 0.3306
/*6  */     assert(render);                                                                    // (4) 0.05785
/*10 */     if (render->filled_mv_blocks_num > 0)                                              // (3) 0.1488
/*12 */         ff_mpeg_draw_horiz_band(s, 0, 0);                                              // (1) 0.1983
/*14 */ }                                                                                      // (6) 0.008264
