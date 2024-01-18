// commit message qemu@b2dfd71c48 (target=0, prob=0.10677848, correct=True): memory: prepare for multiple bits in the dirty log mask
/*0  */ static void xen_log_start(MemoryListener *listener,                           // (4) 0.0979
/*2  */                           MemoryRegionSection *section)                       // (1) 0.2168
/*4  */ {                                                                             // (5) 0.006993
/*6  */     XenIOState *state = container_of(listener, XenIOState, memory_listener);  // (2) 0.1748
/*10 */     xen_sync_dirty_bitmap(state, section->offset_within_address_space,        // (3) 0.1678
/*12 */                           int128_get64(section->size));                       // (0) 0.2448
/*14 */ }                                                                             // (6) 0.006993
