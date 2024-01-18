// commit message qemu@563890c7c7 (target=1, prob=0.9412123, correct=True): libqtest: escape strings in QMP commands, fix leak
/*0  */ static int qmp_tmp105_get_temperature(const char *id)                       // (3) 0.1104
/*2  */ {                                                                           // (9) 0.006135
/*4  */     QDict *response;                                                        // (5) 0.05521
/*6  */     int ret;                                                                // (7) 0.03681
/*10 */     response = qmp("{ 'execute': 'qom-get', 'arguments': { 'path': '%s', "  // (0) 0.1902
/*12 */                    "'property': 'temperature' } }", id);                    // (1) 0.184
/*14 */     g_assert(qdict_haskey(response, "return"));                             // (2) 0.1166
/*16 */     ret = qdict_get_int(response, "return");                                // (4) 0.1043
/*18 */     QDECREF(response);                                                      // (6) 0.05521
/*20 */     return ret;                                                             // (8) 0.03681
/*22 */ }                                                                           // (10) 0.006135
