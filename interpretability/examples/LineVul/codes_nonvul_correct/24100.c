// commit message qemu@35c5a52d1d (target=0, prob=0.24910635, correct=True): acpi: do not use TARGET_PAGE_SIZE
/*0  */ void nvdimm_init_acpi_state(AcpiNVDIMMState *state, MemoryRegion *io,     // (6) 0.08599
/*2  */                             FWCfgState *fw_cfg, Object *owner)            // (1) 0.1274
/*4  */ {                                                                         // (9) 0.003185
/*6  */     memory_region_init_io(&state->io_mr, owner, &nvdimm_dsm_ops, state,   // (4) 0.09873
/*8  */                           "nvdimm-acpi-io", NVDIMM_ACPI_IO_LEN);          // (0) 0.1529
/*10 */     memory_region_add_subregion(io, NVDIMM_ACPI_IO_BASE, &state->io_mr);  // (3) 0.1083
/*14 */     state->dsm_mem = g_array_new(false, true /* clear */, 1);             // (7) 0.07962
/*16 */     acpi_data_push(state->dsm_mem, TARGET_PAGE_SIZE);                     // (8) 0.07962
/*18 */     fw_cfg_add_file(fw_cfg, NVDIMM_DSM_MEM_FILE, state->dsm_mem->data,    // (2) 0.121
/*20 */                     state->dsm_mem->len);                                 // (5) 0.08917
/*22 */ }                                                                         // (10) 0.003185
