// commit message qemu@e175bce587 (target=1, prob=0.055747166, correct=False): target-i386: Use switch in check_hw_breakpoints()
/*0  */ void helper_single_step(CPUX86State *env)  // (2) 0.1591
/*2  */ {                                          // (6) 0.01136
/*4  */ #ifndef CONFIG_USER_ONLY                   // (4) 0.1136
/*6  */     check_hw_breakpoints(env, 1);          // (3) 0.1591
/*8  */     env->dr[6] |= DR6_BS;                  // (1) 0.1818
/*10 */ #endif                                     // (5) 0.02273
/*12 */     raise_exception(env, EXCP01_DB);       // (0) 0.1818
/*14 */ }                                          // (7) 0.01136
