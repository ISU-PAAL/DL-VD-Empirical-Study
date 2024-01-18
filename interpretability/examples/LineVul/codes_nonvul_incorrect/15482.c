// commit message qemu@076b35b5a5 (target=0, prob=0.5255663, correct=False): machine: add default_ram_size to machine class
/*0   */ static void set_memory_options(uint64_t *ram_slots, ram_addr_t *maxram_size)      // (3) 0.05664
/*2   */ {                                                                                 // (23) 0.001954
/*4   */     uint64_t sz;                                                                  // (19) 0.01953
/*6   */     const char *mem_str;                                                          // (18) 0.01953
/*8   */     const char *maxmem_str, *slots_str;                                           // (13) 0.0332
/*10  */     const ram_addr_t default_ram_size = (ram_addr_t)DEFAULT_RAM_SIZE *            // (4) 0.05664
/*12  */                                         1024 * 1024;                              // (0) 0.08398
/*14  */     QemuOpts *opts = qemu_find_opts_singleton("memory");                          // (6) 0.05078
/*18  */     sz = 0;                                                                       // (21) 0.01562
/*20  */     mem_str = qemu_opt_get(opts, "size");                                         // (11) 0.04102
/*22  */     if (mem_str) {                                                                // (20) 0.01953
/*24  */         if (!*mem_str) {                                                          // (16) 0.0293
/*26  */             error_report("missing 'size' option value");                          // (9) 0.04297
/*28  */             exit(EXIT_FAILURE);                                                   // (12) 0.03906
/*30  */         }                                                                         // (22) 0.01562
/*34  */         sz = qemu_opt_get_size(opts, "size", ram_size);                           // (2) 0.05859
/*38  */         /* Fix up legacy suffix-less format */                                    // (15) 0.03125
/*40  */         if (g_ascii_isdigit(mem_str[strlen(mem_str) - 1])) {                      // (1) 0.06836
/*42  */             uint64_t overflow_check = sz;                                         // (10) 0.04297
/*46  */             sz <<= 20;                                                            // (14) 0.0332
/*48  */             if ((sz >> 20) != overflow_check) {                                   // (8) 0.04687
/*50  */                 error_report("too large 'size' option value");                    // (5) 0.05273
/*52  */                 exit(EXIT_FAILURE);                                               // (7) 0.04687
/*54  */             }                                                                     // (17) 0.02344
/*56  */         }                                                                         // 0.0
/*58  */     }                                                                             // 0.0
/*62  */     /* backward compatibility behaviour for case "-m 0" */                        // 0.0
/*64  */     if (sz == 0) {                                                                // 0.0
/*66  */         sz = default_ram_size;                                                    // 0.0
/*68  */     }                                                                             // 0.0
/*72  */     sz = QEMU_ALIGN_UP(sz, 8192);                                                 // 0.0
/*74  */     ram_size = sz;                                                                // 0.0
/*76  */     if (ram_size != sz) {                                                         // 0.0
/*78  */         error_report("ram size too large");                                       // 0.0
/*80  */         exit(EXIT_FAILURE);                                                       // 0.0
/*82  */     }                                                                             // 0.0
/*86  */     /* store value for the future use */                                          // 0.0
/*88  */     qemu_opt_set_number(opts, "size", ram_size, &error_abort);                    // 0.0
/*90  */     *maxram_size = ram_size;                                                      // 0.0
/*94  */     maxmem_str = qemu_opt_get(opts, "maxmem");                                    // 0.0
/*96  */     slots_str = qemu_opt_get(opts, "slots");                                      // 0.0
/*98  */     if (maxmem_str && slots_str) {                                                // 0.0
/*100 */         uint64_t slots;                                                           // 0.0
/*104 */         sz = qemu_opt_get_size(opts, "maxmem", 0);                                // 0.0
/*106 */         slots = qemu_opt_get_number(opts, "slots", 0);                            // 0.0
/*108 */         if (sz < ram_size) {                                                      // 0.0
/*110 */             error_report("invalid value of -m option maxmem: "                    // 0.0
/*112 */                          "maximum memory size (0x%" PRIx64 ") must be at least "  // 0.0
/*114 */                          "the initial memory size (0x" RAM_ADDR_FMT ")",          // 0.0
/*116 */                          sz, ram_size);                                           // 0.0
/*118 */             exit(EXIT_FAILURE);                                                   // 0.0
/*120 */         } else if (sz > ram_size) {                                               // 0.0
/*122 */             if (!slots) {                                                         // 0.0
/*124 */                 error_report("invalid value of -m option: maxmem was "            // 0.0
/*126 */                              "specified, but no hotplug slots were specified");   // 0.0
/*128 */                 exit(EXIT_FAILURE);                                               // 0.0
/*130 */             }                                                                     // 0.0
/*132 */         } else if (slots) {                                                       // 0.0
/*134 */             error_report("invalid value of -m option maxmem: "                    // 0.0
/*136 */                          "memory slots were specified but maximum memory size "   // 0.0
/*138 */                          "(0x%" PRIx64 ") is equal to the initial memory size "   // 0.0
/*140 */                          "(0x" RAM_ADDR_FMT ")", sz, ram_size);                   // 0.0
/*142 */             exit(EXIT_FAILURE);                                                   // 0.0
/*144 */         }                                                                         // 0.0
/*148 */         *maxram_size = sz;                                                        // 0.0
/*150 */         *ram_slots = slots;                                                       // 0.0
/*152 */     } else if ((!maxmem_str && slots_str) ||                                      // 0.0
/*154 */             (maxmem_str && !slots_str)) {                                         // 0.0
/*156 */         error_report("invalid -m option value: missing "                          // 0.0
/*158 */                 "'%s' option", slots_str ? "maxmem" : "slots");                   // 0.0
/*160 */         exit(EXIT_FAILURE);                                                       // 0.0
/*162 */     }                                                                             // 0.0
/*164 */ }                                                                                 // 0.0
