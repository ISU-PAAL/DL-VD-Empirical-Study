// commit message qemu@ff9d38963e (target=0, prob=0.2611707, correct=True): check-qdict: Simplify qdict_crumple_test_recursive()
/*0   */ static void qdict_crumple_test_recursive(void)                            // (15) 0.03125
/*2   */ {                                                                         // (20) 0.001953
/*4   */     QDict *src, *dst, *rule, *vnc, *acl, *listen;                         // (9) 0.05273
/*6   */     QObject *child, *res;                                                 // (17) 0.02148
/*8   */     QList *rules;                                                         // (19) 0.01562
/*12  */     src = qdict_new();                                                    // (18) 0.01953
/*14  */     qdict_put(src, "vnc.listen.addr", qstring_from_str("127.0.0.1"));     // (0) 0.06836
/*16  */     qdict_put(src, "vnc.listen.port", qstring_from_str("5901"));          // (6) 0.05859
/*18  */     qdict_put(src, "vnc.acl.rules.0.match", qstring_from_str("fred"));    // (3) 0.0625
/*20  */     qdict_put(src, "vnc.acl.rules.0.policy", qstring_from_str("allow"));  // (4) 0.0625
/*22  */     qdict_put(src, "vnc.acl.rules.1.match", qstring_from_str("bob"));     // (1) 0.06445
/*24  */     qdict_put(src, "vnc.acl.rules.1.policy", qstring_from_str("deny"));   // (2) 0.06445
/*26  */     qdict_put(src, "vnc.acl.default", qstring_from_str("deny"));          // (7) 0.05664
/*28  */     qdict_put(src, "vnc.acl..name", qstring_from_str("acl0"));            // (8) 0.05664
/*30  */     qdict_put(src, "vnc.acl.rule..name", qstring_from_str("acl0"));       // (5) 0.06055
/*34  */     res = qdict_crumple(src, &error_abort);                               // (13) 0.03906
/*38  */     g_assert_cmpint(qobject_type(res), ==, QTYPE_QDICT);                  // (10) 0.05078
/*42  */     dst = qobject_to_qdict(res);                                          // (16) 0.0293
/*46  */     g_assert_cmpint(qdict_size(dst), ==, 1);                              // (12) 0.04297
/*50  */     child = qdict_get(dst, "vnc");                                        // (14) 0.0332
/*52  */     g_assert_cmpint(qobject_type(child), ==, QTYPE_QDICT);                // (11) 0.05078
/*54  */     vnc = qobject_to_qdict(child);                                        // 0.0
/*58  */     child = qdict_get(vnc, "listen");                                     // 0.0
/*60  */     g_assert_cmpint(qobject_type(child), ==, QTYPE_QDICT);                // 0.0
/*62  */     listen = qobject_to_qdict(child);                                     // 0.0
/*64  */     g_assert_cmpstr("127.0.0.1", ==, qdict_get_str(listen, "addr"));      // 0.0
/*66  */     g_assert_cmpstr("5901", ==, qdict_get_str(listen, "port"));           // 0.0
/*70  */     child = qdict_get(vnc, "acl");                                        // 0.0
/*72  */     g_assert_cmpint(qobject_type(child), ==, QTYPE_QDICT);                // 0.0
/*74  */     acl = qobject_to_qdict(child);                                        // 0.0
/*78  */     child = qdict_get(acl, "rules");                                      // 0.0
/*80  */     g_assert_cmpint(qobject_type(child), ==, QTYPE_QLIST);                // 0.0
/*82  */     rules = qobject_to_qlist(child);                                      // 0.0
/*84  */     g_assert_cmpint(qlist_size(rules), ==, 2);                            // 0.0
/*88  */     rule = qobject_to_qdict(qlist_pop(rules));                            // 0.0
/*90  */     g_assert_cmpint(qdict_size(rule), ==, 2);                             // 0.0
/*92  */     g_assert_cmpstr("fred", ==, qdict_get_str(rule, "match"));            // 0.0
/*94  */     g_assert_cmpstr("allow", ==, qdict_get_str(rule, "policy"));          // 0.0
/*96  */     QDECREF(rule);                                                        // 0.0
/*100 */     rule = qobject_to_qdict(qlist_pop(rules));                            // 0.0
/*102 */     g_assert_cmpint(qdict_size(rule), ==, 2);                             // 0.0
/*104 */     g_assert_cmpstr("bob", ==, qdict_get_str(rule, "match"));             // 0.0
/*106 */     g_assert_cmpstr("deny", ==, qdict_get_str(rule, "policy"));           // 0.0
/*108 */     QDECREF(rule);                                                        // 0.0
/*112 */     /* With recursive crumpling, we should see all names unescaped */     // 0.0
/*114 */     g_assert_cmpstr("acl0", ==, qdict_get_str(vnc, "acl.name"));          // 0.0
/*116 */     child = qdict_get(vnc, "acl");                                        // 0.0
/*118 */     g_assert_cmpint(qobject_type(child), ==, QTYPE_QDICT);                // 0.0
/*120 */     acl = qdict_get_qdict(vnc, "acl");                                    // 0.0
/*122 */     g_assert_cmpstr("acl0", ==, qdict_get_str(acl, "rule.name"));         // 0.0
/*126 */     QDECREF(src);                                                         // 0.0
/*128 */     QDECREF(dst);                                                         // 0.0
/*130 */ }                                                                         // 0.0
