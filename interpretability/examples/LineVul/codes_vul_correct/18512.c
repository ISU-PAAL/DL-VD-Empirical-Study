// commit message qemu@e0cb42ae4b (target=1, prob=0.54325575, correct=True): xen: Switch uses of xc_map_foreign_{pages,bulk} to use libxenforeignmemory API.
/*0   */ static void xen_remap_bucket(MapCacheEntry *entry,                              // (11) 0.03125
/*2   */                              hwaddr size,                                       // (3) 0.06445
/*4   */                              hwaddr address_index)                              // (2) 0.06836
/*6   */ {                                                                               // (23) 0.001953
/*8   */     uint8_t *vaddr_base;                                                        // (16) 0.02539
/*10  */     xen_pfn_t *pfns;                                                            // (14) 0.02734
/*12  */     int *err;                                                                   // (19) 0.01367
/*14  */     unsigned int i;                                                             // (20) 0.01367
/*16  */     hwaddr nb_pfn = size >> XC_PAGE_SHIFT;                                      // (6) 0.04492
/*20  */     trace_xen_remap_bucket(address_index);                                      // (9) 0.03516
/*24  */     pfns = g_malloc0(nb_pfn * sizeof (xen_pfn_t));                              // (4) 0.05469
/*26  */     err = g_malloc0(nb_pfn * sizeof (int));                                     // (8) 0.03906
/*30  */     if (entry->vaddr_base != NULL) {                                            // (12) 0.0293
/*32  */         if (munmap(entry->vaddr_base, entry->size) != 0) {                      // (5) 0.05273
/*34  */             perror("unmap fails");                                              // (10) 0.03516
/*36  */             exit(-1);                                                           // (13) 0.0293
/*38  */         }                                                                       // (18) 0.01562
/*40  */     }                                                                           // (21) 0.007812
/*42  */     g_free(entry->valid_mapping);                                               // (15) 0.02734
/*44  */     entry->valid_mapping = NULL;                                                // (17) 0.02344
/*48  */     for (i = 0; i < nb_pfn; i++) {                                              // (7) 0.03906
/*50  */         pfns[i] = (address_index << (MCACHE_BUCKET_SHIFT-XC_PAGE_SHIFT)) + i;   // (0) 0.08398
/*52  */     }                                                                           // (22) 0.007812
/*56  */     vaddr_base = xc_map_foreign_bulk(xen_xc, xen_domid, PROT_READ|PROT_WRITE,   // (1) 0.07422
/*58  */                                      pfns, err, nb_pfn);                        // 0.0
/*60  */     if (vaddr_base == NULL) {                                                   // 0.0
/*62  */         perror("xc_map_foreign_bulk");                                          // 0.0
/*64  */         exit(-1);                                                               // 0.0
/*66  */     }                                                                           // 0.0
/*70  */     entry->vaddr_base = vaddr_base;                                             // 0.0
/*72  */     entry->paddr_index = address_index;                                         // 0.0
/*74  */     entry->size = size;                                                         // 0.0
/*76  */     entry->valid_mapping = (unsigned long *) g_malloc0(sizeof(unsigned long) *  // 0.0
/*78  */             BITS_TO_LONGS(size >> XC_PAGE_SHIFT));                              // 0.0
/*82  */     bitmap_zero(entry->valid_mapping, nb_pfn);                                  // 0.0
/*84  */     for (i = 0; i < nb_pfn; i++) {                                              // 0.0
/*86  */         if (!err[i]) {                                                          // 0.0
/*88  */             bitmap_set(entry->valid_mapping, i, 1);                             // 0.0
/*90  */         }                                                                       // 0.0
/*92  */     }                                                                           // 0.0
/*96  */     g_free(pfns);                                                               // 0.0
/*98  */     g_free(err);                                                                // 0.0
/*100 */ }                                                                               // 0.0
