// commit message qemu@de00982e9e (target=0, prob=0.032931447, correct=True): xen-platform: convert to memory API
/*0  */ static void platform_mmio_map(PCIDevice *d, int region_num,               // (4) 0.1061
/*2  */                               pcibus_t addr, pcibus_t size, int type)     // (1) 0.2222
/*4  */ {                                                                         // (6) 0.005051
/*6  */     int mmio_io_addr;                                                     // (5) 0.05556
/*10 */     mmio_io_addr = cpu_register_io_memory_simple(&platform_mmio_handler,  // (2) 0.1364
/*12 */                                                  DEVICE_NATIVE_ENDIAN);   // (0) 0.2879
/*16 */     cpu_register_physical_memory(addr, size, mmio_io_addr);               // (3) 0.1111
/*18 */ }                                                                         // (7) 0.005051
