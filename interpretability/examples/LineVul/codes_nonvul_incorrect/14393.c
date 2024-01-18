// commit message qemu@a426e12217 (target=0, prob=0.78069055, correct=False): kvm: Fix coding style violations
/*0  */ int kvm_log_start(target_phys_addr_t phys_addr, ram_addr_t size)     // (2) 0.1503
/*2  */ {                                                                    // (4) 0.00578
/*4  */         return kvm_dirty_pages_log_change(phys_addr, size,           // (3) 0.1445
/*6  */                                           KVM_MEM_LOG_DIRTY_PAGES,   // (0) 0.3179
/*8  */                                           KVM_MEM_LOG_DIRTY_PAGES);  // (1) 0.3179
/*10 */ }                                                                    // (5) 0.00578
