// commit message qemu@9bada89711 (target=0, prob=0.4891525, correct=True): qjson: surprise, allocating 6 QObjects per token is expensive
/*0   */ static void json_message_process_token(JSONLexer *lexer, GString *input,        // (3) 0.04297
/*2   */                                        JSONTokenType type, int x, int y)        // (0) 0.0957
/*4   */ {                                                                               // (32) 0.001953
/*6   */     JSONMessageParser *parser = container_of(lexer, JSONMessageParser, lexer);  // (2) 0.04492
/*8   */     QDict *dict;                                                                // (23) 0.01758
/*12  */     switch (type) {                                                             // (29) 0.01562
/*14  */     case JSON_LCURLY:                                                           // (20) 0.01953
/*16  */         parser->brace_count++;                                                  // (15) 0.02539
/*18  */         break;                                                                  // (24) 0.01758
/*20  */     case JSON_RCURLY:                                                           // (19) 0.01953
/*22  */         parser->brace_count--;                                                  // (14) 0.02734
/*24  */         break;                                                                  // (25) 0.01758
/*26  */     case JSON_LSQUARE:                                                          // (18) 0.01953
/*28  */         parser->bracket_count++;                                                // (13) 0.02734
/*30  */         break;                                                                  // (26) 0.01758
/*32  */     case JSON_RSQUARE:                                                          // (22) 0.01953
/*34  */         parser->bracket_count--;                                                // (12) 0.0293
/*36  */         break;                                                                  // (28) 0.01758
/*38  */     default:                                                                    // (30) 0.009766
/*40  */         break;                                                                  // (27) 0.01758
/*42  */     }                                                                           // (31) 0.007812
/*46  */     dict = qdict_new();                                                         // (21) 0.01953
/*48  */     qdict_put(dict, "type", qint_from_int(type));                               // (4) 0.04297
/*50  */     qdict_put(dict, "token", qstring_from_str(input->str));                     // (1) 0.04687
/*52  */     qdict_put(dict, "x", qint_from_int(x));                                     // (6) 0.04297
/*54  */     qdict_put(dict, "y", qint_from_int(y));                                     // (5) 0.04297
/*58  */     parser->token_size += input->len;                                           // (16) 0.02539
/*62  */     g_queue_push_tail(parser->tokens, dict);                                    // (7) 0.03711
/*66  */     if (type == JSON_ERROR) {                                                   // (17) 0.02344
/*68  */         goto out_emit_bad;                                                      // (10) 0.0293
/*70  */     } else if (parser->brace_count < 0 ||                                       // (11) 0.0293
/*72  */         parser->bracket_count < 0 ||                                            // (8) 0.03125
/*74  */         (parser->brace_count == 0 &&                                            // (9) 0.03125
/*76  */          parser->bracket_count == 0)) {                                         // 0.0
/*78  */         goto out_emit;                                                          // 0.0
/*80  */     } else if (parser->token_size > MAX_TOKEN_SIZE ||                           // 0.0
/*82  */                parser->bracket_count + parser->brace_count > MAX_NESTING) {     // 0.0
/*84  */         /* Security consideration, we limit total memory allocated per object   // 0.0
/*86  */          * and the maximum recursion depth that a message can force.            // 0.0
/*88  */          */                                                                     // 0.0
/*90  */         goto out_emit_bad;                                                      // 0.0
/*92  */     }                                                                           // 0.0
/*96  */     return;                                                                     // 0.0
/*100 */ out_emit_bad:                                                                   // 0.0
/*102 */     /*                                                                          // 0.0
/*104 */      * Clear out token list and tell the parser to emit an error                // 0.0
/*106 */      * indication by passing it a NULL list                                     // 0.0
/*108 */      */                                                                         // 0.0
/*110 */     json_message_free_tokens(parser);                                           // 0.0
/*112 */ out_emit:                                                                       // 0.0
/*114 */     /* send current list of tokens to parser and reset tokenizer */             // 0.0
/*116 */     parser->brace_count = 0;                                                    // 0.0
/*118 */     parser->bracket_count = 0;                                                  // 0.0
/*120 */     /* parser->emit takes ownership of parser->tokens.  */                      // 0.0
/*122 */     parser->emit(parser, parser->tokens);                                       // 0.0
/*124 */     parser->tokens = g_queue_new();                                             // 0.0
/*126 */     parser->token_size = 0;                                                     // 0.0
/*128 */ }                                                                               // 0.0
