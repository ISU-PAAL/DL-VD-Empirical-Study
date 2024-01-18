// commit message FFmpeg@f4aaf987a5 (target=1, prob=0.58029497, correct=True): frame_thread_encoder: fix handling of case where the encoder does not output a packet.
/*0   */ int ff_thread_video_encode_frame(AVCodecContext *avctx, AVPacket *pkt, const AVFrame *frame, int *got_packet_ptr){                               // (2) 0.08203
/*2   */     ThreadContext *c = avctx->internal->frame_thread_encoder;                                                                                    // (11) 0.03906
/*4   */     Task task;                                                                                                                                   // (20) 0.01176
/*6   */     int ret;                                                                                                                                     // (21) 0.01172
/*10  */     av_assert1(!*got_packet_ptr);                                                                                                                // (14) 0.0332
/*14  */     if(frame){                                                                                                                                   // (19) 0.01367
/*16  */         if(!(avctx->flags & CODEC_FLAG_INPUT_PRESERVED)){                                                                                        // (4) 0.06053
/*18  */             AVFrame *new = avcodec_alloc_frame();                                                                                                // (7) 0.04687
/*20  */             if(!new)                                                                                                                             // (16) 0.03124
/*22  */                 return AVERROR(ENOMEM);                                                                                                          // (8) 0.04687
/*24  */             pthread_mutex_lock(&c->buffer_mutex);                                                                                                // (6) 0.05077
/*26  */             ret = c->parent_avctx->get_buffer(c->parent_avctx, new);                                                                             // (3) 0.06444
/*28  */             pthread_mutex_unlock(&c->buffer_mutex);                                                                                              // (5) 0.05272
/*30  */             if(ret<0)                                                                                                                            // (15) 0.0332
/*32  */                 return ret;                                                                                                                      // (13) 0.03515
/*34  */             new->pts = frame->pts;                                                                                                               // (10) 0.04101
/*36  */             new->quality = frame->quality;                                                                                                       // (12) 0.0371
/*38  */             new->pict_type = frame->pict_type;                                                                                                   // (9) 0.04491
/*40  */             av_image_copy(new->data, new->linesize, (const uint8_t **)frame->data, frame->linesize,                                              // (1) 0.08397
/*42  */                           avctx->pix_fmt, avctx->width, avctx->height);                                                                          // (0) 0.08603
/*44  */             frame = new;                                                                                                                         // (17) 0.02929
/*46  */         }                                                                                                                                        // (18) 0.01562
/*50  */         task.index = c->task_index;                                                                                                              // 0.0
/*52  */         task.indata = (void*)frame;                                                                                                              // 0.0
/*54  */         pthread_mutex_lock(&c->task_fifo_mutex);                                                                                                 // 0.0
/*56  */         av_fifo_generic_write(c->task_fifo, &task, sizeof(task), NULL);                                                                          // 0.0
/*58  */         pthread_cond_signal(&c->task_fifo_cond);                                                                                                 // 0.0
/*60  */         pthread_mutex_unlock(&c->task_fifo_mutex);                                                                                               // 0.0
/*64  */         c->task_index = (c->task_index+1) % BUFFER_SIZE;                                                                                         // 0.0
/*68  */         if(!c->finished_tasks[c->finished_task_index].outdata && (c->task_index - c->finished_task_index) % BUFFER_SIZE <= avctx->thread_count)  // 0.0
/*70  */             return 0;                                                                                                                            // 0.0
/*72  */     }                                                                                                                                            // 0.0
/*76  */     if(c->task_index == c->finished_task_index)                                                                                                  // 0.0
/*78  */         return 0;                                                                                                                                // 0.0
/*82  */     pthread_mutex_lock(&c->finished_task_mutex);                                                                                                 // 0.0
/*84  */     while (!c->finished_tasks[c->finished_task_index].outdata) {                                                                                 // 0.0
/*86  */         pthread_cond_wait(&c->finished_task_cond, &c->finished_task_mutex);                                                                      // 0.0
/*88  */     }                                                                                                                                            // 0.0
/*90  */     task = c->finished_tasks[c->finished_task_index];                                                                                            // 0.0
/*92  */     *pkt = *(AVPacket*)(task.outdata);                                                                                                           // 0.0
/*94  */     av_freep(&c->finished_tasks[c->finished_task_index].outdata);                                                                                // 0.0
/*96  */     c->finished_task_index = (c->finished_task_index+1) % BUFFER_SIZE;                                                                           // 0.0
/*98  */     pthread_mutex_unlock(&c->finished_task_mutex);                                                                                               // 0.0
/*102 */     *got_packet_ptr = 1;                                                                                                                         // 0.0
/*106 */     return task.return_code;                                                                                                                     // 0.0
/*108 */ }                                                                                                                                                // 0.0
