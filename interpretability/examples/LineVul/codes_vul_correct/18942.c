// commit message qemu@7e5f90fa3f (target=1, prob=0.633681, correct=True): uImage: only try to load 'kernel' images (Hollis Blanchard)
/*0   */ int load_uimage(const char *filename, target_ulong *ep, target_ulong *loadaddr,  // (2) 0.05078
/*2   */                 int *is_linux)                                                   // (7) 0.04102
/*4   */ {                                                                                // (33) 0.001954
/*6   */     int fd;                                                                      // (28) 0.01367
/*8   */     int size;                                                                    // (29) 0.01172
/*10  */     uboot_image_header_t h;                                                      // (14) 0.02539
/*12  */     uboot_image_header_t *hdr = &h;                                              // (8) 0.03516
/*14  */     uint8_t *data = NULL;                                                        // (18) 0.02344
/*16  */     int ret = -1;                                                                // (24) 0.01758
/*20  */     fd = open(filename, O_RDONLY | O_BINARY);                                    // (4) 0.04297
/*22  */     if (fd < 0)                                                                  // (25) 0.01758
/*24  */         return -1;                                                               // (19) 0.02148
/*28  */     size = read(fd, hdr, sizeof(uboot_image_header_t));                          // (3) 0.04492
/*30  */     if (size < 0)                                                                // (26) 0.01758
/*32  */         goto out;                                                                // (21) 0.01953
/*36  */     bswap_uboot_header(hdr);                                                     // (10) 0.0293
/*40  */     if (hdr->ih_magic != IH_MAGIC)                                               // (9) 0.03516
/*42  */         goto out;                                                                // (20) 0.01953
/*46  */     /* TODO: Implement Multi-File images.  */                                    // (11) 0.0293
/*48  */     if (hdr->ih_type == IH_TYPE_MULTI) {                                         // (5) 0.04297
/*50  */         fprintf(stderr, "Unable to load multi-file u-boot images\n");            // (1) 0.05664
/*52  */         goto out;                                                                // (23) 0.01953
/*54  */     }                                                                            // (32) 0.007812
/*58  */     switch (hdr->ih_comp) {                                                      // (16) 0.02539
/*60  */     case IH_COMP_NONE:                                                           // (17) 0.02539
/*62  */     case IH_COMP_GZIP:                                                           // (12) 0.02734
/*64  */         break;                                                                   // (27) 0.01758
/*66  */     default:                                                                     // (30) 0.009766
/*68  */         fprintf(stderr,                                                          // (13) 0.02734
/*70  */                 "Unable to load u-boot images with compression type %d\n",       // (0) 0.0625
/*72  */                 hdr->ih_comp);                                                   // (6) 0.04297
/*74  */         goto out;                                                                // (22) 0.01953
/*76  */     }                                                                            // (31) 0.007812
/*80  */     /* TODO: Check CPU type.  */                                                 // (15) 0.02539
/*82  */     if (is_linux) {                                                              // 0.0
/*84  */         if (hdr->ih_type == IH_TYPE_KERNEL && hdr->ih_os == IH_OS_LINUX)         // 0.0
/*86  */             *is_linux = 1;                                                       // 0.0
/*88  */         else                                                                     // 0.0
/*90  */             *is_linux = 0;                                                       // 0.0
/*92  */     }                                                                            // 0.0
/*96  */     *ep = hdr->ih_ep;                                                            // 0.0
/*98  */     data = qemu_malloc(hdr->ih_size);                                            // 0.0
/*100 */     if (!data)                                                                   // 0.0
/*102 */         goto out;                                                                // 0.0
/*106 */     if (read(fd, data, hdr->ih_size) != hdr->ih_size) {                          // 0.0
/*108 */         fprintf(stderr, "Error reading file\n");                                 // 0.0
/*110 */         goto out;                                                                // 0.0
/*112 */     }                                                                            // 0.0
/*116 */     if (hdr->ih_comp == IH_COMP_GZIP) {                                          // 0.0
/*118 */         uint8_t *compressed_data;                                                // 0.0
/*120 */         size_t max_bytes;                                                        // 0.0
/*122 */         ssize_t bytes;                                                           // 0.0
/*126 */         compressed_data = data;                                                  // 0.0
/*128 */         max_bytes = UBOOT_MAX_GUNZIP_BYTES;                                      // 0.0
/*130 */         data = qemu_malloc(max_bytes);                                           // 0.0
/*134 */         bytes = gunzip(data, max_bytes, compressed_data, hdr->ih_size);          // 0.0
/*136 */         qemu_free(compressed_data);                                              // 0.0
/*138 */         if (bytes < 0) {                                                         // 0.0
/*140 */             fprintf(stderr, "Unable to decompress gzipped image!\n");            // 0.0
/*142 */             goto out;                                                            // 0.0
/*144 */         }                                                                        // 0.0
/*146 */         hdr->ih_size = bytes;                                                    // 0.0
/*148 */     }                                                                            // 0.0
/*152 */     cpu_physical_memory_write_rom(hdr->ih_load, data, hdr->ih_size);             // 0.0
/*156 */     if (loadaddr)                                                                // 0.0
/*158 */         *loadaddr = hdr->ih_load;                                                // 0.0
/*162 */     ret = hdr->ih_size;                                                          // 0.0
/*166 */ out:                                                                             // 0.0
/*168 */     if (data)                                                                    // 0.0
/*170 */         qemu_free(data);                                                         // 0.0
/*172 */     close(fd);                                                                   // 0.0
/*174 */     return ret;                                                                  // 0.0
/*176 */ }                                                                                // 0.0
