// commit message qemu@fedf0d35aa (target=1, prob=0.49698377, correct=False): ui: Use g_new() & friends where that makes obvious sense
/*0  */ int vnc_job_add_rect(VncJob *job, int x, int y, int w, int h)  // (0) 0.1677
/*2  */ {                                                              // (10) 0.005988
/*4  */     VncRectEntry *entry = g_malloc0(sizeof(VncRectEntry));     // (1) 0.1437
/*8  */     entry->rect.x = x;                                         // (5) 0.06587
/*10 */     entry->rect.y = y;                                         // (6) 0.06587
/*12 */     entry->rect.w = w;                                         // (7) 0.06587
/*14 */     entry->rect.h = h;                                         // (8) 0.06587
/*18 */     vnc_lock_queue(queue);                                     // (4) 0.07186
/*20 */     QLIST_INSERT_HEAD(&job->rectangles, entry, next);          // (2) 0.1198
/*22 */     vnc_unlock_queue(queue);                                   // (3) 0.07784
/*24 */     return 1;                                                  // (9) 0.03593
/*26 */ }                                                              // (11) 0.005988
