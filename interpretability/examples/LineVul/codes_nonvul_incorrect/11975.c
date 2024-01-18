// commit message qemu@30de46db50 (target=0, prob=0.71201336, correct=False): vhost-user-test: Fix 'make check' broken on glib < 2.26
/*0   */ static void read_guest_mem(void)                                                // (17) 0.02148
/*2   */ {                                                                               // (27) 0.001953
/*4   */     uint32_t *guest_mem;                                                        // (14) 0.02539
/*6   */     gint64 end_time;                                                            // (19) 0.01953
/*8   */     int i, j;                                                                   // (21) 0.01562
/*10  */     size_t size;                                                                // (22) 0.01562
/*14  */     g_mutex_lock(data_mutex);                                                   // (13) 0.0293
/*18  */     end_time = g_get_monotonic_time() + 5 * G_TIME_SPAN_SECOND;                 // (2) 0.05859
/*20  */     while (!fds_num) {                                                          // (18) 0.02148
/*22  */         if (!_cond_wait_until(data_cond, data_mutex, end_time)) {               // (3) 0.05859
/*24  */             /* timeout has passed */                                            // (12) 0.03125
/*26  */             g_assert(fds_num);                                                  // (9) 0.03906
/*28  */             break;                                                              // (15) 0.02539
/*30  */         }                                                                       // (23) 0.01562
/*32  */     }                                                                           // (26) 0.007812
/*36  */     /* check for sanity */                                                      // (24) 0.01562
/*38  */     g_assert_cmpint(fds_num, >, 0);                                             // (10) 0.03711
/*40  */     g_assert_cmpint(fds_num, ==, memory.nregions);                              // (7) 0.04492
/*44  */     /* iterate all regions */                                                   // (20) 0.01758
/*46  */     for (i = 0; i < fds_num; i++) {                                             // (11) 0.03711
/*50  */         /* We'll check only the region statring at 0x0*/                        // (8) 0.04102
/*52  */         if (memory.regions[i].guest_phys_addr != 0x0) {                         // (5) 0.05469
/*54  */             continue;                                                           // (16) 0.02539
/*56  */         }                                                                       // (25) 0.01562
/*60  */         g_assert_cmpint(memory.regions[i].memory_size, >, 1024);                // (4) 0.05664
/*64  */         size =  memory.regions[i].memory_size + memory.regions[i].mmap_offset;  // (1) 0.06445
/*68  */         guest_mem = mmap(0, size, PROT_READ | PROT_WRITE,                       // (6) 0.05273
/*70  */                          MAP_SHARED, fds[i], 0);                                // (0) 0.07227
/*74  */         g_assert(guest_mem != MAP_FAILED);                                      // 0.0
/*76  */         guest_mem += (memory.regions[i].mmap_offset / sizeof(*guest_mem));      // 0.0
/*80  */         for (j = 0; j < 256; j++) {                                             // 0.0
/*82  */             uint32_t a = readl(memory.regions[i].guest_phys_addr + j*4);        // 0.0
/*84  */             uint32_t b = guest_mem[j];                                          // 0.0
/*88  */             g_assert_cmpint(a, ==, b);                                          // 0.0
/*90  */         }                                                                       // 0.0
/*94  */         munmap(guest_mem, memory.regions[i].memory_size);                       // 0.0
/*96  */     }                                                                           // 0.0
/*100 */     g_assert_cmpint(1, ==, 1);                                                  // 0.0
/*102 */     g_mutex_unlock(data_mutex);                                                 // 0.0
/*104 */ }                                                                               // 0.0
