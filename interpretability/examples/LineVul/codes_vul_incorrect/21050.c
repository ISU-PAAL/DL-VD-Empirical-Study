// commit message FFmpeg@bf5af56875 (target=1, prob=0.2478229, correct=False): license/copyright change - fixed memory leaks
/*0  */ void show_help(void)                                                                          // (23) 0.01367
/*2  */ {                                                                                             // (28) 0.001953
/*4  */     const char *prog;                                                                         // (20) 0.01758
/*6  */     const OptionDef *po;                                                                      // (19) 0.01758
/*8  */     int i, expert;                                                                            // (21) 0.01562
/*10 */                                                                                               // (25) 0.007812
/*12 */     prog = do_play ? "ffplay" : "ffmpeg";                                                     // (11) 0.03516
/*16 */     printf("%s version " FFMPEG_VERSION ", Copyright (c) 2000, 2001, 2002 Gerard Lantau\n",   // (2) 0.0625
/*18 */            prog);                                                                             // (16) 0.02344
/*20 */                                                                                               // (27) 0.007812
/*22 */     if (!do_play) {                                                                           // (18) 0.01953
/*24 */         printf("usage: ffmpeg [[options] -i input_file]... {[options] outfile}...\n"          // (1) 0.06641
/*26 */                "Hyper fast MPEG1/MPEG4/H263/RV and AC3/MPEG audio encoder\n");                // (0) 0.08008
/*28 */     } else {                                                                                  // (24) 0.01172
/*30 */         printf("usage: ffplay [options] input_file...\n"                                      // (6) 0.04492
/*32 */                "Simple audio player\n");                                                      // (8) 0.04102
/*34 */     }                                                                                         // (26) 0.007812
/*36 */                                                                                               // (17) 0.02148
/*38 */     printf("\n"                                                                               // (22) 0.01562
/*40 */            "Main options are:\n");                                                            // (12) 0.0332
/*42 */     for(i=0;i<2;i++) {                                                                        // (14) 0.03125
/*44 */         if (i == 1)                                                                           // (15) 0.02539
/*46 */             printf("\nAdvanced options are:\n");                                              // (9) 0.04102
/*48 */         for(po = options; po->name != NULL; po++) {                                           // (7) 0.04297
/*50 */             char buf[64];                                                                     // (13) 0.03125
/*52 */             expert = (po->flags & OPT_EXPERT) != 0;                                           // (4) 0.05078
/*54 */             if (expert == i) {                                                                // (10) 0.03711
/*56 */                 strcpy(buf, po->name);                                                        // (5) 0.04883
/*58 */                 if (po->flags & HAS_ARG) {                                                    // (3) 0.05273
/*60 */                     strcat(buf, " ");                                                         // 0.0
/*62 */                     strcat(buf, po->argname);                                                 // 0.0
/*64 */                 }                                                                             // 0.0
/*66 */                 printf("-%-17s  %s\n", buf, po->help);                                        // 0.0
/*68 */             }                                                                                 // 0.0
/*70 */         }                                                                                     // 0.0
/*72 */     }                                                                                         // 0.0
/*76 */     exit(1);                                                                                  // 0.0
/*78 */ }                                                                                             // 0.0
