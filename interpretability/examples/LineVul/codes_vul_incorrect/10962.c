// commit message FFmpeg@27bcf55f45 (target=1, prob=0.4991803, correct=False): vsrc_buffer: add flags param to av_vsrc_buffer_add_video_buffer_ref
/*0   */ int av_vsrc_buffer_add_video_buffer_ref(AVFilterContext *buffer_filter, AVFilterBufferRef *picref)  // (4) 0.0625
/*2   */ {                                                                                                   // (20) 0.001953
/*4   */     BufferSourceContext *c = buffer_filter->priv;                                                   // (12) 0.0293
/*6   */     AVFilterLink *outlink = buffer_filter->outputs[0];                                              // (11) 0.03711
/*8   */     int ret;                                                                                        // (18) 0.01172
/*12  */     if (c->picref) {                                                                                // (17) 0.02148
/*14  */         av_log(buffer_filter, AV_LOG_ERROR,                                                         // (10) 0.04102
/*16  */                "Buffering several frames is not supported. "                                        // (8) 0.04687
/*18  */                "Please consume all available frames before adding a new one.\n"                     // (5) 0.05664
/*20  */             );                                                                                      // (16) 0.02344
/*22  */         //return -1;                                                                                // (15) 0.02344
/*24  */     }                                                                                               // (19) 0.007813
/*28  */     if (picref->video->w != c->w || picref->video->h != c->h || picref->format != c->pix_fmt) {     // (3) 0.08008
/*30  */         AVFilterContext *scale = buffer_filter->outputs[0]->dst;                                    // (6) 0.05078
/*32  */         AVFilterLink *link;                                                                         // (14) 0.02539
/*34  */         char scale_param[1024];                                                                     // (13) 0.02734
/*38  */         av_log(buffer_filter, AV_LOG_INFO,                                                          // (9) 0.04102
/*40  */                "Buffer video input changed from size:%dx%d fmt:%s to size:%dx%d fmt:%s\n",          // (1) 0.08594
/*42  */                c->w, c->h, av_pix_fmt_descriptors[c->pix_fmt].name,                                 // (2) 0.08594
/*44  */                picref->video->w, picref->video->h, av_pix_fmt_descriptors[picref->format].name);    // (0) 0.0918
/*48  */         if (!scale || strcmp(scale->filter->name, "scale")) {                                       // (7) 0.04687
/*50  */             AVFilter *f = avfilter_get_by_name("scale");                                            // 0.0
/*54  */             av_log(buffer_filter, AV_LOG_INFO, "Inserting scaler filter\n");                        // 0.0
/*56  */             if ((ret = avfilter_open(&scale, f, "Input equalizer")) < 0)                            // 0.0
/*58  */                 return ret;                                                                         // 0.0
/*62  */             snprintf(scale_param, sizeof(scale_param)-1, "%d:%d:%s", c->w, c->h, c->sws_param);     // 0.0
/*64  */             if ((ret = avfilter_init_filter(scale, scale_param, NULL)) < 0) {                       // 0.0
/*66  */                 avfilter_free(scale);                                                               // 0.0
/*68  */                 return ret;                                                                         // 0.0
/*70  */             }                                                                                       // 0.0
/*74  */             if ((ret = avfilter_insert_filter(buffer_filter->outputs[0], scale, 0, 0)) < 0) {       // 0.0
/*76  */                 avfilter_free(scale);                                                               // 0.0
/*78  */                 return ret;                                                                         // 0.0
/*80  */             }                                                                                       // 0.0
/*82  */             scale->outputs[0]->time_base = scale->inputs[0]->time_base;                             // 0.0
/*86  */             scale->outputs[0]->format= c->pix_fmt;                                                  // 0.0
/*88  */         } else if (!strcmp(scale->filter->name, "scale")) {                                         // 0.0
/*90  */             snprintf(scale_param, sizeof(scale_param)-1, "%d:%d:%s",                                // 0.0
/*92  */                      scale->outputs[0]->w, scale->outputs[0]->h, c->sws_param);                     // 0.0
/*94  */             scale->filter->init(scale, scale_param, NULL);                                          // 0.0
/*96  */         }                                                                                           // 0.0
/*100 */         c->pix_fmt = scale->inputs[0]->format = picref->format;                                     // 0.0
/*102 */         c->w       = scale->inputs[0]->w      = picref->video->w;                                   // 0.0
/*104 */         c->h       = scale->inputs[0]->h      = picref->video->h;                                   // 0.0
/*108 */         link = scale->outputs[0];                                                                   // 0.0
/*110 */         if ((ret =  link->srcpad->config_props(link)) < 0)                                          // 0.0
/*112 */             return ret;                                                                             // 0.0
/*114 */     }                                                                                               // 0.0
/*118 */     c->picref = avfilter_get_video_buffer(outlink, AV_PERM_WRITE,                                   // 0.0
/*120 */                                           picref->video->w, picref->video->h);                      // 0.0
/*122 */     av_image_copy(c->picref->data, c->picref->linesize,                                             // 0.0
/*124 */                   picref->data, picref->linesize,                                                   // 0.0
/*126 */                   picref->format, picref->video->w, picref->video->h);                              // 0.0
/*128 */     avfilter_copy_buffer_ref_props(c->picref, picref);                                              // 0.0
/*132 */     return 0;                                                                                       // 0.0
/*134 */ }                                                                                                   // 0.0
