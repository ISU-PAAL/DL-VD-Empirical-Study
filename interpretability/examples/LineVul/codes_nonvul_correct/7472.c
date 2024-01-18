// commit message FFmpeg@ae21776207 (target=0, prob=0.36096802, correct=True): lavfi: add missing check in avfilter_filter_samples()
/*0  */ void avfilter_filter_samples(AVFilterLink *link, AVFilterBufferRef *samplesref)            // (8) 0.04688
/*2  */ {                                                                                          // (17) 0.001953
/*4  */     void (*filter_samples)(AVFilterLink *, AVFilterBufferRef *);                           // (12) 0.04102
/*6  */     AVFilterPad *dst = link->dstpad;                                                       // (14) 0.03125
/*8  */     int i;                                                                                 // (16) 0.01172
/*12 */     FF_DPRINTF_START(NULL, filter_samples); ff_dlog_link(NULL, link, 1);                   // (4) 0.06445
/*16 */     if (!(filter_samples = dst->filter_samples))                                           // (13) 0.03516
/*18 */         filter_samples = avfilter_default_filter_samples;                                  // (9) 0.04297
/*22 */     /* prepare to copy the samples if the buffer has insufficient permissions */           // (15) 0.03125
/*24 */     if ((dst->min_perms & samplesref->perms) != dst->min_perms ||                          // (7) 0.05273
/*26 */         dst->rej_perms & samplesref->perms) {                                              // (11) 0.04297
/*30 */         av_log(link->dst, AV_LOG_DEBUG,                                                    // (10) 0.04297
/*32 */                "Copying audio data in avfilter (have perms %x, need %x, reject %x)\n",     // (2) 0.07617
/*34 */                samplesref->perms, link->dstpad->min_perms, link->dstpad->rej_perms);       // (1) 0.08398
/*38 */         link->cur_buf = avfilter_default_get_audio_buffer(link, dst->min_perms,            // (5) 0.06445
/*40 */                                                           samplesref->audio->nb_samples);  // (0) 0.1309
/*42 */         link->cur_buf->pts                = samplesref->pts;                               // (3) 0.07227
/*44 */         link->cur_buf->audio->sample_rate = samplesref->audio->sample_rate;                // (6) 0.05469
/*48 */         /* Copy actual data into new samples buffer */                                     // 0.0
/*50 */         for (i = 0; samplesref->data[i]; i++)                                              // 0.0
/*52 */             memcpy(link->cur_buf->data[i], samplesref->data[i], samplesref->linesize[0]);  // 0.0
/*56 */         avfilter_unref_buffer(samplesref);                                                 // 0.0
/*58 */     } else                                                                                 // 0.0
/*60 */         link->cur_buf = samplesref;                                                        // 0.0
/*64 */     filter_samples(link, link->cur_buf);                                                   // 0.0
/*66 */ }                                                                                          // 0.0
