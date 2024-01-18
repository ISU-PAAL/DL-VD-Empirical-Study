// commit message qemu@ddf2190896 (target=0, prob=0.06418423, correct=True): qapi: Unbox base members
/*0  */ static void test_dealloc_types(void)                    // (20) 0.02632
/*2  */ {                                                       // (21) 0.002392
/*4  */     UserDefOne *ud1test, *ud1a, *ud1b;                  // (2) 0.05024
/*6  */     UserDefOneList *ud1list;                            // (19) 0.02871
/*10 */     ud1test = g_malloc0(sizeof(UserDefOne));            // (3) 0.05024
/*12 */     ud1test->base = g_new0(UserDefZero, 1);             // (4) 0.05024
/*14 */     ud1test->base->integer = 42;                        // (16) 0.03349
/*16 */     ud1test->string = g_strdup("hi there 42");          // (9) 0.04785
/*20 */     qapi_free_UserDefOne(ud1test);                      // (14) 0.03828
/*24 */     ud1a = g_malloc0(sizeof(UserDefOne));               // (5) 0.05024
/*26 */     ud1a->base = g_new0(UserDefZero, 1);                // (6) 0.05024
/*28 */     ud1a->base->integer = 43;                           // (17) 0.03349
/*30 */     ud1a->string = g_strdup("hi there 43");             // (10) 0.04785
/*34 */     ud1b = g_malloc0(sizeof(UserDefOne));               // (7) 0.05024
/*36 */     ud1b->base = g_new0(UserDefZero, 1);                // (8) 0.05024
/*38 */     ud1b->base->integer = 44;                           // (18) 0.03349
/*40 */     ud1b->string = g_strdup("hi there 44");             // (11) 0.04785
/*44 */     ud1list = g_malloc0(sizeof(UserDefOneList));        // (1) 0.05263
/*46 */     ud1list->value = ud1a;                              // (15) 0.03589
/*48 */     ud1list->next = g_malloc0(sizeof(UserDefOneList));  // (0) 0.05742
/*50 */     ud1list->next->value = ud1b;                        // (12) 0.04067
/*54 */     qapi_free_UserDefOneList(ud1list);                  // (13) 0.04067
/*56 */ }                                                       // (22) 0.002392
