// commit message qemu@0fb6395c0c (target=0, prob=0.10573353, correct=True): Use error_is_set() only when necessary (again)
/*0  */ static void test_validate_fail_union_flat(TestInputVisitorData *data,                   // (3) 0.1019
/*2  */                                           const void *unused)                           // (0) 0.2282
/*4  */ {                                                                                       // (9) 0.004854
/*6  */     UserDefFlatUnion *tmp = NULL;                                                       // (6) 0.06311
/*8  */     Error *errp = NULL;                                                                 // (7) 0.04854
/*10 */     Visitor *v;                                                                         // (8) 0.03883
/*14 */     v = validate_test_init(data, "{ 'string': 'c', 'integer': 41, 'boolean': true }");  // (1) 0.1553
/*18 */     visit_type_UserDefFlatUnion(v, &tmp, NULL, &errp);                                  // (2) 0.1165
/*20 */     g_assert(error_is_set(&errp));                                                      // (5) 0.07767
/*22 */     qapi_free_UserDefFlatUnion(tmp);                                                    // (4) 0.07767
/*24 */ }                                                                                       // (10) 0.004854
