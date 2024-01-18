// commit message FFmpeg@64e105e051 (target=0, prob=0.8869931, correct=False): Fix a potential endless loop (nb (1 * 3) / 2 == 1)
/*0  */ static void dyn_buf_write(void *opaque, UINT8 *buf, int buf_size)  // (1) 0.0531
/*2  */ {                                                                  // (28) 0.002212
/*4  */     DynBuffer *d = opaque;                                         // (22) 0.02212
/*6  */     int new_size, new_allocated_size;                              // (13) 0.03319
/*8  */     UINT8 *new_buffer;                                             // (19) 0.02434
/*10 */                                                                    // (24) 0.00885
/*12 */     /* reallocate buffer if needed */                              // (20) 0.02434
/*14 */     new_size = d->pos + buf_size;                                  // (11) 0.03319
/*16 */     new_allocated_size = d->allocated_size;                        // (8) 0.03761
/*18 */     while (new_size > new_allocated_size) {                        // (9) 0.03761
/*20 */         if (!new_allocated_size)                                   // (10) 0.0354
/*22 */             new_allocated_size = new_size;                         // (4) 0.04867
/*24 */         else                                                       // (23) 0.0177
/*26 */             new_allocated_size = (new_allocated_size * 3) / 2;     // (0) 0.06858
/*28 */     }                                                              // (25) 0.00885
/*30 */                                                                    // (26) 0.00885
/*32 */     if (new_allocated_size > d->allocated_size) {                  // (7) 0.04425
/*34 */         new_buffer = av_malloc(new_allocated_size);                // (3) 0.05088
/*36 */         if (!new_buffer)                                           // (16) 0.02876
/*38 */             return;                                                // (18) 0.02876
/*40 */         memcpy(new_buffer, d->buffer, d->size);                    // (2) 0.05088
/*42 */         av_free(d->buffer);                                        // (12) 0.03319
/*44 */         d->buffer = new_buffer;                                    // (14) 0.03319
/*46 */         d->allocated_size = new_allocated_size;                    // (6) 0.04646
/*48 */     }                                                              // (27) 0.00885
/*50 */     memcpy(d->buffer + d->pos, buf, buf_size);                     // (5) 0.04646
/*52 */     d->pos = new_size;                                             // (21) 0.02434
/*54 */     if (d->pos > d->size)                                          // (17) 0.02876
/*56 */         d->size = d->pos;                                          // (15) 0.03319
/*58 */ }                                                                  // (29) 0.002212
