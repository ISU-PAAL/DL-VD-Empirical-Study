// commit message qemu@6acbe4c6f1 (target=0, prob=0.52139384, correct=False): qdev: remove baked in notion of aliases (v2)
/*0 */ static void lsi53c895a_register_devices(void)      // (1) 0.2623
/*2 */ {                                                  // (3) 0.01639
/*4 */     type_register_static(&lsi_info);               // (2) 0.2295
/*6 */     type_register_static_alias(&lsi_info, "lsi");  // (0) 0.3279
/*8 */ }                                                  // (4) 0.01639
