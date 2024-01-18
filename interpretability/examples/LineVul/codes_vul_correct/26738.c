// commit message qemu@fedf0d35aa (target=1, prob=0.75808555, correct=True): ui: Use g_new() & friends where that makes obvious sense
/*0  */ VncJob *vnc_job_new(VncState *vs)             // (1) 0.156
/*2  */ {                                             // (7) 0.009174
/*4  */     VncJob *job = g_malloc0(sizeof(VncJob));  // (0) 0.2018
/*8  */     job->vs = vs;                             // (5) 0.08257
/*10 */     vnc_lock_queue(queue);                    // (4) 0.1101
/*12 */     QLIST_INIT(&job->rectangles);             // (2) 0.1284
/*14 */     vnc_unlock_queue(queue);                  // (3) 0.1193
/*16 */     return job;                               // (6) 0.05505
/*18 */ }                                             // (8) 0.009174
