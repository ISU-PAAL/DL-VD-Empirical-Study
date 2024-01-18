// commit message qemu@bd79255d25 (target=0, prob=0.595312, correct=False): translate: check cflags instead of use_icount global
/*0  */ static void spr_read_tbu (DisasContext *ctx, int gprn, int sprn)  // (1) 0.1727
/*2  */ {                                                                 // (10) 0.007194
/*4  */     if (use_icount) {                                             // (6) 0.07914
/*6  */         gen_io_start();                                           // (3) 0.09353
/*8  */     }                                                             // (7) 0.02878
/*10 */     gen_helper_load_tbu(cpu_gpr[gprn], cpu_env);                  // (0) 0.1871
/*12 */     if (use_icount) {                                             // (5) 0.07914
/*14 */         gen_io_end();                                             // (4) 0.09353
/*16 */         gen_stop_exception(ctx);                                  // (2) 0.1151
/*18 */     }                                                             // (8) 0.02878
/*20 */ }                                                                 // (9) 0.007194
