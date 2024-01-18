// commit message FFmpeg@f929ab0569 (target=0, prob=0.38295406, correct=True): cosmetics: Write NULL pointer equality checks more compactly
/*0  */ static int getopt(int argc, char *argv[], char *opts)                     // (8) 0.03906
/*2  */ {                                                                         // (29) 0.001953
/*4  */     static int sp = 1;                                                    // (21) 0.01758
/*6  */     int c;                                                                // (27) 0.01172
/*8  */     char *cp;                                                             // (26) 0.01367
/*12 */     if (sp == 1)                                                          // (22) 0.01758
/*14 */         if (optind >= argc ||                                             // (11) 0.0293
/*16 */             argv[optind][0] != '-' || argv[optind][1] == '\0')            // (0) 0.07031
/*18 */             return EOF;                                                   // (13) 0.0293
/*20 */         else if (!strcmp(argv[optind], "--")) {                           // (7) 0.04492
/*22 */             optind++;                                                     // (17) 0.02734
/*24 */             return EOF;                                                   // (14) 0.0293
/*26 */         }                                                                 // (24) 0.01562
/*28 */     optopt = c = argv[optind][sp];                                        // (10) 0.03125
/*30 */     if (c == ':' || (cp = strchr(opts, c)) == NULL) {                     // (2) 0.05078
/*32 */         fprintf(stderr, ": illegal option -- %c\n", c);                   // (4) 0.05078
/*34 */         if (argv[optind][++sp] == '\0') {                                 // (5) 0.04687
/*36 */             optind++;                                                     // (18) 0.02734
/*38 */             sp = 1;                                                       // (16) 0.0293
/*40 */         }                                                                 // (25) 0.01562
/*42 */         return '?';                                                       // (20) 0.02148
/*44 */     }                                                                     // (28) 0.007812
/*46 */     if (*++cp == ':') {                                                   // (19) 0.02344
/*48 */         if (argv[optind][sp+1] != '\0')                                   // (6) 0.04687
/*50 */             optarg = &argv[optind++][sp+1];                               // (3) 0.05078
/*52 */         else if(++optind >= argc) {                                       // (9) 0.03516
/*54 */             fprintf(stderr, ": option requires an argument -- %c\n", c);  // (1) 0.0625
/*56 */             sp = 1;                                                       // (15) 0.0293
/*58 */             return '?';                                                   // (12) 0.0293
/*60 */         } else                                                            // (23) 0.01758
/*62 */             optarg = argv[optind++];                                      // 0.0
/*64 */         sp = 1;                                                           // 0.0
/*66 */     } else {                                                              // 0.0
/*68 */         if (argv[optind][++sp] == '\0') {                                 // 0.0
/*70 */             sp = 1;                                                       // 0.0
/*72 */             optind++;                                                     // 0.0
/*74 */         }                                                                 // 0.0
/*76 */         optarg = NULL;                                                    // 0.0
/*78 */     }                                                                     // 0.0
/*82 */     return c;                                                             // 0.0
/*84 */ }                                                                         // 0.0
