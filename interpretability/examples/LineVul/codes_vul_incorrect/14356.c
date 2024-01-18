// commit message qemu@0280b3eb7c (target=1, prob=0.39441708, correct=False): s390x/kvm: use cpu model for gscb on compat machines
/*0  */ static void ccw_machine_class_init(ObjectClass *oc, void *data)  // (7) 0.03906
/*2  */ {                                                                // (27) 0.001954
/*4  */     MachineClass *mc = MACHINE_CLASS(oc);                        // (13) 0.03125
/*6  */     NMIClass *nc = NMI_CLASS(oc);                                // (14) 0.03125
/*8  */     HotplugHandlerClass *hc = HOTPLUG_HANDLER_CLASS(oc);         // (4) 0.04492
/*10 */     S390CcwMachineClass *s390mc = S390_MACHINE_CLASS(mc);        // (1) 0.05078
/*14 */     s390mc->ri_allowed = true;                                   // (18) 0.02539
/*16 */     s390mc->cpu_model_allowed = true;                            // (16) 0.0293
/*18 */     s390mc->css_migration_enabled = true;                        // (15) 0.03125
/*20 */     s390mc->gs_allowed = true;                                   // (19) 0.02539
/*22 */     mc->init = ccw_init;                                         // (20) 0.02344
/*24 */     mc->reset = s390_machine_reset;                              // (17) 0.02734
/*26 */     mc->hot_add_cpu = s390_hot_add_cpu;                          // (8) 0.03906
/*28 */     mc->block_default_type = IF_VIRTIO;                          // (11) 0.0332
/*30 */     mc->no_cdrom = 1;                                            // (22) 0.02344
/*32 */     mc->no_floppy = 1;                                           // (24) 0.02344
/*34 */     mc->no_serial = 1;                                           // (26) 0.02148
/*36 */     mc->no_parallel = 1;                                         // (23) 0.02344
/*38 */     mc->no_sdcard = 1;                                           // (21) 0.02344
/*40 */     mc->use_sclp = 1;                                            // (25) 0.02344
/*42 */     mc->max_cpus = S390_MAX_CPUS;                                // (9) 0.03516
/*44 */     mc->has_hotpluggable_cpus = true;                            // (12) 0.0332
/*46 */     mc->get_hotplug_handler = s390_get_hotplug_handler;          // (6) 0.04297
/*48 */     mc->cpu_index_to_instance_props = s390_cpu_index_to_props;   // (0) 0.05469
/*50 */     mc->possible_cpu_arch_ids = s390_possible_cpu_arch_ids;      // (2) 0.05078
/*52 */     /* it is overridden with 'host' cpu *in kvm_arch_init* */    // (5) 0.04492
/*54 */     mc->default_cpu_type = S390_CPU_TYPE_NAME("qemu");           // (3) 0.04687
/*56 */     hc->plug = s390_machine_device_plug;                         // (10) 0.0332
/*58 */     hc->unplug_request = s390_machine_device_unplug_request;     // 0.0
/*60 */     nc->nmi_monitor_handler = s390_nmi;                          // 0.0
/*62 */ }                                                                // 0.0
