// commit message qemu@a8170e5e97 (target=0, prob=0.017861893, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ void *rom_ptr(target_phys_addr_t addr)      // (0) 0.1765
/*2  */ {                                           // (6) 0.01176
/*4  */     Rom *rom;                               // (5) 0.08235
/*8  */     rom = find_rom(addr);                   // (3) 0.1294
/*10 */     if (!rom || !rom->data)                 // (2) 0.1412
/*12 */         return NULL;                        // (4) 0.1176
/*14 */     return rom->data + (addr - rom->addr);  // (1) 0.1765
/*16 */ }                                           // (7) 0.01176
