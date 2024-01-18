// commit message qemu@3ac2f2f765 (target=1, prob=0.99919075, correct=True): qapi: fix memory leak in bdrv_image_info_specific_dump
/*0  */ void bdrv_image_info_specific_dump(fprintf_function func_fprintf, void *f,  // (2) 0.1145
/*2  */                                    ImageInfoSpecific *info_spec)            // (0) 0.185
/*4  */ {                                                                           // (11) 0.004405
/*6  */     QObject *obj, *data;                                                    // (8) 0.04846
/*8  */     Visitor *v = qmp_output_visitor_new(&obj);                              // (4) 0.08811
/*12 */     visit_type_ImageInfoSpecific(v, NULL, &info_spec, &error_abort);        // (1) 0.1145
/*14 */     visit_complete(v, &obj);                                                // (7) 0.05286
/*16 */     assert(qobject_type(obj) == QTYPE_QDICT);                               // (5) 0.08811
/*18 */     data = qdict_get(qobject_to_qdict(obj), "data");                        // (3) 0.1013
/*20 */     dump_qobject(func_fprintf, f, 1, data);                                 // (6) 0.0837
/*23 */     visit_free(v);                                                          // (9) 0.03965
/*25 */ }                                                                           // (10) 0.004405
