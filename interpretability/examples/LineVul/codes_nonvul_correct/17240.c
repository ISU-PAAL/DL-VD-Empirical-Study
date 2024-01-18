// commit message qemu@68931a4082 (target=0, prob=0.008990848, correct=True): target-xtensa: xtfpga: attach FLASH to system IO
/*0  */ static void xtensa_kc705_init(MachineState *machine)  // (2) 0.1125
/*2  */ {                                                     // (9) 0.00625
/*4  */     static const LxBoardDesc kc705_board = {          // (6) 0.1
/*6  */         .flash_base = 0xf0000000,                     // (7) 0.1
/*8  */         .flash_size = 0x08000000,                     // (4) 0.1063
/*10 */         .flash_boot_base = 0x06000000,                // (1) 0.1188
/*12 */         .flash_sector_size = 0x20000,                 // (0) 0.1188
/*14 */         .sram_size = 0x2000000,                       // (3) 0.1125
/*16 */     };                                                // (8) 0.025
/*18 */     lx_init(&kc705_board, machine);                   // (5) 0.1
/*20 */ }                                                     // (10) 0.00625
