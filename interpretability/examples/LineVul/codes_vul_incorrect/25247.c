// commit message qemu@2d896b454a (target=1, prob=0.042876545, correct=False): Revert "hw/mips: MIPS Boston board support"
/*0  */ static void boston_lcd_event(void *opaque, int event)     // (2) 0.1452
/*2  */ {                                                         // (6) 0.008065
/*4  */     BostonState *s = opaque;                              // (4) 0.08065
/*6  */     if (event == CHR_EVENT_OPENED && !s->lcd_inited) {    // (1) 0.2097
/*8  */         qemu_chr_fe_printf(&s->lcd_display, "        ");  // (0) 0.2823
/*10 */         s->lcd_inited = true;                             // (3) 0.1371
/*12 */     }                                                     // (5) 0.03226
/*14 */ }                                                         // (7) 0.008065
