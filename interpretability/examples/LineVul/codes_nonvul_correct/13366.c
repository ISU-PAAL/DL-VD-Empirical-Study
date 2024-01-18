// commit message qemu@810f49b56a (target=0, prob=0.39412907, correct=True): QMP: Drop wrong assert()
/*0  */ static void monitor_protocol_emitter(Monitor *mon, QObject *data)        // (7) 0.04121
/*2  */ {                                                                        // (27) 0.002169
/*4  */     QDict *qmp;                                                          // (20) 0.02169
/*8  */     qmp = qdict_new();                                                   // (17) 0.02386
/*12 */     if (!monitor_has_error(mon)) {                                       // (13) 0.03037
/*14 */         /* success response */                                           // (18) 0.02386
/*16 */         if (data) {                                                      // (15) 0.02603
/*18 */             assert(qobject_type(data) == QTYPE_QDICT);                   // (1) 0.06074
/*20 */             qobject_incref(data);                                        // (9) 0.04121
/*22 */             qdict_put_obj(qmp, "return", data);                          // (3) 0.0564
/*24 */         } else {                                                         // (21) 0.02169
/*26 */             /* return an empty QDict by default */                       // (6) 0.04555
/*28 */             qdict_put(qmp, "return", qdict_new());                       // (2) 0.05857
/*30 */         }                                                                // (23) 0.01735
/*32 */     } else {                                                             // (24) 0.01302
/*34 */         /* error response */                                             // (19) 0.02386
/*36 */         qdict_put(mon->error->error, "desc", qerror_human(mon->error));  // (0) 0.06508
/*38 */         qdict_put(qmp, "error", mon->error->error);                      // (5) 0.05206
/*40 */         QINCREF(mon->error->error);                                      // (10) 0.03688
/*42 */         QDECREF(mon->error);                                             // (12) 0.03254
/*44 */         mon->error = NULL;                                               // (14) 0.0282
/*46 */     }                                                                    // (25) 0.008677
/*50 */     if (mon->mc->id) {                                                   // (16) 0.02603
/*52 */         qdict_put_obj(qmp, "id", mon->mc->id);                           // (4) 0.0564
/*54 */         mon->mc->id = NULL;                                              // (11) 0.03254
/*56 */     }                                                                    // (26) 0.008677
/*60 */     monitor_json_emitter(mon, QOBJECT(qmp));                             // (8) 0.04121
/*62 */     QDECREF(qmp);                                                        // (22) 0.02169
/*64 */ }                                                                        // (28) 0.002169
