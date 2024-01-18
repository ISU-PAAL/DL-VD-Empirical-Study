// commit message qemu@1e5ffbedde (target=1, prob=0.19902569, correct=False): fixed float to int overflow bug - added ARM host correct roundings for float rounding
/*0 */ void helper_frndint(void)  // (1) 0.2903
/*2 */ {                          // (2) 0.03226
/*4 */     ST0 = rint(ST0);       // (0) 0.3871
/*6 */ }                          // (3) 0.03226
