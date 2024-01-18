// commit message FFmpeg@2bb62455c8 (target=0, prob=0.22536585, correct=True): Revert "lavu: add snprintf(), vsnprint() and strtod() replacements for MS runtime."
/*0  */ double avpriv_strtod(char *restrict nptr, char **restrict endptr)            // (8) 0.04297
/*2  */ {                                                                            // (29) 0.001953
/*4  */     char *end;                                                               // (27) 0.01367
/*6  */     double res;                                                              // (28) 0.01172
/*10 */     /* Skip leading spaces */                                                // (26) 0.01563
/*12 */     while (isspace(*nptr))                                                   // (24) 0.02148
/*14 */         nptr++;                                                              // (25) 0.01953
/*18 */     if (!av_strncasecmp(nptr, "infinity", 8)) {                              // (9) 0.04297
/*20 */         end = nptr + 8;                                                      // (11) 0.02734
/*22 */         res = INFINITY;                                                      // (19) 0.02539
/*24 */     } else if (!av_strncasecmp(nptr, "inf", 3)) {                            // (4) 0.04492
/*26 */         end = nptr + 3;                                                      // (12) 0.02734
/*28 */         res = INFINITY;                                                      // (20) 0.02539
/*30 */     } else if (!av_strncasecmp(nptr, "+infinity", 9)) {                      // (1) 0.04687
/*32 */         end = nptr + 9;                                                      // (13) 0.02734
/*34 */         res = INFINITY;                                                      // (21) 0.02539
/*36 */     } else if (!av_strncasecmp(nptr, "+inf", 4)) {                           // (5) 0.04492
/*38 */         end = nptr + 4;                                                      // (14) 0.02734
/*40 */         res = INFINITY;                                                      // (22) 0.02539
/*42 */     } else if (!av_strncasecmp(nptr, "-infinity", 9)) {                      // (2) 0.04687
/*44 */         end = nptr + 9;                                                      // (15) 0.02734
/*46 */         res = -INFINITY;                                                     // (18) 0.02734
/*48 */     } else if (!av_strncasecmp(nptr, "-inf", 4)) {                           // (7) 0.04492
/*50 */         end = nptr + 4;                                                      // (16) 0.02734
/*52 */         res = -INFINITY;                                                     // (17) 0.02734
/*54 */     } else if (!av_strncasecmp(nptr, "nan", 3)) {                            // (3) 0.04492
/*56 */         end = check_nan_suffix(nptr + 3);                                    // (10) 0.04102
/*58 */         res = NAN;                                                           // (23) 0.02344
/*60 */     } else if (!av_strncasecmp(nptr, "+nan", 4) ||                           // (6) 0.04492
/*62 */                !av_strncasecmp(nptr, "-nan", 4)) {                           // (0) 0.06055
/*64 */         end = check_nan_suffix(nptr + 4);                                    // 0.0
/*66 */         res = NAN;                                                           // 0.0
/*68 */     } else if (!av_strncasecmp(nptr, "0x", 2) ||                             // 0.0
/*70 */                !av_strncasecmp(nptr, "-0x", 3) ||                            // 0.0
/*72 */                !av_strncasecmp(nptr, "+0x", 3)) {                            // 0.0
/*74 */         /* FIXME this doesn't handle exponents, non-integers (float/double)  // 0.0
/*76 */          * and numbers too large for long long */                            // 0.0
/*78 */         res = strtoll(nptr, &end, 16);                                       // 0.0
/*80 */     } else {                                                                 // 0.0
/*82 */         res = strtod(nptr, &end);                                            // 0.0
/*84 */     }                                                                        // 0.0
/*88 */     if (endptr)                                                              // 0.0
/*90 */         *endptr = end;                                                       // 0.0
/*94 */     return res;                                                              // 0.0
/*96 */ }                                                                            // 0.0
