// commit message qemu@1a61a9ae61 (target=0, prob=0.51440895, correct=False): PPC: KVM: set has-idle in guest device tree
/*0  */ int kvmppc_get_hypercall(CPUPPCState *env, uint8_t *buf, int buf_len)  // (2) 0.07712
/*2  */ {                                                                      // (23) 0.002571
/*4  */     PowerPCCPU *cpu = ppc_env_get_cpu(env);                            // (4) 0.05398
/*6  */     CPUState *cs = CPU(cpu);                                           // (13) 0.03085
/*8  */     uint32_t *hc = (uint32_t*)buf;                                     // (5) 0.04884
/*12 */     struct kvm_ppc_pvinfo pvinfo;                                      // (6) 0.0437
/*16 */     if (kvm_check_extension(cs->kvm_state, KVM_CAP_PPC_GET_PVINFO) &&  // (1) 0.08997
/*18 */         !kvm_vm_ioctl(cs->kvm_state, KVM_PPC_GET_PVINFO, &pvinfo)) {   // (0) 0.1054
/*20 */         memcpy(buf, pvinfo.hcall, buf_len);                            // (3) 0.0617
/*24 */         return 0;                                                      // (17) 0.02571
/*26 */     }                                                                  // (21) 0.01028
/*30 */     /*                                                                 // (22) 0.01028
/*32 */      * Fallback to always fail hypercalls:                             // (9) 0.03599
/*34 */      *                                                                 // (20) 0.01285
/*36 */      *     li r3, -1                                                   // (7) 0.03856
/*38 */      *     nop                                                         // (14) 0.02828
/*40 */      *     nop                                                         // (15) 0.02828
/*42 */      *     nop                                                         // (16) 0.02828
/*44 */      */                                                                // (19) 0.01285
/*48 */     hc[0] = 0x3860ffff;                                                // (8) 0.03856
/*50 */     hc[1] = 0x60000000;                                                // (10) 0.03599
/*52 */     hc[2] = 0x60000000;                                                // (11) 0.03599
/*54 */     hc[3] = 0x60000000;                                                // (12) 0.03599
/*58 */     return 0;                                                          // (18) 0.01542
/*60 */ }                                                                      // (24) 0.002571
