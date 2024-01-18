// commit message qemu@7c56045670 (target=0, prob=0.0078927465, correct=True):  Register only valid register access widths
/*0  */ static void slavio_led_mem_writes(void *opaque, target_phys_addr_t addr,         // (2) 0.1159
/*2  */                                   uint32_t val)                                  // (0) 0.1674
/*4  */ {                                                                                // (14) 0.004292
/*6  */     MiscState *s = opaque;                                                       // (6) 0.04292
/*8  */     uint32_t saddr;                                                              // (7) 0.04292
/*12 */     saddr = addr & LED_MAXADDR;                                                  // (4) 0.06009
/*14 */     MISC_DPRINTF("Write diagnostic LED reg 0x" TARGET_FMT_plx " =  %x\n", addr,  // (1) 0.1545
/*16 */                  val);                                                           // (3) 0.07725
/*18 */     switch (saddr) {                                                             // (8) 0.03863
/*20 */     case 0:                                                                      // (11) 0.02575
/*22 */         s->leds = val;                                                           // (5) 0.06009
/*24 */         break;                                                                   // (9) 0.03863
/*26 */     default:                                                                     // (12) 0.02146
/*28 */         break;                                                                   // (10) 0.03863
/*30 */     }                                                                            // (13) 0.01717
/*32 */ }                                                                                // (15) 0.004292
