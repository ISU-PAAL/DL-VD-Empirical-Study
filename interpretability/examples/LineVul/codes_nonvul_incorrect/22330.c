// commit message qemu@5229f45bd9 (target=0, prob=0.59981, correct=False): aux: fix break that wanted to break two levels out
/*0   */ AUXReply aux_request(AUXBus *bus, AUXCommand cmd, uint32_t address,             // (7) 0.04688
/*2   */                       uint8_t len, uint8_t *data)                               // (2) 0.06641
/*4   */ {                                                                               // (26) 0.001953
/*6   */     AUXReply ret = AUX_NACK;                                                    // (13) 0.02734
/*8   */     I2CBus *i2c_bus = aux_get_i2c_bus(bus);                                     // (5) 0.05078
/*10  */     size_t i;                                                                   // (21) 0.01563
/*12  */     bool is_write = false;                                                      // (17) 0.01953
/*16  */     DPRINTF("request at address 0x%" PRIX32 ", command %u, len %u\n", address,  // (4) 0.05664
/*18  */             cmd, len);                                                          // (12) 0.0293
/*22  */     switch (cmd) {                                                              // (22) 0.01562
/*24  */     /*                                                                          // (25) 0.007812
/*26  */      * Forward the request on the AUX bus..                                     // (14) 0.02734
/*28  */      */                                                                         // (24) 0.009766
/*30  */     case WRITE_AUX:                                                             // (18) 0.01758
/*32  */     case READ_AUX:                                                              // (19) 0.01758
/*34  */         is_write = cmd == READ_AUX ? false : true;                              // (9) 0.04297
/*36  */         for (i = 0; i < len; i++) {                                             // (10) 0.03906
/*38  */             if (!address_space_rw(&bus->aux_addr_space, address++,              // (3) 0.05859
/*40  */                                   MEMTXATTRS_UNSPECIFIED, data++, 1,            // (0) 0.09375
/*42  */                                   is_write)) {                                  // (1) 0.07422
/*44  */                 ret = AUX_I2C_ACK;                                              // (6) 0.05078
/*46  */             } else {                                                            // (15) 0.02734
/*48  */                 ret = AUX_NACK;                                                 // (8) 0.04492
/*50  */                 break;                                                          // (11) 0.0332
/*52  */             }                                                                   // (16) 0.02344
/*54  */         }                                                                       // (23) 0.01562
/*56  */         break;                                                                  // (20) 0.01758
/*58  */     /*                                                                          // 0.0
/*60  */      * Classic I2C transactions..                                               // 0.0
/*62  */      */                                                                         // 0.0
/*64  */     case READ_I2C:                                                              // 0.0
/*66  */     case WRITE_I2C:                                                             // 0.0
/*68  */         is_write = cmd == READ_I2C ? false : true;                              // 0.0
/*70  */         if (i2c_bus_busy(i2c_bus)) {                                            // 0.0
/*72  */             i2c_end_transfer(i2c_bus);                                          // 0.0
/*74  */         }                                                                       // 0.0
/*78  */         if (i2c_start_transfer(i2c_bus, address, is_write)) {                   // 0.0
/*80  */             ret = AUX_I2C_NACK;                                                 // 0.0
/*82  */             break;                                                              // 0.0
/*84  */         }                                                                       // 0.0
/*88  */         ret = AUX_I2C_ACK;                                                      // 0.0
/*90  */         while (len > 0) {                                                       // 0.0
/*92  */             if (i2c_send_recv(i2c_bus, data++, is_write) < 0) {                 // 0.0
/*94  */                 ret = AUX_I2C_NACK;                                             // 0.0
/*96  */                 break;                                                          // 0.0
/*98  */             }                                                                   // 0.0
/*100 */             len--;                                                              // 0.0
/*102 */         }                                                                       // 0.0
/*104 */         i2c_end_transfer(i2c_bus);                                              // 0.0
/*106 */         break;                                                                  // 0.0
/*108 */     /*                                                                          // 0.0
/*110 */      * I2C MOT transactions.                                                    // 0.0
/*112 */      *                                                                          // 0.0
/*114 */      * Here we send a start when:                                               // 0.0
/*116 */      *  - We didn't start transaction yet.                                      // 0.0
/*118 */      *  - We had a READ and we do a WRITE.                                      // 0.0
/*120 */      *  - We changed the address.                                               // 0.0
/*122 */      */                                                                         // 0.0
/*124 */     case WRITE_I2C_MOT:                                                         // 0.0
/*126 */     case READ_I2C_MOT:                                                          // 0.0
/*128 */         is_write = cmd == READ_I2C_MOT ? false : true;                          // 0.0
/*130 */         if (!i2c_bus_busy(i2c_bus)) {                                           // 0.0
/*132 */             /*                                                                  // 0.0
/*134 */              * No transactions started..                                        // 0.0
/*136 */              */                                                                 // 0.0
/*138 */             if (i2c_start_transfer(i2c_bus, address, is_write)) {               // 0.0
/*140 */                 ret = AUX_I2C_NACK;                                             // 0.0
/*142 */                 break;                                                          // 0.0
/*144 */             }                                                                   // 0.0
/*146 */         } else if ((address != bus->last_i2c_address) ||                        // 0.0
/*148 */                    (bus->last_transaction != cmd)) {                            // 0.0
/*150 */             /*                                                                  // 0.0
/*152 */              * Transaction started but we need to restart..                     // 0.0
/*154 */              */                                                                 // 0.0
/*156 */             i2c_end_transfer(i2c_bus);                                          // 0.0
/*158 */             if (i2c_start_transfer(i2c_bus, address, is_write)) {               // 0.0
/*160 */                 ret = AUX_I2C_NACK;                                             // 0.0
/*162 */                 break;                                                          // 0.0
/*164 */             }                                                                   // 0.0
/*166 */         }                                                                       // 0.0
/*170 */         while (len > 0) {                                                       // 0.0
/*172 */             if (i2c_send_recv(i2c_bus, data++, is_write) < 0) {                 // 0.0
/*174 */                 ret = AUX_I2C_NACK;                                             // 0.0
/*176 */                 i2c_end_transfer(i2c_bus);                                      // 0.0
/*178 */                 break;                                                          // 0.0
/*180 */             }                                                                   // 0.0
/*182 */             len--;                                                              // 0.0
/*184 */         }                                                                       // 0.0
/*186 */         bus->last_transaction = cmd;                                            // 0.0
/*188 */         bus->last_i2c_address = address;                                        // 0.0
/*190 */         ret = AUX_I2C_ACK;                                                      // 0.0
/*192 */         break;                                                                  // 0.0
/*194 */     default:                                                                    // 0.0
/*196 */         DPRINTF("Not implemented!\n");                                          // 0.0
/*198 */         return AUX_NACK;                                                        // 0.0
/*200 */     }                                                                           // 0.0
/*204 */     DPRINTF("reply: %u\n", ret);                                                // 0.0
/*206 */     return ret;                                                                 // 0.0
/*208 */ }                                                                               // 0.0
