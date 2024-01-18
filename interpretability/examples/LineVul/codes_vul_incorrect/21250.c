// commit message qemu@8be7e7e4c7 (target=1, prob=0.385404, correct=False): qemu-option: qemu_opts_create(): use error_set()
/*0  */ static int virtcon_parse(const char *devname)                              // (16) 0.02539
/*2  */ {                                                                          // (26) 0.001953
/*4  */     QemuOptsList *device = qemu_find_opts("device");                       // (6) 0.04492
/*6  */     static int index = 0;                                                  // (20) 0.01758
/*8  */     char label[32];                                                        // (21) 0.01562
/*10 */     QemuOpts *bus_opts, *dev_opts;                                         // (10) 0.03906
/*14 */     if (strcmp(devname, "none") == 0)                                      // (14) 0.0332
/*16 */         return 0;                                                          // (19) 0.01953
/*18 */     if (index == MAX_VIRTIO_CONSOLES) {                                    // (13) 0.03711
/*20 */         fprintf(stderr, "qemu: too many virtio consoles\n");               // (4) 0.05273
/*22 */         exit(1);                                                           // (18) 0.02148
/*24 */     }                                                                      // (24) 0.007812
/*28 */     bus_opts = qemu_opts_create(device, NULL, 0);                          // (7) 0.04492
/*30 */     if (arch_type == QEMU_ARCH_S390X) {                                    // (11) 0.03906
/*32 */         qemu_opt_set(bus_opts, "driver", "virtio-serial-s390");            // (1) 0.0625
/*34 */     } else {                                                               // (22) 0.01172
/*36 */         qemu_opt_set(bus_opts, "driver", "virtio-serial-pci");             // (2) 0.0625
/*38 */     }                                                                      // (23) 0.009766
/*42 */     dev_opts = qemu_opts_create(device, NULL, 0);                          // (8) 0.04492
/*44 */     qemu_opt_set(dev_opts, "driver", "virtconsole");                       // (9) 0.04492
/*48 */     snprintf(label, sizeof(label), "virtcon%d", index);                    // (12) 0.03906
/*50 */     virtcon_hds[index] = qemu_chr_new(label, devname, NULL);               // (3) 0.05469
/*52 */     if (!virtcon_hds[index]) {                                             // (15) 0.02734
/*54 */         fprintf(stderr, "qemu: could not open virtio console '%s': %s\n",  // (0) 0.06641
/*56 */                 devname, strerror(errno));                                 // (5) 0.04883
/*58 */         return -1;                                                         // (17) 0.02148
/*60 */     }                                                                      // (25) 0.007812
/*62 */     qemu_opt_set(dev_opts, "chardev", label);                              // 0.0
/*66 */     index++;                                                               // 0.0
/*68 */     return 0;                                                              // 0.0
/*70 */ }                                                                          // 0.0
