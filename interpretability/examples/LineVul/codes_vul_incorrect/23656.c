// commit message qemu@82e59a676c (target=1, prob=0.26146373, correct=False): qmp: Fix design bug and read beyond buffer in memchar-write
/*0  */ void hmp_memchar_write(Monitor *mon, const QDict *qdict)      // (2) 0.1373
/*2  */ {                                                             // (8) 0.006536
/*4  */     uint32_t size;                                            // (7) 0.05882
/*6  */     const char *chardev = qdict_get_str(qdict, "device");     // (1) 0.1438
/*8  */     const char *data = qdict_get_str(qdict, "data");          // (3) 0.1373
/*10 */     Error *errp = NULL;                                       // (5) 0.06536
/*14 */     size = strlen(data);                                      // (6) 0.06536
/*16 */     qmp_memchar_write(chardev, size, data, false, 0, &errp);  // (0) 0.1699
/*20 */     hmp_handle_error(mon, &errp);                             // (4) 0.1046
/*22 */ }                                                             // (9) 0.006536
