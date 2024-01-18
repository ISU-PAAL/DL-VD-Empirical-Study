// commit message qemu@aec4b054ea (target=1, prob=0.098008394, correct=False): check-qjson: Test errors from qobject_from_json()
/*0  */ static void keyword_literal(void)                                       // (25) 0.01758
/*2  */ {                                                                       // (32) 0.001953
/*4  */     QObject *obj;                                                       // (29) 0.01562
/*6  */     QBool *qbool;                                                       // (26) 0.01758
/*8  */     QObject *null;                                                      // (30) 0.01562
/*10 */     QString *str;                                                       // (31) 0.01562
/*14 */     obj = qobject_from_json("true", NULL);                              // (9) 0.03125
/*16 */     qbool = qobject_to_qbool(obj);                                      // (10) 0.03125
/*18 */     g_assert(qbool);                                                    // (21) 0.01953
/*20 */     g_assert(qbool_get_bool(qbool) == true);                            // (5) 0.03906
/*24 */     str = qobject_to_json(obj);                                         // (15) 0.02734
/*26 */     g_assert(strcmp(qstring_get_str(str), "true") == 0);                // (2) 0.04883
/*28 */     QDECREF(str);                                                       // (28) 0.01758
/*32 */     QDECREF(qbool);                                                     // (22) 0.01953
/*36 */     obj = qobject_from_json("false", NULL);                             // (11) 0.03125
/*38 */     qbool = qobject_to_qbool(obj);                                      // (12) 0.03125
/*40 */     g_assert(qbool);                                                    // (23) 0.01953
/*42 */     g_assert(qbool_get_bool(qbool) == false);                           // (4) 0.03906
/*46 */     str = qobject_to_json(obj);                                         // (14) 0.02734
/*48 */     g_assert(strcmp(qstring_get_str(str), "false") == 0);               // (3) 0.04883
/*50 */     QDECREF(str);                                                       // (27) 0.01758
/*54 */     QDECREF(qbool);                                                     // (17) 0.01953
/*58 */     qbool = qobject_to_qbool(qobject_from_jsonf("%i", false));          // (0) 0.05273
/*60 */     g_assert(qbool);                                                    // (18) 0.01953
/*62 */     g_assert(qbool_get_bool(qbool) == false);                           // (6) 0.03906
/*64 */     QDECREF(qbool);                                                     // (20) 0.01953
/*68 */     /* Test that non-zero values other than 1 get collapsed to true */  // (8) 0.03516
/*70 */     qbool = qobject_to_qbool(qobject_from_jsonf("%i", 2));              // (1) 0.05273
/*72 */     g_assert(qbool);                                                    // (24) 0.01953
/*74 */     g_assert(qbool_get_bool(qbool) == true);                            // (7) 0.03906
/*76 */     QDECREF(qbool);                                                     // (19) 0.01953
/*80 */     obj = qobject_from_json("null", NULL);                              // (13) 0.03125
/*82 */     g_assert(obj != NULL);                                              // (16) 0.02148
/*84 */     g_assert(qobject_type(obj) == QTYPE_QNULL);                         // 0.0
/*88 */     null = qnull();                                                     // 0.0
/*90 */     g_assert(null == obj);                                              // 0.0
/*94 */     qobject_decref(obj);                                                // 0.0
/*96 */     qobject_decref(null);                                               // 0.0
/*98 */ }                                                                       // 0.0
