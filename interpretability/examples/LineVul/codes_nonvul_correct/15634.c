// commit message qemu@0e9b9edae7 (target=0, prob=0.006006357, correct=True): acpi: convert linker from GArray to BIOSLinker structure
/*0 */ void *bios_linker_loader_cleanup(GArray *linker)  // (0) 0.4318
/*2 */ {                                                 // (2) 0.02273
/*4 */     return g_array_free(linker, false);           // (1) 0.3409
/*6 */ }                                                 // (3) 0.02273
