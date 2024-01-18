// commit message qemu@9fbf4a58c9 (target=1, prob=0.359055, correct=False): target/mips: Check memory permissions with mem_idx
/*0   */ static int get_physical_address (CPUMIPSState *env, hwaddr *physical,                         // (7) 0.04102
/*2   */                                 int *prot, target_ulong real_address,                         // (0) 0.08398
/*4   */                                 int rw, int access_type)                                      // (1) 0.07813
/*6   */ {                                                                                             // (22) 0.001953
/*8   */     /* User mode can only access useg/xuseg */                                                // (17) 0.03125
/*10  */     int user_mode = (env->hflags & MIPS_HFLAG_MODE) == MIPS_HFLAG_UM;                         // (2) 0.06055
/*12  */     int supervisor_mode = (env->hflags & MIPS_HFLAG_MODE) == MIPS_HFLAG_SM;                   // (3) 0.06055
/*14  */     int kernel_mode = !user_mode && !supervisor_mode;                                         // (9) 0.03711
/*16  */ #if defined(TARGET_MIPS64)                                                                    // (20) 0.02148
/*18  */     int UX = (env->CP0_Status & (1 << CP0St_UX)) != 0;                                        // (6) 0.05078
/*20  */     int SX = (env->CP0_Status & (1 << CP0St_SX)) != 0;                                        // (5) 0.05273
/*22  */     int KX = (env->CP0_Status & (1 << CP0St_KX)) != 0;                                        // (4) 0.05469
/*24  */ #endif                                                                                        // (21) 0.003906
/*26  */     int ret = TLBRET_MATCH;                                                                   // (18) 0.02539
/*28  */     /* effective address (modified for KVM T&E kernel segments) */                            // (14) 0.03516
/*30  */     target_ulong address = real_address;                                                      // (19) 0.02539
/*34  */ #define USEG_LIMIT      0x7FFFFFFFUL                                                          // (8) 0.03711
/*36  */ #define KSEG0_BASE      0x80000000UL                                                          // (11) 0.03711
/*38  */ #define KSEG1_BASE      0xA0000000UL                                                          // (13) 0.03711
/*40  */ #define KSEG2_BASE      0xC0000000UL                                                          // (12) 0.03711
/*42  */ #define KSEG3_BASE      0xE0000000UL                                                          // (10) 0.03711
/*46  */ #define KVM_KSEG0_BASE  0x40000000UL                                                          // (15) 0.03516
/*48  */ #define KVM_KSEG2_BASE  0x60000000UL                                                          // (16) 0.03516
/*52  */     if (kvm_enabled()) {                                                                      // 0.0
/*54  */         /* KVM T&E adds guest kernel segments in useg */                                      // 0.0
/*56  */         if (real_address >= KVM_KSEG0_BASE) {                                                 // 0.0
/*58  */             if (real_address < KVM_KSEG2_BASE) {                                              // 0.0
/*60  */                 /* kseg0 */                                                                   // 0.0
/*62  */                 address += KSEG0_BASE - KVM_KSEG0_BASE;                                       // 0.0
/*64  */             } else if (real_address <= USEG_LIMIT) {                                          // 0.0
/*66  */                 /* kseg2/3 */                                                                 // 0.0
/*68  */                 address += KSEG2_BASE - KVM_KSEG2_BASE;                                       // 0.0
/*70  */             }                                                                                 // 0.0
/*72  */         }                                                                                     // 0.0
/*74  */     }                                                                                         // 0.0
/*78  */     if (address <= USEG_LIMIT) {                                                              // 0.0
/*80  */         /* useg */                                                                            // 0.0
/*82  */         if (env->CP0_Status & (1 << CP0St_ERL)) {                                             // 0.0
/*84  */             *physical = address & 0xFFFFFFFF;                                                 // 0.0
/*86  */             *prot = PAGE_READ | PAGE_WRITE;                                                   // 0.0
/*88  */         } else {                                                                              // 0.0
/*90  */             ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);  // 0.0
/*92  */         }                                                                                     // 0.0
/*94  */ #if defined(TARGET_MIPS64)                                                                    // 0.0
/*96  */     } else if (address < 0x4000000000000000ULL) {                                             // 0.0
/*98  */         /* xuseg */                                                                           // 0.0
/*100 */         if (UX && address <= (0x3FFFFFFFFFFFFFFFULL & env->SEGMask)) {                        // 0.0
/*102 */             ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);  // 0.0
/*104 */         } else {                                                                              // 0.0
/*106 */             ret = TLBRET_BADADDR;                                                             // 0.0
/*108 */         }                                                                                     // 0.0
/*110 */     } else if (address < 0x8000000000000000ULL) {                                             // 0.0
/*112 */         /* xsseg */                                                                           // 0.0
/*114 */         if ((supervisor_mode || kernel_mode) &&                                               // 0.0
/*116 */             SX && address <= (0x7FFFFFFFFFFFFFFFULL & env->SEGMask)) {                        // 0.0
/*118 */             ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);  // 0.0
/*120 */         } else {                                                                              // 0.0
/*122 */             ret = TLBRET_BADADDR;                                                             // 0.0
/*124 */         }                                                                                     // 0.0
/*126 */     } else if (address < 0xC000000000000000ULL) {                                             // 0.0
/*128 */         /* xkphys */                                                                          // 0.0
/*130 */         if (kernel_mode && KX &&                                                              // 0.0
/*132 */             (address & 0x07FFFFFFFFFFFFFFULL) <= env->PAMask) {                               // 0.0
/*134 */             *physical = address & env->PAMask;                                                // 0.0
/*136 */             *prot = PAGE_READ | PAGE_WRITE;                                                   // 0.0
/*138 */         } else {                                                                              // 0.0
/*140 */             ret = TLBRET_BADADDR;                                                             // 0.0
/*142 */         }                                                                                     // 0.0
/*144 */     } else if (address < 0xFFFFFFFF80000000ULL) {                                             // 0.0
/*146 */         /* xkseg */                                                                           // 0.0
/*148 */         if (kernel_mode && KX &&                                                              // 0.0
/*150 */             address <= (0xFFFFFFFF7FFFFFFFULL & env->SEGMask)) {                              // 0.0
/*152 */             ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);  // 0.0
/*154 */         } else {                                                                              // 0.0
/*156 */             ret = TLBRET_BADADDR;                                                             // 0.0
/*158 */         }                                                                                     // 0.0
/*160 */ #endif                                                                                        // 0.0
/*162 */     } else if (address < (int32_t)KSEG1_BASE) {                                               // 0.0
/*164 */         /* kseg0 */                                                                           // 0.0
/*166 */         if (kernel_mode) {                                                                    // 0.0
/*168 */             *physical = address - (int32_t)KSEG0_BASE;                                        // 0.0
/*170 */             *prot = PAGE_READ | PAGE_WRITE;                                                   // 0.0
/*172 */         } else {                                                                              // 0.0
/*174 */             ret = TLBRET_BADADDR;                                                             // 0.0
/*176 */         }                                                                                     // 0.0
/*178 */     } else if (address < (int32_t)KSEG2_BASE) {                                               // 0.0
/*180 */         /* kseg1 */                                                                           // 0.0
/*182 */         if (kernel_mode) {                                                                    // 0.0
/*184 */             *physical = address - (int32_t)KSEG1_BASE;                                        // 0.0
/*186 */             *prot = PAGE_READ | PAGE_WRITE;                                                   // 0.0
/*188 */         } else {                                                                              // 0.0
/*190 */             ret = TLBRET_BADADDR;                                                             // 0.0
/*192 */         }                                                                                     // 0.0
/*194 */     } else if (address < (int32_t)KSEG3_BASE) {                                               // 0.0
/*196 */         /* sseg (kseg2) */                                                                    // 0.0
/*198 */         if (supervisor_mode || kernel_mode) {                                                 // 0.0
/*200 */             ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);  // 0.0
/*202 */         } else {                                                                              // 0.0
/*204 */             ret = TLBRET_BADADDR;                                                             // 0.0
/*206 */         }                                                                                     // 0.0
/*208 */     } else {                                                                                  // 0.0
/*210 */         /* kseg3 */                                                                           // 0.0
/*212 */         /* XXX: debug segment is not emulated */                                              // 0.0
/*214 */         if (kernel_mode) {                                                                    // 0.0
/*216 */             ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);  // 0.0
/*218 */         } else {                                                                              // 0.0
/*220 */             ret = TLBRET_BADADDR;                                                             // 0.0
/*222 */         }                                                                                     // 0.0
/*224 */     }                                                                                         // 0.0
/*226 */     return ret;                                                                               // 0.0
/*228 */ }                                                                                             // 0.0
