// commit message qemu@3a21532626 (target=0, prob=0.2302612, correct=True): ehci: adaptive wakeup rate.
/*0   */ static void ehci_mem_writel(void *ptr, target_phys_addr_t addr, uint32_t val)    // (1) 0.05664
/*2   */ {                                                                                // (27) 0.001953
/*4   */     EHCIState *s = ptr;                                                          // (16) 0.02344
/*6   */     uint32_t *mmio = (uint32_t *)(&s->mmio[addr]);                               // (8) 0.05078
/*8   */     uint32_t old = *mmio;                                                        // (14) 0.02539
/*10  */     int i;                                                                       // (23) 0.01172
/*14  */     trace_usb_ehci_mmio_writel(addr, addr2str(addr), val);                       // (7) 0.05078
/*18  */     /* Only aligned reads are allowed on OHCI */                                 // (13) 0.02734
/*20  */     if (addr & 3) {                                                              // (17) 0.01953
/*22  */         fprintf(stderr, "usb-ehci: Mis-aligned write to addr 0x"                 // (2) 0.05664
/*24  */                 TARGET_FMT_plx "\n", addr);                                      // (4) 0.05469
/*26  */         return;                                                                  // (18) 0.01758
/*28  */     }                                                                            // (25) 0.007812
/*32  */     if (addr >= PORTSC && addr < PORTSC + 4 * NB_PORTS) {                        // (9) 0.04883
/*34  */         handle_port_status_write(s, (addr-PORTSC)/4, val);                       // (5) 0.05469
/*36  */         trace_usb_ehci_mmio_change(addr, addr2str(addr), *mmio, old);            // (0) 0.06445
/*38  */         return;                                                                  // (19) 0.01758
/*40  */     }                                                                            // (24) 0.007813
/*44  */     if (addr < OPREGBASE) {                                                      // (15) 0.02539
/*46  */         fprintf(stderr, "usb-ehci: write attempt to read-only register"          // (3) 0.05469
/*48  */                 TARGET_FMT_plx "\n", addr);                                      // (6) 0.05469
/*50  */         return;                                                                  // (20) 0.01758
/*52  */     }                                                                            // (26) 0.007812
/*58  */     /* Do any register specific pre-write processing here.  */                   // (12) 0.03125
/*60  */     switch(addr) {                                                               // (22) 0.01562
/*62  */     case USBCMD:                                                                 // (21) 0.01563
/*64  */         if (val & USBCMD_HCRESET) {                                              // (10) 0.03906
/*66  */             ehci_reset(s);                                                       // (11) 0.03516
/*68  */             val = s->usbcmd;                                                     // 0.0
/*70  */             break;                                                               // 0.0
/*72  */         }                                                                        // 0.0
/*76  */         if (((USBCMD_RUNSTOP | USBCMD_PSE | USBCMD_ASE) & val) !=                // 0.0
/*78  */             ((USBCMD_RUNSTOP | USBCMD_PSE | USBCMD_ASE) & s->usbcmd)) {          // 0.0
/*80  */             if (!ehci_enabled(s)) {                                              // 0.0
/*82  */                 qemu_mod_timer(s->frame_timer, qemu_get_clock_ns(vm_clock));     // 0.0
/*84  */                 SET_LAST_RUN_CLOCK(s);                                           // 0.0
/*86  */             }                                                                    // 0.0
/*88  */             ehci_update_halt(s);                                                 // 0.0
/*90  */         }                                                                        // 0.0
/*94  */         /* not supporting dynamic frame list size at the moment */               // 0.0
/*96  */         if ((val & USBCMD_FLS) && !(s->usbcmd & USBCMD_FLS)) {                   // 0.0
/*98  */             fprintf(stderr, "attempt to set frame list size -- value %d\n",      // 0.0
/*100 */                     val & USBCMD_FLS);                                           // 0.0
/*102 */             val &= ~USBCMD_FLS;                                                  // 0.0
/*104 */         }                                                                        // 0.0
/*106 */         break;                                                                   // 0.0
/*110 */     case USBSTS:                                                                 // 0.0
/*112 */         val &= USBSTS_RO_MASK;              // bits 6 through 31 are RO          // 0.0
/*114 */         ehci_clear_usbsts(s, val);          // bits 0 through 5 are R/WC         // 0.0
/*116 */         val = s->usbsts;                                                         // 0.0
/*118 */         ehci_set_interrupt(s, 0);                                                // 0.0
/*120 */         break;                                                                   // 0.0
/*124 */     case USBINTR:                                                                // 0.0
/*126 */         val &= USBINTR_MASK;                                                     // 0.0
/*128 */         break;                                                                   // 0.0
/*132 */     case FRINDEX:                                                                // 0.0
/*134 */         val &= 0x00003ff8; /* frindex is 14bits and always a multiple of 8 */    // 0.0
/*136 */         break;                                                                   // 0.0
/*140 */     case CONFIGFLAG:                                                             // 0.0
/*142 */         val &= 0x1;                                                              // 0.0
/*144 */         if (val) {                                                               // 0.0
/*146 */             for(i = 0; i < NB_PORTS; i++)                                        // 0.0
/*148 */                 handle_port_owner_write(s, i, 0);                                // 0.0
/*150 */         }                                                                        // 0.0
/*152 */         break;                                                                   // 0.0
/*156 */     case PERIODICLISTBASE:                                                       // 0.0
/*158 */         if (ehci_periodic_enabled(s)) {                                          // 0.0
/*160 */             fprintf(stderr,                                                      // 0.0
/*162 */               "ehci: PERIODIC list base register set while periodic schedule\n"  // 0.0
/*164 */               "      is enabled and HC is enabled\n");                           // 0.0
/*166 */         }                                                                        // 0.0
/*168 */         break;                                                                   // 0.0
/*172 */     case ASYNCLISTADDR:                                                          // 0.0
/*174 */         if (ehci_async_enabled(s)) {                                             // 0.0
/*176 */             fprintf(stderr,                                                      // 0.0
/*178 */               "ehci: ASYNC list address register set while async schedule\n"     // 0.0
/*180 */               "      is enabled and HC is enabled\n");                           // 0.0
/*182 */         }                                                                        // 0.0
/*184 */         break;                                                                   // 0.0
/*186 */     }                                                                            // 0.0
/*190 */     *mmio = val;                                                                 // 0.0
/*192 */     trace_usb_ehci_mmio_change(addr, addr2str(addr), *mmio, old);                // 0.0
/*194 */ }                                                                                // 0.0
