// commit message FFmpeg@add41decd9 (target=0, prob=0.929655, correct=False): Remove return statements following infinite loops without break
/*0   */ int av_set_string3(void *obj, const char *name, const char *val, int alloc, const AVOption **o_out)                              // (1) 0.06445
/*2   */ {                                                                                                                                // (26) 0.001953
/*4   */     int ret;                                                                                                                     // (25) 0.01172
/*6   */     const AVOption *o = av_opt_find(obj, name, NULL, 0, 0);                                                                      // (2) 0.04883
/*8   */     if (o_out)                                                                                                                   // (23) 0.01758
/*10  */         *o_out = o;                                                                                                              // (17) 0.02734
/*12  */     if (!o)                                                                                                                      // (24) 0.01367
/*14  */         return AVERROR_OPTION_NOT_FOUND;                                                                                         // (11) 0.03906
/*16  */     if (!val || o->offset<=0)                                                                                                    // (18) 0.02734
/*18  */         return AVERROR(EINVAL);                                                                                                  // (14) 0.03125
/*22  */     if (o->type == FF_OPT_TYPE_BINARY) {                                                                                         // (9) 0.04102
/*24  */         uint8_t **dst = (uint8_t **)(((uint8_t*)obj) + o->offset);                                                               // (0) 0.06836
/*26  */         int *lendst = (int *)(dst + 1);                                                                                          // (4) 0.04297
/*28  */         uint8_t *bin, *ptr;                                                                                                      // (13) 0.0332
/*30  */         int len = strlen(val);                                                                                                   // (15) 0.0293
/*32  */         av_freep(dst);                                                                                                           // (16) 0.0293
/*34  */         *lendst = 0;                                                                                                             // (19) 0.02734
/*36  */         if (len & 1) return AVERROR(EINVAL);                                                                                     // (5) 0.04297
/*38  */         len /= 2;                                                                                                                // (20) 0.02344
/*40  */         ptr = bin = av_malloc(len);                                                                                              // (12) 0.03516
/*42  */         while (*val) {                                                                                                           // (21) 0.02344
/*44  */             int a = hexchar2int(*val++);                                                                                         // (6) 0.04297
/*46  */             int b = hexchar2int(*val++);                                                                                         // (7) 0.04297
/*48  */             if (a < 0 || b < 0) {                                                                                                // (8) 0.04297
/*50  */                 av_free(bin);                                                                                                    // (10) 0.04102
/*52  */                 return AVERROR(EINVAL);                                                                                          // (3) 0.04688
/*54  */             }                                                                                                                    // (22) 0.02344
/*56  */             *ptr++ = (a << 4) | b;                                                                                               // 0.0
/*58  */         }                                                                                                                        // 0.0
/*60  */         *dst = bin;                                                                                                              // 0.0
/*62  */         *lendst = len;                                                                                                           // 0.0
/*64  */         return 0;                                                                                                                // 0.0
/*66  */     }                                                                                                                            // 0.0
/*68  */     if (o->type != FF_OPT_TYPE_STRING) {                                                                                         // 0.0
/*70  */         int notfirst=0;                                                                                                          // 0.0
/*72  */         for (;;) {                                                                                                               // 0.0
/*74  */             int i;                                                                                                               // 0.0
/*76  */             char buf[256];                                                                                                       // 0.0
/*78  */             int cmd=0;                                                                                                           // 0.0
/*80  */             double d;                                                                                                            // 0.0
/*84  */             if (*val == '+' || *val == '-')                                                                                      // 0.0
/*86  */                 cmd= *(val++);                                                                                                   // 0.0
/*90  */             for (i=0; i<sizeof(buf)-1 && val[i] && val[i]!='+' && val[i]!='-'; i++)                                              // 0.0
/*92  */                 buf[i]= val[i];                                                                                                  // 0.0
/*94  */             buf[i]=0;                                                                                                            // 0.0
/*98  */             {                                                                                                                    // 0.0
/*100 */                 const AVOption *o_named = av_opt_find(obj, buf, o->unit, 0, 0);                                                  // 0.0
/*102 */                 if (o_named && o_named->type == FF_OPT_TYPE_CONST)                                                               // 0.0
/*104 */                     d= o_named->default_val.dbl;                                                                                 // 0.0
/*106 */                 else if (!strcmp(buf, "default")) d= o->default_val.dbl;                                                         // 0.0
/*108 */                 else if (!strcmp(buf, "max"    )) d= o->max;                                                                     // 0.0
/*110 */                 else if (!strcmp(buf, "min"    )) d= o->min;                                                                     // 0.0
/*112 */                 else if (!strcmp(buf, "none"   )) d= 0;                                                                          // 0.0
/*114 */                 else if (!strcmp(buf, "all"    )) d= ~0;                                                                         // 0.0
/*116 */                 else {                                                                                                           // 0.0
/*118 */                     int res = av_expr_parse_and_eval(&d, buf, const_names, const_values, NULL, NULL, NULL, NULL, NULL, 0, obj);  // 0.0
/*120 */                     if (res < 0) {                                                                                               // 0.0
/*122 */                         av_log(obj, AV_LOG_ERROR, "Unable to parse option value \"%s\"\n", val);                                 // 0.0
/*124 */                         return res;                                                                                              // 0.0
/*126 */                     }                                                                                                            // 0.0
/*128 */                 }                                                                                                                // 0.0
/*130 */             }                                                                                                                    // 0.0
/*132 */             if (o->type == FF_OPT_TYPE_FLAGS) {                                                                                  // 0.0
/*134 */                 if      (cmd=='+') d= av_get_int(obj, name, NULL) | (int64_t)d;                                                  // 0.0
/*136 */                 else if (cmd=='-') d= av_get_int(obj, name, NULL) &~(int64_t)d;                                                  // 0.0
/*138 */             } else {                                                                                                             // 0.0
/*140 */                 if      (cmd=='+') d= notfirst*av_get_double(obj, name, NULL) + d;                                               // 0.0
/*142 */                 else if (cmd=='-') d= notfirst*av_get_double(obj, name, NULL) - d;                                               // 0.0
/*144 */             }                                                                                                                    // 0.0
/*148 */             if ((ret = av_set_number2(obj, name, d, 1, 1, o_out)) < 0)                                                           // 0.0
/*150 */                 return ret;                                                                                                      // 0.0
/*152 */             val+= i;                                                                                                             // 0.0
/*154 */             if (!*val)                                                                                                           // 0.0
/*156 */                 return 0;                                                                                                        // 0.0
/*158 */             notfirst=1;                                                                                                          // 0.0
/*160 */         }                                                                                                                        // 0.0
/*162 */         return AVERROR(EINVAL);                                                                                                  // 0.0
/*164 */     }                                                                                                                            // 0.0
/*168 */     if (alloc) {                                                                                                                 // 0.0
/*170 */         av_free(*(void**)(((uint8_t*)obj) + o->offset));                                                                         // 0.0
/*172 */         val= av_strdup(val);                                                                                                     // 0.0
/*174 */     }                                                                                                                            // 0.0
/*178 */     memcpy(((uint8_t*)obj) + o->offset, &val, sizeof(val));                                                                      // 0.0
/*180 */     return 0;                                                                                                                    // 0.0
/*182 */ }                                                                                                                                // 0.0
