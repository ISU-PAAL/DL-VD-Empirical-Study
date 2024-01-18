// commit message qemu@0479097859 (target=1, prob=0.035193525, correct=False): hw/ppc/spapr: Fix segfault when instantiating a 'pc-dimm' without 'memdev'
/*0  */ static void pc_dimm_get_size(Object *obj, Visitor *v, const char *name,  // (2) 0.1269
/*2  */                              void *opaque, Error **errp)                 // (0) 0.1929
/*4  */ {                                                                        // (9) 0.005076
/*6  */     uint64_t value;                                                      // (7) 0.04569
/*8  */     MemoryRegion *mr;                                                    // (8) 0.04061
/*10 */     PCDIMMDevice *dimm = PC_DIMM(obj);                                   // (3) 0.1066
/*12 */     PCDIMMDeviceClass *ddc = PC_DIMM_GET_CLASS(obj);                     // (1) 0.132
/*16 */     mr = ddc->get_memory_region(dimm);                                   // (5) 0.09137
/*18 */     value = memory_region_size(mr);                                      // (6) 0.06599
/*22 */     visit_type_uint64(v, name, &value, errp);                            // (4) 0.1015
/*24 */ }                                                                        // (10) 0.005076
