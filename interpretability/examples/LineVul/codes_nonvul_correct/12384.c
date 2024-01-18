// commit message qemu@65c0f1e955 (target=0, prob=0.01828572, correct=True): json-parser: don't replicate tokens at each level of recursion
/*0  */ static QObject *parse_keyword(JSONParserContext *ctxt, QList **tokens)             // (1) 0.06284
/*2  */ {                                                                                  // (26) 0.002732
/*4  */     QObject *token, *ret;                                                          // (9) 0.03005
/*6  */     QList *working = qlist_copy(*tokens);                                          // (7) 0.04645
/*10 */     token = qlist_pop(working);                                                    // (8) 0.03279
/*12 */     if (token == NULL) {                                                           // (13) 0.02732
/*14 */         goto out;                                                                  // (14) 0.02732
/*16 */     }                                                                              // (22) 0.01093
/*20 */     if (token_get_type(token) != JSON_KEYWORD) {                                   // (4) 0.05738
/*22 */         goto out;                                                                  // (15) 0.02732
/*24 */     }                                                                              // (23) 0.01093
/*28 */     if (token_is_keyword(token, "true")) {                                         // (6) 0.04918
/*30 */         ret = QOBJECT(qbool_from_int(true));                                       // (2) 0.06011
/*32 */     } else if (token_is_keyword(token, "false")) {                                 // (5) 0.05464
/*34 */         ret = QOBJECT(qbool_from_int(false));                                      // (3) 0.06011
/*36 */     } else {                                                                       // (19) 0.01639
/*38 */         parse_error(ctxt, token, "invalid keyword `%s'", token_get_value(token));  // (0) 0.09016
/*40 */         goto out;                                                                  // (16) 0.02732
/*42 */     }                                                                              // (24) 0.01093
/*46 */     qobject_decref(token);                                                         // (10) 0.03005
/*48 */     QDECREF(*tokens);                                                              // (11) 0.03005
/*50 */     *tokens = working;                                                             // (17) 0.02732
/*54 */     return ret;                                                                    // (20) 0.01639
/*58 */ out:                                                                               // (25) 0.008197
/*60 */     qobject_decref(token);                                                         // (12) 0.03005
/*62 */     QDECREF(working);                                                              // (18) 0.02459
/*66 */     return NULL;                                                                   // (21) 0.01639
/*68 */ }                                                                                  // (27) 0.002732
