// commit message qemu@f61eddcb2b (target=0, prob=0.18564345, correct=True): vl.c: Replace fprintf(stderr) with error_report()
/*0  */ static int parallel_parse(const char *devname)                     // (8) 0.0424
/*2  */ {                                                                  // (18) 0.003534
/*4  */     static int index = 0;                                          // (12) 0.0318
/*6  */     char label[32];                                                // (13) 0.02827
/*10 */     if (strcmp(devname, "none") == 0)                              // (6) 0.06007
/*12 */         return 0;                                                  // (11) 0.03534
/*14 */     if (index == MAX_PARALLEL_PORTS) {                             // (5) 0.0636
/*16 */         fprintf(stderr, "qemu: too many parallel ports\n");        // (2) 0.09187
/*18 */         exit(1);                                                   // (9) 0.03887
/*20 */     }                                                              // (16) 0.01413
/*22 */     snprintf(label, sizeof(label), "parallel%d", index);           // (4) 0.07067
/*24 */     parallel_hds[index] = qemu_chr_new(label, devname, NULL);      // (1) 0.09541
/*26 */     if (!parallel_hds[index]) {                                    // (7) 0.04947
/*28 */         fprintf(stderr, "qemu: could not connect parallel device"  // (3) 0.08834
/*30 */                 " to character backend '%s'\n", devname);          // (0) 0.1025
/*32 */         return -1;                                                 // (10) 0.03887
/*34 */     }                                                              // (17) 0.01413
/*36 */     index++;                                                       // (15) 0.01767
/*38 */     return 0;                                                      // (14) 0.0212
/*40 */ }                                                                  // (19) 0.003534
