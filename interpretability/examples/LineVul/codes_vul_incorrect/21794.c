// commit message qemu@ab3ad07f89 (target=1, prob=0.33985606, correct=False): x86: Use g_new() & friends where that makes obvious sense
/*0  */ static void kvm_hwpoison_page_add(ram_addr_t ram_addr)   // (2) 0.1264
/*2  */ {                                                        // (10) 0.005747
/*4  */     HWPoisonPage *page;                                  // (7) 0.05747
/*8  */     QLIST_FOREACH(page, &hwpoison_page_list, list) {     // (0) 0.1322
/*10 */         if (page->ram_addr == ram_addr) {                // (3) 0.1149
/*12 */             return;                                      // (5) 0.07471
/*14 */         }                                                // (8) 0.04598
/*16 */     }                                                    // (9) 0.02299
/*18 */     page = g_malloc(sizeof(HWPoisonPage));               // (4) 0.1092
/*20 */     page->ram_addr = ram_addr;                           // (6) 0.07471
/*22 */     QLIST_INSERT_HEAD(&hwpoison_page_list, page, list);  // (1) 0.1322
/*24 */ }                                                        // (11) 0.005747
