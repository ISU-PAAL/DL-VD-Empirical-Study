// commit message qemu@17b74b9867 (target=0, prob=0.018031107, correct=True): migration: Move qjson.[ch] to migration/
/*0 */ void json_prop_int(QJSON *json, const char *name, int64_t val)  // (0) 0.3594
/*2 */ {                                                               // (3) 0.01562
/*4 */     json_emit_element(json, name);                              // (2) 0.2188
/*6 */     qstring_append_int(json->str, val);                         // (1) 0.25
/*8 */ }                                                               // (4) 0.01562
