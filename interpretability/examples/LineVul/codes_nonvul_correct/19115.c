// commit message qemu@732b530c1b (target=0, prob=0.12608854, correct=True): nvdimm acpi: set HDLE properly
/*0   */ static void nvdimm_build_common_dsm(Aml *dev)                                  // (9) 0.03516
/*2   */ {                                                                              // (29) 0.001953
/*4   */     Aml *method, *ifctx, *function, *dsm_mem, *unpatched, *result_size;        // (1) 0.06055
/*6   */     uint8_t byte_list[1];                                                      // (18) 0.02539
/*10  */     method = aml_method(NVDIMM_COMMON_DSM, 4, AML_SERIALIZED);                 // (0) 0.06055
/*12  */     function = aml_arg(2);                                                     // (19) 0.02344
/*14  */     dsm_mem = aml_name(NVDIMM_ACPI_MEM_ADDR);                                  // (4) 0.05273
/*18  */     /*                                                                         // (26) 0.007812
/*20  */      * do not support any method if DSM memory address has not been            // (11) 0.0332
/*22  */      * patched.                                                                // (22) 0.01367
/*24  */      */                                                                        // (23) 0.009766
/*26  */     unpatched = aml_if(aml_equal(dsm_mem, aml_int(0x0)));                      // (2) 0.06055
/*30  */     /*                                                                         // (27) 0.007812
/*32  */      * function 0 is called to inquire what functions are supported by         // (13) 0.03125
/*34  */      * OSPM                                                                    // (21) 0.01562
/*36  */      */                                                                        // (24) 0.009766
/*38  */     ifctx = aml_if(aml_equal(function, aml_int(0)));                           // (6) 0.04883
/*40  */     byte_list[0] = 0 /* No function Supported */;                              // (12) 0.0332
/*42  */     aml_append(ifctx, aml_return(aml_buffer(1, byte_list)));                   // (5) 0.05273
/*44  */     aml_append(unpatched, ifctx);                                              // (15) 0.0293
/*48  */     /* No function is supported yet. */                                        // (20) 0.02148
/*50  */     byte_list[0] = 1 /* Not Supported */;                                      // (14) 0.03125
/*52  */     aml_append(unpatched, aml_return(aml_buffer(1, byte_list)));               // (3) 0.05469
/*54  */     aml_append(method, unpatched);                                             // (17) 0.02734
/*58  */     /*                                                                         // (28) 0.007812
/*60  */      * The HDLE indicates the DSM function is issued from which device,        // (10) 0.03516
/*62  */      * it is not used at this time as no function is supported yet.            // (8) 0.03711
/*64  */      * Currently we make it always be 0 for all the devices and will set       // (7) 0.03711
/*66  */      * the appropriate value once real function is implemented.                // (16) 0.02734
/*68  */      */                                                                        // (25) 0.009766
/*70  */     aml_append(method, aml_store(aml_int(0x0), aml_name("HDLE")));             // 0.0
/*72  */     aml_append(method, aml_store(aml_arg(1), aml_name("REVS")));               // 0.0
/*74  */     aml_append(method, aml_store(aml_arg(2), aml_name("FUNC")));               // 0.0
/*78  */     /*                                                                         // 0.0
/*80  */      * tell QEMU about the real address of DSM memory, then QEMU               // 0.0
/*82  */      * gets the control and fills the result in DSM memory.                    // 0.0
/*84  */      */                                                                        // 0.0
/*86  */     aml_append(method, aml_store(dsm_mem, aml_name("NTFI")));                  // 0.0
/*90  */     result_size = aml_local(1);                                                // 0.0
/*92  */     aml_append(method, aml_store(aml_name("RLEN"), result_size));              // 0.0
/*94  */     aml_append(method, aml_store(aml_shiftleft(result_size, aml_int(3)),       // 0.0
/*96  */                                  result_size));                                // 0.0
/*98  */     aml_append(method, aml_create_field(aml_name("ODAT"), aml_int(0),          // 0.0
/*100 */                                         result_size, "OBUF"));                 // 0.0
/*102 */     aml_append(method, aml_concatenate(aml_buffer(0, NULL), aml_name("OBUF"),  // 0.0
/*104 */                                        aml_arg(6)));                           // 0.0
/*106 */     aml_append(method, aml_return(aml_arg(6)));                                // 0.0
/*108 */     aml_append(dev, method);                                                   // 0.0
/*110 */ }                                                                              // 0.0
