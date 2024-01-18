// commit message qemu@f4bf56fb78 (target=1, prob=0.83513445, correct=True): vhost: remove assertion to prevent crash
/*0   */ static int vhost_user_set_mem_table(struct vhost_dev *dev,                              // (11) 0.04102
/*2   */                                     struct vhost_memory *mem)                           // (1) 0.08398
/*4   */ {                                                                                       // (21) 0.001953
/*6   */     int fds[VHOST_MEMORY_MAX_NREGIONS];                                                 // (10) 0.04102
/*8   */     int i, fd;                                                                          // (18) 0.01758
/*10  */     size_t fd_num = 0;                                                                  // (14) 0.02539
/*12  */     bool reply_supported = virtio_has_feature(dev->protocol_features,                   // (9) 0.04297
/*14  */                                               VHOST_USER_PROTOCOL_F_REPLY_ACK);         // (0) 0.125
/*18  */     VhostUserMsg msg = {                                                                // (16) 0.01953
/*20  */         .hdr.request = VHOST_USER_SET_MEM_TABLE,                                        // (6) 0.05078
/*22  */         .hdr.flags = VHOST_USER_VERSION,                                                // (12) 0.04102
/*24  */     };                                                                                  // (19) 0.007813
/*28  */     if (reply_supported) {                                                              // (17) 0.01953
/*30  */         msg.hdr.flags |= VHOST_USER_NEED_REPLY_MASK;                                    // (4) 0.06055
/*32  */     }                                                                                   // (20) 0.007812
/*36  */     for (i = 0; i < dev->mem->nregions; ++i) {                                          // (8) 0.04492
/*38  */         struct vhost_memory_region *reg = dev->mem->regions + i;                        // (7) 0.05078
/*40  */         ram_addr_t offset;                                                              // (13) 0.02734
/*42  */         MemoryRegion *mr;                                                               // (15) 0.02344
/*46  */         assert((uintptr_t)reg->userspace_addr == reg->userspace_addr);                  // (5) 0.05469
/*48  */         mr = memory_region_from_host((void *)(uintptr_t)reg->userspace_addr,            // (3) 0.06445
/*50  */                                      &offset);                                          // (2) 0.07617
/*52  */         fd = memory_region_get_fd(mr);                                                  // 0.0
/*54  */         if (fd > 0) {                                                                   // 0.0
/*56  */             msg.payload.memory.regions[fd_num].userspace_addr = reg->userspace_addr;    // 0.0
/*58  */             msg.payload.memory.regions[fd_num].memory_size  = reg->memory_size;         // 0.0
/*60  */             msg.payload.memory.regions[fd_num].guest_phys_addr = reg->guest_phys_addr;  // 0.0
/*62  */             msg.payload.memory.regions[fd_num].mmap_offset = offset;                    // 0.0
/*64  */             assert(fd_num < VHOST_MEMORY_MAX_NREGIONS);                                 // 0.0
/*66  */             fds[fd_num++] = fd;                                                         // 0.0
/*68  */         }                                                                               // 0.0
/*70  */     }                                                                                   // 0.0
/*74  */     msg.payload.memory.nregions = fd_num;                                               // 0.0
/*78  */     if (!fd_num) {                                                                      // 0.0
/*80  */         error_report("Failed initializing vhost-user memory map, "                      // 0.0
/*82  */                      "consider using -object memory-backend-file share=on");            // 0.0
/*84  */         return -1;                                                                      // 0.0
/*86  */     }                                                                                   // 0.0
/*90  */     msg.hdr.size = sizeof(msg.payload.memory.nregions);                                 // 0.0
/*92  */     msg.hdr.size += sizeof(msg.payload.memory.padding);                                 // 0.0
/*94  */     msg.hdr.size += fd_num * sizeof(VhostUserMemoryRegion);                             // 0.0
/*98  */     if (vhost_user_write(dev, &msg, fds, fd_num) < 0) {                                 // 0.0
/*100 */         return -1;                                                                      // 0.0
/*102 */     }                                                                                   // 0.0
/*106 */     if (reply_supported) {                                                              // 0.0
/*108 */         return process_message_reply(dev, &msg);                                        // 0.0
/*110 */     }                                                                                   // 0.0
/*114 */     return 0;                                                                           // 0.0
/*116 */ }                                                                                       // 0.0
