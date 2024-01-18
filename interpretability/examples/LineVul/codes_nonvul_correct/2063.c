// commit message qemu@2aece63c8a (target=0, prob=0.4766759, correct=True): hostmem: detect host backend memory is being used properly
/*0  */ host_memory_backend_can_be_deleted(UserCreatable *uc, Error **errp)  // (1) 0.1984
/*2  */ {                                                                    // (8) 0.007937
/*4  */     MemoryRegion *mr;                                                // (5) 0.06349
/*8  */     mr = host_memory_backend_get_memory(MEMORY_BACKEND(uc), errp);   // (0) 0.2302
/*10 */     if (memory_region_is_mapped(mr)) {                               // (2) 0.1349
/*12 */         return false;                                                // (3) 0.07937
/*14 */     } else {                                                         // (6) 0.04762
/*16 */         return true;                                                 // (4) 0.07937
/*18 */     }                                                                // (7) 0.03175
/*20 */ }                                                                    // (9) 0.007937
