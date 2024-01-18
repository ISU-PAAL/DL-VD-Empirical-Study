// commit message qemu@8f68760561 (target=1, prob=0.3200458, correct=False): spapr_pci: drop useless check in spapr_phb_vfio_get_loc_code()
/*0  */ static char *spapr_phb_vfio_get_loc_code(sPAPRPHBState *sphb,  PCIDevice *pdev)  // (0) 0.1046
/*2  */ {                                                                                // (24) 0.002551
/*4  */     char *path = NULL, *buf = NULL, *host = NULL;                                // (6) 0.04847
/*8  */     /* Get the PCI VFIO host id */                                               // (9) 0.03316
/*10 */     host = object_property_get_str(OBJECT(pdev), "host", NULL);                  // (5) 0.06122
/*12 */     if (!host) {                                                                 // (17) 0.02041
/*14 */         goto err_out;                                                            // (11) 0.03061
/*16 */     }                                                                            // (21) 0.0102
/*20 */     /* Construct the path of the file that will give us the DT location */       // (7) 0.04592
/*22 */     path = g_strdup_printf("/sys/bus/pci/devices/%s/devspec", host);             // (1) 0.07908
/*24 */     g_free(host);                                                                // (13) 0.02296
/*26 */     if (!path || !g_file_get_contents(path, &buf, NULL, NULL)) {                 // (3) 0.06888
/*28 */         goto err_out;                                                            // (12) 0.03061
/*30 */     }                                                                            // (22) 0.0102
/*32 */     g_free(path);                                                                // (14) 0.02296
/*36 */     /* Construct and read from host device tree the loc-code */                  // (8) 0.04082
/*38 */     path = g_strdup_printf("/proc/device-tree%s/ibm,loc-code", buf);             // (2) 0.07908
/*40 */     g_free(buf);                                                                 // (15) 0.02296
/*42 */     if (!path || !g_file_get_contents(path, &buf, NULL, NULL)) {                 // (4) 0.06888
/*44 */         goto err_out;                                                            // (10) 0.03061
/*46 */     }                                                                            // (23) 0.0102
/*48 */     return buf;                                                                  // (18) 0.01531
/*52 */ err_out:                                                                         // (20) 0.0102
/*54 */     g_free(path);                                                                // (16) 0.02296
/*56 */     return NULL;                                                                 // (19) 0.01531
/*58 */ }                                                                                // (25) 0.002551
