// commit message qemu@c641483fbe (target=1, prob=0.014762123, correct=False): ide: kill ide_dma_submit_check
/*0  */ static inline void ide_dma_submit_check(IDEState *s,  // (1) 0.2048
/*2  */           BlockDriverCompletionFunc *dma_cb)          // (0) 0.253
/*4  */ {                                                     // (5) 0.01205
/*6  */     if (s->bus->dma->aiocb)                           // (2) 0.1928
/*8  */ 	return;                                              // (4) 0.03614
/*10 */     dma_cb(s, -1);                                    // (3) 0.1566
/*12 */ }                                                     // (6) 0.01205
