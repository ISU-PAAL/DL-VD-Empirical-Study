// commit message qemu@0920a17199 (target=1, prob=0.8294692, correct=True): qapi: Share test_init code in test-qmp-input*
/*0  */ static Visitor *validate_test_init_raw(TestInputVisitorData *data,  // (2) 0.1034
/*2  */                                        const char *json_string)     // (0) 0.2217
/*4  */ {                                                                   // (10) 0.004926
/*6  */     Visitor *v;                                                     // (8) 0.03941
/*10 */     data->obj = qobject_from_json(json_string);                     // (4) 0.08867
/*12 */     g_assert(data->obj != NULL);                                    // (6) 0.06404
/*16 */     data->qiv = qmp_input_visitor_new_strict(data->obj);            // (1) 0.1232
/*18 */     g_assert(data->qiv != NULL);                                    // (5) 0.06897
/*22 */     v = qmp_input_get_visitor(data->qiv);                           // (3) 0.09852
/*24 */     g_assert(v != NULL);                                            // (7) 0.05419
/*28 */     return v;                                                       // (9) 0.02956
/*30 */ }                                                                   // (11) 0.004926
