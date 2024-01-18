// commit message qemu@fc3b32958a (target=0, prob=0.009616244, correct=True): smbios: Make multiple -smbios type= accumulate sanely
/*0  */ static void smbios_build_type_1_fields(QemuOpts *opts)                          // (8) 0.04492
/*2  */ {                                                                               // (24) 0.001953
/*4  */     const char *val;                                                            // (14) 0.01563
/*8  */     val = qemu_opt_get(opts, "manufacturer");                                   // (9) 0.03906
/*10 */     if (val) {                                                                  // (15) 0.01562
/*12 */         smbios_add_field(1, offsetof(struct smbios_type_1, manufacturer_str),   // (6) 0.06445
/*14 */                          val, strlen(val) + 1);                                 // (2) 0.06641
/*16 */     }                                                                           // (20) 0.007812
/*18 */     val = qemu_opt_get(opts, "product");                                        // (11) 0.03711
/*20 */     if (val) {                                                                  // (16) 0.01562
/*22 */         smbios_add_field(1, offsetof(struct smbios_type_1, product_name_str),   // (0) 0.06836
/*24 */                          val, strlen(val) + 1);                                 // (3) 0.06641
/*26 */     }                                                                           // (21) 0.007812
/*28 */     val = qemu_opt_get(opts, "version");                                        // (12) 0.03711
/*30 */     if (val) {                                                                  // (17) 0.01562
/*32 */         smbios_add_field(1, offsetof(struct smbios_type_1, version_str),        // (7) 0.06445
/*34 */                          val, strlen(val) + 1);                                 // (4) 0.06641
/*36 */     }                                                                           // (22) 0.007812
/*38 */     val = qemu_opt_get(opts, "serial");                                         // (13) 0.03711
/*40 */     if (val) {                                                                  // (18) 0.01562
/*42 */         smbios_add_field(1, offsetof(struct smbios_type_1, serial_number_str),  // (1) 0.06836
/*44 */                          val, strlen(val) + 1);                                 // (5) 0.06641
/*46 */     }                                                                           // (23) 0.007812
/*48 */     val = qemu_opt_get(opts, "uuid");                                           // (10) 0.03906
/*50 */     if (val) {                                                                  // (19) 0.01562
/*52 */         if (qemu_uuid_parse(val, qemu_uuid) != 0) {                             // 0.0
/*54 */             error_report("Invalid UUID");                                       // 0.0
/*56 */             exit(1);                                                            // 0.0
/*58 */         }                                                                       // 0.0
/*60 */     }                                                                           // 0.0
/*62 */     val = qemu_opt_get(opts, "sku");                                            // 0.0
/*64 */     if (val) {                                                                  // 0.0
/*66 */         smbios_add_field(1, offsetof(struct smbios_type_1, sku_number_str),     // 0.0
/*68 */                          val, strlen(val) + 1);                                 // 0.0
/*70 */     }                                                                           // 0.0
/*72 */     val = qemu_opt_get(opts, "family");                                         // 0.0
/*74 */     if (val) {                                                                  // 0.0
/*76 */         smbios_add_field(1, offsetof(struct smbios_type_1, family_str),         // 0.0
/*78 */                          val, strlen(val) + 1);                                 // 0.0
/*80 */     }                                                                           // 0.0
/*82 */ }                                                                               // 0.0
