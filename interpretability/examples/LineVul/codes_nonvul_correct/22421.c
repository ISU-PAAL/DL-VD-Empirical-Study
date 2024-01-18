// commit message qemu@42a268c241 (target=0, prob=0.33195567, correct=True): tcg: Change translator-side labels to a pointer
/*0    */ static void disas_xtensa_insn(CPUXtensaState *env, DisasContext *dc)                 // (6) 0.05273
/*2    */ {                                                                                    // (24) 0.001953
/*4    */ #define HAS_OPTION_BITS(opt) do { \                                                  // (12) 0.0293
/*6    */         if (!option_bits_enabled(dc, opt)) { \                                       // (7) 0.04102
/*8    */             qemu_log("Option is not enabled %s:%d\n", \                              // (3) 0.05859
/*10   */                     __FILE__, __LINE__); \                                           // (4) 0.05469
/*12   */             goto invalid_opcode; \                                                   // (9) 0.03516
/*14   */         } \                                                                          // (20) 0.01758
/*16   */     } while (0)                                                                      // (21) 0.01562
/*20   */ #define HAS_OPTION(opt) HAS_OPTION_BITS(XTENSA_OPTION_BIT(opt))                      // (5) 0.05469
/*24   */ #define TBD() qemu_log("TBD(pc = %08x): %s:%d\n", dc->pc, __FILE__, __LINE__)        // (1) 0.07617
/*26   */ #define RESERVED() do { \                                                            // (19) 0.01953
/*28   */         qemu_log("RESERVED(pc = %08x, %02x%02x%02x): %s:%d\n", \                     // (0) 0.08398
/*30   */                 dc->pc, b0, b1, b2, __FILE__, __LINE__); \                           // (2) 0.07227
/*32   */         goto invalid_opcode; \                                                       // (13) 0.02734
/*34   */     } while (0)                                                                      // (22) 0.01562
/*40   */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // (16) 0.02539
/*42   */ #define OP0 (((b0) & 0xf0) >> 4)                                                     // (10) 0.0332
/*44   */ #define OP1 (((b2) & 0xf0) >> 4)                                                     // (11) 0.0332
/*46   */ #define OP2 ((b2) & 0xf)                                                             // (18) 0.02344
/*48   */ #define RRR_R ((b1) & 0xf)                                                           // (14) 0.02734
/*50   */ #define RRR_S (((b1) & 0xf0) >> 4)                                                   // (8) 0.03711
/*52   */ #define RRR_T ((b0) & 0xf)                                                           // (15) 0.02734
/*54   */ #else                                                                                // (23) 0.003906
/*56   */ #define OP0 (((b0) & 0xf))                                                           // (17) 0.02539
/*58   */ #define OP1 (((b2) & 0xf))                                                           // 0.0
/*60   */ #define OP2 (((b2) & 0xf0) >> 4)                                                     // 0.0
/*62   */ #define RRR_R (((b1) & 0xf0) >> 4)                                                   // 0.0
/*64   */ #define RRR_S (((b1) & 0xf))                                                         // 0.0
/*66   */ #define RRR_T (((b0) & 0xf0) >> 4)                                                   // 0.0
/*68   */ #endif                                                                               // 0.0
/*70   */ #define RRR_X ((RRR_R & 0x4) >> 2)                                                   // 0.0
/*72   */ #define RRR_Y ((RRR_T & 0x4) >> 2)                                                   // 0.0
/*74   */ #define RRR_W (RRR_R & 0x3)                                                          // 0.0
/*78   */ #define RRRN_R RRR_R                                                                 // 0.0
/*80   */ #define RRRN_S RRR_S                                                                 // 0.0
/*82   */ #define RRRN_T RRR_T                                                                 // 0.0
/*86   */ #define RRI4_R RRR_R                                                                 // 0.0
/*88   */ #define RRI4_S RRR_S                                                                 // 0.0
/*90   */ #define RRI4_T RRR_T                                                                 // 0.0
/*92   */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // 0.0
/*94   */ #define RRI4_IMM4 ((b2) & 0xf)                                                       // 0.0
/*96   */ #else                                                                                // 0.0
/*98   */ #define RRI4_IMM4 (((b2) & 0xf0) >> 4)                                               // 0.0
/*100  */ #endif                                                                               // 0.0
/*104  */ #define RRI8_R RRR_R                                                                 // 0.0
/*106  */ #define RRI8_S RRR_S                                                                 // 0.0
/*108  */ #define RRI8_T RRR_T                                                                 // 0.0
/*110  */ #define RRI8_IMM8 (b2)                                                               // 0.0
/*112  */ #define RRI8_IMM8_SE ((((b2) & 0x80) ? 0xffffff00 : 0) | RRI8_IMM8)                  // 0.0
/*116  */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // 0.0
/*118  */ #define RI16_IMM16 (((b1) << 8) | (b2))                                              // 0.0
/*120  */ #else                                                                                // 0.0
/*122  */ #define RI16_IMM16 (((b2) << 8) | (b1))                                              // 0.0
/*124  */ #endif                                                                               // 0.0
/*128  */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // 0.0
/*130  */ #define CALL_N (((b0) & 0xc) >> 2)                                                   // 0.0
/*132  */ #define CALL_OFFSET ((((b0) & 0x3) << 16) | ((b1) << 8) | (b2))                      // 0.0
/*134  */ #else                                                                                // 0.0
/*136  */ #define CALL_N (((b0) & 0x30) >> 4)                                                  // 0.0
/*138  */ #define CALL_OFFSET ((((b0) & 0xc0) >> 6) | ((b1) << 2) | ((b2) << 10))              // 0.0
/*140  */ #endif                                                                               // 0.0
/*142  */ #define CALL_OFFSET_SE \                                                             // 0.0
/*144  */     (((CALL_OFFSET & 0x20000) ? 0xfffc0000 : 0) | CALL_OFFSET)                       // 0.0
/*148  */ #define CALLX_N CALL_N                                                               // 0.0
/*150  */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // 0.0
/*152  */ #define CALLX_M ((b0) & 0x3)                                                         // 0.0
/*154  */ #else                                                                                // 0.0
/*156  */ #define CALLX_M (((b0) & 0xc0) >> 6)                                                 // 0.0
/*158  */ #endif                                                                               // 0.0
/*160  */ #define CALLX_S RRR_S                                                                // 0.0
/*164  */ #define BRI12_M CALLX_M                                                              // 0.0
/*166  */ #define BRI12_S RRR_S                                                                // 0.0
/*168  */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // 0.0
/*170  */ #define BRI12_IMM12 ((((b1) & 0xf) << 8) | (b2))                                     // 0.0
/*172  */ #else                                                                                // 0.0
/*174  */ #define BRI12_IMM12 ((((b1) & 0xf0) >> 4) | ((b2) << 4))                             // 0.0
/*176  */ #endif                                                                               // 0.0
/*178  */ #define BRI12_IMM12_SE (((BRI12_IMM12 & 0x800) ? 0xfffff000 : 0) | BRI12_IMM12)      // 0.0
/*182  */ #define BRI8_M BRI12_M                                                               // 0.0
/*184  */ #define BRI8_R RRI8_R                                                                // 0.0
/*186  */ #define BRI8_S RRI8_S                                                                // 0.0
/*188  */ #define BRI8_IMM8 RRI8_IMM8                                                          // 0.0
/*190  */ #define BRI8_IMM8_SE RRI8_IMM8_SE                                                    // 0.0
/*194  */ #define RSR_SR (b1)                                                                  // 0.0
/*198  */     uint8_t b0 = cpu_ldub_code(env, dc->pc);                                         // 0.0
/*200  */     uint8_t b1 = cpu_ldub_code(env, dc->pc + 1);                                     // 0.0
/*202  */     uint8_t b2 = 0;                                                                  // 0.0
/*204  */     unsigned len = xtensa_op0_insn_len(OP0);                                         // 0.0
/*208  */     static const uint32_t B4CONST[] = {                                              // 0.0
/*210  */         0xffffffff, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 16, 32, 64, 128, 256             // 0.0
/*212  */     };                                                                               // 0.0
/*216  */     static const uint32_t B4CONSTU[] = {                                             // 0.0
/*218  */         32768, 65536, 2, 3, 4, 5, 6, 7, 8, 10, 12, 16, 32, 64, 128, 256              // 0.0
/*220  */     };                                                                               // 0.0
/*224  */     switch (len) {                                                                   // 0.0
/*226  */     case 2:                                                                          // 0.0
/*228  */         HAS_OPTION(XTENSA_OPTION_CODE_DENSITY);                                      // 0.0
/*230  */         break;                                                                       // 0.0
/*234  */     case 3:                                                                          // 0.0
/*236  */         b2 = cpu_ldub_code(env, dc->pc + 2);                                         // 0.0
/*238  */         break;                                                                       // 0.0
/*242  */     default:                                                                         // 0.0
/*244  */         RESERVED();                                                                  // 0.0
/*246  */     }                                                                                // 0.0
/*248  */     dc->next_pc = dc->pc + len;                                                      // 0.0
/*252  */     switch (OP0) {                                                                   // 0.0
/*254  */     case 0: /*QRST*/                                                                 // 0.0
/*256  */         switch (OP1) {                                                               // 0.0
/*258  */         case 0: /*RST0*/                                                             // 0.0
/*260  */             switch (OP2) {                                                           // 0.0
/*262  */             case 0: /*ST0*/                                                          // 0.0
/*264  */                 if ((RRR_R & 0xc) == 0x8) {                                          // 0.0
/*266  */                     HAS_OPTION(XTENSA_OPTION_BOOLEAN);                               // 0.0
/*268  */                 }                                                                    // 0.0
/*272  */                 switch (RRR_R) {                                                     // 0.0
/*274  */                 case 0: /*SNM0*/                                                     // 0.0
/*276  */                     switch (CALLX_M) {                                               // 0.0
/*278  */                     case 0: /*ILL*/                                                  // 0.0
/*280  */                         gen_exception_cause(dc, ILLEGAL_INSTRUCTION_CAUSE);          // 0.0
/*282  */                         break;                                                       // 0.0
/*286  */                     case 1: /*reserved*/                                             // 0.0
/*288  */                         RESERVED();                                                  // 0.0
/*290  */                         break;                                                       // 0.0
/*294  */                     case 2: /*JR*/                                                   // 0.0
/*296  */                         switch (CALLX_N) {                                           // 0.0
/*298  */                         case 0: /*RET*/                                              // 0.0
/*300  */                         case 2: /*JX*/                                               // 0.0
/*302  */                             if (gen_window_check1(dc, CALLX_S)) {                    // 0.0
/*304  */                                 gen_jump(dc, cpu_R[CALLX_S]);                        // 0.0
/*306  */                             }                                                        // 0.0
/*308  */                             break;                                                   // 0.0
/*312  */                         case 1: /*RETWw*/                                            // 0.0
/*314  */                             HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);             // 0.0
/*316  */                             {                                                        // 0.0
/*318  */                                 TCGv_i32 tmp = tcg_const_i32(dc->pc);                // 0.0
/*320  */                                 gen_advance_ccount(dc);                              // 0.0
/*322  */                                 gen_helper_retw(tmp, cpu_env, tmp);                  // 0.0
/*324  */                                 gen_jump(dc, tmp);                                   // 0.0
/*326  */                                 tcg_temp_free(tmp);                                  // 0.0
/*328  */                             }                                                        // 0.0
/*330  */                             break;                                                   // 0.0
/*334  */                         case 3: /*reserved*/                                         // 0.0
/*336  */                             RESERVED();                                              // 0.0
/*338  */                             break;                                                   // 0.0
/*340  */                         }                                                            // 0.0
/*342  */                         break;                                                       // 0.0
/*346  */                     case 3: /*CALLX*/                                                // 0.0
/*348  */                         if (!gen_window_check2(dc, CALLX_S, CALLX_N << 2)) {         // 0.0
/*350  */                             break;                                                   // 0.0
/*352  */                         }                                                            // 0.0
/*354  */                         switch (CALLX_N) {                                           // 0.0
/*356  */                         case 0: /*CALLX0*/                                           // 0.0
/*358  */                             {                                                        // 0.0
/*360  */                                 TCGv_i32 tmp = tcg_temp_new_i32();                   // 0.0
/*362  */                                 tcg_gen_mov_i32(tmp, cpu_R[CALLX_S]);                // 0.0
/*364  */                                 tcg_gen_movi_i32(cpu_R[0], dc->next_pc);             // 0.0
/*366  */                                 gen_jump(dc, tmp);                                   // 0.0
/*368  */                                 tcg_temp_free(tmp);                                  // 0.0
/*370  */                             }                                                        // 0.0
/*372  */                             break;                                                   // 0.0
/*376  */                         case 1: /*CALLX4w*/                                          // 0.0
/*378  */                         case 2: /*CALLX8w*/                                          // 0.0
/*380  */                         case 3: /*CALLX12w*/                                         // 0.0
/*382  */                             HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);             // 0.0
/*384  */                             {                                                        // 0.0
/*386  */                                 TCGv_i32 tmp = tcg_temp_new_i32();                   // 0.0
/*390  */                                 tcg_gen_mov_i32(tmp, cpu_R[CALLX_S]);                // 0.0
/*392  */                                 gen_callw(dc, CALLX_N, tmp);                         // 0.0
/*394  */                                 tcg_temp_free(tmp);                                  // 0.0
/*396  */                             }                                                        // 0.0
/*398  */                             break;                                                   // 0.0
/*400  */                         }                                                            // 0.0
/*402  */                         break;                                                       // 0.0
/*404  */                     }                                                                // 0.0
/*406  */                     break;                                                           // 0.0
/*410  */                 case 1: /*MOVSPw*/                                                   // 0.0
/*412  */                     HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);                     // 0.0
/*414  */                     if (gen_window_check2(dc, RRR_T, RRR_S)) {                       // 0.0
/*416  */                         TCGv_i32 pc = tcg_const_i32(dc->pc);                         // 0.0
/*418  */                         gen_advance_ccount(dc);                                      // 0.0
/*420  */                         gen_helper_movsp(cpu_env, pc);                               // 0.0
/*422  */                         tcg_gen_mov_i32(cpu_R[RRR_T], cpu_R[RRR_S]);                 // 0.0
/*424  */                         tcg_temp_free(pc);                                           // 0.0
/*426  */                     }                                                                // 0.0
/*428  */                     break;                                                           // 0.0
/*432  */                 case 2: /*SYNC*/                                                     // 0.0
/*434  */                     switch (RRR_T) {                                                 // 0.0
/*436  */                     case 0: /*ISYNC*/                                                // 0.0
/*438  */                         break;                                                       // 0.0
/*442  */                     case 1: /*RSYNC*/                                                // 0.0
/*444  */                         break;                                                       // 0.0
/*448  */                     case 2: /*ESYNC*/                                                // 0.0
/*450  */                         break;                                                       // 0.0
/*454  */                     case 3: /*DSYNC*/                                                // 0.0
/*456  */                         break;                                                       // 0.0
/*460  */                     case 8: /*EXCW*/                                                 // 0.0
/*462  */                         HAS_OPTION(XTENSA_OPTION_EXCEPTION);                         // 0.0
/*464  */                         break;                                                       // 0.0
/*468  */                     case 12: /*MEMW*/                                                // 0.0
/*470  */                         break;                                                       // 0.0
/*474  */                     case 13: /*EXTW*/                                                // 0.0
/*476  */                         break;                                                       // 0.0
/*480  */                     case 15: /*NOP*/                                                 // 0.0
/*482  */                         break;                                                       // 0.0
/*486  */                     default: /*reserved*/                                            // 0.0
/*488  */                         RESERVED();                                                  // 0.0
/*490  */                         break;                                                       // 0.0
/*492  */                     }                                                                // 0.0
/*494  */                     break;                                                           // 0.0
/*498  */                 case 3: /*RFEIx*/                                                    // 0.0
/*500  */                     switch (RRR_T) {                                                 // 0.0
/*502  */                     case 0: /*RFETx*/                                                // 0.0
/*504  */                         HAS_OPTION(XTENSA_OPTION_EXCEPTION);                         // 0.0
/*506  */                         switch (RRR_S) {                                             // 0.0
/*508  */                         case 0: /*RFEx*/                                             // 0.0
/*510  */                             if (gen_check_privilege(dc)) {                           // 0.0
/*512  */                                 tcg_gen_andi_i32(cpu_SR[PS], cpu_SR[PS], ~PS_EXCM);  // 0.0
/*514  */                                 gen_helper_check_interrupts(cpu_env);                // 0.0
/*516  */                                 gen_jump(dc, cpu_SR[EPC1]);                          // 0.0
/*518  */                             }                                                        // 0.0
/*520  */                             break;                                                   // 0.0
/*524  */                         case 1: /*RFUEx*/                                            // 0.0
/*526  */                             RESERVED();                                              // 0.0
/*528  */                             break;                                                   // 0.0
/*532  */                         case 2: /*RFDEx*/                                            // 0.0
/*534  */                             if (gen_check_privilege(dc)) {                           // 0.0
/*536  */                                 gen_jump(dc, cpu_SR[                                 // 0.0
/*538  */                                          dc->config->ndepc ? DEPC : EPC1]);          // 0.0
/*540  */                             }                                                        // 0.0
/*542  */                             break;                                                   // 0.0
/*546  */                         case 4: /*RFWOw*/                                            // 0.0
/*548  */                         case 5: /*RFWUw*/                                            // 0.0
/*550  */                             HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);             // 0.0
/*552  */                             if (gen_check_privilege(dc)) {                           // 0.0
/*554  */                                 TCGv_i32 tmp = tcg_const_i32(1);                     // 0.0
/*558  */                                 tcg_gen_andi_i32(                                    // 0.0
/*560  */                                         cpu_SR[PS], cpu_SR[PS], ~PS_EXCM);           // 0.0
/*562  */                                 tcg_gen_shl_i32(tmp, tmp, cpu_SR[WINDOW_BASE]);      // 0.0
/*566  */                                 if (RRR_S == 4) {                                    // 0.0
/*568  */                                     tcg_gen_andc_i32(cpu_SR[WINDOW_START],           // 0.0
/*570  */                                             cpu_SR[WINDOW_START], tmp);              // 0.0
/*572  */                                 } else {                                             // 0.0
/*574  */                                     tcg_gen_or_i32(cpu_SR[WINDOW_START],             // 0.0
/*576  */                                             cpu_SR[WINDOW_START], tmp);              // 0.0
/*578  */                                 }                                                    // 0.0
/*582  */                                 gen_helper_restore_owb(cpu_env);                     // 0.0
/*584  */                                 gen_helper_check_interrupts(cpu_env);                // 0.0
/*586  */                                 gen_jump(dc, cpu_SR[EPC1]);                          // 0.0
/*590  */                                 tcg_temp_free(tmp);                                  // 0.0
/*592  */                             }                                                        // 0.0
/*594  */                             break;                                                   // 0.0
/*598  */                         default: /*reserved*/                                        // 0.0
/*600  */                             RESERVED();                                              // 0.0
/*602  */                             break;                                                   // 0.0
/*604  */                         }                                                            // 0.0
/*606  */                         break;                                                       // 0.0
/*610  */                     case 1: /*RFIx*/                                                 // 0.0
/*612  */                         HAS_OPTION(XTENSA_OPTION_HIGH_PRIORITY_INTERRUPT);           // 0.0
/*614  */                         if (RRR_S >= 2 && RRR_S <= dc->config->nlevel) {             // 0.0
/*616  */                             if (gen_check_privilege(dc)) {                           // 0.0
/*618  */                                 tcg_gen_mov_i32(cpu_SR[PS],                          // 0.0
/*620  */                                                 cpu_SR[EPS2 + RRR_S - 2]);           // 0.0
/*622  */                                 gen_helper_check_interrupts(cpu_env);                // 0.0
/*624  */                                 gen_jump(dc, cpu_SR[EPC1 + RRR_S - 1]);              // 0.0
/*626  */                             }                                                        // 0.0
/*628  */                         } else {                                                     // 0.0
/*630  */                             qemu_log("RFI %d is illegal\n", RRR_S);                  // 0.0
/*632  */                             gen_exception_cause(dc, ILLEGAL_INSTRUCTION_CAUSE);      // 0.0
/*634  */                         }                                                            // 0.0
/*636  */                         break;                                                       // 0.0
/*640  */                     case 2: /*RFME*/                                                 // 0.0
/*642  */                         TBD();                                                       // 0.0
/*644  */                         break;                                                       // 0.0
/*648  */                     default: /*reserved*/                                            // 0.0
/*650  */                         RESERVED();                                                  // 0.0
/*652  */                         break;                                                       // 0.0
/*656  */                     }                                                                // 0.0
/*658  */                     break;                                                           // 0.0
/*662  */                 case 4: /*BREAKx*/                                                   // 0.0
/*664  */                     HAS_OPTION(XTENSA_OPTION_DEBUG);                                 // 0.0
/*666  */                     if (dc->debug) {                                                 // 0.0
/*668  */                         gen_debug_exception(dc, DEBUGCAUSE_BI);                      // 0.0
/*670  */                     }                                                                // 0.0
/*672  */                     break;                                                           // 0.0
/*676  */                 case 5: /*SYSCALLx*/                                                 // 0.0
/*678  */                     HAS_OPTION(XTENSA_OPTION_EXCEPTION);                             // 0.0
/*680  */                     switch (RRR_S) {                                                 // 0.0
/*682  */                     case 0: /*SYSCALLx*/                                             // 0.0
/*684  */                         gen_exception_cause(dc, SYSCALL_CAUSE);                      // 0.0
/*686  */                         break;                                                       // 0.0
/*690  */                     case 1: /*SIMCALL*/                                              // 0.0
/*692  */                         if (semihosting_enabled) {                                   // 0.0
/*694  */                             if (gen_check_privilege(dc)) {                           // 0.0
/*696  */                                 gen_helper_simcall(cpu_env);                         // 0.0
/*698  */                             }                                                        // 0.0
/*700  */                         } else {                                                     // 0.0
/*702  */                             qemu_log("SIMCALL but semihosting is disabled\n");       // 0.0
/*704  */                             gen_exception_cause(dc, ILLEGAL_INSTRUCTION_CAUSE);      // 0.0
/*706  */                         }                                                            // 0.0
/*708  */                         break;                                                       // 0.0
/*712  */                     default:                                                         // 0.0
/*714  */                         RESERVED();                                                  // 0.0
/*716  */                         break;                                                       // 0.0
/*718  */                     }                                                                // 0.0
/*720  */                     break;                                                           // 0.0
/*724  */                 case 6: /*RSILx*/                                                    // 0.0
/*726  */                     HAS_OPTION(XTENSA_OPTION_INTERRUPT);                             // 0.0
/*728  */                     if (gen_check_privilege(dc) &&                                   // 0.0
/*730  */                         gen_window_check1(dc, RRR_T)) {                              // 0.0
/*732  */                         tcg_gen_mov_i32(cpu_R[RRR_T], cpu_SR[PS]);                   // 0.0
/*734  */                         tcg_gen_andi_i32(cpu_SR[PS], cpu_SR[PS], ~PS_INTLEVEL);      // 0.0
/*736  */                         tcg_gen_ori_i32(cpu_SR[PS], cpu_SR[PS], RRR_S);              // 0.0
/*738  */                         gen_helper_check_interrupts(cpu_env);                        // 0.0
/*740  */                         gen_jumpi_check_loop_end(dc, 0);                             // 0.0
/*742  */                     }                                                                // 0.0
/*744  */                     break;                                                           // 0.0
/*748  */                 case 7: /*WAITIx*/                                                   // 0.0
/*750  */                     HAS_OPTION(XTENSA_OPTION_INTERRUPT);                             // 0.0
/*752  */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*754  */                         gen_waiti(dc, RRR_S);                                        // 0.0
/*756  */                     }                                                                // 0.0
/*758  */                     break;                                                           // 0.0
/*762  */                 case 8: /*ANY4p*/                                                    // 0.0
/*764  */                 case 9: /*ALL4p*/                                                    // 0.0
/*766  */                 case 10: /*ANY8p*/                                                   // 0.0
/*768  */                 case 11: /*ALL8p*/                                                   // 0.0
/*770  */                     HAS_OPTION(XTENSA_OPTION_BOOLEAN);                               // 0.0
/*772  */                     {                                                                // 0.0
/*774  */                         const unsigned shift = (RRR_R & 2) ? 8 : 4;                  // 0.0
/*776  */                         TCGv_i32 mask = tcg_const_i32(                               // 0.0
/*778  */                                 ((1 << shift) - 1) << RRR_S);                        // 0.0
/*780  */                         TCGv_i32 tmp = tcg_temp_new_i32();                           // 0.0
/*784  */                         tcg_gen_and_i32(tmp, cpu_SR[BR], mask);                      // 0.0
/*786  */                         if (RRR_R & 1) { /*ALL*/                                     // 0.0
/*788  */                             tcg_gen_addi_i32(tmp, tmp, 1 << RRR_S);                  // 0.0
/*790  */                         } else { /*ANY*/                                             // 0.0
/*792  */                             tcg_gen_add_i32(tmp, tmp, mask);                         // 0.0
/*794  */                         }                                                            // 0.0
/*796  */                         tcg_gen_shri_i32(tmp, tmp, RRR_S + shift);                   // 0.0
/*798  */                         tcg_gen_deposit_i32(cpu_SR[BR], cpu_SR[BR],                  // 0.0
/*800  */                                 tmp, RRR_T, 1);                                      // 0.0
/*802  */                         tcg_temp_free(mask);                                         // 0.0
/*804  */                         tcg_temp_free(tmp);                                          // 0.0
/*806  */                     }                                                                // 0.0
/*808  */                     break;                                                           // 0.0
/*812  */                 default: /*reserved*/                                                // 0.0
/*814  */                     RESERVED();                                                      // 0.0
/*816  */                     break;                                                           // 0.0
/*820  */                 }                                                                    // 0.0
/*822  */                 break;                                                               // 0.0
/*826  */             case 1: /*AND*/                                                          // 0.0
/*828  */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*830  */                     tcg_gen_and_i32(cpu_R[RRR_R], cpu_R[RRR_S], cpu_R[RRR_T]);       // 0.0
/*832  */                 }                                                                    // 0.0
/*834  */                 break;                                                               // 0.0
/*838  */             case 2: /*OR*/                                                           // 0.0
/*840  */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*842  */                     tcg_gen_or_i32(cpu_R[RRR_R], cpu_R[RRR_S], cpu_R[RRR_T]);        // 0.0
/*844  */                 }                                                                    // 0.0
/*846  */                 break;                                                               // 0.0
/*850  */             case 3: /*XOR*/                                                          // 0.0
/*852  */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*854  */                     tcg_gen_xor_i32(cpu_R[RRR_R], cpu_R[RRR_S], cpu_R[RRR_T]);       // 0.0
/*856  */                 }                                                                    // 0.0
/*858  */                 break;                                                               // 0.0
/*862  */             case 4: /*ST1*/                                                          // 0.0
/*864  */                 switch (RRR_R) {                                                     // 0.0
/*866  */                 case 0: /*SSR*/                                                      // 0.0
/*868  */                     if (gen_window_check1(dc, RRR_S)) {                              // 0.0
/*870  */                         gen_right_shift_sar(dc, cpu_R[RRR_S]);                       // 0.0
/*872  */                     }                                                                // 0.0
/*874  */                     break;                                                           // 0.0
/*878  */                 case 1: /*SSL*/                                                      // 0.0
/*880  */                     if (gen_window_check1(dc, RRR_S)) {                              // 0.0
/*882  */                         gen_left_shift_sar(dc, cpu_R[RRR_S]);                        // 0.0
/*884  */                     }                                                                // 0.0
/*886  */                     break;                                                           // 0.0
/*890  */                 case 2: /*SSA8L*/                                                    // 0.0
/*892  */                     if (gen_window_check1(dc, RRR_S)) {                              // 0.0
/*894  */                         TCGv_i32 tmp = tcg_temp_new_i32();                           // 0.0
/*896  */                         tcg_gen_shli_i32(tmp, cpu_R[RRR_S], 3);                      // 0.0
/*898  */                         gen_right_shift_sar(dc, tmp);                                // 0.0
/*900  */                         tcg_temp_free(tmp);                                          // 0.0
/*902  */                     }                                                                // 0.0
/*904  */                     break;                                                           // 0.0
/*908  */                 case 3: /*SSA8B*/                                                    // 0.0
/*910  */                     if (gen_window_check1(dc, RRR_S)) {                              // 0.0
/*912  */                         TCGv_i32 tmp = tcg_temp_new_i32();                           // 0.0
/*914  */                         tcg_gen_shli_i32(tmp, cpu_R[RRR_S], 3);                      // 0.0
/*916  */                         gen_left_shift_sar(dc, tmp);                                 // 0.0
/*918  */                         tcg_temp_free(tmp);                                          // 0.0
/*920  */                     }                                                                // 0.0
/*922  */                     break;                                                           // 0.0
/*926  */                 case 4: /*SSAI*/                                                     // 0.0
/*928  */                     {                                                                // 0.0
/*930  */                         TCGv_i32 tmp = tcg_const_i32(                                // 0.0
/*932  */                                 RRR_S | ((RRR_T & 1) << 4));                         // 0.0
/*934  */                         gen_right_shift_sar(dc, tmp);                                // 0.0
/*936  */                         tcg_temp_free(tmp);                                          // 0.0
/*938  */                     }                                                                // 0.0
/*940  */                     break;                                                           // 0.0
/*944  */                 case 6: /*RER*/                                                      // 0.0
/*946  */                     TBD();                                                           // 0.0
/*948  */                     break;                                                           // 0.0
/*952  */                 case 7: /*WER*/                                                      // 0.0
/*954  */                     TBD();                                                           // 0.0
/*956  */                     break;                                                           // 0.0
/*960  */                 case 8: /*ROTWw*/                                                    // 0.0
/*962  */                     HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);                     // 0.0
/*964  */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*966  */                         TCGv_i32 tmp = tcg_const_i32(                                // 0.0
/*968  */                                 RRR_T | ((RRR_T & 8) ? 0xfffffff0 : 0));             // 0.0
/*970  */                         gen_helper_rotw(cpu_env, tmp);                               // 0.0
/*972  */                         tcg_temp_free(tmp);                                          // 0.0
/*974  */                         /* This can change tb->flags, so exit tb */                  // 0.0
/*976  */                         gen_jumpi_check_loop_end(dc, -1);                            // 0.0
/*978  */                     }                                                                // 0.0
/*980  */                     break;                                                           // 0.0
/*984  */                 case 14: /*NSAu*/                                                    // 0.0
/*986  */                     HAS_OPTION(XTENSA_OPTION_MISC_OP_NSA);                           // 0.0
/*988  */                     if (gen_window_check2(dc, RRR_S, RRR_T)) {                       // 0.0
/*990  */                         gen_helper_nsa(cpu_R[RRR_T], cpu_R[RRR_S]);                  // 0.0
/*992  */                     }                                                                // 0.0
/*994  */                     break;                                                           // 0.0
/*998  */                 case 15: /*NSAUu*/                                                   // 0.0
/*1000 */                     HAS_OPTION(XTENSA_OPTION_MISC_OP_NSA);                           // 0.0
/*1002 */                     if (gen_window_check2(dc, RRR_S, RRR_T)) {                       // 0.0
/*1004 */                         gen_helper_nsau(cpu_R[RRR_T], cpu_R[RRR_S]);                 // 0.0
/*1006 */                     }                                                                // 0.0
/*1008 */                     break;                                                           // 0.0
/*1012 */                 default: /*reserved*/                                                // 0.0
/*1014 */                     RESERVED();                                                      // 0.0
/*1016 */                     break;                                                           // 0.0
/*1018 */                 }                                                                    // 0.0
/*1020 */                 break;                                                               // 0.0
/*1024 */             case 5: /*TLB*/                                                          // 0.0
/*1026 */                 HAS_OPTION_BITS(                                                     // 0.0
/*1028 */                         XTENSA_OPTION_BIT(XTENSA_OPTION_MMU) |                       // 0.0
/*1030 */                         XTENSA_OPTION_BIT(XTENSA_OPTION_REGION_PROTECTION) |         // 0.0
/*1032 */                         XTENSA_OPTION_BIT(XTENSA_OPTION_REGION_TRANSLATION));        // 0.0
/*1034 */                 if (gen_check_privilege(dc) &&                                       // 0.0
/*1036 */                     gen_window_check2(dc, RRR_S, RRR_T)) {                           // 0.0
/*1038 */                     TCGv_i32 dtlb = tcg_const_i32((RRR_R & 8) != 0);                 // 0.0
/*1042 */                     switch (RRR_R & 7) {                                             // 0.0
/*1044 */                     case 3: /*RITLB0*/ /*RDTLB0*/                                    // 0.0
/*1046 */                         gen_helper_rtlb0(cpu_R[RRR_T],                               // 0.0
/*1048 */                                 cpu_env, cpu_R[RRR_S], dtlb);                        // 0.0
/*1050 */                         break;                                                       // 0.0
/*1054 */                     case 4: /*IITLB*/ /*IDTLB*/                                      // 0.0
/*1056 */                         gen_helper_itlb(cpu_env, cpu_R[RRR_S], dtlb);                // 0.0
/*1058 */                         /* This could change memory mapping, so exit tb */           // 0.0
/*1060 */                         gen_jumpi_check_loop_end(dc, -1);                            // 0.0
/*1062 */                         break;                                                       // 0.0
/*1066 */                     case 5: /*PITLB*/ /*PDTLB*/                                      // 0.0
/*1068 */                         tcg_gen_movi_i32(cpu_pc, dc->pc);                            // 0.0
/*1070 */                         gen_helper_ptlb(cpu_R[RRR_T],                                // 0.0
/*1072 */                                 cpu_env, cpu_R[RRR_S], dtlb);                        // 0.0
/*1074 */                         break;                                                       // 0.0
/*1078 */                     case 6: /*WITLB*/ /*WDTLB*/                                      // 0.0
/*1080 */                         gen_helper_wtlb(                                             // 0.0
/*1082 */                                 cpu_env, cpu_R[RRR_T], cpu_R[RRR_S], dtlb);          // 0.0
/*1084 */                         /* This could change memory mapping, so exit tb */           // 0.0
/*1086 */                         gen_jumpi_check_loop_end(dc, -1);                            // 0.0
/*1088 */                         break;                                                       // 0.0
/*1092 */                     case 7: /*RITLB1*/ /*RDTLB1*/                                    // 0.0
/*1094 */                         gen_helper_rtlb1(cpu_R[RRR_T],                               // 0.0
/*1096 */                                 cpu_env, cpu_R[RRR_S], dtlb);                        // 0.0
/*1098 */                         break;                                                       // 0.0
/*1102 */                     default:                                                         // 0.0
/*1104 */                         tcg_temp_free(dtlb);                                         // 0.0
/*1106 */                         RESERVED();                                                  // 0.0
/*1108 */                         break;                                                       // 0.0
/*1110 */                     }                                                                // 0.0
/*1112 */                     tcg_temp_free(dtlb);                                             // 0.0
/*1114 */                 }                                                                    // 0.0
/*1116 */                 break;                                                               // 0.0
/*1120 */             case 6: /*RT0*/                                                          // 0.0
/*1122 */                 if (!gen_window_check2(dc, RRR_R, RRR_T)) {                          // 0.0
/*1124 */                     break;                                                           // 0.0
/*1126 */                 }                                                                    // 0.0
/*1128 */                 switch (RRR_S) {                                                     // 0.0
/*1130 */                 case 0: /*NEG*/                                                      // 0.0
/*1132 */                     tcg_gen_neg_i32(cpu_R[RRR_R], cpu_R[RRR_T]);                     // 0.0
/*1134 */                     break;                                                           // 0.0
/*1138 */                 case 1: /*ABS*/                                                      // 0.0
/*1140 */                     {                                                                // 0.0
/*1142 */                         TCGv_i32 zero = tcg_const_i32(0);                            // 0.0
/*1144 */                         TCGv_i32 neg = tcg_temp_new_i32();                           // 0.0
/*1148 */                         tcg_gen_neg_i32(neg, cpu_R[RRR_T]);                          // 0.0
/*1150 */                         tcg_gen_movcond_i32(TCG_COND_GE, cpu_R[RRR_R],               // 0.0
/*1152 */                                 cpu_R[RRR_T], zero, cpu_R[RRR_T], neg);              // 0.0
/*1154 */                         tcg_temp_free(neg);                                          // 0.0
/*1156 */                         tcg_temp_free(zero);                                         // 0.0
/*1158 */                     }                                                                // 0.0
/*1160 */                     break;                                                           // 0.0
/*1164 */                 default: /*reserved*/                                                // 0.0
/*1166 */                     RESERVED();                                                      // 0.0
/*1168 */                     break;                                                           // 0.0
/*1170 */                 }                                                                    // 0.0
/*1172 */                 break;                                                               // 0.0
/*1176 */             case 7: /*reserved*/                                                     // 0.0
/*1178 */                 RESERVED();                                                          // 0.0
/*1180 */                 break;                                                               // 0.0
/*1184 */             case 8: /*ADD*/                                                          // 0.0
/*1186 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1188 */                     tcg_gen_add_i32(cpu_R[RRR_R], cpu_R[RRR_S], cpu_R[RRR_T]);       // 0.0
/*1190 */                 }                                                                    // 0.0
/*1192 */                 break;                                                               // 0.0
/*1196 */             case 9: /*ADD**/                                                         // 0.0
/*1198 */             case 10:                                                                 // 0.0
/*1200 */             case 11:                                                                 // 0.0
/*1202 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1204 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*1206 */                     tcg_gen_shli_i32(tmp, cpu_R[RRR_S], OP2 - 8);                    // 0.0
/*1208 */                     tcg_gen_add_i32(cpu_R[RRR_R], tmp, cpu_R[RRR_T]);                // 0.0
/*1210 */                     tcg_temp_free(tmp);                                              // 0.0
/*1212 */                 }                                                                    // 0.0
/*1214 */                 break;                                                               // 0.0
/*1218 */             case 12: /*SUB*/                                                         // 0.0
/*1220 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1222 */                     tcg_gen_sub_i32(cpu_R[RRR_R], cpu_R[RRR_S], cpu_R[RRR_T]);       // 0.0
/*1224 */                 }                                                                    // 0.0
/*1226 */                 break;                                                               // 0.0
/*1230 */             case 13: /*SUB**/                                                        // 0.0
/*1232 */             case 14:                                                                 // 0.0
/*1234 */             case 15:                                                                 // 0.0
/*1236 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1238 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*1240 */                     tcg_gen_shli_i32(tmp, cpu_R[RRR_S], OP2 - 12);                   // 0.0
/*1242 */                     tcg_gen_sub_i32(cpu_R[RRR_R], tmp, cpu_R[RRR_T]);                // 0.0
/*1244 */                     tcg_temp_free(tmp);                                              // 0.0
/*1246 */                 }                                                                    // 0.0
/*1248 */                 break;                                                               // 0.0
/*1250 */             }                                                                        // 0.0
/*1252 */             break;                                                                   // 0.0
/*1256 */         case 1: /*RST1*/                                                             // 0.0
/*1258 */             switch (OP2) {                                                           // 0.0
/*1260 */             case 0: /*SLLI*/                                                         // 0.0
/*1262 */             case 1:                                                                  // 0.0
/*1264 */                 if (gen_window_check2(dc, RRR_R, RRR_S)) {                           // 0.0
/*1266 */                     tcg_gen_shli_i32(cpu_R[RRR_R], cpu_R[RRR_S],                     // 0.0
/*1268 */                                      32 - (RRR_T | ((OP2 & 1) << 4)));               // 0.0
/*1270 */                 }                                                                    // 0.0
/*1272 */                 break;                                                               // 0.0
/*1276 */             case 2: /*SRAI*/                                                         // 0.0
/*1278 */             case 3:                                                                  // 0.0
/*1280 */                 if (gen_window_check2(dc, RRR_R, RRR_T)) {                           // 0.0
/*1282 */                     tcg_gen_sari_i32(cpu_R[RRR_R], cpu_R[RRR_T],                     // 0.0
/*1284 */                                      RRR_S | ((OP2 & 1) << 4));                      // 0.0
/*1286 */                 }                                                                    // 0.0
/*1288 */                 break;                                                               // 0.0
/*1292 */             case 4: /*SRLI*/                                                         // 0.0
/*1294 */                 if (gen_window_check2(dc, RRR_R, RRR_T)) {                           // 0.0
/*1296 */                     tcg_gen_shri_i32(cpu_R[RRR_R], cpu_R[RRR_T], RRR_S);             // 0.0
/*1298 */                 }                                                                    // 0.0
/*1300 */                 break;                                                               // 0.0
/*1304 */             case 6: /*XSR*/                                                          // 0.0
/*1306 */                 if (gen_check_sr(dc, RSR_SR, SR_X) &&                                // 0.0
/*1308 */                     (RSR_SR < 64 || gen_check_privilege(dc)) &&                      // 0.0
/*1310 */                     gen_window_check1(dc, RRR_T)) {                                  // 0.0
/*1312 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*1316 */                     tcg_gen_mov_i32(tmp, cpu_R[RRR_T]);                              // 0.0
/*1318 */                     gen_rsr(dc, cpu_R[RRR_T], RSR_SR);                               // 0.0
/*1320 */                     gen_wsr(dc, RSR_SR, tmp);                                        // 0.0
/*1322 */                     tcg_temp_free(tmp);                                              // 0.0
/*1324 */                 }                                                                    // 0.0
/*1326 */                 break;                                                               // 0.0
/*1330 */                 /*                                                                   // 0.0
/*1332 */                  * Note: 64 bit ops are used here solely because SAR values          // 0.0
/*1334 */                  * have range 0..63                                                  // 0.0
/*1336 */                  */                                                                  // 0.0
/*1338 */ #define gen_shift_reg(cmd, reg) do { \                                               // 0.0
/*1340 */                     TCGv_i64 tmp = tcg_temp_new_i64(); \                             // 0.0
/*1342 */                     tcg_gen_extu_i32_i64(tmp, reg); \                                // 0.0
/*1344 */                     tcg_gen_##cmd##_i64(v, v, tmp); \                                // 0.0
/*1346 */                     tcg_gen_trunc_i64_i32(cpu_R[RRR_R], v); \                        // 0.0
/*1348 */                     tcg_temp_free_i64(v); \                                          // 0.0
/*1350 */                     tcg_temp_free_i64(tmp); \                                        // 0.0
/*1352 */                 } while (0)                                                          // 0.0
/*1356 */ #define gen_shift(cmd) gen_shift_reg(cmd, cpu_SR[SAR])                               // 0.0
/*1360 */             case 8: /*SRC*/                                                          // 0.0
/*1362 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1364 */                     TCGv_i64 v = tcg_temp_new_i64();                                 // 0.0
/*1366 */                     tcg_gen_concat_i32_i64(v, cpu_R[RRR_T], cpu_R[RRR_S]);           // 0.0
/*1368 */                     gen_shift(shr);                                                  // 0.0
/*1370 */                 }                                                                    // 0.0
/*1372 */                 break;                                                               // 0.0
/*1376 */             case 9: /*SRL*/                                                          // 0.0
/*1378 */                 if (!gen_window_check2(dc, RRR_R, RRR_T)) {                          // 0.0
/*1380 */                     break;                                                           // 0.0
/*1382 */                 }                                                                    // 0.0
/*1384 */                 if (dc->sar_5bit) {                                                  // 0.0
/*1386 */                     tcg_gen_shr_i32(cpu_R[RRR_R], cpu_R[RRR_T], cpu_SR[SAR]);        // 0.0
/*1388 */                 } else {                                                             // 0.0
/*1390 */                     TCGv_i64 v = tcg_temp_new_i64();                                 // 0.0
/*1392 */                     tcg_gen_extu_i32_i64(v, cpu_R[RRR_T]);                           // 0.0
/*1394 */                     gen_shift(shr);                                                  // 0.0
/*1396 */                 }                                                                    // 0.0
/*1398 */                 break;                                                               // 0.0
/*1402 */             case 10: /*SLL*/                                                         // 0.0
/*1404 */                 if (!gen_window_check2(dc, RRR_R, RRR_S)) {                          // 0.0
/*1406 */                     break;                                                           // 0.0
/*1408 */                 }                                                                    // 0.0
/*1410 */                 if (dc->sar_m32_5bit) {                                              // 0.0
/*1412 */                     tcg_gen_shl_i32(cpu_R[RRR_R], cpu_R[RRR_S], dc->sar_m32);        // 0.0
/*1414 */                 } else {                                                             // 0.0
/*1416 */                     TCGv_i64 v = tcg_temp_new_i64();                                 // 0.0
/*1418 */                     TCGv_i32 s = tcg_const_i32(32);                                  // 0.0
/*1420 */                     tcg_gen_sub_i32(s, s, cpu_SR[SAR]);                              // 0.0
/*1422 */                     tcg_gen_andi_i32(s, s, 0x3f);                                    // 0.0
/*1424 */                     tcg_gen_extu_i32_i64(v, cpu_R[RRR_S]);                           // 0.0
/*1426 */                     gen_shift_reg(shl, s);                                           // 0.0
/*1428 */                     tcg_temp_free(s);                                                // 0.0
/*1430 */                 }                                                                    // 0.0
/*1432 */                 break;                                                               // 0.0
/*1436 */             case 11: /*SRA*/                                                         // 0.0
/*1438 */                 if (!gen_window_check2(dc, RRR_R, RRR_T)) {                          // 0.0
/*1440 */                     break;                                                           // 0.0
/*1442 */                 }                                                                    // 0.0
/*1444 */                 if (dc->sar_5bit) {                                                  // 0.0
/*1446 */                     tcg_gen_sar_i32(cpu_R[RRR_R], cpu_R[RRR_T], cpu_SR[SAR]);        // 0.0
/*1448 */                 } else {                                                             // 0.0
/*1450 */                     TCGv_i64 v = tcg_temp_new_i64();                                 // 0.0
/*1452 */                     tcg_gen_ext_i32_i64(v, cpu_R[RRR_T]);                            // 0.0
/*1454 */                     gen_shift(sar);                                                  // 0.0
/*1456 */                 }                                                                    // 0.0
/*1458 */                 break;                                                               // 0.0
/*1460 */ #undef gen_shift                                                                     // 0.0
/*1462 */ #undef gen_shift_reg                                                                 // 0.0
/*1466 */             case 12: /*MUL16U*/                                                      // 0.0
/*1468 */                 HAS_OPTION(XTENSA_OPTION_16_BIT_IMUL);                               // 0.0
/*1470 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1472 */                     TCGv_i32 v1 = tcg_temp_new_i32();                                // 0.0
/*1474 */                     TCGv_i32 v2 = tcg_temp_new_i32();                                // 0.0
/*1476 */                     tcg_gen_ext16u_i32(v1, cpu_R[RRR_S]);                            // 0.0
/*1478 */                     tcg_gen_ext16u_i32(v2, cpu_R[RRR_T]);                            // 0.0
/*1480 */                     tcg_gen_mul_i32(cpu_R[RRR_R], v1, v2);                           // 0.0
/*1482 */                     tcg_temp_free(v2);                                               // 0.0
/*1484 */                     tcg_temp_free(v1);                                               // 0.0
/*1486 */                 }                                                                    // 0.0
/*1488 */                 break;                                                               // 0.0
/*1492 */             case 13: /*MUL16S*/                                                      // 0.0
/*1494 */                 HAS_OPTION(XTENSA_OPTION_16_BIT_IMUL);                               // 0.0
/*1496 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1498 */                     TCGv_i32 v1 = tcg_temp_new_i32();                                // 0.0
/*1500 */                     TCGv_i32 v2 = tcg_temp_new_i32();                                // 0.0
/*1502 */                     tcg_gen_ext16s_i32(v1, cpu_R[RRR_S]);                            // 0.0
/*1504 */                     tcg_gen_ext16s_i32(v2, cpu_R[RRR_T]);                            // 0.0
/*1506 */                     tcg_gen_mul_i32(cpu_R[RRR_R], v1, v2);                           // 0.0
/*1508 */                     tcg_temp_free(v2);                                               // 0.0
/*1510 */                     tcg_temp_free(v1);                                               // 0.0
/*1512 */                 }                                                                    // 0.0
/*1514 */                 break;                                                               // 0.0
/*1518 */             default: /*reserved*/                                                    // 0.0
/*1520 */                 RESERVED();                                                          // 0.0
/*1522 */                 break;                                                               // 0.0
/*1524 */             }                                                                        // 0.0
/*1526 */             break;                                                                   // 0.0
/*1530 */         case 2: /*RST2*/                                                             // 0.0
/*1532 */             if (OP2 >= 8 && !gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {           // 0.0
/*1534 */                 break;                                                               // 0.0
/*1536 */             }                                                                        // 0.0
/*1540 */             if (OP2 >= 12) {                                                         // 0.0
/*1542 */                 HAS_OPTION(XTENSA_OPTION_32_BIT_IDIV);                               // 0.0
/*1544 */                 int label = gen_new_label();                                         // 0.0
/*1546 */                 tcg_gen_brcondi_i32(TCG_COND_NE, cpu_R[RRR_T], 0, label);            // 0.0
/*1548 */                 gen_exception_cause(dc, INTEGER_DIVIDE_BY_ZERO_CAUSE);               // 0.0
/*1550 */                 gen_set_label(label);                                                // 0.0
/*1552 */             }                                                                        // 0.0
/*1556 */             switch (OP2) {                                                           // 0.0
/*1558 */ #define BOOLEAN_LOGIC(fn, r, s, t) \                                                 // 0.0
/*1560 */                 do { \                                                               // 0.0
/*1562 */                     HAS_OPTION(XTENSA_OPTION_BOOLEAN); \                             // 0.0
/*1564 */                     TCGv_i32 tmp1 = tcg_temp_new_i32(); \                            // 0.0
/*1566 */                     TCGv_i32 tmp2 = tcg_temp_new_i32(); \                            // 0.0
/*1568 */                     \                                                                // 0.0
/*1570 */                     tcg_gen_shri_i32(tmp1, cpu_SR[BR], s); \                         // 0.0
/*1572 */                     tcg_gen_shri_i32(tmp2, cpu_SR[BR], t); \                         // 0.0
/*1574 */                     tcg_gen_##fn##_i32(tmp1, tmp1, tmp2); \                          // 0.0
/*1576 */                     tcg_gen_deposit_i32(cpu_SR[BR], cpu_SR[BR], tmp1, r, 1); \       // 0.0
/*1578 */                     tcg_temp_free(tmp1); \                                           // 0.0
/*1580 */                     tcg_temp_free(tmp2); \                                           // 0.0
/*1582 */                 } while (0)                                                          // 0.0
/*1586 */             case 0: /*ANDBp*/                                                        // 0.0
/*1588 */                 BOOLEAN_LOGIC(and, RRR_R, RRR_S, RRR_T);                             // 0.0
/*1590 */                 break;                                                               // 0.0
/*1594 */             case 1: /*ANDBCp*/                                                       // 0.0
/*1596 */                 BOOLEAN_LOGIC(andc, RRR_R, RRR_S, RRR_T);                            // 0.0
/*1598 */                 break;                                                               // 0.0
/*1602 */             case 2: /*ORBp*/                                                         // 0.0
/*1604 */                 BOOLEAN_LOGIC(or, RRR_R, RRR_S, RRR_T);                              // 0.0
/*1606 */                 break;                                                               // 0.0
/*1610 */             case 3: /*ORBCp*/                                                        // 0.0
/*1612 */                 BOOLEAN_LOGIC(orc, RRR_R, RRR_S, RRR_T);                             // 0.0
/*1614 */                 break;                                                               // 0.0
/*1618 */             case 4: /*XORBp*/                                                        // 0.0
/*1620 */                 BOOLEAN_LOGIC(xor, RRR_R, RRR_S, RRR_T);                             // 0.0
/*1622 */                 break;                                                               // 0.0
/*1626 */ #undef BOOLEAN_LOGIC                                                                 // 0.0
/*1630 */             case 8: /*MULLi*/                                                        // 0.0
/*1632 */                 HAS_OPTION(XTENSA_OPTION_32_BIT_IMUL);                               // 0.0
/*1634 */                 tcg_gen_mul_i32(cpu_R[RRR_R], cpu_R[RRR_S], cpu_R[RRR_T]);           // 0.0
/*1636 */                 break;                                                               // 0.0
/*1640 */             case 10: /*MULUHi*/                                                      // 0.0
/*1642 */             case 11: /*MULSHi*/                                                      // 0.0
/*1644 */                 HAS_OPTION(XTENSA_OPTION_32_BIT_IMUL_HIGH);                          // 0.0
/*1646 */                 {                                                                    // 0.0
/*1648 */                     TCGv lo = tcg_temp_new();                                        // 0.0
/*1652 */                     if (OP2 == 10) {                                                 // 0.0
/*1654 */                         tcg_gen_mulu2_i32(lo, cpu_R[RRR_R],                          // 0.0
/*1656 */                                           cpu_R[RRR_S], cpu_R[RRR_T]);               // 0.0
/*1658 */                     } else {                                                         // 0.0
/*1660 */                         tcg_gen_muls2_i32(lo, cpu_R[RRR_R],                          // 0.0
/*1662 */                                           cpu_R[RRR_S], cpu_R[RRR_T]);               // 0.0
/*1664 */                     }                                                                // 0.0
/*1666 */                     tcg_temp_free(lo);                                               // 0.0
/*1668 */                 }                                                                    // 0.0
/*1670 */                 break;                                                               // 0.0
/*1674 */             case 12: /*QUOUi*/                                                       // 0.0
/*1676 */                 tcg_gen_divu_i32(cpu_R[RRR_R], cpu_R[RRR_S], cpu_R[RRR_T]);          // 0.0
/*1678 */                 break;                                                               // 0.0
/*1682 */             case 13: /*QUOSi*/                                                       // 0.0
/*1684 */             case 15: /*REMSi*/                                                       // 0.0
/*1686 */                 {                                                                    // 0.0
/*1688 */                     int label1 = gen_new_label();                                    // 0.0
/*1690 */                     int label2 = gen_new_label();                                    // 0.0
/*1694 */                     tcg_gen_brcondi_i32(TCG_COND_NE, cpu_R[RRR_S], 0x80000000,       // 0.0
/*1696 */                             label1);                                                 // 0.0
/*1698 */                     tcg_gen_brcondi_i32(TCG_COND_NE, cpu_R[RRR_T], 0xffffffff,       // 0.0
/*1700 */                             label1);                                                 // 0.0
/*1702 */                     tcg_gen_movi_i32(cpu_R[RRR_R],                                   // 0.0
/*1704 */                             OP2 == 13 ? 0x80000000 : 0);                             // 0.0
/*1706 */                     tcg_gen_br(label2);                                              // 0.0
/*1708 */                     gen_set_label(label1);                                           // 0.0
/*1710 */                     if (OP2 == 13) {                                                 // 0.0
/*1712 */                         tcg_gen_div_i32(cpu_R[RRR_R],                                // 0.0
/*1714 */                                 cpu_R[RRR_S], cpu_R[RRR_T]);                         // 0.0
/*1716 */                     } else {                                                         // 0.0
/*1718 */                         tcg_gen_rem_i32(cpu_R[RRR_R],                                // 0.0
/*1720 */                                 cpu_R[RRR_S], cpu_R[RRR_T]);                         // 0.0
/*1722 */                     }                                                                // 0.0
/*1724 */                     gen_set_label(label2);                                           // 0.0
/*1726 */                 }                                                                    // 0.0
/*1728 */                 break;                                                               // 0.0
/*1732 */             case 14: /*REMUi*/                                                       // 0.0
/*1734 */                 tcg_gen_remu_i32(cpu_R[RRR_R], cpu_R[RRR_S], cpu_R[RRR_T]);          // 0.0
/*1736 */                 break;                                                               // 0.0
/*1740 */             default: /*reserved*/                                                    // 0.0
/*1742 */                 RESERVED();                                                          // 0.0
/*1744 */                 break;                                                               // 0.0
/*1746 */             }                                                                        // 0.0
/*1748 */             break;                                                                   // 0.0
/*1752 */         case 3: /*RST3*/                                                             // 0.0
/*1754 */             switch (OP2) {                                                           // 0.0
/*1756 */             case 0: /*RSR*/                                                          // 0.0
/*1758 */                 if (gen_check_sr(dc, RSR_SR, SR_R) &&                                // 0.0
/*1760 */                     (RSR_SR < 64 || gen_check_privilege(dc)) &&                      // 0.0
/*1762 */                     gen_window_check1(dc, RRR_T)) {                                  // 0.0
/*1764 */                     gen_rsr(dc, cpu_R[RRR_T], RSR_SR);                               // 0.0
/*1766 */                 }                                                                    // 0.0
/*1768 */                 break;                                                               // 0.0
/*1772 */             case 1: /*WSR*/                                                          // 0.0
/*1774 */                 if (gen_check_sr(dc, RSR_SR, SR_W) &&                                // 0.0
/*1776 */                     (RSR_SR < 64 || gen_check_privilege(dc)) &&                      // 0.0
/*1778 */                     gen_window_check1(dc, RRR_T)) {                                  // 0.0
/*1780 */                     gen_wsr(dc, RSR_SR, cpu_R[RRR_T]);                               // 0.0
/*1782 */                 }                                                                    // 0.0
/*1784 */                 break;                                                               // 0.0
/*1788 */             case 2: /*SEXTu*/                                                        // 0.0
/*1790 */                 HAS_OPTION(XTENSA_OPTION_MISC_OP_SEXT);                              // 0.0
/*1792 */                 if (gen_window_check2(dc, RRR_R, RRR_S)) {                           // 0.0
/*1794 */                     int shift = 24 - RRR_T;                                          // 0.0
/*1798 */                     if (shift == 24) {                                               // 0.0
/*1800 */                         tcg_gen_ext8s_i32(cpu_R[RRR_R], cpu_R[RRR_S]);               // 0.0
/*1802 */                     } else if (shift == 16) {                                        // 0.0
/*1804 */                         tcg_gen_ext16s_i32(cpu_R[RRR_R], cpu_R[RRR_S]);              // 0.0
/*1806 */                     } else {                                                         // 0.0
/*1808 */                         TCGv_i32 tmp = tcg_temp_new_i32();                           // 0.0
/*1810 */                         tcg_gen_shli_i32(tmp, cpu_R[RRR_S], shift);                  // 0.0
/*1812 */                         tcg_gen_sari_i32(cpu_R[RRR_R], tmp, shift);                  // 0.0
/*1814 */                         tcg_temp_free(tmp);                                          // 0.0
/*1816 */                     }                                                                // 0.0
/*1818 */                 }                                                                    // 0.0
/*1820 */                 break;                                                               // 0.0
/*1824 */             case 3: /*CLAMPSu*/                                                      // 0.0
/*1826 */                 HAS_OPTION(XTENSA_OPTION_MISC_OP_CLAMPS);                            // 0.0
/*1828 */                 if (gen_window_check2(dc, RRR_R, RRR_S)) {                           // 0.0
/*1830 */                     TCGv_i32 tmp1 = tcg_temp_new_i32();                              // 0.0
/*1832 */                     TCGv_i32 tmp2 = tcg_temp_new_i32();                              // 0.0
/*1834 */                     TCGv_i32 zero = tcg_const_i32(0);                                // 0.0
/*1838 */                     tcg_gen_sari_i32(tmp1, cpu_R[RRR_S], 24 - RRR_T);                // 0.0
/*1840 */                     tcg_gen_xor_i32(tmp2, tmp1, cpu_R[RRR_S]);                       // 0.0
/*1842 */                     tcg_gen_andi_i32(tmp2, tmp2, 0xffffffff << (RRR_T + 7));         // 0.0
/*1846 */                     tcg_gen_sari_i32(tmp1, cpu_R[RRR_S], 31);                        // 0.0
/*1848 */                     tcg_gen_xori_i32(tmp1, tmp1, 0xffffffff >> (25 - RRR_T));        // 0.0
/*1852 */                     tcg_gen_movcond_i32(TCG_COND_EQ, cpu_R[RRR_R], tmp2, zero,       // 0.0
/*1854 */                             cpu_R[RRR_S], tmp1);                                     // 0.0
/*1856 */                     tcg_temp_free(tmp1);                                             // 0.0
/*1858 */                     tcg_temp_free(tmp2);                                             // 0.0
/*1860 */                     tcg_temp_free(zero);                                             // 0.0
/*1862 */                 }                                                                    // 0.0
/*1864 */                 break;                                                               // 0.0
/*1868 */             case 4: /*MINu*/                                                         // 0.0
/*1870 */             case 5: /*MAXu*/                                                         // 0.0
/*1872 */             case 6: /*MINUu*/                                                        // 0.0
/*1874 */             case 7: /*MAXUu*/                                                        // 0.0
/*1876 */                 HAS_OPTION(XTENSA_OPTION_MISC_OP_MINMAX);                            // 0.0
/*1878 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1880 */                     static const TCGCond cond[] = {                                  // 0.0
/*1882 */                         TCG_COND_LE,                                                 // 0.0
/*1884 */                         TCG_COND_GE,                                                 // 0.0
/*1886 */                         TCG_COND_LEU,                                                // 0.0
/*1888 */                         TCG_COND_GEU                                                 // 0.0
/*1890 */                     };                                                               // 0.0
/*1892 */                     tcg_gen_movcond_i32(cond[OP2 - 4], cpu_R[RRR_R],                 // 0.0
/*1894 */                             cpu_R[RRR_S], cpu_R[RRR_T],                              // 0.0
/*1896 */                             cpu_R[RRR_S], cpu_R[RRR_T]);                             // 0.0
/*1898 */                 }                                                                    // 0.0
/*1900 */                 break;                                                               // 0.0
/*1904 */             case 8: /*MOVEQZ*/                                                       // 0.0
/*1906 */             case 9: /*MOVNEZ*/                                                       // 0.0
/*1908 */             case 10: /*MOVLTZ*/                                                      // 0.0
/*1910 */             case 11: /*MOVGEZ*/                                                      // 0.0
/*1912 */                 if (gen_window_check3(dc, RRR_R, RRR_S, RRR_T)) {                    // 0.0
/*1914 */                     static const TCGCond cond[] = {                                  // 0.0
/*1916 */                         TCG_COND_EQ,                                                 // 0.0
/*1918 */                         TCG_COND_NE,                                                 // 0.0
/*1920 */                         TCG_COND_LT,                                                 // 0.0
/*1922 */                         TCG_COND_GE,                                                 // 0.0
/*1924 */                     };                                                               // 0.0
/*1926 */                     TCGv_i32 zero = tcg_const_i32(0);                                // 0.0
/*1930 */                     tcg_gen_movcond_i32(cond[OP2 - 8], cpu_R[RRR_R],                 // 0.0
/*1932 */                             cpu_R[RRR_T], zero, cpu_R[RRR_S], cpu_R[RRR_R]);         // 0.0
/*1934 */                     tcg_temp_free(zero);                                             // 0.0
/*1936 */                 }                                                                    // 0.0
/*1938 */                 break;                                                               // 0.0
/*1942 */             case 12: /*MOVFp*/                                                       // 0.0
/*1944 */             case 13: /*MOVTp*/                                                       // 0.0
/*1946 */                 HAS_OPTION(XTENSA_OPTION_BOOLEAN);                                   // 0.0
/*1948 */                 if (gen_window_check2(dc, RRR_R, RRR_S)) {                           // 0.0
/*1950 */                     TCGv_i32 zero = tcg_const_i32(0);                                // 0.0
/*1952 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*1956 */                     tcg_gen_andi_i32(tmp, cpu_SR[BR], 1 << RRR_T);                   // 0.0
/*1958 */                     tcg_gen_movcond_i32(OP2 & 1 ? TCG_COND_NE : TCG_COND_EQ,         // 0.0
/*1960 */                             cpu_R[RRR_R], tmp, zero,                                 // 0.0
/*1962 */                             cpu_R[RRR_S], cpu_R[RRR_R]);                             // 0.0
/*1966 */                     tcg_temp_free(tmp);                                              // 0.0
/*1968 */                     tcg_temp_free(zero);                                             // 0.0
/*1970 */                 }                                                                    // 0.0
/*1972 */                 break;                                                               // 0.0
/*1976 */             case 14: /*RUR*/                                                         // 0.0
/*1978 */                 if (gen_window_check1(dc, RRR_R)) {                                  // 0.0
/*1980 */                     int st = (RRR_S << 4) + RRR_T;                                   // 0.0
/*1982 */                     if (uregnames[st].name) {                                        // 0.0
/*1984 */                         tcg_gen_mov_i32(cpu_R[RRR_R], cpu_UR[st]);                   // 0.0
/*1986 */                     } else {                                                         // 0.0
/*1988 */                         qemu_log("RUR %d not implemented, ", st);                    // 0.0
/*1990 */                         TBD();                                                       // 0.0
/*1992 */                     }                                                                // 0.0
/*1994 */                 }                                                                    // 0.0
/*1996 */                 break;                                                               // 0.0
/*2000 */             case 15: /*WUR*/                                                         // 0.0
/*2002 */                 if (gen_window_check1(dc, RRR_T)) {                                  // 0.0
/*2004 */                     if (uregnames[RSR_SR].name) {                                    // 0.0
/*2006 */                         gen_wur(RSR_SR, cpu_R[RRR_T]);                               // 0.0
/*2008 */                     } else {                                                         // 0.0
/*2010 */                         qemu_log("WUR %d not implemented, ", RSR_SR);                // 0.0
/*2012 */                         TBD();                                                       // 0.0
/*2014 */                     }                                                                // 0.0
/*2016 */                 }                                                                    // 0.0
/*2018 */                 break;                                                               // 0.0
/*2022 */             }                                                                        // 0.0
/*2024 */             break;                                                                   // 0.0
/*2028 */         case 4: /*EXTUI*/                                                            // 0.0
/*2030 */         case 5:                                                                      // 0.0
/*2032 */             if (gen_window_check2(dc, RRR_R, RRR_T)) {                               // 0.0
/*2034 */                 int shiftimm = RRR_S | ((OP1 & 1) << 4);                             // 0.0
/*2036 */                 int maskimm = (1 << (OP2 + 1)) - 1;                                  // 0.0
/*2040 */                 TCGv_i32 tmp = tcg_temp_new_i32();                                   // 0.0
/*2042 */                 tcg_gen_shri_i32(tmp, cpu_R[RRR_T], shiftimm);                       // 0.0
/*2044 */                 tcg_gen_andi_i32(cpu_R[RRR_R], tmp, maskimm);                        // 0.0
/*2046 */                 tcg_temp_free(tmp);                                                  // 0.0
/*2048 */             }                                                                        // 0.0
/*2050 */             break;                                                                   // 0.0
/*2054 */         case 6: /*CUST0*/                                                            // 0.0
/*2056 */             RESERVED();                                                              // 0.0
/*2058 */             break;                                                                   // 0.0
/*2062 */         case 7: /*CUST1*/                                                            // 0.0
/*2064 */             RESERVED();                                                              // 0.0
/*2066 */             break;                                                                   // 0.0
/*2070 */         case 8: /*LSCXp*/                                                            // 0.0
/*2072 */             switch (OP2) {                                                           // 0.0
/*2074 */             case 0: /*LSXf*/                                                         // 0.0
/*2076 */             case 1: /*LSXUf*/                                                        // 0.0
/*2078 */             case 4: /*SSXf*/                                                         // 0.0
/*2080 */             case 5: /*SSXUf*/                                                        // 0.0
/*2082 */                 HAS_OPTION(XTENSA_OPTION_FP_COPROCESSOR);                            // 0.0
/*2084 */                 if (gen_window_check2(dc, RRR_S, RRR_T) &&                           // 0.0
/*2086 */                     gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2088 */                     TCGv_i32 addr = tcg_temp_new_i32();                              // 0.0
/*2090 */                     tcg_gen_add_i32(addr, cpu_R[RRR_S], cpu_R[RRR_T]);               // 0.0
/*2092 */                     gen_load_store_alignment(dc, 2, addr, false);                    // 0.0
/*2094 */                     if (OP2 & 0x4) {                                                 // 0.0
/*2096 */                         tcg_gen_qemu_st32(cpu_FR[RRR_R], addr, dc->cring);           // 0.0
/*2098 */                     } else {                                                         // 0.0
/*2100 */                         tcg_gen_qemu_ld32u(cpu_FR[RRR_R], addr, dc->cring);          // 0.0
/*2102 */                     }                                                                // 0.0
/*2104 */                     if (OP2 & 0x1) {                                                 // 0.0
/*2106 */                         tcg_gen_mov_i32(cpu_R[RRR_S], addr);                         // 0.0
/*2108 */                     }                                                                // 0.0
/*2110 */                     tcg_temp_free(addr);                                             // 0.0
/*2112 */                 }                                                                    // 0.0
/*2114 */                 break;                                                               // 0.0
/*2118 */             default: /*reserved*/                                                    // 0.0
/*2120 */                 RESERVED();                                                          // 0.0
/*2122 */                 break;                                                               // 0.0
/*2124 */             }                                                                        // 0.0
/*2126 */             break;                                                                   // 0.0
/*2130 */         case 9: /*LSC4*/                                                             // 0.0
/*2132 */             if (!gen_window_check2(dc, RRR_S, RRR_T)) {                              // 0.0
/*2134 */                 break;                                                               // 0.0
/*2136 */             }                                                                        // 0.0
/*2138 */             switch (OP2) {                                                           // 0.0
/*2140 */             case 0: /*L32E*/                                                         // 0.0
/*2142 */                 HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);                         // 0.0
/*2144 */                 if (gen_check_privilege(dc)) {                                       // 0.0
/*2146 */                     TCGv_i32 addr = tcg_temp_new_i32();                              // 0.0
/*2148 */                     tcg_gen_addi_i32(addr, cpu_R[RRR_S],                             // 0.0
/*2150 */                             (0xffffffc0 | (RRR_R << 2)));                            // 0.0
/*2152 */                     tcg_gen_qemu_ld32u(cpu_R[RRR_T], addr, dc->ring);                // 0.0
/*2154 */                     tcg_temp_free(addr);                                             // 0.0
/*2156 */                 }                                                                    // 0.0
/*2158 */                 break;                                                               // 0.0
/*2162 */             case 4: /*S32E*/                                                         // 0.0
/*2164 */                 HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);                         // 0.0
/*2166 */                 if (gen_check_privilege(dc)) {                                       // 0.0
/*2168 */                     TCGv_i32 addr = tcg_temp_new_i32();                              // 0.0
/*2170 */                     tcg_gen_addi_i32(addr, cpu_R[RRR_S],                             // 0.0
/*2172 */                             (0xffffffc0 | (RRR_R << 2)));                            // 0.0
/*2174 */                     tcg_gen_qemu_st32(cpu_R[RRR_T], addr, dc->ring);                 // 0.0
/*2176 */                     tcg_temp_free(addr);                                             // 0.0
/*2178 */                 }                                                                    // 0.0
/*2180 */                 break;                                                               // 0.0
/*2184 */             default:                                                                 // 0.0
/*2186 */                 RESERVED();                                                          // 0.0
/*2188 */                 break;                                                               // 0.0
/*2190 */             }                                                                        // 0.0
/*2192 */             break;                                                                   // 0.0
/*2196 */         case 10: /*FP0*/                                                             // 0.0
/*2198 */             HAS_OPTION(XTENSA_OPTION_FP_COPROCESSOR);                                // 0.0
/*2200 */             switch (OP2) {                                                           // 0.0
/*2202 */             case 0: /*ADD.Sf*/                                                       // 0.0
/*2204 */                 if (gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2206 */                     gen_helper_add_s(cpu_FR[RRR_R], cpu_env,                         // 0.0
/*2208 */                                      cpu_FR[RRR_S], cpu_FR[RRR_T]);                  // 0.0
/*2210 */                 }                                                                    // 0.0
/*2212 */                 break;                                                               // 0.0
/*2216 */             case 1: /*SUB.Sf*/                                                       // 0.0
/*2218 */                 if (gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2220 */                     gen_helper_sub_s(cpu_FR[RRR_R], cpu_env,                         // 0.0
/*2222 */                                      cpu_FR[RRR_S], cpu_FR[RRR_T]);                  // 0.0
/*2224 */                 }                                                                    // 0.0
/*2226 */                 break;                                                               // 0.0
/*2230 */             case 2: /*MUL.Sf*/                                                       // 0.0
/*2232 */                 if (gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2234 */                     gen_helper_mul_s(cpu_FR[RRR_R], cpu_env,                         // 0.0
/*2236 */                                      cpu_FR[RRR_S], cpu_FR[RRR_T]);                  // 0.0
/*2238 */                 }                                                                    // 0.0
/*2240 */                 break;                                                               // 0.0
/*2244 */             case 4: /*MADD.Sf*/                                                      // 0.0
/*2246 */                 if (gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2248 */                     gen_helper_madd_s(cpu_FR[RRR_R], cpu_env,                        // 0.0
/*2250 */                                       cpu_FR[RRR_R], cpu_FR[RRR_S],                  // 0.0
/*2252 */                                       cpu_FR[RRR_T]);                                // 0.0
/*2254 */                 }                                                                    // 0.0
/*2256 */                 break;                                                               // 0.0
/*2260 */             case 5: /*MSUB.Sf*/                                                      // 0.0
/*2262 */                 if (gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2264 */                     gen_helper_msub_s(cpu_FR[RRR_R], cpu_env,                        // 0.0
/*2266 */                                       cpu_FR[RRR_R], cpu_FR[RRR_S],                  // 0.0
/*2268 */                                       cpu_FR[RRR_T]);                                // 0.0
/*2270 */                 }                                                                    // 0.0
/*2272 */                 break;                                                               // 0.0
/*2276 */             case 8: /*ROUND.Sf*/                                                     // 0.0
/*2278 */             case 9: /*TRUNC.Sf*/                                                     // 0.0
/*2280 */             case 10: /*FLOOR.Sf*/                                                    // 0.0
/*2282 */             case 11: /*CEIL.Sf*/                                                     // 0.0
/*2284 */             case 14: /*UTRUNC.Sf*/                                                   // 0.0
/*2286 */                 if (gen_window_check1(dc, RRR_R) &&                                  // 0.0
/*2288 */                     gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2290 */                     static const unsigned rounding_mode_const[] = {                  // 0.0
/*2292 */                         float_round_nearest_even,                                    // 0.0
/*2294 */                         float_round_to_zero,                                         // 0.0
/*2296 */                         float_round_down,                                            // 0.0
/*2298 */                         float_round_up,                                              // 0.0
/*2300 */                         [6] = float_round_to_zero,                                   // 0.0
/*2302 */                     };                                                               // 0.0
/*2304 */                     TCGv_i32 rounding_mode = tcg_const_i32(                          // 0.0
/*2306 */                             rounding_mode_const[OP2 & 7]);                           // 0.0
/*2308 */                     TCGv_i32 scale = tcg_const_i32(RRR_T);                           // 0.0
/*2312 */                     if (OP2 == 14) {                                                 // 0.0
/*2314 */                         gen_helper_ftoui(cpu_R[RRR_R], cpu_FR[RRR_S],                // 0.0
/*2316 */                                 rounding_mode, scale);                               // 0.0
/*2318 */                     } else {                                                         // 0.0
/*2320 */                         gen_helper_ftoi(cpu_R[RRR_R], cpu_FR[RRR_S],                 // 0.0
/*2322 */                                 rounding_mode, scale);                               // 0.0
/*2324 */                     }                                                                // 0.0
/*2328 */                     tcg_temp_free(rounding_mode);                                    // 0.0
/*2330 */                     tcg_temp_free(scale);                                            // 0.0
/*2332 */                 }                                                                    // 0.0
/*2334 */                 break;                                                               // 0.0
/*2338 */             case 12: /*FLOAT.Sf*/                                                    // 0.0
/*2340 */             case 13: /*UFLOAT.Sf*/                                                   // 0.0
/*2342 */                 if (gen_window_check1(dc, RRR_S) &&                                  // 0.0
/*2344 */                     gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2346 */                     TCGv_i32 scale = tcg_const_i32(-RRR_T);                          // 0.0
/*2350 */                     if (OP2 == 13) {                                                 // 0.0
/*2352 */                         gen_helper_uitof(cpu_FR[RRR_R], cpu_env,                     // 0.0
/*2354 */                                 cpu_R[RRR_S], scale);                                // 0.0
/*2356 */                     } else {                                                         // 0.0
/*2358 */                         gen_helper_itof(cpu_FR[RRR_R], cpu_env,                      // 0.0
/*2360 */                                 cpu_R[RRR_S], scale);                                // 0.0
/*2362 */                     }                                                                // 0.0
/*2364 */                     tcg_temp_free(scale);                                            // 0.0
/*2366 */                 }                                                                    // 0.0
/*2368 */                 break;                                                               // 0.0
/*2372 */             case 15: /*FP1OP*/                                                       // 0.0
/*2374 */                 switch (RRR_T) {                                                     // 0.0
/*2376 */                 case 0: /*MOV.Sf*/                                                   // 0.0
/*2378 */                     if (gen_check_cpenable(dc, 0)) {                                 // 0.0
/*2380 */                         tcg_gen_mov_i32(cpu_FR[RRR_R], cpu_FR[RRR_S]);               // 0.0
/*2382 */                     }                                                                // 0.0
/*2384 */                     break;                                                           // 0.0
/*2388 */                 case 1: /*ABS.Sf*/                                                   // 0.0
/*2390 */                     if (gen_check_cpenable(dc, 0)) {                                 // 0.0
/*2392 */                         gen_helper_abs_s(cpu_FR[RRR_R], cpu_FR[RRR_S]);              // 0.0
/*2394 */                     }                                                                // 0.0
/*2396 */                     break;                                                           // 0.0
/*2400 */                 case 4: /*RFRf*/                                                     // 0.0
/*2402 */                     if (gen_window_check1(dc, RRR_R) &&                              // 0.0
/*2404 */                         gen_check_cpenable(dc, 0)) {                                 // 0.0
/*2406 */                         tcg_gen_mov_i32(cpu_R[RRR_R], cpu_FR[RRR_S]);                // 0.0
/*2408 */                     }                                                                // 0.0
/*2410 */                     break;                                                           // 0.0
/*2414 */                 case 5: /*WFRf*/                                                     // 0.0
/*2416 */                     if (gen_window_check1(dc, RRR_S) &&                              // 0.0
/*2418 */                         gen_check_cpenable(dc, 0)) {                                 // 0.0
/*2420 */                         tcg_gen_mov_i32(cpu_FR[RRR_R], cpu_R[RRR_S]);                // 0.0
/*2422 */                     }                                                                // 0.0
/*2424 */                     break;                                                           // 0.0
/*2428 */                 case 6: /*NEG.Sf*/                                                   // 0.0
/*2430 */                     if (gen_check_cpenable(dc, 0)) {                                 // 0.0
/*2432 */                         gen_helper_neg_s(cpu_FR[RRR_R], cpu_FR[RRR_S]);              // 0.0
/*2434 */                     }                                                                // 0.0
/*2436 */                     break;                                                           // 0.0
/*2440 */                 default: /*reserved*/                                                // 0.0
/*2442 */                     RESERVED();                                                      // 0.0
/*2444 */                     break;                                                           // 0.0
/*2446 */                 }                                                                    // 0.0
/*2448 */                 break;                                                               // 0.0
/*2452 */             default: /*reserved*/                                                    // 0.0
/*2454 */                 RESERVED();                                                          // 0.0
/*2456 */                 break;                                                               // 0.0
/*2458 */             }                                                                        // 0.0
/*2460 */             break;                                                                   // 0.0
/*2464 */         case 11: /*FP1*/                                                             // 0.0
/*2466 */             HAS_OPTION(XTENSA_OPTION_FP_COPROCESSOR);                                // 0.0
/*2470 */ #define gen_compare(rel, br, a, b) \                                                 // 0.0
/*2472 */     do { \                                                                           // 0.0
/*2474 */         if (gen_check_cpenable(dc, 0)) { \                                           // 0.0
/*2476 */             TCGv_i32 bit = tcg_const_i32(1 << br); \                                 // 0.0
/*2478 */             \                                                                        // 0.0
/*2480 */             gen_helper_##rel(cpu_env, bit, cpu_FR[a], cpu_FR[b]); \                  // 0.0
/*2482 */             tcg_temp_free(bit); \                                                    // 0.0
/*2484 */         } \                                                                          // 0.0
/*2486 */     } while (0)                                                                      // 0.0
/*2490 */             switch (OP2) {                                                           // 0.0
/*2492 */             case 1: /*UN.Sf*/                                                        // 0.0
/*2494 */                 gen_compare(un_s, RRR_R, RRR_S, RRR_T);                              // 0.0
/*2496 */                 break;                                                               // 0.0
/*2500 */             case 2: /*OEQ.Sf*/                                                       // 0.0
/*2502 */                 gen_compare(oeq_s, RRR_R, RRR_S, RRR_T);                             // 0.0
/*2504 */                 break;                                                               // 0.0
/*2508 */             case 3: /*UEQ.Sf*/                                                       // 0.0
/*2510 */                 gen_compare(ueq_s, RRR_R, RRR_S, RRR_T);                             // 0.0
/*2512 */                 break;                                                               // 0.0
/*2516 */             case 4: /*OLT.Sf*/                                                       // 0.0
/*2518 */                 gen_compare(olt_s, RRR_R, RRR_S, RRR_T);                             // 0.0
/*2520 */                 break;                                                               // 0.0
/*2524 */             case 5: /*ULT.Sf*/                                                       // 0.0
/*2526 */                 gen_compare(ult_s, RRR_R, RRR_S, RRR_T);                             // 0.0
/*2528 */                 break;                                                               // 0.0
/*2532 */             case 6: /*OLE.Sf*/                                                       // 0.0
/*2534 */                 gen_compare(ole_s, RRR_R, RRR_S, RRR_T);                             // 0.0
/*2536 */                 break;                                                               // 0.0
/*2540 */             case 7: /*ULE.Sf*/                                                       // 0.0
/*2542 */                 gen_compare(ule_s, RRR_R, RRR_S, RRR_T);                             // 0.0
/*2544 */                 break;                                                               // 0.0
/*2548 */ #undef gen_compare                                                                   // 0.0
/*2552 */             case 8: /*MOVEQZ.Sf*/                                                    // 0.0
/*2554 */             case 9: /*MOVNEZ.Sf*/                                                    // 0.0
/*2556 */             case 10: /*MOVLTZ.Sf*/                                                   // 0.0
/*2558 */             case 11: /*MOVGEZ.Sf*/                                                   // 0.0
/*2560 */                 if (gen_window_check1(dc, RRR_T) &&                                  // 0.0
/*2562 */                     gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2564 */                     static const TCGCond cond[] = {                                  // 0.0
/*2566 */                         TCG_COND_EQ,                                                 // 0.0
/*2568 */                         TCG_COND_NE,                                                 // 0.0
/*2570 */                         TCG_COND_LT,                                                 // 0.0
/*2572 */                         TCG_COND_GE,                                                 // 0.0
/*2574 */                     };                                                               // 0.0
/*2576 */                     TCGv_i32 zero = tcg_const_i32(0);                                // 0.0
/*2580 */                     tcg_gen_movcond_i32(cond[OP2 - 8], cpu_FR[RRR_R],                // 0.0
/*2582 */                             cpu_R[RRR_T], zero, cpu_FR[RRR_S], cpu_FR[RRR_R]);       // 0.0
/*2584 */                     tcg_temp_free(zero);                                             // 0.0
/*2586 */                 }                                                                    // 0.0
/*2588 */                 break;                                                               // 0.0
/*2592 */             case 12: /*MOVF.Sf*/                                                     // 0.0
/*2594 */             case 13: /*MOVT.Sf*/                                                     // 0.0
/*2596 */                 HAS_OPTION(XTENSA_OPTION_BOOLEAN);                                   // 0.0
/*2598 */                 if (gen_check_cpenable(dc, 0)) {                                     // 0.0
/*2600 */                     TCGv_i32 zero = tcg_const_i32(0);                                // 0.0
/*2602 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*2606 */                     tcg_gen_andi_i32(tmp, cpu_SR[BR], 1 << RRR_T);                   // 0.0
/*2608 */                     tcg_gen_movcond_i32(OP2 & 1 ? TCG_COND_NE : TCG_COND_EQ,         // 0.0
/*2610 */                             cpu_FR[RRR_R], tmp, zero,                                // 0.0
/*2612 */                             cpu_FR[RRR_S], cpu_FR[RRR_R]);                           // 0.0
/*2616 */                     tcg_temp_free(tmp);                                              // 0.0
/*2618 */                     tcg_temp_free(zero);                                             // 0.0
/*2620 */                 }                                                                    // 0.0
/*2622 */                 break;                                                               // 0.0
/*2626 */             default: /*reserved*/                                                    // 0.0
/*2628 */                 RESERVED();                                                          // 0.0
/*2630 */                 break;                                                               // 0.0
/*2632 */             }                                                                        // 0.0
/*2634 */             break;                                                                   // 0.0
/*2638 */         default: /*reserved*/                                                        // 0.0
/*2640 */             RESERVED();                                                              // 0.0
/*2642 */             break;                                                                   // 0.0
/*2644 */         }                                                                            // 0.0
/*2646 */         break;                                                                       // 0.0
/*2650 */     case 1: /*L32R*/                                                                 // 0.0
/*2652 */         if (gen_window_check1(dc, RRR_T)) {                                          // 0.0
/*2654 */             TCGv_i32 tmp = tcg_const_i32(                                            // 0.0
/*2656 */                     ((dc->tb->flags & XTENSA_TBFLAG_LITBASE) ?                       // 0.0
/*2658 */                      0 : ((dc->pc + 3) & ~3)) +                                      // 0.0
/*2660 */                     (0xfffc0000 | (RI16_IMM16 << 2)));                               // 0.0
/*2664 */             if (dc->tb->flags & XTENSA_TBFLAG_LITBASE) {                             // 0.0
/*2666 */                 tcg_gen_add_i32(tmp, tmp, dc->litbase);                              // 0.0
/*2668 */             }                                                                        // 0.0
/*2670 */             tcg_gen_qemu_ld32u(cpu_R[RRR_T], tmp, dc->cring);                        // 0.0
/*2672 */             tcg_temp_free(tmp);                                                      // 0.0
/*2674 */         }                                                                            // 0.0
/*2676 */         break;                                                                       // 0.0
/*2680 */     case 2: /*LSAI*/                                                                 // 0.0
/*2682 */ #define gen_load_store(type, shift) do { \                                           // 0.0
/*2684 */             if (gen_window_check2(dc, RRI8_S, RRI8_T)) { \                           // 0.0
/*2686 */                 TCGv_i32 addr = tcg_temp_new_i32(); \                                // 0.0
/*2688 */                 \                                                                    // 0.0
/*2690 */                 tcg_gen_addi_i32(addr, cpu_R[RRI8_S], RRI8_IMM8 << shift); \         // 0.0
/*2692 */                 if (shift) { \                                                       // 0.0
/*2694 */                     gen_load_store_alignment(dc, shift, addr, false); \              // 0.0
/*2696 */                 } \                                                                  // 0.0
/*2698 */                 tcg_gen_qemu_##type(cpu_R[RRI8_T], addr, dc->cring); \               // 0.0
/*2700 */                 tcg_temp_free(addr); \                                               // 0.0
/*2702 */             } \                                                                      // 0.0
/*2704 */         } while (0)                                                                  // 0.0
/*2708 */         switch (RRI8_R) {                                                            // 0.0
/*2710 */         case 0: /*L8UI*/                                                             // 0.0
/*2712 */             gen_load_store(ld8u, 0);                                                 // 0.0
/*2714 */             break;                                                                   // 0.0
/*2718 */         case 1: /*L16UI*/                                                            // 0.0
/*2720 */             gen_load_store(ld16u, 1);                                                // 0.0
/*2722 */             break;                                                                   // 0.0
/*2726 */         case 2: /*L32I*/                                                             // 0.0
/*2728 */             gen_load_store(ld32u, 2);                                                // 0.0
/*2730 */             break;                                                                   // 0.0
/*2734 */         case 4: /*S8I*/                                                              // 0.0
/*2736 */             gen_load_store(st8, 0);                                                  // 0.0
/*2738 */             break;                                                                   // 0.0
/*2742 */         case 5: /*S16I*/                                                             // 0.0
/*2744 */             gen_load_store(st16, 1);                                                 // 0.0
/*2746 */             break;                                                                   // 0.0
/*2750 */         case 6: /*S32I*/                                                             // 0.0
/*2752 */             gen_load_store(st32, 2);                                                 // 0.0
/*2754 */             break;                                                                   // 0.0
/*2758 */ #define gen_dcache_hit_test(w, shift) do { \                                         // 0.0
/*2760 */             if (gen_window_check1(dc, RRI##w##_S)) { \                               // 0.0
/*2762 */                 TCGv_i32 addr = tcg_temp_new_i32(); \                                // 0.0
/*2764 */                 TCGv_i32 res = tcg_temp_new_i32(); \                                 // 0.0
/*2766 */                 tcg_gen_addi_i32(addr, cpu_R[RRI##w##_S], \                          // 0.0
/*2768 */                                  RRI##w##_IMM##w << shift); \                        // 0.0
/*2770 */                 tcg_gen_qemu_ld8u(res, addr, dc->cring); \                           // 0.0
/*2772 */                 tcg_temp_free(addr); \                                               // 0.0
/*2774 */                 tcg_temp_free(res); \                                                // 0.0
/*2776 */             } \                                                                      // 0.0
/*2778 */         } while (0)                                                                  // 0.0
/*2782 */ #define gen_dcache_hit_test4() gen_dcache_hit_test(4, 4)                             // 0.0
/*2784 */ #define gen_dcache_hit_test8() gen_dcache_hit_test(8, 2)                             // 0.0
/*2788 */         case 7: /*CACHEc*/                                                           // 0.0
/*2790 */             if (RRI8_T < 8) {                                                        // 0.0
/*2792 */                 HAS_OPTION(XTENSA_OPTION_DCACHE);                                    // 0.0
/*2794 */             }                                                                        // 0.0
/*2798 */             switch (RRI8_T) {                                                        // 0.0
/*2800 */             case 0: /*DPFRc*/                                                        // 0.0
/*2802 */                 gen_window_check1(dc, RRI8_S);                                       // 0.0
/*2804 */                 break;                                                               // 0.0
/*2808 */             case 1: /*DPFWc*/                                                        // 0.0
/*2810 */                 gen_window_check1(dc, RRI8_S);                                       // 0.0
/*2812 */                 break;                                                               // 0.0
/*2816 */             case 2: /*DPFROc*/                                                       // 0.0
/*2818 */                 gen_window_check1(dc, RRI8_S);                                       // 0.0
/*2820 */                 break;                                                               // 0.0
/*2824 */             case 3: /*DPFWOc*/                                                       // 0.0
/*2826 */                 gen_window_check1(dc, RRI8_S);                                       // 0.0
/*2828 */                 break;                                                               // 0.0
/*2832 */             case 4: /*DHWBc*/                                                        // 0.0
/*2834 */                 gen_dcache_hit_test8();                                              // 0.0
/*2836 */                 break;                                                               // 0.0
/*2840 */             case 5: /*DHWBIc*/                                                       // 0.0
/*2842 */                 gen_dcache_hit_test8();                                              // 0.0
/*2844 */                 break;                                                               // 0.0
/*2848 */             case 6: /*DHIc*/                                                         // 0.0
/*2850 */                 if (gen_check_privilege(dc)) {                                       // 0.0
/*2852 */                     gen_dcache_hit_test8();                                          // 0.0
/*2854 */                 }                                                                    // 0.0
/*2856 */                 break;                                                               // 0.0
/*2860 */             case 7: /*DIIc*/                                                         // 0.0
/*2862 */                 if (gen_check_privilege(dc)) {                                       // 0.0
/*2864 */                     gen_window_check1(dc, RRI8_S);                                   // 0.0
/*2866 */                 }                                                                    // 0.0
/*2868 */                 break;                                                               // 0.0
/*2872 */             case 8: /*DCEc*/                                                         // 0.0
/*2874 */                 switch (OP1) {                                                       // 0.0
/*2876 */                 case 0: /*DPFLl*/                                                    // 0.0
/*2878 */                     HAS_OPTION(XTENSA_OPTION_DCACHE_INDEX_LOCK);                     // 0.0
/*2880 */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*2882 */                         gen_dcache_hit_test4();                                      // 0.0
/*2884 */                     }                                                                // 0.0
/*2886 */                     break;                                                           // 0.0
/*2890 */                 case 2: /*DHUl*/                                                     // 0.0
/*2892 */                     HAS_OPTION(XTENSA_OPTION_DCACHE_INDEX_LOCK);                     // 0.0
/*2894 */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*2896 */                         gen_dcache_hit_test4();                                      // 0.0
/*2898 */                     }                                                                // 0.0
/*2900 */                     break;                                                           // 0.0
/*2904 */                 case 3: /*DIUl*/                                                     // 0.0
/*2906 */                     HAS_OPTION(XTENSA_OPTION_DCACHE_INDEX_LOCK);                     // 0.0
/*2908 */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*2910 */                         gen_window_check1(dc, RRI4_S);                               // 0.0
/*2912 */                     }                                                                // 0.0
/*2914 */                     break;                                                           // 0.0
/*2918 */                 case 4: /*DIWBc*/                                                    // 0.0
/*2920 */                     HAS_OPTION(XTENSA_OPTION_DCACHE);                                // 0.0
/*2922 */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*2924 */                         gen_window_check1(dc, RRI4_S);                               // 0.0
/*2926 */                     }                                                                // 0.0
/*2928 */                     break;                                                           // 0.0
/*2932 */                 case 5: /*DIWBIc*/                                                   // 0.0
/*2934 */                     HAS_OPTION(XTENSA_OPTION_DCACHE);                                // 0.0
/*2936 */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*2938 */                         gen_window_check1(dc, RRI4_S);                               // 0.0
/*2940 */                     }                                                                // 0.0
/*2942 */                     break;                                                           // 0.0
/*2946 */                 default: /*reserved*/                                                // 0.0
/*2948 */                     RESERVED();                                                      // 0.0
/*2950 */                     break;                                                           // 0.0
/*2954 */                 }                                                                    // 0.0
/*2956 */                 break;                                                               // 0.0
/*2960 */ #undef gen_dcache_hit_test                                                           // 0.0
/*2962 */ #undef gen_dcache_hit_test4                                                          // 0.0
/*2964 */ #undef gen_dcache_hit_test8                                                          // 0.0
/*2968 */ #define gen_icache_hit_test(w, shift) do { \                                         // 0.0
/*2970 */             if (gen_window_check1(dc, RRI##w##_S)) { \                               // 0.0
/*2972 */                 TCGv_i32 addr = tcg_temp_new_i32(); \                                // 0.0
/*2974 */                 tcg_gen_movi_i32(cpu_pc, dc->pc); \                                  // 0.0
/*2976 */                 tcg_gen_addi_i32(addr, cpu_R[RRI##w##_S], \                          // 0.0
/*2978 */                                  RRI##w##_IMM##w << shift); \                        // 0.0
/*2980 */                 gen_helper_itlb_hit_test(cpu_env, addr); \                           // 0.0
/*2982 */                 tcg_temp_free(addr); \                                               // 0.0
/*2984 */             }\                                                                       // 0.0
/*2986 */         } while (0)                                                                  // 0.0
/*2990 */ #define gen_icache_hit_test4() gen_icache_hit_test(4, 4)                             // 0.0
/*2992 */ #define gen_icache_hit_test8() gen_icache_hit_test(8, 2)                             // 0.0
/*2996 */             case 12: /*IPFc*/                                                        // 0.0
/*2998 */                 HAS_OPTION(XTENSA_OPTION_ICACHE);                                    // 0.0
/*3000 */                 gen_window_check1(dc, RRI8_S);                                       // 0.0
/*3002 */                 break;                                                               // 0.0
/*3006 */             case 13: /*ICEc*/                                                        // 0.0
/*3008 */                 switch (OP1) {                                                       // 0.0
/*3010 */                 case 0: /*IPFLl*/                                                    // 0.0
/*3012 */                     HAS_OPTION(XTENSA_OPTION_ICACHE_INDEX_LOCK);                     // 0.0
/*3014 */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*3016 */                         gen_icache_hit_test4();                                      // 0.0
/*3018 */                     }                                                                // 0.0
/*3020 */                     break;                                                           // 0.0
/*3024 */                 case 2: /*IHUl*/                                                     // 0.0
/*3026 */                     HAS_OPTION(XTENSA_OPTION_ICACHE_INDEX_LOCK);                     // 0.0
/*3028 */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*3030 */                         gen_icache_hit_test4();                                      // 0.0
/*3032 */                     }                                                                // 0.0
/*3034 */                     break;                                                           // 0.0
/*3038 */                 case 3: /*IIUl*/                                                     // 0.0
/*3040 */                     HAS_OPTION(XTENSA_OPTION_ICACHE_INDEX_LOCK);                     // 0.0
/*3042 */                     if (gen_check_privilege(dc)) {                                   // 0.0
/*3044 */                         gen_window_check1(dc, RRI4_S);                               // 0.0
/*3046 */                     }                                                                // 0.0
/*3048 */                     break;                                                           // 0.0
/*3052 */                 default: /*reserved*/                                                // 0.0
/*3054 */                     RESERVED();                                                      // 0.0
/*3056 */                     break;                                                           // 0.0
/*3058 */                 }                                                                    // 0.0
/*3060 */                 break;                                                               // 0.0
/*3064 */             case 14: /*IHIc*/                                                        // 0.0
/*3066 */                 HAS_OPTION(XTENSA_OPTION_ICACHE);                                    // 0.0
/*3068 */                 gen_icache_hit_test8();                                              // 0.0
/*3070 */                 break;                                                               // 0.0
/*3074 */             case 15: /*IIIc*/                                                        // 0.0
/*3076 */                 HAS_OPTION(XTENSA_OPTION_ICACHE);                                    // 0.0
/*3078 */                 if (gen_check_privilege(dc)) {                                       // 0.0
/*3080 */                     gen_window_check1(dc, RRI8_S);                                   // 0.0
/*3082 */                 }                                                                    // 0.0
/*3084 */                 break;                                                               // 0.0
/*3088 */             default: /*reserved*/                                                    // 0.0
/*3090 */                 RESERVED();                                                          // 0.0
/*3092 */                 break;                                                               // 0.0
/*3094 */             }                                                                        // 0.0
/*3096 */             break;                                                                   // 0.0
/*3100 */ #undef gen_icache_hit_test                                                           // 0.0
/*3102 */ #undef gen_icache_hit_test4                                                          // 0.0
/*3104 */ #undef gen_icache_hit_test8                                                          // 0.0
/*3108 */         case 9: /*L16SI*/                                                            // 0.0
/*3110 */             gen_load_store(ld16s, 1);                                                // 0.0
/*3112 */             break;                                                                   // 0.0
/*3114 */ #undef gen_load_store                                                                // 0.0
/*3118 */         case 10: /*MOVI*/                                                            // 0.0
/*3120 */             if (gen_window_check1(dc, RRI8_T)) {                                     // 0.0
/*3122 */                 tcg_gen_movi_i32(cpu_R[RRI8_T],                                      // 0.0
/*3124 */                                  RRI8_IMM8 | (RRI8_S << 8) |                         // 0.0
/*3126 */                                  ((RRI8_S & 0x8) ? 0xfffff000 : 0));                 // 0.0
/*3128 */             }                                                                        // 0.0
/*3130 */             break;                                                                   // 0.0
/*3134 */ #define gen_load_store_no_hw_align(type) do { \                                      // 0.0
/*3136 */             if (gen_window_check2(dc, RRI8_S, RRI8_T)) { \                           // 0.0
/*3138 */                 TCGv_i32 addr = tcg_temp_local_new_i32(); \                          // 0.0
/*3140 */                 tcg_gen_addi_i32(addr, cpu_R[RRI8_S], RRI8_IMM8 << 2); \             // 0.0
/*3142 */                 gen_load_store_alignment(dc, 2, addr, true); \                       // 0.0
/*3144 */                 tcg_gen_qemu_##type(cpu_R[RRI8_T], addr, dc->cring); \               // 0.0
/*3146 */                 tcg_temp_free(addr); \                                               // 0.0
/*3148 */             } \                                                                      // 0.0
/*3150 */         } while (0)                                                                  // 0.0
/*3154 */         case 11: /*L32AIy*/                                                          // 0.0
/*3156 */             HAS_OPTION(XTENSA_OPTION_MP_SYNCHRO);                                    // 0.0
/*3158 */             gen_load_store_no_hw_align(ld32u); /*TODO acquire?*/                     // 0.0
/*3160 */             break;                                                                   // 0.0
/*3164 */         case 12: /*ADDI*/                                                            // 0.0
/*3166 */             if (gen_window_check2(dc, RRI8_S, RRI8_T)) {                             // 0.0
/*3168 */                 tcg_gen_addi_i32(cpu_R[RRI8_T], cpu_R[RRI8_S], RRI8_IMM8_SE);        // 0.0
/*3170 */             }                                                                        // 0.0
/*3172 */             break;                                                                   // 0.0
/*3176 */         case 13: /*ADDMI*/                                                           // 0.0
/*3178 */             if (gen_window_check2(dc, RRI8_S, RRI8_T)) {                             // 0.0
/*3180 */                 tcg_gen_addi_i32(cpu_R[RRI8_T], cpu_R[RRI8_S],                       // 0.0
/*3182 */                                  RRI8_IMM8_SE << 8);                                 // 0.0
/*3184 */             }                                                                        // 0.0
/*3186 */             break;                                                                   // 0.0
/*3190 */         case 14: /*S32C1Iy*/                                                         // 0.0
/*3192 */             HAS_OPTION(XTENSA_OPTION_CONDITIONAL_STORE);                             // 0.0
/*3194 */             if (gen_window_check2(dc, RRI8_S, RRI8_T)) {                             // 0.0
/*3196 */                 int label = gen_new_label();                                         // 0.0
/*3198 */                 TCGv_i32 tmp = tcg_temp_local_new_i32();                             // 0.0
/*3200 */                 TCGv_i32 addr = tcg_temp_local_new_i32();                            // 0.0
/*3202 */                 TCGv_i32 tpc;                                                        // 0.0
/*3206 */                 tcg_gen_mov_i32(tmp, cpu_R[RRI8_T]);                                 // 0.0
/*3208 */                 tcg_gen_addi_i32(addr, cpu_R[RRI8_S], RRI8_IMM8 << 2);               // 0.0
/*3210 */                 gen_load_store_alignment(dc, 2, addr, true);                         // 0.0
/*3214 */                 gen_advance_ccount(dc);                                              // 0.0
/*3216 */                 tpc = tcg_const_i32(dc->pc);                                         // 0.0
/*3218 */                 gen_helper_check_atomctl(cpu_env, tpc, addr);                        // 0.0
/*3220 */                 tcg_gen_qemu_ld32u(cpu_R[RRI8_T], addr, dc->cring);                  // 0.0
/*3222 */                 tcg_gen_brcond_i32(TCG_COND_NE, cpu_R[RRI8_T],                       // 0.0
/*3224 */                         cpu_SR[SCOMPARE1], label);                                   // 0.0
/*3228 */                 tcg_gen_qemu_st32(tmp, addr, dc->cring);                             // 0.0
/*3232 */                 gen_set_label(label);                                                // 0.0
/*3234 */                 tcg_temp_free(tpc);                                                  // 0.0
/*3236 */                 tcg_temp_free(addr);                                                 // 0.0
/*3238 */                 tcg_temp_free(tmp);                                                  // 0.0
/*3240 */             }                                                                        // 0.0
/*3242 */             break;                                                                   // 0.0
/*3246 */         case 15: /*S32RIy*/                                                          // 0.0
/*3248 */             HAS_OPTION(XTENSA_OPTION_MP_SYNCHRO);                                    // 0.0
/*3250 */             gen_load_store_no_hw_align(st32); /*TODO release?*/                      // 0.0
/*3252 */             break;                                                                   // 0.0
/*3254 */ #undef gen_load_store_no_hw_align                                                    // 0.0
/*3258 */         default: /*reserved*/                                                        // 0.0
/*3260 */             RESERVED();                                                              // 0.0
/*3262 */             break;                                                                   // 0.0
/*3264 */         }                                                                            // 0.0
/*3266 */         break;                                                                       // 0.0
/*3270 */     case 3: /*LSCIp*/                                                                // 0.0
/*3272 */         switch (RRI8_R) {                                                            // 0.0
/*3274 */         case 0: /*LSIf*/                                                             // 0.0
/*3276 */         case 4: /*SSIf*/                                                             // 0.0
/*3278 */         case 8: /*LSIUf*/                                                            // 0.0
/*3280 */         case 12: /*SSIUf*/                                                           // 0.0
/*3282 */             HAS_OPTION(XTENSA_OPTION_FP_COPROCESSOR);                                // 0.0
/*3284 */             if (gen_window_check1(dc, RRI8_S) &&                                     // 0.0
/*3286 */                 gen_check_cpenable(dc, 0)) {                                         // 0.0
/*3288 */                 TCGv_i32 addr = tcg_temp_new_i32();                                  // 0.0
/*3290 */                 tcg_gen_addi_i32(addr, cpu_R[RRI8_S], RRI8_IMM8 << 2);               // 0.0
/*3292 */                 gen_load_store_alignment(dc, 2, addr, false);                        // 0.0
/*3294 */                 if (RRI8_R & 0x4) {                                                  // 0.0
/*3296 */                     tcg_gen_qemu_st32(cpu_FR[RRI8_T], addr, dc->cring);              // 0.0
/*3298 */                 } else {                                                             // 0.0
/*3300 */                     tcg_gen_qemu_ld32u(cpu_FR[RRI8_T], addr, dc->cring);             // 0.0
/*3302 */                 }                                                                    // 0.0
/*3304 */                 if (RRI8_R & 0x8) {                                                  // 0.0
/*3306 */                     tcg_gen_mov_i32(cpu_R[RRI8_S], addr);                            // 0.0
/*3308 */                 }                                                                    // 0.0
/*3310 */                 tcg_temp_free(addr);                                                 // 0.0
/*3312 */             }                                                                        // 0.0
/*3314 */             break;                                                                   // 0.0
/*3318 */         default: /*reserved*/                                                        // 0.0
/*3320 */             RESERVED();                                                              // 0.0
/*3322 */             break;                                                                   // 0.0
/*3324 */         }                                                                            // 0.0
/*3326 */         break;                                                                       // 0.0
/*3330 */     case 4: /*MAC16d*/                                                               // 0.0
/*3332 */         HAS_OPTION(XTENSA_OPTION_MAC16);                                             // 0.0
/*3334 */         {                                                                            // 0.0
/*3336 */             enum {                                                                   // 0.0
/*3338 */                 MAC16_UMUL = 0x0,                                                    // 0.0
/*3340 */                 MAC16_MUL  = 0x4,                                                    // 0.0
/*3342 */                 MAC16_MULA = 0x8,                                                    // 0.0
/*3344 */                 MAC16_MULS = 0xc,                                                    // 0.0
/*3346 */                 MAC16_NONE = 0xf,                                                    // 0.0
/*3348 */             } op = OP1 & 0xc;                                                        // 0.0
/*3350 */             bool is_m1_sr = (OP2 & 0x3) == 2;                                        // 0.0
/*3352 */             bool is_m2_sr = (OP2 & 0xc) == 0;                                        // 0.0
/*3354 */             uint32_t ld_offset = 0;                                                  // 0.0
/*3358 */             if (OP2 > 9) {                                                           // 0.0
/*3360 */                 RESERVED();                                                          // 0.0
/*3362 */             }                                                                        // 0.0
/*3366 */             switch (OP2 & 2) {                                                       // 0.0
/*3368 */             case 0: /*MACI?/MACC?*/                                                  // 0.0
/*3370 */                 is_m1_sr = true;                                                     // 0.0
/*3372 */                 ld_offset = (OP2 & 1) ? -4 : 4;                                      // 0.0
/*3376 */                 if (OP2 >= 8) { /*MACI/MACC*/                                        // 0.0
/*3378 */                     if (OP1 == 0) { /*LDINC/LDDEC*/                                  // 0.0
/*3380 */                         op = MAC16_NONE;                                             // 0.0
/*3382 */                     } else {                                                         // 0.0
/*3384 */                         RESERVED();                                                  // 0.0
/*3386 */                     }                                                                // 0.0
/*3388 */                 } else if (op != MAC16_MULA) { /*MULA.*.*.LDINC/LDDEC*/              // 0.0
/*3390 */                     RESERVED();                                                      // 0.0
/*3392 */                 }                                                                    // 0.0
/*3394 */                 break;                                                               // 0.0
/*3398 */             case 2: /*MACD?/MACA?*/                                                  // 0.0
/*3400 */                 if (op == MAC16_UMUL && OP2 != 7) { /*UMUL only in MACAA*/           // 0.0
/*3402 */                     RESERVED();                                                      // 0.0
/*3404 */                 }                                                                    // 0.0
/*3406 */                 break;                                                               // 0.0
/*3408 */             }                                                                        // 0.0
/*3412 */             if (op != MAC16_NONE) {                                                  // 0.0
/*3414 */                 if (!is_m1_sr && !gen_window_check1(dc, RRR_S)) {                    // 0.0
/*3416 */                     break;                                                           // 0.0
/*3418 */                 }                                                                    // 0.0
/*3420 */                 if (!is_m2_sr && !gen_window_check1(dc, RRR_T)) {                    // 0.0
/*3422 */                     break;                                                           // 0.0
/*3424 */                 }                                                                    // 0.0
/*3426 */             }                                                                        // 0.0
/*3430 */             if (ld_offset && !gen_window_check1(dc, RRR_S)) {                        // 0.0
/*3432 */                 break;                                                               // 0.0
/*3434 */             }                                                                        // 0.0
/*3438 */             {                                                                        // 0.0
/*3440 */                 TCGv_i32 vaddr = tcg_temp_new_i32();                                 // 0.0
/*3442 */                 TCGv_i32 mem32 = tcg_temp_new_i32();                                 // 0.0
/*3446 */                 if (ld_offset) {                                                     // 0.0
/*3448 */                     tcg_gen_addi_i32(vaddr, cpu_R[RRR_S], ld_offset);                // 0.0
/*3450 */                     gen_load_store_alignment(dc, 2, vaddr, false);                   // 0.0
/*3452 */                     tcg_gen_qemu_ld32u(mem32, vaddr, dc->cring);                     // 0.0
/*3454 */                 }                                                                    // 0.0
/*3456 */                 if (op != MAC16_NONE) {                                              // 0.0
/*3458 */                     TCGv_i32 m1 = gen_mac16_m(                                       // 0.0
/*3460 */                             is_m1_sr ? cpu_SR[MR + RRR_X] : cpu_R[RRR_S],            // 0.0
/*3462 */                             OP1 & 1, op == MAC16_UMUL);                              // 0.0
/*3464 */                     TCGv_i32 m2 = gen_mac16_m(                                       // 0.0
/*3466 */                             is_m2_sr ? cpu_SR[MR + 2 + RRR_Y] : cpu_R[RRR_T],        // 0.0
/*3468 */                             OP1 & 2, op == MAC16_UMUL);                              // 0.0
/*3472 */                     if (op == MAC16_MUL || op == MAC16_UMUL) {                       // 0.0
/*3474 */                         tcg_gen_mul_i32(cpu_SR[ACCLO], m1, m2);                      // 0.0
/*3476 */                         if (op == MAC16_UMUL) {                                      // 0.0
/*3478 */                             tcg_gen_movi_i32(cpu_SR[ACCHI], 0);                      // 0.0
/*3480 */                         } else {                                                     // 0.0
/*3482 */                             tcg_gen_sari_i32(cpu_SR[ACCHI], cpu_SR[ACCLO], 31);      // 0.0
/*3484 */                         }                                                            // 0.0
/*3486 */                     } else {                                                         // 0.0
/*3488 */                         TCGv_i32 lo = tcg_temp_new_i32();                            // 0.0
/*3490 */                         TCGv_i32 hi = tcg_temp_new_i32();                            // 0.0
/*3494 */                         tcg_gen_mul_i32(lo, m1, m2);                                 // 0.0
/*3496 */                         tcg_gen_sari_i32(hi, lo, 31);                                // 0.0
/*3498 */                         if (op == MAC16_MULA) {                                      // 0.0
/*3500 */                             tcg_gen_add2_i32(cpu_SR[ACCLO], cpu_SR[ACCHI],           // 0.0
/*3502 */                                              cpu_SR[ACCLO], cpu_SR[ACCHI],           // 0.0
/*3504 */                                              lo, hi);                                // 0.0
/*3506 */                         } else {                                                     // 0.0
/*3508 */                             tcg_gen_sub2_i32(cpu_SR[ACCLO], cpu_SR[ACCHI],           // 0.0
/*3510 */                                              cpu_SR[ACCLO], cpu_SR[ACCHI],           // 0.0
/*3512 */                                              lo, hi);                                // 0.0
/*3514 */                         }                                                            // 0.0
/*3516 */                         tcg_gen_ext8s_i32(cpu_SR[ACCHI], cpu_SR[ACCHI]);             // 0.0
/*3520 */                         tcg_temp_free_i32(lo);                                       // 0.0
/*3522 */                         tcg_temp_free_i32(hi);                                       // 0.0
/*3524 */                     }                                                                // 0.0
/*3526 */                     tcg_temp_free(m1);                                               // 0.0
/*3528 */                     tcg_temp_free(m2);                                               // 0.0
/*3530 */                 }                                                                    // 0.0
/*3532 */                 if (ld_offset) {                                                     // 0.0
/*3534 */                     tcg_gen_mov_i32(cpu_R[RRR_S], vaddr);                            // 0.0
/*3536 */                     tcg_gen_mov_i32(cpu_SR[MR + RRR_W], mem32);                      // 0.0
/*3538 */                 }                                                                    // 0.0
/*3540 */                 tcg_temp_free(vaddr);                                                // 0.0
/*3542 */                 tcg_temp_free(mem32);                                                // 0.0
/*3544 */             }                                                                        // 0.0
/*3546 */         }                                                                            // 0.0
/*3548 */         break;                                                                       // 0.0
/*3552 */     case 5: /*CALLN*/                                                                // 0.0
/*3554 */         switch (CALL_N) {                                                            // 0.0
/*3556 */         case 0: /*CALL0*/                                                            // 0.0
/*3558 */             tcg_gen_movi_i32(cpu_R[0], dc->next_pc);                                 // 0.0
/*3560 */             gen_jumpi(dc, (dc->pc & ~3) + (CALL_OFFSET_SE << 2) + 4, 0);             // 0.0
/*3562 */             break;                                                                   // 0.0
/*3566 */         case 1: /*CALL4w*/                                                           // 0.0
/*3568 */         case 2: /*CALL8w*/                                                           // 0.0
/*3570 */         case 3: /*CALL12w*/                                                          // 0.0
/*3572 */             HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);                             // 0.0
/*3574 */             if (gen_window_check1(dc, CALL_N << 2)) {                                // 0.0
/*3576 */                 gen_callwi(dc, CALL_N,                                               // 0.0
/*3578 */                            (dc->pc & ~3) + (CALL_OFFSET_SE << 2) + 4, 0);            // 0.0
/*3580 */             }                                                                        // 0.0
/*3582 */             break;                                                                   // 0.0
/*3584 */         }                                                                            // 0.0
/*3586 */         break;                                                                       // 0.0
/*3590 */     case 6: /*SI*/                                                                   // 0.0
/*3592 */         switch (CALL_N) {                                                            // 0.0
/*3594 */         case 0: /*J*/                                                                // 0.0
/*3596 */             gen_jumpi(dc, dc->pc + 4 + CALL_OFFSET_SE, 0);                           // 0.0
/*3598 */             break;                                                                   // 0.0
/*3602 */         case 1: /*BZ*/                                                               // 0.0
/*3604 */             if (gen_window_check1(dc, BRI12_S)) {                                    // 0.0
/*3606 */                 static const TCGCond cond[] = {                                      // 0.0
/*3608 */                     TCG_COND_EQ, /*BEQZ*/                                            // 0.0
/*3610 */                     TCG_COND_NE, /*BNEZ*/                                            // 0.0
/*3612 */                     TCG_COND_LT, /*BLTZ*/                                            // 0.0
/*3614 */                     TCG_COND_GE, /*BGEZ*/                                            // 0.0
/*3616 */                 };                                                                   // 0.0
/*3620 */                 gen_brcondi(dc, cond[BRI12_M & 3], cpu_R[BRI12_S], 0,                // 0.0
/*3622 */                         4 + BRI12_IMM12_SE);                                         // 0.0
/*3624 */             }                                                                        // 0.0
/*3626 */             break;                                                                   // 0.0
/*3630 */         case 2: /*BI0*/                                                              // 0.0
/*3632 */             if (gen_window_check1(dc, BRI8_S)) {                                     // 0.0
/*3634 */                 static const TCGCond cond[] = {                                      // 0.0
/*3636 */                     TCG_COND_EQ, /*BEQI*/                                            // 0.0
/*3638 */                     TCG_COND_NE, /*BNEI*/                                            // 0.0
/*3640 */                     TCG_COND_LT, /*BLTI*/                                            // 0.0
/*3642 */                     TCG_COND_GE, /*BGEI*/                                            // 0.0
/*3644 */                 };                                                                   // 0.0
/*3648 */                 gen_brcondi(dc, cond[BRI8_M & 3],                                    // 0.0
/*3650 */                         cpu_R[BRI8_S], B4CONST[BRI8_R], 4 + BRI8_IMM8_SE);           // 0.0
/*3652 */             }                                                                        // 0.0
/*3654 */             break;                                                                   // 0.0
/*3658 */         case 3: /*BI1*/                                                              // 0.0
/*3660 */             switch (BRI8_M) {                                                        // 0.0
/*3662 */             case 0: /*ENTRYw*/                                                       // 0.0
/*3664 */                 HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);                         // 0.0
/*3666 */                 {                                                                    // 0.0
/*3668 */                     TCGv_i32 pc = tcg_const_i32(dc->pc);                             // 0.0
/*3670 */                     TCGv_i32 s = tcg_const_i32(BRI12_S);                             // 0.0
/*3672 */                     TCGv_i32 imm = tcg_const_i32(BRI12_IMM12);                       // 0.0
/*3674 */                     gen_advance_ccount(dc);                                          // 0.0
/*3676 */                     gen_helper_entry(cpu_env, pc, s, imm);                           // 0.0
/*3678 */                     tcg_temp_free(imm);                                              // 0.0
/*3680 */                     tcg_temp_free(s);                                                // 0.0
/*3682 */                     tcg_temp_free(pc);                                               // 0.0
/*3684 */                     /* This can change tb->flags, so exit tb */                      // 0.0
/*3686 */                     gen_jumpi_check_loop_end(dc, -1);                                // 0.0
/*3688 */                 }                                                                    // 0.0
/*3690 */                 break;                                                               // 0.0
/*3694 */             case 1: /*B1*/                                                           // 0.0
/*3696 */                 switch (BRI8_R) {                                                    // 0.0
/*3698 */                 case 0: /*BFp*/                                                      // 0.0
/*3700 */                 case 1: /*BTp*/                                                      // 0.0
/*3702 */                     HAS_OPTION(XTENSA_OPTION_BOOLEAN);                               // 0.0
/*3704 */                     {                                                                // 0.0
/*3706 */                         TCGv_i32 tmp = tcg_temp_new_i32();                           // 0.0
/*3708 */                         tcg_gen_andi_i32(tmp, cpu_SR[BR], 1 << RRI8_S);              // 0.0
/*3710 */                         gen_brcondi(dc,                                              // 0.0
/*3712 */                                 BRI8_R == 1 ? TCG_COND_NE : TCG_COND_EQ,             // 0.0
/*3714 */                                 tmp, 0, 4 + RRI8_IMM8_SE);                           // 0.0
/*3716 */                         tcg_temp_free(tmp);                                          // 0.0
/*3718 */                     }                                                                // 0.0
/*3720 */                     break;                                                           // 0.0
/*3724 */                 case 8: /*LOOP*/                                                     // 0.0
/*3726 */                 case 9: /*LOOPNEZ*/                                                  // 0.0
/*3728 */                 case 10: /*LOOPGTZ*/                                                 // 0.0
/*3730 */                     HAS_OPTION(XTENSA_OPTION_LOOP);                                  // 0.0
/*3732 */                     if (gen_window_check1(dc, RRI8_S)) {                             // 0.0
/*3734 */                         uint32_t lend = dc->pc + RRI8_IMM8 + 4;                      // 0.0
/*3736 */                         TCGv_i32 tmp = tcg_const_i32(lend);                          // 0.0
/*3740 */                         tcg_gen_subi_i32(cpu_SR[LCOUNT], cpu_R[RRI8_S], 1);          // 0.0
/*3742 */                         tcg_gen_movi_i32(cpu_SR[LBEG], dc->next_pc);                 // 0.0
/*3744 */                         gen_helper_wsr_lend(cpu_env, tmp);                           // 0.0
/*3746 */                         tcg_temp_free(tmp);                                          // 0.0
/*3750 */                         if (BRI8_R > 8) {                                            // 0.0
/*3752 */                             int label = gen_new_label();                             // 0.0
/*3754 */                             tcg_gen_brcondi_i32(                                     // 0.0
/*3756 */                                     BRI8_R == 9 ? TCG_COND_NE : TCG_COND_GT,         // 0.0
/*3758 */                                     cpu_R[RRI8_S], 0, label);                        // 0.0
/*3760 */                             gen_jumpi(dc, lend, 1);                                  // 0.0
/*3762 */                             gen_set_label(label);                                    // 0.0
/*3764 */                         }                                                            // 0.0
/*3768 */                         gen_jumpi(dc, dc->next_pc, 0);                               // 0.0
/*3770 */                     }                                                                // 0.0
/*3772 */                     break;                                                           // 0.0
/*3776 */                 default: /*reserved*/                                                // 0.0
/*3778 */                     RESERVED();                                                      // 0.0
/*3780 */                     break;                                                           // 0.0
/*3784 */                 }                                                                    // 0.0
/*3786 */                 break;                                                               // 0.0
/*3790 */             case 2: /*BLTUI*/                                                        // 0.0
/*3792 */             case 3: /*BGEUI*/                                                        // 0.0
/*3794 */                 if (gen_window_check1(dc, BRI8_S)) {                                 // 0.0
/*3796 */                     gen_brcondi(dc, BRI8_M == 2 ? TCG_COND_LTU : TCG_COND_GEU,       // 0.0
/*3798 */                                 cpu_R[BRI8_S], B4CONSTU[BRI8_R],                     // 0.0
/*3800 */                                 4 + BRI8_IMM8_SE);                                   // 0.0
/*3802 */                 }                                                                    // 0.0
/*3804 */                 break;                                                               // 0.0
/*3806 */             }                                                                        // 0.0
/*3808 */             break;                                                                   // 0.0
/*3812 */         }                                                                            // 0.0
/*3814 */         break;                                                                       // 0.0
/*3818 */     case 7: /*B*/                                                                    // 0.0
/*3820 */         {                                                                            // 0.0
/*3822 */             TCGCond eq_ne = (RRI8_R & 8) ? TCG_COND_NE : TCG_COND_EQ;                // 0.0
/*3826 */             switch (RRI8_R & 7) {                                                    // 0.0
/*3828 */             case 0: /*BNONE*/ /*BANY*/                                               // 0.0
/*3830 */                 if (gen_window_check2(dc, RRI8_S, RRI8_T)) {                         // 0.0
/*3832 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*3834 */                     tcg_gen_and_i32(tmp, cpu_R[RRI8_S], cpu_R[RRI8_T]);              // 0.0
/*3836 */                     gen_brcondi(dc, eq_ne, tmp, 0, 4 + RRI8_IMM8_SE);                // 0.0
/*3838 */                     tcg_temp_free(tmp);                                              // 0.0
/*3840 */                 }                                                                    // 0.0
/*3842 */                 break;                                                               // 0.0
/*3846 */             case 1: /*BEQ*/ /*BNE*/                                                  // 0.0
/*3848 */             case 2: /*BLT*/ /*BGE*/                                                  // 0.0
/*3850 */             case 3: /*BLTU*/ /*BGEU*/                                                // 0.0
/*3852 */                 if (gen_window_check2(dc, RRI8_S, RRI8_T)) {                         // 0.0
/*3854 */                     static const TCGCond cond[] = {                                  // 0.0
/*3856 */                         [1] = TCG_COND_EQ,                                           // 0.0
/*3858 */                         [2] = TCG_COND_LT,                                           // 0.0
/*3860 */                         [3] = TCG_COND_LTU,                                          // 0.0
/*3862 */                         [9] = TCG_COND_NE,                                           // 0.0
/*3864 */                         [10] = TCG_COND_GE,                                          // 0.0
/*3866 */                         [11] = TCG_COND_GEU,                                         // 0.0
/*3868 */                     };                                                               // 0.0
/*3870 */                     gen_brcond(dc, cond[RRI8_R], cpu_R[RRI8_S], cpu_R[RRI8_T],       // 0.0
/*3872 */                             4 + RRI8_IMM8_SE);                                       // 0.0
/*3874 */                 }                                                                    // 0.0
/*3876 */                 break;                                                               // 0.0
/*3880 */             case 4: /*BALL*/ /*BNALL*/                                               // 0.0
/*3882 */                 if (gen_window_check2(dc, RRI8_S, RRI8_T)) {                         // 0.0
/*3884 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*3886 */                     tcg_gen_and_i32(tmp, cpu_R[RRI8_S], cpu_R[RRI8_T]);              // 0.0
/*3888 */                     gen_brcond(dc, eq_ne, tmp, cpu_R[RRI8_T],                        // 0.0
/*3890 */                             4 + RRI8_IMM8_SE);                                       // 0.0
/*3892 */                     tcg_temp_free(tmp);                                              // 0.0
/*3894 */                 }                                                                    // 0.0
/*3896 */                 break;                                                               // 0.0
/*3900 */             case 5: /*BBC*/ /*BBS*/                                                  // 0.0
/*3902 */                 if (gen_window_check2(dc, RRI8_S, RRI8_T)) {                         // 0.0
/*3904 */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // 0.0
/*3906 */                     TCGv_i32 bit = tcg_const_i32(0x80000000);                        // 0.0
/*3908 */ #else                                                                                // 0.0
/*3910 */                     TCGv_i32 bit = tcg_const_i32(0x00000001);                        // 0.0
/*3912 */ #endif                                                                               // 0.0
/*3914 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*3916 */                     tcg_gen_andi_i32(tmp, cpu_R[RRI8_T], 0x1f);                      // 0.0
/*3918 */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // 0.0
/*3920 */                     tcg_gen_shr_i32(bit, bit, tmp);                                  // 0.0
/*3922 */ #else                                                                                // 0.0
/*3924 */                     tcg_gen_shl_i32(bit, bit, tmp);                                  // 0.0
/*3926 */ #endif                                                                               // 0.0
/*3928 */                     tcg_gen_and_i32(tmp, cpu_R[RRI8_S], bit);                        // 0.0
/*3930 */                     gen_brcondi(dc, eq_ne, tmp, 0, 4 + RRI8_IMM8_SE);                // 0.0
/*3932 */                     tcg_temp_free(tmp);                                              // 0.0
/*3934 */                     tcg_temp_free(bit);                                              // 0.0
/*3936 */                 }                                                                    // 0.0
/*3938 */                 break;                                                               // 0.0
/*3942 */             case 6: /*BBCI*/ /*BBSI*/                                                // 0.0
/*3944 */             case 7:                                                                  // 0.0
/*3946 */                 if (gen_window_check1(dc, RRI8_S)) {                                 // 0.0
/*3948 */                     TCGv_i32 tmp = tcg_temp_new_i32();                               // 0.0
/*3950 */                     tcg_gen_andi_i32(tmp, cpu_R[RRI8_S],                             // 0.0
/*3952 */ #ifdef TARGET_WORDS_BIGENDIAN                                                        // 0.0
/*3954 */                             0x80000000 >> (((RRI8_R & 1) << 4) | RRI8_T));           // 0.0
/*3956 */ #else                                                                                // 0.0
/*3958 */                             0x00000001 << (((RRI8_R & 1) << 4) | RRI8_T));           // 0.0
/*3960 */ #endif                                                                               // 0.0
/*3962 */                     gen_brcondi(dc, eq_ne, tmp, 0, 4 + RRI8_IMM8_SE);                // 0.0
/*3964 */                     tcg_temp_free(tmp);                                              // 0.0
/*3966 */                 }                                                                    // 0.0
/*3968 */                 break;                                                               // 0.0
/*3972 */             }                                                                        // 0.0
/*3974 */         }                                                                            // 0.0
/*3976 */         break;                                                                       // 0.0
/*3980 */ #define gen_narrow_load_store(type) do { \                                           // 0.0
/*3982 */             if (gen_window_check2(dc, RRRN_S, RRRN_T)) { \                           // 0.0
/*3984 */                 TCGv_i32 addr = tcg_temp_new_i32(); \                                // 0.0
/*3986 */                 tcg_gen_addi_i32(addr, cpu_R[RRRN_S], RRRN_R << 2); \                // 0.0
/*3988 */                 gen_load_store_alignment(dc, 2, addr, false); \                      // 0.0
/*3990 */                 tcg_gen_qemu_##type(cpu_R[RRRN_T], addr, dc->cring); \               // 0.0
/*3992 */                 tcg_temp_free(addr); \                                               // 0.0
/*3994 */             } \                                                                      // 0.0
/*3996 */         } while (0)                                                                  // 0.0
/*4000 */     case 8: /*L32I.Nn*/                                                              // 0.0
/*4002 */         gen_narrow_load_store(ld32u);                                                // 0.0
/*4004 */         break;                                                                       // 0.0
/*4008 */     case 9: /*S32I.Nn*/                                                              // 0.0
/*4010 */         gen_narrow_load_store(st32);                                                 // 0.0
/*4012 */         break;                                                                       // 0.0
/*4014 */ #undef gen_narrow_load_store                                                         // 0.0
/*4018 */     case 10: /*ADD.Nn*/                                                              // 0.0
/*4020 */         if (gen_window_check3(dc, RRRN_R, RRRN_S, RRRN_T)) {                         // 0.0
/*4022 */             tcg_gen_add_i32(cpu_R[RRRN_R], cpu_R[RRRN_S], cpu_R[RRRN_T]);            // 0.0
/*4024 */         }                                                                            // 0.0
/*4026 */         break;                                                                       // 0.0
/*4030 */     case 11: /*ADDI.Nn*/                                                             // 0.0
/*4032 */         if (gen_window_check2(dc, RRRN_R, RRRN_S)) {                                 // 0.0
/*4034 */             tcg_gen_addi_i32(cpu_R[RRRN_R], cpu_R[RRRN_S],                           // 0.0
/*4036 */                              RRRN_T ? RRRN_T : -1);                                  // 0.0
/*4038 */         }                                                                            // 0.0
/*4040 */         break;                                                                       // 0.0
/*4044 */     case 12: /*ST2n*/                                                                // 0.0
/*4046 */         if (!gen_window_check1(dc, RRRN_S)) {                                        // 0.0
/*4048 */             break;                                                                   // 0.0
/*4050 */         }                                                                            // 0.0
/*4052 */         if (RRRN_T < 8) { /*MOVI.Nn*/                                                // 0.0
/*4054 */             tcg_gen_movi_i32(cpu_R[RRRN_S],                                          // 0.0
/*4056 */                     RRRN_R | (RRRN_T << 4) |                                         // 0.0
/*4058 */                     ((RRRN_T & 6) == 6 ? 0xffffff80 : 0));                           // 0.0
/*4060 */         } else { /*BEQZ.Nn*/ /*BNEZ.Nn*/                                             // 0.0
/*4062 */             TCGCond eq_ne = (RRRN_T & 4) ? TCG_COND_NE : TCG_COND_EQ;                // 0.0
/*4066 */             gen_brcondi(dc, eq_ne, cpu_R[RRRN_S], 0,                                 // 0.0
/*4068 */                     4 + (RRRN_R | ((RRRN_T & 3) << 4)));                             // 0.0
/*4070 */         }                                                                            // 0.0
/*4072 */         break;                                                                       // 0.0
/*4076 */     case 13: /*ST3n*/                                                                // 0.0
/*4078 */         switch (RRRN_R) {                                                            // 0.0
/*4080 */         case 0: /*MOV.Nn*/                                                           // 0.0
/*4082 */             if (gen_window_check2(dc, RRRN_S, RRRN_T)) {                             // 0.0
/*4084 */                 tcg_gen_mov_i32(cpu_R[RRRN_T], cpu_R[RRRN_S]);                       // 0.0
/*4086 */             }                                                                        // 0.0
/*4088 */             break;                                                                   // 0.0
/*4092 */         case 15: /*S3*/                                                              // 0.0
/*4094 */             switch (RRRN_T) {                                                        // 0.0
/*4096 */             case 0: /*RET.Nn*/                                                       // 0.0
/*4098 */                 gen_jump(dc, cpu_R[0]);                                              // 0.0
/*4100 */                 break;                                                               // 0.0
/*4104 */             case 1: /*RETW.Nn*/                                                      // 0.0
/*4106 */                 HAS_OPTION(XTENSA_OPTION_WINDOWED_REGISTER);                         // 0.0
/*4108 */                 {                                                                    // 0.0
/*4110 */                     TCGv_i32 tmp = tcg_const_i32(dc->pc);                            // 0.0
/*4112 */                     gen_advance_ccount(dc);                                          // 0.0
/*4114 */                     gen_helper_retw(tmp, cpu_env, tmp);                              // 0.0
/*4116 */                     gen_jump(dc, tmp);                                               // 0.0
/*4118 */                     tcg_temp_free(tmp);                                              // 0.0
/*4120 */                 }                                                                    // 0.0
/*4122 */                 break;                                                               // 0.0
/*4126 */             case 2: /*BREAK.Nn*/                                                     // 0.0
/*4128 */                 HAS_OPTION(XTENSA_OPTION_DEBUG);                                     // 0.0
/*4130 */                 if (dc->debug) {                                                     // 0.0
/*4132 */                     gen_debug_exception(dc, DEBUGCAUSE_BN);                          // 0.0
/*4134 */                 }                                                                    // 0.0
/*4136 */                 break;                                                               // 0.0
/*4140 */             case 3: /*NOP.Nn*/                                                       // 0.0
/*4142 */                 break;                                                               // 0.0
/*4146 */             case 6: /*ILL.Nn*/                                                       // 0.0
/*4148 */                 gen_exception_cause(dc, ILLEGAL_INSTRUCTION_CAUSE);                  // 0.0
/*4150 */                 break;                                                               // 0.0
/*4154 */             default: /*reserved*/                                                    // 0.0
/*4156 */                 RESERVED();                                                          // 0.0
/*4158 */                 break;                                                               // 0.0
/*4160 */             }                                                                        // 0.0
/*4162 */             break;                                                                   // 0.0
/*4166 */         default: /*reserved*/                                                        // 0.0
/*4168 */             RESERVED();                                                              // 0.0
/*4170 */             break;                                                                   // 0.0
/*4172 */         }                                                                            // 0.0
/*4174 */         break;                                                                       // 0.0
/*4178 */     default: /*reserved*/                                                            // 0.0
/*4180 */         RESERVED();                                                                  // 0.0
/*4182 */         break;                                                                       // 0.0
/*4184 */     }                                                                                // 0.0
/*4188 */     if (dc->is_jmp == DISAS_NEXT) {                                                  // 0.0
/*4190 */         gen_check_loop_end(dc, 0);                                                   // 0.0
/*4192 */     }                                                                                // 0.0
/*4194 */     dc->pc = dc->next_pc;                                                            // 0.0
/*4198 */     return;                                                                          // 0.0
/*4202 */ invalid_opcode:                                                                      // 0.0
/*4204 */     qemu_log("INVALID(pc = %08x)\n", dc->pc);                                        // 0.0
/*4206 */     gen_exception_cause(dc, ILLEGAL_INSTRUCTION_CAUSE);                              // 0.0
/*4208 */ #undef HAS_OPTION                                                                    // 0.0
/*4210 */ }                                                                                    // 0.0
