// commit message qemu@0d2cd785ef (target=1, prob=0.794381, correct=True): qom-test: Fix qmp() leaks
/*0  */ static void test_properties(const char *path, bool recurse)                      // (14) 0.0293
/*2  */ {                                                                                // (24) 0.001953
/*4  */     char *child_path;                                                            // (19) 0.01758
/*6  */     QDict *response, *tuple;                                                     // (15) 0.02539
/*8  */     QList *list;                                                                 // (22) 0.01563
/*10 */     QListEntry *entry;                                                           // (17) 0.01758
/*14 */     g_test_message("Obtaining properties of %s", path);                          // (10) 0.03516
/*16 */     response = qmp("{ 'execute': 'qom-list',"                                    // (11) 0.03516
/*18 */                    "  'arguments': { 'path': %s } }", path);                     // (1) 0.06836
/*20 */     g_assert(response);                                                          // (20) 0.01758
/*24 */     if (!recurse) {                                                              // (18) 0.01758
/*26 */         return;                                                                  // (21) 0.01758
/*28 */     }                                                                            // (23) 0.007812
/*32 */     g_assert(qdict_haskey(response, "return"));                                  // (9) 0.03711
/*34 */     list = qobject_to_qlist(qdict_get(response, "return"));                      // (6) 0.04688
/*36 */     QLIST_FOREACH_ENTRY(list, entry) {                                           // (13) 0.0332
/*38 */         tuple = qobject_to_qdict(qlist_entry_obj(entry));                        // (5) 0.05078
/*40 */         bool is_child = strstart(qdict_get_str(tuple, "type"), "child<", NULL);  // (3) 0.06641
/*42 */         bool is_link = strstart(qdict_get_str(tuple, "type"), "link<", NULL);    // (2) 0.06641
/*46 */         if (is_child || is_link) {                                               // (12) 0.03516
/*48 */             child_path = g_strdup_printf("%s/%s",                                // (4) 0.05664
/*50 */                                          path, qdict_get_str(tuple, "name"));    // (0) 0.1094
/*52 */             test_properties(child_path, is_child);                               // (7) 0.04492
/*54 */             g_free(child_path);                                                  // (8) 0.03711
/*56 */         } else {                                                                 // (16) 0.01953
/*58 */             const char *prop = qdict_get_str(tuple, "name");                     // 0.0
/*60 */             g_test_message("Testing property %s.%s", path, prop);                // 0.0
/*62 */             response = qmp("{ 'execute': 'qom-get',"                             // 0.0
/*64 */                            "  'arguments': { 'path': %s,"                        // 0.0
/*66 */                            "                 'property': %s } }",                // 0.0
/*68 */                            path, prop);                                          // 0.0
/*70 */             /* qom-get may fail but should not, e.g., segfault. */               // 0.0
/*72 */             g_assert(response);                                                  // 0.0
/*74 */         }                                                                        // 0.0
/*76 */     }                                                                            // 0.0
/*78 */ }                                                                                // 0.0
