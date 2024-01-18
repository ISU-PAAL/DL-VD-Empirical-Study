// commit message qemu@55e1819c50 (target=0, prob=0.15918326, correct=True): qobject: Simplify QObject
/*0  */ QString *qstring_from_substr(const char *str, int start, int end)  // (0) 0.1215
/*2  */ {                                                                  // (10) 0.005525
/*4  */     QString *qstring;                                              // (8) 0.04972
/*8  */     qstring = g_malloc(sizeof(*qstring));                          // (4) 0.09392
/*12 */     qstring->length = end - start + 1;                             // (6) 0.07735
/*14 */     qstring->capacity = qstring->length;                           // (7) 0.07182
/*18 */     qstring->string = g_malloc(qstring->capacity + 1);             // (2) 0.1105
/*20 */     memcpy(qstring->string, str + start, qstring->length);         // (1) 0.116
/*22 */     qstring->string[qstring->length] = 0;                          // (5) 0.0884
/*26 */     QOBJECT_INIT(qstring, &qstring_type);                          // (3) 0.105
/*30 */     return qstring;                                                // (9) 0.03867
/*32 */ }                                                                  // (11) 0.005525
