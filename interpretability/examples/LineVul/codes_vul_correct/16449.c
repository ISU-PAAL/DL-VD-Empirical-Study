// commit message qemu@8786db7cb9 (target=1, prob=0.5420273, correct=True): memory: prepare AddressSpace for exporting
/*0  */ void set_system_memory_map(MemoryRegion *mr)  // (0) 0.2188
/*2  */ {                                             // (4) 0.01562
/*4  */     memory_region_transaction_begin();        // (2) 0.1875
/*6  */     address_space_memory.root = mr;           // (1) 0.2188
/*8  */     memory_region_transaction_commit();       // (3) 0.1875
/*10 */ }                                             // (5) 0.01562
