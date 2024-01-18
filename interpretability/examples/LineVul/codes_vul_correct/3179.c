// commit message qemu@aec4b054ea (target=1, prob=0.53098524, correct=True): check-qjson: Test errors from qobject_from_json()
/*0   */ static void simple_whitespace(void)                                           // (14) 0.01953
/*2   */ {                                                                             // (21) 0.001953
/*4   */     int i;                                                                    // (19) 0.01172
/*6   */     struct {                                                                  // (20) 0.009766
/*8   */         const char *encoded;                                                  // (13) 0.02539
/*10  */         LiteralQObject decoded;                                               // (12) 0.02734
/*12  */     } test_cases[] = {                                                        // (15) 0.01953
/*14  */         {                                                                     // (18) 0.01562
/*16  */             .encoded = " [ 43 , 42 ]",                                        // (10) 0.04297
/*18  */             .decoded = QLIT_QLIST(((LiteralQObject[]){                        // (7) 0.06055
/*20  */                         QLIT_QINT(43),                                        // (4) 0.0625
/*22  */                         QLIT_QINT(42),                                        // (6) 0.0625
/*24  */                         { }                                                   // (9) 0.04883
/*26  */                     })),                                                      // (11) 0.04102
/*28  */         },                                                                    // (16) 0.01562
/*30  */         {                                                                     // (17) 0.01562
/*32  */             .encoded = " [ 43 , { 'h' : 'b' }, [ ], 42 ]",                    // (3) 0.06445
/*34  */             .decoded = QLIT_QLIST(((LiteralQObject[]){                        // (8) 0.06055
/*36  */                         QLIT_QINT(43),                                        // (5) 0.0625
/*38  */                         QLIT_QDICT(((LiteralQDictEntry[]){                    // (1) 0.08203
/*40  */                                     { "h", QLIT_QSTR("b") },                  // (0) 0.0957
/*42  */                                     { }})),                                   // (2) 0.07617
/*44  */                         QLIT_QLIST(((LiteralQObject[]){                       // 0.0
/*46  */                                     { }})),                                   // 0.0
/*48  */                         QLIT_QINT(42),                                        // 0.0
/*50  */                         { }                                                   // 0.0
/*52  */                     })),                                                      // 0.0
/*54  */         },                                                                    // 0.0
/*56  */         {                                                                     // 0.0
/*58  */             .encoded = " [ 43 , { 'h' : 'b' , 'a' : 32 }, [ ], 42 ]",         // 0.0
/*60  */             .decoded = QLIT_QLIST(((LiteralQObject[]){                        // 0.0
/*62  */                         QLIT_QINT(43),                                        // 0.0
/*64  */                         QLIT_QDICT(((LiteralQDictEntry[]){                    // 0.0
/*66  */                                     { "h", QLIT_QSTR("b") },                  // 0.0
/*68  */                                     { "a", QLIT_QINT(32) },                   // 0.0
/*70  */                                     { }})),                                   // 0.0
/*72  */                         QLIT_QLIST(((LiteralQObject[]){                       // 0.0
/*74  */                                     { }})),                                   // 0.0
/*76  */                         QLIT_QINT(42),                                        // 0.0
/*78  */                         { }                                                   // 0.0
/*80  */                     })),                                                      // 0.0
/*82  */         },                                                                    // 0.0
/*84  */         { }                                                                   // 0.0
/*86  */     };                                                                        // 0.0
/*90  */     for (i = 0; test_cases[i].encoded; i++) {                                 // 0.0
/*92  */         QObject *obj;                                                         // 0.0
/*94  */         QString *str;                                                         // 0.0
/*98  */         obj = qobject_from_json(test_cases[i].encoded, NULL);                 // 0.0
/*100 */         g_assert(compare_litqobj_to_qobj(&test_cases[i].decoded, obj) == 1);  // 0.0
/*104 */         str = qobject_to_json(obj);                                           // 0.0
/*106 */         qobject_decref(obj);                                                  // 0.0
/*110 */         obj = qobject_from_json(qstring_get_str(str), NULL);                  // 0.0
/*112 */         g_assert(compare_litqobj_to_qobj(&test_cases[i].decoded, obj) == 1);  // 0.0
/*116 */         qobject_decref(obj);                                                  // 0.0
/*118 */         QDECREF(str);                                                         // 0.0
/*120 */     }                                                                         // 0.0
/*122 */ }                                                                             // 0.0
