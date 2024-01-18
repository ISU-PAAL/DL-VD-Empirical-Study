// commit message qemu@b3db211f3c (target=0, prob=0.008102797, correct=True): qapi: rename *qmp-*-visitor* to *qobject-*-visitor*
/*0 */ static Visitor *visitor_input_test_init_raw(TestInputVisitorData *data,  // (1) 0.217
/*2 */                                             const char *json_string)     // (0) 0.4717
/*4 */ {                                                                        // (3) 0.009434
/*6 */     return visitor_input_test_init_internal(data, json_string, NULL);    // (2) 0.2075
/*8 */ }                                                                        // (4) 0.009434
