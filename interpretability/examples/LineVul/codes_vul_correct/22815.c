// commit message qemu@0b2c1beea4 (target=1, prob=0.65002984, correct=True): keyval: Support lists
/*0   */ static const char *keyval_parse_one(QDict *qdict, const char *params,      // (3) 0.04492
/*2   */                                     const char *implied_key,               // (0) 0.08398
/*4   */                                     Error **errp)                          // (1) 0.07813
/*6   */ {                                                                          // (30) 0.001953
/*8   */     const char *key, *key_end, *s;                                         // (12) 0.03125
/*10  */     size_t len;                                                            // (22) 0.01562
/*12  */     char key_in_cur[128];                                                  // (16) 0.02344
/*14  */     QDict *cur;                                                            // (18) 0.01758
/*16  */     int ret;                                                               // (26) 0.01172
/*18  */     QObject *next;                                                         // (19) 0.01563
/*20  */     QString *val;                                                          // (21) 0.01562
/*24  */     key = params;                                                          // (24) 0.01367
/*26  */     len = strcspn(params, "=,");                                           // (13) 0.03125
/*28  */     if (implied_key && len && key[len] != '=') {                           // (5) 0.04102
/*30  */         /* Desugar implied key */                                          // (14) 0.02539
/*32  */         key = implied_key;                                                 // (15) 0.02539
/*34  */         len = strlen(implied_key);                                         // (10) 0.0332
/*36  */     }                                                                      // (29) 0.007812
/*38  */     key_end = key + len;                                                   // (17) 0.02148
/*42  */     /*                                                                     // (28) 0.007812
/*44  */      * Loop over key fragments: @s points to current fragment, it          // (8) 0.03516
/*46  */      * applies to @cur.  @key_in_cur[] holds the previous fragment.        // (4) 0.04492
/*48  */      */                                                                    // (27) 0.009766
/*50  */     cur = qdict;                                                           // (20) 0.01562
/*52  */     s = key;                                                               // (25) 0.01367
/*54  */     for (;;) {                                                             // (23) 0.01562
/*56  */         ret = parse_qapi_name(s, false);                                   // (6) 0.03906
/*58  */         len = ret < 0 ? 0 : ret;                                           // (11) 0.0332
/*60  */         assert(s + len <= key_end);                                        // (9) 0.0332
/*62  */         if (!len || (s + len < key_end && s[len] != '.')) {                // (2) 0.05664
/*64  */             assert(key != implied_key);                                    // (7) 0.03711
/*66  */             error_setg(errp, "Invalid parameter '%.*s'",                   // 0.0
/*68  */                        (int)(key_end - key), key);                         // 0.0
/*70  */             return NULL;                                                   // 0.0
/*72  */         }                                                                  // 0.0
/*74  */         if (len >= sizeof(key_in_cur)) {                                   // 0.0
/*76  */             assert(key != implied_key);                                    // 0.0
/*78  */             error_setg(errp, "Parameter%s '%.*s' is too long",             // 0.0
/*80  */                        s != key || s + len != key_end ? " fragment" : "",  // 0.0
/*82  */                        (int)len, s);                                       // 0.0
/*84  */             return NULL;                                                   // 0.0
/*86  */         }                                                                  // 0.0
/*90  */         if (s != key) {                                                    // 0.0
/*92  */             next = keyval_parse_put(cur, key_in_cur, NULL,                 // 0.0
/*94  */                                     key, s - 1, errp);                     // 0.0
/*96  */             if (!next) {                                                   // 0.0
/*98  */                 return NULL;                                               // 0.0
/*100 */             }                                                              // 0.0
/*102 */             cur = qobject_to_qdict(next);                                  // 0.0
/*104 */             assert(cur);                                                   // 0.0
/*106 */         }                                                                  // 0.0
/*110 */         memcpy(key_in_cur, s, len);                                        // 0.0
/*112 */         key_in_cur[len] = 0;                                               // 0.0
/*114 */         s += len;                                                          // 0.0
/*118 */         if (*s != '.') {                                                   // 0.0
/*120 */             break;                                                         // 0.0
/*122 */         }                                                                  // 0.0
/*124 */         s++;                                                               // 0.0
/*126 */     }                                                                      // 0.0
/*130 */     if (key == implied_key) {                                              // 0.0
/*132 */         assert(!*s);                                                       // 0.0
/*134 */         s = params;                                                        // 0.0
/*136 */     } else {                                                               // 0.0
/*138 */         if (*s != '=') {                                                   // 0.0
/*140 */             error_setg(errp, "Expected '=' after parameter '%.*s'",        // 0.0
/*142 */                        (int)(s - key), key);                               // 0.0
/*144 */             return NULL;                                                   // 0.0
/*146 */         }                                                                  // 0.0
/*148 */         s++;                                                               // 0.0
/*150 */     }                                                                      // 0.0
/*154 */     val = qstring_new();                                                   // 0.0
/*156 */     for (;;) {                                                             // 0.0
/*158 */         if (!*s) {                                                         // 0.0
/*160 */             break;                                                         // 0.0
/*162 */         } else if (*s == ',') {                                            // 0.0
/*164 */             s++;                                                           // 0.0
/*166 */             if (*s != ',') {                                               // 0.0
/*168 */                 break;                                                     // 0.0
/*170 */             }                                                              // 0.0
/*172 */         }                                                                  // 0.0
/*174 */         qstring_append_chr(val, *s++);                                     // 0.0
/*176 */     }                                                                      // 0.0
/*180 */     if (!keyval_parse_put(cur, key_in_cur, val, key, key_end, errp)) {     // 0.0
/*182 */         return NULL;                                                       // 0.0
/*184 */     }                                                                      // 0.0
/*186 */     return s;                                                              // 0.0
/*188 */ }                                                                          // 0.0
