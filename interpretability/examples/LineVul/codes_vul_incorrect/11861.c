// commit message qemu@c508277335 (target=1, prob=0.07153563, correct=False): vmxnet3: Fix reading/writing guest memory specially when behind an IOMMU
/*0 */ static bool vmxnet3_verify_driver_magic(hwaddr dshmem)                        // (1) 0.2899
/*2 */ {                                                                             // (2) 0.01449
/*4 */     return (VMXNET3_READ_DRV_SHARED32(dshmem, magic) == VMXNET3_REV1_MAGIC);  // (0) 0.5652
/*6 */ }                                                                             // (3) 0.01449
