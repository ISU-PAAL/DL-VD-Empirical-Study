// commit message qemu@363e13f86e (target=0, prob=0.7848524, correct=False): tests: Don't check qobject_type() before qobject_to_qstring()
/*0  */ static void vararg_string(void)                                              // (13) 0.02875
/*2  */ {                                                                            // (20) 0.003195
/*4  */     int i;                                                                   // (16) 0.01917
/*6  */     struct {                                                                 // (17) 0.01597
/*8  */         const char *decoded;                                                 // (9) 0.04153
/*10 */     } test_cases[] = {                                                       // (12) 0.03195
/*12 */         { "hello world" },                                                   // (8) 0.04153
/*14 */         { "the quick brown fox jumped over the fence" },                     // (4) 0.0607
/*16 */         {}                                                                   // (14) 0.02556
/*18 */     };                                                                       // (19) 0.01278
/*22 */     for (i = 0; test_cases[i].decoded; i++) {                                // (3) 0.06709
/*24 */         QObject *obj;                                                        // (10) 0.03834
/*26 */         QString *str;                                                        // (11) 0.03834
/*30 */         obj = qobject_from_jsonf("%s", test_cases[i].decoded);               // (1) 0.09265
/*34 */         g_assert(obj != NULL);                                               // (6) 0.04792
/*36 */         g_assert(qobject_type(obj) == QTYPE_QSTRING);                        // (2) 0.08307
/*38 */                                                                              // (15) 0.02556
/*40 */         str = qobject_to_qstring(obj);                                       // (5) 0.0607
/*42 */         g_assert(strcmp(qstring_get_str(str), test_cases[i].decoded) == 0);  // (0) 0.1118
/*46 */         QDECREF(str);                                                        // (7) 0.04153
/*48 */     }                                                                        // (18) 0.01278
/*50 */ }                                                                            // (21) 0.003195
