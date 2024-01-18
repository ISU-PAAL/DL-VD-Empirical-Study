// commit message qemu@ac58fe7b2c (target=1, prob=0.43366376, correct=False): macio: switch pmac_dma_write() over to new offset/len implementation
/*0   */ static void pmac_dma_write(BlockBackend *blk,                                   // (10) 0.0332
/*2   */                          int64_t sector_num, int nb_sectors,                    // (2) 0.07617
/*4   */                          void (*cb)(void *opaque, int ret), void *opaque)       // (1) 0.08008
/*6   */ {                                                                               // (23) 0.001953
/*8   */     DBDMA_io *io = opaque;                                                      // (16) 0.02539
/*10  */     MACIOIDEState *m = io->opaque;                                              // (15) 0.0293
/*12  */     IDEState *s = idebus_active_if(&m->bus);                                    // (7) 0.03711
/*14  */     dma_addr_t dma_addr, dma_len;                                               // (9) 0.03711
/*16  */     void *mem;                                                                  // (22) 0.01367
/*18  */     int nsector, remainder;                                                     // (20) 0.01758
/*20  */     int extra = 0;                                                              // (21) 0.01562
/*24  */     qemu_iovec_destroy(&io->iov);                                               // (11) 0.0332
/*26  */     qemu_iovec_init(&io->iov, io->len / MACIO_PAGE_SIZE + 1);                   // (4) 0.06055
/*30  */     if (io->remainder_len > 0) {                                                // (14) 0.03125
/*32  */         /* Return remainder of request */                                       // (17) 0.02539
/*34  */         int transfer = MIN(io->remainder_len, io->len);                         // (6) 0.04687
/*38  */         MACIO_DPRINTF("--- processing write remainder %x\n", transfer);         // (5) 0.05078
/*40  */         cpu_physical_memory_read(io->addr,                                      // (8) 0.03711
/*42  */                                  &io->remainder + (0x200 - transfer),           // (0) 0.08984
/*44  */                                  transfer);                                     // (3) 0.06641
/*48  */         io->remainder_len -= transfer;                                          // (13) 0.0332
/*50  */         io->len -= transfer;                                                    // (19) 0.02539
/*52  */         io->addr += transfer;                                                   // (18) 0.02539
/*56  */         s->io_buffer_index += transfer;                                         // (12) 0.0332
/*58  */         s->io_buffer_size -= transfer;                                          // 0.0
/*62  */         if (io->remainder_len != 0) {                                           // 0.0
/*64  */             /* Still waiting for remainder */                                   // 0.0
/*66  */             return;                                                             // 0.0
/*68  */         }                                                                       // 0.0
/*72  */         MACIO_DPRINTF("--> prepending bounce buffer with size 0x200\n");        // 0.0
/*76  */         /* Sector transfer complete - prepend to request */                     // 0.0
/*78  */         qemu_iovec_add(&io->iov, &io->remainder, 0x200);                        // 0.0
/*80  */         extra = 1;                                                              // 0.0
/*82  */     }                                                                           // 0.0
/*86  */     if (s->drive_kind == IDE_CD) {                                              // 0.0
/*88  */         sector_num = (int64_t)(s->lba << 2) + (s->io_buffer_index >> 9);        // 0.0
/*90  */     } else {                                                                    // 0.0
/*92  */         sector_num = ide_get_sector(s) + (s->io_buffer_index >> 9);             // 0.0
/*94  */     }                                                                           // 0.0
/*98  */     nsector = (io->len >> 9);                                                   // 0.0
/*100 */     remainder = io->len - (nsector << 9);                                       // 0.0
/*104 */     MACIO_DPRINTF("--- DMA write transfer - addr: %" HWADDR_PRIx " len: %x\n",  // 0.0
/*106 */                   io->addr, io->len);                                           // 0.0
/*108 */     MACIO_DPRINTF("xxx remainder: %x\n", remainder);                            // 0.0
/*110 */     MACIO_DPRINTF("xxx sector_num: %"PRIx64"   nsector: %x\n",                  // 0.0
/*112 */                   sector_num, nsector);                                         // 0.0
/*116 */     dma_addr = io->addr;                                                        // 0.0
/*118 */     dma_len = io->len;                                                          // 0.0
/*120 */     mem = dma_memory_map(&address_space_memory, dma_addr, &dma_len,             // 0.0
/*122 */                          DMA_DIRECTION_TO_DEVICE);                              // 0.0
/*126 */     if (!remainder) {                                                           // 0.0
/*128 */         MACIO_DPRINTF("--- DMA write aligned - addr: %" HWADDR_PRIx             // 0.0
/*130 */                       " len: %x\n", io->addr, io->len);                         // 0.0
/*132 */         qemu_iovec_add(&io->iov, mem, io->len);                                 // 0.0
/*134 */     } else {                                                                    // 0.0
/*136 */         /* Write up to last complete sector */                                  // 0.0
/*138 */         MACIO_DPRINTF("--- DMA write unaligned - addr: %" HWADDR_PRIx           // 0.0
/*140 */                       " len: %x\n", io->addr, (nsector << 9));                  // 0.0
/*142 */         qemu_iovec_add(&io->iov, mem, (nsector << 9));                          // 0.0
/*146 */         MACIO_DPRINTF("--- DMA write read    - bounce addr: %p "                // 0.0
/*148 */                       "remainder_len: %x\n", &io->remainder, remainder);        // 0.0
/*150 */         cpu_physical_memory_read(io->addr + (nsector << 9), &io->remainder,     // 0.0
/*152 */                                  remainder);                                    // 0.0
/*156 */         io->remainder_len = 0x200 - remainder;                                  // 0.0
/*160 */         MACIO_DPRINTF("xxx remainder_len: %x\n", io->remainder_len);            // 0.0
/*162 */     }                                                                           // 0.0
/*166 */     s->io_buffer_size -= ((nsector + extra) << 9);                              // 0.0
/*168 */     s->io_buffer_index += ((nsector + extra) << 9);                             // 0.0
/*172 */     io->len = 0;                                                                // 0.0
/*176 */     MACIO_DPRINTF("--- Block write transfer   - sector_num: %"PRIx64"  "        // 0.0
/*178 */                   "nsector: %x\n", sector_num, nsector + extra);                // 0.0
/*182 */     m->aiocb = blk_aio_writev(blk, sector_num, &io->iov, nsector + extra, cb,   // 0.0
/*184 */                               io);                                              // 0.0
/*186 */ }                                                                               // 0.0
