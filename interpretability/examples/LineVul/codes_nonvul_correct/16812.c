// commit message qemu@4a1418e07b (target=0, prob=0.06130196, correct=True): Unbreak large mem support by removing kqemu
/*0  */ void kqemu_modify_page(CPUState *env, ram_addr_t ram_addr)                   // (9) 0.04883
/*2  */ {                                                                            // (24) 0.001953
/*4  */     unsigned long page_index;                                                // (14) 0.01758
/*6  */     int ret;                                                                 // (18) 0.01172
/*8  */ #ifdef _WIN32                                                                // (16) 0.01172
/*10 */     DWORD temp;                                                              // (15) 0.01367
/*12 */ #endif                                                                       // (21) 0.003906
/*16 */     page_index = ram_addr >> TARGET_PAGE_BITS;                               // (11) 0.03906
/*18 */     if (!modified_ram_pages_table[page_index]) {                             // (12) 0.03516
/*20 */ #if 0                                                                        // (19) 0.005859
/*22 */         printf("%d: modify_page=%08lx\n", nb_modified_ram_pages, ram_addr);  // (5) 0.07031
/*24 */ #endif                                                                       // (23) 0.003906
/*26 */         modified_ram_pages_table[page_index] = 1;                            // (10) 0.04297
/*28 */         modified_ram_pages[nb_modified_ram_pages++] = ram_addr;              // (8) 0.05273
/*30 */         if (nb_modified_ram_pages >= KQEMU_MAX_MODIFIED_RAM_PAGES) {         // (6) 0.06445
/*32 */             /* flush */                                                      // (13) 0.02734
/*34 */ #ifdef _WIN32                                                                // (17) 0.01172
/*36 */             ret = DeviceIoControl(kqemu_fd, KQEMU_MODIFY_RAM_PAGES,          // (3) 0.07617
/*38 */                                   &nb_modified_ram_pages,                    // (2) 0.08203
/*40 */                                   sizeof(nb_modified_ram_pages),             // (0) 0.08398
/*42 */                                   NULL, 0, &temp, NULL);                     // (1) 0.08203
/*44 */ #else                                                                        // (22) 0.003906
/*46 */             ret = ioctl(kqemu_fd, KQEMU_MODIFY_RAM_PAGES,                    // (4) 0.07227
/*48 */                         &nb_modified_ram_pages);                             // (7) 0.0625
/*50 */ #endif                                                                       // (20) 0.003907
/*52 */             kqemu_reset_modified_ram_pages();                                // 0.0
/*54 */         }                                                                    // 0.0
/*56 */     }                                                                        // 0.0
/*58 */ }                                                                            // 0.0
