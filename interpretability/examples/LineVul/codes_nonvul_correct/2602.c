// commit message qemu@42a268c241 (target=0, prob=0.20712262, correct=True): tcg: Change translator-side labels to a pointer
/*0  */ int gen_new_label(void)                  // (7) 0.05921
/*2  */ {                                        // (11) 0.006579
/*4  */     TCGContext *s = &tcg_ctx;            // (1) 0.09868
/*6  */     int idx;                             // (9) 0.04605
/*8  */     TCGLabel *l;                         // (8) 0.05921
/*12 */     if (s->nb_labels >= TCG_MAX_LABELS)  // (0) 0.1316
/*14 */         tcg_abort();                     // (4) 0.08553
/*16 */     idx = s->nb_labels++;                // (5) 0.08553
/*18 */     l = &s->labels[idx];                 // (2) 0.09211
/*20 */     l->has_value = 0;                    // (6) 0.07237
/*22 */     l->u.first_reloc = NULL;             // (3) 0.09211
/*24 */     return idx;                          // (10) 0.04605
/*26 */ }                                        // (12) 0.006579
