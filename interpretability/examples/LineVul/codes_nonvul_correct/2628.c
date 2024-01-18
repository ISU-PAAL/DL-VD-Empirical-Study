// commit message qemu@f02ca5cbea (target=0, prob=0.02107382, correct=True): Fix bit fitting checks
/*0  */ static inline void tcg_out_ld_ptr(TCGContext *s, int ret,                           // (6) 0.07
/*2  */                                   tcg_target_long arg)                              // (1) 0.1367
/*4  */ {                                                                                   // (12) 0.003333
/*6  */ #if defined(__sparc_v9__) && !defined(__sparc_v8plus__)                             // (4) 0.09
/*8  */     if (arg != (arg & 0xffffffff))                                                  // (8) 0.05
/*10 */         fprintf(stderr, "unimplemented %s with offset %ld\n", __func__, arg);       // (2) 0.1133
/*12 */     if (arg != (arg & 0xfff))                                                       // (9) 0.04667
/*14 */         tcg_out32(s, SETHI | INSN_RD(ret) | (((uint32_t)arg & 0xfffffc00) >> 10));  // (0) 0.15
/*16 */     tcg_out32(s, LDX | INSN_RD(ret) | INSN_RS1(ret) |                               // (3) 0.1033
/*18 */               INSN_IMM13(arg & 0x3ff));                                             // (5) 0.09
/*20 */ #else                                                                               // (11) 0.006667
/*22 */     tcg_out_ld_raw(s, ret, arg);                                                    // (7) 0.06
/*24 */ #endif                                                                              // (10) 0.006667
/*26 */ }                                                                                   // (13) 0.003333
