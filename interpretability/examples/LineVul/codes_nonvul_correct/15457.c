// commit message qemu@c54616608a (target=0, prob=0.4709552, correct=True): qjson: Give each of the six structural chars its own token type
/*0   */ static void json_message_process_token(JSONLexer *lexer, QString *token, JSONTokenType type, int x, int y)  // (0) 0.06445
/*2   */ {                                                                                                           // (32) 0.001953
/*4   */     JSONMessageParser *parser = container_of(lexer, JSONMessageParser, lexer);                              // (1) 0.04493
/*6   */     QDict *dict;                                                                                            // (27) 0.01758
/*10  */     if (type == JSON_OPERATOR) {                                                                            // (14) 0.02539
/*12  */         switch (qstring_get_str(token)[0]) {                                                                // (5) 0.04102
/*14  */         case '{':                                                                                           // (22) 0.02148
/*16  */             parser->brace_count++;                                                                          // (9) 0.0332
/*18  */             break;                                                                                          // (16) 0.02539
/*20  */         case '}':                                                                                           // (23) 0.02148
/*22  */             parser->brace_count--;                                                                          // (7) 0.03516
/*24  */             break;                                                                                          // (17) 0.02539
/*26  */         case '[':                                                                                           // (26) 0.01953
/*28  */             parser->bracket_count++;                                                                        // (8) 0.03516
/*30  */             break;                                                                                          // (20) 0.02539
/*32  */         case ']':                                                                                           // (24) 0.02148
/*34  */             parser->bracket_count--;                                                                        // (6) 0.03711
/*36  */             break;                                                                                          // (18) 0.02539
/*38  */         default:                                                                                            // (29) 0.01758
/*40  */             break;                                                                                          // (19) 0.02539
/*42  */         }                                                                                                   // (30) 0.01562
/*44  */     }                                                                                                       // (31) 0.007812
/*48  */     dict = qdict_new();                                                                                     // (25) 0.01953
/*50  */     qdict_put(dict, "type", qint_from_int(type));                                                           // (3) 0.04297
/*52  */     QINCREF(token);                                                                                         // (28) 0.01758
/*54  */     qdict_put(dict, "token", token);                                                                        // (13) 0.0293
/*56  */     qdict_put(dict, "x", qint_from_int(x));                                                                 // (4) 0.04297
/*58  */     qdict_put(dict, "y", qint_from_int(y));                                                                 // (2) 0.04297
/*62  */     parser->token_size += token->length;                                                                    // (15) 0.02539
/*66  */     qlist_append(parser->tokens, dict);                                                                     // (10) 0.03125
/*70  */     if (type == JSON_ERROR) {                                                                               // (21) 0.02344
/*72  */         goto out_emit_bad;                                                                                  // (11) 0.0293
/*74  */     } else if (parser->brace_count < 0 ||                                                                   // (12) 0.0293
/*76  */         parser->bracket_count < 0 ||                                                                        // 0.0
/*78  */         (parser->brace_count == 0 &&                                                                        // 0.0
/*80  */          parser->bracket_count == 0)) {                                                                     // 0.0
/*82  */         goto out_emit;                                                                                      // 0.0
/*84  */     } else if (parser->token_size > MAX_TOKEN_SIZE ||                                                       // 0.0
/*86  */                parser->bracket_count + parser->brace_count > MAX_NESTING) {                                 // 0.0
/*88  */         /* Security consideration, we limit total memory allocated per object                               // 0.0
/*90  */          * and the maximum recursion depth that a message can force.                                        // 0.0
/*92  */          */                                                                                                 // 0.0
/*94  */         goto out_emit_bad;                                                                                  // 0.0
/*96  */     }                                                                                                       // 0.0
/*100 */     return;                                                                                                 // 0.0
/*104 */ out_emit_bad:                                                                                               // 0.0
/*106 */     /*                                                                                                      // 0.0
/*108 */      * Clear out token list and tell the parser to emit an error                                            // 0.0
/*110 */      * indication by passing it a NULL list                                                                 // 0.0
/*112 */      */                                                                                                     // 0.0
/*114 */     QDECREF(parser->tokens);                                                                                // 0.0
/*116 */     parser->tokens = NULL;                                                                                  // 0.0
/*118 */ out_emit:                                                                                                   // 0.0
/*120 */     /* send current list of tokens to parser and reset tokenizer */                                         // 0.0
/*122 */     parser->brace_count = 0;                                                                                // 0.0
/*124 */     parser->bracket_count = 0;                                                                              // 0.0
/*126 */     parser->emit(parser, parser->tokens);                                                                   // 0.0
/*128 */     if (parser->tokens) {                                                                                   // 0.0
/*130 */         QDECREF(parser->tokens);                                                                            // 0.0
/*132 */     }                                                                                                       // 0.0
/*134 */     parser->tokens = qlist_new();                                                                           // 0.0
/*136 */     parser->token_size = 0;                                                                                 // 0.0
/*138 */ }                                                                                                           // 0.0
