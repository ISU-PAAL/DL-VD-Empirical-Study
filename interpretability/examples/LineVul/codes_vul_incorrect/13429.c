// commit message FFmpeg@6abc56e892 (target=1, prob=0.42545697, correct=False): dshow: use distinct buffers per stream.
/*0   */ static int dshow_read_header(AVFormatContext *avctx)                                           // (10) 0.03126
/*2   */ {                                                                                              // (26) 0.001957
/*4   */     struct dshow_ctx *ctx = avctx->priv_data;                                                  // (9) 0.03516
/*6   */     IGraphBuilder *graph = NULL;                                                               // (16) 0.02149
/*8   */     ICreateDevEnum *devenum = NULL;                                                            // (11) 0.0293
/*10  */     IMediaControl *control = NULL;                                                             // (17) 0.02149
/*12  */     IMediaEvent *media_event = NULL;                                                           // (13) 0.02539
/*14  */     HANDLE media_event_handle;                                                                 // (15) 0.02344
/*16  */     HANDLE proc;                                                                               // (21) 0.01563
/*18  */     int ret = AVERROR(EIO);                                                                    // (14) 0.02539
/*20  */     int r;                                                                                     // (23) 0.01172
/*24  */     CoInitialize(0);                                                                           // (20) 0.01758
/*28  */     if (!ctx->list_devices && !parse_device_name(avctx)) {                                     // (7) 0.04297
/*30  */         av_log(avctx, AV_LOG_ERROR, "Malformed dshow input string.\n");                        // (4) 0.06055
/*32  */         goto error;                                                                            // (19) 0.01953
/*34  */     }                                                                                          // (24) 0.007812
/*38  */     ctx->video_codec_id = avctx->video_codec_id ? avctx->video_codec_id                        // (3) 0.0625
/*40  */                                                 : AV_CODEC_ID_RAWVIDEO;                        // (0) 0.1152
/*42  */     if (ctx->pixel_format != AV_PIX_FMT_NONE) {                                                // (6) 0.04492
/*44  */         if (ctx->video_codec_id != AV_CODEC_ID_RAWVIDEO) {                                     // (5) 0.05859
/*46  */             av_log(avctx, AV_LOG_ERROR, "Pixel format may only be set when "                   // (2) 0.06445
/*48  */                               "video codec is not set or set to rawvideo\n");                  // (1) 0.08398
/*50  */             ret = AVERROR(EINVAL);                                                             // (8) 0.04101
/*52  */             goto error;                                                                        // (12) 0.02734
/*54  */         }                                                                                      // (22) 0.01562
/*56  */     }                                                                                          // (25) 0.007812
/*58  */     if (ctx->framerate) {                                                                      // (18) 0.02148
/*60  */         r = av_parse_video_rate(&ctx->requested_framerate, ctx->framerate);                    // 0.0
/*62  */         if (r < 0) {                                                                           // 0.0
/*64  */             av_log(avctx, AV_LOG_ERROR, "Could not parse framerate '%s'.\n", ctx->framerate);  // 0.0
/*66  */             goto error;                                                                        // 0.0
/*68  */         }                                                                                      // 0.0
/*70  */     }                                                                                          // 0.0
/*74  */     r = CoCreateInstance(&CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,                       // 0.0
/*76  */                          &IID_IGraphBuilder, (void **) &graph);                                // 0.0
/*78  */     if (r != S_OK) {                                                                           // 0.0
/*80  */         av_log(avctx, AV_LOG_ERROR, "Could not create capture graph.\n");                      // 0.0
/*82  */         goto error;                                                                            // 0.0
/*84  */     }                                                                                          // 0.0
/*86  */     ctx->graph = graph;                                                                        // 0.0
/*90  */     r = CoCreateInstance(&CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,                  // 0.0
/*92  */                          &IID_ICreateDevEnum, (void **) &devenum);                             // 0.0
/*94  */     if (r != S_OK) {                                                                           // 0.0
/*96  */         av_log(avctx, AV_LOG_ERROR, "Could not enumerate system devices.\n");                  // 0.0
/*98  */         goto error;                                                                            // 0.0
/*100 */     }                                                                                          // 0.0
/*104 */     if (ctx->list_devices) {                                                                   // 0.0
/*106 */         av_log(avctx, AV_LOG_INFO, "DirectShow video devices\n");                              // 0.0
/*108 */         dshow_cycle_devices(avctx, devenum, VideoDevice, NULL);                                // 0.0
/*110 */         av_log(avctx, AV_LOG_INFO, "DirectShow audio devices\n");                              // 0.0
/*112 */         dshow_cycle_devices(avctx, devenum, AudioDevice, NULL);                                // 0.0
/*114 */         ret = AVERROR_EXIT;                                                                    // 0.0
/*116 */         goto error;                                                                            // 0.0
/*118 */     }                                                                                          // 0.0
/*120 */     if (ctx->list_options) {                                                                   // 0.0
/*122 */         if (ctx->device_name[VideoDevice])                                                     // 0.0
/*124 */             dshow_list_device_options(avctx, devenum, VideoDevice);                            // 0.0
/*126 */         if (ctx->device_name[AudioDevice])                                                     // 0.0
/*128 */             dshow_list_device_options(avctx, devenum, AudioDevice);                            // 0.0
/*130 */         ret = AVERROR_EXIT;                                                                    // 0.0
/*132 */         goto error;                                                                            // 0.0
/*134 */     }                                                                                          // 0.0
/*138 */     if (ctx->device_name[VideoDevice]) {                                                       // 0.0
/*140 */         if ((r = dshow_open_device(avctx, devenum, VideoDevice)) < 0 ||                        // 0.0
/*142 */             (r = dshow_add_device(avctx, VideoDevice)) < 0) {                                  // 0.0
/*144 */             ret = r;                                                                           // 0.0
/*146 */             goto error;                                                                        // 0.0
/*148 */         }                                                                                      // 0.0
/*150 */     }                                                                                          // 0.0
/*152 */     if (ctx->device_name[AudioDevice]) {                                                       // 0.0
/*154 */         if ((r = dshow_open_device(avctx, devenum, AudioDevice)) < 0 ||                        // 0.0
/*156 */             (r = dshow_add_device(avctx, AudioDevice)) < 0) {                                  // 0.0
/*158 */             ret = r;                                                                           // 0.0
/*160 */             goto error;                                                                        // 0.0
/*162 */         }                                                                                      // 0.0
/*164 */     }                                                                                          // 0.0
/*168 */     ctx->mutex = CreateMutex(NULL, 0, NULL);                                                   // 0.0
/*170 */     if (!ctx->mutex) {                                                                         // 0.0
/*172 */         av_log(avctx, AV_LOG_ERROR, "Could not create Mutex\n");                               // 0.0
/*174 */         goto error;                                                                            // 0.0
/*176 */     }                                                                                          // 0.0
/*178 */     ctx->event[1] = CreateEvent(NULL, 1, 0, NULL);                                             // 0.0
/*180 */     if (!ctx->event[1]) {                                                                      // 0.0
/*182 */         av_log(avctx, AV_LOG_ERROR, "Could not create Event\n");                               // 0.0
/*184 */         goto error;                                                                            // 0.0
/*186 */     }                                                                                          // 0.0
/*190 */     r = IGraphBuilder_QueryInterface(graph, &IID_IMediaControl, (void **) &control);           // 0.0
/*192 */     if (r != S_OK) {                                                                           // 0.0
/*194 */         av_log(avctx, AV_LOG_ERROR, "Could not get media control.\n");                         // 0.0
/*196 */         goto error;                                                                            // 0.0
/*198 */     }                                                                                          // 0.0
/*200 */     ctx->control = control;                                                                    // 0.0
/*204 */     r = IGraphBuilder_QueryInterface(graph, &IID_IMediaEvent, (void **) &media_event);         // 0.0
/*206 */     if (r != S_OK) {                                                                           // 0.0
/*208 */         av_log(avctx, AV_LOG_ERROR, "Could not get media event.\n");                           // 0.0
/*210 */         goto error;                                                                            // 0.0
/*212 */     }                                                                                          // 0.0
/*214 */     ctx->media_event = media_event;                                                            // 0.0
/*218 */     r = IMediaEvent_GetEventHandle(media_event, (void *) &media_event_handle);                 // 0.0
/*220 */     if (r != S_OK) {                                                                           // 0.0
/*222 */         av_log(avctx, AV_LOG_ERROR, "Could not get media event handle.\n");                    // 0.0
/*224 */         goto error;                                                                            // 0.0
/*226 */     }                                                                                          // 0.0
/*228 */     proc = GetCurrentProcess();                                                                // 0.0
/*230 */     r = DuplicateHandle(proc, media_event_handle, proc, &ctx->event[0],                        // 0.0
/*232 */                         0, 0, DUPLICATE_SAME_ACCESS);                                          // 0.0
/*234 */     if (!r) {                                                                                  // 0.0
/*236 */         av_log(avctx, AV_LOG_ERROR, "Could not duplicate media event handle.\n");              // 0.0
/*238 */         goto error;                                                                            // 0.0
/*240 */     }                                                                                          // 0.0
/*244 */     r = IMediaControl_Run(control);                                                            // 0.0
/*246 */     if (r == S_FALSE) {                                                                        // 0.0
/*248 */         OAFilterState pfs;                                                                     // 0.0
/*250 */         r = IMediaControl_GetState(control, 0, &pfs);                                          // 0.0
/*252 */     }                                                                                          // 0.0
/*254 */     if (r != S_OK) {                                                                           // 0.0
/*256 */         av_log(avctx, AV_LOG_ERROR, "Could not run filter\n");                                 // 0.0
/*258 */         goto error;                                                                            // 0.0
/*260 */     }                                                                                          // 0.0
/*264 */     ret = 0;                                                                                   // 0.0
/*268 */ error:                                                                                         // 0.0
/*272 */     if (devenum)                                                                               // 0.0
/*274 */         ICreateDevEnum_Release(devenum);                                                       // 0.0
/*278 */     if (ret < 0)                                                                               // 0.0
/*280 */         dshow_read_close(avctx);                                                               // 0.0
/*284 */     return ret;                                                                                // 0.0
/*286 */ }                                                                                              // 0.0
