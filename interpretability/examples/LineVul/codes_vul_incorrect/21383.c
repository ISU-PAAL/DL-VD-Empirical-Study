// commit message qemu@5efed5a172 (target=1, prob=0.17511466, correct=False): bios-tables-test: handle false-positive smbios signature matches
/*0  */ static void test_smbios_ep_address(test_data *data)     // (5) 0.07031
/*2  */ {                                                       // (15) 0.003906
/*4  */     uint32_t off;                                       // (11) 0.03516
/*8  */     /* find smbios entry point structure */             // (9) 0.04688
/*10 */     for (off = 0xf0000; off < 0x100000; off += 0x10) {  // (0) 0.09766
/*12 */         uint8_t sig[] = "_SM_";                         // (6) 0.07031
/*14 */         int i;                                          // (10) 0.03906
/*18 */         for (i = 0; i < sizeof sig - 1; ++i) {          // (1) 0.09375
/*20 */             sig[i] = readb(off + i);                    // (2) 0.08984
/*22 */         }                                               // (12) 0.03125
/*26 */         if (!memcmp(sig, "_SM_", sizeof sig)) {         // (3) 0.08984
/*28 */             break;                                      // (8) 0.05078
/*30 */         }                                               // (13) 0.03125
/*32 */     }                                                   // (14) 0.01562
/*36 */     g_assert_cmphex(off, <, 0x100000);                  // (4) 0.07422
/*38 */     data->smbios_ep_addr = off;                         // (7) 0.05859
/*40 */ }                                                       // (16) 0.003906
