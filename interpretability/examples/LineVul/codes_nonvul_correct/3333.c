// commit message qemu@0ae18ceeaa (target=0, prob=0.19524142, correct=True): Check NIC model in some NIC init functions (Mark McLoughlin)
/*0   */ static void sun4d_hw_init(const struct sun4d_hwdef *hwdef, ram_addr_t RAM_size,  // (6) 0.06025
/*2   */                           const char *boot_device,                               // (5) 0.06205
/*4   */                           DisplayState *ds, const char *kernel_filename,         // (1) 0.07178
/*6   */                           const char *kernel_cmdline,                            // (4) 0.06397
/*8   */                           const char *initrd_filename, const char *cpu_model)    // (0) 0.07776
/*10  */ {                                                                                // (24) 0.001963
/*12  */     CPUState *env, *envs[MAX_CPUS];                                              // (13) 0.03302
/*14  */     unsigned int i;                                                              // (23) 0.0136
/*16  */     void *iounits[MAX_IOUNITS], *espdma, *ledma, *main_esp, *nvram, *sbi;        // (2) 0.07174
/*18  */     qemu_irq *cpu_irqs[MAX_CPUS], *sbi_irq, *sbi_cpu_irq,                        // (3) 0.06979
/*20  */         *espdma_irq, *ledma_irq;                                                 // (7) 0.04265
/*22  */     qemu_irq *esp_reset, *le_reset;                                              // (11) 0.03685
/*24  */     ram_addr_t ram_offset, prom_offset, tcx_offset;                              // (9) 0.04079
/*26  */     unsigned long kernel_size;                                                   // (16) 0.01758
/*28  */     int ret;                                                                     // (19) 0.01677
/*30  */     char buf[1024];                                                              // (21) 0.01568
/*32  */     int drive_index;                                                             // (20) 0.01592
/*34  */     void *fw_cfg;                                                                // (17) 0.01751
/*38  */     /* init CPUs */                                                              // (22) 0.01364
/*40  */     if (!cpu_model)                                                              // (18) 0.01748
/*42  */         cpu_model = hwdef->default_cpu_model;                                    // (8) 0.04081
/*46  */     for (i = 0; i < smp_cpus; i++) {                                             // (10) 0.0388
/*48  */         env = cpu_init(cpu_model);                                               // (12) 0.03308
/*50  */         if (!env) {                                                              // (15) 0.02329
/*52  */             fprintf(stderr, "qemu: Unable to find Sparc CPU definition\n");      // 0.0
/*54  */             exit(1);                                                             // 0.0
/*56  */         }                                                                        // 0.0
/*58  */         cpu_sparc_set_id(env, i);                                                // 0.0
/*60  */         envs[i] = env;                                                           // 0.0
/*62  */         if (i == 0) {                                                            // 0.0
/*64  */             qemu_register_reset(main_cpu_reset, env);                            // 0.0
/*66  */         } else {                                                                 // 0.0
/*68  */             qemu_register_reset(secondary_cpu_reset, env);                       // 0.0
/*70  */             env->halted = 1;                                                     // 0.0
/*72  */         }                                                                        // 0.0
/*74  */         cpu_irqs[i] = qemu_allocate_irqs(cpu_set_irq, envs[i], MAX_PILS);        // 0.0
/*76  */         env->prom_addr = hwdef->slavio_base;                                     // 0.0
/*78  */     }                                                                            // 0.0
/*82  */     for (i = smp_cpus; i < MAX_CPUS; i++)                                        // 0.0
/*84  */         cpu_irqs[i] = qemu_allocate_irqs(dummy_cpu_set_irq, NULL, MAX_PILS);     // 0.0
/*88  */     /* allocate RAM */                                                           // 0.0
/*90  */     if ((uint64_t)RAM_size > hwdef->max_mem) {                                   // 0.0
/*92  */         fprintf(stderr,                                                          // (14) 0.02716
/*94  */                 "qemu: Too much memory for this machine: %d, maximum %d\n",      // 0.0
/*96  */                 (unsigned int)(RAM_size / (1024 * 1024)),                        // 0.0
/*98  */                 (unsigned int)(hwdef->max_mem / (1024 * 1024)));                 // 0.0
/*100 */         exit(1);                                                                 // 0.0
/*102 */     }                                                                            // 0.0
/*104 */     ram_offset = qemu_ram_alloc(RAM_size);                                       // 0.0
/*106 */     cpu_register_physical_memory(0, RAM_size, ram_offset);                       // 0.0
/*110 */     /* load boot prom */                                                         // 0.0
/*112 */     prom_offset = qemu_ram_alloc(PROM_SIZE_MAX);                                 // 0.0
/*114 */     cpu_register_physical_memory(hwdef->slavio_base,                             // 0.0
/*116 */                                  (PROM_SIZE_MAX + TARGET_PAGE_SIZE - 1) &        // 0.0
/*118 */                                  TARGET_PAGE_MASK,                               // 0.0
/*120 */                                  prom_offset | IO_MEM_ROM);                      // 0.0
/*124 */     if (bios_name == NULL)                                                       // 0.0
/*126 */         bios_name = PROM_FILENAME;                                               // 0.0
/*128 */     snprintf(buf, sizeof(buf), "%s/%s", bios_dir, bios_name);                    // 0.0
/*130 */     ret = load_elf(buf, hwdef->slavio_base - PROM_VADDR, NULL, NULL, NULL);      // 0.0
/*132 */     if (ret < 0 || ret > PROM_SIZE_MAX)                                          // 0.0
/*134 */         ret = load_image_targphys(buf, hwdef->slavio_base, PROM_SIZE_MAX);       // 0.0
/*136 */     if (ret < 0 || ret > PROM_SIZE_MAX) {                                        // 0.0
/*138 */         fprintf(stderr, "qemu: could not load prom '%s'\n",                      // 0.0
/*140 */                 buf);                                                            // 0.0
/*142 */         exit(1);                                                                 // 0.0
/*144 */     }                                                                            // 0.0
/*148 */     /* set up devices */                                                         // 0.0
/*150 */     sbi = sbi_init(hwdef->sbi_base, &sbi_irq, &sbi_cpu_irq, cpu_irqs);           // 0.0
/*154 */     for (i = 0; i < MAX_IOUNITS; i++)                                            // 0.0
/*156 */         if (hwdef->iounit_bases[i] != (target_phys_addr_t)-1)                    // 0.0
/*158 */             iounits[i] = iommu_init(hwdef->iounit_bases[i],                      // 0.0
/*160 */                                     hwdef->iounit_version,                       // 0.0
/*162 */                                     sbi_irq[hwdef->me_irq]);                     // 0.0
/*166 */     espdma = sparc32_dma_init(hwdef->espdma_base, sbi_irq[hwdef->esp_irq],       // 0.0
/*168 */                               iounits[0], &espdma_irq, &esp_reset);              // 0.0
/*172 */     ledma = sparc32_dma_init(hwdef->ledma_base, sbi_irq[hwdef->le_irq],          // 0.0
/*174 */                              iounits[0], &ledma_irq, &le_reset);                 // 0.0
/*178 */     if (graphic_depth != 8 && graphic_depth != 24) {                             // 0.0
/*180 */         fprintf(stderr, "qemu: Unsupported depth: %d\n", graphic_depth);         // 0.0
/*182 */         exit (1);                                                                // 0.0
/*184 */     }                                                                            // 0.0
/*186 */     tcx_offset = qemu_ram_alloc(hwdef->vram_size);                               // 0.0
/*188 */     tcx_init(ds, hwdef->tcx_base, phys_ram_base + tcx_offset, tcx_offset,        // 0.0
/*190 */              hwdef->vram_size, graphic_width, graphic_height, graphic_depth);    // 0.0
/*194 */     if (nd_table[0].model == NULL)                                               // 0.0
/*196 */         nd_table[0].model = "lance";                                             // 0.0
/*198 */     if (strcmp(nd_table[0].model, "lance") == 0) {                               // 0.0
/*200 */         lance_init(&nd_table[0], hwdef->le_base, ledma, *ledma_irq, le_reset);   // 0.0
/*202 */     } else if (strcmp(nd_table[0].model, "?") == 0) {                            // 0.0
/*204 */         fprintf(stderr, "qemu: Supported NICs: lance\n");                        // 0.0
/*206 */         exit (1);                                                                // 0.0
/*208 */     } else {                                                                     // 0.0
/*210 */         fprintf(stderr, "qemu: Unsupported NIC: %s\n", nd_table[0].model);       // 0.0
/*212 */         exit (1);                                                                // 0.0
/*214 */     }                                                                            // 0.0
/*218 */     nvram = m48t59_init(sbi_irq[0], hwdef->nvram_base, 0,                        // 0.0
/*220 */                         hwdef->nvram_size, 8);                                   // 0.0
/*224 */     slavio_timer_init_all(hwdef->counter_base, sbi_irq[hwdef->clock1_irq],       // 0.0
/*226 */                           sbi_cpu_irq, smp_cpus);                                // 0.0
/*230 */     slavio_serial_ms_kbd_init(hwdef->ms_kb_base, sbi_irq[hwdef->ms_kb_irq],      // 0.0
/*232 */                               nographic, ESCC_CLOCK, 1);                         // 0.0
/*234 */     // Slavio TTYA (base+4, Linux ttyS0) is the first Qemu serial device         // 0.0
/*236 */     // Slavio TTYB (base+0, Linux ttyS1) is the second Qemu serial device        // 0.0
/*238 */     escc_init(hwdef->serial_base, sbi_irq[hwdef->ser_irq], serial_hds[1],        // 0.0
/*240 */               serial_hds[0], ESCC_CLOCK, 1);                                     // 0.0
/*244 */     if (drive_get_max_bus(IF_SCSI) > 0) {                                        // 0.0
/*246 */         fprintf(stderr, "qemu: too many SCSI bus\n");                            // 0.0
/*248 */         exit(1);                                                                 // 0.0
/*250 */     }                                                                            // 0.0
/*254 */     main_esp = esp_init(hwdef->esp_base, 2,                                      // 0.0
/*256 */                         espdma_memory_read, espdma_memory_write,                 // 0.0
/*258 */                         espdma, *espdma_irq, esp_reset);                         // 0.0
/*262 */     for (i = 0; i < ESP_MAX_DEVS; i++) {                                         // 0.0
/*264 */         drive_index = drive_get_index(IF_SCSI, 0, i);                            // 0.0
/*266 */         if (drive_index == -1)                                                   // 0.0
/*268 */             continue;                                                            // 0.0
/*270 */         esp_scsi_attach(main_esp, drives_table[drive_index].bdrv, i);            // 0.0
/*272 */     }                                                                            // 0.0
/*276 */     kernel_size = sun4m_load_kernel(kernel_filename, initrd_filename,            // 0.0
/*278 */                                     RAM_size);                                   // 0.0
/*282 */     nvram_init(nvram, (uint8_t *)&nd_table[0].macaddr, kernel_cmdline,           // 0.0
/*284 */                boot_device, RAM_size, kernel_size, graphic_width,                // 0.0
/*286 */                graphic_height, graphic_depth, hwdef->nvram_machine_id,           // 0.0
/*288 */                "Sun4d");                                                         // 0.0
/*292 */     fw_cfg = fw_cfg_init(0, 0, CFG_ADDR, CFG_ADDR + 2);                          // 0.0
/*294 */     fw_cfg_add_i32(fw_cfg, FW_CFG_ID, 1);                                        // 0.0
/*296 */     fw_cfg_add_i64(fw_cfg, FW_CFG_RAM_SIZE, (uint64_t)ram_size);                 // 0.0
/*298 */     fw_cfg_add_i16(fw_cfg, FW_CFG_MACHINE_ID, hwdef->machine_id);                // 0.0
/*300 */ }                                                                                // 0.0
