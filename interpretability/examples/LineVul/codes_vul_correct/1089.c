// commit message qemu@384b557da1 (target=1, prob=0.8849421, correct=True): vhost: ensure vhost_ops are set before calling iotlb callback
/*0  */ int vhost_backend_invalidate_device_iotlb(struct vhost_dev *dev,               // (2) 0.1277
/*2  */                                                  uint64_t iova, uint64_t len)  // (0) 0.3245
/*4  */ {                                                                              // (7) 0.005319
/*6  */     struct vhost_iotlb_msg imsg;                                               // (4) 0.07447
/*10 */     imsg.iova = iova;                                                          // (5) 0.06383
/*12 */     imsg.size = len;                                                           // (6) 0.05319
/*14 */     imsg.type = VHOST_IOTLB_INVALIDATE;                                        // (3) 0.1117
/*18 */     return dev->vhost_ops->vhost_send_device_iotlb_msg(dev, &imsg);            // (1) 0.1543
/*20 */ }                                                                              // (8) 0.005319
