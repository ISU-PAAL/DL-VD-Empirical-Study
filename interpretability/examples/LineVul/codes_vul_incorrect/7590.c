// commit message qemu@31478f26ab (target=1, prob=0.03417517, correct=False): qapi: Improve how keyval input visitor reports unexpected dicts
/*0  */ Visitor *qobject_input_visitor_new_keyval(QObject *obj)            // (6) 0.07955
/*2  */ {                                                                  // (11) 0.003788
/*4  */     QObjectInputVisitor *v = qobject_input_visitor_base_new(obj);  // (2) 0.0947
/*8  */     v->visitor.type_int64 = qobject_input_type_int64_keyval;       // (0) 0.09848
/*10 */     v->visitor.type_uint64 = qobject_input_type_uint64_keyval;     // (1) 0.09848
/*12 */     v->visitor.type_bool = qobject_input_type_bool_keyval;         // (3) 0.09091
/*14 */     v->visitor.type_str = qobject_input_type_str;                  // (7) 0.07955
/*16 */     v->visitor.type_number = qobject_input_type_number_keyval;     // (4) 0.09091
/*18 */     v->visitor.type_any = qobject_input_type_any;                  // (8) 0.07955
/*20 */     v->visitor.type_null = qobject_input_type_null;                // (9) 0.07955
/*22 */     v->visitor.type_size = qobject_input_type_size_keyval;         // (5) 0.09091
/*26 */     return &v->visitor;                                            // (10) 0.03788
/*28 */ }                                                                  // (12) 0.003788
