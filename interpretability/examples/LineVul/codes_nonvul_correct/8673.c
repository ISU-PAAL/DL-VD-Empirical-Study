// commit message qemu@f17fd4fdf0 (target=0, prob=0.15286356, correct=True): util/cutils: Return qemu_strtosz*() error and value separately
/*0  */ static int64_t do_strtosz(const char *nptr, char **end,             // (2) 0.04297
/*2  */                           const char default_suffix, int64_t unit)  // (0) 0.07422
/*4  */ {                                                                   // (39) 0.001953
/*6  */     int64_t retval;                                                 // (23) 0.01953
/*8  */     char *endptr;                                                   // (28) 0.01563
/*10 */     unsigned char c;                                                // (31) 0.01367
/*12 */     int mul_required = 0;                                           // (24) 0.01953
/*14 */     double val, mul, integral, fraction;                            // (16) 0.02344
/*18 */     errno = 0;                                                      // (29) 0.01562
/*20 */     val = strtod(nptr, &endptr);                                    // (5) 0.03125
/*22 */     if (isnan(val) || endptr == nptr || errno != 0) {               // (1) 0.04492
/*24 */         retval = -EINVAL;                                           // (6) 0.0293
/*26 */         goto out;                                                   // (20) 0.01953
/*28 */     }                                                               // (34) 0.007812
/*30 */     fraction = modf(val, &integral);                                // (11) 0.02734
/*32 */     if (fraction != 0) {                                            // (17) 0.02148
/*34 */         mul_required = 1;                                           // (14) 0.02539
/*36 */     }                                                               // (33) 0.007813
/*38 */     c = *endptr;                                                    // (27) 0.01758
/*40 */     mul = suffix_mul(c, unit);                                      // (10) 0.02734
/*42 */     if (mul >= 0) {                                                 // (18) 0.02148
/*44 */         endptr++;                                                   // (25) 0.01953
/*46 */     } else {                                                        // (32) 0.01172
/*48 */         mul = suffix_mul(default_suffix, unit);                     // (3) 0.04102
/*50 */         assert(mul >= 0);                                           // (12) 0.02734
/*52 */     }                                                               // (35) 0.007812
/*54 */     if (mul == 1 && mul_required) {                                 // (7) 0.0293
/*56 */         retval = -EINVAL;                                           // (8) 0.0293
/*58 */         goto out;                                                   // (21) 0.01953
/*60 */     }                                                               // (36) 0.007812
/*62 */     if ((val * mul >= INT64_MAX) || val < 0) {                      // (4) 0.03906
/*64 */         retval = -ERANGE;                                           // (13) 0.02734
/*66 */         goto out;                                                   // (22) 0.01953
/*68 */     }                                                               // (37) 0.007812
/*70 */     retval = val * mul;                                             // (26) 0.01953
/*74 */ out:                                                                // (38) 0.003906
/*76 */     if (end) {                                                      // (30) 0.01562
/*78 */         *end = endptr;                                              // (15) 0.02539
/*80 */     } else if (*endptr) {                                           // (19) 0.02148
/*82 */         retval = -EINVAL;                                           // (9) 0.0293
/*84 */     }                                                               // 0.0
/*88 */     return retval;                                                  // 0.0
/*90 */ }                                                                   // 0.0
