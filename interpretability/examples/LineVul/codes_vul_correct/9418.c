// commit message qemu@f65ed4c152 (target=1, prob=0.9990721, correct=True): KVM: Coalesced MMIO support
/*0  */ int kvm_init(int smp_cpus)                                                      // (14) 0.02539
/*1  */ {                                                                               // (33) 0.001953
/*2  */     KVMState *s;                                                                // (26) 0.01758
/*3  */     int ret;                                                                    // (28) 0.01172
/*4  */     int i;                                                                      // (29) 0.01172
/*5  */     if (smp_cpus > 1)                                                           // (15) 0.02539
/*6  */         return -EINVAL;                                                         // (17) 0.02539
/*7  */     s = qemu_mallocz(sizeof(KVMState));                                         // (6) 0.03906
/*8  */     if (s == NULL)                                                              // (27) 0.01758
/*9  */         return -ENOMEM;                                                         // (16) 0.02539
/*10 */     for (i = 0; i < ARRAY_SIZE(s->slots); i++)                                  // (3) 0.04492
/*11 */         s->slots[i].slot = i;                                                   // (9) 0.03516
/*12 */     s->vmfd = -1;                                                               // (21) 0.02148
/*13 */     s->fd = open("/dev/kvm", O_RDWR);                                           // (7) 0.03906
/*14 */     if (s->fd == -1) {                                                          // (18) 0.02539
/*15 */         fprintf(stderr, "Could not access KVM kernel module: %m\n");            // (0) 0.05469
/*16 */         ret = -errno;                                                           // (19) 0.02539
/*17 */         goto err;                                                               // (24) 0.01953
/*18 */     }                                                                           // (32) 0.007812
/*19 */     ret = kvm_ioctl(s, KVM_GET_API_VERSION, 0);                                 // (2) 0.04687
/*20 */     if (ret < KVM_API_VERSION) {                                                // (12) 0.0293
/*21 */             ret = -EINVAL;                                                      // (10) 0.03516
/*22 */         fprintf(stderr, "kvm version too old\n");                               // (5) 0.04492
/*23 */         goto err;                                                               // (25) 0.01953
/*24 */     }                                                                           // (31) 0.007812
/*25 */     if (ret > KVM_API_VERSION) {                                                // (11) 0.0293
/*26 */         ret = -EINVAL;                                                          // (13) 0.02734
/*27 */         fprintf(stderr, "kvm version not supported\n");                         // (4) 0.04492
/*28 */         goto err;                                                               // (23) 0.01953
/*29 */     }                                                                           // (30) 0.007813
/*30 */     s->vmfd = kvm_ioctl(s, KVM_CREATE_VM, 0);                                   // (1) 0.05078
/*31 */     if (s->vmfd < 0)                                                            // (20) 0.02344
/*32 */         goto err;                                                               // (22) 0.01953
/*33 */     /* initially, KVM allocated its own memory and we had to jump through       // (8) 0.03516
/*34 */      * hooks to make phys_ram_base point to this.  Modern versions of KVM       // 0.0
/*35 */      * just use a user allocated buffer so we can use phys_ram_base             // 0.0
/*36 */      * unmodified.  Make sure we have a sufficiently modern version of KVM.     // 0.0
/*37 */      */                                                                         // 0.0
/*38 */     ret = kvm_ioctl(s, KVM_CHECK_EXTENSION, KVM_CAP_USER_MEMORY);               // 0.0
/*39 */     if (ret <= 0) {                                                             // 0.0
/*40 */         if (ret == 0)                                                           // 0.0
/*41 */             ret = -EINVAL;                                                      // 0.0
/*42 */         fprintf(stderr, "kvm does not support KVM_CAP_USER_MEMORY\n");          // 0.0
/*43 */         goto err;                                                               // 0.0
/*44 */     }                                                                           // 0.0
/*45 */     /* There was a nasty bug in < kvm-80 that prevents memory slots from being  // 0.0
/*46 */      * destroyed properly.  Since we rely on this capability, refuse to work    // 0.0
/*47 */      * with any kernel without this capability. */                              // 0.0
/*48 */     ret = kvm_ioctl(s, KVM_CHECK_EXTENSION,                                     // 0.0
/*49 */                     KVM_CAP_DESTROY_MEMORY_REGION_WORKS);                       // 0.0
/*50 */     if (ret <= 0) {                                                             // 0.0
/*51 */         if (ret == 0)                                                           // 0.0
/*52 */             ret = -EINVAL;                                                      // 0.0
/*53 */         fprintf(stderr,                                                         // 0.0
/*54 */                 "KVM kernel module broken (DESTROY_MEMORY_REGION)\n"            // 0.0
/*55 */                 "Please upgrade to at least kvm-81.\n");                        // 0.0
/*56 */         goto err;                                                               // 0.0
/*57 */     }                                                                           // 0.0
/*58 */     ret = kvm_arch_init(s, smp_cpus);                                           // 0.0
/*59 */     if (ret < 0)                                                                // 0.0
/*60 */         goto err;                                                               // 0.0
/*61 */     kvm_state = s;                                                              // 0.0
/*62 */     return 0;                                                                   // 0.0
/*63 */ err:                                                                            // 0.0
/*64 */     if (s) {                                                                    // 0.0
/*65 */         if (s->vmfd != -1)                                                      // 0.0
/*66 */             close(s->vmfd);                                                     // 0.0
/*67 */         if (s->fd != -1)                                                        // 0.0
/*68 */             close(s->fd);                                                       // 0.0
/*69 */     }                                                                           // 0.0
/*70 */     qemu_free(s);                                                               // 0.0
/*71 */     return ret;                                                                 // 0.0
/*72 */ }                                                                               // 0.0
