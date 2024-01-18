// commit message FFmpeg@13705b69eb (target=1, prob=0.9821853, correct=True): mem corruption fix
/*0 */ static inline int mirror(int v, int m){  // (3) 0.1594
/*2 */     if     (v<0) return -v;              // (1) 0.2464
/*4 */     else if(v>m) return 2*m-v;           // (0) 0.2464
/*6 */     else         return v;               // (2) 0.2174
/*8 */ }                                        // (4) 0.01449
