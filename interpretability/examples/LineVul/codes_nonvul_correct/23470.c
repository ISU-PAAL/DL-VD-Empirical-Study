// commit message FFmpeg@2758cdedfb (target=0, prob=0.28657016, correct=True): lavf: reorganize URLProtocols
/*0  */ int ffurl_alloc(URLContext **puc, const char *filename, int flags,            // (11) 0.0404
/*2  */                 const AVIOInterruptCB *int_cb)                                // (5) 0.05253
/*4  */ {                                                                             // (22) 0.00202
/*6  */     URLProtocol *up = NULL;                                                   // (18) 0.02222
/*8  */     char proto_str[128], proto_nested[128], *ptr;                             // (12) 0.0404
/*10 */     size_t proto_len = strspn(filename, URL_SCHEME_CHARS);                    // (6) 0.05253
/*14 */     if (filename[proto_len] != ':' || is_dos_path(filename))                  // (8) 0.04848
/*16 */         strcpy(proto_str, "file");                                            // (14) 0.03838
/*18 */     else                                                                      // (20) 0.008081
/*20 */         av_strlcpy(proto_str, filename,                                       // (13) 0.0404
/*22 */                    FFMIN(proto_len + 1, sizeof(proto_str)));                  // (0) 0.07273
/*26 */     av_strlcpy(proto_nested, proto_str, sizeof(proto_nested));                // (4) 0.05455
/*28 */     if ((ptr = strchr(proto_nested, '+')))                                    // (9) 0.04242
/*30 */         *ptr = '\0';                                                          // (17) 0.02828
/*34 */     while (up = ffurl_protocol_next(up)) {                                    // (15) 0.03636
/*36 */         if (!strcmp(proto_str, up->name))                                     // (10) 0.04242
/*38 */             return url_alloc_for_protocol(puc, up, filename, flags, int_cb);  // (1) 0.06869
/*40 */         if (up->flags & URL_PROTOCOL_FLAG_NESTED_SCHEME &&                    // (3) 0.06263
/*42 */             !strcmp(proto_nested, up->name))                                  // (7) 0.05051
/*44 */             return url_alloc_for_protocol(puc, up, filename, flags, int_cb);  // (2) 0.06869
/*46 */     }                                                                         // (21) 0.008081
/*48 */     *puc = NULL;                                                              // (19) 0.01818
/*50 */     return AVERROR_PROTOCOL_NOT_FOUND;                                        // (16) 0.03636
/*52 */ }                                                                             // (23) 0.00202
