// commit message qemu@1931076077 (target=0, prob=0.6114013, correct=False): migration: optimize the downtime
/*0  */ void memory_global_dirty_log_stop(void)                     // (3) 0.1057
/*2  */ {                                                           // (7) 0.00813
/*4  */     global_dirty_log = false;                               // (6) 0.08943
/*8  */     /* Refresh DIRTY_LOG_MIGRATION bit.  */                 // (1) 0.1545
/*10 */     memory_region_transaction_begin();                      // (4) 0.09756
/*12 */     memory_region_update_pending = true;                    // (2) 0.1138
/*14 */     memory_region_transaction_commit();                     // (5) 0.09756
/*18 */     MEMORY_LISTENER_CALL_GLOBAL(log_global_stop, Reverse);  // (0) 0.2033
/*20 */ }                                                           // (8) 0.00813
