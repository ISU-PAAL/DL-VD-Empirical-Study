// commit message qemu@a1c3e4b839 (target=1, prob=0.99897337, correct=True): ehci: Schedule async-bh when IAAD bit gets set
/*0  */ static void ehci_mem_writel(void *ptr, target_phys_addr_t addr, uint32_t val)    // (1) 0.05664
/*1  */ {                                                                                // (26) 0.001953
/*2  */     EHCIState *s = ptr;                                                          // (18) 0.02344
/*3  */     uint32_t *mmio = (uint32_t *)(&s->mmio[addr]);                               // (8) 0.05078
/*4  */     uint32_t old = *mmio;                                                        // (15) 0.02539
/*5  */     int i;                                                                       // (25) 0.01172
/*6  */     trace_usb_ehci_mmio_writel(addr, addr2str(addr), val);                       // (7) 0.05078
/*7  */     /* Only aligned reads are allowed on OHCI */                                 // (14) 0.02734
/*8  */     if (addr & 3) {                                                              // (19) 0.01953
/*9  */         fprintf(stderr, "usb-ehci: Mis-aligned write to addr 0x"                 // (2) 0.05664
/*10 */                 TARGET_FMT_plx "\n", addr);                                      // (5) 0.05469
/*11 */         return;                                                                  // (20) 0.01758
/*12 */     if (addr >= PORTSC && addr < PORTSC + 4 * NB_PORTS) {                        // (9) 0.04883
/*13 */         handle_port_status_write(s, (addr-PORTSC)/4, val);                       // (4) 0.05469
/*14 */         trace_usb_ehci_mmio_change(addr, addr2str(addr), *mmio, old);            // (0) 0.06445
/*15 */         return;                                                                  // (21) 0.01758
/*16 */     if (addr < OPREGBASE) {                                                      // (16) 0.02539
/*17 */         fprintf(stderr, "usb-ehci: write attempt to read-only register"          // (3) 0.05469
/*18 */                 TARGET_FMT_plx "\n", addr);                                      // (6) 0.05469
/*19 */         return;                                                                  // (22) 0.01758
/*20 */     /* Do any register specific pre-write processing here.  */                   // (13) 0.03125
/*21 */     switch(addr) {                                                               // (24) 0.01562
/*22 */     case USBCMD:                                                                 // (23) 0.01563
/*23 */         if (val & USBCMD_HCRESET) {                                              // (10) 0.03906
/*24 */             ehci_reset(s);                                                       // (12) 0.03516
/*25 */             val = s->usbcmd;                                                     // (11) 0.03711
/*26 */             break;                                                               // (17) 0.02539
/*27 */         /* not supporting dynamic frame list size at the moment */               // 0.0
/*28 */         if ((val & USBCMD_FLS) && !(s->usbcmd & USBCMD_FLS)) {                   // 0.0
/*29 */             fprintf(stderr, "attempt to set frame list size -- value %d\n",      // 0.0
/*30 */                     val & USBCMD_FLS);                                           // 0.0
/*31 */             val &= ~USBCMD_FLS;                                                  // 0.0
/*32 */         if (((USBCMD_RUNSTOP | USBCMD_PSE | USBCMD_ASE) & val) !=                // 0.0
/*33 */             ((USBCMD_RUNSTOP | USBCMD_PSE | USBCMD_ASE) & s->usbcmd)) {          // 0.0
/*34 */             if (s->pstate == EST_INACTIVE) {                                     // 0.0
/*35 */                 SET_LAST_RUN_CLOCK(s);                                           // 0.0
/*36 */             s->usbcmd = val; /* Set usbcmd for ehci_update_halt() */             // 0.0
/*37 */             ehci_update_halt(s);                                                 // 0.0
/*38 */             qemu_mod_timer(s->frame_timer, qemu_get_clock_ns(vm_clock));         // 0.0
/*39 */         break;                                                                   // 0.0
/*40 */     case USBSTS:                                                                 // 0.0
/*41 */         val &= USBSTS_RO_MASK;              // bits 6 through 31 are RO          // 0.0
/*42 */         ehci_clear_usbsts(s, val);          // bits 0 through 5 are R/WC         // 0.0
/*43 */         val = s->usbsts;                                                         // 0.0
/*44 */         ehci_update_irq(s);                                                      // 0.0
/*45 */         break;                                                                   // 0.0
/*46 */     case USBINTR:                                                                // 0.0
/*47 */         val &= USBINTR_MASK;                                                     // 0.0
/*48 */         break;                                                                   // 0.0
/*49 */     case FRINDEX:                                                                // 0.0
/*50 */         val &= 0x00003ff8; /* frindex is 14bits and always a multiple of 8 */    // 0.0
/*51 */         break;                                                                   // 0.0
/*52 */     case CONFIGFLAG:                                                             // 0.0
/*53 */         val &= 0x1;                                                              // 0.0
/*54 */         if (val) {                                                               // 0.0
/*55 */             for(i = 0; i < NB_PORTS; i++)                                        // 0.0
/*56 */                 handle_port_owner_write(s, i, 0);                                // 0.0
/*57 */         break;                                                                   // 0.0
/*58 */     case PERIODICLISTBASE:                                                       // 0.0
/*59 */         if (ehci_periodic_enabled(s)) {                                          // 0.0
/*60 */             fprintf(stderr,                                                      // 0.0
/*61 */               "ehci: PERIODIC list base register set while periodic schedule\n"  // 0.0
/*62 */               "      is enabled and HC is enabled\n");                           // 0.0
/*63 */         break;                                                                   // 0.0
/*64 */     case ASYNCLISTADDR:                                                          // 0.0
/*65 */         if (ehci_async_enabled(s)) {                                             // 0.0
/*66 */             fprintf(stderr,                                                      // 0.0
/*67 */               "ehci: ASYNC list address register set while async schedule\n"     // 0.0
/*68 */               "      is enabled and HC is enabled\n");                           // 0.0
/*69 */         break;                                                                   // 0.0
/*70 */     *mmio = val;                                                                 // 0.0
/*71 */     trace_usb_ehci_mmio_change(addr, addr2str(addr), *mmio, old);                // 0.0
