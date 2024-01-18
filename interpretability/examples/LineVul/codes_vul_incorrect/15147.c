// commit message qemu@3a3b8502e6 (target=1, prob=0.1306799, correct=False): spapr: Fix RTAS token numbers
/*0  */ void spapr_pci_rtas_init(void)                                               // (7) 0.05226
/*2  */ {                                                                            // (10) 0.003484
/*4  */     spapr_rtas_register("read-pci-config", rtas_read_pci_config);            // (4) 0.1045
/*6  */     spapr_rtas_register("write-pci-config", rtas_write_pci_config);          // (5) 0.1045
/*8  */     spapr_rtas_register("ibm,read-pci-config", rtas_ibm_read_pci_config);    // (1) 0.1254
/*10 */     spapr_rtas_register("ibm,write-pci-config", rtas_ibm_write_pci_config);  // (3) 0.1254
/*12 */     if (msi_supported) {                                                     // (8) 0.03833
/*14 */         spapr_rtas_register("ibm,query-interrupt-source-number",             // (6) 0.09756
/*16 */                             rtas_ibm_query_interrupt_source_number);         // (0) 0.1498
/*18 */         spapr_rtas_register("ibm,change-msi", rtas_ibm_change_msi);          // (2) 0.1254
/*20 */     }                                                                        // (9) 0.01394
/*22 */ }                                                                            // (11) 0.003484
