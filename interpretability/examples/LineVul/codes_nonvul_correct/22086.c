// commit message FFmpeg@808c10e728 (target=0, prob=0.30986422, correct=True): avutil/log: check that len is within the buffer before reading it
/*0  */ static void format_line(void *ptr, int level, const char *fmt, va_list vl,  // (8) 0.04883
/*2  */                         AVBPrint part[3], int *print_prefix, int type[2])   // (1) 0.08008
/*4  */ {                                                                           // (19) 0.001953
/*6  */     AVClass* avc = ptr ? *(AVClass **) ptr : NULL;                          // (10) 0.04102
/*8  */     av_bprint_init(part+0, 0, 1);                                           // (14) 0.03516
/*10 */     av_bprint_init(part+1, 0, 1);                                           // (15) 0.03516
/*12 */     av_bprint_init(part+2, 0, 65536);                                       // (12) 0.03711
/*16 */     if(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;                 // (5) 0.05859
/*18 */     if (*print_prefix && avc) {                                             // (16) 0.02539
/*20 */         if (avc->parent_log_context_offset) {                               // (11) 0.04102
/*22 */             AVClass** parent = *(AVClass ***) (((uint8_t *) ptr) +          // (3) 0.0625
/*24 */                                    avc->parent_log_context_offset);         // (0) 0.08789
/*26 */             if (parent && *parent) {                                        // (13) 0.03711
/*28 */                 av_bprintf(part+0, "[%s @ %p] ",                            // (4) 0.0625
/*30 */                          (*parent)->item_name(parent), parent);             // (2) 0.07031
/*32 */                 if(type) type[0] = get_category(parent);                    // (6) 0.05859
/*34 */             }                                                               // (17) 0.02344
/*36 */         }                                                                   // (18) 0.01562
/*38 */         av_bprintf(part+1, "[%s @ %p] ",                                    // (9) 0.04687
/*40 */                  avc->item_name(ptr), ptr);                                 // (7) 0.05273
/*42 */         if(type) type[1] = get_category(ptr);                               // 0.0
/*44 */     }                                                                       // 0.0
/*48 */     av_vbprintf(part+2, fmt, vl);                                           // 0.0
/*52 */     if(*part[0].str || *part[1].str || *part[2].str) {                      // 0.0
/*54 */         char lastc = part[2].len ? part[2].str[part[2].len - 1] : 0;        // 0.0
/*56 */         *print_prefix = lastc == '\n' || lastc == '\r';                     // 0.0
/*58 */     }                                                                       // 0.0
/*60 */ }                                                                           // 0.0
