// commit message qemu@85df0de4cf (target=0, prob=0.7885681, correct=False): Allow to register a callback with fw_cfg_add_callback() fw_cfg_add_callback() checks if key has FW_CFG_WRITE_CHANNEL bit set after masking the key with FW_CFG_ENTRY_MASK.
/*0  */ int fw_cfg_add_callback(void *opaque, uint16_t key, FWCfgCallback callback,  // (2) 0.09818
/*2  */                         void *callback_opaque, uint8_t *data, size_t len)    // (0) 0.1527
/*4  */ {                                                                            // (14) 0.003636
/*6  */     FWCfgState *s = opaque;                                                  // (10) 0.04364
/*8  */     int arch = !!(key & FW_CFG_ARCH_LOCAL);                                  // (4) 0.07273
/*12 */     key &= FW_CFG_ENTRY_MASK;                                                // (5) 0.06182
/*16 */     if (key >= FW_CFG_MAX_ENTRY || !(key & FW_CFG_WRITE_CHANNEL)             // (1) 0.12
/*18 */         || len > 65535)                                                      // (9) 0.04727
/*20 */         return 0;                                                            // (11) 0.03636
/*24 */     s->entries[arch][key].data = data;                                       // (6) 0.05818
/*26 */     s->entries[arch][key].len = len;                                         // (7) 0.05818
/*28 */     s->entries[arch][key].callback_opaque = callback_opaque;                 // (3) 0.08
/*30 */     s->entries[arch][key].callback = callback;                               // (8) 0.05818
/*34 */     return 1;                                                                // (12) 0.02182
/*36 */ }                                                                            // (13) 0.003636
