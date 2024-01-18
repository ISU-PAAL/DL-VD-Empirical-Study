// commit message qemu@e549e7161f (target=1, prob=0.01729045, correct=False): json-parser: Accept 'null' in QMP
/*0  */ static QObject *parse_keyword(JSONParserContext *ctxt)                             // (8) 0.04893
/*2  */ {                                                                                  // (22) 0.003058
/*4  */     QObject *token, *ret;                                                          // (10) 0.03364
/*6  */     JSONParserContext saved_ctxt = parser_context_save(ctxt);                      // (4) 0.06116
/*10 */     token = parser_context_pop_token(ctxt);                                        // (9) 0.04893
/*12 */     if (token == NULL) {                                                           // (11) 0.03058
/*14 */         goto out;                                                                  // (12) 0.03058
/*16 */     }                                                                              // (18) 0.01223
/*20 */     if (token_get_type(token) != JSON_KEYWORD) {                                   // (3) 0.06422
/*22 */         goto out;                                                                  // (13) 0.03058
/*24 */     }                                                                              // (19) 0.01223
/*28 */     if (token_is_keyword(token, "true")) {                                         // (6) 0.05505
/*30 */         ret = QOBJECT(qbool_from_int(true));                                       // (1) 0.06728
/*32 */     } else if (token_is_keyword(token, "false")) {                                 // (5) 0.06116
/*34 */         ret = QOBJECT(qbool_from_int(false));                                      // (2) 0.06728
/*38 */     } else {                                                                       // (15) 0.01835
/*40 */         parse_error(ctxt, token, "invalid keyword `%s'", token_get_value(token));  // (0) 0.1009
/*42 */         goto out;                                                                  // (14) 0.03058
/*44 */     }                                                                              // (20) 0.01223
/*48 */     return ret;                                                                    // (16) 0.01835
/*52 */ out:                                                                               // (21) 0.009174
/*54 */     parser_context_restore(ctxt, saved_ctxt);                                      // (7) 0.05505
/*58 */     return NULL;                                                                   // (17) 0.01835
/*60 */ }                                                                                  // (23) 0.003058
