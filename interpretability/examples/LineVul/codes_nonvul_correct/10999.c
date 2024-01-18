// commit message qemu@9a78eead0c (target=0, prob=0.01990924, correct=True): target-xxx: Use fprintf_function (format checking)
/*0  */ void m68k_cpu_list(FILE *f, int (*cpu_fprintf)(FILE *f, const char *fmt, ...))  // (1) 0.2783
/*2  */ {                                                                               // (5) 0.008696
/*4  */     unsigned int i;                                                             // (3) 0.06087
/*8  */     for (i = 0; m68k_cpu_defs[i].name; i++) {                                   // (2) 0.2174
/*10 */         (*cpu_fprintf)(f, "%s\n", m68k_cpu_defs[i].name);                       // (0) 0.287
/*12 */     }                                                                           // (4) 0.03478
/*14 */ }                                                                               // (6) 0.008696
