// commit message qemu@6f864e6ec8 (target=0, prob=0.5230468, correct=False): vfio-pci: Lazy PCI option ROM loading
/*0  */ static int vfio_load_rom(VFIODevice *vdev)                                    // (10) 0.03711
/*2  */ {                                                                             // (25) 0.001953
/*4  */     uint64_t size = vdev->rom_size;                                           // (12) 0.03125
/*6  */     char name[32];                                                            // (22) 0.01563
/*8  */     off_t off = 0, voff = vdev->rom_offset;                                   // (9) 0.03906
/*10 */     ssize_t bytes;                                                            // (20) 0.01758
/*12 */     void *ptr;                                                                // (23) 0.01367
/*16 */     /* If loading ROM from file, pci handles it */                            // (16) 0.02734
/*18 */     if (vdev->pdev.romfile || !vdev->pdev.rom_bar || !size) {                 // (4) 0.05664
/*20 */         return 0;                                                             // (19) 0.01953
/*22 */     }                                                                         // (24) 0.007812
/*26 */     DPRINTF("%s(%04x:%02x:%02x.%x)\n", __func__, vdev->host.domain,           // (0) 0.07422
/*28 */             vdev->host.bus, vdev->host.slot, vdev->host.function);            // (3) 0.0625
/*32 */     snprintf(name, sizeof(name), "vfio[%04x:%02x:%02x.%x].rom",               // (1) 0.06641
/*34 */              vdev->host.domain, vdev->host.bus, vdev->host.slot,              // (2) 0.06445
/*36 */              vdev->host.function);                                            // (11) 0.03711
/*38 */     memory_region_init_ram(&vdev->pdev.rom, OBJECT(vdev), name, size);        // (5) 0.05664
/*40 */     ptr = memory_region_get_ram_ptr(&vdev->pdev.rom);                         // (8) 0.04492
/*42 */     memset(ptr, 0xff, size);                                                  // (18) 0.02539
/*46 */     while (size) {                                                            // (21) 0.01563
/*48 */         bytes = pread(vdev->fd, ptr + off, size, voff + off);                 // (6) 0.05469
/*50 */         if (bytes == 0) {                                                     // (17) 0.02734
/*52 */             break; /* expect that we could get back less than the ROM BAR */  // (7) 0.05078
/*54 */         } else if (bytes > 0) {                                               // (13) 0.03125
/*56 */             off += bytes;                                                     // (15) 0.0293
/*58 */             size -= bytes;                                                    // (14) 0.0293
/*60 */         } else {                                                              // 0.0
/*62 */             if (errno == EINTR || errno == EAGAIN) {                          // 0.0
/*64 */                 continue;                                                     // 0.0
/*66 */             }                                                                 // 0.0
/*68 */             error_report("vfio: Error reading device ROM: %m");               // 0.0
/*70 */             memory_region_destroy(&vdev->pdev.rom);                           // 0.0
/*72 */             return -errno;                                                    // 0.0
/*74 */         }                                                                     // 0.0
/*76 */     }                                                                         // 0.0
/*80 */     pci_register_bar(&vdev->pdev, PCI_ROM_SLOT, 0, &vdev->pdev.rom);          // 0.0
/*82 */     vdev->pdev.has_rom = true;                                                // 0.0
/*84 */     return 0;                                                                 // 0.0
/*86 */ }                                                                             // 0.0
