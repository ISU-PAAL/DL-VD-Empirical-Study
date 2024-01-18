// commit message qemu@75f2749822 (target=0, prob=0.045885894, correct=True): pc: memhp: move nvdimm hotplug out of memory hotplug
/*0  */ void acpi_memory_unplug_cb(MemHotplugState *mem_st,          // (3) 0.1015
/*2  */                            DeviceState *dev, Error **errp)   // (0) 0.1827
/*4  */ {                                                            // (11) 0.005076
/*6  */     MemStatus *mdev;                                         // (7) 0.04569
/*10 */     mdev = acpi_memory_slot_status(mem_st, dev, errp);       // (2) 0.1218
/*12 */     if (!mdev) {                                             // (8) 0.04569
/*14 */         return;                                              // (9) 0.04569
/*16 */     }                                                        // (10) 0.0203
/*20 */     /* nvdimm device hot unplug is not supported yet. */     // (4) 0.08629
/*22 */     assert(!object_dynamic_cast(OBJECT(dev), TYPE_NVDIMM));  // (1) 0.1269
/*24 */     mdev->is_enabled = false;                                // (5) 0.06091
/*26 */     mdev->dimm = NULL;                                       // (6) 0.05584
/*28 */ }                                                            // (12) 0.005076
