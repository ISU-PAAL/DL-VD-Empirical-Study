// commit message qemu@a0067da157 (target=1, prob=0.9992398, correct=True): qapi: check invalid arguments on no-args commands
/*0  */ static void test_dispatch_cmd_failure(void)                                     // (9) 0.04106
/*2  */ {                                                                               // (19) 0.002933
/*4  */     QDict *req = qdict_new();                                                   // (8) 0.04106
/*7  */     QObject *resp;                                                              // (18) 0.02346
/*11 */     qdict_put_obj(req, "execute", QOBJECT(qstring_from_str("user_def_cmd2")));  // (0) 0.09971
/*15 */     resp = qmp_dispatch(QOBJECT(req));                                          // (6) 0.04985
/*17 */     assert(resp != NULL);                                                       // (15) 0.02639
/*19 */     assert(qdict_haskey(qobject_to_qdict(resp), "error"));                      // (2) 0.07331
/*23 */     qobject_decref(resp);                                                       // (11) 0.03226
/*25 */     QDECREF(req);                                                               // (16) 0.02639
/*29 */     /* check that with extra arguments it throws an error */                    // (10) 0.04106
/*31 */     req = qdict_new();                                                          // (13) 0.02933
/*33 */     qdict_put(args, "a", qint_from_int(66));                                    // (4) 0.06452
/*35 */     qdict_put(req, "arguments", args);                                          // (7) 0.04692
/*39 */     qdict_put_obj(req, "execute", QOBJECT(qstring_from_str("user_def_cmd")));   // (1) 0.09677
/*43 */     resp = qmp_dispatch(QOBJECT(req));                                          // (5) 0.04985
/*45 */     assert(resp != NULL);                                                       // (17) 0.02639
/*47 */     assert(qdict_haskey(qobject_to_qdict(resp), "error"));                      // (3) 0.07331
/*51 */     qobject_decref(resp);                                                       // (12) 0.03226
/*53 */     QDECREF(req);                                                               // (14) 0.02639
/*55 */ }                                                                               // (20) 0.002933
