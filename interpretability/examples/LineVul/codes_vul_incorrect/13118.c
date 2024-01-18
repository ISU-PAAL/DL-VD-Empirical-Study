// commit message qemu@dd09c36159 (target=1, prob=0.12256759, correct=False): target/ppc: support for 32-bit carry and overflow
/*0 */ static void spr_read_xer (DisasContext *ctx, int gprn, int sprn)  // (0) 0.4528
/*2 */ {                                                                 // (2) 0.01887
/*4 */     gen_read_xer(cpu_gpr[gprn]);                                  // (1) 0.3585
/*6 */ }                                                                 // (3) 0.01887
