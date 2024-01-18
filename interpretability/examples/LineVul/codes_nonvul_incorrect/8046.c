// commit message FFmpeg@dc5d151568 (target=0, prob=0.6578794, correct=False): avformat/hlsenc: use av_bprintf without buffer limit in replace_int_data_in_filename
/*0   */ static int replace_int_data_in_filename(char *buf, int buf_size, const char *filename, char placeholder, int64_t number)  // (3) 0.06836
/*2   */ {                                                                                                                         // (23) 0.001955
/*4   */     const char *p;                                                                                                        // (19) 0.01562
/*6   */     char *q, buf1[20], c;                                                                                                 // (13) 0.02734
/*8   */     int nd, len, addchar_count;                                                                                           // (14) 0.02734
/*10  */     int found_count = 0;                                                                                                  // (18) 0.01953
/*14  */     q = buf;                                                                                                              // (22) 0.01367
/*16  */     p = filename;                                                                                                         // (21) 0.01367
/*18  */     for (;;) {                                                                                                            // (20) 0.01562
/*20  */         c = *p;                                                                                                           // (16) 0.02344
/*22  */         if (c == '\0')                                                                                                    // (12) 0.0293
/*24  */             break;                                                                                                        // (15) 0.02539
/*26  */         if (c == '%' && *(p+1) == '%')  // %%                                                                             // (5) 0.05469
/*28  */             addchar_count = 2;                                                                                            // (10) 0.03516
/*30  */         else if (c == '%' && (av_isdigit(*(p+1)) || *(p+1) == placeholder)) {                                             // (1) 0.07617
/*32  */             nd = 0;                                                                                                       // (11) 0.03125
/*34  */             addchar_count = 1;                                                                                            // (9) 0.03516
/*36  */             while (av_isdigit(*(p + addchar_count))) {                                                                    // (6) 0.05469
/*38  */                 nd = nd * 10 + *(p + addchar_count) - '0';                                                                // (2) 0.07031
/*40  */                 addchar_count++;                                                                                          // (8) 0.03906
/*42  */             }                                                                                                             // (17) 0.02344
/*46  */             if (*(p + addchar_count) == placeholder) {                                                                    // (7) 0.04883
/*48  */                 len = snprintf(buf1, sizeof(buf1), "%0*"PRId64, (number < 0) ? nd : nd++, number);                        // (0) 0.09961
/*50  */                 if (len < 1)  // returned error or empty buf1                                                             // (4) 0.05664
/*52  */                     goto fail;                                                                                            // 0.0
/*54  */                 if ((q - buf + len) > buf_size - 1)                                                                       // 0.0
/*56  */                     goto fail;                                                                                            // 0.0
/*58  */                 memcpy(q, buf1, len);                                                                                     // 0.0
/*60  */                 q += len;                                                                                                 // 0.0
/*62  */                 p += (addchar_count + 1);                                                                                 // 0.0
/*64  */                 addchar_count = 0;                                                                                        // 0.0
/*66  */                 found_count++;                                                                                            // 0.0
/*68  */             }                                                                                                             // 0.0
/*72  */         } else                                                                                                            // 0.0
/*74  */             addchar_count = 1;                                                                                            // 0.0
/*78  */         while (addchar_count--)                                                                                           // 0.0
/*80  */             if ((q - buf) < buf_size - 1)                                                                                 // 0.0
/*82  */                 *q++ = *p++;                                                                                              // 0.0
/*84  */             else                                                                                                          // 0.0
/*86  */                 goto fail;                                                                                                // 0.0
/*88  */     }                                                                                                                     // 0.0
/*90  */     *q = '\0';                                                                                                            // 0.0
/*92  */     return found_count;                                                                                                   // 0.0
/*94  */ fail:                                                                                                                     // 0.0
/*96  */     *q = '\0';                                                                                                            // 0.0
/*98  */     return -1;                                                                                                            // 0.0
/*100 */ }                                                                                                                         // 0.0
