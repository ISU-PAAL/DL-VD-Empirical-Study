// commit message qemu@1e356fc14b (target=1, prob=0.10429499, correct=False): mem-prealloc: reduce large guest start-up and migration time.
/*0  */ void os_mem_prealloc(int fd, char *area, size_t memory, Error **errp)  // (0) 0.2114
/*2  */ {                                                                      // (7) 0.008131
/*4  */     int i;                                                             // (5) 0.04878
/*6  */     size_t pagesize = getpagesize();                                   // (4) 0.1057
/*10 */     memory = (memory + pagesize - 1) & -pagesize;                      // (3) 0.1463
/*12 */     for (i = 0; i < memory / pagesize; i++) {                          // (2) 0.1545
/*14 */         memset(area + pagesize * i, 0, 1);                             // (1) 0.1707
/*16 */     }                                                                  // (6) 0.03252
/*18 */ }                                                                      // (8) 0.00813
