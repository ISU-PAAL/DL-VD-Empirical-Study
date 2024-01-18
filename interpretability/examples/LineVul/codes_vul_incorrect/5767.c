// commit message qemu@f8ed85ac99 (target=1, prob=0.22497852, correct=False): Fix bad error handling after memory_region_init_ram()
/*0   */ static void qxl_realize_common(PCIQXLDevice *qxl, Error **errp)                 // (0) 0.05273
/*2   */ {                                                                               // (27) 0.001953
/*4   */     uint8_t* config = qxl->pci.config;                                          // (11) 0.03711
/*6   */     uint32_t pci_device_rev;                                                    // (16) 0.02539
/*8   */     uint32_t io_size;                                                           // (22) 0.02148
/*12  */     qxl->mode = QXL_MODE_UNDEFINED;                                             // (12) 0.03711
/*14  */     qxl->generation = 1;                                                        // (23) 0.02148
/*16  */     qxl->num_memslots = NUM_MEMSLOTS;                                           // (8) 0.04102
/*18  */     qemu_mutex_init(&qxl->track_lock);                                          // (10) 0.03906
/*20  */     qemu_mutex_init(&qxl->async_lock);                                          // (9) 0.04102
/*22  */     qxl->current_async = QXL_UNDEFINED_IO;                                      // (6) 0.04297
/*24  */     qxl->guest_bug = 0;                                                         // (15) 0.02734
/*28  */     switch (qxl->revision) {                                                    // (17) 0.02539
/*30  */     case 1: /* spice 0.4 -- qxl-1 */                                            // (13) 0.03516
/*32  */         pci_device_rev = QXL_REVISION_STABLE_V04;                               // (1) 0.05078
/*34  */         io_size = 8;                                                            // (18) 0.02539
/*36  */         break;                                                                  // (24) 0.01758
/*38  */     case 2: /* spice 0.6 -- qxl-2 */                                            // (14) 0.03516
/*40  */         pci_device_rev = QXL_REVISION_STABLE_V06;                               // (2) 0.05078
/*42  */         io_size = 16;                                                           // (19) 0.02539
/*44  */         break;                                                                  // (25) 0.01758
/*46  */     case 3: /* qxl-3 */                                                         // (20) 0.02539
/*48  */         pci_device_rev = QXL_REVISION_STABLE_V10;                               // (3) 0.05078
/*50  */         io_size = 32; /* PCI region size must be pow2 */                        // (7) 0.04297
/*52  */         break;                                                                  // (26) 0.01758
/*54  */     case 4: /* qxl-4 */                                                         // (21) 0.02539
/*56  */         pci_device_rev = QXL_REVISION_STABLE_V12;                               // (4) 0.05078
/*58  */         io_size = pow2ceil(QXL_IO_RANGE_SIZE);                                  // (5) 0.05078
/*60  */         break;                                                                  // 0.0
/*62  */     default:                                                                    // 0.0
/*64  */         error_setg(errp, "Invalid revision %d for qxl device (max %d)",         // 0.0
/*66  */                    qxl->revision, QXL_DEFAULT_REVISION);                        // 0.0
/*68  */         return;                                                                 // 0.0
/*70  */     }                                                                           // 0.0
/*74  */     pci_set_byte(&config[PCI_REVISION_ID], pci_device_rev);                     // 0.0
/*76  */     pci_set_byte(&config[PCI_INTERRUPT_PIN], 1);                                // 0.0
/*80  */     qxl->rom_size = qxl_rom_size();                                             // 0.0
/*82  */     memory_region_init_ram(&qxl->rom_bar, OBJECT(qxl), "qxl.vrom",              // 0.0
/*84  */                            qxl->rom_size, &error_abort);                        // 0.0
/*86  */     vmstate_register_ram(&qxl->rom_bar, &qxl->pci.qdev);                        // 0.0
/*88  */     init_qxl_rom(qxl);                                                          // 0.0
/*90  */     init_qxl_ram(qxl);                                                          // 0.0
/*94  */     qxl->guest_surfaces.cmds = g_new0(QXLPHYSICAL, qxl->ssd.num_surfaces);      // 0.0
/*96  */     memory_region_init_ram(&qxl->vram_bar, OBJECT(qxl), "qxl.vram",             // 0.0
/*98  */                            qxl->vram_size, &error_abort);                       // 0.0
/*100 */     vmstate_register_ram(&qxl->vram_bar, &qxl->pci.qdev);                       // 0.0
/*102 */     memory_region_init_alias(&qxl->vram32_bar, OBJECT(qxl), "qxl.vram32",       // 0.0
/*104 */                              &qxl->vram_bar, 0, qxl->vram32_size);              // 0.0
/*108 */     memory_region_init_io(&qxl->io_bar, OBJECT(qxl), &qxl_io_ops, qxl,          // 0.0
/*110 */                           "qxl-ioports", io_size);                              // 0.0
/*112 */     if (qxl->id == 0) {                                                         // 0.0
/*114 */         vga_dirty_log_start(&qxl->vga);                                         // 0.0
/*116 */     }                                                                           // 0.0
/*118 */     memory_region_set_flush_coalesced(&qxl->io_bar);                            // 0.0
/*124 */     pci_register_bar(&qxl->pci, QXL_IO_RANGE_INDEX,                             // 0.0
/*126 */                      PCI_BASE_ADDRESS_SPACE_IO, &qxl->io_bar);                  // 0.0
/*130 */     pci_register_bar(&qxl->pci, QXL_ROM_RANGE_INDEX,                            // 0.0
/*132 */                      PCI_BASE_ADDRESS_SPACE_MEMORY, &qxl->rom_bar);             // 0.0
/*136 */     pci_register_bar(&qxl->pci, QXL_RAM_RANGE_INDEX,                            // 0.0
/*138 */                      PCI_BASE_ADDRESS_SPACE_MEMORY, &qxl->vga.vram);            // 0.0
/*142 */     pci_register_bar(&qxl->pci, QXL_VRAM_RANGE_INDEX,                           // 0.0
/*144 */                      PCI_BASE_ADDRESS_SPACE_MEMORY, &qxl->vram32_bar);          // 0.0
/*148 */     if (qxl->vram32_size < qxl->vram_size) {                                    // 0.0
/*150 */         /*                                                                      // 0.0
/*152 */          * Make the 64bit vram bar show up only in case it is                   // 0.0
/*154 */          * configured to be larger than the 32bit vram bar.                     // 0.0
/*156 */          */                                                                     // 0.0
/*158 */         pci_register_bar(&qxl->pci, QXL_VRAM64_RANGE_INDEX,                     // 0.0
/*160 */                          PCI_BASE_ADDRESS_SPACE_MEMORY |                        // 0.0
/*162 */                          PCI_BASE_ADDRESS_MEM_TYPE_64 |                         // 0.0
/*164 */                          PCI_BASE_ADDRESS_MEM_PREFETCH,                         // 0.0
/*166 */                          &qxl->vram_bar);                                       // 0.0
/*168 */     }                                                                           // 0.0
/*172 */     /* print pci bar details */                                                 // 0.0
/*174 */     dprint(qxl, 1, "ram/%s: %d MB [region 0]\n",                                // 0.0
/*176 */            qxl->id == 0 ? "pri" : "sec",                                        // 0.0
/*178 */            qxl->vga.vram_size / (1024*1024));                                   // 0.0
/*180 */     dprint(qxl, 1, "vram/32: %d MB [region 1]\n",                               // 0.0
/*182 */            qxl->vram32_size / (1024*1024));                                     // 0.0
/*184 */     dprint(qxl, 1, "vram/64: %d MB %s\n",                                       // 0.0
/*186 */            qxl->vram_size / (1024*1024),                                        // 0.0
/*188 */            qxl->vram32_size < qxl->vram_size ? "[region 4]" : "[unmapped]");    // 0.0
/*192 */     qxl->ssd.qxl.base.sif = &qxl_interface.base;                                // 0.0
/*194 */     if (qemu_spice_add_display_interface(&qxl->ssd.qxl, qxl->vga.con) != 0) {   // 0.0
/*196 */         error_setg(errp, "qxl interface %d.%d not supported by spice-server",   // 0.0
/*198 */                    SPICE_INTERFACE_QXL_MAJOR, SPICE_INTERFACE_QXL_MINOR);       // 0.0
/*200 */         return;                                                                 // 0.0
/*202 */     }                                                                           // 0.0
/*204 */     qemu_add_vm_change_state_handler(qxl_vm_change_state_handler, qxl);         // 0.0
/*208 */     qxl->update_irq = qemu_bh_new(qxl_update_irq_bh, qxl);                      // 0.0
/*210 */     qxl_reset_state(qxl);                                                       // 0.0
/*214 */     qxl->update_area_bh = qemu_bh_new(qxl_render_update_area_bh, qxl);          // 0.0
/*216 */     qxl->ssd.cursor_bh = qemu_bh_new(qemu_spice_cursor_refresh_bh, &qxl->ssd);  // 0.0
/*218 */ }                                                                               // 0.0
