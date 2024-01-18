// commit message qemu@3c3e88a814 (target=0, prob=0.021166923, correct=True): pc-dimm: get memory region from ->get_memory_region()
/*0  */ static void pc_dimm_get_size(Object *obj, Visitor *v, const char *name,  // (2) 0.1412
/*2  */                              void *opaque, Error **errp)                 // (0) 0.2147
/*4  */ {                                                                        // (8) 0.00565
/*6  */     int64_t value;                                                       // (6) 0.05085
/*8  */     MemoryRegion *mr;                                                    // (7) 0.0452
/*10 */     PCDIMMDevice *dimm = PC_DIMM(obj);                                   // (3) 0.1186
/*14 */     mr = host_memory_backend_get_memory(dimm->hostmem, errp);            // (1) 0.1469
/*16 */     value = memory_region_size(mr);                                      // (5) 0.07345
/*20 */     visit_type_int(v, name, &value, errp);                               // (4) 0.1073
/*22 */ }                                                                        // (9) 0.00565
