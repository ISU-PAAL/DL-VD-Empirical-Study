// commit message qemu@e69a17f65e (target=0, prob=0.30524793, correct=True): openpic: use standard bitmap operations
/*0  */ static void openpic_save_IRQ_queue(QEMUFile* f, IRQQueue *q)  // (1) 0.1786
/*2  */ {                                                             // (7) 0.007143
/*4  */     unsigned int i;                                           // (5) 0.05
/*8  */     for (i = 0; i < BF_WIDTH(MAX_IRQ); i++)                   // (2) 0.1714
/*10 */         qemu_put_be32s(f, &q->queue[i]);                      // (0) 0.1857
/*14 */     qemu_put_sbe32s(f, &q->next);                             // (4) 0.15
/*16 */     qemu_put_sbe32s(f, &q->priority);                         // (3) 0.15
/*18 */ }                                                             // (6) 0.007143
