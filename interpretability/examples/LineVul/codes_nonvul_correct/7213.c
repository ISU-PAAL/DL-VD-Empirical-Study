// commit message qemu@aa8f057e74 (target=0, prob=0.36725438, correct=True): virtio-crypto: Convert to DEFINE_PROP_LINK
/*0  */ static void virtio_crypto_instance_init(Object *obj)                    // (9) 0.04878
/*2  */ {                                                                       // (12) 0.003049
/*4  */     VirtIOCrypto *vcrypto = VIRTIO_CRYPTO(obj);                         // (4) 0.07012
/*8  */     /*                                                                  // (11) 0.0122
/*10 */      * The default config_size is sizeof(struct virtio_crypto_config).  // (6) 0.06707
/*12 */      * Can be overriden with virtio_crypto_set_config_size.             // (5) 0.07012
/*14 */      */                                                                 // (10) 0.01524
/*16 */     vcrypto->config_size = sizeof(struct virtio_crypto_config);         // (7) 0.06707
/*20 */     object_property_add_link(obj, "cryptodev",                          // (8) 0.05488
/*22 */                              TYPE_CRYPTODEV_BACKEND,                    // (3) 0.1189
/*24 */                              (Object **)&vcrypto->conf.cryptodev,       // (2) 0.1311
/*26 */                              virtio_crypto_check_cryptodev_is_used,     // (1) 0.1341
/*28 */                              OBJ_PROP_LINK_UNREF_ON_RELEASE, NULL);     // (0) 0.1433
/*30 */ }                                                                       // (13) 0.003049
