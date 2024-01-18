// commit message qemu@9bada89711 (target=0, prob=0.027568614, correct=True): qjson: surprise, allocating 6 QObjects per token is expensive
/*0  */ static QObject *parse_escape(JSONParserContext *ctxt, va_list *ap)    // (8) 0.0433
/*2  */ {                                                                     // (26) 0.002062
/*4  */     QObject *token;                                                   // (21) 0.01649
/*6  */     const char *val;                                                  // (22) 0.01649
/*10 */     if (ap == NULL) {                                                 // (19) 0.02062
/*12 */         return NULL;                                                  // (20) 0.02062
/*14 */     }                                                                 // (24) 0.008247
/*18 */     token = parser_context_pop_token(ctxt);                           // (11) 0.03299
/*20 */     assert(token && token_get_type(token) == JSON_ESCAPE);            // (7) 0.04536
/*22 */     val = token_get_value(token);                                     // (18) 0.0268
/*26 */     if (!strcmp(val, "%p")) {                                         // (17) 0.02887
/*28 */         return va_arg(*ap, QObject *);                                // (9) 0.03711
/*30 */     } else if (!strcmp(val, "%i")) {                                  // (12) 0.03299
/*32 */         return QOBJECT(qbool_from_bool(va_arg(*ap, int)));            // (2) 0.05773
/*34 */     } else if (!strcmp(val, "%d")) {                                  // (14) 0.03299
/*36 */         return QOBJECT(qint_from_int(va_arg(*ap, int)));              // (5) 0.05773
/*38 */     } else if (!strcmp(val, "%ld")) {                                 // (13) 0.03299
/*40 */         return QOBJECT(qint_from_int(va_arg(*ap, long)));             // (4) 0.05773
/*42 */     } else if (!strcmp(val, "%lld") ||                                // (10) 0.03505
/*44 */                !strcmp(val, "%I64d")) {                               // (6) 0.05361
/*46 */         return QOBJECT(qint_from_int(va_arg(*ap, long long)));        // (1) 0.05979
/*48 */     } else if (!strcmp(val, "%s")) {                                  // (16) 0.03299
/*50 */         return QOBJECT(qstring_from_str(va_arg(*ap, const char *)));  // (0) 0.06186
/*52 */     } else if (!strcmp(val, "%f")) {                                  // (15) 0.03299
/*54 */         return QOBJECT(qfloat_from_double(va_arg(*ap, double)));      // (3) 0.05773
/*56 */     }                                                                 // (25) 0.008247
/*58 */     return NULL;                                                      // (23) 0.01237
/*60 */ }                                                                     // (27) 0.002062
