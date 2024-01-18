// commit message qemu@196a778428 (target=1, prob=0.06970977, correct=False): spice: drop obsolete iothread locking
/*0   */ static void ioport_write(void *opaque, uint32_t addr, uint32_t val)                     // (4) 0.04886
/*2   */ {                                                                                       // (28) 0.001953
/*4   */     PCIQXLDevice *d = opaque;                                                           // (14) 0.02735
/*6   */     uint32_t io_port = addr - d->io_base;                                               // (9) 0.03711
/*10  */     switch (io_port) {                                                                  // (19) 0.01953
/*12  */     case QXL_IO_RESET:                                                                  // (18) 0.02344
/*14  */     case QXL_IO_SET_MODE:                                                               // (16) 0.02539
/*16  */     case QXL_IO_MEMSLOT_ADD:                                                            // (13) 0.03125
/*18  */     case QXL_IO_MEMSLOT_DEL:                                                            // (10) 0.0332
/*20  */     case QXL_IO_CREATE_PRIMARY:                                                         // (12) 0.03125
/*22  */         break;                                                                          // (21) 0.01758
/*24  */     default:                                                                            // (24) 0.009765
/*26  */         if (d->mode == QXL_MODE_NATIVE || d->mode == QXL_MODE_COMPAT)                   // (2) 0.0664
/*28  */             break;                                                                      // (17) 0.02539
/*30  */         dprint(d, 1, "%s: unexpected port 0x%x in vga mode\n", __FUNCTION__, io_port);  // (1) 0.07812
/*32  */         return;                                                                         // (23) 0.01758
/*34  */     }                                                                                   // (26) 0.007812
/*38  */     switch (io_port) {                                                                  // (20) 0.01953
/*40  */     case QXL_IO_UPDATE_AREA:                                                            // (15) 0.02734
/*42  */     {                                                                                   // (27) 0.007812
/*44  */         QXLRect update = d->ram->update_area;                                           // (7) 0.03906
/*46  */         qemu_mutex_unlock_iothread();                                                   // (6) 0.04101
/*48  */         d->ssd.worker->update_area(d->ssd.worker, d->ram->update_surface,               // (3) 0.06445
/*50  */                                    &update, NULL, 0, 0);                                // (0) 0.08398
/*52  */         qemu_mutex_lock_iothread();                                                     // (8) 0.03906
/*54  */         break;                                                                          // (22) 0.01758
/*56  */     }                                                                                   // (25) 0.007812
/*58  */     case QXL_IO_NOTIFY_CMD:                                                             // (11) 0.03125
/*60  */         d->ssd.worker->wakeup(d->ssd.worker);                                           // (5) 0.04687
/*62  */         break;                                                                          // 0.0
/*64  */     case QXL_IO_NOTIFY_CURSOR:                                                          // 0.0
/*66  */         d->ssd.worker->wakeup(d->ssd.worker);                                           // 0.0
/*68  */         break;                                                                          // 0.0
/*70  */     case QXL_IO_UPDATE_IRQ:                                                             // 0.0
/*72  */         qxl_set_irq(d);                                                                 // 0.0
/*74  */         break;                                                                          // 0.0
/*76  */     case QXL_IO_NOTIFY_OOM:                                                             // 0.0
/*78  */         if (!SPICE_RING_IS_EMPTY(&d->ram->release_ring)) {                              // 0.0
/*80  */             break;                                                                      // 0.0
/*82  */         }                                                                               // 0.0
/*84  */         pthread_yield();                                                                // 0.0
/*86  */         if (!SPICE_RING_IS_EMPTY(&d->ram->release_ring)) {                              // 0.0
/*88  */             break;                                                                      // 0.0
/*90  */         }                                                                               // 0.0
/*92  */         d->oom_running = 1;                                                             // 0.0
/*94  */         d->ssd.worker->oom(d->ssd.worker);                                              // 0.0
/*96  */         d->oom_running = 0;                                                             // 0.0
/*98  */         break;                                                                          // 0.0
/*100 */     case QXL_IO_SET_MODE:                                                               // 0.0
/*102 */         dprint(d, 1, "QXL_SET_MODE %d\n", val);                                         // 0.0
/*104 */         qxl_set_mode(d, val, 0);                                                        // 0.0
/*106 */         break;                                                                          // 0.0
/*108 */     case QXL_IO_LOG:                                                                    // 0.0
/*110 */         if (d->guestdebug) {                                                            // 0.0
/*112 */             fprintf(stderr, "qxl/guest: %s", d->ram->log_buf);                          // 0.0
/*114 */         }                                                                               // 0.0
/*116 */         break;                                                                          // 0.0
/*118 */     case QXL_IO_RESET:                                                                  // 0.0
/*120 */         dprint(d, 1, "QXL_IO_RESET\n");                                                 // 0.0
/*122 */         qxl_hard_reset(d, 0);                                                           // 0.0
/*124 */         break;                                                                          // 0.0
/*126 */     case QXL_IO_MEMSLOT_ADD:                                                            // 0.0
/*128 */         PANIC_ON(val >= NUM_MEMSLOTS);                                                  // 0.0
/*130 */         PANIC_ON(d->guest_slots[val].active);                                           // 0.0
/*132 */         d->guest_slots[val].slot = d->ram->mem_slot;                                    // 0.0
/*134 */         qxl_add_memslot(d, val, 0);                                                     // 0.0
/*136 */         break;                                                                          // 0.0
/*138 */     case QXL_IO_MEMSLOT_DEL:                                                            // 0.0
/*140 */         qxl_del_memslot(d, val);                                                        // 0.0
/*142 */         break;                                                                          // 0.0
/*144 */     case QXL_IO_CREATE_PRIMARY:                                                         // 0.0
/*146 */         PANIC_ON(val != 0);                                                             // 0.0
/*148 */         dprint(d, 1, "QXL_IO_CREATE_PRIMARY\n");                                        // 0.0
/*150 */         d->guest_primary.surface = d->ram->create_surface;                              // 0.0
/*152 */         qxl_create_guest_primary(d, 0);                                                 // 0.0
/*154 */         break;                                                                          // 0.0
/*156 */     case QXL_IO_DESTROY_PRIMARY:                                                        // 0.0
/*158 */         PANIC_ON(val != 0);                                                             // 0.0
/*160 */         dprint(d, 1, "QXL_IO_DESTROY_PRIMARY\n");                                       // 0.0
/*162 */         qxl_destroy_primary(d);                                                         // 0.0
/*164 */         break;                                                                          // 0.0
/*166 */     case QXL_IO_DESTROY_SURFACE_WAIT:                                                   // 0.0
/*168 */         d->ssd.worker->destroy_surface_wait(d->ssd.worker, val);                        // 0.0
/*170 */         break;                                                                          // 0.0
/*172 */     case QXL_IO_DESTROY_ALL_SURFACES:                                                   // 0.0
/*174 */         d->ssd.worker->destroy_surfaces(d->ssd.worker);                                 // 0.0
/*176 */         break;                                                                          // 0.0
/*178 */     default:                                                                            // 0.0
/*180 */         fprintf(stderr, "%s: ioport=0x%x, abort()\n", __FUNCTION__, io_port);           // 0.0
/*182 */         abort();                                                                        // 0.0
/*184 */     }                                                                                   // 0.0
/*186 */ }                                                                                       // 0.0
