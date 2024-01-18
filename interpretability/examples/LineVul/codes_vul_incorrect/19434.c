// commit message qemu@82be8e7394 (target=1, prob=0.28857753, correct=False): ppc/kvm: change kvmppc_get_htab_fd() to return -errno on error
/*0  */ static int get_htab_fd(sPAPRMachineState *spapr)                               // (3) 0.1036
/*2  */ {                                                                              // (10) 0.005181
/*4  */     if (spapr->htab_fd >= 0) {                                                 // (4) 0.08808
/*6  */         return spapr->htab_fd;                                                 // (5) 0.08808
/*8  */     }                                                                          // (8) 0.02073
/*12 */     spapr->htab_fd = kvmppc_get_htab_fd(false);                                // (2) 0.1347
/*14 */     if (spapr->htab_fd < 0) {                                                  // (6) 0.08808
/*16 */         error_report("Unable to open fd for reading hash table from KVM: %s",  // (0) 0.1451
/*18 */                      strerror(errno));                                         // (1) 0.1399
/*20 */     }                                                                          // (9) 0.02073
/*24 */     return spapr->htab_fd;                                                     // (7) 0.06736
/*26 */ }                                                                              // (11) 0.005181
