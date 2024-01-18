// commit message FFmpeg@9c3a8693a2 (target=0, prob=0.4846512, correct=True): avdevice/dshow: Remove unneeded NULL checks
/*0   */ dshow_cycle_devices(AVFormatContext *avctx, ICreateDevEnum *devenum,                        // (8) 0.04688
/*2   */                     enum dshowDeviceType devtype, IBaseFilter **pfilter)                    // (3) 0.06641
/*4   */ {                                                                                           // (20) 0.001953
/*6   */     struct dshow_ctx *ctx = avctx->priv_data;                                               // (12) 0.03516
/*8   */     IBaseFilter *device_filter = NULL;                                                      // (15) 0.02539
/*10  */     IEnumMoniker *classenum = NULL;                                                         // (14) 0.02734
/*12  */     IMoniker *m = NULL;                                                                     // (17) 0.02148
/*14  */     const char *device_name = ctx->device_name[devtype];                                    // (10) 0.03906
/*16  */     int skip = (devtype == VideoDevice) ? ctx->video_device_number                          // (9) 0.04297
/*18  */                                         : ctx->audio_device_number;                         // (1) 0.0957
/*20  */     int r;                                                                                  // (18) 0.01172
/*24  */     const GUID *device_guid[2] = { &CLSID_VideoInputDeviceCategory,                         // (6) 0.05078
/*26  */                                    &CLSID_AudioInputDeviceCategory };                       // (2) 0.08594
/*28  */     const char *devtypename = (devtype == VideoDevice) ? "video" : "audio";                 // (7) 0.05078
/*32  */     r = ICreateDevEnum_CreateClassEnumerator(devenum, device_guid[devtype],                 // (5) 0.05664
/*34  */                                              (IEnumMoniker **) &classenum, 0);              // (0) 0.1133
/*36  */     if (r != S_OK) {                                                                        // (16) 0.02344
/*38  */         av_log(avctx, AV_LOG_ERROR, "Could not enumerate %s devices.\n",                    // (4) 0.0625
/*40  */                devtypename);                                                                // (11) 0.03711
/*42  */         return AVERROR(EIO);                                                                // (13) 0.0293
/*44  */     }                                                                                       // (19) 0.007813
/*48  */     while (!device_filter && IEnumMoniker_Next(classenum, 1, &m, NULL) == S_OK) {           // 0.0
/*50  */         IPropertyBag *bag = NULL;                                                           // 0.0
/*52  */         char *buf = NULL;                                                                   // 0.0
/*54  */         VARIANT var;                                                                        // 0.0
/*58  */         r = IMoniker_BindToStorage(m, 0, 0, &IID_IPropertyBag, (void *) &bag);              // 0.0
/*60  */         if (r != S_OK)                                                                      // 0.0
/*62  */             goto fail1;                                                                     // 0.0
/*66  */         var.vt = VT_BSTR;                                                                   // 0.0
/*68  */         r = IPropertyBag_Read(bag, L"FriendlyName", &var, NULL);                            // 0.0
/*70  */         if (r != S_OK)                                                                      // 0.0
/*72  */             goto fail1;                                                                     // 0.0
/*76  */         buf = dup_wchar_to_utf8(var.bstrVal);                                               // 0.0
/*80  */         if (pfilter) {                                                                      // 0.0
/*82  */             if (strcmp(device_name, buf))                                                   // 0.0
/*84  */                 goto fail1;                                                                 // 0.0
/*88  */             if (!skip--)                                                                    // 0.0
/*90  */                 IMoniker_BindToObject(m, 0, 0, &IID_IBaseFilter, (void *) &device_filter);  // 0.0
/*92  */         } else {                                                                            // 0.0
/*94  */             av_log(avctx, AV_LOG_INFO, " \"%s\"\n", buf);                                   // 0.0
/*96  */         }                                                                                   // 0.0
/*100 */ fail1:                                                                                      // 0.0
/*102 */         if (buf)                                                                            // 0.0
/*104 */             av_free(buf);                                                                   // 0.0
/*106 */         if (bag)                                                                            // 0.0
/*108 */             IPropertyBag_Release(bag);                                                      // 0.0
/*110 */         IMoniker_Release(m);                                                                // 0.0
/*112 */     }                                                                                       // 0.0
/*116 */     IEnumMoniker_Release(classenum);                                                        // 0.0
/*120 */     if (pfilter) {                                                                          // 0.0
/*122 */         if (!device_filter) {                                                               // 0.0
/*124 */             av_log(avctx, AV_LOG_ERROR, "Could not find %s device.\n",                      // 0.0
/*126 */                    devtypename);                                                            // 0.0
/*128 */             return AVERROR(EIO);                                                            // 0.0
/*130 */         }                                                                                   // 0.0
/*132 */         *pfilter = device_filter;                                                           // 0.0
/*134 */     }                                                                                       // 0.0
/*138 */     return 0;                                                                               // 0.0
/*140 */ }                                                                                           // 0.0
