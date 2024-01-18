// commit message FFmpeg@220b24c7c9 (target=1, prob=0.29232103, correct=False): lavc: remove libschroedinger encoding and decoding wrappers
/*0 */ void ff_schro_queue_free(FFSchroQueue *queue, void (*free_func)(void *))  // (0) 0.3714
/*2 */ {                                                                         // (3) 0.01429
/*4 */     while (queue->p_head)                                                 // (2) 0.1571
/*6 */         free_func(ff_schro_queue_pop(queue));                             // (1) 0.3143
/*8 */ }                                                                         // (4) 0.01429
