// commit message qemu@b3db211f3c (target=0, prob=0.005638208, correct=True): qapi: rename *qmp-*-visitor* to *qobject-*-visitor*
/*0  */ static void test_visitor_in_native_list_int32(TestInputVisitorData *data,  // (2) 0.1509
/*2  */                                               const void *unused)          // (1) 0.3208
/*4  */ {                                                                          // (4) 0.006289
/*6  */     test_native_list_integer_helper(data, unused,                          // (3) 0.1132
/*8  */                                     USER_DEF_NATIVE_LIST_UNION_KIND_S32);  // (0) 0.3396
/*10 */ }                                                                          // (5) 0.006289
