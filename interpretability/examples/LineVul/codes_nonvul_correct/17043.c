// commit message qemu@aff3f0f150 (target=0, prob=0.18464978, correct=True): xlnx-ep108: Rename to ZCU102
/*0  */ static void xlnx_ep108_machine_init(MachineClass *mc)  // (1) 0.1579
/*2  */ {                                                      // (6) 0.008772
/*4  */     mc->desc = "Xilinx ZynqMP EP108 board";            // (0) 0.1667
/*6  */     mc->init = xlnx_ep108_init;                        // (3) 0.1404
/*8  */     mc->block_default_type = IF_IDE;                   // (5) 0.1316
/*10 */     mc->units_per_default_bus = 1;                     // (4) 0.1316
/*12 */     mc->ignore_memory_transaction_failures = true;     // (2) 0.1491
/*14 */ }                                                      // (7) 0.008772
