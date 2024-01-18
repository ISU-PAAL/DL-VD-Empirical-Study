// commit message FFmpeg@183216b218 (target=1, prob=0.48464748, correct=False): frame_thread_encoder: make 'exit' member atomic.
/*0   */ static void * attribute_align_arg worker(void *v){                       // (15) 0.02734
/*2   */     AVCodecContext *avctx = v;                                           // (17) 0.02539
/*4   */     ThreadContext *c = avctx->internal->frame_thread_encoder;            // (9) 0.03906
/*6   */     AVPacket *pkt = NULL;                                                // (18) 0.02344
/*10  */     while(!c->exit){                                                     // (21) 0.01953
/*12  */         int got_packet, ret;                                             // (13) 0.0293
/*14  */         AVFrame *frame;                                                  // (19) 0.02344
/*16  */         Task task;                                                       // (22) 0.01953
/*20  */         if(!pkt) pkt= av_mallocz(sizeof(*pkt));                          // (5) 0.05469
/*22  */         if(!pkt) continue;                                               // (14) 0.0293
/*24  */         av_init_packet(pkt);                                             // (11) 0.0332
/*28  */         pthread_mutex_lock(&c->task_fifo_mutex);                         // (7) 0.04883
/*30  */         while (av_fifo_size(c->task_fifo) <= 0 || c->exit) {             // (4) 0.06055
/*32  */             if(c->exit){                                                 // (12) 0.0332
/*34  */                 pthread_mutex_unlock(&c->task_fifo_mutex);               // (1) 0.06641
/*36  */                 goto end;                                                // (10) 0.03516
/*38  */             }                                                            // (20) 0.02344
/*40  */             pthread_cond_wait(&c->task_fifo_cond, &c->task_fifo_mutex);  // (0) 0.07422
/*42  */         }                                                                // (23) 0.01562
/*44  */         av_fifo_generic_read(c->task_fifo, &task, sizeof(task), NULL);   // (3) 0.0625
/*46  */         pthread_mutex_unlock(&c->task_fifo_mutex);                       // (6) 0.05078
/*48  */         frame = task.indata;                                             // (16) 0.02734
/*52  */         ret = avcodec_encode_video2(avctx, pkt, frame, &got_packet);     // (2) 0.06445
/*54  */         pthread_mutex_lock(&c->buffer_mutex);                            // (8) 0.04297
/*56  */         av_frame_unref(frame);                                           // 0.0
/*58  */         pthread_mutex_unlock(&c->buffer_mutex);                          // 0.0
/*60  */         av_frame_free(&frame);                                           // 0.0
/*62  */         if(got_packet) {                                                 // 0.0
/*64  */             int ret2 = av_dup_packet(pkt);                               // 0.0
/*66  */             if (ret >= 0 && ret2 < 0)                                    // 0.0
/*68  */                 ret = ret2;                                              // 0.0
/*70  */         } else {                                                         // 0.0
/*72  */             pkt->data = NULL;                                            // 0.0
/*74  */             pkt->size = 0;                                               // 0.0
/*76  */         }                                                                // 0.0
/*78  */         pthread_mutex_lock(&c->finished_task_mutex);                     // 0.0
/*80  */         c->finished_tasks[task.index].outdata = pkt; pkt = NULL;         // 0.0
/*82  */         c->finished_tasks[task.index].return_code = ret;                 // 0.0
/*84  */         pthread_cond_signal(&c->finished_task_cond);                     // 0.0
/*86  */         pthread_mutex_unlock(&c->finished_task_mutex);                   // 0.0
/*88  */     }                                                                    // 0.0
/*90  */ end:                                                                     // 0.0
/*92  */     av_free(pkt);                                                        // 0.0
/*94  */     pthread_mutex_lock(&c->buffer_mutex);                                // 0.0
/*96  */     avcodec_close(avctx);                                                // 0.0
/*98  */     pthread_mutex_unlock(&c->buffer_mutex);                              // 0.0
/*100 */     av_freep(&avctx);                                                    // 0.0
/*102 */     return NULL;                                                         // 0.0
/*104 */ }                                                                        // 0.0
