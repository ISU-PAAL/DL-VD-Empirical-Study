// commit message qemu@bec1631100 (target=0, prob=0.018477587, correct=True): tcg: Change generator-side labels to a pointer
/*0  */ static inline void tcg_out_goto_label(TCGContext *s, int label_index)     // (2) 0.1437
/*2  */ {                                                                         // (8) 0.005988
/*4  */     TCGLabel *l = &s->labels[label_index];                                // (4) 0.1138
/*8  */     if (!l->has_value) {                                                  // (5) 0.07186
/*10 */         tcg_out_reloc(s, s->code_ptr, R_AARCH64_JUMP26, label_index, 0);  // (0) 0.2335
/*12 */         tcg_out_goto_noaddr(s);                                           // (3) 0.1257
/*14 */     } else {                                                              // (6) 0.03593
/*16 */         tcg_out_goto(s, l->u.value_ptr);                                  // (1) 0.1497
/*18 */     }                                                                     // (7) 0.02395
/*20 */ }                                                                         // (9) 0.005988
