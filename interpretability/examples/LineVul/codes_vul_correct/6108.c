// commit message qemu@2d896b454a (target=1, prob=0.59186107, correct=True): Revert "hw/mips: MIPS Boston board support"
/*0  */ static const void *boston_fdt_filter(void *opaque, const void *fdt_orig,         // (6) 0.04883
/*2  */                                      const void *match_data, hwaddr *load_addr)  // (0) 0.09961
/*4  */ {                                                                                // (25) 0.001953
/*6  */     BostonState *s = BOSTON(opaque);                                             // (14) 0.0293
/*8  */     MachineState *machine = s->mach;                                             // (15) 0.02539
/*10 */     const char *cmdline;                                                         // (19) 0.01758
/*12 */     int err;                                                                     // (22) 0.01172
/*14 */     void *fdt;                                                                   // (20) 0.01562
/*16 */     size_t fdt_sz, ram_low_sz, ram_high_sz;                                      // (4) 0.05078
/*20 */     fdt_sz = fdt_totalsize(fdt_orig) * 2;                                        // (8) 0.04883
/*22 */     fdt = g_malloc0(fdt_sz);                                                     // (13) 0.03516
/*26 */     err = fdt_open_into(fdt_orig, fdt, fdt_sz);                                  // (5) 0.05078
/*28 */     if (err) {                                                                   // (21) 0.01562
/*30 */         fprintf(stderr, "unable to open FDT\n");                                 // (9) 0.04688
/*32 */         return NULL;                                                             // (16) 0.01953
/*34 */     }                                                                            // (23) 0.007812
/*38 */     cmdline = (machine->kernel_cmdline && machine->kernel_cmdline[0])            // (10) 0.04492
/*40 */             ? machine->kernel_cmdline : " ";                                     // (12) 0.04297
/*42 */     err = qemu_fdt_setprop_string(fdt, "/chosen", "bootargs", cmdline);          // (1) 0.06055
/*44 */     if (err < 0) {                                                               // (17) 0.01953
/*46 */         fprintf(stderr, "couldn't set /chosen/bootargs\n");                      // (3) 0.05469
/*48 */         return NULL;                                                             // (18) 0.01953
/*50 */     }                                                                            // (24) 0.007812
/*54 */     ram_low_sz = MIN(256 * M_BYTE, machine->ram_size);                           // (7) 0.04883
/*56 */     ram_high_sz = machine->ram_size - ram_low_sz;                                // (11) 0.04492
/*58 */     qemu_fdt_setprop_sized_cells(fdt, "/memory@0", "reg",                        // (2) 0.05469
/*60 */                                  1, 0x00000000, 1, ram_low_sz,                   // 0.0
/*62 */                                  1, 0x90000000, 1, ram_high_sz);                 // 0.0
/*66 */     fdt = g_realloc(fdt, fdt_totalsize(fdt));                                    // 0.0
/*68 */     qemu_fdt_dumpdtb(fdt, fdt_sz);                                               // 0.0
/*72 */     s->fdt_base = *load_addr;                                                    // 0.0
/*76 */     return fdt;                                                                  // 0.0
/*78 */ }                                                                                // 0.0
