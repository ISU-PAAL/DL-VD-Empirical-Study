// commit message qemu@debaaa114a (target=0, prob=0.25988147, correct=True): qtest/ahci: Allow override of default CLI options
/*0  */ static void test_hba_enable(void)  // (4) 0.125
/*2  */ {                                  // (6) 0.01136
/*4  */     AHCIQState *ahci;              // (3) 0.125
/*8  */     ahci = ahci_boot();            // (5) 0.125
/*10 */     ahci_pci_enable(ahci);         // (1) 0.1591
/*12 */     ahci_hba_enable(ahci);         // (0) 0.1591
/*14 */     ahci_shutdown(ahci);           // (2) 0.1364
/*16 */ }                                  // (7) 0.01136
