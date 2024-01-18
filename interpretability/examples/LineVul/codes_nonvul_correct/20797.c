// commit message qemu@5d1abf2344 (target=0, prob=0.13096659, correct=True): s390x/pci: enforce zPCI state checking
/*0   */ int pcistb_service_call(S390CPU *cpu, uint8_t r1, uint8_t r3, uint64_t gaddr,  // (0) 0.07031
/*2   */                         uint8_t ar)                                            // (2) 0.05664
/*4   */ {                                                                              // (33) 0.001953
/*6   */     CPUS390XState *env = &cpu->env;                                            // (11) 0.03125
/*8   */     S390PCIBusDevice *pbdev;                                                   // (12) 0.02539
/*10  */     MemoryRegion *mr;                                                          // (22) 0.01563
/*12  */     int i;                                                                     // (25) 0.01172
/*14  */     uint32_t fh;                                                               // (16) 0.01953
/*16  */     uint8_t pcias;                                                             // (15) 0.01953
/*18  */     uint8_t len;                                                               // (20) 0.01758
/*20  */     uint8_t buffer[128];                                                       // (14) 0.02148
/*24  */     if (env->psw.mask & PSW_MASK_PSTATE) {                                     // (7) 0.04297
/*26  */         program_interrupt(env, PGM_PRIVILEGED, 6);                             // (3) 0.04883
/*28  */         return 0;                                                              // (17) 0.01953
/*30  */     }                                                                          // (31) 0.007812
/*34  */     fh = env->regs[r1] >> 32;                                                  // (10) 0.0332
/*36  */     pcias = (env->regs[r1] >> 16) & 0xf;                                       // (6) 0.04297
/*38  */     len = env->regs[r1] & 0xff;                                                // (9) 0.0332
/*42  */     if (pcias > 5) {                                                           // (13) 0.02344
/*44  */         DPRINTF("pcistb invalid space\n");                                     // (8) 0.03711
/*46  */         setcc(cpu, ZPCI_PCI_LS_ERR);                                           // (4) 0.04687
/*48  */         s390_set_status_code(env, r1, ZPCI_PCI_ST_INVAL_AS);                   // (1) 0.06836
/*50  */         return 0;                                                              // (18) 0.01953
/*52  */     }                                                                          // (30) 0.007812
/*56  */     switch (len) {                                                             // (23) 0.01562
/*58  */     case 16:                                                                   // (26) 0.01172
/*60  */     case 32:                                                                   // (27) 0.01172
/*62  */     case 64:                                                                   // (28) 0.01172
/*64  */     case 128:                                                                  // (24) 0.01172
/*66  */         break;                                                                 // (21) 0.01758
/*68  */     default:                                                                   // (29) 0.009766
/*70  */         program_interrupt(env, PGM_SPECIFICATION, 6);                          // (5) 0.04492
/*72  */         return 0;                                                              // (19) 0.01953
/*74  */     }                                                                          // (32) 0.007812
/*78  */     pbdev = s390_pci_find_dev_by_fh(fh);                                       // 0.0
/*80  */     if (!pbdev || !(pbdev->fh & FH_MASK_ENABLE)) {                             // 0.0
/*82  */         DPRINTF("pcistb no pci dev fh 0x%x\n", fh);                            // 0.0
/*84  */         setcc(cpu, ZPCI_PCI_LS_INVAL_HANDLE);                                  // 0.0
/*86  */         return 0;                                                              // 0.0
/*88  */     }                                                                          // 0.0
/*92  */     if (pbdev->lgstg_blocked) {                                                // 0.0
/*94  */         setcc(cpu, ZPCI_PCI_LS_ERR);                                           // 0.0
/*96  */         s390_set_status_code(env, r1, ZPCI_PCI_ST_BLOCKED);                    // 0.0
/*98  */         return 0;                                                              // 0.0
/*100 */     }                                                                          // 0.0
/*104 */     mr = pbdev->pdev->io_regions[pcias].memory;                                // 0.0
/*106 */     if (!memory_region_access_valid(mr, env->regs[r3], len, true)) {           // 0.0
/*108 */         program_interrupt(env, PGM_ADDRESSING, 6);                             // 0.0
/*110 */         return 0;                                                              // 0.0
/*112 */     }                                                                          // 0.0
/*116 */     if (s390_cpu_virt_mem_read(cpu, gaddr, ar, buffer, len)) {                 // 0.0
/*118 */         return 0;                                                              // 0.0
/*120 */     }                                                                          // 0.0
/*124 */     for (i = 0; i < len / 8; i++) {                                            // 0.0
/*126 */         memory_region_dispatch_write(mr, env->regs[r3] + i * 8,                // 0.0
/*128 */                                      ldq_p(buffer + i * 8), 8,                 // 0.0
/*130 */                                      MEMTXATTRS_UNSPECIFIED);                  // 0.0
/*132 */     }                                                                          // 0.0
/*136 */     setcc(cpu, ZPCI_PCI_LS_OK);                                                // 0.0
/*138 */     return 0;                                                                  // 0.0
/*140 */ }                                                                              // 0.0
