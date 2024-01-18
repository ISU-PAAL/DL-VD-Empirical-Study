// commit message qemu@0c402e5abb (target=0, prob=0.34720442, correct=True): usb-host: parse port in /proc/bus/usb/devices scan
/*0   */ static int usb_host_scan_dev(void *opaque, USBScanFunc *func)                 // (9) 0.04297
/*2   */ {                                                                             // (30) 0.001953
/*4   */     FILE *f = NULL;                                                           // (19) 0.01758
/*6   */     char line[1024];                                                          // (22) 0.01562
/*8   */     char buf[1024];                                                           // (23) 0.01562
/*10  */     int bus_num, addr, speed, device_count, class_id, product_id, vendor_id;  // (0) 0.05469
/*12  */     char product_name[512];                                                   // (18) 0.01953
/*14  */     int ret = 0;                                                              // (21) 0.01563
/*18  */     if (!usb_host_device_path) {                                              // (13) 0.02734
/*20  */         perror("husb: USB Host Device Path not set");                         // (10) 0.03906
/*22  */         goto the_end;                                                         // (16) 0.02344
/*24  */     }                                                                         // (28) 0.007812
/*26  */     snprintf(line, sizeof(line), "%s/devices", usb_host_device_path);         // (6) 0.04883
/*28  */     f = fopen(line, "r");                                                     // (14) 0.02539
/*30  */     if (!f) {                                                                 // (24) 0.01562
/*32  */         perror("husb: cannot open devices file");                             // (11) 0.03516
/*34  */         goto the_end;                                                         // (17) 0.02344
/*36  */     }                                                                         // (29) 0.007812
/*40  */     device_count = 0;                                                         // (20) 0.01758
/*42  */     bus_num = addr = class_id = product_id = vendor_id = 0;                   // (8) 0.04492
/*44  */     speed = -1; /* Can't get the speed from /[proc|dev]/bus/usb/devices */    // (1) 0.05469
/*46  */     for(;;) {                                                                 // (25) 0.01562
/*48  */         if (fgets(line, sizeof(line), f) == NULL) {                           // (7) 0.04687
/*50  */             break;                                                            // (15) 0.02539
/*52  */         }                                                                     // (26) 0.01562
/*54  */         if (strlen(line) > 0) {                                               // (12) 0.03516
/*56  */             line[strlen(line) - 1] = '\0';                                    // (5) 0.05078
/*58  */         }                                                                     // (27) 0.01562
/*60  */         if (line[0] == 'T' && line[1] == ':') {                               // (4) 0.05273
/*62  */             if (device_count && (vendor_id || product_id)) {                  // (3) 0.05469
/*64  */                 /* New device.  Add the previously discovered device.  */     // (2) 0.05469
/*66  */                 ret = func(opaque, bus_num, addr, 0, class_id, vendor_id,     // 0.0
/*68  */                            product_id, product_name, speed);                  // 0.0
/*70  */                 if (ret) {                                                    // 0.0
/*72  */                     goto the_end;                                             // 0.0
/*74  */                 }                                                             // 0.0
/*76  */             }                                                                 // 0.0
/*78  */             if (get_tag_value(buf, sizeof(buf), line, "Bus=", " ") < 0) {     // 0.0
/*80  */                 goto fail;                                                    // 0.0
/*82  */             }                                                                 // 0.0
/*84  */             bus_num = atoi(buf);                                              // 0.0
/*86  */             if (get_tag_value(buf, sizeof(buf), line, "Dev#=", " ") < 0) {    // 0.0
/*88  */                 goto fail;                                                    // 0.0
/*90  */             }                                                                 // 0.0
/*92  */             addr = atoi(buf);                                                 // 0.0
/*94  */             if (get_tag_value(buf, sizeof(buf), line, "Spd=", " ") < 0) {     // 0.0
/*96  */                 goto fail;                                                    // 0.0
/*98  */             }                                                                 // 0.0
/*100 */             if (!strcmp(buf, "5000")) {                                       // 0.0
/*102 */                 speed = USB_SPEED_SUPER;                                      // 0.0
/*104 */             } else if (!strcmp(buf, "480")) {                                 // 0.0
/*106 */                 speed = USB_SPEED_HIGH;                                       // 0.0
/*108 */             } else if (!strcmp(buf, "1.5")) {                                 // 0.0
/*110 */                 speed = USB_SPEED_LOW;                                        // 0.0
/*112 */             } else {                                                          // 0.0
/*114 */                 speed = USB_SPEED_FULL;                                       // 0.0
/*116 */             }                                                                 // 0.0
/*118 */             product_name[0] = '\0';                                           // 0.0
/*120 */             class_id = 0xff;                                                  // 0.0
/*122 */             device_count++;                                                   // 0.0
/*124 */             product_id = 0;                                                   // 0.0
/*126 */             vendor_id = 0;                                                    // 0.0
/*128 */         } else if (line[0] == 'P' && line[1] == ':') {                        // 0.0
/*130 */             if (get_tag_value(buf, sizeof(buf), line, "Vendor=", " ") < 0) {  // 0.0
/*132 */                 goto fail;                                                    // 0.0
/*134 */             }                                                                 // 0.0
/*136 */             vendor_id = strtoul(buf, NULL, 16);                               // 0.0
/*138 */             if (get_tag_value(buf, sizeof(buf), line, "ProdID=", " ") < 0) {  // 0.0
/*140 */                 goto fail;                                                    // 0.0
/*142 */             }                                                                 // 0.0
/*144 */             product_id = strtoul(buf, NULL, 16);                              // 0.0
/*146 */         } else if (line[0] == 'S' && line[1] == ':') {                        // 0.0
/*148 */             if (get_tag_value(buf, sizeof(buf), line, "Product=", "") < 0) {  // 0.0
/*150 */                 goto fail;                                                    // 0.0
/*152 */             }                                                                 // 0.0
/*154 */             pstrcpy(product_name, sizeof(product_name), buf);                 // 0.0
/*156 */         } else if (line[0] == 'D' && line[1] == ':') {                        // 0.0
/*158 */             if (get_tag_value(buf, sizeof(buf), line, "Cls=", " (") < 0) {    // 0.0
/*160 */                 goto fail;                                                    // 0.0
/*162 */             }                                                                 // 0.0
/*164 */             class_id = strtoul(buf, NULL, 16);                                // 0.0
/*166 */         }                                                                     // 0.0
/*168 */     fail: ;                                                                   // 0.0
/*170 */     }                                                                         // 0.0
/*172 */     if (device_count && (vendor_id || product_id)) {                          // 0.0
/*174 */         /* Add the last device.  */                                           // 0.0
/*176 */         ret = func(opaque, bus_num, addr, 0, class_id, vendor_id,             // 0.0
/*178 */                    product_id, product_name, speed);                          // 0.0
/*180 */     }                                                                         // 0.0
/*182 */  the_end:                                                                     // 0.0
/*184 */     if (f) {                                                                  // 0.0
/*186 */         fclose(f);                                                            // 0.0
/*188 */     }                                                                         // 0.0
/*190 */     return ret;                                                               // 0.0
/*192 */ }                                                                             // 0.0
