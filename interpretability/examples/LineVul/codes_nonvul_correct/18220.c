// commit message qemu@17b74b9867 (target=0, prob=0.027353086, correct=True): migration: Move qjson.[ch] to migration/
/*0 */ QJSON *qjson_new(void)                            // (1) 0.2128
/*2 */ {                                                 // (3) 0.02128
/*4 */     QJSON *json = QJSON(object_new(TYPE_QJSON));  // (0) 0.4255
/*6 */     return json;                                  // (2) 0.1277
/*8 */ }                                                 // (4) 0.02128
