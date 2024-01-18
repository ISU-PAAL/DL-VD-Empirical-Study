// commit message qemu@b7b5233ad7 (target=1, prob=0.9687464, correct=True): bsd-user/mmap.c: Don't try to override g_malloc/g_free
/*0  */ void *g_realloc(void *ptr, size_t size)        // (2) 0.09815
/*2  */ {                                              // (11) 0.006135
/*4  */     size_t old_size, copy;                     // (6) 0.07361
/*6  */     void *new_ptr;                             // (7) 0.05521
/*10 */     if (!ptr)                                  // (10) 0.04294
/*12 */         return g_malloc(size);                 // (3) 0.09201
/*14 */     old_size = *(size_t *)((char *)ptr - 16);  // (0) 0.129
/*16 */     copy = old_size < size ? old_size : size;  // (1) 0.1043
/*18 */     new_ptr = g_malloc(size);                  // (5) 0.08587
/*20 */     memcpy(new_ptr, ptr, copy);                // (4) 0.09201
/*22 */     g_free(ptr);                               // (8) 0.05521
/*24 */     return new_ptr;                            // (9) 0.04907
/*26 */ }                                              // (12) 0.006134
