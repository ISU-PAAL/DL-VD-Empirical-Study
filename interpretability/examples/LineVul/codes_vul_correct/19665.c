// commit message FFmpeg@bf5af56875 (target=1, prob=0.60335356, correct=True): license/copyright change - fixed memory leaks
/*0 */ void prepare_grab(void)                                        // (1) 0.1528
/*2 */ {                                                              // (3) 0.02172
/*4 */     fprintf(stderr, "Must supply at least one input file\n");  // (0) 0.4561
/*6 */     exit(1);                                                   // (2) 0.152
/*8 */ }                                                              // (4) 0.02172
