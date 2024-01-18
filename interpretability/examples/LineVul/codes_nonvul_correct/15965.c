// commit message qemu@af08a58f0c (target=0, prob=0.2503147, correct=True): hw/ppc/spapr: Implement h_set_dabr
/*0  */ static void hypercall_register_types(void)                                     // (16) 0.02148
/*2  */ {                                                                              // (23) 0.001953
/*4  */     /* hcall-pft */                                                            // (18) 0.01953
/*6  */     spapr_register_hypercall(H_ENTER, h_enter);                                // (13) 0.04102
/*8  */     spapr_register_hypercall(H_REMOVE, h_remove);                              // (11) 0.04297
/*10 */     spapr_register_hypercall(H_PROTECT, h_protect);                            // (10) 0.04297
/*12 */     spapr_register_hypercall(H_READ, h_read);                                  // (14) 0.03906
/*16 */     /* hcall-bulk */                                                           // (20) 0.01953
/*18 */     spapr_register_hypercall(H_BULK_REMOVE, h_bulk_remove);                    // (1) 0.05664
/*22 */     /* hcall-dabr */                                                           // (17) 0.02148
/*24 */     spapr_register_hypercall(H_SET_DABR, h_set_dabr);                          // (6) 0.05273
/*28 */     /* hcall-splpar */                                                         // (19) 0.01953
/*30 */     spapr_register_hypercall(H_REGISTER_VPA, h_register_vpa);                  // (5) 0.05273
/*32 */     spapr_register_hypercall(H_CEDE, h_cede);                                  // (9) 0.04492
/*36 */     /* processor register resource access h-calls */                           // (15) 0.02539
/*38 */     spapr_register_hypercall(H_SET_SPRG0, h_set_sprg0);                        // (4) 0.05469
/*40 */     spapr_register_hypercall(H_SET_MODE, h_set_mode);                          // (7) 0.04687
/*44 */     /* "debugger" hcalls (also used by SLOF). Note: We do -not- differenciate  // (0) 0.05664
/*46 */      * here between the "CI" and the "CACHE" variants, they will use whatever  // (8) 0.04687
/*48 */      * mapping attributes qemu is using. When using KVM, the kernel will       // (12) 0.04102
/*50 */      * enforce the attributes more strongly                                    // (21) 0.01953
/*52 */      */                                                                        // (22) 0.009766
/*54 */     spapr_register_hypercall(H_LOGICAL_CI_LOAD, h_logical_load);               // (3) 0.05469
/*56 */     spapr_register_hypercall(H_LOGICAL_CI_STORE, h_logical_store);             // (2) 0.05664
/*58 */     spapr_register_hypercall(H_LOGICAL_CACHE_LOAD, h_logical_load);            // 0.0
/*60 */     spapr_register_hypercall(H_LOGICAL_CACHE_STORE, h_logical_store);          // 0.0
/*62 */     spapr_register_hypercall(H_LOGICAL_ICBI, h_logical_icbi);                  // 0.0
/*64 */     spapr_register_hypercall(H_LOGICAL_DCBF, h_logical_dcbf);                  // 0.0
/*66 */     spapr_register_hypercall(KVMPPC_H_LOGICAL_MEMOP, h_logical_memop);         // 0.0
/*70 */     /* qemu/KVM-PPC specific hcalls */                                         // 0.0
/*72 */     spapr_register_hypercall(KVMPPC_H_RTAS, h_rtas);                           // 0.0
/*76 */     /* ibm,client-architecture-support support */                              // 0.0
/*78 */     spapr_register_hypercall(KVMPPC_H_CAS, h_client_architecture_support);     // 0.0
/*80 */ }                                                                              // 0.0
