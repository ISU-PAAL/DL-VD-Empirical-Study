// commit message qemu@89ae337acb (target=0, prob=0.011440709, correct=True): exec: move listener from AddressSpaceDispatch to AddressSpace
/*0  */ static void mem_begin(MemoryListener *listener)                                        // (2) 0.1765
/*2  */ {                                                                                      // (3) 0.01471
/*4  */     AddressSpaceDispatch *d = container_of(listener, AddressSpaceDispatch, listener);  // (0) 0.3235
/*8  */     d->phys_map.ptr = PHYS_MAP_NODE_NIL;                                               // (1) 0.3235
/*10 */ }                                                                                      // (4) 0.01471
