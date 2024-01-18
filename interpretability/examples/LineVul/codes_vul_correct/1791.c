// commit message FFmpeg@220b24c7c9 (target=1, prob=0.8644622, correct=True): lavc: remove libschroedinger encoding and decoding wrappers
/*0  */ int ff_schro_queue_push_back(FFSchroQueue *queue, void *p_data)            // (1) 0.1323
/*2  */ {                                                                          // (12) 0.005291
/*4  */     FFSchroQueueElement *p_new = av_mallocz(sizeof(FFSchroQueueElement));  // (0) 0.1534
/*8  */     if (!p_new)                                                            // (8) 0.04762
/*10 */         return -1;                                                         // (7) 0.0582
/*14 */     p_new->data = p_data;                                                  // (4) 0.06878
/*18 */     if (!queue->p_head)                                                    // (6) 0.0582
/*20 */         queue->p_head = p_new;                                             // (3) 0.08995
/*22 */     else                                                                   // (11) 0.02116
/*24 */         queue->p_tail->next = p_new;                                       // (2) 0.1005
/*26 */     queue->p_tail = p_new;                                                 // (5) 0.06878
/*30 */     ++queue->size;                                                         // (9) 0.04233
/*32 */     return 0;                                                              // (10) 0.03175
/*34 */ }                                                                          // (13) 0.005291
