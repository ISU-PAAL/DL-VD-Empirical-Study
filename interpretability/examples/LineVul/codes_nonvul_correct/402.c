// commit message qemu@d2ca7c0b0d (target=0, prob=0.009814032, correct=True): qjson: replace QString in JSONLexer with GString
/*0  */ void json_lexer_init(JSONLexer *lexer, JSONLexerEmitter func)  // (0) 0.2529
/*2  */ {                                                              // (6) 0.01149
/*4  */     lexer->emit = func;                                        // (4) 0.1264
/*6  */     lexer->state = IN_START;                                   // (3) 0.1494
/*8  */     lexer->token = qstring_new();                              // (2) 0.1494
/*10 */     lexer->x = lexer->y = 0;                                   // (1) 0.1724
/*12 */ }                                                              // (5) 0.01149
