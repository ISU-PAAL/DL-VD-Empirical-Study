// commit message qemu@1dbfd7892b (target=1, prob=0.00857609, correct=False): acpi: fix bios linker loadder COMMAND_ALLOCATE on bigendian host
/*0  */ void bios_linker_loader_alloc(GArray *linker,                             // (11) 0.03687
/*2  */                               const char *file,                           // (4) 0.07834
/*4  */                               uint32_t alloc_align,                       // (2) 0.08525
/*6  */                               bool alloc_fseg)                            // (3) 0.08295
/*8  */ {                                                                         // (15) 0.002304
/*10 */     BiosLinkerLoaderEntry entry;                                          // (14) 0.02535
/*14 */     assert(!(alloc_align & (alloc_align - 1)));                           // (10) 0.04378
/*18 */     memset(&entry, 0, sizeof entry);                                      // (13) 0.02995
/*20 */     strncpy(entry.alloc.file, file, sizeof entry.alloc.file - 1);         // (6) 0.0553
/*22 */     entry.command = cpu_to_le32(BIOS_LINKER_LOADER_COMMAND_ALLOCATE);     // (5) 0.07373
/*24 */     entry.alloc.align = cpu_to_le32(alloc_align);                         // (9) 0.04608
/*26 */     entry.alloc.zone = cpu_to_le32(alloc_fseg ?                           // (7) 0.05069
/*28 */                                     BIOS_LINKER_LOADER_ALLOC_ZONE_FSEG :  // (0) 0.1244
/*30 */                                     BIOS_LINKER_LOADER_ALLOC_ZONE_HIGH);  // (1) 0.1221
/*34 */     /* Alloc entries must come first, so prepend them */                  // (12) 0.03687
/*36 */     g_array_prepend_vals(linker, &entry, sizeof entry);                   // (8) 0.04839
/*38 */ }                                                                         // (16) 0.002304
