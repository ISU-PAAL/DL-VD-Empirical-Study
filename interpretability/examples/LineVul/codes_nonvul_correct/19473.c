// commit message qemu@b3db211f3c (target=0, prob=0.0054920944, correct=True): qapi: rename *qmp-*-visitor* to *qobject-*-visitor*
/*0 */ static void test_visitor_out_native_list_uint16(TestOutputVisitorData *data,  // (2) 0.2
/*2 */                                                 const void *unused)           // (0) 0.4417
/*4 */ {                                                                             // (3) 0.008333
/*6 */     test_native_list(data, unused, USER_DEF_NATIVE_LIST_UNION_KIND_U16);      // (1) 0.2667
/*8 */ }                                                                             // (4) 0.008333
