// commit message qemu@299f801304 (target=0, prob=0.08451677, correct=True): tcg/optimize: allow constant to have copies
/*0  */ static void tcg_opt_gen_mov(TCGContext *s, TCGOp *op, TCGArg *args,  // (3) 0.05859
/*2  */                             TCGArg dst, TCGArg src)                  // (0) 0.07227
/*4  */ {                                                                    // (26) 0.001953
/*6  */     if (temps_are_copies(dst, src)) {                                // (8) 0.03711
/*8  */         tcg_op_remove(s, op);                                        // (11) 0.03516
/*10 */         return;                                                      // (21) 0.01758
/*12 */     }                                                                // (23) 0.007812
/*16 */     if (temp_is_const(src)) {                                        // (14) 0.02734
/*18 */         tcg_opt_gen_movi(s, op, args, dst, temps[src].val);          // (2) 0.0625
/*20 */         return;                                                      // (22) 0.01758
/*22 */     }                                                                // (24) 0.007812
/*26 */     TCGOpcode new_op = op_to_mov(op->opc);                           // (7) 0.04492
/*28 */     tcg_target_ulong mask;                                           // (17) 0.02344
/*32 */     op->opc = new_op;                                                // (18) 0.02344
/*36 */     reset_temp(dst);                                                 // (20) 0.01953
/*38 */     mask = temps[src].mask;                                          // (19) 0.02344
/*40 */     if (TCG_TARGET_REG_BITS > 32 && new_op == INDEX_op_mov_i32) {    // (1) 0.06641
/*42 */         /* High bits of the destination are now garbage.  */         // (9) 0.03711
/*44 */         mask |= ~0xffffffffull;                                      // (13) 0.0332
/*46 */     }                                                                // (25) 0.007812
/*48 */     temps[dst].mask = mask;                                          // (16) 0.02539
/*52 */     assert(!temp_is_const(src));                                     // (15) 0.02734
/*56 */     if (s->temps[src].type == s->temps[dst].type) {                  // (6) 0.04883
/*58 */         temps[dst].next_copy = temps[src].next_copy;                 // (4) 0.05078
/*60 */         temps[dst].prev_copy = src;                                  // (10) 0.03711
/*62 */         temps[temps[dst].next_copy].prev_copy = dst;                 // (5) 0.05078
/*64 */         temps[src].next_copy = dst;                                  // (12) 0.03516
/*66 */         temps[dst].is_const = false;                                 // 0.0
/*68 */     }                                                                // 0.0
/*72 */     args[0] = dst;                                                   // 0.0
/*74 */     args[1] = src;                                                   // 0.0
/*76 */ }                                                                    // 0.0
