// commit message qemu@56b4a42a2e (target=0, prob=0.6181467, correct=False): tests: check that migration parameters are really assigned
/*0  */ static void migrate_set_downtime(QTestState *who, const char *value)  // (2) 0.1173
/*2  */ {                                                                     // (9) 0.005587
/*4  */     QDict *rsp;                                                       // (5) 0.05587
/*6  */     gchar *cmd;                                                       // (8) 0.04469
/*10 */     cmd = g_strdup_printf("{ 'execute': 'migrate_set_downtime',"      // (1) 0.1508
/*12 */                           "'arguments': { 'value': %s } }", value);   // (0) 0.2235
/*14 */     rsp = qtest_qmp(who, cmd);                                        // (4) 0.08939
/*16 */     g_free(cmd);                                                      // (7) 0.05028
/*18 */     g_assert(qdict_haskey(rsp, "return"));                            // (3) 0.1117
/*20 */     QDECREF(rsp);                                                     // (6) 0.05587
/*22 */ }                                                                     // (10) 0.005587
