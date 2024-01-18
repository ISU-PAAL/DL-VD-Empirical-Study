// commit message qemu@55e1819c50 (target=0, prob=0.016608274, correct=True): qobject: Simplify QObject
/*0  */ QBool *qbool_from_bool(bool value)  // (2) 0.1429
/*2  */ {                                   // (7) 0.01099
/*4  */     QBool *qb;                      // (4) 0.0989
/*8  */     qb = g_malloc(sizeof(*qb));     // (1) 0.1868
/*10 */     qb->value = value;              // (3) 0.1099
/*12 */     QOBJECT_INIT(qb, &qbool_type);  // (0) 0.2088
/*16 */     return qb;                      // (5) 0.07692
/*18 */ }                                   // (6) 0.01099
