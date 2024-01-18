// commit message FFmpeg@a18456a203 (target=0, prob=0.64945304, correct=False): ffserver: check for EOF|error at loop condition
/*0  */ static FFServerIPAddressACL* parse_dynamic_acl(FFServerStream *stream, HTTPContext *c)  // (1) 0.05882
/*2  */ {                                                                                       // (29) 0.002262
/*4  */     FILE* f;                                                                            // (24) 0.01584
/*6  */     char line[1024];                                                                    // (19) 0.0181
/*8  */     char  cmd[1024];                                                                    // (18) 0.02036
/*10 */     FFServerIPAddressACL *acl = NULL;                                                   // (10) 0.03167
/*12 */     int line_num = 0;                                                                   // (16) 0.02262
/*14 */     const char *p;                                                                      // (20) 0.0181
/*18 */     f = fopen(stream->dynamic_acl, "r");                                                // (7) 0.04072
/*20 */     if (!f) {                                                                           // (21) 0.0181
/*22 */         perror(stream->dynamic_acl);                                                    // (8) 0.03846
/*24 */         return NULL;                                                                    // (17) 0.02262
/*26 */     }                                                                                   // (27) 0.00905
/*30 */     acl = av_mallocz(sizeof(FFServerIPAddressACL));                                     // (4) 0.04977
/*34 */     /* Build ACL */                                                                     // (25) 0.01584
/*36 */     for(;;) {                                                                           // (22) 0.0181
/*38 */         if (fgets(line, sizeof(line), f) == NULL)                                       // (2) 0.05204
/*40 */             break;                                                                      // (11) 0.02941
/*42 */         line_num++;                                                                     // (14) 0.02489
/*44 */         p = line;                                                                       // (15) 0.02489
/*46 */         while (av_isspace(*p))                                                          // (9) 0.0362
/*48 */             p++;                                                                        // (12) 0.02941
/*50 */         if (*p == '\0' || *p == '#')                                                    // (5) 0.04977
/*52 */             continue;                                                                   // (13) 0.02941
/*54 */         ffserver_get_arg(cmd, sizeof(cmd), &p);                                         // (3) 0.05204
/*58 */         if (!av_strcasecmp(cmd, "ACL"))                                                 // (6) 0.04751
/*60 */             ffserver_parse_acl_row(NULL, NULL, acl, p, stream->dynamic_acl, line_num);  // (0) 0.0905
/*62 */     }                                                                                   // (28) 0.00905
/*64 */     fclose(f);                                                                          // (23) 0.0181
/*66 */     return acl;                                                                         // (26) 0.01584
/*68 */ }                                                                                       // (30) 0.002262
