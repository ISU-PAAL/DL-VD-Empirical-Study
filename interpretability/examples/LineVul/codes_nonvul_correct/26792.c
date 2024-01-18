// commit message qemu@72cf2d4f0e (target=0, prob=0.036381386, correct=True): Fix sys-queue.h conflict for good
/*0  */ int i2c_start_transfer(i2c_bus *bus, int address, int recv)             // (2) 0.09717
/*2  */ {                                                                       // (15) 0.004049
/*4  */     DeviceState *qdev;                                                  // (11) 0.03644
/*6  */     i2c_slave *slave = NULL;                                            // (6) 0.05263
/*10 */     LIST_FOREACH(qdev, &bus->qbus.children, sibling) {                  // (3) 0.08907
/*12 */         slave = I2C_SLAVE_FROM_QDEV(qdev);                              // (1) 0.1053
/*14 */         if (slave->address == address)                                  // (5) 0.06073
/*16 */             break;                                                      // (7) 0.05263
/*18 */     }                                                                   // (14) 0.01619
/*22 */     if (!slave)                                                         // (12) 0.02834
/*24 */         return 1;                                                       // (10) 0.04049
/*28 */     /* If the bus is already busy, assume this is a repeated            // (4) 0.06478
/*30 */        start condition.  */                                             // (8) 0.04453
/*32 */     bus->current_dev = slave;                                           // (9) 0.04453
/*34 */     slave->info->event(slave, recv ? I2C_START_RECV : I2C_START_SEND);  // (0) 0.1377
/*36 */     return 0;                                                           // (13) 0.02429
/*38 */ }                                                                       // (16) 0.004049
