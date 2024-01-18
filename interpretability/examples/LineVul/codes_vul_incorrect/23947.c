// commit message qemu@b7022d9ac6 (target=1, prob=0.07683516, correct=False): s390: Plug memory leak on s390_pci_generate_event() error path
/*0  */ static void s390_pci_generate_event(uint8_t cc, uint16_t pec, uint32_t fh,     // (1) 0.09821
/*2  */                                     uint32_t fid, uint64_t faddr, uint32_t e)  // (0) 0.1607
/*4  */ {                                                                              // (16) 0.002976
/*6  */     SeiContainer *sei_cont = g_malloc0(sizeof(SeiContainer));                  // (4) 0.07143
/*8  */     S390pciState *s = S390_PCI_HOST_BRIDGE(                                    // (5) 0.07143
/*10 */         object_resolve_path(TYPE_S390_PCI_HOST_BRIDGE, NULL));                 // (2) 0.09226
/*14 */     if (!s) {                                                                  // (14) 0.02381
/*16 */         return;                                                                // (13) 0.02679
/*18 */     }                                                                          // (15) 0.0119
/*22 */     sei_cont->fh = fh;                                                         // (7) 0.04167
/*24 */     sei_cont->fid = fid;                                                       // (9) 0.03869
/*26 */     sei_cont->cc = cc;                                                         // (11) 0.03571
/*28 */     sei_cont->pec = pec;                                                       // (10) 0.03869
/*30 */     sei_cont->faddr = faddr;                                                   // (8) 0.04167
/*32 */     sei_cont->e = e;                                                           // (12) 0.03571
/*36 */     QTAILQ_INSERT_TAIL(&s->pending_sei, sei_cont, link);                       // (3) 0.08333
/*38 */     css_generate_css_crws(0);                                                  // (6) 0.04762
/*40 */ }                                                                              // (17) 0.002976
