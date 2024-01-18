// commit message qemu@af7e9e74c6 (target=1, prob=0.37018442, correct=False): openpic: fix coding style issues
/*0 */ static inline void IRQ_setbit(IRQ_queue_t *q, int n_IRQ)  // (0) 0.4068
/*2 */ {                                                         // (3) 0.01695
/*4 */     q->pending++;                                         // (2) 0.1356
/*6 */     set_bit(q->queue, n_IRQ);                             // (1) 0.2712
/*8 */ }                                                         // (4) 0.01695
