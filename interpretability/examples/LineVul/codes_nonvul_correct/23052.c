// commit message qemu@47c16ed56a (target=0, prob=0.2378226, correct=True): kvm: initialize qemu_host_page_size
/*0   */ static void page_init(void)                                                 // (21) 0.01563
/*2   */ {                                                                           // (30) 0.001953
/*4   */     /* NOTE: we can always suppose that qemu_host_page_size >=              // (9) 0.04102
/*6   */        TARGET_PAGE_SIZE */                                                  // (16) 0.02734
/*8   */ #ifdef _WIN32                                                               // (22) 0.01172
/*10  */     {                                                                       // (23) 0.007812
/*12  */         SYSTEM_INFO system_info;                                            // (17) 0.02734
/*16  */         GetSystemInfo(&system_info);                                        // (15) 0.0293
/*18  */         qemu_real_host_page_size = system_info.dwPageSize;                  // (1) 0.05469
/*20  */     }                                                                       // (24) 0.007812
/*22  */ #else                                                                       // (29) 0.003906
/*24  */     qemu_real_host_page_size = getpagesize();                               // (11) 0.03711
/*26  */ #endif                                                                      // (28) 0.003906
/*28  */     if (qemu_host_page_size == 0) {                                         // (13) 0.03516
/*30  */         qemu_host_page_size = qemu_real_host_page_size;                     // (0) 0.05664
/*32  */     }                                                                       // (25) 0.007812
/*34  */     if (qemu_host_page_size < TARGET_PAGE_SIZE) {                           // (7) 0.04687
/*36  */         qemu_host_page_size = TARGET_PAGE_SIZE;                             // (5) 0.04883
/*38  */     }                                                                       // (26) 0.007812
/*40  */     qemu_host_page_mask = ~(qemu_host_page_size - 1);                       // (3) 0.05273
/*44  */ #if defined(CONFIG_BSD) && defined(CONFIG_USER_ONLY)                        // (10) 0.03906
/*46  */     {                                                                       // (27) 0.007812
/*48  */ #ifdef HAVE_KINFO_GETVMMAP                                                  // (20) 0.02344
/*50  */         struct kinfo_vmentry *freep;                                        // (12) 0.03516
/*52  */         int i, cnt;                                                         // (18) 0.02539
/*56  */         freep = kinfo_getvmmap(getpid(), &cnt);                             // (4) 0.04883
/*58  */         if (freep) {                                                        // (19) 0.02539
/*60  */             mmap_lock();                                                    // (14) 0.03125
/*62  */             for (i = 0; i < cnt; i++) {                                     // (6) 0.04883
/*64  */                 unsigned long startaddr, endaddr;                           // (8) 0.04492
/*68  */                 startaddr = freep[i].kve_start;                             // (2) 0.05469
/*70  */                 endaddr = freep[i].kve_end;                                 // 0.0
/*72  */                 if (h2g_valid(startaddr)) {                                 // 0.0
/*74  */                     startaddr = h2g(startaddr) & TARGET_PAGE_MASK;          // 0.0
/*78  */                     if (h2g_valid(endaddr)) {                               // 0.0
/*80  */                         endaddr = h2g(endaddr);                             // 0.0
/*82  */                         page_set_flags(startaddr, endaddr, PAGE_RESERVED);  // 0.0
/*84  */                     } else {                                                // 0.0
/*86  */ #if TARGET_ABI_BITS <= L1_MAP_ADDR_SPACE_BITS                               // 0.0
/*88  */                         endaddr = ~0ul;                                     // 0.0
/*90  */                         page_set_flags(startaddr, endaddr, PAGE_RESERVED);  // 0.0
/*92  */ #endif                                                                      // 0.0
/*94  */                     }                                                       // 0.0
/*96  */                 }                                                           // 0.0
/*98  */             }                                                               // 0.0
/*100 */             free(freep);                                                    // 0.0
/*102 */             mmap_unlock();                                                  // 0.0
/*104 */         }                                                                   // 0.0
/*106 */ #else                                                                       // 0.0
/*108 */         FILE *f;                                                            // 0.0
/*112 */         last_brk = (unsigned long)sbrk(0);                                  // 0.0
/*116 */         f = fopen("/compat/linux/proc/self/maps", "r");                     // 0.0
/*118 */         if (f) {                                                            // 0.0
/*120 */             mmap_lock();                                                    // 0.0
/*124 */             do {                                                            // 0.0
/*126 */                 unsigned long startaddr, endaddr;                           // 0.0
/*128 */                 int n;                                                      // 0.0
/*132 */                 n = fscanf(f, "%lx-%lx %*[^\n]\n", &startaddr, &endaddr);   // 0.0
/*136 */                 if (n == 2 && h2g_valid(startaddr)) {                       // 0.0
/*138 */                     startaddr = h2g(startaddr) & TARGET_PAGE_MASK;          // 0.0
/*142 */                     if (h2g_valid(endaddr)) {                               // 0.0
/*144 */                         endaddr = h2g(endaddr);                             // 0.0
/*146 */                     } else {                                                // 0.0
/*148 */                         endaddr = ~0ul;                                     // 0.0
/*150 */                     }                                                       // 0.0
/*152 */                     page_set_flags(startaddr, endaddr, PAGE_RESERVED);      // 0.0
/*154 */                 }                                                           // 0.0
/*156 */             } while (!feof(f));                                             // 0.0
/*160 */             fclose(f);                                                      // 0.0
/*162 */             mmap_unlock();                                                  // 0.0
/*164 */         }                                                                   // 0.0
/*166 */ #endif                                                                      // 0.0
/*168 */     }                                                                       // 0.0
/*170 */ #endif                                                                      // 0.0
/*172 */ }                                                                           // 0.0
