// commit message FFmpeg@18516d3e69 (target=1, prob=0.4671434, correct=False): avutil/hwcontext_dxva2: return an error when buffer allocation fails
/*0   */ static int dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, const AVFrame *src,  // (1) 0.05859
/*2   */                            int flags)                                                 // (3) 0.05664
/*4   */ {                                                                                     // (25) 0.001953
/*6   */     IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->data[3];                    // (4) 0.05469
/*8   */     DXVA2Mapping      *map;                                                           // (15) 0.03125
/*10  */     D3DSURFACE_DESC    surfaceDesc;                                                   // (13) 0.0332
/*12  */     D3DLOCKED_RECT     LockedRect;                                                    // (14) 0.0332
/*14  */     HRESULT            hr;                                                            // (12) 0.03711
/*16  */     int i, err, nb_planes;                                                            // (19) 0.02539
/*18  */     int lock_flags = 0;                                                               // (22) 0.01953
/*22  */     nb_planes = av_pix_fmt_count_planes(dst->format);                                 // (6) 0.04883
/*26  */     hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);                            // (7) 0.04297
/*28  */     if (FAILED(hr)) {                                                                 // (21) 0.02344
/*30  */         av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");           // (5) 0.05469
/*32  */         return AVERROR_UNKNOWN;                                                       // (17) 0.0293
/*34  */     }                                                                                 // (23) 0.007812
/*38  */     if (!(flags & AV_HWFRAME_MAP_WRITE))                                              // (10) 0.03906
/*40  */         lock_flags |= D3DLOCK_READONLY;                                               // (8) 0.04102
/*42  */     if (flags & AV_HWFRAME_MAP_OVERWRITE)                                             // (11) 0.03906
/*44  */         lock_flags |= D3DLOCK_DISCARD;                                                // (9) 0.04102
/*48  */     hr = IDirect3DSurface9_LockRect(surface, &LockedRect, NULL, lock_flags);          // (2) 0.05664
/*50  */     if (FAILED(hr)) {                                                                 // (20) 0.02344
/*52  */         av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");                  // (0) 0.06055
/*54  */         return AVERROR_UNKNOWN;                                                       // (18) 0.0293
/*56  */     }                                                                                 // (24) 0.007812
/*60  */     map = av_mallocz(sizeof(*map));                                                   // (16) 0.03125
/*62  */     if (!map)                                                                         // 0.0
/*64  */         goto fail;                                                                    // 0.0
/*68  */     err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,                         // 0.0
/*70  */                                 dxva2_unmap_frame, map);                              // 0.0
/*72  */     if (err < 0) {                                                                    // 0.0
/*74  */         av_freep(&map);                                                               // 0.0
/*76  */         goto fail;                                                                    // 0.0
/*78  */     }                                                                                 // 0.0
/*82  */     for (i = 0; i < nb_planes; i++)                                                   // 0.0
/*84  */         dst->linesize[i] = LockedRect.Pitch;                                          // 0.0
/*88  */     av_image_fill_pointers(dst->data, dst->format, surfaceDesc.Height,                // 0.0
/*90  */                            (uint8_t*)LockedRect.pBits, dst->linesize);                // 0.0
/*94  */     if (dst->format == AV_PIX_FMT_PAL8)                                               // 0.0
/*96  */         dst->data[1] = (uint8_t*)map->palette_dummy;                                  // 0.0
/*100 */     return 0;                                                                         // 0.0
/*102 */ fail:                                                                                 // 0.0
/*104 */     IDirect3DSurface9_UnlockRect(surface);                                            // 0.0
/*106 */     return err;                                                                       // 0.0
/*108 */ }                                                                                     // 0.0
