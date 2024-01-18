// commit message qemu@40c4ed3f95 (target=1, prob=0.085347146, correct=False): ide: Ignore reads during PIO in and writes during PIO out
/*0  */ void ide_data_writew(void *opaque, uint32_t addr, uint32_t val)  // (0) 0.1214
/*2  */ {                                                                // (13) 0.004854
/*4  */     IDEBus *bus = opaque;                                        // (9) 0.04854
/*6  */     IDEState *s = idebus_active_if(bus);                         // (2) 0.08252
/*8  */     uint8_t *p;                                                  // (10) 0.04854
/*12 */     /* PIO data access allowed only when DRQ bit is set */       // (3) 0.08252
/*14 */     if (!(s->status & DRQ_STAT))                                 // (5) 0.07282
/*16 */         return;                                                  // (11) 0.04369
/*20 */     p = s->data_ptr;                                             // (7) 0.0534
/*22 */     *(uint16_t *)p = le16_to_cpu(val);                           // (1) 0.1019
/*24 */     p += 2;                                                      // (12) 0.03398
/*26 */     s->data_ptr = p;                                             // (8) 0.0534
/*28 */     if (p >= s->data_end)                                        // (6) 0.06311
/*30 */         s->end_transfer_func(s);                                 // (4) 0.08252
/*32 */ }                                                                // (14) 0.004854
