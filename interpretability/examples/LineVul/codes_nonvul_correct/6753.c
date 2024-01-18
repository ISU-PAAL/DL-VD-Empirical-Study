// commit message qemu@d5fee0bbe6 (target=0, prob=0.012274716, correct=True): target/ppc: Implement ISA V3.00 radix page fault handler
/*0  */ int ppc64_v3_handle_mmu_fault(PowerPCCPU *cpu, vaddr eaddr, int rwx,   // (2) 0.1561
/*2  */                               int mmu_idx)                             // (1) 0.1756
/*4  */ {                                                                      // (9) 0.004878
/*6  */     if (ppc64_radix_guest(cpu)) { /* Guest uses radix */               // (3) 0.1171
/*8  */         /* TODO - Unsupported */                                       // (5) 0.06829
/*10 */         error_report("Guest Radix Support Unimplemented");             // (4) 0.09756
/*12 */         exit(1);                                                       // (7) 0.05366
/*14 */     } else { /* Guest uses hash */                                     // (6) 0.05366
/*16 */         return ppc_hash64_handle_mmu_fault(cpu, eaddr, rwx, mmu_idx);  // (0) 0.1756
/*18 */     }                                                                  // (8) 0.01951
/*20 */ }                                                                      // (10) 0.004878
