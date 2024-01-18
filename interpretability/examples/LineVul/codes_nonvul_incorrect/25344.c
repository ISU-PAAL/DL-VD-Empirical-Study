// commit message FFmpeg@4dec101acc (target=0, prob=0.5195252, correct=False): dxva: preparations for new hwaccel API
/*0   */ int ff_dxva2_commit_buffer(AVCodecContext *avctx,                                                                                // (9) 0.03711
/*2   */                            AVDXVAContext *ctx,                                                                                   // (6) 0.07031
/*4   */                            DECODER_BUFFER_DESC *dsc,                                                                             // (3) 0.07617
/*6   */                            unsigned type, const void *data, unsigned size,                                                       // (4) 0.07227
/*8   */                            unsigned mb_count)                                                                                    // (7) 0.0625
/*10  */ {                                                                                                                                // (17) 0.001953
/*12  */     void     *dxva_data;                                                                                                         // (10) 0.02734
/*14  */     unsigned dxva_size;                                                                                                          // (12) 0.01758
/*16  */     int      result;                                                                                                             // (11) 0.02148
/*18  */     HRESULT hr;                                                                                                                  // (14) 0.01562
/*22  */ #if CONFIG_D3D11VA                                                                                                               // (13) 0.01758
/*24  */     if (avctx->pix_fmt == AV_PIX_FMT_D3D11VA_VLD)                                                                                // (8) 0.06055
/*26  */         hr = ID3D11VideoContext_GetDecoderBuffer(D3D11VA_CONTEXT(ctx)->video_context,                                            // (5) 0.07227
/*28  */                                                  D3D11VA_CONTEXT(ctx)->decoder,                                                  // (0) 0.123
/*30  */                                                  type,                                                                           // (2) 0.09766
/*32  */                                                  &dxva_size, &dxva_data);                                                        // (1) 0.1172
/*34  */ #endif                                                                                                                           // (16) 0.003906
/*36  */ #if CONFIG_DXVA2                                                                                                                 // (15) 0.01367
/*38  */     if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD)                                                                                  // 0.0
/*40  */         hr = IDirectXVideoDecoder_GetBuffer(DXVA2_CONTEXT(ctx)->decoder, type,                                                   // 0.0
/*42  */                                             &dxva_data, &dxva_size);                                                             // 0.0
/*44  */ #endif                                                                                                                           // 0.0
/*46  */     if (FAILED(hr)) {                                                                                                            // 0.0
/*48  */         av_log(avctx, AV_LOG_ERROR, "Failed to get a buffer for %u: 0x%x\n",                                                     // 0.0
/*50  */                type, hr);                                                                                                        // 0.0
/*52  */         return -1;                                                                                                               // 0.0
/*54  */     }                                                                                                                            // 0.0
/*56  */     if (size <= dxva_size) {                                                                                                     // 0.0
/*58  */         memcpy(dxva_data, data, size);                                                                                           // 0.0
/*62  */ #if CONFIG_D3D11VA                                                                                                               // 0.0
/*64  */         if (avctx->pix_fmt == AV_PIX_FMT_D3D11VA_VLD) {                                                                          // 0.0
/*66  */             D3D11_VIDEO_DECODER_BUFFER_DESC *dsc11 = dsc;                                                                        // 0.0
/*68  */             memset(dsc11, 0, sizeof(*dsc11));                                                                                    // 0.0
/*70  */             dsc11->BufferType           = type;                                                                                  // 0.0
/*72  */             dsc11->DataSize             = size;                                                                                  // 0.0
/*74  */             dsc11->NumMBsInBuffer       = mb_count;                                                                              // 0.0
/*76  */         }                                                                                                                        // 0.0
/*78  */ #endif                                                                                                                           // 0.0
/*80  */ #if CONFIG_DXVA2                                                                                                                 // 0.0
/*82  */         if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {                                                                            // 0.0
/*84  */             DXVA2_DecodeBufferDesc *dsc2 = dsc;                                                                                  // 0.0
/*86  */             memset(dsc2, 0, sizeof(*dsc2));                                                                                      // 0.0
/*88  */             dsc2->CompressedBufferType = type;                                                                                   // 0.0
/*90  */             dsc2->DataSize             = size;                                                                                   // 0.0
/*92  */             dsc2->NumMBsInBuffer       = mb_count;                                                                               // 0.0
/*94  */         }                                                                                                                        // 0.0
/*96  */ #endif                                                                                                                           // 0.0
/*100 */         result = 0;                                                                                                              // 0.0
/*102 */     } else {                                                                                                                     // 0.0
/*104 */         av_log(avctx, AV_LOG_ERROR, "Buffer for type %u was too small\n", type);                                                 // 0.0
/*106 */         result = -1;                                                                                                             // 0.0
/*108 */     }                                                                                                                            // 0.0
/*112 */ #if CONFIG_D3D11VA                                                                                                               // 0.0
/*114 */     if (avctx->pix_fmt == AV_PIX_FMT_D3D11VA_VLD)                                                                                // 0.0
/*116 */         hr = ID3D11VideoContext_ReleaseDecoderBuffer(D3D11VA_CONTEXT(ctx)->video_context, D3D11VA_CONTEXT(ctx)->decoder, type);  // 0.0
/*118 */ #endif                                                                                                                           // 0.0
/*120 */ #if CONFIG_DXVA2                                                                                                                 // 0.0
/*122 */     if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD)                                                                                  // 0.0
/*124 */         hr = IDirectXVideoDecoder_ReleaseBuffer(DXVA2_CONTEXT(ctx)->decoder, type);                                              // 0.0
/*126 */ #endif                                                                                                                           // 0.0
/*128 */     if (FAILED(hr)) {                                                                                                            // 0.0
/*130 */         av_log(avctx, AV_LOG_ERROR,                                                                                              // 0.0
/*132 */                "Failed to release buffer type %u: 0x%x\n",                                                                       // 0.0
/*134 */                type, hr);                                                                                                        // 0.0
/*136 */         result = -1;                                                                                                             // 0.0
/*138 */     }                                                                                                                            // 0.0
/*140 */     return result;                                                                                                               // 0.0
/*142 */ }                                                                                                                                // 0.0
