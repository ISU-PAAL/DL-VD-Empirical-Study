// commit message qemu@7e01376dae (target=0, prob=0.069713935, correct=True): s390x/css: fix ilen in IO instruction handlers
/*0  */ void ioinst_handle_msch(S390CPU *cpu, uint64_t reg1, uint32_t ipb)        // (2) 0.05664
/*2  */ {                                                                         // (33) 0.001953
/*4  */     int cssid, ssid, schid, m;                                            // (12) 0.03125
/*6  */     SubchDev *sch;                                                        // (17) 0.01758
/*8  */     SCHIB schib;                                                          // (26) 0.01562
/*10 */     uint64_t addr;                                                        // (18) 0.01758
/*12 */     int ret = -ENODEV;                                                    // (13) 0.02148
/*14 */     int cc;                                                               // (28) 0.01172
/*16 */     CPUS390XState *env = &cpu->env;                                       // (11) 0.03125
/*18 */     uint8_t ar;                                                           // (19) 0.01758
/*22 */     addr = decode_basedisp_s(env, ipb, &ar);                              // (8) 0.03906
/*24 */     if (addr & 3) {                                                       // (16) 0.01953
/*26 */         program_interrupt(env, PGM_SPECIFICATION, 2);                     // (5) 0.04492
/*28 */         return;                                                           // (20) 0.01758
/*30 */     }                                                                     // (29) 0.007812
/*32 */     if (s390_cpu_virt_mem_read(cpu, addr, ar, &schib, sizeof(schib))) {   // (1) 0.0625
/*34 */         return;                                                           // (21) 0.01758
/*36 */     }                                                                     // (30) 0.007812
/*38 */     if (ioinst_disassemble_sch_ident(reg1, &m, &cssid, &ssid, &schid) ||  // (0) 0.06836
/*40 */         !ioinst_schib_valid(&schib)) {                                    // (9) 0.03906
/*42 */         program_interrupt(env, PGM_OPERAND, 2);                           // (7) 0.04297
/*44 */         return;                                                           // (22) 0.01758
/*46 */     }                                                                     // (31) 0.007812
/*48 */     trace_ioinst_sch_id("msch", cssid, ssid, schid);                      // (3) 0.04883
/*50 */     sch = css_find_subch(m, cssid, ssid, schid);                          // (4) 0.04883
/*52 */     if (sch && css_subch_visible(sch)) {                                  // (10) 0.03516
/*54 */         ret = css_do_msch(sch, &schib);                                   // (6) 0.04492
/*56 */     }                                                                     // (32) 0.007812
/*58 */     switch (ret) {                                                        // (27) 0.01562
/*60 */     case -ENODEV:                                                         // (23) 0.01758
/*62 */         cc = 3;                                                           // (14) 0.02148
/*64 */         break;                                                            // (24) 0.01758
/*66 */     case -EBUSY:                                                          // (25) 0.01758
/*68 */         cc = 2;                                                           // (15) 0.02148
/*70 */         break;                                                            // 0.0
/*72 */     case 0:                                                               // 0.0
/*74 */         cc = 0;                                                           // 0.0
/*76 */         break;                                                            // 0.0
/*78 */     default:                                                              // 0.0
/*80 */         cc = 1;                                                           // 0.0
/*82 */         break;                                                            // 0.0
/*84 */     }                                                                     // 0.0
/*86 */     setcc(cpu, cc);                                                       // 0.0
/*88 */ }                                                                         // 0.0
