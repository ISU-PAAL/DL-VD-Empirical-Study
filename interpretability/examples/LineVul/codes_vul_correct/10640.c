// commit message qemu@21ce148c7e (target=1, prob=0.9920007, correct=True): tests: cris: force inlining
/*0 */ static inline int cris_addc_pi_m(int a, int **b)           // (1) 0.3016
/*2 */ {                                                          // (3) 0.01587
/*4 */ 	asm volatile ("addc [%1+], %0\n" : "+r" (a), "+b" (*b));  // (0) 0.4603
/*6 */ 	return a;                                                 // (2) 0.06349
/*8 */ }                                                          // (4) 0.01587
