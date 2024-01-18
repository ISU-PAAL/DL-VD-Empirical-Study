// commit message qemu@7443b43758 (target=1, prob=0.009693991, correct=False): exec: move qemu_ram_addr_from_host_nofail to cputlb.c
/*0  */ ram_addr_t qemu_ram_addr_from_host_nofail(void *ptr)   // (0) 0.2016
/*2  */ {                                                      // (7) 0.008065
/*4  */     ram_addr_t ram_addr;                               // (3) 0.09677
/*8  */     if (qemu_ram_addr_from_host(ptr, &ram_addr)) {     // (1) 0.2016
/*10 */         fprintf(stderr, "Bad ram pointer %p\n", ptr);  // (2) 0.2016
/*12 */         abort();                                       // (4) 0.07258
/*14 */     }                                                  // (6) 0.03226
/*16 */     return ram_addr;                                   // (5) 0.06452
/*18 */ }                                                      // (8) 0.008065
