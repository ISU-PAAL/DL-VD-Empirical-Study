// commit message qemu@65207c59d9 (target=1, prob=0.016229095, correct=False): monitor: Drop broken, unused asynchronous command interface
/*0 */ static inline bool handler_is_async(const mon_cmd_t *cmd)  // (0) 0.4043
/*2 */ {                                                          // (2) 0.02128
/*4 */     return cmd->flags & MONITOR_CMD_ASYNC;                 // (1) 0.383
/*6 */ }                                                          // (3) 0.02128
