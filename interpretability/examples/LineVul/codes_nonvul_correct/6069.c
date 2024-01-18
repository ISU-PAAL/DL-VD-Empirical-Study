// commit message qemu@80dcfb8532 (target=0, prob=0.35624272, correct=True): virtio-serial-bus: post_load send_event when vm is running
/*0   */ static int virtio_serial_load(QEMUFile *f, void *opaque, int version_id)  // (1) 0.05078
/*2   */ {                                                                         // (32) 0.001953
/*4   */     VirtIOSerial *s = opaque;                                             // (16) 0.02344
/*6   */     VirtIOSerialPort *port;                                               // (20) 0.02148
/*8   */     uint32_t max_nr_ports, nr_active_ports, ports_map;                    // (3) 0.04687
/*10  */     unsigned int i;                                                       // (26) 0.01367
/*12  */     int ret;                                                              // (27) 0.01172
/*16  */     if (version_id > 3) {                                                 // (17) 0.02344
/*18  */         return -EINVAL;                                                   // (14) 0.02539
/*20  */     }                                                                     // (29) 0.007812
/*24  */     /* The virtio device */                                               // (23) 0.01758
/*26  */     ret = virtio_load(&s->vdev, f);                                       // (12) 0.0332
/*28  */     if (ret) {                                                            // (25) 0.01562
/*30  */         return ret;                                                       // (21) 0.01953
/*32  */     }                                                                     // (30) 0.007812
/*36  */     if (version_id < 2) {                                                 // (18) 0.02344
/*38  */         return 0;                                                         // (22) 0.01953
/*40  */     }                                                                     // (31) 0.007812
/*44  */     /* The config space */                                                // (24) 0.01563
/*46  */     qemu_get_be16s(f, &s->config.cols);                                   // (5) 0.04492
/*48  */     qemu_get_be16s(f, &s->config.rows);                                   // (6) 0.04297
/*52  */     qemu_get_be32s(f, &max_nr_ports);                                     // (8) 0.04297
/*54  */     tswap32s(&max_nr_ports);                                              // (13) 0.0293
/*56  */     if (max_nr_ports > tswap32(s->config.max_nr_ports)) {                 // (0) 0.05273
/*58  */         /* Source could have had more ports than us. Fail migration. */   // (9) 0.04102
/*60  */         return -EINVAL;                                                   // (15) 0.02539
/*62  */     }                                                                     // (28) 0.007813
/*66  */     for (i = 0; i < (max_nr_ports + 31) / 32; i++) {                      // (2) 0.05078
/*68  */         qemu_get_be32s(f, &ports_map);                                    // (4) 0.04687
/*72  */         if (ports_map != s->ports_map[i]) {                               // (7) 0.04297
/*74  */             /*                                                            // (19) 0.02344
/*76  */              * Ports active on source and destination don't               // (10) 0.04102
/*78  */              * match. Fail migration.                                     // (11) 0.03516
/*80  */              */                                                           // 0.0
/*82  */             return -EINVAL;                                               // 0.0
/*84  */         }                                                                 // 0.0
/*86  */     }                                                                     // 0.0
/*90  */     qemu_get_be32s(f, &nr_active_ports);                                  // 0.0
/*94  */     /* Items in struct VirtIOSerialPort */                                // 0.0
/*96  */     for (i = 0; i < nr_active_ports; i++) {                               // 0.0
/*98  */         uint32_t id;                                                      // 0.0
/*100 */         bool host_connected;                                              // 0.0
/*104 */         id = qemu_get_be32(f);                                            // 0.0
/*106 */         port = find_port_by_id(s, id);                                    // 0.0
/*108 */         if (!port) {                                                      // 0.0
/*110 */             return -EINVAL;                                               // 0.0
/*112 */         }                                                                 // 0.0
/*116 */         port->guest_connected = qemu_get_byte(f);                         // 0.0
/*118 */         host_connected = qemu_get_byte(f);                                // 0.0
/*120 */         if (host_connected != port->host_connected) {                     // 0.0
/*122 */             /*                                                            // 0.0
/*124 */              * We have to let the guest know of the host connection       // 0.0
/*126 */              * status change                                              // 0.0
/*128 */              */                                                           // 0.0
/*130 */             send_control_event(port, VIRTIO_CONSOLE_PORT_OPEN,            // 0.0
/*132 */                                port->host_connected);                     // 0.0
/*134 */         }                                                                 // 0.0
/*138 */         if (version_id > 2) {                                             // 0.0
/*140 */             uint32_t elem_popped;                                         // 0.0
/*144 */             qemu_get_be32s(f, &elem_popped);                              // 0.0
/*146 */             if (elem_popped) {                                            // 0.0
/*148 */                 qemu_get_be32s(f, &port->iov_idx);                        // 0.0
/*150 */                 qemu_get_be64s(f, &port->iov_offset);                     // 0.0
/*154 */                 qemu_get_buffer(f, (unsigned char *)&port->elem,          // 0.0
/*156 */                                 sizeof(port->elem));                      // 0.0
/*158 */                 virtqueue_map_sg(port->elem.in_sg, port->elem.in_addr,    // 0.0
/*160 */                                  port->elem.in_num, 1);                   // 0.0
/*162 */                 virtqueue_map_sg(port->elem.out_sg, port->elem.out_addr,  // 0.0
/*164 */                                  port->elem.out_num, 1);                  // 0.0
/*168 */                 /*                                                        // 0.0
/*170 */                  *  Port was throttled on source machine.  Let's          // 0.0
/*172 */                  *  unthrottle it here so data starts flowing again.      // 0.0
/*174 */                  */                                                       // 0.0
/*176 */                 virtio_serial_throttle_port(port, false);                 // 0.0
/*178 */             }                                                             // 0.0
/*180 */         }                                                                 // 0.0
/*182 */     }                                                                     // 0.0
/*184 */     return 0;                                                             // 0.0
/*186 */ }                                                                         // 0.0
