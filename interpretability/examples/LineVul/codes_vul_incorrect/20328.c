// commit message qemu@79d5ca5617 (target=1, prob=0.00587853, correct=False): AIO deletion race fix
/*0  */ static AioHandler *find_aio_handler(int fd)    // (2) 0.1569
/*2  */ {                                              // (7) 0.009804
/*4  */     AioHandler *node;                          // (4) 0.08824
/*8  */     LIST_FOREACH(node, &aio_handlers, node) {  // (0) 0.1961
/*10 */         if (node->fd == fd)                    // (1) 0.1569
/*12 */             return node;                       // (3) 0.1373
/*14 */     }                                          // (6) 0.03922
/*18 */     return NULL;                               // (5) 0.05882
/*20 */ }                                              // (8) 0.009804
