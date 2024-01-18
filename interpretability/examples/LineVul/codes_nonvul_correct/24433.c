// commit message FFmpeg@2bb62455c8 (target=0, prob=0.13104959, correct=True): Revert "lavu: add snprintf(), vsnprint() and strtod() replacements for MS runtime."
/*0  */ static char *check_nan_suffix(char *s)                              // (3) 0.09211
/*2  */ {                                                                   // (8) 0.006579
/*4  */     char *start = s;                                                // (6) 0.05921
/*8  */     if (*s++ != '(')                                                // (4) 0.07237
/*10 */         return start;                                               // (5) 0.06579
/*14 */     while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') ||  // (0) 0.2171
/*16 */            (*s >= '0' && *s <= '9') ||  *s == '_')                  // (1) 0.2039
/*18 */         s++;                                                        // (7) 0.05921
/*22 */     return *s == ')' ? s + 1 : start;                               // (2) 0.1053
/*24 */ }                                                                   // (9) 0.006579
