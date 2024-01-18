// commit message qemu@2886be1b01 (target=1, prob=0.5609646, correct=True): acpi: don't pass overflow_time to acpi_pm1_evt_get_sts
/*0  */ static void pm_ioport_read(IORange *ioport, uint64_t addr, unsigned width,        // (4) 0.06202
/*2  */                             uint64_t *data)                                       // (2) 0.08786
/*4  */ {                                                                                 // (23) 0.002584
/*6  */     PIIX4PMState *s = container_of(ioport, PIIX4PMState, ioport);                 // (3) 0.07752
/*8  */     uint32_t val;                                                                 // (9) 0.02326
/*12 */     switch(addr) {                                                                // (15) 0.02067
/*14 */     case 0x00:                                                                    // (16) 0.02067
/*16 */         val = acpi_pm1_evt_get_sts(&s->ar, s->ar.tmr.overflow_time);              // (1) 0.09819
/*18 */         break;                                                                    // (10) 0.02326
/*20 */     case 0x02:                                                                    // (17) 0.02067
/*22 */         val = s->ar.pm1.evt.en;                                                   // (7) 0.05426
/*24 */         break;                                                                    // (11) 0.02326
/*26 */     case 0x04:                                                                    // (18) 0.02067
/*28 */         val = s->ar.pm1.cnt.cnt;                                                  // (6) 0.05685
/*30 */         break;                                                                    // (12) 0.02326
/*32 */     case 0x08:                                                                    // (19) 0.02067
/*34 */         val = acpi_pm_tmr_get(&s->ar);                                            // (5) 0.05943
/*36 */         break;                                                                    // (13) 0.02326
/*38 */     default:                                                                      // (21) 0.01292
/*40 */         val = 0;                                                                  // (8) 0.02842
/*42 */         break;                                                                    // (14) 0.02326
/*44 */     }                                                                             // (22) 0.01034
/*46 */     PIIX4_DPRINTF("PM readw port=0x%04x val=0x%04x\n", (unsigned int)addr, val);  // (0) 0.1059
/*48 */     *data = val;                                                                  // (20) 0.02067
/*50 */ }                                                                                 // (24) 0.002584
