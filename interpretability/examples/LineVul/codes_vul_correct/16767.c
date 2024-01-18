// commit message FFmpeg@92e483f8ed (target=1, prob=0.9947429, correct=True): all: use FFDIFFSIGN to resolve possible undefined behavior in comparators
/*0 */ static int compare_int64(const void *a, const void *b)  // (2) 0.2125
/*2 */ {                                                       // (3) 0.0125
/*4 */     int64_t va = *(int64_t *)a, vb = *(int64_t *)b;     // (0) 0.375
/*6 */     return va < vb ? -1 : va > vb ? +1 : 0;             // (1) 0.275
/*8 */ }                                                       // (4) 0.0125
