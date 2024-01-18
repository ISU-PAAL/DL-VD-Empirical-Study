// commit message qemu@3393bc105d (target=0, prob=0.2605755, correct=True): usb-hub: need to check dev->attached
/*0   */ static int usb_hub_handle_control(USBDevice *dev, USBPacket *p,                  // (3) 0.04102
/*2   */                int request, int value, int index, int length, uint8_t *data)     // (0) 0.06445
/*4   */ {                                                                                // (34) 0.001953
/*6   */     USBHubState *s = (USBHubState *)dev;                                         // (9) 0.03125
/*8   */     int ret;                                                                     // (32) 0.01172
/*12  */     ret = usb_desc_handle_control(dev, p, request, value, index, length, data);  // (1) 0.05273
/*14  */     if (ret >= 0) {                                                              // (21) 0.01953
/*16  */         return ret;                                                              // (22) 0.01953
/*18  */     }                                                                            // (33) 0.007812
/*22  */     switch(request) {                                                            // (29) 0.01562
/*24  */     case EndpointOutRequest | USB_REQ_CLEAR_FEATURE:                             // (4) 0.03906
/*26  */         if (value == 0 && index != 0x81) { /* clear ep halt */                   // (2) 0.04883
/*28  */             goto fail;                                                           // (10) 0.02734
/*30  */         }                                                                        // (31) 0.01562
/*32  */         ret = 0;                                                                 // (17) 0.02148
/*34  */         break;                                                                   // (24) 0.01758
/*36  */     case DeviceRequest | USB_REQ_GET_INTERFACE:                                  // (8) 0.0332
/*38  */         data[0] = 0;                                                             // (11) 0.02734
/*40  */         ret = 1;                                                                 // (18) 0.02148
/*42  */         break;                                                                   // (25) 0.01758
/*44  */     case DeviceOutRequest | USB_REQ_SET_INTERFACE:                               // (6) 0.03516
/*46  */         ret = 0;                                                                 // (19) 0.02148
/*48  */         break;                                                                   // (26) 0.01758
/*50  */         /* usb specific requests */                                              // (16) 0.02344
/*52  */     case GetHubStatus:                                                           // (28) 0.01562
/*54  */         data[0] = 0;                                                             // (12) 0.02734
/*56  */         data[1] = 0;                                                             // (13) 0.02734
/*58  */         data[2] = 0;                                                             // (14) 0.02734
/*60  */         data[3] = 0;                                                             // (15) 0.02734
/*62  */         ret = 4;                                                                 // (20) 0.02148
/*64  */         break;                                                                   // (23) 0.01758
/*66  */     case GetPortStatus:                                                          // (27) 0.01563
/*68  */         {                                                                        // (30) 0.01562
/*70  */             unsigned int n = index - 1;                                          // (5) 0.03711
/*72  */             USBHubPort *port;                                                    // (7) 0.0332
/*74  */             if (n >= NUM_PORTS) {                                                // 0.0
/*76  */                 goto fail;                                                       // 0.0
/*78  */             }                                                                    // 0.0
/*80  */             port = &s->ports[n];                                                 // 0.0
/*82  */             data[0] = port->wPortStatus;                                         // 0.0
/*84  */             data[1] = port->wPortStatus >> 8;                                    // 0.0
/*86  */             data[2] = port->wPortChange;                                         // 0.0
/*88  */             data[3] = port->wPortChange >> 8;                                    // 0.0
/*90  */             ret = 4;                                                             // 0.0
/*92  */         }                                                                        // 0.0
/*94  */         break;                                                                   // 0.0
/*96  */     case SetHubFeature:                                                          // 0.0
/*98  */     case ClearHubFeature:                                                        // 0.0
/*100 */         if (value == 0 || value == 1) {                                          // 0.0
/*102 */         } else {                                                                 // 0.0
/*104 */             goto fail;                                                           // 0.0
/*106 */         }                                                                        // 0.0
/*108 */         ret = 0;                                                                 // 0.0
/*110 */         break;                                                                   // 0.0
/*112 */     case SetPortFeature:                                                         // 0.0
/*114 */         {                                                                        // 0.0
/*116 */             unsigned int n = index - 1;                                          // 0.0
/*118 */             USBHubPort *port;                                                    // 0.0
/*120 */             USBDevice *dev;                                                      // 0.0
/*122 */             if (n >= NUM_PORTS) {                                                // 0.0
/*124 */                 goto fail;                                                       // 0.0
/*126 */             }                                                                    // 0.0
/*128 */             port = &s->ports[n];                                                 // 0.0
/*130 */             dev = port->port.dev;                                                // 0.0
/*132 */             switch(value) {                                                      // 0.0
/*134 */             case PORT_SUSPEND:                                                   // 0.0
/*136 */                 port->wPortStatus |= PORT_STAT_SUSPEND;                          // 0.0
/*138 */                 break;                                                           // 0.0
/*140 */             case PORT_RESET:                                                     // 0.0
/*142 */                 if (dev) {                                                       // 0.0
/*144 */                     usb_send_msg(dev, USB_MSG_RESET);                            // 0.0
/*146 */                     port->wPortChange |= PORT_STAT_C_RESET;                      // 0.0
/*148 */                     /* set enable bit */                                         // 0.0
/*150 */                     port->wPortStatus |= PORT_STAT_ENABLE;                       // 0.0
/*152 */                 }                                                                // 0.0
/*154 */                 break;                                                           // 0.0
/*156 */             case PORT_POWER:                                                     // 0.0
/*158 */                 break;                                                           // 0.0
/*160 */             default:                                                             // 0.0
/*162 */                 goto fail;                                                       // 0.0
/*164 */             }                                                                    // 0.0
/*166 */             ret = 0;                                                             // 0.0
/*168 */         }                                                                        // 0.0
/*170 */         break;                                                                   // 0.0
/*172 */     case ClearPortFeature:                                                       // 0.0
/*174 */         {                                                                        // 0.0
/*176 */             unsigned int n = index - 1;                                          // 0.0
/*178 */             USBHubPort *port;                                                    // 0.0
/*182 */             if (n >= NUM_PORTS) {                                                // 0.0
/*184 */                 goto fail;                                                       // 0.0
/*186 */             }                                                                    // 0.0
/*188 */             port = &s->ports[n];                                                 // 0.0
/*190 */             switch(value) {                                                      // 0.0
/*192 */             case PORT_ENABLE:                                                    // 0.0
/*194 */                 port->wPortStatus &= ~PORT_STAT_ENABLE;                          // 0.0
/*196 */                 break;                                                           // 0.0
/*198 */             case PORT_C_ENABLE:                                                  // 0.0
/*200 */                 port->wPortChange &= ~PORT_STAT_C_ENABLE;                        // 0.0
/*202 */                 break;                                                           // 0.0
/*204 */             case PORT_SUSPEND:                                                   // 0.0
/*206 */                 port->wPortStatus &= ~PORT_STAT_SUSPEND;                         // 0.0
/*208 */                 break;                                                           // 0.0
/*210 */             case PORT_C_SUSPEND:                                                 // 0.0
/*212 */                 port->wPortChange &= ~PORT_STAT_C_SUSPEND;                       // 0.0
/*214 */                 break;                                                           // 0.0
/*216 */             case PORT_C_CONNECTION:                                              // 0.0
/*218 */                 port->wPortChange &= ~PORT_STAT_C_CONNECTION;                    // 0.0
/*220 */                 break;                                                           // 0.0
/*222 */             case PORT_C_OVERCURRENT:                                             // 0.0
/*224 */                 port->wPortChange &= ~PORT_STAT_C_OVERCURRENT;                   // 0.0
/*226 */                 break;                                                           // 0.0
/*228 */             case PORT_C_RESET:                                                   // 0.0
/*230 */                 port->wPortChange &= ~PORT_STAT_C_RESET;                         // 0.0
/*232 */                 break;                                                           // 0.0
/*234 */             default:                                                             // 0.0
/*236 */                 goto fail;                                                       // 0.0
/*238 */             }                                                                    // 0.0
/*240 */             ret = 0;                                                             // 0.0
/*242 */         }                                                                        // 0.0
/*244 */         break;                                                                   // 0.0
/*246 */     case GetHubDescriptor:                                                       // 0.0
/*248 */         {                                                                        // 0.0
/*250 */             unsigned int n, limit, var_hub_size = 0;                             // 0.0
/*252 */             memcpy(data, qemu_hub_hub_descriptor,                                // 0.0
/*254 */                    sizeof(qemu_hub_hub_descriptor));                             // 0.0
/*256 */             data[2] = NUM_PORTS;                                                 // 0.0
/*260 */             /* fill DeviceRemovable bits */                                      // 0.0
/*262 */             limit = ((NUM_PORTS + 1 + 7) / 8) + 7;                               // 0.0
/*264 */             for (n = 7; n < limit; n++) {                                        // 0.0
/*266 */                 data[n] = 0x00;                                                  // 0.0
/*268 */                 var_hub_size++;                                                  // 0.0
/*270 */             }                                                                    // 0.0
/*274 */             /* fill PortPwrCtrlMask bits */                                      // 0.0
/*276 */             limit = limit + ((NUM_PORTS + 7) / 8);                               // 0.0
/*278 */             for (;n < limit; n++) {                                              // 0.0
/*280 */                 data[n] = 0xff;                                                  // 0.0
/*282 */                 var_hub_size++;                                                  // 0.0
/*284 */             }                                                                    // 0.0
/*288 */             ret = sizeof(qemu_hub_hub_descriptor) + var_hub_size;                // 0.0
/*290 */             data[0] = ret;                                                       // 0.0
/*292 */             break;                                                               // 0.0
/*294 */         }                                                                        // 0.0
/*296 */     default:                                                                     // 0.0
/*298 */     fail:                                                                        // 0.0
/*300 */         ret = USB_RET_STALL;                                                     // 0.0
/*302 */         break;                                                                   // 0.0
/*304 */     }                                                                            // 0.0
/*306 */     return ret;                                                                  // 0.0
/*308 */ }                                                                                // 0.0
