// commit message qemu@c1990ebfa1 (target=1, prob=0.04439529, correct=False): json-parser: add handling for NULL token list
/*0  */ QObject *json_parser_parse_err(QList *tokens, va_list *ap, Error **errp)  // (0) 0.218
/*2  */ {                                                                         // (8) 0.007519
/*4  */     JSONParserContext ctxt = {};                                          // (4) 0.08271
/*6  */     QList *working = qlist_copy(tokens);                                  // (1) 0.1278
/*8  */     QObject *result;                                                      // (6) 0.06015
/*12 */     result = parse_value(&ctxt, &working, ap);                            // (2) 0.1278
/*16 */     QDECREF(working);                                                     // (5) 0.06767
/*20 */     error_propagate(errp, ctxt.err);                                      // (3) 0.1203
/*24 */     return result;                                                        // (7) 0.04511
/*26 */ }                                                                         // (9) 0.007519
