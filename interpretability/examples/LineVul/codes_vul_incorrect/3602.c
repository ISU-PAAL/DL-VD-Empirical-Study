// commit message qemu@f8ed85ac99 (target=1, prob=0.2992587, correct=False): Fix bad error handling after memory_region_init_ram()
/*0   */ static void pci_add_option_rom(PCIDevice *pdev, bool is_default_rom,                // (5) 0.04883
/*2   */                                Error **errp)                                        // (0) 0.06836
/*4   */ {                                                                                   // (30) 0.001953
/*6   */     int size;                                                                       // (29) 0.01172
/*8   */     char *path;                                                                     // (27) 0.01367
/*10  */     void *ptr;                                                                      // (28) 0.01367
/*12  */     char name[32];                                                                  // (23) 0.01563
/*14  */     const VMStateDescription *vmsd;                                                 // (16) 0.02344
/*18  */     if (!pdev->romfile)                                                             // (17) 0.02148
/*20  */         return;                                                                     // (21) 0.01758
/*22  */     if (strlen(pdev->romfile) == 0)                                                 // (10) 0.0332
/*24  */         return;                                                                     // (20) 0.01758
/*28  */     if (!pdev->rom_bar) {                                                           // (14) 0.02539
/*30  */         /*                                                                          // (24) 0.01562
/*32  */          * Load rom via fw_cfg instead of creating a rom bar,                       // (7) 0.04492
/*34  */          * for 0.11 compatibility.                                                  // (13) 0.0293
/*36  */          */                                                                         // (19) 0.01758
/*38  */         int class = pci_get_word(pdev->config + PCI_CLASS_DEVICE);                  // (3) 0.05469
/*42  */         /*                                                                          // (25) 0.01562
/*44  */          * Hot-plugged devices can't use the option ROM                             // (9) 0.03906
/*46  */          * if the rom bar is disabled.                                              // (12) 0.03125
/*48  */          */                                                                         // (22) 0.01758
/*50  */         if (DEVICE(pdev)->hotplugged) {                                             // (8) 0.04102
/*52  */             error_setg(errp, "Hot-plugged device without ROM bar"                   // (2) 0.05664
/*54  */                        " can't have an option ROM");                                // (1) 0.05859
/*56  */             return;                                                                 // (15) 0.02539
/*58  */         }                                                                           // (26) 0.01562
/*62  */         if (class == 0x0300) {                                                      // (11) 0.0332
/*64  */             rom_add_vga(pdev->romfile);                                             // (6) 0.04688
/*66  */         } else {                                                                    // (18) 0.01953
/*68  */             rom_add_option(pdev->romfile, -1);                                      // (4) 0.05078
/*70  */         }                                                                           // 0.0
/*72  */         return;                                                                     // 0.0
/*74  */     }                                                                               // 0.0
/*78  */     path = qemu_find_file(QEMU_FILE_TYPE_BIOS, pdev->romfile);                      // 0.0
/*80  */     if (path == NULL) {                                                             // 0.0
/*82  */         path = g_strdup(pdev->romfile);                                             // 0.0
/*84  */     }                                                                               // 0.0
/*88  */     size = get_image_size(path);                                                    // 0.0
/*90  */     if (size < 0) {                                                                 // 0.0
/*92  */         error_setg(errp, "failed to find romfile \"%s\"", pdev->romfile);           // 0.0
/*94  */         g_free(path);                                                               // 0.0
/*96  */         return;                                                                     // 0.0
/*98  */     } else if (size == 0) {                                                         // 0.0
/*100 */         error_setg(errp, "romfile \"%s\" is empty", pdev->romfile);                 // 0.0
/*102 */         g_free(path);                                                               // 0.0
/*104 */         return;                                                                     // 0.0
/*106 */     }                                                                               // 0.0
/*108 */     size = pow2ceil(size);                                                          // 0.0
/*112 */     vmsd = qdev_get_vmsd(DEVICE(pdev));                                             // 0.0
/*116 */     if (vmsd) {                                                                     // 0.0
/*118 */         snprintf(name, sizeof(name), "%s.rom", vmsd->name);                         // 0.0
/*120 */     } else {                                                                        // 0.0
/*122 */         snprintf(name, sizeof(name), "%s.rom", object_get_typename(OBJECT(pdev)));  // 0.0
/*124 */     }                                                                               // 0.0
/*126 */     pdev->has_rom = true;                                                           // 0.0
/*128 */     memory_region_init_ram(&pdev->rom, OBJECT(pdev), name, size, &error_abort);     // 0.0
/*130 */     vmstate_register_ram(&pdev->rom, &pdev->qdev);                                  // 0.0
/*132 */     ptr = memory_region_get_ram_ptr(&pdev->rom);                                    // 0.0
/*134 */     load_image(path, ptr);                                                          // 0.0
/*136 */     g_free(path);                                                                   // 0.0
/*140 */     if (is_default_rom) {                                                           // 0.0
/*142 */         /* Only the default rom images will be patched (if needed). */              // 0.0
/*144 */         pci_patch_ids(pdev, ptr, size);                                             // 0.0
/*146 */     }                                                                               // 0.0
/*150 */     pci_register_bar(pdev, PCI_ROM_SLOT, 0, &pdev->rom);                            // 0.0
/*152 */ }                                                                                   // 0.0
