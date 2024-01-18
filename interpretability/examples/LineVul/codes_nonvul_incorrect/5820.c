// commit message qemu@ca6b6e1e68 (target=0, prob=0.7857567, correct=False): Don't check qobject_type() before qobject_to_qdict()
/*0  */ static QDict *qmp_dispatch_check_obj(const QObject *request, Error **errp)     // (4) 0.05078
/*2  */ {                                                                              // (24) 0.001953
/*4  */     const QDictEntry *ent;                                                     // (19) 0.02148
/*6  */     const char *arg_name;                                                      // (21) 0.01953
/*8  */     const QObject *arg_obj;                                                    // (20) 0.02148
/*10 */     bool has_exec_key = false;                                                 // (16) 0.02344
/*12 */     QDict *dict = NULL;                                                        // (18) 0.02148
/*16 */     if (qobject_type(request) != QTYPE_QDICT) {                                // (7) 0.04102
/*18 */         error_setg(errp, QERR_QMP_BAD_INPUT_OBJECT,                            // (1) 0.06055
/*20 */                    "request is not a dictionary");                             // (5) 0.04883
/*22 */         return NULL;                                                           // (22) 0.01953
/*24 */     }                                                                          // (23) 0.007812
/*28 */     dict = qobject_to_qdict(request);                                          // (15) 0.0293
/*32 */     for (ent = qdict_first(dict); ent;                                         // (14) 0.03125
/*34 */          ent = qdict_next(dict, ent)) {                                        // (9) 0.03906
/*36 */         arg_name = qdict_entry_key(ent);                                       // (11) 0.03906
/*38 */         arg_obj = qdict_entry_value(ent);                                      // (10) 0.03906
/*42 */         if (!strcmp(arg_name, "execute")) {                                    // (8) 0.03906
/*44 */             if (qobject_type(arg_obj) != QTYPE_QSTRING) {                      // (2) 0.06055
/*46 */                 error_setg(errp, QERR_QMP_BAD_INPUT_OBJECT_MEMBER, "execute",  // (0) 0.08789
/*48 */                            "string");                                          // (3) 0.05664
/*50 */                 return NULL;                                                   // (13) 0.03516
/*52 */             }                                                                  // (17) 0.02344
/*54 */             has_exec_key = true;                                               // (12) 0.03711
/*56 */         } else if (strcmp(arg_name, "arguments")) {                            // (6) 0.04492
/*58 */             error_setg(errp, QERR_QMP_EXTRA_MEMBER, arg_name);                 // 0.0
/*60 */             return NULL;                                                       // 0.0
/*62 */         }                                                                      // 0.0
/*64 */     }                                                                          // 0.0
/*68 */     if (!has_exec_key) {                                                       // 0.0
/*70 */         error_setg(errp, QERR_QMP_BAD_INPUT_OBJECT, "execute");                // 0.0
/*72 */         return NULL;                                                           // 0.0
/*74 */     }                                                                          // 0.0
/*78 */     return dict;                                                               // 0.0
/*80 */ }                                                                              // 0.0
