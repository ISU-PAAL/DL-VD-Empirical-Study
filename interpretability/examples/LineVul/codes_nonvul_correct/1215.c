// commit message qemu@b591dc59bc (target=0, prob=0.111644164, correct=True): TCG: fix negative frame offset calculations
/*0  */ static void temp_allocate_frame(TCGContext *s, int temp)                                                                 // (3) 0.08491
/*2  */ {                                                                                                                        // (10) 0.004717
/*4  */     TCGTemp *ts;                                                                                                         // (9) 0.04245
/*6  */     ts = &s->temps[temp];                                                                                                // (7) 0.06132
/*8  */     s->current_frame_offset = (s->current_frame_offset + sizeof(tcg_target_long) - 1) & ~(sizeof(tcg_target_long) - 1);  // (0) 0.2264
/*10 */     if (s->current_frame_offset + sizeof(tcg_target_long) > s->frame_end)                                                // (1) 0.1368
/*12 */         tcg_abort();                                                                                                     // (6) 0.06132
/*14 */     ts->mem_offset = s->current_frame_offset;                                                                            // (4) 0.08019
/*16 */     ts->mem_reg = s->frame_reg;                                                                                          // (5) 0.07075
/*18 */     ts->mem_allocated = 1;                                                                                               // (8) 0.0566
/*20 */     s->current_frame_offset += sizeof(tcg_target_long);                                                                  // (2) 0.09434
/*22 */ }                                                                                                                        // (11) 0.004717
