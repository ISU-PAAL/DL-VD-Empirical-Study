// commit message FFmpeg@fbd6c97f9c (target=1, prob=0.74426216, correct=True): lavu: fix memory leaks by using a mutex instead of atomics
/*0  */ static BufferPoolEntry *get_pool(AVBufferPool *pool)                              // (3) 0.102
/*2  */ {                                                                                 // (9) 0.006803
/*4  */     BufferPoolEntry *cur = NULL, *last = NULL;                                    // (2) 0.1088
/*8  */     do {                                                                          // (8) 0.03401
/*10 */         FFSWAP(BufferPoolEntry*, cur, last);                                      // (1) 0.1361
/*12 */         cur = avpriv_atomic_ptr_cas((void * volatile *)&pool->pool, last, NULL);  // (0) 0.2109
/*14 */         if (!cur)                                                                 // (5) 0.07483
/*16 */             return NULL;                                                          // (4) 0.09524
/*18 */     } while (cur != last);                                                        // (6) 0.06803
/*22 */     return cur;                                                                   // (7) 0.04082
/*24 */ }                                                                                 // (10) 0.006803
