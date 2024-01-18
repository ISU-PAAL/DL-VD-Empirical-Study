// commit message qemu@a907ec52cc (target=1, prob=0.018262072, correct=False): nvme: generate OpenFirmware device path in the "bootorder" fw_cfg file
/*0  */ static void nvme_get_bootindex(Object *obj, Visitor *v, void *opaque,  // (1) 0.2066
/*2  */                                   const char *name, Error **errp)      // (0) 0.3554
/*4  */ {                                                                      // (4) 0.008264
/*6  */     NvmeCtrl *s = NVME(obj);                                           // (3) 0.124
/*10 */     visit_type_int32(v, &s->conf.bootindex, name, errp);               // (2) 0.2066
/*12 */ }                                                                      // (5) 0.008264
