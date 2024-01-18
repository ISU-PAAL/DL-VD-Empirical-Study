// commit message FFmpeg@c896580087 (target=0, prob=0.29025304, correct=True): Re-indent to more closely follow general coding standards used in other parts of FFmpeg. Also change a starting condition; while (condition) { ... bla = bla->next; } loop into a proper for() loop.
/*0  */ static int hex_to_data(uint8_t *data, const char *p)  // (3) 0.05525
/*2  */ {                                                     // (24) 0.002762
/*4  */     int c, len, v;                                    // (16) 0.02762
/*8  */     len = 0;                                          // (20) 0.01934
/*10 */     v = 1;                                            // (21) 0.01934
/*12 */     for(;;) {                                         // (17) 0.0221
/*14 */         skip_spaces(&p);                              // (12) 0.03867
/*16 */         if (*p == '\0')                               // (9) 0.04144
/*18 */             break;                                    // (13) 0.03591
/*20 */         c = toupper((unsigned char)*p++);             // (5) 0.04972
/*22 */         if (c >= '0' && c <= '9')                     // (4) 0.05525
/*24 */             c = c - '0';                              // (6) 0.04972
/*26 */         else if (c >= 'A' && c <= 'F')                // (1) 0.05801
/*28 */             c = c - 'A' + 10;                         // (2) 0.05801
/*30 */         else                                          // (18) 0.0221
/*32 */             break;                                    // (14) 0.03591
/*34 */         v = (v << 4) | c;                             // (7) 0.04696
/*36 */         if (v & 0x100) {                              // (8) 0.0442
/*38 */             if (data)                                 // (10) 0.04144
/*40 */                 data[len] = v;                        // (0) 0.06077
/*42 */             len++;                                    // (15) 0.03591
/*44 */             v = 1;                                    // (11) 0.04144
/*46 */         }                                             // (19) 0.0221
/*48 */     }                                                 // (23) 0.01105
/*50 */     return len;                                       // (22) 0.01657
/*52 */ }                                                     // (25) 0.002762
