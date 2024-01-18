// commit message qemu@12d69ac03b (target=0, prob=0.09489155, correct=True): tests: remove irrelevant assertions from test-aio
/*0  */ static void test_source_wait_event_notifier(void)          // (15) 0.04155
/*2  */ {                                                          // (18) 0.00277
/*4  */     EventNotifierTestData data = { .n = 0, .active = 1 };  // (2) 0.05817
/*6  */     event_notifier_init(&data.e, false);                   // (14) 0.04432
/*8  */     aio_set_event_notifier(ctx, &data.e, event_ready_cb);  // (0) 0.07202
/*10 */     g_assert(g_main_context_iteration(NULL, false));       // (3) 0.0554
/*12 */     g_assert_cmpint(data.n, ==, 0);                        // (8) 0.04986
/*14 */     g_assert_cmpint(data.active, ==, 1);                   // (9) 0.04986
/*18 */     event_notifier_set(&data.e);                           // (17) 0.03878
/*20 */     g_assert(g_main_context_iteration(NULL, false));       // (4) 0.0554
/*22 */     g_assert_cmpint(data.n, ==, 1);                        // (10) 0.04986
/*24 */     g_assert_cmpint(data.active, ==, 0);                   // (11) 0.04986
/*28 */     while (g_main_context_iteration(NULL, false));         // (6) 0.04986
/*30 */     g_assert_cmpint(data.n, ==, 1);                        // (12) 0.04986
/*32 */     g_assert_cmpint(data.active, ==, 0);                   // (7) 0.04986
/*36 */     aio_set_event_notifier(ctx, &data.e, NULL);            // (1) 0.06094
/*38 */     while (g_main_context_iteration(NULL, false));         // (5) 0.04986
/*40 */     g_assert_cmpint(data.n, ==, 1);                        // (13) 0.04986
/*44 */     event_notifier_cleanup(&data.e);                       // (16) 0.04155
/*46 */ }                                                          // (19) 0.00277
