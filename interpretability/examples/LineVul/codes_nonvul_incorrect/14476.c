// commit message qemu@a426e12217 (target=0, prob=0.96442544, correct=False): kvm: Fix coding style violations
/*0 */ static int kvm_client_migration_log(struct CPUPhysMemoryClient *client,  // (0) 0.3636
/*2 */ 				    int enable)                                                      // (2) 0.1818
/*4 */ {                                                                        // (3) 0.01818
/*6 */ 	return kvm_set_migration_log(enable);                                   // (1) 0.2545
/*8 */ }                                                                        // (4) 0.01818
