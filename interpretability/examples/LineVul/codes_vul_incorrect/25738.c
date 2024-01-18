// commit message FFmpeg@74b1bf632f (target=1, prob=0.11529432, correct=False): mp3: Make the extrasize explicit
/*0  */ static void switch_buffer(MPADecodeContext *s, int *pos, int *end_pos,  // (7) 0.08856
/*2  */                           int *end_pos2)                                // (1) 0.1181
/*4  */ {                                                                       // (11) 0.00369
/*6  */     if (s->in_gb.buffer && *pos >= s->gb.size_in_bits) {                // (2) 0.09963
/*8  */         s->gb           = s->in_gb;                                     // (3) 0.09963
/*10 */         s->in_gb.buffer = NULL;                                         // (8) 0.06273
/*12 */         assert((get_bits_count(&s->gb) & 7) == 0);                      // (4) 0.09225
/*14 */         skip_bits_long(&s->gb, *pos - *end_pos);                        // (5) 0.09225
/*16 */         *end_pos2 =                                                     // (9) 0.04797
/*18 */         *end_pos  = *end_pos2 + get_bits_count(&s->gb) - *pos;          // (0) 0.1218
/*20 */         *pos      = get_bits_count(&s->gb);                             // (6) 0.09225
/*22 */     }                                                                   // (10) 0.01476
/*24 */ }                                                                       // (12) 0.00369
