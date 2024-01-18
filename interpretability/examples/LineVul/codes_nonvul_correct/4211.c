// commit message qemu@82ca891283 (target=0, prob=0.49918067, correct=True): vfio-pci: Add extra debugging
/*0  */ static void vfio_bar_write(void *opaque, hwaddr addr,                      // (8) 0.03906
/*2  */                            uint64_t data, unsigned size)                   // (2) 0.06836
/*4  */ {                                                                          // (30) 0.001953
/*6  */     VFIOBAR *bar = opaque;                                                 // (12) 0.02539
/*8  */     union {                                                                // (25) 0.009766
/*10 */         uint8_t byte;                                                      // (13) 0.02539
/*12 */         uint16_t word;                                                     // (14) 0.02539
/*14 */         uint32_t dword;                                                    // (10) 0.02734
/*16 */         uint64_t qword;                                                    // (11) 0.02734
/*18 */     } buf;                                                                 // (21) 0.01172
/*22 */     switch (size) {                                                        // (20) 0.01562
/*24 */     case 1:                                                                // (22) 0.01172
/*26 */         buf.byte = data;                                                   // (15) 0.02539
/*28 */         break;                                                             // (16) 0.01758
/*30 */     case 2:                                                                // (23) 0.01172
/*32 */         buf.word = cpu_to_le16(data);                                      // (9) 0.03906
/*34 */         break;                                                             // (17) 0.01758
/*36 */     case 4:                                                                // (24) 0.01172
/*38 */         buf.dword = cpu_to_le32(data);                                     // (7) 0.04102
/*40 */         break;                                                             // (18) 0.01758
/*42 */     default:                                                               // (26) 0.009766
/*44 */         hw_error("vfio: unsupported write size, %d bytes\n", size);        // (5) 0.05469
/*46 */         break;                                                             // (19) 0.01758
/*48 */     }                                                                      // (28) 0.007812
/*52 */     if (pwrite(bar->fd, &buf, size, bar->fd_offset + addr) != size) {      // (4) 0.05664
/*54 */         error_report("%s(,0x%"HWADDR_PRIx", 0x%"PRIx64", %d) failed: %m",  // (0) 0.08398
/*56 */                      __func__, addr, data, size);                          // (3) 0.05859
/*58 */     }                                                                      // (29) 0.007812
/*62 */     DPRINTF("%s(BAR%d+0x%"HWADDR_PRIx", 0x%"PRIx64", %d)\n",               // (1) 0.07812
/*64 */             __func__, bar->nr, addr, data, size);                          // (6) 0.04883
/*68 */     /*                                                                     // (27) 0.007813
/*70 */      * A read or write to a BAR always signals an INTx EOI.  This will     // 0.0
/*72 */      * do nothing if not pending (including not in INTx mode).  We assume  // 0.0
/*74 */      * that a BAR access is in response to an interrupt and that BAR       // 0.0
/*76 */      * accesses will service the interrupt.  Unfortunately, we don't know  // 0.0
/*78 */      * which access will service the interrupt, so we're potentially       // 0.0
/*80 */      * getting quite a few host interrupts per guest interrupt.            // 0.0
/*82 */      */                                                                    // 0.0
/*84 */     vfio_eoi(container_of(bar, VFIODevice, bars[bar->nr]));                // 0.0
/*86 */ }                                                                          // 0.0
