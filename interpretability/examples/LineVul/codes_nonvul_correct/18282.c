// commit message qemu@6ca8d0fd51 (target=0, prob=0.23297979, correct=True): check for PR_SET_NAME being defined
/*0  */ static void set_proc_name(const char *s)                              // (5) 0.08497
/*2  */ {                                                                     // (11) 0.006536
/*4  */ #ifdef __linux__                                                      // (10) 0.03922
/*6  */     char name[16];                                                    // (7) 0.05229
/*8  */     if (!s)                                                           // (9) 0.04575
/*10 */         return;                                                       // (6) 0.05882
/*12 */     name[sizeof(name) - 1] = 0;                                       // (2) 0.1046
/*14 */     strncpy(name, s, sizeof(name));                                   // (3) 0.09804
/*16 */     /* Could rewrite argv[0] too, but that's a bit more complicated.  // (0) 0.1373
/*18 */        This simple way is enough for `top'. */                        // (1) 0.1046
/*20 */     prctl(PR_SET_NAME, name);                                         // (4) 0.0915
/*22 */ #endif    	                                                           // (8) 0.04575
/*24 */ }                                                                     // (12) 0.006536
