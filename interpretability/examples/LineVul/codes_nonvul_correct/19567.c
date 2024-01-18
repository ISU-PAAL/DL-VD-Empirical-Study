// commit message qemu@b227a8e9aa (target=0, prob=0.15065242, correct=True): Properly implement non-execute bit on PowerPC segments and PTEs. Fix page protection bits for PowerPC 64 MMU.
/*0   */ static int get_bat (CPUState *env, mmu_ctx_t *ctx,                              // (6) 0.03906
/*2   */                     target_ulong virtual, int rw, int type)                     // (2) 0.0625
/*4   */ {                                                                               // (32) 0.001953
/*6   */     target_ulong *BATlt, *BATut, *BATu, *BATl;                                  // (5) 0.04492
/*8   */     target_ulong base, BEPIl, BEPIu, bl;                                        // (7) 0.03906
/*10  */     int i;                                                                      // (25) 0.01172
/*12  */     int ret = -1;                                                               // (19) 0.01758
/*16  */ #if defined (DEBUG_BATS)                                                        // (20) 0.01758
/*18  */     if (loglevel != 0) {                                                        // (16) 0.02344
/*20  */         fprintf(logfile, "%s: %cBAT v 0x" ADDRX "\n", __func__,                 // (1) 0.06445
/*22  */                 type == ACCESS_CODE ? 'I' : 'D', virtual);                      // (3) 0.0625
/*24  */     }                                                                           // (27) 0.007812
/*26  */ #endif                                                                          // (30) 0.003906
/*28  */     switch (type) {                                                             // (24) 0.01562
/*30  */     case ACCESS_CODE:                                                           // (18) 0.01953
/*32  */         BATlt = env->IBAT[1];                                                   // (8) 0.0332
/*34  */         BATut = env->IBAT[0];                                                   // (9) 0.0332
/*36  */         break;                                                                  // (21) 0.01758
/*38  */     default:                                                                    // (26) 0.009766
/*40  */         BATlt = env->DBAT[1];                                                   // (10) 0.0332
/*42  */         BATut = env->DBAT[0];                                                   // (11) 0.0332
/*44  */         break;                                                                  // (22) 0.01758
/*46  */     }                                                                           // (28) 0.007812
/*48  */ #if defined (DEBUG_BATS)                                                        // (23) 0.01758
/*50  */     if (loglevel != 0) {                                                        // (17) 0.02344
/*52  */         fprintf(logfile, "%s...: %cBAT v 0x" ADDRX "\n", __func__,              // (0) 0.06641
/*54  */                 type == ACCESS_CODE ? 'I' : 'D', virtual);                      // (4) 0.0625
/*56  */     }                                                                           // (29) 0.007812
/*58  */ #endif                                                                          // (31) 0.003906
/*60  */     base = virtual & 0xFFFC0000;                                                // (15) 0.02539
/*62  */     for (i = 0; i < 4; i++) {                                                   // (12) 0.03125
/*64  */         BATu = &BATut[i];                                                       // (13) 0.03125
/*66  */         BATl = &BATlt[i];                                                       // (14) 0.03125
/*68  */         BEPIu = *BATu & 0xF0000000;                                             // 0.0
/*70  */         BEPIl = *BATu & 0x0FFE0000;                                             // 0.0
/*72  */         bl = (*BATu & 0x00001FFC) << 15;                                        // 0.0
/*74  */ #if defined (DEBUG_BATS)                                                        // 0.0
/*76  */         if (loglevel != 0) {                                                    // 0.0
/*78  */             fprintf(logfile, "%s: %cBAT%d v 0x" ADDRX " BATu 0x" ADDRX          // 0.0
/*80  */                     " BATl 0x" ADDRX "\n",                                      // 0.0
/*82  */                     __func__, type == ACCESS_CODE ? 'I' : 'D', i, virtual,      // 0.0
/*84  */                     *BATu, *BATl);                                              // 0.0
/*86  */         }                                                                       // 0.0
/*88  */ #endif                                                                          // 0.0
/*90  */         if ((virtual & 0xF0000000) == BEPIu &&                                  // 0.0
/*92  */             ((virtual & 0x0FFE0000) & ~bl) == BEPIl) {                          // 0.0
/*94  */             /* BAT matches */                                                   // 0.0
/*96  */             if ((msr_pr == 0 && (*BATu & 0x00000002)) ||                        // 0.0
/*98  */                 (msr_pr == 1 && (*BATu & 0x00000001))) {                        // 0.0
/*100 */                 /* Get physical address */                                      // 0.0
/*102 */                 ctx->raddr = (*BATl & 0xF0000000) |                             // 0.0
/*104 */                     ((virtual & 0x0FFE0000 & bl) | (*BATl & 0x0FFE0000)) |      // 0.0
/*106 */                     (virtual & 0x0001F000);                                     // 0.0
/*108 */                 if (*BATl & 0x00000001)                                         // 0.0
/*110 */                     ctx->prot = PAGE_READ;                                      // 0.0
/*112 */                 if (*BATl & 0x00000002)                                         // 0.0
/*114 */                     ctx->prot = PAGE_WRITE | PAGE_READ;                         // 0.0
/*116 */ #if defined (DEBUG_BATS)                                                        // 0.0
/*118 */                 if (loglevel != 0) {                                            // 0.0
/*120 */                     fprintf(logfile, "BAT %d match: r 0x" PADDRX                // 0.0
/*122 */                             " prot=%c%c\n",                                     // 0.0
/*124 */                             i, ctx->raddr, ctx->prot & PAGE_READ ? 'R' : '-',   // 0.0
/*126 */                             ctx->prot & PAGE_WRITE ? 'W' : '-');                // 0.0
/*128 */                 }                                                               // 0.0
/*130 */ #endif                                                                          // 0.0
/*132 */                 ret = 0;                                                        // 0.0
/*134 */                 break;                                                          // 0.0
/*136 */             }                                                                   // 0.0
/*138 */         }                                                                       // 0.0
/*140 */     }                                                                           // 0.0
/*142 */     if (ret < 0) {                                                              // 0.0
/*144 */ #if defined (DEBUG_BATS)                                                        // 0.0
/*146 */         if (loglevel != 0) {                                                    // 0.0
/*148 */             fprintf(logfile, "no BAT match for 0x" ADDRX ":\n", virtual);       // 0.0
/*150 */             for (i = 0; i < 4; i++) {                                           // 0.0
/*152 */                 BATu = &BATut[i];                                               // 0.0
/*154 */                 BATl = &BATlt[i];                                               // 0.0
/*156 */                 BEPIu = *BATu & 0xF0000000;                                     // 0.0
/*158 */                 BEPIl = *BATu & 0x0FFE0000;                                     // 0.0
/*160 */                 bl = (*BATu & 0x00001FFC) << 15;                                // 0.0
/*162 */                 fprintf(logfile, "%s: %cBAT%d v 0x" ADDRX " BATu 0x" ADDRX      // 0.0
/*164 */                         " BATl 0x" ADDRX " \n\t"                                // 0.0
/*166 */                         "0x" ADDRX " 0x" ADDRX " 0x" ADDRX "\n",                // 0.0
/*168 */                         __func__, type == ACCESS_CODE ? 'I' : 'D', i, virtual,  // 0.0
/*170 */                         *BATu, *BATl, BEPIu, BEPIl, bl);                        // 0.0
/*172 */             }                                                                   // 0.0
/*174 */         }                                                                       // 0.0
/*176 */ #endif                                                                          // 0.0
/*178 */     }                                                                           // 0.0
/*180 */     /* No hit */                                                                // 0.0
/*182 */     return ret;                                                                 // 0.0
/*184 */ }                                                                               // 0.0
