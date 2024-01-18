// commit message qemu@feced894fb (target=0, prob=0.4071448, correct=True): rng-random: NULL check not needed before g_free()
/*0  */ static void rng_random_set_filename(Object *obj, const char *filename,  // (2) 0.09615
/*2  */                                  Error **errp)                          // (0) 0.1779
/*4  */ {                                                                       // (12) 0.004808
/*6  */     RngBackend *b = RNG_BACKEND(obj);                                   // (3) 0.08654
/*8  */     RndRandom *s = RNG_RANDOM(obj);                                     // (4) 0.08654
/*12 */     if (b->opened) {                                                    // (7) 0.04808
/*14 */         error_set(errp, QERR_PERMISSION_DENIED);                        // (1) 0.1202
/*16 */         return;                                                         // (9) 0.04327
/*18 */     }                                                                   // (10) 0.01923
/*22 */     if (s->filename) {                                                  // (8) 0.04808
/*24 */         g_free(s->filename);                                            // (5) 0.07212
/*26 */     }                                                                   // (11) 0.01923
/*30 */     s->filename = g_strdup(filename);                                   // (6) 0.07212
/*32 */ }                                                                       // (13) 0.004808
