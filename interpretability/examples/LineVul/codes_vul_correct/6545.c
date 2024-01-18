// commit message qemu@3f910692c2 (target=1, prob=0.5170097, correct=True): block/vhdx: check error return of bdrv_getlength()
/*0   */ static int vhdx_log_write(BlockDriverState *bs, BDRVVHDXState *s,             // (2) 0.05078
/*2   */                           void *data, uint32_t length, uint64_t offset)       // (0) 0.08008
/*4   */ {                                                                             // (31) 0.001953
/*6   */     int ret = 0;                                                              // (28) 0.01562
/*8   */     void *buffer = NULL;                                                      // (26) 0.01758
/*10  */     void *merged_sector = NULL;                                               // (21) 0.02344
/*12  */     void *data_tmp, *sector_write;                                            // (11) 0.02734
/*14  */     unsigned int i;                                                           // (29) 0.01367
/*16  */     int sector_offset;                                                        // (27) 0.01563
/*18  */     uint32_t desc_sectors, sectors, total_length;                             // (7) 0.03516
/*20  */     uint32_t sectors_written = 0;                                             // (16) 0.02539
/*22  */     uint32_t aligned_length;                                                  // (23) 0.02148
/*24  */     uint32_t leading_length = 0;                                              // (19) 0.02539
/*26  */     uint32_t trailing_length = 0;                                             // (20) 0.02539
/*28  */     uint32_t partial_sectors = 0;                                             // (14) 0.02734
/*30  */     uint32_t bytes_written = 0;                                               // (18) 0.02539
/*32  */     uint64_t file_offset;                                                     // (22) 0.02148
/*34  */     VHDXHeader *header;                                                       // (25) 0.01953
/*36  */     VHDXLogEntryHeader new_hdr;                                               // (13) 0.02734
/*38  */     VHDXLogDescriptor *new_desc = NULL;                                       // (9) 0.0332
/*40  */     VHDXLogDataSector *data_sector = NULL;                                    // (8) 0.0332
/*42  */     MSGUID new_guid = { 0 };                                                  // (17) 0.02539
/*46  */     header = s->headers[s->curr_header];                                      // (10) 0.03125
/*50  */     /* need to have offset read data, and be on 4096 byte boundary */         // (6) 0.03516
/*54  */     if (length > header->log_length) {                                        // (12) 0.02734
/*56  */         /* no log present.  we could create a log here instead of failing */  // (3) 0.04492
/*58  */         ret = -EINVAL;                                                        // (15) 0.02734
/*60  */         goto exit;                                                            // (24) 0.01953
/*62  */     }                                                                         // (30) 0.007813
/*66  */     if (guid_eq(header->log_guid, zero_guid)) {                               // (4) 0.04492
/*68  */         vhdx_guid_generate(&new_guid);                                        // (5) 0.04297
/*70  */         vhdx_update_headers(bs, s, false, &new_guid);                         // (1) 0.05273
/*72  */     } else {                                                                  // 0.0
/*74  */         /* currently, we require that the log be flushed after                // 0.0
/*76  */          * every write. */                                                    // 0.0
/*78  */         ret = -ENOTSUP;                                                       // 0.0
/*80  */         goto exit;                                                            // 0.0
/*82  */     }                                                                         // 0.0
/*86  */     /* 0 is an invalid sequence number, but may also represent the first      // 0.0
/*88  */      * log write (or a wrapped seq) */                                        // 0.0
/*90  */     if (s->log.sequence == 0) {                                               // 0.0
/*92  */         s->log.sequence = 1;                                                  // 0.0
/*94  */     }                                                                         // 0.0
/*98  */     sector_offset = offset % VHDX_LOG_SECTOR_SIZE;                            // 0.0
/*100 */     file_offset = (offset / VHDX_LOG_SECTOR_SIZE) * VHDX_LOG_SECTOR_SIZE;     // 0.0
/*104 */     aligned_length = length;                                                  // 0.0
/*108 */     /* add in the unaligned head and tail bytes */                            // 0.0
/*110 */     if (sector_offset) {                                                      // 0.0
/*112 */         leading_length = (VHDX_LOG_SECTOR_SIZE - sector_offset);              // 0.0
/*114 */         leading_length = leading_length > length ? length : leading_length;   // 0.0
/*116 */         aligned_length -= leading_length;                                     // 0.0
/*118 */         partial_sectors++;                                                    // 0.0
/*120 */     }                                                                         // 0.0
/*124 */     sectors = aligned_length / VHDX_LOG_SECTOR_SIZE;                          // 0.0
/*126 */     trailing_length = aligned_length - (sectors * VHDX_LOG_SECTOR_SIZE);      // 0.0
/*128 */     if (trailing_length) {                                                    // 0.0
/*130 */         partial_sectors++;                                                    // 0.0
/*132 */     }                                                                         // 0.0
/*136 */     sectors += partial_sectors;                                               // 0.0
/*140 */     /* sectors is now how many sectors the data itself takes, not             // 0.0
/*142 */      * including the header and descriptor metadata */                        // 0.0
/*146 */     new_hdr = (VHDXLogEntryHeader) {                                          // 0.0
/*148 */                 .signature           = VHDX_LOG_SIGNATURE,                    // 0.0
/*150 */                 .tail                = s->log.tail,                           // 0.0
/*152 */                 .sequence_number     = s->log.sequence,                       // 0.0
/*154 */                 .descriptor_count    = sectors,                               // 0.0
/*156 */                 .reserved            = 0,                                     // 0.0
/*158 */                 .flushed_file_offset = bdrv_getlength(bs->file->bs),          // 0.0
/*160 */                 .last_file_offset    = bdrv_getlength(bs->file->bs),          // 0.0
/*162 */               };                                                              // 0.0
/*166 */     new_hdr.log_guid = header->log_guid;                                      // 0.0
/*170 */     desc_sectors = vhdx_compute_desc_sectors(new_hdr.descriptor_count);       // 0.0
/*174 */     total_length = (desc_sectors + sectors) * VHDX_LOG_SECTOR_SIZE;           // 0.0
/*176 */     new_hdr.entry_length = total_length;                                      // 0.0
/*180 */     vhdx_log_entry_hdr_le_export(&new_hdr);                                   // 0.0
/*184 */     buffer = qemu_blockalign(bs, total_length);                               // 0.0
/*186 */     memcpy(buffer, &new_hdr, sizeof(new_hdr));                                // 0.0
/*190 */     new_desc = buffer + sizeof(new_hdr);                                      // 0.0
/*192 */     data_sector = buffer + (desc_sectors * VHDX_LOG_SECTOR_SIZE);             // 0.0
/*194 */     data_tmp = data;                                                          // 0.0
/*198 */     /* All log sectors are 4KB, so for any partial sectors we must            // 0.0
/*200 */      * merge the data with preexisting data from the final file               // 0.0
/*202 */      * destination */                                                         // 0.0
/*204 */     merged_sector = qemu_blockalign(bs, VHDX_LOG_SECTOR_SIZE);                // 0.0
/*208 */     for (i = 0; i < sectors; i++) {                                           // 0.0
/*210 */         new_desc->signature       = VHDX_LOG_DESC_SIGNATURE;                  // 0.0
/*212 */         new_desc->sequence_number = s->log.sequence;                          // 0.0
/*214 */         new_desc->file_offset     = file_offset;                              // 0.0
/*218 */         if (i == 0 && leading_length) {                                       // 0.0
/*220 */             /* partial sector at the front of the buffer */                   // 0.0
/*222 */             ret = bdrv_pread(bs->file, file_offset, merged_sector,            // 0.0
/*224 */                              VHDX_LOG_SECTOR_SIZE);                           // 0.0
/*226 */             if (ret < 0) {                                                    // 0.0
/*228 */                 goto exit;                                                    // 0.0
/*230 */             }                                                                 // 0.0
/*232 */             memcpy(merged_sector + sector_offset, data_tmp, leading_length);  // 0.0
/*234 */             bytes_written = leading_length;                                   // 0.0
/*236 */             sector_write = merged_sector;                                     // 0.0
/*238 */         } else if (i == sectors - 1 && trailing_length) {                     // 0.0
/*240 */             /* partial sector at the end of the buffer */                     // 0.0
/*242 */             ret = bdrv_pread(bs->file,                                        // 0.0
/*244 */                             file_offset,                                      // 0.0
/*246 */                             merged_sector + trailing_length,                  // 0.0
/*248 */                             VHDX_LOG_SECTOR_SIZE - trailing_length);          // 0.0
/*250 */             if (ret < 0) {                                                    // 0.0
/*252 */                 goto exit;                                                    // 0.0
/*254 */             }                                                                 // 0.0
/*256 */             memcpy(merged_sector, data_tmp, trailing_length);                 // 0.0
/*258 */             bytes_written = trailing_length;                                  // 0.0
/*260 */             sector_write = merged_sector;                                     // 0.0
/*262 */         } else {                                                              // 0.0
/*264 */             bytes_written = VHDX_LOG_SECTOR_SIZE;                             // 0.0
/*266 */             sector_write = data_tmp;                                          // 0.0
/*268 */         }                                                                     // 0.0
/*272 */         /* populate the raw sector data into the proper structures,           // 0.0
/*274 */          * as well as update the descriptor, and convert to proper            // 0.0
/*276 */          * endianness */                                                      // 0.0
/*278 */         vhdx_log_raw_to_le_sector(new_desc, data_sector, sector_write,        // 0.0
/*280 */                                   s->log.sequence);                           // 0.0
/*284 */         data_tmp += bytes_written;                                            // 0.0
/*286 */         data_sector++;                                                        // 0.0
/*288 */         new_desc++;                                                           // 0.0
/*290 */         file_offset += VHDX_LOG_SECTOR_SIZE;                                  // 0.0
/*292 */     }                                                                         // 0.0
/*296 */     /* checksum covers entire entry, from the log header through the          // 0.0
/*298 */      * last data sector */                                                    // 0.0
/*300 */     vhdx_update_checksum(buffer, total_length,                                // 0.0
/*302 */                          offsetof(VHDXLogEntryHeader, checksum));             // 0.0
/*306 */     /* now write to the log */                                                // 0.0
/*308 */     ret = vhdx_log_write_sectors(bs, &s->log, &sectors_written, buffer,       // 0.0
/*310 */                                  desc_sectors + sectors);                     // 0.0
/*312 */     if (ret < 0) {                                                            // 0.0
/*314 */         goto exit;                                                            // 0.0
/*316 */     }                                                                         // 0.0
/*320 */     if (sectors_written != desc_sectors + sectors) {                          // 0.0
/*322 */         /* instead of failing, we could flush the log here */                 // 0.0
/*324 */         ret = -EINVAL;                                                        // 0.0
/*326 */         goto exit;                                                            // 0.0
/*328 */     }                                                                         // 0.0
/*332 */     s->log.sequence++;                                                        // 0.0
/*334 */     /* write new tail */                                                      // 0.0
/*336 */     s->log.tail = s->log.write;                                               // 0.0
/*340 */ exit:                                                                         // 0.0
/*342 */     qemu_vfree(buffer);                                                       // 0.0
/*344 */     qemu_vfree(merged_sector);                                                // 0.0
/*346 */     return ret;                                                               // 0.0
/*348 */ }                                                                             // 0.0
