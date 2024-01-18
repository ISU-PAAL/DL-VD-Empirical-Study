// commit message qemu@1a0e4c8b02 (target=1, prob=0.023481764, correct=False): s390x/kvm: fix small race reboot vs. cmma
/*0  */ void s390_machine_reset(void)                                          // (7) 0.06803
/*2  */ {                                                                      // (8) 0.006803
/*4  */     S390CPU *ipl_cpu = S390_CPU(qemu_get_cpu(0));                      // (0) 0.1769
/*8  */     qemu_devices_reset();                                              // (4) 0.07483
/*10 */     s390_cmma_reset();                                                 // (5) 0.07483
/*12 */     s390_crypto_reset();                                               // (6) 0.07483
/*16 */     /* all cpus are stopped - configure and start the ipl cpu only */  // (2) 0.1293
/*18 */     s390_ipl_prepare_cpu(ipl_cpu);                                     // (3) 0.1156
/*20 */     s390_cpu_set_state(CPU_STATE_OPERATING, ipl_cpu);                  // (1) 0.1633
/*22 */ }                                                                      // (9) 0.006803
