// commit message qemu@6e5d97d01d (target=1, prob=0.01830883, correct=False): Handle BH's queued by AIO completions in qemu_aio_flush()
/*0  */ void qemu_aio_flush(void)                                      // (4) 0.06704
/*2  */ {                                                              // (14) 0.005587
/*4  */     AioHandler *node;                                          // (7) 0.05028
/*6  */     int ret;                                                   // (10) 0.03352
/*10 */     do {                                                       // (11) 0.02793
/*12 */         ret = 0;                                               // (5) 0.06145
/*16 */ 	/*                                                            // (12) 0.01117
/*18 */ 	 * If there are pending emulated aio start them now so flush  // (3) 0.0838
/*20 */ 	 * will be able to return 1.                                  // (8) 0.05028
/*22 */ 	 */                                                           // (13) 0.01117
/*24 */         qemu_aio_wait();                                       // (2) 0.08939
/*28 */         LIST_FOREACH(node, &aio_handlers, node) {              // (1) 0.1341
/*30 */             ret |= node->io_flush(node->opaque);               // (0) 0.1397
/*32 */         }                                                      // (9) 0.04469
/*34 */     } while (ret > 0);                                         // (6) 0.05587
/*36 */ }                                                              // (15) 0.005587
