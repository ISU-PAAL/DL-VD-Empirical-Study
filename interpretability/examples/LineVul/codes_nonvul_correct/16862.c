// commit message qemu@a8170e5e97 (target=0, prob=0.00682452, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void musicpal_lcd_write(void *opaque, target_phys_addr_t offset,        // (8) 0.04688
/*2  */                                uint64_t value, unsigned size)                  // (0) 0.07617
/*4  */ {                                                                              // (24) 0.001953
/*6  */     musicpal_lcd_state *s = opaque;                                            // (11) 0.0293
/*10 */     switch (offset) {                                                          // (21) 0.01562
/*12 */     case MP_LCD_IRQCTRL:                                                       // (13) 0.02734
/*14 */         s->irqctrl = value;                                                    // (12) 0.0293
/*16 */         break;                                                                 // (19) 0.01758
/*20 */     case MP_LCD_SPICTRL:                                                       // (14) 0.02734
/*22 */         if (value == MP_LCD_SPI_DATA || value == MP_LCD_SPI_CMD) {             // (2) 0.06836
/*24 */             s->mode = value;                                                   // (10) 0.0332
/*26 */         } else {                                                               // (17) 0.01953
/*28 */             s->mode = MP_LCD_SPI_INVALID;                                      // (6) 0.05273
/*30 */         }                                                                      // (22) 0.01562
/*32 */         break;                                                                 // (18) 0.01758
/*36 */     case MP_LCD_INST:                                                          // (16) 0.02148
/*38 */         if (value >= MP_LCD_INST_SETPAGE0 && value <= MP_LCD_INST_SETPAGE7) {  // (1) 0.07422
/*40 */             s->page = value - MP_LCD_INST_SETPAGE0;                            // (4) 0.05664
/*42 */             s->page_off = 0;                                                   // (9) 0.03711
/*44 */         }                                                                      // (23) 0.01562
/*46 */         break;                                                                 // (20) 0.01758
/*50 */     case MP_LCD_DATA:                                                          // (15) 0.02148
/*52 */         if (s->mode == MP_LCD_SPI_CMD) {                                       // (7) 0.04883
/*54 */             if (value >= MP_LCD_INST_SETPAGE0 &&                               // (5) 0.05273
/*56 */                 value <= MP_LCD_INST_SETPAGE7) {                               // (3) 0.05859
/*58 */                 s->page = value - MP_LCD_INST_SETPAGE0;                        // 0.0
/*60 */                 s->page_off = 0;                                               // 0.0
/*62 */             }                                                                  // 0.0
/*64 */         } else if (s->mode == MP_LCD_SPI_DATA) {                               // 0.0
/*66 */             s->video_ram[s->page*128 + s->page_off] = value;                   // 0.0
/*68 */             s->page_off = (s->page_off + 1) & 127;                             // 0.0
/*70 */         }                                                                      // 0.0
/*72 */         break;                                                                 // 0.0
/*74 */     }                                                                          // 0.0
/*76 */ }                                                                              // 0.0
