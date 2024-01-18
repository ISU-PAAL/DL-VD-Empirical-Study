// commit message qemu@a907ec52cc (target=1, prob=0.27166718, correct=False): nvme: generate OpenFirmware device path in the "bootorder" fw_cfg file
/*0  */ static void nvme_instance_init(Object *obj)                     // (4) 0.1015
/*2  */ {                                                               // (5) 0.007247
/*4  */     object_property_add(obj, "bootindex", "int32",              // (3) 0.1377
/*6  */                         nvme_get_bootindex,                     // (1) 0.2319
/*8  */                         nvme_set_bootindex, NULL, NULL, NULL);  // (0) 0.2753
/*10 */     object_property_set_int(obj, -1, "bootindex", NULL);        // (2) 0.1594
/*12 */ }                                                               // (6) 0.007246
