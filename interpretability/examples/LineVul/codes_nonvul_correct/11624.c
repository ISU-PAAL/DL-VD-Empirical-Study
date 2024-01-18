// commit message qemu@89ae337acb (target=0, prob=0.10503279, correct=True): exec: move listener from AddressSpaceDispatch to AddressSpace
/*0  */ void address_space_destroy_dispatch(AddressSpace *as)  // (1) 0.1923
/*2  */ {                                                      // (5) 0.01282
/*4  */     AddressSpaceDispatch *d = as->dispatch;            // (2) 0.1795
/*8  */     memory_listener_unregister(&d->listener);          // (0) 0.2051
/*10 */     g_free(d);                                         // (4) 0.1154
/*12 */     as->dispatch = NULL;                               // (3) 0.1282
/*14 */ }                                                      // (6) 0.01282
