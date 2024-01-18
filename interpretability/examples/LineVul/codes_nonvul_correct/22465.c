// commit message qemu@28213cb6a6 (target=0, prob=0.033616606, correct=True): acpi: make bios_linker_loader_add_checksum() API offset based
/*0  */ void bios_linker_loader_add_checksum(BIOSLinker *linker, const char *file_name,  // (4) 0.0597
/*2  */                                      void *start, unsigned size,                 // (1) 0.09168
/*4  */                                      uint8_t *checksum)                          // (0) 0.09382
/*6  */ {                                                                                // (19) 0.002132
/*8  */     BiosLinkerLoaderEntry entry;                                                 // (17) 0.02345
/*10 */     const BiosLinkerFileEntry *file = bios_linker_find_file(linker, file_name);  // (3) 0.06183
/*12 */     ptrdiff_t checksum_offset = (gchar *)checksum - file->blob->data;            // (6) 0.05544
/*14 */     ptrdiff_t start_offset = (gchar *)start - file->blob->data;                  // (8) 0.05117
/*18 */     assert(checksum_offset >= 0);                                                // (15) 0.02559
/*20 */     assert(start_offset >= 0);                                                   // (18) 0.02345
/*22 */     assert(checksum_offset + 1 <= file->blob->len);                              // (11) 0.04051
/*24 */     assert(start_offset + size <= file->blob->len);                              // (13) 0.03838
/*26 */     assert(*checksum == 0x0);                                                    // (16) 0.02559
/*30 */     memset(&entry, 0, sizeof entry);                                             // (14) 0.02772
/*32 */     strncpy(entry.cksum.file, file_name, sizeof entry.cksum.file - 1);           // (5) 0.0597
/*34 */     entry.command = cpu_to_le32(BIOS_LINKER_LOADER_COMMAND_ADD_CHECKSUM);        // (2) 0.07249
/*36 */     entry.cksum.offset = cpu_to_le32(checksum_offset);                           // (9) 0.04691
/*38 */     entry.cksum.start = cpu_to_le32(start_offset);                               // (10) 0.04478
/*40 */     entry.cksum.length = cpu_to_le32(size);                                      // (12) 0.04051
/*44 */     g_array_append_vals(linker->cmd_blob, &entry, sizeof entry);                 // (7) 0.0533
/*46 */ }                                                                                // (20) 0.002132
