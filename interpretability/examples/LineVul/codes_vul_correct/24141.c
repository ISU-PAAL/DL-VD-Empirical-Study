// commit message qemu@afea4e1410 (target=1, prob=0.78078973, correct=True): megasas: remove unnecessary megasas_use_msi()
/*0  */ static void megasas_scsi_uninit(PCIDevice *d)      // (1) 0.1348
/*2  */ {                                                  // (8) 0.007092
/*4  */     MegasasState *s = MEGASAS(d);                  // (2) 0.1206
/*8  */     if (megasas_use_msix(s)) {                     // (3) 0.1206
/*10 */         msix_uninit(d, &s->mmio_io, &s->mmio_io);  // (0) 0.2199
/*12 */     }                                              // (6) 0.02837
/*14 */     if (megasas_use_msi(s)) {                      // (4) 0.1206
/*16 */         msi_uninit(d);                             // (5) 0.1064
/*18 */     }                                              // (7) 0.02837
/*20 */ }                                                  // (9) 0.007092
