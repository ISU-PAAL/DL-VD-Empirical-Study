// commit message qemu@68ab47e4b4 (target=1, prob=0.13949938, correct=False): qapi: Change visit_type_FOO() to no longer return partial objects
/*0  */ static void test_validate_fail_struct_nested(TestInputVisitorData *data,                                                                                                                                               // (2) 0.0856
/*2  */                                               const void *unused)                                                                                                                                                      // (1) 0.1984
/*4  */ {                                                                                                                                                                                                                      // (9) 0.003891
/*6  */     UserDefTwo *udp = NULL;                                                                                                                                                                                            // (6) 0.04669
/*8  */     Error *err = NULL;                                                                                                                                                                                                 // (7) 0.03502
/*10 */     Visitor *v;                                                                                                                                                                                                        // (8) 0.03113
/*14 */     v = validate_test_init(data, "{ 'string0': 'string0', 'dict1': { 'string1': 'string1', 'dict2': { 'userdef1': { 'integer': 42, 'string': 'string', 'extra': [42, 23, {'foo':'bar'}] }, 'string2': 'string2'}}}");  // (0) 0.3307
/*18 */     visit_type_UserDefTwo(v, NULL, &udp, &err);                                                                                                                                                                        // (3) 0.0856
/*20 */     error_free_or_abort(&err);                                                                                                                                                                                         // (5) 0.05447
/*22 */     qapi_free_UserDefTwo(udp);                                                                                                                                                                                         // (4) 0.05837
/*24 */ }                                                                                                                                                                                                                      // (10) 0.003891