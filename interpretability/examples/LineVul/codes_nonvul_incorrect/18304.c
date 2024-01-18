// commit message FFmpeg@57d77b3963 (target=0, prob=0.5469671, correct=False): lavu/opencl: apply misc cosmetics fixes
/*0  */ int av_opencl_buffer_read(uint8_t *dst_buf, cl_mem src_cl_buf, size_t buf_size)                            // (4) 0.0878
/*2  */ {                                                                                                          // (16) 0.002439
/*4  */     cl_int status;                                                                                         // (12) 0.01951
/*6  */     void *mapped = clEnqueueMapBuffer(gpu_env.command_queue, src_cl_buf,                                   // (6) 0.06829
/*8  */                                       CL_TRUE,CL_MAP_READ, 0, buf_size,                                    // (0) 0.1317
/*10 */                                       0, NULL, NULL, &status);                                             // (1) 0.1122
/*14 */     if (status != CL_SUCCESS) {                                                                            // (10) 0.03415
/*16 */         av_log(&openclutils, AV_LOG_ERROR, "Could not map OpenCL buffer: %s\n", opencl_errstr(status));    // (3) 0.1024
/*18 */         return AVERROR_EXTERNAL;                                                                           // (9) 0.03902
/*20 */     }                                                                                                      // (14) 0.009756
/*22 */     memcpy(dst_buf, mapped, buf_size);                                                                     // (7) 0.0439
/*26 */     status = clEnqueueUnmapMemObject(gpu_env.command_queue, src_cl_buf, mapped, 0, NULL, NULL);            // (5) 0.08537
/*28 */     if (status != CL_SUCCESS) {                                                                            // (11) 0.03415
/*30 */         av_log(&openclutils, AV_LOG_ERROR, "Could not unmap OpenCL buffer: %s\n", opencl_errstr(status));  // (2) 0.1049
/*32 */         return AVERROR_EXTERNAL;                                                                           // (8) 0.03902
/*34 */     }                                                                                                      // (15) 0.009756
/*36 */     return 0;                                                                                              // (13) 0.01463
/*38 */ }                                                                                                          // (17) 0.002439
