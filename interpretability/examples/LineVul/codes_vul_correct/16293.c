// commit message qemu@7c4228b477 (target=1, prob=0.99895597, correct=True): vfio: Destroy memory regions
/*0  */ static void vfio_unmap_bar(VFIODevice *vdev, int nr)                          // (3) 0.08791
/*2  */ {                                                                             // (13) 0.003663
/*4  */     VFIOBAR *bar = &vdev->bars[nr];                                           // (7) 0.0696
/*8  */     if (!bar->size) {                                                         // (9) 0.03663
/*10 */         return;                                                               // (10) 0.03297
/*12 */     }                                                                         // (11) 0.01465
/*16 */     vfio_bar_quirk_teardown(vdev, nr);                                        // (6) 0.08059
/*20 */     memory_region_del_subregion(&bar->mem, &bar->mmap_mem);                   // (4) 0.08791
/*22 */     munmap(bar->mmap, memory_region_size(&bar->mmap_mem));                    // (5) 0.08791
/*27 */     if (vdev->msix && vdev->msix->table_bar == nr) {                          // (2) 0.09158
/*29 */         memory_region_del_subregion(&bar->mem, &vdev->msix->mmap_mem);        // (1) 0.1172
/*31 */         munmap(vdev->msix->mmap, memory_region_size(&vdev->msix->mmap_mem));  // (0) 0.1319
/*34 */     }                                                                         // (12) 0.01465
/*38 */     memory_region_destroy(&bar->mem);                                         // (8) 0.04762
/*40 */ }                                                                             // (14) 0.003663
