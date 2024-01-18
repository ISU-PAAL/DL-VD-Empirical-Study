// commit message qemu@7d489dcdf5 (target=0, prob=0.322034, correct=True): vfio: fix return type of pread
/*0   */ static void vfio_pci_load_rom(VFIOPCIDevice *vdev)                              // (6) 0.04688
/*2   */ {                                                                               // (23) 0.001953
/*4   */     struct vfio_region_info reg_info = {                                        // (15) 0.03125
/*6   */         .argsz = sizeof(reg_info),                                              // (13) 0.0332
/*8   */         .index = VFIO_PCI_ROM_REGION_INDEX                                      // (7) 0.04688
/*10  */     };                                                                          // (21) 0.007813
/*12  */     uint64_t size;                                                              // (18) 0.01758
/*14  */     off_t off = 0;                                                              // (17) 0.01953
/*16  */     size_t bytes;                                                               // (20) 0.01563
/*20  */     if (ioctl(vdev->vbasedev.fd, VFIO_DEVICE_GET_REGION_INFO, &reg_info)) {     // (1) 0.07227
/*22  */         error_report("vfio: Error getting ROM info: %m");                       // (9) 0.04492
/*24  */         return;                                                                 // (19) 0.01758
/*26  */     }                                                                           // (22) 0.007812
/*30  */     trace_vfio_pci_load_rom(vdev->vbasedev.name, (unsigned long)reg_info.size,  // (4) 0.06836
/*32  */                             (unsigned long)reg_info.offset,                     // (2) 0.07227
/*34  */                             (unsigned long)reg_info.flags);                     // (3) 0.07227
/*38  */     vdev->rom_size = size = reg_info.size;                                      // (11) 0.03516
/*40  */     vdev->rom_offset = reg_info.offset;                                         // (14) 0.03125
/*44  */     if (!vdev->rom_size) {                                                      // (16) 0.02539
/*46  */         vdev->rom_read_failed = true;                                           // (12) 0.03516
/*48  */         error_report("vfio-pci: Cannot read device rom at "                     // (8) 0.04687
/*50  */                     "%s", vdev->vbasedev.name);                                 // (5) 0.06055
/*52  */         error_printf("Device option ROM contents are probably invalid "         // (10) 0.03711
/*54  */                     "(check dmesg).\nSkip option ROM probe with rombar=0, "     // (0) 0.07617
/*56  */                     "or load from file with romfile=\n");                       // 0.0
/*58  */         return;                                                                 // 0.0
/*60  */     }                                                                           // 0.0
/*64  */     vdev->rom = g_malloc(size);                                                 // 0.0
/*66  */     memset(vdev->rom, 0xff, size);                                              // 0.0
/*70  */     while (size) {                                                              // 0.0
/*72  */         bytes = pread(vdev->vbasedev.fd, vdev->rom + off,                       // 0.0
/*74  */                       size, vdev->rom_offset + off);                            // 0.0
/*76  */         if (bytes == 0) {                                                       // 0.0
/*78  */             break;                                                              // 0.0
/*80  */         } else if (bytes > 0) {                                                 // 0.0
/*82  */             off += bytes;                                                       // 0.0
/*84  */             size -= bytes;                                                      // 0.0
/*86  */         } else {                                                                // 0.0
/*88  */             if (errno == EINTR || errno == EAGAIN) {                            // 0.0
/*90  */                 continue;                                                       // 0.0
/*92  */             }                                                                   // 0.0
/*94  */             error_report("vfio: Error reading device ROM: %m");                 // 0.0
/*96  */             break;                                                              // 0.0
/*98  */         }                                                                       // 0.0
/*100 */     }                                                                           // 0.0
/*102 */ }                                                                               // 0.0
