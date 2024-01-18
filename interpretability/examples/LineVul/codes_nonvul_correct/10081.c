// commit message qemu@1931e26054 (target=0, prob=0.0077753263, correct=True): Check the Galilleo config register instead of hardcoding the endianness.
/*0  */ static uint32_t gt64120_read_config(PCIDevice *d, uint32_t address, int len)  // (0) 0.2941
/*2  */ {                                                                             // (6) 0.009804
/*4  */     uint32_t val = pci_default_read_config(d, address, len);                  // (1) 0.2255
/*6  */ #ifdef TARGET_WORDS_BIGENDIAN                                                 // (2) 0.1275
/*8  */     val = bswap32(val);                                                       // (3) 0.1176
/*10 */ #endif                                                                        // (5) 0.01961
/*12 */     return val;                                                               // (4) 0.05882
/*14 */ }                                                                             // (7) 0.009804
