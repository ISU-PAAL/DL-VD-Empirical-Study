// commit message qemu@ad523590f6 (target=0, prob=0.0063980347, correct=True): memory: remove the last param in memory_region_iommu_replay()
/*0  */ void memory_region_iommu_replay_all(MemoryRegion *mr)     // (2) 0.2
/*2  */ {                                                         // (5) 0.01053
/*4  */     IOMMUNotifier *notifier;                              // (3) 0.1263
/*8  */     IOMMU_NOTIFIER_FOREACH(notifier, mr) {                // (1) 0.2211
/*10 */         memory_region_iommu_replay(mr, notifier, false);  // (0) 0.2632
/*12 */     }                                                     // (4) 0.04211
/*14 */ }                                                         // (6) 0.01053
