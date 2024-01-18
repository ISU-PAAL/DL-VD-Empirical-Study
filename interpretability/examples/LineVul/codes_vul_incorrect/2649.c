// commit message qemu@3a55fc0f24 (target=1, prob=0.44875324, correct=False): ivshmem: Receive shared memory synchronously in realize()
/*0   */ static void pci_ivshmem_realize(PCIDevice *dev, Error **errp)                                    // (8) 0.04492
/*2   */ {                                                                                                // (24) 0.001953
/*4   */     IVShmemState *s = IVSHMEM(dev);                                                              // (11) 0.0332
/*6   */     Error *err = NULL;                                                                           // (19) 0.01758
/*8   */     uint8_t *pci_conf;                                                                           // (15) 0.02539
/*10  */     uint8_t attr = PCI_BASE_ADDRESS_SPACE_MEMORY |                                               // (5) 0.05078
/*12  */         PCI_BASE_ADDRESS_MEM_PREFETCH;                                                           // (6) 0.04688
/*16  */     if (!!s->server_chr + !!s->shmobj + !!s->hostmem != 1) {                                     // (4) 0.05664
/*18  */         error_setg(errp,                                                                         // (14) 0.0293
/*20  */                    "You must specify either 'shm', 'chardev' or 'x-memdev'");                    // (0) 0.07617
/*22  */         return;                                                                                  // (20) 0.01758
/*24  */     }                                                                                            // (23) 0.007813
/*28  */     if (s->hostmem) {                                                                            // (17) 0.02148
/*30  */         MemoryRegion *mr;                                                                        // (16) 0.02344
/*34  */         if (s->sizearg) {                                                                        // (12) 0.0332
/*36  */             g_warning("size argument ignored with hostmem");                                     // (10) 0.04297
/*38  */         }                                                                                        // (21) 0.01562
/*42  */         mr = host_memory_backend_get_memory(s->hostmem, &error_abort);                           // (3) 0.0625
/*44  */         s->ivshmem_size = memory_region_size(mr);                                                // (9) 0.04492
/*46  */     } else if (s->sizearg == NULL) {                                                             // (13) 0.0332
/*48  */         s->ivshmem_size = 4 << 20; /* 4 MB default */                                            // (7) 0.04688
/*50  */     } else {                                                                                     // (22) 0.01172
/*52  */         char *end;                                                                               // (18) 0.02148
/*54  */         int64_t size = qemu_strtosz(s->sizearg, &end);                                           // (2) 0.0625
/*56  */         if (size < 0 || *end != '\0' || !is_power_of_2(size)) {                                  // (1) 0.06445
/*58  */             error_setg(errp, "Invalid size %s", s->sizearg);                                     // 0.0
/*60  */             return;                                                                              // 0.0
/*62  */         }                                                                                        // 0.0
/*64  */         s->ivshmem_size = size;                                                                  // 0.0
/*66  */     }                                                                                            // 0.0
/*70  */     /* IRQFD requires MSI */                                                                     // 0.0
/*72  */     if (ivshmem_has_feature(s, IVSHMEM_IOEVENTFD) &&                                             // 0.0
/*74  */         !ivshmem_has_feature(s, IVSHMEM_MSI)) {                                                  // 0.0
/*76  */         error_setg(errp, "ioeventfd/irqfd requires MSI");                                        // 0.0
/*78  */         return;                                                                                  // 0.0
/*80  */     }                                                                                            // 0.0
/*84  */     /* check that role is reasonable */                                                          // 0.0
/*86  */     if (s->role) {                                                                               // 0.0
/*88  */         if (strncmp(s->role, "peer", 5) == 0) {                                                  // 0.0
/*90  */             s->role_val = IVSHMEM_PEER;                                                          // 0.0
/*92  */         } else if (strncmp(s->role, "master", 7) == 0) {                                         // 0.0
/*94  */             s->role_val = IVSHMEM_MASTER;                                                        // 0.0
/*96  */         } else {                                                                                 // 0.0
/*98  */             error_setg(errp, "'role' must be 'peer' or 'master'");                               // 0.0
/*100 */             return;                                                                              // 0.0
/*102 */         }                                                                                        // 0.0
/*104 */     } else {                                                                                     // 0.0
/*106 */         s->role_val = IVSHMEM_MASTER; /* default */                                              // 0.0
/*108 */     }                                                                                            // 0.0
/*112 */     pci_conf = dev->config;                                                                      // 0.0
/*114 */     pci_conf[PCI_COMMAND] = PCI_COMMAND_IO | PCI_COMMAND_MEMORY;                                 // 0.0
/*118 */     /*                                                                                           // 0.0
/*120 */      * Note: we don't use INTx with IVSHMEM_MSI at all, so this is a                             // 0.0
/*122 */      * bald-faced lie then.  But it's a backwards compatible lie.                                // 0.0
/*124 */      */                                                                                          // 0.0
/*126 */     pci_config_set_interrupt_pin(pci_conf, 1);                                                   // 0.0
/*130 */     memory_region_init_io(&s->ivshmem_mmio, OBJECT(s), &ivshmem_mmio_ops, s,                     // 0.0
/*132 */                           "ivshmem-mmio", IVSHMEM_REG_BAR_SIZE);                                 // 0.0
/*136 */     /* region for registers*/                                                                    // 0.0
/*138 */     pci_register_bar(dev, 0, PCI_BASE_ADDRESS_SPACE_MEMORY,                                      // 0.0
/*140 */                      &s->ivshmem_mmio);                                                          // 0.0
/*144 */     memory_region_init(&s->bar, OBJECT(s), "ivshmem-bar2-container", s->ivshmem_size);           // 0.0
/*146 */     if (s->ivshmem_64bit) {                                                                      // 0.0
/*148 */         attr |= PCI_BASE_ADDRESS_MEM_TYPE_64;                                                    // 0.0
/*150 */     }                                                                                            // 0.0
/*154 */     if (s->hostmem != NULL) {                                                                    // 0.0
/*156 */         MemoryRegion *mr;                                                                        // 0.0
/*160 */         IVSHMEM_DPRINTF("using hostmem\n");                                                      // 0.0
/*164 */         mr = host_memory_backend_get_memory(MEMORY_BACKEND(s->hostmem),                          // 0.0
/*166 */                                             &error_abort);                                       // 0.0
/*168 */         vmstate_register_ram(mr, DEVICE(s));                                                     // 0.0
/*170 */         memory_region_add_subregion(&s->bar, 0, mr);                                             // 0.0
/*172 */         pci_register_bar(PCI_DEVICE(s), 2, attr, &s->bar);                                       // 0.0
/*174 */     } else if (s->server_chr != NULL) {                                                          // 0.0
/*176 */         /* FIXME do not rely on what chr drivers put into filename */                            // 0.0
/*178 */         if (strncmp(s->server_chr->filename, "unix:", 5)) {                                      // 0.0
/*180 */             error_setg(errp, "chardev is not a unix client socket");                             // 0.0
/*182 */             return;                                                                              // 0.0
/*184 */         }                                                                                        // 0.0
/*188 */         /* if we get a UNIX socket as the parameter we will talk                                 // 0.0
/*190 */          * to the ivshmem server to receive the memory region */                                 // 0.0
/*194 */         IVSHMEM_DPRINTF("using shared memory server (socket = %s)\n",                            // 0.0
/*196 */                         s->server_chr->filename);                                                // 0.0
/*200 */         if (ivshmem_setup_interrupts(s) < 0) {                                                   // 0.0
/*202 */             error_setg(errp, "failed to initialize interrupts");                                 // 0.0
/*204 */             return;                                                                              // 0.0
/*206 */         }                                                                                        // 0.0
/*210 */         /* we allocate enough space for 16 peers and grow as needed */                           // 0.0
/*212 */         resize_peers(s, 16);                                                                     // 0.0
/*214 */         s->vm_id = -1;                                                                           // 0.0
/*218 */         pci_register_bar(dev, 2, attr, &s->bar);                                                 // 0.0
/*222 */         qemu_chr_add_handlers(s->server_chr, ivshmem_can_receive,                                // 0.0
/*224 */                               ivshmem_check_version, NULL, s);                                   // 0.0
/*226 */     } else {                                                                                     // 0.0
/*228 */         /* just map the file immediately, we're not using a server */                            // 0.0
/*230 */         int fd;                                                                                  // 0.0
/*234 */         IVSHMEM_DPRINTF("using shm_open (shm object = %s)\n", s->shmobj);                        // 0.0
/*238 */         /* try opening with O_EXCL and if it succeeds zero the memory                            // 0.0
/*240 */          * by truncating to 0 */                                                                 // 0.0
/*242 */         if ((fd = shm_open(s->shmobj, O_CREAT|O_RDWR|O_EXCL,                                     // 0.0
/*244 */                         S_IRWXU|S_IRWXG|S_IRWXO)) > 0) {                                         // 0.0
/*246 */            /* truncate file to length PCI device's memory */                                     // 0.0
/*248 */             if (ftruncate(fd, s->ivshmem_size) != 0) {                                           // 0.0
/*250 */                 error_report("could not truncate shared file");                                  // 0.0
/*252 */             }                                                                                    // 0.0
/*256 */         } else if ((fd = shm_open(s->shmobj, O_CREAT|O_RDWR,                                     // 0.0
/*258 */                         S_IRWXU|S_IRWXG|S_IRWXO)) < 0) {                                         // 0.0
/*260 */             error_setg(errp, "could not open shared file");                                      // 0.0
/*262 */             return;                                                                              // 0.0
/*264 */         }                                                                                        // 0.0
/*268 */         if (check_shm_size(s, fd, errp) == -1) {                                                 // 0.0
/*270 */             return;                                                                              // 0.0
/*272 */         }                                                                                        // 0.0
/*276 */         create_shared_memory_BAR(s, fd, attr, &err);                                             // 0.0
/*278 */         if (err) {                                                                               // 0.0
/*280 */             error_propagate(errp, err);                                                          // 0.0
/*282 */             return;                                                                              // 0.0
/*284 */         }                                                                                        // 0.0
/*286 */     }                                                                                            // 0.0
/*290 */     fifo8_create(&s->incoming_fifo, sizeof(int64_t));                                            // 0.0
/*294 */     if (s->role_val == IVSHMEM_PEER) {                                                           // 0.0
/*296 */         error_setg(&s->migration_blocker,                                                        // 0.0
/*298 */                    "Migration is disabled when using feature 'peer mode' in device 'ivshmem'");  // 0.0
/*300 */         migrate_add_blocker(s->migration_blocker);                                               // 0.0
/*302 */     }                                                                                            // 0.0
/*304 */ }                                                                                                // 0.0
