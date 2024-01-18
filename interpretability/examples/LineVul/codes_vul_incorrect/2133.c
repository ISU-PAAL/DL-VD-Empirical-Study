// commit message qemu@bd88c780e6 (target=1, prob=0.01013351, correct=False): qom/cpu: remove host_tid field
/*0  */ static inline int cpu_gdb_index(CPUState *cpu)  // (0) 0.2113
/*2  */ {                                               // (6) 0.01408
/*4  */ #if defined(CONFIG_USER_ONLY)                   // (2) 0.169
/*6  */     return cpu->host_tid;                       // (3) 0.1549
/*8  */ #else                                           // (4) 0.02817
/*10 */     return cpu->cpu_index + 1;                  // (1) 0.169
/*12 */ #endif                                          // (5) 0.02817
/*14 */ }                                               // (7) 0.01408
