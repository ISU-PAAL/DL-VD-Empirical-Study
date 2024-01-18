// commit message qemu@31478f26ab (target=1, prob=0.58131707, correct=True): qapi: Improve how keyval input visitor reports unexpected dicts
/*0  */ static const char *qobject_input_get_keyval(QObjectInputVisitor *qiv,  // (5) 0.07055
/*2  */                                             const char *name,          // (1) 0.1472
/*4  */                                             Error **errp)              // (0) 0.1472
/*6  */ {                                                                      // (16) 0.003067
/*8  */     QObject *qobj;                                                     // (10) 0.02761
/*10 */     QString *qstr;                                                     // (11) 0.02761
/*14 */     qobj = qobject_input_get_object(qiv, name, true, errp);            // (4) 0.07669
/*16 */     if (!qobj) {                                                       // (12) 0.02761
/*18 */         return NULL;                                                   // (8) 0.03067
/*20 */     }                                                                  // (14) 0.01227
/*24 */     qstr = qobject_to_qstring(qobj);                                   // (6) 0.05215
/*26 */     if (!qstr) {                                                       // (13) 0.02761
/*28 */         error_setg(errp, QERR_INVALID_PARAMETER_TYPE,                  // (3) 0.09202
/*30 */                    full_name(qiv, name), "string");                    // (2) 0.09202
/*32 */         return NULL;                                                   // (9) 0.03067
/*34 */     }                                                                  // (15) 0.01227
/*38 */     return qstring_get_str(qstr);                                      // (7) 0.04294
/*40 */ }                                                                      // (17) 0.003067
