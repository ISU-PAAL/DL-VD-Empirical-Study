// commit message qemu@937470bb54 (target=1, prob=0.5746722, correct=True): io: stop incrementing reference in qio_task_get_source
/*0  */ static void test_task_complete(void)                       // (9) 0.04785
/*2  */ {                                                          // (14) 0.004785
/*4  */     QIOTask *task;                                         // (10) 0.04785
/*6  */     Object *obj = object_new(TYPE_DUMMY);                  // (1) 0.08134
/*8  */     Object *src;                                           // (13) 0.03349
/*10 */     struct TestTaskData data = { NULL, NULL, false };      // (2) 0.07656
/*14 */     task = qio_task_new(obj, task_callback, &data, NULL);  // (0) 0.11
/*16 */     src = qio_task_get_source(task);                       // (3) 0.07656
/*20 */     qio_task_complete(task);                               // (7) 0.05742
/*24 */     g_assert(obj == src);                                  // (8) 0.05263
/*28 */     object_unref(obj);                                     // (11) 0.04785
/*30 */     object_unref(src);                                     // (12) 0.04785
/*34 */     g_assert(data.source == obj);                          // (5) 0.0622
/*36 */     g_assert(data.err == NULL);                            // (6) 0.0622
/*38 */     g_assert(data.freed == false);                         // (4) 0.06699
/*40 */ }                                                          // (15) 0.004785
