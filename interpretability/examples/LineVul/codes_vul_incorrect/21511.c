// commit message qemu@a01672d396 (target=1, prob=0.031662993, correct=False): kvm: convert to MemoryListener API
/*0  */ static int kvm_client_sync_dirty_bitmap(struct CPUPhysMemoryClient *client,  // (3) 0.1392
/*2  */                                         target_phys_addr_t start_addr,       // (0) 0.3165
/*4  */                                         target_phys_addr_t end_addr)         // (1) 0.3165
/*6  */ {                                                                            // (4) 0.006329
/*8  */     return kvm_physical_sync_dirty_bitmap(start_addr, end_addr);             // (2) 0.1519
/*10 */ }                                                                            // (5) 0.006329
