// commit message qemu@aec4b054ea (target=1, prob=0.59074485, correct=True): check-qjson: Test errors from qobject_from_json()
/*0  */ static void simple_number(void)                                                  // (21) 0.01774
/*2  */ {                                                                                // (27) 0.002217
/*4  */     int i;                                                                       // (23) 0.0133
/*6  */     struct {                                                                     // (24) 0.01109
/*8  */         const char *encoded;                                                     // (17) 0.02882
/*10 */         int64_t decoded;                                                         // (11) 0.03104
/*12 */         int skip;                                                                // (19) 0.02217
/*14 */     } test_cases[] = {                                                           // (18) 0.02217
/*16 */         { "0", 0 },                                                              // (15) 0.02882
/*18 */         { "1234", 1234 },                                                        // (9) 0.03326
/*20 */         { "1", 1 },                                                              // (14) 0.02882
/*22 */         { "-32", -32 },                                                          // (10) 0.03104
/*24 */         { "-0", 0, .skip = 1 },                                                  // (6) 0.03991
/*26 */         { },                                                                     // (20) 0.01996
/*28 */     };                                                                           // (25) 0.008869
/*32 */     for (i = 0; test_cases[i].encoded; i++) {                                    // (4) 0.04656
/*34 */         QInt *qint;                                                              // (16) 0.02882
/*38 */         qint = qobject_to_qint(qobject_from_json(test_cases[i].encoded, NULL));  // (1) 0.07982
/*40 */         g_assert(qint);                                                          // (13) 0.03104
/*42 */         g_assert(qint_get_int(qint) == test_cases[i].decoded);                   // (2) 0.06874
/*44 */         if (test_cases[i].skip == 0) {                                           // (5) 0.04435
/*46 */             QString *str;                                                        // (8) 0.03548
/*50 */             str = qobject_to_json(QOBJECT(qint));                                // (3) 0.05987
/*52 */             g_assert(strcmp(qstring_get_str(str), test_cases[i].encoded) == 0);  // (0) 0.08647
/*54 */             QDECREF(str);                                                        // (7) 0.03769
/*56 */         }                                                                        // (22) 0.01774
/*60 */         QDECREF(qint);                                                           // (12) 0.03104
/*62 */     }                                                                            // (26) 0.008869
/*64 */ }                                                                                // (28) 0.002217
