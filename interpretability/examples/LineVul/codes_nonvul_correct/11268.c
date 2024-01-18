// commit message qemu@fef6070eff (target=0, prob=0.49552733, correct=True): block: vpc - use block layer ops in vpc_create, instead of posix calls
/*0   */ static int create_dynamic_disk(int fd, uint8_t *buf, int64_t total_sectors)      // (5) 0.02503
/*2   */ {                                                                                // (29) 0.001448
/*4   */     VHDDynDiskHeader *dyndisk_header =                                           // (7) 0.01705
/*6   */         (VHDDynDiskHeader *) buf;                                                // (11) 0.008981
/*8   */     size_t block_size, num_bat_entries;                                          // (28) 0.001853
/*10  */     int i;                                                                       // (22) 0.002976
/*12  */     int ret = -EIO;                                                              // (4) 0.03799
/*16  */     // Write the footer (twice: at the beginning and at the end)                 // (0) 0.2688
/*18  */     block_size = 0x200000;                                                       // (8) 0.01698
/*20  */     num_bat_entries = (total_sectors + block_size / 512) / (block_size / 512);   // (20) 0.003776
/*24  */     if (write(fd, buf, HEADER_SIZE) != HEADER_SIZE) {                            // (21) 0.003049
/*26  */         goto fail;                                                               // (26) 0.002104
/*28  */     }                                                                            // (31) 0.0005388
/*32  */     if (lseek(fd, 1536 + ((num_bat_entries * 4 + 511) & ~511), SEEK_SET) < 0) {  // (17) 0.005133
/*34  */         goto fail;                                                               // (16) 0.005212
/*36  */     }                                                                            // (32) 0.0003524
/*38  */     if (write(fd, buf, HEADER_SIZE) != HEADER_SIZE) {                            // (24) 0.002642
/*40  */         goto fail;                                                               // (15) 0.006113
/*42  */     }                                                                            // (18) 0.004861
/*46  */     // Write the initial BAT                                                     // (2) 0.1357
/*48  */     if (lseek(fd, 3 * 512, SEEK_SET) < 0) {                                      // (10) 0.012
/*50  */         goto fail;                                                               // (13) 0.007134
/*52  */     }                                                                            // (30) 0.001346
/*56  */     memset(buf, 0xFF, 512);                                                      // (19) 0.004187
/*58  */     for (i = 0; i < (num_bat_entries * 4 + 511) / 512; i++) {                    // (25) 0.002336
/*60  */         if (write(fd, buf, 512) != 512) {                                        // (27) 0.00209
/*62  */             goto fail;                                                           // (12) 0.008429
/*64  */         }                                                                        // (23) 0.002794
/*66  */     }                                                                            // (3) 0.05807
/*70  */     // Prepare the Dynamic Disk Header                                           // (1) 0.1697
/*72  */     memset(buf, 0, 1024);                                                        // (6) 0.02346
/*76  */     memcpy(dyndisk_header->magic, "cxsparse", 8);                                // (9) 0.0136
/*80  */     /*                                                                           // (14) 0.006113
/*82  */      * Note: The spec is actually wrong here for data_offset, it says            // 0.0
/*84  */      * 0xFFFFFFFF, but MS tools expect all 64 bits to be set.                    // 0.0
/*86  */      */                                                                          // 0.0
/*88  */     dyndisk_header->data_offset = be64_to_cpu(0xFFFFFFFFFFFFFFFFULL);            // 0.0
/*90  */     dyndisk_header->table_offset = be64_to_cpu(3 * 512);                         // 0.0
/*92  */     dyndisk_header->version = be32_to_cpu(0x00010000);                           // 0.0
/*94  */     dyndisk_header->block_size = be32_to_cpu(block_size);                        // 0.0
/*96  */     dyndisk_header->max_table_entries = be32_to_cpu(num_bat_entries);            // 0.0
/*100 */     dyndisk_header->checksum = be32_to_cpu(vpc_checksum(buf, 1024));             // 0.0
/*104 */     // Write the header                                                          // 0.0
/*106 */     if (lseek(fd, 512, SEEK_SET) < 0) {                                          // 0.0
/*108 */         goto fail;                                                               // 0.0
/*110 */     }                                                                            // 0.0
/*114 */     if (write(fd, buf, 1024) != 1024) {                                          // 0.0
/*116 */         goto fail;                                                               // 0.0
/*118 */     }                                                                            // 0.0
/*120 */     ret = 0;                                                                     // 0.0
/*124 */  fail:                                                                           // 0.0
/*126 */     return ret;                                                                  // 0.0
/*128 */ }                                                                                // 0.0
