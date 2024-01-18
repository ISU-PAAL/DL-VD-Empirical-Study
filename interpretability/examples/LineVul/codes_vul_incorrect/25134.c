// commit message qemu@eb513f82f0 (target=1, prob=0.059627555, correct=False): target-sparc: Don't use {ld, st}*_raw functions
/*0   */ uint64_t helper_ld_asi(CPUSPARCState *env, target_ulong addr, int asi, int size,  // (0) 0.06055
/*2   */                        int sign)                                                  // (3) 0.04883
/*4   */ {                                                                                 // (31) 0.001953
/*6   */     uint64_t ret = 0;                                                             // (20) 0.02148
/*8   */ #if defined(DEBUG_ASI)                                                            // (23) 0.01758
/*10  */     target_ulong last_addr = addr;                                                // (17) 0.02539
/*12  */ #endif                                                                            // (29) 0.003906
/*16  */     if (asi < 0x80) {                                                             // (18) 0.02344
/*18  */         helper_raise_exception(env, TT_PRIV_ACT);                                 // (6) 0.04492
/*20  */     }                                                                             // (28) 0.007812
/*24  */     helper_check_align(env, addr, size - 1);                                      // (8) 0.0332
/*26  */     addr = asi_address_mask(env, asi, addr);                                      // (7) 0.03711
/*30  */     switch (asi) {                                                                // (24) 0.01562
/*32  */     case 0x82: /* Primary no-fault */                                             // (13) 0.0293
/*34  */     case 0x8a: /* Primary no-fault LE */                                          // (9) 0.0332
/*36  */         if (page_check_range(addr, size, PAGE_READ) == -1) {                      // (1) 0.05469
/*38  */ #ifdef DEBUG_ASI                                                                  // (27) 0.01367
/*40  */             dump_asi("read ", last_addr, asi, size, ret);                         // (2) 0.05469
/*42  */ #endif                                                                            // (30) 0.003906
/*44  */             return 0;                                                             // (14) 0.02734
/*46  */         }                                                                         // (25) 0.01562
/*48  */         /* Fall through */                                                        // (21) 0.02148
/*50  */     case 0x80: /* Primary */                                                      // (22) 0.02148
/*52  */     case 0x88: /* Primary LE */                                                   // (19) 0.02344
/*54  */         {                                                                         // (26) 0.01562
/*56  */             switch (size) {                                                       // (12) 0.03125
/*58  */             case 1:                                                               // (15) 0.02734
/*60  */                 ret = ldub_raw(addr);                                             // (4) 0.04883
/*62  */                 break;                                                            // (10) 0.0332
/*64  */             case 2:                                                               // (16) 0.02734
/*66  */                 ret = lduw_raw(addr);                                             // (5) 0.04883
/*68  */                 break;                                                            // (11) 0.0332
/*70  */             case 4:                                                               // 0.0
/*72  */                 ret = ldl_raw(addr);                                              // 0.0
/*74  */                 break;                                                            // 0.0
/*76  */             default:                                                              // 0.0
/*78  */             case 8:                                                               // 0.0
/*80  */                 ret = ldq_raw(addr);                                              // 0.0
/*82  */                 break;                                                            // 0.0
/*84  */             }                                                                     // 0.0
/*86  */         }                                                                         // 0.0
/*88  */         break;                                                                    // 0.0
/*90  */     case 0x83: /* Secondary no-fault */                                           // 0.0
/*92  */     case 0x8b: /* Secondary no-fault LE */                                        // 0.0
/*94  */         if (page_check_range(addr, size, PAGE_READ) == -1) {                      // 0.0
/*96  */ #ifdef DEBUG_ASI                                                                  // 0.0
/*98  */             dump_asi("read ", last_addr, asi, size, ret);                         // 0.0
/*100 */ #endif                                                                            // 0.0
/*102 */             return 0;                                                             // 0.0
/*104 */         }                                                                         // 0.0
/*106 */         /* Fall through */                                                        // 0.0
/*108 */     case 0x81: /* Secondary */                                                    // 0.0
/*110 */     case 0x89: /* Secondary LE */                                                 // 0.0
/*112 */         /* XXX */                                                                 // 0.0
/*114 */         break;                                                                    // 0.0
/*116 */     default:                                                                      // 0.0
/*118 */         break;                                                                    // 0.0
/*120 */     }                                                                             // 0.0
/*124 */     /* Convert from little endian */                                              // 0.0
/*126 */     switch (asi) {                                                                // 0.0
/*128 */     case 0x88: /* Primary LE */                                                   // 0.0
/*130 */     case 0x89: /* Secondary LE */                                                 // 0.0
/*132 */     case 0x8a: /* Primary no-fault LE */                                          // 0.0
/*134 */     case 0x8b: /* Secondary no-fault LE */                                        // 0.0
/*136 */         switch (size) {                                                           // 0.0
/*138 */         case 2:                                                                   // 0.0
/*140 */             ret = bswap16(ret);                                                   // 0.0
/*142 */             break;                                                                // 0.0
/*144 */         case 4:                                                                   // 0.0
/*146 */             ret = bswap32(ret);                                                   // 0.0
/*148 */             break;                                                                // 0.0
/*150 */         case 8:                                                                   // 0.0
/*152 */             ret = bswap64(ret);                                                   // 0.0
/*154 */             break;                                                                // 0.0
/*156 */         default:                                                                  // 0.0
/*158 */             break;                                                                // 0.0
/*160 */         }                                                                         // 0.0
/*162 */     default:                                                                      // 0.0
/*164 */         break;                                                                    // 0.0
/*166 */     }                                                                             // 0.0
/*170 */     /* Convert to signed number */                                                // 0.0
/*172 */     if (sign) {                                                                   // 0.0
/*174 */         switch (size) {                                                           // 0.0
/*176 */         case 1:                                                                   // 0.0
/*178 */             ret = (int8_t) ret;                                                   // 0.0
/*180 */             break;                                                                // 0.0
/*182 */         case 2:                                                                   // 0.0
/*184 */             ret = (int16_t) ret;                                                  // 0.0
/*186 */             break;                                                                // 0.0
/*188 */         case 4:                                                                   // 0.0
/*190 */             ret = (int32_t) ret;                                                  // 0.0
/*192 */             break;                                                                // 0.0
/*194 */         default:                                                                  // 0.0
/*196 */             break;                                                                // 0.0
/*198 */         }                                                                         // 0.0
/*200 */     }                                                                             // 0.0
/*202 */ #ifdef DEBUG_ASI                                                                  // 0.0
/*204 */     dump_asi("read ", last_addr, asi, size, ret);                                 // 0.0
/*206 */ #endif                                                                            // 0.0
/*208 */     return ret;                                                                   // 0.0
/*210 */ }                                                                                 // 0.0
