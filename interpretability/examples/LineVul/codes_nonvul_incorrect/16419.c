// commit message qemu@d0e7605ee0 (target=0, prob=0.5670456, correct=False): Check block driver read error in pflash_cfi0x
/*0   */ pflash_t *pflash_cfi02_register(target_phys_addr_t base, ram_addr_t off,       // (6) 0.05859
/*2   */                                 BlockDriverState *bs, uint32_t sector_len,     // (2) 0.08789
/*4   */                                 int nb_blocs, int nb_mappings, int width,      // (1) 0.0957
/*6   */                                 uint16_t id0, uint16_t id1,                    // (3) 0.08789
/*8   */                                 uint16_t id2, uint16_t id3,                    // (4) 0.08789
/*10  */                                 uint16_t unlock_addr0, uint16_t unlock_addr1)  // (0) 0.0957
/*12  */ {                                                                              // (19) 0.001953
/*14  */     pflash_t *pfl;                                                             // (13) 0.02148
/*16  */     int32_t chip_len;                                                          // (14) 0.02148
/*20  */     chip_len = sector_len * nb_blocs;                                          // (11) 0.03516
/*22  */     /* XXX: to be fixed */                                                     // (16) 0.01953
/*24  */ #if 0                                                                          // (17) 0.005859
/*26  */     if (total_len != (8 * 1024 * 1024) && total_len != (16 * 1024 * 1024) &&   // (8) 0.05664
/*28  */         total_len != (32 * 1024 * 1024) && total_len != (64 * 1024 * 1024))    // (7) 0.05859
/*30  */         return NULL;                                                           // (15) 0.01953
/*32  */ #endif                                                                         // (18) 0.003906
/*34  */     pfl = qemu_mallocz(sizeof(pflash_t));                                      // (9) 0.04297
/*36  */     /* FIXME: Allocate ram ourselves.  */                                      // (12) 0.02734
/*38  */     pfl->storage = qemu_get_ram_ptr(off);                                      // (10) 0.03906
/*40  */     pfl->fl_mem = cpu_register_io_memory(pflash_read_ops, pflash_write_ops,    // (5) 0.0625
/*42  */                                          pfl);                                 // 0.0
/*44  */     pfl->off = off;                                                            // 0.0
/*46  */     pfl->base = base;                                                          // 0.0
/*48  */     pfl->chip_len = chip_len;                                                  // 0.0
/*50  */     pfl->mappings = nb_mappings;                                               // 0.0
/*52  */     pflash_register_memory(pfl, 1);                                            // 0.0
/*54  */     pfl->bs = bs;                                                              // 0.0
/*56  */     if (pfl->bs) {                                                             // 0.0
/*58  */         /* read the initial flash content */                                   // 0.0
/*60  */         bdrv_read(pfl->bs, 0, pfl->storage, chip_len >> 9);                    // 0.0
/*62  */     }                                                                          // 0.0
/*64  */ #if 0 /* XXX: there should be a bit to set up read-only,                       // 0.0
/*66  */        *      the same way the hardware does (with WP pin).                    // 0.0
/*68  */        */                                                                      // 0.0
/*70  */     pfl->ro = 1;                                                               // 0.0
/*72  */ #else                                                                          // 0.0
/*74  */     pfl->ro = 0;                                                               // 0.0
/*76  */ #endif                                                                         // 0.0
/*78  */     pfl->timer = qemu_new_timer(vm_clock, pflash_timer, pfl);                  // 0.0
/*80  */     pfl->sector_len = sector_len;                                              // 0.0
/*82  */     pfl->width = width;                                                        // 0.0
/*84  */     pfl->wcycle = 0;                                                           // 0.0
/*86  */     pfl->cmd = 0;                                                              // 0.0
/*88  */     pfl->status = 0;                                                           // 0.0
/*90  */     pfl->ident[0] = id0;                                                       // 0.0
/*92  */     pfl->ident[1] = id1;                                                       // 0.0
/*94  */     pfl->ident[2] = id2;                                                       // 0.0
/*96  */     pfl->ident[3] = id3;                                                       // 0.0
/*98  */     pfl->unlock_addr[0] = unlock_addr0;                                        // 0.0
/*100 */     pfl->unlock_addr[1] = unlock_addr1;                                        // 0.0
/*102 */     /* Hardcoded CFI table (mostly from SG29 Spansion flash) */                // 0.0
/*104 */     pfl->cfi_len = 0x52;                                                       // 0.0
/*106 */     /* Standard "QRY" string */                                                // 0.0
/*108 */     pfl->cfi_table[0x10] = 'Q';                                                // 0.0
/*110 */     pfl->cfi_table[0x11] = 'R';                                                // 0.0
/*112 */     pfl->cfi_table[0x12] = 'Y';                                                // 0.0
/*114 */     /* Command set (AMD/Fujitsu) */                                            // 0.0
/*116 */     pfl->cfi_table[0x13] = 0x02;                                               // 0.0
/*118 */     pfl->cfi_table[0x14] = 0x00;                                               // 0.0
/*120 */     /* Primary extended table address */                                       // 0.0
/*122 */     pfl->cfi_table[0x15] = 0x31;                                               // 0.0
/*124 */     pfl->cfi_table[0x16] = 0x00;                                               // 0.0
/*126 */     /* Alternate command set (none) */                                         // 0.0
/*128 */     pfl->cfi_table[0x17] = 0x00;                                               // 0.0
/*130 */     pfl->cfi_table[0x18] = 0x00;                                               // 0.0
/*132 */     /* Alternate extended table (none) */                                      // 0.0
/*134 */     pfl->cfi_table[0x19] = 0x00;                                               // 0.0
/*136 */     pfl->cfi_table[0x1A] = 0x00;                                               // 0.0
/*138 */     /* Vcc min */                                                              // 0.0
/*140 */     pfl->cfi_table[0x1B] = 0x27;                                               // 0.0
/*142 */     /* Vcc max */                                                              // 0.0
/*144 */     pfl->cfi_table[0x1C] = 0x36;                                               // 0.0
/*146 */     /* Vpp min (no Vpp pin) */                                                 // 0.0
/*148 */     pfl->cfi_table[0x1D] = 0x00;                                               // 0.0
/*150 */     /* Vpp max (no Vpp pin) */                                                 // 0.0
/*152 */     pfl->cfi_table[0x1E] = 0x00;                                               // 0.0
/*154 */     /* Reserved */                                                             // 0.0
/*156 */     pfl->cfi_table[0x1F] = 0x07;                                               // 0.0
/*158 */     /* Timeout for min size buffer write (NA) */                               // 0.0
/*160 */     pfl->cfi_table[0x20] = 0x00;                                               // 0.0
/*162 */     /* Typical timeout for block erase (512 ms) */                             // 0.0
/*164 */     pfl->cfi_table[0x21] = 0x09;                                               // 0.0
/*166 */     /* Typical timeout for full chip erase (4096 ms) */                        // 0.0
/*168 */     pfl->cfi_table[0x22] = 0x0C;                                               // 0.0
/*170 */     /* Reserved */                                                             // 0.0
/*172 */     pfl->cfi_table[0x23] = 0x01;                                               // 0.0
/*174 */     /* Max timeout for buffer write (NA) */                                    // 0.0
/*176 */     pfl->cfi_table[0x24] = 0x00;                                               // 0.0
/*178 */     /* Max timeout for block erase */                                          // 0.0
/*180 */     pfl->cfi_table[0x25] = 0x0A;                                               // 0.0
/*182 */     /* Max timeout for chip erase */                                           // 0.0
/*184 */     pfl->cfi_table[0x26] = 0x0D;                                               // 0.0
/*186 */     /* Device size */                                                          // 0.0
/*188 */     pfl->cfi_table[0x27] = ctz32(chip_len);                                    // 0.0
/*190 */     /* Flash device interface (8 & 16 bits) */                                 // 0.0
/*192 */     pfl->cfi_table[0x28] = 0x02;                                               // 0.0
/*194 */     pfl->cfi_table[0x29] = 0x00;                                               // 0.0
/*196 */     /* Max number of bytes in multi-bytes write */                             // 0.0
/*198 */     /* XXX: disable buffered write as it's not supported */                    // 0.0
/*200 */     //    pfl->cfi_table[0x2A] = 0x05;                                         // 0.0
/*202 */     pfl->cfi_table[0x2A] = 0x00;                                               // 0.0
/*204 */     pfl->cfi_table[0x2B] = 0x00;                                               // 0.0
/*206 */     /* Number of erase block regions (uniform) */                              // 0.0
/*208 */     pfl->cfi_table[0x2C] = 0x01;                                               // 0.0
/*210 */     /* Erase block region 1 */                                                 // 0.0
/*212 */     pfl->cfi_table[0x2D] = nb_blocs - 1;                                       // 0.0
/*214 */     pfl->cfi_table[0x2E] = (nb_blocs - 1) >> 8;                                // 0.0
/*216 */     pfl->cfi_table[0x2F] = sector_len >> 8;                                    // 0.0
/*218 */     pfl->cfi_table[0x30] = sector_len >> 16;                                   // 0.0
/*222 */     /* Extended */                                                             // 0.0
/*224 */     pfl->cfi_table[0x31] = 'P';                                                // 0.0
/*226 */     pfl->cfi_table[0x32] = 'R';                                                // 0.0
/*228 */     pfl->cfi_table[0x33] = 'I';                                                // 0.0
/*232 */     pfl->cfi_table[0x34] = '1';                                                // 0.0
/*234 */     pfl->cfi_table[0x35] = '0';                                                // 0.0
/*238 */     pfl->cfi_table[0x36] = 0x00;                                               // 0.0
/*240 */     pfl->cfi_table[0x37] = 0x00;                                               // 0.0
/*242 */     pfl->cfi_table[0x38] = 0x00;                                               // 0.0
/*244 */     pfl->cfi_table[0x39] = 0x00;                                               // 0.0
/*248 */     pfl->cfi_table[0x3a] = 0x00;                                               // 0.0
/*252 */     pfl->cfi_table[0x3b] = 0x00;                                               // 0.0
/*254 */     pfl->cfi_table[0x3c] = 0x00;                                               // 0.0
/*258 */     return pfl;                                                                // 0.0
/*260 */ }                                                                              // 0.0
