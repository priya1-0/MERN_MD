
typedef struct {
	parm_d     uint32                      _stat__nat_wan_l2tp; /* WAN to LAN receive L2TP packet type counter */
	var_d      int                         _s1_detector_offset;
	var_d      uint16                      _rf_interrupt_running;
	debug_d    fract                       _debug_array [500];
	shared_d   bool                        _parm__vppn_garbage_collection;
	parm_d     uint16                      _parm__ipbx_call_back_retry_duration;
	parm_d     struct ring_descriptor      _parm__ipbx_call_holding_rering;
	var_d      ufract                      _pcm_rx_gain;
	fast_d     phase_t                     _modulator_phase;
	debug_d    fract                       _v34_equalizer_slew_medium;
	var_d      legacy_callback_t           _legacy_tx_ack_handler;
	var_d      uint16                      _ipod_iface_rx_state;
	var_d      sint15                      _lsf600_s [NLSF600];
	var_d      sint15                      _parm__speech_asm_host_lb;
	parm_d     sint15                      _parm__slac_ring_frequency;
	parm_d     char                        _parm__sdp_g723_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      uint16                      _monitor_ones_flag;
	var_d      ufract                      _ph2_tx_Lx_gain;
	var_d      fract                       _monitor_sample_slow_absolute_threshold;
	var_d      fract40                     _v90_rx_spectrum_result_buffer_real40 [V90_RX_NO_BINS];
	shared_d   int                         _impedance_monitor_filter_offset;
	var_d      fract *                     _ph2p_anal_log_S_plus_start;
	var_d      uint16                      _sonitrol_audio_Lpt_request_sent;
	var_d      uint16                      _DMOVLAY;
	var_d      sint15                      _gear_counter;
	parm_d     sint15                      _parm__ringer_tx_gain;
	var_d      sint15                      _ph2_rx_rate_conv_9K6_8K0_pointer;
	var_d      phase_t                     _ANSam_measured_delta_phase;
	var_d      uint16                      _ph1_tx_ANSpcm_sign_reverse;
	var_d      fract40                     _ANSam_power40;
	var_d      uint16 *                    _v34h_rx_control_this_pointer;
	var_d      uint16                      _v34_symbol_diff_decode_data;
	var_d      uint16                      _v92h_rx_M_1_buffer [V92_MOD_M_BUFFER_SIZE+1]; /* +1 zero word for proper downshift of MSW in shaper */
	var_d      fract                       _convert_target_log;
	parm_d     uint16                      _parm__voip_melp_postfilter_enable;
	var_d      uint16                      _pcm_playback_mode;
	var_d      sint15                      _prev_gain_low_rate_chn_read [2*NF*NUM_GAINFR] ;
	var_d      uint16                      _ipod_command_vad_enable;
	parm_d     uint16                      _parm__sdp_melp_codec_dyn_pt;
	var_d      uint16                      _parm__battery_level_threshold;
	var_d      fract                       _equalizer_slew;
	var_d      uint16                      _saved_v90trn_mask;
	var_d      uint16                      _sonitrol_rx_transaction_count;
	parm_d     fract                       _parm__dm_v34_mse_trn_bias;
	var_d      uint16                      _switch_counter;
	var_d      fract                       _g722_d4l_bl [7];
	var_d      uint16                      _v34n_rx_symbol_rate;
	parm_d     uint16                      _parm__ctcss_enc_frequency;
	fast_d     uint16                      _gaussian_buffer [2];
	var_d      bool                        _ph2_INFO_detected;
	parm_d     bool                        _parm__nat_block_malicious_ports; /* Block malicious ports (Ident 113, Back Orifice 31337/12345, others) */
	var_d      fract                       _pcm_rx_2k_energy_ph3;
	var_d      sint15                      _tone_generator_previous;
	var_d      sint15                      _predicted_rx_xn_B1_Q_n_count;
	var_d      uint16                      _legacy_rx_duplicate_length;
	parm_d     bool                        _parm__net_isp_keep_alive_enable;
	parm_d     uint16                      _parm__sdp_t38_codec_dyn_pt;
	var_d      uint16                      _v34_initialize_data_illegal_setting;
	var_d      uint16                      _ipod_msg_rx_sig_on_offset;
	var_d      sint15 (*                   _v92_x_law_decode_routine) (sint15 code);
	var_d      fract                       _p18_correlator_fit_threshold;
	debug_d    uint16                      _overlay_ph2_uses_ph1_results;
	debug_d    fract                       _ph2_power_trace_Yoffset;
	var_d      sint15                      _l_bit_buffer [NUM_CH_BITS];
	shared_d   uint16                      _stat__ipbx_epoch_clock;
	var_d      fract                       _monitor_be2_angle;
	var_d      sint15                      _v34_yn_perfect_imag;
	var_d      sint15                      _v34_rx_xn_imag;
	debug_d    sint15                      _false_hit_miss_limit;
	var_d      sint15                      _lpbuf_pitchAuto [PIT_COR_LEN];
	var_d      sint15                      _noise_fg [MODE][MA_NP][M_LP];
	var_d      sint15                      _tone_pattern_index;
	var_d      uint16                      _v34f_recp_requests_restart;
	var_d      uint16                      _rf_sample_interrupt_offset;
	var_d      thread_routine_t            _pcm_btr_routine;
	var_d      fract32                     _ph2p_powr_P_buffer32 [PH2P_NO_TONES];
	var_d      fract                       _pcm_ctl_echo_rx_DC;
	parm_d     uint16                      _parm__selcall_enc_lead_out;
	var_d      sint15                      _v92_rx_Ru_detect_count;
	var_d      fract                       _dtmf_last_col_level;
	var_d      fract CIRCULAR              _cc_rx_delay_buffer_imag [CC_RX_DELAY_SIZE];
	shared_d   uint16                      _sonitrol_CS_port;
	var_d      uint16                      _v92n_rx_CP_specify;
	var_d      sint15                      _p18_hit_counter;
	shared_d   bool                        _vppn_sent_final_poll;
	var_d      sint15                      _l_firstTime_lsp_to_freq;
	local_d    fract CIRCULAR              _fsk_lpf_buffer_real [2 * C7K2_RX_LPF_SIZE];
	debug_d    uint16                      _sample_state;
	var_d      sint15                      _mem_w0 [M_LP];
	debug_d    uint16                      _baud_rx_state;
	var_d      fract*                      _ph2_rx_special_bpf_coef_pointer;
	var_d      fract                       _log_previous_energy;
	var_d      uint16                      _stat__phone_memcard_state;
	parm_d     uint16                      _parm__rtp_srtp_aes_keylength;
	var_d      sint15                      _lpfsp_delout [LPF_ORD];
	var_d      fract                       _g711_rx_vad_level_passthrough;
	parm_d     uint16                      _parm__ipbx_ring_debounce;
	var_d      fract                       _g722_d4l_dl [7];
	var_d      uint16                      _v90n_parm_nominal_power;
	var_d      event_t                     _V92_EVENT__XX_RECEIVED_CRC_ERROR;
	var_d      uint16                      _stat__oicp_ved_key_mask;
	var_d      fract                       _ph2_rx_passband_buffer [2*(PH2_RX_DATA_SIZE+16)];
	shared_d   uint16                      _sonitrol_lc_download_ethernet_initiated;
	parm_d     uint16                      _parm__codec_line_in_use_debounce;
	var_d      ufract                      _agc_2_gain;
	parm_d     bool                        _parm__ipbx_fxo_pstn_cid_forward_enable;
	var_d      uint16                      _v34n_parm_difference_option;
	const_d    uint16                      _v17_long_seg2_length;
	var_d      fract                       _v34_resync_data_buffer_imag [2*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract                       _v92_system_ID_input;
	var_d      uint16                      _ipod_msg_tx_sig_type;
	parm_d     uint16                      _parm__speech_dec_g711_plc_en;
	parm_d     uint32                      _stat__nat_wan_frag_required; /* WAN to LAN receive fragmentation required packet exit counter */
	shared_d   uint16                      _dprmbx_generate_ack;
	var_d      uint16                      _ph2p_powr_L1_delay_delay_start;
	parm_d     bool                        _parm__selcall_enc_enable;
	var_d      uint16                      _ipbx_parameter_index;
	parm_d     uint16                      _stat__dm_v92_negotiation;
	debug_d    fract                       _v34_equalizer_slew_slow;
	var_d      fract                       _equalizer_lagging_real [2*((xV34_XX_EQUALIZER_SIZE)/2)];
	var_d      sint15                      _v34_tx_local_data_enable;
	debug_d    sint15                      _valid_hit_limit;
	var_d      fract                       _pcm_tx_hpf_ff;
	var_d      const sint15*               _ph1_tx_ANSpcm_cosine_pointer;
	parm_d     struct tone_descriptor      _parm__ipbx_off_hook_warning_tone;
	const_d    fract                       _train_on_data_64_slew;
	var_d      const uint16*               _v90_rx_dil_tp_ptr;
	parm_d     uint16                      _parm__ipbx_epoch_clock_limit;
	var_d      uint16                      _V90S_LEN_8K0_J_DELAY;
	var_d      int                         _sonitrol_v34_mode;
	parm_d     uint16                      _parm__video_capture_mode;
	var_d      sint15                      _V34H_RX_BASE_GROUP_SIZE_1;
	var_d      uint16                      _scrambled_mark_count;
	var_d      call_info_t                 _parm__ipbx_incoming_call_history [IPBX_HIST__INCOMING_NO_OF];
	var_d      fract   CIRCULAR            _pcm_xmit_reshape_buffer [2*PCM_XMIT_RESHAPE_SIZE];
	local_d    uint16                      _pick_max_index;
	var_d      sint15                      _parm__speech_rtp_tone_frame_mask; /* RTP_TONE__BIT__DTMF | RTP_TONE__BIT__ANS */
	fast_d     int                         _rate_double_control;
	parm_d     bool                        _parm__nat_ice_enable;
	var_d      fract                       _pcm_btr_measurement_imag;
	var_d      uint16                      _led_pattern_index;
	var_d      g723_decstatdef_t           _g723_DecStat;
	shared_d   uint16                      _parm__vppn_keepalive_debounce [NUMBER_OF_LINES_PER_DSP];
	parm_d     bool                        _parm__voip_silence_supression_enable; /* Some codecs have silence supression built in and separately controlled */
	var_d      uint16                      _ph2_INFOMARKS_qualify_length;
	var_d      sint15                      _rf_fm_sample_cnt;
	fast_d     fract                       _precision_sin_value;
	var_d      uint16                      _nat_icmp_src_port; /* Source IP port */
	parm_d     uint16                      _parm__enc_used_mode;
	var_d      uint16                      _rx_trans_packets;
	var_d      sint15                      _btrec_phdet_jam_holdoff;
	var_d      uint16                      _number_of_iterations;
	var_d      sint15                      _pcm_rx_interpolator_poffset;
	var_d      sint15                      _parm__speech_rtp_min_frame_size;
	var_d      task_t                      _bg_task_table [NUMBER_OF_BG_TASKS];
	var_d      fract32                     _notch_datax32_060;
	var_d      uint16                      _force_train_word_pointer;
	shared_d   int                         _impedance_monitor_decimate;
	stat_d     sint15                      _stat__speech_enc_fill_slot_size;
	var_d      fract                       _FALL_fallback_value;
	var_d      fract                       _monitor_be2_count_length_log;
	var_d      ident_t                     _fg_thread_idents [NUMBER_OF_TOTAL_THREAD_COMP];
	const_d    uint16                      _v17_short_limit;
	fast_d     fract                       _rx_sample;
	debug_d    bool                        _v34s_reneg_test_produce_noise;
	var_d      uint32                      _asm_encode_rtp_dtmf_generate_end;
	var_d      uint16                      _nat_rtp_open_port [NUMBER_OF_CHANNELS_PER_DSP]; /* Open RTP port numbers */
	parm_d     uint16                      _parm__ipbx_hookflash_delay;
	fast_d     sint15                      _decode_frame_sample_counter;
	shared_d   uint16                      _radio_led_mask;
	var_d      sint15                      _ipbx_disassociation_counter;
	var_d      sint15                      _l_prev_scale;
	fast_d     int                         _current_fg_state;
	var_d      uint16                      _parm__rtp_srtp_mode;
	var_d      uint16                      _faxparm_active__silence_duration;
	const_d    fract                       _V92_RX_RETRAIN_Ag_THRESHOLD;
	var_d      fract                       _lec__worst_erl_ratio;
	var_d      uint16                      _v34n_tx_control_channel_data_rate;
	var_d      sint15                      _trellis_equ_error;
	var_d      sint15                      _lookback_output_imag;
	var_d      sint15                      _v34_tx_xn_local_imag;
	debug_d    fract                       _debug_array2 [500];
	parm_d     struct tone_descriptor      _parm__ipbx_sit2_tone;
	parm_d     char                        _parm__ata_phone_lock_password [ATA_PASSWORD_SIZEOF];
	debug_d    fract                       _debug_array3 [500];
	parm_d     uint32                      _stat__nat_wan_frag_created; /* WAN to LAN receive fragment forwarding created counter */
	debug_d    fract                       _debug_array4 [500];
	debug_d    fract                       _debug_array5 [500];
	debug_d    uint16                      _V34S_LEN_8K0_MAX_1ST_GEAR;
	var_d      fract                       _v34_rx_zn_tilde_imag;
	debug_d    fract                       _debug_array6 [500];
	var_d      fract                       _g722_enc_slow;
	parm_d     uint16                      _parm__receiver_gain;
	var_d      sint15                      _parm__speech_dec_cng_order;
	var_d      uint16                      _dgi_pad_gain;
	const_d    fract                       _monitor_sample_slow_hi_absolute_threshold;
	var_d      uint16                      _ph2n_rx_carrier [V34N_MAX_SYMBOL+1];
	var_d      sint15                      _fallback_flag;
	var_d      sint15                      _lec__td_update_ratio;
	var_d      uint16                      _force_train_bit_pointer;
	parm_d     sdp_session_t               _sdp_e;
	var_d      fract                       _ANSam_magnitude;
	var_d      sint15                      _cc_rx_PP_repetition_limit;
	var_d      uint16                      _save_sm_INFO1c_end_delay;
	var_d      fract                       _cc_rx_ANAL_energy_log;
	var_d      sint15 (*                   _ph1_x_law_encode_routine) (sint15 valu);
	var_d      sint15                      _floor_detect__shift;
	parm_d     uint16                      _parm__disconnect_tone_cadence_table [6 * 2 * DT_TABLE_ENTRY_NUM];
	var_d      uint16                      _ipod_htd_coded_speech_buffer [IPOD_MAX_PAYLOAD_SIZE];
	parm_d     uint32                      _parm__net_static_ip_address;
	stat_d     uint16                      _stat__dm_tx_data_rate;
	var_d      uint16                      _v34_rx_valid_qn_coefs_flag;
	var_d      fract                       _v92_system_ID_outputA;
	var_d      SPP_data_buffer_t *         _audio_delay_queue;
	parm_d     struct ring_descriptor      _parm__ipbx_call_back_ring_splash;
	var_d      fract                       _v34_resync_mean_buffer_imag [1*(V34_RESYNC_Nx2_plus_1)];
	debug_d    tone_detector_vars_t        _tone_detector_variables [NUMBER_MAX_TONE_DETECTORS+1];
	fast_d     phase_t                     _tx_clock_phase;
	parm_d     char                        _parm__ata_configuration_request_message [ATA_MESSAGE_SIZEOF];
	var_d      uint16                      _equalizer_poffset;
	var_d      fract                       _pcm_HI_peak_value;
	var_d      fract                       _V90_RX_R_ENERGY_THRESHOLD;
	var_d      bool                        _firstTime_syn;
	debug_d    sint15                      _ec_very_slow_shift_slew_local;
	shared_d   transaction_list_t          _mgcp_tx_transaction_list [MAX_MGCP_TRANSACTION_HISTORY];
	var_d      fract                       _ph2p_anal_log_E_buffer [PH2P_NO_TONES];
	var_d      uint8                       _sonitrol_remote_updnload_ip [4];
	debug_d    sint15                      _V34S_RUN_HOLDOFF_TIME;
	var_d      const fract*                _fsk_tx_passband_coef_pointer;
	fast_d     sint15*                     _encode_frame_pointer;
	parm_d     char                        _parm__sdp_g726_40_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      sint15                      _v34_rx_Y0_m;
	shared_d   sint15                      _default_w;
	var_d      uint16                      _tx_dtmf_count;
	var_d      sint15                      _lec__span_size;
	const_d    fract                       _threshold_s;
	var_d      uint16                      _orig_v8_CJ_sent;
	var_d      uint16                      _ipod_iface_tx_next_seqnum;
	fast_d     fract                       _noise_simulator_rx;
	var_d      ufract                      _V90_RX_R_CORREL_THRESHOLD;
	debug_d    fract                       _fax_energy_detect_threshold;
	var_d      G722_2_Coder_State          _g722_2_encstruct;
	var_d      fract                       _p18_angle_store_real [3];
	fast_d     sint15                      _decode_frame [MAX_CODER_FRAME_SIZE];
	var_d      fract                       _energy_coefs_buffer_internal [5];
	parm_d     bool                        _parm__nat_stun_symmetric_deterministic_enable;
	const_d    fract                       _monitor_sample_slow_lo_absolute_threshold;
	var_d      fract40                     _v90_rx_spectrum_result_buffer_imag40 [V90_RX_NO_BINS];
	var_d      sint15                      _noise_del [MIX_ORD];
	var_d      fract CIRCULAR              _ph2_tx_interpolator_buffer_real [2*(PH2_TX_INTERPOLATOR_SIZE)];
	var_d      uint16                      _lec__td_tone_det_flag;
	parm_d     char                        _parm__mgcp_remote_domain_name [NET_DOMAIN_SIZEOF];
	var_d      uint16                      _v90h_rx_buffer1 [6];
	var_d      uint16                      _v90h_rx_buffer2 [6];
	var_d      fract                       _v34_tx_zn_local_real;
	debug_d    sint15                      _silence_average_counter;
	shared_d   sint15                      _dev_retry_count;
	parm_d     uint16                      _parm__ipbx_fc_call_waiting_enable;
	shared_d   int                         _debug_host_buffer_state;
	debug_d    fract                       _V34_BE_LOG_MINIMUM_GAIN;
	var_d      ufract                      _lec__rx_suppressor_decr;
	var_d      fract                       _sdt_dcd_threshold;
	var_d      int                         _number_bg_states;
	var_d      fract32                     _notch_datay32_120;
	var_d      sint15                      _ata_pfd_area;
	var_d      sint15                      _pcm_folding_remeasure;
	var_d      uint16                      _v34n_parm_ptt_lo_carrier_option;
	var_d      uint16                      _v34n_rx_carrier_frequency;
	const_d    fract                       _silence_adjust;
	var_d      uint16                      _extra_rate_reduction_poffset;
	parm_d     uint16                      _parm__cp_rd_qualify_metric;
	var_d      sint15                      _v34n_measured_roundtrip_delay;
	fast_d     sint15                      _encode_frame_active_indication;
	var_d      char                        _sip_sock_buffer [MAX_SIP_MESSAGE_SIZE];
	var_d      uint16                      _PH2_RX_OFFSET_LENGTH;
	var_d      uint16*                     _v34n_rx_INFO0_body [14];
	var_d      uint16                      _nat_ip_length; /* IP packet length */
	var_d      fract                       _p18_demod_imag;
	shared_d   sint15                      _dev_send_channel;
	var_d      sint15                      _v90_rx_dil_length;
	var_d      fract                       _data_9k6_lookup_internal_buffer [34];
	var_d      int                         _sonitrol_legacy_audio_mode;
	var_d      complex                     _edge_m1200;
	parm_d     bool                        _parm__ipbx_bridge_security_code_enable;
	var_d      sint15                      _frameSize;
	debug_d    fract                       _debug_fract1;
	var_d      sint15                      _parm__audio_agc_center_shift;
	debug_d    fract                       _debug_fract2;
	debug_d    fract                       _debug_fract3;
	debug_d    fract                       _debug_fract4;
	var_d      uint16                      _PH2_RX_PROBING_OFFSET_LENGTH;
	local_d    uint16                      _v34n_tx_asymmetric_option;
	debug_d    fract                       _debug_fract5;
	var_d      fract                       _lec__rx_input;
	var_d      uint16                      _sonitrol_line_enabled;
	var_d      sint15                      _v92_system_ID_modulo_nrm;
	debug_d    fract                       _debug_fract6;
	debug_d    sint15                      _V34_RESYNC_PERCENT_THRESHOLD;
	var_d      uint16                      _v90_rx_dil_sp_mask;
	debug_d    fract                       _debug_fract7;
	parm_d     uint16                      _stat__watchdog_timer_reset;
	debug_d    fract                       _debug_fract8;
	var_d      sint15                      _phone_key_debounce_count;
	debug_d    fract                       _debug_fract9;
	parm_d     bool                        _parm__radio_handset_continuous_transmit_enable;
	var_d      nat_tab_t                   _nat_translation [NAT_TRANSLATION_LIST_ENTRIES]; /* Translation table entries */
	var_d      sint15                      _lookback_input_imag;
	var_d      uint16                      _tst_test_flag;
	debug_d    sint15                      _silence_output;
	var_d      sint15                      _asm_decode_within_g711;
	var_d      uint16                      _v90_rx_s_value;
	parm_d     bool                        _parm__audio_monitor_rx_enable;
	shared_d   uint16                      _sonitrol_lc_type2_shutdown;
	var_d      sint15                      _saved_remote_echo_value;
	var_d      fract                       _gpf_RLgain;
	parm_d     bool                        _parm__ata_configuration_update_from_sip;
	var_d      sint15                      _enc_freq_prev [MA_NP][M_LP];
	debug_d    fract                       _CONVERT_AGC_1_GAIN_MAX_LOG;
	const_d    sint15                      _ANSAM_TRACKING_LIMIT;
	var_d      uint16*                     _v34n_tx_INFO1c_body [22];
	parm_d     char                        _parm__sip_remote_user_name [STRSIZE_64]; /* remote host/dialed party configuration */
	var_d      uint16                      _v8_tx_QC_data_octet;
	parm_d     uint16                      _parm__ipbx_fc_priority_forward_enable;
	parm_d     uint16                      _parm__ipbx_fc_unassigned_76;
	var_d      const sint15 *              _v34_frame_rx_save_bit_parse_pointer_bits;
	var_d      fract                       _ph2_ac_sample_buffer [2*(PH2_AUTOCORREL_BUFFER_LENGTH)];
	var_d      const struct sip_form_string_names * _sip_form_strings;
	persist_d  uint16                      _ph2n_rx_2743_option;
	parm_d     uint32                      _stat__nat_wan_tcp; /* WAN to LAN receive TCP packet type counter */
	parm_d     struct tone_descriptor      _parm__ipbx_reorder_tone;
	parm_d     uint16                      _parm__v92_MH_information;
	var_d      uint16                      _legacy_alarm_count;
	var_d      ufract                      _tx_bpf_gain_adjust;
	parm_d     bool                        _parm__dtmf_generate_abcd;
	fast_d     uint16                      _parm__dpbx_led_and_mask;
	var_d      sint15                      _v90_shape_shift_count_limit;
	var_d      fract                       _cc_rx_ANAL_DC_real;
	var_d      bool                        _ph2n_rxtx_v92_enable;
	var_d      fract                       _fsk_ANSam_deviation;
	shared_d   uint16                      _wiznet_shutdown_flag;
	var_d      call_info_t                 _parm__ipbx_outgoing_call_history [IPBX_HIST__OUTGOING_NO_OF];
	var_d      sint15                      _tone_priority_gen_count;
	parm_d     uint16                      _parm__mpeg4_quantization_number;
	var_d      mgcp_call_t                 _mgcp_conference_call;
	stat_d     sint15                      _stat__speech_dec_silence_active;
	var_d      sint15                      _v34_tx_4D_indicator;
	local_d    uint16                      _res_r;
	var_d      uint16                      _PCM_LEN_8K0_EQC_TRN1A_5TH;
	var_d      sint31                      _picp_last_entry_time;
	var_d      sint15                      _asm_encode_rtp_ans_prev;
	var_d      sint15                      _PH2P_ANAL_TEST_PREEMPH_VALUE;
	debug_d    bool                        _v34s_special_startup;
	local_d    uint16                      _v34n_rx_auxiliary_channel;
	var_d      sint15                      _act_min_sub [ENH_VEC_LENF];
	parm_d     uint16                      _parm__sdp_g729b_codec_dyn_pt;
	var_d      phase_t                     _ANSam_delta_phase;
	parm_d     sint15                      _parm__g722_reset_flag_old;
	var_d      sint15                      _Acf [SIZ_ACF];
	var_d      fract*                      _g711_rx_cng_frame_pointer;
	var_d      fract                       _monitor_sample_agc_2_relative_threshold;
	var_d      fract                       _ANSam_magnitude_lpf;
	var_d      sint15                      _l_refl_coef [1];
	parm_d     bool                        _parm__sip_notify_authentication;
	var_d      nat_frag_t                  _nat_fragment [NAT_FRAGMENT_LIST_ENTRIES]; /* Fragmentation translation array */
	var_d      fract                       _v34n_tx_optional_gain;
	var_d      uint16*                     _v90n_rx_INFO1a_body [7];
	parm_d     uint16                      _parm__ipbx_fc_caller_id_outbound_enable_once;
	debug_d    sint15                      _ec_ztrain_shift_slew_remote;
	fast_d     uint16                      _dpbx_key_debounce_count;
	shared_d   bool                        _parm__ipbx_do_not_disturb_mode;
	var_d      fract                       _ph2p_anal_variance_02_table [PH2P_NO_PREEMPHASIS];
	var_d      struct iface *              _nat_wan_ifp; /* Iface pointer to WAN device */
	var_d      uint16                      _ipod_command_ec_config;
	parm_d     uint16                      _stat__vpcm_coding_law;
	parm_d     bool                        _parm__sip_invite_authentication;
	shared_d   uint16                      _sonitrol_system_startup_complete;
	var_d      pcm_ec_slew_calculations_t  _pcm_eq_fb_slews;
	var_d      fract32                     _ptloop_angle32;
	var_d      sint15                      _asm_encode_buffer_pending;
	var_d      fract                       _pcm_AL_MSE_value;
	var_d      fract                       _THD_sum_L1_magnitude;
	var_d      uint16                      _local_buffer_pointer_rear;
	var_d      sint15                      _v34_rx_pn_tilde_imag;
	persist_d  sint15                      _ph2n_probing_L2_SE_power_adjust;
	var_d      sint15                      _parm__speech_rtp_jitter_buffer_bypass;
	var_d      sint15                      _constel_counter;
	var_d      uint16                      _v90n_rx_data_rate; /* 0 = cleardown, 1-22 data rates */
	fast_d     uint16                      _v34_rx_trellis_new_scores [16];
	var_d      fract32                     _ph2p_fefo_dw_k_buffer32 [PH2P_FEFO_BIN_COUNT];
	var_d      uint16                      _v90n_parm_dpcm_data_rate_option [2];
	parm_d     uint16                      _parm__vpcm_reference_point;
	var_d      sint15                      _v29_anti_lock_count;
	var_d      fract                       _v90_rx_DIL_done_flag;
	var_d      uint16                      _ph2p_anal_maxrates_14_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _v90n_rx_shaping_lookahead; /* 0 - 3 = Requested lookahead */
	parm_d     uint32                      _stat__nat_rcv_end_point; /* LAN to WAN receive end-point packet exit counter */
	var_d      sint15                      _lag0q_s [NF600+1];
	const_d    phase_t                     _ANSAM_DELTA_PHASE_LIMIT;
	var_d      bool                        _cid_signal_active;
	parm_d     uint16                      _parm__rtp_public_external_port_min;
	var_d      sint15                      _scrambler_match_count;
	var_d      sint15                      _ph2_rx_checker_count;
	var_d      uint16*                     _v34n_tx_MP1_body [30];
	var_d      uint32                      _speech_direct_playback_size;
	var_d      fract                       _tmp_half_energy;
	var_d      uint16                      _phone_key_matrix;
	parm_d     char                        _parm__ata_configuration_success_message [ATA_MESSAGE_SIZEOF];
	fast_d     sint15                      _parm__faxdet_v21_decrement;
	var_d      uint16                      _v34_frame_rx_calculated_crc;
	parm_d     bool                        _parm__net_lan_pppoe_pap_enable;
	var_d      uint16                      _v90_tx_send_RxN_sequence_flag;
	var_d      uint16                      _v90_rx_RBS_adjust_enable;
	var_d      fract                       _cc_rx_S_last_energy_log [3];
	var_d      fract                       _g722_d4l_oldrl;
	var_d      uint16                      _v90n_tx_maximum_power;
	var_d      fract                       _ph2_dummy_loopback_real;
	const_d    uint16                      _v92n_tx_max_coefs_section; /* INFO1a */
	var_d      uint16                      _phase2;
	var_d      fract                       _pcm_maximal_value;
	var_d      fract                       _lec__data_buffer [2*LEC__BUFFER_SIZE];
	var_d      fract32                     _v34_rx_qn_save1_coef_real32 [V34_NO_QN_COEFS];
	parm_d     uint16                      _parm__sip_timer_registration_retry;
	var_d      fract32                     _notch_datay32_180;
	var_d      fract32                     _lec__td_err_sum32;
	var_d      uint16*                     _v34h_rx_control_next_pointer;
	var_d      sint15                      _ph2p_fefo_bin_step;
	fast_d     int                         _dc_offset_counter;
	var_d      sint15                      _pcm_rx_clock_phase_ph3;
	parm_d     uint32                      _stat__nat_wan_ip_tunnel; /* WAN to LAN receive IP tunneling packet type counter */
	var_d      uint16                      _v34n_rx_control_channel_data_rate;
	fast_d     uint16                      _vppn_device_registration_id_index;
	var_d      sint15                      _sint15_input_limit;
	var_d      sint15                      _v90_tx_s_shape_offset;
	fast_d     fract*                      _tx_passband_coef_pointer;
	const_d    fract                       _train_on_data_16_slew;
	shared_d   bool                        _dev_poh_delay [NUMBER_OF_LINES_PER_DSP];
	persist_d  uint16                      _ph2n_rx_lo_3000_option;
	var_d      sint15                      _dgi_count [TOTAL_SLOT];
	shared_d   int                         _sample_interrupt_tx_offset;
	var_d      sint15                      _ph2n_tx_transmit_attenuation;
	parm_d     sint15                      _parm__codec_ring_detect_threshold;
	fast_d     uint16                      _parm__dtmf_record_prevention;
	var_d      fract                       _affine_imag;
	var_d      sint15                      _l_bpfsp [NUM_BANDS*(PITCH_FR - FRAMESIZE)];
	var_d      sint15                      _v34n_rx_TRN_length;
	var_d      sint15                      _v34h_rx_Q_n;
	var_d      sint15                      _qk_global [ENH_VEC_LENF];
	parm_d     char                        _parm__mgcp_default_display_name [STRSIZE_64]; /* universal display name.  Could be different per provider */
	var_d      fract                       _sequence_outband_s_level;
	parm_d     uint32                      _stat__net_enet_rcv_alloc_fails;
	var_d      fract                       _convert_gain_input_log;
	var_d      uint16                      _v90n_rx_silence_option; /* 0 = normal, 1 = silence */
	var_d      const char *                _content_parser_error_msg;
	var_d      uint16                      _v34f_recp_enable_E_send_flag;
	parm_d     struct tone_descriptor      _parm__ipbx_busy_tone;
	var_d      uint16                      _parm__ooma_conf_press_time;
	var_d      uint16                      _v90_frame_rx_JD_found;
	coef_d     fract                       _lec__adj_buffer [LEC__BLOCK_SIZE];
	var_d      event_t                     _bg_task_event;
	var_d      uint16                      _v90n_tx_training_redundancy; /* 0 - 3 = number of redundant bits */
	var_d      sint15                      _pcm_eq_ep_slew_shift;
	debug_d    sint15                      _ec_ztrain_shift_slew_local;
	var_d      fract                       _cc_rx_ANAL_prev_AGC2_log;
	var_d      sint15                      _codewd_13x9 [13];
	parm_d     char                        _parm__net_syslog_server [NET_DOMAIN_SIZEOF];
	debug_d    uint16                      _V34S_ANSW_8K0_3RT_SNend_to_Edet;
	var_d      fract                       _ph2p_anal_gain_average;
	var_d      sint15                      _clock_info_poffset;
	fast_d     sint15                      _encode_octet_cnt;
	var_d      fract                       _ph2_rx_checker_energy;
	var_d      fract                       _group_lists_internal_buffer [88];
	var_d      uint16                      _legacy_rx_duplicate_data [SSP_BUFFER_SIZE];
	var_d      pitTrackParam               _pitTrack_global [TRACK_NUM];
	shared_d   uint16                      _sonitrol_CS_address [4];
	parm_d     sint15                      _parm__headset_tx_gain;
	var_d      sint15                      _predicted_rx_xn_B1_real;
	const_d    uint16                      _fax_v21_holdoff_length;
	var_d      uint16                      _bg_kernel_anomaly;
	var_d      uint16                      _extra_rate_reduction_counter;
	parm_d     bool                        _parm__codec_line_in_use_inhibit;
	debug_d    bool                        _baud_tx_parity_stick;
	var_d      sint15                      _v34_bulk_extra_local_offset;
	var_d      int                         _lec__tec_error_offset;
	fast_d     uint16                      _sart_tx_data_unit;
	var_d      sint15                      _parm__speech_rtp_enc_frame_cnt;
	var_d      uint16                      _local_buffer_pointer_size;
	var_d      int                         _g722_d4l_sg [2];
	parm_d     uint16                      _parm__jpeg_auto_capture;
	fast_d     uint16                      _dtmf_clamp_enabled;
	var_d      fract                       _g722_d4l_al1;
	var_d      fract                       _lec__probe_nlp_input;
	debug_d    sint15                      _silence_state;
	stat_d     sint15                      _stat__speech_enc_frame_mtr;
	var_d      fract                       _g722_d4l_sl;
	var_d      fract                       _g722_d4l_al2;
	fast_d     sint15                      _parm_enc [MAX_CODER_PARM_SIZE];
	local_d    uint16                      _parm__ipbx_mode;
	parm_d     uint16                      _parm__pump_diag_event;
	parm_d     bool                        _parm__mgcp_rsip_keepalive;
	var_d      uint16                      _v34h_tx_buffer [16];
	var_d      uint16                      _stat__oicp_ved_key_state;
	var_d      struct quant_param          _quant_par;
	shared_d   uint16                      _stat__led_slow_flash_mask;
	var_d      uint16                      _lec__2100_disabled;
	stat_d     uint16                      _stat__dm_carrier_code;
	var_d      fract                       _ph2p_anal_log_B_buffer [PH2P_NO_PREEQ_BINS];
	var_d      sint15                      _synth_buf [L_FRAME+M_LP];
	local_d    fract                       _sdt_angle_store_complex [6];
	var_d      uint32                      _v34h_tx_g8_table [276];
	shared_d   bool                        _parm__ipbx_message_waiting;
	const_d    ufract                      _V34_QN_UPDATE_MEDIUM_SLEW;
	var_d      sip_call_t                  _sip_parser;
	local_d    uint16                      _parm__voip_provider_default [NUMBER_OF_LINES_PER_DSP];
	var_d      sint15                      _ph2p_anal_start_bin;
	local_d    fract CIRCULAR              _fsk_interpolator_buffer_imag [2 * C7K2_FSK_RX_INTERPOLATOR_SIZE];
	debug_d    uint16                      _V34S_RUN_V0_M_ERROR_LIMIT;
	var_d      fract                       _ph2n_probing_adj_Whi;
	parm_d     char                        _parm__mgcp_sdp_session_name [STRSIZE_32];
	debug_d    fract                       _V34_BE_LOG_MAXIMUM_GAIN;
	parm_d     uint16                      _parm__pump_data_modes;
	var_d      uint16                      _v90n_rx_attenuation; /* TX/Codec TX signal RMS in unsigned 3.13 */
	local_d    bool                        _parm__ipbx_zoom_alarm_service;
	var_d      sint15                      _AC_retry_count;
	var_d      sint15                      _l_prev_tilt;
	const_d    fract                       _dgidect_tune_echo_level;
	var_d      sint15                      _picp_edit_position;
	var_d      sint15                      _g723_extra;
	parm_d     char                        _parm__ata_options_domain_name [NET_DOMAIN_SIZEOF];
	var_d      sint15                      _ANSam_cycle_count;
	const_d    uint16                      _fax_send_length;
	var_d      fract  CIRCULAR             _v92_system_ID_buffer [V92_SYSTEM_ID_SIZE*2];
	var_d      sint15                      _v34_tx_xn_imag;
	var_d      uint16                      _pcm_disc_slot_match_value;
	persist_d  uint16                      _ph2n_rx_hi_3000_option;
	var_d      fract                       _half_input_sample;
	var_d      sint15 CIRCULAR             _v34_tx_qn_remote_buffer_real [2*V34_NO_QN_COEFS];
	fast_d     ufract                      _parm__hw_tx_gain_correction;
	var_d      sint15                      _cc_tx_passband_coef_poffset;
	var_d      sint31                      _ac97_rx_dma;
	parm_d     sint15                      _parm__g722_mode_old;
	shared_d   uint16                      _mpi_status_mask [NUMBER_OF_LINES_PER_DSP];
	var_d      sint15                      _vad_flag;
	var_d      fract                       _lec__alpha_value;
	var_d      fract                       _v34_equalizer_agc_gain;
	var_d      uint16                      _tx_dtmf_detect_count;
	var_d      fract                       _baud_timing_buffer [2];
	fast_d     fract CIRCULAR              _rx_rate_conv_data_buffer [2 * RATE_CNV_RX_SIZE];
	var_d      fract                       _g722_dec_shigh;
	var_d      fract                       _v92_rx_Lu_level;
	var_d      fract                       _v90_shape_1_min;
	var_d      sint15                      _dcd_level;
	var_d      sint15                      _test_tone_phase;
	shared_d   sint31                      _impedance_monitor_max_slow_lpf1;
	shared_d   sint31                      _impedance_monitor_max_slow_lpf2;
	fast_d     sint15                      _v34_rx_trellis_disable_equalizer_update;
	parm_d     sint15                      _parm__speech_g726_reverse_mode;
	var_d      fract                       _ph2n_probing_L1_log_N_buffer [PH2P_NO_TONES];
	var_d      uint16                      _sart_rx_count;
	var_d      sint15                      _mse_count;
	parm_d     uint16                      _parm__mgcp_end_point_naming;
	var_d      fract                       _energy_total_log;
	var_d      fract32                     _g711_last_out32;
	var_d      uint16                      _rx_count_test;
	parm_d     uint16                      _parm__pump_fax_mode;
	parm_d     char                        _parm__sdp_g722_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	const_d    fract                       _BAUD_PLL_CLOCK_SCALE;
	var_d      sint15                      _ph2_guard_tone_enable;
	var_d      const tone_detector_coef_t* _s1_detector_constants;
	shared_d   uint16                      _ipbx_gled_mask [NUMBER_OF_LINES_PER_DSP];
	parm_d     uint16                      _parm__ipbx_fc_disturb_accept_enable;
	var_d      fract                       _g168_exc_level;
	parm_d     uint16                      _parm__nat_udp_mode; /* NAT UDP operating mode */
	var_d      fract40                     _DIL_calculation_pad_mse40;
	var_d      bool                        _v34_rx_parm_use_precoding_in_renegotiation;
	debug_d    uint16                      _v17_short_state;
	fast_d     fract                       _tx_sample;
	var_d      sint15                      _w_fs [NUM_HARM];
	var_d      fract                       _v90_rx_R_correlation_buffer [V90_RX_R_CORRELATION_LENGTH];
	var_d      fract                       _notch_buffer [6];
	var_d      fract                       _v29_nrm_mse_32 [2];
	fast_d     rtp_packet_t*               _rtp_video_enc_packet;
	fast_d     int                         _baud_rx_cntr;
	var_d      fract40                     _energy_input40;
	parm_d     sint15                      _parm__slac_port_tx_gain;
	var_d      phase_t                     _V34_TX_CARRIER_FREQUENCY;
	var_d      uint16                      _ph2n_rx_v90_ITU_bits_reserved;
	var_d      sint15                      _v90_tx_ks_value;
	var_d      ufract                      _v34_local_echo_gain;
	var_d      sint15                      _cc_rx_lpf_poffset;
	parm_d     uint32                      _stat__nat_rcv_header_option; /* LAN to WAN receive IP header option packet exit counter */
	fast_d     fract                       _out_vxxmod_local;
	parm_d     uint16                      _parm__reset_flag_old;
	var_d      fract CIRCULAR              _rate_reduction_buffer_imag [2 * C7K2_FSK_REDUCE_LPF_SIZE];
	var_d      fract                       _v29_save_equalized_imag;
	fast_d     int                         _periodic_timer;
	var_d      fract                       _ph2p_L2_log_power_display_buffer [PH2P_NO_BINS_x2];
	parm_d     sint15                      _parm__codec_parallel_in_use_detect_method;
	var_d      sint15                      _v92_rx_un_perfect;
	parm_d     uint16                      _parm__ipbx_call_back_ring_wait_duration;
	var_d      uint16                      _orig_side;
	parm_d     uint32                      _stat__net_current_netmask;
	var_d      event_t                     _V92_EVENT__XX_RECEIVED;
	debug_d    sint15                      _V34_S_SIGNAL_DEGREE_WIDTH;
	var_d      sint15                      _f0q_s [NF600+1];
	var_d      fract                       _fsk_TONE_toneadjust;
	var_d      uint16                      _ipod_htd_fbdnt_semaphore;
	var_d      fract                       _input_sample_energy_log [2];
	shared_d   fract                       _impedance_monitor_coefs [IMPEDANCE_MONITOR_COEF_SIZE];
	var_d      sint15                      _ipbx_announce_ip_address_index;
	var_d      uint16*                     _v34h_tx_m_ijk_ring_index_pointer;
	shared_d   uint16                      _stat__led_slow_flash_state;
	var_d      uint16                      _send__v8__gstn_access;
	var_d      complex                     _equalizer_coef_complex [C7K2_RX_EQUALIZER_SIZE];
	var_d      uint16                      _v92_frame_rx_bits_per_baud;
	var_d      fract                       _ph2n_probing_adj_Wlo;
	parm_d     char                        _parm__net_assigned_cloned_mac_address [ATA_MAC_ADDRESS_SIZEOF];
	parm_d     uint16                      _parm__mbx_dma_timeout;
	var_d      sint15                      _ANSam_min_tracking_count;
	var_d      uint16                      _ipod_msg_tx_bfi;
	const_d    fract                       _threshold_aa;
	parm_d     struct sockaddr_in          _stat__sip_global_keep_alive_address;
	const_d    fract                       _threshold_ac;
	var_d      sint15                      _cc_tx_rate_poffset;
	parm_d     uint32                      _stat__nat_snd_rtp_end_point; /* LAN to WAN send RTP end-point packet exit counter */
	var_d      sint15                      _old_speech [L_TOTAL];
	debug_d    sint15                      _ec_fast_shift_slew_remote;
	var_d      sint15                      _f0q_mem_s;
	var_d      uint16                      _shadow_caller_name;
	var_d      sint15                      _rf_fm_last_word;
	var_d      sint15                      _PH2P_FEFO_DW_K_GAIN_MARGIN;
	parm_d     uint16                      _parm__net_router_circuit_default_dial_retry;
	var_d      fract                       _DIL_probing_pad_out_table [DIL_PROBING_PAD_LENGTH];
	var_d      sint15                      _tone_pattern_count;
	var_d      fract                       _ph2n_probing_adj_Wme;
	var_d      fract32                     _v34_rx_qn_save1_coef_imag32 [V34_NO_QN_COEFS];
	var_d      sint15                      _p18_reversal_timeout;
	var_d      fract                       _jitter_min_freq;
	parm_d     fract                       _parm__mse_limit1;
	var_d      bool                        _first_time_npp;
	parm_d     fract                       _parm__mse_limit2;
	var_d      fract   CIRCULAR            _pcm_rx_interpolator_buffer [2*PCM_RX_INTERPOLATOR_SIZE];
	var_d      uint16                      _v34_frame_rx_bit_buffer [11];
	parm_d     bool                        _parm__radio_transmit_test_tone_enable;
	var_d      uint16                      _ph2_tx_data_size;
	var_d      uint16                      _ph2n_tx_carrier [V34N_MAX_SYMBOL+1];
	parm_d     uint16                      _parm__nat_timeout_fragment; /* Idle seconds before fragment NAT timeout */
	var_d      uint16                      _v34h_rx_L_over_4_1_size;
	var_d      fract                       _cc_rx_ANAL_prev_DC_angle;
	var_d      sint15                      _dtmf_detect_valid;
	parm_d     uint32                      _stat__nat_wan_alg_delivers; /* WAN to LAN receive ALG delivers packet exit counter */
	var_d      bool                        _from_fax;
	debug_d    sint15                      _v8_tx_QC_repeat_count;
	var_d      uint16*                     _v92n_rx_SUVu_body [ 9];
	const_d    sint15                      _dcd_diversion_on_limit;
	parm_d     bool                        _parm__phone_memory_card_read_enable;
	local_d    fract CIRCULAR              _sdt_data_buffer_imag [C7K2_RX_SEQUENCE_DETECTOR_SIZE * 2];
	var_d      uint16                      _v90h_rx_residue;
	var_d      sint15                      _v92_rx_gain_adjust_exponent;
	fast_d     fract CIRCULAR              _rx_interpolator_buffer_imag [2 * C7K2_RX_INTERPOLATOR_SIZE];
	persist_d  uint16                      _ph2n_tx_2800_option;
	var_d      fract32                     _ph2p_fefo_dw_k_buffer_scaled32 [PH2P_FEFO_BIN_COUNT];
	const_d    fract                       _train_on_data_256_slew;
	var_d      sint15                      _v90_tx_k_output_offset;
	stat_d     uint16                      _stat__dm_state;
	parm_d     char                        _parm__ata_admin_name [ATA_ACCOUNT_SIZEOF];
	var_d      kernel_t                    _fg_kernel;
	var_d      uint16                      _rate_reduction_poffset;
	shared_d   char                        _mgcp_sock_buffer [MAX_MGCP_MESSAGE_SIZE];
	var_d      uint16                      _content_parser_error;
	var_d      uint16                      _parm__ooma_key_repeat_time;
	var_d      uint16                      _v92n_tx_train_8pt;
	var_d      sint15                      _rate_seq_counter;
	local_d    bool                        _parm__ipbx_distinctive_ring_last_call_service;
	var_d      fract                       _lec__td_error [LEC__TD_BLOCK_SIZE];
	var_d      uint16*                     _v92n_tx_CPd_body_constel [18];
	var_d      fract                       _ptloop_2nd_order_slew;
	var_d      fract                       _pcm_HI_peak_MSE_max [V34_TRN2_MSE_STACK_SIZE];
	var_d      fract *                     _ph2p_anal_variance_CS_table;
	var_d      fract                       _weightdenum_ilbc [NSUB_MAX*(LPC_FILTERORDER+1)];
	var_d      sint15                      _constel_midpoints_table_rbs [SIZE_MID_RBS];
	var_d      uint16                      _v34h_rx_b_bits_per_mapping_frame;
	var_d      uint16                      _v34n_rxtx_call_direction;
	shared_d   SPP_data_buffer_t *         _dprmbx_outgoing_queue;
	var_d      sint15                      _mem_zero [M_LP];
	var_d      uint16                      _ph4n_rx_answer_to_call_maxrate;
	parm_d     bool                        _parm__codec_disconnect_tone_3_enable;
	var_d      sint15                      _fsk_local_interpolator_poffset;
	fast_d     uint16                      _vppn_device_vanished_debounce;
	parm_d     uint16                      _parm__sdp_AVT_codec_dyn_pt;
	var_d      sint15*                     _lsp_new_ptr;
	var_d      sint15                      _g726_enc_coding;
	var_d      fract                       _v34f_eqc_co_DC_imag;
	var_d      uint16                      _ph2n_rx_v92_mode_bits;
	var_d      int                         _number_bg_tasks;
	parm_d     bool                        _parm__audio_monitor_tx_enable;
	debug_d    sint15                      _ec_ytrain_shift_slew_local;
	var_d      sint15                      _constellation_real;
	parm_d     struct tone_descriptor      _parm__ipbx_call_ring_default_tone;
	fast_d     uint16                      _asm_decode_within_bad_frame;
	var_d      uint16                      _ph2n_tx_acknowledge;
	coef_d     fract                       _lec__td_coef [LEC__TD_COEF_SIZE];
	var_d      fract                       _v34_TRN1_agc_value;
	shared_d   uint16                      _parm__net_debug_dsp_enable;
	var_d      bool                        _within_task_update;
	var_d      uint16                      _v90_frame_rx_index;
	parm_d     uint32                      _stat__nat_wan_forwards; /* WAN to LAN receive packet forward exit counter */
	var_d      fract                       _v92_system_ID_echo_DC_level;
	var_d      sint15                      _minspec_counter;
	var_d      int                         _rxs_aux_rx_baud [THREAD_BUFFER_SIZE];
	parm_d     uint16                      _parm__voip_melp_encode_rate;
	var_d      sint15                      _asm_decode_sample_unpack_mask;
	var_d      fract32                     _ph2p_fefo_ar_ai_stage1_buffer32 [2*(PH2P_FEFO_BIN_COUNT)];
	parm_d     char                        _parm__mgcp_default_user_name [STRSIZE_64]; /* lowest possible default login name.  Only used if there's no other choice */
	parm_d     char                        _parm__voip_preferred_codecs [STRSIZE_64]; /* List of codecs in preferred order (can be used for incoming selection reference independent of outgoing) */
	var_d      struct led_descriptor       _dpbx_led_special_on_pattern;
	parm_d     char                        _parm__sdp_g726_24_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      uint16                      _speech_direct_playback_frame_size;
	var_d      fract CIRCULAR              _g168_tx_cng_iir_data_buffer [G168_TX_CNG_LPC_ORDER];
	var_d      fract                       _phasedet_test_phase;
	var_d      fract                       _demod_leading_real;
	var_d      bool                        _stat__picp_dtmf_tone_on;
	parm_d     bool                        _parm__net_lan_heartbeat_signal_enable;
	var_d      sint15                      _enh_i;
	var_d      sint15                      _g711a_plc_frame_size;
	var_d      sint15                      _l_noise_gain;
	var_d      uint16                      _v34s_retrain_from_data_flag;
	var_d      sint15                      _angle_1st_data_predicted;
	var_d      sint15                      _ener [NB_GAIN];
	fast_d     sint15                      _parm__faxdet_ced_decrement;
	stat_d     uint16                      _stat__ipod_chan_id;
	var_d      sint15                      _count_update;
	var_d      sint15                      _v90_rx_delay_poffset;
	shared_d   mgcp_call_t                 _mgcp_all_endpoints_call;
	fast_d     sint15                      _v34n_tx_trellis_setting;
	var_d      fract                       _dtmf_row_harmonic;
	var_d      fract                       _v90_rx_R_expected_energy;
	var_d      uint16                      _v92_frame_rx_state;
	var_d      uint16                      _ph4n_tx_ITU_reserved;
	var_d      sint15 CIRCULAR             _v34_rx_qn_hat_buffer_imag [2*V34_NO_QN_COEFS];
	var_d      fract                       _constel_input0;
	var_d      fract                       _constel_input1;
	var_d      sint15                      _v90_tx_s_value;
	var_d      fract                       _constel_input2;
	var_d      int                         _lec__td_data_poffset;
	var_d      fract                       _constel_input3;
	var_d      uint16                      _sonitrol_remote_audio_port;
	var_d      sint15                      _agc_2_lpf_width;
	local_d    bool                        _parm__ipbx_polarity_connect;
	parm_d     struct rip_tar_s            _parm__net_router_rip [RIP_TABLE_ENTRIES];
	var_d      fract                       _rxs_demod_half_real [THREAD_BUFFER_SIZE];
	fast_d     fract                       _faxdet_value_ced;
	var_d      sint15                      _v90_rx_dil_count;
	var_d      sint15                      _degree_limit;
	parm_d     struct led_descriptor       _parm__ipbx_led_message_waiting;
	coef_d     fract                       _lec__tec_update [LEC__TEC_BLOCK_SIZE];
	var_d      fract                       _monitor_input_data [4];
	parm_d     uint16                      _parm__ipbx_fc_outgoing_block_disable;
	var_d      sint15                      _v34_tx_xn_remote_imag;
	var_d      uint32                      _asm_encode_rtp_cng_prev;
	var_d      uint16                      _v34h_rx_aux_restore_flag;
	var_d      sint15                      _picp_feature;
	var_d      sint15 CIRCULAR             _pcm_rx_8K0_transfer_buffer [2*16];
	var_d      uint16                      _stat__ipbx_device_state;
	var_d      fract CIRCULAR              _rx_interpolator_buffer [2 * C7K2_FSK_RX_INTERPOLATOR_SIZE];
	var_d      uint16                      _v90n_rxtx_v90_enable;
	shared_d   sint15                      _dev_rx_frame_index [NUMBER_OF_LINES_PER_DSP];
	var_d      ufract                      _v34n_rx_receive_level;
	debug_d    uint16                      _ph1n_rx_index_QTS;
	var_d      sint15                      _l_disp_del [DISP_ORD];
	var_d      uint16                      _v90n_rx_nominal_power;
	var_d      fract                       _pcm_rx_AGC2_log_adjust;
	var_d      sint15                      _count_sil;
	parm_d     bool                        _parm__mgcp_nat_keep_alive_enable;
	parm_d     bool                        _parm__nat_block_anonymous_probing; /* Block anonymous probing requests */
	var_d      sint15                      _g_voicedEn;
	var_d      bool                        _prev_uv_fsmag;
	var_d      sint15*                     _parm__speech_enc_asm_addr;
	var_d      sint15                      _g_bitNum;
	parm_d     struct tone_descriptor      _parm__ipbx_call_holding_tone;
	var_d      uint16                      _v90_dpcm_dil_ref [8];
	parm_d     uint16                      _parm__mf_tone;
	var_d      fract32                     _sense_silence_lpf2_32;
	parm_d     uint32                      _parm__mpeg2_sendto_port;
	var_d      sint15                      _ANSam_sample_count;
	fast_d     uint16                      _dpbx_led_pattern_queue_out;
	fast_d     sint15                      _asm_decode_packet_type;
	parm_d     bool                        _parm__ctcss_dec_enable;
	stat_d     uint16                      _stat__rx_v34_symbol_rate;
	var_d      sint15                      _gpf_iloop_length;
	var_d      sint15                      _noise_gain_melp_syn;
	var_d      uint16                      _uicp_access;
	parm_d     uint16                      _parm__ipbx_warm_line_duration;
	debug_d    sint15                      _V34_TRN2_MSE_STACK_COUNT;
	var_d      sint15                      _pcm_ec_limit;
	var_d      uint16                      _tx_wr_index;
	var_d      sint15                      _l_melp_v_cb_size [4];
	var_d      rtp_stream_t                _parm__rtp_stream;
	local_d    fract CIRCULAR              _sdt_data_buffer_complex [C7K2_RX_SEQUENCE_DETECTOR_SIZE * 2];
	var_d      ipbx_call_t *               _ipbx_call_hold;
	const_d    fract                       _dgidet_tune_max_spacing;
	var_d      sint15                      _nb_ener;
	var_d      thread_routine_t            _mg_run_entry_pointer;
	var_d      fract                       _ANSam_trace_mid_real;
	var_d      sint15                      _cc_tx_rate_counter;
	local_d    bool                        _parm__ipbx_call_back_service;
	var_d      sint15                      _g_bitBufSize;
	var_d      uint16*                     _v90_frame_rx_cp_body_start [32];
	var_d      uint16                      _dtmf_packet_on;
	var_d      int                         _gip [2][MBEST_GAIN];
	parm_d     uint16                      _parm__codec_disconnect_tone_2_duration;
	var_d      int                         _giq [2][MBEST_GAIN*N76ST1];
	var_d      sint15                      _lec__nlp_quiet_counter;
	parm_d     char                        _parm__net_assigned_router_name [ATA_ROUTER_NAME_SIZEOF];
	var_d      uint16                      _phone_power_switch_debounce_count;
	var_d      sint15                      _parm__speech_ip_generic_info;
	var_d      sint15                      _bpfdelout [NUM_BANDS][BPF_ORD];
	parm_d     struct tone_descriptor      _parm__ipbx_message_waiting_ring_splash_tone;
	var_d      sint15 CIRCULAR             _v92h_rx_K_frame [2*V92_LEN_8K0_DATA_FRAME];
	var_d      bool                        _ata_check_boot;
	var_d      uint16                      _asm_decode_lb_started;
	var_d      sint15                      _g711a_plc_poverlap;
	var_d      sint15                      _decode_frame_size;
	var_d      sint15                      _parm__speech_ip_source_addr [2];
	parm_d     uint16                      _stat__phone_ptt_state;
	var_d      uint16                      _parm__tripwire_monitor_length;
	parm_d     uint32                      _stat__nat_rcv_forwards; /* LAN to WAN receive packet forward exit counter */
	var_d      fract                       _phasedet_cos_value;
	var_d      fract                       _g711a_plc_buffer_out [G711_PLC_MAX_FRAME_SIZE];
	shared_d   uint32                      _parm__orc_ip_address;
	var_d      sint15                      _current_output_imag;
	var_d      fract                       _g711_rx_vad_level_mean_msw;
	var_d      sint15                      _v34_tx_pn_remote_real;
	const_d    sint15                      _dcd_diversion_off_limit;
	var_d      fract32                     _equalizer_coef_real32 [xV34_XX_EQUALIZER_TAPS];
	fast_d     sint15                      _encode_frame_sample_counter;
	var_d      sint15                      _phone_headset_tx_volume;
	var_d      uint16                      _stat__audio_codec_model;
	var_d      sint15                      _detect_rate_reduce_counter;
	var_d      fract                       _v34_renego_prev_real;
	fast_d     phase_t                     _modulator_increment;
	var_d      uint16                      _lookback_codeword;
	parm_d     uint32                      _parm__camera_baud_rate;
	var_d      sint15                      _lec__peak_activity_counter;
	var_d      plcpc_data_t                _speech_plcpc_data;
	var_d      sint15                      _ph2_rx_checker_bpf_offset;
	const_d    sint15                      _PH2S_INFO0_ACK_LIMIT;
	var_d      fract CIRCULAR              _goertzel_buffer [MAX_GOERTZEL];
	var_d      fract                       _fsk_local_interpolator_buffer_gain [C7K2_FSK_TX_INTERPOLATOR_SIZE * 2];
	parm_d     sint15 *                    _parm__pcm_playback_intro_bufferp;
	parm_d     uint32                      _stat__net_enet_wtol_passthrough;
	parm_d     uint16                      _parm__ipbx_fc_call_waiting_disable;
	var_d      ufract                      _g711_rx_vad_level_kf;
	fast_d     sint15                      _v34_rx_trellis_s_2m_1_table [4 * 3];
	const_d    fract                       _ANSAM_MAGNITUDE_LIMIT;
	parm_d     char                        _parm__sdp_gsm_fr_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      uint16                      _pushed_equalizer_poffset;
	var_d      sint15                      _parm__speech_rtp_encode_audio_packet_type;
	var_d      fract32                     _fax_error_mse32;
	var_d      fract                       _v34n_tx_required_gain;
	var_d      sint15                      _postLPFOutHis_hi [2];
	var_d      uint16                      _shared_btlz_tx_index;
	var_d      fract                       _pcm_btr_gain_normalize;
	parm_d     uint16                      _parm__nat_timeout_tcp_closed; /* Idle seconds before closed TCP NAT timeout */
	var_d      ufract                      _g711_rx_vad_level_kr;
	var_d      ufract                      _v34n_rx_inverse_gain_adjust;
	persist_d  uint16                      _ph2n_rx_lo_3200_option;
	fast_d     sint15                      _rate_reduction_counter;
	debug_d    uint16                      _dt_active_change;
	var_d      uint32                      _asm_encode_rtp_dtmf_start;
	var_d      sint15                      _dcd_integration_time;
	var_d      uint16*                     _pold_scores;
	var_d      sint15                      _phase_hit_count;
	parm_d     uint16                      _parm__dm_v32_rate_en_mask;
	parm_d     uint16                      _stat__v92_upstream_robbed_bit_mask;
	var_d      fract                       _fract_output_real;
	parm_d     uint16                      _parm__ipbx_fc_distinctive_ring_enable;
	fast_d     int                         _baud_xx_data;
	var_d      uint16                      _v90n_tx_RBS_positions;
	debug_d    sint15                      _V34S_LEN_8K0_SPECIAL_LOCAL_TRAIN;
	var_d      sint15                      _parm__speech_ip_dest_addr [2];
	var_d      uint16                      _ph2_rx_checker_length;
	var_d      fract CIRCULAR              _lec__datamax_buffer [2* LEC__DATADLMAX_SIZE];
	shared_d   int                         _debug_host_buffer_chars;
	var_d      fract                       _ANSam_midpoint_value;
	var_d      fract                       _eqout_leading_delay_real;
	var_d      sint15                      _v34_rx_cn_imag;
	var_d      sint15                      _g711a_plc_erase_sample_cnt;
	var_d      uint16                      _dgidet_padrb_max_index;
	var_d      uint16                      _v34n_rx_probing_maxrate;
	shared_d   uint16                      _parm__dtmf_tone_off_time;
	var_d      sint15                      _parm__speech_rtp_dtmf_en;
	var_d      sint15                      _l_lsp_check [3];
	var_d      sint15                      _decode_frame_error_indication;
	var_d      uint16                      _v90n_rxtx_coding_law;
	var_d      uint16                      _FALL_catastrophic_flag;
	const_d    uint16                      _v17_capture_rate;
	var_d      fract                       _decision_pcm_output;
	var_d      fract                       _v34_tx_zn_remote_real;
	const_d    uint16                      _sart_rx_size;
	debug_d    uint16                      _ORIG_V8_CM_COUNT_NOM;
	var_d      fract                       _cc_rx_ANAL_BEn_real;
	var_d      fract                       _v34_TRN2_MSE_value;
	var_d      fract32                     _notch_datax32_120;
	var_d      int                         _sonitrol_ANI_DNIS_offset;
	var_d      uint16                      _v90n_rx_Uinfo_ucode; /* JO unused, #define DO_V90_DPCM? */
	var_d      char *                      _picp_list;
	debug_d    fract                       _V34_AB_SIGNAL_MIN_ENERGY;
	var_d      uint16                      _ipod_command_low_line_quality;
	debug_d    fract                       _ec_very_slow_slew;
	parm_d     bool                        _parm__ata_phone_lock_enable;
	debug_d    bool                        _v34s_reneg_test_resp_ignore_S;
	parm_d     sint15                      _parm__priority_pattern [TONE_PATTERN_COUNT + 1];
	parm_d     uint16                      _parm__pcm_playback_loop_mode;
	fast_d     phase_t                     _tx_clock_phase_local;
	var_d      uint16*                     _v90_frame_tx_cpt_body_start [32];
	fast_d     sint15                      _decode_first_frame;
	var_d      sint15                      _silenceEn;
	var_d      int                         _previous_call_id_index;
	parm_d     bool                        _parm__ata_configuration_update_on_reset;
	var_d      sint15                      _PH2P_POWR_NOISE_ADJ_EXPONENT;
	var_d      sint15                      _ph2n_rx_transmit_attenuation;
	var_d      fract                       _V90_RX_RETRAIN_Et_THRESHOLD;
	var_d      sint15                      _pcm_ec_total_taps;
	fast_d     int                         _fg_event_insert;
	var_d      uint32                      _v34h_rx_z8_table [276];
	debug_d    sint15                      _V34S_AGC_1_SETTLE_TIME;
	var_d      SAA7115_ConfParams          _saa7115_globalptr;
	local_d    uint16                      _v34n_rx_asymmetric_option;
	shared_d   sint15                      _default_w0;
	fast_d     sint15                      _asm_decode_default_frame_size;
	parm_d     uint16                      _parm__mgcp_nat_keep_alive_interval;
	debug_d    sint15                      _V34_S_SIGNAL_2T_LIMIT;
	fast_d     uint16                      _rx_rate_conv_offset;
	var_d      fract                       _pcm_tx_power_log_prev;
	parm_d     uint16                      _parm__sart_rx_mode;
	fast_d     uint16                      _asm_stream_fill_cnt;
	var_d      fract                       _detect_v21_detect_biquad_data [6];
	parm_d     uint16                      _parm__pcm_playback_mode;
	debug_d    fract                       _V34_S_SIGNAL_MIN_ENERGY;
	var_d      fract                       _ph2_tx_passband_buffer [2*(PH2_TX_DATA_SIZE+16)];
	var_d      sint15                      _sh_sumAcf [NB_SUMACF];
	var_d      fract                       _pcm_LO_MSE_value;
	local_d    bool                        _parm__ipbx_speed_dial_service;
	var_d      sint15                      _ph2_guard_counter;
	var_d      uint16 CIRCULAR             _v92_system_ID_codes [V92_SYSTEM_ID_SIZE*1];
	debug_d    sint15                      _ec_xtrain_shift_slew_local;
	var_d      event_t                     _pattern_type;
	var_d      sint15                      _v34_rx_yn_tilde_real;
	var_d      uint16                      _v90n_parm_v90_enable;
	var_d      bool                        _tone_priority_series;
	var_d      uint16                      _shadow_line_sniff;
	var_d      fract *                     _ph2p_anal_log_E_plus_start;
	parm_d     uint32                      _stat__nat_wan_non_end_point; /* WAN to LAN receive non-end-point packet exit counter */
	var_d      uint32                      _next_rand_minstdgen;
	var_d      sint15                      _p18_2100_notch_poffset;
	var_d      fract                       _previous_sign;
	persist_d  uint16                      _ph2n_rx_hi_3200_option;
	parm_d     uint32                      _stat__nat_wan_ttl_discard; /* WAN to LAN receive TTL discard packet exit counter */
	debug_d    uint16                      _cp_previous;
	parm_d     bool                        _parm__sip_ringing_retransmit;
	var_d      uint16                      _sdt_bit_delay_buffer [4];
	var_d      fract                       _PH2P_ANAL_TEST_REQUIRED_GAIN;
	var_d      sint15                      _v34h_tx_J_super_frame_size_x2;
	var_d      sint15                      _v90_rx_timeout_count;
	var_d      uint16                      _v90n_parm_rx_reneg_16pt_option;
	var_d      const fract *               _ph2p_anal_preemph6_pointer;
	parm_d     char                        _parm__sdp_AVT_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	parm_d     sint15                      _parm__ipbx_fxs_cid_retry_count;
	var_d      sint15                      _postLPFOutHis_lo [2];
	var_d      nat_tab_t *                 _nat_free_list; /* Empty table list head */
	parm_d     fract                       _parm__dtmf_col_2nd_harm;
	parm_d     fract                       _parm__dtmf_rel_rev_twist;
	const_d    fract                       _ec_medium_slew;
	var_d      fract   CIRCULAR            _pcm_error_lpf_buffer [2*PCM_ERROR_LPF_BUFFER_SIZE];
	debug_d    uint16                      _sart_rx_release;
	var_d      uint16*                     _v90_frame_rx_dil_body_ucode [5];
	parm_d     uint32                      _stat__nat_snd_broadcasts; /* LAN to WAN send broadcast packet exit counter */
	var_d      uint16                      _v34h_rx_K_number_shell_bits;
	parm_d     uint16                      _parm__ipbx_fc_caller_redial;
	var_d      sint15 (*                   _pcm_x_law_encode_routine) (sint15 valu);
	var_d      fract                       _cc_rx_cx_real;
	var_d      sint15                      _v34_pp_equalized_data_poffset;
	parm_d     uint16                      _parm__fxpmp_modulation_code;
	var_d      uint32                      _v34h_rx_g4_table [70];
	local_d    bool                        _parm__ipbx_three_way_conference_service;
	parm_d     char                        _parm__sip_incoming_auth_password [STRSIZE_64];
	var_d      sint15                      _parm__speech_dtmf_min_duration; /* 50 */
	var_d      sint15                      _ANSam_count_2100;
	var_d      fax_save_state              _fax_save_state_0;
	var_d      fax_save_state              _fax_save_state_1;
	var_d      fract                       _v32_rx_lpf_buffer [C7K2_RX_LPF_SIZE];
	shared_d   sint15                      _gci_tx_frame_abort [NUMBER_OF_LINES_PER_DSP];
	var_d      uint16                      _v34h_baud_tx_flag_previous;
	var_d      fract                       _ph2_dummy_loopback_sample;
	var_d      uint16                      _V34S_LEN_8K0_1RT_MAX_1ST_SHORT;
	stat_d     uint16                      _stat__call_progress_tone_detect_mask;
	var_d      fract                       _ph2p_anal_variance_01_table [PH2P_NO_PREEMPHASIS];
	fast_d     sint15                      _asm_decode_type;
	var_d      ipbx_call_t *               _ipbx_call_conference;
	var_d      sint15                      _v34_tx_s_n;
	var_d      uint16                      _v92n_tx_constel_index [6];
	parm_d     uint16                      _parm__pulse_delay_time;
	debug_d    sint15                      _cp_state;
	var_d      uint16                      _sonitrol_line_sniff;
	var_d      sint15                      _act_min_shift [ENH_VEC_LENF];
	fast_d     uint16                      _vppn_device_temporary_id_index;
	var_d      fract                       _DIL_probing_pad_in_table [DIL_PROBING_PAD_LENGTH];
	const_d    sint15                      _fsk_TONE_increment;
	var_d      sint15                      _l_guard;
	const_d    uint16                      _v17_short_seg2_length;
	var_d      sint15                      _ph2p_fefo_powr_SE_gain_adjust;
	var_d      fract32                     _ph2p_fefo_delta_buffer32 [PH2P_NO_BINS];
	var_d      fract                       _echo_correlation;
	var_d      sint15                      _affine_update_poffset;
	var_d      phase_t                     _tx_clock_phase_slave;
	var_d      sint15                      _saved_v90trn_shift;
	var_d      uint16                      _ph2p_anal_maxrates_13_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16 *                    _dev_message_pointer;
	var_d      sint15                      _prev_pcof [MIX_ORD + 1];
	var_d      sint15                      _sample_rx_buffer [SAMPLE_BUF_RX_SIZE];
	var_d      fract32                     _ph2_ac_lpf_data_buffer32 [PH2_LPF_DATA_BUFFER_LENGTH];
	local_d    bool                        _parm__ipbx_message_waiting_service;
	parm_d     uint16                      _parm__sip_local_port;
	debug_d    sint15                      _V34_BE_POWER_SLEW;
	var_d      fsk_interpolator_buffer_t CIRCULAR _fsk_local_interpolator_buffer [C7K2_FSK_TX_INTERPOLATOR_SIZE / 2];
	var_d      uint16                      _v17_coef_phase;
	const_d    uint16                      _ANSW_V8_JM_COUNT_NOM;
	debug_d    bool                        _v34s_retrigger_retrain;
	parm_d     uint16                      _parm__video_encoding_mode;
	debug_d    fract                       _threshold_s1;
	var_d      uint16 *                    _v34_frame_tx_bit_pointer;
	debug_d    fract                       _threshold_s2;
	var_d      uint16                      _both_up;
	var_d      uint16                      _sys_number_missed_8K0_samples;
	parm_d     uint32                      _parm__mgcp_public_external_ip_address;
	var_d      sint15                      _ph2_AB_zero_count;
	var_d      fract                       _V34_SLEW_SIN_RETRAIN;
	var_d      uint16                      _mbx__htod [MBX_HTOD_SIZE];
	var_d      int                         _legacy_tx_in;
	var_d      uint16                      _rd_energy_detect;
	var_d      sint15                      _v34_resync_count;
	parm_d     uint16                      _parm__ipbx_fc_caller_id_outbound_enable;
	local_d    uint16                      _sart_rx_buffer [2 * SART_RX_BUFFER_SIZE];
	debug_d    fract                       _V34_BE2_SLEW_FAST;
	var_d      uint16                      _v92n_rx_max_coefs_section; /* INFO1a */
	var_d      sint31                      _ata_update_time_code;
	parm_d     bool                        _parm__nat_stun_enable;
	var_d      sint15                      _cc_rx_S_repetition_limit;
	parm_d     uint32                      _stat__nat_snd_pptp; /* LAN to WAN send PPTP packet type counter */
	parm_d     sint15                      _parm__slac_ring_amplitude;
	fast_d     sint15*                     _encode_bit_data_pointer;
	debug_d    uint16                      _V34S_RENEG_RESP_T_S_TO_SN_TIMEOUT;
	var_d      uint32                      _parm__tripwire_jpeg_record;
	fast_d     int                         _number_fg_states;
	parm_d     bool                        _parm__ata_ftp_server_enable;
	var_d      fract32                     _notch_datax32_180;
	parm_d     uint16                      _parm__ipbx_hangup_silence_duration;
	var_d      sint15                      _enc_lsp_new [M_LP];
	fast_d     uint16                      _rate_conv_modulo_counter;
	var_d      fract32                     _equalizer_coef_imag32 [xV34_XX_EQUALIZER_TAPS];
	local_d    char                        _parm__ipbx_input_pattern_pstn [IPBX_INPUT_PATTERN_SIZEOF];
	var_d      uint16                      _v90n_parm_coding_law;
	debug_d    uint16                      _v17_short_enable;
	parm_d     struct time_s               _parm__ata_current_time;
	var_d      uint16                      _ph1_x_law_index_to_code_convert;
	var_d      uint16                      _send_message_count;
	debug_d    sint15                      _state0_save_decimation_limit;
	var_d      fract32                     _v34_rx_yn_perfect_real_32;
	var_d      fract                       _V34_PRE_LO_EQUALIZER_COEFS [5];
	var_d      memory_direct_tx            _speech_direct_playback_function;
	var_d      sint15                      _noisespect [ENH_VEC_LENF];
	debug_d    uint16                      _crc_tx_flush_flag;
	var_d      phase_t                     _V34_RXI_PLL_COUNT;
	var_d      ufract                      _agc_2_normal_slew;
	shared_d   struct led_operands         _dpbx_led_pattern [LED_DEVICE_COUNT];
	debug_d    sint15                      _baud_tx_delete_bit_count;
	var_d      SPP_tx_transaction_t *      _ethernet_SPP_tx_queue;
	var_d      fract                       _ph2p_anal_log_S_buffer [PH2P_NO_TONES];
	fast_d     fract                       _AGC_2_REFERENCE_LEVEL;
	parm_d     uint16                      _parm__sdp_gsm_amr_codec_dyn_pt;
	debug_d    fract                       _threshold_sf;
	var_d      fract                       _pcm_btr_equalized_prev;
	var_d      uint16                      _v34n_parm_hi_carrier_option;
	parm_d     uint32                      _parm__nat_dmz_host_ip_addr; /* DMZ host IP address */
	var_d      fract                       _pcm_btr_perfect_prev;
	var_d      fract                       _THD_measurement_compare;
	var_d      uint16                      _ipod_ms_timer;
	debug_d    fract                       _dcd_energy_x;
	var_d      ufract                      _lec__rx_suppressor_incr;
	debug_d    fract                       _dcd_energy_y;
	var_d      fract                       _energy_receive_log;
	var_d      sint15                      _ptloop_monitor_count;
	parm_d     uint32                      _stat__nat_snd_ip_tunnel; /* LAN to WAN send IP tunneling packet type counter */
	var_d      ufract                      _ph2_guard_tone_gain;
	debug_d    fract                       _V34_BE2_SLEW_MEDIUM;
	var_d      g723_codcngdef_t            _g723_CodCng;
	var_d      const uint8*                _speech_direct_playback_data;
	debug_d    bool                        _baud_tx_parity_even_space;
	var_d      uint16**                    _v90_frame_rx_save_bit_parse_pointer;
	var_d      uint16                      _ipod_command_max_fax_rate;
	var_d      uint16                      _v34h_rx_m_count_4D;
	var_d      struct iface *              _nat_lan_ifp; /* Iface pointer to LAN device */
	var_d      ufract                      _lec__tx_suppressor_decr;
	var_d      bool                        _ata_need_cfg;
	var_d      phase_t                     _ph2_guard_tone_phase;
	var_d      uint16                      _control_message;
	var_d      uint32                      _descrambler32;
	var_d      uint16                      _legacy_periodic_count;
	var_d      thread_routine_t            _pcm_ec_routine;
	var_d      sint15                      _v34n_tx_qn_coef_imag [V34_NO_QN_COEFS];
	parm_d     struct tone_descriptor      _parm__ipbx_alternate_dial_tone;
	var_d      fract                       _ph2n_probing_Whi;
	var_d      uint16                      _ph2p_powr_L1_to_L2_delay_offset;
	var_d      fract32                     _v29_nrm_mse;
	debug_d    ufract                      _v34s_reneg_test_noise_level;
	parm_d     char                        _parm__net_router_globalstar_script [ATA_MODEM_SCRIPT_SIZEOF];
	var_d      sint31                      _trellis_equ_error_cnt;
	var_d      uint16*                     _v34h_tx_last_e0_pointer;
	var_d      sint15                      _lec__delay_size;
	var_d      sint15                      _temporary_buffer [8];
	var_d      phase_t                     _modulator_offset;
	var_d      sint15                      _affine_poffset_delay1;
	var_d      sint15                      _affine_poffset_delay2;
	parm_d     sint15                      _parm__codec_caller_id_type_2_mode;
	parm_d     char                        _parm__ata_timeserver_domain_name [NET_DOMAIN_SIZEOF];
	var_d      fract                       _v34_slew_cos_BE;
	debug_d    fract                       _debug_LEC__DELAY_SIZE;
	var_d      uint16                      _legacy_audio_transition_expected;
	var_d      fract                       _correct_precoder_imag;
	parm_d     sint15                      _parm__g722_reset_flag;
	var_d      uint16                      _ph4n_tx_receive_nonlinear;
	var_d      fract                       _error_real;
	var_d      uint16                      _picp_saved_digit;
	var_d      uint16 *                    _ph2p_anal_maxrates_CS_pointer;
	var_d      sint15                      _speech_overlap [ENH_OVERLAP_LEN];
	var_d      uint16                      _v90n_tx_receive_shaping_a1; /* Shaping parameter a1 in signed 2.6 or 10.6 */
	var_d      uint16                      _v90n_tx_receive_shaping_a2; /* Shaping parameter a2 in signed 2.6 or 10.6 */
	var_d      fract CIRCULAR              _v34_pp_equalized_data_imag [CC_RX_PP_ANALYSIS_SIZE * 2];
	parm_d     uint32                      _stat__net_enet_snd_broadcasts;
	var_d      SpeexBits                   _speex_bits;
	var_d      fract                       _v34_CONV_agc_value;
	fast_d     sint15                      _faxdet_v21_cnt;
	shared_d   uint16                      _dprmbx_catastrophic_failure;
	var_d      uint16                      _fsk_storage [ADDRESS_LIST_LENGTH];
	var_d      fract                       _temp1_ilbc_buffer [207];
	parm_d     uint32                      _parm__mpeg4_target_bit_rate;
	var_d      sint15                      _answ_v8_CJ_count;
	var_d      uint16                      _sart_rx_timeout_tmr;
	var_d      fract                       _agc_2_lpf [2];
	parm_d     uint32                      _stat__test_phone_key_register;
	var_d      sint15 CIRCULAR             _v34_rx_qn_buffer_real [2*V34_NO_QN_COEFS];
	var_d      uint16                      _v90_rx_p_frame [6];
	parm_d     bool                        _parm__net_dhcp_server_broadcast_enable;
	var_d      uint16*                     _v92n_rx_INFO1a_body [9];
	var_d      uint16                      _V90S_LEN_T_DIL_PROCESS_BLOCK;
	var_d      fract CIRCULAR              _v92_rx_Ru_pattern_buffer [2*6*1];
	var_d      fract CIRCULAR              _local_interpolator_buffer [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	parm_d     uint16                      _parm__sip_remote_port; /* port is only used if there's no provider.  Set */
	var_d      sint15                      _dec_old_exc [L_FRAME+PIT_MAX+L_INTERPOL];
	var_d      uint16                      _force_low_line_semaphore;
	var_d      fract*                      _holdbuff;
	parm_d     uint16                      _parm__codec_disconnect_voltage_duration;
	local_d    uint16                      _v34n_rx_data_rate_option;
	var_d      uint16                      _v90n_tx_receive_shaping_b1; /* Shaping parameter b1 in signed 2.6 or 10.6 */
	var_d      uint16                      _v90n_tx_receive_shaping_b2; /* Shaping parameter b2 in signed 2.6 or 10.6 */
	var_d      int                         _echo_canceller_display_decimate;
	parm_d     uint16                      _parm__voip_echo_canceller_enable;
	var_d      sint15                      _mem_syn [M_LP];
	var_d      sint15                      _test_tone_increment;
	local_d    fract CIRCULAR              _lec__delay_buffer [LEC__DELAY_SIZE];
	var_d      bool                        _v90h_rx_write_enable;
	var_d      uint16                      _lookback_base;
	var_d      sint15                      _g_bitBufSize12;
	var_d      uint16                      _previous_rx_baud; /* run on odd slots */
	var_d      sid_syncState               _amrsync_struct;
	var_d      phase_t                     _fsk_ANSam_phase;
	parm_d     bool                        _parm__ata_configuration_update_enable;
	var_d      sint15                      _v34_rx_predicted_V0_m_value;
	var_d      fract CIRCULAR              _silence_passband_buffer [2 * C7K2_TX_BPF_SIZE];
	coef_d     fract                       _lec__coef_buffer [LEC__DATA_SIZE];
	var_d      uint32 (*                   _v34h_rx_shaper_shellmap_routine) (uint16 *buffer, uint16 M_bits, uint16 g4_length);
	parm_d     uint32                      _stat__nat_wan_udp; /* WAN to LAN receive UDP packet type counter */
	var_d      uint16                      _v90h_tx_buffer [6];
	var_d      fract                       _phase_loop_real;
	parm_d     struct tone_descriptor      _parm__ipbx_input_error_tone;
	var_d      uint16                      _v34_frame_rx_sync_register;
	var_d      uint16                      _saved_v90trn_pad_detect;
	var_d      uint16                      _descrambler_output_shift;
	fast_d     sint15                      _decode_gain_exponent;
	var_d      sint15                      _monitor_ones_cntr;
	var_d      sint15                      _prev_sbp3;
	var_d      mse_struct                  _v34_MSE_stack;
	var_d      sint15                      _V90_APCM_DIL_LENGTH;
	var_d      uint16*                     _v90_frame_rx_dil_body_sp [2];
	var_d      int                         _current_bg_task;
	var_d      uint32                      _parm__speech_rtp_cng_delay;
	var_d      uint16                      _speech_direct_playback_fcnt;
	var_d      sint15                      _g_bitBufSize24;
	var_d      ufract                      _lec__alpha_calculation_ratio;
	var_d      uint16                      _v34h_rx_control_hi_frame [8];
	var_d      sint15                      _p18_exponent;
	var_d      uint16                      _v90n_rx_constel_codec [8*6];
	persist_d  fract                       _ph2n_probing_L2_log_P_buffer [PH2P_NO_TONES];
	parm_d     tone_detector_coef_t        _parm__tone_detectors [NUMBER_GENERAL_DETECTORS];
	parm_d     uint16                      _stat__phone_power_switch_state;
	var_d      uint16                      _v34h_rx_control_lo_frame [8];
	shared_d   sint15                      _lsp_cos [512];
	var_d      uint16 *                    _ph2p_anal_preemph_results_pointer;
	var_d      sint15                      _prev_uv_low_rate_chn_read;
	persist_d  uint16                      _ph2n_tx_lo_3000_option;
	var_d      fract                       _DIL_calculation_pad_gain;
	var_d      sint15                      _v34_rx_4D_indicator;
	var_d      fract                       _ph2n_probing_Wlo;
	var_d      fract                       _dgi_in0;
	var_d      uint16                      _v90n_rx_constel_codes [8*6];
	var_d      uint16*                     _v90_frame_rx_dil_body_tp [2];
	var_d      sint15                      _dgi_in1;
	var_d      sint15                      _dgi_in2;
	var_d      uint16                      _pattern_counter;
	const_d    uint16                      _fax_pause_length;
	var_d      phase_t                     _V34_RX_CARRIER_FREQUENCY;
	var_d      fract                       _jitter_jitter_limit;
	var_d      fract                       _ptloop_anti_oscillation_slew;
	parm_d     uint16                      _parm__sdp_NSE_codec_dyn_pt;
	var_d      uint16                      _parm__rtp_decode_gain;
	var_d      fract                       _PH2P_ANAL_DEMOD_ENERGY_LOSS;
	var_d      sint15                      _gpf_RLexp;
	parm_d     uint16                      _parm__v8__gstn_access;
	var_d      uint16                      _rd_energy_on_time;
	parm_d     uint16                      _parm__radio_key_selection;
	var_d      bool                        _fsk_run_data_sart;
	parm_d     uint16                      _parm__lec_nlp_control;
	var_d      sint15                      _pcm_rx_8K0_transfer_out_poffset;
	var_d      bool                        _dev_ring_minimum_duration;
	debug_d    uint16                      _ph2_rx_baud_shift_register;
	var_d      fract                       _ph2n_probing_Wme;
	var_d      sint15                      _decode_input_imag;
	var_d      sint15                      _gx_s [2*NF600];
	var_d      uint16                      _in_v32;
	debug_d    uint16                      _V90_TEST_LOG_INPUT_TIMING;
	var_d      uint32                      _encode_frame_start_timestamp;
	persist_d  uint16                      _v34n_tx_difference_option;
	var_d      uint16                      _send__v8__protocols;
	parm_d     uint16                      _parm__dtmf_detector_count;
	var_d      uint16                      _sonitrol_bad_checksum_count;
	var_d      fract                       _pcm_probe_real;
	local_d    uint16 CIRCULAR             _status_buffer [512*2];
	var_d      sint15                      _lec__controller_count;
	parm_d     char                        _parm__ata_admin_password [ATA_PASSWORD_SIZEOF];
	shared_d   uint16                      _parm__vppn_device_firmware_image [VPPN_DEV__SIZEOF_FIRMWARE_IMAGE];
	fast_d     uint16                      _asm_decode_within_frame;
	var_d      uint8                       _audio_device [32];
	var_d      sint15                      _codewd74 [7];
	var_d      sint15                      _fr_cur;
	fast_d     sint15                      _rx_rate_double_poffset;
	var_d      bool                        _vppn_device_memory_read;
	var_d      sint15                      _lsp_new_q [M_LP];
	var_d      uint16                      _v34n_parm_auxiliary_option;
	var_d      bool                        _v92_MH_response_ack_flag;
	local_d    bool                        _parm__ipbx_call_return_service;
	var_d      fract                       _convert_agc_2_input_log;
	var_d      uint16                      _timeout_sema;
	parm_d     struct led_descriptor       _parm__dpbx_led_ringing_or_waiting;
	local_d    bool                        _parm__ipbx_polarity_dial_done;
	fast_d     int                         _aux_tx_data;
	var_d      uint16                      _ph2_rx_data_size_1;
	var_d      phase_t                     _V34_RXI_PLL_HALF_ADJUST;
	var_d      uint16                      _parm__video_ssl_enable;
	var_d      sint15                      _handset_in_sample;
	var_d      sint15                      _dgidet_padrb_count [TOTAL_SLOT * STATISTIC_LEN];
	var_d      fract                       _v92_equalizer_input;
	var_d      sint15                      _codewd84 [8];
	var_d      fract                       _v90_rx_predicted_point;
	var_d      fract                       _demod_half_real;
	var_d      bool                        _event_dsp_uses_background;
	parm_d     uint16                      _parm__sdp_g729_codec_dyn_pt;
	parm_d     char                        _parm__ata_local_update_domain_name [NET_DOMAIN_SIZEOF];
	parm_d     char                        _parm__ata_firmware_failed_message [ATA_MESSAGE_SIZEOF];
	parm_d     sint15                      _parm__speech_g729parm_bitrev;
	var_d      sint15                      _l_pulse_cof [MIX_ORD +1];
	parm_d     char                        _parm__mgcp_endpoint_naming [STRSIZE_32];
	var_d      uint16                      _p18_poffset;
	parm_d     struct ring_descriptor      _parm__ipbx_call_pstn_ring_default;
	var_d      sint15                      _pcm_rx_2k_phase;
	var_d      uint16                      _stat__phone_paycard_state;
	parm_d     struct date_s               _parm__ata_provider_lock_expiration;
	var_d      fract                       _tst_saved_2k_dif;
	var_d      sint15                      _rx_freerun_clock_phase;
	stat_d     sint15                      _stat__speech_dec_sample_counter;
	var_d      fract                       _v29_rot_mse_32 [2];
	var_d      fract                       _jitter_1st_order_slew;
	var_d      int                         _pcm_tx_thread_control;
	var_d      uint16                      _tdv_index;
	var_d      sint15                      _v34_tx_qn_pointer;
	fast_d     fract                       _faxdet_threshold_absolute;
	var_d      fract                       _equalizer_raw_output_imag;
	var_d      fract                       _force_train_imag;
	var_d      sint15                      _saved_v90trn_offset;
	persist_d  uint16                      _ph2n_tx_hi_3000_option;
	debug_d    uint16                      _PH2S_LEN_T_TURNAROUND_DELAY;
	parm_d     uint16                      _parm__codec_audio_clamp_duration;
	var_d      uint16*                     _v90_frame_tx_codec;
	var_d      uint16                      _lim_r;
	var_d      sint15                      _RCoeff [MP1];
	var_d      uint32                      _nat_private_addr; /* Private IP adresss */
	var_d      fract40 CIRCULAR            _pcm_ec_conv_buffer40 [2*PCM_EC_CONV_SIZE];
	var_d      state_t                     _automode_modulation_state;
	var_d      fract                       _tmp_baud_sum_imag;
	parm_d     uint16                      _parm__vpcm_nominal_power;
	var_d      sint15                      _v34p_bg_sample_count;
	var_d      bool                        _prev_uv_flag;
	var_d      uint16*                     _v90_frame_tx_codes;
	var_d      struct melp_param           _prev_par_transcode;
	var_d      sint15                      _v34_rx_xn_hat_imag;
	var_d      uint16*                     _v92n_tx_CPd_body_modulus [18];
	var_d      fract                       _v92_system_ID_error_adj;
	var_d      uint16*                     _v90h_rx_buffer_load_pointer;
	shared_d   volatile int                _codec_int_state;
	var_d      uint32                      _nat_remote_addr; /* Destination IP adresss */
	var_d      uint16                      _ph2n_rx_v92_ITU_marks_reserved; /* INFO1a */
	var_d      uint16                      _test_input_chang;
	var_d      sint15                      _predicted_rx_xn_B1_P_x8;
	var_d      sint15                      _v34_tx_cn_imag;
	var_d      memory_direct_rx            _speech_direct_record_function;
	var_d      sint15                      _ph2p_bg_dlyd64_out_offset;
	fast_d     vocoder_t                   _vocoder_f;
	var_d      fract                       _V34_SLEW_SIN_BE2;
	shared_d   volatile uint16             _codec_control_word;
	parm_d     struct tone_descriptor      _parm__ipbx_call_back_ring_splash_tone;
	var_d      fract                       _equalized_complex [2];
	var_d      fract                       _tx_8K0_echo_sample;
	persist_d  uint16                      _ph2n_probing_use_shaping;
	var_d      fract                       _ph2p_anal_log_P_buffer [PH2P_NO_TONES];
	var_d      sint15                      _delta_level;
	parm_d     uint16                      _parm__selcall_enc_gain;
	var_d      fract CIRCULAR              _v34_rx_qn_perfect_buffer_imag [2*(V34_NO_QN_COEFS + 1)];
	var_d      sint15                      _prev_gain_err;
	var_d      sint15                      _btrec_phdet_state;
	var_d      fract32                     _lec__dc_offset32;
	var_d      sint15                      _v34_scheduled_retrain_in_seconds;
	parm_d     sint15                      _parm__slac_caller_id_type_2_mode;
	parm_d     uint32                      _stat__net_enet_snd_success;
	parm_d     struct sockaddr             _nat_arp_target; /* ARP target lookup address */
	fast_d     uint16                      _sart_rx_data_unit_1;
	fast_d     uint16                      _sart_rx_data_unit_2;
	var_d      sint15                      _v34s_run_holdoff_count;
	var_d      fract CIRCULAR              _p18_data_buffer_real [C7K2_RX_SEQUENCE_DETECTOR_SIZE * 2];
	const_d    uint16                      _v17_seg1_length;
	var_d      sint15                      _txs_output_sample [THREAD_BUFFER_SIZE];
	var_d      uint32                      _asm_encode_rtp_ans_start;
	var_d      uint16                      _ipod_rx_frame_report_seqnum;
	var_d      fract                       _v34n_rx_receive_gain;
	shared_d   sint31                      _dev_timed_event_period [NUMBER_OF_LINES_PER_DSP];
	parm_d     char                        _parm__sip_additional_accept_types [STRSIZE_256];
	var_d      bool                        _ph2_retrain_flag;
	var_d      int                         _legacy_tx_out;
	var_d      fract                       _ANSam_trace_magphase_mid_imag;
	var_d      uint16                      _ipod_msg_rx_vfd;
	debug_d    bool                        _baud_rx_parity_stick;
	var_d      fract32                     _v34_equalizer_agc_gain32;
	fast_d     sint15*                     _decode_bit_data_pointer;
	var_d      fract                       _ph2n_rx_preeq_gain;
	var_d      sint15                      _mem_lpc [NF600][LPC_ORD];
	parm_d     sint15                      _parm__ipbx_voice_tx_gain;
	fast_d     sint15                      _v34_rx_trellis_yn_poffset;
	var_d      sint15                      _pcm_probe_ecc_state;
	debug_d    fract                       _v34_equalizer_slew_data_slow;
	var_d      sint15                      _u_tmp [LPC_ORD + 1];
	var_d      uint16                      _legacy_rx_ack_sent;
	parm_d     bool                        _stat__net_pppoe_status;
	fast_d     uint16                      _asm_decode_cnt;
	var_d      sint15                      _v92_system_ID_code;
	var_d      uint16                      _ethernet_outgoing_count_flag;
	var_d      uint16                      _v27_tx_poly;
	var_d      sint15                      _v90_rx_s_input_offset;
	var_d      fax_save_state*             _fax_save_state_current;
	shared_d   uint16                      _dev_tx_frame [NUMBER_OF_LINES_PER_DSP*IPBX_DEV_MESSAGE_MAX_LENGTH];
	var_d      fract                       _dtmf_hpf_biquad_data [6];
	debug_d    bool                        _v34n_parm_error_recovery_enable;
	var_d      uint32                      _nat_public_addr; /* Public IP adresss */
	stat_d     uint16                      _stat__sart_tx_mode;
	var_d      fract32                     _ph2p_fefo_test_m_prime32;
	var_d      uint16                      _predicted_rx_xn_B1_disable;
	shared_d   int                         _impedance_monitor_decimation_counter;
	var_d      SPP_data_buffer_t *         _SPP_incoming_queue;
	var_d      sint15                      _stat__daa_debounce_count;
	parm_d     uint32                      _stat__nat_rcv_tcp; /* LAN to WAN receive TCP packet type counter */
	var_d      uint16                      _ph2n_rx_Uinfo_ucode;
	var_d      fract32                     _pcm_tx_hpf_fb32;
	persist_d  uint16                      _ph2n_rx_tx_3429_option;
	var_d      uint16                      _in_dtmf_early_detect;
	var_d      sint15                      _tonemute_delay_poffset;
	var_d      agc_data_t                  _audio_agc_data;
	debug_d    sint15                      _cp_keep_counter;
	var_d      complex CIRCULAR            _rx_interpolator_buffer_complex [2 * C7K2_RX_INTERPOLATOR_SIZE];
	parm_d     char                        _parm__mgcp_distinctive_ring_names [8][32];
	fast_d     vppn_packet_t *             _vppn_decode_packet;
	var_d      sint15                      _less_count;
	local_d    uint16                      _fg_svalue_queue [NUMBER_OF_FG_EVENTS];
	var_d      fract                       _v34_temp_hi_pre_emph_adjust_table [11];
	var_d      uint16                      _v34s_last_frame_was_an_MPA;
	var_d      uint16 *                    _dev_compare_pointer;
	var_d      fract                       _g168_exc_peak;
	var_d      sint15                      _sample_tx_buffer [SAMPLE_BUF_TX_SIZE];
	parm_d     uint16                      _parm__sdp_g726_40_codec_dyn_pt;
	var_d      mse_struct                  _pcm_HI_peak_MSE_stack [V34_TRN2_MSE_STACK_SIZE];
	var_d      fract CIRCULAR              _local_interpolator_buffer_real [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	var_d      uint16                      _parm__rtp_dtmf_playout_digit;
	var_d      uint16                      _v34n_data_rate_MAXIMUM [V34N_MAX_SYMBOL+1];
	parm_d     uint32                      _stat__net_enet_rcv_success;
	var_d      uint16                      _sonitrol_current_ring_count;
	var_d      fract                       _phasedet_sin_value;
	var_d      uint16*                     _v90h_rx_buffer_stream_pointer;
	var_d      sint15                      _rate_validation_cmp;
	var_d      fract                       _v21_detect_coefs_buffer_internal [10];
	var_d      char                        _picp_lcd_display_save_buffer [LCD_CHAR_ROWS][LCD_CHAR_COLS];
	var_d      uint16                      _tempmse;
	fast_d     sint15                      _v34_rx_trellis_yn_hat_poffset;
	fast_d     sint15                      _echo_canceller_poffset;
	shared_d   uint16                      _parm__vppn_device_firmware_length;
	local_d    uint16                      _sart_tx_buffer [2 * SART_TX_BUFFER_SIZE];
	parm_d     uint16                      _parm__mf_tone_on_time;
	var_d      sint15                      _good_pitch [NF];
	var_d      uint16                      _v90_dpcm_dil_first;
	var_d      uint16                      _v92n_rx_prefilter_fb_taps;
	var_d      sint15                      _v34_yn_equalized_imag;
	parm_d     uint16                      _parm__tel_digit;
	var_d      sint15                      _btrec_baud_coef_shift;
	var_d      timer_list_t                _bg_timer_list [NUMBER_OF_BG_TIMERS];
	var_d      uint16                      _next_80_ms;
	local_d    uint16                      _v34n_rx_use_shaping;
	var_d      sint31                      _saturation;
	var_d      sint15*                     _parm__speech_dec_asm_addr;
	var_d      uint16 *                    _nat_pkt_icmp_ptr; /* Pointer to ICMP header */
	local_d    bool                        _parm__ipbx_line_enable [NUMBER_OF_LINES_PER_DSP];
	debug_d    phase_t                     _V34_B_OVER_CK80;
	parm_d     sint15                      _parm__codec_disconnect_tone_2_bandwidth;
	fast_d     bool                        _vppn_device_command_send_end;
	var_d      sint15                      _v34_frame_tx_word_count;
	var_d      sint15                      _v90_rx_JE_detect_count;
	var_d      uint16                      _rd_trans2_count;
	parm_d     sint15                      _parm__codec_port_tx_gain;
	debug_d    sint15                      _overlay_8K0_timeout;
	var_d      fract                       _ph2n_probing_receive_preeq_level;
	var_d      uint16                      _nat_ip_header_size; /* IP packet header size */
	parm_d     struct tone_descriptor      _parm__ipbx_call_forward_ring_splash_tone;
	var_d      fract                       _cc_rx_equalizer_coef_real [CC_RX_EQUALIZER_SIZE];
	var_d      uint16                      _v34h_rx_residue_length;
	var_d      int                         _ipod_dth_coded_speech_length;
	const_d    sint15                      _monitor_decimation_limit;
	local_d    uint16                      _parm__ipbx_dial_speed_dial;
	stat_d     uint16                      _stat__ipod_mod_type;
	parm_d     char                        _parm__nat_turn_server_domain_name [NET_DOMAIN_SIZEOF];
	debug_d    bool                        _v34s_reneg_test_init_ignore_S;
	var_d      sint15                      _v34n_parm_sample_ec_update_increment;
	var_d      sint15                      _remote_ec_shift_slew;
	var_d      sint15                      _lec__datamax_half_counter;
	var_d      uint32                      _parm__speech_rtp_flow_tag;
	var_d      phase_t                     _add_deletes_per_baud;
	parm_d     uint16                      _parm__ipbx_fc_reserved_90;
	parm_d     uint16                      _parm__ipbx_fc_reserved_91;
	parm_d     uint32                      _stat__net_enet_rcv_errors;
	var_d      uint16                      _v34h_tx_L_over_4_1_size;
	debug_d    uint16                      _cp_active_change;
	var_d      sint15                      _v92_rx_yn_perfect;
	parm_d     uint16                      _parm__ipbx_fc_reserved_99;
	var_d      sint15                      _g711_rx_vad_hangover_counter;
	var_d      fract                       _demod_lagging_half_real;
	var_d      fract                       _v34f_eqc_initial_DC_mag_log;
	var_d      sint15                      _enc_past_qua_en [4];
	var_d      int                         _i_gain [N9+1];
	var_d      uint16                      _ph4n_tx_acknowledge;
	var_d      uint16 **                   _v34_frame_rx_bit_parse_pointer;
	fast_d     sint15                      _v34_rx_trellis_s_2m_0_table [4 * 3];
	debug_d    sint15                      _mark_counter;
	var_d      sint15 CIRCULAR             _v34_rx_qn_tilde_buffer_imag [2*V34_NO_QN_COEFS];
	const_d    fract                       _equalizer_slew_resync_fast;
	stat_d     uint16                      _stat__ipod_loopback_pattern;
	var_d      sint15                      _cc_rx_rate_poffset;
	stat_d     uint16                      _stat__ipod_dth_coder;
	var_d      uint16                      _timeout_clock;
	var_d      event_t                     _fg_status_event_queue [STATUS_BUFFER_SIZEOF];
	parm_d     uint32                      _parm__net_dhcp_server_ending_ip_address;
	var_d      fract32                     _lec__td_dat_sum32;
	var_d      uint16                      _parm__ooma_key_press_time;
	debug_d    fract                       _v34_equalizer_slew_B1_slow;
	debug_d    fract                       _V34S_FULL_PHROLL_THRESHOLD;
	var_d      fract                       _sdt_DC_angle_store_imag;
	persist_d  uint16                      _v34n_rx_CME_option;
	var_d      uint16                      _legacy_rx_duplicate_count;
	local_d    char                        _parm__ipbx_zoom_alarm_code_dial_pattern [IPBX_DIAL_STRING_SIZEOF];
	var_d      sint15*                     _new_speech;
	var_d      sint15                      _DIL_probing_RBS_slot_storage [6];
	var_d      sint15                      _sh_ener [NB_GAIN];
	var_d      sint15                      _constel_decisions_table_rbs [SIZE_DEC_RBS];
	var_d      ufract                      _V34N_TX_GAIN_ADJUST_TABLE [V34N_MAX_MAXRATE*2*2];
	var_d      sint15                      _v90_shape_2_offset;
	var_d      sint15                      _v34_rx_pn_real;
	var_d      sint15                      _v34h_tx_w_1_quantize;
	var_d      sint15                      _ipbx_outgoing_history_index;
	local_d    bool                        _parm__ipbx_outgoing_block_service;
	var_d      sint15*                     _p_window;
	shared_d   fract32                     _impedance_monitor_tx_speech_pow32;
	local_d    bool                        _parm__ipbx_hot_line_dialing;
	var_d      fract                       _phasedet_rnd_imag_value;
	var_d      fract                       _faxdet_data_v21 [6];
	var_d      bool                        _ph2_AB_detected;
	var_d      sint15                      _ipbx_incoming_history_index;
	local_d    bool                        _parm__ipbx_polarity_idle;
	parm_d     bool                        _parm__ffsk_enc_enable;
	var_d      sint15                      _predicted_rx_xn_B1_Q_n_real [16 * 8];
	parm_d     fract                       _parm__dtmf_early_row_no_tone_level;
	fast_d     uint16                      _vppn_encode_packet_byte_data;
	shared_d   volatile int                _rx_data_ti;
	debug_d    uint16                      _ANSW_LEN_MS_PREWAIT_DELAY;
	var_d      phase_t                     _ANSam_phase;
	var_d      uint16                      _v92n_rx_eye_modulus [2*6];
	var_d      fract                       _fract_input_real;
	shared_d   uint16                      _parm__vppn_device_firmware_offset;
	var_d      fract40                     _p18_energy40;
	coef_d     fract                       _lec__tec_coef [LEC__TEC_COEF_SIZE];
	var_d      sint15                      _v90_tx_dil_tp_offset;
	local_d    bool                        _parm__ipbx_polarity_dialing;
	debug_d    uint16                      _sart_rx_processed_cnt;
	const_d    fract                       _min_phroll_convergence_thresh;
	var_d      sint15                      _parm__speech_rtp_auto_vad_turnoff;
	var_d      sint15                      _v90_shape_frame_size;
	var_d      sint15                      _l_res_cb_size [4];
	var_d      uint16                      _ph1_tx_sample_counter;
	var_d      uint16                      _nat_lan_hw_addr [EADDR_LEN_16]; /* Public HW MAC address for LAN side */
	var_d      fract                       _v34f_eqc_DC_mag_log;
	parm_d     char                        _parm__sdp_session_name [SDP_SESSION_NAME_LENGTH];
	var_d      phase_t                     _guard_tone_phase;
	var_d      fract                       _v34f_eqc_sd_DC_real;
	var_d      sint15                      _v90h_tx_control_frame [12];
	var_d      fract                       _temp_c7k2_interpolator_coefs [MAX_C7K2_INTERPOLATOR_SIZE];
	shared_d   bool                        _parm__ipbx_busy_forward_enable;
	var_d      sint15                      _pspr_y2_hi;
	var_d      uint16                      _parm__vppn_device_command [VPPN_DEV_MESSAGE_MAX_LENGTH];
	var_d      uint16                      _mbx__dtoh_hidden [MBX_DTOH_SIZE];
	parm_d     uint16                      _parm__v8__protocols;
	var_d      sint15                      _size_st [NSTAGEMAX];
	parm_d     char                        _parm__mgcp_call_agent_address [NET_DOMAIN_SIZEOF];
	var_d      int                         _ipod_dth_coded_speech_offset;
	parm_d     uint16                      _parm__slac_impedance_commands [IPBX_SLAC_PORT_IMPEDANCES][IPBX_SLAC_COMMAND_SIZEOF];
	var_d      uint16                      _PH2P_ANAL_USE_SHAPING;
	fast_d     fract                       _faxdet_value_grl_ansam;
	var_d      int                         _rxs_run_rx_baud_thread [THREAD_BUFFER_SIZE];
	var_d      uint16                      _pcm_rx_3dB_pad_detect;
	var_d      uint16                      _v90n_tx_training_silence_option; /* 0 = normal, 1 = silence */
	shared_d   uint32                      _dprmbx_post_fw_upgrade_success;
	var_d      fract                       _v34_resync_variance_buffer_imag [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      uint16                      _stop_timer_count;
	var_d      uint16                      _stat__ipbx_device_error_mask;
	var_d      uint16 *                    _v34h_rx_buffer_stream_pointer;
	var_d      int                         _sonitrol_legacy_mode;
	var_d      uint16                      _v90_previous_ks_value;
	parm_d     uint16                      _parm__dm_carrier_loss_disconnect_duration;
	var_d      fract *                     _ph2p_anal_log_P_plus_start;
	var_d      uint16                      _report_rx_packet_flag;
	parm_d     uint16                      _parm__codec_ring_minimum_period;
	var_d      sint15                      _qplsp_lsf_vq [LPC_ORD];
	var_d      fract                       _cc_rx_AC_energy_log;
	var_d      fract                       _convert_adjust_output_log;
	stat_d     sint15                      _stat__speech_rtp_in_silence;
	var_d      sint15                      _hh1 [L_SUBFR];
	var_d      sint15                      _v90_tx_p_frame [6];
	parm_d     bool                        _parm__net_isp_dhcp_enable;
	fast_d     ufract                      _v34n_tx_transmit_gain;
	var_d      uint16                      _lec__force_nlp;
	var_d      sint15                      _v34h_rx_Z_m_previous;
	var_d      uint16                      _dtmf_clamp_detect;
	var_d      uint16                      _global_width;
	var_d      fract CIRCULAR              _rate_reduction_buffer [C7K2_FSK_REDUCE_LPF_SIZE * 2];
	var_d      rtp_packet_t                _rtp_rx_packet; /* RTP RX packet when host split from DSP */
	fast_d     rtp_packet_t*               _rtp_dec_packet;
	parm_d     uint32                      _stat__nat_rcv_frag_forward; /* LAN to WAN receive fragment forwarding success packet exit counter */
	var_d      uint16                      _excessive_ff;
	var_d      uint16                      _parm__battery_level_threshold_crossed;
	local_d    bool                        _parm__ipbx_caller_id_outbound_service;
	fast_d     fract                       _total_ec_sum;
	var_d      uint16                      _detect_equalizer_poffset;
	var_d      fract                       _edge_m1200_imag;
	var_d      sint15                      _Next_Min;
	var_d      uint16                      _send__v8__vpcm_availability;
	var_d      const uint16 *              _nearest_group_table;
	const_d    fract                       _parm__dm_v92_mse_catastrophic;
	var_d      fract                       _rx_rate_double_buffer [2*RX_RATE_DOUBLE_SIZE];
	var_d      fract                       _v33_fback_nearest_group_table_internal_buffer [64];
	var_d      uint16                      _ata_led_use_mask_sip;
	var_d      uint16                      _parm__record_method;
	var_d      uint32                      _nat_lan_ip_addr; /* Public IP address for LAN side in network order */
	var_d      uint16                      _v90_tx_dil_ucode;
	parm_d     uint16                      _parm__ipbx_timeout_hold_duration;
	var_d      sint15                      _dev_pattern_index;
	var_d      bool                        _comn_v8_ANSpcm_detect_loss;
	shared_d   uint16                      _codec_tx_mask;
	parm_d     uint16                      _parm__mgcp_call_agent_ota_parameters;
	var_d      uint16                      _newsidframe;
	parm_d     uint32                      _stat__nat_wan_rtp_end_point; /* WAN to LAN receive RTP end-point packet exit counter */
	parm_d     uint32                      _stat__net_dhcp_lease_time;
	parm_d     uint16                      _parm__ipbx_fc_blocked_number_disable;
	var_d      uint16                      _ph2n_rx_coding_law;
	local_d    uint16                      _first_received_rate;
	var_d      fract                       _v34_resync_perfect_real;
	parm_d     struct ring_descriptor      _parm__ipbx_call_back_ring;
	local_d    uint16                      _v34n_rx_remote_to_local_maxrate;
	fast_d     uint16                      _vppn_encode_packet_index;
	stat_d     uint16                      _stat__dm_rx_bits_per_symbol;
	var_d      uint16                      _v90n_tx_constellation_mask;
	stat_d     uint16                      _stat__tx_v34_symbol_rate;
	var_d      fract                       _ph2p_anal_variance_00_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _v34_equalizer_agc_update_enabled;
	local_d    uint16                      _parm__ipbx_voip_no_provider_available;
	var_d      sint15                      _mem2_postfilt [LPC_ORD];
	var_d      uint16                      _ipbx_periodic_interval;
	const_d    bool                        _v92_linear_mode_enable;
	var_d      sint15                      _lec__td_check_ratio;
	var_d      fract40                     _ph2p_fefo_spectrum_buffer40 [2*PH2P_FEFO_BIN_COUNT];
	parm_d     sint15                      _parm__speaker_monitor_tx_gain;
	parm_d     uint16                      _parm__ipbx_fc_caller_id_outbound_disable;
	parm_d     char                        _parm__ata_recovery_domain_name [NET_DOMAIN_SIZEOF];
	var_d      uint16                      _v34h_rx_half_data_frame_counter;
	var_d      uint16                      _answ_v8_found_CI;
	parm_d     char                        _parm__ata_firmware_request_message [ATA_MESSAGE_SIZEOF];
	shared_d   int                         _impedance_monitor_tx_noise_floor_index;
	var_d      uint16                      _answ_v8_found_CJ;
	debug_d    uint16                      _V34S_REVERSALS_FOUND_THRESHOLD;
	var_d      fract                       _rxs_input_sample [THREAD_BUFFER_SIZE];
	var_d      sint15                      _v90_rx_delay_poffset_current;
	var_d      fract                       _v34_TRN2_MSE_N_value;
	shared_d   uint16                      _parm__vppn_device_firmware_checksum;
	var_d      uint16                      _answ_v8_found_CM;
	fast_d     event_t                     _fgkernel_current_event;
	shared_d   uint16                      _sample_buffer_size;
	persist_d  uint16                      _ph2n_tx_lo_3200_option;
	parm_d     struct tone_descriptor      _parm__codec_disconnect_tone_1;
	parm_d     struct tone_descriptor      _parm__codec_disconnect_tone_2;
	var_d      sint15                      _lec__nlp_detect_quiet;
	parm_d     struct tone_descriptor      _parm__codec_disconnect_tone_3;
	var_d      fract                       _cc_rx_ANAL_BEp_imag;
	var_d      phase_t                     _rx_clock_phase_slave;
	var_d      uint16                      _saved_output_sample_value;
	var_d      uint16                      _sart_rx_array [RX_SART_BUFFER_SIZE+1];
	var_d      uint16                      _ph2p_anal_maxrates_12_table [PH2P_NO_PREEMPHASIS];
	var_d      ufract                      _pcm_btr_gain_gain;
	var_d      fract                       _demod_lagging_real;
	var_d      fract                       _detect_demod_real;
	var_d      uint16                      _ph2_rx_data_size;
	var_d      uint16                      _v90_rx_JE_detect_flag;
	var_d      sint15                      _pspr_y2_lo;
	parm_d     uint16                      _parm__voip_melp_npp_enable;
	var_d      fract CIRCULAR              _v92_rx_decoder_ep_buffer [V92_RX_DECODER_EP_SIZE*2]; /* MEMORY_AVAILABLE */
	var_d      sint15                      _v34_BE_modify_Gp_exp;
	parm_d     uint32                      _parm__net_private_ip_address;
	var_d      uint16                      _legacy_SPP_expected_ack_count;
	var_d      sint15                      _pcm_ctl_ep_nlms_extra_shift; /* T */
	var_d      fract                       _tmp_baud_UVW_real [3];
	var_d      sint15                      _v34h_rx_Z_m;
	var_d      sint15                      _v34_tx_remote_pattern_offset;
	parm_d     struct tone_descriptor      _parm__ipbx_initial_dial_tone;
	var_d      fract                       _lec__probe_nlp_clip;
	const_d    ufract                      _V34_QN_UPDATE_SLOW_SLEW;
	parm_d     sint15                      _parm__g722_frame_type;
	var_d      fract40                     _ph2p_powr_spectrum_power_buffer40 [PH2P_NO_BINS_x2];
	var_d      sint15                      _parents [2*MSVQ_M];
	parm_d     uint16                      _parm__ipbx_dialing_duration;
	var_d      sint15                      _v34s_run_v0_m_holdoff_count;
	var_d      sint15                      _dgi_max_count;
	var_d      sint15                      _picp_index;
	var_d      fract                       _txs_out_vxxmod_local [THREAD_BUFFER_SIZE];
	var_d      sint15                      _v90_rx_dil_tp_cnt;
	var_d      uint16                      _pcm_ctl_use_alternate_double;
	var_d      uint16                      _ipod_msg_rx_flags;
	debug_d    bool                        _baud_rx_parity_used;
	var_d      sint15                      _l_postLPFInHis [2];
	var_d      sint15                      _v34s_post_MPA_bit_counter;
	parm_d     uint32                      _stat__phone_timer_start_time;
	var_d      uint16                      _v92n_rx_train_8pt;
	var_d      sint15                      _idftc_idft_real [160];
	var_d      uint16                      _saved_scrambler_mask;
	var_d      sint15                      _cc_rx_rate_counter;
	debug_d    uint16                      _v8_tx_state;
	fast_d     vppn_packet_t *             _vppn_decode_packet_list;
	const_d    sint15                      _DELTA_INTEGRATION_TIME;
	var_d      uint16                      _v92h_rx_control_frame [V92_LEN_8K0_DATA_FRAME];
	var_d      uint32                      _parm__speech_rtp_flow_spec;
	var_d      sint15                      _sm_shift [ENH_VEC_LENF];
	parm_d     uint16                      _parm__cp_rd_energy_off_duration;
	var_d      sint15                      _l_postLPFOutHis_hi [2];
	debug_d    fract                       _MONITOR_PHASE_THRESHOLD;
	const_d    fract                       _ANSAM_LOWER_THRESHOLD;
	var_d      sint15                      _lambdaD [ENH_VEC_LENF];
	var_d      int                         _melp_ip [NSUBFRAME600][NSTAGEMAX][MBEST_LSF];
	var_d      int                         _melp_iq [NSUBFRAME600][NSTAGEMAX][MBEST_LSF];
	var_d      sint15                      _dec_sharp;
	var_d      mse_struct                  _v34_TRN2_MSE_S_stack [V34_TRN2_MSE_STACK_SIZE];
	var_d      fract                       _FALL_fallforward_value;
	var_d      sint15                      _DIL_probing_RBS_bislot_storage [12];
	var_d      fract                       _pcm_btr_error;
	debug_d    uint16                      _v34b_bg_ph2_state;
	var_d      bool                        _v92_MH_detect_enable;
	parm_d     struct led_descriptor       _parm__dpbx_led_use_and_hold;
	var_d      fract                       _dcd_probe_diversion;
	debug_d    bool                        _baud_rx_parity_even_space;
	var_d      fract                       _v34n_rx_mse_bias;
	var_d      uint16                      _v34n_tx_probing_maxrate;
	var_d      fract                       _ph2n_probing_transmit_gain;
	debug_d    uint16                      _sart_overlay_state_prev;
	parm_d     char                        _parm__sip_info_hookflash_string [STRSIZE_32];
	var_d      ufract                      _pcm_whiten_transmit_gain;
	debug_d    uint16                      _overlay_minor_index;
	var_d      fract                       _eqout_leading_imag;
	var_d      sint31                      _temp_saturation;
	parm_d     uint16                      _parm__rtp_packet_duration; /* Packet duration in msec */
	var_d      uint16                      _ans_counter;
	var_d      sint15                      _v27_rx_guard_count;
	var_d      uint16                      _v8_rx_QC_type_flag;
	var_d      fract                       _v23_orig_tx_passband_coefs_buffer_internal [C7K2_FSK_TX_BPF_SIZE];
	var_d      sint15                      _dgi_pad_type;
	var_d      sint15                      _local_ec_shift_slew;
	shared_d   fract                       _impedance_monitor_rx_in [IMPEDANCE_MONITOR_DECIMATE_DATA_SIZE * 2];
	const_d    sint15                      _ANSAM_CYCLE_COUNT_MAX;
	persist_d  uint16                      _ph2n_rx_receive_difference;
	persist_d  uint16                      _ph2n_tx_hi_3200_option;
	var_d      uint16                      _PCM_LEN_8K0_MAX_GEAR_TRAIN; /* 1500 ms */
	parm_d     sint15                      _parm__headset_rx_gain;
	var_d      fract                       _g722_e4l_bl [7];
	var_d      fract                       _pcm_16K_demod;
	var_d      sint15                      _tonemute_count;
	var_d      sint15                      _pcm_equalizer_ep_poffset;
	var_d      uint16                      _v34h_rx_write_enable;
	parm_d     bool                        _parm__ata_lcd_menu_accounts_display;
	var_d      sint15                      _curAcf_dtx [MP1];
	var_d      sint15                      _dec_gain_code;
	var_d      fract                       _v90_rx_Uinfo_magnitude;
	var_d      fract                       _demod_imag;
	const_d    sint15                      _ANSAM_MIN_SAMPLES;
	var_d      uint16*                     _v90_frame_tx_dil_body_ucode [5];
	var_d      uint16*                     _pnew_scores;
	debug_d    uint16                      _V34S_RESP_8K0_3RT_S_SN_to_Edet;
	var_d      sint15                      _stat__daa_disconnect_state;
	var_d      fract                       _edge_p1200_real;
	var_d      fract*                      _g711a_plc_pitchbufend;
	var_d      bool                        _ph2s_short_roundtrip_flag;
	var_d      sint15                      _g_gl_buffer [SIG_LENGTH];
	var_d      sint15                      _agal_shift [ENH_VEC_LENF];
	var_d      fract                       _V34_SLEW_COS_BE2;
	var_d      fract                       _eqout_lagging_delay_real;
	var_d      uint16                      _v92n_rx_symbol_rate;
	var_d      fract                       _v32bis_7200_nearest_group_table_internal_buffer [64];
	var_d      sint15                      _lec__nlp_tight_counter;
	shared_d   uint16                      _stat__led_ringing_state;
	debug_d    uint16                      _ph2_power_trace_bin_count;
	parm_d     uint16                      _stat__net_dual_ethernet;
	var_d      sint15                      _lag0q_mem_s;
	parm_d     bool                        _parm__radio_transmitter_power_amp_mode;
	var_d      fract                       _pre_equalizer_coefs [5];
	var_d      fract                       _g722_dec_dethigh;
	var_d      fract                       _v34_temp_lo_lo_pre_equalizer_coefs [5];
	debug_d    uint16                      _ORIG_LEN_MS_MAXIMUM_ANS;
	var_d      uint16                      _v90n_parm_rx_pcm_3429_option;
	parm_d     uint16                      _parm__ipbx_disconnect_debounce;
	shared_d   uint16                      _ipbx_led_mask [NUMBER_OF_LINES_PER_DSP];
	var_d      fract                       _g722_e4l_dl [7];
	shared_d   bool                        _parm__ipbx_call_forward_enable;
	var_d      uint16                      _tx_rd_index;
	debug_d    uint16                      _v34s_reneg_special_flag;
	parm_d     uint16                      _parm__speech_tx_dtx_flag;
	var_d      uint16                      _PCM_LEN_8K0_EQC_TRN1A_START;
	var_d      sint15                      _picp_size_of;
	const_d    sint15                      _monitor_be2_limit;
	var_d      fract                       _v92_system_ID_coefs [V92_SYSTEM_ID_SIZE*1];
	stat_d     uint16                      _stat__mbx_dma_cycle_cnt;
	var_d      sint15                      _l_postLPFOutHis_lo [2];
	debug_d    uint16                      _sync_ack;
	var_d      uint16                      _phone_zeroize_debounce_count;
	var_d      sint15                      _lec__tec_update_ratio;
	var_d      uint16*                     _ata_sample_record_base;
	var_d      sint15                      _bpvi [NF600][NUM_BANDS];
	var_d      fract                       _g722_dec_slow;
	var_d      uint16                      _v90_tx_send_JE_sequence_flag;
	var_d      sint15                      _v90_rx_eye_modulus [6*1];
	var_d      uint16                      _v90_apcm_dil_second;
	parm_d     uint16                      _parm__ipbx_fc_two_digit_speed_dial_program;
	parm_d     char                        _parm__ata_processor_chip_id [ATA_CHIP_ID_SIZEOF];
	var_d      sint15                      _ec_update_rate_divider;
	parm_d     char                        _parm__ata_firmware_success_message [ATA_MESSAGE_SIZEOF];
	var_d      uint16 CIRCULAR             _temp_dm_buffer [32];
	const_d    uint16                      _v29_train_length;
	var_d      thread_routine_t            _v92_system_ID_subroutine;
	var_d      sint15                      _bulk_delay_input_poffset;
	var_d      sint15                      _old_T0;
	var_d      uint16                      _sart_rx_buffer_element;
	var_d      sint15*                     _synth_p;
	var_d      sint15                      _pcm_btr_type_limit;
	debug_d    sint15                      _silence_change_counter;
	var_d      uint16                      _test_s_lsw;
	var_d      fract32                     _parm__audio_agc_noise_floor;
	var_d      sint15                      _detect_v21_detect_counter;
	var_d      sint15                      _ptloop_phdet_jam_holdoff;
	var_d      sint15                      _v34_rx_yn_hat_real;
	local_d    char                        _parm__ipbx_call_forward_list [IPBX_LIST__CALL_FORWARD_NO_OF][IPBX_DIAL_STRING_SIZEOF];
	debug_d    uint16                      _V34S_ORIG_8K0_2RT_JEend_to_Edet;
	var_d      uint16                      _ph2n_tx_optional_attenuation;
	var_d      sint15                      _V90_LEN_8K0_TRN1D_TEST;
	var_d      sint15                      _PH2P_BG_CALCULATE_NORM_POWER;
	var_d      uint16                      _v92n_parm_apcm_data_rate_option [2];
	var_d      sint15                      _v92_rx_decoder_ep_error;
	parm_d     sint15                      _parm__slac_port_rx_gain;
	var_d      sint15                      _pcm_ep_equalizer_size;
	parm_d     bool                        _parm__sip_use_nat_discovery;
	var_d      uint16                      _mbx__htod_hidden [MBX_HTOD_SIZE];
	fast_d     fract                       _faxdet_threshold_v21;
	debug_d    ufract                      _V34_BE_SLEW_SLOW;
	var_d      uint16                      _ph4n_tx_answer_to_call_maxrate;
	var_d      sint15                      _ph2p_fefo_start_bin_phase_index;
	var_d      sint15                      _v34n_established_ph4_count;
	const_d    fract                       _train_on_data_128_slew;
	var_d      sint15                      _l_pulse_del [MIX_ORD];
	var_d      uint16                      _lec__nlp_gauge_mode;
	var_d      fract                       _energy_echo_log;
	var_d      sint15                      _gpf_search_srt;
	parm_d     bool                        _parm__codec_disconnect_voltage_enable;
	var_d      phase_t                     _ANSam_trace_phase;
	var_d      sint15                      _picp_function;
	parm_d     bool                        _parm__phone_paycard_enable;
	persist_d  uint16                      _v34n_rx_difference_option;
	parm_d     char                        _stat__ata_update_bootfile_url [ATA_URL_SIZEOF];
	var_d      uint16                      _trellis_data;
	var_d      bool                        _ipod_g726_monitor_state;
	parm_d     struct tone_descriptor      _parm__ipbx_sit3_tone;
	var_d      sint15*                     _wsp;
	var_d      sint15                      _ph2_tx_interpolator_offset;
	const_d    fract                       _threshold_fax_ab2;
	parm_d     uint16                      _parm__mgcp_remote_port; /* port is only used if there's no provider.  Set */
	var_d      fract32                     _notch_datay32_300;
	var_d      uint16                      _ph1_x_law_round_value;
	fast_d     uint16                      _ph4n_rx_trained_trellis;
	var_d      sint15                      _enc_byte_counter;
	var_d      fract                       _cc_rx_ANAL_coef_angle;
	fast_d     sint15                      _dc_offset;
	var_d      fract                       _phasedet_rnd_real_value;
	var_d      bool                        _parm__ipbx_caller_id_inbound_current_enable;
	var_d      sint15                      _dtx_prev_energy;
	var_d      uint16                      _faxparm_parm__v21_holdoff_timer;
	var_d      uint16                      _v92h_rx_K_value;
	fast_d     sint15                      _asm_encode_build_word;
	var_d      thread_routine_t            _pcm_rx_renegot_detect_routine;
	parm_d     sint15                      _parm__speakerphone_tx_gain;
	var_d      uint16                      _flushsart;
	var_d      fract CIRCULAR              _v34_rx_qn_equalized_buffer_imag [2*(V34_NO_QN_COEFS + 1)];
	var_d      sint15                      _parm__speech_mac_dest_addr [3];
	var_d      sint15                      _f0q_dec_mem_s;
	var_d      sint15                      _v34_bulk_extra_buffer_imag [BULK_EXTRA_BUFFER_SIZE];
	var_d      fract                       _ph2n_rx_preeq_Whi;
	var_d      sint15                      _lec__datamax_half_size;
	parm_d     uint16                      _parm__phone_entry_time;
	parm_d     uint32                      _stat__nat_snd_tcp; /* LAN to WAN send TCP packet type counter */
	var_d      uint16                      _current_mode;
	var_d      sint15                      _parm__speech_rtp_ssrc_ident [2];
	var_d      sint15                      _pcm_rx_slot_counter;
	parm_d     uint16                      _parm__voip_gsmamr_encode_rate;
	var_d      uint16                      _done_with_dtmf;
	var_d      const fract *               _cmr_notch_coefs;
	var_d      fract                       _remote_ec_slew;
	var_d      sint15                      _lec__datamax_half_holdoff;
	var_d      ufract                      _lec__tx_suppressor_incr;
	var_d      fract                       _lec__best_can_ratio;
	debug_d    sint15                      _v34_helper_state_index;
	var_d      fract32                     _v34_rx_yn_perfect_imag_32;
	parm_d     fract                       _parm__tone_detectors_slew_rate;
	var_d      fract                       _data_12k_lookup_internal_buffer [64];
	parm_d     char                        _parm__sip_allowed_event_types [STRSIZE_256];
	var_d      uint16                      _shadow_DNIS_digits;
	const_d    sint15                      _minimum_first_trn_length;
	var_d      fract                       _tonemute_rx;
	fast_d     uint16                      _stat__dpbx_key_mask;
	var_d      uint16                      _lookback_poffset;
	var_d      fract32                     _ph2p_fefo_test_b32;
	var_d      sint15                      _handset_out_sample;
	var_d      sint15                      _l_pitch_avg;
	var_d      fract                       _lec__best_lin_ratio;
	var_d      sint15 CIRCULAR             _v34_tx_qn_buffer_real [2*V34_NO_QN_COEFS];
	var_d      bool                        _w_fs_init;
	var_d      sint15                      _v90_frame_rx_residue_length;
	parm_d     bool                        _parm__radio_receiver_vibrate_enable;
	var_d      fract                       _local_ec_slewx;
	var_d      uint16                      _ph2p_anal_maxrates_05_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _v92n_rx_prefilter_ff_taps;
	var_d      uint16                      _v34n_parm_hi_data_rate_option;
	var_d      sint15                      _g_frameSize;
	parm_d     uint16                      _parm__net_ddns_service_name;
	var_d      uint16                      _ipod_iface_tx_state;
	var_d      sint15                      _SN_LT0;
	debug_d    uint16                      _v17_short_ratdet;
	parm_d     struct tone_descriptor      _parm__ipbx_stuttered_dial_tone;
	debug_d    uint16                      _baud_tx_two_stop_bits;
	var_d      char                        _picp_line_1_buffer [LCD_CHAR_DISPLAY_MAX];
	fast_d     phase_t                     _rx_clock_cycles_per_sample;
	stat_d     sint15                      _stat__speech_udp_message_length;
	const_d    fract                       _dcd_diversion_diff_threshold;
	var_d      uint16                      _v34n_parm_16point_option;
	var_d      fract                       _tmp_baud_UVW_complex [6];
	var_d      sint15                      _gpf_coarse_match;
	shared_d   bool                        _parm__ipbx_no_answer_forward_enable;
	var_d      fract                       _g168_exc_floor;
	var_d      uint16                      _v34n_tx_MD_length;
	var_d      fract                       _cc_tx_guard_xmit_amplitude;
	var_d      sint15                      _v34_tx_pn_real;
	var_d      nat_tab_t *                 _nat_public_table [NAT_HASHMOD]; /* Hashed list head - using public IP port */
	parm_d     uint16                      _parm__decoder_mode;
	var_d      fract32                     _btrec_rx_phase_second32;
	var_d      bool                        _fsk_run_data_hdlc;
	local_d    uint16                      _v34n_rxtx_auxiliary_option;
	var_d      fract                       _v34_pnt12_MSE_value;
	debug_d    ufract                      _V34_BE0_SLEW_SLOW;
	local_d    fract                       _sense_silence_lpf1;
	var_d      uint16                      _led_pattern;
	local_d    fract                       _sense_silence_lpf2;
	var_d      sint15                      _l_postLPF [6];
	stat_d     uint16                      _stat__ipod_timeslot;
	var_d      sint15                      _asm_within_cng_delay;
	var_d      sint15                      _v34_frame_tx_bit_count;
	fast_d     uint16                      _dpbx_led_pattern_queue_in;
	var_d      uint16                      _v90_rx_data_holdoff_flag;
	parm_d     sint15                      _parm__ipbx_tone_max;
	var_d      sint15                      _cc_tx_guard_tone_increment;
	var_d      fract                       _tonemute_tx;
	parm_d     uint16                      _parm__pump_fallback_rates;
	var_d      fract40                     _ph2p_powr_reconstruction_buffer40 [2*PH2P_NO_BINS];
	parm_d     uint16                      _parm__codec_ring_silence_period;
	parm_d     char                        _parm__net_assigned_host_name [ATA_HOST_NAME_SIZEOF];
	var_d      uint16                      _shadow_panel_group_desc [70+1];
	var_d      sint31                      _ac97_minor_number;
	shared_d   volatile int                _tx_data_ti;
	var_d      sint15                      _v34_rx_pn_hat_real;
	fast_d     int                         _number_fg_comp [NUMBER_OF_FG_BLOCKS];
	var_d      fract                       _ptloop_angle [2];
	var_d      sint15                      _v34_rx_un_imag;
	parm_d     sint15                      _parm__slac_message_waiting_bias;
	local_d    char                        _parm__ipbx_zoom_alarm_inital_dial_pattern [IPBX_DIAL_STRING_SIZEOF];
	var_d      uint16                      _allowed_detect_tones;
	var_d      sint15                      _v34n_rx_qn_coef_imag [V34_NO_QN_COEFS];
	debug_d    sint15                      _ec_slow_shift_slew_remote;
	var_d      int                         _sip_tcp_sockid;
	debug_d    uint16                      _answ_v8_allow_CM_detection;
	parm_d     bool                        _parm__ilbc_high_rate;
	fast_d     rtp_stream_t*               _current_audio_rtp_stream;
	var_d      uint16                      _ipod_msg_tx_trans_bits;
	var_d      rtp_packet_t                _rtp_tx_packet; /* RTP TX packet when host split from DSP */
	var_d      fract32                     _p18_full_energy32;
	var_d      fract                       _pcm_8K0_perfect;
	local_d    uint16                      _v34n_rxtx_asymmetric_rates;
	var_d      uint16                      _shadow_configuration_available;
	local_d    bool                        _parm__ipbx_attended_transfer_service;
	local_d    bool                        _parm__ipbx_call_waiting_service;
	var_d      uint16                      _v90n_tx_CPt_type; /* 0 = CPt, 1 = CP */
	var_d      sint15                      _v90h_rx_shaper_wait_flag;
	local_d    fract CIRCULAR              _echo_canceller_buffer [2 * V32_ECHO_BUFFER_SIZE];
	var_d      fract                       _lec__datamax_full_value;
	var_d      sint15                      _v92_rx_Ru_detect_flag;
	var_d      uint16                      _pcm_tx_clock_fractional_adjust;
	var_d      const sint15*               _enc_bitsno_array;
	var_d      fract *                     _saved_Lx_log_power_pointer;
	var_d      uint8                       _ipod_iface_rx_buffer [RTMSC_FRAME_SIZE_MAX];
	debug_d    uint16                      _baud_tx_state;
	var_d      fract                       _rxs_demod_real [THREAD_BUFFER_SIZE];
	var_d      sint15                      _tonemute_valid_count;
	stat_d     uint16                      _stat__v8__protocols;
	parm_d     uint16                      _parm__ipbx_timeout_no_answer_drop_duration;
	var_d      fract                       _pcm_HI_value;
	var_d      fract                       _ph2n_rx_preeq_Wlo;
	parm_d     uint16                      _parm__jpeg_thumbnail_height;
	fast_d     fract                       _noise_generator_tx;
	var_d      int                         _g722_dec_mode;
	var_d      sint15                      _ata_pfd_status;
	var_d      fract                       _pcm_LO_value;
	var_d      fract                       _v34_temp_hi_hi_pre_equalizer_coefs [5];
	var_d      fract32                     _v29_rot_mse;
	var_d      sint15                      _v34_pp_skip_count;
	parm_d     uint16                      _parm__sdp_mpeg4_codec_dyn_pt;
	var_d      uint16                      _producing_1300_calling_tone;
	shared_d   uint16                      _parm__net_debug_level_sip;
	parm_d     uint16                      _parm__sdp_speex_codec_dyn_pt;
	var_d      fract40                     _ph2p_powr_variable_buffer40 [2*PH2P_NO_BINS_x2];
	parm_d     char                        _parm__ata_system_info_1 [STRSIZE_64];
	parm_d     sint15                      _parm__disconnect_tone_num_tones;
	parm_d     char                        _parm__ata_system_info_2 [STRSIZE_64];
	var_d      fract                       _ph2n_rx_preeq_Wme;
	parm_d     char                        _parm__ata_system_info_3 [STRSIZE_64];
	parm_d     uint32                      _parm__net_dns_secondary_address;
	parm_d     char                        _parm__ata_system_info_4 [STRSIZE_64];
	parm_d     char                        _stat__ata_update_extra_url [ATA_URL_SIZEOF];
	parm_d     char                        _parm__ata_system_info_5 [STRSIZE_64];
	var_d      uint16                      _nat_icmp_type; /* ICMP packet type */
	const_d    uint16                      _fax_v21_rlsd_length;
	var_d      sint15                      _v90_rx_base_group [6*2*BASGRP_MAX_2];
	parm_d     uint16                      _parm__disconnect_tone_cadence_detect_mask;
	parm_d     uint16                      _parm__dm_v90_options_mask;
	parm_d     uint16                      _parm__rtp_stream_duration; /* Stream duration in msec */
	var_d      fract                       _v34f_eqc_pr_DC_mag_log;
	var_d      sint15                      _count_ext;
	var_d      fract                       _ph2p_anal_L2_variance;
	parm_d     uint16                      _parm__pump_diag_modes;
	var_d      fract                       _g722_dec_detlow;
	var_d      uint16                      _nat_ip_type; /* IP packet type */
	var_d      uint16                      _fg_kernel_anomaly;
	fast_d     int                         _fg_status_remove;
	var_d      uint16                      _ph4n_tx_control_channel_data_rate;
	var_d      sint15                      _enc_lsp_old [M_LP];
	var_d      fract                       _v34_equalized_real;
	var_d      struct led_descriptor       _parm__ipbx_green_led_descriptor;
	var_d      uint16                      _gear_change_period;
	debug_d    sint15                      _silence_keep_counter;
	var_d      uint16                      _faxmon_final_frame_seen;
	var_d      fract CIRCULAR              _cc_rx_interpolator_buffer_imag [CC_RX_INTERPOLATOR_SIZE*2];
	parm_d     fract                       _parm__dtmf_min_tone_level;
	var_d      fract                       _v34n_rx_receive_agc2_level;
	var_d      bool                        _syn_erase;
	parm_d     uint32                      _stat__nat_wan_icmp; /* WAN to LAN receive ICMP packet type counter */
	var_d      uint16                      _FALL_fallforward_flag;
	parm_d     uint16                      _parm__nat_timeout_tcp_opening; /* Idle seconds before opening TCP NAT timeout */
	var_d      sint15                      _v34h_tx_mapping_frame_count;
	var_d      sint15                      _v34_rx_yn_real;
	debug_d    uint16                      _PCM_TEST_RBS_SIMULATION_ENABLE;
	var_d      DecState                    _speex_dec_state;
	var_d      sint15                      _envdel2 [NUM_BANDS];
	var_d      fract CIRCULAR              _extra_rate_reduction_buffer_imag [2 * C7K2_FSK_REDUCE_LPF_SIZE];
	var_d      bool                        _v92_modem_type;
	fast_d     fract                       _faxdet_value_previous;
	debug_d    uint16                      _ORIG_V8_CI_COUNT_MIN;
	var_d      uint16                      _v90n_rx_v90_enable;
	var_d      fract                       _ANSam_trace_imag;
	var_d      sint15                      _l_firstTime_bpvc_ana;
	var_d      fract                       _cc_tx_guard_tone_amplitude;
	var_d      uint16                      _lec__detect_bits;
	var_d      sint15                      _v34_rx_qn_equalized_poffset;
	var_d      sint15                      _seed_fer;
	var_d      sint15                      _prpr_y1_hi;
	var_d      fract40                     _ph2_rx_checker_sum40;
	var_d      sint15                      _constel_symmetric_table_rbs [SIZE_SYM_RBS];
	var_d      bool                        _v92_frame_rx_short;
	var_d      uint16                      _v90n_tx_training_shaping_lookahead; /* 0 - 3 = Requested lookahead */
	var_d      uint16                      _v34_frame_tx_bits_per_baud;
	debug_d    sint15                      _valid_miss_limit;
	var_d      fract                       _ANSam_trace_magphase_min_real;
	var_d      sint31                      _ph1_tx_ANSpcm_phase32;
	shared_d   uint16                      _dprmbx_poll_count;
	var_d      uint16                      _v90_rx_R_detect_inversion;
	parm_d     char                        _parm__ata_factory_password [ATA_PASSWORD_SIZEOF];
	debug_d    energy_buffer_t             _monitor_sample_slow [6];
	var_d      fract                       _affine_perfect_imag;
	var_d      bool                        _v34s_special_local_train_option;
	var_d      sint15                      _g711_rx_vad_strict_hangover_counter;
	var_d      fract                       _v21_ans_tx_passband_coefs_buffer_internal [C7K2_FSK_TX_BPF_SIZE];
	var_d      sint15                      _v90_rx_Sd_detect_counter;
	fast_d     fract                       _agc_2_signal_imag;
	var_d      sint15                      _v34_tx_qn_remote_offset;
	parm_d     uint16                      _parm__sdp_ilbc_codec_dyn_pt;
	var_d      sint15                      _ph2n_rx_frequency_offset;
	var_d      fract                       _dtmf_mnsqr [8];
	var_d      SBDecState                  _speex_uwb_dec_state;
	var_d      FAX_test_t                  _FAX_test;
	var_d      uint16                      _ph4n_rx_call_to_answer_maxrate;
	var_d      sint15                      _v34n_rx_preeq_exponent;
	parm_d     sint15                      _parm__speech_enc_slot_cnt;
	const_d    fract                       _V92_RX_RETRAIN_Et_THRESHOLD;
	parm_d     uint16                      _parm__rtp_port_minimum;
	var_d      fract                       _v34_temp_lo_me_pre_equalizer_coefs [5];
	var_d      sint15                      _l_index;
	var_d      fract                       _ANSam_trace_max_real;
	parm_d     uint16                      _parm__dm_v34_trellis_num;
	var_d      sint15                      _DIL_probing_slot_counter;
	parm_d     uint16                      _parm__v8__modulation_modes [3];
	var_d      bool                        _ata_ignore_code_image_flag;
	parm_d     struct led_descriptor       _parm__dpbx_led_call_holding;
	var_d      uint16                      _prev_diffdec_input;
	var_d      uint16                      _vppn_device_command_queue [VPPN_DEV_COMMAND__QUEUE_SIZEOF][VPPN_DEV_MESSAGE_MAX_LENGTH];
	var_d      fract                       _g722_e3h_nbh;
	fast_d     uint16                      _parm__vppn_device_manufacturer_id;
	var_d      sint15                      _speech_in_npp [ENH_WINLEN];
	var_d      fract                       _sequence_outband_level;
	var_d      sint15                      _xxx_rx_exponent;
	var_d      fract32                     _p18_half_energy32;
	parm_d     uint16                      _parm__pulse_make_time;
	var_d      fract                       _lec__probe_nlp_output;
	var_d      mse_struct                  _pcm_AL_peak_MSE_stack [V34_TRN2_MSE_STACK_SIZE];
	var_d      sint15                      _parm__speech_enc_transition_control;
	debug_d    uint16                      _V34S_RENEG_TEST_T_S_LENGTH;
	var_d      uint16                      _ipod_command_max_fnbdt_rate;
	var_d      sint15                      _l_firstTime_pitch_ana;
	var_d      sint15                      _agc_1_exponent;
	var_d      sint15                      _lec__an_excess;
	fast_d     sint31                      _dc_offset_accumulator;
	var_d      sint15                      _ph2n_rx_preeq_exponent;
	var_d      sint15                      _g_quant_par [quant_param_LEN];
	fast_d     uint16                      _vppn_device_command_send_index;
	var_d      uint16                      _lec__cng_frame_sil_detect;
	var_d      fract32                     _faxdet_data_sum_ced;
	var_d      sint15                      _v34_local_echo_exponent;
	var_d      fract CIRCULAR              _cc_rx_equalizer_data_imag [CC_RX_EQUALIZER_SIZE*2];
	var_d      sint15                      _past_gain;
	var_d      sint15                      _ata_pfd_configuration_attempts;
	var_d      sint15                      _v34_tx_yn_remote_real;
	var_d      sint15                      _parm__ipbx_sit_id;
	var_d      sint15                      _v34_pp_sync_count;
	debug_d    sint15                      _ec_ytrain_shift_slew_remote;
	var_d      uint16                      _test_input_mixup;
	var_d      sint15                      _phone_ringer_tx_volume;
	parm_d     uint32                      _parm__net_isp_heartbeat_server_ip_address;
	var_d      sint15                      _dgi_pad_expo;
	var_d      ufract                      _V34N_RX_GAIN_ADJUST_TABLE [V34N_MAX_MAXRATE*2*2];
	debug_d    uint16                      _V34S_ANSW_8K0_1RT_Jsrt_to_S_SNdet;
	var_d      sint15 *                    _saved_Lx_SE_power_adjust_pointer;
	var_d      complex                     _edge_p1200;
	var_d      sint15                      _lec__datamax_poffset;
	var_d      fract                       _lec__nlp_threshold;
	var_d      sint15                      _l_syn_begin;
	var_d      fract                       _lec__rx_output;
	parm_d     uint16                      _parm__rtp_jitter_buffer_start_depth; /* Starting jitter buffer depth in msec */
	var_d      sint15                      _v90_tx_s_input_offset;
	parm_d     uint32                      _stat__nat_snd_translated; /* LAN to WAN send translated packet counter */
	local_d    uint16                      _parm__voip_provider_alternate [NUMBER_OF_LINES_PER_DSP];
	var_d      uint16                      _v90n_rx_rx_coding_law; /* 0 = uLaw, 1 = Alaw */
	var_d      uint16                      _v90n_tx_training_constel_mapping; /* 0 = no mapping, 1 = mapping */
	var_d      sint15                      _DIL_probing_table_offset;
	var_d      sint15                      _detect_limit;
	var_d      uint16*                     _v90_tx_dil_sp_ptr;
	var_d      fract*                      _ph2_rx_passband_coef_pointer;
	shared_d   bool                        _parm__dtmf_detect_abcd;
	var_d      int                         _g722_e4l_sg [2];
	var_d      uint16                      _v92_frame_rx_size_SUVu;
	local_d    fract                       _sdt_angle_store_real [3];
	local_d    bool                        _parm__ipbx_unattended_transfer_service;
	debug_d    sint15                      _v17_diagnostics_mse_count;
	var_d      sint15*                     _lsp_old_ptr;
	var_d      fract                       _g722_e4l_sl;
	parm_d     bool                        _parm__radio_headset_continuous_transmit_enable;
	var_d      sint15                      _prpr_y1_lo;
	shared_d   uint8                       _sonitrol_remote_lcfw_ip [4];
	var_d      uint16                      _v90n_rx_coding_law;
	var_d      fract                       _trn_8K0_perfect;
	shared_d   uint16                      _parm__dtmf_playout_min_duration;
	var_d      sint15                      _btrec_baud_AkQk_shift;
	const_d    ufract                      _V34_QN_UPDATE_DATA_SLOW_SLEW;
	persist_d  uint16                      _ph2n_tx_tx_3429_option;
	var_d      fract32                     _ptloop_2nd_order_term32;
	var_d      sint15                      _l_ase_del [LPC_ORD];
	var_d      fract                       _pcm_16K_ec_sample;
	var_d      sint15                      _l_ase_den [LPC_ORD];
	var_d      uint16                      _legacy_audio_ack_received;
	parm_d     uint16                      _parm__sart_hdlc_crc32_tx_en;
	debug_d    uint16                      _sart_overlay_state;
	var_d      fract                       _v90_rx_1K3_energy_log;
	var_d      sint15                      _parm__speech_ip_identifier;
	var_d      fract                       _v92_rx_Ru_Rxx0;
	fast_d     sint15                      _asm_encode_shift_decrement;
	var_d      sint15                      _l_melp_uv_cb_size;
	var_d      sint15                      _v90_frame_rx_input_length;
	var_d      fract                       _ph2n_rx_mse_bias;
	var_d      fract                       _v92_rx_Ru_Rxx3;
	var_d      uint16                      _rd_period_beyond_range;
	persist_d  uint16                      _v34n_tx_hi_carrier_option;
	parm_d     struct ring_descriptor      _parm__ipbx_distinctive_ring_1;
	parm_d     struct ring_descriptor      _parm__ipbx_distinctive_ring_2;
	var_d      fract                       _v92_rx_Ru_Rxx6;
	parm_d     struct ring_descriptor      _parm__ipbx_distinctive_ring_3;
	var_d      fract                       _btrec_p2400_real;
	parm_d     struct ring_descriptor      _parm__ipbx_distinctive_ring_4;
	var_d      sint15                      _PH2P_POWR_LX_INITIAL_TUNE;
	debug_d    sint15                      _V34S_GEAR_CONVERGENCE_THRESHOLD;
	debug_d    uint16                      _answ_v8_use_invert;
	parm_d     struct ring_descriptor      _parm__ipbx_distinctive_ring_5;
	parm_d     struct ring_descriptor      _parm__ipbx_call_forward_ring_splash;
	parm_d     struct ring_descriptor      _parm__ipbx_distinctive_ring_6;
	var_d      sint15                      _v34n_rx_frequency_offset;
	parm_d     struct ring_descriptor      _parm__ipbx_distinctive_ring_7;
	parm_d     char                        _parm__ata_serial_number [ATA_SERIAL_NO_SIZEOF];
	parm_d     struct ring_descriptor      _parm__ipbx_distinctive_ring_8;
	parm_d     char                        _stat__net_ddns_status [DDNS_STATUS_SIZEOF];
	var_d      fract                       _lec__tx_input;
	var_d      uint16                      _ph4n_rx_trained_nonlinear;
	var_d      sint15                      _pcm_probe_eqc_state;
	parm_d     uint16                      _parm__codec_ring_detect_period_minimum;
	var_d      fract                       _lec__probe_nlp_noise;
	parm_d     uint16                      _parm__ipbx_hangup_disconnect_duration;
	var_d      uint16                      _v90_tx_send_MP_frame_flag;
	var_d      uint16                      _received_e_seq;
	const_d    sint15                      _mark_threshold;
	var_d      fract                       _sense_silence_level;
	stat_d     uint16                      _stat__v8_disconnect_reason;
	var_d      uint16                      _ipod_command_timeslot;
	var_d      sint15                      _l_qplsp [LPC_ORD];
	var_d      sint15                      _noise_shift [ENH_VEC_LENF];
	fast_d     ufract                      _decode_gain_linear;
	debug_d    sint15                      _V34S_FULL_CONVERGENCE_THRESHOLD;
	fast_d     sint15                      _coef_offset_double;
	var_d      fract                       _v90_rx_retrain_Et_energy_log;
	var_d      uint16                      _stat__daa_gain_state;
	var_d      sint15                      _g_w_fs_inv [NUM_HARM];
	parm_d     char                        _parm__ata_user_name [ATA_ACCOUNT_SIZEOF];
	var_d      sint15                      _speech_sync_dec_delay_cntr;
	debug_d    bool                        _v34n_parm_preemptive_phase_roll_slow;
	var_d      uint16*                     _v92n_tx_SUVd_body [ 7];
	var_d      fract                       _v92_rx_Ru_RxxY;
	var_d      fract                       _tmp_full_energy;
	var_d      fract                       _g168_inp_peak;
	var_d      uint16                      _dtmf_mode;
	var_d      cngdata_t                   _g711_cng_data;
	var_d      sint15                      _parm__speech_rtp_enc_sample_cnt;
	var_d      fract CIRCULAR              _ph2_rx_rate_conv_9K6_8K0_buffer [2*(PH2_RX_RATE_CONV_DATA_BUFFER)];
	var_d      uint16                      _legacy_rx_buffer [SSP_BUFFER_SIZE];
	var_d      uint16*                     _v90n_rx_constel_codes_pointer; /* CPx value, DM *buffer */
	parm_d     uint16                      _parm__operating_mode;
	var_d      uint16                      _ipod_msg_rx_mod_type;
	var_d      fract                       _helper_imag;
	parm_d     char                        _stat__ata_update_codefile_url [ATA_URL_SIZEOF];
	debug_d    sint15                      _ph2p_powr_power_block_count;
	var_d      uint16*                     _v90_frame_tx_dil_body_h [5];
	var_d      uint16                      _v34h_tx_residue_length;
	var_d      fract*                      _v34_tx_decor_coefs;
	var_d      fract                       _g711_rx_cng_frame_buffer [G711_FRAME_BUFFER_SIZE];
	var_d      bool                        _v92_equalizer_coef_nulling;
	var_d      uint16                      _phone_zeroize_condition;
	var_d      sint15                      _input_code;
	var_d      uint32                      _v34h_rx_g2_table [36];
	parm_d     uint32                      _stat__nat_rcv_udp; /* LAN to WAN receive UDP packet type counter */
	var_d      bool                        _v92s_eqc_TRN1u2_flag;
	const_d    bool                        _v92s_retrigger_modem_on_hold;
	parm_d     uint32                      _parm__net_static_gateway_address;
	stat_d     uint16                      _stat__v8__gstn_access;
	var_d      uint16                      _ipod_v32_start_state;
	var_d      uint16                      _save_rx_answer_to_call_maxrate;
	parm_d     uint16                      _parm__ipbx_hook_debounce;
	var_d      sint15                      _dev_cid_repeat_count;
	parm_d     bool                        _parm__ata_daylight_savings_enable;
	var_d      sint15                      _act_min [ENH_VEC_LENF]  ;
	var_d      fract                       _v29_rot_equalized_real;
	parm_d     bool                        _parm__nat_dmz_enable; /* DMZ enable */
	parm_d     bool                        _parm__ipbx_fxo_autoanswer_any_enable;
	var_d      uint16                      _v90n_parm_rx_train_16pt_option;
	var_d      uint16                      _shadow_franchise_id [4+1];
	var_d      fract                       _equalizer_output_real;
	var_d      bool                        _v34s_special_remove_DC_offset;
	var_d      sint15                      _prpr_x0;
	var_d      fract                       _v34f_eqc_sd_DC_mag_log;
	var_d      sint15                      _prpr_x1;
	var_d      uint16                      _predicted_rx_xn_B1_flag;
	var_d      sint15                      _bpfdel [BPF_ORD + BPF_ORD/3];
	var_d      fract                       _pcm_rx_ph2_2k_energy_ratio;
	const_d    fract                       _silence_hysteresis;
	debug_d    uint16                      _overlay_ph2_to_ph2;
	var_d      rtp_statistics_t            _stat__rtp_statistics;
	parm_d     uint16                      _parm__sdp_gsm_fr_codec_dyn_pt;
	var_d      fract                       _FALL_adjusted_mse_delta;
	var_d      sint15                      _fsk_shift_gain;
	var_d      fract                       _jitter_Q_factor;
	var_d      uint16                      _ph2p_anal_maxrates_11_table [PH2P_NO_PREEMPHASIS];
	debug_d    sint15                      _v34s_capture_counter;
	fast_d     sint15                      _asm_decode_current_shift;
	var_d      sint15 CIRCULAR             _loopback_buffer [32];
	var_d      sint15                      _n_pwr;
	debug_d    sint15                      _v34_equalizer_slew_data_offset;
	fast_d     fract                       _faxdet_value_ansam;
	var_d      fract                       _cc_rx_ANAL_coef_real;
	parm_d     bool                        _parm__sip_prack_authentication;
	var_d      uint16                      _faxparm_active__pump_fax_mode;
	var_d      fract                       _train_on_data_slew_v29;
	var_d      sint31                      _prpr_y1;
	var_d      sint31                      _prpr_y2;
	var_d      fract                       _v34_MSE_S_value;
	var_d      fract                       _v34s_prev_phase_roll_second;
	var_d      bool                        _tone_priority_flag;
	var_d      uint16                      _rd_decimate;
	shared_d   int                         _sample_interrupt_offset;
	var_d      uint16                      _parm__srtp_session_keys [4*CRYPTO_MAX_ENCRYPTION_LEN];
	var_d      sint15                      _l_codewd_13x9 [13];
	var_d      fract                       _g722_e4h_szh;
	local_d    uint16                      _received_rate_seq;
	var_d      uint16                      _dtmf_off_end;
	var_d      fract                       _ph2p_anal_log_Eb;
	parm_d     uint16                      _parm__sip_timer_reinvite_expires;
	var_d      sint15                      _cc_enable_ones;
	var_d      fract                       _training_mse_log;
	var_d      fract                       _rxs_out_vxxmod_local [THREAD_BUFFER_SIZE];
	var_d      fract                       _g168_inp_level;
	var_d      sint15                      _ph4n_tx_receive_qn_coef_real [V34_NO_QN_COEFS];
	var_d      fract                       _det_energy;
	var_d      fract                       _lec__datamax_half_value;
	var_d      fract                       _ph2p_anal_log_Ep;
	parm_d     uint16                      _parm__dm_clock_control;
	fast_d     uint16 *                    _tx_rate_conv_pointer;
	var_d      fract CIRCULAR              _v92_rx_Ru_feedback_buffer [2*6*2];
	var_d      uint16                      _v90n_tx_training_shaping_a1; /* Shaping parameter a1 in signed 2.6 or 10.6 */
	debug_d    bool                        _v34s_conditional_ecc;
	var_d      uint16                      _stat__slac_model;
	var_d      uint16                      _v90n_tx_training_shaping_a2; /* Shaping parameter a2 in signed 2.6 or 10.6 */
	parm_d     uint32                      _stat__nat_wan_discards; /* WAN to LAN receive packet discard exit counter */
	var_d      sint15                      _sigbuf_ana [LPF_ORD + PITCH_FR];
	shared_d   uint16                      _sonitrol_local_mask [4];
	parm_d     uint16                      _parm__sip_response_code_retry_registration;
	var_d      uint16                      _ph2n_rx_optional_attenuation;
	var_d      sint15                      _lsd_recovery_state;
	var_d      g726_state_OBJECT           _g726_dec_state;
	var_d      bool                        _v92_tx_send_SdN_flag;
	parm_d     uint16                      _parm__jpeg_thumbnail_width;
	var_d      sint15                      _dgidet_noise_count;
	parm_d     uint32                      _stat__nat_rcv_ipsec; /* LAN to WAN receive IPsec packet type counter */
	local_d    uint16                      _fsk_interpolator_poffset;
	var_d      sint15                      _v34f_eqc_sd_DC_angle;
	var_d      sint15                      _pcm_rx_clock_phase_slave;
	var_d      uint16                      _v90_frame_tx_mapping;
	var_d      fract                       _pcm_rx_2k_AGC2_gain;
	var_d      sint15                      _picp_position;
	parm_d     bool                        _parm__ata_firmware_update_on_reset;
	fast_d     uint16                      _parm__dpbx_key_and_mask;
	var_d      sint15                      _cc_rx_lpf_coef_poffset;
	var_d      fract*                      _v34_tx_decor_poffset;
	parm_d     uint32                      _stat__nat_rcv_pppoe; /* LAN to WAN receive PPPoE packet exit counter */
	var_d      char                        _ata_pfd_processor_die_id [ATA_DIE_ID_SIZEOF];
	var_d      sint15                      _bad_lsf;
	var_d      char                        _sip_content_body_buffer [MAX_SDP_MESSAGE_SIZE];
	fast_d     sint15                      _tx_passband_poffset;
	var_d      uint16                      _v90n_tx_training_shaping_b1; /* Shaping parameter b1 in signed 2.6 or 10.6 */
	var_d      sint15                      _pcm_equalizer_fb_poffset;
	parm_d     uint32                      _parm__net_static_netmask;
	local_d    uint16                      _parm__ipbx_voip_primary_provider_unavailable;
	var_d      uint16                      _v90n_tx_training_shaping_b2; /* Shaping parameter b2 in signed 2.6 or 10.6 */
	var_d      uint32                      _speech_direct_playback_index;
	debug_d    uint16                      _mark_idle_nmd_seen;
	stat_d     uint16                      _stat__speech_enc_current_frame;
	var_d      fract32                     _ANSam_magnitude_lpf32;
	parm_d     char                        _parm__radio_lcd_menu_password [ATA_PASSWORD_SIZEOF];
	var_d      uint16                      _ipod_msg_rx_digit_pair;
	parm_d     struct tone_descriptor      _parm__ipbx_prompt_tone;
	debug_d    bool                        _v34s_reneg_allow_send_MP_within_ignore;
	var_d      sint15                      _prev_lpc_gain;
	var_d      fract32                     _ph2p_fefo_test_b_prime32;
	var_d      thread_routine_t            _pcm_rx_decision_routine;
	parm_d     uint16                      _parm__ata_web_server_port;
	parm_d     uint32                      _stat__nat_rcv_frag_created; /* LAN to WAN receive fragment forwarding created counter */
	var_d      int                         _lec__tec_data_poffset;
	var_d      uint16                      _sdt_poffset;
	var_d      uint16                      _ipod_msg_tx_sig_on_offset;
	parm_d     uint32                      _stat__nat_snd_l2tp; /* LAN to WAN send L2TP packet type counter */
	parm_d     sint15                      _parm__slac_message_waiting_mode;
	local_d    bool                        _parm__ipbx_blocked_number_service;
	parm_d     uint32                      _stat__nat_snd_non_ipv4; /* LAN to WAN send non-IPV4 packet exit counter */
	var_d      uint16                      _v92_frame_rx_bits_per_data_frame;
	var_d      fract                       _ph2p_anal_log_Gr;
	var_d      uint32                      _fsk_bitstream;
	var_d      plc_data_t                  _speech_plc_data;
	var_d      fract                       _ph2p_anal_log_Gt;
	fast_d     fract                       _faxdet_threshold_difference;
	var_d      fract CIRCULAR              _cc_rx_rate_buffer [CC_RX_RATE_SIZE * 2];
	var_d      bool                        _comn_v8_ANSpcm_detect;
	var_d      uint16                      _shadow_local_port;
	parm_d     sint15                      _parm__codec_port_impedance;
	var_d      fract                       _v23_ans_tx_passband_coefs_buffer_internal [C7K2_FSK_TX_BPF_SIZE];
	parm_d     char                        _parm__sdp_gsm_amr_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      uint16                      _v27_tx_poly_mask;
	var_d      ufract                      _V34_RXI_ADJUST;
	local_d    uint16                      _and_mask;
	var_d      sint15                      _lsf600q_s [NLSF600];
	parm_d     uint32                      _stat__nat_snd_alg_discards; /* LAN to WAN send ALG discard packet exit counter */
	var_d      uint16                      _test_s_ext;
	debug_d    uint16                      _baud_rx_shift;
	var_d      sint15                      _v34h_rx_w_1_quantize;
	var_d      fract                       _v90_shape_4_min;
	var_d      uint16                      _v34n_tx_clock_mode;
	var_d      struct uicp_match_data      _match_data [2];
	var_d      fract *                     _ph2_log_power_input_pointer;
	var_d      sint15                      _MeanE;
	var_d      uint8                       _ipod_iface_tx_buffer [RTMSC_FRAME_SIZE_MAX];
	parm_d     uint32                      _stat__net_enet_ltow_passthrough;
	var_d      fract                       _baud_edge_buffer [4];
	var_d      sint15                      _l_data_idx;
	var_d      sint15                      _v34_rx_W0_2m;
	var_d      uint16                      _v90n_rxtx_pcm_3429_option;
	var_d      fract40                     _energy_echo40;
	var_d      sint15                      _timer_CNGgen_value;
	var_d      int                         _sip_udp_sockid;
	var_d      const uint16*               _detect_tone_lengths_p;
	fast_d     Flag                        _Overflow;
	debug_d    sint15                      _monitor_state0_save_delay;
	var_d      fract CIRCULAR              _p18_lpf_buffer_real [2 * C7K2_RX_LPF_SIZE];
	var_d      uint16                      _sart_rx_private_buffer [MBX__PRIMARY_RX_SIZEOF];
	var_d      uint16                      _rd_metric;
	parm_d     uint16                      _parm__test_QCA2d_holdoff;
	var_d      SPP_data_buffer_t *         _ethernet_outgoing_ack_queue;
	var_d      powr_variable_setup_table_t _ph2p_powr_variable_setup_table [PH2P_NO_BINS_x2];
	var_d      sint15                      _saved_tx_MP_bit_count;
	parm_d     struct date_s               _parm__ata_date;
	var_d      uint16                      _v34h_rx_M_number_rings;
	var_d      sint15                      _v34_tx_un_imag;
	var_d      uint32                      _speech_direct_record_index;
	var_d      uint16                      _nat_ip_id; /* IP packet identification */
	var_d      uint16                      _v90_dpcm_dil_lsp;
	var_d      sint15                      _prev_gain_q_gain;
	parm_d     uint16                      _parm__ipbx_fc_distinctive_ring_disable;
	var_d      fract                       _sense_silence_hysteresis;
	var_d      uint16                      _v27_rx_guard_flag;
	var_d      fract                       _delta_threshold;
	var_d      fract                       _s1_detector_data [TONE_DETECTOR_DECIMATE];
	var_d      fract                       _ph2_rx_checker_bpf_buffer [2*(63+1-1)];
	parm_d     uint16                      _parm__mgcp_timer_T1;
	parm_d     uint16                      _parm__mgcp_timer_T2;
	parm_d     uint16                      _parm__mgcp_timer_T3;
	parm_d     uint16                      _parm__mgcp_timer_T4;
	var_d      fract                       _v34_BE_modify_Gp_gain;
	var_d      sint15                      _parm__speech_udp_dest_port;
	var_d      char                        _stream_char_memory [NBITS600];
	parm_d     uint16                      _parm__ctcss_enc_gain;
	var_d      sint15                      _prev_ncof [MIX_ORD + 1];
	var_d      fract                       _s1_detector_slew_rate;
	var_d      fract                       _mvxx_coefs [5];
	var_d      sint15                      _v34_tx_interpolator_size;
	const_d    fract                       _train_on_data_512_slew;
	var_d      expand8*                    _shared_btlz_tx_datap;
	parm_d     char                        _parm__ata_user_message [ATA_MESSAGE_SIZEOF];
	var_d      uint16                      _ec_error_poffset;
	var_d      fract  CIRCULAR             _v90_shape_data [2*V90_SHAPE_DATA_SIZE]; /* Investigational linear shaping data */
	var_d      uint16                      _rd_lastoff_cnt;
	var_d      uint16                      _sonitrol_local_port;
	var_d      uint16                      _v90_dpcm_dil_ltp;
	var_d      fract32                     _ptloop_phdet_error_very_slow32;
	var_d      sint15                      _v92_pcm_decode_table [256];
	var_d      char                        _picp_edit_buffer [LCD_CHAR_DISPLAY_MAX];
	parm_d     uint32                      _stat__phone_call_start_time;
	var_d      fract                       _ph2n_probing_L1_log_P_buffer [PH2P_NO_TONES];
	var_d      uint16                      _sart_tx_count;
	fast_d     uint16                      _rx_b1_frame_erase_flag;
	var_d      sint15                      _rf_fm_get_offset;
	var_d      sint15                      _V90_RX_R_REVERSAL_WAIT; /* default */
	var_d      fract                       _sdt_off_threshold;
	var_d      sint15                      _sigsave [PITCHMAX];
	var_d      sint15                      _PH2P_POWR_LX_INITIAL_ROUNDING;
	var_d      uint16                      _dma_timer;
	fast_d     sint15                      _output_sample;
	parm_d     uint32                      _stat__nat_rcv_discards; /* LAN to WAN receive packet discard exit counter */
	var_d      sint15                      _predicted_rx_xn_B1_Q_n_offset;
	var_d      fract                       _retrain_real;
	debug_d    long_silence_detect_t       _dt_silence_state;
	var_d      int                         _v34_equalizer_train_16point;
	var_d      complex CIRCULAR            _rx_lpf_buffer_complex [2 * C7K2_RX_LPF_SIZE];
	parm_d     sint15                      _parm__speech_enc_fill_slot_size;
	var_d      fract                       _V90_RX_RETRAIN_Bt_THRESHOLD;
	var_d      uint16                      _tx_trans_packets;
	var_d      uint16                      _set_dtmf_off_on_next_pass;
	var_d      fract                       _ANSam_trace_magphase_lpf_imag;
	var_d      sint15                      _g726_enc_bit_number;
	stat_d     uint16                      _stat__dm_tx_bits_per_symbol;
	fast_d     uint16                      _ph4n_tx_receive_trellis;
	var_d      sint15                      _PCM_BTR_PRESET_PHASE;
	shared_d   bool                        _dev_poh_pending [NUMBER_OF_LINES_PER_DSP];
	var_d      phase_t                     _guard_tone_increment;
	parm_d     uint32                      _stat__net_current_dns_primary_address;
	var_d      uint16                      _v34h_rx_r_bits;
	var_d      uint16                      _shadow_DNIS;
	debug_d    bool                        _fax_fx_flag;
	local_d    char                        _parm__ipbx_blocked_number_list [IPBX_LIST__BLOCKED_NUMBER_NO_OF][IPBX_DIAL_STRING_SIZEOF];
	var_d      char                        _sonitrol_ANI_DNIS_buffer [SONITROL_ANI_DNIS_BUFFER_SIZE];
	var_d      uint16                      _saved_v90trn_index_to_code;
	parm_d     bool                        _parm__ata_internal_web_server_enable;
	fast_d     sint15                      _encode_gain_exponent;
	stat_d     uint16                      _stat__speech_dec_fill_slot_size;
	parm_d     char                        _parm__ata_help_url [ATA_URL_SIZEOF];
	var_d      sint15                      _ph4n_rx_trained_qn_coef_imag [V34_NO_QN_COEFS];
	parm_d     uint16                      _parm__sdp_g723_codec_dyn_pt;
	var_d      fract                       _v92_system_ID_output;
	var_d      sint15                      _asm_decode_packed_odd;
	parm_d     uint32                      _stat__nat_wan_end_point; /* WAN to LAN receive end-point packet exit counter */
	parm_d     uint32                      _parm__net_dns_primary_address;
	var_d      uint16                      _v90n_tx_CPx_type; /* CPx value */
	var_d      uint16*                     _v90_frame_rx_dil_body_start [10];
	var_d      SBDecState                  _speex_sb_dec_state;
	var_d      fract                       _ANSam_trace_count_2100_imag;
	var_d      g723_deccngdef_t            _g723_DecCng;
	var_d      fract                       _equalized_yn_imag;
	parm_d     uint16                      _parm__sdp_g726_32_codec_dyn_pt;
	var_d      uint16                      _PH2P_BG_SAMPLE_OFFSET_LENGTH;
	fast_d     uint16                      _vppn_device_command_queue_in;
	shared_d   uint16                      _interrupt_cpu_pcount;
	var_d      fract                       _min_energy;
	var_d      sint15                      _v34_yn_error_real;
	var_d      uint32                      _nat_icmp_dst_addr; /* Destination IP adresss */
	const_d    uint16                      _ph2n_tx_v92_ITU_marks_reserved; /* INFO1a */
	var_d      sint15                      _v34_tx_yn_real;
	var_d      uint16                      _ph4n_rx_auxiliary_option;
	debug_d    uint16                      _V90_TEST_LOG_INPUT_ENABLE;
	var_d      uint16                      _legacy_response_expected;
	var_d      sint15                      _l_default_w0;
	fast_d     uint16                      _parm__report_event_mask;
	var_d      int                         _sonitrol_v34_unreliable_counter;
	parm_d     uint16                      _parm__codec_ring_detect_duration;
	parm_d     bool                        _parm__mgcp_send_response_to_src_port;
	shared_d   uint16                      _vppn_selector_next_channel;
	var_d      const uint16*               _special_data_pointer;
	var_d      uint16                      _phone_ptt_debounce_count;
	const_d    fract                       _parm__dm_v92_mse_cmn_bias;
	var_d      struct proc *               _sip_timer_proc;
	var_d      fract                       _g722_e3l_nbl;
	var_d      fract                       _v34_TRN2_MSE_precode_value;
	var_d      uint16                      _v90n_rx_constel_index [6]; /* 0 - 5 = constellation used */
	var_d      fract32                     _notch_datax32_300;
	var_d      sint15                      _frame_buffer_pointer;
	parm_d     uint16                      _parm__sdp_g728_codec_dyn_pt;
	var_d      uint16                      _ph2p_anal_maxrate;
	parm_d     uint16                      _parm__ipbx_initial_dial_duration;
	var_d      int                         _record_sample_rx_pcm;
	var_d      fract                       _DIL_probing_1st_repetition_table [DIL_PROBING_1ST_LENGTH];
	debug_d    uint16                      _v34s_short_renegotiations;
	parm_d     bool                        _parm__net_isp_pppoe_enable;
	var_d      thread_comp_t               _fg_thread_table [NUMBER_OF_FG_BLOCKS][NUMBER_OF_RX_BAUD_THREAD_COMP];
	var_d      ufract                      _xxx_rx_gain;
	var_d      sint15                      _ph2_rx_special_bpf_offset;
	fast_d     int                         _aux_rx_data;
	fast_d     uint16                      _vppn_encode_packet_byte_flag;
	var_d      fract32                     _v34_resync_vcomp_buffer_real32 [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      uint16                      _ph2p_anal_maxrate_results [PH2P_NO_SYMBOL_RATES*PH2P_NO_CARRIERS];
	var_d      uint16 *                    _nat_pkt_snap_ptr; /* Pointer to SNAP header */
	fast_d     sint15                      _sigdet_data [16];
	parm_d     bool                        _parm__ata_factory_lock_bypass_enable;
	var_d      sint15                      _fsk_rx_clock_phase_saved;
	local_d    uint16                      _v34n_rx_train_16pt;
	var_d      sint15                      _var_sp_2 [ENH_VEC_LENF];
	var_d      uint16                      _v90h_rx_residue_length;
	var_d      uint16                      _ph2n_measured_roundtrip_delay;
	var_d      fract                       _tonemute_new_exp_check;
	var_d      phase_t                     _ph2p_fefo_ws_k_buffer [PH2P_FEFO_BIN_COUNT];
	var_d      sint15                      _dcd_diversion_count;
	stat_d     uint16                      _stat__vpcm_robbed_bit_mask;
	shared_d   uint16                      _vppn_statistics_channel;
	var_d      fract                       _ph2p_anal_variance_15_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _lec__tx_output;
	var_d      fract                       _V34_SLEW_COS_RETRAIN;
	var_d      sint15                      _sdt_reversal_timeout;
	var_d      uint16                      _ipod_rx_v34_status;
	var_d      int                         _sip_prefer_tcp;
	var_d      sint15                      _orig_v8_CM_count;
	parm_d     uint16                      _parm__v92_MH_test_wait;
	shared_d   uint16                      _parm__vppn_device_vanished_debounce;
	var_d      sint15                      _bpfsp [NUM_BANDS][PITCH_FR - FRAME];
	debug_d    fpos_t                      _initial_pos;
	var_d      sint15                      _g_silenceEn;
	var_d      uint16                      _ipod_msg_rx_sig_off_offset;
	var_d      fract                       _ANSam_trace_min_imag;
	local_d    uint16                      _possible_rates;
	var_d      sint15                      _qplsp_low_rate_chn_read [LPC_ORD] ;
	fast_d     fract CIRCULAR              _rx_lpf_buffer_imag [2 * C7K2_RX_LPF_SIZE];
	var_d      uint16                      _tdt_index;
	var_d      uint16                      _ph2p_anal_maxrates_04_table [PH2P_NO_PREEMPHASIS];
	var_d      struct proc *               _sip_mesg_proc;
	var_d      fract                       _pcm_btr_coef_error;
	var_d      fract                       _guard_tone_amplitude;
	parm_d     uint16                      _parm__dm_v34_carrier_mask;
	var_d      char                        _stat__sms_message [500];
	var_d      sint15                      _retrain_limit;
	debug_d    fract                       _cp_relative_energy;
	var_d      uint16                      _PH2_TX_OFFSET_LENGTH;
	var_d      fract                       _cc_rx_PP_tone_noise_ratio;
	var_d      uint16                      _pcm_eq_which_flag;
	var_d      fract40                     _lec__sum_buffer40 [LEC__BLOCK_SIZE];
	var_d      fract                       _ec_coef_delta_buffer [V32_LOCAL_TAPS+V32_REMOTE_TAPS];
	var_d      sint15                      _Az_dec [MP1*2];
	var_d      sint15                      _lec__nlp_controller_count;
	debug_d    uint16                      _ph2n_parm_optional_tx_attenuation_enable;
	stat_d     uint16                      _stat__ipod_dtmf_detect;
	var_d      fract                       _v90_rx_ALL_energy_log;
	var_d      uint16                      _ANSam_detect_2100;
	var_d      fract CIRCULAR              _v34_tx_decor_buffer [2*V34_DECOR_TAPS];
	var_d      uint16                      _ph2_rx_dcd_integration_time;
	var_d      fract                       _pushed_demod_imag;
	var_d      fract                       _v92_system_ID_echo;
	var_d      sint15                      _current_input_imag;
	const_d    uint16                      _baud_tx_break_duration;
	var_d      fract                       _equalizer_coef_real [C7K2_RX_EQUALIZER_SIZE];
	var_d      sint15                      _renegociate_threshold;
	var_d      fract *                     _ph2p_anal_log_N_plus_start;
	parm_d     ufract                      _parm__pump_v34_transmit_level;
	parm_d     char                        _parm__sdp_speex_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      thread_routine_t            _output_filter_v34_routine;
	parm_d     sint15                      _parm__slac_message_waiting_frequency;
	parm_d     struct led_descriptor       _parm__ipbx_led_use_and_hold;
	var_d      sint31                      _ac97_dma_rx_irq;
	debug_d    uint16                      _ph1n_tx_index_ANSpcm;
	var_d      bool                        _pcm_test_disable_inner_rx_rate_double;
	var_d      uint16                      _v90n_tx_receive_constel_mapping; /* 0 = no mapping, 1 = mapping */
	parm_d     uint16                      _parm__dm_v34_symbol_difference_max;
	var_d      fract                       _lec__alpha_error;
	var_d      sint15                      _v34p_bg_block_count;
	var_d      uint16                      _sart_tx_buffer_element;
	var_d      sint15                      _cc_tx_guard_tone_phase;
	var_d      timer_list_t                _fg_timer_list [NUMBER_OF_FG_TIMERS];
	var_d      sint15                      _gpf_search_end;
	var_d      uint16                      _legacy_ssp_timer;
	var_d      sint15                      _v90_frame_tx_index;
	var_d      uint16                      _nat_tcp_header_size; /* TCP packet header size */
	var_d      int                         _current_bg_state;
	shared_d   sint15                      _dev_poh_count;
	parm_d     sint15                      _parm__line_rx_exponent;
	var_d      uint16                      _v90n_parm_tx_pcm_3429_option;
	var_d      sint15                      _pcm_xmit_deshape_poffset;
	var_d      bool                        _ph2_INFOMARKS_detect_enable;
	const_d    fract                       _dgidet_tune_equalizer_conv;
	var_d      sint15                      _old_rc [2];
	local_d    uint16                      _parm__ipbx_dial_direct;
	var_d      sint15                      _parm__speech_rtp_little_endian;
	var_d      sint15                      _g_melp_par [NF*melp_param_LEN];
	var_d      char                        _previous_call_ids [MAX_SIP_PREVIOUS_CALLS][STRSIZE_96];
	parm_d     uint16                      _parm__ipbx_fc_unattended_transfer;
	var_d      uint16                      _legacy_tx_buffer [SSP_BUFFER_SIZE];
	parm_d     bool                        _parm__mgcp_use_nat_discovery;
	var_d      uint16                      _faxparm_parm__SART_mode;
	var_d      bool                        _v92_rx_Su_disable_flag;
	parm_d     sint15                      _parm__ipbx_voice_rx_gain;
	fast_d     sint15                      _v34_rx_trellis_lookback_poffset;
	var_d      uint16                      _dtmf_match_count;
	var_d      bool                        _ph2n_rxtx_sh2_enable;
	parm_d     uint16                      _parm__ipbx_fc_block_anonymous_enable;
	parm_d     uint16                      _parm__test_tone_gain;
	const_d    fract                       _ANSAM_LPF_SLEW_1ST;
	var_d      fract                       _ANSam_trace_magphase_max_imag;
	parm_d     uint16                      _parm__enc_mode;
	parm_d     bool                        _parm__radio_fsk_mode_enable;
	var_d      bool                        _vppn_device_firmware_read;
	var_d      uint16                      _v27_rx_poly;
	var_d      uint16                      _pcm_x_law_index_to_code_convert;
	parm_d     uint16                      _parm__ipbx_fc_do_not_disturb_enable;
	var_d      uint16                      _v90_rx_dil_ucode;
	var_d      uint16                      _orig_counter;
	fast_d     fract                       _input_sample;
	shared_d   uint16                      _parm__dtmf_pad_duration;
	var_d      sdp_session_t               _sdp_parser;
	parm_d     uint32                      _parm__jpeg_capture_time;
	var_d      uint16                      _sequence_reg;
	var_d      sint15                      _special_equal_counter;
	var_d      uint16                      _v34h_rx_buffer1 [8];
	parm_d     ufract                      _parm__pump_v92_transmit_level;
	var_d      sint15                      _PCM_EQUALIZER_FF_SHIFT;
	var_d      uint16                      _v34h_rx_buffer2 [8];
	debug_d    fract                       _V34_S_SIGNAL_MAX_ENERGY;
	parm_d     fract                       _parm__dm_v34_mse_cmn_bias;
	parm_d     uint16                      _parm__nat_timeout_icmp; /* Idle seconds before ICMP NAT timeout */
	var_d      fract                       _ph2p_anal_log_adjust;
	var_d      monitor_be2_t               _monitor_be2;
	stat_d     uint16                      _stat__sart_rx_mode;
	var_d      fract                       _eqout_lagging_imag;
	var_d      sint15                      _tmp_p_e [MSVQ_M*LPC_ORD];
	var_d      uint16                      _dtmf_off_counter;
	var_d      sint15                      _stat__ipbx_speech_codec_mode;
	parm_d     char                        _parm__net_router_commands [ROUTER__COMMANDS_NO_OF][ROUTER__COMMANDS_SIZEOF];
	parm_d     char                        _parm__nat_stun_server_domain_name [NET_DOMAIN_SIZEOF];
	var_d      uint16                      _test_s_msw;
	var_d      fract                       _ph2_tx_dcd_threshold;
	var_d      uint16                      _encoded_size;
	local_d    char                        _parm__voip_default_user_name [STRSIZE_64];
	var_d      sint15                      _count_fr0;
	parm_d     uint16                      _parm__ipbx_fc_priority_forward_disable;
	fast_d     int                         _number_permanent_fg_states;
	parm_d     char                        _parm__ipbx_fxo_security_code_string [ATA_PASSWORD_SIZEOF];
	var_d      sint15                      _mem_w [M_LP];
	var_d      uint16                      _V34S_RECP_8K0_INFO0hend_to_Sdet;
	var_d      bool                        _parm__ipbx_caller_id_outbound_current_enable;
	var_d      uint16                      _v90n_rx_constel_mapping; /* 0 = no mapping, 1 = mapping */
	parm_d     bool                        _parm__repeater_talkthrough_enable;
	var_d      sint15                      _v90_rx_SdN_samples_remaining;
	parm_d     uint16                      _parm__sip_timer_registration_max;
	var_d      sint15                      _v92_rx_decoder_wait_count;
	var_d      ufract                      _v34_tx_remote_gain_adjust;
	fast_d     int                         _fg_thread_max_usage;
	stat_d     uint16                      _stat__disconnect_tone_cadence_detect_mask;
	fast_d     int                         _bg_event_insert;
	var_d      fract                       _sigdet_data16 [8];
	parm_d     uint16                      _parm__phone_sle_4428_psc;
	var_d      sint31                      _dgi_error32 [4 * 1];
	var_d      fract32                     _conv_energy32;
	parm_d     uint32                      _stat__net_pppoe_server_ip_addess;
	var_d      sint15                      _v34f_eqc_DC_angle;
	var_d      bool                        _ph2s_short_phase2_flag;
	var_d      uint16                      _parm__rtp_dtmf_generate_digit;
	var_d      fract CIRCULAR              _equalizer_buffer_imag [2 * C7K2_RX_EQUALIZER_SIZE];
	var_d      uint16                      _global_height;
	var_d      uint16                      _v90n_rx_CP_type; /* 0 = CPt, 1 = CP */
	debug_d    sint15                      _ch_seize_counter;
	var_d      sint15                      _v34_yn_perfect_real;
	var_d      sint15                      _v34_rx_xn_real;
	shared_d   uint16                      _automation_not_available;
	fast_d     int                         _aux_tx_baud;
	var_d      uint16                      _descrambler_bits_per_baud;
	var_d      uint16                      _tone_priority_ms;
	var_d      ufract                      _lec__alpha;
	var_d      fract CIRCULAR              _cc_rx_delay_buffer_real [CC_RX_DELAY_SIZE];
	var_d      uint16                      _v34n_parm_shaping_option;
	var_d      sint15                      _l_dontcare;
	var_d      fract                       _g722_e4l_szl;
	var_d      sint15                      _Vad_Min;
	var_d      fract *                     _ph2p_anal_log_Z_plus_start;
	var_d      uint16                      _mbx_rx_build_bit_cnt;
	fast_d     int                         _dc_offset_display_counter;
	var_d      bool                        _comn_v8_TONEq_done;
	fast_d     phase_t                     _rx_clock_phase;
	var_d      fract                       _V34_SLEW_SIN_BE;
	local_d    char                        _parm__ipbx_busy_forward_dial_string [IPBX_DIAL_STRING_SIZEOF];
	var_d      sint15                      _v34s_gear_counter;
	var_d      uint16                      _ph2n_probing_train_16pt;
	var_d      sint15                      _ANSam_max_tracking_count;
	fast_d     fract                       _faxdet_value_v21;
	var_d      sint15                      _v90_shape_test_offset;
	var_d      sint15                      _parm__speech_mac_ethernet_type;
	var_d      fract                       _v34f_eqc_diff_DC_magnitude;
	parm_d     bool                        _parm__sip_use_received_via_info;
	parm_d     uint16                      _parm__phone_volume_adjust_time;
	parm_d     sint15                      _parm__codec_port_rx_gain;
	var_d      sint15                      _v34_rx_xn_tilde_imag;
	var_d      uint16                      _rd_cadence_history_1;
	var_d      uint16                      _rd_cadence_history_2;
	parm_d     uint16                      _parm__ipbx_hookflash_maximum;
	debug_d    ufract                      _V34_BE_SLEW_MEDIUM;
	var_d      sint15                      _pcm_xmit_reshape_poffset;
	debug_d    sint15                      _V34_RESYNC_LOG2_MEASURE_ADJUST;
	parm_d     struct led_descriptor       _parm__dpbx_led_call_forward;
	var_d      fract                       _v34_pnt3_MSE_value;
	var_d      uint16                      _v92n_rx_prefilter_gain;
	var_d      uint16                      _ipod_iface_rx_next_seqnum;
	var_d      fract                       _v34_resync_data_buffer_real [2*(V34_RESYNC_Nx2_plus_1)];
	var_d      uint16                      _ph1_tx_ANSpcm_exponent;
	stat_d     sint15                      _stat__speech_enc_frame_based_active;
	parm_d     struct tone_descriptor      _parm__ipbx_pstn_call_waiting_tone_default;
	parm_d     uint16                      _parm__spk_monitor_tx_gain;
	var_d      uint16                      _sonitrol_caller_name;
	var_d      fract32                     _v34_resync_vcomp_buffer_imag32 [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      uint16*                     _v90h_rx_control_pointer;
	parm_d     sint15                      _parm__slac_message_waiting_transition;
	parm_d     char                        _parm__ata_boot_rom_revision [ATA_REVISION_SIZEOF];
	parm_d     uint16                      _parm__dtmf_detector_period;
	parm_d     sint15                      _parm__speech_dec_slot_cnt;
	var_d      fract                       _g722_d3h_nbh;
	var_d      uint16 * CIRCULAR           _bulk_delay_buffer_pntr;
	var_d      uint16                      _ipod_htd_fbdnt_payload_size;
	var_d      int                         _echo_canceller_display_counter;
	shared_d   uint16                      _vppn_packet_selector_state;
	var_d      uint16                      _parm__rtp_dtmf_generate_duration;
	var_d      fract40                     _sigdet_data40 [2];
	parm_d     uint16                      _parm__camera_number;
	var_d      uint16                      _v90_tx_ph34_state;
	var_d      fract32                     _notch_datay32_420;
	var_d      sint15                      _ph2p_bg_sample_offset;
	parm_d     uint32                      _stat__nat_snd_udp; /* LAN to WAN send UDP packet type counter */
	var_d      sint15                      _l_prev_par [melp_param_LEN];
	var_d      uint16                      _lec__nlp_cng_detect;
	var_d      sint15                      _parm__speech_report_mask;
	stat_d     sint15                      _stat__speech_drop_frame_candidate;
	shared_d   uint16                      _sport0_shift_count;
	var_d      uint16                      _current_rate;
	var_d      fract                       _pcm_btr_measurement_real;
	var_d      sint15                      _g711_rx_dtx_prev_active;
	var_d      uint16                      _local_buffer_pointer_start;
	debug_d    sint15                      _silence_valid;
	parm_d     uint16                      _parm__ipbx_fc_busy_forward_disable;
	fast_d     uint16*                     _asm_decodep;
	parm_d     uint16                      _parm__net_assigned_mtu;
	const_d    fract                       _equalizer_slew_fast;
	parm_d     char                        _parm__net_ddns_host_name [NET_DOMAIN_SIZEOF];
	shared_d   int                         _impedance_monitor_last_fail_state;
	var_d      uint16                      _rx_dtmf_count;
	const_d    sint15                      _REVERSAL_TIMEOUT_INIT;
	var_d      sint15*                     _lsp_new_q_ptr;
	var_d      fract                       _v34_pnt0_MSE_value;
	parm_d     uint32                      _stat__nat_wan_firewalled; /* WAN TO LAN receive firewalled packet exit counter */
	var_d      uint16                      _parm__fxpmp_silence_duration;
	parm_d     uint16                      _parm__ipbx_fc_busy_number_redial;
	var_d      sint15                      _answ_v8_JM_count;
	local_d    bool                        _parm__ipbx_distinctive_ring_service;
	parm_d     uint16                      _parm__sip_timer_invite_expires;
	parm_d     bool                        _parm__ctcss_enc_enable;
	var_d      uint16                      _v92n_tx_CPd_word;
	var_d      thread_routine_t            _pcm_eq_errtine;
	parm_d     sint15                      _parm__speech_enc_frame_rate;
	var_d      fract32                     _ph2_rx_signal_detect_filter32;
	fast_d     phase_t                     _tx_clock_phase_remote;
	var_d      sint15                      _V34_RXI_COUNT;
	var_d      sint15                      _lookback_output_real;
	var_d      sint15                      _v34_tx_xn_local_real;
	var_d      fract                       _PH2P_ANAL_16PT_NOISE_LIMIT;
	var_d      sint15                      _sync_bit;
	var_d      uint16*                     _v34n_rx_INFO1c_body [22];
	debug_d    uint16                      _V34S_RUN_8K0_ONE_SECOND_TIME;
	var_d      fract                       _v34_rx_zn_tilde_real;
	parm_d     char                        _parm__sip_distinctive_ring_names [IPBX_STANDARD_RING_TYPES][32];
	var_d      fract                       _THD_measurement_noise;
	var_d      fract32                     _ph2p_fefo_test_delta32;
	parm_d     struct tone_descriptor      _parm__ipbx_key_confirmation_tone;
	var_d      fract                       _pcm_AL_value;
	shared_d   uint16                      _dprmbx_outgoing_data_sent;
	parm_d     uint16                      _parm__ctcss_dec_frequency;
	var_d      sint15                      _prev_ma;
	debug_d    fract                       _CONVERT_AGC_1_ENERGY_TARGET_LOG;
	var_d      fax_save_state*             _fax_save_state_old;
	var_d      fract                       _g722_rxs_qmf_space [RX_QMF_SIZE * 2];
	var_d      uint16                      _last_sig_level;
	debug_d    uint16                      _sart_tx_hybrid_packed_length;
	const_d    fract                       _ec_fast_slew;
	var_d      sint15                      _v90_rx_R_reversal_wait;
	var_d      sint15                      _tilt_del [1];
	var_d      uint16                      _sonitrol_ANI;
	fast_d     uint16                      _parm__vppn_device_timeslot;
	var_d      sint15                      _V90_RX_RETRAIN_DETECT_LIMIT;
	var_d      uint16                      _ata_led_use_mask_ipbx;
	var_d      uint16 *                    _nat_pkt_ip_tun_ptr; /* Pointer to IP tunnel header */
	var_d      fract32                     _v34_rx_yn_equalized_real32;
	parm_d     uint32                      _stat__nat_rcv_alg_delivers; /* LAN to WAN receive ALG delivers packet exit counter */
	var_d      uint16                      _going_up;
	parm_d     uint16                      _parm__selcall_enc_tone_period;
	var_d      ufract                      _V34_TXI_ADJUST;
	parm_d     struct tone_descriptor      _parm__ipbx_call_holding_rering_tone;
	var_d      uint16                      _ipod_rx_frame_counter;
	parm_d     bool                        _parm__net_dns_parallel_search_mode;
	var_d      fract                       _jitter_jitter_imag;
	parm_d     uint16                      _parm__sdp_g722p2_codec_dyn_pt;
	var_d      fract                       _equalizer_leading_imag [2*((xV34_XX_EQUALIZER_SIZE)/2)];
	var_d      fract                       _v90_rx_retrain_delay_buffer [V90_RX_RETRAIN_DELAY_SIZE];
	persist_d  uint16                      _v34n_rx_hi_carrier_option;
	var_d      sint15                      _sh_Acf [NB_CURACF];
	var_d      complex                     _btrec_p2400;
	var_d      fract                       _V34_TX_PRE_EMPH_COEFS [xC8K0_V34_XX_TX_BPF_SIZE];
	var_d      sint15                      _lec__nlp_activity_counter;
	var_d      uint16                      _v34_frame_rx_receive_crc;
	var_d      uint16                      _v90_tx_MP_frame_sent;
	var_d      uint16                      _CID_data;
	shared_d   fract32                     _impedance_monitor_tx_power32;
	var_d      fract                       _v34_resync_mean_buffer_real [1*(V34_RESYNC_Nx2_plus_1)];
	parm_d     uint32                      _stat__nat_wan_no_translation; /* WAN to LAN receive no translation exit counter */
	var_d      uint16                      _ipod_htd_voice_flags;
	parm_d     uint32                      _stat__nat_snd_ip_forward; /* LAN to WAN send IP forwarding success packet exit counter */
	parm_d     bool                        _parm__codec_disconnect_polarity_enable;
	var_d      uint16                      _rf_dma_debug;
	var_d      powr_measurement_t          _tx_measurment_buffer_1;
	debug_d    fract                       _debug_fract10;
	parm_d     uint16                      _parm__voip_echo_canceller_tail_length;
	var_d      uint16                      _rd_post_event;
	var_d      uint8                       _sonitrol_wiznet_workaround_ip [4];
	local_d    uint16                      _v34n_tx_remote_to_local_maxrate;
	parm_d     uint16                      _stat__caller_id_msg_cksum;
	parm_d     bool                        _parm__codec_disconnect_tone_2_enable;
	var_d      fract                       _v34_pp_result_log_table [CC_RX_PP_ANALYSIS_SIZE];
	persist_d  uint16                      _v34n_tx_hi_data_rate_option;
	var_d      uint16                      _ipod_msg_xx_payload_buffer [IPOD_MAX_PAYLOAD_SIZE];
	var_d      fract CIRCULAR              _cc_rx_lpf_buffer_imag [CC_RX_LPF_SIZE*2];
	var_d      uint16                      _v32ter_nonlinear_control;
	var_d      uint16                      _v34h_tx_half_data_frame_counter;
	persist_d  uint16                      _ph2n_rx_receive_clock;
	parm_d     struct ring_descriptor      _parm__ipbx_call_station_ring_default;
	var_d      uint16                      _v34h_tx_r_bits;
	var_d      event_t                     _ipbx_digit_detect_end_event;
	shared_d   uint16                      _sonitrol_remote_lcfw_port;
	var_d      tone_detector_vars_t        _s1_detector_variables [NUMBER_S1_DETECTORS+1];
	debug_d    uint16                      _V34S_LEN_T_2ND_CHECK_WAIT;
	var_d      uint16                      _ph2n_rx_use_shaping;
	fast_d     uint16                      _vppn_device_command_ack_index;
	parm_d     uint16                      _parm__sip_timer_registration_min;
	var_d      uint16                      _sart_tx_read_index;
	var_d      struct vppn_device_statistics_s _stat__vppn_device_statistics;
	var_d      sint15                      _saved_rx_mapper_loop_counter;
	var_d      fract                       _dtmf_col_harmonic;
	var_d      sint15                      _scal_res2_buf [PIT_MAX+L_SUBFR];
	var_d      sint15                      _parm__speech_rtp_tone_replace_audio; /* RTP_TONE__BIT__DTMF | RTP_TONE__BIT__ANS */
	parm_d     char                        _parm__ata_lcd_menu_password [ATA_PASSWORD_SIZEOF];
	parm_d     uint32                      _stat__net_current_ip_address;
	fast_d     uint16                      _dtmf_detector_counter;
	var_d      uint16                      _parm__rtp_vocal_to_net_payload_map [RTP_NUM_PAYLOAD_MAPPINGS];
	var_d      uint16                      _n16_bits;
	parm_d     struct tone_descriptor      _parm__ipbx_message_wait_dial_tone;
	parm_d     sint31                      _parm__sip_incoming_resubscribe_interval;
	var_d      fract                       _g722_d4h_bh [7];
	var_d      ufract                      _v34_resync_total_buffer [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract                       _cc_tx_eye_map_gain;
	var_d      char *                      _parm__ipbx_dial_string;
	stat_d     sint15                      _stat__speech_enc_mbx_cnt;
	var_d      sint15                      _prev_pitch_pitch_vq;
	var_d      uint32                      _parm__tripwire_audio_record;
	const_d    fract                       _BAUD_AGC_REFERENCE;
	var_d      uint16*                     _v34h_rx_e0_last_pointer;
	var_d      sint15                      _descrambler_mask_table [6];
	var_d      fract                       _convert_adjust_output_gain;
	var_d      fract                       _v90_rx_retrain_Bt_energy_log;
	const_d    fract                       _energy_delta_threshold_v17;
	parm_d     uint16                      _parm__dm_v92_negotiation;
	var_d      sint15                      _lec__td_tone_det_cnt;
	var_d      sint15                      _old_A [M_LP+1];
	var_d      sint15                      _v34_bulk_extra_input_offset;
	var_d      uint16                      _v34h_rx_V0_m_register;
	var_d      fract                       _p18_demod_real;
	var_d      uint16                      _cmr_notch_count;
	var_d      uint16 *                    _nat_pkt_icmp_ip_ptr; /* Pointer to ICMP IP header */
	parm_d     bool                        _parm__slac_message_waiting_type;
	var_d      uint16*                     _v34n_rx_MP0_body [18];
	var_d      bool                        _v34_frame_rx_E_found;
	var_d      uint16                      _stat__daa_ring_state;
	var_d      sint15                      _postHPFOutHis_hi [2];
	var_d      bool                        _v92_MH_timeout_flag;
	fast_d     uint16                      _vppn_decode_packet_index;
	var_d      uint16                      _ipod_msg_tx_sig_level;
	var_d      sint15                      _lookback_input_real;
	var_d      uint16                      _timer_flag;
	fast_d     tv_union_t                  _thread_variable;
	stat_d     uint16                      _stat__ipod_chan_state;
	var_d      uint16                      _ph2p_anal_maxrates_10_table [PH2P_NO_PREEMPHASIS];
	var_d      sint15                      _var_sp_av [ENH_VEC_LENF];
	var_d      sint15                      _sense_silence_keep;
	parm_d     struct led_descriptor       _parm__ipbx_led_use_and_waiting;
	var_d      fract                       _DIL_probing_pad_ot_table [DIL_PROBING_PAD_LENGTH];
	var_d      fract                       _pcm_pstfilter_ff;
	const_d    uint16                      _v17_ept_length;
	var_d      fract                       _v34s_prev_prev_phase_roll_second;
	parm_d     bool                        _parm__sip_refer_authentication;
	var_d      fract                       _g722_d4h_dh [7];
	var_d      sint15                      _ph2_INFO_detect_state;
	var_d      uint16                      _new_scores_poffset;
	var_d      fract                       _sdt_peak_hold;
	var_d      sint15*                     _lsp_old_q_ptr;
	var_d      fract                       _metric0;
	var_d      fract                       _g711a_plc_overlapbuf [G711_PLC_MAX_FRAME_SIZE];
	var_d      fract                       _metric1;
	var_d      uint16                      _send_to_connect;
	var_d      fract                       _g722_d4h_szh;
	var_d      fract                       _metric2;
	debug_d    sint15                      _fax_continuous_silence_counter;
	var_d      fract                       _metric3;
	var_d      fract                       _tonemute_delay_buffer [TONEMUTE_DELAY_SIZE];
	var_d      fract                       _g722_d4h_oldrh;
	var_d      sint15                      _pcm_folding_half_length;
	fast_d     int                         _fg_thread_offsets [NUMBER_OF_FG_BLOCKS+1];
	var_d      sint15                      _qla [ENH_VEC_LENF];
	var_d      sint15                      _l_firstTime;
	var_d      uint16                      _cc_rx_pc_is_also_running_flag;
	var_d      sint15                      _sh_sid_sav;
	var_d      sint15                      _ph2s_INFO0_ack_counter;
	var_d      uint16                      _FALL_fallback_flag;
	var_d      sint15                      _v92_rx_decoder_ep_poffset;
	var_d      bool                        _fsk_run_dcd_monitor;
	fast_d     uint16 *                    _rx_rate_conv_pointer;
	var_d      uint16*                     _v92_rx_eye_pointer;
	var_d      bool                        _ata_check_code;
	var_d      int                         _g722_rx_qmf_data_offset;
	var_d      uint16                      _PCM_LEN_8K0_MIN_GEAR_TRAIN; /* 1300 ms */
	var_d      sint15                      _g600_s [2*NF600];
	shared_d   fract                       _impedance_monitor_future_rx [IMPEDANCE_MONITOR_FUTURE_RX_SIZE];
	var_d      uint16                      _lec__doubletalk_probe;
	var_d      uint16                      _faxparm_parm__CED_generate;
	var_d      uint16                      _g711b_cng_flag;
	fast_d     uint16                      _faxdet_ansam_count;
	var_d      bool                        _v34_rx_B1_enable_flag;
	var_d      uint16                      _ph2_AB_edge_correl_last;
	shared_d   uint16                      _dpbx_previous_service;
	var_d      sint15                      _l_erase;
	var_d      fract                       _saved_precalculated_correct;
	var_d      sint15                      _V90_SdN_REMAIN;
	var_d      sint15                      _bid_dtx [M_LP];
	var_d      fract*                      _g711a_plc_pitchbufstart;
	parm_d     uint16                      _parm__dm_carrier_detect_duration;
	var_d      uint16                      _v34n_rx_MD_length;
	var_d      uint16                      _ipod_sec_timer;
	var_d      uint32                      _v34h_tx_z8_table [276];
	var_d      uint16                      _parm__jpeg_delete_fifo;
	parm_d     bool                        _parm__test_tone_enable;
	parm_d     uint16                      _parm__ipbx_brief_pause_duration;
	var_d      sint15                      _fsk_rx_clock_cycles_saved;
	var_d      sint15                      _SN_LT0_shift;
	parm_d     char                        _parm__sdp_mpeg4_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      uint16                      _pcm_eq_flag;
	var_d      phase_t                     _fsk_local_interpolator_buffer_offset [C7K2_FSK_TX_INTERPOLATOR_SIZE * 2];
	var_d      sint15                      _v90h_data_frame_bit_count;
	var_d      uint32                      _ata_random_delay_cfg;
	parm_d     struct led_descriptor       _parm__ipbx_led_call_holding;
	shared_d   int                         _impedance_monitor_future_rx_offset;
	var_d      sint15                      _v34_frame_rx_bit_count;
	var_d      sint15                      _v34_rx_pn_tilde_real;
	parm_d     fract                       _parm__dtmf_row_no_tone_level;
	var_d      uint16                      _ph2n_tx_v92_mode_bits;
	shared_d   uint16                      _interrupt_running_fg;
	var_d      sint15                      _circb_index;
	var_d      fract                       _temp2_ilbc_buffer [BLOCKL_MAX];
	var_d      fract                       _V90_DECN_RBS_BIAS_PARAMETER;
	var_d      uint16                      _v90n_rx_pcm_3429_option;
	var_d      fract                       _v34_TRN1_MSE_value;
	fast_d     fract                       _equalized_imag;
	var_d      fract                       _train_on_data_switch;
	debug_d    energy_buffer_t             _monitor_sample_agc_2 [6];
	var_d      fract                       _ptloop_1st_order_slew;
	var_d      sint15                      _l_good_pitch [3];
	var_d      fract                       _cc_rx_ANAL_angle;
	var_d      uint16                      _v90_shape_current_state;
	shared_d   fract                       _impedance_monitor_future_tx [IMPEDANCE_MONITOR_FUTURE_TX_SIZE];
	var_d      sint15                      _Ksi_min_var;
	var_d      uint16                      _v92n_rx_wait_CPu;
	var_d      uint16                      _ph4n_tx_ITU_bit_reserved;
	var_d      fract                       _v34_BE_Gn;
	local_d    bool                        _sdt_found_detect_flag;
	var_d      fract                       _v34_BE_Gp;
	var_d      sint15                      _fsk_ANSam_enable;
	parm_d     uint16                      _parm__mpeg4_rate_control_mode;
	var_d      uint16                      _ph2n_sm_INFO1c_end_delay;
	var_d      sint15                      _postHPFOutHis_lo [2];
	var_d      sint15                      _v92_test_client_type;
	var_d      sint15                      _circb_shift [NUM_MINWIN][ENH_VEC_LENF];
	var_d      int                         _start_data_flag;
	var_d      bool                        _ata_need_mac;
	local_d    bool                        _parm__ipbx_blocked_number_enable;
	var_d      uint16                      _pcm_rx_RBS_current_symbol;
	var_d      sint15	*                    _cbk_mst1_s;
	local_d    bool                        _parm__ipbx_priority_forward_service;
	parm_d     uint16                      _parm__mgcp_timer_retransmition_max;
	parm_d     uint32                      _parm__net_dhcp_server_rebinding_time;
	local_d    char                        _parm__ipbx_line_name [NUMBER_OF_LINES_PER_DSP][STRSIZE_64];
	parm_d     uint32                      _stat__nat_rcv_pptp; /* LAN to WAN receive PPTP packet type counter */
	var_d      sint15                      _asm_ans_seen;
	var_d      uint16                      _ph4n_rx_primary_channel_maxrate;
	fast_d     bool                        _baud_tx_16_bit_mode;
	var_d      sint15                      _dgi_ref_meanA [4 * STATISTIC_LEN];
	var_d      fract32                     _v34_rx_yn_equalized_imag32;
	var_d      uint32                      _v34h_tx_g4_table [70];
	var_d      sint15                      _dgi_ref_meanB [4 * 2];
	var_d      uint16                      _vppn_device_firmware_address;
	var_d      bool                        _sart_rx_overflow;
	var_d      uint16                      _pcm_btr_enable_postset_flag;
	var_d      sint15                      _old_wsp [L_FRAME+PIT_MAX];
	var_d      fract                       _g722_tx_qmf_space [G722_QMF_ORDER * 2];
	debug_d    uint16                      _saved_scrambler_input;
	shared_d   bool                        _parm__ipbx_priority_forward_enable;
	var_d      sint15                      _lec__data_size_exp_adjust;
	var_d      uint16                      _ipod_command_fnbdt_enable;
	var_d      fract                       _g722_rxd_qmf_space [RX_QMF_SIZE * 2];
	var_d      fract  CIRCULAR             _v90_shape_coefs [2*(5)];
	var_d      uint16                      _v34h_rx_residue;
	fast_d     uint16                      _baud_tx_data_unit;
	var_d      sint15                      _sense_rate_reduce_counter;
	var_d      uint16                      _V90S_LEN_8K0_DIL_STATISTICS;
	parm_d     uint32                      _parm__net_dhcp_server_renewal_time;
	shared_d   uint16                      _sonitrol_line_fail_count;
	debug_d    int                         _tone_detector_num_tones;
	var_d      sint15                      _dec_Vad;
	var_d      sint15                      _tonemute_poffset;
	var_d      fract                       _tone_detector_data [TONE_DETECTOR_DECIMATE];
	var_d      fract                       _g722_enc_shigh;
	var_d      fract                       _affine_real;
	var_d      sint15                      _l_codewd74 [7];
	debug_d    uint16                      _ph2_rx_btrec_clock_state;
	var_d      uint16 (*                   _line_tx_intp) (void);
	parm_d     sint15                      _parm__ata_time_zone;
	var_d      uint16                      _ph2n_tx_required_attenuation;
	var_d      uint16                      _v34_symbol_diff_encode_data;
	parm_d     struct ring_descriptor      _parm__ipbx_message_waiting_ring_splash;
	var_d      uint16                      _rf_tuning_enable;
	var_d      uint16                      _rf_dma_difference;
	debug_d    sint15                      _V34_EQUALIZER_SCALE;
	var_d      sint15                      _dec_freq_prev [MA_NP][M_LP];
	var_d      sint15                      _g729_test_compressed_data [80];
	var_d      bool                        _parm__ipbx_call_waiting_current_enable;
	parm_d     bool                        _parm__net_static_config_enable;
	var_d      sint15                      _fsk_correlator_flag_holdoff;
	var_d      sint15                      _gpf_index_offset;
	var_d      sint15                      _v92_rx_MD_length;
	var_d      bool                        _v8_tx_QC_data_flag;
	parm_d     uint32                      _stat__phone_timer_elapsed_time;
	parm_d     char                        _parm__ata_processor_die_id [ATA_DIE_ID_SIZEOF];
	var_d      sint15                      _v34_rx_interpolator_size;
	var_d      uint16                      _test_input_index;
	var_d      fract                       _monitor_be2_offset;
	var_d      fract                       _g168_err_average;
	var_d      uint16*                     _v92n_tx_CPd_body_start [14];
	var_d      sint15                      _l_codewd84 [8];
	var_d      fract                       _lec__alpha_rxx_mag;
	var_d      uint16                      _ipod_command_fax_enable;
	parm_d     uint16                      _parm__selcall_enc_lead_in;
	var_d      fract                       _pcm_HI_MSE_value;
	var_d      uint16                      _v90n_tx_nominal_power;
	var_d      uint16                      _tx_train_point_B;
	var_d      uint16                      _tx_train_point_D;
	debug_d    sint15                      _V34S_PARTIAL_CONVERGENCE_THRESHOLD;
	var_d      sint15                      _lsfq [M_LP];
	var_d      sint15                      _prev_pitch_sc_ana;
	var_d      uint16                      _coder_frame_length;
	shared_d   bool                        _stat__vppn_epoch_clock_indication;
	var_d      fract                       _pcm_rx_TRN1C_log_energy;
	stat_d     uint32                      _stat__speech_rtp_timestamp;
	var_d      sint15                      _g_hp1_coeff_sec1 [6];
	var_d      sint15                      _g_hp1_coeff_sec2 [6];
	var_d      sint15                      _g_hp1_coeff_sec3 [6];
	var_d      fract32                     _agc_2_lpf32;
	var_d      sint15                      _bpviq [NF600][NUM_BANDS];
	var_d      uint16                      _ipod_htd_voice_payload_size;
	parm_d     uint16                      _parm__ipbx_fc_outgoing_block_enable;
	var_d      fract32                     _pcm_DC_offset_sum_32;
	var_d      uint16                      _lec__cng_train_freeze;
	parm_d     uint16                      _parm__cmr_notch_select;
	parm_d     uint16                      _parm__v8__vpcm_availability;
	fast_d     uint16                      _parm__analog_loopback;
	var_d      fract                       _local_ec_slew;
	var_d      sip_subscribe_info_t        _subscribe_parser;
	var_d      sint15                      _parm__speech_enc_host_flag;
	local_d    fract                       _ph2p_L1_log_power_display_buffer [PH2P_NO_BINS_x2];
	var_d      uint16                      _v90n_rx_apcm_data_rate_option [2]; /* 2 words in V92 */
	var_d      sint15                      _v34_tx_remote_data_enable;
	var_d      fract32                     _ANSam_magnitude_min32;
	var_d      uint16                      _v34h_rx_m_ijk_ring_index_buffer [8];
	var_d      const fract *               _ph2p_anal_preemph1_pointer;
	var_d      sint15                      _prev_tilt;
	parm_d     bool                        _parm__sip_subscribe_authentication;
	debug_d    uint16                      _V34S_ORIG_8K0_1RT_Jsrt_to_S_SNdet;
	var_d      fract                       _double_output0;
	var_d      sint15                      _alphacorr;
	var_d      fract                       _double_output1;
	shared_d   uint16                      _vppn_previous_device_temporary_id [PKT_VPPN__SIZEOF_TEMPORARY_ID];
	var_d      fract                       _ph2n_probing_Gr_gain;
	const_d    fract                       _delta_energy_threshold;
	var_d      uint16*                     _v90_frame_tx_cp_body_start [32];
	local_d    fract CIRCULAR              _fsk_interpolator_buffer_real [2 * C7K2_FSK_RX_INTERPOLATOR_SIZE];
	debug_d    uint16                      _monitor_state_value;
	var_d      sint15                      _v92_system_ID_energy_nrm;
	var_d      sint15                      _dtmf_unclamp_delay;
	local_d    sint15                      _asm_decode_mbx [ASM_DECODE_SLOT_CNT_MAX * ASM_DECODE_SLOT_SIZE_MAX];
	var_d      uint16                      _v90n_tx_CP_type; /* 0 = CPt, 1 = CP */
	debug_d    uint16                      _v34n_sm_INFO1c_end_delay;
	var_d      sint15                      _guard_tone_enable;
	parm_d     char                        _parm__ata_firmware_revision [ATA_REVISION_SIZEOF];
	parm_d     uint16                      _parm__sdp_cn_codec_dyn_pt;
	var_d      sint15                      _v34_tx_xn_real;
	var_d      sint15                      _top_lpc [LPC_ORD];
	var_d      sint15                      _pcm_equalizer_ff_poffset;
	parm_d     uint16                      _stat__v92_upstream_digital_attenuation;
	var_d      fract                       _pcm_AL_peak_MSE_max [V34_TRN2_MSE_STACK_SIZE];
	fast_d     ufract                      _parm__pump_transmit_level;
	var_d      uint16                      _ph2n_probing_maxrate [2*(V34N_MAX_SYMBOL + 1)];
	var_d      uint16                      _ipod_dth_coded_speech_buffer [IPOD_MAX_PAYLOAD_SIZE];
	shared_d   uint16                      _parm__vppn_device_registration_next [PKT_VPPN__SIZEOF_REGISTRATION_ID];
	fast_d     sint15                      _faxdet_data_ansam_cntr;
	debug_d    bool                        _v34s_reneg_init_S_to_SN_to_retrain;
	parm_d     sint15                      _parm__dtmf_low_tone_gain;
	var_d      fract   CIRCULAR            _pcm_equalizer_ep_buffer [2*PCM_EP_EQUALIZER_SIZE_MAX];
	var_d      fract                       _g722_d3l_nbl;
	persist_d  uint16                      _ph2n_rx_2800_option;
	var_d      fract                       _v92_system_ID_codec_in;
	var_d      uint16                      _uicp_tone_played;
	var_d      sint15                      _sense_silence_change;
	var_d      sint15                      _parm__speech_rtp_dtmf_payload_type;
	parm_d     char                        _parm__sip_answ_user_name [STRSIZE_64]; /* answering machine From: header */
	debug_d    uint16                      _sart_tx_hybrid_packed_mode;
	parm_d     char                        _parm__sdp_g711a_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      fract                       _p18_baud_UVW_imag [3];
	var_d      bool                        _picp_menu_item_edit;
	parm_d     char                        _parm__sdp_gsm_efr_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      fract                       _v92_rx_decoder_ep_alpha_gain;
	var_d      fract                       _lec__tec_error [LEC__TEC_BLOCK_SIZE];
	shared_d   struct vppn_device_info_s   _stat__vppn_device_info [NUMBER_OF_LINES_PER_DSP];
	var_d      fract                       _v92_rx_decoder_ff_coefs [V92_RX_DECODER_FF_SIZE]; /* MEMORY_AVAILABLE */
	var_d      fract                       _pre_ec_power;
	parm_d     sint15                      _parm__speakerphone_rx_gain;
	local_d    uint16                      _bg_svalue_queue [NUMBER_OF_BG_EVENTS];
	fast_d     phase_t                     _tx_clock_cycles_per_sample;
	var_d      fract                       _ANSam_trace_magphase_imag;
	var_d      sint15                      _phone_speakerphone_tx_volume;
	var_d      uint16                      _v90n_tx_receive_attenuation; /* TX/Codec TX signal RMS in unsigned 3.13 */
	var_d      fract                       _ph2p_anal_variance_14_table [PH2P_NO_PREEMPHASIS];
	var_d      fract32                     _v90_shape_4_min32;
	var_d      uint32                      _pattern_test_delay32;
	var_d      fract40                     _energy_total40;
	var_d      uint16                      _ph2_tx_baud_current;
	var_d      fract                       _cc_rx_S_center_edge_ratio;
	var_d      fract   CIRCULAR            _pcm_equalizer_ff_buffer [2*PCM_FF_EQUALIZER_SIZE_MAX];
	var_d      uint16                      _sart_tx_private_buffer [MBX__PRIMARY_TX_SIZEOF];
	var_d      fract32                     _detect_energy_lpf1_32;
	var_d      fract                       _tonemute_old_exp_check;
	var_d      sint15                      _V34_TXI_COUNT;
	var_d      sint15                      _bulk_delay_local_poffset;
	parm_d     uint32                      _stat__nat_snd_requests; /* LAN to WAN send packet entry counter */
	debug_d    uint16                      _sync_state;
	var_d      uint16*                     _v34n_tx_INFO1a_body [9];
	parm_d     uint32                      _parm__net_private_netmask;
	var_d      uint16                      _ph2p_anal_maxrates_03_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _v34s_rev_count;
	var_d      uint16                      _ph2n_rx_acknowledge;
	shared_d   uint16                      _interrupt_cpu_icount;
	var_d      uint16                      _v34h_tx_M_number_rings;
	var_d      uint16                      _faxparm_active__SART_mode;
	parm_d     uint32                      _stat__nat_rcv_frag_required; /* LAN to WAN receive fragmentation required packet exit counter */
	local_d    char                        _parm__ipbx_speed_dial_array [IPBX_LIST__SPEED_DIAL_NO_OF][IPBX_DIAL_STRING_SIZEOF];
	var_d      fract                       _convert_agc_2_output_log;
	parm_d     uint16                      _parm__dm_v90_shaping_lookahead;
	var_d      sint15                      _voicedEn;
	var_d      uint16                      _ph2_INFO_correl_last;
	var_d      sint15*                     _parm__speech_enc_host_addr;
	var_d      fract CIRCULAR              _rate_reduction_buffer_real [2 * C7K2_FSK_REDUCE_LPF_SIZE];
	var_d      sint15                      _pcm_btr_gain_exponent;
	shared_d   uint16                      _sonitrol_lc_type1_shutdown;
	var_d      fract                       _v29_save_equalized_real;
	var_d      fract                       _v34_BE_log_Gp_prev;
	var_d      sint15                      _ALPHA0;
	var_d      fract                       _faxdet_data_grl [4];
	var_d      uint16*                     _v92n_rx_MH_body [2];
	parm_d     char                        _parm__sdp_g729_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	local_d    uint16                      _v34n_tx_data_rate;
	var_d      fract                       _v34_BE_neg_log_magnitude;
	var_d      fract                       _PCM_BTR_FREQ_ERROR_RATIO;
	var_d      sint15                      _pastCoeff [MP1];
	fast_d     fract CIRCULAR              _tx_rate_conv_data_buffer [2 * RATE_CNV_TX_SIZE];
	parm_d     uint16                      _stat__caller_id_msg [CID_RX_BUFFER_LENGTH];
	var_d      uint16                      _code_load_duration;
	var_d      uint16                      _v34h_rx_q_bits_per_2D_subgroup;
	var_d      fract                       _ph2n_probing_receive_level;
	parm_d     char                        _parm__sdp_session_owner [SDP_SESSION_NAME_LENGTH];
	stat_d     uint16                      _stat__speech_rx_dtx_flag;
	var_d      uint16                      _parm__rtp_net_to_vocal_payload_map [RTP_NUM_PAYLOAD_MAPPINGS];
	var_d      sint15                      _v92_system_ID_modulo_rbs;
	var_d      fract                       _pcm_ec_conv_energy_log;
	parm_d     uint16                      _parm__mgcp_timer_retransmition_min;
	var_d      sint15                      _lsp_new_dtx [M_LP];
	var_d      sint15                      _ph2p_powr_SB_power_adjust;
	var_d      sint15                      _gpf_RRexp;
	parm_d     bool                        _parm__net_dhcp_server_enable;
	parm_d     uint16                      _parm__speech_g711_transition;
	parm_d     bool                        _parm__ipbx_fxo_pstn_call_enable;
	parm_d     uint16                      _parm__sip_nat_keep_alive_interval;
	var_d      sint15                      _enc_seed;
	stat_d     sint15                      _stat__speech_dec_frame_mtr;
	var_d      fract                       _pcm_saved_point;
	const_d    fract                       _monitor_sample_fast_relative_threshold;
	var_d      fract                       _pcm_eq_error;
	stat_d     sint15                      _stat__speech_enc_overflow_cnt;
	var_d      sint15                      _tone_generator_silence;
	var_d      bool                        _ata_first_update;
	var_d      fract *                     _ph2p_anal_maxrate_lookup_pointer;
	var_d      fract                       _ph2p_anal_log_R_buffer [PH2P_NO_PREEQ_BINS];
	parm_d     uint16                      _parm__sip_response_code_sit1;
	var_d      fract                       _affine_ptloop_imag;
	parm_d     uint16                      _parm__sip_response_code_sit2;
	var_d      uint16                      _PCM_LEN_8K0_EQC_TRN1A_1ST;
	parm_d     uint16                      _parm__sip_response_code_sit3;
	parm_d     uint16                      _parm__sip_response_code_sit4;
	parm_d     uint32                      _parm__net_router_globalstar_baudrate;
	var_d      uint16                      _test_2_lsw;
	fast_d     int                         _max_number_fg_comp [NUMBER_OF_FG_BLOCKS];
	debug_d    sint15                      _ec_medium_shift_slew_remote;
	stat_d     bool                        _stat__cp_rd_within_detect;
	parm_d     uint16                      _parm__cp_rd_cycle_period_max;
	var_d      uint16                      _PCM_LEN_8K0_GEAR_FLOOR_HOLDOFF; /*  675 ms */
	var_d      fract                       _cc_rx_ALL_energy_log;
	parm_d     bool                        _parm__ipbx_bridge_pstn_call_enable;
	var_d      sint15                      _lpc_del [LPC_ORD];
	parm_d     uint16                      _parm__dm_options_mask;
	var_d      sint15                      _g711a_plc_poffset;
	var_d      uint16                      _send__v8__call_function;
	var_d      sint15                      _pcm_ff_equalizer_size;
	parm_d     sint15                      _parm__speech_enc_slot_size;
	var_d      fract                       _tmp_baud_sum_complex [2];
	var_d      uint16                      _ph1_rx_TONEq_detect_count;
	var_d      uint16                      _ph4n_rx_train_precoding;
	var_d      uint16                      _PCM_LEN_8K0_MAX_ECC_TRAIN; /* 1900 ms */
	local_d    uint16                      _v34n_rx_local_to_remote_maxrate;
	var_d      fract                       _FALL_mse_value;
	var_d      SSL_CTX                     _clnt_ctx;
	var_d      bool                        _dcd_diversion_status;
	local_d    fract CIRCULAR              _sdt_data_buffer_real [C7K2_RX_SEQUENCE_DETECTOR_SIZE * 2];
	var_d      uint16*                     _v90_frame_tx_cp_body_cm [2];
	var_d      uint16                      _ph4n_tx_call_to_answer_maxrate;
	var_d      uint16                      _ph2n_tx_v90_ITU_bits_reserved;
	fast_d     sint15                      _v34_rx_trellis_distance_4D [8 * 5];
	var_d      sint15                      _lec__alpha_rxx_exp;
	var_d      uint16*                     _v90_frame_tx_dil_body_start [10];
	var_d      fract                       _txs_out_vxxmod_remote [THREAD_BUFFER_SIZE];
	var_d      uint16                      _ipod_msg_rx_coder;
	fast_d     fract CIRCULAR              _rx_interpolator_buffer_real [2 * C7K2_RX_INTERPOLATOR_SIZE];
	debug_d    sint15                      _V34_TRN2_MSE_REPORT_RATE;
	var_d      fract                       _fsk_ANSam_tx_passband_coefs_buffer_internal [C7K2_FSK_TX_BPF_SIZE];
	shared_d   uint16                      _parm__led_latch;
	var_d      powr_phase_offset_t         _ph2p_fefo_powr_phase_offset_buffer [PH2P_NO_BINS];
	var_d      sint15                      _convert_log__exponent;
	var_d      uint16                      _v34n_parm_lo_carrier_option;
	var_d      fract                       _dcd_threshold;
	var_d      fract                       _monitor_input_sample;
	var_d      struct led_descriptor       _dpbx_led_special_off_pattern;
	var_d      sint15                      _DIL_probing_index_value;
	var_d      sint15                      _tx_passband_offset;
	var_d      int                         _ata_sample_record_fd;
	var_d      fract                       _v92_system_ID_inputA;
	debug_d    sint15                      _cp_valid;
	var_d      uint16                      _maximum_dtmf_off;
	var_d      const uint16*               _v90_rx_dil_ucode_ptr;
	var_d      sint15                      _bpfdelin [NUM_BANDS][BPF_ORD];
	parm_d     uint32                      _stat__nat_snd_frag_failed; /* LAN to WAN send fragment forwarding failed packet exit counter */
	local_d    char                        _parm__ipbx_priority_forward_dial_string [IPBX_DIAL_STRING_SIZEOF];
	fast_d     fract                       _perfect_imag;
	var_d      sint15                      _ivbuf_pitchAuto [PIT_COR_LEN];
	var_d      sint15                      _ph2_rxtx_rate_conv_modulo_counter;
	var_d      Speech_Decode_FrameState    _amrDec_struct;
	debug_d    fract                       _ph2_tx_eye_imag_previous;
	var_d      sint15                      _YY_LT;
	var_d      fract                       _V34_PRE_HI_EQUALIZER_COEFS [5];
	var_d      int                         _ata_retry_count;
	var_d      fract                       _v34f_eqc_co_DC_real;
	debug_d    sint15                      _ec_fast_shift_slew_local;
	var_d      sint15                      _dgidet_ec_counter;
	var_d      fract                       _pcm_btr_AkQk_error;
	var_d      uint16                      _sonitrol_franchise_id [4+1];
	var_d      fract                       _agc_2_variable_buffer [9];
	var_d      int                         _g722_d4h_sg [2];
	var_d      fract                       _g722_d4h_sh;
	parm_d     bool                        _parm__ata_provider_lock_enable;
	debug_d    uint16                      _baud_tx_break_tmr;
	var_d      sint15                      _cc_rx_demodulator_phase;
	var_d      fract                       _THD_measurement_actual;
	var_d      sint15                      _v34_rx_qn_hat_pointer;
	var_d      uint16                      _parm__speech_enc_dtmf_digit_mask;
	parm_d     uint16                      _parm__ipbx_bridge_billing_delay_duration;
	var_d      sint15                      _l_noise_cof [MIX_ORD +1];
	var_d      bool                        _uicp_service;
	var_d      uint16                      _nat_private_port; /* Private IP port */
	var_d      bool                        _ata_need_boot;
	var_d      fract                       _PH2P_ANAL_TRANSMIT_GAIN;
	debug_d    uint16                      _ANSW_LEN_MS_NOMINAL_REVERSAL;
	var_d      uint16                      _v34_local_fetching_flag;
	var_d      fract                       _previous_half_input_sample;
	var_d      int                         _bfi600;
	stat_d     sint15                      _stat__speech_noise_detect;
	parm_d     uint16                      _parm__ipbx_fc_call_waiting_disable_once;
	const_d    fract                       _ANSAM_LPF_SLEW_2ND;
	var_d      sint15                      _tone_priority_index;
	var_d      uint32                      _overrun_counter;
	var_d      sint15                      _l_prev_gain_dec;
	var_d      uint16                      _nat_remote_port; /* Destination IP port */
	stat_d     uint16                      _stat__cp_rd_ringtype;
	var_d      sint15                      _enc_sid_gain;
	parm_d     fract                       _parm__dm_v34_mse_data_bias;
	debug_d    fract                       _ph2_tx_eye_real_previous;
	var_d      uint16                      _v34s_special_local_train_length;
	var_d      bool                        _v92_tx_repeat_CPd_flag;
	var_d      fract                       _g722_d4l_szl;
	var_d      fract                       _ph2p_anal_log_Whi;
	var_d      uint16                      _ipod_msg_tx_sig_off_offset;
	parm_d     bool                        _parm__ipbx_fxo_autoanswer_anonymous_enable;
	var_d      uint16                      _v92n_rx_filter_sections; /* INFO1a */
	var_d      sint15                      _cc_enable_not_flags;
	var_d      sint15                      _v34s_number_final_MPA_to_send;
	shared_d   fract                       _impedance_monitor_tx_noise_floor_last;
	var_d      uint16                      _faxparm_parm__pump_fax_time;
	var_d      fract                       _convert_agc_1_input_log;
	var_d      uint16                      _PCM_LEN_8K0_EQC_FILL; /* @8K0, 1/2 FF equalizer */
	local_d    event_t                     _bg_event_queue [NUMBER_OF_BG_EVENTS];
	var_d      sint15                      _sh_RCoeff;
	var_d      uint16                      _lec__nlp_probe;
	parm_d     uint32                      _stat__nat_wan_ipsec; /* WAN to LAN receive IPsec packet type counter */
	parm_d     uint16                      _parm__pcm_playback_intro_size;
	persist_d  uint16                      _v34n_tx_attenuation_option;
	parm_d     uint16                      _parm__nat_tcp_mode; /* NAT TCP operating mode */
	var_d      sint15 CIRCULAR             _v34_rx_qn_hat_buffer_real [2*V34_NO_QN_COEFS];
	const_d    fract                       _energy_delta_threshold_fax;
	var_d      uint16                      _far_mode;
	var_d      char *                      _parm__ipbx_post_connect_dial_sequence;
	parm_d     uint32                      _stat__nat_wan_alg_discards; /* WAN to LAN receive ALG discard packet exit counter */
	parm_d     char                        _parm__sip_accept_language_string [STRSIZE_32];
	parm_d     fract                       _parm__pump_noise_level;
	parm_d     uint32                      _stat__nat_wan_pppoe; /* WAN to LAN receive PPPoE packet exit counter */
	fast_d     sint15                      _v34_tx_trellis_state;
	var_d      fract                       _v34_rx_zn_hat_imag;
	var_d      uint16                      _saved_input_sample_8kHz;
	parm_d     bool                        _parm__net_isp_pptp_enable;
	var_d      fract	CIRCULAR              _tonemute_buffer [2*TONEMUTE_SIZE];
	parm_d     bool                        _parm__ata_timeserver_enable;
	parm_d     char                        _parm__ata_manufacturer [ATA_MANUFACTURER_SIZEOF];
	var_d      sint15                      _pcm_folding_result1;
	var_d      sint15                      _pcm_folding_result2;
	fast_d     uint16                      _tx_rate_conv_offset;
	var_d      fract                       _lec__fix_buffer [LEC__BLOCK_SIZE-1];
	local_d    bool                        _parm__ipbx_caller_id_outbound_enable;
	parm_d     sint15                      _parm__phone_autoanswer_mode;
	debug_d    uint16                      _v17_short_count;
	var_d      fract                       _dgidet_ec_peak;
	shared_d   int                         _impedance_monitor_future_tx_offset;
	var_d      sint15                      _asm_lb_packet_ready;
	var_d      uint16                      _PH2P_ANAL_TEST_ENABLE;
	debug_d    uint16                      _V34S_LEN_8K0_1ST_GEAR_CHANGE;
	var_d      sint15                      _v34_tx_xn_remote_real;
	parm_d     uint16                      _parm__ipbx_fc_caller_id_inbound_enable;
	var_d      uint16                      _v90_rx_ph4_MPAs_flag;
	var_d      sint15                      _curCoeff_dtx [MP1];
	parm_d     sint15                      _parm__speech_dec_missing_event_en;
	parm_d     sint15                      _parm__slac_ring_bias;
	shared_d   int                         _sample_foreground_offset;
	shared_d   int                         _mgcp_sockid;
	parm_d     bool                        _parm__ipbx_fxo_security_code_enable;
	var_d      sint15                      _pcm_rx_inv_exponent;
	var_d      uint16                      _nat_public_port; /* Public IP port */
	parm_d     uint16                      _parm__test_QCA2d_delay;
	var_d      fract32                     _notch_datax32_420;
	var_d      uint16                      _test_input_value;
	var_d      struct led_descriptor       _parm__ipbx_red_led_descriptor;
	var_d      uint16                      _ph2_data_timeout_enable;
	var_d      uint16                      _v90h_rx_state;
	var_d      fract                       _pcm_ctl_echo_tx_DC;
	var_d      sint15                      _v90_tx_s_output_offset;
	parm_d     uint16                      _parm__ipbx_fc_call_trace;
	var_d      ufract                      _pcm_rx_inv_gain;
	debug_d    fract                       _v34_equalizer_slew_fast;
	var_d      sint15                      _g_msvq_levels [4];
	var_d      uint16                      _g711a_plc_flag;
	var_d      fract                       _post_ec_power;
	var_d      sint15                      _past_ftyp;
	parm_d     char                        _parm__ata_update_domain_name [NET_DOMAIN_SIZEOF];
	var_d      ufract                      _v34n_tx_gain_adjust;
	parm_d     uint32                      _stat__nat_snd_delivers; /* LAN to WAN send packet deliver exit counter (into upper IP layers) */
	fast_d     int                         _baud_tx_data;
	const_d    sint15                      _ANSAM_2100_MAX_x2;
	var_d      uint16                      _legacy_rx_last_ack_type;
	var_d      uint16                      _v34n_rx_preemph_value;
	var_d      fract32                     _v34_rx_qn_train_coef_real32 [V34_NO_QN_COEFS];
	parm_d     bool                        _parm__net_router_rip_enable;
	parm_d     bool                        _parm__ata_lcd_menu_hide_update;
	parm_d     struct led_descriptor       _parm__dpbx_led_message_waiting;
	var_d      sint15                      _v90_shape_4_offset;
	shared_d   uint16                      _parm__net_debug_level_video;
	var_d      phase_t                     _v34_temp_hi_carrier;
	var_d      fract                       _g711_last_in;
	var_d      uint16                      _v90n_parm_shaping_lookahead;
	var_d      uint16                      _v90_tx_dil_tp_mask;
	var_d      uint16                      _stat__daa_hook_state;
	parm_d     uint16                      _parm__net_isp_connect_on_demand_interval;
	var_d      fract                       _v34_CONV_MSE_value;
	const_d    sint15                      _v29_anti_lock_limit;
	var_d      sint15                      _asm_sending_extra_frame;
	parm_d     uint16                      _parm__voip_echo_canceller_mode;
	var_d      sint15                      _cmn_regulation_counter;
	var_d      uint16                      _dtmf_peak_row_index;
	debug_d    sint15                      _tone_detect_delay;
	var_d      uint16                      _pcm_disc_slot_match_save;
	var_d      uint16                      _v34s_special_local_train_offset;
	debug_d    fract                       _CONVERT_AGC_1_GAIN_MIN_LOG;
	var_d      sint15                      _bulk_delay_remote_poffset;
	parm_d     uint16                      _parm__nat_promiscuous_mode; /* NAT promiscuous mode to anonymous TCP/UDP for local processing */
	shared_d   sint15                      _wi_array [FFTLENGTH/2+1];
	var_d      sint15                      _lec__statistics_count;
	var_d      fract                       _energy_delta_ref_level;
	var_d      fract                       _ph2p_anal_log_Wlo;
	var_d      sint15                      _l_fpitch [NUM_PITCHES];
	parm_d     uint16                      _parm__cp_rd_cycle_period_min;
	parm_d     uint32                      _stat__nat_snd_tcp_non_syn; /* LAN to WAN send TCP non-SYN packet packet exit counter */
	var_d      sint15                      _ph_t;
	var_d      fract                       _pcm_monitor_preemph_in;
	var_d      ufract                      _PCM_WHITEN_NULLOIS_GAIN;
	var_d      sint15                      _lpres_delin [LPF_ORD];
	shared_d   uint16                      _dev_timed_event [NUMBER_OF_LINES_PER_DSP];
	var_d      fract                       _g711a_plc_pitchbuf [HISTORYLEN];
	fast_d     sint15                      _faxdet_decimate_limit;
	var_d      sint15                      _current_output_real;
	var_d      uint32                      _asm_cng_release;
	var_d      fract                       _THD_sum_L2_N_norm;
	fast_d     const fract *               _rx_lpf_coefs;
	var_d      uint16                      _v90n_rxtx_silence_option; /* 0 = normal, 1 = silence */
	var_d      RX_State                    _g722_2_rx_state;
	var_d      sint15                      _l_lastGain;
	debug_d    uint16                      _ph2_power_trace_which_count;
	var_d      fract                       _ph2p_anal_log_Wme;
	var_d      fract CIRCULAR              _cc_rx_energy_delay_buffer [CC_RX_ENERGY_DELAY_SIZE];
	var_d      uint16                      _nat_wan_hw_addr [EADDR_LEN_16]; /* Public HW MAC address for WAN side */
	debug_d    uint16                      _monitor_be2_status;
	parm_d     sint15                      _parm__speech_enc_g711_transition;
	var_d      unsigned char               _chbuf [CHSIZE600];
	var_d      sint15                      _convert_adjust_output_exponent;
	shared_d   uint16                      _parm__pump_conference_mode;
	parm_d     bool                        _parm__net_dhcp_server_restart;
	var_d      sint15                      _asm_decode_missing_frame_seen;
	parm_d     uint16                      _stat__phone_headset_state;
	var_d      uint16                      _v90n_parm_reference_point;
	local_d    fract CIRCULAR              _extra_rate_reduction_buffer [C7K2_FSK_REDUCE_LPF_SIZE * 2];
	debug_d    uint16                      _ph1n_rx_index_ANSpcm;
	debug_d    uint16                      _answ_v8_use_15Hz;
	var_d      fract40                     _dgidet_noise_energy40;
	var_d      uint16                      _v90_dpcm_dil_sp [MAX_DIL_SP_WORDS];
	var_d      sint15                      _PH2P_POWR_GAIN_MARGIN;
	parm_d     uint16                      _parm__ipbx_led_priority_table [PRIORITY_TABLE_SIZEOF];
	shared_d   sint15                      _gci_rx_frame_abort [NUMBER_OF_LINES_PER_DSP];
	fast_d     uint16                      _fgkernel_current_svalue;
	var_d      fract32                     _dtmf_hpf_pow32;
	var_d      int                         _lec__periodic_statistics_index;
	var_d      sint15                      _postLPFInHis [2];
	fast_d     sint15                      _faxdet_decimate_limit_ansam;
	var_d      sint15                      _sys_number_missed_samples_max;
	var_d      fract CIRCULAR              _remote_interpolator_buffer_imag [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	var_d      uint16                      _sart_tx_write_index;
	var_d      fract32                     _v34f_eqc_timing32;
	var_d      uint16                      _ph2_AB_qualify_length;
	var_d      fract32                     _cc_rx_spectrum_result_table32_imag [CC_RX_SPECTRUM_SIZE];
	var_d      sint15                      _ipbx_tone_parameter;
	var_d      sint15	*                    _cbk_st_s [NSTAGEMAX];
	var_d      uint8                       _g726_enc_parm;
	var_d      uint16                      _ipod_msg_rx_bfi;
	var_d      sint15 (*                   _ph1_x_law_decode_routine) (sint15 code);
	var_d      uint16                      _local_buffer_pointer_front;
	var_d      fract                       _dcd_rcv_level;
	var_d      fract                       _p18_2100_notch_buffer [(P18_2100_NOTCH_SIZE-1)*2];
	var_d      fract                       _cc_rx_diff_energy_log;
	parm_d     bool                        _parm__net_lan_heartbeat_server_ip_address;
	var_d      fract                       _PCM_GEAR_CONVERGENCE_THRESHOLD;
	var_d      sint15                      _v34_rx_cn_real;
	debug_d    uint16                      _V34S_ANSW_8K0_2RT_Jend_to_Jdet;
	parm_d     uint16                      _parm__dm_line_quality_monitor_mode;
	debug_d    uint16                      _v34b_mg_run_active_flag;
	var_d      fract32                     _ph2p_powr_L2_spectrum_power_buffer32 [PH2P_NO_BINS_x2];
	const_d    uint16                      _fax_v21_aborts_hs;
	var_d      uint16                      _v90_dpcm_dil_tp [MAX_DIL_TP_WORDS];
	var_d      uint16                      _v34h_tx_b_bits_per_mapping_frame;
	shared_d   uint16                      _debug_host_buffer [MAX_HOST_BUFFER_CHARS/2 + 1];
	const_d    sint15                      _V92_DECODER_FF_SHIFT;
	var_d      uint16 *                    _nat_pkt_ip_ptr; /* Pointer to IP header */
	parm_d     sint15                      _parm__speech_enc_mode;
	var_d      sint31                      _voicedCnt;
	parm_d     ufract                      _parm__line_tx_gain;
	var_d      uint16                      _valid_switch;
	var_d      uint16                      _last_digit;
	local_d    bool                        _sdt_initial_detect_flag;
	shared_d   uint16                      _parm__vppn_device_registration_mask;
	var_d      sint15                      _sigbuf_pitch_ana [LPF_ORD + PITCH_FR];
	var_d      fract32                     _g711_rx_cng_frame_counter;
	var_d      bool                        _v92n_rxtx_v92_enable;
	var_d      sint15                      _l_grps_cnt;
	var_d      fract                       _PCM_FULL_CONVERGENCE_THRESHOLD;
	persist_d  uint16                      _ph2n_tx_3429_option;
	var_d      fract                       _cc_rx_ALL_threshold;
	var_d      sint31                      _frame_count;
	var_d      sint15                      _pcm_ff_ct_position;
	debug_d    sint15                      _cp_change_counter;
	fast_d     sint15                      _asm_decode_shift_decrement;
	var_d      fract                       _energy_delta_slew_rate;
	parm_d     uint16                      _parm__ipbx_line_concurrent_line_count;
	var_d      uint32                      _nat_wan_ip_addr; /* Public IP address for WAN side in network order */
	var_d      uint16                      _v34s_capture_buffer [5*3];
	var_d      sint15                      _l_lsp_cos [DFTLENGTH];
	var_d      fract32                     _detect_v21_detect_lpf1_32;
	local_d    uint16                      _parm__ipbx_dial_after_pound_8;
	local_d    uint16                      _parm__ipbx_dial_after_pound_9;
	var_d      sint15                      _asm_encode_rtp_dtmf_prev;
	var_d      fract CIRCULAR              _rx_lpf_vxx_buffer [2 * C7K2_RX_LPF_SIZE];
	local_d    fract CIRCULAR              _ec_error_buffer [2 * EC_UPDATE_RATE];
	var_d      uint16                      _ph2n_rx_required_attenuation;
	debug_d    phase_t                     _V34_A_OVER_CK80;
	var_d      sint15                      _v90_rx_shaper_frame_size;
	parm_d     sint15                      _parm__cid_data_index;
	parm_d     sint15                      _parm__codec_disconnect_tone_1_bandwidth;
	shared_d   uint16                      _parm__orc_codec_type;
	var_d      sint15                      _back_sigbuf [PIT_COR_LEN - PIT_SUBFRAME];
	const_d    uint16                      _fax_CNG_off_length;
	debug_d    fract                       _V34_EQUALIZER_RANDOM_AMPLITUDE;
	var_d      sint15                      _pastVad;
	var_d      fract                       _cc_rx_ANAL_prev_DC_energy_log;
	var_d      struct led_descriptor *     _ipbx_led_p;
	var_d      uint16                      _lec__cng_frame_sid_enable;
	parm_d     struct tone_descriptor      _parm__ipbx_sit4_tone;
	var_d      uint16                      _PCM_LEN_8K0_ECC_HOLDOFF; /* twice 8K0 taps */
	var_d      uint16                      _v90_rx_dil_ref;
	var_d      fract                       _dcd_probe_agc_2;
	parm_d     char                        _parm__mgcp_remote_user_name [STRSIZE_64]; /* remote host/dialed party configuration */
	var_d      sint15                      _enc_frame;
	debug_d    uint16                      _baud_tx_within_tmd_break;
	var_d      fract                       _v92_rx_decoder_ep_input;
	var_d      fract                       _lec__probe_rx_input;
	var_d      uint16                      _sart_tx_array [TX_SART_BUFFER_SIZE+1];
	var_d      uint16*                     _v90n_tx_INFO0d_body [20];
	var_d      sint15                      _g_w_fs_init;
	parm_d     uint16                      _parm__sdp_g726_24_codec_dyn_pt;
	debug_d    uint16                      _baud_rx_crc_hi;
	var_d      uint16                      _v34_pp_ftr_offset;
	var_d      sint15                      _phone_speaker_monitor_tx_volume;
	var_d      fract32                     _edge_p1200_real32;
	var_d      fract                       _demod_leading_half_imag;
	var_d      sint15                      _v34_rx_qn_tilde_pointer;
	parm_d     ufract                      _parm__dtmf_low_tone_level;
	var_d      uint16                      _mbx_rx_build_data;
	var_d      fract                       _v92s_reneg_monitor_reference;
	parm_d     struct led_descriptor       _parm__dpbx_led_line_in_use;
	shared_d   uint16                      _phone_led_mask;
	local_d    fract32                     _echo_canceller_coefs32 [V32_LOCAL_TAPS + V32_REMOTE_TAPS];
	debug_d    bool                        _v34n_parm_remote_clear_disable;
	var_d      fract                       _phase_loop_complex [2];
	var_d      fract                       _pcm_16K_output_sample;
	fast_d     rtp_packet_t*               _rtp_enc_packet;
	const_d    uint16                      _mark_data_unit;
	var_d      fract *                     _saved_Lx_log_N_pointer;
	var_d      char                        _ata_cmdbuf [256];
	var_d      int                         _flag_RDS_read_stream;
	shared_d   uint16                      _sonitrol_local_address [4];
	var_d      uint16                      _ipod_msg_tx_flags;
	var_d      int                         _sonitrol_udp_socket;
	var_d      sint15*                     _dec_exc;
	fast_d     sint15                      _asm_encode_current_shift;
	debug_d    uint16                      _V34S_LEN_8K0_2ND_FAST_TRAIN;
	var_d      uint16                      _ph2p_anal_preemph_results_buffer [PH2P_NO_SYMBOL_RATES*PH2P_NO_CARRIERS];
	var_d      uint16                      _v34n_tx_data_rate_option;
	var_d      sint15                      _decision_pcm_offset;
	var_d      sint15                      _answ_v8_JM_sent;
	parm_d     fract                       _parm__dtmf_early_col_no_tone_level;
	parm_d     char                        _parm__sdp_g726_32_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	local_d    bool                        _parm__ipbx_distinctive_ring_enable;
	var_d      sint15                      _v92_rx_modulus_2_value; /* V92_TEST_FORCE_MODULUS */
	parm_d     struct led_descriptor       _parm__ipbx_led_call_forward;
	local_d    uint16                      _v34n_rx_use_nonlinear;
	var_d      sint15                      _x_law_encode_sample_counter;
	var_d      fract                       _pre_equalized_energy_level;
	parm_d     sint15                      _parm__slac_message_waiting_amplitude;
	debug_d    ufract                      _V34_BE0_SLEW_MEDIUM;
	var_d      uint16                      _v92n_rx_MH_indication;
	stat_d     uint16                      _stat__round_trip_delay;
	stat_d     sint15                      _stat__speech_rtp_encode_current_packet_type;
	var_d      sint15                      _lec__last_nlp_state;
	var_d      sint15                      _dec_T2 [2];
	var_d      mse_struct                  _pcm_LO_peak_MSE_stack [V34_TRN2_MSE_STACK_SIZE];
	debug_d    bool                        _v34s_reneg_ignore_send_MP_recv_MP;
	var_d      uint16                      _v90_dpcm_dil_second;
	var_d      uint16                      _test_input_count;
	local_d    bool                        _parm__ipbx_caller_id_waiting_enable;
	var_d      fract32                     _fsk_previous_dif32;
	debug_d    fract                       _ph2_power_trace_previous_Y;
	var_d      int                         _use_buffered_threads;
	var_d      fract                       _ph2n_rx_receive_level;
	var_d      fract32                     _v34_rx_qn_train_coef_imag32 [V34_NO_QN_COEFS];
	var_d      sint15                      _prev_fsmag_quant_fsmag [NUM_HARM];
	var_d      fract                       _v92_rx_decoder_ep_output;
	var_d      fract                       _lec__probe_rx_output;
	var_d      uint16                      _shadow_caller_id;
	var_d      sint15                      _v34h_tx_control_hi_frame [16];
	var_d      sint15                      _v34h_tx_control_lo_frame [16];
	var_d      sint15                      _pcm_btr_phase;
	shared_d   uint16                      _sdp_parse_desc_ok;
	var_d      uint16*                     _v92n_tx_MH_body [2];
	persist_d  uint16                      _v34n_rx_symbol_option;
	debug_d    sint15                      _V34S_ENERGY_INPUT_SLEW;
	var_d      statistics_buffer_t         _statistics_buffer;
	var_d      int                         _rxs_count;
	parm_d     struct radio_channel_s      _parm__radio_channel_settings [RADIO_MAX_CHANNELS];
	fast_d     uint16                      _fg_time_until_next_timer_update;
	parm_d     uint16                      _parm__disconnect_tone_tone_mask [DT_TABLE_ENTRY_NUM];
	var_d      sint15                      _tmpbuf [M_LP];
	parm_d     char                        _parm__ipbx_bridge_autoanswer_list [IPBX_LIST__AUTOANSWER_NO_OF][IPBX_DIAL_STRING_SIZEOF];
	local_d    bool                        _parm__ipbx_disturb_accept_enable;
	var_d      g723_codstatdef_t           _g723_CodStat;
	var_d      uint16                      _save_rx_call_to_answer_maxrate;
	var_d      event_t                     _boot_event;
	debug_d    uint16                      _baud_rx_crc_lo;
	debug_d    int                         _bds_counter;
	var_d      fract                       _v92_rx_decoder_ff_output;
	var_d      uint16                      _v90_tx_sign;
	var_d      int                         _rxs_baud_rx_data [THREAD_BUFFER_SIZE];
	var_d      uint8 *                     _ipod_iface_tx_bufp;
	var_d      sint15                      _dcdel [DC_ORD];
	var_d      uint16                      _rx_overspeed_offset;
	const_d    uint16                      _ANSW_V8_CJ_COUNT_MIN;
	parm_d     uint32                      _parm__net_dhcp_server_client_lease_time;
	var_d      uint16                      _rd_energy_state;
	local_d    uint16                      _v32_rate_jump_table_index;
	var_d      uint16                      _faxparm_parm__pump_fax_mode;
	parm_d     char                        _parm__net_lan_password [ATA_PASSWORD_SIZEOF];
	debug_d    uint16                      _input_data_flag;
	parm_d     bool                        _parm__codec_parallel_in_use_disconnect;
	var_d      int                         _number_bg_timers;
	var_d      bool                        _v92n_parm_v92_enable;
	local_d    thread_routine_t            _trellis_routine;
	var_d      sint15                      _v90_shape_1_offset;
	var_d      uint16                      _v90n_parm_maximum_power;
	var_d      sint15                      _memt_postfilt;
	var_d      int                         _lec__periodic_statistics_counter;
	parm_d     bool                        _parm__ata_telnet_server_enable;
	parm_d     sint15                      _parm__speech_enc_cng_order;
	var_d      uint16                      _PCM_LEN_8K0_EQC_TRN1A_LENGTH;
	var_d      sint15                      _pcm_TRN2_MSE_report_rate;
	var_d      sint15                      _l_prev_gain_sub;
	const_d    fract                       _gear_change_threshold;
	var_d      fract                       _fsk_previous_dif_lsb;
	var_d      uint16                      _v21_flag_holdoff;
	parm_d     uint32                      _stat__nat_snd_blocked; /* LAN TO WAN send blocked packet exit counter */
	var_d      fract                       _pcm_btr_freq_error_ratio;
	parm_d     bool                        _parm__ipbx_bridge_single_stage_dialing_enable;
	var_d      fract CIRCULAR              _g168_rx_cng_buffer [G168_RX_CNG_BUFFER_SIZE];
	shared_d   char                        _sdp_buffer [MAX_SDP_MESSAGE_SIZE];
	parm_d     const sint15 *              _parm__pcm_playback_once_bufferp;
	stat_d     sint15                      _stat__speech_strict_silence_detect;
	var_d      uint16                      _sonitrol_line_failed;
	var_d      sint15                      _v90_tx_dil_sp_cnt;
	parm_d     uint16                      _parm__audio_encoding_mode;
	var_d      bool                        _ph2_test_reverse_enable;
	parm_d     uint16                      _parm__ipbx_fc_hookflash_simulation;
	var_d      uint16                      _prev_rx_frame_report;
	var_d      fract                       _convert_agc_1_output_log;
	var_d      uint16                      _ph2n_tx_v92_ITU_bits_carrier;
	var_d      fract                       _g168_inp_floor;
	var_d      uint16                      _scrambler_mask_table [5];
	var_d      SPP_data_buffer_t *         _ethernet_outgoing_queue;
	var_d      sint15                      _YY_LT_shift;
	var_d      sint15                      _v34n_tx_qn_coef_real [V34_NO_QN_COEFS];
	var_d      uint16                      _v34p_bg_block_finished_flags [PH2P_SAMPLE_MAX_PH2B_BLOCKS];
	parm_d     bool                        _parm__sip_require_user_name; /* authentication info */
	stat_d     sint15                      _stat__speech_dec_playout_frame;
	var_d      uint16                      _v92n_rx_prefilter_RMS;
	stat_d     uint16                      _stat__cp_rd_energy_on_time;
	shared_d   uint16                      _dprmbx_outgoing_data_pending;
	var_d      fract                       _V34_RX_LPF_COEFS [(xC8K0_V34_XX_HALF_RX_LPF_SIZE)*2];
	var_d      uint16                      _stat__phone_memcard_provider;
	stat_d     uint16                      _stat__vpcm_digital_attenuation;
	parm_d     char                        _parm__sdp_g728_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      sint15                      _MeanSE;
	local_d    fract CIRCULAR              _fsk_lpf_buffer_imag [2 * C7K2_RX_LPF_SIZE];
	shared_d   uint16                      _wiznet_reset_flag;
	var_d      uint16                      _keep_alive_count;
	debug_d    bool                        _v34s_reneg_allow_recv_MP_within_ignore;
	parm_d     uint16                      _parm__codec_disconnect_tone_1_duration;
	parm_d     uint16                      _parm__sdp_g722_codec_dyn_pt;
	var_d      bool                        _v92n_tx_v92_enable;
	var_d      uint16                      _v90n_rx_redundancy; /* CPx value */
	var_d      fract                       _g722_e4l_oldrl;
	var_d      sint15                      _lec__best_can_poffset;
	var_d      sint15                      _sdt_reversal_timeout_init;
	var_d      fract                       _correct_precoder_real;
	parm_d     uint16                      _parm__ipbx_timeout_pause_duration;
	shared_d   uint16                      _mpi_debounce_reconnect [NUMBER_OF_LINES_PER_DSP];
	var_d      uint16                      _call_automation_not_available;
	debug_d    sint15                      _V34S_LEN_8K0_1RT_MIN_1ST_TRAIN;
	var_d      sint15                      _ph2_tx_baud_counter;
	var_d      fract                       _lec__alpha_err_mag;
	var_d      uint16                      _saved_scrambler_align;
	var_d      fract                       _v34f_eqc_diff_DC_gain;
	var_d      fract                       _fsk_TONE_sgnladjust;
	var_d      sint15                      _l_sigbuf_pit [LPF_ORD + PITCH_FR];
	var_d      fract CIRCULAR              _v34_pp_equalized_data_real [CC_RX_PP_ANALYSIS_SIZE * 2];
	var_d      sint15                      _dec_past_qua_en [4];
	var_d      sint15                      _l_postHPFOutHis_hi [2];
	parm_d     char                        _parm__sdp_g729b_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	parm_d     uint16                      _parm__digital_data_modes;
	persist_d  sint15                      _ph2n_probing_frequency_offset;
	var_d      fract                       _v34_temp_pre_emph_coefs_1 [33];
	var_d      sint15                      _gpf_LLexp;
	parm_d     uint32                      _stat__nat_wan_header_option; /* WAN to LAN receive IP header option packet counter */
	var_d      uint16                      _comn_v8_timeout_T1_counter;
	var_d      fract                       _v34_temp_pre_emph_coefs_6 [33];
	var_d      fract                       _v34_MSE_value_count;
	var_d      fract                       _equalizer_lagging_imag [2*((xV34_XX_EQUALIZER_SIZE)/2)];
	var_d      fract                       _phase_roll_hilbert_buffer [PHASE_ROLL_HILBERT_BUFFER_SIZE];
	var_d      uint32                      _tick_timer;
	var_d      fract                       _dcd_diversion_delta_slew_rate;
	fast_d     sint15                      _parm__faxdet_v21_threshold;
	var_d      uint16                      _CONNECT_event_reported;
	var_d      uint16                      _v92n_tx_clock_adjust; /* Jp */
	local_d    bool                        _parm__ipbx_call_waiting_enable;
	parm_d     uint32                      _stat__nat_wan_blocked; /* WAN TO LAN receive blocked packet exit counter */
	var_d      sint15                      _ANSam_trace_index;
	var_d      void   (*                   _v34h_tx_parser_shellmap_routine) (uint16 R0_msw,  uint16 R0_lsw);
	const_d    sint15                      _HIT_COUNTER_INIT;
	var_d      uint16                      _lec__canceller_control;
	var_d      sint15                      _Min_buffer [16];
	var_d      sint31                      _oicp_last_entry_time;
	var_d      uint16                      _v90n_rx_constellation_mask;
	parm_d     struct tone_descriptor      _parm__ipbx_confirm_tone;
	var_d      fract                       _cc_rx_PP_total_tone_ratio;
	var_d      sint15                      _MeanSLE;
	var_d      ufract                      _agc_2_inv_gain;
	var_d      uint16                      _faxmon_status_code;
	parm_d     char                        _parm__sip_nat_keep_alive_domain_name [NET_DOMAIN_SIZEOF];
	var_d      fract                       _v21_detect_level;
	var_d      fract32                     _edge_p1200_imag32;
	var_d      int                         _g722_tx_qmf_data_offset;
	var_d      fract  CIRCULAR             _g711a_plc_history [2*HISTORYLEN];
	var_d      fract                       _FALL_adjusted_mse_value;
	var_d      sint15                      _ph2n_rx_maxrate [V34N_MAX_SYMBOL+1];
	parm_d     uint16                      _stat__v92_MH_information;
	var_d      fract                       _v34_BE_log_Gn;
	var_d      fract                       _v34_BE_log_Gp;
	var_d      fract                       _DIL_probing_pad_gain;
	var_d      ufract                      _V34_T_OVER_8K0_RATIO;
	var_d      uint16                      _rled_pattern_index;
	var_d      fract32                     _v34_rx_yn_error_real32;
	var_d      uint16                      _sonitrol_remote_updnload_port;
	var_d      sint15                      _ph2p_bg_sample_out_offset;
	var_d      uint16                      _test_2_ext;
	fast_d     uint16                      _parm__dpbx_key_polarity_mask;
	var_d      fract                       _jitter_max_freq;
	var_d      fract                       _ph2p_anal_variance_13_table [PH2P_NO_PREEMPHASIS];
	var_d      monitor_t                   _monitor;
	var_d      fract32                     _v90_shape_3_min32;
	debug_d    uint16                      _V34S_LEN_8K0_PRE_GEAR_CHANGE;
	var_d      fract                       _ph2p_anal_adj_log_Whi;
	var_d      uint16                      _v34h_tx_Q_n;
	var_d      fract                       _lec__tec_excite;
	var_d      sint15                      _saved_status_code;
	var_d      uint16                      _tx_match_sequence;
	parm_d     struct time_s               _parm__ata_time;
	fast_d     int                         _baud_cntr;
	var_d      fract                       _V34_PRE_ME_EQUALIZER_COEFS [5];
	var_d      sint15                      _g_w_fs [NUM_HARM];
	var_d      uint16                      _v34n_tx_symbol_rate;
	parm_d     uint16                      _parm__ipbx_interdigit_duration;
	parm_d     uint16                      _parm__max_jpeg_save_files;
	var_d      uint16*                     _v92n_tx_CPd_body_pretaps [12];
	var_d      uint16                      _lec__nlp_sil_detect;
	parm_d     char                        _parm__ata_model_number [ATA_MODEL_NUMBER_SIZEOF];
	var_d      bool                        _ipod_within_data_g726;
	var_d      uint16                      _v90n_tx_pcm_3429_option;
	var_d      uint16                      _ph2p_anal_maxrates_02_table [PH2P_NO_PREEMPHASIS];
	var_d      sint15                      _v34_rx_qn_pointer;
	var_d      fract                       _V34_INTERPOLATOR_COEFS [xC8K0_V34_XX_INTERPOLATOR_COEFS_SIZE];
	var_d      int                         _g726_out_bits;
	shared_d   fract32                     _impedance_monitor_tx_noise_floor_sum32;
	var_d      uint16                      _asm_post_g711_transition;
	var_d      uint16                      _v90_tx_offset;
	debug_d    uint16                      _sart_tx_processed_cnt;
	var_d      sint15                      _lpfsp_delin [LPF_ORD];
	var_d      fract                       _ptloop_2nd_order_term [2];
	var_d      uint16                      _ph2p_fefo_holdoff_flag;
	var_d      sint15                      _av_shift [ENH_VEC_LENF];
	var_d      nat_tab_t *                 _nat_l2tp_entry; /* L2TP translation entry */
	var_d      sint15                      _decode_input_real;
	parm_d     bool                        _parm__net_lan_pppoe_enable;
	var_d      uint16                      _sense_silence_detect;
	var_d      uint16*                     _v90_tx_dil_tp_ptr;
	var_d      thread_routine_t            _pcm_eq_routine;
	debug_d    fract                       _v34_equalizer_slew_B1_medium;
	var_d      uint16                      _ipod_command_vocoder_select;
	parm_d     char                        _stat__net_current_host_name [ATA_HOST_NAME_SIZEOF];
	var_d      uint16                      _ipod_error_flags;
	fast_d     uint16                      _bg_time_until_next_timer_update;
	var_d      fract                       _v90_shape_3_min;
	var_d      sint15                      _l_postHPFOutHis_lo [2];
	var_d      sint15                      _pcm_rx_8K0_transfer_in_poffset;
	var_d      sint15                      _cc_tx_modulator_increment;
	var_d      uint16                      _v34n_rxtx_hi_data_rate_option;
	shared_d   uint16                      _parm__orc_rtpmap_number;
	const_d    fract                       _threshold_fax_ab;
	const_d    fract                       _threshold_fax_ac;
	var_d      uint16                      _pcm_ctl_enable_tx_hpf; /* ??? 1 ??? */
	var_d      int                         _sonitrol_connection_established;
	parm_d     bool                        _parm__rtp_srtp_enable;
	var_d      uint16                      _mbx__dtoh [MBX_DTOH_SIZE];
	var_d      fract                       _cc_rx_Tk_energy_log [9];
	var_d      uint16                      _v90_apcm_dil_length;
	parm_d     uint32                      _stat__nat_snd_create_failed; /* LAN to WAN send translation entry create failed packet exit counter */
	var_d      char                        _sip_temp_print_space [STRSIZE_32];
	parm_d     sint15                      _parm__radio_alarm_settings;
	fast_d     uint16                      _goertzel_buffer_poffset;
	var_d      uint16                      _v34n_parm_ptt_symbol_option;
	var_d      sint15                      _tone_priority_count;
	var_d      uint16                      _pcm_playback_size;
	var_d      fract                       _v34_temp_hi_lo_pre_equalizer_coefs [5];
	parm_d     char                        _parm__ata_configuration_failed_message [ATA_MESSAGE_SIZEOF];
	debug_d    sint15                      _tonedt_rate_reduction_counter;
	var_d      sint15                      _V34_RXI_TAPS;
	var_d      sint15                      _hpspeech600 [IN_BEG +  180] ;
	var_d      sint15                      _l_default_w;
	var_d      fract                       _p18_angle_store_imag [3];
	var_d      sint15                      _cc_tx_interpolator_poffset;
	var_d      fract                       _v92_rx_decoder_ff_alpha_gain;
	parm_d     uint16                      _parm__dtmf_clamp_count;
	var_d      fract CIRCULAR              _ph2_tx_interpolator_buffer_imag [2*(PH2_TX_INTERPOLATOR_SIZE)];
	var_d      fract                       _PH2_RX_DCD_HYSTERESIS;
	var_d      sint15                      _zero_dtx [MP1];
	var_d      sint31                      _ac97_tx_dma;
	var_d      uint16                      _v92n_rx_MH_information;
	var_d      uint16                      _tone_detector_8kHz;
	var_d      sint15                      _agal [ENH_VEC_LENF];
	var_d      fract                       _v34_tx_zn_local_imag;
	const_d    fract                       _BAUD_PLL_FREQ_ERROR_RATIO;
	var_d      fract32                     _pcm_equalizer_ep_coefs32 [PCM_EP_EQUALIZER_SIZE_MAX];
	var_d      event_t                     _V90_RX_R_REVERSAL_EVENT; /* default */
	var_d      uint16                      _predicted_rx_xn_B1_1st_data_flag;
	var_d      sint15                      _l_noise_del [MIX_ORD];
	parm_d     uint16                      _parm__mgcp_response_code_sit1;
	var_d      uint16                      _v34n_parm_attenuation_option;
	parm_d     uint16                      _parm__mgcp_response_code_sit2;
	parm_d     uint16                      _parm__mgcp_response_code_sit3;
	var_d      sint15                      _v90_rx_retrain_delay_poffset;
	shared_d   sint15                      _mpi_status_index [NUMBER_OF_LINES_PER_DSP];
	parm_d     uint16                      _parm__mgcp_response_code_sit4;
	debug_d    uint16                      _sart_overlay_loaded;
	parm_d     uint16                      _parm__sdp_jpeg_codec_dyn_pt;
	local_d    bool                        _parm__ipbx_busy_forward_service;
	var_d      uint16                      _scrambler_output_shift;
	parm_d     sint15                      _parm__priority_generators [(TONE_GENERATOR_COUNT * 2) + 1];
	parm_d     uint16                      _parm__sip_timer_no_answer_duration;
	parm_d     uint32                      _parm__ata_configuration_update_random_delay;
	parm_d     tone_detector_coef_t        _parm__disconnect_tone_detector_table [NUMBER_DT_DETECTORS];
	parm_d     bool                        _parm__net_lan_save_for_isp;
	var_d      sint15                      _fpitch_global [NUM_PITCHES];
	var_d      fract                       _equalizer_raw_output_real;
	var_d      uint16                      _v92n_rx_max_coefs_total; /* INFO1a */
	var_d      fract                       _force_train_real;
	fast_d     uint16                      _faxdet_detect_value;
	debug_d    uint16                      _baud_tx_unshifted;
	var_d      sint15                      _lec__nlp_cng_offset_index;
	local_d    char                        _parm__ipbx_hot_warm_dial_string [IPBX_DIAL_STRING_SIZEOF];
	const_d    fract                       _threshold_fax_cc;
	debug_d    uint16                      _v34_short_enable;
	debug_d    sint15                      _phase_hit_limit;
	var_d      fract                       _ph2p_anal_adj_log_Wlo;
	var_d      fract                       _lec__nlp_cng_offset;
	parm_d     uint32                      _stat__nat_rcv_broadcast; /* LAN to WAN receive broadcast packet exit counter */
	var_d      sint31                      _dgidet_padrb_mean32 [TOTAL_SLOT * STATISTIC_LEN];
	debug_d    sint15                      _ec_xtrain_shift_slew_remote;
	var_d      uint16                      _legacy_binary_upload_mode;
	stat_d     fract                       _stat__snr_mse_measure;
	debug_d    uint16                      _fax_v21_CED_length;
	var_d      fract                       _tmp_baud_sum_real;
	var_d      uint16                      _phone_headset_debounce_count;
	var_d      struct led_descriptor *     _ipbx_rled_p;
	var_d      sint15                      _v34_rx_xn_hat_real;
	var_d      uint16*                     _v34h_tx_buffer_current;
	var_d      sint15                      _lec__alpha_err_exp;
	var_d      fract                       _ph2p_anal_adj_log_Wme;
	debug_d    uint16                      _V34S_ANSW_8K0_1RT_S_SN_to_JEdet;
	var_d      fract                       _btrec_baud_agc_slew;
	var_d      uint16                      _PCM_LEN_8K0_EQC_TRN1A_2ND;
	const_d    fract                       _energy_off_threshold;
	stat_d     uint16                      _stat__ipod_loopback_mode;
	var_d      uint16                      _ipod_msg_rx_sig_level;
	var_d      sint15                      _decode_frame_received_indication;
	var_d      uint16                      _v34n_parm_data_rate_option;
	var_d      sint15                      _v34_tx_cn_real;
	var_d      uint16                      _v8_rx_QC_data_flag;
	var_d      uint16                      _stat__ipbx_device_type;
	parm_d     uint16                      _parm__sdp_g711a_codec_dyn_pt;
	parm_d     bool                        _parm__net_debug_enable;
	var_d      fract                       _pcm_LO_peak_MSE_max [V34_TRN2_MSE_STACK_SIZE];
	var_d      sint15                      _v90_rx_SdN_samples_remaining_ph3;
	var_d      uint16                      _lec__periodic_statistics_buffer [18];
	var_d      uint16                      _v90_apcm_dil_lsp;
	var_d      sint15                      _pitch_avg_global;
	var_d      fract CIRCULAR              _v34_rx_qn_perfect_buffer_real [2*(V34_NO_QN_COEFS + 1)];
	parm_d     uint16                      _parm__ipbx_fc_caller_id_inbound_disable;
	var_d      bool                        _p1800_search_active;
	debug_d    bool                        _v34s_reneg_test_init_variable_S_length;
	parm_d     uint32                      _stat__nat_rcv_frag_failed; /* LAN to WAN receive fragment forwarding failed packet exit counter */
	var_d      sint15                      _pspr_x0;
	var_d      fract                       _cc_rx_ANAL_DC_imag;
	var_d      results_t                   _lec__rx_results;
	var_d      sint15                      _pspr_x1;
	debug_d    uint16                      _baud_tx_crc_hi;
	local_d    char                        _parm__ipbx_line_number [NUMBER_OF_LINES_PER_DSP][IPBX_DIAL_STRING_SIZEOF];
	var_d      fract                       _v34_BE_pos_log_magnitude;
	var_d      bool                        _fsk_TONE_flag;
	fast_d     int                         _aux_rx_baud;
	var_d      bool                        _asm_encode_rtp_dtmf_generate_prev;
	var_d      int                         _legacy_rx_in;
	var_d      sint15                      _v34f_eqc_co_DC_angle;
	parm_d     uint16                      _parm__ipbx_bridge_security_entry_duration;
	var_d      uint16                      _v92h_rx_buffer1 [V92_LEN_8K0_DATA_FRAME];
	const_d    fract                       _DELTA_HYSTERESIS;
	var_d      uint16                      _v92h_rx_buffer2 [V92_LEN_8K0_DATA_FRAME];
	var_d      sint15                      _ph2p_anal_count_length;
	var_d      fract                       _lec__dc_offset;
	var_d      fract                       _ANSam_trace_magphase_mid_real;
	var_d      G722_2_Decoder_State        _g722_2_decstruct;
	var_d      bool                        _v92_frame_tx_short;
	shared_d   struct proc *               _mgcp_mesg_proc;
	var_d      uint16                      _v90_apcm_dil_ltp;
	var_d      uint16                      _ph4n_rx_acknowledge;
	var_d      sint15                      _lec__buffer_size;
	var_d      sint15                      _gpf_oloop_length;
	parm_d     uint16                      _parm__ipbx_timeout_hold_drop_duration;
	var_d      fract *                     _saved_Lx_log_P_pointer;
	shared_d   sint15                      _wr_array [FFTLENGTH/2+1];
	var_d      uint16                      _comn_v8_found_QC;
	stat_d     sint15                      _stat__speech_dec_missing_mtr;
	var_d      sint15                      _dec_sid_gain;
	parm_d     char                        _parm__sdp_ilbc_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      fract                       _pcm_rx_TRN2A_log_gain_ratio;
	parm_d     bool                        _parm__orc_iface_enable;
	parm_d     uint16                      _parm__cp_rd_above_range_metric;
	var_d      uint16                      _saved_tx_MP_data;
	var_d      sint15                      _v34_frame_rx_word_count;
	const_d    sint15                      _V92_RX_RETRAIN_DETECT_LIMIT;
	var_d      uint32                      _ata_update_time_cfg;
	var_d      call_info_t                 _stat__ipbx_fxo_incoming_info;
	parm_d     uint16                      _parm__ipbx_fc_call_waiting_caller_id_enable;
	var_d      dtmf_queue_t                _dtmf_queue_ipod;
	var_d      uint16                      _v90_tx_dil_ref;
	var_d      uint16*                     _v34n_tx_INFO0_body [14];
	var_d      sint15                      _test_counter;
	parm_d     uint16                      _parm__mgcp_public_external_mgcp_port;
	var_d      sint15                      _constel_midpoints_table_nrm [SIZE_MID_NRM];
	fast_d     bool                        _within_fg_state_update;
	debug_d    uint16                      _baud_rx_no_carrier_flag;
	var_d      fract                       _retrain_threshold;
	var_d      uint16                      _forced_scrambler_lsw;
	var_d      sint15                      _v90_tx_dil_length;
	var_d      fract32                     _pcm_btr_predict_lsw;
	var_d      phase_t                     _V34_RXI_PLL_COUNT_x2;
	var_d      uint16                      _v92n_rx_precoder_fb_taps;
	parm_d     uint16                      _parm__spk_monitor_rx_gain;
	parm_d     char                        _parm__sdp_mpeg2_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      uint16                      _nat_ip_protocol; /* IP packet protocol */
	debug_d    fract                       _V34_BE2_SLEW_SLOW;
	parm_d     struct led_descriptor       _parm__dpbx_led_pstn_in_use;
	var_d      sint15                      _lec__datamax_half_excess;
	var_d      fract32                     _v34_rx_yn_error_imag32;
	var_d      fract                       _cc_rx_PP_energy_log;
	shared_d   uint16                      _parm__net_debug_level_net;
	parm_d     uint16                      _parm__tel_answer_tone_length;
	var_d      uint16 *                    _v34h_rx_m_ijk_ring_index_pointer;
	var_d      fract                       _FALL_adjusted_mse_count;
	parm_d     uint16                      _parm__ipbx_timeout_warning_duration;
	var_d      sint15                      _asm_decode_packed_frame_start;
	var_d      SSL                         _clnt_ssl;
	var_d      sint15                      _ppastVad;
	var_d      sint15                      _ctl;
	var_d      fract                       _lec__probe_tx_output;
	var_d      fract                       _g722_enc_detlow;
	shared_d   uint16                      _parm__vppn_channel_activation_mask;
	var_d      sint15                      _predicted_rx_xn_B1_Q_n_buffer [16 * 8];
	var_d      uint16                      _sonitrol_DNIS_digits;
	var_d      uint16                      _sonitrol_franchise_label [5+1];
	var_d      fract32                     _v34_resync_mcomp_buffer_real32 [1*(V34_RESYNC_Nx2_plus_1)];
	debug_d    fract                       _CONVERT_AGC_2_ENERGY_TARGET_LOG;
	var_d      int                         _g726_in_bits;
	parm_d     sint15                      _parm__codec_line_in_use_detect_method;
	fast_d     uint16                      _parm__dpbx_led_polarity_mask;
	var_d      fract                       _baud_slew_buffer [7];
	debug_d    uint16                      _v8_tx_sync_code;
	var_d      iLBC_Enc_Inst_t             _Enc_Inst;
	debug_d    bool                        _v34s_reneg_test_init_ignore_SN;
	var_d      uint32                      _parm__tripwire_video_record;
	var_d      fract                       _lec__dc_offset_intermediate;
	parm_d     sint15*                     _parm__speech_enc_mbx_addr;
	var_d      bool                        _g168_initialized;
	var_d      sint15                      _lec__nlp_loose_counter;
	var_d      fract                       _ph2_dummy_loopback_imag;
	var_d      sint15                      _v90_shape_preload_count;
	var_d      uint16                      _phone_power_switch_condition;
	var_d      uint16                      _v17_correct_phase;
	var_d      fract                       _V34_SLEW_COS_BE;
	var_d      uint16                      _saved_scrambler_lsw;
	debug_d    bool                        _v34s_reneg_resp_S_to_SN_to_retrain;
	var_d      int                         _txs_count;
	var_d      uint16                      _ipod_iface_tx_size;
	var_d      sint15                      _v34_yn_equalized_real;
	var_d      uint16                      _v90_tx_dil_sp_mask;
	var_d      fract CIRCULAR              _v90_rx_delay_buffer [2*V90_RX_DELAY_BUFFER_SIZE];
	var_d      uint16                      _ph2_rx_baud_current;
	parm_d     uint16                      _parm__sdp_g711u_codec_dyn_pt;
	var_d      VPORTCAP_Params             _vportcap_globalptr;
	var_d      fract32                     _ph2p_fefo_ar_ai_stage2_buffer32 [2*(PH2P_FEFO_BIN_COUNT)];
	parm_d     struct radio_encryption_s   _parm__radio_encryption_settings [RADIO_MAX_KEYS];
	var_d      sint15                      _agc_2_inv_exponent;
	debug_d    uint16                      _baud_tx_crc_lo;
	var_d      fract                       _ph2p_anal_log_BxR_buffer [PH2P_NO_PREEQ_BINS];
	var_d      uint16                      _baud_rx_data_unit;
	var_d      sint15                      _enc_cur_gain;
	var_d      uint16*                     _saved_v90trn_pad_table;
	parm_d     sint15                      _stat__speech_dec_frame_based_active;
	var_d      sint15                      _Prev_Min;
	var_d      event_t                     _loss_event;
	var_d      fract                       _cc_rx_notch_buffer [4];
	var_d      bool                        _dgs_first;
	var_d      fract                       _g168_err_level;
	var_d      fract32                     _lec__dc_offset_lpf32;
	var_d      uint16                      _test_2_msw;
	var_d      fract                       _ph2n_probing_receive_gain;
	var_d      sint15                      _v92_rx_decoder_up_cutoff;
	persist_d  uint16                      _ph2n_tx_2743_option;
	var_d      pcm_ec_slew_calculations_t  _pcm_eq_ff_slews;
	parm_d     char                        _stat__mgcp_local_contact_domain_name [NET_DOMAIN_SIZEOF];
	var_d      bool                        _stat__ipbx_fxo_cid_received;
	var_d      sint15                      _cc_rx_PP_repetition_counter;
	stat_d     sint15                      _stat__tx_level_dbm;
	debug_d    uint16                      _baud_rx_substate;
	var_d      uint16                      _pcm_rx_6dB_pad_detect;
	var_d      sint15                      _v92h_rx_K_input_offset;
	var_d      uint16                      _ethernet_outgoing_count;
	parm_d     char                        _parm__ata_service_name [ATA_SERVICE_NAME_SIZEOF];
	var_d      bool                        _firstTime_classify;
	var_d      sint15                      _v34_tx_local_pattern_offset;
	stat_d     bool                        _stat__cp_rd_ring_energy_active;
	var_d      fract                       _constel_output0;
	var_d      uint16                      _save_measured_roundtrip_delay;
	var_d      fract                       _constel_output1;
	var_d      fract                       _constel_output2;
	var_d      fract                       _constel_output3;
	local_d    uint16                      _fsk_lpf_poffset;
	parm_d     char                        _parm__sdp_g726_16_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	parm_d     char                        _parm__sdp_melp_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      uint16*                     _v92n_rx_CPus_body [ 8];
	var_d      fract32                     _faxdet_data_sum_v21;
	fast_d     sint15                      _parm__faxdet_ced_threshold;
	var_d      fract                       _ph2_rx_special_bpf_buffer [2*(63+1-1)];
	shared_d   uint16                      _parm__audio_monitor_gain;
	parm_d     uint16                      _stat__radio_;
	parm_d     uint16                      _parm__pulse_break_time;
	var_d      fract                       _convert_energy_log;
	var_d      sint15                      _asm_decode_packed_length;
	debug_d    sint15                      _ec_slow_shift_slew_local;
	parm_d     uint16                      _parm__ipbx_fc_caller_id_outbound_disable_once;
	var_d      sint15                      _predicted_rx_xn_B1_imag;
	var_d      sint15 CIRCULAR             _v34_rx_qn_tilde_buffer_real [2*V34_NO_QN_COEFS];
	var_d      bool                        _v34s_reneg_initiator;
	var_d      fract *                     _ph2p_anal_variance_CS_pointer;
	var_d      uint16                      _faxmon_frame_state;
	var_d      sint15                      _pcm_disc_slot_match_number;
	const_d    sint15                      _hit_counter_init;
	var_d      uint16                      _phone_ptt_condition;
	var_d      fract                       _pcm_tx_power_log;
	local_d    fract                       _detect_v21_detect_lpf1;
	local_d    fract                       _detect_v21_detect_lpf2;
	parm_d     uint16                      _parm__jpeg_thumbnail_enable;
	local_d    bool                        _parm__ipbx_caller_id_inbound_service;
	debug_d    fract                       _V34_BE_INITIAL_Gn;
	debug_d    fract                       _V34_AB_SIGNAL_SLEW_RATE;
	debug_d    fract                       _V34_BE_INITIAL_Gp;
	var_d      uint16*                     _v90n_tx_INFO1a_body [7];
	var_d      uint16                      _v90_shape_lookahead_1;
	var_d      fract                       _sdt_DC_angle_store_real;
	var_d      uint16                      _v90_shape_lookahead_2;
	var_d      uint16                      _v90_shape_lookahead_3;
	var_d      sint15                      _v34f_eqc_diff_DC_exponent;
	parm_d     bool                        _parm__net_isp_reconnect_on_link_loss;
	parm_d     char                        _parm__ata_configuration_revision [ATA_REVISION_SIZEOF];
	var_d      sint15                      _l_envdel [NUM_BANDS*ENV_ORD];
	stat_d     uint16                      _stat__speech_dec_current_frame;
	var_d      sint15                      _l_postHPFInHis [2];
	parm_d     uint16                      _parm__ipbx_fc_block_anonymous_disable;
	var_d      fract40                     _v92_rx_decoder_ep_input_energy40;
	var_d      uint16                      _v90_rx_reneg_flag;
	var_d      sint15                      _V90_CENTER_TAP_DELAY;
	var_d      sint15                      _MeanSZC;
	var_d      fract32                     _tmp_full_energy32;
	var_d      uint16                      _faxmon_frame [MAX_T30_FRAME_SIZE];
	var_d      uint16 *                    _ph2p_anal_maxrates_CS_table;
	const_d    sint15                      _ch_seize_threshold;
	shared_d   uint16                      _parm__dtmf_tone_on_time;
	var_d      sint15                      _cc_counter_ones;
	var_d      thread_routine_t            _pcm_rx_retrain_detect_routine;
	var_d      mse_struct                  _v34_TRN2_MSE_stack [V34_TRN2_MSE_STACK_SIZE];
	var_d      struct led_descriptor *     _ipbx_gled_p;
	var_d      sint15                      _pcm_btr_1st;
	const_d    fract                       _silence_lpf_slew;
	parm_d     char                        _parm__radio_ptt_digit_keys [RADIO_PTT_KEYS_SIZEOF];
	var_d      fract                       _lec__best_erl_ratio;
	var_d      phase_t                     _fsk_clock_capture_width;
	shared_d   uint16                      _sonitrol_ethernet_local_timer;
	var_d      uint16                      _special_match_lsw;
	var_d      sint15                      _v92_rx_decoder_ep_alpha_exp;
	debug_d    uint16                      _MONITOR_PHASE_RAW_STATUS;
	var_d      fract                       _cc_rx_PP_last_compare_ratio;
	var_d      fract                       _trellis_minval;
	var_d      sint15 CIRCULAR             _v34_tx_qn_remote_buffer_imag [2*V34_NO_QN_COEFS];
	shared_d   sint31                      _impedance_monitor_max_tap_lpf1;
	var_d      uint16                      _sonitrol_audio_ip_configured;
	shared_d   sint31                      _impedance_monitor_max_tap_lpf2;
	var_d      sint15                      _v34_pp_fill_count;
	var_d      sint15                      _v34n_tx_TRN_length;
	var_d      fract                       _PH2P_ANAL_MSE_CORRECT;
	debug_d    const tone_detector_coef_t* _tone_detector_constants;
	var_d      fract CIRCULAR              _cc_tx_interpolator_buffer [CC_TX_INTERPOLATOR_SIZE*2];
	var_d      uint16                      _shadow_panel_group_id [4+1];
	var_d      fract                       _v34n_rx_preeq_gain;
	var_d      uint16                      _ANSam_detect_15Hz;
	var_d      sint15                      _lec__nlp_detect_tight;
	var_d      sint15                      _enc_old_exc [L_FRAME+PIT_MAX+L_INTERPOL];
	shared_d   uint16                      _parm__net_debug_level_vppn;
	parm_d     uint32                      _stat__nat_wan_create; /* WAN to LAN receive translation created counter */
	var_d      uint16                      _stat__ipbx_sub_state;
	shared_d   sint15                      _sample_buffer [SAMPLE_BUFFER_SIZE];
	parm_d     uint16                      _parm__v8__call_function;
	var_d      sint15                      _ph2p_fefo_gain_adjust_shift;
	var_d      uint16                      _ph4n_rx_MP_type;
	var_d      fract                       _v34_BE_log_jam_baud_agc;
	parm_d     uint16                      _parm__codec_disconnect_tone_3_duration;
	const_d    uint16                      _v92n_tx_filter_sections; /* INFO1a */
	var_d      fract                       _sequence_detect_level;
	const_d    fract                       _fsk_TONE_tonesize;
	var_d      sint15                      _sid_sav;
	var_d      sint15                      _BETA0;
	var_d      fract                       _v34_resync_variance_buffer_real [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      bool                        _ph2_INFOMARKS_detected;
	var_d      sint15                      _phone_input_scan_count;
	var_d      fract32                     _rf_rx_dc_ioffset;
	var_d      sint15                      _equalizer_coef_count;
	var_d      uint32                      _parm__speech_rtp_cng_duration; /* 240 ms */
	var_d      bool                        _fsk_run_demodulator;
	var_d      complex                     _detect_demod_complex;
	var_d      fract                       _v34_temp_hi_me_pre_equalizer_coefs [5];
	var_d      void  (*                    _v90_rx_decision_routine) (fract);
	parm_d     char                        _parm__sip_incoming_auth_user_name [STRSIZE_64]; /* this holds registration auth info for one single user */
	var_d      fract                       _v34_MSE_value;
	var_d      sint15                      _l_lpres_delout [LPF_ORD];
	const_d    fract                       _DELTA_ENERGY_THRESHOLD;
	var_d      uint16                      _sart_rx_timeout_reload;
	shared_d   uint16                      _sample_cnt_high;
	shared_d   int                         _mgcp_controller_sockid;
	var_d      uint16 *                    _nat_pkt_pppoe_ptr; /* Pointer to PPPoE header */
	var_d      uint16                      _ph2n_rx_v92_ITU_bits_carrier;
	var_d      uint16                      _FALL_fallforward_possible_flag;
	var_d      fract32                     _dgs_energy32;
	var_d      fract                       _max_energy;
	var_d      bool                        _ph2_INFO_detect_enable;
	var_d      bool                        _rd_prev_was_off;
	var_d      bool                        _dma_enabled;
	stat_d     sint15                      _stat__speech_decoder_underflow;
	debug_d    uint16                      _overlay_ph2_overrides_probing_results;
	var_d      sint15                      _output_lock_offset;
	var_d      uint16*                     _v92n_tx_Jp_body [10];
	var_d      sint15                      _v34h_tx_V0_m;
	var_d      fract                       _lec__data_size_mag_adjust;
	var_d      uint16*                     _v92n_rx_Ja_body_end [ 5];
	parm_d     struct tone_descriptor      _parm__ipbx_number_error_tone;
	parm_d     uint16                      _parm__ipbx_fc_disturb_accept_disable;
	var_d      char                        _parm__ipbx_dial_prefix [3];
	var_d      fract                       _edge_m1200_real;
	var_d      uint16                      _v34h_tx_AMP_value;
	var_d      uint16                      _train_scrambler_low;
	var_d      int                         _v34_delay_forced_start;
	var_d      sint15                      _mem_syn_pst [M_LP];
	var_d      uint16                      _parm__rtp_encode_gain;
	var_d      uint16                      _found_POST_2100_calling_tone;
	stat_d     uint16                      _stat__tone_detect_mask;
	var_d      sint15                      _enc_sharp;
	var_d      fract                       _ANSam_current_sample;
	var_d      uint16                      _nat_icmp_ip_protocol; /* IP packet protocol */
	var_d      uint16                      _ph2n_tx_maxrate [V34N_MAX_SYMBOL+1];
	var_d      int                         _legacy_rx_out;
	var_d      sint15                      _ph2p_fefo_SB_gain_adjust;
	local_d    uint16                      _v34n_rx_data_rate;
	var_d      uint16                      _v34n_rxtx_cleardown_active;
	var_d      fract                       _tonemute_new_enr_check;
	var_d      state_t                     _automode_next_state;
	parm_d     uint16                      _parm__rtp_jitter_buffer_minimum_depth; /* Minimum jitter buffer depth in msec */
	var_d      sint15                      _dev_xx_frame_offset;
	local_d    uint16                      _v34n_rx_primary_channel_maxrate;
	var_d      sint15                      _SN_LT;
	var_d      uint16                      _rf_dma_fail;
	var_d      fract32                     _v34_resync_mcomp_buffer_imag32 [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      sint15                      _lastGain_postfilt;
	var_d      sint15                      _ph2p_fefo_holdoff_time;
	var_d      fract32                     _ph2p_powr_dmod_rx_buffer32 [PH2P_BLOCKSIZE + PH2P_WINDOW_LENGTH_NOISE];
	debug_d    uint16                      _V34S_LEN_8K0_1ST_PHASE_CHANGE;
	var_d      uint16                      _v90_tx_send_Rx_sequence_flag;
	var_d      uint16                      _fsk_bitstream_lsb;
	parm_d     uint32                      _parm__ata_firmware_update_random_delay;
	var_d      uint16                      _ph4n_tx_primary_channel_maxrate;
	parm_d     sint15                      _parm__speech_dtmf_regeneration;
	var_d      int                         _sonitrol_wiznet_channel;
	var_d      uint16                      _found_AA_tone;
	var_d      uint16                      _tx_count_test;
	var_d      SPP_data_buffer_t *         _audio_outgoing_buffer;
	var_d      fract32                     _tmp_half_energy32;
	debug_d    sint15                      _V34S_LEN_8K0_REMOTE_GUARD;
	var_d      sint15                      _v34_delay_forced_state;
	var_d      uint16                      _v8_rx_QC_data_octet;
	var_d      sint15 (*                   _pcm_x_law_decode_routine) (sint15 code);
	var_d      fract                       _cc_rx_ANAL_BEp_real;
	var_d      sint15                      _state0_save_decimation_count;
	var_d      fract                       _gpf_RRval;
	var_d      state_list_t                _bg_state_list [NUMBER_OF_BG_STATES];
	var_d      int                         _sonitrol_line_status;
	var_d      fract32                     _ptloop_phdet_error_slow32;
	var_d      bool                        _xxx_rb_mode_enable;
	var_d      fract32                     _dtmf_lpf_pow32;
	var_d      uint16                      _v92n_tx_CPd_constel;
	var_d      uint16                      _CID_baud;
	parm_d     bool                        _parm__ipbx_fxo_voip_call_enable;
	const_d    fract                       _correlator_fit_threshold;
	var_d      fract                       _v34_slew_pos_BE;
	shared_d   uint16                      _saved__pump_conference_mode;
	var_d      sint15                      _DIL_probing_index_value_7bit;
	var_d      uint16                      _lec__doubletalk_detect;
	parm_d     uint16                      _parm__ipbx_no_answer_duration;
	var_d      sint15                      _s1_detector_rate_reduction_counter;
	local_d    fract                       _detect_energy_lpf1;
	var_d      uint16                      _asm_oob_tone;
	local_d    fract                       _detect_energy_lpf2;
	local_d    voip_provider_t             _parm__voip_provider [MAX_VOIP_PROVIDERS];
	var_d      event_t                     _fg_inhibit_queue [9];
	var_d      sint15*                     _speech;
	var_d      fract                       _previous_eq_data0;
	var_d      fract                       _previous_eq_data1;
	var_d      uint16                      _ipod_msg_tx_mod_type;
	var_d      int                         _ig_best [(MBEST_GAIN*N9)+1];
	shared_d   fract                       _hsflag_fract_exchange_buffer [4];
	const_d    sint15                      _v29_anti_lock_recovery_limit;
	fast_d     uint16                      _parm__vppn_device_state;
	parm_d     uint16                      _parm__ipbx_timeout_tone_duration;
	fast_d     fract                       _faxdet_value_previous_ansam;
	var_d      fract                       _g711a_plc_lastq [POVERLAPMAX];
	parm_d     uint16                      _parm__ipbx_fc_busy_forward_enable;
	var_d      sint15                      _v90_shape_not_first;
	var_d      fract                       _v90_shape_filters [V90_SHAPER_FRAME_SIZEOF*5];
	var_d      sint15                      _PH2P_POWR_LX_FINAL_TUNE;
	var_d      uint16                      _PCM_LEN_8K0_1ST_GEAR_CHANGE; /* 192 ms */
	var_d      uint16                      _v34_frame_rx_E_found_previous;
	var_d      fract                       _V34_SLEW_RETRAIN;
	var_d      sint15                      _v34_tx_W0_2m;
	parm_d     uint16                      _parm__cp_rd_inc_detect_duration;
	parm_d     bool                        _parm__net_isp_save_as_assigned;
	var_d      uint32                      _v34h_tx_g2_table [36];
	var_d      sint15                      _p18_reversal_timeout_init;
	debug_d    uint16                      _V34S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT;
	local_d    fract                       _echo_canceller_coefs [V32_LOCAL_TAPS + V32_REMOTE_TAPS];
	var_d      fract                       _v34n_rx_optional_gain;
	var_d      bool                        _v92_modem_on_hold_enable;
	var_d      uint16                      _lookback_array_poffset;
	parm_d     char                        _parm__ata_lcr_domain_name [NET_DOMAIN_SIZEOF];
	var_d      uint16  CIRCULAR            _v90_rx_k_frame [V90_RX_K_FRAME_LEN*2];
	var_d      uint16                      _ipod_msg_rx_sig_type;
	var_d      uint16                      _v34n_parm_ptt_hi_carrier_option;
	parm_d     bool                        _parm__slac_ring_type;
	var_d      sint15                      _act_min_sub_shift [ENH_VEC_LENF];
	parm_d     bool                        _stat__net_dhcp_status;
	local_d    uint16                      _parm__ipbx_dial_after_8;
	var_d      classParam                  _classStat_global [TRACK_NUM];
	var_d      legacy_callback_t           _legacy_rx_retransmit_handler;
	parm_d     uint16                      _parm__test_tone;
	local_d    uint16                      _parm__ipbx_dial_after_9;
	shared_d   uint16                      _record_sample_mode;
	shared_d   uint16                      _sample_cnt;
	fast_d     fract                       _pcm_DC_offset_value;
	var_d      void (*                     _line_rx_intp) (uint16);
	var_d      sint15                      _prev_lsp [M_LP];
	parm_d     sint15                      _parm__dtmf_high_tone_gain;
	fast_d     sint15                      _asm_encode_audio_frame_cnt;
	var_d      sint15                      _w_lsf_s [NLSF600];
	var_d      uint16                      _v34h_rx_state;
	parm_d     uint16                      _parm__dm_v90_dpcm_data_rate_mask [2];
	var_d      sint15                      _v34_rx_qn_save1_coefs [2*2*V34_NO_QN_COEFS];
	var_d      uint16                      _v34h_tx_m_ijk_ring_index_buffer [8];
	parm_d     uint16                      _parm__net_router_mode;
	var_d      sint15                      _constellation_imag;
	local_d    fract                       _ph2p_bg_sample_buffer [PH2P_BG_SAMPLE_SIZE];
	var_d      uint16                      _dtmf_peak_col_index;
	var_d      ufract                      _lec__rx_suppressor_gain;
	var_d      fract                       _perfect_complex [2];
	var_d      uint16                      _phone_hook_switch_condition;
	const_d    fract                       _energy_lpf_shift_slew;
	var_d      ufract                      _btrec_baud_filter_gain_lsw;
	var_d      fract                       _eqout_leading_real;
	debug_d    uint16                      _saved_descrambler_input;
	parm_d     struct circuit_tab_s        _parm__net_router_circuit [CIRCUIT_TABLE_ENTRIES];
	debug_d    uint16                      _sart_rx_hybrid_packed_mode_data;
	parm_d     uint32                      _stat__nat_rcv_l2tp; /* LAN to WAN receive L2TP packet type counter */
	var_d      uint16                      _v34_frame_tx_bit_buffer [12]; /* 172+16    = 16*11.75 */
	var_d      char *                      _picp_gain_name;
	var_d      uint16                      _v90_tx_send_Ed_sequence_flag;
	var_d      sint15                      _dgs_energy_count;
	var_d      fract                       _p18_dcd_threshold;
	var_d      thread_routine_t            _v34_forced_train_routine;
	parm_d     uint32                      _parm__mpeg2_sendto_ip_address;
	var_d      sint15                      _pcm_ec_conv_poffset;
	var_d      sint15                      _cc_rx_delay_poffset;
	const_d    uint16                      _fax_CNG_on_length;
	var_d      fract*                      _gpf_xpointer;
	const_d    uint16                      _fax_CNG_preoff_length;
	var_d      sint15                      _res2_buf [PIT_MAX+L_SUBFR];
	var_d      fract                       _demod_leading_imag;
	parm_d     uint32                      _stat__phone_call_elapsed_time;
	parm_d     uint16                      _parm__ipbx_fc_no_answer_forward_disable;
	debug_d    bool                        _v34s_reneg_init_SN_to_S_to_retrain;
	var_d      uint16                      _v90n_rx_maximum_power;
	var_d      uint16                      _stat__oicp_parse_state;
	var_d      uint16                      _lec__nlp_clp_enable;
	var_d      fract                       _syntdenum_ilbc [NSUB_MAX*(LPC_FILTERORDER+1)];
	var_d      uint32                      _encode_frame_end_timestamp;
	var_d      sint15                      _pcm_saved_L_over_2_size;
	parm_d     uint16                      _parm__call_progress_cadence_detect_mask;
	var_d      fract                       _lec__td_data [2*LEC__TD_DATA_SIZE];
	var_d      sint15                      _cc_rx_interpolator_poffset;
	var_d      bool                        _v92n_parm_moh_enable;
	var_d      nat_tab_t *                 _nat_ipsec_entry; /* IPsec translation entry */
	var_d      sint15                      _DIL_calculation_RBS_pcm_maximum;
	var_d      fract                       _demod_real;
	var_d      sint15                      _picp_speed_dial_index;
	parm_d     uint16                      _parm__mbx_timeout_flash_duration;
	var_d      uint16                      _clock_mode;
	const_d    fract                       _monitor_sample_slow_relative_threshold;
	shared_d   uint16                      _sonitrol_local_gateway [4];
	fast_d     ufract                      _parm__analog_loss_attn;
	var_d      nat_tab_t *                 _nat_pptp_entry; /* PPTP translation entry */
	var_d      uint16                      _pcm_rx_sign;
	parm_d     char                        _parm__net_assigned_domain_name [NET_DOMAIN_SIZEOF];
	var_d      sint15                      _l_envdel2 [NUM_BANDS];
	var_d      fract                       _rxs_demod_half_imag [THREAD_BUFFER_SIZE];
	parm_d     bool                        _parm__ipbx_fxo_cid_required;
	parm_d     bool                        _parm__selcall_dec_enable;
	var_d      uint16                      _v34h_tx_q_bits_per_2D_subgroup;
	var_d      sint15                      _v34_frame_rx_save_bit_count;
	var_d      sint15                      _MeanLSF [M_LP];
	parm_d     uint16                      _parm__mgcp_controller_local_port;
	var_d      sint15                      _v34_rx_trellis_lookback_array [V34_LOOKBACK_DEPTH * (16 * 5)];
	parm_d     uint32                      _stat__nat_snd_icmp; /* LAN to WAN send ICMP packet type counter */
	parm_d     uint16                      _parm__ipbx_fc_call_forward_disable;
	var_d      uint32                      _nat_icmp_src_addr; /* Source IP adresss */
	var_d      sint15                      _clock_cycles_per_baud;
	var_d      results_t                   _lec__tx_results;
	persist_d  uint16                      _v34n_tx_lo_carrier_option;
	var_d      fract                       _cc_rx_ANAL_prev_energy_log;
	var_d      int                         _start_bfi600;
	parm_d     uint16                      _parm__dtx_flag;
	debug_d    bool                        _v34s_reneg_test_resp_ignore_SN;
	fast_d     int                         _fg_event_remove;
	fast_d     fract                       _faxdet_value_grl;
	var_d      uint16                      _v90n_tx_receive_data_rate; /* 0 = cleardown, 1-22 data rates */
	fast_d     bool                        _baud_tx_flag;
	local_d    bool                        _parm__ipbx_remote_feature_code_service;
	var_d      sint15                      _picp_number_of;
	var_d      sint15                      _v90_rx_R_detect_flag;
	var_d      fract                       _cc_rx_S_energy_log;
	var_d      fract                       _cc_rx_PP_DC_save_energy_log;
	parm_d     uint32                      _stat__nat_snd_ip_fragment; /* LAN to WAN send IP fragment packet type counter */
	parm_d     uint16                      _stat__sip_is_registered;
	stat_d     uint16                      _stat__call_progress_cadence_detect_mask;
	parm_d     char                        _parm__net_ddns_password [ATA_PASSWORD_SIZEOF];
	parm_d     uint16                      _parm__nat_timeout_ip; /* Idle seconds before IP NAT timeout */
	parm_d     char                        _parm__ipbx_fxo_autoanswer_list [IPBX_LIST__AUTOANSWER_NO_OF][IPBX_DIAL_STRING_SIZEOF];
	var_d      sint15                      _lag0q_dec_mem_s;
	parm_d     struct led_descriptor       _parm__ipbx_led_do_not_disturb;
	var_d      int                         _sonitrol_v34_oob_counter;
	var_d      uint16                      _special_data_limit;
	var_d      sint15                      _g_dcdelin [DC_ORD];
	parm_d     uint16                      _parm__ipbx_fc_do_not_disturb_disable;
	parm_d     fract                       _parm__dtmf_rel_for_twist;
	var_d      sint15                      _v34_resync_baud_correction;
	var_d      uint16 *                    _sart_rx_pointer;
	stat_d     uint16                      _stat__speech_g711_vad_flag;
	var_d      ufract                      _v34_resync_nxt_value;
	var_d      bool                        _ph1s_short_phase1_flag;
	var_d      fract                       _ph2p_anal_variance_12_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _v34n_parm_symbol_option;
	var_d      fract32                     _v90_shape_2_min32;
	var_d      fract                       _pcm_AL_peak_value;
	var_d      sint15                      _rf_fm_put_offset;
	fast_d     bool                        _current_fg_state_active;
	var_d      sint15                      _uicp_number_of;
	parm_d     uint32                      _stat__net_enet_snd_non_rtp;
	debug_d    uint16                      _baud_rx_data_size_code;
	var_d      sint15                      _orig_v8_CJ_count;
	var_d      uint16                      _v90_tx_send_MPA_frame_flag;
	var_d      fract32                     _btrec_baud_filter_gain32;
	var_d      fract                       _ANSam_trace_mid_imag;
	var_d      phase_t                     _ph2_guard_tone_increment;
	var_d      uint16                      _v34h_aux_tx_flag;
	var_d      ufract                      _V34_QN_UPDATE_SLEW;
	var_d      sint15                      _CID_count;
	var_d      uint16                      _bgkernel_current_svalue;
	var_d      fract (*                    _v90_rx_forced_train_routine) (fract);
	var_d      uint16                      _v34h_tx_P_data_frame_size;
	var_d      sint15                      _uicp_feature;
	var_d      sint15                      _pulse_del [MIX_ORD];
	parm_d     uint16                      _parm__sip_session_timer;
	var_d      fract                       _ph2p_anal_log_Gr_exponent;
	var_d      uint16                      _ph2p_anal_maxrates_01_table [PH2P_NO_PREEMPHASIS];
	var_d      sint15                      _gxq_s [2][MBEST_GAIN][NSUBFRAME600*NF600];
	var_d      uint16                      _v34_frame_rx_MP_found_previous;
	const_d    fract                       _equalizer_slew_resync_slow;
	var_d      sint15                      _l_fs_real [PITCHMAX];
	fast_d     int                         _number_fg_timers;
	var_d      sint15                      _v90_tx_dil_sp_offset;
	var_d      sint15                      _v34_tx_pn_remote_imag;
	var_d      uint32                      _rf_interrupt_sample_count;
	var_d      uint16                      _empty_packet_count;
	var_d      uint16                      _v34_local_echo_adjust;
	var_d      uint16                      _v34_resync_state;
	var_d      sint15                      _v34h_rx_V0_m_error_count;
	var_d      sint15                      _l_bpfdelout [NUM_BANDS*BPF_ORD];
	parm_d     uint32                      _stat__nat_rcv_no_translation; /* LAN to WAN receive no translation exit counter */
	var_d      fract                       _saved_peak;
	var_d      fract                       _v34_renego_prev_imag;
	local_d    bool                        _parm__ipbx_warm_line_dialing;
	debug_d    uint16                      _ORIG_LEN_MS_INITIAL;
	parm_d     uint32                      _parm__sip_public_external_ip_address;
	debug_d    fpos_t                      _endtxbd_pos;
	var_d      fract                       _g711_rx_vad_level_min;
	local_d    uint16                      _v34n_tx_local_to_remote_maxrate;
	var_d      uint16                      _v34h_rx_aux_adjust_flag;
	var_d      sint15                      _prpr_y2_hi;
	var_d      uint16                      _pcm_bulk_delay_output_flag;
	debug_d    uint16                      _saved_descrambler_output;
	var_d      fract32                     _pcm_equalizer_fb_coefs32 [PCM_FB_EQUALIZER_SIZE_MAX];
	var_d      uint16                      _v92n_rx_precoder_ff_taps;
	var_d      sint15                      _l_prev_gain_err;
	stat_d     sint15                      _stat__speech_ip_total_length;
	var_d      sint15                      _v34_rx_qn_train_coefs [2*2*V34_NO_QN_COEFS];
	debug_d    uint16                      _baud_tx_delete_fourth;
	var_d      uint16                      _v90_rx_ph4_TRN2_flag;
	parm_d     bool                        _parm__nat_block_redirection; /* Block NAT redirection */
	var_d      uint16                      _lec__rx_cng_frame_poffset;
	var_d      sint15                      _lec__sum_exp;
	parm_d     uint16                      _stat__radio_operating_mode;
	parm_d     struct tone_descriptor      _parm__ipbx_secondary_dial_tone;
	parm_d     uint16                      _parm__sdp_mpeg2_codec_dyn_pt;
	var_d      uint16                      _nat_icmp_dst_port; /* Destination IP port */
	local_d    bool                        _parm__ipbx_call_waiting_caller_id_service;
	var_d      sint15                      _SN_LT_shift;
	var_d      fract                       _fract_output_imag;
	debug_d    sint31                      _v8_tx_count;
	var_d      fract                       _v34_pp_correlate_angle;
	var_d      fract CIRCULAR              _v34_rx_qn_equalized_buffer_real [2*(V34_NO_QN_COEFS + 1)];
	var_d      fract                       _v21_orig_tx_passband_coefs_buffer_internal [C7K2_FSK_TX_BPF_SIZE];
	var_d      sint15                      _renegotiate_threshold;
	parm_d     uint32                      _stat__nat_snd_forwards; /* LAN to WAN send packet forward exit counter */
	var_d      sint15                      _v34_bulk_extra_buffer_real [BULK_EXTRA_BUFFER_SIZE];
	var_d      fract                       _eqout_leading_delay_imag;
	var_d      fract                       _THD_sum_L2_magnitude;
	debug_d    uint16                      _ANSW_LEN_MS_SILENCE_DETECT;
	local_d    bool                        _parm__ipbx_no_answer_forward_service;
	parm_d     bool                        _parm__nat_block_multicast; /* Block multicast */
	parm_d     char                        _parm__net_debug_server [NET_DOMAIN_SIZEOF];
	var_d      sint15                      _v34h_rx_J_super_frame_size_x2;
	var_d      fract                       _fsk_previous_dif_msb;
	parm_d     uint16                      _parm__slac_audio_clamp_duration;
	var_d      uint16                      _ipod_msg_rx_trans_bits;
	var_d      fract                       _v34_tx_zn_remote_imag;
	shared_d   uint16                      _gci_debounce [NUMBER_OF_LINES_PER_DSP];
	var_d      uint16                      _ipod_remote_mode_prev;
	var_d      uint16                      _scramb_lsb;
	var_d      uint16                      _ph2n_tx_frequency_offset;
	var_d      fract                       _cc_rx_ANAL_BEn_imag;
	const_d    fract                       _monitor_sample_agc_2_hi_relative_threshold;
	var_d      int                         _idxVec_ilbc [STATE_LEN];
	parm_d     uint16                      _parm__ipbx_fc_call_forward_enable;
	var_d      uint16                      _v34_equalizer_agc_exp_counter;
	var_d      sint15                      _pcm_xmit_noshape_poffset;
	var_d      sint15                      _mem1_postfilt [LPC_ORD];
	fast_d     sint15                      _remote_interpolator_poffset;
	local_d    uint16                      _v24_cts;
	var_d      sint15                      _att_gain;
	stat_d     sint15                      _stat__speech_enc_mode;
	shared_d   sint15                      _dev_tx_frame_index [NUMBER_OF_LINES_PER_DSP];
	var_d      sint15                      _l_pitTrack [pitTrackParam_LEN * TRACK_NUM];
	var_d      fract                       _pcm_rx_2k_energy;
	var_d      uint32                      _stat__rtp_counter;
	parm_d     uint16                      _parm__ipbx_line_concurrent_voip_count;
	var_d      fract40                     _energy_receive40;
	var_d      sint15                      _PH2P_POWR_LX_FINAL_ROUNDING;
	parm_d     bool                        _parm__net_lan_pppoe_chap_enable;
	fast_d     fract                       _pcm_DC_offset_count;
	var_d      ufract                      _ph2_guard_tone_amplitude;
	var_d      uint16                      _V90S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT;
	parm_d     uint16                      _parm__net_isp_keep_alive_interval;
	var_d      fract                       _cp_biquad_data_buffer [26];
	parm_d     struct tone_descriptor      _parm__ipbx_call_disconnect_tone;
	var_d      sint15                      _pcm_ec_conv_counter;
	parm_d     struct route_tab_s          _parm__net_router_static [ROUTE_TABLE_ENTRIES];
	var_d      sint15                      _l_lpfsp_delout [LPF_ORD];
	var_d      sint15                      _v34_delay_forced_timer;
	debug_d    uint16                      _ANSW_LEN_MS_RLSD_TURNON_DELAY;
	var_d      sint15*                     _scal_res2;
	var_d      sint15*                     _pcm_saved_base_group_table;
	var_d      uint16                      _pcm_playback_data;
	var_d      sint15                      _prev_phase_roll_second;
	var_d      fract                       _v34_tx_decor_output;
	shared_d   int                         _impedance_monitor_rx_speech_overhang;
	debug_d    sint15                      _false_miss_hit_limit;
	var_d      fract                       _out_vxxmod_remote;
	var_d      uint32                      _speech_direct_record_size;
	var_d      fract                       _g722_e4h_bh [7];
	shared_d   uint16                      _wiznet_startup_flag;
	var_d      sint15                      _DIL_probing_pad_exponent;
	var_d      sint15                      _stat__daa_disconnect_count;
	fast_d     sint15                      _decode_transfer_frame;
	var_d      sdp_session_t               _mgcp_sdp_shadow;
	var_d      uint16                      _ipbx_mgcp_dialing_mode;
	var_d      uint16                      _v34n_parm_ptt_attenuation_option;
	parm_d     uint32                      _stat__nat_rcv_ip_tunnel; /* LAN to WAN receive IP tunneling packet type counter */
	shared_d   int                         _impedance_monitor_decimated_sample_count;
	var_d      fract                       _pcm_LO_peak_value;
	var_d      fract32                     _ANSam_magnitude_max32;
	var_d      sint15                      _v34_rx_yn_tilde_imag;
	var_d      EncState                    _speex_enc_state;
	var_d      sint15                      _pcm_folding_minus_delay;
	var_d      fract                       _v34_pp_correlate_log;
	parm_d     sint15                      _parm__handset_tx_gain;
	var_d      fract                       _g168_exc_average;
	var_d      sint15                      _parm__ipbx_distinctive_ring_id;
	parm_d     char                        _parm__ata_email_domain_name [NET_DOMAIN_SIZEOF];
	var_d      uint16                      _phase2_timer;
	const_d    fract                       _monitor_sample_agc_2_lo_relative_threshold;
	var_d      sint15                      _g723_UseHp;
	var_d      sint15                      _prpr_y2_lo;
	local_d    uint16                      _v24_rxd;
	var_d      sint15                      _v34_BE_modify_Gn_exp;
	var_d      sint15                      _v34_rx_un_real;
	var_d      sint15                      _l_syn_inp [4];
	parm_d     char                        _parm__ata_nonce_string [ATA_NONCE_SIZEOF];
	parm_d     bool                        _parm__voip_melp_channel_packing;
	var_d      uint16*                     _v34n_rx_MP1_body [30];
	var_d      sint15                      _p18_demodulator_decrement;
	var_d      sint15                      _monitor_state0_save_count;
	var_d      fract                       _detect_energy_biquad_data [4];
	var_d      sint15                      _v34n_rx_qn_coef_real [V34_NO_QN_COEFS];
	parm_d     fract                       _parm__dm_v34_mse_fallforward;
	parm_d     uint16                      _parm__ipbx_fxo_cid_wait_duration;
	var_d      sint15                      _g711a_plc_overlaplen;
	var_d      sint15                      _cc_tx_modulator_phase;
	var_d      uint16                      _ipod_msg_tx_vad;
	debug_d    uint16                      _ANSW_LEN_MS_NOMINAL_JM;
	var_d      uint16                      _pcm_playback_index;
	var_d      uint16                      _shadow_ANI;
	debug_d    uint16                      _ANSW_LEN_MS_MINIMUM_ANSam;
	var_d      sint15                      _l_sig2 [BEGIN + PITCHMAX];
	parm_d     uint16                      _parm__pump_diag_count_lsw;
	parm_d     bool                        _parm__sip_session_timer_mode;
	var_d      uint16                      _ph4n_tx_MP_type;
	local_d    uint16                      _fg_status_svalue_queue [STATUS_BUFFER_SIZEOF];
	local_d    uint16                      _lookback_array [LOOKBACK_BUFFER_SIZE];
	var_d      uint16                      _nat_icmp_ip_header_size; /* IP packet header size */
	var_d      fract                       _cc_rx_cx_imag;
	var_d      sint15                      _l_sync_bit;
	parm_d     uint16                      _parm__mgcp_tos_value;
	var_d      SBEncState                  _speex_uwb_enc_state;
	var_d      fract                       _ph2p_anal_log_Z_buffer [PH2P_NO_TONES];
	var_d      uint16 *                    _nat_pkt_tcp_ptr; /* Pointer to TCP header */
	var_d      fract                       _g722_e4h_dh [7];
	var_d      sint15                      _ph2_rx_baud_counter;
	var_d      fract                       _g711a_plc_buffer_in [G711_PLC_MAX_FRAME_SIZE];
	parm_d     struct ring_descriptor      _parm__ipbx_call_ring_default;
	parm_d     uint16                      _parm__mgcp_call_agent_protocol;
	stat_d     uint16                      _stat__mbx_dma_state;
	var_d      event_t                     _fg_event_queue [NUMBER_OF_FG_EVENTS];
	var_d      sint15                      _enc_lsp_old_q [M_LP];
	var_d      sint15                      _prev_gain_q_gain_dec;
	fast_d     fract                       _dtmf_clamp_gain;
	var_d      fract32                     _sense_silence_lpf1_32;
	persist_d  uint16                      _ph2n_rx_receive_hi_data_rate;
	var_d      uint16*                     _pcm_saved_eye_map_table;
	parm_d     uint32                      _parm__ata_configuration_update_periodic_delay;
	parm_d     uint16                      _parm__ipbx_green_priority_table [PRIORITY_TABLE_SIZEOF];
	var_d      uint16                      _ata_led_use_mask_phone;
	var_d      sint15                      _w_fs_inv [NUM_HARM];
	var_d      sint15                      _l_tilt_del [TILT_ORD];
	const_d    ufract                      _V34_QN_UPDATE_TRN2_SLOW_SLEW;
	var_d      fract                       _btrec_baud_second_slew;
	shared_d   uint16                      _parm__vppn_device_firmware_version;
	fast_d     sint15                      _local_interpolator_poffset;
	var_d      sint15                      _v34_equalizer_agc_exp;
	var_d      sint15                      _cc_rx_demodulator_decrement;
	var_d      uint16                      _v90_rx_eye_map [6*V90_EYE_MAP_ENTRY_SIZEOF];
	parm_d     uint16                      _parm__sdp_g726_16_codec_dyn_pt;
	shared_d   sint31                      _system_clock_previous;
	var_d      fract                       _ph2p_anal_log_P_buffer_adj [PH2P_NO_TONES];
	stat_d     sint15                      _stat__speech_udp_checksum;
	var_d      uint16                      _v92n_rx_clock_adjust; /* Jp */
	var_d      sint15                      _v34n_tx_frequency_offset;
	var_d      fract                       _rxi_coef [8];
	var_d      sint15                      _lec__nlp_cng_counter;
	var_d      sint15                      _pcm_btr_preset_phase_local;
	var_d      sint15                      _l_ase_num [LPC_ORD +1];
	fast_d     int                         _tone_detector_offset;
	var_d      sint15                      _cc_rx_equalizer_poffset;
	var_d      fract                       _v34_slew_sin_BE0;
	var_d      fract                       _v34_slew_sin_BE2;
	var_d      fract                       _monitor_be2_buffer [5];
	var_d      fract                       _v92_system_ID_error;
	local_d    uint16                      _v34n_rxtx_data_rate_option;
	var_d      fract32                     _faxdet_data_sum_grl_ansam;
	const_d    sint15                      _ANSAM_MAX_SAMPLES_PLUS_1;
	var_d      fract                       _dtmf_goertzel_scale;
	var_d      uint16                      _v90_dpcm_dil_h [8];
	var_d      fract                       _ph2n_rx_receive_gain;
	var_d      uint16                      _v90_tx_skip_TRN2d_flag;
	var_d      sint15                      _pcm_active_RBS_slot;
	var_d      sint15                      _cc_rx_rate_reduction_counter;
	var_d      sint15                      _v34f_cc_DC_detect;
	var_d      uint16                      _v90n_tx_Uinfo_ucode;
	parm_d     uint16                      _parm__ipbx_fc_busy_number_redial_cancel;
	shared_d   int                         _impedance_monitor_tx_noise_floor_sum_counter;
	var_d      fract                       _dcd_diversion_threshold;
	var_d      sint15                      _monitor_decimation_count;
	var_d      fract CIRCULAR              _cc_rx_interpolator_buffer_real [CC_RX_INTERPOLATOR_SIZE*2];
	var_d      uint16                      _telephony_temp;
	var_d      sint15                      _l_prev_pcof [MIX_ORD+1];
	var_d      fract*                      _erroroffset;
	parm_d     sint15                      _parm__line_tx_exponent;
	var_d      uint16                      _v92n_tx_MH_information;
	var_d      ufract                      _lec__alpha_maximum;
	var_d      fract CIRCULAR              _extra_rate_reduction_buffer_real [2 * C7K2_FSK_REDUCE_LPF_SIZE];
	debug_d    fract                       _V34S_PARTIAL_PHROLL_THRESHOLD;
	var_d      ufract                      _agc_1_gain;
	var_d      bool                        _rxs_baud_rx_flag [THREAD_BUFFER_SIZE];
	var_d      fract                       _PH2P_ANAL_PREEQ_ENERGY_LOSS;
	var_d      const uint16*               _detect_tone_masks_p;
	var_d      sint15                      _ph2p_fefo_y_coord_scale_N;
	parm_d     uint16                      _parm__cp_rd_below_range_metric;
	fast_d     int                         _baud_rx_data;
	var_d      sint15                      _v90_rx_L_over_2_size_RBS;
	var_d      uint32                      _scrambler32;
	var_d      sint15                      _pcm_ec_slew; /* used as an exponent value */
	var_d      fract                       _ANSam_trace_real;
	parm_d     char                        _parm__sdp_cn_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      sint15                      _asm_encode_rtp_dtmf_tone;
	local_d    bool                        _parm__ipbx_block_anonymous_service;
	var_d      uint16                      _ans_side;
	const_d    fract                       _ec_slow_slew;
	parm_d     bool                        _parm__ata_firmware_update_enable;
	var_d      fract                       _old_scores [8];
	parm_d     sint15*                     _parm__speech_dec_mbx_addr;
	var_d      uint32                      _v34h_rx_g8_table [276];
	var_d      fract                       _affine_perfect_real;
	parm_d     uint32                      _stat__nat_snd_frag_forward; /* LAN to WAN send fragment forwarding success packet exit counter */
	var_d      fract                       _pcm_rx_feedback_energy;
	var_d      const uint16*               _v90_rx_dil_sp_ptr;
	fast_d     fract                       _agc_2_signal_real;
	var_d      uint16                      _pcm_disable_input_prefilter_flag; /* ??? 1 ??? */
	var_d      fract                       _ph2p_anal_variance_05_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _v90n_tx_reneg_16pt_option;
	shared_d   fract                       _impedance_monitor_saved_coefs [IMPEDANCE_MONITOR_COEF_SIZE];
	var_d      int                         _run_rx_baud_thread;
	var_d      sint15                      _dec_cur_gain;
	var_d      fract                       _v34_TRN2_MSE_S_value;
	var_d      bool                        _parm__tripwire_polarity_control;
	var_d      ufract                      _saved_v34n_tx_transmit_gain;
	var_d      phase_t                     _fsk_ANSam_increment;
	var_d      uint16                      _PCM_LEN_8K0_PRE_GEAR_CHANGE; /*  384 ms * 2, quick fix temp */
	var_d      fract                       _dtmf_peak_row_level;
	parm_d     uint16                      _parm__ipbx_fxo_security_entry_duration;
	parm_d     struct tone_descriptor      _parm__ipbx_distinctive_ring_tone_1;
	parm_d     char                        _parm__ata_factory_name [ATA_ACCOUNT_SIZEOF];
	parm_d     struct tone_descriptor      _parm__ipbx_distinctive_ring_tone_2;
	parm_d     struct tone_descriptor      _parm__ipbx_distinctive_ring_tone_3;
	var_d      uint16                      _ipod_msg_tx_vfd;
	parm_d     struct tone_descriptor      _parm__ipbx_distinctive_ring_tone_4;
	var_d      uint16                      _v92n_tx_data_rate;
	parm_d     struct tone_descriptor      _parm__ipbx_call_forward_dial_tone;
	parm_d     struct tone_descriptor      _parm__ipbx_distinctive_ring_tone_5;
	parm_d     struct tone_descriptor      _parm__ipbx_distinctive_ring_tone_6;
	parm_d     struct tone_descriptor      _parm__ipbx_distinctive_ring_tone_7;
	parm_d     struct tone_descriptor      _parm__ipbx_distinctive_ring_tone_8;
	var_d      sint15                      _PCM_EQUALIZER_EP_SHIFT;
	var_d      sint15                      _parm__speech_udp_source_port;
	var_d      sint15                      _g_dcdel [DC_ORD];
	const_d    uint16                      _V92_TEST_MOH_HOLDOFF;
	var_d      sint15                      _mem_pre;
	var_d      sint15                      _av2_shift [ENH_VEC_LENF];
	parm_d     uint16                      _parm__pcm_playback_loop_size;
	var_d      uint16                      _parm__vppn_device_registration_id [PKT_VPPN__SIZEOF_REGISTRATION_ID];
	var_d      uint16                      _phone_hook_switch_debounce_count;
	parm_d     uint16                      _parm__voip_fax_processing_mode; /* Choice of disabled, uLaw, Alaw, T.38 RTP or T.38 UDPTL */
	const_d    fract                       _threshold_v17;
	var_d      uint16                      _rd_criteria_duration;
	var_d      uint16                      _save_rx_MH_indication;
	const_d    uint16                      _v92n_tx_max_coefs_total; /* INFO1a */
	var_d      ufract                      _PCM_WHITEN_MINIMAL_GAIN;
	parm_d     bool                        _parm__net_isp_connect_on_demand_enable;
	var_d      uint16*                     _shaping_tx_eye_map;
	shared_d   int                         _impedance_monitor_tx_in_offset;
	parm_d     uint16                      _parm__rtp_tos_value;
	parm_d     struct tone_descriptor      _parm__ipbx_sit1_tone;
	var_d      uint16                      _sonitrol_audio_clamp;
	parm_d     uint32                      _stat__nat_wan_receives; /* WAN to LAN receive packet entry counter */
	var_d      fract32                     _pcm_prefilter_fb32;
	var_d      uint16                      _v90n_tx_symbol_rate;
	var_d      unsigned char               _bit_buffer [NUM_CH_BITS];
	var_d      fract CIRCULAR              _cc_rx_equalizer_data_real [CC_RX_EQUALIZER_SIZE*2];
	var_d      uint8                       _sonitrol_remote_control_ip [4];
	var_d      sint15 CIRCULAR             _v90_tx_k_frame [2*V90_TX_K_FRAME_LEN]; /* K0-K5 for each shaping frame */
	var_d      sint15                      _syn_begin;
	var_d      fract                       _pcm_folding_one_over_length;
	parm_d     char                        _parm__mgcp_call_agent_port [NET_DOMAIN_SIZEOF];
	var_d      uint32                      _v90n_rxtx_dpcm_data_rate_option32;
	const_d    fract                       _threshold_v22;
	var_d      fract                       _error_imag;
	var_d      sint15                      _g_dcdelout_hi [DC_ORD];
	const_d    fract                       _threshold_v27;
	const_d    fract                       _threshold_v29;
	parm_d     uint16                      _parm__dm_v92_apcm_data_rate_mask [2];
	var_d      bool                        _v92_tx_send_Jp_frame_flag;
	parm_d     sint15                      _parm__speech_dec_fill_slot_size;
	var_d      uint32                      _ac97_sample_counter;
	var_d      uint16                      _sonitrol_caller_id;
	var_d      sint15 CIRCULAR             _v34_rx_qn_buffer_imag [2*V34_NO_QN_COEFS];
	var_d      sint15                      _l_sigsave [PITCHMAX];
	parm_d     ufract                      _parm__line_rx_gain;
	var_d      uint16*                     _v90_frame_rx_dil_body_h [5];
	var_d      phase_t                     _V34_TXI_PLL_COUNT;
	var_d      uint16                      _v90_rx_ks_value;
	var_d      sint15                      _parm__speech_ip_ttl_protocol;
	var_d      fract                       _jitter_frequency;
	debug_d    uint16                      _V34S_RUN_V0_M_HOLDOFF_TIME;
	var_d      sint15                      _ph2_rx_passband_offset;
	var_d      uint16                      _v34h_tx_SWP_value;
	var_d      sint15                      _g723_UsePf;
	var_d      fract                       _PCM_PARTIAL_CONVERGENCE_THRESHOLD;
	var_d      state_t                     _faxparm_parm__start_state;
	fast_d     sint15                      _v34_rx_trellis_best_score;
	local_d    uint16                      _or_mask;
	persist_d  uint16                      _ph2n_rx_receive_attenuation;
	var_d      fract                       _g722_enc_dethigh;
	var_d      uint16                      _ph1_tx_pcm_state;
	var_d      fract                       _gpf_LLval;
	parm_d     sint15                      _parm__g722_dtx_flag;
	var_d      sint15                      _lec__nlp_cng_offset_counter;
	var_d      sint15                      _v34h_tx_m_count_4D;
	const_d    sint15                      _reversal_timeout_init;
	var_d      uint16                      _phone_headset_condition;
	fast_d     uint16*                     _asm_encodep;
	var_d      sint15                      _faxparm_active__v21_holdoff_timer;
	var_d      bool                        _ata_check_cfg;
	var_d      uint16                      _orig_v8_CI_sent;
	var_d      uint16*                     _v92n_rx_CP_body_start [31];
	var_d      sint15                      _pcm_btr_type_value;
	var_d      fract40                     _training_mse40;
	fast_d     int                         _fg_status_insert;
	var_d      sint15                      _local_gear_value;
	debug_d    uint16                      _baud_rx_fsk_oversample;
	var_d      fract32                     _v34_rx_qn_save0_coef_real32 [V34_NO_QN_COEFS];
	var_d      fract                       _phase_loop_imag;
	var_d      fract                       _lec__probe_xx_output;
	var_d      sint15 *                    _picp_gain_pointer;
	var_d      fract                       _v34_slew_BE0;
	var_d      fract                       _train_on_data_slew;
	parm_d     uint32                      _stat__nat_wan_non_ipv4; /* WAN to LAN receive non-IPV4 packet exit counter */
	var_d      fract                       _v34_slew_BE2;
	var_d      fract                       _v92_predicted_echo;
	debug_d    sint15                      _con_s;
	var_d      fract                       _v34n_rx_required_gain;
	parm_d     sint15 *                    _parm__pcm_playback_loop_bufferp;
	var_d      fract*                      _g711a_plc_pointer_out;
	shared_d   uint16                      _parm__vppn_timeslot_assignment [VPPN_TIMESLOT_COUNT];
	fast_d     fract                       _random_imag_value;
	var_d      fract                       _PCM_RX_AGC2_TARGET_ADJUSTED;
	var_d      fract                       _PH2P_ANAL_NOISE_THRESHOLD;
	parm_d     bool                        _parm__nat_turn_enable;
	var_d      sint15                      _l_prev_sbp3;
	parm_d     sint15                      _parm__tone_pattern [TONE_PATTERN_COUNT + 1];
	var_d      ipbx_call_t *               _ipbx_call_incoming;
	local_d    bool                        _parm__ipbx_polarity_answer;
	var_d      uint16                      _forced_scrambler_msw;
	var_d      uint16                      _stat__daa_debounce_state;
	var_d      fract                       _ph2p_anal_log_Gr_remainder;
	var_d      sint15                      _pcm_btr_predict_msw;
	debug_d    sint15                      _dt_valid;
	stat_d     sint15                      _stat__speech_rtp_sequence_number;
	var_d      uint16                      _ph2_rx_signal_detect;
	var_d      sint15                      _pcm_btr_2nd;
	var_d      sint15                      _constel_decisions_table_nrm [SIZE_DEC_NRM];
	stat_d     sint15                      _stat__speech_silence_detect;
	var_d      uint16                      _stat__oicp_current_key_bit;
	var_d      fract                       _cc_rx_spectrum_offset_table [CC_RX_SPECTRUM_SIZE];
	var_d      uint16*                     _v90n_rx_Jd_body [10];
	debug_d    uint16                      _baud_tx_corrupt_packet_cnt;
	debug_d    sint31                      _bits_counter;
	var_d      sint15                      _pcm_btr_measurement_angle;
	var_d      sint15                      _PH2P_ANAL_TEST_SYMBOL_RATE;
	var_d      uint16                      _pcm_rx_sign_previous;
	var_d      fract                       _pcm_prefilter_ff;
	var_d      uint16                      _rf_sample_foreground_offset;
	var_d      fract*                      _ph2p_bg_sample_in_pointer;
	const_d    fract                       _parm__dm_v92_mse_data_bias;
	var_d      g726_state_OBJECT           _g726_enc_state;
	var_d      sint15                      _lsd_recovery_substate;
	parm_d     struct tone_descriptor      _parm__ipbx_pre_ringback_tone;
	var_d      fract *                     _ph2_tx_passband_coef_pointer;
	parm_d     uint16                      _stat__caller_id_msg_len;
	var_d      sint15                      _dg_s [(MBEST_GAIN*N9)+1];
	var_d      uint16                      _v34n_parm_clock_option;
	var_d      sint15                      _lec__block_update_counter;
	parm_d     uint16                      _parm__ipbx_fxo_billing_delay_duration;
	var_d      uint16                      _ipod_msg_rx_chan_ID;
	debug_d    uint16                      _V34S_ORIG_8K0_2RT_INFO1cend_to_Jsrt;
	var_d      fract                       _helper_real;
	var_d      sint15                      _prev_scale;
	parm_d     uint16                      _parm__ipbx_fxo_cid_clear_duration;
	var_d      sint15                      _v90_rx_sample_counter;
	var_d      fract                       _v34_TRN2_agc_value;
	var_d      uint16                      _v92n_tx_E2u_extend;
	var_d      sint15                      _dec_seed;
	const_d    uint16                      _second_trn_length;
	fast_d     fract CIRCULAR              _tx_passband_buffer [2*(C7K2_FSK_TX_BPF_SIZE)];
	var_d      fract                       _pcm_probe_imag;
	var_d      sint15                      _g_dcdelout_lo [DC_ORD];
	var_d      uint16                      _PCM_LEN_8K0_EQC_TRN1A_3RD;
	var_d      sint15                      _v34s_log_energy_previous;
	var_d      fract                       _cmr_notch_data [4];
	parm_d     sint15                      _parm__speech_device_type;
	parm_d     uint32                      _stat__nat_wan_create_failed; /* WAN to LAN receive translation entry create failed packet exit counter */
	parm_d     uint32                      _stat__nat_rcv_receives; /* LAN to WAN receive packet entry counter */
	var_d      fract                       _V34N_TRN2_DATA_MAXRATE_TABLE [V34N_MAX_MAXRATE];
	debug_d    uint16                      _ORIG_LEN_MS_SART_TO_SAMPLE_DWELL;
	var_d      bool                        _picp_dtmf_tone_started;
	persist_d  uint16                      _v34n_rxtx_difference_option;
	var_d      uint16                      _saved_scrambler_msw;
	var_d      uint16 *                    _sart_tx_pointer;
	var_d      sint15                      _v34s_run_V0_m_error_count;
	var_d      int                         _ipod_htd_coded_speech_offset;
	var_d      fract                       _guard_tone_gain;
	shared_d   uint16                      _stat__led_ringing_mask;
	var_d      mse_struct                  _v34_TRN2_MSE_N_stack [V34_TRN2_MSE_STACK_SIZE];
	fast_d     sint15                      _parm__analog_loss_count;
	parm_d     uint16                      _parm__ipbx_message_waiting_refresh_duration;
	parm_d     uint16                      _parm__vpcm_maximum_power;
	var_d      uint16                      _rd_trans2_state;
	var_d      fract*                      _gpf_rpointer;
	var_d      sint15                      _l_postHPF [6];
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_1;
	parm_d     uint16                      _parm__nat_timeout_triggered; /* Idle seconds before port triggered NAT timeout */
	var_d      uint32                      _parm__speech_rtp_cng_period; /* 240 ms */
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_2;
	var_d      fract                       _v34_local_echo_coefs [xV34_XX_LOCAL_TAPS];
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_3;
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_4;
	var_d      sint15                      _uicp_function;
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_5;
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_6;
	var_d      uint16                      _ph2n_probing_preemph [2*(V34N_MAX_SYMBOL + 1)];
	parm_d     bool                        _parm__sip_bye_authentication;
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_7;
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_8;
	const_d    fract                       _DCD_HYSTERESIS;
	var_d      SPP_rx_transaction_t *      _ethernet_SPP_rx_message;
	var_d      fract                       _demod_half_imag;
	var_d      uint16                      _ipod_msg_tx_payload_size;
	var_d      fract32                     _v34_BE_pos_power_32;
	var_d      uint16*                     _v92n_tx_INFO1a_body [9];
	fast_d     vppn_packet_t *             _vppn_encode_packet;
	var_d      uint16                      _ph2_ac_sample_bit_pattern [10];
	var_d      ufract                      _saved_parm__pump_transmit_level;
	var_d      sint15                      _DIL_calculation_pad_exponent;
	var_d      sint15                      _PH2P_ANAL_TEST_CARRIER_FREQUENCY;
	var_d      sint15                      _v_flag;
	const_d    fract                       _train_on_data_32_slew;
	var_d      sint15                      _pcm_fb_equalizer_size;
	var_d      v34f_cc_energy_data_t       _cc_rx_AC;
	var_d      fract32                     _sigdet_save32 [2];
	shared_d   int                         _interrupt_sample_count;
	var_d      fract                       _ph2n_rx_receive_agc2_level;
	var_d      uint16                      _v92n_tx_CPd_modulus;
	var_d      SPP_data_buffer_t *         _sonitrol_v34_rx_buffer;
	fast_d     uint16                      _asm_encode_control_mask;
	var_d      sint15                      _DIL_probing_symbol_counter;
	var_d      fract32                     _input_sample_energy32;
	var_d      uint16                      _v34n_rx_clock_mode;
	local_d    uint16                      _v24_dcd;
	var_d      fract   CIRCULAR            _pcm_xmit_noshape_buffer [2*PCM_XMIT_NOSHAPE_SIZE];
	var_d      uint16                      _PMOVLAY;
	debug_d    uint16                      _mark_idle_rx_active;
	var_d      sint15                      _lsd_recovery_signal_state;
	var_d      uint16                      _vppn_device_firmware_length;
	var_d      powr_measurement_t          _rx_measurment_buffer_1;
	parm_d     uint32                      _stat__nat_rcv_non_ipv4; /* LAN to WAN receive non-IPV4 packet exit counter */
	var_d      uint16                      _ph4n_tx_auxiliary_option;
	parm_d     char                        _parm__ata_user_password [ATA_PASSWORD_SIZEOF];
	var_d      sint15                      _ds_gain [N9+1];
	var_d      sint15                      _v90_tx_dil_ucode_offset;
	var_d      uint8 *                     _ipod_iface_rx_bufp;
	var_d      fract                       _cc_rx_PP_BEn_save_energy_log;
	var_d      uint16*                     _v90_frame_tx_dil_body_sp [2];
	var_d      sint15                      _g723_UseVx;
	var_d      uint16                      _v92n_tx_reneg_8pt_option;
	debug_d    bool                        _orig_v8_allow_very_short_ANSam;
	persist_d  uint16                      _v34n_rx_hi_data_rate_option;
	var_d      fract                       _pcm_16K_input_sample;
	var_d      uint16                      _loopback_poffset;
	var_d      sint15                      _g726_dec_coding;
	parm_d     uint32                      _stat__nat_wan_pptp; /* WAN to LAN receive PPTP packet type counter */
	debug_d    sint15                      _baud_rx_cnt;
	var_d      sint15                      _lec__td_hold_1st_cnt;
	var_d      uint16                      _tx_packet_count;
	var_d      fract                       _THD_sum_L2_S_over_N;
	var_d      uint16*                     _v34n_tx_MP0_body [18];
	var_d      sint15                      _v34_rx_qn_save0_coefs [2*2*V34_NO_QN_COEFS];
	var_d      sint15                      _v90_rx_R_detect_slot;
	var_d      uint16                      _sonitrol_panel_group_desc [70+1];
	shared_d   uint16                      _gci_control [NUMBER_OF_LINES_PER_DSP];
	debug_d    uint16                      _PCM_TEST_PAD_SIMULATION_SELECT;
	var_d      sint15                      _g_hpspeech [IN_BEG+BLOCK];
	var_d      sint15                      _PCM_EC_INPUT_PRE_SHIFT;
	var_d      uint16                      _tx_dtmf_early_count;
	var_d      uint16*                     _v90_frame_tx_dil_body_tp [2];
	local_d    bool                        _parm__ipbx_disturb_accept_service;
	var_d      uint16                      _v90n_tx_training_attenuation; /* TX/Codec TX signal RMS in unsigned 3.13 */
	debug_d    fract                       _cp_threshold;
	var_d      uint16                      _bitval;
	var_d      uint16                      _special_match_msw;
	var_d      uint16                      _v34n_parm_CME_option;
	parm_d     struct tone_descriptor      _parm__ipbx_call_waiting_tone_default;
	var_d      fract CIRCULAR              _p18_data_buffer_imag [C7K2_RX_SEQUENCE_DETECTOR_SIZE * 2];
	var_d      uint16                      _v92h_rx_Q_table [V92_MOD_M_BUFFER_SIZE*V92_LEN_8K0_DATA_FRAME];
	var_d      fract                       _pcm_8K0_equalized_ep;
	var_d      uint16                      _sonitrol_audio_ip_timeout;
	parm_d     char                        _parm__ata_user_email [ATA_MESSAGE_SIZEOF];
	var_d      fract                       _pcm_8K0_equalized_eq;
	parm_d     bool                        _parm__nat_ipsec_enable; /* IPsec enable */
	var_d      fract                       _pcm_8K0_equalized_er;
	var_d      uint16*                     _v34h_tx_pointer;
	var_d      fract                       _pcm_btr_gain_power;
	var_d      ufract                      _PCM_WHITEN_MAXIMAL_GAIN;
	var_d      sint15                      _ph2_ac_sample_offset;
	var_d      v34f_cc_energy_data_t       _cc_rx_DC;
	debug_d    sint15                      _V34_RESYNC_FILL_LENGTH;
	parm_d     uint32                      _stat__net_current_gateway_address;
	debug_d    uint16                      _sart_tx_underflow;
	parm_d     char                        _parm__net_router_modem_script [ATA_MODEM_SCRIPT_SIZEOF];
	var_d      int                         _g722_e4h_sg [2];
	var_d      fract                       _ph2p_powr_powr_cx_buffer [PH2P_BLOCKSIZE];
	var_d      fract                       _pcm_8K0_equalized_fb;
	var_d      fract                       _g722_e4h_sh;
	var_d      fract                       _pcm_8K0_equalized_ff;
	parm_d     uint16                      _parm__nat_hairpin_enable; /* NAT hairpin routing enable */
	var_d      sint15                      _PH2P_POWR_L2_FINAL_TUNE;
	var_d      sint15                      _n_pwr_shift;
	var_d      uint16                      _stat__uicp_parse_state;
	parm_d     bool                        _parm__sip_allow_incoming_registration;
	var_d      complex                     _pushed_demod_complex;
	var_d      uint16                      _rx_wr_index;
	shared_d   uint16                      _stat__vppn_master_firmware_version;
	var_d      char *                      _uicp_list;
	var_d      uint16                      _V90S_APCM_8K0_1RT_Jsrt_to_S_SNdet;
	var_d      sint15                      _angle_1st_data_correction;
	var_d      SBEncState                  _speex_sb_enc_state;
	var_d      sint15 *                    _pcm_playback_bufferp;
	var_d      thread_routine_t            _v34_resync_train_routine;
	parm_d     bool                        _parm__ata_local_update_enable;
	var_d      fract                       _v34n_rx_preeq_Whi;
	var_d      bool                        _v92_MH_disconnect_flag;
	fast_d     uint16                      _vppn_hook_debounce;
	parm_d     uint32                      _stat__nat_rcv_translated; /* LAN to WAN receive translated packet counter */
	var_d      uint16                      _ph2_tx_data_size_1;
	var_d      uint16                      _parm__tripwire_captured;
	shared_d   bool                        _stat__ipbx_hook_state [NUMBER_OF_LINES_PER_DSP];
	var_d      fract32                     _v34_rx_qn_save0_coef_imag32 [V34_NO_QN_COEFS];
	parm_d     bool                        _parm__codec_disconnect_tone_1_enable;
	fast_d     uint16                      _rx_interpolator_poffset;
	parm_d     uint32                      _stat__nat_wan_frag_failed; /* WAN to LAN receive fragment forwarding failed packet exit counter */
	var_d      sint15                      _pcm_ec_counter;
	const_d    uint16                      _V92_TEST_MOH_SILENCE_LENGTH;
	debug_d    uint16                      _baud_rx_bit_cnt;
	var_d      bool                        _stat__in_conference;
	var_d      uint16                      _v92n_parm_rx_reneg_8pt_option;
	var_d      sint15                      _v34_tx_un_real;
	persist_d  uint16                      _v34n_rx_lo_carrier_option;
	var_d      fract                       _pcm_folding_value1;
	parm_d     bool                        _parm__sip_allow_incoming_subscription;
	var_d      fract                       _pcm_folding_value2;
	shared_d   uint16                      _parm__net_debug_level_omc;
	var_d      bool                        _parm__audio_agc_enable;
	var_d      struct melp_param           _melp_par [NF];
	var_d      bool                        _v92_MH_response_end_flag;
	var_d      uint16                      _PCM_LEN_8K0_EQC_TRN1A_FILL; /* @8K0, 1/2 FF equalizer */
	var_d      fract32                     _btrec_phdet_error_lpf32;
	var_d      uint16                      _rd_prev_rings;
	var_d      sint15                      _v34h_tx_Z_m;
	var_d      uint16                      _vppn_device_firmware_offset;
	var_d      sint15*                     _plookback;
	parm_d     uint16                      _parm__ipbx_pause_wait_duration;
	parm_d     sdp_session_t               _rsdp;
	var_d      fract                       _train_on_data_coordinate;
	parm_d     bool                        _parm__nat_pptp_enable; /* Point-to-Point Tunneling Protocol (PPTP) enable */
	var_d      uint16                      _picp_access;
	parm_d     uint32                      _parm__rtp_public_external_ip_address;
	var_d      sint15                      _lambdaD_shift [ENH_VEC_LENF];
	var_d      uint16                      _ipod_htd_voice_semaphore;
	var_d      fract CIRCULAR              _local_interpolator_buffer_imag [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	var_d      state_t                     _faxmon_modulation_state;
	shared_d   fract                       _impedance_monitor_tx_noise_floors [LIM_NOISE_FLOOR_COUNT];
	var_d      fract                       _btrec_baud_first_slew;
	debug_d    uint16                      _v8_rx_sync_code;
	var_d      bool                        _v92_tx_send_Sd_align_flag;
	shared_d   fract                       _impedance_monitor_tx_in [IMPEDANCE_MONITOR_DECIMATE_DATA_SIZE * 2];
	const_d    sint15                      _V92_RuN_REMAIN;
	var_d      uint16                      _ph4n_rx_trained_shaping;
	var_d      fract   CIRCULAR            _pcm_xmit_deshape_buffer [2*PCM_XMIT_DESHAPE_SIZE];
	var_d      fract                       _DIL_probing_2nd_repetition_table [DIL_PROBING_2ND_LENGTH];
	parm_d     uint16                      _parm__rx_type;
	var_d      fract CIRCULAR              _ph2_tx_rate_conv_9K6_8K0_buffer [2*(PH2_TX_RATE_CONV_DATA_BUFFER)];
	parm_d     uint16                      _stat__mgcp_local_contact_port;
	var_d      bool                        _v34s_special_local_train_enable;
	shared_d   uint16                      _parm__net_debug_level_ooma;
	parm_d     fract                       _parm__dtmf_col_no_tone_level;
	parm_d     uint16                      _parm__fxpmp_prefax;
	fast_d     uint16                      _dpbx_key_mask;
	var_d      sint15                      _pcm_TRN2_MSE_flag;
	var_d      sint15                      _cc_rx_S_repetition_counter;
	var_d      sint15                      _smoothedspect [ENH_VEC_LENF];
	parm_d     sint15                      _parm__codec_disconnect_silence_threshold;
	var_d      fract                       _ph2p_anal_variance_11_table [PH2P_NO_PREEMPHASIS];
	var_d      fract32                     _v90_shape_1_min32;
	var_d      sint15                      _v90_rx_k_input_offset;
	var_d      sint15                      _asm_decode_sample_unpack_shift_cnt;
	var_d      fract                       _ANSam_trace_magphase_lpf_real;
	var_d      uint16                      _v90_tx_eye_map [V90_EYE_MAP_ENTRY_SIZEOF*6*2];
	fast_d     uint16                      _vppn_device_command_send_wait;
	var_d      uint16                      _fsk_bitstream_msb;
	const_d    fract                       _DELTA_SLEW_RATE;
	var_d      fract                       _v34_slew_cos_BE0;
	var_d      sint15                      _orig_v8_CI_count;
	var_d      sint15                      _lec__error_poffset;
	parm_d     uint32                      _stat__nat_rcv_ip_fragment; /* LAN to WAN receive IP fragment packet type counter */
	var_d      fract                       _v34_slew_cos_BE2;
	parm_d     char                        _stat__ata_update_cfgfile_url [ATA_URL_SIZEOF];
	var_d      uint16                      _v34n_parm_cc_asymmetric_option;
	var_d      sint15                      _l_prev_fsmag [NUM_HARM];
	fast_d     phase_t                     _demodulator_decrement;
	var_d      sint15                      _pcm_rx_exponent;
	var_d      fract                       _cc_rx_equalizer_coef_imag [CC_RX_EQUALIZER_SIZE];
	var_d      fract32*                    _saved_Lx_spectrum_power_pointer32;
	var_d      uint16                      _v34h_rx_P_data_frame_size;
	parm_d     fract                       _parm__dtmf_row_2nd_harm;
	var_d      sint15                      _g_msvq_bits [4];
	var_d      uint16                      _ph2p_anal_maxrates_00_table [PH2P_NO_PREEMPHASIS];
	var_d      sint15                      _cc_counter_not_flags;
	var_d      fract                       _error_complex [2];
	var_d      uint16                      _v92h_rx_R0_sign;
	parm_d     ufract                      _parm__dtmf_high_tone_level;
	var_d      sint15                      _ph4n_rx_trained_qn_coef_real [V34_NO_QN_COEFS];
	debug_d    uint16                      _ORIG_LEN_MS_Te;
	var_d      fract                       _ANSam_trace_count_2100_real;
	debug_d    sint15                      _v34_TRN2_MSE_report_rate;
	parm_d     sint15                      _parm__codec_disconnect_reversals_originate;
	var_d      fract32                     _edge_m1200_real32;
	var_d      fract                       _equalized_yn_real;
	stat_d     sint15                      _stat__rx_level_dbm;
	debug_d    uint16                      _V34S_RUN_8K0_STATISTICS_TIME;
	var_d      sint15                      _l_bpfdelin [NUM_BANDS*BPF_ORD];
	local_d    sint15                      _asm_encode_mbx [ASM_ENCODE_SLOT_CNT_MAX * ASM_ENCODE_SLOT_SIZE_MAX];
	var_d      fract                       _demod_lagging_half_imag;
	parm_d     uint32                      _parm__net_router_circuit_default_dial_wait;
	parm_d     bool                        _parm__net_lan_pptp_enable;
	var_d      int                         _lec__td_error_offset;
	parm_d     uint16                      _parm__sart_hdlc_crc32_rx_en;
	var_d      jmp_buf                     _bg_task_jmp_buf;
	parm_d     struct led_descriptor       _parm__ipbx_led_line_in_use;
	var_d      sint15                      _asm_within_dtmf_min;
	var_d      uint8                       _g726_dec_parm;
	var_d      fract                       _v34n_rx_preeq_Wlo;
	var_d      uint16                      _v34_tx_local_use_nonlinear;
	debug_d    sint15                      _cp_output;
	shared_d   uint16                      _sonitrol_ethernet_master_timer;
	var_d      uint16                      _v92n_tx_CPd_prefilt;
	var_d      bool                        _fsk_run_decision;
	var_d      uint16                      _v34h_tx_K_number_shell_bits;
	debug_d    ufract                      _V34_BE_SLEW_FAST;
	var_d      uint16                      _saved_apcm_receive_level;
	parm_d     uint32                      _parm__net_router_modem_baudrate;
	var_d      bool                        _comn_v8_from_on_hold;
	var_d      uint16                      _orig_v8_found_JM;
	var_d      fract                       _THD_sum_L2_S_power;
	fast_d     phase_t                     _demodulator_phase;
	var_d      sint15                      _ph2p_powr_rx_clear_length;
	parm_d     uint16                      _parm__dm_v34_ptt_restriction_mask;
	debug_d    uint16                      _fax_rlsd_length;
	fast_d     bool                        _parm__report_timer_tick;
	coef_d     fract CIRCULAR              _lec__error_buffer [2 * LEC__BLOCK_SIZE];
	parm_d     sint15                      _parm__speech_dec_mode;
	parm_d     struct tone_descriptor      _parm__ipbx_ringback_tone;
	var_d      uint16                      _pcm_disable_input_pstfilter_flag; /* ??? 1 ??? */
	var_d      uint16                      _v34h_tx_N_bits_per_data_frame;
	var_d      sint15                      _lec__delay_poffset;
	var_d      fract                       _cc_rx_S_last_compare_ratio;
	var_d      fract                       _v34n_rx_preeq_Wme;
	var_d      uint16                      _orig_v8_found_ANS;
	var_d      sint15                      _l_classStat [classParam_LEN * TRACK_NUM];
	var_d      sint15                      _sumAcf [SIZ_SUMACF];
	var_d      sint15                      _v34_rx_pn_imag;
	var_d      complex                     _demod_complex;
	var_d      fract                       _PH2P_ANAL_THD_THRESHOLD;
	parm_d     uint16                      _parm__mgcp_max_forwards;
	var_d      fract                       _DIL_calculation_pad_target_log;
	var_d      uint16                      _v90_tx_send_Jd_frame_flag;
	var_d      fract CIRCULAR              _rx_lpf_buffer [C7K2_FSK_RX_LPF_SIZE * 2];
	var_d      sint31                      _g_voicedCnt;
	var_d      fract                       _v34_MSE_value_energy;
	var_d      sint15                      _predicted_rx_xn_B1_Q_n_imag [16 * 8];
	var_d      fract                       _lec__holding_buffer [3*LEC__BLOCK_SIZE];
	parm_d     uint16                      _parm__dm_v34_test_options_mask;
	var_d      fract CIRCULAR              _cc_tx_passband_buffer [(CC_TX_PASSBAND_SIZE-1) * 2];
	parm_d     uint16                      _stat__phone_hook_switch_state;
	parm_d     uint16                      _parm__cp_rd_min_detect_duration;
	var_d      event_t                     _V92_EVENT__XXA_RECEIVED;
	debug_d    uint16                      _v34s_conditional_frequency_offset;
	var_d      fract                       _previous_eq_error;
	var_d      char                        _picp_dial_string [LCD_CHAR_DISPLAY_MAX];
	var_d      fract                       _fract_input_imag;
	var_d      uint16                      _v90_apcm_dil_first;
	parm_d     uint16                      _parm__nat_timeout_udp; /* Idle seconds before UDP NAT timeout */
	var_d      sint15                      _pcm_error_lpf_poffset;
	var_d      ufract                      _lec__tx_suppressor_gain;
	var_d      uint16                      _fsk_baud_rx_data;
	var_d      fract                       _ANSam_trace_min_real;
	var_d      fract                       _pcm_agc_2_delta_log;
	var_d      sint15                      _missed_sample_counter;
	parm_d     int                         _parm__tone_detectors_num_tones;
	fast_d     fract CIRCULAR              _rx_lpf_buffer_real [2 * C7K2_RX_LPF_SIZE];
	var_d      fract32                     _pcm_pstfilter_fb32;
	var_d      int                         _echo_canceller_debug_display_offset;
	parm_d     uint16                      _parm__slac_initialization_commands [IPBX_SLAC_COMMAND_SIZEOF];
	var_d      uint16                      _ipod_msg_tx_coder;
	var_d      fract                       _V90_RX_1K3_ENERGY_THRESHOLD;
	fast_d     sint15                      _faxdet_data_cntr;
	var_d      sint15                      _speech_sync_enc_delay_cntr;
	var_d      uint16                      _prev_cng_flag;
	var_d      sint15                      _det_exponent;
	var_d      sint15                      _v90_rx_dil_lsp;
	debug_d    sint15                      _cp_decimate;
	fast_d     sint15*                     _decode_frame_pointer;
	var_d      uint16                      _rd_trans2_timer;
	local_d    bool                        _parm__ipbx_do_not_disturb_service;
	var_d      ufract                      _v34_temp_pre_emph_adjust_table [11];
	local_d    bool                        _parm__ipbx_forward_last_call_service;
	var_d      fract                       _v34f_eqc_sd_DC_imag;
	var_d      sint15                      _PCM_EQUALIZER_FB_SHIFT;
	var_d      uint16                      _ph1_x_law_round_mask;
	parm_d     bool                        _parm__sip_nat_keep_alive_enable;
	fast_d     rtp_stream_t*               _current_video_rtp_stream;
	var_d      fract32                     _v34_rx_yn_error_real_32;
	var_d      uint16                      _active_detect_tones;
	parm_d     uint16                      _faxparm_active__CED_generate;
	var_d      sint15                      _envdel [NUM_BANDS][ENV_ORD];
	parm_d     struct tone_descriptor      _parm__ipbx_call_hold_disconnect_tone;
	parm_d     uint32                      _stat__net_dhcp_server_ip_addess;
	fast_d     fract                       _random_real_value;
	shared_d   uint16                      _system_clock_remainder;
	var_d      fract                       _lec__tec_data [2*LEC__TEC_DATA_SIZE];
	var_d      uint16                      _saved_scrambler_shift;
	var_d      uint16                      _v90n_tx_receive_shaping_lookahead; /* 0 - 3 = Requested lookahead */
	var_d      mse_struct                  _v34_pnt12_MSE_stack [V34_TRN2_MSE_STACK_SIZE];
	var_d      fract32                     _phroll_remote_energy32;
	var_d      fract                       _jitter_2nd_order_slew;
	local_d    uint16                      _v34n_tx_use_shaping;
	const_d    fract                       _full_convergence_threshold;
	var_d      uint16                      _scrambler_bits_per_baud;
	parm_d     char                        _parm__sip_incoming_auth_realm [STRSIZE_64]; /* normally, this would come from a database of users and auth info */
	var_d      sint15                      _v90_rx_dil_ltp;
	var_d      uint16                      _common_local_return;
	var_d      uint16                      _tone_pattern_ms;
	var_d      uint16                      _parm__record_enable;
	parm_d     struct led_descriptor       _parm__ipbx_led_ringing_or_waiting;
	var_d      fract                       _pushed_demod_real;
	var_d      sint15                      _current_input_real;
	parm_d     char                        _parm__sdp_jpeg_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      uint16                      _dtmf_clamp_state;
	const_d    sint15                      _v17_diagnostics_mse_limit;
	var_d      legacy_comm_data_t          _legacy_comm_data;
	var_d      sint15                      _v34_tx_Y0_m;
	shared_d   uint16                      _sonitrol_hotplug_state;
	stat_d     uint16                      _stat__ipod_allowed_mode_mask;
	var_d      sint15                      _asm_lb_packet_buffer [ASM_DECODE_SLOT_SIZE_MAX];
	local_d    char                        _parm__ipbx_call_forward_dial_string [IPBX_DIAL_STRING_SIZEOF];
	var_d      sint15                      _angle_1st_data_difference;
	var_d      quant_param600              _quant_par600;
	persist_d  uint16                      _v34n_tx_CME_option;
	var_d      sint15                      _disp_del [DISP_ORD];
	parm_d     uint16                      _parm__rtp_port_maximum;
	var_d      uint16                      _change_detect_tones;
	local_d    bool                        _parm__ipbx_block_last_call_service;
	parm_d     nat_port_forward_t          _parm__nat_port_forward [NAT_PORT_FORWARD_ENTRIES];
	var_d      uint16*                     _asm_encode_savep;
	var_d      fract                       _cc_rx_Nk_energy_log [9];
	parm_d     sint15                      _parm__speech_asm_lb;
	debug_d    uint16                      _baud_tx_data_size_code;
	var_d      sint15                      _ph2_rx_dcd_level;
	var_d      sint15                      _parm__speech_rtp_cn_payload_type;
	var_d      unsigned int                _g726_in_buffer;
	var_d      sint15                      _flag_chang;
	debug_d    ufract                      _V34_BE0_SLEW_FAST;
	var_d      uint16                      _pcm_bulk_delay_input_last;
	parm_d     uint16                      _parm__voip_g723_high_rate_enable;
	var_d      sint15                      _ph2_tx_Lx_offset;
	var_d      fract                       _convert_log__gain;
	var_d      uint16                      _lec__nlp_sid_enable;
	parm_d     uint16                      _parm__sart_binary_prev_data;
	var_d      fract                       _v92_rx_decoder_ep_coefs [V92_RX_DECODER_EP_SIZE]; /* MEMORY_AVAILABLE */
	var_d      void (*                     _v34_delay_forced_routine) (void);
	var_d      struct led_descriptor       _dpbx_led_pattern_queue [DPBX_LED__QUEUE_SIZEOF];
	parm_d     uint16                      _parm__ipbx_reconnect_debounce;
	var_d      uint16                      _v34h_rx_AMP_value;
	fast_d     bool                        _stat__vppn_ringing_on;
	var_d      uint8*                      _speech_direct_record_data;
	var_d      sint15                      _phone_key_repeat_count;
	parm_d     uint16                      _parm__mgcp_rsip_keepalive_interval;
	var_d      fract                       _ANSam_trace_magphase_max_real;
	var_d      thread_routine_t            _v92_MH_retrain_routine;
	var_d      uint16 *                    _nat_pkt_payload_ptr; /* Pointer to packet payload */
	var_d      sint15                      _asm_encode_rtp_ans_send_cnt;
	parm_d     sint15                      _parm__lec_delay_length;
	debug_d    sint15                      _ec_very_slow_shift_slew_remote;
	shared_d   sint15                      _hsflag_sint15_exchange_buffer [4];
	var_d      fract                       _v34_resync_perfect_imag;
	debug_d    uint16                      _dt_status_bit;
	var_d      sint15                      _parm__speech_rtp_sequence_number;
	parm_d     char                        _parm__net_ddns_user_name [ATA_ACCOUNT_SIZEOF];
	var_d      sint15                      _xq_s [NSTAGEMAX][MBEST_LSF][NLSF600];
	const_d    sint15                      _v32_timeout_margin;
	var_d      uint16                      _test_1_ext;
	var_d      uint16                      _pcm_ctl_disable_whiten;
	var_d      int                         _sonitrol_v34_spp_state;
	var_d      fract                       _eqout_lagging_real;
	parm_d     uint32                      _parm__ata_configuration_update_error_retry_delay;
	var_d      fract                       _v32_rx_trellis_best_score;
	const_d    fract                       _phroll_convergence_threshold;
	const_d    fract                       _dcd_energy_inc;
	debug_d    sint15                      _prev_con_s;
	var_d      sint15                      _pcm_rx_offset;
	var_d      thread_routine_t            _pcm_rx_8K0_data_routine_in;
	var_d      fract32                     _pcm_equalizer_ff_coefs32 [PCM_FF_EQUALIZER_SIZE_MAX];
	var_d      uint16*                     _v90n_tx_Jd_body [10];
	var_d      sint15                      _picp_offset;
	parm_d     uint16                      _parm__sip_remote_user_parm;
	var_d      results_t                   _lec__xx_results;
	var_d      uint16                      _v90n_rx_v90_override;
	var_d      uint16                      _v34h_tx_process_enable;
	var_d      fract                       _v34_slew_neg_BE;
	var_d      fract32                     _faxdet_data_sum_ansam;
	var_d      sint15                      _dec_lsp_old [M_LP];
	var_d      bool                        _stat_sms_message_received;
	var_d      Speech_Encode_FrameState    _amrEnc_struct;
	var_d      fract                       _DIL_probing_pad_gain_log;
	var_d      sint15                      _l_lpres_delin [LPF_ORD];
	shared_d   uint16                      _sample_overflow_count;
	var_d      fract                       _demod_lagging_imag;
	var_d      uint16                      _p18_bit_delay_buffer [4];
	var_d      fract                       _detect_demod_imag;
	var_d      v34f_cc_energy_data_t       _cc_rx_S;
	var_d      sint15                      _v34_rx_predicted_V0_m_Px2_counter;
	parm_d     bool                        _parm__sip_info_authentication;
	var_d      uint8                       _localflag [ENH_VEC_LENF];
	var_d      uint16                      _v90_rx_ph34_state;
	var_d      sint15                      _lec__data_size;
	var_d      uint16                      _orig_v8_CM_sent;
	var_d      sint15 CIRCULAR             _v90_tx_t_frame [6]; /* T0 - T5 */
	var_d      sint15                      _lec__enr_inve;
	var_d      ufract                      _lec__enr_invg;
	var_d      fract                       _tmp_baud_UVW_imag [3];
	const_d    fract                       _CORRELATOR_FIT_THRESHOLD;
	debug_d    uint16                      _sync_ack_state;
	var_d      char                        _parm__ipbx_dialed_number [IPBX_DIAL_STRING_SIZEOF];
	var_d      sint15                      _asm_extra_frame_just_sent;
	var_d      sint15                      _tonemute_decimate;
	var_d      v34f_cc_energy_data_t       _cc_rx_PP;
	var_d      int                         _ig_mem [(MBEST_GAIN*N9)+1];
	var_d      fract CIRCULAR              _equalizer_buffer_real [2 * C7K2_RX_EQUALIZER_SIZE];
	debug_d    uint16                      _sart_rx_hybrid_packed_mode;
	var_d      sint15                      _v90h_tx_state;
	fast_d     sint15                      _encode_frame_size;
	var_d      fract40                     _pcm_equalizer_ff_sum40;
	var_d      uint16                      _pcm_bulk_delay_buffer [PCM_BULK_DELAY_BUFFER_SIZEOF];
	var_d      uint16                      _v34_frame_rx_bit_offset;
	var_d      fract*                      _g711a_plc_pointer_in;
	var_d      fract                       _lec__rx_cng_frame_buffer [CNG_FRAME_BUFFER_SIZE];
	var_d      sint31                      _tick_irq;
	var_d      uint16                      _sonitrol_audio_Lpt_response_recvd;
	var_d      fract                       _v34_BE_modify_Gn_gain;
	var_d      uint16                      _control_value;
	debug_d    uint16                      _saved_scrambler_output;
	var_d      sint15                      _l_firsttime;
	var_d      fract                       _v90_shape_2_min;
	var_d      uint16                      _ipod_iface_rx_size;
	var_d      fract32                     _edge_m1200_imag32;
	parm_d     uint16                      _parm__ipbx_fc_call_waiting_caller_id_disable;
	var_d      int                         _sms_index;
	var_d      fract                       _v34_temp_lo_pre_emph_adjust_table [11];
	var_d      uint16                      _v92n_rxtx_apcm_data_rate_max;
	debug_d    uint16                      _mark_idle_tx_active;
	var_d      uint16                      _keep_alive_flag;
	parm_d     uint16                      _parm__codec_ring_detect_period_maximum;
	var_d      sint15                      _ph2n_probing_frequency_buffer [PH2P_NO_TONES];
	debug_d    uint16                      _ORIG_LEN_MS_RLSD_TURNON_DELAY;
	var_d      sint15                      _v92_rx_yn_tilde_poffset;
	var_d      uint16                      _report_tx_packet_flag;
	var_d      sint15                      _v90_rx_spectrum_offset_buffer [V90_RX_NO_BINS];
	var_d      uint16                      _v92_rx_sign;
	var_d      sint15                      _asm_vad_currently_off;
	var_d      uint16                      _DIL_probing_pad_type;
	var_d      sint15                      _v34_rx_xn_tilde_real;
	var_d      sint15                      _v90_shape_store_offset;
	parm_d     bool                        _parm__sip_info_hookflash;
	stat_d     uint16                      _stat__ipod_dth_vfd;
	local_d    uint16                      _v24_dsr;
	debug_d    uint16                      _V34S_LEN_8K0_PHROLL_PASS;
	var_d      fract                       _ph2p_anal_variance_04_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16*                     _v90n_rx_constel_codec_pointer; /* CPx value, DM *buffer */
	parm_d     char                        _parm__ata_finalize_domain_name [NET_DOMAIN_SIZEOF];
	var_d      uint16                      _stat__ipbx_state;
	var_d      uint16                      _v90n_rxtx_dpcm_data_rate_max;
	var_d      sint15                      _Gain_global [ENH_VEC_LENF];
	parm_d     uint32                      _parm__net_dhcp_server_starting_ip_address;
	parm_d     uint16                      _parm__ipbx_call_back_duration;
	var_d      sint15                      _l_prev_uv;
	var_d      bool                        _phone_lock_bypass;
	var_d      uint16*                     _v90_frame_tx_dil_body_ref [5];
	debug_d    energy_buffer_t             _monitor_sample_fast [6];
	var_d      sint15                      _lec__best_lin_poffset;
	var_d      uint16                      _scramb_msb;
	var_d      sint15                      _prev_fsmag_low_rate_chn_read [NUM_HARM] ;
	shared_d   struct proc *               _mgcp_timer_proc;
	var_d      fract                       _agc_2_feedback_slew;
	var_d      char                        _stat__sms_response [500];
	var_d      sint15                      _v92_system_ID_in_poffset;
	var_d      sint15                      _special_train_counter;
	var_d      TX_State                    _g722_2_tx_state;
	var_d      fract32                     _rf_rx_dc_qoffset;
	var_d      sint15                      _g600q_s [2*NF600];
	var_d      sint15                      _detect_count;
	var_d      uint16                      _v34_equalizer_btrec_enabled;
	debug_d    uint16                      _baud_rx_data_dlvd;
	var_d      uint16                      _last_interrupt_count;
	var_d      sint15                      _gpf_fine_match;
	parm_d     uint16                      _parm__ffsk_enc_gain;
	var_d      uint16                      _v90_rx_k_value;
	var_d      uint16                      _pcm_artificial_echo_flag;
	debug_d    uint16                      _ph2_tx_baud_shift_register;
	parm_d     char                        _parm__net_isp_password [STRSIZE_64];
	var_d      bool                        _fg_event_dsp_uses_background;
	var_d      uint16                      _tempword;
	var_d      uint16                      _parm__rtp_transfer_channels;
	var_d      sint31                      _ac97_major_number;
	var_d      uint16                      _dtmf_on_start;
	var_d      sint15                      _gain_pitch;
	parm_d     uint16                      _stat__phone_key_code;
	var_d      uint16                      _ipod_msg_rx_dom;
	var_d      sint15                      _v34_rx_predicted_V0_m_Jx2_counter;
	var_d      sint15                      _pspr_y1_hi;
	var_d      uint16                      _V34S_LEN_8K0_1RT_MIN_1ST_SHORT;
	var_d      fract                       _phasedet_rnd_complex_value [2];
	var_d      fract                       _edge_p1200_imag;
	var_d      uint32                      _v92n_rxtx_apcm_data_rate_option32;
	const_d    sint15                      _FAX_test_error_limit;
	parm_d     sint15                      _parm__codec_message_waiting_mode;
	var_d      sint15                      _constel_symmetric_table_nrm [SIZE_SYM_NRM];
	fast_d     sint15                      _tx_rate_double_poffset;
	const_d    fract                       _ANSAM_UPPER_THRESHOLD;
	var_d      sint15                      _v90_tx_dil_tp_cnt;
	local_d    uint16                      _saved_bit_pattern [12];
	var_d      uint16                      _short_train_resynchronization_active;
	parm_d     uint16                      _stat__phone_key_matrix;
	var_d      fract                       _eqout_lagging_delay_imag;
	parm_d     uint16                      _parm__mgcp_public_external_rtp_port_min;
	debug_d    uint16                      _line_rx_buffer_element;
	var_d      uint16                      _sart_rx_read_index;
	fast_d     sint15                      _asm_encode_packed_length;
	shared_d   uint32                      _mgcp_next_transaction_id;
	parm_d     bool                        _parm__ipbx_fxo_autoanswer_enable;
	var_d      uint16                      _ph2_INFOMARKS_one_count;
	parm_d     uint16                      _parm__mf_tone_off_time;
	local_d    tone_generator_buffer_t     _priority_generator_buffer [TONE_GENERATOR_COUNT];
	debug_d    sint15                      _V34_RESYNC_MEASURE_LENGTH;
	var_d      fract                       _rxs_out_vxxmod_remote [THREAD_BUFFER_SIZE];
	var_d      uint16                      _v34n_parm_precoder_option;
	parm_d     char                        _parm__sdp_g711u_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	fast_d     fract                       _remote_ec_sum;
	var_d      uint16                      _dgi_pad_loss;
	var_d      sint15                      _p18_demodulator_phase;
	var_d      fract*                      _gpf_lpointer;
	var_d      fract                       _sdt_delta_energy_threshold;
	shared_d   uint16                      _mpi_debounce [NUMBER_OF_LINES_PER_DSP];
	var_d      fract                       _dtmf_last_row_level;
	var_d      uint16                      _v90n_rx_reference_point;
	var_d      uint16                      _PH2S_LEN_T_DATA_TIMEOUT;
	var_d      fract                       _THD_measurement_variance;
	var_d      uint16                      _v34n_parm_asymmetric_option;
	var_d      uint16                      _v34h_tx_residue_hi;
	var_d      event_t                     _V90_RX_R_DETECT_EVENT; /* default */
	var_d      uint16                      _pcm_rx_8K0_divisor_flag;
	var_d      uint16                      _rf_transmit_enabled;
	parm_d     uint32                      _stat__nat_wan_translated; /* WAN to LAN receive translated packet counter */
	var_d      sint15                      _g729_prm [80];
	var_d      sint15                      _g_bitNum12;
	parm_d     uint16                      _parm__ipbx_fc_one_digit_speed_dial_program;
	var_d      uint16                      _v90n_rx_saved_parameters [4+6+8*6];
	parm_d     uint16                      _parm__codec_parallel_in_use_debounce;
	var_d      sint15                      _lspSid_q [M_LP];
	var_d      uint16                      _pcm_slot_counter;
	var_d      fract                       _THD_measurement_relative;
	var_d      sint15                      _lec__data_poffset;
	parm_d     uint16                      _parm__pump_diag_count_msw;
	var_d      sint15                      _lec__datamax_full_counter;
	var_d      sint15                      _PH2P_POWR_LX_PROCESS_LENGTH;
	parm_d     uint16                      _parm__dm_v34_ptt_carrier_mask;
	var_d      uint16*                     _v92n_rx_CP_body_cm [ 2];
	var_d      sint15                      _v34h_rx_I1ij_m;
	var_d      fract                       _jitter_jitter_real;
	var_d      fract                       _cc_rx_ANAL_AGC2_log;
	local_d    uint16                      _pick_max_stat;
	var_d      fract                       _equalizer_leading_real [2*((xV34_XX_EQUALIZER_SIZE)/2)];
	debug_d    uint16                      _ANSW_LEN_MS_CJ_TIMEOUT;
	var_d      state_list_t                _fg_state_list [NUMBER_OF_FG_STATES];
	var_d      bool                        _ata_need_code;
	var_d      fract                       _sense_silence_threshold;
	debug_d    bool                        _baud_tx_parity_used;
	debug_d    uint16                      _cp_status_bit;
	var_d      phase_t                     _v34_resync_phase_correction;
	parm_d     uint32                      _stat__nat_snd_frag_created; /* LAN to WAN send fragment forwarding created counter */
	parm_d     sint15                      _parm__codec_disconnect_reversals_answer;
	var_d      sint15                      _g_bitNum24;
	var_d      sint15                      _l_top_lpc [LPC_ORD];
	var_d      uint32                      _ata_random_delay_code;
	fast_d     uint16                      _rx_lpf_poffset;
	local_d    uint16                      _v34n_tx_primary_channel_maxrate;
	var_d      sint15                      _lookback_update_base;
	var_d      fract                       _lec__probe_tx_input;
	var_d      uint16                      _silence_passband_poffset;
	const_d    phase_t                     _ANSam_trace_offset;
	var_d      sint15                      _v34_rx_yn_hat_imag;
	local_d    char                        _parm__ipbx_disturb_accept_list [IPBX_LIST__DISTURB_ACCEPT_NO_OF][IPBX_DIAL_STRING_SIZEOF];
	debug_d    sint15                      _ec_medium_shift_slew_local;
	debug_d    uint16                      _baud_tx_bit_cnt;
	parm_d     uint16                      _parm__sip_public_external_sip_port;
	var_d      fract                       _v34_MSE_N_value;
	parm_d     sint15                      _parm__slac_ring_transition;
	var_d      uint16                      _v92n_tx_constel_size [6];
	var_d      fract CIRCULAR              _cc_rx_lpf_buffer_real [CC_RX_LPF_SIZE*2];
	var_d      sint15                      _agc_2_exponent;
	var_d      ufract                      _lec__slew;
	parm_d     uint16                      _parm__nat_timeout_tcp_open; /* Idle seconds before open TCP NAT timeout */
	var_d      fract                       _g168_err_floor;
	var_d      uint16                      _gled_pattern_index;
	var_d      fract                       _b202_ans_tx_passband_coefs_buffer_internal [C7K2_FSK_TX_BPF_SIZE];
	var_d      phase_t                     _v34_temp_lo_carrier;
	var_d      fract                       _V90_RX_ALL_ENERGY_THRESHOLD;
	shared_d   uint16                      _clock_rx;
	var_d      fract32                     _lec__dc_offset_sum32;
	var_d      uint16                      _ph4n_rx_trained_maxrate;
	fast_d     uint16                      _parm__dpbx_led_or_mask;
	parm_d     uint16                      _parm__codec_disconnect_silence_duration;
	var_d      bool                        _v34s_special_local_decor_option;
	var_d      sint15                      _v34h_rx_V0_m;
	var_d      fract                       _v34_BE_jam_baud_agc;
	const_d    uint16                      _fax_v21_CED_pause;
	var_d      sint15                      _uicp_size_of;
	var_d      uint16                      _v90_rx_s_frame [6*2];
	var_d      uint16                      _v27_tx_guard_count;
	parm_d     uint16                      _parm__codec_initialization_commands [IPBX_SLAC_COMMAND_SIZEOF];
	var_d      uint16                      _parm__data_storage_level_crossed;
	var_d      sint15                      _pcm_rx_slot_counter_xtr;
	parm_d     char                        _parm__ata_logo_url [ATA_URL_SIZEOF];
	var_d      sint15                      _pspr_y1_lo;
	var_d      fract                       _cc_rx_PP_last_energy_log [9];
	var_d      fract                       _det_energy32 [2];
	var_d      fract                       _g168_err_peak;
	var_d      uint16                      _sonitrol_good_message_count;
	var_d      int                         _pcm_test_disable_outer_rx_rate_double;
	var_d      bool                        _v92_MH_RT_found_flag;
	debug_d    bool                        _v34s_reneg_test_resp_variable_S_length;
	var_d      fract                       _lec__nlp_cng_offset_buffer [LEC__CNG_OFFSET_DATA_SIZE];
	parm_d     char                        _parm__mgcp_hostname [STRSIZE_32];
	var_d      fract                       _sdt_correlator_fit_threshold;
	var_d      uint16                      _shadow_line_enabled;
	persist_d  uint16                      _v34n_rx_attenuation_option;
	var_d      bool                        _current_bg_task_active;
	var_d      uint16                      _v90h_rx_control_frame [6];
	parm_d     char                        _parm__net_isp_user_name [STRSIZE_64];
	var_d      sint15                      _l_firstTime_melp_ana;
	var_d      sint15                      _vad_prev_energy;
	var_d      uint16                      _stat__picp_parse_state;
	var_d      sint15                      _PCM_PEAK_MSE_STACK_COUNT;
	var_d      sint15                      _PH2P_POWR_L1_FINAL_TUNE;
	const_d    uint16                      _ch_seize_data_unit;
	var_d      sint15                      _tone_pattern_gen_index;
	var_d      sint15                      _cc_rx_rate_reduction_ratio;
	var_d      sint15                      _l_prev_lpc_gain;
	debug_d    uint16                      _initial_training;
	var_d      uint16                      _v90n_tx_receive_redundancy; /* 0 - 3 = number of redundant bits */
	var_d      fract40                     _det_energy40;
	var_d      fract32                     _v34_BE_neg_power_32;
	var_d      uint32                      _ata_sample_record_index;
	var_d      int                         _rxs_aux_rx_data [THREAD_BUFFER_SIZE];
	var_d      bool                        _fsk_run_flag_correlator;
	fast_d     bool                        _baud_rx_16_bit_mode;
	var_d      ipbx_call_t *               _ipbx_call_current;
	parm_d     bool                        _parm__net_isp_heartbeat_signal_enable;
	parm_d     uint16                      _parm__voip_ilbc_high_rate_enable;
	var_d      sint15                      _rev_count;
	var_d      sint15                      _rate_reduction_ratio;
	var_d      g723_vadstatdef_t           _g723_VadStat;
	var_d      uint16                      _v34h_tx_residue_lo;
	var_d      uint16                      _ph2n_sm_INFO0h_end_delay;
	var_d      const fract*                _tx_bpf_coef_pointer;
	stat_d     sint15                      _stat__speech_dec_bad_frame_mtr;
	local_d    bool                        _parm__ipbx_call_forward_service;
	const_d    uint16                      _fax_v21_energy_length;
	parm_d     sint15                      _parm__lec_length;
	var_d      ufract                      _v34n_rx_transmit_gain;
	var_d      sint15                      _ANSam_trace_count_2100_value;
	debug_d    fract                       _cp_hysteresis;
	var_d      fract40                     _v92_rx_decoder_ff_input_energy40;
	var_d      uint16                      _test_1_msw;
	parm_d     uint32                      _stat__nat_rcv_alg_discards; /* LAN to WAN receive ALG discard packet exit counter */
	parm_d     char                        _parm__sip_user_agent [STRSIZE_96];
	var_d      mse_struct                  _v34_MSE_S_stack;
	var_d      sint15                      _g711a_plc_frame_counter;
	persist_d  fract                       _ph2n_probing_L2_log_N_buffer [PH2P_NO_TONES];
	const_d    uint16                      _V92N_RX_PREFILTER_GAIN_x4;
	var_d      uint16                      _ph2n_rx_preemph [V34N_MAX_SYMBOL+1];
	parm_d     char                        _stat__sip_local_contact_domain_name [NET_DOMAIN_SIZEOF];
	var_d      sint15                      _g711_rx_vad_peak_kf;
	shared_d   uint16                      _mpi_debounce_disconnect [NUMBER_OF_LINES_PER_DSP];
	var_d      fract                       _p18_delta_energy_threshold;
	var_d      uint16                      _okay_to_turn_off;
	var_d      uint16                      _lec__nlp_cng_enable;
	local_d    bool                        _parm__ipbx_block_anonymous_enable;
	parm_d     struct led_descriptor       _parm__ipbx_led_pstn_in_use;
	var_d      sint15 CIRCULAR             _v34_tx_qn_buffer_imag [2*V34_NO_QN_COEFS];
	fast_d     int                         _baud_tx_cntr;
	var_d      sint15                      _g711_rx_vad_peak_kr;
	var_d      sint15                      _g723_WrkRate;
	var_d      sint15                      _prev_qpitch_pitch_vq;
	var_d      uint16                      _descrambled_mark_count;
	parm_d     nat_port_trigger_t          _parm__nat_port_trigger [NAT_PORT_TRIGGER_ENTRIES];
	debug_d    uint16                      _hdlc_lead_flag_cnt;
	var_d      sint15*                     _v34h_tx_control_pointer;
	var_d      uint16                      _s1_flags;
	var_d      uint16                      _v90_frame_rx_sync_register [3];
	var_d      uint16                      _v90_tx_eye_modulus [6];
	var_d      fract                       _new_scores [8];
	var_d      fract                       _v34_ph2_common_name_values [V34_PH2_COMMON_NAME_SIZE];
	var_d      sint15                      _l_lpc_del [LPC_ORD];
	parm_d     struct led_descriptor       _parm__dpbx_led_use_and_waiting;
	var_d      uint16                      _best_rmt;
	var_d      sint15                      _v34_tx_pn_imag;
	var_d      sint15                      _v92_rx_i_DF_count;
	var_d      bool                        _v92_tx_send_CPd_flag;
	var_d      uint16*                     _v90_tx_dil_ucode_ptr;
	const_d    sint15                      _V92_DECODER_EP_SHIFT;
	var_d      sint15                      _v90_shape_3_offset;
	var_d      fract                       _ptloop_angle_change_limit;
	fast_d     bool                        _stat__vppn_off_hook;
	var_d      uint16                      _pcm_disc_slot_match_list [6];
	var_d      sint15                      _tst_rx_8K0_transfer_overflow;
	shared_d   uint16                      _parm__vppn_channel_active_count;
	var_d      uint16                      _pcm_ctl_ep_nlms_override; /* T */
	debug_d    sint15                      _V34S_LEN_8K0_1RT_MAX_1ST_TRAIN;
	var_d      sint15                      _v90n_rx_shaping_a1; /* Shaping parameter a1 in signed 2.6 or 10.6 */
	parm_d     sint15                      _parm__codec_disconnect_tone_3_bandwidth;
	parm_d     uint16                      _parm__voip_fax_processing_rate; /* Rate for T.38 */
	var_d      sint15                      _v90n_rx_shaping_a2; /* Shaping parameter a2 in signed 2.6 or 10.6 */
	var_d      fract                       _PCM_TRN2_DATA_MAXRATE_TABLE [V90_NO_DATA_RATES];
	var_d      fract32                     _detect_energy_lpf2_32;
	var_d      fract                       _g722_e4h_ah1;
	var_d      sint15                      _v34_rx_pn_hat_imag;
	var_d      fract                       _g722_e4h_ah2;
	var_d      uint16                      _parm__rtp_dtmf_playout_duration;
	parm_d     uint16                      _parm__sdp_gsm_efr_codec_dyn_pt;
	var_d      fract40                     _ph2_ac_output40;
	parm_d     uint16                      _parm__codec_impedance_commands [IPBX_SLAC_PORT_IMPEDANCES][IPBX_SLAC_COMMAND_SIZEOF];
	var_d      char                        _ipbx_digit_detected;
	var_d      sint15                      _ph2_tx_passband_offset;
	var_d      bool                        _v34_frame_rx_MP_found;
	fast_d     fract                       _equalized_real;
	const_d    uint16                      _pre_gear_change_period;
	parm_d     char                        _parm__sdp_t38_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      sint15                      _v90_tx_dil_lsp;
	var_d      sint15                      _v90n_rx_shaping_b1; /* Shaping parameter b1 in signed 2.6 or 10.6 */
	var_d      fract   CIRCULAR            _pcm_equalizer_fb_buffer [2*PCM_FB_EQUALIZER_SIZE_MAX];
	var_d      sint15                      _v90n_rx_shaping_b2; /* Shaping parameter b2 in signed 2.6 or 10.6 */
	var_d      fract*                      _v34_tx_decor_pointer;
	var_d      sint15*                     _enc_exc;
	var_d      fract                       _cc_rx_ANAL_DC_angle;
	var_d      uint16 **                   _v34_frame_rx_save_bit_parse_pointer;
	debug_d    uint16                      _V34S_LEN_8K0_2ND_PHASE_CHANGE;
	var_d      uint16                      _current_codeword;
	var_d      fract                       _DIL_calculation_pad_gain_log;
	var_d      fract                       _pcm_8K0_error;
	var_d      fract                       _THD_sum_L2_S_norm;
	var_d      fract                       _dtmf_peak_col_level;
	debug_d    bool                        _V90_TEST_PARM_LIMIT_SYMBOL;
	var_d      fract                       _rxs_demod_imag [THREAD_BUFFER_SIZE];
	fast_d     vppn_packet_t *             _vppn_encode_packet_list;
	var_d      sint15                      _circb_min_shift [ENH_VEC_LENF];
	var_d      uint16                      _V90_TRAIN_EC_WITH_RBS;
	local_d    char                        _parm__voip_default_display_name [STRSIZE_64];
	var_d      sint15                      _loopback_buffer_length;
	parm_d     uint16                      _parm__lec_mode;
	parm_d     uint16                      _parm__voip_g722p2_encode_rate;
	fast_d     uint16 *                    _mbx;
	var_d      sint15                      _v90_tx_sample_counter;
	const_d    fract                       _equalizer_slew_special;
	var_d      fract32                     _ptloop_phdet_error_fast32;
	parm_d     struct led_descriptor       _parm__dpbx_led_do_not_disturb;
	var_d      sint15                      _gpf_RRadj;
	var_d      bool                        _fsk_TONE_started;
	var_d      uint16                      _ph4n_tx_receive_shaping;
	const_d    fract                       _threshold_fsk;
	var_d      sint15                      _v90_tx_dil_ltp;
	var_d      uint16                      _v34n_sm_INFO0h_end_delay;
	var_d      sint15                      _ptloop_phdet_state;
	var_d      sint15                      _v90_successive_reneg_count;
	fast_d     sint15                      _decode_byte_counter;
	parm_d     char                        _parm__sdp_NSE_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      sint15                      _ph2p_powr_dmod_rx_offset32;
	var_d      fract                       _v92_system_ID_max_spacing;
	parm_d     sint15                      _parm__slac_port_impedance;
	parm_d     uint16                      _parm__ipbx_answer_hangup_delay;
	var_d      ufract                      _v34_local_echo_value;
	debug_d    uint16                      _V34S_INIT_8K0_2RT_S_SN_to_Edet;
	parm_d     sint15                      _chwordsize;
	var_d      uint16                      _pcm_bulk_delay_input_flag;
	var_d      cngdata_t                   _lec__cng_data;
	var_d      uint16                      _ata_led_use_mask_update;
	stat_d     sint15                      _stat__speech_dec_default_sample_cnt;
	var_d      uint16                      _parm__slac_ring_generator [16];
	var_d      sint15                      _pcm_ec_type;
	var_d      iLBC_Dec_Inst_t             _Dec_Inst;
	var_d      bool                        _comn_v8_TONEq_send;
	fast_d     uint16                      _vppn_device_command_queue_out;
	parm_d     sint31                      _parm__sip_incoming_reregister_interval;
	parm_d     uint32                      _parm__net_dhcp_server_wins_address;
	parm_d     uint16                      _parm__ipbx_fc_no_answer_forward_enable;
	var_d      uint16 *                    _nat_pkt_udp_ptr; /* Pointer to UDP header */
	var_d      g168_noise_floor_t          _g168_nf_data;
	parm_d     uint32                      _stat__nat_snd_ipsec; /* LAN to WAN send IPsec packet type counter */
	parm_d     uint32                      _stat__nat_snd_create; /* LAN to WAN send translation created counter */
	parm_d     uint32                      _stat__nat_wan_frag_forward; /* WAN to LAN receive fragment forwarding success packet exit counter */
	var_d      sint15                      _g711a_plc_pitch;
	const_d    sint15                      _ANSAM_2100_MAX;
	var_d      sint15                      _lec__average_activity_counter;
	shared_d   uint32                      _parm__dest_rtp_address;
	var_d      sint15                      _special_data_counter;
	var_d      bool                        _v92n_tx_v92_override;
	parm_d     uint16                      _parm__ata_web_server_language;
	var_d      uint16                      _v90_dpcm_dil_length;
	fast_d     sint15                      _parm_dec [MAX_CODER_PARM_SIZE];
	var_d      sint15                      _l_lpfsp_delin [LPF_ORD];
	var_d      sint15                      _l_mem1 [LPC_ORD];
	var_d      sint15                      _l_mem2 [LPC_ORD];
	var_d      fract                       _ph2p_anal_log_N_buffer [PH2P_NO_TONES];
	var_d      fract                       _v34_equalized_imag;
	stat_d     uint16                      _stat__dtmf_detect;
	var_d      sint15                      _lec__datamax_full_size;
	fast_d     bool                        _baud_rx_flag;
	var_d      uint16*                     _v34n_rx_INFO1a_body [9];
	parm_d     sint15                      _parm__codec_caller_id_type_1_mode;
	parm_d     uint16                      _stat__sip_local_contact_port;
	var_d      uint16                      _chan_start_flag;
	parm_d     uint32                      _stat__nat_snd_pppoe; /* LAN to WAN send PPPoE packet exit counter */
	var_d      nat_tab_t *                 _nat_private_table [NAT_HASHMOD]; /* Hashed list head - using private IP port */
	var_d      fract40                     _dgidet_ec_energy40;
	var_d      sint15                      _DIL_probing_slot_counter_xtr;
	var_d      sint15                      _fsk_rx_clock_phase;
	parm_d     bool                        _local__voip_silence_supression_enable; /* Some codecs have silence supression built in and separately controlled */
	var_d      sint15                      _v34_rx_yn_imag;
	var_d      uint16                      _sonitrol_remote_control_port;
	parm_d     uint32                      _parm__net_dhcp_server_short_lease_time;
	parm_d     uint16                      _parm__rtp_session_timeout_interval; /* Session timeout in seconds */
	debug_d    uint16                      _sync_prev_data;
	var_d      uint16                      _parm__data_storage_level;
	parm_d     uint32                      _stat__nat_rcv_ip_forward; /* LAN to WAN receive IP forwarding success packet exit counter */
	shared_d   uint16                      _gci_indication [NUMBER_OF_LINES_PER_DSP];
	var_d      int                         _s1_detector_num_tones;
	var_d      uint16                      _selected_rate;
	var_d      sint15                      _rx_interpolator_pointer_adjust;
	persist_d  uint16                      _ph2n_rx_receive_CME;
	var_d      sint15                      _prev_prev_phase_roll_second;
	parm_d     uint32                      _parm__net_dhcp_server_gateway_address;
	var_d      sint15                      _v34_rx_qn_perfect_poffset;
	var_d      uint16                      _v34n_tx_preemph_value;
	parm_d     bool                        _parm__ipbx_bridge_autoanswer_anonymous_enable;
	var_d      fract                       _ANSam_trace_magphase_min_imag;
	var_d      fract                       _ph2p_anal_variance_10_table [PH2P_NO_PREEMPHASIS];
	var_d      sint15                      _v90_frame_rx_save_bit_count;
	local_d    char                        _parm__ipbx_input_pattern_voip [IPBX_INPUT_PATTERN_SIZEOF];
	var_d      fract                       _tx_rate_double_buffer [2*TX_RATE_DOUBLE_SIZE];
	fast_d     sint15                      _faxdet_ced_cnt;
	shared_d   struct proc *               _wiznet_interrupt_process;
	var_d      sint15                      _PCM_TRN2_MSE_REPORT_RATE;
	shared_d   uint16                      _dev_rx_frame [NUMBER_OF_LINES_PER_DSP*IPBX_DEV_MESSAGE_MAX_LENGTH];
	var_d      sint15                      _PH2P_FEFO_GAIN_MARGIN;
	local_d    tone_generator_buffer_t     _tone_generator_buffer [TONE_GENERATOR_COUNT];
	var_d      fract                       _cc_rx_PP_BEp_save_energy_log;
	var_d      sint15                      _l_memt;
	parm_d     bool                        _parm__radio_receiver_monitor_enable;
	var_d      uint16                      _lec__td_hold_1st_flag;
	var_d      fract                       _ANSam_trace_max_imag;
	var_d      uint32                      _stat__symlist_checksum;
	var_d      uint16                      _monitor_input_raw_status;
	var_d      fract32                     _echo_canceller_error_sum;
	var_d      char                        _ipbx_announce_ip_address [IPBX_ANNOUNCE__IP_ADDR];
	parm_d     struct tone_descriptor      _parm__ipbx_call_conference_tone;
	var_d      uint16                      _rd_laston_cnt;
	parm_d     char                        _parm__net_lan_user_name [ATA_ACCOUNT_SIZEOF];
	fast_d     uint16                      _v34_rx_trellis_old_scores [16];
	var_d      uint32                      _asm_encode_rtp_start;
	const_d    fract                       _equalizer_slew_slow;
	local_d    char                        _parm__ipbx_distinctive_ring_list [IPBX_LIST__DISTINCTIVE_RING_NO_OF][IPBX_DIAL_STRING_SIZEOF];
	var_d      sint15                      _ph2n_probing_Gr_exponent;
	var_d      sint15                      _v92n_rx_prefilter_exponent;
	var_d      uint16                      _v90n_tx_receive_silence_option; /* 0 = normal, 1 = silence */
	var_d      sint15                      _g726_dec_bit_number;
	var_d      uint16                      _PCM_LEN_8K0_EQC_TRN1A_4TH;
	var_d      bool                        _within_bg_state_update;
	var_d      sint15                      _v90_rx_rate_reduction_counter;
	var_d      uint16                      _v34_frame_rx_residue;
	debug_d    uint16                      _V34S_RENEG_INIT_T_S_TO_SN_TIMEOUT;
	var_d      sint15                      _l_twid_idx;
	var_d      uint16                      _going_down;
	var_d      sint15                      _fsk_previous_exp;
	var_d      sint15                      _lec__holding_poffset;
	debug_d    uint16                      _v17_diagnostics_mse_sum [3];
	shared_d   int                         _impedance_monitor_rx_speech_detected;
	local_d    char                        _parm__ipbx_no_answer_forward_dial_string [IPBX_DIAL_STRING_SIZEOF];
	parm_d     bool                        _parm__ata_lcd_menu_protect_enable;
	shared_d   int                         _impedance_monitor_rx_in_offset;
	fast_d     fract                       _noise_generator_bpf_data [4];
	var_d      sint15                      _v34_tx_yn_remote_imag;
	var_d      uint16                      _v90n_tx_training_data_rate; /* 0 = cleardown, 1-22 data rates */
	shared_d   uint16                      _parm__dest_rtp_port;
	parm_d     char                        _parm__net_hardware_mac_address [ATA_MAC_ADDRESS_SIZEOF];
	var_d      fract                       _p18_baud_UVW_real [3];
	var_d      struct melp_param           _prev_par_syn;
	parm_d     uint16                      _parm__radio_receiver_squelch_level;
	var_d      sint15                      _retrain_count;
	var_d      uint16                      _shadow_ring_count;
	const_d    fract                       _DELTA_REF_LEVEL;
	var_d      uint16                      _ipod_msg_rx_payload_size;
	debug_d    cp_t                        _dt_table [DT_TABLE_ENTRY_NUM];
	shared_d   bool                        _vppn_device_update_in_progress;
	parm_d     uint16                      _parm__pcm_playback_intro_mode;
	parm_d     uint16                      _parm__mgcp_local_port;
	parm_d     uint16                      _parm__fxpmp_preamble_duration;
	var_d      fract                       _ANSam_trace_magphase_real;
	stat_d     uint16                      _stat__v8__call_function;
	var_d      sint15                      _V34_TXI_TAPS;
	var_d      fract32                     _notch_datay32_060;
	var_d      uint16                      _found_CNG_tone;
	parm_d     bool                        _parm__ffsk_dec_enable;
	var_d      fract                       _cc_rx_ANAL_ALL_energy_log;
	parm_d     ufract                      _parm__tone_transmit_level;
	var_d      fract32                     _faxdet_data_sum_grl;
	var_d      sint15                      _g729_coder_buffer [L_FRAME];
	parm_d     uint16                      _parm__ipbx_fc_caller_redial_cancel;
	debug_d    bool                        _v34s_retrigger_renegotiation;
	shared_d   uint16                      _debug_host_buffer_throttle;
	var_d      fract                       _v32bis_nearest_group_table_internal_buffer [64];
	var_d      sint15                      _output_lock_buffer [(2*OUTPUT_LOCK_SIZE)];
	var_d      fract                       _v32_nearest_group_table_internal_buffer [64];
	var_d      uint16                      _v90n_tx_apcm_data_rate_option; /* used in V92 */
	parm_d     sint15                      _parm__ipbx_tone_gain;
	var_d      uint16                      _descrambler_output;
	parm_d     char                        _parm__sdp_g722p2_codec_name [RTPMAP_CODEC_NAME_LENGTH];
	var_d      thread_routine_t            _pcm_rx_statistics_routine;
	var_d      sint15                      _PCM_EC_OUTPUT_POST_SHIFT;
	var_d      fract32                     _phase_roll__second_order_term_32;
	var_d      sint15                      _ph2p_powr_saved_holdoff_I7_offset;
	local_d    fract                       _sdt_angle_store_imag [3];
	parm_d     bool                        _parm__sip_register_authentication;
	var_d      uint16*                     _v90_frame_rx_cp_body_cm [2];
	var_d      fract                       _faxdet_data_ced [6];
	var_d      uint16                      _v34h_rx_SWP_value;
	var_d      uint16                      _v34_tx_remote_use_nonlinear;
	var_d      uint16                      _special_match_nsw;
	var_d      uint16                      _sonitrol_v34_spp_len_counter;
	var_d      uint16                      _orig_v8_found_ANSam;
	parm_d     uint16                      _parm__transmitter_gain;
	fast_d     fract                       _precision_cos_value;
	var_d      uint16                      _pcm_code_segment;
	var_d      uint16                      _htd_dtmf_semaphore;
	fast_d     uint16                      _vppn_device_command_send_retry;
	var_d      sint15                      _v90_tx_k_value;
	parm_d     uint32                      _stat__net_current_dns_secondary_address;
	var_d      struct led_descriptor       _parm__ipbx_led_descriptor;
	parm_d     char                        _parm__ipbx_bridge_security_code_string [ATA_PASSWORD_SIZEOF];
	var_d      uint16                      _legacy_binary_download_mode;
	var_d      uint16                      _sonitrol_audio_edge_detect;
	var_d      sint31                      _PCM_BTR_FREQ32;
	debug_d    uint16                      _V34S_LEN_8K0_PRE_PHASE_CHANGE;
	var_d      uint16                      _v34n_parm_cc_data_rate_option;
	parm_d     bool                        _parm__sip_send_response_to_src_port;
	parm_d     uint16                      _parm__ipbx_fc_call_waiting_enable_once;
	var_d      fract                       _btrec_p2400_imag;
	var_d      sint15                      _v34f_srce_1st_MPh_flag;
	shared_d   uint16                      _ipbx_rled_mask [NUMBER_OF_LINES_PER_DSP];
	var_d      sint15                      _dtmf_clamp_delay;
	var_d      sint15                      _g711a_plc_history_poffset;
	parm_d     uint16                      _parm__voip_dtmf_transmit_method; /* Choice of disabled, audio, RTP out-of-band or SIP out-of-band */
	var_d      sint15                      _v34h_tx_I1ij_m;
	var_d      uint16                      _v90_dpcm_dil_ucode [MAX_DIL_UCODE];
	var_d      uint16                      _rx_packet_count;
	const_d    fract                       _equalizer_slew_medium;
	var_d      event_t                     _bgkernel_current_event;
	var_d      sint15                      _lec__datamax_full_excess;
	fast_d     sint15                      _asm_pkt_type;
	var_d      uint16                      _sonitrol_ring_count;
	var_d      sint15                      _v90_rx_retrain_detect_counter;
	var_d      uint16                      _rf_sample_overflow_count;
	shared_d   struct proc *               _wiznet_poll_process;
	shared_d   uint16                      _parm__net_debug_level_mgcp;
	fast_d     sint15                      _encode_frame [MAX_CODER_FRAME_SIZE];
	parm_d     uint16                      _parm__ipbx_hookflash_minimum;
	parm_d     sint15                      _parm__handset_rx_gain;
	parm_d     char                        _parm__sip_remote_domain_name [NET_DOMAIN_SIZEOF];
	parm_d     uint32                      _stat__nat_wan_delivers; /* WAN to LAN receive packet deliver exit counter (into upper IP layers) */
	var_d      sint15	*                    _cbk_gain_s [2];
	var_d      fract                       _v34_pp_correlate_offset;
	debug_d    uint16                      _ANSW_LEN_MS_ANSam_CI_SEARCH;
	var_d      sint15                      _parm__speech_dec_host_flag;
	var_d      uint16                      _sonitrol_DNIS;
	debug_d    uint16                      _V34S_FINAL_MPA_SEND_COUNT;
	var_d      sint15                      _v90_tx_k_input_offset;
	var_d      fract                       _affine_ptloop_real;
	const_d    uint16                      _V92S_LEN_8K0_CPT_HOLDOFF;
	const_d    fract                       _monitor_be2_threshold;
	debug_d    sint15                      _V34_AB_SIGNAL_C8K0_LIMIT;
	var_d      const sint15*               _ph1_tx_ANSpcm_double_pointer;
	parm_d     uint16                      _parm__cid_data_buffer [CID_DATA_BUFFER_SIZEOF];
	var_d      ufract                      _ph1_tx_ANSpcm_gain;
	fast_d     uint16                      _conv_bpf_clip;
	shared_d   fract                       _impedance_monitor_decimated_rx [IMPEDANCE_MONITOR_INTERNAL_SIZE];
	parm_d     uint16                      _parm__sip_response_code_try_backup;
	var_d      unsigned int                _g726_out_buffer;
	var_d      sint15                      _g711a_plc_pitchblen;
	var_d      uint16                      _coder_rate;
	const_d    sint15                      _maximum_first_trn_length;
	var_d      fract                       _dtmf_lpf_biquad_data [4];
	parm_d     uint16                      _parm__disconnect_tone_cadence_mask [DT_TABLE_ENTRY_NUM];
	var_d      int                         _echo_canceller_display_lt_counter;
	var_d      sint15                      _v92_rx_decoder_ff_alpha_exp;
	debug_d    uint16                      _V90_TEST_LOG_INPUT_START;
	var_d      bool                        _picp_service;
	shared_d   uint16                      _parm__net_debug_level_pmp;
	const_d    uint16                      _sart_tx_size;
	var_d      sint15                      _pcm_rx_clock_phase;
	var_d      sint15                      _lec__datamax_full_holdoff;
	var_d      uint16                      _lec__xx_detect_activity;
	fast_d     uint16                      _vppn_device_command_queue_overflow;
	debug_d    uint16                      _ORIG_LEN_MS_SILENCE_DETECT;
	debug_d    ufract                      _v29_gain_adjust;
	var_d      int                         _record_sample_tx_pcm;
	var_d      fract32                     _ph2p_powr_N_buffer32 [PH2P_NO_TONES];
	var_d      uint16                      _v90n_tx_coding_law; /* JO unused, #define DO_V90_DPCM? */
	var_d      uint16                      _v34n_tx_carrier_frequency;
	debug_d    cpd_t                       _dt_data [DT_TABLE_ENTRY_NUM];
	var_d      sint15                      _cc_tx_passband_poffset;
	var_d      sint15                      _L_exc_err [4];
	shared_d   uint16                      _dprmbx_ack_channel;
	var_d      fract                       _v29_rot_equalized_imag;
	stat_d     uint16                      _stat__v8__vpcm_availability;
	var_d      int                         _sip_startup_complete;
	var_d      sint15                      _asm_encode_sample_pack_mask;
	var_d      fract                       _cc_rx_ANAL_DC_energy_log;
	var_d      ufract                      _v34n_rx_gain_adjust;
	var_d      fract                       _equalizer_output_imag;
	parm_d     bool                        _parm__ata_external_web_server_enable;
	parm_d     struct date_s               _parm__ata_current_date;
	parm_d     sint15                      _parm__slac_caller_id_type_1_mode;
	shared_d   int                         _impedance_monitor_detect_holdoff_counter;
	var_d      fract                       _g168_inp_average;
	var_d      uint16                      _differential_data;
	local_d    uint16                      _v34n_tx_use_nonlinear;
	var_d      sint15                      _uicp_index;
	var_d      uint64                      _v90_rx_q_table64 [6];
	fast_d     sint15                      _decode_frame_active_indication;
	debug_d    bool                        _orig_v8_allow_ANSam;
	fast_d     fract                       _perfect_real;
	var_d      sint15                      _parm__speech_rtp_jitter_buffer_lock;
	var_d      uint16                      _v90_rx_dil_tp_mask;
	var_d      uint16                      _v92n_tx_MH_indication;
	var_d      uint16                      _p18_lpf_poffset;
	parm_d     uint32                      _stat__nat_snd_alg_delivers; /* LAN to WAN send ALG delivers packet exit counter */
	local_d    bool                        _parm__ipbx_caller_id_inbound_enable;
	debug_d    sint15                      _cp_detected;
	var_d      sint15                      _retrain_counter;
	var_d      sint15                      _cod_vad_enable;
	shared_d   fract                       _impedance_monitor_decimated_tx [IMPEDANCE_MONITOR_INTERNAL_SIZE];
	parm_d     uint16                      _parm__sart_tx_mode;
	var_d      uint16                      _fsk_TONE_counter;
	var_d      fract                       _lec__best_erl_buffer [LEC__BEST_SIZE];
	parm_d     uint16                      _stat__mgcp_controller_local_contact_port;
	var_d      thread_routine_t            _pcm_rx_8K0_ph34_routine;
	parm_d     char                        _parm__ata_hardware_revision [ATA_REVISION_SIZEOF];
	var_d      sint15                      _postHPFInHis [2];
	var_d      fract                       _cc_rx_ANAL_coef_imag;
	var_d      struct timer                _nat_timer; /* Timer callback function */
	parm_d     nat_address_port_block_t    _parm__nat_address_port_block [NAT_ADDRESS_PORT_BLOCK_ENTRIES];
	parm_d     bool                        _parm__sip_options_authentication;
	var_d      sint15 CIRCULAR             _v90_tx_s_frame [2*V90_TX_S_FRAME_LEN]; /* $0-$5 for each shaping frame */
	var_d      sint15                      _angle_1st_data_input;
	var_d      fract                       _v32_rx_lpf_coefs_internal_buffer [C7K2_RX_LPF_SIZE];
	debug_d    uint16                      _overlay_ph2_to_v34;
	var_d      sint15                      _v34_resync_min_index;
	var_d      uint16                      _v92n_tx_train_8pt_option;
	fast_d     ufract                      _parm__hw_rx_gain_correction;
	var_d      uint16                      _v34f_srce_requests_restart;
	var_d      uint16                      _parm__overall_operating_mode;
	var_d      uint16                      _rx_call_to_answer_new_maxrate;
	parm_d     uint16                      _parm__dm_v34_options_mask;
	parm_d     uint16                      _parm__pcm_playback_once_size;
	var_d      ufract                      _v34_tx_local_gain_adjust;
	var_d      fract32                     _v34_rx_yn_perfect_real32;
	var_d      sint15                      _ph4n_tx_receive_qn_coef_imag [V34_NO_QN_COEFS];
	var_d      ufract                      _v34_tx_preemph_gain_adjust;
	var_d      fract32                     _detect_v21_detect_lpf2_32;
	persist_d  uint16                      _v34n_tx_symbol_option;
	var_d      sint15                      _dcdelout_hi [DC_ORD];
	local_d    uint16                      _v34n_tx_auxiliary_channel;
	var_d      uint16                      _tim_sart_semaphore;
	var_d      uint16                      _ata_call_record_channel;
	var_d      sint15*                     _parm__speech_dec_host_addr;
	debug_d    sint15                      _V34S_LEN_8K0_MIN_LOCAL_TRAIN;
	parm_d     uint16                      _parm__dm_v34_data_rate_mask;
	var_d      uint16                      _v92n_rx_prefilter_gain_x4;
	var_d      fract32                     _tonemute_sum_rx;
	var_d      uint16                      _parm__audio_input;
	var_d      fract                       _lec__nlp_cng_offset_decrement;
	stat_d     uint16                      _stat__disconnect_tone_tone_detect_mask;
	local_d    char                        _parm__ipbx_outgoing_block_list [IPBX_LIST__OUTGOING_BLOCK_NO_OF][IPBX_DIAL_STRING_SIZEOF];
	stat_d     uint16                      _stat__ipod_debug_enabled;
	var_d      uint16 *                    _nat_pkt_mac_ptr; /* Pointer to MAC header */
	debug_d    uint16                      _cp_change;
	var_d      sint15                      _g729_test_uncompressed_data [L_FRAME];
	var_d      fract                       _pcm_rx_TRN2A_log_energy;
	var_d      mse_struct                  _v34_pnt3_MSE_stack [V34_TRN2_MSE_STACK_SIZE];
	var_d      sint31                      _ac97_dma_tx_irq;
	var_d      thread_routine_t            _pcm_rx_sequence_detect_routine;
	var_d      fract                       _g711_rx_vad_peak_mean;
	parm_d     uint16                      _parm__selcall_enc_tone_set;
	parm_d     uint16                      _parm__ipbx_red_priority_table [PRIORITY_TABLE_SIZEOF];
	var_d      uint16                      _sart_rx_write_index;
	parm_d     uint32                      _stat__nat_rcv_delivers; /* LAN to WAN receive packet deliver exit counter (into upper IP layers) */
	var_d      ufract                      _ph2p_anal_flatvar;
	var_d      fract                       _ph2p_anal_variance_03_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2n_rx_train_16pt;
	parm_d     uint16                      _stat__mgcp_is_registered;
	var_d      sint15                      _v90_tx_dil_count;
	debug_d    sint15                      _g729_sync_debug [MAX_CODER_FRAME_SIZE];
	var_d      fract                       _data_14k4_lookup_internal_buffer [140];
	debug_d    uint16                      _dcd_energy_y_select;
	var_d      bool                        _prev_uv_sc_ana;
	parm_d     uint16                      _parm__sip_tos_value;
	var_d      fract                       _v34_rx_zn_hat_real;
	coef_d     fract                       _lec__td_update [LEC__TD_BLOCK_SIZE];
	parm_d     fract                       _parm__dm_v34_mse_fallback;
	var_d      uint16                      _bulk_delay_buffer_size;
	var_d      uint32                      _ata_sample_record_size;
	var_d      bool                        _v92n_parm_sh2_enable;
	var_d      uint16                      _V34_MD_LENGTH_INCREMENT;
	var_d      uint16                      _dtmf_unclamp_detect;
	var_d      sint15                      _lpres_delout [LPF_ORD];
	var_d      uint16                      _ph2n_tx_preemph [V34N_MAX_SYMBOL+1];
	debug_d    uint16                      _dt_previous;
	var_d      fract                       _v34_pp_result_ang_table [CC_RX_PP_ANALYSIS_SIZE];
	var_d      uint16                      _rx_rd_index;
	var_d      fract                       _pcm_rx_TRN2A_log_energy_ratio;
	var_d      sint15                      _v90_tx_residue_length;
	var_d      fract                       _pcm_16K_rx_sample;
	var_d      sint15                      _cc_rx_energy_delay_poffset;
	parm_d     bool                        _parm__ipbx_fxo_cid_after_ring;
	var_d      uint16                      _delta_t;
	parm_d     sint31                      _parm__ata_firmware_update_periodic_delay;
	parm_d     uint16                      _parm__decoder_prev_mode;
	var_d      uint16                      _ph2p_anal_maxrates_15_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_powr_temp_x_buffer [2*PH2P_BLOCKSIZE];
	debug_d    sint15                      _dt_output;
	var_d      sint15                      _parm__speech_rtp_ans_send_cnt; /* 1 */
	persist_d  uint16                      _ph2n_rx_3429_option;
	parm_d     sint15                      _parm__speech_dec_slot_size;
	var_d      sint15                      _v34s_special_local_train_shift_slew;
	var_d      uint8                       _sonitrol_remote_audio_ip [4];
	const_d    fract                       _silence_threshold;
	var_d      sint15                      _tmp_lpc [LPC_ORD];
	debug_d    uint16                      _ph1n_tx_index_QTS;
	parm_d     uint16                      _stat__vpcm_digital_mode;
	var_d      sint15                      _v92_rx_decoder_ff_error;
	parm_d     uint16                      _parm__codec_ring_detect_method;
	parm_d     uint32                      _stat__nat_wan_broadcast; /* WAN to LAN receive broadcast packet exit counter */
	var_d      uint16                      _v90n_tx_train_16pt_option;
	var_d      mse_struct                  _v34_pnt0_MSE_stack [V34_TRN2_MSE_STACK_SIZE];
	var_d      uint16                      _v92n_parm_rx_train_8pt_option;
	var_d      sint15                      _lec__best_erl_poffset;
	parm_d     bool                        _parm__nat_l2tp_enable; /* Layer 2 Tunneling Protocol (L2TP) enable */
	var_d      phase_t                     _phase_adjust;
	var_d      sint15                      _ph2p_anal_preemph_index;
	var_d      uint16                      _vppn_device_firmware_checksum;
	var_d      fract                       _v34_slew_sin_BE;
	var_d      fract*                      _datamaxoffset;
	var_d      sint15                      _tone_priority_gen_index;
	debug_d    cpd_t                       _cp_data [CP_TABLE_ENTRY_NUM];
	var_d      uint16                      _trcval;
	stat_d     uint16                      _stat__dm_v90_enable;
	var_d      fract CIRCULAR              _p18_lpf_buffer_imag [2 * C7K2_RX_LPF_SIZE];
	var_d      void (*                     _v90_frame_rx_parse_routine) (void);
	shared_d   uint16                      _parm__dtmf_wait_duration;
	debug_d    fract                       _tone_detector_slew_rate;
	var_d      sint15                      _lec__nlp_detect_loose;
	var_d      fract32                     _v34_rx_yn_error_imag_32;
	debug_d    uint16                      _v8_rx_state;
	var_d      uint16*                     _v92n_tx_CPd_body_word [2];
	var_d      fract32                     _ph2p_powr_L1_spectrum_power_buffer32 [PH2P_NO_BINS_x2];
	debug_d    fract                       _v17_diagnostics_mse_log;
	var_d      uint16                      _current_crc;
	var_d      fract *                     _ph2_rx_checker_bpf_coef_pointer;
	var_d      sint15                      _v92_system_ID_energy_rbs;
	var_d      sint15                      _ph2_tx_rate_conv_9K6_8K0_pointer;
	var_d      uint16*                     _v90n_rx_INFO0d_body [20];
	const_d    ufract                      _V34_QN_UPDATE_FAST_SLEW;
	parm_d     sint15                      _parm__speech_audio_frame_cnt;
	var_d      sint15                      _circb_min [ENH_VEC_LENF];
	parm_d     uint32                      _parm__mgcp_rtp_public_external_ip_address;
	parm_d     bool                        _parm__ata_am_pm_display_enable;
	debug_d    uint16                      _baud_hdlc_frame_start_indicator;
	var_d      uint16                      _stat__slac_revision;
	const_d    uint16                      _first_gear_change_period;
	var_d      sint15                      _dcdelout_lo [DC_ORD];
	var_d      sint15                      _sdt_hit_counter;
	var_d      sint15                      _v34_resync_data_offset;
	var_d      bool                        _cid_data_seen;
	var_d      sint15                      _v90_shape_shift_count;
	var_d      sint15                      _tone_pattern_gen_count;
	parm_d     char                        _parm__sip_nat_keep_alive_message [STRSIZE_64];
	var_d      uint16                      _sonitrol_unexpected_disconnect;
	var_d      uint16                      _ipod_msg_tx_digit_pair;
	parm_d     sint15                      _parm__speech_dec_frame_rate;
	shared_d   uint16                      _parm__net_debug_level_ata;
	parm_d     struct tone_descriptor      _parm__ipbx_station_call_waiting_tone_default;
	const_d    fract                       _monitor_sample_agc_2_target;
	var_d      sint15                      _TILT_FACTOR0;
	var_d      uint16                      _ipod_timer;
	var_d      fract                       _fsk_gain_adjust;
	var_d      uint16                      _v92n_tx_constel_points [4*V92_MAX_CONSTEL_SIZE]; /* 128 for normal, 128 for RBS constel */
	var_d      sint15                      _l_prev_ncof [MIX_ORD+1];
	var_d      bool                        _vppn_device_firmware_update;
	var_d      fract                       _retrain_imag;
	var_d      fract                       _v34_BE_log_Gn_prev;
	var_d      uint16                      _pcm_ctl_use_pcm_DC_offset_value;
	var_d      uint16                      _ph2_data_timeout_start;
	var_d      sint15                      _decode_frame_concealment_indication;
	var_d      uint16 *                    _ph2p_anal_maxrate_results_pointer;
	var_d      nat_tab_t *                 _nat_triggered_list; /* Triggered table list head */
	var_d      fract                       _dcd_diversion;
	var_d      fract                       _g722_e4l_al1;
	var_d      fract                       _g722_e4l_al2;
	var_d      sint15                      _lsd_recovery_rlsd_state;
	var_d      sint15                      _l_prev_gain [2*NF*NUM_GAINFR];
	parm_d     uint16                      _parm__sip_max_forwards;
	var_d      sint15                      _ph2s_orig_INFO1_counter;
	var_d      fract                       _fax_error_mse_limit;
	var_d      fract CIRCULAR              _remote_interpolator_buffer_real [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	var_d      fract32                     _ph2p_fefo_delta_buffer_hertz32 [PH2P_NO_BINS];
	var_d      sint15                      _ase_del [LPC_ORD];
	var_d      fract32                     _cc_rx_spectrum_result_table32_real [CC_RX_SPECTRUM_SIZE];
	parm_d     uint32                      _stat__nat_wan_ip_forward; /* WAN to LAN receive IP forwarding success packet exit counter */
	var_d      uint16                      _stat__g168_faxdet_detect_value;
	parm_d     sint15                      _parm__slac_port_spkr_gain;
	local_d    uint16                      _bulk_delay_buffer [BULK_DELAY_BUFFER_SIZEOF];
	var_d      uint16                      _pcm_rx_8K0_divisor_flag_ph3;
	var_d      fract32                     _btrec_rx_phase_first_low;
	shared_d   uint16                      _parm__vppn_device_firmware_address;
	debug_d    uint16                      _line_rx_overflow;
	stat_d     sint15                      _stat__speech_dec_mbx_cnt;
	var_d      sint15                      _v34_yn_error_imag;
	var_d      kernel_t                    _bg_kernel;
	var_d      uint16                      _ph2n_rx_pcm_3429_option;
	fast_d     uint16                      _stat__faxdet_detect_value;
	local_d    bool                        _parm__ipbx_disturb_accept_last_call_service;
	var_d      bool                        _ph2_AB_detect_enable;
	var_d      sint15                      _v34_tx_yn_imag;
	parm_d     uint32                      _stat__nat_snd_discards; /* LAN to WAN send packet discard exit counter */
	var_d      ufract                      _ph2_scale_value;
	var_d      sint15                      _lspSid [M_LP];
	fast_d     fract                       _faxdet_threshold_ced;
	parm_d     uint32                      _stat__nat_rcv_ttl_discard; /* LAN to WAN receive TTL discard packet exit counter */
	var_d      uint16                      _v90n_rx_dpcm_data_rate_option [2];
	var_d      fract CIRCULAR              _cc_tx_rate_buffer [CC_TX_RATE_SIZE * 2];
	var_d      uint16                      _v34s_gear_change_period;
	var_d      uint16                      _v27_tx_guard_flag;
	var_d      uint16                      _pcm_digital_pad_table [256];
	parm_d     bool                        _parm__net_syslog_enable;
	parm_d     bool                        _parm__codec_disconnect_silence_enable;
	var_d      fract                       _ph2n_probing_receive_agc2_level;
	parm_d     char                        _stat__sip_global_keep_alive_domain_name [NET_DOMAIN_SIZEOF];
	var_d      uint16                      _faxparm_parm__silence_duration;
	var_d      fract                       _PH2P_ANAL_CENTER_ENERGY_WEIGHT;
	fast_d     ufract                      _encode_gain_linear;
	parm_d     uint16                      _parm__reset_flag;
	parm_d     uint16                      _parm__ipbx_fc_blocked_number_enable;
	parm_d     uint32                      _stat__nat_wan_ip_fragment; /* WAN to LAN receive IP fragment packet type counter */
	local_d    uint16                      _v34n_rx_trellis_setting;
	var_d      sint15                      _measured_bulk_delay;
	shared_d   fract                       _impedance_monitor_tx_data [IMPEDANCE_MONITOR_COEF_SIZE * 2];
	local_d    bool                        _parm__ipbx_three_way_calling_service;
	var_d      uint16                      _ph3n_rx_shaping_lookahead;
	var_d      sint15                      _V90_RX_Sd_DETECT_LIMIT;
	const_d    fract                       _parm__dm_v92_mse_trn_bias;
	var_d      pcm_ec_slew_calculations_t  _pcm_eq_ep_slews;
	var_d      fract32                     _v34_rx_yn_perfect_imag32;
	var_d      sint15                      _parm__speech_mac_src_addr [3];
	fast_d     int                         _bg_event_remove;
	parm_d     sint15                      _parm__speech_g729octet_bitrev;
	var_d      shaper_routine_t            _pcm_rx_8K0_data_routine;
	stat_d     uint16                      _stat__v8__modulation_modes [3];
	parm_d     uint16                      _parm__radio_channel_selection;
	parm_d     sint15                      _parm__tone_generators [(TONE_GENERATOR_COUNT * 2) + 1];
	var_d      call_info_t*                _picp_history;
	stat_d     sint15                      _stat__speech_dec_mode;
	var_d      uint16                      _sonitrol_panel_group_id [4+1];
	var_d      fract                       _v34_temp_lo_hi_pre_equalizer_coefs [5];
	var_d      sint15                      _phone_handset_tx_volume;
	var_d      sint15                      _gpf_LLadj;
	var_d      sint15                      _v92_rx_slot_counter;
	var_d      sint15                      _v90_rx_shaper_state;
	var_d      bool                        _tone_pattern_flag;
	var_d      fract                       _v34_TRN2_MSE_rate_value;
	stat_d     sint15                      _stat__speech_rtp_generic_info;
	debug_d    uint16                      _line_tx_buffer_element;
	var_d      sint15                      _g711_rx_dtx_counter;
	shared_d   mgcp_message_t              _mgcp_parser_message;
	var_d      fract                       _demod_leading_half_real;
	var_d      const sint15 *              _v34_frame_rx_bit_parse_pointer_bits;
	var_d      fract                       _data_7k2_lookup_internal_buffer [16];
	parm_d     uint16                      _stat__phone_zeroize_state;
	var_d      uint16                      _v90_rx_S_send_flag;
	var_d      uint16                      _rd_period_cnt;
	parm_d     uint16                      _parm__sart_rx_release_threshold;
	var_d      bool                        _tone_pattern_series;
	var_d      uint16                      _op_state;
	parm_d     bool                        _parm__ipbx_bridge_autoanswer_any_enable;
	var_d      fract                       _vala;
	var_d      fract                       _valb;
	var_d      bool                        _current_bg_state_active;
	var_d      fract                       _valc;
	var_d      fract                       _vald;
	parm_d     sint15                      _parm__melp_rate;
	var_d      fract                       _double_echo0;
	var_d      fract                       _double_echo1;
	fast_d     uint16                      _asm_encode_within_frame;
	var_d      uint16                      _ata_sample_record_channel;
	debug_d    bool                        _v34s_apply_agc_1;
	parm_d     struct tone_descriptor      _parm__ipbx_call_back_ring_tone;
	var_d      sint15                      _dcdelin [DC_ORD];
	debug_d    uint16                      _ORIG_V8_CJ_COUNT_MIN;
	var_d      sint15                      _parm__speech_ip_fragment_offset;
	var_d      uint16                      _shadow_franchise_label [5+1];
	var_d      int                         _sonitrol_v34_plus_counter;
	fast_d     uint16                      _parm__report_status_mask;
	parm_d     bool                        _parm__ipbx_bridge_autoanswer_enable;
	local_d    bool                        _parm__ipbx_outgoing_block_enable;
	fast_d     uint16                      _faxdet_ansam_dropout_count;
	var_d      fract                       _phasedet_complex_value [2];
	var_d      fract                       _DIL_probing_pad_mse_log;
	var_d      complex CIRCULAR            _equalizer_buffer_complex [2 * C7K2_RX_EQUALIZER_SIZE];
	var_d      sint15                      _circb [NUM_MINWIN][ENH_VEC_LENF];
	var_d      sint15                      _fsk_processing_mode;
	stat_d     sint15                      _stat__speech_ip_header_checksum;
	parm_d     char                        _parm__net_unique_device_id [ATA_UNIQUE_ID_SIZEOF];
	var_d      uint16                      _send__v8__modulation_modes [3];
	parm_d     char                        _parm__mgcp_sdp_session_owner [STRSIZE_32];
	var_d      fract                       _equalizer_coef_imag [C7K2_RX_EQUALIZER_SIZE];
	var_d      uint16                      _ph2n_rx_carrier_s3429;
	var_d      uint16                      _oicp_saved_digit;
	parm_d     uint32                      _parm__ata_firmware_update_error_retry_delay;
	var_d      uint16                      _v34h_tx_state;
	var_d      uint16                      _v34n_parm_trellis_option;
	var_d      sint15                      _ph2n_probing_L1_SE_power_adjust;
	var_d      uint16                      _dtmf_mode_semaphore;
	var_d      sint15                      _g_rate;
	var_d      uint16*                     _v90_frame_rx_dil_body_ref [5];
	var_d      uint16                      _v34n_parm_nonlinear_option;
	var_d      uint16                      _v34h_rx_Qn_1st_2D;
	local_d    bool                        _parm__ipbx_default_feature_code_service;
	var_d      fract                       _g722_d4h_ah1;
	var_d      fract                       _g722_d4h_ah2;
	var_d      sint15*                     _res2;
	local_d    uint16                      _v34n_tx_train_16pt;
	parm_d     bool                        _parm__ipbx_bridge_fxs_call_enable;
	parm_d     uint16                      _parm__audio_sync_enable;
	var_d      sint15                      _PH2P_POWR_RX_CLEAR_INIT;
	var_d      sint31                      _g_next;
	var_d      sint15                      _v90_rx_dil_sp_cnt;
	var_d      uint16 *                    _v34h_rx_buffer_load_pointer;
	fast_d     sint15                      _sample_conversion_control;
	var_d      sint15                      _fsk_TONE_phase;
	var_d      uint16                      _legacy_SPP_nack_count;
	local_d    uint16                      _v24_txd;
	debug_d    sint15                      _cp_average_counter;
	stat_d     sint15                      _stat__speech_ip_identifier;
	var_d      ufract                      _v34_resync_min_value;
	parm_d     uint16                      _parm__disconnect_tone_cadence_repeat [DT_TABLE_ENTRY_NUM];
	var_d      ufract                      _g711_rx_vad_level_mean_lsw;
	var_d      uint16                      _parm__vppn_device_temporary_id [PKT_VPPN__SIZEOF_TEMPORARY_ID];
	var_d      uint16                      _v90n_tx_reference_point;
	var_d      sint15 *                    _v90_frame_rx_bit_pointer;
	var_d      fract                       _pcm_8K0_equalized;
	local_d    uint16                      _parm__ipbx_pstn_not_available;
	parm_d     uint16                      _parm__cp_rd_decimate_cnt;
	var_d      uint16                      _ipod_tx_v34_status;
	local_d    bool                        _parm__ipbx_visual_message_waiting_service;
	var_d      fract                       _g722_e4h_oldrh;
	var_d      fract                       _mean_square_error;
	var_d      bool                        _v92n_rx_v92_enable;
} datastruct_t DATASTRUCT;

#define stat__nat_wan_l2tp               DATASTRUCT._stat__nat_wan_l2tp
#define s1_detector_offset               DATASTRUCT._s1_detector_offset
#define rf_interrupt_running             DATASTRUCT._rf_interrupt_running
#define debug_array                      DATASTRUCT._debug_array
#define parm__vppn_garbage_collection    DATASTRUCT._parm__vppn_garbage_collection
#define parm__ipbx_call_back_retry_duration DATASTRUCT._parm__ipbx_call_back_retry_duration
#define parm__ipbx_call_holding_rering   DATASTRUCT._parm__ipbx_call_holding_rering
#define pcm_rx_gain                      DATASTRUCT._pcm_rx_gain
#define modulator_phase                  DATASTRUCT._modulator_phase
#define v34_equalizer_slew_medium        DATASTRUCT._v34_equalizer_slew_medium
#define legacy_tx_ack_handler            DATASTRUCT._legacy_tx_ack_handler
#define ipod_iface_rx_state              DATASTRUCT._ipod_iface_rx_state
#define lsf600_s                         DATASTRUCT._lsf600_s
#define parm__speech_asm_host_lb         DATASTRUCT._parm__speech_asm_host_lb
#define parm__slac_ring_frequency        DATASTRUCT._parm__slac_ring_frequency
#define parm__sdp_g723_codec_name        DATASTRUCT._parm__sdp_g723_codec_name
#define monitor_ones_flag                DATASTRUCT._monitor_ones_flag
#define ph2_tx_Lx_gain                   DATASTRUCT._ph2_tx_Lx_gain
#define monitor_sample_slow_absolute_threshold DATASTRUCT._monitor_sample_slow_absolute_threshold
#define v90_rx_spectrum_result_buffer_real40 DATASTRUCT._v90_rx_spectrum_result_buffer_real40
#define impedance_monitor_filter_offset  DATASTRUCT._impedance_monitor_filter_offset
#define ph2p_anal_log_S_plus_start       DATASTRUCT._ph2p_anal_log_S_plus_start
#define sonitrol_audio_Lpt_request_sent  DATASTRUCT._sonitrol_audio_Lpt_request_sent
#define DMOVLAY                          DATASTRUCT._DMOVLAY
#define gear_counter                     DATASTRUCT._gear_counter
#define parm__ringer_tx_gain             DATASTRUCT._parm__ringer_tx_gain
#define ph2_rx_rate_conv_9K6_8K0_pointer DATASTRUCT._ph2_rx_rate_conv_9K6_8K0_pointer
#define ANSam_measured_delta_phase       DATASTRUCT._ANSam_measured_delta_phase
#define ph1_tx_ANSpcm_sign_reverse       DATASTRUCT._ph1_tx_ANSpcm_sign_reverse
#define ANSam_power40                    DATASTRUCT._ANSam_power40
#define v34h_rx_control_this_pointer     DATASTRUCT._v34h_rx_control_this_pointer
#define v34_symbol_diff_decode_data      DATASTRUCT._v34_symbol_diff_decode_data
#define v92h_rx_M_1_buffer               DATASTRUCT._v92h_rx_M_1_buffer
#define convert_target_log               DATASTRUCT._convert_target_log
#define parm__voip_melp_postfilter_enable DATASTRUCT._parm__voip_melp_postfilter_enable
#define pcm_playback_mode                DATASTRUCT._pcm_playback_mode
#define prev_gain_low_rate_chn_read      DATASTRUCT._prev_gain_low_rate_chn_read
#define ipod_command_vad_enable          DATASTRUCT._ipod_command_vad_enable
#define parm__sdp_melp_codec_dyn_pt      DATASTRUCT._parm__sdp_melp_codec_dyn_pt
#define parm__battery_level_threshold    DATASTRUCT._parm__battery_level_threshold
#define equalizer_slew                   DATASTRUCT._equalizer_slew
#define saved_v90trn_mask                DATASTRUCT._saved_v90trn_mask
#define sonitrol_rx_transaction_count    DATASTRUCT._sonitrol_rx_transaction_count
#define parm__dm_v34_mse_trn_bias        DATASTRUCT._parm__dm_v34_mse_trn_bias
#define switch_counter                   DATASTRUCT._switch_counter
#define g722_d4l_bl                      DATASTRUCT._g722_d4l_bl
#define v34n_rx_symbol_rate              DATASTRUCT._v34n_rx_symbol_rate
#define parm__ctcss_enc_frequency        DATASTRUCT._parm__ctcss_enc_frequency
#define gaussian_buffer                  DATASTRUCT._gaussian_buffer
#define ph2_INFO_detected                DATASTRUCT._ph2_INFO_detected
#define parm__nat_block_malicious_ports  DATASTRUCT._parm__nat_block_malicious_ports
#define pcm_rx_2k_energy_ph3             DATASTRUCT._pcm_rx_2k_energy_ph3
#define tone_generator_previous          DATASTRUCT._tone_generator_previous
#define predicted_rx_xn_B1_Q_n_count     DATASTRUCT._predicted_rx_xn_B1_Q_n_count
#define legacy_rx_duplicate_length       DATASTRUCT._legacy_rx_duplicate_length
#define parm__net_isp_keep_alive_enable  DATASTRUCT._parm__net_isp_keep_alive_enable
#define parm__sdp_t38_codec_dyn_pt       DATASTRUCT._parm__sdp_t38_codec_dyn_pt
#define v34_initialize_data_illegal_setting DATASTRUCT._v34_initialize_data_illegal_setting
#define ipod_msg_rx_sig_on_offset        DATASTRUCT._ipod_msg_rx_sig_on_offset
#define v92_x_law_decode_routine         DATASTRUCT._v92_x_law_decode_routine
#define p18_correlator_fit_threshold     DATASTRUCT._p18_correlator_fit_threshold
#define overlay_ph2_uses_ph1_results     DATASTRUCT._overlay_ph2_uses_ph1_results
#define ph2_power_trace_Yoffset          DATASTRUCT._ph2_power_trace_Yoffset
#define l_bit_buffer                     DATASTRUCT._l_bit_buffer
#define stat__ipbx_epoch_clock           DATASTRUCT._stat__ipbx_epoch_clock
#define monitor_be2_angle                DATASTRUCT._monitor_be2_angle
#define v34_yn_perfect_imag              DATASTRUCT._v34_yn_perfect_imag
#define v34_rx_xn_imag                   DATASTRUCT._v34_rx_xn_imag
#define false_hit_miss_limit             DATASTRUCT._false_hit_miss_limit
#define lpbuf_pitchAuto                  DATASTRUCT._lpbuf_pitchAuto
#define noise_fg                         DATASTRUCT._noise_fg
#define tone_pattern_index               DATASTRUCT._tone_pattern_index
#define v34f_recp_requests_restart       DATASTRUCT._v34f_recp_requests_restart
#define rf_sample_interrupt_offset       DATASTRUCT._rf_sample_interrupt_offset
#define pcm_btr_routine                  DATASTRUCT._pcm_btr_routine
#define ph2p_powr_P_buffer32             DATASTRUCT._ph2p_powr_P_buffer32
#define pcm_ctl_echo_rx_DC               DATASTRUCT._pcm_ctl_echo_rx_DC
#define parm__selcall_enc_lead_out       DATASTRUCT._parm__selcall_enc_lead_out
#define v92_rx_Ru_detect_count           DATASTRUCT._v92_rx_Ru_detect_count
#define dtmf_last_col_level              DATASTRUCT._dtmf_last_col_level
#define cc_rx_delay_buffer_imag          DATASTRUCT._cc_rx_delay_buffer_imag
#define sonitrol_CS_port                 DATASTRUCT._sonitrol_CS_port
#define v92n_rx_CP_specify               DATASTRUCT._v92n_rx_CP_specify
#define p18_hit_counter                  DATASTRUCT._p18_hit_counter
#define vppn_sent_final_poll             DATASTRUCT._vppn_sent_final_poll
#define l_firstTime_lsp_to_freq          DATASTRUCT._l_firstTime_lsp_to_freq
#define fsk_lpf_buffer_real              DATASTRUCT._fsk_lpf_buffer_real
#define sample_state                     DATASTRUCT._sample_state
#define mem_w0                           DATASTRUCT._mem_w0
#define baud_rx_state                    DATASTRUCT._baud_rx_state
#define ph2_rx_special_bpf_coef_pointer  DATASTRUCT._ph2_rx_special_bpf_coef_pointer
#define log_previous_energy              DATASTRUCT._log_previous_energy
#define stat__phone_memcard_state        DATASTRUCT._stat__phone_memcard_state
#define parm__rtp_srtp_aes_keylength     DATASTRUCT._parm__rtp_srtp_aes_keylength
#define lpfsp_delout                     DATASTRUCT._lpfsp_delout
#define g711_rx_vad_level_passthrough    DATASTRUCT._g711_rx_vad_level_passthrough
#define parm__ipbx_ring_debounce         DATASTRUCT._parm__ipbx_ring_debounce
#define g722_d4l_dl                      DATASTRUCT._g722_d4l_dl
#define v90n_parm_nominal_power          DATASTRUCT._v90n_parm_nominal_power
#define V92_EVENT__XX_RECEIVED_CRC_ERROR DATASTRUCT._V92_EVENT__XX_RECEIVED_CRC_ERROR
#define stat__oicp_ved_key_mask          DATASTRUCT._stat__oicp_ved_key_mask
#define ph2_rx_passband_buffer           DATASTRUCT._ph2_rx_passband_buffer
#define sonitrol_lc_download_ethernet_initiated DATASTRUCT._sonitrol_lc_download_ethernet_initiated
#define parm__codec_line_in_use_debounce DATASTRUCT._parm__codec_line_in_use_debounce
#define agc_2_gain                       DATASTRUCT._agc_2_gain
#define parm__ipbx_fxo_pstn_cid_forward_enable DATASTRUCT._parm__ipbx_fxo_pstn_cid_forward_enable
#define v34n_parm_difference_option      DATASTRUCT._v34n_parm_difference_option
#define v17_long_seg2_length             DATASTRUCT._v17_long_seg2_length
#define v34_resync_data_buffer_imag      DATASTRUCT._v34_resync_data_buffer_imag
#define v92_system_ID_input              DATASTRUCT._v92_system_ID_input
#define ipod_msg_tx_sig_type             DATASTRUCT._ipod_msg_tx_sig_type
#define parm__speech_dec_g711_plc_en     DATASTRUCT._parm__speech_dec_g711_plc_en
#define stat__nat_wan_frag_required      DATASTRUCT._stat__nat_wan_frag_required
#define dprmbx_generate_ack              DATASTRUCT._dprmbx_generate_ack
#define ph2p_powr_L1_delay_delay_start   DATASTRUCT._ph2p_powr_L1_delay_delay_start
#define parm__selcall_enc_enable         DATASTRUCT._parm__selcall_enc_enable
#define ipbx_parameter_index             DATASTRUCT._ipbx_parameter_index
#define stat__dm_v92_negotiation         DATASTRUCT._stat__dm_v92_negotiation
#define v34_equalizer_slew_slow          DATASTRUCT._v34_equalizer_slew_slow
#define equalizer_lagging_real           DATASTRUCT._equalizer_lagging_real
#define v34_tx_local_data_enable         DATASTRUCT._v34_tx_local_data_enable
#define valid_hit_limit                  DATASTRUCT._valid_hit_limit
#define pcm_tx_hpf_ff                    DATASTRUCT._pcm_tx_hpf_ff
#define ph1_tx_ANSpcm_cosine_pointer     DATASTRUCT._ph1_tx_ANSpcm_cosine_pointer
#define parm__ipbx_off_hook_warning_tone DATASTRUCT._parm__ipbx_off_hook_warning_tone
#define train_on_data_64_slew            DATASTRUCT._train_on_data_64_slew
#define v90_rx_dil_tp_ptr                DATASTRUCT._v90_rx_dil_tp_ptr
#define parm__ipbx_epoch_clock_limit     DATASTRUCT._parm__ipbx_epoch_clock_limit
#define V90S_LEN_8K0_J_DELAY             DATASTRUCT._V90S_LEN_8K0_J_DELAY
#define sonitrol_v34_mode                DATASTRUCT._sonitrol_v34_mode
#define parm__video_capture_mode         DATASTRUCT._parm__video_capture_mode
#define V34H_RX_BASE_GROUP_SIZE_1        DATASTRUCT._V34H_RX_BASE_GROUP_SIZE_1
#define scrambled_mark_count             DATASTRUCT._scrambled_mark_count
#define parm__ipbx_incoming_call_history DATASTRUCT._parm__ipbx_incoming_call_history
#define pcm_xmit_reshape_buffer          DATASTRUCT._pcm_xmit_reshape_buffer
#define pick_max_index                   DATASTRUCT._pick_max_index
#define parm__speech_rtp_tone_frame_mask DATASTRUCT._parm__speech_rtp_tone_frame_mask
#define rate_double_control              DATASTRUCT._rate_double_control
#define parm__nat_ice_enable             DATASTRUCT._parm__nat_ice_enable
#define pcm_btr_measurement_imag         DATASTRUCT._pcm_btr_measurement_imag
#define led_pattern_index                DATASTRUCT._led_pattern_index
#define g723_DecStat                     DATASTRUCT._g723_DecStat
#define parm__vppn_keepalive_debounce    DATASTRUCT._parm__vppn_keepalive_debounce
#define parm__voip_silence_supression_enable DATASTRUCT._parm__voip_silence_supression_enable
#define ph2_INFOMARKS_qualify_length     DATASTRUCT._ph2_INFOMARKS_qualify_length
#define rf_fm_sample_cnt                 DATASTRUCT._rf_fm_sample_cnt
#define precision_sin_value              DATASTRUCT._precision_sin_value
#define nat_icmp_src_port                DATASTRUCT._nat_icmp_src_port
#define parm__enc_used_mode              DATASTRUCT._parm__enc_used_mode
#define rx_trans_packets                 DATASTRUCT._rx_trans_packets
#define btrec_phdet_jam_holdoff          DATASTRUCT._btrec_phdet_jam_holdoff
#define number_of_iterations             DATASTRUCT._number_of_iterations
#define pcm_rx_interpolator_poffset      DATASTRUCT._pcm_rx_interpolator_poffset
#define parm__speech_rtp_min_frame_size  DATASTRUCT._parm__speech_rtp_min_frame_size
#define bg_task_table                    DATASTRUCT._bg_task_table
#define notch_datax32_060                DATASTRUCT._notch_datax32_060
#define force_train_word_pointer         DATASTRUCT._force_train_word_pointer
#define impedance_monitor_decimate       DATASTRUCT._impedance_monitor_decimate
#define stat__speech_enc_fill_slot_size  DATASTRUCT._stat__speech_enc_fill_slot_size
#define FALL_fallback_value              DATASTRUCT._FALL_fallback_value
#define monitor_be2_count_length_log     DATASTRUCT._monitor_be2_count_length_log
#define fg_thread_idents                 DATASTRUCT._fg_thread_idents
#define v17_short_limit                  DATASTRUCT._v17_short_limit
#define rx_sample                        DATASTRUCT._rx_sample
#define v34s_reneg_test_produce_noise    DATASTRUCT._v34s_reneg_test_produce_noise
#define asm_encode_rtp_dtmf_generate_end DATASTRUCT._asm_encode_rtp_dtmf_generate_end
#define nat_rtp_open_port                DATASTRUCT._nat_rtp_open_port
#define parm__ipbx_hookflash_delay       DATASTRUCT._parm__ipbx_hookflash_delay
#define decode_frame_sample_counter      DATASTRUCT._decode_frame_sample_counter
#define radio_led_mask                   DATASTRUCT._radio_led_mask
#define ipbx_disassociation_counter      DATASTRUCT._ipbx_disassociation_counter
#define l_prev_scale                     DATASTRUCT._l_prev_scale
#define current_fg_state                 DATASTRUCT._current_fg_state
#define parm__rtp_srtp_mode              DATASTRUCT._parm__rtp_srtp_mode
#define faxparm_active__silence_duration DATASTRUCT._faxparm_active__silence_duration
#define V92_RX_RETRAIN_Ag_THRESHOLD      DATASTRUCT._V92_RX_RETRAIN_Ag_THRESHOLD
#define lec__worst_erl_ratio             DATASTRUCT._lec__worst_erl_ratio
#define v34n_tx_control_channel_data_rate DATASTRUCT._v34n_tx_control_channel_data_rate
#define trellis_equ_error                DATASTRUCT._trellis_equ_error
#define lookback_output_imag             DATASTRUCT._lookback_output_imag
#define v34_tx_xn_local_imag             DATASTRUCT._v34_tx_xn_local_imag
#define debug_array2                     DATASTRUCT._debug_array2
#define parm__ipbx_sit2_tone             DATASTRUCT._parm__ipbx_sit2_tone
#define parm__ata_phone_lock_password    DATASTRUCT._parm__ata_phone_lock_password
#define debug_array3                     DATASTRUCT._debug_array3
#define stat__nat_wan_frag_created       DATASTRUCT._stat__nat_wan_frag_created
#define debug_array4                     DATASTRUCT._debug_array4
#define debug_array5                     DATASTRUCT._debug_array5
#define V34S_LEN_8K0_MAX_1ST_GEAR        DATASTRUCT._V34S_LEN_8K0_MAX_1ST_GEAR
#define v34_rx_zn_tilde_imag             DATASTRUCT._v34_rx_zn_tilde_imag
#define debug_array6                     DATASTRUCT._debug_array6
#define g722_enc_slow                    DATASTRUCT._g722_enc_slow
#define parm__receiver_gain              DATASTRUCT._parm__receiver_gain
#define parm__speech_dec_cng_order       DATASTRUCT._parm__speech_dec_cng_order
#define dgi_pad_gain                     DATASTRUCT._dgi_pad_gain
#define monitor_sample_slow_hi_absolute_threshold DATASTRUCT._monitor_sample_slow_hi_absolute_threshold
#define ph2n_rx_carrier                  DATASTRUCT._ph2n_rx_carrier
#define fallback_flag                    DATASTRUCT._fallback_flag
#define lec__td_update_ratio             DATASTRUCT._lec__td_update_ratio
#define force_train_bit_pointer          DATASTRUCT._force_train_bit_pointer
#define sdp_e                            DATASTRUCT._sdp_e
#define ANSam_magnitude                  DATASTRUCT._ANSam_magnitude
#define cc_rx_PP_repetition_limit        DATASTRUCT._cc_rx_PP_repetition_limit
#define save_sm_INFO1c_end_delay         DATASTRUCT._save_sm_INFO1c_end_delay
#define cc_rx_ANAL_energy_log            DATASTRUCT._cc_rx_ANAL_energy_log
#define ph1_x_law_encode_routine         DATASTRUCT._ph1_x_law_encode_routine
#define floor_detect__shift              DATASTRUCT._floor_detect__shift
#define parm__disconnect_tone_cadence_table DATASTRUCT._parm__disconnect_tone_cadence_table
#define ipod_htd_coded_speech_buffer     DATASTRUCT._ipod_htd_coded_speech_buffer
#define parm__net_static_ip_address      DATASTRUCT._parm__net_static_ip_address
#define stat__dm_tx_data_rate            DATASTRUCT._stat__dm_tx_data_rate
#define v34_rx_valid_qn_coefs_flag       DATASTRUCT._v34_rx_valid_qn_coefs_flag
#define v92_system_ID_outputA            DATASTRUCT._v92_system_ID_outputA
#define audio_delay_queue                DATASTRUCT._audio_delay_queue
#define parm__ipbx_call_back_ring_splash DATASTRUCT._parm__ipbx_call_back_ring_splash
#define v34_resync_mean_buffer_imag      DATASTRUCT._v34_resync_mean_buffer_imag
#define tone_detector_variables          DATASTRUCT._tone_detector_variables
#define tx_clock_phase                   DATASTRUCT._tx_clock_phase
#define parm__ata_configuration_request_message DATASTRUCT._parm__ata_configuration_request_message
#define equalizer_poffset                DATASTRUCT._equalizer_poffset
#define pcm_HI_peak_value                DATASTRUCT._pcm_HI_peak_value
#define V90_RX_R_ENERGY_THRESHOLD        DATASTRUCT._V90_RX_R_ENERGY_THRESHOLD
#define firstTime_syn                    DATASTRUCT._firstTime_syn
#define ec_very_slow_shift_slew_local    DATASTRUCT._ec_very_slow_shift_slew_local
#define mgcp_tx_transaction_list         DATASTRUCT._mgcp_tx_transaction_list
#define ph2p_anal_log_E_buffer           DATASTRUCT._ph2p_anal_log_E_buffer
#define sonitrol_remote_updnload_ip      DATASTRUCT._sonitrol_remote_updnload_ip
#define V34S_RUN_HOLDOFF_TIME            DATASTRUCT._V34S_RUN_HOLDOFF_TIME
#define fsk_tx_passband_coef_pointer     DATASTRUCT._fsk_tx_passband_coef_pointer
#define encode_frame_pointer             DATASTRUCT._encode_frame_pointer
#define parm__sdp_g726_40_codec_name     DATASTRUCT._parm__sdp_g726_40_codec_name
#define v34_rx_Y0_m                      DATASTRUCT._v34_rx_Y0_m
#define default_w                        DATASTRUCT._default_w
#define tx_dtmf_count                    DATASTRUCT._tx_dtmf_count
#define lec__span_size                   DATASTRUCT._lec__span_size
#define threshold_s                      DATASTRUCT._threshold_s
#define orig_v8_CJ_sent                  DATASTRUCT._orig_v8_CJ_sent
#define ipod_iface_tx_next_seqnum        DATASTRUCT._ipod_iface_tx_next_seqnum
#define noise_simulator_rx               DATASTRUCT._noise_simulator_rx
#define V90_RX_R_CORREL_THRESHOLD        DATASTRUCT._V90_RX_R_CORREL_THRESHOLD
#define fax_energy_detect_threshold      DATASTRUCT._fax_energy_detect_threshold
#define g722_2_encstruct                 DATASTRUCT._g722_2_encstruct
#define p18_angle_store_real             DATASTRUCT._p18_angle_store_real
#define decode_frame                     DATASTRUCT._decode_frame
#define energy_coefs_buffer_internal     DATASTRUCT._energy_coefs_buffer_internal
#define parm__nat_stun_symmetric_deterministic_enable DATASTRUCT._parm__nat_stun_symmetric_deterministic_enable
#define monitor_sample_slow_lo_absolute_threshold DATASTRUCT._monitor_sample_slow_lo_absolute_threshold
#define v90_rx_spectrum_result_buffer_imag40 DATASTRUCT._v90_rx_spectrum_result_buffer_imag40
#define noise_del                        DATASTRUCT._noise_del
#define ph2_tx_interpolator_buffer_real  DATASTRUCT._ph2_tx_interpolator_buffer_real
#define lec__td_tone_det_flag            DATASTRUCT._lec__td_tone_det_flag
#define parm__mgcp_remote_domain_name    DATASTRUCT._parm__mgcp_remote_domain_name
#define v90h_rx_buffer1                  DATASTRUCT._v90h_rx_buffer1
#define v90h_rx_buffer2                  DATASTRUCT._v90h_rx_buffer2
#define v34_tx_zn_local_real             DATASTRUCT._v34_tx_zn_local_real
#define silence_average_counter          DATASTRUCT._silence_average_counter
#define dev_retry_count                  DATASTRUCT._dev_retry_count
#define parm__ipbx_fc_call_waiting_enable DATASTRUCT._parm__ipbx_fc_call_waiting_enable
#define debug_host_buffer_state          DATASTRUCT._debug_host_buffer_state
#define V34_BE_LOG_MINIMUM_GAIN          DATASTRUCT._V34_BE_LOG_MINIMUM_GAIN
#define lec__rx_suppressor_decr          DATASTRUCT._lec__rx_suppressor_decr
#define sdt_dcd_threshold                DATASTRUCT._sdt_dcd_threshold
#define number_bg_states                 DATASTRUCT._number_bg_states
#define notch_datay32_120                DATASTRUCT._notch_datay32_120
#define ata_pfd_area                     DATASTRUCT._ata_pfd_area
#define pcm_folding_remeasure            DATASTRUCT._pcm_folding_remeasure
#define v34n_parm_ptt_lo_carrier_option  DATASTRUCT._v34n_parm_ptt_lo_carrier_option
#define v34n_rx_carrier_frequency        DATASTRUCT._v34n_rx_carrier_frequency
#define silence_adjust                   DATASTRUCT._silence_adjust
#define extra_rate_reduction_poffset     DATASTRUCT._extra_rate_reduction_poffset
#define parm__cp_rd_qualify_metric       DATASTRUCT._parm__cp_rd_qualify_metric
#define v34n_measured_roundtrip_delay    DATASTRUCT._v34n_measured_roundtrip_delay
#define encode_frame_active_indication   DATASTRUCT._encode_frame_active_indication
#define sip_sock_buffer                  DATASTRUCT._sip_sock_buffer
#define PH2_RX_OFFSET_LENGTH             DATASTRUCT._PH2_RX_OFFSET_LENGTH
#define v34n_rx_INFO0_body               DATASTRUCT._v34n_rx_INFO0_body
#define nat_ip_length                    DATASTRUCT._nat_ip_length
#define p18_demod_imag                   DATASTRUCT._p18_demod_imag
#define dev_send_channel                 DATASTRUCT._dev_send_channel
#define v90_rx_dil_length                DATASTRUCT._v90_rx_dil_length
#define data_9k6_lookup_internal_buffer  DATASTRUCT._data_9k6_lookup_internal_buffer
#define sonitrol_legacy_audio_mode       DATASTRUCT._sonitrol_legacy_audio_mode
#define edge_m1200                       DATASTRUCT._edge_m1200
#define parm__ipbx_bridge_security_code_enable DATASTRUCT._parm__ipbx_bridge_security_code_enable
#define frameSize                        DATASTRUCT._frameSize
#define debug_fract1                     DATASTRUCT._debug_fract1
#define parm__audio_agc_center_shift     DATASTRUCT._parm__audio_agc_center_shift
#define debug_fract2                     DATASTRUCT._debug_fract2
#define debug_fract3                     DATASTRUCT._debug_fract3
#define debug_fract4                     DATASTRUCT._debug_fract4
#define PH2_RX_PROBING_OFFSET_LENGTH     DATASTRUCT._PH2_RX_PROBING_OFFSET_LENGTH
#define v34n_tx_asymmetric_option        DATASTRUCT._v34n_tx_asymmetric_option
#define debug_fract5                     DATASTRUCT._debug_fract5
#define lec__rx_input                    DATASTRUCT._lec__rx_input
#define sonitrol_line_enabled            DATASTRUCT._sonitrol_line_enabled
#define v92_system_ID_modulo_nrm         DATASTRUCT._v92_system_ID_modulo_nrm
#define debug_fract6                     DATASTRUCT._debug_fract6
#define V34_RESYNC_PERCENT_THRESHOLD     DATASTRUCT._V34_RESYNC_PERCENT_THRESHOLD
#define v90_rx_dil_sp_mask               DATASTRUCT._v90_rx_dil_sp_mask
#define debug_fract7                     DATASTRUCT._debug_fract7
#define stat__watchdog_timer_reset       DATASTRUCT._stat__watchdog_timer_reset
#define debug_fract8                     DATASTRUCT._debug_fract8
#define phone_key_debounce_count         DATASTRUCT._phone_key_debounce_count
#define debug_fract9                     DATASTRUCT._debug_fract9
#define parm__radio_handset_continuous_transmit_enable DATASTRUCT._parm__radio_handset_continuous_transmit_enable
#define nat_translation                  DATASTRUCT._nat_translation
#define lookback_input_imag              DATASTRUCT._lookback_input_imag
#define tst_test_flag                    DATASTRUCT._tst_test_flag
#define silence_output                   DATASTRUCT._silence_output
#define asm_decode_within_g711           DATASTRUCT._asm_decode_within_g711
#define v90_rx_s_value                   DATASTRUCT._v90_rx_s_value
#define parm__audio_monitor_rx_enable    DATASTRUCT._parm__audio_monitor_rx_enable
#define sonitrol_lc_type2_shutdown       DATASTRUCT._sonitrol_lc_type2_shutdown
#define saved_remote_echo_value          DATASTRUCT._saved_remote_echo_value
#define gpf_RLgain                       DATASTRUCT._gpf_RLgain
#define parm__ata_configuration_update_from_sip DATASTRUCT._parm__ata_configuration_update_from_sip
#define enc_freq_prev                    DATASTRUCT._enc_freq_prev
#define CONVERT_AGC_1_GAIN_MAX_LOG       DATASTRUCT._CONVERT_AGC_1_GAIN_MAX_LOG
#define ANSAM_TRACKING_LIMIT             DATASTRUCT._ANSAM_TRACKING_LIMIT
#define v34n_tx_INFO1c_body              DATASTRUCT._v34n_tx_INFO1c_body
#define parm__sip_remote_user_name       DATASTRUCT._parm__sip_remote_user_name
#define v8_tx_QC_data_octet              DATASTRUCT._v8_tx_QC_data_octet
#define parm__ipbx_fc_priority_forward_enable DATASTRUCT._parm__ipbx_fc_priority_forward_enable
#define parm__ipbx_fc_unassigned_76      DATASTRUCT._parm__ipbx_fc_unassigned_76
#define v34_frame_rx_save_bit_parse_pointer_bits DATASTRUCT._v34_frame_rx_save_bit_parse_pointer_bits
#define ph2_ac_sample_buffer             DATASTRUCT._ph2_ac_sample_buffer
#define sip_form_strings                 DATASTRUCT._sip_form_strings
#define ph2n_rx_2743_option              DATASTRUCT._ph2n_rx_2743_option
#define stat__nat_wan_tcp                DATASTRUCT._stat__nat_wan_tcp
#define parm__ipbx_reorder_tone          DATASTRUCT._parm__ipbx_reorder_tone
#define parm__v92_MH_information         DATASTRUCT._parm__v92_MH_information
#define legacy_alarm_count               DATASTRUCT._legacy_alarm_count
#define tx_bpf_gain_adjust               DATASTRUCT._tx_bpf_gain_adjust
#define parm__dtmf_generate_abcd         DATASTRUCT._parm__dtmf_generate_abcd
#define parm__dpbx_led_and_mask          DATASTRUCT._parm__dpbx_led_and_mask
#define v90_shape_shift_count_limit      DATASTRUCT._v90_shape_shift_count_limit
#define cc_rx_ANAL_DC_real               DATASTRUCT._cc_rx_ANAL_DC_real
#define ph2n_rxtx_v92_enable             DATASTRUCT._ph2n_rxtx_v92_enable
#define fsk_ANSam_deviation              DATASTRUCT._fsk_ANSam_deviation
#define wiznet_shutdown_flag             DATASTRUCT._wiznet_shutdown_flag
#define parm__ipbx_outgoing_call_history DATASTRUCT._parm__ipbx_outgoing_call_history
#define tone_priority_gen_count          DATASTRUCT._tone_priority_gen_count
#define parm__mpeg4_quantization_number  DATASTRUCT._parm__mpeg4_quantization_number
#define mgcp_conference_call             DATASTRUCT._mgcp_conference_call
#define stat__speech_dec_silence_active  DATASTRUCT._stat__speech_dec_silence_active
#define v34_tx_4D_indicator              DATASTRUCT._v34_tx_4D_indicator
#define res_r                            DATASTRUCT._res_r
#define PCM_LEN_8K0_EQC_TRN1A_5TH        DATASTRUCT._PCM_LEN_8K0_EQC_TRN1A_5TH
#define picp_last_entry_time             DATASTRUCT._picp_last_entry_time
#define asm_encode_rtp_ans_prev          DATASTRUCT._asm_encode_rtp_ans_prev
#define PH2P_ANAL_TEST_PREEMPH_VALUE     DATASTRUCT._PH2P_ANAL_TEST_PREEMPH_VALUE
#define v34s_special_startup             DATASTRUCT._v34s_special_startup
#define v34n_rx_auxiliary_channel        DATASTRUCT._v34n_rx_auxiliary_channel
#define act_min_sub                      DATASTRUCT._act_min_sub
#define parm__sdp_g729b_codec_dyn_pt     DATASTRUCT._parm__sdp_g729b_codec_dyn_pt
#define ANSam_delta_phase                DATASTRUCT._ANSam_delta_phase
#define parm__g722_reset_flag_old        DATASTRUCT._parm__g722_reset_flag_old
#define Acf                              DATASTRUCT._Acf
#define g711_rx_cng_frame_pointer        DATASTRUCT._g711_rx_cng_frame_pointer
#define monitor_sample_agc_2_relative_threshold DATASTRUCT._monitor_sample_agc_2_relative_threshold
#define ANSam_magnitude_lpf              DATASTRUCT._ANSam_magnitude_lpf
#define l_refl_coef                      DATASTRUCT._l_refl_coef
#define parm__sip_notify_authentication  DATASTRUCT._parm__sip_notify_authentication
#define nat_fragment                     DATASTRUCT._nat_fragment
#define v34n_tx_optional_gain            DATASTRUCT._v34n_tx_optional_gain
#define v90n_rx_INFO1a_body              DATASTRUCT._v90n_rx_INFO1a_body
#define parm__ipbx_fc_caller_id_outbound_enable_once DATASTRUCT._parm__ipbx_fc_caller_id_outbound_enable_once
#define ec_ztrain_shift_slew_remote      DATASTRUCT._ec_ztrain_shift_slew_remote
#define dpbx_key_debounce_count          DATASTRUCT._dpbx_key_debounce_count
#define parm__ipbx_do_not_disturb_mode   DATASTRUCT._parm__ipbx_do_not_disturb_mode
#define ph2p_anal_variance_02_table      DATASTRUCT._ph2p_anal_variance_02_table
#define nat_wan_ifp                      DATASTRUCT._nat_wan_ifp
#define ipod_command_ec_config           DATASTRUCT._ipod_command_ec_config
#define stat__vpcm_coding_law            DATASTRUCT._stat__vpcm_coding_law
#define parm__sip_invite_authentication  DATASTRUCT._parm__sip_invite_authentication
#define sonitrol_system_startup_complete DATASTRUCT._sonitrol_system_startup_complete
#define pcm_eq_fb_slews                  DATASTRUCT._pcm_eq_fb_slews
#define ptloop_angle32                   DATASTRUCT._ptloop_angle32
#define asm_encode_buffer_pending        DATASTRUCT._asm_encode_buffer_pending
#define pcm_AL_MSE_value                 DATASTRUCT._pcm_AL_MSE_value
#define THD_sum_L1_magnitude             DATASTRUCT._THD_sum_L1_magnitude
#define local_buffer_pointer_rear        DATASTRUCT._local_buffer_pointer_rear
#define v34_rx_pn_tilde_imag             DATASTRUCT._v34_rx_pn_tilde_imag
#define ph2n_probing_L2_SE_power_adjust  DATASTRUCT._ph2n_probing_L2_SE_power_adjust
#define parm__speech_rtp_jitter_buffer_bypass DATASTRUCT._parm__speech_rtp_jitter_buffer_bypass
#define constel_counter                  DATASTRUCT._constel_counter
#define v90n_rx_data_rate                DATASTRUCT._v90n_rx_data_rate
#define v34_rx_trellis_new_scores        DATASTRUCT._v34_rx_trellis_new_scores
#define ph2p_fefo_dw_k_buffer32          DATASTRUCT._ph2p_fefo_dw_k_buffer32
#define v90n_parm_dpcm_data_rate_option  DATASTRUCT._v90n_parm_dpcm_data_rate_option
#define parm__vpcm_reference_point       DATASTRUCT._parm__vpcm_reference_point
#define v29_anti_lock_count              DATASTRUCT._v29_anti_lock_count
#define v90_rx_DIL_done_flag             DATASTRUCT._v90_rx_DIL_done_flag
#define ph2p_anal_maxrates_14_table      DATASTRUCT._ph2p_anal_maxrates_14_table
#define v90n_rx_shaping_lookahead        DATASTRUCT._v90n_rx_shaping_lookahead
#define stat__nat_rcv_end_point          DATASTRUCT._stat__nat_rcv_end_point
#define lag0q_s                          DATASTRUCT._lag0q_s
#define ANSAM_DELTA_PHASE_LIMIT          DATASTRUCT._ANSAM_DELTA_PHASE_LIMIT
#define cid_signal_active                DATASTRUCT._cid_signal_active
#define parm__rtp_public_external_port_min DATASTRUCT._parm__rtp_public_external_port_min
#define scrambler_match_count            DATASTRUCT._scrambler_match_count
#define ph2_rx_checker_count             DATASTRUCT._ph2_rx_checker_count
#define v34n_tx_MP1_body                 DATASTRUCT._v34n_tx_MP1_body
#define speech_direct_playback_size      DATASTRUCT._speech_direct_playback_size
#define tmp_half_energy                  DATASTRUCT._tmp_half_energy
#define phone_key_matrix                 DATASTRUCT._phone_key_matrix
#define parm__ata_configuration_success_message DATASTRUCT._parm__ata_configuration_success_message
#define parm__faxdet_v21_decrement       DATASTRUCT._parm__faxdet_v21_decrement
#define v34_frame_rx_calculated_crc      DATASTRUCT._v34_frame_rx_calculated_crc
#define parm__net_lan_pppoe_pap_enable   DATASTRUCT._parm__net_lan_pppoe_pap_enable
#define v90_tx_send_RxN_sequence_flag    DATASTRUCT._v90_tx_send_RxN_sequence_flag
#define v90_rx_RBS_adjust_enable         DATASTRUCT._v90_rx_RBS_adjust_enable
#define cc_rx_S_last_energy_log          DATASTRUCT._cc_rx_S_last_energy_log
#define g722_d4l_oldrl                   DATASTRUCT._g722_d4l_oldrl
#define v90n_tx_maximum_power            DATASTRUCT._v90n_tx_maximum_power
#define ph2_dummy_loopback_real          DATASTRUCT._ph2_dummy_loopback_real
#define v92n_tx_max_coefs_section        DATASTRUCT._v92n_tx_max_coefs_section
#define phase2                           DATASTRUCT._phase2
#define pcm_maximal_value                DATASTRUCT._pcm_maximal_value
#define lec__data_buffer                 DATASTRUCT._lec__data_buffer
#define v34_rx_qn_save1_coef_real32      DATASTRUCT._v34_rx_qn_save1_coef_real32
#define parm__sip_timer_registration_retry DATASTRUCT._parm__sip_timer_registration_retry
#define notch_datay32_180                DATASTRUCT._notch_datay32_180
#define lec__td_err_sum32                DATASTRUCT._lec__td_err_sum32
#define v34h_rx_control_next_pointer     DATASTRUCT._v34h_rx_control_next_pointer
#define ph2p_fefo_bin_step               DATASTRUCT._ph2p_fefo_bin_step
#define dc_offset_counter                DATASTRUCT._dc_offset_counter
#define pcm_rx_clock_phase_ph3           DATASTRUCT._pcm_rx_clock_phase_ph3
#define stat__nat_wan_ip_tunnel          DATASTRUCT._stat__nat_wan_ip_tunnel
#define v34n_rx_control_channel_data_rate DATASTRUCT._v34n_rx_control_channel_data_rate
#define vppn_device_registration_id_index DATASTRUCT._vppn_device_registration_id_index
#define sint15_input_limit               DATASTRUCT._sint15_input_limit
#define v90_tx_s_shape_offset            DATASTRUCT._v90_tx_s_shape_offset
#define tx_passband_coef_pointer         DATASTRUCT._tx_passband_coef_pointer
#define train_on_data_16_slew            DATASTRUCT._train_on_data_16_slew
#define dev_poh_delay                    DATASTRUCT._dev_poh_delay
#define ph2n_rx_lo_3000_option           DATASTRUCT._ph2n_rx_lo_3000_option
#define dgi_count                        DATASTRUCT._dgi_count
#define sample_interrupt_tx_offset       DATASTRUCT._sample_interrupt_tx_offset
#define ph2n_tx_transmit_attenuation     DATASTRUCT._ph2n_tx_transmit_attenuation
#define parm__codec_ring_detect_threshold DATASTRUCT._parm__codec_ring_detect_threshold
#define parm__dtmf_record_prevention     DATASTRUCT._parm__dtmf_record_prevention
#define affine_imag                      DATASTRUCT._affine_imag
#define l_bpfsp                          DATASTRUCT._l_bpfsp
#define v34n_rx_TRN_length               DATASTRUCT._v34n_rx_TRN_length
#define v34h_rx_Q_n                      DATASTRUCT._v34h_rx_Q_n
#define qk_global                        DATASTRUCT._qk_global
#define parm__mgcp_default_display_name  DATASTRUCT._parm__mgcp_default_display_name
#define sequence_outband_s_level         DATASTRUCT._sequence_outband_s_level
#define stat__net_enet_rcv_alloc_fails   DATASTRUCT._stat__net_enet_rcv_alloc_fails
#define convert_gain_input_log           DATASTRUCT._convert_gain_input_log
#define v90n_rx_silence_option           DATASTRUCT._v90n_rx_silence_option
#define content_parser_error_msg         DATASTRUCT._content_parser_error_msg
#define v34f_recp_enable_E_send_flag     DATASTRUCT._v34f_recp_enable_E_send_flag
#define parm__ipbx_busy_tone             DATASTRUCT._parm__ipbx_busy_tone
#define parm__ooma_conf_press_time       DATASTRUCT._parm__ooma_conf_press_time
#define v90_frame_rx_JD_found            DATASTRUCT._v90_frame_rx_JD_found
#define lec__adj_buffer                  DATASTRUCT._lec__adj_buffer
#define bg_task_event                    DATASTRUCT._bg_task_event
#define v90n_tx_training_redundancy      DATASTRUCT._v90n_tx_training_redundancy
#define pcm_eq_ep_slew_shift             DATASTRUCT._pcm_eq_ep_slew_shift
#define ec_ztrain_shift_slew_local       DATASTRUCT._ec_ztrain_shift_slew_local
#define cc_rx_ANAL_prev_AGC2_log         DATASTRUCT._cc_rx_ANAL_prev_AGC2_log
#define codewd_13x9                      DATASTRUCT._codewd_13x9
#define parm__net_syslog_server          DATASTRUCT._parm__net_syslog_server
#define V34S_ANSW_8K0_3RT_SNend_to_Edet  DATASTRUCT._V34S_ANSW_8K0_3RT_SNend_to_Edet
#define ph2p_anal_gain_average           DATASTRUCT._ph2p_anal_gain_average
#define clock_info_poffset               DATASTRUCT._clock_info_poffset
#define encode_octet_cnt                 DATASTRUCT._encode_octet_cnt
#define ph2_rx_checker_energy            DATASTRUCT._ph2_rx_checker_energy
#define group_lists_internal_buffer      DATASTRUCT._group_lists_internal_buffer
#define legacy_rx_duplicate_data         DATASTRUCT._legacy_rx_duplicate_data
#define pitTrack_global                  DATASTRUCT._pitTrack_global
#define sonitrol_CS_address              DATASTRUCT._sonitrol_CS_address
#define parm__headset_tx_gain            DATASTRUCT._parm__headset_tx_gain
#define predicted_rx_xn_B1_real          DATASTRUCT._predicted_rx_xn_B1_real
#define fax_v21_holdoff_length           DATASTRUCT._fax_v21_holdoff_length
#define bg_kernel_anomaly                DATASTRUCT._bg_kernel_anomaly
#define extra_rate_reduction_counter     DATASTRUCT._extra_rate_reduction_counter
#define parm__codec_line_in_use_inhibit  DATASTRUCT._parm__codec_line_in_use_inhibit
#define baud_tx_parity_stick             DATASTRUCT._baud_tx_parity_stick
#define v34_bulk_extra_local_offset      DATASTRUCT._v34_bulk_extra_local_offset
#define lec__tec_error_offset            DATASTRUCT._lec__tec_error_offset
#define sart_tx_data_unit                DATASTRUCT._sart_tx_data_unit
#define parm__speech_rtp_enc_frame_cnt   DATASTRUCT._parm__speech_rtp_enc_frame_cnt
#define local_buffer_pointer_size        DATASTRUCT._local_buffer_pointer_size
#define g722_d4l_sg                      DATASTRUCT._g722_d4l_sg
#define parm__jpeg_auto_capture          DATASTRUCT._parm__jpeg_auto_capture
#define dtmf_clamp_enabled               DATASTRUCT._dtmf_clamp_enabled
#define g722_d4l_al1                     DATASTRUCT._g722_d4l_al1
#define lec__probe_nlp_input             DATASTRUCT._lec__probe_nlp_input
#define silence_state                    DATASTRUCT._silence_state
#define stat__speech_enc_frame_mtr       DATASTRUCT._stat__speech_enc_frame_mtr
#define g722_d4l_sl                      DATASTRUCT._g722_d4l_sl
#define g722_d4l_al2                     DATASTRUCT._g722_d4l_al2
#define parm_enc                         DATASTRUCT._parm_enc
#define parm__ipbx_mode                  DATASTRUCT._parm__ipbx_mode
#define parm__pump_diag_event            DATASTRUCT._parm__pump_diag_event
#define parm__mgcp_rsip_keepalive        DATASTRUCT._parm__mgcp_rsip_keepalive
#define v34h_tx_buffer                   DATASTRUCT._v34h_tx_buffer
#define stat__oicp_ved_key_state         DATASTRUCT._stat__oicp_ved_key_state
#define quant_par                        DATASTRUCT._quant_par
#define stat__led_slow_flash_mask        DATASTRUCT._stat__led_slow_flash_mask
#define lec__2100_disabled               DATASTRUCT._lec__2100_disabled
#define stat__dm_carrier_code            DATASTRUCT._stat__dm_carrier_code
#define ph2p_anal_log_B_buffer           DATASTRUCT._ph2p_anal_log_B_buffer
#define synth_buf                        DATASTRUCT._synth_buf
#define sdt_angle_store_complex          DATASTRUCT._sdt_angle_store_complex
#define v34h_tx_g8_table                 DATASTRUCT._v34h_tx_g8_table
#define parm__ipbx_message_waiting       DATASTRUCT._parm__ipbx_message_waiting
#define V34_QN_UPDATE_MEDIUM_SLEW        DATASTRUCT._V34_QN_UPDATE_MEDIUM_SLEW
#define sip_parser                       DATASTRUCT._sip_parser
#define parm__voip_provider_default      DATASTRUCT._parm__voip_provider_default
#define ph2p_anal_start_bin              DATASTRUCT._ph2p_anal_start_bin
#define fsk_interpolator_buffer_imag     DATASTRUCT._fsk_interpolator_buffer_imag
#define V34S_RUN_V0_M_ERROR_LIMIT        DATASTRUCT._V34S_RUN_V0_M_ERROR_LIMIT
#define ph2n_probing_adj_Whi             DATASTRUCT._ph2n_probing_adj_Whi
#define parm__mgcp_sdp_session_name      DATASTRUCT._parm__mgcp_sdp_session_name
#define V34_BE_LOG_MAXIMUM_GAIN          DATASTRUCT._V34_BE_LOG_MAXIMUM_GAIN
#define parm__pump_data_modes            DATASTRUCT._parm__pump_data_modes
#define v90n_rx_attenuation              DATASTRUCT._v90n_rx_attenuation
#define parm__ipbx_zoom_alarm_service    DATASTRUCT._parm__ipbx_zoom_alarm_service
#define AC_retry_count                   DATASTRUCT._AC_retry_count
#define l_prev_tilt                      DATASTRUCT._l_prev_tilt
#define dgidect_tune_echo_level          DATASTRUCT._dgidect_tune_echo_level
#define picp_edit_position               DATASTRUCT._picp_edit_position
#define g723_extra                       DATASTRUCT._g723_extra
#define parm__ata_options_domain_name    DATASTRUCT._parm__ata_options_domain_name
#define ANSam_cycle_count                DATASTRUCT._ANSam_cycle_count
#define fax_send_length                  DATASTRUCT._fax_send_length
#define v92_system_ID_buffer             DATASTRUCT._v92_system_ID_buffer
#define v34_tx_xn_imag                   DATASTRUCT._v34_tx_xn_imag
#define pcm_disc_slot_match_value        DATASTRUCT._pcm_disc_slot_match_value
#define ph2n_rx_hi_3000_option           DATASTRUCT._ph2n_rx_hi_3000_option
#define half_input_sample                DATASTRUCT._half_input_sample
#define v34_tx_qn_remote_buffer_real     DATASTRUCT._v34_tx_qn_remote_buffer_real
#define parm__hw_tx_gain_correction      DATASTRUCT._parm__hw_tx_gain_correction
#define cc_tx_passband_coef_poffset      DATASTRUCT._cc_tx_passband_coef_poffset
#define ac97_rx_dma                      DATASTRUCT._ac97_rx_dma
#define parm__g722_mode_old              DATASTRUCT._parm__g722_mode_old
#define mpi_status_mask                  DATASTRUCT._mpi_status_mask
#define vad_flag                         DATASTRUCT._vad_flag
#define lec__alpha_value                 DATASTRUCT._lec__alpha_value
#define v34_equalizer_agc_gain           DATASTRUCT._v34_equalizer_agc_gain
#define tx_dtmf_detect_count             DATASTRUCT._tx_dtmf_detect_count
#define baud_timing_buffer               DATASTRUCT._baud_timing_buffer
#define rx_rate_conv_data_buffer         DATASTRUCT._rx_rate_conv_data_buffer
#define g722_dec_shigh                   DATASTRUCT._g722_dec_shigh
#define v92_rx_Lu_level                  DATASTRUCT._v92_rx_Lu_level
#define v90_shape_1_min                  DATASTRUCT._v90_shape_1_min
#define dcd_level                        DATASTRUCT._dcd_level
#define test_tone_phase                  DATASTRUCT._test_tone_phase
#define impedance_monitor_max_slow_lpf1  DATASTRUCT._impedance_monitor_max_slow_lpf1
#define impedance_monitor_max_slow_lpf2  DATASTRUCT._impedance_monitor_max_slow_lpf2
#define v34_rx_trellis_disable_equalizer_update DATASTRUCT._v34_rx_trellis_disable_equalizer_update
#define parm__speech_g726_reverse_mode   DATASTRUCT._parm__speech_g726_reverse_mode
#define ph2n_probing_L1_log_N_buffer     DATASTRUCT._ph2n_probing_L1_log_N_buffer
#define sart_rx_count                    DATASTRUCT._sart_rx_count
#define mse_count                        DATASTRUCT._mse_count
#define parm__mgcp_end_point_naming      DATASTRUCT._parm__mgcp_end_point_naming
#define energy_total_log                 DATASTRUCT._energy_total_log
#define g711_last_out32                  DATASTRUCT._g711_last_out32
#define rx_count_test                    DATASTRUCT._rx_count_test
#define parm__pump_fax_mode              DATASTRUCT._parm__pump_fax_mode
#define parm__sdp_g722_codec_name        DATASTRUCT._parm__sdp_g722_codec_name
#define BAUD_PLL_CLOCK_SCALE             DATASTRUCT._BAUD_PLL_CLOCK_SCALE
#define ph2_guard_tone_enable            DATASTRUCT._ph2_guard_tone_enable
#define s1_detector_constants            DATASTRUCT._s1_detector_constants
#define ipbx_gled_mask                   DATASTRUCT._ipbx_gled_mask
#define parm__ipbx_fc_disturb_accept_enable DATASTRUCT._parm__ipbx_fc_disturb_accept_enable
#define g168_exc_level                   DATASTRUCT._g168_exc_level
#define parm__nat_udp_mode               DATASTRUCT._parm__nat_udp_mode
#define DIL_calculation_pad_mse40        DATASTRUCT._DIL_calculation_pad_mse40
#define v34_rx_parm_use_precoding_in_renegotiation DATASTRUCT._v34_rx_parm_use_precoding_in_renegotiation
#define v17_short_state                  DATASTRUCT._v17_short_state
#define tx_sample                        DATASTRUCT._tx_sample
#define w_fs                             DATASTRUCT._w_fs
#define v90_rx_R_correlation_buffer      DATASTRUCT._v90_rx_R_correlation_buffer
#define notch_buffer                     DATASTRUCT._notch_buffer
#define v29_nrm_mse_32                   DATASTRUCT._v29_nrm_mse_32
#define rtp_video_enc_packet             DATASTRUCT._rtp_video_enc_packet
#define baud_rx_cntr                     DATASTRUCT._baud_rx_cntr
#define energy_input40                   DATASTRUCT._energy_input40
#define parm__slac_port_tx_gain          DATASTRUCT._parm__slac_port_tx_gain
#define V34_TX_CARRIER_FREQUENCY         DATASTRUCT._V34_TX_CARRIER_FREQUENCY
#define ph2n_rx_v90_ITU_bits_reserved    DATASTRUCT._ph2n_rx_v90_ITU_bits_reserved
#define v90_tx_ks_value                  DATASTRUCT._v90_tx_ks_value
#define v34_local_echo_gain              DATASTRUCT._v34_local_echo_gain
#define cc_rx_lpf_poffset                DATASTRUCT._cc_rx_lpf_poffset
#define stat__nat_rcv_header_option      DATASTRUCT._stat__nat_rcv_header_option
#define out_vxxmod_local                 DATASTRUCT._out_vxxmod_local
#define parm__reset_flag_old             DATASTRUCT._parm__reset_flag_old
#define rate_reduction_buffer_imag       DATASTRUCT._rate_reduction_buffer_imag
#define v29_save_equalized_imag          DATASTRUCT._v29_save_equalized_imag
#define periodic_timer                   DATASTRUCT._periodic_timer
#define ph2p_L2_log_power_display_buffer DATASTRUCT._ph2p_L2_log_power_display_buffer
#define parm__codec_parallel_in_use_detect_method DATASTRUCT._parm__codec_parallel_in_use_detect_method
#define v92_rx_un_perfect                DATASTRUCT._v92_rx_un_perfect
#define parm__ipbx_call_back_ring_wait_duration DATASTRUCT._parm__ipbx_call_back_ring_wait_duration
#define orig_side                        DATASTRUCT._orig_side
#define stat__net_current_netmask        DATASTRUCT._stat__net_current_netmask
#define V92_EVENT__XX_RECEIVED           DATASTRUCT._V92_EVENT__XX_RECEIVED
#define V34_S_SIGNAL_DEGREE_WIDTH        DATASTRUCT._V34_S_SIGNAL_DEGREE_WIDTH
#define f0q_s                            DATASTRUCT._f0q_s
#define fsk_TONE_toneadjust              DATASTRUCT._fsk_TONE_toneadjust
#define ipod_htd_fbdnt_semaphore         DATASTRUCT._ipod_htd_fbdnt_semaphore
#define input_sample_energy_log          DATASTRUCT._input_sample_energy_log
#define impedance_monitor_coefs          DATASTRUCT._impedance_monitor_coefs
#define ipbx_announce_ip_address_index   DATASTRUCT._ipbx_announce_ip_address_index
#define v34h_tx_m_ijk_ring_index_pointer DATASTRUCT._v34h_tx_m_ijk_ring_index_pointer
#define stat__led_slow_flash_state       DATASTRUCT._stat__led_slow_flash_state
#define send__v8__gstn_access            DATASTRUCT._send__v8__gstn_access
#define equalizer_coef_complex           DATASTRUCT._equalizer_coef_complex
#define v92_frame_rx_bits_per_baud       DATASTRUCT._v92_frame_rx_bits_per_baud
#define ph2n_probing_adj_Wlo             DATASTRUCT._ph2n_probing_adj_Wlo
#define parm__net_assigned_cloned_mac_address DATASTRUCT._parm__net_assigned_cloned_mac_address
#define parm__mbx_dma_timeout            DATASTRUCT._parm__mbx_dma_timeout
#define ANSam_min_tracking_count         DATASTRUCT._ANSam_min_tracking_count
#define ipod_msg_tx_bfi                  DATASTRUCT._ipod_msg_tx_bfi
#define threshold_aa                     DATASTRUCT._threshold_aa
#define stat__sip_global_keep_alive_address DATASTRUCT._stat__sip_global_keep_alive_address
#define threshold_ac                     DATASTRUCT._threshold_ac
#define cc_tx_rate_poffset               DATASTRUCT._cc_tx_rate_poffset
#define stat__nat_snd_rtp_end_point      DATASTRUCT._stat__nat_snd_rtp_end_point
#define old_speech                       DATASTRUCT._old_speech
#define ec_fast_shift_slew_remote        DATASTRUCT._ec_fast_shift_slew_remote
#define f0q_mem_s                        DATASTRUCT._f0q_mem_s
#define shadow_caller_name               DATASTRUCT._shadow_caller_name
#define rf_fm_last_word                  DATASTRUCT._rf_fm_last_word
#define PH2P_FEFO_DW_K_GAIN_MARGIN       DATASTRUCT._PH2P_FEFO_DW_K_GAIN_MARGIN
#define parm__net_router_circuit_default_dial_retry DATASTRUCT._parm__net_router_circuit_default_dial_retry
#define DIL_probing_pad_out_table        DATASTRUCT._DIL_probing_pad_out_table
#define tone_pattern_count               DATASTRUCT._tone_pattern_count
#define ph2n_probing_adj_Wme             DATASTRUCT._ph2n_probing_adj_Wme
#define v34_rx_qn_save1_coef_imag32      DATASTRUCT._v34_rx_qn_save1_coef_imag32
#define p18_reversal_timeout             DATASTRUCT._p18_reversal_timeout
#define jitter_min_freq                  DATASTRUCT._jitter_min_freq
#define parm__mse_limit1                 DATASTRUCT._parm__mse_limit1
#define first_time_npp                   DATASTRUCT._first_time_npp
#define parm__mse_limit2                 DATASTRUCT._parm__mse_limit2
#define pcm_rx_interpolator_buffer       DATASTRUCT._pcm_rx_interpolator_buffer
#define v34_frame_rx_bit_buffer          DATASTRUCT._v34_frame_rx_bit_buffer
#define parm__radio_transmit_test_tone_enable DATASTRUCT._parm__radio_transmit_test_tone_enable
#define ph2_tx_data_size                 DATASTRUCT._ph2_tx_data_size
#define ph2n_tx_carrier                  DATASTRUCT._ph2n_tx_carrier
#define parm__nat_timeout_fragment       DATASTRUCT._parm__nat_timeout_fragment
#define v34h_rx_L_over_4_1_size          DATASTRUCT._v34h_rx_L_over_4_1_size
#define cc_rx_ANAL_prev_DC_angle         DATASTRUCT._cc_rx_ANAL_prev_DC_angle
#define dtmf_detect_valid                DATASTRUCT._dtmf_detect_valid
#define stat__nat_wan_alg_delivers       DATASTRUCT._stat__nat_wan_alg_delivers
#define from_fax                         DATASTRUCT._from_fax
#define v8_tx_QC_repeat_count            DATASTRUCT._v8_tx_QC_repeat_count
#define v92n_rx_SUVu_body                DATASTRUCT._v92n_rx_SUVu_body
#define dcd_diversion_on_limit           DATASTRUCT._dcd_diversion_on_limit
#define parm__phone_memory_card_read_enable DATASTRUCT._parm__phone_memory_card_read_enable
#define sdt_data_buffer_imag             DATASTRUCT._sdt_data_buffer_imag
#define v90h_rx_residue                  DATASTRUCT._v90h_rx_residue
#define v92_rx_gain_adjust_exponent      DATASTRUCT._v92_rx_gain_adjust_exponent
#define rx_interpolator_buffer_imag      DATASTRUCT._rx_interpolator_buffer_imag
#define ph2n_tx_2800_option              DATASTRUCT._ph2n_tx_2800_option
#define ph2p_fefo_dw_k_buffer_scaled32   DATASTRUCT._ph2p_fefo_dw_k_buffer_scaled32
#define train_on_data_256_slew           DATASTRUCT._train_on_data_256_slew
#define v90_tx_k_output_offset           DATASTRUCT._v90_tx_k_output_offset
#define stat__dm_state                   DATASTRUCT._stat__dm_state
#define parm__ata_admin_name             DATASTRUCT._parm__ata_admin_name
#define fg_kernel                        DATASTRUCT._fg_kernel
#define rate_reduction_poffset           DATASTRUCT._rate_reduction_poffset
#define mgcp_sock_buffer                 DATASTRUCT._mgcp_sock_buffer
#define content_parser_error             DATASTRUCT._content_parser_error
#define parm__ooma_key_repeat_time       DATASTRUCT._parm__ooma_key_repeat_time
#define v92n_tx_train_8pt                DATASTRUCT._v92n_tx_train_8pt
#define rate_seq_counter                 DATASTRUCT._rate_seq_counter
#define parm__ipbx_distinctive_ring_last_call_service DATASTRUCT._parm__ipbx_distinctive_ring_last_call_service
#define lec__td_error                    DATASTRUCT._lec__td_error
#define v92n_tx_CPd_body_constel         DATASTRUCT._v92n_tx_CPd_body_constel
#define ptloop_2nd_order_slew            DATASTRUCT._ptloop_2nd_order_slew
#define pcm_HI_peak_MSE_max              DATASTRUCT._pcm_HI_peak_MSE_max
#define ph2p_anal_variance_CS_table      DATASTRUCT._ph2p_anal_variance_CS_table
#define weightdenum_ilbc                 DATASTRUCT._weightdenum_ilbc
#define constel_midpoints_table_rbs      DATASTRUCT._constel_midpoints_table_rbs
#define v34h_rx_b_bits_per_mapping_frame DATASTRUCT._v34h_rx_b_bits_per_mapping_frame
#define v34n_rxtx_call_direction         DATASTRUCT._v34n_rxtx_call_direction
#define dprmbx_outgoing_queue            DATASTRUCT._dprmbx_outgoing_queue
#define mem_zero                         DATASTRUCT._mem_zero
#define ph4n_rx_answer_to_call_maxrate   DATASTRUCT._ph4n_rx_answer_to_call_maxrate
#define parm__codec_disconnect_tone_3_enable DATASTRUCT._parm__codec_disconnect_tone_3_enable
#define fsk_local_interpolator_poffset   DATASTRUCT._fsk_local_interpolator_poffset
#define vppn_device_vanished_debounce    DATASTRUCT._vppn_device_vanished_debounce
#define parm__sdp_AVT_codec_dyn_pt       DATASTRUCT._parm__sdp_AVT_codec_dyn_pt
#define lsp_new_ptr                      DATASTRUCT._lsp_new_ptr
#define g726_enc_coding                  DATASTRUCT._g726_enc_coding
#define v34f_eqc_co_DC_imag              DATASTRUCT._v34f_eqc_co_DC_imag
#define ph2n_rx_v92_mode_bits            DATASTRUCT._ph2n_rx_v92_mode_bits
#define number_bg_tasks                  DATASTRUCT._number_bg_tasks
#define parm__audio_monitor_tx_enable    DATASTRUCT._parm__audio_monitor_tx_enable
#define ec_ytrain_shift_slew_local       DATASTRUCT._ec_ytrain_shift_slew_local
#define constellation_real               DATASTRUCT._constellation_real
#define parm__ipbx_call_ring_default_tone DATASTRUCT._parm__ipbx_call_ring_default_tone
#define asm_decode_within_bad_frame      DATASTRUCT._asm_decode_within_bad_frame
#define ph2n_tx_acknowledge              DATASTRUCT._ph2n_tx_acknowledge
#define lec__td_coef                     DATASTRUCT._lec__td_coef
#define v34_TRN1_agc_value               DATASTRUCT._v34_TRN1_agc_value
#define parm__net_debug_dsp_enable       DATASTRUCT._parm__net_debug_dsp_enable
#define within_task_update               DATASTRUCT._within_task_update
#define v90_frame_rx_index               DATASTRUCT._v90_frame_rx_index
#define stat__nat_wan_forwards           DATASTRUCT._stat__nat_wan_forwards
#define v92_system_ID_echo_DC_level      DATASTRUCT._v92_system_ID_echo_DC_level
#define minspec_counter                  DATASTRUCT._minspec_counter
#define rxs_aux_rx_baud                  DATASTRUCT._rxs_aux_rx_baud
#define parm__voip_melp_encode_rate      DATASTRUCT._parm__voip_melp_encode_rate
#define asm_decode_sample_unpack_mask    DATASTRUCT._asm_decode_sample_unpack_mask
#define ph2p_fefo_ar_ai_stage1_buffer32  DATASTRUCT._ph2p_fefo_ar_ai_stage1_buffer32
#define parm__mgcp_default_user_name     DATASTRUCT._parm__mgcp_default_user_name
#define parm__voip_preferred_codecs      DATASTRUCT._parm__voip_preferred_codecs
#define dpbx_led_special_on_pattern      DATASTRUCT._dpbx_led_special_on_pattern
#define parm__sdp_g726_24_codec_name     DATASTRUCT._parm__sdp_g726_24_codec_name
#define speech_direct_playback_frame_size DATASTRUCT._speech_direct_playback_frame_size
#define g168_tx_cng_iir_data_buffer      DATASTRUCT._g168_tx_cng_iir_data_buffer
#define phasedet_test_phase              DATASTRUCT._phasedet_test_phase
#define demod_leading_real               DATASTRUCT._demod_leading_real
#define stat__picp_dtmf_tone_on          DATASTRUCT._stat__picp_dtmf_tone_on
#define parm__net_lan_heartbeat_signal_enable DATASTRUCT._parm__net_lan_heartbeat_signal_enable
#define enh_i                            DATASTRUCT._enh_i
#define g711a_plc_frame_size             DATASTRUCT._g711a_plc_frame_size
#define l_noise_gain                     DATASTRUCT._l_noise_gain
#define v34s_retrain_from_data_flag      DATASTRUCT._v34s_retrain_from_data_flag
#define angle_1st_data_predicted         DATASTRUCT._angle_1st_data_predicted
#define ener                             DATASTRUCT._ener
#define parm__faxdet_ced_decrement       DATASTRUCT._parm__faxdet_ced_decrement
#define stat__ipod_chan_id               DATASTRUCT._stat__ipod_chan_id
#define count_update                     DATASTRUCT._count_update
#define v90_rx_delay_poffset             DATASTRUCT._v90_rx_delay_poffset
#define mgcp_all_endpoints_call          DATASTRUCT._mgcp_all_endpoints_call
#define v34n_tx_trellis_setting          DATASTRUCT._v34n_tx_trellis_setting
#define dtmf_row_harmonic                DATASTRUCT._dtmf_row_harmonic
#define v90_rx_R_expected_energy         DATASTRUCT._v90_rx_R_expected_energy
#define v92_frame_rx_state               DATASTRUCT._v92_frame_rx_state
#define ph4n_tx_ITU_reserved             DATASTRUCT._ph4n_tx_ITU_reserved
#define v34_rx_qn_hat_buffer_imag        DATASTRUCT._v34_rx_qn_hat_buffer_imag
#define constel_input0                   DATASTRUCT._constel_input0
#define constel_input1                   DATASTRUCT._constel_input1
#define v90_tx_s_value                   DATASTRUCT._v90_tx_s_value
#define constel_input2                   DATASTRUCT._constel_input2
#define lec__td_data_poffset             DATASTRUCT._lec__td_data_poffset
#define constel_input3                   DATASTRUCT._constel_input3
#define sonitrol_remote_audio_port       DATASTRUCT._sonitrol_remote_audio_port
#define agc_2_lpf_width                  DATASTRUCT._agc_2_lpf_width
#define parm__ipbx_polarity_connect      DATASTRUCT._parm__ipbx_polarity_connect
#define parm__net_router_rip             DATASTRUCT._parm__net_router_rip
#define rxs_demod_half_real              DATASTRUCT._rxs_demod_half_real
#define faxdet_value_ced                 DATASTRUCT._faxdet_value_ced
#define v90_rx_dil_count                 DATASTRUCT._v90_rx_dil_count
#define degree_limit                     DATASTRUCT._degree_limit
#define parm__ipbx_led_message_waiting   DATASTRUCT._parm__ipbx_led_message_waiting
#define lec__tec_update                  DATASTRUCT._lec__tec_update
#define monitor_input_data               DATASTRUCT._monitor_input_data
#define parm__ipbx_fc_outgoing_block_disable DATASTRUCT._parm__ipbx_fc_outgoing_block_disable
#define v34_tx_xn_remote_imag            DATASTRUCT._v34_tx_xn_remote_imag
#define asm_encode_rtp_cng_prev          DATASTRUCT._asm_encode_rtp_cng_prev
#define v34h_rx_aux_restore_flag         DATASTRUCT._v34h_rx_aux_restore_flag
#define picp_feature                     DATASTRUCT._picp_feature
#define pcm_rx_8K0_transfer_buffer       DATASTRUCT._pcm_rx_8K0_transfer_buffer
#define stat__ipbx_device_state          DATASTRUCT._stat__ipbx_device_state
#define rx_interpolator_buffer           DATASTRUCT._rx_interpolator_buffer
#define v90n_rxtx_v90_enable             DATASTRUCT._v90n_rxtx_v90_enable
#define dev_rx_frame_index               DATASTRUCT._dev_rx_frame_index
#define v34n_rx_receive_level            DATASTRUCT._v34n_rx_receive_level
#define ph1n_rx_index_QTS                DATASTRUCT._ph1n_rx_index_QTS
#define l_disp_del                       DATASTRUCT._l_disp_del
#define v90n_rx_nominal_power            DATASTRUCT._v90n_rx_nominal_power
#define pcm_rx_AGC2_log_adjust           DATASTRUCT._pcm_rx_AGC2_log_adjust
#define count_sil                        DATASTRUCT._count_sil
#define parm__mgcp_nat_keep_alive_enable DATASTRUCT._parm__mgcp_nat_keep_alive_enable
#define parm__nat_block_anonymous_probing DATASTRUCT._parm__nat_block_anonymous_probing
#define g_voicedEn                       DATASTRUCT._g_voicedEn
#define prev_uv_fsmag                    DATASTRUCT._prev_uv_fsmag
#define parm__speech_enc_asm_addr        DATASTRUCT._parm__speech_enc_asm_addr
#define g_bitNum                         DATASTRUCT._g_bitNum
#define parm__ipbx_call_holding_tone     DATASTRUCT._parm__ipbx_call_holding_tone
#define v90_dpcm_dil_ref                 DATASTRUCT._v90_dpcm_dil_ref
#define parm__mf_tone                    DATASTRUCT._parm__mf_tone
#define sense_silence_lpf2_32            DATASTRUCT._sense_silence_lpf2_32
#define parm__mpeg2_sendto_port          DATASTRUCT._parm__mpeg2_sendto_port
#define ANSam_sample_count               DATASTRUCT._ANSam_sample_count
#define dpbx_led_pattern_queue_out       DATASTRUCT._dpbx_led_pattern_queue_out
#define asm_decode_packet_type           DATASTRUCT._asm_decode_packet_type
#define parm__ctcss_dec_enable           DATASTRUCT._parm__ctcss_dec_enable
#define stat__rx_v34_symbol_rate         DATASTRUCT._stat__rx_v34_symbol_rate
#define gpf_iloop_length                 DATASTRUCT._gpf_iloop_length
#define noise_gain_melp_syn              DATASTRUCT._noise_gain_melp_syn
#define uicp_access                      DATASTRUCT._uicp_access
#define parm__ipbx_warm_line_duration    DATASTRUCT._parm__ipbx_warm_line_duration
#define V34_TRN2_MSE_STACK_COUNT         DATASTRUCT._V34_TRN2_MSE_STACK_COUNT
#define pcm_ec_limit                     DATASTRUCT._pcm_ec_limit
#define tx_wr_index                      DATASTRUCT._tx_wr_index
#define l_melp_v_cb_size                 DATASTRUCT._l_melp_v_cb_size
#define parm__rtp_stream                 DATASTRUCT._parm__rtp_stream
#define sdt_data_buffer_complex          DATASTRUCT._sdt_data_buffer_complex
#define ipbx_call_hold                   DATASTRUCT._ipbx_call_hold
#define dgidet_tune_max_spacing          DATASTRUCT._dgidet_tune_max_spacing
#define nb_ener                          DATASTRUCT._nb_ener
#define mg_run_entry_pointer             DATASTRUCT._mg_run_entry_pointer
#define ANSam_trace_mid_real             DATASTRUCT._ANSam_trace_mid_real
#define cc_tx_rate_counter               DATASTRUCT._cc_tx_rate_counter
#define parm__ipbx_call_back_service     DATASTRUCT._parm__ipbx_call_back_service
#define g_bitBufSize                     DATASTRUCT._g_bitBufSize
#define v90_frame_rx_cp_body_start       DATASTRUCT._v90_frame_rx_cp_body_start
#define dtmf_packet_on                   DATASTRUCT._dtmf_packet_on
#define gip                              DATASTRUCT._gip
#define parm__codec_disconnect_tone_2_duration DATASTRUCT._parm__codec_disconnect_tone_2_duration
#define giq                              DATASTRUCT._giq
#define lec__nlp_quiet_counter           DATASTRUCT._lec__nlp_quiet_counter
#define parm__net_assigned_router_name   DATASTRUCT._parm__net_assigned_router_name
#define phone_power_switch_debounce_count DATASTRUCT._phone_power_switch_debounce_count
#define parm__speech_ip_generic_info     DATASTRUCT._parm__speech_ip_generic_info
#define bpfdelout                        DATASTRUCT._bpfdelout
#define parm__ipbx_message_waiting_ring_splash_tone DATASTRUCT._parm__ipbx_message_waiting_ring_splash_tone
#define v92h_rx_K_frame                  DATASTRUCT._v92h_rx_K_frame
#define ata_check_boot                   DATASTRUCT._ata_check_boot
#define asm_decode_lb_started            DATASTRUCT._asm_decode_lb_started
#define g711a_plc_poverlap               DATASTRUCT._g711a_plc_poverlap
#define decode_frame_size                DATASTRUCT._decode_frame_size
#define parm__speech_ip_source_addr      DATASTRUCT._parm__speech_ip_source_addr
#define stat__phone_ptt_state            DATASTRUCT._stat__phone_ptt_state
#define parm__tripwire_monitor_length    DATASTRUCT._parm__tripwire_monitor_length
#define stat__nat_rcv_forwards           DATASTRUCT._stat__nat_rcv_forwards
#define phasedet_cos_value               DATASTRUCT._phasedet_cos_value
#define g711a_plc_buffer_out             DATASTRUCT._g711a_plc_buffer_out
#define parm__orc_ip_address             DATASTRUCT._parm__orc_ip_address
#define current_output_imag              DATASTRUCT._current_output_imag
#define g711_rx_vad_level_mean_msw       DATASTRUCT._g711_rx_vad_level_mean_msw
#define v34_tx_pn_remote_real            DATASTRUCT._v34_tx_pn_remote_real
#define dcd_diversion_off_limit          DATASTRUCT._dcd_diversion_off_limit
#define equalizer_coef_real32            DATASTRUCT._equalizer_coef_real32
#define encode_frame_sample_counter      DATASTRUCT._encode_frame_sample_counter
#define phone_headset_tx_volume          DATASTRUCT._phone_headset_tx_volume
#define stat__audio_codec_model          DATASTRUCT._stat__audio_codec_model
#define detect_rate_reduce_counter       DATASTRUCT._detect_rate_reduce_counter
#define v34_renego_prev_real             DATASTRUCT._v34_renego_prev_real
#define modulator_increment              DATASTRUCT._modulator_increment
#define lookback_codeword                DATASTRUCT._lookback_codeword
#define parm__camera_baud_rate           DATASTRUCT._parm__camera_baud_rate
#define lec__peak_activity_counter       DATASTRUCT._lec__peak_activity_counter
#define speech_plcpc_data                DATASTRUCT._speech_plcpc_data
#define ph2_rx_checker_bpf_offset        DATASTRUCT._ph2_rx_checker_bpf_offset
#define PH2S_INFO0_ACK_LIMIT             DATASTRUCT._PH2S_INFO0_ACK_LIMIT
#define goertzel_buffer                  DATASTRUCT._goertzel_buffer
#define fsk_local_interpolator_buffer_gain DATASTRUCT._fsk_local_interpolator_buffer_gain
#define parm__pcm_playback_intro_bufferp DATASTRUCT._parm__pcm_playback_intro_bufferp
#define stat__net_enet_wtol_passthrough  DATASTRUCT._stat__net_enet_wtol_passthrough
#define parm__ipbx_fc_call_waiting_disable DATASTRUCT._parm__ipbx_fc_call_waiting_disable
#define g711_rx_vad_level_kf             DATASTRUCT._g711_rx_vad_level_kf
#define v34_rx_trellis_s_2m_1_table      DATASTRUCT._v34_rx_trellis_s_2m_1_table
#define ANSAM_MAGNITUDE_LIMIT            DATASTRUCT._ANSAM_MAGNITUDE_LIMIT
#define parm__sdp_gsm_fr_codec_name      DATASTRUCT._parm__sdp_gsm_fr_codec_name
#define pushed_equalizer_poffset         DATASTRUCT._pushed_equalizer_poffset
#define parm__speech_rtp_encode_audio_packet_type DATASTRUCT._parm__speech_rtp_encode_audio_packet_type
#define fax_error_mse32                  DATASTRUCT._fax_error_mse32
#define v34n_tx_required_gain            DATASTRUCT._v34n_tx_required_gain
#define postLPFOutHis_hi                 DATASTRUCT._postLPFOutHis_hi
#define shared_btlz_tx_index             DATASTRUCT._shared_btlz_tx_index
#define pcm_btr_gain_normalize           DATASTRUCT._pcm_btr_gain_normalize
#define parm__nat_timeout_tcp_closed     DATASTRUCT._parm__nat_timeout_tcp_closed
#define g711_rx_vad_level_kr             DATASTRUCT._g711_rx_vad_level_kr
#define v34n_rx_inverse_gain_adjust      DATASTRUCT._v34n_rx_inverse_gain_adjust
#define ph2n_rx_lo_3200_option           DATASTRUCT._ph2n_rx_lo_3200_option
#define rate_reduction_counter           DATASTRUCT._rate_reduction_counter
#define dt_active_change                 DATASTRUCT._dt_active_change
#define asm_encode_rtp_dtmf_start        DATASTRUCT._asm_encode_rtp_dtmf_start
#define dcd_integration_time             DATASTRUCT._dcd_integration_time
#define pold_scores                      DATASTRUCT._pold_scores
#define phase_hit_count                  DATASTRUCT._phase_hit_count
#define parm__dm_v32_rate_en_mask        DATASTRUCT._parm__dm_v32_rate_en_mask
#define stat__v92_upstream_robbed_bit_mask DATASTRUCT._stat__v92_upstream_robbed_bit_mask
#define fract_output_real                DATASTRUCT._fract_output_real
#define parm__ipbx_fc_distinctive_ring_enable DATASTRUCT._parm__ipbx_fc_distinctive_ring_enable
#define baud_xx_data                     DATASTRUCT._baud_xx_data
#define v90n_tx_RBS_positions            DATASTRUCT._v90n_tx_RBS_positions
#define V34S_LEN_8K0_SPECIAL_LOCAL_TRAIN DATASTRUCT._V34S_LEN_8K0_SPECIAL_LOCAL_TRAIN
#define parm__speech_ip_dest_addr        DATASTRUCT._parm__speech_ip_dest_addr
#define ph2_rx_checker_length            DATASTRUCT._ph2_rx_checker_length
#define lec__datamax_buffer              DATASTRUCT._lec__datamax_buffer
#define debug_host_buffer_chars          DATASTRUCT._debug_host_buffer_chars
#define ANSam_midpoint_value             DATASTRUCT._ANSam_midpoint_value
#define eqout_leading_delay_real         DATASTRUCT._eqout_leading_delay_real
#define v34_rx_cn_imag                   DATASTRUCT._v34_rx_cn_imag
#define g711a_plc_erase_sample_cnt       DATASTRUCT._g711a_plc_erase_sample_cnt
#define dgidet_padrb_max_index           DATASTRUCT._dgidet_padrb_max_index
#define v34n_rx_probing_maxrate          DATASTRUCT._v34n_rx_probing_maxrate
#define parm__dtmf_tone_off_time         DATASTRUCT._parm__dtmf_tone_off_time
#define parm__speech_rtp_dtmf_en         DATASTRUCT._parm__speech_rtp_dtmf_en
#define l_lsp_check                      DATASTRUCT._l_lsp_check
#define decode_frame_error_indication    DATASTRUCT._decode_frame_error_indication
#define v90n_rxtx_coding_law             DATASTRUCT._v90n_rxtx_coding_law
#define FALL_catastrophic_flag           DATASTRUCT._FALL_catastrophic_flag
#define v17_capture_rate                 DATASTRUCT._v17_capture_rate
#define decision_pcm_output              DATASTRUCT._decision_pcm_output
#define v34_tx_zn_remote_real            DATASTRUCT._v34_tx_zn_remote_real
#define sart_rx_size                     DATASTRUCT._sart_rx_size
#define ORIG_V8_CM_COUNT_NOM             DATASTRUCT._ORIG_V8_CM_COUNT_NOM
#define cc_rx_ANAL_BEn_real              DATASTRUCT._cc_rx_ANAL_BEn_real
#define v34_TRN2_MSE_value               DATASTRUCT._v34_TRN2_MSE_value
#define notch_datax32_120                DATASTRUCT._notch_datax32_120
#define sonitrol_ANI_DNIS_offset         DATASTRUCT._sonitrol_ANI_DNIS_offset
#define v90n_rx_Uinfo_ucode              DATASTRUCT._v90n_rx_Uinfo_ucode
#define picp_list                        DATASTRUCT._picp_list
#define V34_AB_SIGNAL_MIN_ENERGY         DATASTRUCT._V34_AB_SIGNAL_MIN_ENERGY
#define ipod_command_low_line_quality    DATASTRUCT._ipod_command_low_line_quality
#define ec_very_slow_slew                DATASTRUCT._ec_very_slow_slew
#define parm__ata_phone_lock_enable      DATASTRUCT._parm__ata_phone_lock_enable
#define v34s_reneg_test_resp_ignore_S    DATASTRUCT._v34s_reneg_test_resp_ignore_S
#define parm__priority_pattern           DATASTRUCT._parm__priority_pattern
#define parm__pcm_playback_loop_mode     DATASTRUCT._parm__pcm_playback_loop_mode
#define tx_clock_phase_local             DATASTRUCT._tx_clock_phase_local
#define v90_frame_tx_cpt_body_start      DATASTRUCT._v90_frame_tx_cpt_body_start
#define decode_first_frame               DATASTRUCT._decode_first_frame
#define silenceEn                        DATASTRUCT._silenceEn
#define previous_call_id_index           DATASTRUCT._previous_call_id_index
#define parm__ata_configuration_update_on_reset DATASTRUCT._parm__ata_configuration_update_on_reset
#define PH2P_POWR_NOISE_ADJ_EXPONENT     DATASTRUCT._PH2P_POWR_NOISE_ADJ_EXPONENT
#define ph2n_rx_transmit_attenuation     DATASTRUCT._ph2n_rx_transmit_attenuation
#define V90_RX_RETRAIN_Et_THRESHOLD      DATASTRUCT._V90_RX_RETRAIN_Et_THRESHOLD
#define pcm_ec_total_taps                DATASTRUCT._pcm_ec_total_taps
#define fg_event_insert                  DATASTRUCT._fg_event_insert
#define v34h_rx_z8_table                 DATASTRUCT._v34h_rx_z8_table
#define V34S_AGC_1_SETTLE_TIME           DATASTRUCT._V34S_AGC_1_SETTLE_TIME
#define saa7115_globalptr                DATASTRUCT._saa7115_globalptr
#define v34n_rx_asymmetric_option        DATASTRUCT._v34n_rx_asymmetric_option
#define default_w0                       DATASTRUCT._default_w0
#define asm_decode_default_frame_size    DATASTRUCT._asm_decode_default_frame_size
#define parm__mgcp_nat_keep_alive_interval DATASTRUCT._parm__mgcp_nat_keep_alive_interval
#define V34_S_SIGNAL_2T_LIMIT            DATASTRUCT._V34_S_SIGNAL_2T_LIMIT
#define rx_rate_conv_offset              DATASTRUCT._rx_rate_conv_offset
#define pcm_tx_power_log_prev            DATASTRUCT._pcm_tx_power_log_prev
#define parm__sart_rx_mode               DATASTRUCT._parm__sart_rx_mode
#define asm_stream_fill_cnt              DATASTRUCT._asm_stream_fill_cnt
#define detect_v21_detect_biquad_data    DATASTRUCT._detect_v21_detect_biquad_data
#define parm__pcm_playback_mode          DATASTRUCT._parm__pcm_playback_mode
#define V34_S_SIGNAL_MIN_ENERGY          DATASTRUCT._V34_S_SIGNAL_MIN_ENERGY
#define ph2_tx_passband_buffer           DATASTRUCT._ph2_tx_passband_buffer
#define sh_sumAcf                        DATASTRUCT._sh_sumAcf
#define pcm_LO_MSE_value                 DATASTRUCT._pcm_LO_MSE_value
#define parm__ipbx_speed_dial_service    DATASTRUCT._parm__ipbx_speed_dial_service
#define ph2_guard_counter                DATASTRUCT._ph2_guard_counter
#define v92_system_ID_codes              DATASTRUCT._v92_system_ID_codes
#define ec_xtrain_shift_slew_local       DATASTRUCT._ec_xtrain_shift_slew_local
#define pattern_type                     DATASTRUCT._pattern_type
#define v34_rx_yn_tilde_real             DATASTRUCT._v34_rx_yn_tilde_real
#define v90n_parm_v90_enable             DATASTRUCT._v90n_parm_v90_enable
#define tone_priority_series             DATASTRUCT._tone_priority_series
#define shadow_line_sniff                DATASTRUCT._shadow_line_sniff
#define ph2p_anal_log_E_plus_start       DATASTRUCT._ph2p_anal_log_E_plus_start
#define stat__nat_wan_non_end_point      DATASTRUCT._stat__nat_wan_non_end_point
#define next_rand_minstdgen              DATASTRUCT._next_rand_minstdgen
#define p18_2100_notch_poffset           DATASTRUCT._p18_2100_notch_poffset
#define previous_sign                    DATASTRUCT._previous_sign
#define ph2n_rx_hi_3200_option           DATASTRUCT._ph2n_rx_hi_3200_option
#define stat__nat_wan_ttl_discard        DATASTRUCT._stat__nat_wan_ttl_discard
#define cp_previous                      DATASTRUCT._cp_previous
#define parm__sip_ringing_retransmit     DATASTRUCT._parm__sip_ringing_retransmit
#define sdt_bit_delay_buffer             DATASTRUCT._sdt_bit_delay_buffer
#define PH2P_ANAL_TEST_REQUIRED_GAIN     DATASTRUCT._PH2P_ANAL_TEST_REQUIRED_GAIN
#define v34h_tx_J_super_frame_size_x2    DATASTRUCT._v34h_tx_J_super_frame_size_x2
#define v90_rx_timeout_count             DATASTRUCT._v90_rx_timeout_count
#define v90n_parm_rx_reneg_16pt_option   DATASTRUCT._v90n_parm_rx_reneg_16pt_option
#define ph2p_anal_preemph6_pointer       DATASTRUCT._ph2p_anal_preemph6_pointer
#define parm__sdp_AVT_codec_name         DATASTRUCT._parm__sdp_AVT_codec_name
#define parm__ipbx_fxs_cid_retry_count   DATASTRUCT._parm__ipbx_fxs_cid_retry_count
#define postLPFOutHis_lo                 DATASTRUCT._postLPFOutHis_lo
#define nat_free_list                    DATASTRUCT._nat_free_list
#define parm__dtmf_col_2nd_harm          DATASTRUCT._parm__dtmf_col_2nd_harm
#define parm__dtmf_rel_rev_twist         DATASTRUCT._parm__dtmf_rel_rev_twist
#define ec_medium_slew                   DATASTRUCT._ec_medium_slew
#define pcm_error_lpf_buffer             DATASTRUCT._pcm_error_lpf_buffer
#define sart_rx_release                  DATASTRUCT._sart_rx_release
#define v90_frame_rx_dil_body_ucode      DATASTRUCT._v90_frame_rx_dil_body_ucode
#define stat__nat_snd_broadcasts         DATASTRUCT._stat__nat_snd_broadcasts
#define v34h_rx_K_number_shell_bits      DATASTRUCT._v34h_rx_K_number_shell_bits
#define parm__ipbx_fc_caller_redial      DATASTRUCT._parm__ipbx_fc_caller_redial
#define pcm_x_law_encode_routine         DATASTRUCT._pcm_x_law_encode_routine
#define cc_rx_cx_real                    DATASTRUCT._cc_rx_cx_real
#define v34_pp_equalized_data_poffset    DATASTRUCT._v34_pp_equalized_data_poffset
#define parm__fxpmp_modulation_code      DATASTRUCT._parm__fxpmp_modulation_code
#define v34h_rx_g4_table                 DATASTRUCT._v34h_rx_g4_table
#define parm__ipbx_three_way_conference_service DATASTRUCT._parm__ipbx_three_way_conference_service
#define parm__sip_incoming_auth_password DATASTRUCT._parm__sip_incoming_auth_password
#define parm__speech_dtmf_min_duration   DATASTRUCT._parm__speech_dtmf_min_duration
#define ANSam_count_2100                 DATASTRUCT._ANSam_count_2100
#define fax_save_state_0                 DATASTRUCT._fax_save_state_0
#define fax_save_state_1                 DATASTRUCT._fax_save_state_1
#define v32_rx_lpf_buffer                DATASTRUCT._v32_rx_lpf_buffer
#define gci_tx_frame_abort               DATASTRUCT._gci_tx_frame_abort
#define v34h_baud_tx_flag_previous       DATASTRUCT._v34h_baud_tx_flag_previous
#define ph2_dummy_loopback_sample        DATASTRUCT._ph2_dummy_loopback_sample
#define V34S_LEN_8K0_1RT_MAX_1ST_SHORT   DATASTRUCT._V34S_LEN_8K0_1RT_MAX_1ST_SHORT
#define stat__call_progress_tone_detect_mask DATASTRUCT._stat__call_progress_tone_detect_mask
#define ph2p_anal_variance_01_table      DATASTRUCT._ph2p_anal_variance_01_table
#define asm_decode_type                  DATASTRUCT._asm_decode_type
#define ipbx_call_conference             DATASTRUCT._ipbx_call_conference
#define v34_tx_s_n                       DATASTRUCT._v34_tx_s_n
#define v92n_tx_constel_index            DATASTRUCT._v92n_tx_constel_index
#define parm__pulse_delay_time           DATASTRUCT._parm__pulse_delay_time
#define cp_state                         DATASTRUCT._cp_state
#define sonitrol_line_sniff              DATASTRUCT._sonitrol_line_sniff
#define act_min_shift                    DATASTRUCT._act_min_shift
#define vppn_device_temporary_id_index   DATASTRUCT._vppn_device_temporary_id_index
#define DIL_probing_pad_in_table         DATASTRUCT._DIL_probing_pad_in_table
#define fsk_TONE_increment               DATASTRUCT._fsk_TONE_increment
#define l_guard                          DATASTRUCT._l_guard
#define v17_short_seg2_length            DATASTRUCT._v17_short_seg2_length
#define ph2p_fefo_powr_SE_gain_adjust    DATASTRUCT._ph2p_fefo_powr_SE_gain_adjust
#define ph2p_fefo_delta_buffer32         DATASTRUCT._ph2p_fefo_delta_buffer32
#define echo_correlation                 DATASTRUCT._echo_correlation
#define affine_update_poffset            DATASTRUCT._affine_update_poffset
#define tx_clock_phase_slave             DATASTRUCT._tx_clock_phase_slave
#define saved_v90trn_shift               DATASTRUCT._saved_v90trn_shift
#define ph2p_anal_maxrates_13_table      DATASTRUCT._ph2p_anal_maxrates_13_table
#define dev_message_pointer              DATASTRUCT._dev_message_pointer
#define prev_pcof                        DATASTRUCT._prev_pcof
#define sample_rx_buffer                 DATASTRUCT._sample_rx_buffer
#define ph2_ac_lpf_data_buffer32         DATASTRUCT._ph2_ac_lpf_data_buffer32
#define parm__ipbx_message_waiting_service DATASTRUCT._parm__ipbx_message_waiting_service
#define parm__sip_local_port             DATASTRUCT._parm__sip_local_port
#define V34_BE_POWER_SLEW                DATASTRUCT._V34_BE_POWER_SLEW
#define fsk_local_interpolator_buffer    DATASTRUCT._fsk_local_interpolator_buffer
#define v17_coef_phase                   DATASTRUCT._v17_coef_phase
#define ANSW_V8_JM_COUNT_NOM             DATASTRUCT._ANSW_V8_JM_COUNT_NOM
#define v34s_retrigger_retrain           DATASTRUCT._v34s_retrigger_retrain
#define parm__video_encoding_mode        DATASTRUCT._parm__video_encoding_mode
#define threshold_s1                     DATASTRUCT._threshold_s1
#define v34_frame_tx_bit_pointer         DATASTRUCT._v34_frame_tx_bit_pointer
#define threshold_s2                     DATASTRUCT._threshold_s2
#define both_up                          DATASTRUCT._both_up
#define sys_number_missed_8K0_samples    DATASTRUCT._sys_number_missed_8K0_samples
#define parm__mgcp_public_external_ip_address DATASTRUCT._parm__mgcp_public_external_ip_address
#define ph2_AB_zero_count                DATASTRUCT._ph2_AB_zero_count
#define V34_SLEW_SIN_RETRAIN             DATASTRUCT._V34_SLEW_SIN_RETRAIN
#define mbx__htod                        DATASTRUCT._mbx__htod
#define legacy_tx_in                     DATASTRUCT._legacy_tx_in
#define rd_energy_detect                 DATASTRUCT._rd_energy_detect
#define v34_resync_count                 DATASTRUCT._v34_resync_count
#define parm__ipbx_fc_caller_id_outbound_enable DATASTRUCT._parm__ipbx_fc_caller_id_outbound_enable
#define sart_rx_buffer                   DATASTRUCT._sart_rx_buffer
#define V34_BE2_SLEW_FAST                DATASTRUCT._V34_BE2_SLEW_FAST
#define v92n_rx_max_coefs_section        DATASTRUCT._v92n_rx_max_coefs_section
#define ata_update_time_code             DATASTRUCT._ata_update_time_code
#define parm__nat_stun_enable            DATASTRUCT._parm__nat_stun_enable
#define cc_rx_S_repetition_limit         DATASTRUCT._cc_rx_S_repetition_limit
#define stat__nat_snd_pptp               DATASTRUCT._stat__nat_snd_pptp
#define parm__slac_ring_amplitude        DATASTRUCT._parm__slac_ring_amplitude
#define encode_bit_data_pointer          DATASTRUCT._encode_bit_data_pointer
#define V34S_RENEG_RESP_T_S_TO_SN_TIMEOUT DATASTRUCT._V34S_RENEG_RESP_T_S_TO_SN_TIMEOUT
#define parm__tripwire_jpeg_record       DATASTRUCT._parm__tripwire_jpeg_record
#define number_fg_states                 DATASTRUCT._number_fg_states
#define parm__ata_ftp_server_enable      DATASTRUCT._parm__ata_ftp_server_enable
#define notch_datax32_180                DATASTRUCT._notch_datax32_180
#define parm__ipbx_hangup_silence_duration DATASTRUCT._parm__ipbx_hangup_silence_duration
#define enc_lsp_new                      DATASTRUCT._enc_lsp_new
#define rate_conv_modulo_counter         DATASTRUCT._rate_conv_modulo_counter
#define equalizer_coef_imag32            DATASTRUCT._equalizer_coef_imag32
#define parm__ipbx_input_pattern_pstn    DATASTRUCT._parm__ipbx_input_pattern_pstn
#define v90n_parm_coding_law             DATASTRUCT._v90n_parm_coding_law
#define v17_short_enable                 DATASTRUCT._v17_short_enable
#define parm__ata_current_time           DATASTRUCT._parm__ata_current_time
#define ph1_x_law_index_to_code_convert  DATASTRUCT._ph1_x_law_index_to_code_convert
#define send_message_count               DATASTRUCT._send_message_count
#define state0_save_decimation_limit     DATASTRUCT._state0_save_decimation_limit
#define v34_rx_yn_perfect_real_32        DATASTRUCT._v34_rx_yn_perfect_real_32
#define V34_PRE_LO_EQUALIZER_COEFS       DATASTRUCT._V34_PRE_LO_EQUALIZER_COEFS
#define speech_direct_playback_function  DATASTRUCT._speech_direct_playback_function
#define noisespect                       DATASTRUCT._noisespect
#define crc_tx_flush_flag                DATASTRUCT._crc_tx_flush_flag
#define V34_RXI_PLL_COUNT                DATASTRUCT._V34_RXI_PLL_COUNT
#define agc_2_normal_slew                DATASTRUCT._agc_2_normal_slew
#define dpbx_led_pattern                 DATASTRUCT._dpbx_led_pattern
#define baud_tx_delete_bit_count         DATASTRUCT._baud_tx_delete_bit_count
#define ethernet_SPP_tx_queue            DATASTRUCT._ethernet_SPP_tx_queue
#define ph2p_anal_log_S_buffer           DATASTRUCT._ph2p_anal_log_S_buffer
#define AGC_2_REFERENCE_LEVEL            DATASTRUCT._AGC_2_REFERENCE_LEVEL
#define parm__sdp_gsm_amr_codec_dyn_pt   DATASTRUCT._parm__sdp_gsm_amr_codec_dyn_pt
#define threshold_sf                     DATASTRUCT._threshold_sf
#define pcm_btr_equalized_prev           DATASTRUCT._pcm_btr_equalized_prev
#define v34n_parm_hi_carrier_option      DATASTRUCT._v34n_parm_hi_carrier_option
#define parm__nat_dmz_host_ip_addr       DATASTRUCT._parm__nat_dmz_host_ip_addr
#define pcm_btr_perfect_prev             DATASTRUCT._pcm_btr_perfect_prev
#define THD_measurement_compare          DATASTRUCT._THD_measurement_compare
#define ipod_ms_timer                    DATASTRUCT._ipod_ms_timer
#define dcd_energy_x                     DATASTRUCT._dcd_energy_x
#define lec__rx_suppressor_incr          DATASTRUCT._lec__rx_suppressor_incr
#define dcd_energy_y                     DATASTRUCT._dcd_energy_y
#define energy_receive_log               DATASTRUCT._energy_receive_log
#define ptloop_monitor_count             DATASTRUCT._ptloop_monitor_count
#define stat__nat_snd_ip_tunnel          DATASTRUCT._stat__nat_snd_ip_tunnel
#define ph2_guard_tone_gain              DATASTRUCT._ph2_guard_tone_gain
#define V34_BE2_SLEW_MEDIUM              DATASTRUCT._V34_BE2_SLEW_MEDIUM
#define g723_CodCng                      DATASTRUCT._g723_CodCng
#define speech_direct_playback_data      DATASTRUCT._speech_direct_playback_data
#define baud_tx_parity_even_space        DATASTRUCT._baud_tx_parity_even_space
#define v90_frame_rx_save_bit_parse_pointer DATASTRUCT._v90_frame_rx_save_bit_parse_pointer
#define ipod_command_max_fax_rate        DATASTRUCT._ipod_command_max_fax_rate
#define v34h_rx_m_count_4D               DATASTRUCT._v34h_rx_m_count_4D
#define nat_lan_ifp                      DATASTRUCT._nat_lan_ifp
#define lec__tx_suppressor_decr          DATASTRUCT._lec__tx_suppressor_decr
#define ata_need_cfg                     DATASTRUCT._ata_need_cfg
#define ph2_guard_tone_phase             DATASTRUCT._ph2_guard_tone_phase
#define control_message                  DATASTRUCT._control_message
#define descrambler32                    DATASTRUCT._descrambler32
#define legacy_periodic_count            DATASTRUCT._legacy_periodic_count
#define pcm_ec_routine                   DATASTRUCT._pcm_ec_routine
#define v34n_tx_qn_coef_imag             DATASTRUCT._v34n_tx_qn_coef_imag
#define parm__ipbx_alternate_dial_tone   DATASTRUCT._parm__ipbx_alternate_dial_tone
#define ph2n_probing_Whi                 DATASTRUCT._ph2n_probing_Whi
#define ph2p_powr_L1_to_L2_delay_offset  DATASTRUCT._ph2p_powr_L1_to_L2_delay_offset
#define v29_nrm_mse                      DATASTRUCT._v29_nrm_mse
#define v34s_reneg_test_noise_level      DATASTRUCT._v34s_reneg_test_noise_level
#define parm__net_router_globalstar_script DATASTRUCT._parm__net_router_globalstar_script
#define trellis_equ_error_cnt            DATASTRUCT._trellis_equ_error_cnt
#define v34h_tx_last_e0_pointer          DATASTRUCT._v34h_tx_last_e0_pointer
#define lec__delay_size                  DATASTRUCT._lec__delay_size
#define temporary_buffer                 DATASTRUCT._temporary_buffer
#define modulator_offset                 DATASTRUCT._modulator_offset
#define affine_poffset_delay1            DATASTRUCT._affine_poffset_delay1
#define affine_poffset_delay2            DATASTRUCT._affine_poffset_delay2
#define parm__codec_caller_id_type_2_mode DATASTRUCT._parm__codec_caller_id_type_2_mode
#define parm__ata_timeserver_domain_name DATASTRUCT._parm__ata_timeserver_domain_name
#define v34_slew_cos_BE                  DATASTRUCT._v34_slew_cos_BE
#define debug_LEC__DELAY_SIZE            DATASTRUCT._debug_LEC__DELAY_SIZE
#define legacy_audio_transition_expected DATASTRUCT._legacy_audio_transition_expected
#define correct_precoder_imag            DATASTRUCT._correct_precoder_imag
#define parm__g722_reset_flag            DATASTRUCT._parm__g722_reset_flag
#define ph4n_tx_receive_nonlinear        DATASTRUCT._ph4n_tx_receive_nonlinear
#define error_real                       DATASTRUCT._error_real
#define picp_saved_digit                 DATASTRUCT._picp_saved_digit
#define ph2p_anal_maxrates_CS_pointer    DATASTRUCT._ph2p_anal_maxrates_CS_pointer
#define speech_overlap                   DATASTRUCT._speech_overlap
#define v90n_tx_receive_shaping_a1       DATASTRUCT._v90n_tx_receive_shaping_a1
#define v90n_tx_receive_shaping_a2       DATASTRUCT._v90n_tx_receive_shaping_a2
#define v34_pp_equalized_data_imag       DATASTRUCT._v34_pp_equalized_data_imag
#define stat__net_enet_snd_broadcasts    DATASTRUCT._stat__net_enet_snd_broadcasts
#define speex_bits                       DATASTRUCT._speex_bits
#define v34_CONV_agc_value               DATASTRUCT._v34_CONV_agc_value
#define faxdet_v21_cnt                   DATASTRUCT._faxdet_v21_cnt
#define dprmbx_catastrophic_failure      DATASTRUCT._dprmbx_catastrophic_failure
#define fsk_storage                      DATASTRUCT._fsk_storage
#define temp1_ilbc_buffer                DATASTRUCT._temp1_ilbc_buffer
#define parm__mpeg4_target_bit_rate      DATASTRUCT._parm__mpeg4_target_bit_rate
#define answ_v8_CJ_count                 DATASTRUCT._answ_v8_CJ_count
#define sart_rx_timeout_tmr              DATASTRUCT._sart_rx_timeout_tmr
#define agc_2_lpf                        DATASTRUCT._agc_2_lpf
#define stat__test_phone_key_register    DATASTRUCT._stat__test_phone_key_register
#define v34_rx_qn_buffer_real            DATASTRUCT._v34_rx_qn_buffer_real
#define v90_rx_p_frame                   DATASTRUCT._v90_rx_p_frame
#define parm__net_dhcp_server_broadcast_enable DATASTRUCT._parm__net_dhcp_server_broadcast_enable
#define v92n_rx_INFO1a_body              DATASTRUCT._v92n_rx_INFO1a_body
#define V90S_LEN_T_DIL_PROCESS_BLOCK     DATASTRUCT._V90S_LEN_T_DIL_PROCESS_BLOCK
#define v92_rx_Ru_pattern_buffer         DATASTRUCT._v92_rx_Ru_pattern_buffer
#define local_interpolator_buffer        DATASTRUCT._local_interpolator_buffer
#define parm__sip_remote_port            DATASTRUCT._parm__sip_remote_port
#define dec_old_exc                      DATASTRUCT._dec_old_exc
#define force_low_line_semaphore         DATASTRUCT._force_low_line_semaphore
#define holdbuff                         DATASTRUCT._holdbuff
#define parm__codec_disconnect_voltage_duration DATASTRUCT._parm__codec_disconnect_voltage_duration
#define v34n_rx_data_rate_option         DATASTRUCT._v34n_rx_data_rate_option
#define v90n_tx_receive_shaping_b1       DATASTRUCT._v90n_tx_receive_shaping_b1
#define v90n_tx_receive_shaping_b2       DATASTRUCT._v90n_tx_receive_shaping_b2
#define echo_canceller_display_decimate  DATASTRUCT._echo_canceller_display_decimate
#define parm__voip_echo_canceller_enable DATASTRUCT._parm__voip_echo_canceller_enable
#define mem_syn                          DATASTRUCT._mem_syn
#define test_tone_increment              DATASTRUCT._test_tone_increment
#define lec__delay_buffer                DATASTRUCT._lec__delay_buffer
#define v90h_rx_write_enable             DATASTRUCT._v90h_rx_write_enable
#define lookback_base                    DATASTRUCT._lookback_base
#define g_bitBufSize12                   DATASTRUCT._g_bitBufSize12
#define previous_rx_baud                 DATASTRUCT._previous_rx_baud
#define amrsync_struct                   DATASTRUCT._amrsync_struct
#define fsk_ANSam_phase                  DATASTRUCT._fsk_ANSam_phase
#define parm__ata_configuration_update_enable DATASTRUCT._parm__ata_configuration_update_enable
#define v34_rx_predicted_V0_m_value      DATASTRUCT._v34_rx_predicted_V0_m_value
#define silence_passband_buffer          DATASTRUCT._silence_passband_buffer
#define lec__coef_buffer                 DATASTRUCT._lec__coef_buffer
#define v34h_rx_shaper_shellmap_routine  DATASTRUCT._v34h_rx_shaper_shellmap_routine
#define stat__nat_wan_udp                DATASTRUCT._stat__nat_wan_udp
#define v90h_tx_buffer                   DATASTRUCT._v90h_tx_buffer
#define phase_loop_real                  DATASTRUCT._phase_loop_real
#define parm__ipbx_input_error_tone      DATASTRUCT._parm__ipbx_input_error_tone
#define v34_frame_rx_sync_register       DATASTRUCT._v34_frame_rx_sync_register
#define saved_v90trn_pad_detect          DATASTRUCT._saved_v90trn_pad_detect
#define descrambler_output_shift         DATASTRUCT._descrambler_output_shift
#define decode_gain_exponent             DATASTRUCT._decode_gain_exponent
#define monitor_ones_cntr                DATASTRUCT._monitor_ones_cntr
#define prev_sbp3                        DATASTRUCT._prev_sbp3
#define v34_MSE_stack                    DATASTRUCT._v34_MSE_stack
#define V90_APCM_DIL_LENGTH              DATASTRUCT._V90_APCM_DIL_LENGTH
#define v90_frame_rx_dil_body_sp         DATASTRUCT._v90_frame_rx_dil_body_sp
#define current_bg_task                  DATASTRUCT._current_bg_task
#define parm__speech_rtp_cng_delay       DATASTRUCT._parm__speech_rtp_cng_delay
#define speech_direct_playback_fcnt      DATASTRUCT._speech_direct_playback_fcnt
#define g_bitBufSize24                   DATASTRUCT._g_bitBufSize24
#define lec__alpha_calculation_ratio     DATASTRUCT._lec__alpha_calculation_ratio
#define v34h_rx_control_hi_frame         DATASTRUCT._v34h_rx_control_hi_frame
#define p18_exponent                     DATASTRUCT._p18_exponent
#define v90n_rx_constel_codec            DATASTRUCT._v90n_rx_constel_codec
#define ph2n_probing_L2_log_P_buffer     DATASTRUCT._ph2n_probing_L2_log_P_buffer
#define parm__tone_detectors             DATASTRUCT._parm__tone_detectors
#define stat__phone_power_switch_state   DATASTRUCT._stat__phone_power_switch_state
#define v34h_rx_control_lo_frame         DATASTRUCT._v34h_rx_control_lo_frame
#define lsp_cos                          DATASTRUCT._lsp_cos
#define ph2p_anal_preemph_results_pointer DATASTRUCT._ph2p_anal_preemph_results_pointer
#define prev_uv_low_rate_chn_read        DATASTRUCT._prev_uv_low_rate_chn_read
#define ph2n_tx_lo_3000_option           DATASTRUCT._ph2n_tx_lo_3000_option
#define DIL_calculation_pad_gain         DATASTRUCT._DIL_calculation_pad_gain
#define v34_rx_4D_indicator              DATASTRUCT._v34_rx_4D_indicator
#define ph2n_probing_Wlo                 DATASTRUCT._ph2n_probing_Wlo
#define dgi_in0                          DATASTRUCT._dgi_in0
#define v90n_rx_constel_codes            DATASTRUCT._v90n_rx_constel_codes
#define v90_frame_rx_dil_body_tp         DATASTRUCT._v90_frame_rx_dil_body_tp
#define dgi_in1                          DATASTRUCT._dgi_in1
#define dgi_in2                          DATASTRUCT._dgi_in2
#define pattern_counter                  DATASTRUCT._pattern_counter
#define fax_pause_length                 DATASTRUCT._fax_pause_length
#define V34_RX_CARRIER_FREQUENCY         DATASTRUCT._V34_RX_CARRIER_FREQUENCY
#define jitter_jitter_limit              DATASTRUCT._jitter_jitter_limit
#define ptloop_anti_oscillation_slew     DATASTRUCT._ptloop_anti_oscillation_slew
#define parm__sdp_NSE_codec_dyn_pt       DATASTRUCT._parm__sdp_NSE_codec_dyn_pt
#define parm__rtp_decode_gain            DATASTRUCT._parm__rtp_decode_gain
#define PH2P_ANAL_DEMOD_ENERGY_LOSS      DATASTRUCT._PH2P_ANAL_DEMOD_ENERGY_LOSS
#define gpf_RLexp                        DATASTRUCT._gpf_RLexp
#define parm__v8__gstn_access            DATASTRUCT._parm__v8__gstn_access
#define rd_energy_on_time                DATASTRUCT._rd_energy_on_time
#define parm__radio_key_selection        DATASTRUCT._parm__radio_key_selection
#define fsk_run_data_sart                DATASTRUCT._fsk_run_data_sart
#define parm__lec_nlp_control            DATASTRUCT._parm__lec_nlp_control
#define pcm_rx_8K0_transfer_out_poffset  DATASTRUCT._pcm_rx_8K0_transfer_out_poffset
#define dev_ring_minimum_duration        DATASTRUCT._dev_ring_minimum_duration
#define ph2_rx_baud_shift_register       DATASTRUCT._ph2_rx_baud_shift_register
#define ph2n_probing_Wme                 DATASTRUCT._ph2n_probing_Wme
#define decode_input_imag                DATASTRUCT._decode_input_imag
#define gx_s                             DATASTRUCT._gx_s
#define in_v32                           DATASTRUCT._in_v32
#define V90_TEST_LOG_INPUT_TIMING        DATASTRUCT._V90_TEST_LOG_INPUT_TIMING
#define encode_frame_start_timestamp     DATASTRUCT._encode_frame_start_timestamp
#define v34n_tx_difference_option        DATASTRUCT._v34n_tx_difference_option
#define send__v8__protocols              DATASTRUCT._send__v8__protocols
#define parm__dtmf_detector_count        DATASTRUCT._parm__dtmf_detector_count
#define sonitrol_bad_checksum_count      DATASTRUCT._sonitrol_bad_checksum_count
#define pcm_probe_real                   DATASTRUCT._pcm_probe_real
#define status_buffer                    DATASTRUCT._status_buffer
#define lec__controller_count            DATASTRUCT._lec__controller_count
#define parm__ata_admin_password         DATASTRUCT._parm__ata_admin_password
#define parm__vppn_device_firmware_image DATASTRUCT._parm__vppn_device_firmware_image
#define asm_decode_within_frame          DATASTRUCT._asm_decode_within_frame
#define audio_device                     DATASTRUCT._audio_device
#define codewd74                         DATASTRUCT._codewd74
#define fr_cur                           DATASTRUCT._fr_cur
#define rx_rate_double_poffset           DATASTRUCT._rx_rate_double_poffset
#define vppn_device_memory_read          DATASTRUCT._vppn_device_memory_read
#define lsp_new_q                        DATASTRUCT._lsp_new_q
#define v34n_parm_auxiliary_option       DATASTRUCT._v34n_parm_auxiliary_option
#define v92_MH_response_ack_flag         DATASTRUCT._v92_MH_response_ack_flag
#define parm__ipbx_call_return_service   DATASTRUCT._parm__ipbx_call_return_service
#define convert_agc_2_input_log          DATASTRUCT._convert_agc_2_input_log
#define timeout_sema                     DATASTRUCT._timeout_sema
#define parm__dpbx_led_ringing_or_waiting DATASTRUCT._parm__dpbx_led_ringing_or_waiting
#define parm__ipbx_polarity_dial_done    DATASTRUCT._parm__ipbx_polarity_dial_done
#define aux_tx_data                      DATASTRUCT._aux_tx_data
#define ph2_rx_data_size_1               DATASTRUCT._ph2_rx_data_size_1
#define V34_RXI_PLL_HALF_ADJUST          DATASTRUCT._V34_RXI_PLL_HALF_ADJUST
#define parm__video_ssl_enable           DATASTRUCT._parm__video_ssl_enable
#define handset_in_sample                DATASTRUCT._handset_in_sample
#define dgidet_padrb_count               DATASTRUCT._dgidet_padrb_count
#define v92_equalizer_input              DATASTRUCT._v92_equalizer_input
#define codewd84                         DATASTRUCT._codewd84
#define v90_rx_predicted_point           DATASTRUCT._v90_rx_predicted_point
#define demod_half_real                  DATASTRUCT._demod_half_real
#define event_dsp_uses_background        DATASTRUCT._event_dsp_uses_background
#define parm__sdp_g729_codec_dyn_pt      DATASTRUCT._parm__sdp_g729_codec_dyn_pt
#define parm__ata_local_update_domain_name DATASTRUCT._parm__ata_local_update_domain_name
#define parm__ata_firmware_failed_message DATASTRUCT._parm__ata_firmware_failed_message
#define parm__speech_g729parm_bitrev     DATASTRUCT._parm__speech_g729parm_bitrev
#define l_pulse_cof                      DATASTRUCT._l_pulse_cof
#define parm__mgcp_endpoint_naming       DATASTRUCT._parm__mgcp_endpoint_naming
#define p18_poffset                      DATASTRUCT._p18_poffset
#define parm__ipbx_call_pstn_ring_default DATASTRUCT._parm__ipbx_call_pstn_ring_default
#define pcm_rx_2k_phase                  DATASTRUCT._pcm_rx_2k_phase
#define stat__phone_paycard_state        DATASTRUCT._stat__phone_paycard_state
#define parm__ata_provider_lock_expiration DATASTRUCT._parm__ata_provider_lock_expiration
#define tst_saved_2k_dif                 DATASTRUCT._tst_saved_2k_dif
#define rx_freerun_clock_phase           DATASTRUCT._rx_freerun_clock_phase
#define stat__speech_dec_sample_counter  DATASTRUCT._stat__speech_dec_sample_counter
#define v29_rot_mse_32                   DATASTRUCT._v29_rot_mse_32
#define jitter_1st_order_slew            DATASTRUCT._jitter_1st_order_slew
#define pcm_tx_thread_control            DATASTRUCT._pcm_tx_thread_control
#define tdv_index                        DATASTRUCT._tdv_index
#define v34_tx_qn_pointer                DATASTRUCT._v34_tx_qn_pointer
#define faxdet_threshold_absolute        DATASTRUCT._faxdet_threshold_absolute
#define equalizer_raw_output_imag        DATASTRUCT._equalizer_raw_output_imag
#define force_train_imag                 DATASTRUCT._force_train_imag
#define saved_v90trn_offset              DATASTRUCT._saved_v90trn_offset
#define ph2n_tx_hi_3000_option           DATASTRUCT._ph2n_tx_hi_3000_option
#define PH2S_LEN_T_TURNAROUND_DELAY      DATASTRUCT._PH2S_LEN_T_TURNAROUND_DELAY
#define parm__codec_audio_clamp_duration DATASTRUCT._parm__codec_audio_clamp_duration
#define v90_frame_tx_codec               DATASTRUCT._v90_frame_tx_codec
#define lim_r                            DATASTRUCT._lim_r
#define RCoeff                           DATASTRUCT._RCoeff
#define nat_private_addr                 DATASTRUCT._nat_private_addr
#define pcm_ec_conv_buffer40             DATASTRUCT._pcm_ec_conv_buffer40
#define automode_modulation_state        DATASTRUCT._automode_modulation_state
#define tmp_baud_sum_imag                DATASTRUCT._tmp_baud_sum_imag
#define parm__vpcm_nominal_power         DATASTRUCT._parm__vpcm_nominal_power
#define v34p_bg_sample_count             DATASTRUCT._v34p_bg_sample_count
#define prev_uv_flag                     DATASTRUCT._prev_uv_flag
#define v90_frame_tx_codes               DATASTRUCT._v90_frame_tx_codes
#define prev_par_transcode               DATASTRUCT._prev_par_transcode
#define v34_rx_xn_hat_imag               DATASTRUCT._v34_rx_xn_hat_imag
#define v92n_tx_CPd_body_modulus         DATASTRUCT._v92n_tx_CPd_body_modulus
#define v92_system_ID_error_adj          DATASTRUCT._v92_system_ID_error_adj
#define v90h_rx_buffer_load_pointer      DATASTRUCT._v90h_rx_buffer_load_pointer
#define codec_int_state                  DATASTRUCT._codec_int_state
#define nat_remote_addr                  DATASTRUCT._nat_remote_addr
#define ph2n_rx_v92_ITU_marks_reserved   DATASTRUCT._ph2n_rx_v92_ITU_marks_reserved
#define test_input_chang                 DATASTRUCT._test_input_chang
#define predicted_rx_xn_B1_P_x8          DATASTRUCT._predicted_rx_xn_B1_P_x8
#define v34_tx_cn_imag                   DATASTRUCT._v34_tx_cn_imag
#define speech_direct_record_function    DATASTRUCT._speech_direct_record_function
#define ph2p_bg_dlyd64_out_offset        DATASTRUCT._ph2p_bg_dlyd64_out_offset
#define vocoder_f                        DATASTRUCT._vocoder_f
#define V34_SLEW_SIN_BE2                 DATASTRUCT._V34_SLEW_SIN_BE2
#define codec_control_word               DATASTRUCT._codec_control_word
#define parm__ipbx_call_back_ring_splash_tone DATASTRUCT._parm__ipbx_call_back_ring_splash_tone
#define equalized_complex                DATASTRUCT._equalized_complex
#define tx_8K0_echo_sample               DATASTRUCT._tx_8K0_echo_sample
#define ph2n_probing_use_shaping         DATASTRUCT._ph2n_probing_use_shaping
#define ph2p_anal_log_P_buffer           DATASTRUCT._ph2p_anal_log_P_buffer
#define delta_level                      DATASTRUCT._delta_level
#define parm__selcall_enc_gain           DATASTRUCT._parm__selcall_enc_gain
#define v34_rx_qn_perfect_buffer_imag    DATASTRUCT._v34_rx_qn_perfect_buffer_imag
#define prev_gain_err                    DATASTRUCT._prev_gain_err
#define btrec_phdet_state                DATASTRUCT._btrec_phdet_state
#define lec__dc_offset32                 DATASTRUCT._lec__dc_offset32
#define v34_scheduled_retrain_in_seconds DATASTRUCT._v34_scheduled_retrain_in_seconds
#define parm__slac_caller_id_type_2_mode DATASTRUCT._parm__slac_caller_id_type_2_mode
#define stat__net_enet_snd_success       DATASTRUCT._stat__net_enet_snd_success
#define nat_arp_target                   DATASTRUCT._nat_arp_target
#define sart_rx_data_unit_1              DATASTRUCT._sart_rx_data_unit_1
#define sart_rx_data_unit_2              DATASTRUCT._sart_rx_data_unit_2
#define v34s_run_holdoff_count           DATASTRUCT._v34s_run_holdoff_count
#define p18_data_buffer_real             DATASTRUCT._p18_data_buffer_real
#define v17_seg1_length                  DATASTRUCT._v17_seg1_length
#define txs_output_sample                DATASTRUCT._txs_output_sample
#define asm_encode_rtp_ans_start         DATASTRUCT._asm_encode_rtp_ans_start
#define ipod_rx_frame_report_seqnum      DATASTRUCT._ipod_rx_frame_report_seqnum
#define v34n_rx_receive_gain             DATASTRUCT._v34n_rx_receive_gain
#define dev_timed_event_period           DATASTRUCT._dev_timed_event_period
#define parm__sip_additional_accept_types DATASTRUCT._parm__sip_additional_accept_types
#define ph2_retrain_flag                 DATASTRUCT._ph2_retrain_flag
#define legacy_tx_out                    DATASTRUCT._legacy_tx_out
#define ANSam_trace_magphase_mid_imag    DATASTRUCT._ANSam_trace_magphase_mid_imag
#define ipod_msg_rx_vfd                  DATASTRUCT._ipod_msg_rx_vfd
#define baud_rx_parity_stick             DATASTRUCT._baud_rx_parity_stick
#define v34_equalizer_agc_gain32         DATASTRUCT._v34_equalizer_agc_gain32
#define decode_bit_data_pointer          DATASTRUCT._decode_bit_data_pointer
#define ph2n_rx_preeq_gain               DATASTRUCT._ph2n_rx_preeq_gain
#define mem_lpc                          DATASTRUCT._mem_lpc
#define parm__ipbx_voice_tx_gain         DATASTRUCT._parm__ipbx_voice_tx_gain
#define v34_rx_trellis_yn_poffset        DATASTRUCT._v34_rx_trellis_yn_poffset
#define pcm_probe_ecc_state              DATASTRUCT._pcm_probe_ecc_state
#define v34_equalizer_slew_data_slow     DATASTRUCT._v34_equalizer_slew_data_slow
#define u_tmp                            DATASTRUCT._u_tmp
#define legacy_rx_ack_sent               DATASTRUCT._legacy_rx_ack_sent
#define stat__net_pppoe_status           DATASTRUCT._stat__net_pppoe_status
#define asm_decode_cnt                   DATASTRUCT._asm_decode_cnt
#define v92_system_ID_code               DATASTRUCT._v92_system_ID_code
#define ethernet_outgoing_count_flag     DATASTRUCT._ethernet_outgoing_count_flag
#define v27_tx_poly                      DATASTRUCT._v27_tx_poly
#define v90_rx_s_input_offset            DATASTRUCT._v90_rx_s_input_offset
#define fax_save_state_current           DATASTRUCT._fax_save_state_current
#define dev_tx_frame                     DATASTRUCT._dev_tx_frame
#define dtmf_hpf_biquad_data             DATASTRUCT._dtmf_hpf_biquad_data
#define v34n_parm_error_recovery_enable  DATASTRUCT._v34n_parm_error_recovery_enable
#define nat_public_addr                  DATASTRUCT._nat_public_addr
#define stat__sart_tx_mode               DATASTRUCT._stat__sart_tx_mode
#define ph2p_fefo_test_m_prime32         DATASTRUCT._ph2p_fefo_test_m_prime32
#define predicted_rx_xn_B1_disable       DATASTRUCT._predicted_rx_xn_B1_disable
#define impedance_monitor_decimation_counter DATASTRUCT._impedance_monitor_decimation_counter
#define SPP_incoming_queue               DATASTRUCT._SPP_incoming_queue
#define stat__daa_debounce_count         DATASTRUCT._stat__daa_debounce_count
#define stat__nat_rcv_tcp                DATASTRUCT._stat__nat_rcv_tcp
#define ph2n_rx_Uinfo_ucode              DATASTRUCT._ph2n_rx_Uinfo_ucode
#define pcm_tx_hpf_fb32                  DATASTRUCT._pcm_tx_hpf_fb32
#define ph2n_rx_tx_3429_option           DATASTRUCT._ph2n_rx_tx_3429_option
#define in_dtmf_early_detect             DATASTRUCT._in_dtmf_early_detect
#define tonemute_delay_poffset           DATASTRUCT._tonemute_delay_poffset
#define audio_agc_data                   DATASTRUCT._audio_agc_data
#define cp_keep_counter                  DATASTRUCT._cp_keep_counter
#define rx_interpolator_buffer_complex   DATASTRUCT._rx_interpolator_buffer_complex
#define parm__mgcp_distinctive_ring_names DATASTRUCT._parm__mgcp_distinctive_ring_names
#define vppn_decode_packet               DATASTRUCT._vppn_decode_packet
#define less_count                       DATASTRUCT._less_count
#define fg_svalue_queue                  DATASTRUCT._fg_svalue_queue
#define v34_temp_hi_pre_emph_adjust_table DATASTRUCT._v34_temp_hi_pre_emph_adjust_table
#define v34s_last_frame_was_an_MPA       DATASTRUCT._v34s_last_frame_was_an_MPA
#define dev_compare_pointer              DATASTRUCT._dev_compare_pointer
#define g168_exc_peak                    DATASTRUCT._g168_exc_peak
#define sample_tx_buffer                 DATASTRUCT._sample_tx_buffer
#define parm__sdp_g726_40_codec_dyn_pt   DATASTRUCT._parm__sdp_g726_40_codec_dyn_pt
#define pcm_HI_peak_MSE_stack            DATASTRUCT._pcm_HI_peak_MSE_stack
#define local_interpolator_buffer_real   DATASTRUCT._local_interpolator_buffer_real
#define parm__rtp_dtmf_playout_digit     DATASTRUCT._parm__rtp_dtmf_playout_digit
#define v34n_data_rate_MAXIMUM           DATASTRUCT._v34n_data_rate_MAXIMUM
#define stat__net_enet_rcv_success       DATASTRUCT._stat__net_enet_rcv_success
#define sonitrol_current_ring_count      DATASTRUCT._sonitrol_current_ring_count
#define phasedet_sin_value               DATASTRUCT._phasedet_sin_value
#define v90h_rx_buffer_stream_pointer    DATASTRUCT._v90h_rx_buffer_stream_pointer
#define rate_validation_cmp              DATASTRUCT._rate_validation_cmp
#define v21_detect_coefs_buffer_internal DATASTRUCT._v21_detect_coefs_buffer_internal
#define picp_lcd_display_save_buffer     DATASTRUCT._picp_lcd_display_save_buffer
#define tempmse                          DATASTRUCT._tempmse
#define v34_rx_trellis_yn_hat_poffset    DATASTRUCT._v34_rx_trellis_yn_hat_poffset
#define echo_canceller_poffset           DATASTRUCT._echo_canceller_poffset
#define parm__vppn_device_firmware_length DATASTRUCT._parm__vppn_device_firmware_length
#define sart_tx_buffer                   DATASTRUCT._sart_tx_buffer
#define parm__mf_tone_on_time            DATASTRUCT._parm__mf_tone_on_time
#define good_pitch                       DATASTRUCT._good_pitch
#define v90_dpcm_dil_first               DATASTRUCT._v90_dpcm_dil_first
#define v92n_rx_prefilter_fb_taps        DATASTRUCT._v92n_rx_prefilter_fb_taps
#define v34_yn_equalized_imag            DATASTRUCT._v34_yn_equalized_imag
#define parm__tel_digit                  DATASTRUCT._parm__tel_digit
#define btrec_baud_coef_shift            DATASTRUCT._btrec_baud_coef_shift
#define bg_timer_list                    DATASTRUCT._bg_timer_list
#define next_80_ms                       DATASTRUCT._next_80_ms
#define v34n_rx_use_shaping              DATASTRUCT._v34n_rx_use_shaping
#define saturation                       DATASTRUCT._saturation
#define parm__speech_dec_asm_addr        DATASTRUCT._parm__speech_dec_asm_addr
#define nat_pkt_icmp_ptr                 DATASTRUCT._nat_pkt_icmp_ptr
#define parm__ipbx_line_enable           DATASTRUCT._parm__ipbx_line_enable
#define V34_B_OVER_CK80                  DATASTRUCT._V34_B_OVER_CK80
#define parm__codec_disconnect_tone_2_bandwidth DATASTRUCT._parm__codec_disconnect_tone_2_bandwidth
#define vppn_device_command_send_end     DATASTRUCT._vppn_device_command_send_end
#define v34_frame_tx_word_count          DATASTRUCT._v34_frame_tx_word_count
#define v90_rx_JE_detect_count           DATASTRUCT._v90_rx_JE_detect_count
#define rd_trans2_count                  DATASTRUCT._rd_trans2_count
#define parm__codec_port_tx_gain         DATASTRUCT._parm__codec_port_tx_gain
#define overlay_8K0_timeout              DATASTRUCT._overlay_8K0_timeout
#define ph2n_probing_receive_preeq_level DATASTRUCT._ph2n_probing_receive_preeq_level
#define nat_ip_header_size               DATASTRUCT._nat_ip_header_size
#define parm__ipbx_call_forward_ring_splash_tone DATASTRUCT._parm__ipbx_call_forward_ring_splash_tone
#define cc_rx_equalizer_coef_real        DATASTRUCT._cc_rx_equalizer_coef_real
#define v34h_rx_residue_length           DATASTRUCT._v34h_rx_residue_length
#define ipod_dth_coded_speech_length     DATASTRUCT._ipod_dth_coded_speech_length
#define monitor_decimation_limit         DATASTRUCT._monitor_decimation_limit
#define parm__ipbx_dial_speed_dial       DATASTRUCT._parm__ipbx_dial_speed_dial
#define stat__ipod_mod_type              DATASTRUCT._stat__ipod_mod_type
#define parm__nat_turn_server_domain_name DATASTRUCT._parm__nat_turn_server_domain_name
#define v34s_reneg_test_init_ignore_S    DATASTRUCT._v34s_reneg_test_init_ignore_S
#define v34n_parm_sample_ec_update_increment DATASTRUCT._v34n_parm_sample_ec_update_increment
#define remote_ec_shift_slew             DATASTRUCT._remote_ec_shift_slew
#define lec__datamax_half_counter        DATASTRUCT._lec__datamax_half_counter
#define parm__speech_rtp_flow_tag        DATASTRUCT._parm__speech_rtp_flow_tag
#define add_deletes_per_baud             DATASTRUCT._add_deletes_per_baud
#define parm__ipbx_fc_reserved_90        DATASTRUCT._parm__ipbx_fc_reserved_90
#define parm__ipbx_fc_reserved_91        DATASTRUCT._parm__ipbx_fc_reserved_91
#define stat__net_enet_rcv_errors        DATASTRUCT._stat__net_enet_rcv_errors
#define v34h_tx_L_over_4_1_size          DATASTRUCT._v34h_tx_L_over_4_1_size
#define cp_active_change                 DATASTRUCT._cp_active_change
#define v92_rx_yn_perfect                DATASTRUCT._v92_rx_yn_perfect
#define parm__ipbx_fc_reserved_99        DATASTRUCT._parm__ipbx_fc_reserved_99
#define g711_rx_vad_hangover_counter     DATASTRUCT._g711_rx_vad_hangover_counter
#define demod_lagging_half_real          DATASTRUCT._demod_lagging_half_real
#define v34f_eqc_initial_DC_mag_log      DATASTRUCT._v34f_eqc_initial_DC_mag_log
#define enc_past_qua_en                  DATASTRUCT._enc_past_qua_en
#define i_gain                           DATASTRUCT._i_gain
#define ph4n_tx_acknowledge              DATASTRUCT._ph4n_tx_acknowledge
#define v34_frame_rx_bit_parse_pointer   DATASTRUCT._v34_frame_rx_bit_parse_pointer
#define v34_rx_trellis_s_2m_0_table      DATASTRUCT._v34_rx_trellis_s_2m_0_table
#define mark_counter                     DATASTRUCT._mark_counter
#define v34_rx_qn_tilde_buffer_imag      DATASTRUCT._v34_rx_qn_tilde_buffer_imag
#define equalizer_slew_resync_fast       DATASTRUCT._equalizer_slew_resync_fast
#define stat__ipod_loopback_pattern      DATASTRUCT._stat__ipod_loopback_pattern
#define cc_rx_rate_poffset               DATASTRUCT._cc_rx_rate_poffset
#define stat__ipod_dth_coder             DATASTRUCT._stat__ipod_dth_coder
#define timeout_clock                    DATASTRUCT._timeout_clock
#define fg_status_event_queue            DATASTRUCT._fg_status_event_queue
#define parm__net_dhcp_server_ending_ip_address DATASTRUCT._parm__net_dhcp_server_ending_ip_address
#define lec__td_dat_sum32                DATASTRUCT._lec__td_dat_sum32
#define parm__ooma_key_press_time        DATASTRUCT._parm__ooma_key_press_time
#define v34_equalizer_slew_B1_slow       DATASTRUCT._v34_equalizer_slew_B1_slow
#define V34S_FULL_PHROLL_THRESHOLD       DATASTRUCT._V34S_FULL_PHROLL_THRESHOLD
#define sdt_DC_angle_store_imag          DATASTRUCT._sdt_DC_angle_store_imag
#define v34n_rx_CME_option               DATASTRUCT._v34n_rx_CME_option
#define legacy_rx_duplicate_count        DATASTRUCT._legacy_rx_duplicate_count
#define parm__ipbx_zoom_alarm_code_dial_pattern DATASTRUCT._parm__ipbx_zoom_alarm_code_dial_pattern
#define new_speech                       DATASTRUCT._new_speech
#define DIL_probing_RBS_slot_storage     DATASTRUCT._DIL_probing_RBS_slot_storage
#define sh_ener                          DATASTRUCT._sh_ener
#define constel_decisions_table_rbs      DATASTRUCT._constel_decisions_table_rbs
#define V34N_TX_GAIN_ADJUST_TABLE        DATASTRUCT._V34N_TX_GAIN_ADJUST_TABLE
#define v90_shape_2_offset               DATASTRUCT._v90_shape_2_offset
#define v34_rx_pn_real                   DATASTRUCT._v34_rx_pn_real
#define v34h_tx_w_1_quantize             DATASTRUCT._v34h_tx_w_1_quantize
#define ipbx_outgoing_history_index      DATASTRUCT._ipbx_outgoing_history_index
#define parm__ipbx_outgoing_block_service DATASTRUCT._parm__ipbx_outgoing_block_service
#define p_window                         DATASTRUCT._p_window
#define impedance_monitor_tx_speech_pow32 DATASTRUCT._impedance_monitor_tx_speech_pow32
#define parm__ipbx_hot_line_dialing      DATASTRUCT._parm__ipbx_hot_line_dialing
#define phasedet_rnd_imag_value          DATASTRUCT._phasedet_rnd_imag_value
#define faxdet_data_v21                  DATASTRUCT._faxdet_data_v21
#define ph2_AB_detected                  DATASTRUCT._ph2_AB_detected
#define ipbx_incoming_history_index      DATASTRUCT._ipbx_incoming_history_index
#define parm__ipbx_polarity_idle         DATASTRUCT._parm__ipbx_polarity_idle
#define parm__ffsk_enc_enable            DATASTRUCT._parm__ffsk_enc_enable
#define predicted_rx_xn_B1_Q_n_real      DATASTRUCT._predicted_rx_xn_B1_Q_n_real
#define parm__dtmf_early_row_no_tone_level DATASTRUCT._parm__dtmf_early_row_no_tone_level
#define vppn_encode_packet_byte_data     DATASTRUCT._vppn_encode_packet_byte_data
#define rx_data_ti                       DATASTRUCT._rx_data_ti
#define ANSW_LEN_MS_PREWAIT_DELAY        DATASTRUCT._ANSW_LEN_MS_PREWAIT_DELAY
#define ANSam_phase                      DATASTRUCT._ANSam_phase
#define v92n_rx_eye_modulus              DATASTRUCT._v92n_rx_eye_modulus
#define fract_input_real                 DATASTRUCT._fract_input_real
#define parm__vppn_device_firmware_offset DATASTRUCT._parm__vppn_device_firmware_offset
#define p18_energy40                     DATASTRUCT._p18_energy40
#define lec__tec_coef                    DATASTRUCT._lec__tec_coef
#define v90_tx_dil_tp_offset             DATASTRUCT._v90_tx_dil_tp_offset
#define parm__ipbx_polarity_dialing      DATASTRUCT._parm__ipbx_polarity_dialing
#define sart_rx_processed_cnt            DATASTRUCT._sart_rx_processed_cnt
#define min_phroll_convergence_thresh    DATASTRUCT._min_phroll_convergence_thresh
#define parm__speech_rtp_auto_vad_turnoff DATASTRUCT._parm__speech_rtp_auto_vad_turnoff
#define v90_shape_frame_size             DATASTRUCT._v90_shape_frame_size
#define l_res_cb_size                    DATASTRUCT._l_res_cb_size
#define ph1_tx_sample_counter            DATASTRUCT._ph1_tx_sample_counter
#define nat_lan_hw_addr                  DATASTRUCT._nat_lan_hw_addr
#define v34f_eqc_DC_mag_log              DATASTRUCT._v34f_eqc_DC_mag_log
#define parm__sdp_session_name           DATASTRUCT._parm__sdp_session_name
#define guard_tone_phase                 DATASTRUCT._guard_tone_phase
#define v34f_eqc_sd_DC_real              DATASTRUCT._v34f_eqc_sd_DC_real
#define v90h_tx_control_frame            DATASTRUCT._v90h_tx_control_frame
#define temp_c7k2_interpolator_coefs     DATASTRUCT._temp_c7k2_interpolator_coefs
#define parm__ipbx_busy_forward_enable   DATASTRUCT._parm__ipbx_busy_forward_enable
#define pspr_y2_hi                       DATASTRUCT._pspr_y2_hi
#define parm__vppn_device_command        DATASTRUCT._parm__vppn_device_command
#define mbx__dtoh_hidden                 DATASTRUCT._mbx__dtoh_hidden
#define parm__v8__protocols              DATASTRUCT._parm__v8__protocols
#define size_st                          DATASTRUCT._size_st
#define parm__mgcp_call_agent_address    DATASTRUCT._parm__mgcp_call_agent_address
#define ipod_dth_coded_speech_offset     DATASTRUCT._ipod_dth_coded_speech_offset
#define parm__slac_impedance_commands    DATASTRUCT._parm__slac_impedance_commands
#define PH2P_ANAL_USE_SHAPING            DATASTRUCT._PH2P_ANAL_USE_SHAPING
#define faxdet_value_grl_ansam           DATASTRUCT._faxdet_value_grl_ansam
#define rxs_run_rx_baud_thread           DATASTRUCT._rxs_run_rx_baud_thread
#define pcm_rx_3dB_pad_detect            DATASTRUCT._pcm_rx_3dB_pad_detect
#define v90n_tx_training_silence_option  DATASTRUCT._v90n_tx_training_silence_option
#define dprmbx_post_fw_upgrade_success   DATASTRUCT._dprmbx_post_fw_upgrade_success
#define v34_resync_variance_buffer_imag  DATASTRUCT._v34_resync_variance_buffer_imag
#define stop_timer_count                 DATASTRUCT._stop_timer_count
#define stat__ipbx_device_error_mask     DATASTRUCT._stat__ipbx_device_error_mask
#define v34h_rx_buffer_stream_pointer    DATASTRUCT._v34h_rx_buffer_stream_pointer
#define sonitrol_legacy_mode             DATASTRUCT._sonitrol_legacy_mode
#define v90_previous_ks_value            DATASTRUCT._v90_previous_ks_value
#define parm__dm_carrier_loss_disconnect_duration DATASTRUCT._parm__dm_carrier_loss_disconnect_duration
#define ph2p_anal_log_P_plus_start       DATASTRUCT._ph2p_anal_log_P_plus_start
#define report_rx_packet_flag            DATASTRUCT._report_rx_packet_flag
#define parm__codec_ring_minimum_period  DATASTRUCT._parm__codec_ring_minimum_period
#define qplsp_lsf_vq                     DATASTRUCT._qplsp_lsf_vq
#define cc_rx_AC_energy_log              DATASTRUCT._cc_rx_AC_energy_log
#define convert_adjust_output_log        DATASTRUCT._convert_adjust_output_log
#define stat__speech_rtp_in_silence      DATASTRUCT._stat__speech_rtp_in_silence
#define hh1                              DATASTRUCT._hh1
#define v90_tx_p_frame                   DATASTRUCT._v90_tx_p_frame
#define parm__net_isp_dhcp_enable        DATASTRUCT._parm__net_isp_dhcp_enable
#define v34n_tx_transmit_gain            DATASTRUCT._v34n_tx_transmit_gain
#define lec__force_nlp                   DATASTRUCT._lec__force_nlp
#define v34h_rx_Z_m_previous             DATASTRUCT._v34h_rx_Z_m_previous
#define dtmf_clamp_detect                DATASTRUCT._dtmf_clamp_detect
#define global_width                     DATASTRUCT._global_width
#define rate_reduction_buffer            DATASTRUCT._rate_reduction_buffer
#define rtp_rx_packet                    DATASTRUCT._rtp_rx_packet
#define rtp_dec_packet                   DATASTRUCT._rtp_dec_packet
#define stat__nat_rcv_frag_forward       DATASTRUCT._stat__nat_rcv_frag_forward
#define excessive_ff                     DATASTRUCT._excessive_ff
#define parm__battery_level_threshold_crossed DATASTRUCT._parm__battery_level_threshold_crossed
#define parm__ipbx_caller_id_outbound_service DATASTRUCT._parm__ipbx_caller_id_outbound_service
#define total_ec_sum                     DATASTRUCT._total_ec_sum
#define detect_equalizer_poffset         DATASTRUCT._detect_equalizer_poffset
#define edge_m1200_imag                  DATASTRUCT._edge_m1200_imag
#define Next_Min                         DATASTRUCT._Next_Min
#define send__v8__vpcm_availability      DATASTRUCT._send__v8__vpcm_availability
#define nearest_group_table              DATASTRUCT._nearest_group_table
#define parm__dm_v92_mse_catastrophic    DATASTRUCT._parm__dm_v92_mse_catastrophic
#define rx_rate_double_buffer            DATASTRUCT._rx_rate_double_buffer
#define v33_fback_nearest_group_table_internal_buffer DATASTRUCT._v33_fback_nearest_group_table_internal_buffer
#define ata_led_use_mask_sip             DATASTRUCT._ata_led_use_mask_sip
#define parm__record_method              DATASTRUCT._parm__record_method
#define nat_lan_ip_addr                  DATASTRUCT._nat_lan_ip_addr
#define v90_tx_dil_ucode                 DATASTRUCT._v90_tx_dil_ucode
#define parm__ipbx_timeout_hold_duration DATASTRUCT._parm__ipbx_timeout_hold_duration
#define dev_pattern_index                DATASTRUCT._dev_pattern_index
#define comn_v8_ANSpcm_detect_loss       DATASTRUCT._comn_v8_ANSpcm_detect_loss
#define codec_tx_mask                    DATASTRUCT._codec_tx_mask
#define parm__mgcp_call_agent_ota_parameters DATASTRUCT._parm__mgcp_call_agent_ota_parameters
#define newsidframe                      DATASTRUCT._newsidframe
#define stat__nat_wan_rtp_end_point      DATASTRUCT._stat__nat_wan_rtp_end_point
#define stat__net_dhcp_lease_time        DATASTRUCT._stat__net_dhcp_lease_time
#define parm__ipbx_fc_blocked_number_disable DATASTRUCT._parm__ipbx_fc_blocked_number_disable
#define ph2n_rx_coding_law               DATASTRUCT._ph2n_rx_coding_law
#define first_received_rate              DATASTRUCT._first_received_rate
#define v34_resync_perfect_real          DATASTRUCT._v34_resync_perfect_real
#define parm__ipbx_call_back_ring        DATASTRUCT._parm__ipbx_call_back_ring
#define v34n_rx_remote_to_local_maxrate  DATASTRUCT._v34n_rx_remote_to_local_maxrate
#define vppn_encode_packet_index         DATASTRUCT._vppn_encode_packet_index
#define stat__dm_rx_bits_per_symbol      DATASTRUCT._stat__dm_rx_bits_per_symbol
#define v90n_tx_constellation_mask       DATASTRUCT._v90n_tx_constellation_mask
#define stat__tx_v34_symbol_rate         DATASTRUCT._stat__tx_v34_symbol_rate
#define ph2p_anal_variance_00_table      DATASTRUCT._ph2p_anal_variance_00_table
#define v34_equalizer_agc_update_enabled DATASTRUCT._v34_equalizer_agc_update_enabled
#define parm__ipbx_voip_no_provider_available DATASTRUCT._parm__ipbx_voip_no_provider_available
#define mem2_postfilt                    DATASTRUCT._mem2_postfilt
#define ipbx_periodic_interval           DATASTRUCT._ipbx_periodic_interval
#define v92_linear_mode_enable           DATASTRUCT._v92_linear_mode_enable
#define lec__td_check_ratio              DATASTRUCT._lec__td_check_ratio
#define ph2p_fefo_spectrum_buffer40      DATASTRUCT._ph2p_fefo_spectrum_buffer40
#define parm__speaker_monitor_tx_gain    DATASTRUCT._parm__speaker_monitor_tx_gain
#define parm__ipbx_fc_caller_id_outbound_disable DATASTRUCT._parm__ipbx_fc_caller_id_outbound_disable
#define parm__ata_recovery_domain_name   DATASTRUCT._parm__ata_recovery_domain_name
#define v34h_rx_half_data_frame_counter  DATASTRUCT._v34h_rx_half_data_frame_counter
#define answ_v8_found_CI                 DATASTRUCT._answ_v8_found_CI
#define parm__ata_firmware_request_message DATASTRUCT._parm__ata_firmware_request_message
#define impedance_monitor_tx_noise_floor_index DATASTRUCT._impedance_monitor_tx_noise_floor_index
#define answ_v8_found_CJ                 DATASTRUCT._answ_v8_found_CJ
#define V34S_REVERSALS_FOUND_THRESHOLD   DATASTRUCT._V34S_REVERSALS_FOUND_THRESHOLD
#define rxs_input_sample                 DATASTRUCT._rxs_input_sample
#define v90_rx_delay_poffset_current     DATASTRUCT._v90_rx_delay_poffset_current
#define v34_TRN2_MSE_N_value             DATASTRUCT._v34_TRN2_MSE_N_value
#define parm__vppn_device_firmware_checksum DATASTRUCT._parm__vppn_device_firmware_checksum
#define answ_v8_found_CM                 DATASTRUCT._answ_v8_found_CM
#define fgkernel_current_event           DATASTRUCT._fgkernel_current_event
#define sample_buffer_size               DATASTRUCT._sample_buffer_size
#define ph2n_tx_lo_3200_option           DATASTRUCT._ph2n_tx_lo_3200_option
#define parm__codec_disconnect_tone_1    DATASTRUCT._parm__codec_disconnect_tone_1
#define parm__codec_disconnect_tone_2    DATASTRUCT._parm__codec_disconnect_tone_2
#define lec__nlp_detect_quiet            DATASTRUCT._lec__nlp_detect_quiet
#define parm__codec_disconnect_tone_3    DATASTRUCT._parm__codec_disconnect_tone_3
#define cc_rx_ANAL_BEp_imag              DATASTRUCT._cc_rx_ANAL_BEp_imag
#define rx_clock_phase_slave             DATASTRUCT._rx_clock_phase_slave
#define saved_output_sample_value        DATASTRUCT._saved_output_sample_value
#define sart_rx_array                    DATASTRUCT._sart_rx_array
#define ph2p_anal_maxrates_12_table      DATASTRUCT._ph2p_anal_maxrates_12_table
#define pcm_btr_gain_gain                DATASTRUCT._pcm_btr_gain_gain
#define demod_lagging_real               DATASTRUCT._demod_lagging_real
#define detect_demod_real                DATASTRUCT._detect_demod_real
#define ph2_rx_data_size                 DATASTRUCT._ph2_rx_data_size
#define v90_rx_JE_detect_flag            DATASTRUCT._v90_rx_JE_detect_flag
#define pspr_y2_lo                       DATASTRUCT._pspr_y2_lo
#define parm__voip_melp_npp_enable       DATASTRUCT._parm__voip_melp_npp_enable
#define v92_rx_decoder_ep_buffer         DATASTRUCT._v92_rx_decoder_ep_buffer
#define v34_BE_modify_Gp_exp             DATASTRUCT._v34_BE_modify_Gp_exp
#define parm__net_private_ip_address     DATASTRUCT._parm__net_private_ip_address
#define legacy_SPP_expected_ack_count    DATASTRUCT._legacy_SPP_expected_ack_count
#define pcm_ctl_ep_nlms_extra_shift      DATASTRUCT._pcm_ctl_ep_nlms_extra_shift
#define tmp_baud_UVW_real                DATASTRUCT._tmp_baud_UVW_real
#define v34h_rx_Z_m                      DATASTRUCT._v34h_rx_Z_m
#define v34_tx_remote_pattern_offset     DATASTRUCT._v34_tx_remote_pattern_offset
#define parm__ipbx_initial_dial_tone     DATASTRUCT._parm__ipbx_initial_dial_tone
#define lec__probe_nlp_clip              DATASTRUCT._lec__probe_nlp_clip
#define V34_QN_UPDATE_SLOW_SLEW          DATASTRUCT._V34_QN_UPDATE_SLOW_SLEW
#define parm__g722_frame_type            DATASTRUCT._parm__g722_frame_type
#define ph2p_powr_spectrum_power_buffer40 DATASTRUCT._ph2p_powr_spectrum_power_buffer40
#define parents                          DATASTRUCT._parents
#define parm__ipbx_dialing_duration      DATASTRUCT._parm__ipbx_dialing_duration
#define v34s_run_v0_m_holdoff_count      DATASTRUCT._v34s_run_v0_m_holdoff_count
#define dgi_max_count                    DATASTRUCT._dgi_max_count
#define picp_index                       DATASTRUCT._picp_index
#define txs_out_vxxmod_local             DATASTRUCT._txs_out_vxxmod_local
#define v90_rx_dil_tp_cnt                DATASTRUCT._v90_rx_dil_tp_cnt
#define pcm_ctl_use_alternate_double     DATASTRUCT._pcm_ctl_use_alternate_double
#define ipod_msg_rx_flags                DATASTRUCT._ipod_msg_rx_flags
#define baud_rx_parity_used              DATASTRUCT._baud_rx_parity_used
#define l_postLPFInHis                   DATASTRUCT._l_postLPFInHis
#define v34s_post_MPA_bit_counter        DATASTRUCT._v34s_post_MPA_bit_counter
#define stat__phone_timer_start_time     DATASTRUCT._stat__phone_timer_start_time
#define v92n_rx_train_8pt                DATASTRUCT._v92n_rx_train_8pt
#define idftc_idft_real                  DATASTRUCT._idftc_idft_real
#define saved_scrambler_mask             DATASTRUCT._saved_scrambler_mask
#define cc_rx_rate_counter               DATASTRUCT._cc_rx_rate_counter
#define v8_tx_state                      DATASTRUCT._v8_tx_state
#define vppn_decode_packet_list          DATASTRUCT._vppn_decode_packet_list
#define DELTA_INTEGRATION_TIME           DATASTRUCT._DELTA_INTEGRATION_TIME
#define v92h_rx_control_frame            DATASTRUCT._v92h_rx_control_frame
#define parm__speech_rtp_flow_spec       DATASTRUCT._parm__speech_rtp_flow_spec
#define sm_shift                         DATASTRUCT._sm_shift
#define parm__cp_rd_energy_off_duration  DATASTRUCT._parm__cp_rd_energy_off_duration
#define l_postLPFOutHis_hi               DATASTRUCT._l_postLPFOutHis_hi
#define MONITOR_PHASE_THRESHOLD          DATASTRUCT._MONITOR_PHASE_THRESHOLD
#define ANSAM_LOWER_THRESHOLD            DATASTRUCT._ANSAM_LOWER_THRESHOLD
#define lambdaD                          DATASTRUCT._lambdaD
#define melp_ip                          DATASTRUCT._melp_ip
#define melp_iq                          DATASTRUCT._melp_iq
#define dec_sharp                        DATASTRUCT._dec_sharp
#define v34_TRN2_MSE_S_stack             DATASTRUCT._v34_TRN2_MSE_S_stack
#define FALL_fallforward_value           DATASTRUCT._FALL_fallforward_value
#define DIL_probing_RBS_bislot_storage   DATASTRUCT._DIL_probing_RBS_bislot_storage
#define pcm_btr_error                    DATASTRUCT._pcm_btr_error
#define v34b_bg_ph2_state                DATASTRUCT._v34b_bg_ph2_state
#define v92_MH_detect_enable             DATASTRUCT._v92_MH_detect_enable
#define parm__dpbx_led_use_and_hold      DATASTRUCT._parm__dpbx_led_use_and_hold
#define dcd_probe_diversion              DATASTRUCT._dcd_probe_diversion
#define baud_rx_parity_even_space        DATASTRUCT._baud_rx_parity_even_space
#define v34n_rx_mse_bias                 DATASTRUCT._v34n_rx_mse_bias
#define v34n_tx_probing_maxrate          DATASTRUCT._v34n_tx_probing_maxrate
#define ph2n_probing_transmit_gain       DATASTRUCT._ph2n_probing_transmit_gain
#define sart_overlay_state_prev          DATASTRUCT._sart_overlay_state_prev
#define parm__sip_info_hookflash_string  DATASTRUCT._parm__sip_info_hookflash_string
#define pcm_whiten_transmit_gain         DATASTRUCT._pcm_whiten_transmit_gain
#define overlay_minor_index              DATASTRUCT._overlay_minor_index
#define eqout_leading_imag               DATASTRUCT._eqout_leading_imag
#define temp_saturation                  DATASTRUCT._temp_saturation
#define parm__rtp_packet_duration        DATASTRUCT._parm__rtp_packet_duration
#define ans_counter                      DATASTRUCT._ans_counter
#define v27_rx_guard_count               DATASTRUCT._v27_rx_guard_count
#define v8_rx_QC_type_flag               DATASTRUCT._v8_rx_QC_type_flag
#define v23_orig_tx_passband_coefs_buffer_internal DATASTRUCT._v23_orig_tx_passband_coefs_buffer_internal
#define dgi_pad_type                     DATASTRUCT._dgi_pad_type
#define local_ec_shift_slew              DATASTRUCT._local_ec_shift_slew
#define impedance_monitor_rx_in          DATASTRUCT._impedance_monitor_rx_in
#define ANSAM_CYCLE_COUNT_MAX            DATASTRUCT._ANSAM_CYCLE_COUNT_MAX
#define ph2n_rx_receive_difference       DATASTRUCT._ph2n_rx_receive_difference
#define ph2n_tx_hi_3200_option           DATASTRUCT._ph2n_tx_hi_3200_option
#define PCM_LEN_8K0_MAX_GEAR_TRAIN       DATASTRUCT._PCM_LEN_8K0_MAX_GEAR_TRAIN
#define parm__headset_rx_gain            DATASTRUCT._parm__headset_rx_gain
#define g722_e4l_bl                      DATASTRUCT._g722_e4l_bl
#define pcm_16K_demod                    DATASTRUCT._pcm_16K_demod
#define tonemute_count                   DATASTRUCT._tonemute_count
#define pcm_equalizer_ep_poffset         DATASTRUCT._pcm_equalizer_ep_poffset
#define v34h_rx_write_enable             DATASTRUCT._v34h_rx_write_enable
#define parm__ata_lcd_menu_accounts_display DATASTRUCT._parm__ata_lcd_menu_accounts_display
#define curAcf_dtx                       DATASTRUCT._curAcf_dtx
#define dec_gain_code                    DATASTRUCT._dec_gain_code
#define v90_rx_Uinfo_magnitude           DATASTRUCT._v90_rx_Uinfo_magnitude
#define demod_imag                       DATASTRUCT._demod_imag
#define ANSAM_MIN_SAMPLES                DATASTRUCT._ANSAM_MIN_SAMPLES
#define v90_frame_tx_dil_body_ucode      DATASTRUCT._v90_frame_tx_dil_body_ucode
#define pnew_scores                      DATASTRUCT._pnew_scores
#define V34S_RESP_8K0_3RT_S_SN_to_Edet   DATASTRUCT._V34S_RESP_8K0_3RT_S_SN_to_Edet
#define stat__daa_disconnect_state       DATASTRUCT._stat__daa_disconnect_state
#define edge_p1200_real                  DATASTRUCT._edge_p1200_real
#define g711a_plc_pitchbufend            DATASTRUCT._g711a_plc_pitchbufend
#define ph2s_short_roundtrip_flag        DATASTRUCT._ph2s_short_roundtrip_flag
#define g_gl_buffer                      DATASTRUCT._g_gl_buffer
#define agal_shift                       DATASTRUCT._agal_shift
#define V34_SLEW_COS_BE2                 DATASTRUCT._V34_SLEW_COS_BE2
#define eqout_lagging_delay_real         DATASTRUCT._eqout_lagging_delay_real
#define v92n_rx_symbol_rate              DATASTRUCT._v92n_rx_symbol_rate
#define v32bis_7200_nearest_group_table_internal_buffer DATASTRUCT._v32bis_7200_nearest_group_table_internal_buffer
#define lec__nlp_tight_counter           DATASTRUCT._lec__nlp_tight_counter
#define stat__led_ringing_state          DATASTRUCT._stat__led_ringing_state
#define ph2_power_trace_bin_count        DATASTRUCT._ph2_power_trace_bin_count
#define stat__net_dual_ethernet          DATASTRUCT._stat__net_dual_ethernet
#define lag0q_mem_s                      DATASTRUCT._lag0q_mem_s
#define parm__radio_transmitter_power_amp_mode DATASTRUCT._parm__radio_transmitter_power_amp_mode
#define pre_equalizer_coefs              DATASTRUCT._pre_equalizer_coefs
#define g722_dec_dethigh                 DATASTRUCT._g722_dec_dethigh
#define v34_temp_lo_lo_pre_equalizer_coefs DATASTRUCT._v34_temp_lo_lo_pre_equalizer_coefs
#define ORIG_LEN_MS_MAXIMUM_ANS          DATASTRUCT._ORIG_LEN_MS_MAXIMUM_ANS
#define v90n_parm_rx_pcm_3429_option     DATASTRUCT._v90n_parm_rx_pcm_3429_option
#define parm__ipbx_disconnect_debounce   DATASTRUCT._parm__ipbx_disconnect_debounce
#define ipbx_led_mask                    DATASTRUCT._ipbx_led_mask
#define g722_e4l_dl                      DATASTRUCT._g722_e4l_dl
#define parm__ipbx_call_forward_enable   DATASTRUCT._parm__ipbx_call_forward_enable
#define tx_rd_index                      DATASTRUCT._tx_rd_index
#define v34s_reneg_special_flag          DATASTRUCT._v34s_reneg_special_flag
#define parm__speech_tx_dtx_flag         DATASTRUCT._parm__speech_tx_dtx_flag
#define PCM_LEN_8K0_EQC_TRN1A_START      DATASTRUCT._PCM_LEN_8K0_EQC_TRN1A_START
#define picp_size_of                     DATASTRUCT._picp_size_of
#define monitor_be2_limit                DATASTRUCT._monitor_be2_limit
#define v92_system_ID_coefs              DATASTRUCT._v92_system_ID_coefs
#define stat__mbx_dma_cycle_cnt          DATASTRUCT._stat__mbx_dma_cycle_cnt
#define l_postLPFOutHis_lo               DATASTRUCT._l_postLPFOutHis_lo
#define sync_ack                         DATASTRUCT._sync_ack
#define phone_zeroize_debounce_count     DATASTRUCT._phone_zeroize_debounce_count
#define lec__tec_update_ratio            DATASTRUCT._lec__tec_update_ratio
#define ata_sample_record_base           DATASTRUCT._ata_sample_record_base
#define bpvi                             DATASTRUCT._bpvi
#define g722_dec_slow                    DATASTRUCT._g722_dec_slow
#define v90_tx_send_JE_sequence_flag     DATASTRUCT._v90_tx_send_JE_sequence_flag
#define v90_rx_eye_modulus               DATASTRUCT._v90_rx_eye_modulus
#define v90_apcm_dil_second              DATASTRUCT._v90_apcm_dil_second
#define parm__ipbx_fc_two_digit_speed_dial_program DATASTRUCT._parm__ipbx_fc_two_digit_speed_dial_program
#define parm__ata_processor_chip_id      DATASTRUCT._parm__ata_processor_chip_id
#define ec_update_rate_divider           DATASTRUCT._ec_update_rate_divider
#define parm__ata_firmware_success_message DATASTRUCT._parm__ata_firmware_success_message
#define temp_dm_buffer                   DATASTRUCT._temp_dm_buffer
#define v29_train_length                 DATASTRUCT._v29_train_length
#define v92_system_ID_subroutine         DATASTRUCT._v92_system_ID_subroutine
#define bulk_delay_input_poffset         DATASTRUCT._bulk_delay_input_poffset
#define old_T0                           DATASTRUCT._old_T0
#define sart_rx_buffer_element           DATASTRUCT._sart_rx_buffer_element
#define synth_p                          DATASTRUCT._synth_p
#define pcm_btr_type_limit               DATASTRUCT._pcm_btr_type_limit
#define silence_change_counter           DATASTRUCT._silence_change_counter
#define test_s_lsw                       DATASTRUCT._test_s_lsw
#define parm__audio_agc_noise_floor      DATASTRUCT._parm__audio_agc_noise_floor
#define detect_v21_detect_counter        DATASTRUCT._detect_v21_detect_counter
#define ptloop_phdet_jam_holdoff         DATASTRUCT._ptloop_phdet_jam_holdoff
#define v34_rx_yn_hat_real               DATASTRUCT._v34_rx_yn_hat_real
#define parm__ipbx_call_forward_list     DATASTRUCT._parm__ipbx_call_forward_list
#define V34S_ORIG_8K0_2RT_JEend_to_Edet  DATASTRUCT._V34S_ORIG_8K0_2RT_JEend_to_Edet
#define ph2n_tx_optional_attenuation     DATASTRUCT._ph2n_tx_optional_attenuation
#define V90_LEN_8K0_TRN1D_TEST           DATASTRUCT._V90_LEN_8K0_TRN1D_TEST
#define PH2P_BG_CALCULATE_NORM_POWER     DATASTRUCT._PH2P_BG_CALCULATE_NORM_POWER
#define v92n_parm_apcm_data_rate_option  DATASTRUCT._v92n_parm_apcm_data_rate_option
#define v92_rx_decoder_ep_error          DATASTRUCT._v92_rx_decoder_ep_error
#define parm__slac_port_rx_gain          DATASTRUCT._parm__slac_port_rx_gain
#define pcm_ep_equalizer_size            DATASTRUCT._pcm_ep_equalizer_size
#define parm__sip_use_nat_discovery      DATASTRUCT._parm__sip_use_nat_discovery
#define mbx__htod_hidden                 DATASTRUCT._mbx__htod_hidden
#define faxdet_threshold_v21             DATASTRUCT._faxdet_threshold_v21
#define V34_BE_SLEW_SLOW                 DATASTRUCT._V34_BE_SLEW_SLOW
#define ph4n_tx_answer_to_call_maxrate   DATASTRUCT._ph4n_tx_answer_to_call_maxrate
#define ph2p_fefo_start_bin_phase_index  DATASTRUCT._ph2p_fefo_start_bin_phase_index
#define v34n_established_ph4_count       DATASTRUCT._v34n_established_ph4_count
#define train_on_data_128_slew           DATASTRUCT._train_on_data_128_slew
#define l_pulse_del                      DATASTRUCT._l_pulse_del
#define lec__nlp_gauge_mode              DATASTRUCT._lec__nlp_gauge_mode
#define energy_echo_log                  DATASTRUCT._energy_echo_log
#define gpf_search_srt                   DATASTRUCT._gpf_search_srt
#define parm__codec_disconnect_voltage_enable DATASTRUCT._parm__codec_disconnect_voltage_enable
#define ANSam_trace_phase                DATASTRUCT._ANSam_trace_phase
#define picp_function                    DATASTRUCT._picp_function
#define parm__phone_paycard_enable       DATASTRUCT._parm__phone_paycard_enable
#define v34n_rx_difference_option        DATASTRUCT._v34n_rx_difference_option
#define stat__ata_update_bootfile_url    DATASTRUCT._stat__ata_update_bootfile_url
#define trellis_data                     DATASTRUCT._trellis_data
#define ipod_g726_monitor_state          DATASTRUCT._ipod_g726_monitor_state
#define parm__ipbx_sit3_tone             DATASTRUCT._parm__ipbx_sit3_tone
#define wsp                              DATASTRUCT._wsp
#define ph2_tx_interpolator_offset       DATASTRUCT._ph2_tx_interpolator_offset
#define threshold_fax_ab2                DATASTRUCT._threshold_fax_ab2
#define parm__mgcp_remote_port           DATASTRUCT._parm__mgcp_remote_port
#define notch_datay32_300                DATASTRUCT._notch_datay32_300
#define ph1_x_law_round_value            DATASTRUCT._ph1_x_law_round_value
#define ph4n_rx_trained_trellis          DATASTRUCT._ph4n_rx_trained_trellis
#define enc_byte_counter                 DATASTRUCT._enc_byte_counter
#define cc_rx_ANAL_coef_angle            DATASTRUCT._cc_rx_ANAL_coef_angle
#define dc_offset                        DATASTRUCT._dc_offset
#define phasedet_rnd_real_value          DATASTRUCT._phasedet_rnd_real_value
#define parm__ipbx_caller_id_inbound_current_enable DATASTRUCT._parm__ipbx_caller_id_inbound_current_enable
#define dtx_prev_energy                  DATASTRUCT._dtx_prev_energy
#define faxparm_parm__v21_holdoff_timer  DATASTRUCT._faxparm_parm__v21_holdoff_timer
#define v92h_rx_K_value                  DATASTRUCT._v92h_rx_K_value
#define asm_encode_build_word            DATASTRUCT._asm_encode_build_word
#define pcm_rx_renegot_detect_routine    DATASTRUCT._pcm_rx_renegot_detect_routine
#define parm__speakerphone_tx_gain       DATASTRUCT._parm__speakerphone_tx_gain
#define flushsart                        DATASTRUCT._flushsart
#define v34_rx_qn_equalized_buffer_imag  DATASTRUCT._v34_rx_qn_equalized_buffer_imag
#define parm__speech_mac_dest_addr       DATASTRUCT._parm__speech_mac_dest_addr
#define f0q_dec_mem_s                    DATASTRUCT._f0q_dec_mem_s
#define v34_bulk_extra_buffer_imag       DATASTRUCT._v34_bulk_extra_buffer_imag
#define ph2n_rx_preeq_Whi                DATASTRUCT._ph2n_rx_preeq_Whi
#define lec__datamax_half_size           DATASTRUCT._lec__datamax_half_size
#define parm__phone_entry_time           DATASTRUCT._parm__phone_entry_time
#define stat__nat_snd_tcp                DATASTRUCT._stat__nat_snd_tcp
#define current_mode                     DATASTRUCT._current_mode
#define parm__speech_rtp_ssrc_ident      DATASTRUCT._parm__speech_rtp_ssrc_ident
#define pcm_rx_slot_counter              DATASTRUCT._pcm_rx_slot_counter
#define parm__voip_gsmamr_encode_rate    DATASTRUCT._parm__voip_gsmamr_encode_rate
#define done_with_dtmf                   DATASTRUCT._done_with_dtmf
#define cmr_notch_coefs                  DATASTRUCT._cmr_notch_coefs
#define remote_ec_slew                   DATASTRUCT._remote_ec_slew
#define lec__datamax_half_holdoff        DATASTRUCT._lec__datamax_half_holdoff
#define lec__tx_suppressor_incr          DATASTRUCT._lec__tx_suppressor_incr
#define lec__best_can_ratio              DATASTRUCT._lec__best_can_ratio
#define v34_helper_state_index           DATASTRUCT._v34_helper_state_index
#define v34_rx_yn_perfect_imag_32        DATASTRUCT._v34_rx_yn_perfect_imag_32
#define parm__tone_detectors_slew_rate   DATASTRUCT._parm__tone_detectors_slew_rate
#define data_12k_lookup_internal_buffer  DATASTRUCT._data_12k_lookup_internal_buffer
#define parm__sip_allowed_event_types    DATASTRUCT._parm__sip_allowed_event_types
#define shadow_DNIS_digits               DATASTRUCT._shadow_DNIS_digits
#define minimum_first_trn_length         DATASTRUCT._minimum_first_trn_length
#define tonemute_rx                      DATASTRUCT._tonemute_rx
#define stat__dpbx_key_mask              DATASTRUCT._stat__dpbx_key_mask
#define lookback_poffset                 DATASTRUCT._lookback_poffset
#define ph2p_fefo_test_b32               DATASTRUCT._ph2p_fefo_test_b32
#define handset_out_sample               DATASTRUCT._handset_out_sample
#define l_pitch_avg                      DATASTRUCT._l_pitch_avg
#define lec__best_lin_ratio              DATASTRUCT._lec__best_lin_ratio
#define v34_tx_qn_buffer_real            DATASTRUCT._v34_tx_qn_buffer_real
#define w_fs_init                        DATASTRUCT._w_fs_init
#define v90_frame_rx_residue_length      DATASTRUCT._v90_frame_rx_residue_length
#define parm__radio_receiver_vibrate_enable DATASTRUCT._parm__radio_receiver_vibrate_enable
#define local_ec_slewx                   DATASTRUCT._local_ec_slewx
#define ph2p_anal_maxrates_05_table      DATASTRUCT._ph2p_anal_maxrates_05_table
#define v92n_rx_prefilter_ff_taps        DATASTRUCT._v92n_rx_prefilter_ff_taps
#define v34n_parm_hi_data_rate_option    DATASTRUCT._v34n_parm_hi_data_rate_option
#define g_frameSize                      DATASTRUCT._g_frameSize
#define parm__net_ddns_service_name      DATASTRUCT._parm__net_ddns_service_name
#define ipod_iface_tx_state              DATASTRUCT._ipod_iface_tx_state
#define SN_LT0                           DATASTRUCT._SN_LT0
#define v17_short_ratdet                 DATASTRUCT._v17_short_ratdet
#define parm__ipbx_stuttered_dial_tone   DATASTRUCT._parm__ipbx_stuttered_dial_tone
#define baud_tx_two_stop_bits            DATASTRUCT._baud_tx_two_stop_bits
#define picp_line_1_buffer               DATASTRUCT._picp_line_1_buffer
#define rx_clock_cycles_per_sample       DATASTRUCT._rx_clock_cycles_per_sample
#define stat__speech_udp_message_length  DATASTRUCT._stat__speech_udp_message_length
#define dcd_diversion_diff_threshold     DATASTRUCT._dcd_diversion_diff_threshold
#define v34n_parm_16point_option         DATASTRUCT._v34n_parm_16point_option
#define tmp_baud_UVW_complex             DATASTRUCT._tmp_baud_UVW_complex
#define gpf_coarse_match                 DATASTRUCT._gpf_coarse_match
#define parm__ipbx_no_answer_forward_enable DATASTRUCT._parm__ipbx_no_answer_forward_enable
#define g168_exc_floor                   DATASTRUCT._g168_exc_floor
#define v34n_tx_MD_length                DATASTRUCT._v34n_tx_MD_length
#define cc_tx_guard_xmit_amplitude       DATASTRUCT._cc_tx_guard_xmit_amplitude
#define v34_tx_pn_real                   DATASTRUCT._v34_tx_pn_real
#define nat_public_table                 DATASTRUCT._nat_public_table
#define parm__decoder_mode               DATASTRUCT._parm__decoder_mode
#define btrec_rx_phase_second32          DATASTRUCT._btrec_rx_phase_second32
#define fsk_run_data_hdlc                DATASTRUCT._fsk_run_data_hdlc
#define v34n_rxtx_auxiliary_option       DATASTRUCT._v34n_rxtx_auxiliary_option
#define v34_pnt12_MSE_value              DATASTRUCT._v34_pnt12_MSE_value
#define V34_BE0_SLEW_SLOW                DATASTRUCT._V34_BE0_SLEW_SLOW
#define sense_silence_lpf1               DATASTRUCT._sense_silence_lpf1
#define led_pattern                      DATASTRUCT._led_pattern
#define sense_silence_lpf2               DATASTRUCT._sense_silence_lpf2
#define l_postLPF                        DATASTRUCT._l_postLPF
#define stat__ipod_timeslot              DATASTRUCT._stat__ipod_timeslot
#define asm_within_cng_delay             DATASTRUCT._asm_within_cng_delay
#define v34_frame_tx_bit_count           DATASTRUCT._v34_frame_tx_bit_count
#define dpbx_led_pattern_queue_in        DATASTRUCT._dpbx_led_pattern_queue_in
#define v90_rx_data_holdoff_flag         DATASTRUCT._v90_rx_data_holdoff_flag
#define parm__ipbx_tone_max              DATASTRUCT._parm__ipbx_tone_max
#define cc_tx_guard_tone_increment       DATASTRUCT._cc_tx_guard_tone_increment
#define tonemute_tx                      DATASTRUCT._tonemute_tx
#define parm__pump_fallback_rates        DATASTRUCT._parm__pump_fallback_rates
#define ph2p_powr_reconstruction_buffer40 DATASTRUCT._ph2p_powr_reconstruction_buffer40
#define parm__codec_ring_silence_period  DATASTRUCT._parm__codec_ring_silence_period
#define parm__net_assigned_host_name     DATASTRUCT._parm__net_assigned_host_name
#define shadow_panel_group_desc          DATASTRUCT._shadow_panel_group_desc
#define ac97_minor_number                DATASTRUCT._ac97_minor_number
#define tx_data_ti                       DATASTRUCT._tx_data_ti
#define v34_rx_pn_hat_real               DATASTRUCT._v34_rx_pn_hat_real
#define number_fg_comp                   DATASTRUCT._number_fg_comp
#define ptloop_angle                     DATASTRUCT._ptloop_angle
#define v34_rx_un_imag                   DATASTRUCT._v34_rx_un_imag
#define parm__slac_message_waiting_bias  DATASTRUCT._parm__slac_message_waiting_bias
#define parm__ipbx_zoom_alarm_inital_dial_pattern DATASTRUCT._parm__ipbx_zoom_alarm_inital_dial_pattern
#define allowed_detect_tones             DATASTRUCT._allowed_detect_tones
#define v34n_rx_qn_coef_imag             DATASTRUCT._v34n_rx_qn_coef_imag
#define ec_slow_shift_slew_remote        DATASTRUCT._ec_slow_shift_slew_remote
#define sip_tcp_sockid                   DATASTRUCT._sip_tcp_sockid
#define answ_v8_allow_CM_detection       DATASTRUCT._answ_v8_allow_CM_detection
#define parm__ilbc_high_rate             DATASTRUCT._parm__ilbc_high_rate
#define current_audio_rtp_stream         DATASTRUCT._current_audio_rtp_stream
#define ipod_msg_tx_trans_bits           DATASTRUCT._ipod_msg_tx_trans_bits
#define rtp_tx_packet                    DATASTRUCT._rtp_tx_packet
#define p18_full_energy32                DATASTRUCT._p18_full_energy32
#define pcm_8K0_perfect                  DATASTRUCT._pcm_8K0_perfect
#define v34n_rxtx_asymmetric_rates       DATASTRUCT._v34n_rxtx_asymmetric_rates
#define shadow_configuration_available   DATASTRUCT._shadow_configuration_available
#define parm__ipbx_attended_transfer_service DATASTRUCT._parm__ipbx_attended_transfer_service
#define parm__ipbx_call_waiting_service  DATASTRUCT._parm__ipbx_call_waiting_service
#define v90n_tx_CPt_type                 DATASTRUCT._v90n_tx_CPt_type
#define v90h_rx_shaper_wait_flag         DATASTRUCT._v90h_rx_shaper_wait_flag
#define echo_canceller_buffer            DATASTRUCT._echo_canceller_buffer
#define lec__datamax_full_value          DATASTRUCT._lec__datamax_full_value
#define v92_rx_Ru_detect_flag            DATASTRUCT._v92_rx_Ru_detect_flag
#define pcm_tx_clock_fractional_adjust   DATASTRUCT._pcm_tx_clock_fractional_adjust
#define enc_bitsno_array                 DATASTRUCT._enc_bitsno_array
#define saved_Lx_log_power_pointer       DATASTRUCT._saved_Lx_log_power_pointer
#define ipod_iface_rx_buffer             DATASTRUCT._ipod_iface_rx_buffer
#define baud_tx_state                    DATASTRUCT._baud_tx_state
#define rxs_demod_real                   DATASTRUCT._rxs_demod_real
#define tonemute_valid_count             DATASTRUCT._tonemute_valid_count
#define stat__v8__protocols              DATASTRUCT._stat__v8__protocols
#define parm__ipbx_timeout_no_answer_drop_duration DATASTRUCT._parm__ipbx_timeout_no_answer_drop_duration
#define pcm_HI_value                     DATASTRUCT._pcm_HI_value
#define ph2n_rx_preeq_Wlo                DATASTRUCT._ph2n_rx_preeq_Wlo
#define parm__jpeg_thumbnail_height      DATASTRUCT._parm__jpeg_thumbnail_height
#define noise_generator_tx               DATASTRUCT._noise_generator_tx
#define g722_dec_mode                    DATASTRUCT._g722_dec_mode
#define ata_pfd_status                   DATASTRUCT._ata_pfd_status
#define pcm_LO_value                     DATASTRUCT._pcm_LO_value
#define v34_temp_hi_hi_pre_equalizer_coefs DATASTRUCT._v34_temp_hi_hi_pre_equalizer_coefs
#define v29_rot_mse                      DATASTRUCT._v29_rot_mse
#define v34_pp_skip_count                DATASTRUCT._v34_pp_skip_count
#define parm__sdp_mpeg4_codec_dyn_pt     DATASTRUCT._parm__sdp_mpeg4_codec_dyn_pt
#define producing_1300_calling_tone      DATASTRUCT._producing_1300_calling_tone
#define parm__net_debug_level_sip        DATASTRUCT._parm__net_debug_level_sip
#define parm__sdp_speex_codec_dyn_pt     DATASTRUCT._parm__sdp_speex_codec_dyn_pt
#define ph2p_powr_variable_buffer40      DATASTRUCT._ph2p_powr_variable_buffer40
#define parm__ata_system_info_1          DATASTRUCT._parm__ata_system_info_1
#define parm__disconnect_tone_num_tones  DATASTRUCT._parm__disconnect_tone_num_tones
#define parm__ata_system_info_2          DATASTRUCT._parm__ata_system_info_2
#define ph2n_rx_preeq_Wme                DATASTRUCT._ph2n_rx_preeq_Wme
#define parm__ata_system_info_3          DATASTRUCT._parm__ata_system_info_3
#define parm__net_dns_secondary_address  DATASTRUCT._parm__net_dns_secondary_address
#define parm__ata_system_info_4          DATASTRUCT._parm__ata_system_info_4
#define stat__ata_update_extra_url       DATASTRUCT._stat__ata_update_extra_url
#define parm__ata_system_info_5          DATASTRUCT._parm__ata_system_info_5
#define nat_icmp_type                    DATASTRUCT._nat_icmp_type
#define fax_v21_rlsd_length              DATASTRUCT._fax_v21_rlsd_length
#define v90_rx_base_group                DATASTRUCT._v90_rx_base_group
#define parm__disconnect_tone_cadence_detect_mask DATASTRUCT._parm__disconnect_tone_cadence_detect_mask
#define parm__dm_v90_options_mask        DATASTRUCT._parm__dm_v90_options_mask
#define parm__rtp_stream_duration        DATASTRUCT._parm__rtp_stream_duration
#define v34f_eqc_pr_DC_mag_log           DATASTRUCT._v34f_eqc_pr_DC_mag_log
#define count_ext                        DATASTRUCT._count_ext
#define ph2p_anal_L2_variance            DATASTRUCT._ph2p_anal_L2_variance
#define parm__pump_diag_modes            DATASTRUCT._parm__pump_diag_modes
#define g722_dec_detlow                  DATASTRUCT._g722_dec_detlow
#define nat_ip_type                      DATASTRUCT._nat_ip_type
#define fg_kernel_anomaly                DATASTRUCT._fg_kernel_anomaly
#define fg_status_remove                 DATASTRUCT._fg_status_remove
#define ph4n_tx_control_channel_data_rate DATASTRUCT._ph4n_tx_control_channel_data_rate
#define enc_lsp_old                      DATASTRUCT._enc_lsp_old
#define v34_equalized_real               DATASTRUCT._v34_equalized_real
#define parm__ipbx_green_led_descriptor  DATASTRUCT._parm__ipbx_green_led_descriptor
#define gear_change_period               DATASTRUCT._gear_change_period
#define silence_keep_counter             DATASTRUCT._silence_keep_counter
#define faxmon_final_frame_seen          DATASTRUCT._faxmon_final_frame_seen
#define cc_rx_interpolator_buffer_imag   DATASTRUCT._cc_rx_interpolator_buffer_imag
#define parm__dtmf_min_tone_level        DATASTRUCT._parm__dtmf_min_tone_level
#define v34n_rx_receive_agc2_level       DATASTRUCT._v34n_rx_receive_agc2_level
#define syn_erase                        DATASTRUCT._syn_erase
#define stat__nat_wan_icmp               DATASTRUCT._stat__nat_wan_icmp
#define FALL_fallforward_flag            DATASTRUCT._FALL_fallforward_flag
#define parm__nat_timeout_tcp_opening    DATASTRUCT._parm__nat_timeout_tcp_opening
#define v34h_tx_mapping_frame_count      DATASTRUCT._v34h_tx_mapping_frame_count
#define v34_rx_yn_real                   DATASTRUCT._v34_rx_yn_real
#define PCM_TEST_RBS_SIMULATION_ENABLE   DATASTRUCT._PCM_TEST_RBS_SIMULATION_ENABLE
#define speex_dec_state                  DATASTRUCT._speex_dec_state
#define envdel2                          DATASTRUCT._envdel2
#define extra_rate_reduction_buffer_imag DATASTRUCT._extra_rate_reduction_buffer_imag
#define v92_modem_type                   DATASTRUCT._v92_modem_type
#define faxdet_value_previous            DATASTRUCT._faxdet_value_previous
#define ORIG_V8_CI_COUNT_MIN             DATASTRUCT._ORIG_V8_CI_COUNT_MIN
#define v90n_rx_v90_enable               DATASTRUCT._v90n_rx_v90_enable
#define ANSam_trace_imag                 DATASTRUCT._ANSam_trace_imag
#define l_firstTime_bpvc_ana             DATASTRUCT._l_firstTime_bpvc_ana
#define cc_tx_guard_tone_amplitude       DATASTRUCT._cc_tx_guard_tone_amplitude
#define lec__detect_bits                 DATASTRUCT._lec__detect_bits
#define v34_rx_qn_equalized_poffset      DATASTRUCT._v34_rx_qn_equalized_poffset
#define seed_fer                         DATASTRUCT._seed_fer
#define prpr_y1_hi                       DATASTRUCT._prpr_y1_hi
#define ph2_rx_checker_sum40             DATASTRUCT._ph2_rx_checker_sum40
#define constel_symmetric_table_rbs      DATASTRUCT._constel_symmetric_table_rbs
#define v92_frame_rx_short               DATASTRUCT._v92_frame_rx_short
#define v90n_tx_training_shaping_lookahead DATASTRUCT._v90n_tx_training_shaping_lookahead
#define v34_frame_tx_bits_per_baud       DATASTRUCT._v34_frame_tx_bits_per_baud
#define valid_miss_limit                 DATASTRUCT._valid_miss_limit
#define ANSam_trace_magphase_min_real    DATASTRUCT._ANSam_trace_magphase_min_real
#define ph1_tx_ANSpcm_phase32            DATASTRUCT._ph1_tx_ANSpcm_phase32
#define dprmbx_poll_count                DATASTRUCT._dprmbx_poll_count
#define v90_rx_R_detect_inversion        DATASTRUCT._v90_rx_R_detect_inversion
#define parm__ata_factory_password       DATASTRUCT._parm__ata_factory_password
#define monitor_sample_slow              DATASTRUCT._monitor_sample_slow
#define affine_perfect_imag              DATASTRUCT._affine_perfect_imag
#define v34s_special_local_train_option  DATASTRUCT._v34s_special_local_train_option
#define g711_rx_vad_strict_hangover_counter DATASTRUCT._g711_rx_vad_strict_hangover_counter
#define v21_ans_tx_passband_coefs_buffer_internal DATASTRUCT._v21_ans_tx_passband_coefs_buffer_internal
#define v90_rx_Sd_detect_counter         DATASTRUCT._v90_rx_Sd_detect_counter
#define agc_2_signal_imag                DATASTRUCT._agc_2_signal_imag
#define v34_tx_qn_remote_offset          DATASTRUCT._v34_tx_qn_remote_offset
#define parm__sdp_ilbc_codec_dyn_pt      DATASTRUCT._parm__sdp_ilbc_codec_dyn_pt
#define ph2n_rx_frequency_offset         DATASTRUCT._ph2n_rx_frequency_offset
#define dtmf_mnsqr                       DATASTRUCT._dtmf_mnsqr
#define speex_uwb_dec_state              DATASTRUCT._speex_uwb_dec_state
#define FAX_test                         DATASTRUCT._FAX_test
#define ph4n_rx_call_to_answer_maxrate   DATASTRUCT._ph4n_rx_call_to_answer_maxrate
#define v34n_rx_preeq_exponent           DATASTRUCT._v34n_rx_preeq_exponent
#define parm__speech_enc_slot_cnt        DATASTRUCT._parm__speech_enc_slot_cnt
#define V92_RX_RETRAIN_Et_THRESHOLD      DATASTRUCT._V92_RX_RETRAIN_Et_THRESHOLD
#define parm__rtp_port_minimum           DATASTRUCT._parm__rtp_port_minimum
#define v34_temp_lo_me_pre_equalizer_coefs DATASTRUCT._v34_temp_lo_me_pre_equalizer_coefs
#define l_index                          DATASTRUCT._l_index
#define ANSam_trace_max_real             DATASTRUCT._ANSam_trace_max_real
#define parm__dm_v34_trellis_num         DATASTRUCT._parm__dm_v34_trellis_num
#define DIL_probing_slot_counter         DATASTRUCT._DIL_probing_slot_counter
#define parm__v8__modulation_modes       DATASTRUCT._parm__v8__modulation_modes
#define ata_ignore_code_image_flag       DATASTRUCT._ata_ignore_code_image_flag
#define parm__dpbx_led_call_holding      DATASTRUCT._parm__dpbx_led_call_holding
#define prev_diffdec_input               DATASTRUCT._prev_diffdec_input
#define vppn_device_command_queue        DATASTRUCT._vppn_device_command_queue
#define g722_e3h_nbh                     DATASTRUCT._g722_e3h_nbh
#define parm__vppn_device_manufacturer_id DATASTRUCT._parm__vppn_device_manufacturer_id
#define speech_in_npp                    DATASTRUCT._speech_in_npp
#define sequence_outband_level           DATASTRUCT._sequence_outband_level
#define xxx_rx_exponent                  DATASTRUCT._xxx_rx_exponent
#define p18_half_energy32                DATASTRUCT._p18_half_energy32
#define parm__pulse_make_time            DATASTRUCT._parm__pulse_make_time
#define lec__probe_nlp_output            DATASTRUCT._lec__probe_nlp_output
#define pcm_AL_peak_MSE_stack            DATASTRUCT._pcm_AL_peak_MSE_stack
#define parm__speech_enc_transition_control DATASTRUCT._parm__speech_enc_transition_control
#define V34S_RENEG_TEST_T_S_LENGTH       DATASTRUCT._V34S_RENEG_TEST_T_S_LENGTH
#define ipod_command_max_fnbdt_rate      DATASTRUCT._ipod_command_max_fnbdt_rate
#define l_firstTime_pitch_ana            DATASTRUCT._l_firstTime_pitch_ana
#define agc_1_exponent                   DATASTRUCT._agc_1_exponent
#define lec__an_excess                   DATASTRUCT._lec__an_excess
#define dc_offset_accumulator            DATASTRUCT._dc_offset_accumulator
#define ph2n_rx_preeq_exponent           DATASTRUCT._ph2n_rx_preeq_exponent
#define g_quant_par                      DATASTRUCT._g_quant_par
#define vppn_device_command_send_index   DATASTRUCT._vppn_device_command_send_index
#define lec__cng_frame_sil_detect        DATASTRUCT._lec__cng_frame_sil_detect
#define faxdet_data_sum_ced              DATASTRUCT._faxdet_data_sum_ced
#define v34_local_echo_exponent          DATASTRUCT._v34_local_echo_exponent
#define cc_rx_equalizer_data_imag        DATASTRUCT._cc_rx_equalizer_data_imag
#define past_gain                        DATASTRUCT._past_gain
#define ata_pfd_configuration_attempts   DATASTRUCT._ata_pfd_configuration_attempts
#define v34_tx_yn_remote_real            DATASTRUCT._v34_tx_yn_remote_real
#define parm__ipbx_sit_id                DATASTRUCT._parm__ipbx_sit_id
#define v34_pp_sync_count                DATASTRUCT._v34_pp_sync_count
#define ec_ytrain_shift_slew_remote      DATASTRUCT._ec_ytrain_shift_slew_remote
#define test_input_mixup                 DATASTRUCT._test_input_mixup
#define phone_ringer_tx_volume           DATASTRUCT._phone_ringer_tx_volume
#define parm__net_isp_heartbeat_server_ip_address DATASTRUCT._parm__net_isp_heartbeat_server_ip_address
#define dgi_pad_expo                     DATASTRUCT._dgi_pad_expo
#define V34N_RX_GAIN_ADJUST_TABLE        DATASTRUCT._V34N_RX_GAIN_ADJUST_TABLE
#define V34S_ANSW_8K0_1RT_Jsrt_to_S_SNdet DATASTRUCT._V34S_ANSW_8K0_1RT_Jsrt_to_S_SNdet
#define saved_Lx_SE_power_adjust_pointer DATASTRUCT._saved_Lx_SE_power_adjust_pointer
#define edge_p1200                       DATASTRUCT._edge_p1200
#define lec__datamax_poffset             DATASTRUCT._lec__datamax_poffset
#define lec__nlp_threshold               DATASTRUCT._lec__nlp_threshold
#define l_syn_begin                      DATASTRUCT._l_syn_begin
#define lec__rx_output                   DATASTRUCT._lec__rx_output
#define parm__rtp_jitter_buffer_start_depth DATASTRUCT._parm__rtp_jitter_buffer_start_depth
#define v90_tx_s_input_offset            DATASTRUCT._v90_tx_s_input_offset
#define stat__nat_snd_translated         DATASTRUCT._stat__nat_snd_translated
#define parm__voip_provider_alternate    DATASTRUCT._parm__voip_provider_alternate
#define v90n_rx_rx_coding_law            DATASTRUCT._v90n_rx_rx_coding_law
#define v90n_tx_training_constel_mapping DATASTRUCT._v90n_tx_training_constel_mapping
#define DIL_probing_table_offset         DATASTRUCT._DIL_probing_table_offset
#define detect_limit                     DATASTRUCT._detect_limit
#define v90_tx_dil_sp_ptr                DATASTRUCT._v90_tx_dil_sp_ptr
#define ph2_rx_passband_coef_pointer     DATASTRUCT._ph2_rx_passband_coef_pointer
#define parm__dtmf_detect_abcd           DATASTRUCT._parm__dtmf_detect_abcd
#define g722_e4l_sg                      DATASTRUCT._g722_e4l_sg
#define v92_frame_rx_size_SUVu           DATASTRUCT._v92_frame_rx_size_SUVu
#define sdt_angle_store_real             DATASTRUCT._sdt_angle_store_real
#define parm__ipbx_unattended_transfer_service DATASTRUCT._parm__ipbx_unattended_transfer_service
#define v17_diagnostics_mse_count        DATASTRUCT._v17_diagnostics_mse_count
#define lsp_old_ptr                      DATASTRUCT._lsp_old_ptr
#define g722_e4l_sl                      DATASTRUCT._g722_e4l_sl
#define parm__radio_headset_continuous_transmit_enable DATASTRUCT._parm__radio_headset_continuous_transmit_enable
#define prpr_y1_lo                       DATASTRUCT._prpr_y1_lo
#define sonitrol_remote_lcfw_ip          DATASTRUCT._sonitrol_remote_lcfw_ip
#define v90n_rx_coding_law               DATASTRUCT._v90n_rx_coding_law
#define trn_8K0_perfect                  DATASTRUCT._trn_8K0_perfect
#define parm__dtmf_playout_min_duration  DATASTRUCT._parm__dtmf_playout_min_duration
#define btrec_baud_AkQk_shift            DATASTRUCT._btrec_baud_AkQk_shift
#define V34_QN_UPDATE_DATA_SLOW_SLEW     DATASTRUCT._V34_QN_UPDATE_DATA_SLOW_SLEW
#define ph2n_tx_tx_3429_option           DATASTRUCT._ph2n_tx_tx_3429_option
#define ptloop_2nd_order_term32          DATASTRUCT._ptloop_2nd_order_term32
#define l_ase_del                        DATASTRUCT._l_ase_del
#define pcm_16K_ec_sample                DATASTRUCT._pcm_16K_ec_sample
#define l_ase_den                        DATASTRUCT._l_ase_den
#define legacy_audio_ack_received        DATASTRUCT._legacy_audio_ack_received
#define parm__sart_hdlc_crc32_tx_en      DATASTRUCT._parm__sart_hdlc_crc32_tx_en
#define sart_overlay_state               DATASTRUCT._sart_overlay_state
#define v90_rx_1K3_energy_log            DATASTRUCT._v90_rx_1K3_energy_log
#define parm__speech_ip_identifier       DATASTRUCT._parm__speech_ip_identifier
#define v92_rx_Ru_Rxx0                   DATASTRUCT._v92_rx_Ru_Rxx0
#define asm_encode_shift_decrement       DATASTRUCT._asm_encode_shift_decrement
#define l_melp_uv_cb_size                DATASTRUCT._l_melp_uv_cb_size
#define v90_frame_rx_input_length        DATASTRUCT._v90_frame_rx_input_length
#define ph2n_rx_mse_bias                 DATASTRUCT._ph2n_rx_mse_bias
#define v92_rx_Ru_Rxx3                   DATASTRUCT._v92_rx_Ru_Rxx3
#define rd_period_beyond_range           DATASTRUCT._rd_period_beyond_range
#define v34n_tx_hi_carrier_option        DATASTRUCT._v34n_tx_hi_carrier_option
#define parm__ipbx_distinctive_ring_1    DATASTRUCT._parm__ipbx_distinctive_ring_1
#define parm__ipbx_distinctive_ring_2    DATASTRUCT._parm__ipbx_distinctive_ring_2
#define v92_rx_Ru_Rxx6                   DATASTRUCT._v92_rx_Ru_Rxx6
#define parm__ipbx_distinctive_ring_3    DATASTRUCT._parm__ipbx_distinctive_ring_3
#define btrec_p2400_real                 DATASTRUCT._btrec_p2400_real
#define parm__ipbx_distinctive_ring_4    DATASTRUCT._parm__ipbx_distinctive_ring_4
#define PH2P_POWR_LX_INITIAL_TUNE        DATASTRUCT._PH2P_POWR_LX_INITIAL_TUNE
#define V34S_GEAR_CONVERGENCE_THRESHOLD  DATASTRUCT._V34S_GEAR_CONVERGENCE_THRESHOLD
#define answ_v8_use_invert               DATASTRUCT._answ_v8_use_invert
#define parm__ipbx_distinctive_ring_5    DATASTRUCT._parm__ipbx_distinctive_ring_5
#define parm__ipbx_call_forward_ring_splash DATASTRUCT._parm__ipbx_call_forward_ring_splash
#define parm__ipbx_distinctive_ring_6    DATASTRUCT._parm__ipbx_distinctive_ring_6
#define v34n_rx_frequency_offset         DATASTRUCT._v34n_rx_frequency_offset
#define parm__ipbx_distinctive_ring_7    DATASTRUCT._parm__ipbx_distinctive_ring_7
#define parm__ata_serial_number          DATASTRUCT._parm__ata_serial_number
#define parm__ipbx_distinctive_ring_8    DATASTRUCT._parm__ipbx_distinctive_ring_8
#define stat__net_ddns_status            DATASTRUCT._stat__net_ddns_status
#define lec__tx_input                    DATASTRUCT._lec__tx_input
#define ph4n_rx_trained_nonlinear        DATASTRUCT._ph4n_rx_trained_nonlinear
#define pcm_probe_eqc_state              DATASTRUCT._pcm_probe_eqc_state
#define parm__codec_ring_detect_period_minimum DATASTRUCT._parm__codec_ring_detect_period_minimum
#define lec__probe_nlp_noise             DATASTRUCT._lec__probe_nlp_noise
#define parm__ipbx_hangup_disconnect_duration DATASTRUCT._parm__ipbx_hangup_disconnect_duration
#define v90_tx_send_MP_frame_flag        DATASTRUCT._v90_tx_send_MP_frame_flag
#define received_e_seq                   DATASTRUCT._received_e_seq
#define mark_threshold                   DATASTRUCT._mark_threshold
#define sense_silence_level              DATASTRUCT._sense_silence_level
#define stat__v8_disconnect_reason       DATASTRUCT._stat__v8_disconnect_reason
#define ipod_command_timeslot            DATASTRUCT._ipod_command_timeslot
#define l_qplsp                          DATASTRUCT._l_qplsp
#define noise_shift                      DATASTRUCT._noise_shift
#define decode_gain_linear               DATASTRUCT._decode_gain_linear
#define V34S_FULL_CONVERGENCE_THRESHOLD  DATASTRUCT._V34S_FULL_CONVERGENCE_THRESHOLD
#define coef_offset_double               DATASTRUCT._coef_offset_double
#define v90_rx_retrain_Et_energy_log     DATASTRUCT._v90_rx_retrain_Et_energy_log
#define stat__daa_gain_state             DATASTRUCT._stat__daa_gain_state
#define g_w_fs_inv                       DATASTRUCT._g_w_fs_inv
#define parm__ata_user_name              DATASTRUCT._parm__ata_user_name
#define speech_sync_dec_delay_cntr       DATASTRUCT._speech_sync_dec_delay_cntr
#define v34n_parm_preemptive_phase_roll_slow DATASTRUCT._v34n_parm_preemptive_phase_roll_slow
#define v92n_tx_SUVd_body                DATASTRUCT._v92n_tx_SUVd_body
#define v92_rx_Ru_RxxY                   DATASTRUCT._v92_rx_Ru_RxxY
#define tmp_full_energy                  DATASTRUCT._tmp_full_energy
#define g168_inp_peak                    DATASTRUCT._g168_inp_peak
#define dtmf_mode                        DATASTRUCT._dtmf_mode
#define g711_cng_data                    DATASTRUCT._g711_cng_data
#define parm__speech_rtp_enc_sample_cnt  DATASTRUCT._parm__speech_rtp_enc_sample_cnt
#define ph2_rx_rate_conv_9K6_8K0_buffer  DATASTRUCT._ph2_rx_rate_conv_9K6_8K0_buffer
#define legacy_rx_buffer                 DATASTRUCT._legacy_rx_buffer
#define v90n_rx_constel_codes_pointer    DATASTRUCT._v90n_rx_constel_codes_pointer
#define parm__operating_mode             DATASTRUCT._parm__operating_mode
#define ipod_msg_rx_mod_type             DATASTRUCT._ipod_msg_rx_mod_type
#define helper_imag                      DATASTRUCT._helper_imag
#define stat__ata_update_codefile_url    DATASTRUCT._stat__ata_update_codefile_url
#define ph2p_powr_power_block_count      DATASTRUCT._ph2p_powr_power_block_count
#define v90_frame_tx_dil_body_h          DATASTRUCT._v90_frame_tx_dil_body_h
#define v34h_tx_residue_length           DATASTRUCT._v34h_tx_residue_length
#define v34_tx_decor_coefs               DATASTRUCT._v34_tx_decor_coefs
#define g711_rx_cng_frame_buffer         DATASTRUCT._g711_rx_cng_frame_buffer
#define v92_equalizer_coef_nulling       DATASTRUCT._v92_equalizer_coef_nulling
#define phone_zeroize_condition          DATASTRUCT._phone_zeroize_condition
#define input_code                       DATASTRUCT._input_code
#define v34h_rx_g2_table                 DATASTRUCT._v34h_rx_g2_table
#define stat__nat_rcv_udp                DATASTRUCT._stat__nat_rcv_udp
#define v92s_eqc_TRN1u2_flag             DATASTRUCT._v92s_eqc_TRN1u2_flag
#define v92s_retrigger_modem_on_hold     DATASTRUCT._v92s_retrigger_modem_on_hold
#define parm__net_static_gateway_address DATASTRUCT._parm__net_static_gateway_address
#define stat__v8__gstn_access            DATASTRUCT._stat__v8__gstn_access
#define ipod_v32_start_state             DATASTRUCT._ipod_v32_start_state
#define save_rx_answer_to_call_maxrate   DATASTRUCT._save_rx_answer_to_call_maxrate
#define parm__ipbx_hook_debounce         DATASTRUCT._parm__ipbx_hook_debounce
#define dev_cid_repeat_count             DATASTRUCT._dev_cid_repeat_count
#define parm__ata_daylight_savings_enable DATASTRUCT._parm__ata_daylight_savings_enable
#define act_min                          DATASTRUCT._act_min
#define v29_rot_equalized_real           DATASTRUCT._v29_rot_equalized_real
#define parm__nat_dmz_enable             DATASTRUCT._parm__nat_dmz_enable
#define parm__ipbx_fxo_autoanswer_any_enable DATASTRUCT._parm__ipbx_fxo_autoanswer_any_enable
#define v90n_parm_rx_train_16pt_option   DATASTRUCT._v90n_parm_rx_train_16pt_option
#define shadow_franchise_id              DATASTRUCT._shadow_franchise_id
#define equalizer_output_real            DATASTRUCT._equalizer_output_real
#define v34s_special_remove_DC_offset    DATASTRUCT._v34s_special_remove_DC_offset
#define prpr_x0                          DATASTRUCT._prpr_x0
#define v34f_eqc_sd_DC_mag_log           DATASTRUCT._v34f_eqc_sd_DC_mag_log
#define prpr_x1                          DATASTRUCT._prpr_x1
#define predicted_rx_xn_B1_flag          DATASTRUCT._predicted_rx_xn_B1_flag
#define bpfdel                           DATASTRUCT._bpfdel
#define pcm_rx_ph2_2k_energy_ratio       DATASTRUCT._pcm_rx_ph2_2k_energy_ratio
#define silence_hysteresis               DATASTRUCT._silence_hysteresis
#define overlay_ph2_to_ph2               DATASTRUCT._overlay_ph2_to_ph2
#define stat__rtp_statistics             DATASTRUCT._stat__rtp_statistics
#define parm__sdp_gsm_fr_codec_dyn_pt    DATASTRUCT._parm__sdp_gsm_fr_codec_dyn_pt
#define FALL_adjusted_mse_delta          DATASTRUCT._FALL_adjusted_mse_delta
#define fsk_shift_gain                   DATASTRUCT._fsk_shift_gain
#define jitter_Q_factor                  DATASTRUCT._jitter_Q_factor
#define ph2p_anal_maxrates_11_table      DATASTRUCT._ph2p_anal_maxrates_11_table
#define v34s_capture_counter             DATASTRUCT._v34s_capture_counter
#define asm_decode_current_shift         DATASTRUCT._asm_decode_current_shift
#define loopback_buffer                  DATASTRUCT._loopback_buffer
#define n_pwr                            DATASTRUCT._n_pwr
#define v34_equalizer_slew_data_offset   DATASTRUCT._v34_equalizer_slew_data_offset
#define faxdet_value_ansam               DATASTRUCT._faxdet_value_ansam
#define cc_rx_ANAL_coef_real             DATASTRUCT._cc_rx_ANAL_coef_real
#define parm__sip_prack_authentication   DATASTRUCT._parm__sip_prack_authentication
#define faxparm_active__pump_fax_mode    DATASTRUCT._faxparm_active__pump_fax_mode
#define train_on_data_slew_v29           DATASTRUCT._train_on_data_slew_v29
#define prpr_y1                          DATASTRUCT._prpr_y1
#define prpr_y2                          DATASTRUCT._prpr_y2
#define v34_MSE_S_value                  DATASTRUCT._v34_MSE_S_value
#define v34s_prev_phase_roll_second      DATASTRUCT._v34s_prev_phase_roll_second
#define tone_priority_flag               DATASTRUCT._tone_priority_flag
#define rd_decimate                      DATASTRUCT._rd_decimate
#define sample_interrupt_offset          DATASTRUCT._sample_interrupt_offset
#define parm__srtp_session_keys          DATASTRUCT._parm__srtp_session_keys
#define l_codewd_13x9                    DATASTRUCT._l_codewd_13x9
#define g722_e4h_szh                     DATASTRUCT._g722_e4h_szh
#define received_rate_seq                DATASTRUCT._received_rate_seq
#define dtmf_off_end                     DATASTRUCT._dtmf_off_end
#define ph2p_anal_log_Eb                 DATASTRUCT._ph2p_anal_log_Eb
#define parm__sip_timer_reinvite_expires DATASTRUCT._parm__sip_timer_reinvite_expires
#define cc_enable_ones                   DATASTRUCT._cc_enable_ones
#define training_mse_log                 DATASTRUCT._training_mse_log
#define rxs_out_vxxmod_local             DATASTRUCT._rxs_out_vxxmod_local
#define g168_inp_level                   DATASTRUCT._g168_inp_level
#define ph4n_tx_receive_qn_coef_real     DATASTRUCT._ph4n_tx_receive_qn_coef_real
#define det_energy                       DATASTRUCT._det_energy
#define lec__datamax_half_value          DATASTRUCT._lec__datamax_half_value
#define ph2p_anal_log_Ep                 DATASTRUCT._ph2p_anal_log_Ep
#define parm__dm_clock_control           DATASTRUCT._parm__dm_clock_control
#define tx_rate_conv_pointer             DATASTRUCT._tx_rate_conv_pointer
#define v92_rx_Ru_feedback_buffer        DATASTRUCT._v92_rx_Ru_feedback_buffer
#define v90n_tx_training_shaping_a1      DATASTRUCT._v90n_tx_training_shaping_a1
#define v34s_conditional_ecc             DATASTRUCT._v34s_conditional_ecc
#define stat__slac_model                 DATASTRUCT._stat__slac_model
#define v90n_tx_training_shaping_a2      DATASTRUCT._v90n_tx_training_shaping_a2
#define stat__nat_wan_discards           DATASTRUCT._stat__nat_wan_discards
#define sigbuf_ana                       DATASTRUCT._sigbuf_ana
#define sonitrol_local_mask              DATASTRUCT._sonitrol_local_mask
#define parm__sip_response_code_retry_registration DATASTRUCT._parm__sip_response_code_retry_registration
#define ph2n_rx_optional_attenuation     DATASTRUCT._ph2n_rx_optional_attenuation
#define lsd_recovery_state               DATASTRUCT._lsd_recovery_state
#define g726_dec_state                   DATASTRUCT._g726_dec_state
#define v92_tx_send_SdN_flag             DATASTRUCT._v92_tx_send_SdN_flag
#define parm__jpeg_thumbnail_width       DATASTRUCT._parm__jpeg_thumbnail_width
#define dgidet_noise_count               DATASTRUCT._dgidet_noise_count
#define stat__nat_rcv_ipsec              DATASTRUCT._stat__nat_rcv_ipsec
#define fsk_interpolator_poffset         DATASTRUCT._fsk_interpolator_poffset
#define v34f_eqc_sd_DC_angle             DATASTRUCT._v34f_eqc_sd_DC_angle
#define pcm_rx_clock_phase_slave         DATASTRUCT._pcm_rx_clock_phase_slave
#define v90_frame_tx_mapping             DATASTRUCT._v90_frame_tx_mapping
#define pcm_rx_2k_AGC2_gain              DATASTRUCT._pcm_rx_2k_AGC2_gain
#define picp_position                    DATASTRUCT._picp_position
#define parm__ata_firmware_update_on_reset DATASTRUCT._parm__ata_firmware_update_on_reset
#define parm__dpbx_key_and_mask          DATASTRUCT._parm__dpbx_key_and_mask
#define cc_rx_lpf_coef_poffset           DATASTRUCT._cc_rx_lpf_coef_poffset
#define v34_tx_decor_poffset             DATASTRUCT._v34_tx_decor_poffset
#define stat__nat_rcv_pppoe              DATASTRUCT._stat__nat_rcv_pppoe
#define ata_pfd_processor_die_id         DATASTRUCT._ata_pfd_processor_die_id
#define bad_lsf                          DATASTRUCT._bad_lsf
#define sip_content_body_buffer          DATASTRUCT._sip_content_body_buffer
#define tx_passband_poffset              DATASTRUCT._tx_passband_poffset
#define v90n_tx_training_shaping_b1      DATASTRUCT._v90n_tx_training_shaping_b1
#define pcm_equalizer_fb_poffset         DATASTRUCT._pcm_equalizer_fb_poffset
#define parm__net_static_netmask         DATASTRUCT._parm__net_static_netmask
#define parm__ipbx_voip_primary_provider_unavailable DATASTRUCT._parm__ipbx_voip_primary_provider_unavailable
#define v90n_tx_training_shaping_b2      DATASTRUCT._v90n_tx_training_shaping_b2
#define speech_direct_playback_index     DATASTRUCT._speech_direct_playback_index
#define mark_idle_nmd_seen               DATASTRUCT._mark_idle_nmd_seen
#define stat__speech_enc_current_frame   DATASTRUCT._stat__speech_enc_current_frame
#define ANSam_magnitude_lpf32            DATASTRUCT._ANSam_magnitude_lpf32
#define parm__radio_lcd_menu_password    DATASTRUCT._parm__radio_lcd_menu_password
#define ipod_msg_rx_digit_pair           DATASTRUCT._ipod_msg_rx_digit_pair
#define parm__ipbx_prompt_tone           DATASTRUCT._parm__ipbx_prompt_tone
#define v34s_reneg_allow_send_MP_within_ignore DATASTRUCT._v34s_reneg_allow_send_MP_within_ignore
#define prev_lpc_gain                    DATASTRUCT._prev_lpc_gain
#define ph2p_fefo_test_b_prime32         DATASTRUCT._ph2p_fefo_test_b_prime32
#define pcm_rx_decision_routine          DATASTRUCT._pcm_rx_decision_routine
#define parm__ata_web_server_port        DATASTRUCT._parm__ata_web_server_port
#define stat__nat_rcv_frag_created       DATASTRUCT._stat__nat_rcv_frag_created
#define lec__tec_data_poffset            DATASTRUCT._lec__tec_data_poffset
#define sdt_poffset                      DATASTRUCT._sdt_poffset
#define ipod_msg_tx_sig_on_offset        DATASTRUCT._ipod_msg_tx_sig_on_offset
#define stat__nat_snd_l2tp               DATASTRUCT._stat__nat_snd_l2tp
#define parm__slac_message_waiting_mode  DATASTRUCT._parm__slac_message_waiting_mode
#define parm__ipbx_blocked_number_service DATASTRUCT._parm__ipbx_blocked_number_service
#define stat__nat_snd_non_ipv4           DATASTRUCT._stat__nat_snd_non_ipv4
#define v92_frame_rx_bits_per_data_frame DATASTRUCT._v92_frame_rx_bits_per_data_frame
#define ph2p_anal_log_Gr                 DATASTRUCT._ph2p_anal_log_Gr
#define fsk_bitstream                    DATASTRUCT._fsk_bitstream
#define speech_plc_data                  DATASTRUCT._speech_plc_data
#define ph2p_anal_log_Gt                 DATASTRUCT._ph2p_anal_log_Gt
#define faxdet_threshold_difference      DATASTRUCT._faxdet_threshold_difference
#define cc_rx_rate_buffer                DATASTRUCT._cc_rx_rate_buffer
#define comn_v8_ANSpcm_detect            DATASTRUCT._comn_v8_ANSpcm_detect
#define shadow_local_port                DATASTRUCT._shadow_local_port
#define parm__codec_port_impedance       DATASTRUCT._parm__codec_port_impedance
#define v23_ans_tx_passband_coefs_buffer_internal DATASTRUCT._v23_ans_tx_passband_coefs_buffer_internal
#define parm__sdp_gsm_amr_codec_name     DATASTRUCT._parm__sdp_gsm_amr_codec_name
#define v27_tx_poly_mask                 DATASTRUCT._v27_tx_poly_mask
#define V34_RXI_ADJUST                   DATASTRUCT._V34_RXI_ADJUST
#define and_mask                         DATASTRUCT._and_mask
#define lsf600q_s                        DATASTRUCT._lsf600q_s
#define stat__nat_snd_alg_discards       DATASTRUCT._stat__nat_snd_alg_discards
#define test_s_ext                       DATASTRUCT._test_s_ext
#define baud_rx_shift                    DATASTRUCT._baud_rx_shift
#define v34h_rx_w_1_quantize             DATASTRUCT._v34h_rx_w_1_quantize
#define v90_shape_4_min                  DATASTRUCT._v90_shape_4_min
#define v34n_tx_clock_mode               DATASTRUCT._v34n_tx_clock_mode
#define match_data                       DATASTRUCT._match_data
#define ph2_log_power_input_pointer      DATASTRUCT._ph2_log_power_input_pointer
#define MeanE                            DATASTRUCT._MeanE
#define ipod_iface_tx_buffer             DATASTRUCT._ipod_iface_tx_buffer
#define stat__net_enet_ltow_passthrough  DATASTRUCT._stat__net_enet_ltow_passthrough
#define baud_edge_buffer                 DATASTRUCT._baud_edge_buffer
#define l_data_idx                       DATASTRUCT._l_data_idx
#define v34_rx_W0_2m                     DATASTRUCT._v34_rx_W0_2m
#define v90n_rxtx_pcm_3429_option        DATASTRUCT._v90n_rxtx_pcm_3429_option
#define energy_echo40                    DATASTRUCT._energy_echo40
#define timer_CNGgen_value               DATASTRUCT._timer_CNGgen_value
#define sip_udp_sockid                   DATASTRUCT._sip_udp_sockid
#define detect_tone_lengths_p            DATASTRUCT._detect_tone_lengths_p
#define Overflow                         DATASTRUCT._Overflow
#define monitor_state0_save_delay        DATASTRUCT._monitor_state0_save_delay
#define p18_lpf_buffer_real              DATASTRUCT._p18_lpf_buffer_real
#define sart_rx_private_buffer           DATASTRUCT._sart_rx_private_buffer
#define rd_metric                        DATASTRUCT._rd_metric
#define parm__test_QCA2d_holdoff         DATASTRUCT._parm__test_QCA2d_holdoff
#define ethernet_outgoing_ack_queue      DATASTRUCT._ethernet_outgoing_ack_queue
#define ph2p_powr_variable_setup_table   DATASTRUCT._ph2p_powr_variable_setup_table
#define saved_tx_MP_bit_count            DATASTRUCT._saved_tx_MP_bit_count
#define parm__ata_date                   DATASTRUCT._parm__ata_date
#define v34h_rx_M_number_rings           DATASTRUCT._v34h_rx_M_number_rings
#define v34_tx_un_imag                   DATASTRUCT._v34_tx_un_imag
#define speech_direct_record_index       DATASTRUCT._speech_direct_record_index
#define nat_ip_id                        DATASTRUCT._nat_ip_id
#define v90_dpcm_dil_lsp                 DATASTRUCT._v90_dpcm_dil_lsp
#define prev_gain_q_gain                 DATASTRUCT._prev_gain_q_gain
#define parm__ipbx_fc_distinctive_ring_disable DATASTRUCT._parm__ipbx_fc_distinctive_ring_disable
#define sense_silence_hysteresis         DATASTRUCT._sense_silence_hysteresis
#define v27_rx_guard_flag                DATASTRUCT._v27_rx_guard_flag
#define delta_threshold                  DATASTRUCT._delta_threshold
#define s1_detector_data                 DATASTRUCT._s1_detector_data
#define ph2_rx_checker_bpf_buffer        DATASTRUCT._ph2_rx_checker_bpf_buffer
#define parm__mgcp_timer_T1              DATASTRUCT._parm__mgcp_timer_T1
#define parm__mgcp_timer_T2              DATASTRUCT._parm__mgcp_timer_T2
#define parm__mgcp_timer_T3              DATASTRUCT._parm__mgcp_timer_T3
#define parm__mgcp_timer_T4              DATASTRUCT._parm__mgcp_timer_T4
#define v34_BE_modify_Gp_gain            DATASTRUCT._v34_BE_modify_Gp_gain
#define parm__speech_udp_dest_port       DATASTRUCT._parm__speech_udp_dest_port
#define stream_char_memory               DATASTRUCT._stream_char_memory
#define parm__ctcss_enc_gain             DATASTRUCT._parm__ctcss_enc_gain
#define prev_ncof                        DATASTRUCT._prev_ncof
#define s1_detector_slew_rate            DATASTRUCT._s1_detector_slew_rate
#define mvxx_coefs                       DATASTRUCT._mvxx_coefs
#define v34_tx_interpolator_size         DATASTRUCT._v34_tx_interpolator_size
#define train_on_data_512_slew           DATASTRUCT._train_on_data_512_slew
#define shared_btlz_tx_datap             DATASTRUCT._shared_btlz_tx_datap
#define parm__ata_user_message           DATASTRUCT._parm__ata_user_message
#define ec_error_poffset                 DATASTRUCT._ec_error_poffset
#define v90_shape_data                   DATASTRUCT._v90_shape_data
#define rd_lastoff_cnt                   DATASTRUCT._rd_lastoff_cnt
#define sonitrol_local_port              DATASTRUCT._sonitrol_local_port
#define v90_dpcm_dil_ltp                 DATASTRUCT._v90_dpcm_dil_ltp
#define ptloop_phdet_error_very_slow32   DATASTRUCT._ptloop_phdet_error_very_slow32
#define v92_pcm_decode_table             DATASTRUCT._v92_pcm_decode_table
#define picp_edit_buffer                 DATASTRUCT._picp_edit_buffer
#define stat__phone_call_start_time      DATASTRUCT._stat__phone_call_start_time
#define ph2n_probing_L1_log_P_buffer     DATASTRUCT._ph2n_probing_L1_log_P_buffer
#define sart_tx_count                    DATASTRUCT._sart_tx_count
#define rx_b1_frame_erase_flag           DATASTRUCT._rx_b1_frame_erase_flag
#define rf_fm_get_offset                 DATASTRUCT._rf_fm_get_offset
#define V90_RX_R_REVERSAL_WAIT           DATASTRUCT._V90_RX_R_REVERSAL_WAIT
#define sdt_off_threshold                DATASTRUCT._sdt_off_threshold
#define sigsave                          DATASTRUCT._sigsave
#define PH2P_POWR_LX_INITIAL_ROUNDING    DATASTRUCT._PH2P_POWR_LX_INITIAL_ROUNDING
#define dma_timer                        DATASTRUCT._dma_timer
#define output_sample                    DATASTRUCT._output_sample
#define stat__nat_rcv_discards           DATASTRUCT._stat__nat_rcv_discards
#define predicted_rx_xn_B1_Q_n_offset    DATASTRUCT._predicted_rx_xn_B1_Q_n_offset
#define retrain_real                     DATASTRUCT._retrain_real
#define dt_silence_state                 DATASTRUCT._dt_silence_state
#define v34_equalizer_train_16point      DATASTRUCT._v34_equalizer_train_16point
#define rx_lpf_buffer_complex            DATASTRUCT._rx_lpf_buffer_complex
#define parm__speech_enc_fill_slot_size  DATASTRUCT._parm__speech_enc_fill_slot_size
#define V90_RX_RETRAIN_Bt_THRESHOLD      DATASTRUCT._V90_RX_RETRAIN_Bt_THRESHOLD
#define tx_trans_packets                 DATASTRUCT._tx_trans_packets
#define set_dtmf_off_on_next_pass        DATASTRUCT._set_dtmf_off_on_next_pass
#define ANSam_trace_magphase_lpf_imag    DATASTRUCT._ANSam_trace_magphase_lpf_imag
#define g726_enc_bit_number              DATASTRUCT._g726_enc_bit_number
#define stat__dm_tx_bits_per_symbol      DATASTRUCT._stat__dm_tx_bits_per_symbol
#define ph4n_tx_receive_trellis          DATASTRUCT._ph4n_tx_receive_trellis
#define PCM_BTR_PRESET_PHASE             DATASTRUCT._PCM_BTR_PRESET_PHASE
#define dev_poh_pending                  DATASTRUCT._dev_poh_pending
#define guard_tone_increment             DATASTRUCT._guard_tone_increment
#define stat__net_current_dns_primary_address DATASTRUCT._stat__net_current_dns_primary_address
#define v34h_rx_r_bits                   DATASTRUCT._v34h_rx_r_bits
#define shadow_DNIS                      DATASTRUCT._shadow_DNIS
#define fax_fx_flag                      DATASTRUCT._fax_fx_flag
#define parm__ipbx_blocked_number_list   DATASTRUCT._parm__ipbx_blocked_number_list
#define sonitrol_ANI_DNIS_buffer         DATASTRUCT._sonitrol_ANI_DNIS_buffer
#define saved_v90trn_index_to_code       DATASTRUCT._saved_v90trn_index_to_code
#define parm__ata_internal_web_server_enable DATASTRUCT._parm__ata_internal_web_server_enable
#define encode_gain_exponent             DATASTRUCT._encode_gain_exponent
#define stat__speech_dec_fill_slot_size  DATASTRUCT._stat__speech_dec_fill_slot_size
#define parm__ata_help_url               DATASTRUCT._parm__ata_help_url
#define ph4n_rx_trained_qn_coef_imag     DATASTRUCT._ph4n_rx_trained_qn_coef_imag
#define parm__sdp_g723_codec_dyn_pt      DATASTRUCT._parm__sdp_g723_codec_dyn_pt
#define v92_system_ID_output             DATASTRUCT._v92_system_ID_output
#define asm_decode_packed_odd            DATASTRUCT._asm_decode_packed_odd
#define stat__nat_wan_end_point          DATASTRUCT._stat__nat_wan_end_point
#define parm__net_dns_primary_address    DATASTRUCT._parm__net_dns_primary_address
#define v90n_tx_CPx_type                 DATASTRUCT._v90n_tx_CPx_type
#define v90_frame_rx_dil_body_start      DATASTRUCT._v90_frame_rx_dil_body_start
#define speex_sb_dec_state               DATASTRUCT._speex_sb_dec_state
#define ANSam_trace_count_2100_imag      DATASTRUCT._ANSam_trace_count_2100_imag
#define g723_DecCng                      DATASTRUCT._g723_DecCng
#define equalized_yn_imag                DATASTRUCT._equalized_yn_imag
#define parm__sdp_g726_32_codec_dyn_pt   DATASTRUCT._parm__sdp_g726_32_codec_dyn_pt
#define PH2P_BG_SAMPLE_OFFSET_LENGTH     DATASTRUCT._PH2P_BG_SAMPLE_OFFSET_LENGTH
#define vppn_device_command_queue_in     DATASTRUCT._vppn_device_command_queue_in
#define interrupt_cpu_pcount             DATASTRUCT._interrupt_cpu_pcount
#define min_energy                       DATASTRUCT._min_energy
#define v34_yn_error_real                DATASTRUCT._v34_yn_error_real
#define nat_icmp_dst_addr                DATASTRUCT._nat_icmp_dst_addr
#define ph2n_tx_v92_ITU_marks_reserved   DATASTRUCT._ph2n_tx_v92_ITU_marks_reserved
#define v34_tx_yn_real                   DATASTRUCT._v34_tx_yn_real
#define ph4n_rx_auxiliary_option         DATASTRUCT._ph4n_rx_auxiliary_option
#define V90_TEST_LOG_INPUT_ENABLE        DATASTRUCT._V90_TEST_LOG_INPUT_ENABLE
#define legacy_response_expected         DATASTRUCT._legacy_response_expected
#define l_default_w0                     DATASTRUCT._l_default_w0
#define parm__report_event_mask          DATASTRUCT._parm__report_event_mask
#define sonitrol_v34_unreliable_counter  DATASTRUCT._sonitrol_v34_unreliable_counter
#define parm__codec_ring_detect_duration DATASTRUCT._parm__codec_ring_detect_duration
#define parm__mgcp_send_response_to_src_port DATASTRUCT._parm__mgcp_send_response_to_src_port
#define vppn_selector_next_channel       DATASTRUCT._vppn_selector_next_channel
#define special_data_pointer             DATASTRUCT._special_data_pointer
#define phone_ptt_debounce_count         DATASTRUCT._phone_ptt_debounce_count
#define parm__dm_v92_mse_cmn_bias        DATASTRUCT._parm__dm_v92_mse_cmn_bias
#define sip_timer_proc                   DATASTRUCT._sip_timer_proc
#define g722_e3l_nbl                     DATASTRUCT._g722_e3l_nbl
#define v34_TRN2_MSE_precode_value       DATASTRUCT._v34_TRN2_MSE_precode_value
#define v90n_rx_constel_index            DATASTRUCT._v90n_rx_constel_index
#define notch_datax32_300                DATASTRUCT._notch_datax32_300
#define frame_buffer_pointer             DATASTRUCT._frame_buffer_pointer
#define parm__sdp_g728_codec_dyn_pt      DATASTRUCT._parm__sdp_g728_codec_dyn_pt
#define ph2p_anal_maxrate                DATASTRUCT._ph2p_anal_maxrate
#define parm__ipbx_initial_dial_duration DATASTRUCT._parm__ipbx_initial_dial_duration
#define record_sample_rx_pcm             DATASTRUCT._record_sample_rx_pcm
#define DIL_probing_1st_repetition_table DATASTRUCT._DIL_probing_1st_repetition_table
#define v34s_short_renegotiations        DATASTRUCT._v34s_short_renegotiations
#define parm__net_isp_pppoe_enable       DATASTRUCT._parm__net_isp_pppoe_enable
#define fg_thread_table                  DATASTRUCT._fg_thread_table
#define xxx_rx_gain                      DATASTRUCT._xxx_rx_gain
#define ph2_rx_special_bpf_offset        DATASTRUCT._ph2_rx_special_bpf_offset
#define aux_rx_data                      DATASTRUCT._aux_rx_data
#define vppn_encode_packet_byte_flag     DATASTRUCT._vppn_encode_packet_byte_flag
#define v34_resync_vcomp_buffer_real32   DATASTRUCT._v34_resync_vcomp_buffer_real32
#define ph2p_anal_maxrate_results        DATASTRUCT._ph2p_anal_maxrate_results
#define nat_pkt_snap_ptr                 DATASTRUCT._nat_pkt_snap_ptr
#define sigdet_data                      DATASTRUCT._sigdet_data
#define parm__ata_factory_lock_bypass_enable DATASTRUCT._parm__ata_factory_lock_bypass_enable
#define fsk_rx_clock_phase_saved         DATASTRUCT._fsk_rx_clock_phase_saved
#define v34n_rx_train_16pt               DATASTRUCT._v34n_rx_train_16pt
#define var_sp_2                         DATASTRUCT._var_sp_2
#define v90h_rx_residue_length           DATASTRUCT._v90h_rx_residue_length
#define ph2n_measured_roundtrip_delay    DATASTRUCT._ph2n_measured_roundtrip_delay
#define tonemute_new_exp_check           DATASTRUCT._tonemute_new_exp_check
#define ph2p_fefo_ws_k_buffer            DATASTRUCT._ph2p_fefo_ws_k_buffer
#define dcd_diversion_count              DATASTRUCT._dcd_diversion_count
#define stat__vpcm_robbed_bit_mask       DATASTRUCT._stat__vpcm_robbed_bit_mask
#define vppn_statistics_channel          DATASTRUCT._vppn_statistics_channel
#define ph2p_anal_variance_15_table      DATASTRUCT._ph2p_anal_variance_15_table
#define lec__tx_output                   DATASTRUCT._lec__tx_output
#define V34_SLEW_COS_RETRAIN             DATASTRUCT._V34_SLEW_COS_RETRAIN
#define sdt_reversal_timeout             DATASTRUCT._sdt_reversal_timeout
#define ipod_rx_v34_status               DATASTRUCT._ipod_rx_v34_status
#define sip_prefer_tcp                   DATASTRUCT._sip_prefer_tcp
#define orig_v8_CM_count                 DATASTRUCT._orig_v8_CM_count
#define parm__v92_MH_test_wait           DATASTRUCT._parm__v92_MH_test_wait
#define parm__vppn_device_vanished_debounce DATASTRUCT._parm__vppn_device_vanished_debounce
#define bpfsp                            DATASTRUCT._bpfsp
#define initial_pos                      DATASTRUCT._initial_pos
#define g_silenceEn                      DATASTRUCT._g_silenceEn
#define ipod_msg_rx_sig_off_offset       DATASTRUCT._ipod_msg_rx_sig_off_offset
#define ANSam_trace_min_imag             DATASTRUCT._ANSam_trace_min_imag
#define possible_rates                   DATASTRUCT._possible_rates
#define qplsp_low_rate_chn_read          DATASTRUCT._qplsp_low_rate_chn_read
#define rx_lpf_buffer_imag               DATASTRUCT._rx_lpf_buffer_imag
#define tdt_index                        DATASTRUCT._tdt_index
#define ph2p_anal_maxrates_04_table      DATASTRUCT._ph2p_anal_maxrates_04_table
#define sip_mesg_proc                    DATASTRUCT._sip_mesg_proc
#define pcm_btr_coef_error               DATASTRUCT._pcm_btr_coef_error
#define guard_tone_amplitude             DATASTRUCT._guard_tone_amplitude
#define parm__dm_v34_carrier_mask        DATASTRUCT._parm__dm_v34_carrier_mask
#define stat__sms_message                DATASTRUCT._stat__sms_message
#define retrain_limit                    DATASTRUCT._retrain_limit
#define cp_relative_energy               DATASTRUCT._cp_relative_energy
#define PH2_TX_OFFSET_LENGTH             DATASTRUCT._PH2_TX_OFFSET_LENGTH
#define cc_rx_PP_tone_noise_ratio        DATASTRUCT._cc_rx_PP_tone_noise_ratio
#define pcm_eq_which_flag                DATASTRUCT._pcm_eq_which_flag
#define lec__sum_buffer40                DATASTRUCT._lec__sum_buffer40
#define ec_coef_delta_buffer             DATASTRUCT._ec_coef_delta_buffer
#define Az_dec                           DATASTRUCT._Az_dec
#define lec__nlp_controller_count        DATASTRUCT._lec__nlp_controller_count
#define ph2n_parm_optional_tx_attenuation_enable DATASTRUCT._ph2n_parm_optional_tx_attenuation_enable
#define stat__ipod_dtmf_detect           DATASTRUCT._stat__ipod_dtmf_detect
#define v90_rx_ALL_energy_log            DATASTRUCT._v90_rx_ALL_energy_log
#define ANSam_detect_2100                DATASTRUCT._ANSam_detect_2100
#define v34_tx_decor_buffer              DATASTRUCT._v34_tx_decor_buffer
#define ph2_rx_dcd_integration_time      DATASTRUCT._ph2_rx_dcd_integration_time
#define pushed_demod_imag                DATASTRUCT._pushed_demod_imag
#define v92_system_ID_echo               DATASTRUCT._v92_system_ID_echo
#define current_input_imag               DATASTRUCT._current_input_imag
#define baud_tx_break_duration           DATASTRUCT._baud_tx_break_duration
#define equalizer_coef_real              DATASTRUCT._equalizer_coef_real
#define renegociate_threshold            DATASTRUCT._renegociate_threshold
#define ph2p_anal_log_N_plus_start       DATASTRUCT._ph2p_anal_log_N_plus_start
#define parm__pump_v34_transmit_level    DATASTRUCT._parm__pump_v34_transmit_level
#define parm__sdp_speex_codec_name       DATASTRUCT._parm__sdp_speex_codec_name
#define output_filter_v34_routine        DATASTRUCT._output_filter_v34_routine
#define parm__slac_message_waiting_frequency DATASTRUCT._parm__slac_message_waiting_frequency
#define parm__ipbx_led_use_and_hold      DATASTRUCT._parm__ipbx_led_use_and_hold
#define ac97_dma_rx_irq                  DATASTRUCT._ac97_dma_rx_irq
#define ph1n_tx_index_ANSpcm             DATASTRUCT._ph1n_tx_index_ANSpcm
#define pcm_test_disable_inner_rx_rate_double DATASTRUCT._pcm_test_disable_inner_rx_rate_double
#define v90n_tx_receive_constel_mapping  DATASTRUCT._v90n_tx_receive_constel_mapping
#define parm__dm_v34_symbol_difference_max DATASTRUCT._parm__dm_v34_symbol_difference_max
#define lec__alpha_error                 DATASTRUCT._lec__alpha_error
#define v34p_bg_block_count              DATASTRUCT._v34p_bg_block_count
#define sart_tx_buffer_element           DATASTRUCT._sart_tx_buffer_element
#define cc_tx_guard_tone_phase           DATASTRUCT._cc_tx_guard_tone_phase
#define fg_timer_list                    DATASTRUCT._fg_timer_list
#define gpf_search_end                   DATASTRUCT._gpf_search_end
#define legacy_ssp_timer                 DATASTRUCT._legacy_ssp_timer
#define v90_frame_tx_index               DATASTRUCT._v90_frame_tx_index
#define nat_tcp_header_size              DATASTRUCT._nat_tcp_header_size
#define current_bg_state                 DATASTRUCT._current_bg_state
#define dev_poh_count                    DATASTRUCT._dev_poh_count
#define parm__line_rx_exponent           DATASTRUCT._parm__line_rx_exponent
#define v90n_parm_tx_pcm_3429_option     DATASTRUCT._v90n_parm_tx_pcm_3429_option
#define pcm_xmit_deshape_poffset         DATASTRUCT._pcm_xmit_deshape_poffset
#define ph2_INFOMARKS_detect_enable      DATASTRUCT._ph2_INFOMARKS_detect_enable
#define dgidet_tune_equalizer_conv       DATASTRUCT._dgidet_tune_equalizer_conv
#define old_rc                           DATASTRUCT._old_rc
#define parm__ipbx_dial_direct           DATASTRUCT._parm__ipbx_dial_direct
#define parm__speech_rtp_little_endian   DATASTRUCT._parm__speech_rtp_little_endian
#define g_melp_par                       DATASTRUCT._g_melp_par
#define previous_call_ids                DATASTRUCT._previous_call_ids
#define parm__ipbx_fc_unattended_transfer DATASTRUCT._parm__ipbx_fc_unattended_transfer
#define legacy_tx_buffer                 DATASTRUCT._legacy_tx_buffer
#define parm__mgcp_use_nat_discovery     DATASTRUCT._parm__mgcp_use_nat_discovery
#define faxparm_parm__SART_mode          DATASTRUCT._faxparm_parm__SART_mode
#define v92_rx_Su_disable_flag           DATASTRUCT._v92_rx_Su_disable_flag
#define parm__ipbx_voice_rx_gain         DATASTRUCT._parm__ipbx_voice_rx_gain
#define v34_rx_trellis_lookback_poffset  DATASTRUCT._v34_rx_trellis_lookback_poffset
#define dtmf_match_count                 DATASTRUCT._dtmf_match_count
#define ph2n_rxtx_sh2_enable             DATASTRUCT._ph2n_rxtx_sh2_enable
#define parm__ipbx_fc_block_anonymous_enable DATASTRUCT._parm__ipbx_fc_block_anonymous_enable
#define parm__test_tone_gain             DATASTRUCT._parm__test_tone_gain
#define ANSAM_LPF_SLEW_1ST               DATASTRUCT._ANSAM_LPF_SLEW_1ST
#define ANSam_trace_magphase_max_imag    DATASTRUCT._ANSam_trace_magphase_max_imag
#define parm__enc_mode                   DATASTRUCT._parm__enc_mode
#define parm__radio_fsk_mode_enable      DATASTRUCT._parm__radio_fsk_mode_enable
#define vppn_device_firmware_read        DATASTRUCT._vppn_device_firmware_read
#define v27_rx_poly                      DATASTRUCT._v27_rx_poly
#define pcm_x_law_index_to_code_convert  DATASTRUCT._pcm_x_law_index_to_code_convert
#define parm__ipbx_fc_do_not_disturb_enable DATASTRUCT._parm__ipbx_fc_do_not_disturb_enable
#define v90_rx_dil_ucode                 DATASTRUCT._v90_rx_dil_ucode
#define orig_counter                     DATASTRUCT._orig_counter
#define input_sample                     DATASTRUCT._input_sample
#define parm__dtmf_pad_duration          DATASTRUCT._parm__dtmf_pad_duration
#define sdp_parser                       DATASTRUCT._sdp_parser
#define parm__jpeg_capture_time          DATASTRUCT._parm__jpeg_capture_time
#define sequence_reg                     DATASTRUCT._sequence_reg
#define special_equal_counter            DATASTRUCT._special_equal_counter
#define v34h_rx_buffer1                  DATASTRUCT._v34h_rx_buffer1
#define parm__pump_v92_transmit_level    DATASTRUCT._parm__pump_v92_transmit_level
#define PCM_EQUALIZER_FF_SHIFT           DATASTRUCT._PCM_EQUALIZER_FF_SHIFT
#define v34h_rx_buffer2                  DATASTRUCT._v34h_rx_buffer2
#define V34_S_SIGNAL_MAX_ENERGY          DATASTRUCT._V34_S_SIGNAL_MAX_ENERGY
#define parm__dm_v34_mse_cmn_bias        DATASTRUCT._parm__dm_v34_mse_cmn_bias
#define parm__nat_timeout_icmp           DATASTRUCT._parm__nat_timeout_icmp
#define ph2p_anal_log_adjust             DATASTRUCT._ph2p_anal_log_adjust
#define monitor_be2                      DATASTRUCT._monitor_be2
#define stat__sart_rx_mode               DATASTRUCT._stat__sart_rx_mode
#define eqout_lagging_imag               DATASTRUCT._eqout_lagging_imag
#define tmp_p_e                          DATASTRUCT._tmp_p_e
#define dtmf_off_counter                 DATASTRUCT._dtmf_off_counter
#define stat__ipbx_speech_codec_mode     DATASTRUCT._stat__ipbx_speech_codec_mode
#define parm__net_router_commands        DATASTRUCT._parm__net_router_commands
#define parm__nat_stun_server_domain_name DATASTRUCT._parm__nat_stun_server_domain_name
#define test_s_msw                       DATASTRUCT._test_s_msw
#define ph2_tx_dcd_threshold             DATASTRUCT._ph2_tx_dcd_threshold
#define encoded_size                     DATASTRUCT._encoded_size
#define parm__voip_default_user_name     DATASTRUCT._parm__voip_default_user_name
#define count_fr0                        DATASTRUCT._count_fr0
#define parm__ipbx_fc_priority_forward_disable DATASTRUCT._parm__ipbx_fc_priority_forward_disable
#define number_permanent_fg_states       DATASTRUCT._number_permanent_fg_states
#define parm__ipbx_fxo_security_code_string DATASTRUCT._parm__ipbx_fxo_security_code_string
#define mem_w                            DATASTRUCT._mem_w
#define V34S_RECP_8K0_INFO0hend_to_Sdet  DATASTRUCT._V34S_RECP_8K0_INFO0hend_to_Sdet
#define parm__ipbx_caller_id_outbound_current_enable DATASTRUCT._parm__ipbx_caller_id_outbound_current_enable
#define v90n_rx_constel_mapping          DATASTRUCT._v90n_rx_constel_mapping
#define parm__repeater_talkthrough_enable DATASTRUCT._parm__repeater_talkthrough_enable
#define v90_rx_SdN_samples_remaining     DATASTRUCT._v90_rx_SdN_samples_remaining
#define parm__sip_timer_registration_max DATASTRUCT._parm__sip_timer_registration_max
#define v92_rx_decoder_wait_count        DATASTRUCT._v92_rx_decoder_wait_count
#define v34_tx_remote_gain_adjust        DATASTRUCT._v34_tx_remote_gain_adjust
#define fg_thread_max_usage              DATASTRUCT._fg_thread_max_usage
#define stat__disconnect_tone_cadence_detect_mask DATASTRUCT._stat__disconnect_tone_cadence_detect_mask
#define bg_event_insert                  DATASTRUCT._bg_event_insert
#define sigdet_data16                    DATASTRUCT._sigdet_data16
#define parm__phone_sle_4428_psc         DATASTRUCT._parm__phone_sle_4428_psc
#define dgi_error32                      DATASTRUCT._dgi_error32
#define conv_energy32                    DATASTRUCT._conv_energy32
#define stat__net_pppoe_server_ip_addess DATASTRUCT._stat__net_pppoe_server_ip_addess
#define v34f_eqc_DC_angle                DATASTRUCT._v34f_eqc_DC_angle
#define ph2s_short_phase2_flag           DATASTRUCT._ph2s_short_phase2_flag
#define parm__rtp_dtmf_generate_digit    DATASTRUCT._parm__rtp_dtmf_generate_digit
#define equalizer_buffer_imag            DATASTRUCT._equalizer_buffer_imag
#define global_height                    DATASTRUCT._global_height
#define v90n_rx_CP_type                  DATASTRUCT._v90n_rx_CP_type
#define ch_seize_counter                 DATASTRUCT._ch_seize_counter
#define v34_yn_perfect_real              DATASTRUCT._v34_yn_perfect_real
#define v34_rx_xn_real                   DATASTRUCT._v34_rx_xn_real
#define automation_not_available         DATASTRUCT._automation_not_available
#define aux_tx_baud                      DATASTRUCT._aux_tx_baud
#define descrambler_bits_per_baud        DATASTRUCT._descrambler_bits_per_baud
#define tone_priority_ms                 DATASTRUCT._tone_priority_ms
#define lec__alpha                       DATASTRUCT._lec__alpha
#define cc_rx_delay_buffer_real          DATASTRUCT._cc_rx_delay_buffer_real
#define v34n_parm_shaping_option         DATASTRUCT._v34n_parm_shaping_option
#define l_dontcare                       DATASTRUCT._l_dontcare
#define g722_e4l_szl                     DATASTRUCT._g722_e4l_szl
#define Vad_Min                          DATASTRUCT._Vad_Min
#define ph2p_anal_log_Z_plus_start       DATASTRUCT._ph2p_anal_log_Z_plus_start
#define mbx_rx_build_bit_cnt             DATASTRUCT._mbx_rx_build_bit_cnt
#define dc_offset_display_counter        DATASTRUCT._dc_offset_display_counter
#define comn_v8_TONEq_done               DATASTRUCT._comn_v8_TONEq_done
#define rx_clock_phase                   DATASTRUCT._rx_clock_phase
#define V34_SLEW_SIN_BE                  DATASTRUCT._V34_SLEW_SIN_BE
#define parm__ipbx_busy_forward_dial_string DATASTRUCT._parm__ipbx_busy_forward_dial_string
#define v34s_gear_counter                DATASTRUCT._v34s_gear_counter
#define ph2n_probing_train_16pt          DATASTRUCT._ph2n_probing_train_16pt
#define ANSam_max_tracking_count         DATASTRUCT._ANSam_max_tracking_count
#define faxdet_value_v21                 DATASTRUCT._faxdet_value_v21
#define v90_shape_test_offset            DATASTRUCT._v90_shape_test_offset
#define parm__speech_mac_ethernet_type   DATASTRUCT._parm__speech_mac_ethernet_type
#define v34f_eqc_diff_DC_magnitude       DATASTRUCT._v34f_eqc_diff_DC_magnitude
#define parm__sip_use_received_via_info  DATASTRUCT._parm__sip_use_received_via_info
#define parm__phone_volume_adjust_time   DATASTRUCT._parm__phone_volume_adjust_time
#define parm__codec_port_rx_gain         DATASTRUCT._parm__codec_port_rx_gain
#define v34_rx_xn_tilde_imag             DATASTRUCT._v34_rx_xn_tilde_imag
#define rd_cadence_history_1             DATASTRUCT._rd_cadence_history_1
#define rd_cadence_history_2             DATASTRUCT._rd_cadence_history_2
#define parm__ipbx_hookflash_maximum     DATASTRUCT._parm__ipbx_hookflash_maximum
#define V34_BE_SLEW_MEDIUM               DATASTRUCT._V34_BE_SLEW_MEDIUM
#define pcm_xmit_reshape_poffset         DATASTRUCT._pcm_xmit_reshape_poffset
#define V34_RESYNC_LOG2_MEASURE_ADJUST   DATASTRUCT._V34_RESYNC_LOG2_MEASURE_ADJUST
#define parm__dpbx_led_call_forward      DATASTRUCT._parm__dpbx_led_call_forward
#define v34_pnt3_MSE_value               DATASTRUCT._v34_pnt3_MSE_value
#define v92n_rx_prefilter_gain           DATASTRUCT._v92n_rx_prefilter_gain
#define ipod_iface_rx_next_seqnum        DATASTRUCT._ipod_iface_rx_next_seqnum
#define v34_resync_data_buffer_real      DATASTRUCT._v34_resync_data_buffer_real
#define ph1_tx_ANSpcm_exponent           DATASTRUCT._ph1_tx_ANSpcm_exponent
#define stat__speech_enc_frame_based_active DATASTRUCT._stat__speech_enc_frame_based_active
#define parm__ipbx_pstn_call_waiting_tone_default DATASTRUCT._parm__ipbx_pstn_call_waiting_tone_default
#define parm__spk_monitor_tx_gain        DATASTRUCT._parm__spk_monitor_tx_gain
#define sonitrol_caller_name             DATASTRUCT._sonitrol_caller_name
#define v34_resync_vcomp_buffer_imag32   DATASTRUCT._v34_resync_vcomp_buffer_imag32
#define v90h_rx_control_pointer          DATASTRUCT._v90h_rx_control_pointer
#define parm__slac_message_waiting_transition DATASTRUCT._parm__slac_message_waiting_transition
#define parm__ata_boot_rom_revision      DATASTRUCT._parm__ata_boot_rom_revision
#define parm__dtmf_detector_period       DATASTRUCT._parm__dtmf_detector_period
#define parm__speech_dec_slot_cnt        DATASTRUCT._parm__speech_dec_slot_cnt
#define g722_d3h_nbh                     DATASTRUCT._g722_d3h_nbh
#define bulk_delay_buffer_pntr           DATASTRUCT._bulk_delay_buffer_pntr
#define ipod_htd_fbdnt_payload_size      DATASTRUCT._ipod_htd_fbdnt_payload_size
#define echo_canceller_display_counter   DATASTRUCT._echo_canceller_display_counter
#define vppn_packet_selector_state       DATASTRUCT._vppn_packet_selector_state
#define parm__rtp_dtmf_generate_duration DATASTRUCT._parm__rtp_dtmf_generate_duration
#define sigdet_data40                    DATASTRUCT._sigdet_data40
#define parm__camera_number              DATASTRUCT._parm__camera_number
#define v90_tx_ph34_state                DATASTRUCT._v90_tx_ph34_state
#define notch_datay32_420                DATASTRUCT._notch_datay32_420
#define ph2p_bg_sample_offset            DATASTRUCT._ph2p_bg_sample_offset
#define stat__nat_snd_udp                DATASTRUCT._stat__nat_snd_udp
#define l_prev_par                       DATASTRUCT._l_prev_par
#define lec__nlp_cng_detect              DATASTRUCT._lec__nlp_cng_detect
#define parm__speech_report_mask         DATASTRUCT._parm__speech_report_mask
#define stat__speech_drop_frame_candidate DATASTRUCT._stat__speech_drop_frame_candidate
#define sport0_shift_count               DATASTRUCT._sport0_shift_count
#define current_rate                     DATASTRUCT._current_rate
#define pcm_btr_measurement_real         DATASTRUCT._pcm_btr_measurement_real
#define g711_rx_dtx_prev_active          DATASTRUCT._g711_rx_dtx_prev_active
#define local_buffer_pointer_start       DATASTRUCT._local_buffer_pointer_start
#define silence_valid                    DATASTRUCT._silence_valid
#define parm__ipbx_fc_busy_forward_disable DATASTRUCT._parm__ipbx_fc_busy_forward_disable
#define asm_decodep                      DATASTRUCT._asm_decodep
#define parm__net_assigned_mtu           DATASTRUCT._parm__net_assigned_mtu
#define equalizer_slew_fast              DATASTRUCT._equalizer_slew_fast
#define parm__net_ddns_host_name         DATASTRUCT._parm__net_ddns_host_name
#define impedance_monitor_last_fail_state DATASTRUCT._impedance_monitor_last_fail_state
#define rx_dtmf_count                    DATASTRUCT._rx_dtmf_count
#define REVERSAL_TIMEOUT_INIT            DATASTRUCT._REVERSAL_TIMEOUT_INIT
#define lsp_new_q_ptr                    DATASTRUCT._lsp_new_q_ptr
#define v34_pnt0_MSE_value               DATASTRUCT._v34_pnt0_MSE_value
#define stat__nat_wan_firewalled         DATASTRUCT._stat__nat_wan_firewalled
#define parm__fxpmp_silence_duration     DATASTRUCT._parm__fxpmp_silence_duration
#define parm__ipbx_fc_busy_number_redial DATASTRUCT._parm__ipbx_fc_busy_number_redial
#define answ_v8_JM_count                 DATASTRUCT._answ_v8_JM_count
#define parm__ipbx_distinctive_ring_service DATASTRUCT._parm__ipbx_distinctive_ring_service
#define parm__sip_timer_invite_expires   DATASTRUCT._parm__sip_timer_invite_expires
#define parm__ctcss_enc_enable           DATASTRUCT._parm__ctcss_enc_enable
#define v92n_tx_CPd_word                 DATASTRUCT._v92n_tx_CPd_word
#define pcm_eq_errtine                   DATASTRUCT._pcm_eq_errtine
#define parm__speech_enc_frame_rate      DATASTRUCT._parm__speech_enc_frame_rate
#define ph2_rx_signal_detect_filter32    DATASTRUCT._ph2_rx_signal_detect_filter32
#define tx_clock_phase_remote            DATASTRUCT._tx_clock_phase_remote
#define V34_RXI_COUNT                    DATASTRUCT._V34_RXI_COUNT
#define lookback_output_real             DATASTRUCT._lookback_output_real
#define v34_tx_xn_local_real             DATASTRUCT._v34_tx_xn_local_real
#define PH2P_ANAL_16PT_NOISE_LIMIT       DATASTRUCT._PH2P_ANAL_16PT_NOISE_LIMIT
#define sync_bit                         DATASTRUCT._sync_bit
#define v34n_rx_INFO1c_body              DATASTRUCT._v34n_rx_INFO1c_body
#define V34S_RUN_8K0_ONE_SECOND_TIME     DATASTRUCT._V34S_RUN_8K0_ONE_SECOND_TIME
#define v34_rx_zn_tilde_real             DATASTRUCT._v34_rx_zn_tilde_real
#define parm__sip_distinctive_ring_names DATASTRUCT._parm__sip_distinctive_ring_names
#define THD_measurement_noise            DATASTRUCT._THD_measurement_noise
#define ph2p_fefo_test_delta32           DATASTRUCT._ph2p_fefo_test_delta32
#define parm__ipbx_key_confirmation_tone DATASTRUCT._parm__ipbx_key_confirmation_tone
#define pcm_AL_value                     DATASTRUCT._pcm_AL_value
#define dprmbx_outgoing_data_sent        DATASTRUCT._dprmbx_outgoing_data_sent
#define parm__ctcss_dec_frequency        DATASTRUCT._parm__ctcss_dec_frequency
#define prev_ma                          DATASTRUCT._prev_ma
#define CONVERT_AGC_1_ENERGY_TARGET_LOG  DATASTRUCT._CONVERT_AGC_1_ENERGY_TARGET_LOG
#define fax_save_state_old               DATASTRUCT._fax_save_state_old
#define g722_rxs_qmf_space               DATASTRUCT._g722_rxs_qmf_space
#define last_sig_level                   DATASTRUCT._last_sig_level
#define sart_tx_hybrid_packed_length     DATASTRUCT._sart_tx_hybrid_packed_length
#define ec_fast_slew                     DATASTRUCT._ec_fast_slew
#define v90_rx_R_reversal_wait           DATASTRUCT._v90_rx_R_reversal_wait
#define tilt_del                         DATASTRUCT._tilt_del
#define sonitrol_ANI                     DATASTRUCT._sonitrol_ANI
#define parm__vppn_device_timeslot       DATASTRUCT._parm__vppn_device_timeslot
#define V90_RX_RETRAIN_DETECT_LIMIT      DATASTRUCT._V90_RX_RETRAIN_DETECT_LIMIT
#define ata_led_use_mask_ipbx            DATASTRUCT._ata_led_use_mask_ipbx
#define nat_pkt_ip_tun_ptr               DATASTRUCT._nat_pkt_ip_tun_ptr
#define v34_rx_yn_equalized_real32       DATASTRUCT._v34_rx_yn_equalized_real32
#define stat__nat_rcv_alg_delivers       DATASTRUCT._stat__nat_rcv_alg_delivers
#define going_up                         DATASTRUCT._going_up
#define parm__selcall_enc_tone_period    DATASTRUCT._parm__selcall_enc_tone_period
#define V34_TXI_ADJUST                   DATASTRUCT._V34_TXI_ADJUST
#define parm__ipbx_call_holding_rering_tone DATASTRUCT._parm__ipbx_call_holding_rering_tone
#define ipod_rx_frame_counter            DATASTRUCT._ipod_rx_frame_counter
#define parm__net_dns_parallel_search_mode DATASTRUCT._parm__net_dns_parallel_search_mode
#define jitter_jitter_imag               DATASTRUCT._jitter_jitter_imag
#define parm__sdp_g722p2_codec_dyn_pt    DATASTRUCT._parm__sdp_g722p2_codec_dyn_pt
#define equalizer_leading_imag           DATASTRUCT._equalizer_leading_imag
#define v90_rx_retrain_delay_buffer      DATASTRUCT._v90_rx_retrain_delay_buffer
#define v34n_rx_hi_carrier_option        DATASTRUCT._v34n_rx_hi_carrier_option
#define sh_Acf                           DATASTRUCT._sh_Acf
#define btrec_p2400                      DATASTRUCT._btrec_p2400
#define V34_TX_PRE_EMPH_COEFS            DATASTRUCT._V34_TX_PRE_EMPH_COEFS
#define lec__nlp_activity_counter        DATASTRUCT._lec__nlp_activity_counter
#define v34_frame_rx_receive_crc         DATASTRUCT._v34_frame_rx_receive_crc
#define v90_tx_MP_frame_sent             DATASTRUCT._v90_tx_MP_frame_sent
#define CID_data                         DATASTRUCT._CID_data
#define impedance_monitor_tx_power32     DATASTRUCT._impedance_monitor_tx_power32
#define v34_resync_mean_buffer_real      DATASTRUCT._v34_resync_mean_buffer_real
#define stat__nat_wan_no_translation     DATASTRUCT._stat__nat_wan_no_translation
#define ipod_htd_voice_flags             DATASTRUCT._ipod_htd_voice_flags
#define stat__nat_snd_ip_forward         DATASTRUCT._stat__nat_snd_ip_forward
#define parm__codec_disconnect_polarity_enable DATASTRUCT._parm__codec_disconnect_polarity_enable
#define rf_dma_debug                     DATASTRUCT._rf_dma_debug
#define tx_measurment_buffer_1           DATASTRUCT._tx_measurment_buffer_1
#define debug_fract10                    DATASTRUCT._debug_fract10
#define parm__voip_echo_canceller_tail_length DATASTRUCT._parm__voip_echo_canceller_tail_length
#define rd_post_event                    DATASTRUCT._rd_post_event
#define sonitrol_wiznet_workaround_ip    DATASTRUCT._sonitrol_wiznet_workaround_ip
#define v34n_tx_remote_to_local_maxrate  DATASTRUCT._v34n_tx_remote_to_local_maxrate
#define stat__caller_id_msg_cksum        DATASTRUCT._stat__caller_id_msg_cksum
#define parm__codec_disconnect_tone_2_enable DATASTRUCT._parm__codec_disconnect_tone_2_enable
#define v34_pp_result_log_table          DATASTRUCT._v34_pp_result_log_table
#define v34n_tx_hi_data_rate_option      DATASTRUCT._v34n_tx_hi_data_rate_option
#define ipod_msg_xx_payload_buffer       DATASTRUCT._ipod_msg_xx_payload_buffer
#define cc_rx_lpf_buffer_imag            DATASTRUCT._cc_rx_lpf_buffer_imag
#define v32ter_nonlinear_control         DATASTRUCT._v32ter_nonlinear_control
#define v34h_tx_half_data_frame_counter  DATASTRUCT._v34h_tx_half_data_frame_counter
#define ph2n_rx_receive_clock            DATASTRUCT._ph2n_rx_receive_clock
#define parm__ipbx_call_station_ring_default DATASTRUCT._parm__ipbx_call_station_ring_default
#define v34h_tx_r_bits                   DATASTRUCT._v34h_tx_r_bits
#define ipbx_digit_detect_end_event      DATASTRUCT._ipbx_digit_detect_end_event
#define sonitrol_remote_lcfw_port        DATASTRUCT._sonitrol_remote_lcfw_port
#define s1_detector_variables            DATASTRUCT._s1_detector_variables
#define V34S_LEN_T_2ND_CHECK_WAIT        DATASTRUCT._V34S_LEN_T_2ND_CHECK_WAIT
#define ph2n_rx_use_shaping              DATASTRUCT._ph2n_rx_use_shaping
#define vppn_device_command_ack_index    DATASTRUCT._vppn_device_command_ack_index
#define parm__sip_timer_registration_min DATASTRUCT._parm__sip_timer_registration_min
#define sart_tx_read_index               DATASTRUCT._sart_tx_read_index
#define stat__vppn_device_statistics     DATASTRUCT._stat__vppn_device_statistics
#define saved_rx_mapper_loop_counter     DATASTRUCT._saved_rx_mapper_loop_counter
#define dtmf_col_harmonic                DATASTRUCT._dtmf_col_harmonic
#define scal_res2_buf                    DATASTRUCT._scal_res2_buf
#define parm__speech_rtp_tone_replace_audio DATASTRUCT._parm__speech_rtp_tone_replace_audio
#define parm__ata_lcd_menu_password      DATASTRUCT._parm__ata_lcd_menu_password
#define stat__net_current_ip_address     DATASTRUCT._stat__net_current_ip_address
#define dtmf_detector_counter            DATASTRUCT._dtmf_detector_counter
#define parm__rtp_vocal_to_net_payload_map DATASTRUCT._parm__rtp_vocal_to_net_payload_map
#define n16_bits                         DATASTRUCT._n16_bits
#define parm__ipbx_message_wait_dial_tone DATASTRUCT._parm__ipbx_message_wait_dial_tone
#define parm__sip_incoming_resubscribe_interval DATASTRUCT._parm__sip_incoming_resubscribe_interval
#define g722_d4h_bh                      DATASTRUCT._g722_d4h_bh
#define v34_resync_total_buffer          DATASTRUCT._v34_resync_total_buffer
#define cc_tx_eye_map_gain               DATASTRUCT._cc_tx_eye_map_gain
#define parm__ipbx_dial_string           DATASTRUCT._parm__ipbx_dial_string
#define stat__speech_enc_mbx_cnt         DATASTRUCT._stat__speech_enc_mbx_cnt
#define prev_pitch_pitch_vq              DATASTRUCT._prev_pitch_pitch_vq
#define parm__tripwire_audio_record      DATASTRUCT._parm__tripwire_audio_record
#define BAUD_AGC_REFERENCE               DATASTRUCT._BAUD_AGC_REFERENCE
#define v34h_rx_e0_last_pointer          DATASTRUCT._v34h_rx_e0_last_pointer
#define descrambler_mask_table           DATASTRUCT._descrambler_mask_table
#define convert_adjust_output_gain       DATASTRUCT._convert_adjust_output_gain
#define v90_rx_retrain_Bt_energy_log     DATASTRUCT._v90_rx_retrain_Bt_energy_log
#define energy_delta_threshold_v17       DATASTRUCT._energy_delta_threshold_v17
#define parm__dm_v92_negotiation         DATASTRUCT._parm__dm_v92_negotiation
#define lec__td_tone_det_cnt             DATASTRUCT._lec__td_tone_det_cnt
#define old_A                            DATASTRUCT._old_A
#define v34_bulk_extra_input_offset      DATASTRUCT._v34_bulk_extra_input_offset
#define v34h_rx_V0_m_register            DATASTRUCT._v34h_rx_V0_m_register
#define p18_demod_real                   DATASTRUCT._p18_demod_real
#define cmr_notch_count                  DATASTRUCT._cmr_notch_count
#define nat_pkt_icmp_ip_ptr              DATASTRUCT._nat_pkt_icmp_ip_ptr
#define parm__slac_message_waiting_type  DATASTRUCT._parm__slac_message_waiting_type
#define v34n_rx_MP0_body                 DATASTRUCT._v34n_rx_MP0_body
#define v34_frame_rx_E_found             DATASTRUCT._v34_frame_rx_E_found
#define stat__daa_ring_state             DATASTRUCT._stat__daa_ring_state
#define postHPFOutHis_hi                 DATASTRUCT._postHPFOutHis_hi
#define v92_MH_timeout_flag              DATASTRUCT._v92_MH_timeout_flag
#define vppn_decode_packet_index         DATASTRUCT._vppn_decode_packet_index
#define ipod_msg_tx_sig_level            DATASTRUCT._ipod_msg_tx_sig_level
#define lookback_input_real              DATASTRUCT._lookback_input_real
#define timer_flag                       DATASTRUCT._timer_flag
#define thread_variable                  DATASTRUCT._thread_variable
#define stat__ipod_chan_state            DATASTRUCT._stat__ipod_chan_state
#define ph2p_anal_maxrates_10_table      DATASTRUCT._ph2p_anal_maxrates_10_table
#define var_sp_av                        DATASTRUCT._var_sp_av
#define sense_silence_keep               DATASTRUCT._sense_silence_keep
#define parm__ipbx_led_use_and_waiting   DATASTRUCT._parm__ipbx_led_use_and_waiting
#define DIL_probing_pad_ot_table         DATASTRUCT._DIL_probing_pad_ot_table
#define pcm_pstfilter_ff                 DATASTRUCT._pcm_pstfilter_ff
#define v17_ept_length                   DATASTRUCT._v17_ept_length
#define v34s_prev_prev_phase_roll_second DATASTRUCT._v34s_prev_prev_phase_roll_second
#define parm__sip_refer_authentication   DATASTRUCT._parm__sip_refer_authentication
#define g722_d4h_dh                      DATASTRUCT._g722_d4h_dh
#define ph2_INFO_detect_state            DATASTRUCT._ph2_INFO_detect_state
#define new_scores_poffset               DATASTRUCT._new_scores_poffset
#define sdt_peak_hold                    DATASTRUCT._sdt_peak_hold
#define lsp_old_q_ptr                    DATASTRUCT._lsp_old_q_ptr
#define metric0                          DATASTRUCT._metric0
#define g711a_plc_overlapbuf             DATASTRUCT._g711a_plc_overlapbuf
#define metric1                          DATASTRUCT._metric1
#define send_to_connect                  DATASTRUCT._send_to_connect
#define g722_d4h_szh                     DATASTRUCT._g722_d4h_szh
#define metric2                          DATASTRUCT._metric2
#define fax_continuous_silence_counter   DATASTRUCT._fax_continuous_silence_counter
#define metric3                          DATASTRUCT._metric3
#define tonemute_delay_buffer            DATASTRUCT._tonemute_delay_buffer
#define g722_d4h_oldrh                   DATASTRUCT._g722_d4h_oldrh
#define pcm_folding_half_length          DATASTRUCT._pcm_folding_half_length
#define fg_thread_offsets                DATASTRUCT._fg_thread_offsets
#define qla                              DATASTRUCT._qla
#define l_firstTime                      DATASTRUCT._l_firstTime
#define cc_rx_pc_is_also_running_flag    DATASTRUCT._cc_rx_pc_is_also_running_flag
#define sh_sid_sav                       DATASTRUCT._sh_sid_sav
#define ph2s_INFO0_ack_counter           DATASTRUCT._ph2s_INFO0_ack_counter
#define FALL_fallback_flag               DATASTRUCT._FALL_fallback_flag
#define v92_rx_decoder_ep_poffset        DATASTRUCT._v92_rx_decoder_ep_poffset
#define fsk_run_dcd_monitor              DATASTRUCT._fsk_run_dcd_monitor
#define rx_rate_conv_pointer             DATASTRUCT._rx_rate_conv_pointer
#define v92_rx_eye_pointer               DATASTRUCT._v92_rx_eye_pointer
#define ata_check_code                   DATASTRUCT._ata_check_code
#define g722_rx_qmf_data_offset          DATASTRUCT._g722_rx_qmf_data_offset
#define PCM_LEN_8K0_MIN_GEAR_TRAIN       DATASTRUCT._PCM_LEN_8K0_MIN_GEAR_TRAIN
#define g600_s                           DATASTRUCT._g600_s
#define impedance_monitor_future_rx      DATASTRUCT._impedance_monitor_future_rx
#define lec__doubletalk_probe            DATASTRUCT._lec__doubletalk_probe
#define faxparm_parm__CED_generate       DATASTRUCT._faxparm_parm__CED_generate
#define g711b_cng_flag                   DATASTRUCT._g711b_cng_flag
#define faxdet_ansam_count               DATASTRUCT._faxdet_ansam_count
#define v34_rx_B1_enable_flag            DATASTRUCT._v34_rx_B1_enable_flag
#define ph2_AB_edge_correl_last          DATASTRUCT._ph2_AB_edge_correl_last
#define dpbx_previous_service            DATASTRUCT._dpbx_previous_service
#define l_erase                          DATASTRUCT._l_erase
#define saved_precalculated_correct      DATASTRUCT._saved_precalculated_correct
#define V90_SdN_REMAIN                   DATASTRUCT._V90_SdN_REMAIN
#define bid_dtx                          DATASTRUCT._bid_dtx
#define g711a_plc_pitchbufstart          DATASTRUCT._g711a_plc_pitchbufstart
#define parm__dm_carrier_detect_duration DATASTRUCT._parm__dm_carrier_detect_duration
#define v34n_rx_MD_length                DATASTRUCT._v34n_rx_MD_length
#define ipod_sec_timer                   DATASTRUCT._ipod_sec_timer
#define v34h_tx_z8_table                 DATASTRUCT._v34h_tx_z8_table
#define parm__jpeg_delete_fifo           DATASTRUCT._parm__jpeg_delete_fifo
#define parm__test_tone_enable           DATASTRUCT._parm__test_tone_enable
#define parm__ipbx_brief_pause_duration  DATASTRUCT._parm__ipbx_brief_pause_duration
#define fsk_rx_clock_cycles_saved        DATASTRUCT._fsk_rx_clock_cycles_saved
#define SN_LT0_shift                     DATASTRUCT._SN_LT0_shift
#define parm__sdp_mpeg4_codec_name       DATASTRUCT._parm__sdp_mpeg4_codec_name
#define pcm_eq_flag                      DATASTRUCT._pcm_eq_flag
#define fsk_local_interpolator_buffer_offset DATASTRUCT._fsk_local_interpolator_buffer_offset
#define v90h_data_frame_bit_count        DATASTRUCT._v90h_data_frame_bit_count
#define ata_random_delay_cfg             DATASTRUCT._ata_random_delay_cfg
#define parm__ipbx_led_call_holding      DATASTRUCT._parm__ipbx_led_call_holding
#define impedance_monitor_future_rx_offset DATASTRUCT._impedance_monitor_future_rx_offset
#define v34_frame_rx_bit_count           DATASTRUCT._v34_frame_rx_bit_count
#define v34_rx_pn_tilde_real             DATASTRUCT._v34_rx_pn_tilde_real
#define parm__dtmf_row_no_tone_level     DATASTRUCT._parm__dtmf_row_no_tone_level
#define ph2n_tx_v92_mode_bits            DATASTRUCT._ph2n_tx_v92_mode_bits
#define interrupt_running_fg             DATASTRUCT._interrupt_running_fg
#define circb_index                      DATASTRUCT._circb_index
#define temp2_ilbc_buffer                DATASTRUCT._temp2_ilbc_buffer
#define V90_DECN_RBS_BIAS_PARAMETER      DATASTRUCT._V90_DECN_RBS_BIAS_PARAMETER
#define v90n_rx_pcm_3429_option          DATASTRUCT._v90n_rx_pcm_3429_option
#define v34_TRN1_MSE_value               DATASTRUCT._v34_TRN1_MSE_value
#define equalized_imag                   DATASTRUCT._equalized_imag
#define train_on_data_switch             DATASTRUCT._train_on_data_switch
#define monitor_sample_agc_2             DATASTRUCT._monitor_sample_agc_2
#define ptloop_1st_order_slew            DATASTRUCT._ptloop_1st_order_slew
#define l_good_pitch                     DATASTRUCT._l_good_pitch
#define cc_rx_ANAL_angle                 DATASTRUCT._cc_rx_ANAL_angle
#define v90_shape_current_state          DATASTRUCT._v90_shape_current_state
#define impedance_monitor_future_tx      DATASTRUCT._impedance_monitor_future_tx
#define Ksi_min_var                      DATASTRUCT._Ksi_min_var
#define v92n_rx_wait_CPu                 DATASTRUCT._v92n_rx_wait_CPu
#define ph4n_tx_ITU_bit_reserved         DATASTRUCT._ph4n_tx_ITU_bit_reserved
#define v34_BE_Gn                        DATASTRUCT._v34_BE_Gn
#define sdt_found_detect_flag            DATASTRUCT._sdt_found_detect_flag
#define v34_BE_Gp                        DATASTRUCT._v34_BE_Gp
#define fsk_ANSam_enable                 DATASTRUCT._fsk_ANSam_enable
#define parm__mpeg4_rate_control_mode    DATASTRUCT._parm__mpeg4_rate_control_mode
#define ph2n_sm_INFO1c_end_delay         DATASTRUCT._ph2n_sm_INFO1c_end_delay
#define postHPFOutHis_lo                 DATASTRUCT._postHPFOutHis_lo
#define v92_test_client_type             DATASTRUCT._v92_test_client_type
#define circb_shift                      DATASTRUCT._circb_shift
#define start_data_flag                  DATASTRUCT._start_data_flag
#define ata_need_mac                     DATASTRUCT._ata_need_mac
#define parm__ipbx_blocked_number_enable DATASTRUCT._parm__ipbx_blocked_number_enable
#define pcm_rx_RBS_current_symbol        DATASTRUCT._pcm_rx_RBS_current_symbol
#define cbk_mst1_s                       DATASTRUCT._cbk_mst1_s
#define parm__ipbx_priority_forward_service DATASTRUCT._parm__ipbx_priority_forward_service
#define parm__mgcp_timer_retransmition_max DATASTRUCT._parm__mgcp_timer_retransmition_max
#define parm__net_dhcp_server_rebinding_time DATASTRUCT._parm__net_dhcp_server_rebinding_time
#define parm__ipbx_line_name             DATASTRUCT._parm__ipbx_line_name
#define stat__nat_rcv_pptp               DATASTRUCT._stat__nat_rcv_pptp
#define asm_ans_seen                     DATASTRUCT._asm_ans_seen
#define ph4n_rx_primary_channel_maxrate  DATASTRUCT._ph4n_rx_primary_channel_maxrate
#define baud_tx_16_bit_mode              DATASTRUCT._baud_tx_16_bit_mode
#define dgi_ref_meanA                    DATASTRUCT._dgi_ref_meanA
#define v34_rx_yn_equalized_imag32       DATASTRUCT._v34_rx_yn_equalized_imag32
#define v34h_tx_g4_table                 DATASTRUCT._v34h_tx_g4_table
#define dgi_ref_meanB                    DATASTRUCT._dgi_ref_meanB
#define vppn_device_firmware_address     DATASTRUCT._vppn_device_firmware_address
#define sart_rx_overflow                 DATASTRUCT._sart_rx_overflow
#define pcm_btr_enable_postset_flag      DATASTRUCT._pcm_btr_enable_postset_flag
#define old_wsp                          DATASTRUCT._old_wsp
#define g722_tx_qmf_space                DATASTRUCT._g722_tx_qmf_space
#define saved_scrambler_input            DATASTRUCT._saved_scrambler_input
#define parm__ipbx_priority_forward_enable DATASTRUCT._parm__ipbx_priority_forward_enable
#define lec__data_size_exp_adjust        DATASTRUCT._lec__data_size_exp_adjust
#define ipod_command_fnbdt_enable        DATASTRUCT._ipod_command_fnbdt_enable
#define g722_rxd_qmf_space               DATASTRUCT._g722_rxd_qmf_space
#define v90_shape_coefs                  DATASTRUCT._v90_shape_coefs
#define v34h_rx_residue                  DATASTRUCT._v34h_rx_residue
#define baud_tx_data_unit                DATASTRUCT._baud_tx_data_unit
#define sense_rate_reduce_counter        DATASTRUCT._sense_rate_reduce_counter
#define V90S_LEN_8K0_DIL_STATISTICS      DATASTRUCT._V90S_LEN_8K0_DIL_STATISTICS
#define parm__net_dhcp_server_renewal_time DATASTRUCT._parm__net_dhcp_server_renewal_time
#define sonitrol_line_fail_count         DATASTRUCT._sonitrol_line_fail_count
#define tone_detector_num_tones          DATASTRUCT._tone_detector_num_tones
#define dec_Vad                          DATASTRUCT._dec_Vad
#define tonemute_poffset                 DATASTRUCT._tonemute_poffset
#define tone_detector_data               DATASTRUCT._tone_detector_data
#define g722_enc_shigh                   DATASTRUCT._g722_enc_shigh
#define affine_real                      DATASTRUCT._affine_real
#define l_codewd74                       DATASTRUCT._l_codewd74
#define ph2_rx_btrec_clock_state         DATASTRUCT._ph2_rx_btrec_clock_state
#define line_tx_intp                     DATASTRUCT._line_tx_intp
#define parm__ata_time_zone              DATASTRUCT._parm__ata_time_zone
#define ph2n_tx_required_attenuation     DATASTRUCT._ph2n_tx_required_attenuation
#define v34_symbol_diff_encode_data      DATASTRUCT._v34_symbol_diff_encode_data
#define parm__ipbx_message_waiting_ring_splash DATASTRUCT._parm__ipbx_message_waiting_ring_splash
#define rf_tuning_enable                 DATASTRUCT._rf_tuning_enable
#define rf_dma_difference                DATASTRUCT._rf_dma_difference
#define V34_EQUALIZER_SCALE              DATASTRUCT._V34_EQUALIZER_SCALE
#define dec_freq_prev                    DATASTRUCT._dec_freq_prev
#define g729_test_compressed_data        DATASTRUCT._g729_test_compressed_data
#define parm__ipbx_call_waiting_current_enable DATASTRUCT._parm__ipbx_call_waiting_current_enable
#define parm__net_static_config_enable   DATASTRUCT._parm__net_static_config_enable
#define fsk_correlator_flag_holdoff      DATASTRUCT._fsk_correlator_flag_holdoff
#define gpf_index_offset                 DATASTRUCT._gpf_index_offset
#define v92_rx_MD_length                 DATASTRUCT._v92_rx_MD_length
#define v8_tx_QC_data_flag               DATASTRUCT._v8_tx_QC_data_flag
#define stat__phone_timer_elapsed_time   DATASTRUCT._stat__phone_timer_elapsed_time
#define parm__ata_processor_die_id       DATASTRUCT._parm__ata_processor_die_id
#define v34_rx_interpolator_size         DATASTRUCT._v34_rx_interpolator_size
#define test_input_index                 DATASTRUCT._test_input_index
#define monitor_be2_offset               DATASTRUCT._monitor_be2_offset
#define g168_err_average                 DATASTRUCT._g168_err_average
#define v92n_tx_CPd_body_start           DATASTRUCT._v92n_tx_CPd_body_start
#define l_codewd84                       DATASTRUCT._l_codewd84
#define lec__alpha_rxx_mag               DATASTRUCT._lec__alpha_rxx_mag
#define ipod_command_fax_enable          DATASTRUCT._ipod_command_fax_enable
#define parm__selcall_enc_lead_in        DATASTRUCT._parm__selcall_enc_lead_in
#define pcm_HI_MSE_value                 DATASTRUCT._pcm_HI_MSE_value
#define v90n_tx_nominal_power            DATASTRUCT._v90n_tx_nominal_power
#define tx_train_point_B                 DATASTRUCT._tx_train_point_B
#define tx_train_point_D                 DATASTRUCT._tx_train_point_D
#define V34S_PARTIAL_CONVERGENCE_THRESHOLD DATASTRUCT._V34S_PARTIAL_CONVERGENCE_THRESHOLD
#define lsfq                             DATASTRUCT._lsfq
#define prev_pitch_sc_ana                DATASTRUCT._prev_pitch_sc_ana
#define coder_frame_length               DATASTRUCT._coder_frame_length
#define stat__vppn_epoch_clock_indication DATASTRUCT._stat__vppn_epoch_clock_indication
#define pcm_rx_TRN1C_log_energy          DATASTRUCT._pcm_rx_TRN1C_log_energy
#define stat__speech_rtp_timestamp       DATASTRUCT._stat__speech_rtp_timestamp
#define g_hp1_coeff_sec1                 DATASTRUCT._g_hp1_coeff_sec1
#define g_hp1_coeff_sec2                 DATASTRUCT._g_hp1_coeff_sec2
#define g_hp1_coeff_sec3                 DATASTRUCT._g_hp1_coeff_sec3
#define agc_2_lpf32                      DATASTRUCT._agc_2_lpf32
#define bpviq                            DATASTRUCT._bpviq
#define ipod_htd_voice_payload_size      DATASTRUCT._ipod_htd_voice_payload_size
#define parm__ipbx_fc_outgoing_block_enable DATASTRUCT._parm__ipbx_fc_outgoing_block_enable
#define pcm_DC_offset_sum_32             DATASTRUCT._pcm_DC_offset_sum_32
#define lec__cng_train_freeze            DATASTRUCT._lec__cng_train_freeze
#define parm__cmr_notch_select           DATASTRUCT._parm__cmr_notch_select
#define parm__v8__vpcm_availability      DATASTRUCT._parm__v8__vpcm_availability
#define parm__analog_loopback            DATASTRUCT._parm__analog_loopback
#define local_ec_slew                    DATASTRUCT._local_ec_slew
#define subscribe_parser                 DATASTRUCT._subscribe_parser
#define parm__speech_enc_host_flag       DATASTRUCT._parm__speech_enc_host_flag
#define ph2p_L1_log_power_display_buffer DATASTRUCT._ph2p_L1_log_power_display_buffer
#define v90n_rx_apcm_data_rate_option    DATASTRUCT._v90n_rx_apcm_data_rate_option
#define v34_tx_remote_data_enable        DATASTRUCT._v34_tx_remote_data_enable
#define ANSam_magnitude_min32            DATASTRUCT._ANSam_magnitude_min32
#define v34h_rx_m_ijk_ring_index_buffer  DATASTRUCT._v34h_rx_m_ijk_ring_index_buffer
#define ph2p_anal_preemph1_pointer       DATASTRUCT._ph2p_anal_preemph1_pointer
#define prev_tilt                        DATASTRUCT._prev_tilt
#define parm__sip_subscribe_authentication DATASTRUCT._parm__sip_subscribe_authentication
#define V34S_ORIG_8K0_1RT_Jsrt_to_S_SNdet DATASTRUCT._V34S_ORIG_8K0_1RT_Jsrt_to_S_SNdet
#define double_output0                   DATASTRUCT._double_output0
#define alphacorr                        DATASTRUCT._alphacorr
#define double_output1                   DATASTRUCT._double_output1
#define vppn_previous_device_temporary_id DATASTRUCT._vppn_previous_device_temporary_id
#define ph2n_probing_Gr_gain             DATASTRUCT._ph2n_probing_Gr_gain
#define delta_energy_threshold           DATASTRUCT._delta_energy_threshold
#define v90_frame_tx_cp_body_start       DATASTRUCT._v90_frame_tx_cp_body_start
#define fsk_interpolator_buffer_real     DATASTRUCT._fsk_interpolator_buffer_real
#define monitor_state_value              DATASTRUCT._monitor_state_value
#define v92_system_ID_energy_nrm         DATASTRUCT._v92_system_ID_energy_nrm
#define dtmf_unclamp_delay               DATASTRUCT._dtmf_unclamp_delay
#define asm_decode_mbx                   DATASTRUCT._asm_decode_mbx
#define v90n_tx_CP_type                  DATASTRUCT._v90n_tx_CP_type
#define v34n_sm_INFO1c_end_delay         DATASTRUCT._v34n_sm_INFO1c_end_delay
#define guard_tone_enable                DATASTRUCT._guard_tone_enable
#define parm__ata_firmware_revision      DATASTRUCT._parm__ata_firmware_revision
#define parm__sdp_cn_codec_dyn_pt        DATASTRUCT._parm__sdp_cn_codec_dyn_pt
#define v34_tx_xn_real                   DATASTRUCT._v34_tx_xn_real
#define top_lpc                          DATASTRUCT._top_lpc
#define pcm_equalizer_ff_poffset         DATASTRUCT._pcm_equalizer_ff_poffset
#define stat__v92_upstream_digital_attenuation DATASTRUCT._stat__v92_upstream_digital_attenuation
#define pcm_AL_peak_MSE_max              DATASTRUCT._pcm_AL_peak_MSE_max
#define parm__pump_transmit_level        DATASTRUCT._parm__pump_transmit_level
#define ph2n_probing_maxrate             DATASTRUCT._ph2n_probing_maxrate
#define ipod_dth_coded_speech_buffer     DATASTRUCT._ipod_dth_coded_speech_buffer
#define parm__vppn_device_registration_next DATASTRUCT._parm__vppn_device_registration_next
#define faxdet_data_ansam_cntr           DATASTRUCT._faxdet_data_ansam_cntr
#define v34s_reneg_init_S_to_SN_to_retrain DATASTRUCT._v34s_reneg_init_S_to_SN_to_retrain
#define parm__dtmf_low_tone_gain         DATASTRUCT._parm__dtmf_low_tone_gain
#define pcm_equalizer_ep_buffer          DATASTRUCT._pcm_equalizer_ep_buffer
#define g722_d3l_nbl                     DATASTRUCT._g722_d3l_nbl
#define ph2n_rx_2800_option              DATASTRUCT._ph2n_rx_2800_option
#define v92_system_ID_codec_in           DATASTRUCT._v92_system_ID_codec_in
#define uicp_tone_played                 DATASTRUCT._uicp_tone_played
#define sense_silence_change             DATASTRUCT._sense_silence_change
#define parm__speech_rtp_dtmf_payload_type DATASTRUCT._parm__speech_rtp_dtmf_payload_type
#define parm__sip_answ_user_name         DATASTRUCT._parm__sip_answ_user_name
#define sart_tx_hybrid_packed_mode       DATASTRUCT._sart_tx_hybrid_packed_mode
#define parm__sdp_g711a_codec_name       DATASTRUCT._parm__sdp_g711a_codec_name
#define p18_baud_UVW_imag                DATASTRUCT._p18_baud_UVW_imag
#define picp_menu_item_edit              DATASTRUCT._picp_menu_item_edit
#define parm__sdp_gsm_efr_codec_name     DATASTRUCT._parm__sdp_gsm_efr_codec_name
#define v92_rx_decoder_ep_alpha_gain     DATASTRUCT._v92_rx_decoder_ep_alpha_gain
#define lec__tec_error                   DATASTRUCT._lec__tec_error
#define stat__vppn_device_info           DATASTRUCT._stat__vppn_device_info
#define v92_rx_decoder_ff_coefs          DATASTRUCT._v92_rx_decoder_ff_coefs
#define pre_ec_power                     DATASTRUCT._pre_ec_power
#define parm__speakerphone_rx_gain       DATASTRUCT._parm__speakerphone_rx_gain
#define bg_svalue_queue                  DATASTRUCT._bg_svalue_queue
#define tx_clock_cycles_per_sample       DATASTRUCT._tx_clock_cycles_per_sample
#define ANSam_trace_magphase_imag        DATASTRUCT._ANSam_trace_magphase_imag
#define phone_speakerphone_tx_volume     DATASTRUCT._phone_speakerphone_tx_volume
#define v90n_tx_receive_attenuation      DATASTRUCT._v90n_tx_receive_attenuation
#define ph2p_anal_variance_14_table      DATASTRUCT._ph2p_anal_variance_14_table
#define v90_shape_4_min32                DATASTRUCT._v90_shape_4_min32
#define pattern_test_delay32             DATASTRUCT._pattern_test_delay32
#define energy_total40                   DATASTRUCT._energy_total40
#define ph2_tx_baud_current              DATASTRUCT._ph2_tx_baud_current
#define cc_rx_S_center_edge_ratio        DATASTRUCT._cc_rx_S_center_edge_ratio
#define pcm_equalizer_ff_buffer          DATASTRUCT._pcm_equalizer_ff_buffer
#define sart_tx_private_buffer           DATASTRUCT._sart_tx_private_buffer
#define detect_energy_lpf1_32            DATASTRUCT._detect_energy_lpf1_32
#define tonemute_old_exp_check           DATASTRUCT._tonemute_old_exp_check
#define V34_TXI_COUNT                    DATASTRUCT._V34_TXI_COUNT
#define bulk_delay_local_poffset         DATASTRUCT._bulk_delay_local_poffset
#define stat__nat_snd_requests           DATASTRUCT._stat__nat_snd_requests
#define sync_state                       DATASTRUCT._sync_state
#define v34n_tx_INFO1a_body              DATASTRUCT._v34n_tx_INFO1a_body
#define parm__net_private_netmask        DATASTRUCT._parm__net_private_netmask
#define ph2p_anal_maxrates_03_table      DATASTRUCT._ph2p_anal_maxrates_03_table
#define v34s_rev_count                   DATASTRUCT._v34s_rev_count
#define ph2n_rx_acknowledge              DATASTRUCT._ph2n_rx_acknowledge
#define interrupt_cpu_icount             DATASTRUCT._interrupt_cpu_icount
#define v34h_tx_M_number_rings           DATASTRUCT._v34h_tx_M_number_rings
#define faxparm_active__SART_mode        DATASTRUCT._faxparm_active__SART_mode
#define stat__nat_rcv_frag_required      DATASTRUCT._stat__nat_rcv_frag_required
#define parm__ipbx_speed_dial_array      DATASTRUCT._parm__ipbx_speed_dial_array
#define convert_agc_2_output_log         DATASTRUCT._convert_agc_2_output_log
#define parm__dm_v90_shaping_lookahead   DATASTRUCT._parm__dm_v90_shaping_lookahead
#define voicedEn                         DATASTRUCT._voicedEn
#define ph2_INFO_correl_last             DATASTRUCT._ph2_INFO_correl_last
#define parm__speech_enc_host_addr       DATASTRUCT._parm__speech_enc_host_addr
#define rate_reduction_buffer_real       DATASTRUCT._rate_reduction_buffer_real
#define pcm_btr_gain_exponent            DATASTRUCT._pcm_btr_gain_exponent
#define sonitrol_lc_type1_shutdown       DATASTRUCT._sonitrol_lc_type1_shutdown
#define v29_save_equalized_real          DATASTRUCT._v29_save_equalized_real
#define v34_BE_log_Gp_prev               DATASTRUCT._v34_BE_log_Gp_prev
#define ALPHA0                           DATASTRUCT._ALPHA0
#define faxdet_data_grl                  DATASTRUCT._faxdet_data_grl
#define v92n_rx_MH_body                  DATASTRUCT._v92n_rx_MH_body
#define parm__sdp_g729_codec_name        DATASTRUCT._parm__sdp_g729_codec_name
#define v34n_tx_data_rate                DATASTRUCT._v34n_tx_data_rate
#define v34_BE_neg_log_magnitude         DATASTRUCT._v34_BE_neg_log_magnitude
#define PCM_BTR_FREQ_ERROR_RATIO         DATASTRUCT._PCM_BTR_FREQ_ERROR_RATIO
#define pastCoeff                        DATASTRUCT._pastCoeff
#define tx_rate_conv_data_buffer         DATASTRUCT._tx_rate_conv_data_buffer
#define stat__caller_id_msg              DATASTRUCT._stat__caller_id_msg
#define code_load_duration               DATASTRUCT._code_load_duration
#define v34h_rx_q_bits_per_2D_subgroup   DATASTRUCT._v34h_rx_q_bits_per_2D_subgroup
#define ph2n_probing_receive_level       DATASTRUCT._ph2n_probing_receive_level
#define parm__sdp_session_owner          DATASTRUCT._parm__sdp_session_owner
#define stat__speech_rx_dtx_flag         DATASTRUCT._stat__speech_rx_dtx_flag
#define parm__rtp_net_to_vocal_payload_map DATASTRUCT._parm__rtp_net_to_vocal_payload_map
#define v92_system_ID_modulo_rbs         DATASTRUCT._v92_system_ID_modulo_rbs
#define pcm_ec_conv_energy_log           DATASTRUCT._pcm_ec_conv_energy_log
#define parm__mgcp_timer_retransmition_min DATASTRUCT._parm__mgcp_timer_retransmition_min
#define lsp_new_dtx                      DATASTRUCT._lsp_new_dtx
#define ph2p_powr_SB_power_adjust        DATASTRUCT._ph2p_powr_SB_power_adjust
#define gpf_RRexp                        DATASTRUCT._gpf_RRexp
#define parm__net_dhcp_server_enable     DATASTRUCT._parm__net_dhcp_server_enable
#define parm__speech_g711_transition     DATASTRUCT._parm__speech_g711_transition
#define parm__ipbx_fxo_pstn_call_enable  DATASTRUCT._parm__ipbx_fxo_pstn_call_enable
#define parm__sip_nat_keep_alive_interval DATASTRUCT._parm__sip_nat_keep_alive_interval
#define enc_seed                         DATASTRUCT._enc_seed
#define stat__speech_dec_frame_mtr       DATASTRUCT._stat__speech_dec_frame_mtr
#define pcm_saved_point                  DATASTRUCT._pcm_saved_point
#define monitor_sample_fast_relative_threshold DATASTRUCT._monitor_sample_fast_relative_threshold
#define pcm_eq_error                     DATASTRUCT._pcm_eq_error
#define stat__speech_enc_overflow_cnt    DATASTRUCT._stat__speech_enc_overflow_cnt
#define tone_generator_silence           DATASTRUCT._tone_generator_silence
#define ata_first_update                 DATASTRUCT._ata_first_update
#define ph2p_anal_maxrate_lookup_pointer DATASTRUCT._ph2p_anal_maxrate_lookup_pointer
#define ph2p_anal_log_R_buffer           DATASTRUCT._ph2p_anal_log_R_buffer
#define parm__sip_response_code_sit1     DATASTRUCT._parm__sip_response_code_sit1
#define affine_ptloop_imag               DATASTRUCT._affine_ptloop_imag
#define parm__sip_response_code_sit2     DATASTRUCT._parm__sip_response_code_sit2
#define PCM_LEN_8K0_EQC_TRN1A_1ST        DATASTRUCT._PCM_LEN_8K0_EQC_TRN1A_1ST
#define parm__sip_response_code_sit3     DATASTRUCT._parm__sip_response_code_sit3
#define parm__sip_response_code_sit4     DATASTRUCT._parm__sip_response_code_sit4
#define parm__net_router_globalstar_baudrate DATASTRUCT._parm__net_router_globalstar_baudrate
#define test_2_lsw                       DATASTRUCT._test_2_lsw
#define max_number_fg_comp               DATASTRUCT._max_number_fg_comp
#define ec_medium_shift_slew_remote      DATASTRUCT._ec_medium_shift_slew_remote
#define stat__cp_rd_within_detect        DATASTRUCT._stat__cp_rd_within_detect
#define parm__cp_rd_cycle_period_max     DATASTRUCT._parm__cp_rd_cycle_period_max
#define PCM_LEN_8K0_GEAR_FLOOR_HOLDOFF   DATASTRUCT._PCM_LEN_8K0_GEAR_FLOOR_HOLDOFF
#define cc_rx_ALL_energy_log             DATASTRUCT._cc_rx_ALL_energy_log
#define parm__ipbx_bridge_pstn_call_enable DATASTRUCT._parm__ipbx_bridge_pstn_call_enable
#define lpc_del                          DATASTRUCT._lpc_del
#define parm__dm_options_mask            DATASTRUCT._parm__dm_options_mask
#define g711a_plc_poffset                DATASTRUCT._g711a_plc_poffset
#define send__v8__call_function          DATASTRUCT._send__v8__call_function
#define pcm_ff_equalizer_size            DATASTRUCT._pcm_ff_equalizer_size
#define parm__speech_enc_slot_size       DATASTRUCT._parm__speech_enc_slot_size
#define tmp_baud_sum_complex             DATASTRUCT._tmp_baud_sum_complex
#define ph1_rx_TONEq_detect_count        DATASTRUCT._ph1_rx_TONEq_detect_count
#define ph4n_rx_train_precoding          DATASTRUCT._ph4n_rx_train_precoding
#define PCM_LEN_8K0_MAX_ECC_TRAIN        DATASTRUCT._PCM_LEN_8K0_MAX_ECC_TRAIN
#define v34n_rx_local_to_remote_maxrate  DATASTRUCT._v34n_rx_local_to_remote_maxrate
#define FALL_mse_value                   DATASTRUCT._FALL_mse_value
#define clnt_ctx                         DATASTRUCT._clnt_ctx
#define dcd_diversion_status             DATASTRUCT._dcd_diversion_status
#define sdt_data_buffer_real             DATASTRUCT._sdt_data_buffer_real
#define v90_frame_tx_cp_body_cm          DATASTRUCT._v90_frame_tx_cp_body_cm
#define ph4n_tx_call_to_answer_maxrate   DATASTRUCT._ph4n_tx_call_to_answer_maxrate
#define ph2n_tx_v90_ITU_bits_reserved    DATASTRUCT._ph2n_tx_v90_ITU_bits_reserved
#define v34_rx_trellis_distance_4D       DATASTRUCT._v34_rx_trellis_distance_4D
#define lec__alpha_rxx_exp               DATASTRUCT._lec__alpha_rxx_exp
#define v90_frame_tx_dil_body_start      DATASTRUCT._v90_frame_tx_dil_body_start
#define txs_out_vxxmod_remote            DATASTRUCT._txs_out_vxxmod_remote
#define ipod_msg_rx_coder                DATASTRUCT._ipod_msg_rx_coder
#define rx_interpolator_buffer_real      DATASTRUCT._rx_interpolator_buffer_real
#define V34_TRN2_MSE_REPORT_RATE         DATASTRUCT._V34_TRN2_MSE_REPORT_RATE
#define fsk_ANSam_tx_passband_coefs_buffer_internal DATASTRUCT._fsk_ANSam_tx_passband_coefs_buffer_internal
#define parm__led_latch                  DATASTRUCT._parm__led_latch
#define ph2p_fefo_powr_phase_offset_buffer DATASTRUCT._ph2p_fefo_powr_phase_offset_buffer
#define convert_log__exponent            DATASTRUCT._convert_log__exponent
#define v34n_parm_lo_carrier_option      DATASTRUCT._v34n_parm_lo_carrier_option
#define dcd_threshold                    DATASTRUCT._dcd_threshold
#define monitor_input_sample             DATASTRUCT._monitor_input_sample
#define dpbx_led_special_off_pattern     DATASTRUCT._dpbx_led_special_off_pattern
#define DIL_probing_index_value          DATASTRUCT._DIL_probing_index_value
#define tx_passband_offset               DATASTRUCT._tx_passband_offset
#define ata_sample_record_fd             DATASTRUCT._ata_sample_record_fd
#define v92_system_ID_inputA             DATASTRUCT._v92_system_ID_inputA
#define cp_valid                         DATASTRUCT._cp_valid
#define maximum_dtmf_off                 DATASTRUCT._maximum_dtmf_off
#define v90_rx_dil_ucode_ptr             DATASTRUCT._v90_rx_dil_ucode_ptr
#define bpfdelin                         DATASTRUCT._bpfdelin
#define stat__nat_snd_frag_failed        DATASTRUCT._stat__nat_snd_frag_failed
#define parm__ipbx_priority_forward_dial_string DATASTRUCT._parm__ipbx_priority_forward_dial_string
#define perfect_imag                     DATASTRUCT._perfect_imag
#define ivbuf_pitchAuto                  DATASTRUCT._ivbuf_pitchAuto
#define ph2_rxtx_rate_conv_modulo_counter DATASTRUCT._ph2_rxtx_rate_conv_modulo_counter
#define amrDec_struct                    DATASTRUCT._amrDec_struct
#define ph2_tx_eye_imag_previous         DATASTRUCT._ph2_tx_eye_imag_previous
#define YY_LT                            DATASTRUCT._YY_LT
#define V34_PRE_HI_EQUALIZER_COEFS       DATASTRUCT._V34_PRE_HI_EQUALIZER_COEFS
#define ata_retry_count                  DATASTRUCT._ata_retry_count
#define v34f_eqc_co_DC_real              DATASTRUCT._v34f_eqc_co_DC_real
#define ec_fast_shift_slew_local         DATASTRUCT._ec_fast_shift_slew_local
#define dgidet_ec_counter                DATASTRUCT._dgidet_ec_counter
#define pcm_btr_AkQk_error               DATASTRUCT._pcm_btr_AkQk_error
#define sonitrol_franchise_id            DATASTRUCT._sonitrol_franchise_id
#define agc_2_variable_buffer            DATASTRUCT._agc_2_variable_buffer
#define g722_d4h_sg                      DATASTRUCT._g722_d4h_sg
#define g722_d4h_sh                      DATASTRUCT._g722_d4h_sh
#define parm__ata_provider_lock_enable   DATASTRUCT._parm__ata_provider_lock_enable
#define baud_tx_break_tmr                DATASTRUCT._baud_tx_break_tmr
#define cc_rx_demodulator_phase          DATASTRUCT._cc_rx_demodulator_phase
#define THD_measurement_actual           DATASTRUCT._THD_measurement_actual
#define v34_rx_qn_hat_pointer            DATASTRUCT._v34_rx_qn_hat_pointer
#define parm__speech_enc_dtmf_digit_mask DATASTRUCT._parm__speech_enc_dtmf_digit_mask
#define parm__ipbx_bridge_billing_delay_duration DATASTRUCT._parm__ipbx_bridge_billing_delay_duration
#define l_noise_cof                      DATASTRUCT._l_noise_cof
#define uicp_service                     DATASTRUCT._uicp_service
#define nat_private_port                 DATASTRUCT._nat_private_port
#define ata_need_boot                    DATASTRUCT._ata_need_boot
#define PH2P_ANAL_TRANSMIT_GAIN          DATASTRUCT._PH2P_ANAL_TRANSMIT_GAIN
#define ANSW_LEN_MS_NOMINAL_REVERSAL     DATASTRUCT._ANSW_LEN_MS_NOMINAL_REVERSAL
#define v34_local_fetching_flag          DATASTRUCT._v34_local_fetching_flag
#define previous_half_input_sample       DATASTRUCT._previous_half_input_sample
#define bfi600                           DATASTRUCT._bfi600
#define stat__speech_noise_detect        DATASTRUCT._stat__speech_noise_detect
#define parm__ipbx_fc_call_waiting_disable_once DATASTRUCT._parm__ipbx_fc_call_waiting_disable_once
#define ANSAM_LPF_SLEW_2ND               DATASTRUCT._ANSAM_LPF_SLEW_2ND
#define tone_priority_index              DATASTRUCT._tone_priority_index
#define overrun_counter                  DATASTRUCT._overrun_counter
#define l_prev_gain_dec                  DATASTRUCT._l_prev_gain_dec
#define nat_remote_port                  DATASTRUCT._nat_remote_port
#define stat__cp_rd_ringtype             DATASTRUCT._stat__cp_rd_ringtype
#define enc_sid_gain                     DATASTRUCT._enc_sid_gain
#define parm__dm_v34_mse_data_bias       DATASTRUCT._parm__dm_v34_mse_data_bias
#define ph2_tx_eye_real_previous         DATASTRUCT._ph2_tx_eye_real_previous
#define v34s_special_local_train_length  DATASTRUCT._v34s_special_local_train_length
#define v92_tx_repeat_CPd_flag           DATASTRUCT._v92_tx_repeat_CPd_flag
#define g722_d4l_szl                     DATASTRUCT._g722_d4l_szl
#define ph2p_anal_log_Whi                DATASTRUCT._ph2p_anal_log_Whi
#define ipod_msg_tx_sig_off_offset       DATASTRUCT._ipod_msg_tx_sig_off_offset
#define parm__ipbx_fxo_autoanswer_anonymous_enable DATASTRUCT._parm__ipbx_fxo_autoanswer_anonymous_enable
#define v92n_rx_filter_sections          DATASTRUCT._v92n_rx_filter_sections
#define cc_enable_not_flags              DATASTRUCT._cc_enable_not_flags
#define v34s_number_final_MPA_to_send    DATASTRUCT._v34s_number_final_MPA_to_send
#define impedance_monitor_tx_noise_floor_last DATASTRUCT._impedance_monitor_tx_noise_floor_last
#define faxparm_parm__pump_fax_time      DATASTRUCT._faxparm_parm__pump_fax_time
#define convert_agc_1_input_log          DATASTRUCT._convert_agc_1_input_log
#define PCM_LEN_8K0_EQC_FILL             DATASTRUCT._PCM_LEN_8K0_EQC_FILL
#define bg_event_queue                   DATASTRUCT._bg_event_queue
#define sh_RCoeff                        DATASTRUCT._sh_RCoeff
#define lec__nlp_probe                   DATASTRUCT._lec__nlp_probe
#define stat__nat_wan_ipsec              DATASTRUCT._stat__nat_wan_ipsec
#define parm__pcm_playback_intro_size    DATASTRUCT._parm__pcm_playback_intro_size
#define v34n_tx_attenuation_option       DATASTRUCT._v34n_tx_attenuation_option
#define parm__nat_tcp_mode               DATASTRUCT._parm__nat_tcp_mode
#define v34_rx_qn_hat_buffer_real        DATASTRUCT._v34_rx_qn_hat_buffer_real
#define energy_delta_threshold_fax       DATASTRUCT._energy_delta_threshold_fax
#define far_mode                         DATASTRUCT._far_mode
#define parm__ipbx_post_connect_dial_sequence DATASTRUCT._parm__ipbx_post_connect_dial_sequence
#define stat__nat_wan_alg_discards       DATASTRUCT._stat__nat_wan_alg_discards
#define parm__sip_accept_language_string DATASTRUCT._parm__sip_accept_language_string
#define parm__pump_noise_level           DATASTRUCT._parm__pump_noise_level
#define stat__nat_wan_pppoe              DATASTRUCT._stat__nat_wan_pppoe
#define v34_tx_trellis_state             DATASTRUCT._v34_tx_trellis_state
#define v34_rx_zn_hat_imag               DATASTRUCT._v34_rx_zn_hat_imag
#define saved_input_sample_8kHz          DATASTRUCT._saved_input_sample_8kHz
#define parm__net_isp_pptp_enable        DATASTRUCT._parm__net_isp_pptp_enable
#define tonemute_buffer                  DATASTRUCT._tonemute_buffer
#define parm__ata_timeserver_enable      DATASTRUCT._parm__ata_timeserver_enable
#define parm__ata_manufacturer           DATASTRUCT._parm__ata_manufacturer
#define pcm_folding_result1              DATASTRUCT._pcm_folding_result1
#define pcm_folding_result2              DATASTRUCT._pcm_folding_result2
#define tx_rate_conv_offset              DATASTRUCT._tx_rate_conv_offset
#define lec__fix_buffer                  DATASTRUCT._lec__fix_buffer
#define parm__ipbx_caller_id_outbound_enable DATASTRUCT._parm__ipbx_caller_id_outbound_enable
#define parm__phone_autoanswer_mode      DATASTRUCT._parm__phone_autoanswer_mode
#define v17_short_count                  DATASTRUCT._v17_short_count
#define dgidet_ec_peak                   DATASTRUCT._dgidet_ec_peak
#define impedance_monitor_future_tx_offset DATASTRUCT._impedance_monitor_future_tx_offset
#define asm_lb_packet_ready              DATASTRUCT._asm_lb_packet_ready
#define PH2P_ANAL_TEST_ENABLE            DATASTRUCT._PH2P_ANAL_TEST_ENABLE
#define V34S_LEN_8K0_1ST_GEAR_CHANGE     DATASTRUCT._V34S_LEN_8K0_1ST_GEAR_CHANGE
#define v34_tx_xn_remote_real            DATASTRUCT._v34_tx_xn_remote_real
#define parm__ipbx_fc_caller_id_inbound_enable DATASTRUCT._parm__ipbx_fc_caller_id_inbound_enable
#define v90_rx_ph4_MPAs_flag             DATASTRUCT._v90_rx_ph4_MPAs_flag
#define curCoeff_dtx                     DATASTRUCT._curCoeff_dtx
#define parm__speech_dec_missing_event_en DATASTRUCT._parm__speech_dec_missing_event_en
#define parm__slac_ring_bias             DATASTRUCT._parm__slac_ring_bias
#define sample_foreground_offset         DATASTRUCT._sample_foreground_offset
#define mgcp_sockid                      DATASTRUCT._mgcp_sockid
#define parm__ipbx_fxo_security_code_enable DATASTRUCT._parm__ipbx_fxo_security_code_enable
#define pcm_rx_inv_exponent              DATASTRUCT._pcm_rx_inv_exponent
#define nat_public_port                  DATASTRUCT._nat_public_port
#define parm__test_QCA2d_delay           DATASTRUCT._parm__test_QCA2d_delay
#define notch_datax32_420                DATASTRUCT._notch_datax32_420
#define test_input_value                 DATASTRUCT._test_input_value
#define parm__ipbx_red_led_descriptor    DATASTRUCT._parm__ipbx_red_led_descriptor
#define ph2_data_timeout_enable          DATASTRUCT._ph2_data_timeout_enable
#define v90h_rx_state                    DATASTRUCT._v90h_rx_state
#define pcm_ctl_echo_tx_DC               DATASTRUCT._pcm_ctl_echo_tx_DC
#define v90_tx_s_output_offset           DATASTRUCT._v90_tx_s_output_offset
#define parm__ipbx_fc_call_trace         DATASTRUCT._parm__ipbx_fc_call_trace
#define pcm_rx_inv_gain                  DATASTRUCT._pcm_rx_inv_gain
#define v34_equalizer_slew_fast          DATASTRUCT._v34_equalizer_slew_fast
#define g_msvq_levels                    DATASTRUCT._g_msvq_levels
#define g711a_plc_flag                   DATASTRUCT._g711a_plc_flag
#define post_ec_power                    DATASTRUCT._post_ec_power
#define past_ftyp                        DATASTRUCT._past_ftyp
#define parm__ata_update_domain_name     DATASTRUCT._parm__ata_update_domain_name
#define v34n_tx_gain_adjust              DATASTRUCT._v34n_tx_gain_adjust
#define stat__nat_snd_delivers           DATASTRUCT._stat__nat_snd_delivers
#define baud_tx_data                     DATASTRUCT._baud_tx_data
#define ANSAM_2100_MAX_x2                DATASTRUCT._ANSAM_2100_MAX_x2
#define legacy_rx_last_ack_type          DATASTRUCT._legacy_rx_last_ack_type
#define v34n_rx_preemph_value            DATASTRUCT._v34n_rx_preemph_value
#define v34_rx_qn_train_coef_real32      DATASTRUCT._v34_rx_qn_train_coef_real32
#define parm__net_router_rip_enable      DATASTRUCT._parm__net_router_rip_enable
#define parm__ata_lcd_menu_hide_update   DATASTRUCT._parm__ata_lcd_menu_hide_update
#define parm__dpbx_led_message_waiting   DATASTRUCT._parm__dpbx_led_message_waiting
#define v90_shape_4_offset               DATASTRUCT._v90_shape_4_offset
#define parm__net_debug_level_video      DATASTRUCT._parm__net_debug_level_video
#define v34_temp_hi_carrier              DATASTRUCT._v34_temp_hi_carrier
#define g711_last_in                     DATASTRUCT._g711_last_in
#define v90n_parm_shaping_lookahead      DATASTRUCT._v90n_parm_shaping_lookahead
#define v90_tx_dil_tp_mask               DATASTRUCT._v90_tx_dil_tp_mask
#define stat__daa_hook_state             DATASTRUCT._stat__daa_hook_state
#define parm__net_isp_connect_on_demand_interval DATASTRUCT._parm__net_isp_connect_on_demand_interval
#define v34_CONV_MSE_value               DATASTRUCT._v34_CONV_MSE_value
#define v29_anti_lock_limit              DATASTRUCT._v29_anti_lock_limit
#define asm_sending_extra_frame          DATASTRUCT._asm_sending_extra_frame
#define parm__voip_echo_canceller_mode   DATASTRUCT._parm__voip_echo_canceller_mode
#define cmn_regulation_counter           DATASTRUCT._cmn_regulation_counter
#define dtmf_peak_row_index              DATASTRUCT._dtmf_peak_row_index
#define tone_detect_delay                DATASTRUCT._tone_detect_delay
#define pcm_disc_slot_match_save         DATASTRUCT._pcm_disc_slot_match_save
#define v34s_special_local_train_offset  DATASTRUCT._v34s_special_local_train_offset
#define CONVERT_AGC_1_GAIN_MIN_LOG       DATASTRUCT._CONVERT_AGC_1_GAIN_MIN_LOG
#define bulk_delay_remote_poffset        DATASTRUCT._bulk_delay_remote_poffset
#define parm__nat_promiscuous_mode       DATASTRUCT._parm__nat_promiscuous_mode
#define wi_array                         DATASTRUCT._wi_array
#define lec__statistics_count            DATASTRUCT._lec__statistics_count
#define energy_delta_ref_level           DATASTRUCT._energy_delta_ref_level
#define ph2p_anal_log_Wlo                DATASTRUCT._ph2p_anal_log_Wlo
#define l_fpitch                         DATASTRUCT._l_fpitch
#define parm__cp_rd_cycle_period_min     DATASTRUCT._parm__cp_rd_cycle_period_min
#define stat__nat_snd_tcp_non_syn        DATASTRUCT._stat__nat_snd_tcp_non_syn
#define ph_t                             DATASTRUCT._ph_t
#define pcm_monitor_preemph_in           DATASTRUCT._pcm_monitor_preemph_in
#define PCM_WHITEN_NULLOIS_GAIN          DATASTRUCT._PCM_WHITEN_NULLOIS_GAIN
#define lpres_delin                      DATASTRUCT._lpres_delin
#define dev_timed_event                  DATASTRUCT._dev_timed_event
#define g711a_plc_pitchbuf               DATASTRUCT._g711a_plc_pitchbuf
#define faxdet_decimate_limit            DATASTRUCT._faxdet_decimate_limit
#define current_output_real              DATASTRUCT._current_output_real
#define asm_cng_release                  DATASTRUCT._asm_cng_release
#define THD_sum_L2_N_norm                DATASTRUCT._THD_sum_L2_N_norm
#define rx_lpf_coefs                     DATASTRUCT._rx_lpf_coefs
#define v90n_rxtx_silence_option         DATASTRUCT._v90n_rxtx_silence_option
#define g722_2_rx_state                  DATASTRUCT._g722_2_rx_state
#define l_lastGain                       DATASTRUCT._l_lastGain
#define ph2_power_trace_which_count      DATASTRUCT._ph2_power_trace_which_count
#define ph2p_anal_log_Wme                DATASTRUCT._ph2p_anal_log_Wme
#define cc_rx_energy_delay_buffer        DATASTRUCT._cc_rx_energy_delay_buffer
#define nat_wan_hw_addr                  DATASTRUCT._nat_wan_hw_addr
#define monitor_be2_status               DATASTRUCT._monitor_be2_status
#define parm__speech_enc_g711_transition DATASTRUCT._parm__speech_enc_g711_transition
#define chbuf                            DATASTRUCT._chbuf
#define convert_adjust_output_exponent   DATASTRUCT._convert_adjust_output_exponent
#define parm__pump_conference_mode       DATASTRUCT._parm__pump_conference_mode
#define parm__net_dhcp_server_restart    DATASTRUCT._parm__net_dhcp_server_restart
#define asm_decode_missing_frame_seen    DATASTRUCT._asm_decode_missing_frame_seen
#define stat__phone_headset_state        DATASTRUCT._stat__phone_headset_state
#define v90n_parm_reference_point        DATASTRUCT._v90n_parm_reference_point
#define extra_rate_reduction_buffer      DATASTRUCT._extra_rate_reduction_buffer
#define ph1n_rx_index_ANSpcm             DATASTRUCT._ph1n_rx_index_ANSpcm
#define answ_v8_use_15Hz                 DATASTRUCT._answ_v8_use_15Hz
#define dgidet_noise_energy40            DATASTRUCT._dgidet_noise_energy40
#define v90_dpcm_dil_sp                  DATASTRUCT._v90_dpcm_dil_sp
#define PH2P_POWR_GAIN_MARGIN            DATASTRUCT._PH2P_POWR_GAIN_MARGIN
#define parm__ipbx_led_priority_table    DATASTRUCT._parm__ipbx_led_priority_table
#define gci_rx_frame_abort               DATASTRUCT._gci_rx_frame_abort
#define fgkernel_current_svalue          DATASTRUCT._fgkernel_current_svalue
#define dtmf_hpf_pow32                   DATASTRUCT._dtmf_hpf_pow32
#define lec__periodic_statistics_index   DATASTRUCT._lec__periodic_statistics_index
#define postLPFInHis                     DATASTRUCT._postLPFInHis
#define faxdet_decimate_limit_ansam      DATASTRUCT._faxdet_decimate_limit_ansam
#define sys_number_missed_samples_max    DATASTRUCT._sys_number_missed_samples_max
#define remote_interpolator_buffer_imag  DATASTRUCT._remote_interpolator_buffer_imag
#define sart_tx_write_index              DATASTRUCT._sart_tx_write_index
#define v34f_eqc_timing32                DATASTRUCT._v34f_eqc_timing32
#define ph2_AB_qualify_length            DATASTRUCT._ph2_AB_qualify_length
#define cc_rx_spectrum_result_table32_imag DATASTRUCT._cc_rx_spectrum_result_table32_imag
#define ipbx_tone_parameter              DATASTRUCT._ipbx_tone_parameter
#define cbk_st_s                         DATASTRUCT._cbk_st_s
#define g726_enc_parm                    DATASTRUCT._g726_enc_parm
#define ipod_msg_rx_bfi                  DATASTRUCT._ipod_msg_rx_bfi
#define ph1_x_law_decode_routine         DATASTRUCT._ph1_x_law_decode_routine
#define local_buffer_pointer_front       DATASTRUCT._local_buffer_pointer_front
#define dcd_rcv_level                    DATASTRUCT._dcd_rcv_level
#define p18_2100_notch_buffer            DATASTRUCT._p18_2100_notch_buffer
#define cc_rx_diff_energy_log            DATASTRUCT._cc_rx_diff_energy_log
#define parm__net_lan_heartbeat_server_ip_address DATASTRUCT._parm__net_lan_heartbeat_server_ip_address
#define PCM_GEAR_CONVERGENCE_THRESHOLD   DATASTRUCT._PCM_GEAR_CONVERGENCE_THRESHOLD
#define v34_rx_cn_real                   DATASTRUCT._v34_rx_cn_real
#define V34S_ANSW_8K0_2RT_Jend_to_Jdet   DATASTRUCT._V34S_ANSW_8K0_2RT_Jend_to_Jdet
#define parm__dm_line_quality_monitor_mode DATASTRUCT._parm__dm_line_quality_monitor_mode
#define v34b_mg_run_active_flag          DATASTRUCT._v34b_mg_run_active_flag
#define ph2p_powr_L2_spectrum_power_buffer32 DATASTRUCT._ph2p_powr_L2_spectrum_power_buffer32
#define fax_v21_aborts_hs                DATASTRUCT._fax_v21_aborts_hs
#define v90_dpcm_dil_tp                  DATASTRUCT._v90_dpcm_dil_tp
#define v34h_tx_b_bits_per_mapping_frame DATASTRUCT._v34h_tx_b_bits_per_mapping_frame
#define debug_host_buffer                DATASTRUCT._debug_host_buffer
#define V92_DECODER_FF_SHIFT             DATASTRUCT._V92_DECODER_FF_SHIFT
#define nat_pkt_ip_ptr                   DATASTRUCT._nat_pkt_ip_ptr
#define parm__speech_enc_mode            DATASTRUCT._parm__speech_enc_mode
#define voicedCnt                        DATASTRUCT._voicedCnt
#define parm__line_tx_gain               DATASTRUCT._parm__line_tx_gain
#define valid_switch                     DATASTRUCT._valid_switch
#define last_digit                       DATASTRUCT._last_digit
#define sdt_initial_detect_flag          DATASTRUCT._sdt_initial_detect_flag
#define parm__vppn_device_registration_mask DATASTRUCT._parm__vppn_device_registration_mask
#define sigbuf_pitch_ana                 DATASTRUCT._sigbuf_pitch_ana
#define g711_rx_cng_frame_counter        DATASTRUCT._g711_rx_cng_frame_counter
#define v92n_rxtx_v92_enable             DATASTRUCT._v92n_rxtx_v92_enable
#define l_grps_cnt                       DATASTRUCT._l_grps_cnt
#define PCM_FULL_CONVERGENCE_THRESHOLD   DATASTRUCT._PCM_FULL_CONVERGENCE_THRESHOLD
#define ph2n_tx_3429_option              DATASTRUCT._ph2n_tx_3429_option
#define cc_rx_ALL_threshold              DATASTRUCT._cc_rx_ALL_threshold
#define frame_count                      DATASTRUCT._frame_count
#define pcm_ff_ct_position               DATASTRUCT._pcm_ff_ct_position
#define cp_change_counter                DATASTRUCT._cp_change_counter
#define asm_decode_shift_decrement       DATASTRUCT._asm_decode_shift_decrement
#define energy_delta_slew_rate           DATASTRUCT._energy_delta_slew_rate
#define parm__ipbx_line_concurrent_line_count DATASTRUCT._parm__ipbx_line_concurrent_line_count
#define nat_wan_ip_addr                  DATASTRUCT._nat_wan_ip_addr
#define v34s_capture_buffer              DATASTRUCT._v34s_capture_buffer
#define l_lsp_cos                        DATASTRUCT._l_lsp_cos
#define detect_v21_detect_lpf1_32        DATASTRUCT._detect_v21_detect_lpf1_32
#define parm__ipbx_dial_after_pound_8    DATASTRUCT._parm__ipbx_dial_after_pound_8
#define parm__ipbx_dial_after_pound_9    DATASTRUCT._parm__ipbx_dial_after_pound_9
#define asm_encode_rtp_dtmf_prev         DATASTRUCT._asm_encode_rtp_dtmf_prev
#define rx_lpf_vxx_buffer                DATASTRUCT._rx_lpf_vxx_buffer
#define ec_error_buffer                  DATASTRUCT._ec_error_buffer
#define ph2n_rx_required_attenuation     DATASTRUCT._ph2n_rx_required_attenuation
#define V34_A_OVER_CK80                  DATASTRUCT._V34_A_OVER_CK80
#define v90_rx_shaper_frame_size         DATASTRUCT._v90_rx_shaper_frame_size
#define parm__cid_data_index             DATASTRUCT._parm__cid_data_index
#define parm__codec_disconnect_tone_1_bandwidth DATASTRUCT._parm__codec_disconnect_tone_1_bandwidth
#define parm__orc_codec_type             DATASTRUCT._parm__orc_codec_type
#define back_sigbuf                      DATASTRUCT._back_sigbuf
#define fax_CNG_off_length               DATASTRUCT._fax_CNG_off_length
#define V34_EQUALIZER_RANDOM_AMPLITUDE   DATASTRUCT._V34_EQUALIZER_RANDOM_AMPLITUDE
#define pastVad                          DATASTRUCT._pastVad
#define cc_rx_ANAL_prev_DC_energy_log    DATASTRUCT._cc_rx_ANAL_prev_DC_energy_log
#define ipbx_led_p                       DATASTRUCT._ipbx_led_p
#define lec__cng_frame_sid_enable        DATASTRUCT._lec__cng_frame_sid_enable
#define parm__ipbx_sit4_tone             DATASTRUCT._parm__ipbx_sit4_tone
#define PCM_LEN_8K0_ECC_HOLDOFF          DATASTRUCT._PCM_LEN_8K0_ECC_HOLDOFF
#define v90_rx_dil_ref                   DATASTRUCT._v90_rx_dil_ref
#define dcd_probe_agc_2                  DATASTRUCT._dcd_probe_agc_2
#define parm__mgcp_remote_user_name      DATASTRUCT._parm__mgcp_remote_user_name
#define enc_frame                        DATASTRUCT._enc_frame
#define baud_tx_within_tmd_break         DATASTRUCT._baud_tx_within_tmd_break
#define v92_rx_decoder_ep_input          DATASTRUCT._v92_rx_decoder_ep_input
#define lec__probe_rx_input              DATASTRUCT._lec__probe_rx_input
#define sart_tx_array                    DATASTRUCT._sart_tx_array
#define v90n_tx_INFO0d_body              DATASTRUCT._v90n_tx_INFO0d_body
#define g_w_fs_init                      DATASTRUCT._g_w_fs_init
#define parm__sdp_g726_24_codec_dyn_pt   DATASTRUCT._parm__sdp_g726_24_codec_dyn_pt
#define baud_rx_crc_hi                   DATASTRUCT._baud_rx_crc_hi
#define v34_pp_ftr_offset                DATASTRUCT._v34_pp_ftr_offset
#define phone_speaker_monitor_tx_volume  DATASTRUCT._phone_speaker_monitor_tx_volume
#define edge_p1200_real32                DATASTRUCT._edge_p1200_real32
#define demod_leading_half_imag          DATASTRUCT._demod_leading_half_imag
#define v34_rx_qn_tilde_pointer          DATASTRUCT._v34_rx_qn_tilde_pointer
#define parm__dtmf_low_tone_level        DATASTRUCT._parm__dtmf_low_tone_level
#define mbx_rx_build_data                DATASTRUCT._mbx_rx_build_data
#define v92s_reneg_monitor_reference     DATASTRUCT._v92s_reneg_monitor_reference
#define parm__dpbx_led_line_in_use       DATASTRUCT._parm__dpbx_led_line_in_use
#define phone_led_mask                   DATASTRUCT._phone_led_mask
#define echo_canceller_coefs32           DATASTRUCT._echo_canceller_coefs32
#define v34n_parm_remote_clear_disable   DATASTRUCT._v34n_parm_remote_clear_disable
#define phase_loop_complex               DATASTRUCT._phase_loop_complex
#define pcm_16K_output_sample            DATASTRUCT._pcm_16K_output_sample
#define rtp_enc_packet                   DATASTRUCT._rtp_enc_packet
#define mark_data_unit                   DATASTRUCT._mark_data_unit
#define saved_Lx_log_N_pointer           DATASTRUCT._saved_Lx_log_N_pointer
#define ata_cmdbuf                       DATASTRUCT._ata_cmdbuf
#define flag_RDS_read_stream             DATASTRUCT._flag_RDS_read_stream
#define sonitrol_local_address           DATASTRUCT._sonitrol_local_address
#define ipod_msg_tx_flags                DATASTRUCT._ipod_msg_tx_flags
#define sonitrol_udp_socket              DATASTRUCT._sonitrol_udp_socket
#define dec_exc                          DATASTRUCT._dec_exc
#define asm_encode_current_shift         DATASTRUCT._asm_encode_current_shift
#define V34S_LEN_8K0_2ND_FAST_TRAIN      DATASTRUCT._V34S_LEN_8K0_2ND_FAST_TRAIN
#define ph2p_anal_preemph_results_buffer DATASTRUCT._ph2p_anal_preemph_results_buffer
#define v34n_tx_data_rate_option         DATASTRUCT._v34n_tx_data_rate_option
#define decision_pcm_offset              DATASTRUCT._decision_pcm_offset
#define answ_v8_JM_sent                  DATASTRUCT._answ_v8_JM_sent
#define parm__dtmf_early_col_no_tone_level DATASTRUCT._parm__dtmf_early_col_no_tone_level
#define parm__sdp_g726_32_codec_name     DATASTRUCT._parm__sdp_g726_32_codec_name
#define parm__ipbx_distinctive_ring_enable DATASTRUCT._parm__ipbx_distinctive_ring_enable
#define v92_rx_modulus_2_value           DATASTRUCT._v92_rx_modulus_2_value
#define parm__ipbx_led_call_forward      DATASTRUCT._parm__ipbx_led_call_forward
#define v34n_rx_use_nonlinear            DATASTRUCT._v34n_rx_use_nonlinear
#define x_law_encode_sample_counter      DATASTRUCT._x_law_encode_sample_counter
#define pre_equalized_energy_level       DATASTRUCT._pre_equalized_energy_level
#define parm__slac_message_waiting_amplitude DATASTRUCT._parm__slac_message_waiting_amplitude
#define V34_BE0_SLEW_MEDIUM              DATASTRUCT._V34_BE0_SLEW_MEDIUM
#define v92n_rx_MH_indication            DATASTRUCT._v92n_rx_MH_indication
#define stat__round_trip_delay           DATASTRUCT._stat__round_trip_delay
#define stat__speech_rtp_encode_current_packet_type DATASTRUCT._stat__speech_rtp_encode_current_packet_type
#define lec__last_nlp_state              DATASTRUCT._lec__last_nlp_state
#define dec_T2                           DATASTRUCT._dec_T2
#define pcm_LO_peak_MSE_stack            DATASTRUCT._pcm_LO_peak_MSE_stack
#define v34s_reneg_ignore_send_MP_recv_MP DATASTRUCT._v34s_reneg_ignore_send_MP_recv_MP
#define v90_dpcm_dil_second              DATASTRUCT._v90_dpcm_dil_second
#define test_input_count                 DATASTRUCT._test_input_count
#define parm__ipbx_caller_id_waiting_enable DATASTRUCT._parm__ipbx_caller_id_waiting_enable
#define fsk_previous_dif32               DATASTRUCT._fsk_previous_dif32
#define ph2_power_trace_previous_Y       DATASTRUCT._ph2_power_trace_previous_Y
#define use_buffered_threads             DATASTRUCT._use_buffered_threads
#define ph2n_rx_receive_level            DATASTRUCT._ph2n_rx_receive_level
#define v34_rx_qn_train_coef_imag32      DATASTRUCT._v34_rx_qn_train_coef_imag32
#define prev_fsmag_quant_fsmag           DATASTRUCT._prev_fsmag_quant_fsmag
#define v92_rx_decoder_ep_output         DATASTRUCT._v92_rx_decoder_ep_output
#define lec__probe_rx_output             DATASTRUCT._lec__probe_rx_output
#define shadow_caller_id                 DATASTRUCT._shadow_caller_id
#define v34h_tx_control_hi_frame         DATASTRUCT._v34h_tx_control_hi_frame
#define v34h_tx_control_lo_frame         DATASTRUCT._v34h_tx_control_lo_frame
#define pcm_btr_phase                    DATASTRUCT._pcm_btr_phase
#define sdp_parse_desc_ok                DATASTRUCT._sdp_parse_desc_ok
#define v92n_tx_MH_body                  DATASTRUCT._v92n_tx_MH_body
#define v34n_rx_symbol_option            DATASTRUCT._v34n_rx_symbol_option
#define V34S_ENERGY_INPUT_SLEW           DATASTRUCT._V34S_ENERGY_INPUT_SLEW
#define statistics_buffer                DATASTRUCT._statistics_buffer
#define rxs_count                        DATASTRUCT._rxs_count
#define parm__radio_channel_settings     DATASTRUCT._parm__radio_channel_settings
#define fg_time_until_next_timer_update  DATASTRUCT._fg_time_until_next_timer_update
#define parm__disconnect_tone_tone_mask  DATASTRUCT._parm__disconnect_tone_tone_mask
#define tmpbuf                           DATASTRUCT._tmpbuf
#define parm__ipbx_bridge_autoanswer_list DATASTRUCT._parm__ipbx_bridge_autoanswer_list
#define parm__ipbx_disturb_accept_enable DATASTRUCT._parm__ipbx_disturb_accept_enable
#define g723_CodStat                     DATASTRUCT._g723_CodStat
#define save_rx_call_to_answer_maxrate   DATASTRUCT._save_rx_call_to_answer_maxrate
#define boot_event                       DATASTRUCT._boot_event
#define baud_rx_crc_lo                   DATASTRUCT._baud_rx_crc_lo
#define bds_counter                      DATASTRUCT._bds_counter
#define v92_rx_decoder_ff_output         DATASTRUCT._v92_rx_decoder_ff_output
#define v90_tx_sign                      DATASTRUCT._v90_tx_sign
#define rxs_baud_rx_data                 DATASTRUCT._rxs_baud_rx_data
#define ipod_iface_tx_bufp               DATASTRUCT._ipod_iface_tx_bufp
#define dcdel                            DATASTRUCT._dcdel
#define rx_overspeed_offset              DATASTRUCT._rx_overspeed_offset
#define ANSW_V8_CJ_COUNT_MIN             DATASTRUCT._ANSW_V8_CJ_COUNT_MIN
#define parm__net_dhcp_server_client_lease_time DATASTRUCT._parm__net_dhcp_server_client_lease_time
#define rd_energy_state                  DATASTRUCT._rd_energy_state
#define v32_rate_jump_table_index        DATASTRUCT._v32_rate_jump_table_index
#define faxparm_parm__pump_fax_mode      DATASTRUCT._faxparm_parm__pump_fax_mode
#define parm__net_lan_password           DATASTRUCT._parm__net_lan_password
#define input_data_flag                  DATASTRUCT._input_data_flag
#define parm__codec_parallel_in_use_disconnect DATASTRUCT._parm__codec_parallel_in_use_disconnect
#define number_bg_timers                 DATASTRUCT._number_bg_timers
#define v92n_parm_v92_enable             DATASTRUCT._v92n_parm_v92_enable
#define trellis_routine                  DATASTRUCT._trellis_routine
#define v90_shape_1_offset               DATASTRUCT._v90_shape_1_offset
#define v90n_parm_maximum_power          DATASTRUCT._v90n_parm_maximum_power
#define memt_postfilt                    DATASTRUCT._memt_postfilt
#define lec__periodic_statistics_counter DATASTRUCT._lec__periodic_statistics_counter
#define parm__ata_telnet_server_enable   DATASTRUCT._parm__ata_telnet_server_enable
#define parm__speech_enc_cng_order       DATASTRUCT._parm__speech_enc_cng_order
#define PCM_LEN_8K0_EQC_TRN1A_LENGTH     DATASTRUCT._PCM_LEN_8K0_EQC_TRN1A_LENGTH
#define pcm_TRN2_MSE_report_rate         DATASTRUCT._pcm_TRN2_MSE_report_rate
#define l_prev_gain_sub                  DATASTRUCT._l_prev_gain_sub
#define gear_change_threshold            DATASTRUCT._gear_change_threshold
#define fsk_previous_dif_lsb             DATASTRUCT._fsk_previous_dif_lsb
#define v21_flag_holdoff                 DATASTRUCT._v21_flag_holdoff
#define stat__nat_snd_blocked            DATASTRUCT._stat__nat_snd_blocked
#define pcm_btr_freq_error_ratio         DATASTRUCT._pcm_btr_freq_error_ratio
#define parm__ipbx_bridge_single_stage_dialing_enable DATASTRUCT._parm__ipbx_bridge_single_stage_dialing_enable
#define g168_rx_cng_buffer               DATASTRUCT._g168_rx_cng_buffer
#define sdp_buffer                       DATASTRUCT._sdp_buffer
#define parm__pcm_playback_once_bufferp  DATASTRUCT._parm__pcm_playback_once_bufferp
#define stat__speech_strict_silence_detect DATASTRUCT._stat__speech_strict_silence_detect
#define sonitrol_line_failed             DATASTRUCT._sonitrol_line_failed
#define v90_tx_dil_sp_cnt                DATASTRUCT._v90_tx_dil_sp_cnt
#define parm__audio_encoding_mode        DATASTRUCT._parm__audio_encoding_mode
#define ph2_test_reverse_enable          DATASTRUCT._ph2_test_reverse_enable
#define parm__ipbx_fc_hookflash_simulation DATASTRUCT._parm__ipbx_fc_hookflash_simulation
#define prev_rx_frame_report             DATASTRUCT._prev_rx_frame_report
#define convert_agc_1_output_log         DATASTRUCT._convert_agc_1_output_log
#define ph2n_tx_v92_ITU_bits_carrier     DATASTRUCT._ph2n_tx_v92_ITU_bits_carrier
#define g168_inp_floor                   DATASTRUCT._g168_inp_floor
#define scrambler_mask_table             DATASTRUCT._scrambler_mask_table
#define ethernet_outgoing_queue          DATASTRUCT._ethernet_outgoing_queue
#define YY_LT_shift                      DATASTRUCT._YY_LT_shift
#define v34n_tx_qn_coef_real             DATASTRUCT._v34n_tx_qn_coef_real
#define v34p_bg_block_finished_flags     DATASTRUCT._v34p_bg_block_finished_flags
#define parm__sip_require_user_name      DATASTRUCT._parm__sip_require_user_name
#define stat__speech_dec_playout_frame   DATASTRUCT._stat__speech_dec_playout_frame
#define v92n_rx_prefilter_RMS            DATASTRUCT._v92n_rx_prefilter_RMS
#define stat__cp_rd_energy_on_time       DATASTRUCT._stat__cp_rd_energy_on_time
#define dprmbx_outgoing_data_pending     DATASTRUCT._dprmbx_outgoing_data_pending
#define V34_RX_LPF_COEFS                 DATASTRUCT._V34_RX_LPF_COEFS
#define stat__phone_memcard_provider     DATASTRUCT._stat__phone_memcard_provider
#define stat__vpcm_digital_attenuation   DATASTRUCT._stat__vpcm_digital_attenuation
#define parm__sdp_g728_codec_name        DATASTRUCT._parm__sdp_g728_codec_name
#define MeanSE                           DATASTRUCT._MeanSE
#define fsk_lpf_buffer_imag              DATASTRUCT._fsk_lpf_buffer_imag
#define wiznet_reset_flag                DATASTRUCT._wiznet_reset_flag
#define keep_alive_count                 DATASTRUCT._keep_alive_count
#define v34s_reneg_allow_recv_MP_within_ignore DATASTRUCT._v34s_reneg_allow_recv_MP_within_ignore
#define parm__codec_disconnect_tone_1_duration DATASTRUCT._parm__codec_disconnect_tone_1_duration
#define parm__sdp_g722_codec_dyn_pt      DATASTRUCT._parm__sdp_g722_codec_dyn_pt
#define v92n_tx_v92_enable               DATASTRUCT._v92n_tx_v92_enable
#define v90n_rx_redundancy               DATASTRUCT._v90n_rx_redundancy
#define g722_e4l_oldrl                   DATASTRUCT._g722_e4l_oldrl
#define lec__best_can_poffset            DATASTRUCT._lec__best_can_poffset
#define sdt_reversal_timeout_init        DATASTRUCT._sdt_reversal_timeout_init
#define correct_precoder_real            DATASTRUCT._correct_precoder_real
#define parm__ipbx_timeout_pause_duration DATASTRUCT._parm__ipbx_timeout_pause_duration
#define mpi_debounce_reconnect           DATASTRUCT._mpi_debounce_reconnect
#define call_automation_not_available    DATASTRUCT._call_automation_not_available
#define V34S_LEN_8K0_1RT_MIN_1ST_TRAIN   DATASTRUCT._V34S_LEN_8K0_1RT_MIN_1ST_TRAIN
#define ph2_tx_baud_counter              DATASTRUCT._ph2_tx_baud_counter
#define lec__alpha_err_mag               DATASTRUCT._lec__alpha_err_mag
#define saved_scrambler_align            DATASTRUCT._saved_scrambler_align
#define v34f_eqc_diff_DC_gain            DATASTRUCT._v34f_eqc_diff_DC_gain
#define fsk_TONE_sgnladjust              DATASTRUCT._fsk_TONE_sgnladjust
#define l_sigbuf_pit                     DATASTRUCT._l_sigbuf_pit
#define v34_pp_equalized_data_real       DATASTRUCT._v34_pp_equalized_data_real
#define dec_past_qua_en                  DATASTRUCT._dec_past_qua_en
#define l_postHPFOutHis_hi               DATASTRUCT._l_postHPFOutHis_hi
#define parm__sdp_g729b_codec_name       DATASTRUCT._parm__sdp_g729b_codec_name
#define parm__digital_data_modes         DATASTRUCT._parm__digital_data_modes
#define ph2n_probing_frequency_offset    DATASTRUCT._ph2n_probing_frequency_offset
#define v34_temp_pre_emph_coefs_1        DATASTRUCT._v34_temp_pre_emph_coefs_1
#define gpf_LLexp                        DATASTRUCT._gpf_LLexp
#define stat__nat_wan_header_option      DATASTRUCT._stat__nat_wan_header_option
#define comn_v8_timeout_T1_counter       DATASTRUCT._comn_v8_timeout_T1_counter
#define v34_temp_pre_emph_coefs_6        DATASTRUCT._v34_temp_pre_emph_coefs_6
#define v34_MSE_value_count              DATASTRUCT._v34_MSE_value_count
#define equalizer_lagging_imag           DATASTRUCT._equalizer_lagging_imag
#define phase_roll_hilbert_buffer        DATASTRUCT._phase_roll_hilbert_buffer
#define tick_timer                       DATASTRUCT._tick_timer
#define dcd_diversion_delta_slew_rate    DATASTRUCT._dcd_diversion_delta_slew_rate
#define parm__faxdet_v21_threshold       DATASTRUCT._parm__faxdet_v21_threshold
#define CONNECT_event_reported           DATASTRUCT._CONNECT_event_reported
#define v92n_tx_clock_adjust             DATASTRUCT._v92n_tx_clock_adjust
#define parm__ipbx_call_waiting_enable   DATASTRUCT._parm__ipbx_call_waiting_enable
#define stat__nat_wan_blocked            DATASTRUCT._stat__nat_wan_blocked
#define ANSam_trace_index                DATASTRUCT._ANSam_trace_index
#define v34h_tx_parser_shellmap_routine  DATASTRUCT._v34h_tx_parser_shellmap_routine
#define HIT_COUNTER_INIT                 DATASTRUCT._HIT_COUNTER_INIT
#define lec__canceller_control           DATASTRUCT._lec__canceller_control
#define Min_buffer                       DATASTRUCT._Min_buffer
#define oicp_last_entry_time             DATASTRUCT._oicp_last_entry_time
#define v90n_rx_constellation_mask       DATASTRUCT._v90n_rx_constellation_mask
#define parm__ipbx_confirm_tone          DATASTRUCT._parm__ipbx_confirm_tone
#define cc_rx_PP_total_tone_ratio        DATASTRUCT._cc_rx_PP_total_tone_ratio
#define MeanSLE                          DATASTRUCT._MeanSLE
#define agc_2_inv_gain                   DATASTRUCT._agc_2_inv_gain
#define faxmon_status_code               DATASTRUCT._faxmon_status_code
#define parm__sip_nat_keep_alive_domain_name DATASTRUCT._parm__sip_nat_keep_alive_domain_name
#define v21_detect_level                 DATASTRUCT._v21_detect_level
#define edge_p1200_imag32                DATASTRUCT._edge_p1200_imag32
#define g722_tx_qmf_data_offset          DATASTRUCT._g722_tx_qmf_data_offset
#define g711a_plc_history                DATASTRUCT._g711a_plc_history
#define FALL_adjusted_mse_value          DATASTRUCT._FALL_adjusted_mse_value
#define ph2n_rx_maxrate                  DATASTRUCT._ph2n_rx_maxrate
#define stat__v92_MH_information         DATASTRUCT._stat__v92_MH_information
#define v34_BE_log_Gn                    DATASTRUCT._v34_BE_log_Gn
#define v34_BE_log_Gp                    DATASTRUCT._v34_BE_log_Gp
#define DIL_probing_pad_gain             DATASTRUCT._DIL_probing_pad_gain
#define V34_T_OVER_8K0_RATIO             DATASTRUCT._V34_T_OVER_8K0_RATIO
#define rled_pattern_index               DATASTRUCT._rled_pattern_index
#define v34_rx_yn_error_real32           DATASTRUCT._v34_rx_yn_error_real32
#define sonitrol_remote_updnload_port    DATASTRUCT._sonitrol_remote_updnload_port
#define ph2p_bg_sample_out_offset        DATASTRUCT._ph2p_bg_sample_out_offset
#define test_2_ext                       DATASTRUCT._test_2_ext
#define parm__dpbx_key_polarity_mask     DATASTRUCT._parm__dpbx_key_polarity_mask
#define jitter_max_freq                  DATASTRUCT._jitter_max_freq
#define ph2p_anal_variance_13_table      DATASTRUCT._ph2p_anal_variance_13_table
#define monitor                          DATASTRUCT._monitor
#define v90_shape_3_min32                DATASTRUCT._v90_shape_3_min32
#define V34S_LEN_8K0_PRE_GEAR_CHANGE     DATASTRUCT._V34S_LEN_8K0_PRE_GEAR_CHANGE
#define ph2p_anal_adj_log_Whi            DATASTRUCT._ph2p_anal_adj_log_Whi
#define v34h_tx_Q_n                      DATASTRUCT._v34h_tx_Q_n
#define lec__tec_excite                  DATASTRUCT._lec__tec_excite
#define saved_status_code                DATASTRUCT._saved_status_code
#define tx_match_sequence                DATASTRUCT._tx_match_sequence
#define parm__ata_time                   DATASTRUCT._parm__ata_time
#define baud_cntr                        DATASTRUCT._baud_cntr
#define V34_PRE_ME_EQUALIZER_COEFS       DATASTRUCT._V34_PRE_ME_EQUALIZER_COEFS
#define g_w_fs                           DATASTRUCT._g_w_fs
#define v34n_tx_symbol_rate              DATASTRUCT._v34n_tx_symbol_rate
#define parm__ipbx_interdigit_duration   DATASTRUCT._parm__ipbx_interdigit_duration
#define parm__max_jpeg_save_files        DATASTRUCT._parm__max_jpeg_save_files
#define v92n_tx_CPd_body_pretaps         DATASTRUCT._v92n_tx_CPd_body_pretaps
#define lec__nlp_sil_detect              DATASTRUCT._lec__nlp_sil_detect
#define parm__ata_model_number           DATASTRUCT._parm__ata_model_number
#define ipod_within_data_g726            DATASTRUCT._ipod_within_data_g726
#define v90n_tx_pcm_3429_option          DATASTRUCT._v90n_tx_pcm_3429_option
#define ph2p_anal_maxrates_02_table      DATASTRUCT._ph2p_anal_maxrates_02_table
#define v34_rx_qn_pointer                DATASTRUCT._v34_rx_qn_pointer
#define V34_INTERPOLATOR_COEFS           DATASTRUCT._V34_INTERPOLATOR_COEFS
#define g726_out_bits                    DATASTRUCT._g726_out_bits
#define impedance_monitor_tx_noise_floor_sum32 DATASTRUCT._impedance_monitor_tx_noise_floor_sum32
#define asm_post_g711_transition         DATASTRUCT._asm_post_g711_transition
#define v90_tx_offset                    DATASTRUCT._v90_tx_offset
#define sart_tx_processed_cnt            DATASTRUCT._sart_tx_processed_cnt
#define lpfsp_delin                      DATASTRUCT._lpfsp_delin
#define ptloop_2nd_order_term            DATASTRUCT._ptloop_2nd_order_term
#define ph2p_fefo_holdoff_flag           DATASTRUCT._ph2p_fefo_holdoff_flag
#define av_shift                         DATASTRUCT._av_shift
#define nat_l2tp_entry                   DATASTRUCT._nat_l2tp_entry
#define decode_input_real                DATASTRUCT._decode_input_real
#define parm__net_lan_pppoe_enable       DATASTRUCT._parm__net_lan_pppoe_enable
#define sense_silence_detect             DATASTRUCT._sense_silence_detect
#define v90_tx_dil_tp_ptr                DATASTRUCT._v90_tx_dil_tp_ptr
#define pcm_eq_routine                   DATASTRUCT._pcm_eq_routine
#define v34_equalizer_slew_B1_medium     DATASTRUCT._v34_equalizer_slew_B1_medium
#define ipod_command_vocoder_select      DATASTRUCT._ipod_command_vocoder_select
#define stat__net_current_host_name      DATASTRUCT._stat__net_current_host_name
#define ipod_error_flags                 DATASTRUCT._ipod_error_flags
#define bg_time_until_next_timer_update  DATASTRUCT._bg_time_until_next_timer_update
#define v90_shape_3_min                  DATASTRUCT._v90_shape_3_min
#define l_postHPFOutHis_lo               DATASTRUCT._l_postHPFOutHis_lo
#define pcm_rx_8K0_transfer_in_poffset   DATASTRUCT._pcm_rx_8K0_transfer_in_poffset
#define cc_tx_modulator_increment        DATASTRUCT._cc_tx_modulator_increment
#define v34n_rxtx_hi_data_rate_option    DATASTRUCT._v34n_rxtx_hi_data_rate_option
#define parm__orc_rtpmap_number          DATASTRUCT._parm__orc_rtpmap_number
#define threshold_fax_ab                 DATASTRUCT._threshold_fax_ab
#define threshold_fax_ac                 DATASTRUCT._threshold_fax_ac
#define pcm_ctl_enable_tx_hpf            DATASTRUCT._pcm_ctl_enable_tx_hpf
#define sonitrol_connection_established  DATASTRUCT._sonitrol_connection_established
#define parm__rtp_srtp_enable            DATASTRUCT._parm__rtp_srtp_enable
#define mbx__dtoh                        DATASTRUCT._mbx__dtoh
#define cc_rx_Tk_energy_log              DATASTRUCT._cc_rx_Tk_energy_log
#define v90_apcm_dil_length              DATASTRUCT._v90_apcm_dil_length
#define stat__nat_snd_create_failed      DATASTRUCT._stat__nat_snd_create_failed
#define sip_temp_print_space             DATASTRUCT._sip_temp_print_space
#define parm__radio_alarm_settings       DATASTRUCT._parm__radio_alarm_settings
#define goertzel_buffer_poffset          DATASTRUCT._goertzel_buffer_poffset
#define v34n_parm_ptt_symbol_option      DATASTRUCT._v34n_parm_ptt_symbol_option
#define tone_priority_count              DATASTRUCT._tone_priority_count
#define pcm_playback_size                DATASTRUCT._pcm_playback_size
#define v34_temp_hi_lo_pre_equalizer_coefs DATASTRUCT._v34_temp_hi_lo_pre_equalizer_coefs
#define parm__ata_configuration_failed_message DATASTRUCT._parm__ata_configuration_failed_message
#define tonedt_rate_reduction_counter    DATASTRUCT._tonedt_rate_reduction_counter
#define V34_RXI_TAPS                     DATASTRUCT._V34_RXI_TAPS
#define hpspeech600                      DATASTRUCT._hpspeech600
#define l_default_w                      DATASTRUCT._l_default_w
#define p18_angle_store_imag             DATASTRUCT._p18_angle_store_imag
#define cc_tx_interpolator_poffset       DATASTRUCT._cc_tx_interpolator_poffset
#define v92_rx_decoder_ff_alpha_gain     DATASTRUCT._v92_rx_decoder_ff_alpha_gain
#define parm__dtmf_clamp_count           DATASTRUCT._parm__dtmf_clamp_count
#define ph2_tx_interpolator_buffer_imag  DATASTRUCT._ph2_tx_interpolator_buffer_imag
#define PH2_RX_DCD_HYSTERESIS            DATASTRUCT._PH2_RX_DCD_HYSTERESIS
#define zero_dtx                         DATASTRUCT._zero_dtx
#define ac97_tx_dma                      DATASTRUCT._ac97_tx_dma
#define v92n_rx_MH_information           DATASTRUCT._v92n_rx_MH_information
#define tone_detector_8kHz               DATASTRUCT._tone_detector_8kHz
#define agal                             DATASTRUCT._agal
#define v34_tx_zn_local_imag             DATASTRUCT._v34_tx_zn_local_imag
#define BAUD_PLL_FREQ_ERROR_RATIO        DATASTRUCT._BAUD_PLL_FREQ_ERROR_RATIO
#define pcm_equalizer_ep_coefs32         DATASTRUCT._pcm_equalizer_ep_coefs32
#define V90_RX_R_REVERSAL_EVENT          DATASTRUCT._V90_RX_R_REVERSAL_EVENT
#define predicted_rx_xn_B1_1st_data_flag DATASTRUCT._predicted_rx_xn_B1_1st_data_flag
#define l_noise_del                      DATASTRUCT._l_noise_del
#define parm__mgcp_response_code_sit1    DATASTRUCT._parm__mgcp_response_code_sit1
#define v34n_parm_attenuation_option     DATASTRUCT._v34n_parm_attenuation_option
#define parm__mgcp_response_code_sit2    DATASTRUCT._parm__mgcp_response_code_sit2
#define parm__mgcp_response_code_sit3    DATASTRUCT._parm__mgcp_response_code_sit3
#define v90_rx_retrain_delay_poffset     DATASTRUCT._v90_rx_retrain_delay_poffset
#define mpi_status_index                 DATASTRUCT._mpi_status_index
#define parm__mgcp_response_code_sit4    DATASTRUCT._parm__mgcp_response_code_sit4
#define sart_overlay_loaded              DATASTRUCT._sart_overlay_loaded
#define parm__sdp_jpeg_codec_dyn_pt      DATASTRUCT._parm__sdp_jpeg_codec_dyn_pt
#define parm__ipbx_busy_forward_service  DATASTRUCT._parm__ipbx_busy_forward_service
#define scrambler_output_shift           DATASTRUCT._scrambler_output_shift
#define parm__priority_generators        DATASTRUCT._parm__priority_generators
#define parm__sip_timer_no_answer_duration DATASTRUCT._parm__sip_timer_no_answer_duration
#define parm__ata_configuration_update_random_delay DATASTRUCT._parm__ata_configuration_update_random_delay
#define parm__disconnect_tone_detector_table DATASTRUCT._parm__disconnect_tone_detector_table
#define parm__net_lan_save_for_isp       DATASTRUCT._parm__net_lan_save_for_isp
#define fpitch_global                    DATASTRUCT._fpitch_global
#define equalizer_raw_output_real        DATASTRUCT._equalizer_raw_output_real
#define v92n_rx_max_coefs_total          DATASTRUCT._v92n_rx_max_coefs_total
#define force_train_real                 DATASTRUCT._force_train_real
#define faxdet_detect_value              DATASTRUCT._faxdet_detect_value
#define baud_tx_unshifted                DATASTRUCT._baud_tx_unshifted
#define lec__nlp_cng_offset_index        DATASTRUCT._lec__nlp_cng_offset_index
#define parm__ipbx_hot_warm_dial_string  DATASTRUCT._parm__ipbx_hot_warm_dial_string
#define threshold_fax_cc                 DATASTRUCT._threshold_fax_cc
#define v34_short_enable                 DATASTRUCT._v34_short_enable
#define phase_hit_limit                  DATASTRUCT._phase_hit_limit
#define ph2p_anal_adj_log_Wlo            DATASTRUCT._ph2p_anal_adj_log_Wlo
#define lec__nlp_cng_offset              DATASTRUCT._lec__nlp_cng_offset
#define stat__nat_rcv_broadcast          DATASTRUCT._stat__nat_rcv_broadcast
#define dgidet_padrb_mean32              DATASTRUCT._dgidet_padrb_mean32
#define ec_xtrain_shift_slew_remote      DATASTRUCT._ec_xtrain_shift_slew_remote
#define legacy_binary_upload_mode        DATASTRUCT._legacy_binary_upload_mode
#define stat__snr_mse_measure            DATASTRUCT._stat__snr_mse_measure
#define fax_v21_CED_length               DATASTRUCT._fax_v21_CED_length
#define tmp_baud_sum_real                DATASTRUCT._tmp_baud_sum_real
#define phone_headset_debounce_count     DATASTRUCT._phone_headset_debounce_count
#define ipbx_rled_p                      DATASTRUCT._ipbx_rled_p
#define v34_rx_xn_hat_real               DATASTRUCT._v34_rx_xn_hat_real
#define v34h_tx_buffer_current           DATASTRUCT._v34h_tx_buffer_current
#define lec__alpha_err_exp               DATASTRUCT._lec__alpha_err_exp
#define ph2p_anal_adj_log_Wme            DATASTRUCT._ph2p_anal_adj_log_Wme
#define V34S_ANSW_8K0_1RT_S_SN_to_JEdet  DATASTRUCT._V34S_ANSW_8K0_1RT_S_SN_to_JEdet
#define btrec_baud_agc_slew              DATASTRUCT._btrec_baud_agc_slew
#define PCM_LEN_8K0_EQC_TRN1A_2ND        DATASTRUCT._PCM_LEN_8K0_EQC_TRN1A_2ND
#define energy_off_threshold             DATASTRUCT._energy_off_threshold
#define stat__ipod_loopback_mode         DATASTRUCT._stat__ipod_loopback_mode
#define ipod_msg_rx_sig_level            DATASTRUCT._ipod_msg_rx_sig_level
#define decode_frame_received_indication DATASTRUCT._decode_frame_received_indication
#define v34n_parm_data_rate_option       DATASTRUCT._v34n_parm_data_rate_option
#define v34_tx_cn_real                   DATASTRUCT._v34_tx_cn_real
#define v8_rx_QC_data_flag               DATASTRUCT._v8_rx_QC_data_flag
#define stat__ipbx_device_type           DATASTRUCT._stat__ipbx_device_type
#define parm__sdp_g711a_codec_dyn_pt     DATASTRUCT._parm__sdp_g711a_codec_dyn_pt
#define parm__net_debug_enable           DATASTRUCT._parm__net_debug_enable
#define pcm_LO_peak_MSE_max              DATASTRUCT._pcm_LO_peak_MSE_max
#define v90_rx_SdN_samples_remaining_ph3 DATASTRUCT._v90_rx_SdN_samples_remaining_ph3
#define lec__periodic_statistics_buffer  DATASTRUCT._lec__periodic_statistics_buffer
#define v90_apcm_dil_lsp                 DATASTRUCT._v90_apcm_dil_lsp
#define pitch_avg_global                 DATASTRUCT._pitch_avg_global
#define v34_rx_qn_perfect_buffer_real    DATASTRUCT._v34_rx_qn_perfect_buffer_real
#define parm__ipbx_fc_caller_id_inbound_disable DATASTRUCT._parm__ipbx_fc_caller_id_inbound_disable
#define p1800_search_active              DATASTRUCT._p1800_search_active
#define v34s_reneg_test_init_variable_S_length DATASTRUCT._v34s_reneg_test_init_variable_S_length
#define stat__nat_rcv_frag_failed        DATASTRUCT._stat__nat_rcv_frag_failed
#define pspr_x0                          DATASTRUCT._pspr_x0
#define cc_rx_ANAL_DC_imag               DATASTRUCT._cc_rx_ANAL_DC_imag
#define lec__rx_results                  DATASTRUCT._lec__rx_results
#define pspr_x1                          DATASTRUCT._pspr_x1
#define baud_tx_crc_hi                   DATASTRUCT._baud_tx_crc_hi
#define parm__ipbx_line_number           DATASTRUCT._parm__ipbx_line_number
#define v34_BE_pos_log_magnitude         DATASTRUCT._v34_BE_pos_log_magnitude
#define fsk_TONE_flag                    DATASTRUCT._fsk_TONE_flag
#define aux_rx_baud                      DATASTRUCT._aux_rx_baud
#define asm_encode_rtp_dtmf_generate_prev DATASTRUCT._asm_encode_rtp_dtmf_generate_prev
#define legacy_rx_in                     DATASTRUCT._legacy_rx_in
#define v34f_eqc_co_DC_angle             DATASTRUCT._v34f_eqc_co_DC_angle
#define parm__ipbx_bridge_security_entry_duration DATASTRUCT._parm__ipbx_bridge_security_entry_duration
#define v92h_rx_buffer1                  DATASTRUCT._v92h_rx_buffer1
#define DELTA_HYSTERESIS                 DATASTRUCT._DELTA_HYSTERESIS
#define v92h_rx_buffer2                  DATASTRUCT._v92h_rx_buffer2
#define ph2p_anal_count_length           DATASTRUCT._ph2p_anal_count_length
#define lec__dc_offset                   DATASTRUCT._lec__dc_offset
#define ANSam_trace_magphase_mid_real    DATASTRUCT._ANSam_trace_magphase_mid_real
#define g722_2_decstruct                 DATASTRUCT._g722_2_decstruct
#define v92_frame_tx_short               DATASTRUCT._v92_frame_tx_short
#define mgcp_mesg_proc                   DATASTRUCT._mgcp_mesg_proc
#define v90_apcm_dil_ltp                 DATASTRUCT._v90_apcm_dil_ltp
#define ph4n_rx_acknowledge              DATASTRUCT._ph4n_rx_acknowledge
#define lec__buffer_size                 DATASTRUCT._lec__buffer_size
#define gpf_oloop_length                 DATASTRUCT._gpf_oloop_length
#define parm__ipbx_timeout_hold_drop_duration DATASTRUCT._parm__ipbx_timeout_hold_drop_duration
#define saved_Lx_log_P_pointer           DATASTRUCT._saved_Lx_log_P_pointer
#define wr_array                         DATASTRUCT._wr_array
#define comn_v8_found_QC                 DATASTRUCT._comn_v8_found_QC
#define stat__speech_dec_missing_mtr     DATASTRUCT._stat__speech_dec_missing_mtr
#define dec_sid_gain                     DATASTRUCT._dec_sid_gain
#define parm__sdp_ilbc_codec_name        DATASTRUCT._parm__sdp_ilbc_codec_name
#define pcm_rx_TRN2A_log_gain_ratio      DATASTRUCT._pcm_rx_TRN2A_log_gain_ratio
#define parm__orc_iface_enable           DATASTRUCT._parm__orc_iface_enable
#define parm__cp_rd_above_range_metric   DATASTRUCT._parm__cp_rd_above_range_metric
#define saved_tx_MP_data                 DATASTRUCT._saved_tx_MP_data
#define v34_frame_rx_word_count          DATASTRUCT._v34_frame_rx_word_count
#define V92_RX_RETRAIN_DETECT_LIMIT      DATASTRUCT._V92_RX_RETRAIN_DETECT_LIMIT
#define ata_update_time_cfg              DATASTRUCT._ata_update_time_cfg
#define stat__ipbx_fxo_incoming_info     DATASTRUCT._stat__ipbx_fxo_incoming_info
#define parm__ipbx_fc_call_waiting_caller_id_enable DATASTRUCT._parm__ipbx_fc_call_waiting_caller_id_enable
#define dtmf_queue_ipod                  DATASTRUCT._dtmf_queue_ipod
#define v90_tx_dil_ref                   DATASTRUCT._v90_tx_dil_ref
#define v34n_tx_INFO0_body               DATASTRUCT._v34n_tx_INFO0_body
#define test_counter                     DATASTRUCT._test_counter
#define parm__mgcp_public_external_mgcp_port DATASTRUCT._parm__mgcp_public_external_mgcp_port
#define constel_midpoints_table_nrm      DATASTRUCT._constel_midpoints_table_nrm
#define within_fg_state_update           DATASTRUCT._within_fg_state_update
#define baud_rx_no_carrier_flag          DATASTRUCT._baud_rx_no_carrier_flag
#define retrain_threshold                DATASTRUCT._retrain_threshold
#define forced_scrambler_lsw             DATASTRUCT._forced_scrambler_lsw
#define v90_tx_dil_length                DATASTRUCT._v90_tx_dil_length
#define pcm_btr_predict_lsw              DATASTRUCT._pcm_btr_predict_lsw
#define V34_RXI_PLL_COUNT_x2             DATASTRUCT._V34_RXI_PLL_COUNT_x2
#define v92n_rx_precoder_fb_taps         DATASTRUCT._v92n_rx_precoder_fb_taps
#define parm__spk_monitor_rx_gain        DATASTRUCT._parm__spk_monitor_rx_gain
#define parm__sdp_mpeg2_codec_name       DATASTRUCT._parm__sdp_mpeg2_codec_name
#define nat_ip_protocol                  DATASTRUCT._nat_ip_protocol
#define V34_BE2_SLEW_SLOW                DATASTRUCT._V34_BE2_SLEW_SLOW
#define parm__dpbx_led_pstn_in_use       DATASTRUCT._parm__dpbx_led_pstn_in_use
#define lec__datamax_half_excess         DATASTRUCT._lec__datamax_half_excess
#define v34_rx_yn_error_imag32           DATASTRUCT._v34_rx_yn_error_imag32
#define cc_rx_PP_energy_log              DATASTRUCT._cc_rx_PP_energy_log
#define parm__net_debug_level_net        DATASTRUCT._parm__net_debug_level_net
#define parm__tel_answer_tone_length     DATASTRUCT._parm__tel_answer_tone_length
#define v34h_rx_m_ijk_ring_index_pointer DATASTRUCT._v34h_rx_m_ijk_ring_index_pointer
#define FALL_adjusted_mse_count          DATASTRUCT._FALL_adjusted_mse_count
#define parm__ipbx_timeout_warning_duration DATASTRUCT._parm__ipbx_timeout_warning_duration
#define asm_decode_packed_frame_start    DATASTRUCT._asm_decode_packed_frame_start
#define clnt_ssl                         DATASTRUCT._clnt_ssl
#define ppastVad                         DATASTRUCT._ppastVad
#define ctl                              DATASTRUCT._ctl
#define lec__probe_tx_output             DATASTRUCT._lec__probe_tx_output
#define g722_enc_detlow                  DATASTRUCT._g722_enc_detlow
#define parm__vppn_channel_activation_mask DATASTRUCT._parm__vppn_channel_activation_mask
#define predicted_rx_xn_B1_Q_n_buffer    DATASTRUCT._predicted_rx_xn_B1_Q_n_buffer
#define sonitrol_DNIS_digits             DATASTRUCT._sonitrol_DNIS_digits
#define sonitrol_franchise_label         DATASTRUCT._sonitrol_franchise_label
#define v34_resync_mcomp_buffer_real32   DATASTRUCT._v34_resync_mcomp_buffer_real32
#define CONVERT_AGC_2_ENERGY_TARGET_LOG  DATASTRUCT._CONVERT_AGC_2_ENERGY_TARGET_LOG
#define g726_in_bits                     DATASTRUCT._g726_in_bits
#define parm__codec_line_in_use_detect_method DATASTRUCT._parm__codec_line_in_use_detect_method
#define parm__dpbx_led_polarity_mask     DATASTRUCT._parm__dpbx_led_polarity_mask
#define baud_slew_buffer                 DATASTRUCT._baud_slew_buffer
#define v8_tx_sync_code                  DATASTRUCT._v8_tx_sync_code
#define Enc_Inst                         DATASTRUCT._Enc_Inst
#define v34s_reneg_test_init_ignore_SN   DATASTRUCT._v34s_reneg_test_init_ignore_SN
#define parm__tripwire_video_record      DATASTRUCT._parm__tripwire_video_record
#define lec__dc_offset_intermediate      DATASTRUCT._lec__dc_offset_intermediate
#define parm__speech_enc_mbx_addr        DATASTRUCT._parm__speech_enc_mbx_addr
#define g168_initialized                 DATASTRUCT._g168_initialized
#define lec__nlp_loose_counter           DATASTRUCT._lec__nlp_loose_counter
#define ph2_dummy_loopback_imag          DATASTRUCT._ph2_dummy_loopback_imag
#define v90_shape_preload_count          DATASTRUCT._v90_shape_preload_count
#define phone_power_switch_condition     DATASTRUCT._phone_power_switch_condition
#define v17_correct_phase                DATASTRUCT._v17_correct_phase
#define V34_SLEW_COS_BE                  DATASTRUCT._V34_SLEW_COS_BE
#define saved_scrambler_lsw              DATASTRUCT._saved_scrambler_lsw
#define v34s_reneg_resp_S_to_SN_to_retrain DATASTRUCT._v34s_reneg_resp_S_to_SN_to_retrain
#define txs_count                        DATASTRUCT._txs_count
#define ipod_iface_tx_size               DATASTRUCT._ipod_iface_tx_size
#define v34_yn_equalized_real            DATASTRUCT._v34_yn_equalized_real
#define v90_tx_dil_sp_mask               DATASTRUCT._v90_tx_dil_sp_mask
#define v90_rx_delay_buffer              DATASTRUCT._v90_rx_delay_buffer
#define ph2_rx_baud_current              DATASTRUCT._ph2_rx_baud_current
#define parm__sdp_g711u_codec_dyn_pt     DATASTRUCT._parm__sdp_g711u_codec_dyn_pt
#define vportcap_globalptr               DATASTRUCT._vportcap_globalptr
#define ph2p_fefo_ar_ai_stage2_buffer32  DATASTRUCT._ph2p_fefo_ar_ai_stage2_buffer32
#define parm__radio_encryption_settings  DATASTRUCT._parm__radio_encryption_settings
#define agc_2_inv_exponent               DATASTRUCT._agc_2_inv_exponent
#define baud_tx_crc_lo                   DATASTRUCT._baud_tx_crc_lo
#define ph2p_anal_log_BxR_buffer         DATASTRUCT._ph2p_anal_log_BxR_buffer
#define baud_rx_data_unit                DATASTRUCT._baud_rx_data_unit
#define enc_cur_gain                     DATASTRUCT._enc_cur_gain
#define saved_v90trn_pad_table           DATASTRUCT._saved_v90trn_pad_table
#define stat__speech_dec_frame_based_active DATASTRUCT._stat__speech_dec_frame_based_active
#define Prev_Min                         DATASTRUCT._Prev_Min
#define loss_event                       DATASTRUCT._loss_event
#define cc_rx_notch_buffer               DATASTRUCT._cc_rx_notch_buffer
#define dgs_first                        DATASTRUCT._dgs_first
#define g168_err_level                   DATASTRUCT._g168_err_level
#define lec__dc_offset_lpf32             DATASTRUCT._lec__dc_offset_lpf32
#define test_2_msw                       DATASTRUCT._test_2_msw
#define ph2n_probing_receive_gain        DATASTRUCT._ph2n_probing_receive_gain
#define v92_rx_decoder_up_cutoff         DATASTRUCT._v92_rx_decoder_up_cutoff
#define ph2n_tx_2743_option              DATASTRUCT._ph2n_tx_2743_option
#define pcm_eq_ff_slews                  DATASTRUCT._pcm_eq_ff_slews
#define stat__mgcp_local_contact_domain_name DATASTRUCT._stat__mgcp_local_contact_domain_name
#define stat__ipbx_fxo_cid_received      DATASTRUCT._stat__ipbx_fxo_cid_received
#define cc_rx_PP_repetition_counter      DATASTRUCT._cc_rx_PP_repetition_counter
#define stat__tx_level_dbm               DATASTRUCT._stat__tx_level_dbm
#define baud_rx_substate                 DATASTRUCT._baud_rx_substate
#define pcm_rx_6dB_pad_detect            DATASTRUCT._pcm_rx_6dB_pad_detect
#define v92h_rx_K_input_offset           DATASTRUCT._v92h_rx_K_input_offset
#define ethernet_outgoing_count          DATASTRUCT._ethernet_outgoing_count
#define parm__ata_service_name           DATASTRUCT._parm__ata_service_name
#define firstTime_classify               DATASTRUCT._firstTime_classify
#define v34_tx_local_pattern_offset      DATASTRUCT._v34_tx_local_pattern_offset
#define stat__cp_rd_ring_energy_active   DATASTRUCT._stat__cp_rd_ring_energy_active
#define constel_output0                  DATASTRUCT._constel_output0
#define save_measured_roundtrip_delay    DATASTRUCT._save_measured_roundtrip_delay
#define constel_output1                  DATASTRUCT._constel_output1
#define constel_output2                  DATASTRUCT._constel_output2
#define constel_output3                  DATASTRUCT._constel_output3
#define fsk_lpf_poffset                  DATASTRUCT._fsk_lpf_poffset
#define parm__sdp_g726_16_codec_name     DATASTRUCT._parm__sdp_g726_16_codec_name
#define parm__sdp_melp_codec_name        DATASTRUCT._parm__sdp_melp_codec_name
#define v92n_rx_CPus_body                DATASTRUCT._v92n_rx_CPus_body
#define faxdet_data_sum_v21              DATASTRUCT._faxdet_data_sum_v21
#define parm__faxdet_ced_threshold       DATASTRUCT._parm__faxdet_ced_threshold
#define ph2_rx_special_bpf_buffer        DATASTRUCT._ph2_rx_special_bpf_buffer
#define parm__audio_monitor_gain         DATASTRUCT._parm__audio_monitor_gain
#define stat__radio_                     DATASTRUCT._stat__radio_
#define parm__pulse_break_time           DATASTRUCT._parm__pulse_break_time
#define convert_energy_log               DATASTRUCT._convert_energy_log
#define asm_decode_packed_length         DATASTRUCT._asm_decode_packed_length
#define ec_slow_shift_slew_local         DATASTRUCT._ec_slow_shift_slew_local
#define parm__ipbx_fc_caller_id_outbound_disable_once DATASTRUCT._parm__ipbx_fc_caller_id_outbound_disable_once
#define predicted_rx_xn_B1_imag          DATASTRUCT._predicted_rx_xn_B1_imag
#define v34_rx_qn_tilde_buffer_real      DATASTRUCT._v34_rx_qn_tilde_buffer_real
#define v34s_reneg_initiator             DATASTRUCT._v34s_reneg_initiator
#define ph2p_anal_variance_CS_pointer    DATASTRUCT._ph2p_anal_variance_CS_pointer
#define faxmon_frame_state               DATASTRUCT._faxmon_frame_state
#define pcm_disc_slot_match_number       DATASTRUCT._pcm_disc_slot_match_number
#define hit_counter_init                 DATASTRUCT._hit_counter_init
#define phone_ptt_condition              DATASTRUCT._phone_ptt_condition
#define pcm_tx_power_log                 DATASTRUCT._pcm_tx_power_log
#define detect_v21_detect_lpf1           DATASTRUCT._detect_v21_detect_lpf1
#define detect_v21_detect_lpf2           DATASTRUCT._detect_v21_detect_lpf2
#define parm__jpeg_thumbnail_enable      DATASTRUCT._parm__jpeg_thumbnail_enable
#define parm__ipbx_caller_id_inbound_service DATASTRUCT._parm__ipbx_caller_id_inbound_service
#define V34_BE_INITIAL_Gn                DATASTRUCT._V34_BE_INITIAL_Gn
#define V34_AB_SIGNAL_SLEW_RATE          DATASTRUCT._V34_AB_SIGNAL_SLEW_RATE
#define V34_BE_INITIAL_Gp                DATASTRUCT._V34_BE_INITIAL_Gp
#define v90n_tx_INFO1a_body              DATASTRUCT._v90n_tx_INFO1a_body
#define v90_shape_lookahead_1            DATASTRUCT._v90_shape_lookahead_1
#define sdt_DC_angle_store_real          DATASTRUCT._sdt_DC_angle_store_real
#define v90_shape_lookahead_2            DATASTRUCT._v90_shape_lookahead_2
#define v90_shape_lookahead_3            DATASTRUCT._v90_shape_lookahead_3
#define v34f_eqc_diff_DC_exponent        DATASTRUCT._v34f_eqc_diff_DC_exponent
#define parm__net_isp_reconnect_on_link_loss DATASTRUCT._parm__net_isp_reconnect_on_link_loss
#define parm__ata_configuration_revision DATASTRUCT._parm__ata_configuration_revision
#define l_envdel                         DATASTRUCT._l_envdel
#define stat__speech_dec_current_frame   DATASTRUCT._stat__speech_dec_current_frame
#define l_postHPFInHis                   DATASTRUCT._l_postHPFInHis
#define parm__ipbx_fc_block_anonymous_disable DATASTRUCT._parm__ipbx_fc_block_anonymous_disable
#define v92_rx_decoder_ep_input_energy40 DATASTRUCT._v92_rx_decoder_ep_input_energy40
#define v90_rx_reneg_flag                DATASTRUCT._v90_rx_reneg_flag
#define V90_CENTER_TAP_DELAY             DATASTRUCT._V90_CENTER_TAP_DELAY
#define MeanSZC                          DATASTRUCT._MeanSZC
#define tmp_full_energy32                DATASTRUCT._tmp_full_energy32
#define faxmon_frame                     DATASTRUCT._faxmon_frame
#define ph2p_anal_maxrates_CS_table      DATASTRUCT._ph2p_anal_maxrates_CS_table
#define ch_seize_threshold               DATASTRUCT._ch_seize_threshold
#define parm__dtmf_tone_on_time          DATASTRUCT._parm__dtmf_tone_on_time
#define cc_counter_ones                  DATASTRUCT._cc_counter_ones
#define pcm_rx_retrain_detect_routine    DATASTRUCT._pcm_rx_retrain_detect_routine
#define v34_TRN2_MSE_stack               DATASTRUCT._v34_TRN2_MSE_stack
#define ipbx_gled_p                      DATASTRUCT._ipbx_gled_p
#define pcm_btr_1st                      DATASTRUCT._pcm_btr_1st
#define silence_lpf_slew                 DATASTRUCT._silence_lpf_slew
#define parm__radio_ptt_digit_keys       DATASTRUCT._parm__radio_ptt_digit_keys
#define lec__best_erl_ratio              DATASTRUCT._lec__best_erl_ratio
#define fsk_clock_capture_width          DATASTRUCT._fsk_clock_capture_width
#define sonitrol_ethernet_local_timer    DATASTRUCT._sonitrol_ethernet_local_timer
#define special_match_lsw                DATASTRUCT._special_match_lsw
#define v92_rx_decoder_ep_alpha_exp      DATASTRUCT._v92_rx_decoder_ep_alpha_exp
#define MONITOR_PHASE_RAW_STATUS         DATASTRUCT._MONITOR_PHASE_RAW_STATUS
#define cc_rx_PP_last_compare_ratio      DATASTRUCT._cc_rx_PP_last_compare_ratio
#define trellis_minval                   DATASTRUCT._trellis_minval
#define v34_tx_qn_remote_buffer_imag     DATASTRUCT._v34_tx_qn_remote_buffer_imag
#define impedance_monitor_max_tap_lpf1   DATASTRUCT._impedance_monitor_max_tap_lpf1
#define sonitrol_audio_ip_configured     DATASTRUCT._sonitrol_audio_ip_configured
#define impedance_monitor_max_tap_lpf2   DATASTRUCT._impedance_monitor_max_tap_lpf2
#define v34_pp_fill_count                DATASTRUCT._v34_pp_fill_count
#define v34n_tx_TRN_length               DATASTRUCT._v34n_tx_TRN_length
#define PH2P_ANAL_MSE_CORRECT            DATASTRUCT._PH2P_ANAL_MSE_CORRECT
#define tone_detector_constants          DATASTRUCT._tone_detector_constants
#define cc_tx_interpolator_buffer        DATASTRUCT._cc_tx_interpolator_buffer
#define shadow_panel_group_id            DATASTRUCT._shadow_panel_group_id
#define v34n_rx_preeq_gain               DATASTRUCT._v34n_rx_preeq_gain
#define ANSam_detect_15Hz                DATASTRUCT._ANSam_detect_15Hz
#define lec__nlp_detect_tight            DATASTRUCT._lec__nlp_detect_tight
#define enc_old_exc                      DATASTRUCT._enc_old_exc
#define parm__net_debug_level_vppn       DATASTRUCT._parm__net_debug_level_vppn
#define stat__nat_wan_create             DATASTRUCT._stat__nat_wan_create
#define stat__ipbx_sub_state             DATASTRUCT._stat__ipbx_sub_state
#define sample_buffer                    DATASTRUCT._sample_buffer
#define parm__v8__call_function          DATASTRUCT._parm__v8__call_function
#define ph2p_fefo_gain_adjust_shift      DATASTRUCT._ph2p_fefo_gain_adjust_shift
#define ph4n_rx_MP_type                  DATASTRUCT._ph4n_rx_MP_type
#define v34_BE_log_jam_baud_agc          DATASTRUCT._v34_BE_log_jam_baud_agc
#define parm__codec_disconnect_tone_3_duration DATASTRUCT._parm__codec_disconnect_tone_3_duration
#define v92n_tx_filter_sections          DATASTRUCT._v92n_tx_filter_sections
#define sequence_detect_level            DATASTRUCT._sequence_detect_level
#define fsk_TONE_tonesize                DATASTRUCT._fsk_TONE_tonesize
#define sid_sav                          DATASTRUCT._sid_sav
#define BETA0                            DATASTRUCT._BETA0
#define v34_resync_variance_buffer_real  DATASTRUCT._v34_resync_variance_buffer_real
#define ph2_INFOMARKS_detected           DATASTRUCT._ph2_INFOMARKS_detected
#define phone_input_scan_count           DATASTRUCT._phone_input_scan_count
#define rf_rx_dc_ioffset                 DATASTRUCT._rf_rx_dc_ioffset
#define equalizer_coef_count             DATASTRUCT._equalizer_coef_count
#define parm__speech_rtp_cng_duration    DATASTRUCT._parm__speech_rtp_cng_duration
#define fsk_run_demodulator              DATASTRUCT._fsk_run_demodulator
#define detect_demod_complex             DATASTRUCT._detect_demod_complex
#define v34_temp_hi_me_pre_equalizer_coefs DATASTRUCT._v34_temp_hi_me_pre_equalizer_coefs
#define v90_rx_decision_routine          DATASTRUCT._v90_rx_decision_routine
#define parm__sip_incoming_auth_user_name DATASTRUCT._parm__sip_incoming_auth_user_name
#define v34_MSE_value                    DATASTRUCT._v34_MSE_value
#define l_lpres_delout                   DATASTRUCT._l_lpres_delout
#define DELTA_ENERGY_THRESHOLD           DATASTRUCT._DELTA_ENERGY_THRESHOLD
#define sart_rx_timeout_reload           DATASTRUCT._sart_rx_timeout_reload
#define sample_cnt_high                  DATASTRUCT._sample_cnt_high
#define mgcp_controller_sockid           DATASTRUCT._mgcp_controller_sockid
#define nat_pkt_pppoe_ptr                DATASTRUCT._nat_pkt_pppoe_ptr
#define ph2n_rx_v92_ITU_bits_carrier     DATASTRUCT._ph2n_rx_v92_ITU_bits_carrier
#define FALL_fallforward_possible_flag   DATASTRUCT._FALL_fallforward_possible_flag
#define dgs_energy32                     DATASTRUCT._dgs_energy32
#define max_energy                       DATASTRUCT._max_energy
#define ph2_INFO_detect_enable           DATASTRUCT._ph2_INFO_detect_enable
#define rd_prev_was_off                  DATASTRUCT._rd_prev_was_off
#define dma_enabled                      DATASTRUCT._dma_enabled
#define stat__speech_decoder_underflow   DATASTRUCT._stat__speech_decoder_underflow
#define overlay_ph2_overrides_probing_results DATASTRUCT._overlay_ph2_overrides_probing_results
#define output_lock_offset               DATASTRUCT._output_lock_offset
#define v92n_tx_Jp_body                  DATASTRUCT._v92n_tx_Jp_body
#define v34h_tx_V0_m                     DATASTRUCT._v34h_tx_V0_m
#define lec__data_size_mag_adjust        DATASTRUCT._lec__data_size_mag_adjust
#define v92n_rx_Ja_body_end              DATASTRUCT._v92n_rx_Ja_body_end
#define parm__ipbx_number_error_tone     DATASTRUCT._parm__ipbx_number_error_tone
#define parm__ipbx_fc_disturb_accept_disable DATASTRUCT._parm__ipbx_fc_disturb_accept_disable
#define parm__ipbx_dial_prefix           DATASTRUCT._parm__ipbx_dial_prefix
#define edge_m1200_real                  DATASTRUCT._edge_m1200_real
#define v34h_tx_AMP_value                DATASTRUCT._v34h_tx_AMP_value
#define train_scrambler_low              DATASTRUCT._train_scrambler_low
#define v34_delay_forced_start           DATASTRUCT._v34_delay_forced_start
#define mem_syn_pst                      DATASTRUCT._mem_syn_pst
#define parm__rtp_encode_gain            DATASTRUCT._parm__rtp_encode_gain
#define found_POST_2100_calling_tone     DATASTRUCT._found_POST_2100_calling_tone
#define stat__tone_detect_mask           DATASTRUCT._stat__tone_detect_mask
#define enc_sharp                        DATASTRUCT._enc_sharp
#define ANSam_current_sample             DATASTRUCT._ANSam_current_sample
#define nat_icmp_ip_protocol             DATASTRUCT._nat_icmp_ip_protocol
#define ph2n_tx_maxrate                  DATASTRUCT._ph2n_tx_maxrate
#define legacy_rx_out                    DATASTRUCT._legacy_rx_out
#define ph2p_fefo_SB_gain_adjust         DATASTRUCT._ph2p_fefo_SB_gain_adjust
#define v34n_rx_data_rate                DATASTRUCT._v34n_rx_data_rate
#define v34n_rxtx_cleardown_active       DATASTRUCT._v34n_rxtx_cleardown_active
#define tonemute_new_enr_check           DATASTRUCT._tonemute_new_enr_check
#define automode_next_state              DATASTRUCT._automode_next_state
#define parm__rtp_jitter_buffer_minimum_depth DATASTRUCT._parm__rtp_jitter_buffer_minimum_depth
#define dev_xx_frame_offset              DATASTRUCT._dev_xx_frame_offset
#define v34n_rx_primary_channel_maxrate  DATASTRUCT._v34n_rx_primary_channel_maxrate
#define SN_LT                            DATASTRUCT._SN_LT
#define rf_dma_fail                      DATASTRUCT._rf_dma_fail
#define v34_resync_mcomp_buffer_imag32   DATASTRUCT._v34_resync_mcomp_buffer_imag32
#define lastGain_postfilt                DATASTRUCT._lastGain_postfilt
#define ph2p_fefo_holdoff_time           DATASTRUCT._ph2p_fefo_holdoff_time
#define ph2p_powr_dmod_rx_buffer32       DATASTRUCT._ph2p_powr_dmod_rx_buffer32
#define V34S_LEN_8K0_1ST_PHASE_CHANGE    DATASTRUCT._V34S_LEN_8K0_1ST_PHASE_CHANGE
#define v90_tx_send_Rx_sequence_flag     DATASTRUCT._v90_tx_send_Rx_sequence_flag
#define fsk_bitstream_lsb                DATASTRUCT._fsk_bitstream_lsb
#define parm__ata_firmware_update_random_delay DATASTRUCT._parm__ata_firmware_update_random_delay
#define ph4n_tx_primary_channel_maxrate  DATASTRUCT._ph4n_tx_primary_channel_maxrate
#define parm__speech_dtmf_regeneration   DATASTRUCT._parm__speech_dtmf_regeneration
#define sonitrol_wiznet_channel          DATASTRUCT._sonitrol_wiznet_channel
#define found_AA_tone                    DATASTRUCT._found_AA_tone
#define tx_count_test                    DATASTRUCT._tx_count_test
#define audio_outgoing_buffer            DATASTRUCT._audio_outgoing_buffer
#define tmp_half_energy32                DATASTRUCT._tmp_half_energy32
#define V34S_LEN_8K0_REMOTE_GUARD        DATASTRUCT._V34S_LEN_8K0_REMOTE_GUARD
#define v34_delay_forced_state           DATASTRUCT._v34_delay_forced_state
#define v8_rx_QC_data_octet              DATASTRUCT._v8_rx_QC_data_octet
#define pcm_x_law_decode_routine         DATASTRUCT._pcm_x_law_decode_routine
#define cc_rx_ANAL_BEp_real              DATASTRUCT._cc_rx_ANAL_BEp_real
#define state0_save_decimation_count     DATASTRUCT._state0_save_decimation_count
#define gpf_RRval                        DATASTRUCT._gpf_RRval
#define bg_state_list                    DATASTRUCT._bg_state_list
#define sonitrol_line_status             DATASTRUCT._sonitrol_line_status
#define ptloop_phdet_error_slow32        DATASTRUCT._ptloop_phdet_error_slow32
#define xxx_rb_mode_enable               DATASTRUCT._xxx_rb_mode_enable
#define dtmf_lpf_pow32                   DATASTRUCT._dtmf_lpf_pow32
#define v92n_tx_CPd_constel              DATASTRUCT._v92n_tx_CPd_constel
#define CID_baud                         DATASTRUCT._CID_baud
#define parm__ipbx_fxo_voip_call_enable  DATASTRUCT._parm__ipbx_fxo_voip_call_enable
#define correlator_fit_threshold         DATASTRUCT._correlator_fit_threshold
#define v34_slew_pos_BE                  DATASTRUCT._v34_slew_pos_BE
#define saved__pump_conference_mode      DATASTRUCT._saved__pump_conference_mode
#define DIL_probing_index_value_7bit     DATASTRUCT._DIL_probing_index_value_7bit
#define lec__doubletalk_detect           DATASTRUCT._lec__doubletalk_detect
#define parm__ipbx_no_answer_duration    DATASTRUCT._parm__ipbx_no_answer_duration
#define s1_detector_rate_reduction_counter DATASTRUCT._s1_detector_rate_reduction_counter
#define detect_energy_lpf1               DATASTRUCT._detect_energy_lpf1
#define asm_oob_tone                     DATASTRUCT._asm_oob_tone
#define detect_energy_lpf2               DATASTRUCT._detect_energy_lpf2
#define parm__voip_provider              DATASTRUCT._parm__voip_provider
#define fg_inhibit_queue                 DATASTRUCT._fg_inhibit_queue
#define speech                           DATASTRUCT._speech
#define previous_eq_data0                DATASTRUCT._previous_eq_data0
#define previous_eq_data1                DATASTRUCT._previous_eq_data1
#define ipod_msg_tx_mod_type             DATASTRUCT._ipod_msg_tx_mod_type
#define ig_best                          DATASTRUCT._ig_best
#define hsflag_fract_exchange_buffer     DATASTRUCT._hsflag_fract_exchange_buffer
#define v29_anti_lock_recovery_limit     DATASTRUCT._v29_anti_lock_recovery_limit
#define parm__vppn_device_state          DATASTRUCT._parm__vppn_device_state
#define parm__ipbx_timeout_tone_duration DATASTRUCT._parm__ipbx_timeout_tone_duration
#define faxdet_value_previous_ansam      DATASTRUCT._faxdet_value_previous_ansam
#define g711a_plc_lastq                  DATASTRUCT._g711a_plc_lastq
#define parm__ipbx_fc_busy_forward_enable DATASTRUCT._parm__ipbx_fc_busy_forward_enable
#define v90_shape_not_first              DATASTRUCT._v90_shape_not_first
#define v90_shape_filters                DATASTRUCT._v90_shape_filters
#define PH2P_POWR_LX_FINAL_TUNE          DATASTRUCT._PH2P_POWR_LX_FINAL_TUNE
#define PCM_LEN_8K0_1ST_GEAR_CHANGE      DATASTRUCT._PCM_LEN_8K0_1ST_GEAR_CHANGE
#define v34_frame_rx_E_found_previous    DATASTRUCT._v34_frame_rx_E_found_previous
#define V34_SLEW_RETRAIN                 DATASTRUCT._V34_SLEW_RETRAIN
#define v34_tx_W0_2m                     DATASTRUCT._v34_tx_W0_2m
#define parm__cp_rd_inc_detect_duration  DATASTRUCT._parm__cp_rd_inc_detect_duration
#define parm__net_isp_save_as_assigned   DATASTRUCT._parm__net_isp_save_as_assigned
#define v34h_tx_g2_table                 DATASTRUCT._v34h_tx_g2_table
#define p18_reversal_timeout_init        DATASTRUCT._p18_reversal_timeout_init
#define V34S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT DATASTRUCT._V34S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT
#define echo_canceller_coefs             DATASTRUCT._echo_canceller_coefs
#define v34n_rx_optional_gain            DATASTRUCT._v34n_rx_optional_gain
#define v92_modem_on_hold_enable         DATASTRUCT._v92_modem_on_hold_enable
#define lookback_array_poffset           DATASTRUCT._lookback_array_poffset
#define parm__ata_lcr_domain_name        DATASTRUCT._parm__ata_lcr_domain_name
#define v90_rx_k_frame                   DATASTRUCT._v90_rx_k_frame
#define ipod_msg_rx_sig_type             DATASTRUCT._ipod_msg_rx_sig_type
#define v34n_parm_ptt_hi_carrier_option  DATASTRUCT._v34n_parm_ptt_hi_carrier_option
#define parm__slac_ring_type             DATASTRUCT._parm__slac_ring_type
#define act_min_sub_shift                DATASTRUCT._act_min_sub_shift
#define stat__net_dhcp_status            DATASTRUCT._stat__net_dhcp_status
#define parm__ipbx_dial_after_8          DATASTRUCT._parm__ipbx_dial_after_8
#define classStat_global                 DATASTRUCT._classStat_global
#define legacy_rx_retransmit_handler     DATASTRUCT._legacy_rx_retransmit_handler
#define parm__test_tone                  DATASTRUCT._parm__test_tone
#define parm__ipbx_dial_after_9          DATASTRUCT._parm__ipbx_dial_after_9
#define record_sample_mode               DATASTRUCT._record_sample_mode
#define sample_cnt                       DATASTRUCT._sample_cnt
#define pcm_DC_offset_value              DATASTRUCT._pcm_DC_offset_value
#define line_rx_intp                     DATASTRUCT._line_rx_intp
#define prev_lsp                         DATASTRUCT._prev_lsp
#define parm__dtmf_high_tone_gain        DATASTRUCT._parm__dtmf_high_tone_gain
#define asm_encode_audio_frame_cnt       DATASTRUCT._asm_encode_audio_frame_cnt
#define w_lsf_s                          DATASTRUCT._w_lsf_s
#define v34h_rx_state                    DATASTRUCT._v34h_rx_state
#define parm__dm_v90_dpcm_data_rate_mask DATASTRUCT._parm__dm_v90_dpcm_data_rate_mask
#define v34_rx_qn_save1_coefs            DATASTRUCT._v34_rx_qn_save1_coefs
#define v34h_tx_m_ijk_ring_index_buffer  DATASTRUCT._v34h_tx_m_ijk_ring_index_buffer
#define parm__net_router_mode            DATASTRUCT._parm__net_router_mode
#define constellation_imag               DATASTRUCT._constellation_imag
#define ph2p_bg_sample_buffer            DATASTRUCT._ph2p_bg_sample_buffer
#define dtmf_peak_col_index              DATASTRUCT._dtmf_peak_col_index
#define lec__rx_suppressor_gain          DATASTRUCT._lec__rx_suppressor_gain
#define perfect_complex                  DATASTRUCT._perfect_complex
#define phone_hook_switch_condition      DATASTRUCT._phone_hook_switch_condition
#define energy_lpf_shift_slew            DATASTRUCT._energy_lpf_shift_slew
#define btrec_baud_filter_gain_lsw       DATASTRUCT._btrec_baud_filter_gain_lsw
#define eqout_leading_real               DATASTRUCT._eqout_leading_real
#define saved_descrambler_input          DATASTRUCT._saved_descrambler_input
#define parm__net_router_circuit         DATASTRUCT._parm__net_router_circuit
#define sart_rx_hybrid_packed_mode_data  DATASTRUCT._sart_rx_hybrid_packed_mode_data
#define stat__nat_rcv_l2tp               DATASTRUCT._stat__nat_rcv_l2tp
#define v34_frame_tx_bit_buffer          DATASTRUCT._v34_frame_tx_bit_buffer
#define picp_gain_name                   DATASTRUCT._picp_gain_name
#define v90_tx_send_Ed_sequence_flag     DATASTRUCT._v90_tx_send_Ed_sequence_flag
#define dgs_energy_count                 DATASTRUCT._dgs_energy_count
#define p18_dcd_threshold                DATASTRUCT._p18_dcd_threshold
#define v34_forced_train_routine         DATASTRUCT._v34_forced_train_routine
#define parm__mpeg2_sendto_ip_address    DATASTRUCT._parm__mpeg2_sendto_ip_address
#define pcm_ec_conv_poffset              DATASTRUCT._pcm_ec_conv_poffset
#define cc_rx_delay_poffset              DATASTRUCT._cc_rx_delay_poffset
#define fax_CNG_on_length                DATASTRUCT._fax_CNG_on_length
#define gpf_xpointer                     DATASTRUCT._gpf_xpointer
#define fax_CNG_preoff_length            DATASTRUCT._fax_CNG_preoff_length
#define res2_buf                         DATASTRUCT._res2_buf
#define demod_leading_imag               DATASTRUCT._demod_leading_imag
#define stat__phone_call_elapsed_time    DATASTRUCT._stat__phone_call_elapsed_time
#define parm__ipbx_fc_no_answer_forward_disable DATASTRUCT._parm__ipbx_fc_no_answer_forward_disable
#define v34s_reneg_init_SN_to_S_to_retrain DATASTRUCT._v34s_reneg_init_SN_to_S_to_retrain
#define v90n_rx_maximum_power            DATASTRUCT._v90n_rx_maximum_power
#define stat__oicp_parse_state           DATASTRUCT._stat__oicp_parse_state
#define lec__nlp_clp_enable              DATASTRUCT._lec__nlp_clp_enable
#define syntdenum_ilbc                   DATASTRUCT._syntdenum_ilbc
#define encode_frame_end_timestamp       DATASTRUCT._encode_frame_end_timestamp
#define pcm_saved_L_over_2_size          DATASTRUCT._pcm_saved_L_over_2_size
#define parm__call_progress_cadence_detect_mask DATASTRUCT._parm__call_progress_cadence_detect_mask
#define lec__td_data                     DATASTRUCT._lec__td_data
#define cc_rx_interpolator_poffset       DATASTRUCT._cc_rx_interpolator_poffset
#define v92n_parm_moh_enable             DATASTRUCT._v92n_parm_moh_enable
#define nat_ipsec_entry                  DATASTRUCT._nat_ipsec_entry
#define DIL_calculation_RBS_pcm_maximum  DATASTRUCT._DIL_calculation_RBS_pcm_maximum
#define demod_real                       DATASTRUCT._demod_real
#define picp_speed_dial_index            DATASTRUCT._picp_speed_dial_index
#define parm__mbx_timeout_flash_duration DATASTRUCT._parm__mbx_timeout_flash_duration
#define clock_mode                       DATASTRUCT._clock_mode
#define monitor_sample_slow_relative_threshold DATASTRUCT._monitor_sample_slow_relative_threshold
#define sonitrol_local_gateway           DATASTRUCT._sonitrol_local_gateway
#define parm__analog_loss_attn           DATASTRUCT._parm__analog_loss_attn
#define nat_pptp_entry                   DATASTRUCT._nat_pptp_entry
#define pcm_rx_sign                      DATASTRUCT._pcm_rx_sign
#define parm__net_assigned_domain_name   DATASTRUCT._parm__net_assigned_domain_name
#define l_envdel2                        DATASTRUCT._l_envdel2
#define rxs_demod_half_imag              DATASTRUCT._rxs_demod_half_imag
#define parm__ipbx_fxo_cid_required      DATASTRUCT._parm__ipbx_fxo_cid_required
#define parm__selcall_dec_enable         DATASTRUCT._parm__selcall_dec_enable
#define v34h_tx_q_bits_per_2D_subgroup   DATASTRUCT._v34h_tx_q_bits_per_2D_subgroup
#define v34_frame_rx_save_bit_count      DATASTRUCT._v34_frame_rx_save_bit_count
#define MeanLSF                          DATASTRUCT._MeanLSF
#define parm__mgcp_controller_local_port DATASTRUCT._parm__mgcp_controller_local_port
#define v34_rx_trellis_lookback_array    DATASTRUCT._v34_rx_trellis_lookback_array
#define stat__nat_snd_icmp               DATASTRUCT._stat__nat_snd_icmp
#define parm__ipbx_fc_call_forward_disable DATASTRUCT._parm__ipbx_fc_call_forward_disable
#define nat_icmp_src_addr                DATASTRUCT._nat_icmp_src_addr
#define clock_cycles_per_baud            DATASTRUCT._clock_cycles_per_baud
#define lec__tx_results                  DATASTRUCT._lec__tx_results
#define v34n_tx_lo_carrier_option        DATASTRUCT._v34n_tx_lo_carrier_option
#define cc_rx_ANAL_prev_energy_log       DATASTRUCT._cc_rx_ANAL_prev_energy_log
#define start_bfi600                     DATASTRUCT._start_bfi600
#define parm__dtx_flag                   DATASTRUCT._parm__dtx_flag
#define v34s_reneg_test_resp_ignore_SN   DATASTRUCT._v34s_reneg_test_resp_ignore_SN
#define fg_event_remove                  DATASTRUCT._fg_event_remove
#define faxdet_value_grl                 DATASTRUCT._faxdet_value_grl
#define v90n_tx_receive_data_rate        DATASTRUCT._v90n_tx_receive_data_rate
#define baud_tx_flag                     DATASTRUCT._baud_tx_flag
#define parm__ipbx_remote_feature_code_service DATASTRUCT._parm__ipbx_remote_feature_code_service
#define picp_number_of                   DATASTRUCT._picp_number_of
#define v90_rx_R_detect_flag             DATASTRUCT._v90_rx_R_detect_flag
#define cc_rx_S_energy_log               DATASTRUCT._cc_rx_S_energy_log
#define cc_rx_PP_DC_save_energy_log      DATASTRUCT._cc_rx_PP_DC_save_energy_log
#define stat__nat_snd_ip_fragment        DATASTRUCT._stat__nat_snd_ip_fragment
#define stat__sip_is_registered          DATASTRUCT._stat__sip_is_registered
#define stat__call_progress_cadence_detect_mask DATASTRUCT._stat__call_progress_cadence_detect_mask
#define parm__net_ddns_password          DATASTRUCT._parm__net_ddns_password
#define parm__nat_timeout_ip             DATASTRUCT._parm__nat_timeout_ip
#define parm__ipbx_fxo_autoanswer_list   DATASTRUCT._parm__ipbx_fxo_autoanswer_list
#define lag0q_dec_mem_s                  DATASTRUCT._lag0q_dec_mem_s
#define parm__ipbx_led_do_not_disturb    DATASTRUCT._parm__ipbx_led_do_not_disturb
#define sonitrol_v34_oob_counter         DATASTRUCT._sonitrol_v34_oob_counter
#define special_data_limit               DATASTRUCT._special_data_limit
#define g_dcdelin                        DATASTRUCT._g_dcdelin
#define parm__ipbx_fc_do_not_disturb_disable DATASTRUCT._parm__ipbx_fc_do_not_disturb_disable
#define parm__dtmf_rel_for_twist         DATASTRUCT._parm__dtmf_rel_for_twist
#define v34_resync_baud_correction       DATASTRUCT._v34_resync_baud_correction
#define sart_rx_pointer                  DATASTRUCT._sart_rx_pointer
#define stat__speech_g711_vad_flag       DATASTRUCT._stat__speech_g711_vad_flag
#define v34_resync_nxt_value             DATASTRUCT._v34_resync_nxt_value
#define ph1s_short_phase1_flag           DATASTRUCT._ph1s_short_phase1_flag
#define ph2p_anal_variance_12_table      DATASTRUCT._ph2p_anal_variance_12_table
#define v34n_parm_symbol_option          DATASTRUCT._v34n_parm_symbol_option
#define v90_shape_2_min32                DATASTRUCT._v90_shape_2_min32
#define pcm_AL_peak_value                DATASTRUCT._pcm_AL_peak_value
#define rf_fm_put_offset                 DATASTRUCT._rf_fm_put_offset
#define current_fg_state_active          DATASTRUCT._current_fg_state_active
#define uicp_number_of                   DATASTRUCT._uicp_number_of
#define stat__net_enet_snd_non_rtp       DATASTRUCT._stat__net_enet_snd_non_rtp
#define baud_rx_data_size_code           DATASTRUCT._baud_rx_data_size_code
#define orig_v8_CJ_count                 DATASTRUCT._orig_v8_CJ_count
#define v90_tx_send_MPA_frame_flag       DATASTRUCT._v90_tx_send_MPA_frame_flag
#define btrec_baud_filter_gain32         DATASTRUCT._btrec_baud_filter_gain32
#define ANSam_trace_mid_imag             DATASTRUCT._ANSam_trace_mid_imag
#define ph2_guard_tone_increment         DATASTRUCT._ph2_guard_tone_increment
#define v34h_aux_tx_flag                 DATASTRUCT._v34h_aux_tx_flag
#define V34_QN_UPDATE_SLEW               DATASTRUCT._V34_QN_UPDATE_SLEW
#define CID_count                        DATASTRUCT._CID_count
#define bgkernel_current_svalue          DATASTRUCT._bgkernel_current_svalue
#define v90_rx_forced_train_routine      DATASTRUCT._v90_rx_forced_train_routine
#define v34h_tx_P_data_frame_size        DATASTRUCT._v34h_tx_P_data_frame_size
#define uicp_feature                     DATASTRUCT._uicp_feature
#define pulse_del                        DATASTRUCT._pulse_del
#define parm__sip_session_timer          DATASTRUCT._parm__sip_session_timer
#define ph2p_anal_log_Gr_exponent        DATASTRUCT._ph2p_anal_log_Gr_exponent
#define ph2p_anal_maxrates_01_table      DATASTRUCT._ph2p_anal_maxrates_01_table
#define gxq_s                            DATASTRUCT._gxq_s
#define v34_frame_rx_MP_found_previous   DATASTRUCT._v34_frame_rx_MP_found_previous
#define equalizer_slew_resync_slow       DATASTRUCT._equalizer_slew_resync_slow
#define l_fs_real                        DATASTRUCT._l_fs_real
#define number_fg_timers                 DATASTRUCT._number_fg_timers
#define v90_tx_dil_sp_offset             DATASTRUCT._v90_tx_dil_sp_offset
#define v34_tx_pn_remote_imag            DATASTRUCT._v34_tx_pn_remote_imag
#define rf_interrupt_sample_count        DATASTRUCT._rf_interrupt_sample_count
#define empty_packet_count               DATASTRUCT._empty_packet_count
#define v34_local_echo_adjust            DATASTRUCT._v34_local_echo_adjust
#define v34_resync_state                 DATASTRUCT._v34_resync_state
#define v34h_rx_V0_m_error_count         DATASTRUCT._v34h_rx_V0_m_error_count
#define l_bpfdelout                      DATASTRUCT._l_bpfdelout
#define stat__nat_rcv_no_translation     DATASTRUCT._stat__nat_rcv_no_translation
#define saved_peak                       DATASTRUCT._saved_peak
#define v34_renego_prev_imag             DATASTRUCT._v34_renego_prev_imag
#define parm__ipbx_warm_line_dialing     DATASTRUCT._parm__ipbx_warm_line_dialing
#define ORIG_LEN_MS_INITIAL              DATASTRUCT._ORIG_LEN_MS_INITIAL
#define parm__sip_public_external_ip_address DATASTRUCT._parm__sip_public_external_ip_address
#define endtxbd_pos                      DATASTRUCT._endtxbd_pos
#define g711_rx_vad_level_min            DATASTRUCT._g711_rx_vad_level_min
#define v34n_tx_local_to_remote_maxrate  DATASTRUCT._v34n_tx_local_to_remote_maxrate
#define v34h_rx_aux_adjust_flag          DATASTRUCT._v34h_rx_aux_adjust_flag
#define prpr_y2_hi                       DATASTRUCT._prpr_y2_hi
#define pcm_bulk_delay_output_flag       DATASTRUCT._pcm_bulk_delay_output_flag
#define saved_descrambler_output         DATASTRUCT._saved_descrambler_output
#define pcm_equalizer_fb_coefs32         DATASTRUCT._pcm_equalizer_fb_coefs32
#define v92n_rx_precoder_ff_taps         DATASTRUCT._v92n_rx_precoder_ff_taps
#define l_prev_gain_err                  DATASTRUCT._l_prev_gain_err
#define stat__speech_ip_total_length     DATASTRUCT._stat__speech_ip_total_length
#define v34_rx_qn_train_coefs            DATASTRUCT._v34_rx_qn_train_coefs
#define baud_tx_delete_fourth            DATASTRUCT._baud_tx_delete_fourth
#define v90_rx_ph4_TRN2_flag             DATASTRUCT._v90_rx_ph4_TRN2_flag
#define parm__nat_block_redirection      DATASTRUCT._parm__nat_block_redirection
#define lec__rx_cng_frame_poffset        DATASTRUCT._lec__rx_cng_frame_poffset
#define lec__sum_exp                     DATASTRUCT._lec__sum_exp
#define stat__radio_operating_mode       DATASTRUCT._stat__radio_operating_mode
#define parm__ipbx_secondary_dial_tone   DATASTRUCT._parm__ipbx_secondary_dial_tone
#define parm__sdp_mpeg2_codec_dyn_pt     DATASTRUCT._parm__sdp_mpeg2_codec_dyn_pt
#define nat_icmp_dst_port                DATASTRUCT._nat_icmp_dst_port
#define parm__ipbx_call_waiting_caller_id_service DATASTRUCT._parm__ipbx_call_waiting_caller_id_service
#define SN_LT_shift                      DATASTRUCT._SN_LT_shift
#define fract_output_imag                DATASTRUCT._fract_output_imag
#define v8_tx_count                      DATASTRUCT._v8_tx_count
#define v34_pp_correlate_angle           DATASTRUCT._v34_pp_correlate_angle
#define v34_rx_qn_equalized_buffer_real  DATASTRUCT._v34_rx_qn_equalized_buffer_real
#define v21_orig_tx_passband_coefs_buffer_internal DATASTRUCT._v21_orig_tx_passband_coefs_buffer_internal
#define renegotiate_threshold            DATASTRUCT._renegotiate_threshold
#define stat__nat_snd_forwards           DATASTRUCT._stat__nat_snd_forwards
#define v34_bulk_extra_buffer_real       DATASTRUCT._v34_bulk_extra_buffer_real
#define eqout_leading_delay_imag         DATASTRUCT._eqout_leading_delay_imag
#define THD_sum_L2_magnitude             DATASTRUCT._THD_sum_L2_magnitude
#define ANSW_LEN_MS_SILENCE_DETECT       DATASTRUCT._ANSW_LEN_MS_SILENCE_DETECT
#define parm__ipbx_no_answer_forward_service DATASTRUCT._parm__ipbx_no_answer_forward_service
#define parm__nat_block_multicast        DATASTRUCT._parm__nat_block_multicast
#define parm__net_debug_server           DATASTRUCT._parm__net_debug_server
#define v34h_rx_J_super_frame_size_x2    DATASTRUCT._v34h_rx_J_super_frame_size_x2
#define fsk_previous_dif_msb             DATASTRUCT._fsk_previous_dif_msb
#define parm__slac_audio_clamp_duration  DATASTRUCT._parm__slac_audio_clamp_duration
#define ipod_msg_rx_trans_bits           DATASTRUCT._ipod_msg_rx_trans_bits
#define v34_tx_zn_remote_imag            DATASTRUCT._v34_tx_zn_remote_imag
#define gci_debounce                     DATASTRUCT._gci_debounce
#define ipod_remote_mode_prev            DATASTRUCT._ipod_remote_mode_prev
#define scramb_lsb                       DATASTRUCT._scramb_lsb
#define ph2n_tx_frequency_offset         DATASTRUCT._ph2n_tx_frequency_offset
#define cc_rx_ANAL_BEn_imag              DATASTRUCT._cc_rx_ANAL_BEn_imag
#define monitor_sample_agc_2_hi_relative_threshold DATASTRUCT._monitor_sample_agc_2_hi_relative_threshold
#define idxVec_ilbc                      DATASTRUCT._idxVec_ilbc
#define parm__ipbx_fc_call_forward_enable DATASTRUCT._parm__ipbx_fc_call_forward_enable
#define v34_equalizer_agc_exp_counter    DATASTRUCT._v34_equalizer_agc_exp_counter
#define pcm_xmit_noshape_poffset         DATASTRUCT._pcm_xmit_noshape_poffset
#define mem1_postfilt                    DATASTRUCT._mem1_postfilt
#define remote_interpolator_poffset      DATASTRUCT._remote_interpolator_poffset
#define v24_cts                          DATASTRUCT._v24_cts
#define att_gain                         DATASTRUCT._att_gain
#define stat__speech_enc_mode            DATASTRUCT._stat__speech_enc_mode
#define dev_tx_frame_index               DATASTRUCT._dev_tx_frame_index
#define l_pitTrack                       DATASTRUCT._l_pitTrack
#define pcm_rx_2k_energy                 DATASTRUCT._pcm_rx_2k_energy
#define stat__rtp_counter                DATASTRUCT._stat__rtp_counter
#define parm__ipbx_line_concurrent_voip_count DATASTRUCT._parm__ipbx_line_concurrent_voip_count
#define energy_receive40                 DATASTRUCT._energy_receive40
#define PH2P_POWR_LX_FINAL_ROUNDING      DATASTRUCT._PH2P_POWR_LX_FINAL_ROUNDING
#define parm__net_lan_pppoe_chap_enable  DATASTRUCT._parm__net_lan_pppoe_chap_enable
#define pcm_DC_offset_count              DATASTRUCT._pcm_DC_offset_count
#define ph2_guard_tone_amplitude         DATASTRUCT._ph2_guard_tone_amplitude
#define V90S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT DATASTRUCT._V90S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT
#define parm__net_isp_keep_alive_interval DATASTRUCT._parm__net_isp_keep_alive_interval
#define cp_biquad_data_buffer            DATASTRUCT._cp_biquad_data_buffer
#define parm__ipbx_call_disconnect_tone  DATASTRUCT._parm__ipbx_call_disconnect_tone
#define pcm_ec_conv_counter              DATASTRUCT._pcm_ec_conv_counter
#define parm__net_router_static          DATASTRUCT._parm__net_router_static
#define l_lpfsp_delout                   DATASTRUCT._l_lpfsp_delout
#define v34_delay_forced_timer           DATASTRUCT._v34_delay_forced_timer
#define ANSW_LEN_MS_RLSD_TURNON_DELAY    DATASTRUCT._ANSW_LEN_MS_RLSD_TURNON_DELAY
#define scal_res2                        DATASTRUCT._scal_res2
#define pcm_saved_base_group_table       DATASTRUCT._pcm_saved_base_group_table
#define pcm_playback_data                DATASTRUCT._pcm_playback_data
#define prev_phase_roll_second           DATASTRUCT._prev_phase_roll_second
#define v34_tx_decor_output              DATASTRUCT._v34_tx_decor_output
#define impedance_monitor_rx_speech_overhang DATASTRUCT._impedance_monitor_rx_speech_overhang
#define false_miss_hit_limit             DATASTRUCT._false_miss_hit_limit
#define out_vxxmod_remote                DATASTRUCT._out_vxxmod_remote
#define speech_direct_record_size        DATASTRUCT._speech_direct_record_size
#define g722_e4h_bh                      DATASTRUCT._g722_e4h_bh
#define wiznet_startup_flag              DATASTRUCT._wiznet_startup_flag
#define DIL_probing_pad_exponent         DATASTRUCT._DIL_probing_pad_exponent
#define stat__daa_disconnect_count       DATASTRUCT._stat__daa_disconnect_count
#define decode_transfer_frame            DATASTRUCT._decode_transfer_frame
#define mgcp_sdp_shadow                  DATASTRUCT._mgcp_sdp_shadow
#define ipbx_mgcp_dialing_mode           DATASTRUCT._ipbx_mgcp_dialing_mode
#define v34n_parm_ptt_attenuation_option DATASTRUCT._v34n_parm_ptt_attenuation_option
#define stat__nat_rcv_ip_tunnel          DATASTRUCT._stat__nat_rcv_ip_tunnel
#define impedance_monitor_decimated_sample_count DATASTRUCT._impedance_monitor_decimated_sample_count
#define pcm_LO_peak_value                DATASTRUCT._pcm_LO_peak_value
#define ANSam_magnitude_max32            DATASTRUCT._ANSam_magnitude_max32
#define v34_rx_yn_tilde_imag             DATASTRUCT._v34_rx_yn_tilde_imag
#define speex_enc_state                  DATASTRUCT._speex_enc_state
#define pcm_folding_minus_delay          DATASTRUCT._pcm_folding_minus_delay
#define v34_pp_correlate_log             DATASTRUCT._v34_pp_correlate_log
#define parm__handset_tx_gain            DATASTRUCT._parm__handset_tx_gain
#define g168_exc_average                 DATASTRUCT._g168_exc_average
#define parm__ipbx_distinctive_ring_id   DATASTRUCT._parm__ipbx_distinctive_ring_id
#define parm__ata_email_domain_name      DATASTRUCT._parm__ata_email_domain_name
#define phase2_timer                     DATASTRUCT._phase2_timer
#define monitor_sample_agc_2_lo_relative_threshold DATASTRUCT._monitor_sample_agc_2_lo_relative_threshold
#define g723_UseHp                       DATASTRUCT._g723_UseHp
#define prpr_y2_lo                       DATASTRUCT._prpr_y2_lo
#define v24_rxd                          DATASTRUCT._v24_rxd
#define v34_BE_modify_Gn_exp             DATASTRUCT._v34_BE_modify_Gn_exp
#define v34_rx_un_real                   DATASTRUCT._v34_rx_un_real
#define l_syn_inp                        DATASTRUCT._l_syn_inp
#define parm__ata_nonce_string           DATASTRUCT._parm__ata_nonce_string
#define parm__voip_melp_channel_packing  DATASTRUCT._parm__voip_melp_channel_packing
#define v34n_rx_MP1_body                 DATASTRUCT._v34n_rx_MP1_body
#define p18_demodulator_decrement        DATASTRUCT._p18_demodulator_decrement
#define monitor_state0_save_count        DATASTRUCT._monitor_state0_save_count
#define detect_energy_biquad_data        DATASTRUCT._detect_energy_biquad_data
#define v34n_rx_qn_coef_real             DATASTRUCT._v34n_rx_qn_coef_real
#define parm__dm_v34_mse_fallforward     DATASTRUCT._parm__dm_v34_mse_fallforward
#define parm__ipbx_fxo_cid_wait_duration DATASTRUCT._parm__ipbx_fxo_cid_wait_duration
#define g711a_plc_overlaplen             DATASTRUCT._g711a_plc_overlaplen
#define cc_tx_modulator_phase            DATASTRUCT._cc_tx_modulator_phase
#define ipod_msg_tx_vad                  DATASTRUCT._ipod_msg_tx_vad
#define ANSW_LEN_MS_NOMINAL_JM           DATASTRUCT._ANSW_LEN_MS_NOMINAL_JM
#define pcm_playback_index               DATASTRUCT._pcm_playback_index
#define shadow_ANI                       DATASTRUCT._shadow_ANI
#define ANSW_LEN_MS_MINIMUM_ANSam        DATASTRUCT._ANSW_LEN_MS_MINIMUM_ANSam
#define l_sig2                           DATASTRUCT._l_sig2
#define parm__pump_diag_count_lsw        DATASTRUCT._parm__pump_diag_count_lsw
#define parm__sip_session_timer_mode     DATASTRUCT._parm__sip_session_timer_mode
#define ph4n_tx_MP_type                  DATASTRUCT._ph4n_tx_MP_type
#define fg_status_svalue_queue           DATASTRUCT._fg_status_svalue_queue
#define lookback_array                   DATASTRUCT._lookback_array
#define nat_icmp_ip_header_size          DATASTRUCT._nat_icmp_ip_header_size
#define cc_rx_cx_imag                    DATASTRUCT._cc_rx_cx_imag
#define l_sync_bit                       DATASTRUCT._l_sync_bit
#define parm__mgcp_tos_value             DATASTRUCT._parm__mgcp_tos_value
#define speex_uwb_enc_state              DATASTRUCT._speex_uwb_enc_state
#define ph2p_anal_log_Z_buffer           DATASTRUCT._ph2p_anal_log_Z_buffer
#define nat_pkt_tcp_ptr                  DATASTRUCT._nat_pkt_tcp_ptr
#define g722_e4h_dh                      DATASTRUCT._g722_e4h_dh
#define ph2_rx_baud_counter              DATASTRUCT._ph2_rx_baud_counter
#define g711a_plc_buffer_in              DATASTRUCT._g711a_plc_buffer_in
#define parm__ipbx_call_ring_default     DATASTRUCT._parm__ipbx_call_ring_default
#define parm__mgcp_call_agent_protocol   DATASTRUCT._parm__mgcp_call_agent_protocol
#define stat__mbx_dma_state              DATASTRUCT._stat__mbx_dma_state
#define fg_event_queue                   DATASTRUCT._fg_event_queue
#define enc_lsp_old_q                    DATASTRUCT._enc_lsp_old_q
#define prev_gain_q_gain_dec             DATASTRUCT._prev_gain_q_gain_dec
#define dtmf_clamp_gain                  DATASTRUCT._dtmf_clamp_gain
#define sense_silence_lpf1_32            DATASTRUCT._sense_silence_lpf1_32
#define ph2n_rx_receive_hi_data_rate     DATASTRUCT._ph2n_rx_receive_hi_data_rate
#define pcm_saved_eye_map_table          DATASTRUCT._pcm_saved_eye_map_table
#define parm__ata_configuration_update_periodic_delay DATASTRUCT._parm__ata_configuration_update_periodic_delay
#define parm__ipbx_green_priority_table  DATASTRUCT._parm__ipbx_green_priority_table
#define ata_led_use_mask_phone           DATASTRUCT._ata_led_use_mask_phone
#define w_fs_inv                         DATASTRUCT._w_fs_inv
#define l_tilt_del                       DATASTRUCT._l_tilt_del
#define V34_QN_UPDATE_TRN2_SLOW_SLEW     DATASTRUCT._V34_QN_UPDATE_TRN2_SLOW_SLEW
#define btrec_baud_second_slew           DATASTRUCT._btrec_baud_second_slew
#define parm__vppn_device_firmware_version DATASTRUCT._parm__vppn_device_firmware_version
#define local_interpolator_poffset       DATASTRUCT._local_interpolator_poffset
#define v34_equalizer_agc_exp            DATASTRUCT._v34_equalizer_agc_exp
#define cc_rx_demodulator_decrement      DATASTRUCT._cc_rx_demodulator_decrement
#define v90_rx_eye_map                   DATASTRUCT._v90_rx_eye_map
#define parm__sdp_g726_16_codec_dyn_pt   DATASTRUCT._parm__sdp_g726_16_codec_dyn_pt
#define system_clock_previous            DATASTRUCT._system_clock_previous
#define ph2p_anal_log_P_buffer_adj       DATASTRUCT._ph2p_anal_log_P_buffer_adj
#define stat__speech_udp_checksum        DATASTRUCT._stat__speech_udp_checksum
#define v92n_rx_clock_adjust             DATASTRUCT._v92n_rx_clock_adjust
#define v34n_tx_frequency_offset         DATASTRUCT._v34n_tx_frequency_offset
#define rxi_coef                         DATASTRUCT._rxi_coef
#define lec__nlp_cng_counter             DATASTRUCT._lec__nlp_cng_counter
#define pcm_btr_preset_phase_local       DATASTRUCT._pcm_btr_preset_phase_local
#define l_ase_num                        DATASTRUCT._l_ase_num
#define tone_detector_offset             DATASTRUCT._tone_detector_offset
#define cc_rx_equalizer_poffset          DATASTRUCT._cc_rx_equalizer_poffset
#define v34_slew_sin_BE0                 DATASTRUCT._v34_slew_sin_BE0
#define v34_slew_sin_BE2                 DATASTRUCT._v34_slew_sin_BE2
#define monitor_be2_buffer               DATASTRUCT._monitor_be2_buffer
#define v92_system_ID_error              DATASTRUCT._v92_system_ID_error
#define v34n_rxtx_data_rate_option       DATASTRUCT._v34n_rxtx_data_rate_option
#define faxdet_data_sum_grl_ansam        DATASTRUCT._faxdet_data_sum_grl_ansam
#define ANSAM_MAX_SAMPLES_PLUS_1         DATASTRUCT._ANSAM_MAX_SAMPLES_PLUS_1
#define dtmf_goertzel_scale              DATASTRUCT._dtmf_goertzel_scale
#define v90_dpcm_dil_h                   DATASTRUCT._v90_dpcm_dil_h
#define ph2n_rx_receive_gain             DATASTRUCT._ph2n_rx_receive_gain
#define v90_tx_skip_TRN2d_flag           DATASTRUCT._v90_tx_skip_TRN2d_flag
#define pcm_active_RBS_slot              DATASTRUCT._pcm_active_RBS_slot
#define cc_rx_rate_reduction_counter     DATASTRUCT._cc_rx_rate_reduction_counter
#define v34f_cc_DC_detect                DATASTRUCT._v34f_cc_DC_detect
#define v90n_tx_Uinfo_ucode              DATASTRUCT._v90n_tx_Uinfo_ucode
#define parm__ipbx_fc_busy_number_redial_cancel DATASTRUCT._parm__ipbx_fc_busy_number_redial_cancel
#define impedance_monitor_tx_noise_floor_sum_counter DATASTRUCT._impedance_monitor_tx_noise_floor_sum_counter
#define dcd_diversion_threshold          DATASTRUCT._dcd_diversion_threshold
#define monitor_decimation_count         DATASTRUCT._monitor_decimation_count
#define cc_rx_interpolator_buffer_real   DATASTRUCT._cc_rx_interpolator_buffer_real
#define telephony_temp                   DATASTRUCT._telephony_temp
#define l_prev_pcof                      DATASTRUCT._l_prev_pcof
#define erroroffset                      DATASTRUCT._erroroffset
#define parm__line_tx_exponent           DATASTRUCT._parm__line_tx_exponent
#define v92n_tx_MH_information           DATASTRUCT._v92n_tx_MH_information
#define lec__alpha_maximum               DATASTRUCT._lec__alpha_maximum
#define extra_rate_reduction_buffer_real DATASTRUCT._extra_rate_reduction_buffer_real
#define V34S_PARTIAL_PHROLL_THRESHOLD    DATASTRUCT._V34S_PARTIAL_PHROLL_THRESHOLD
#define agc_1_gain                       DATASTRUCT._agc_1_gain
#define rxs_baud_rx_flag                 DATASTRUCT._rxs_baud_rx_flag
#define PH2P_ANAL_PREEQ_ENERGY_LOSS      DATASTRUCT._PH2P_ANAL_PREEQ_ENERGY_LOSS
#define detect_tone_masks_p              DATASTRUCT._detect_tone_masks_p
#define ph2p_fefo_y_coord_scale_N        DATASTRUCT._ph2p_fefo_y_coord_scale_N
#define parm__cp_rd_below_range_metric   DATASTRUCT._parm__cp_rd_below_range_metric
#define baud_rx_data                     DATASTRUCT._baud_rx_data
#define v90_rx_L_over_2_size_RBS         DATASTRUCT._v90_rx_L_over_2_size_RBS
#define scrambler32                      DATASTRUCT._scrambler32
#define pcm_ec_slew                      DATASTRUCT._pcm_ec_slew
#define ANSam_trace_real                 DATASTRUCT._ANSam_trace_real
#define parm__sdp_cn_codec_name          DATASTRUCT._parm__sdp_cn_codec_name
#define asm_encode_rtp_dtmf_tone         DATASTRUCT._asm_encode_rtp_dtmf_tone
#define parm__ipbx_block_anonymous_service DATASTRUCT._parm__ipbx_block_anonymous_service
#define ans_side                         DATASTRUCT._ans_side
#define ec_slow_slew                     DATASTRUCT._ec_slow_slew
#define parm__ata_firmware_update_enable DATASTRUCT._parm__ata_firmware_update_enable
#define old_scores                       DATASTRUCT._old_scores
#define parm__speech_dec_mbx_addr        DATASTRUCT._parm__speech_dec_mbx_addr
#define v34h_rx_g8_table                 DATASTRUCT._v34h_rx_g8_table
#define affine_perfect_real              DATASTRUCT._affine_perfect_real
#define stat__nat_snd_frag_forward       DATASTRUCT._stat__nat_snd_frag_forward
#define pcm_rx_feedback_energy           DATASTRUCT._pcm_rx_feedback_energy
#define v90_rx_dil_sp_ptr                DATASTRUCT._v90_rx_dil_sp_ptr
#define agc_2_signal_real                DATASTRUCT._agc_2_signal_real
#define pcm_disable_input_prefilter_flag DATASTRUCT._pcm_disable_input_prefilter_flag
#define ph2p_anal_variance_05_table      DATASTRUCT._ph2p_anal_variance_05_table
#define v90n_tx_reneg_16pt_option        DATASTRUCT._v90n_tx_reneg_16pt_option
#define impedance_monitor_saved_coefs    DATASTRUCT._impedance_monitor_saved_coefs
#define run_rx_baud_thread               DATASTRUCT._run_rx_baud_thread
#define dec_cur_gain                     DATASTRUCT._dec_cur_gain
#define v34_TRN2_MSE_S_value             DATASTRUCT._v34_TRN2_MSE_S_value
#define parm__tripwire_polarity_control  DATASTRUCT._parm__tripwire_polarity_control
#define saved_v34n_tx_transmit_gain      DATASTRUCT._saved_v34n_tx_transmit_gain
#define fsk_ANSam_increment              DATASTRUCT._fsk_ANSam_increment
#define PCM_LEN_8K0_PRE_GEAR_CHANGE      DATASTRUCT._PCM_LEN_8K0_PRE_GEAR_CHANGE
#define dtmf_peak_row_level              DATASTRUCT._dtmf_peak_row_level
#define parm__ipbx_fxo_security_entry_duration DATASTRUCT._parm__ipbx_fxo_security_entry_duration
#define parm__ipbx_distinctive_ring_tone_1 DATASTRUCT._parm__ipbx_distinctive_ring_tone_1
#define parm__ata_factory_name           DATASTRUCT._parm__ata_factory_name
#define parm__ipbx_distinctive_ring_tone_2 DATASTRUCT._parm__ipbx_distinctive_ring_tone_2
#define parm__ipbx_distinctive_ring_tone_3 DATASTRUCT._parm__ipbx_distinctive_ring_tone_3
#define ipod_msg_tx_vfd                  DATASTRUCT._ipod_msg_tx_vfd
#define parm__ipbx_distinctive_ring_tone_4 DATASTRUCT._parm__ipbx_distinctive_ring_tone_4
#define v92n_tx_data_rate                DATASTRUCT._v92n_tx_data_rate
#define parm__ipbx_call_forward_dial_tone DATASTRUCT._parm__ipbx_call_forward_dial_tone
#define parm__ipbx_distinctive_ring_tone_5 DATASTRUCT._parm__ipbx_distinctive_ring_tone_5
#define parm__ipbx_distinctive_ring_tone_6 DATASTRUCT._parm__ipbx_distinctive_ring_tone_6
#define parm__ipbx_distinctive_ring_tone_7 DATASTRUCT._parm__ipbx_distinctive_ring_tone_7
#define parm__ipbx_distinctive_ring_tone_8 DATASTRUCT._parm__ipbx_distinctive_ring_tone_8
#define PCM_EQUALIZER_EP_SHIFT           DATASTRUCT._PCM_EQUALIZER_EP_SHIFT
#define parm__speech_udp_source_port     DATASTRUCT._parm__speech_udp_source_port
#define g_dcdel                          DATASTRUCT._g_dcdel
#define V92_TEST_MOH_HOLDOFF             DATASTRUCT._V92_TEST_MOH_HOLDOFF
#define mem_pre                          DATASTRUCT._mem_pre
#define av2_shift                        DATASTRUCT._av2_shift
#define parm__pcm_playback_loop_size     DATASTRUCT._parm__pcm_playback_loop_size
#define parm__vppn_device_registration_id DATASTRUCT._parm__vppn_device_registration_id
#define phone_hook_switch_debounce_count DATASTRUCT._phone_hook_switch_debounce_count
#define parm__voip_fax_processing_mode   DATASTRUCT._parm__voip_fax_processing_mode
#define threshold_v17                    DATASTRUCT._threshold_v17
#define rd_criteria_duration             DATASTRUCT._rd_criteria_duration
#define save_rx_MH_indication            DATASTRUCT._save_rx_MH_indication
#define v92n_tx_max_coefs_total          DATASTRUCT._v92n_tx_max_coefs_total
#define PCM_WHITEN_MINIMAL_GAIN          DATASTRUCT._PCM_WHITEN_MINIMAL_GAIN
#define parm__net_isp_connect_on_demand_enable DATASTRUCT._parm__net_isp_connect_on_demand_enable
#define shaping_tx_eye_map               DATASTRUCT._shaping_tx_eye_map
#define impedance_monitor_tx_in_offset   DATASTRUCT._impedance_monitor_tx_in_offset
#define parm__rtp_tos_value              DATASTRUCT._parm__rtp_tos_value
#define parm__ipbx_sit1_tone             DATASTRUCT._parm__ipbx_sit1_tone
#define sonitrol_audio_clamp             DATASTRUCT._sonitrol_audio_clamp
#define stat__nat_wan_receives           DATASTRUCT._stat__nat_wan_receives
#define pcm_prefilter_fb32               DATASTRUCT._pcm_prefilter_fb32
#define v90n_tx_symbol_rate              DATASTRUCT._v90n_tx_symbol_rate
#define bit_buffer                       DATASTRUCT._bit_buffer
#define cc_rx_equalizer_data_real        DATASTRUCT._cc_rx_equalizer_data_real
#define sonitrol_remote_control_ip       DATASTRUCT._sonitrol_remote_control_ip
#define v90_tx_k_frame                   DATASTRUCT._v90_tx_k_frame
#define syn_begin                        DATASTRUCT._syn_begin
#define pcm_folding_one_over_length      DATASTRUCT._pcm_folding_one_over_length
#define parm__mgcp_call_agent_port       DATASTRUCT._parm__mgcp_call_agent_port
#define v90n_rxtx_dpcm_data_rate_option32 DATASTRUCT._v90n_rxtx_dpcm_data_rate_option32
#define threshold_v22                    DATASTRUCT._threshold_v22
#define error_imag                       DATASTRUCT._error_imag
#define g_dcdelout_hi                    DATASTRUCT._g_dcdelout_hi
#define threshold_v27                    DATASTRUCT._threshold_v27
#define threshold_v29                    DATASTRUCT._threshold_v29
#define parm__dm_v92_apcm_data_rate_mask DATASTRUCT._parm__dm_v92_apcm_data_rate_mask
#define v92_tx_send_Jp_frame_flag        DATASTRUCT._v92_tx_send_Jp_frame_flag
#define parm__speech_dec_fill_slot_size  DATASTRUCT._parm__speech_dec_fill_slot_size
#define ac97_sample_counter              DATASTRUCT._ac97_sample_counter
#define sonitrol_caller_id               DATASTRUCT._sonitrol_caller_id
#define v34_rx_qn_buffer_imag            DATASTRUCT._v34_rx_qn_buffer_imag
#define l_sigsave                        DATASTRUCT._l_sigsave
#define parm__line_rx_gain               DATASTRUCT._parm__line_rx_gain
#define v90_frame_rx_dil_body_h          DATASTRUCT._v90_frame_rx_dil_body_h
#define V34_TXI_PLL_COUNT                DATASTRUCT._V34_TXI_PLL_COUNT
#define v90_rx_ks_value                  DATASTRUCT._v90_rx_ks_value
#define parm__speech_ip_ttl_protocol     DATASTRUCT._parm__speech_ip_ttl_protocol
#define jitter_frequency                 DATASTRUCT._jitter_frequency
#define V34S_RUN_V0_M_HOLDOFF_TIME       DATASTRUCT._V34S_RUN_V0_M_HOLDOFF_TIME
#define ph2_rx_passband_offset           DATASTRUCT._ph2_rx_passband_offset
#define v34h_tx_SWP_value                DATASTRUCT._v34h_tx_SWP_value
#define g723_UsePf                       DATASTRUCT._g723_UsePf
#define PCM_PARTIAL_CONVERGENCE_THRESHOLD DATASTRUCT._PCM_PARTIAL_CONVERGENCE_THRESHOLD
#define faxparm_parm__start_state        DATASTRUCT._faxparm_parm__start_state
#define v34_rx_trellis_best_score        DATASTRUCT._v34_rx_trellis_best_score
#define or_mask                          DATASTRUCT._or_mask
#define ph2n_rx_receive_attenuation      DATASTRUCT._ph2n_rx_receive_attenuation
#define g722_enc_dethigh                 DATASTRUCT._g722_enc_dethigh
#define ph1_tx_pcm_state                 DATASTRUCT._ph1_tx_pcm_state
#define gpf_LLval                        DATASTRUCT._gpf_LLval
#define parm__g722_dtx_flag              DATASTRUCT._parm__g722_dtx_flag
#define lec__nlp_cng_offset_counter      DATASTRUCT._lec__nlp_cng_offset_counter
#define v34h_tx_m_count_4D               DATASTRUCT._v34h_tx_m_count_4D
#define reversal_timeout_init            DATASTRUCT._reversal_timeout_init
#define phone_headset_condition          DATASTRUCT._phone_headset_condition
#define asm_encodep                      DATASTRUCT._asm_encodep
#define faxparm_active__v21_holdoff_timer DATASTRUCT._faxparm_active__v21_holdoff_timer
#define ata_check_cfg                    DATASTRUCT._ata_check_cfg
#define orig_v8_CI_sent                  DATASTRUCT._orig_v8_CI_sent
#define v92n_rx_CP_body_start            DATASTRUCT._v92n_rx_CP_body_start
#define pcm_btr_type_value               DATASTRUCT._pcm_btr_type_value
#define training_mse40                   DATASTRUCT._training_mse40
#define fg_status_insert                 DATASTRUCT._fg_status_insert
#define local_gear_value                 DATASTRUCT._local_gear_value
#define baud_rx_fsk_oversample           DATASTRUCT._baud_rx_fsk_oversample
#define v34_rx_qn_save0_coef_real32      DATASTRUCT._v34_rx_qn_save0_coef_real32
#define phase_loop_imag                  DATASTRUCT._phase_loop_imag
#define lec__probe_xx_output             DATASTRUCT._lec__probe_xx_output
#define picp_gain_pointer                DATASTRUCT._picp_gain_pointer
#define v34_slew_BE0                     DATASTRUCT._v34_slew_BE0
#define train_on_data_slew               DATASTRUCT._train_on_data_slew
#define stat__nat_wan_non_ipv4           DATASTRUCT._stat__nat_wan_non_ipv4
#define v34_slew_BE2                     DATASTRUCT._v34_slew_BE2
#define v92_predicted_echo               DATASTRUCT._v92_predicted_echo
#define con_s                            DATASTRUCT._con_s
#define v34n_rx_required_gain            DATASTRUCT._v34n_rx_required_gain
#define parm__pcm_playback_loop_bufferp  DATASTRUCT._parm__pcm_playback_loop_bufferp
#define g711a_plc_pointer_out            DATASTRUCT._g711a_plc_pointer_out
#define parm__vppn_timeslot_assignment   DATASTRUCT._parm__vppn_timeslot_assignment
#define random_imag_value                DATASTRUCT._random_imag_value
#define PCM_RX_AGC2_TARGET_ADJUSTED      DATASTRUCT._PCM_RX_AGC2_TARGET_ADJUSTED
#define PH2P_ANAL_NOISE_THRESHOLD        DATASTRUCT._PH2P_ANAL_NOISE_THRESHOLD
#define parm__nat_turn_enable            DATASTRUCT._parm__nat_turn_enable
#define l_prev_sbp3                      DATASTRUCT._l_prev_sbp3
#define parm__tone_pattern               DATASTRUCT._parm__tone_pattern
#define ipbx_call_incoming               DATASTRUCT._ipbx_call_incoming
#define parm__ipbx_polarity_answer       DATASTRUCT._parm__ipbx_polarity_answer
#define forced_scrambler_msw             DATASTRUCT._forced_scrambler_msw
#define stat__daa_debounce_state         DATASTRUCT._stat__daa_debounce_state
#define ph2p_anal_log_Gr_remainder       DATASTRUCT._ph2p_anal_log_Gr_remainder
#define pcm_btr_predict_msw              DATASTRUCT._pcm_btr_predict_msw
#define dt_valid                         DATASTRUCT._dt_valid
#define stat__speech_rtp_sequence_number DATASTRUCT._stat__speech_rtp_sequence_number
#define ph2_rx_signal_detect             DATASTRUCT._ph2_rx_signal_detect
#define pcm_btr_2nd                      DATASTRUCT._pcm_btr_2nd
#define constel_decisions_table_nrm      DATASTRUCT._constel_decisions_table_nrm
#define stat__speech_silence_detect      DATASTRUCT._stat__speech_silence_detect
#define stat__oicp_current_key_bit       DATASTRUCT._stat__oicp_current_key_bit
#define cc_rx_spectrum_offset_table      DATASTRUCT._cc_rx_spectrum_offset_table
#define v90n_rx_Jd_body                  DATASTRUCT._v90n_rx_Jd_body
#define baud_tx_corrupt_packet_cnt       DATASTRUCT._baud_tx_corrupt_packet_cnt
#define bits_counter                     DATASTRUCT._bits_counter
#define pcm_btr_measurement_angle        DATASTRUCT._pcm_btr_measurement_angle
#define PH2P_ANAL_TEST_SYMBOL_RATE       DATASTRUCT._PH2P_ANAL_TEST_SYMBOL_RATE
#define pcm_rx_sign_previous             DATASTRUCT._pcm_rx_sign_previous
#define pcm_prefilter_ff                 DATASTRUCT._pcm_prefilter_ff
#define rf_sample_foreground_offset      DATASTRUCT._rf_sample_foreground_offset
#define ph2p_bg_sample_in_pointer        DATASTRUCT._ph2p_bg_sample_in_pointer
#define parm__dm_v92_mse_data_bias       DATASTRUCT._parm__dm_v92_mse_data_bias
#define g726_enc_state                   DATASTRUCT._g726_enc_state
#define lsd_recovery_substate            DATASTRUCT._lsd_recovery_substate
#define parm__ipbx_pre_ringback_tone     DATASTRUCT._parm__ipbx_pre_ringback_tone
#define ph2_tx_passband_coef_pointer     DATASTRUCT._ph2_tx_passband_coef_pointer
#define stat__caller_id_msg_len          DATASTRUCT._stat__caller_id_msg_len
#define dg_s                             DATASTRUCT._dg_s
#define v34n_parm_clock_option           DATASTRUCT._v34n_parm_clock_option
#define lec__block_update_counter        DATASTRUCT._lec__block_update_counter
#define parm__ipbx_fxo_billing_delay_duration DATASTRUCT._parm__ipbx_fxo_billing_delay_duration
#define ipod_msg_rx_chan_ID              DATASTRUCT._ipod_msg_rx_chan_ID
#define V34S_ORIG_8K0_2RT_INFO1cend_to_Jsrt DATASTRUCT._V34S_ORIG_8K0_2RT_INFO1cend_to_Jsrt
#define helper_real                      DATASTRUCT._helper_real
#define prev_scale                       DATASTRUCT._prev_scale
#define parm__ipbx_fxo_cid_clear_duration DATASTRUCT._parm__ipbx_fxo_cid_clear_duration
#define v90_rx_sample_counter            DATASTRUCT._v90_rx_sample_counter
#define v34_TRN2_agc_value               DATASTRUCT._v34_TRN2_agc_value
#define v92n_tx_E2u_extend               DATASTRUCT._v92n_tx_E2u_extend
#define dec_seed                         DATASTRUCT._dec_seed
#define second_trn_length                DATASTRUCT._second_trn_length
#define tx_passband_buffer               DATASTRUCT._tx_passband_buffer
#define pcm_probe_imag                   DATASTRUCT._pcm_probe_imag
#define g_dcdelout_lo                    DATASTRUCT._g_dcdelout_lo
#define PCM_LEN_8K0_EQC_TRN1A_3RD        DATASTRUCT._PCM_LEN_8K0_EQC_TRN1A_3RD
#define v34s_log_energy_previous         DATASTRUCT._v34s_log_energy_previous
#define cmr_notch_data                   DATASTRUCT._cmr_notch_data
#define parm__speech_device_type         DATASTRUCT._parm__speech_device_type
#define stat__nat_wan_create_failed      DATASTRUCT._stat__nat_wan_create_failed
#define stat__nat_rcv_receives           DATASTRUCT._stat__nat_rcv_receives
#define V34N_TRN2_DATA_MAXRATE_TABLE     DATASTRUCT._V34N_TRN2_DATA_MAXRATE_TABLE
#define ORIG_LEN_MS_SART_TO_SAMPLE_DWELL DATASTRUCT._ORIG_LEN_MS_SART_TO_SAMPLE_DWELL
#define picp_dtmf_tone_started           DATASTRUCT._picp_dtmf_tone_started
#define v34n_rxtx_difference_option      DATASTRUCT._v34n_rxtx_difference_option
#define saved_scrambler_msw              DATASTRUCT._saved_scrambler_msw
#define sart_tx_pointer                  DATASTRUCT._sart_tx_pointer
#define v34s_run_V0_m_error_count        DATASTRUCT._v34s_run_V0_m_error_count
#define ipod_htd_coded_speech_offset     DATASTRUCT._ipod_htd_coded_speech_offset
#define guard_tone_gain                  DATASTRUCT._guard_tone_gain
#define stat__led_ringing_mask           DATASTRUCT._stat__led_ringing_mask
#define v34_TRN2_MSE_N_stack             DATASTRUCT._v34_TRN2_MSE_N_stack
#define parm__analog_loss_count          DATASTRUCT._parm__analog_loss_count
#define parm__ipbx_message_waiting_refresh_duration DATASTRUCT._parm__ipbx_message_waiting_refresh_duration
#define parm__vpcm_maximum_power         DATASTRUCT._parm__vpcm_maximum_power
#define rd_trans2_state                  DATASTRUCT._rd_trans2_state
#define gpf_rpointer                     DATASTRUCT._gpf_rpointer
#define l_postHPF                        DATASTRUCT._l_postHPF
#define parm__ipbx_call_waiting_tone_1   DATASTRUCT._parm__ipbx_call_waiting_tone_1
#define parm__nat_timeout_triggered      DATASTRUCT._parm__nat_timeout_triggered
#define parm__speech_rtp_cng_period      DATASTRUCT._parm__speech_rtp_cng_period
#define parm__ipbx_call_waiting_tone_2   DATASTRUCT._parm__ipbx_call_waiting_tone_2
#define v34_local_echo_coefs             DATASTRUCT._v34_local_echo_coefs
#define parm__ipbx_call_waiting_tone_3   DATASTRUCT._parm__ipbx_call_waiting_tone_3
#define parm__ipbx_call_waiting_tone_4   DATASTRUCT._parm__ipbx_call_waiting_tone_4
#define uicp_function                    DATASTRUCT._uicp_function
#define parm__ipbx_call_waiting_tone_5   DATASTRUCT._parm__ipbx_call_waiting_tone_5
#define parm__ipbx_call_waiting_tone_6   DATASTRUCT._parm__ipbx_call_waiting_tone_6
#define ph2n_probing_preemph             DATASTRUCT._ph2n_probing_preemph
#define parm__sip_bye_authentication     DATASTRUCT._parm__sip_bye_authentication
#define parm__ipbx_call_waiting_tone_7   DATASTRUCT._parm__ipbx_call_waiting_tone_7
#define parm__ipbx_call_waiting_tone_8   DATASTRUCT._parm__ipbx_call_waiting_tone_8
#define DCD_HYSTERESIS                   DATASTRUCT._DCD_HYSTERESIS
#define ethernet_SPP_rx_message          DATASTRUCT._ethernet_SPP_rx_message
#define demod_half_imag                  DATASTRUCT._demod_half_imag
#define ipod_msg_tx_payload_size         DATASTRUCT._ipod_msg_tx_payload_size
#define v34_BE_pos_power_32              DATASTRUCT._v34_BE_pos_power_32
#define v92n_tx_INFO1a_body              DATASTRUCT._v92n_tx_INFO1a_body
#define vppn_encode_packet               DATASTRUCT._vppn_encode_packet
#define ph2_ac_sample_bit_pattern        DATASTRUCT._ph2_ac_sample_bit_pattern
#define saved_parm__pump_transmit_level  DATASTRUCT._saved_parm__pump_transmit_level
#define DIL_calculation_pad_exponent     DATASTRUCT._DIL_calculation_pad_exponent
#define PH2P_ANAL_TEST_CARRIER_FREQUENCY DATASTRUCT._PH2P_ANAL_TEST_CARRIER_FREQUENCY
#define v_flag                           DATASTRUCT._v_flag
#define train_on_data_32_slew            DATASTRUCT._train_on_data_32_slew
#define pcm_fb_equalizer_size            DATASTRUCT._pcm_fb_equalizer_size
#define cc_rx_AC                         DATASTRUCT._cc_rx_AC
#define sigdet_save32                    DATASTRUCT._sigdet_save32
#define interrupt_sample_count           DATASTRUCT._interrupt_sample_count
#define ph2n_rx_receive_agc2_level       DATASTRUCT._ph2n_rx_receive_agc2_level
#define v92n_tx_CPd_modulus              DATASTRUCT._v92n_tx_CPd_modulus
#define sonitrol_v34_rx_buffer           DATASTRUCT._sonitrol_v34_rx_buffer
#define asm_encode_control_mask          DATASTRUCT._asm_encode_control_mask
#define DIL_probing_symbol_counter       DATASTRUCT._DIL_probing_symbol_counter
#define input_sample_energy32            DATASTRUCT._input_sample_energy32
#define v34n_rx_clock_mode               DATASTRUCT._v34n_rx_clock_mode
#define v24_dcd                          DATASTRUCT._v24_dcd
#define pcm_xmit_noshape_buffer          DATASTRUCT._pcm_xmit_noshape_buffer
#define PMOVLAY                          DATASTRUCT._PMOVLAY
#define mark_idle_rx_active              DATASTRUCT._mark_idle_rx_active
#define lsd_recovery_signal_state        DATASTRUCT._lsd_recovery_signal_state
#define vppn_device_firmware_length      DATASTRUCT._vppn_device_firmware_length
#define rx_measurment_buffer_1           DATASTRUCT._rx_measurment_buffer_1
#define stat__nat_rcv_non_ipv4           DATASTRUCT._stat__nat_rcv_non_ipv4
#define ph4n_tx_auxiliary_option         DATASTRUCT._ph4n_tx_auxiliary_option
#define parm__ata_user_password          DATASTRUCT._parm__ata_user_password
#define ds_gain                          DATASTRUCT._ds_gain
#define v90_tx_dil_ucode_offset          DATASTRUCT._v90_tx_dil_ucode_offset
#define ipod_iface_rx_bufp               DATASTRUCT._ipod_iface_rx_bufp
#define cc_rx_PP_BEn_save_energy_log     DATASTRUCT._cc_rx_PP_BEn_save_energy_log
#define v90_frame_tx_dil_body_sp         DATASTRUCT._v90_frame_tx_dil_body_sp
#define g723_UseVx                       DATASTRUCT._g723_UseVx
#define v92n_tx_reneg_8pt_option         DATASTRUCT._v92n_tx_reneg_8pt_option
#define orig_v8_allow_very_short_ANSam   DATASTRUCT._orig_v8_allow_very_short_ANSam
#define v34n_rx_hi_data_rate_option      DATASTRUCT._v34n_rx_hi_data_rate_option
#define pcm_16K_input_sample             DATASTRUCT._pcm_16K_input_sample
#define loopback_poffset                 DATASTRUCT._loopback_poffset
#define g726_dec_coding                  DATASTRUCT._g726_dec_coding
#define stat__nat_wan_pptp               DATASTRUCT._stat__nat_wan_pptp
#define baud_rx_cnt                      DATASTRUCT._baud_rx_cnt
#define lec__td_hold_1st_cnt             DATASTRUCT._lec__td_hold_1st_cnt
#define tx_packet_count                  DATASTRUCT._tx_packet_count
#define THD_sum_L2_S_over_N              DATASTRUCT._THD_sum_L2_S_over_N
#define v34n_tx_MP0_body                 DATASTRUCT._v34n_tx_MP0_body
#define v34_rx_qn_save0_coefs            DATASTRUCT._v34_rx_qn_save0_coefs
#define v90_rx_R_detect_slot             DATASTRUCT._v90_rx_R_detect_slot
#define sonitrol_panel_group_desc        DATASTRUCT._sonitrol_panel_group_desc
#define gci_control                      DATASTRUCT._gci_control
#define PCM_TEST_PAD_SIMULATION_SELECT   DATASTRUCT._PCM_TEST_PAD_SIMULATION_SELECT
#define g_hpspeech                       DATASTRUCT._g_hpspeech
#define PCM_EC_INPUT_PRE_SHIFT           DATASTRUCT._PCM_EC_INPUT_PRE_SHIFT
#define tx_dtmf_early_count              DATASTRUCT._tx_dtmf_early_count
#define v90_frame_tx_dil_body_tp         DATASTRUCT._v90_frame_tx_dil_body_tp
#define parm__ipbx_disturb_accept_service DATASTRUCT._parm__ipbx_disturb_accept_service
#define v90n_tx_training_attenuation     DATASTRUCT._v90n_tx_training_attenuation
#define cp_threshold                     DATASTRUCT._cp_threshold
#define bitval                           DATASTRUCT._bitval
#define special_match_msw                DATASTRUCT._special_match_msw
#define v34n_parm_CME_option             DATASTRUCT._v34n_parm_CME_option
#define parm__ipbx_call_waiting_tone_default DATASTRUCT._parm__ipbx_call_waiting_tone_default
#define p18_data_buffer_imag             DATASTRUCT._p18_data_buffer_imag
#define v92h_rx_Q_table                  DATASTRUCT._v92h_rx_Q_table
#define pcm_8K0_equalized_ep             DATASTRUCT._pcm_8K0_equalized_ep
#define sonitrol_audio_ip_timeout        DATASTRUCT._sonitrol_audio_ip_timeout
#define parm__ata_user_email             DATASTRUCT._parm__ata_user_email
#define pcm_8K0_equalized_eq             DATASTRUCT._pcm_8K0_equalized_eq
#define parm__nat_ipsec_enable           DATASTRUCT._parm__nat_ipsec_enable
#define pcm_8K0_equalized_er             DATASTRUCT._pcm_8K0_equalized_er
#define v34h_tx_pointer                  DATASTRUCT._v34h_tx_pointer
#define pcm_btr_gain_power               DATASTRUCT._pcm_btr_gain_power
#define PCM_WHITEN_MAXIMAL_GAIN          DATASTRUCT._PCM_WHITEN_MAXIMAL_GAIN
#define ph2_ac_sample_offset             DATASTRUCT._ph2_ac_sample_offset
#define cc_rx_DC                         DATASTRUCT._cc_rx_DC
#define V34_RESYNC_FILL_LENGTH           DATASTRUCT._V34_RESYNC_FILL_LENGTH
#define stat__net_current_gateway_address DATASTRUCT._stat__net_current_gateway_address
#define sart_tx_underflow                DATASTRUCT._sart_tx_underflow
#define parm__net_router_modem_script    DATASTRUCT._parm__net_router_modem_script
#define g722_e4h_sg                      DATASTRUCT._g722_e4h_sg
#define ph2p_powr_powr_cx_buffer         DATASTRUCT._ph2p_powr_powr_cx_buffer
#define pcm_8K0_equalized_fb             DATASTRUCT._pcm_8K0_equalized_fb
#define g722_e4h_sh                      DATASTRUCT._g722_e4h_sh
#define pcm_8K0_equalized_ff             DATASTRUCT._pcm_8K0_equalized_ff
#define parm__nat_hairpin_enable         DATASTRUCT._parm__nat_hairpin_enable
#define PH2P_POWR_L2_FINAL_TUNE          DATASTRUCT._PH2P_POWR_L2_FINAL_TUNE
#define n_pwr_shift                      DATASTRUCT._n_pwr_shift
#define stat__uicp_parse_state           DATASTRUCT._stat__uicp_parse_state
#define parm__sip_allow_incoming_registration DATASTRUCT._parm__sip_allow_incoming_registration
#define pushed_demod_complex             DATASTRUCT._pushed_demod_complex
#define rx_wr_index                      DATASTRUCT._rx_wr_index
#define stat__vppn_master_firmware_version DATASTRUCT._stat__vppn_master_firmware_version
#define uicp_list                        DATASTRUCT._uicp_list
#define V90S_APCM_8K0_1RT_Jsrt_to_S_SNdet DATASTRUCT._V90S_APCM_8K0_1RT_Jsrt_to_S_SNdet
#define angle_1st_data_correction        DATASTRUCT._angle_1st_data_correction
#define speex_sb_enc_state               DATASTRUCT._speex_sb_enc_state
#define pcm_playback_bufferp             DATASTRUCT._pcm_playback_bufferp
#define v34_resync_train_routine         DATASTRUCT._v34_resync_train_routine
#define parm__ata_local_update_enable    DATASTRUCT._parm__ata_local_update_enable
#define v34n_rx_preeq_Whi                DATASTRUCT._v34n_rx_preeq_Whi
#define v92_MH_disconnect_flag           DATASTRUCT._v92_MH_disconnect_flag
#define vppn_hook_debounce               DATASTRUCT._vppn_hook_debounce
#define stat__nat_rcv_translated         DATASTRUCT._stat__nat_rcv_translated
#define ph2_tx_data_size_1               DATASTRUCT._ph2_tx_data_size_1
#define parm__tripwire_captured          DATASTRUCT._parm__tripwire_captured
#define stat__ipbx_hook_state            DATASTRUCT._stat__ipbx_hook_state
#define v34_rx_qn_save0_coef_imag32      DATASTRUCT._v34_rx_qn_save0_coef_imag32
#define parm__codec_disconnect_tone_1_enable DATASTRUCT._parm__codec_disconnect_tone_1_enable
#define rx_interpolator_poffset          DATASTRUCT._rx_interpolator_poffset
#define stat__nat_wan_frag_failed        DATASTRUCT._stat__nat_wan_frag_failed
#define pcm_ec_counter                   DATASTRUCT._pcm_ec_counter
#define V92_TEST_MOH_SILENCE_LENGTH      DATASTRUCT._V92_TEST_MOH_SILENCE_LENGTH
#define baud_rx_bit_cnt                  DATASTRUCT._baud_rx_bit_cnt
#define stat__in_conference              DATASTRUCT._stat__in_conference
#define v92n_parm_rx_reneg_8pt_option    DATASTRUCT._v92n_parm_rx_reneg_8pt_option
#define v34_tx_un_real                   DATASTRUCT._v34_tx_un_real
#define v34n_rx_lo_carrier_option        DATASTRUCT._v34n_rx_lo_carrier_option
#define pcm_folding_value1               DATASTRUCT._pcm_folding_value1
#define parm__sip_allow_incoming_subscription DATASTRUCT._parm__sip_allow_incoming_subscription
#define pcm_folding_value2               DATASTRUCT._pcm_folding_value2
#define parm__net_debug_level_omc        DATASTRUCT._parm__net_debug_level_omc
#define parm__audio_agc_enable           DATASTRUCT._parm__audio_agc_enable
#define melp_par                         DATASTRUCT._melp_par
#define v92_MH_response_end_flag         DATASTRUCT._v92_MH_response_end_flag
#define PCM_LEN_8K0_EQC_TRN1A_FILL       DATASTRUCT._PCM_LEN_8K0_EQC_TRN1A_FILL
#define btrec_phdet_error_lpf32          DATASTRUCT._btrec_phdet_error_lpf32
#define rd_prev_rings                    DATASTRUCT._rd_prev_rings
#define v34h_tx_Z_m                      DATASTRUCT._v34h_tx_Z_m
#define vppn_device_firmware_offset      DATASTRUCT._vppn_device_firmware_offset
#define plookback                        DATASTRUCT._plookback
#define parm__ipbx_pause_wait_duration   DATASTRUCT._parm__ipbx_pause_wait_duration
#define rsdp                             DATASTRUCT._rsdp
#define train_on_data_coordinate         DATASTRUCT._train_on_data_coordinate
#define parm__nat_pptp_enable            DATASTRUCT._parm__nat_pptp_enable
#define picp_access                      DATASTRUCT._picp_access
#define parm__rtp_public_external_ip_address DATASTRUCT._parm__rtp_public_external_ip_address
#define lambdaD_shift                    DATASTRUCT._lambdaD_shift
#define ipod_htd_voice_semaphore         DATASTRUCT._ipod_htd_voice_semaphore
#define local_interpolator_buffer_imag   DATASTRUCT._local_interpolator_buffer_imag
#define faxmon_modulation_state          DATASTRUCT._faxmon_modulation_state
#define impedance_monitor_tx_noise_floors DATASTRUCT._impedance_monitor_tx_noise_floors
#define btrec_baud_first_slew            DATASTRUCT._btrec_baud_first_slew
#define v8_rx_sync_code                  DATASTRUCT._v8_rx_sync_code
#define v92_tx_send_Sd_align_flag        DATASTRUCT._v92_tx_send_Sd_align_flag
#define impedance_monitor_tx_in          DATASTRUCT._impedance_monitor_tx_in
#define V92_RuN_REMAIN                   DATASTRUCT._V92_RuN_REMAIN
#define ph4n_rx_trained_shaping          DATASTRUCT._ph4n_rx_trained_shaping
#define pcm_xmit_deshape_buffer          DATASTRUCT._pcm_xmit_deshape_buffer
#define DIL_probing_2nd_repetition_table DATASTRUCT._DIL_probing_2nd_repetition_table
#define parm__rx_type                    DATASTRUCT._parm__rx_type
#define ph2_tx_rate_conv_9K6_8K0_buffer  DATASTRUCT._ph2_tx_rate_conv_9K6_8K0_buffer
#define stat__mgcp_local_contact_port    DATASTRUCT._stat__mgcp_local_contact_port
#define v34s_special_local_train_enable  DATASTRUCT._v34s_special_local_train_enable
#define parm__net_debug_level_ooma       DATASTRUCT._parm__net_debug_level_ooma
#define parm__dtmf_col_no_tone_level     DATASTRUCT._parm__dtmf_col_no_tone_level
#define parm__fxpmp_prefax               DATASTRUCT._parm__fxpmp_prefax
#define dpbx_key_mask                    DATASTRUCT._dpbx_key_mask
#define pcm_TRN2_MSE_flag                DATASTRUCT._pcm_TRN2_MSE_flag
#define cc_rx_S_repetition_counter       DATASTRUCT._cc_rx_S_repetition_counter
#define smoothedspect                    DATASTRUCT._smoothedspect
#define parm__codec_disconnect_silence_threshold DATASTRUCT._parm__codec_disconnect_silence_threshold
#define ph2p_anal_variance_11_table      DATASTRUCT._ph2p_anal_variance_11_table
#define v90_shape_1_min32                DATASTRUCT._v90_shape_1_min32
#define v90_rx_k_input_offset            DATASTRUCT._v90_rx_k_input_offset
#define asm_decode_sample_unpack_shift_cnt DATASTRUCT._asm_decode_sample_unpack_shift_cnt
#define ANSam_trace_magphase_lpf_real    DATASTRUCT._ANSam_trace_magphase_lpf_real
#define v90_tx_eye_map                   DATASTRUCT._v90_tx_eye_map
#define vppn_device_command_send_wait    DATASTRUCT._vppn_device_command_send_wait
#define fsk_bitstream_msb                DATASTRUCT._fsk_bitstream_msb
#define DELTA_SLEW_RATE                  DATASTRUCT._DELTA_SLEW_RATE
#define v34_slew_cos_BE0                 DATASTRUCT._v34_slew_cos_BE0
#define orig_v8_CI_count                 DATASTRUCT._orig_v8_CI_count
#define lec__error_poffset               DATASTRUCT._lec__error_poffset
#define stat__nat_rcv_ip_fragment        DATASTRUCT._stat__nat_rcv_ip_fragment
#define v34_slew_cos_BE2                 DATASTRUCT._v34_slew_cos_BE2
#define stat__ata_update_cfgfile_url     DATASTRUCT._stat__ata_update_cfgfile_url
#define v34n_parm_cc_asymmetric_option   DATASTRUCT._v34n_parm_cc_asymmetric_option
#define l_prev_fsmag                     DATASTRUCT._l_prev_fsmag
#define demodulator_decrement            DATASTRUCT._demodulator_decrement
#define pcm_rx_exponent                  DATASTRUCT._pcm_rx_exponent
#define cc_rx_equalizer_coef_imag        DATASTRUCT._cc_rx_equalizer_coef_imag
#define saved_Lx_spectrum_power_pointer32 DATASTRUCT._saved_Lx_spectrum_power_pointer32
#define v34h_rx_P_data_frame_size        DATASTRUCT._v34h_rx_P_data_frame_size
#define parm__dtmf_row_2nd_harm          DATASTRUCT._parm__dtmf_row_2nd_harm
#define g_msvq_bits                      DATASTRUCT._g_msvq_bits
#define ph2p_anal_maxrates_00_table      DATASTRUCT._ph2p_anal_maxrates_00_table
#define cc_counter_not_flags             DATASTRUCT._cc_counter_not_flags
#define error_complex                    DATASTRUCT._error_complex
#define v92h_rx_R0_sign                  DATASTRUCT._v92h_rx_R0_sign
#define parm__dtmf_high_tone_level       DATASTRUCT._parm__dtmf_high_tone_level
#define ph4n_rx_trained_qn_coef_real     DATASTRUCT._ph4n_rx_trained_qn_coef_real
#define ORIG_LEN_MS_Te                   DATASTRUCT._ORIG_LEN_MS_Te
#define ANSam_trace_count_2100_real      DATASTRUCT._ANSam_trace_count_2100_real
#define v34_TRN2_MSE_report_rate         DATASTRUCT._v34_TRN2_MSE_report_rate
#define parm__codec_disconnect_reversals_originate DATASTRUCT._parm__codec_disconnect_reversals_originate
#define edge_m1200_real32                DATASTRUCT._edge_m1200_real32
#define equalized_yn_real                DATASTRUCT._equalized_yn_real
#define stat__rx_level_dbm               DATASTRUCT._stat__rx_level_dbm
#define V34S_RUN_8K0_STATISTICS_TIME     DATASTRUCT._V34S_RUN_8K0_STATISTICS_TIME
#define l_bpfdelin                       DATASTRUCT._l_bpfdelin
#define asm_encode_mbx                   DATASTRUCT._asm_encode_mbx
#define demod_lagging_half_imag          DATASTRUCT._demod_lagging_half_imag
#define parm__net_router_circuit_default_dial_wait DATASTRUCT._parm__net_router_circuit_default_dial_wait
#define parm__net_lan_pptp_enable        DATASTRUCT._parm__net_lan_pptp_enable
#define lec__td_error_offset             DATASTRUCT._lec__td_error_offset
#define parm__sart_hdlc_crc32_rx_en      DATASTRUCT._parm__sart_hdlc_crc32_rx_en
#define bg_task_jmp_buf                  DATASTRUCT._bg_task_jmp_buf
#define parm__ipbx_led_line_in_use       DATASTRUCT._parm__ipbx_led_line_in_use
#define asm_within_dtmf_min              DATASTRUCT._asm_within_dtmf_min
#define g726_dec_parm                    DATASTRUCT._g726_dec_parm
#define v34n_rx_preeq_Wlo                DATASTRUCT._v34n_rx_preeq_Wlo
#define v34_tx_local_use_nonlinear       DATASTRUCT._v34_tx_local_use_nonlinear
#define cp_output                        DATASTRUCT._cp_output
#define sonitrol_ethernet_master_timer   DATASTRUCT._sonitrol_ethernet_master_timer
#define v92n_tx_CPd_prefilt              DATASTRUCT._v92n_tx_CPd_prefilt
#define fsk_run_decision                 DATASTRUCT._fsk_run_decision
#define v34h_tx_K_number_shell_bits      DATASTRUCT._v34h_tx_K_number_shell_bits
#define V34_BE_SLEW_FAST                 DATASTRUCT._V34_BE_SLEW_FAST
#define saved_apcm_receive_level         DATASTRUCT._saved_apcm_receive_level
#define parm__net_router_modem_baudrate  DATASTRUCT._parm__net_router_modem_baudrate
#define comn_v8_from_on_hold             DATASTRUCT._comn_v8_from_on_hold
#define orig_v8_found_JM                 DATASTRUCT._orig_v8_found_JM
#define THD_sum_L2_S_power               DATASTRUCT._THD_sum_L2_S_power
#define demodulator_phase                DATASTRUCT._demodulator_phase
#define ph2p_powr_rx_clear_length        DATASTRUCT._ph2p_powr_rx_clear_length
#define parm__dm_v34_ptt_restriction_mask DATASTRUCT._parm__dm_v34_ptt_restriction_mask
#define fax_rlsd_length                  DATASTRUCT._fax_rlsd_length
#define parm__report_timer_tick          DATASTRUCT._parm__report_timer_tick
#define lec__error_buffer                DATASTRUCT._lec__error_buffer
#define parm__speech_dec_mode            DATASTRUCT._parm__speech_dec_mode
#define parm__ipbx_ringback_tone         DATASTRUCT._parm__ipbx_ringback_tone
#define pcm_disable_input_pstfilter_flag DATASTRUCT._pcm_disable_input_pstfilter_flag
#define v34h_tx_N_bits_per_data_frame    DATASTRUCT._v34h_tx_N_bits_per_data_frame
#define lec__delay_poffset               DATASTRUCT._lec__delay_poffset
#define cc_rx_S_last_compare_ratio       DATASTRUCT._cc_rx_S_last_compare_ratio
#define v34n_rx_preeq_Wme                DATASTRUCT._v34n_rx_preeq_Wme
#define orig_v8_found_ANS                DATASTRUCT._orig_v8_found_ANS
#define l_classStat                      DATASTRUCT._l_classStat
#define sumAcf                           DATASTRUCT._sumAcf
#define v34_rx_pn_imag                   DATASTRUCT._v34_rx_pn_imag
#define demod_complex                    DATASTRUCT._demod_complex
#define PH2P_ANAL_THD_THRESHOLD          DATASTRUCT._PH2P_ANAL_THD_THRESHOLD
#define parm__mgcp_max_forwards          DATASTRUCT._parm__mgcp_max_forwards
#define DIL_calculation_pad_target_log   DATASTRUCT._DIL_calculation_pad_target_log
#define v90_tx_send_Jd_frame_flag        DATASTRUCT._v90_tx_send_Jd_frame_flag
#define rx_lpf_buffer                    DATASTRUCT._rx_lpf_buffer
#define g_voicedCnt                      DATASTRUCT._g_voicedCnt
#define v34_MSE_value_energy             DATASTRUCT._v34_MSE_value_energy
#define predicted_rx_xn_B1_Q_n_imag      DATASTRUCT._predicted_rx_xn_B1_Q_n_imag
#define lec__holding_buffer              DATASTRUCT._lec__holding_buffer
#define parm__dm_v34_test_options_mask   DATASTRUCT._parm__dm_v34_test_options_mask
#define cc_tx_passband_buffer            DATASTRUCT._cc_tx_passband_buffer
#define stat__phone_hook_switch_state    DATASTRUCT._stat__phone_hook_switch_state
#define parm__cp_rd_min_detect_duration  DATASTRUCT._parm__cp_rd_min_detect_duration
#define V92_EVENT__XXA_RECEIVED          DATASTRUCT._V92_EVENT__XXA_RECEIVED
#define v34s_conditional_frequency_offset DATASTRUCT._v34s_conditional_frequency_offset
#define previous_eq_error                DATASTRUCT._previous_eq_error
#define picp_dial_string                 DATASTRUCT._picp_dial_string
#define fract_input_imag                 DATASTRUCT._fract_input_imag
#define v90_apcm_dil_first               DATASTRUCT._v90_apcm_dil_first
#define parm__nat_timeout_udp            DATASTRUCT._parm__nat_timeout_udp
#define pcm_error_lpf_poffset            DATASTRUCT._pcm_error_lpf_poffset
#define lec__tx_suppressor_gain          DATASTRUCT._lec__tx_suppressor_gain
#define fsk_baud_rx_data                 DATASTRUCT._fsk_baud_rx_data
#define ANSam_trace_min_real             DATASTRUCT._ANSam_trace_min_real
#define pcm_agc_2_delta_log              DATASTRUCT._pcm_agc_2_delta_log
#define missed_sample_counter            DATASTRUCT._missed_sample_counter
#define parm__tone_detectors_num_tones   DATASTRUCT._parm__tone_detectors_num_tones
#define rx_lpf_buffer_real               DATASTRUCT._rx_lpf_buffer_real
#define pcm_pstfilter_fb32               DATASTRUCT._pcm_pstfilter_fb32
#define echo_canceller_debug_display_offset DATASTRUCT._echo_canceller_debug_display_offset
#define parm__slac_initialization_commands DATASTRUCT._parm__slac_initialization_commands
#define ipod_msg_tx_coder                DATASTRUCT._ipod_msg_tx_coder
#define V90_RX_1K3_ENERGY_THRESHOLD      DATASTRUCT._V90_RX_1K3_ENERGY_THRESHOLD
#define faxdet_data_cntr                 DATASTRUCT._faxdet_data_cntr
#define speech_sync_enc_delay_cntr       DATASTRUCT._speech_sync_enc_delay_cntr
#define prev_cng_flag                    DATASTRUCT._prev_cng_flag
#define det_exponent                     DATASTRUCT._det_exponent
#define v90_rx_dil_lsp                   DATASTRUCT._v90_rx_dil_lsp
#define cp_decimate                      DATASTRUCT._cp_decimate
#define decode_frame_pointer             DATASTRUCT._decode_frame_pointer
#define rd_trans2_timer                  DATASTRUCT._rd_trans2_timer
#define parm__ipbx_do_not_disturb_service DATASTRUCT._parm__ipbx_do_not_disturb_service
#define v34_temp_pre_emph_adjust_table   DATASTRUCT._v34_temp_pre_emph_adjust_table
#define parm__ipbx_forward_last_call_service DATASTRUCT._parm__ipbx_forward_last_call_service
#define v34f_eqc_sd_DC_imag              DATASTRUCT._v34f_eqc_sd_DC_imag
#define PCM_EQUALIZER_FB_SHIFT           DATASTRUCT._PCM_EQUALIZER_FB_SHIFT
#define ph1_x_law_round_mask             DATASTRUCT._ph1_x_law_round_mask
#define parm__sip_nat_keep_alive_enable  DATASTRUCT._parm__sip_nat_keep_alive_enable
#define current_video_rtp_stream         DATASTRUCT._current_video_rtp_stream
#define v34_rx_yn_error_real_32          DATASTRUCT._v34_rx_yn_error_real_32
#define active_detect_tones              DATASTRUCT._active_detect_tones
#define faxparm_active__CED_generate     DATASTRUCT._faxparm_active__CED_generate
#define envdel                           DATASTRUCT._envdel
#define parm__ipbx_call_hold_disconnect_tone DATASTRUCT._parm__ipbx_call_hold_disconnect_tone
#define stat__net_dhcp_server_ip_addess  DATASTRUCT._stat__net_dhcp_server_ip_addess
#define random_real_value                DATASTRUCT._random_real_value
#define system_clock_remainder           DATASTRUCT._system_clock_remainder
#define lec__tec_data                    DATASTRUCT._lec__tec_data
#define saved_scrambler_shift            DATASTRUCT._saved_scrambler_shift
#define v90n_tx_receive_shaping_lookahead DATASTRUCT._v90n_tx_receive_shaping_lookahead
#define v34_pnt12_MSE_stack              DATASTRUCT._v34_pnt12_MSE_stack
#define phroll_remote_energy32           DATASTRUCT._phroll_remote_energy32
#define jitter_2nd_order_slew            DATASTRUCT._jitter_2nd_order_slew
#define v34n_tx_use_shaping              DATASTRUCT._v34n_tx_use_shaping
#define full_convergence_threshold       DATASTRUCT._full_convergence_threshold
#define scrambler_bits_per_baud          DATASTRUCT._scrambler_bits_per_baud
#define parm__sip_incoming_auth_realm    DATASTRUCT._parm__sip_incoming_auth_realm
#define v90_rx_dil_ltp                   DATASTRUCT._v90_rx_dil_ltp
#define common_local_return              DATASTRUCT._common_local_return
#define tone_pattern_ms                  DATASTRUCT._tone_pattern_ms
#define parm__record_enable              DATASTRUCT._parm__record_enable
#define parm__ipbx_led_ringing_or_waiting DATASTRUCT._parm__ipbx_led_ringing_or_waiting
#define pushed_demod_real                DATASTRUCT._pushed_demod_real
#define current_input_real               DATASTRUCT._current_input_real
#define parm__sdp_jpeg_codec_name        DATASTRUCT._parm__sdp_jpeg_codec_name
#define dtmf_clamp_state                 DATASTRUCT._dtmf_clamp_state
#define v17_diagnostics_mse_limit        DATASTRUCT._v17_diagnostics_mse_limit
#define legacy_comm_data                 DATASTRUCT._legacy_comm_data
#define v34_tx_Y0_m                      DATASTRUCT._v34_tx_Y0_m
#define sonitrol_hotplug_state           DATASTRUCT._sonitrol_hotplug_state
#define stat__ipod_allowed_mode_mask     DATASTRUCT._stat__ipod_allowed_mode_mask
#define asm_lb_packet_buffer             DATASTRUCT._asm_lb_packet_buffer
#define parm__ipbx_call_forward_dial_string DATASTRUCT._parm__ipbx_call_forward_dial_string
#define angle_1st_data_difference        DATASTRUCT._angle_1st_data_difference
#define quant_par600                     DATASTRUCT._quant_par600
#define v34n_tx_CME_option               DATASTRUCT._v34n_tx_CME_option
#define disp_del                         DATASTRUCT._disp_del
#define parm__rtp_port_maximum           DATASTRUCT._parm__rtp_port_maximum
#define change_detect_tones              DATASTRUCT._change_detect_tones
#define parm__ipbx_block_last_call_service DATASTRUCT._parm__ipbx_block_last_call_service
#define parm__nat_port_forward           DATASTRUCT._parm__nat_port_forward
#define asm_encode_savep                 DATASTRUCT._asm_encode_savep
#define cc_rx_Nk_energy_log              DATASTRUCT._cc_rx_Nk_energy_log
#define parm__speech_asm_lb              DATASTRUCT._parm__speech_asm_lb
#define baud_tx_data_size_code           DATASTRUCT._baud_tx_data_size_code
#define ph2_rx_dcd_level                 DATASTRUCT._ph2_rx_dcd_level
#define parm__speech_rtp_cn_payload_type DATASTRUCT._parm__speech_rtp_cn_payload_type
#define g726_in_buffer                   DATASTRUCT._g726_in_buffer
#define flag_chang                       DATASTRUCT._flag_chang
#define V34_BE0_SLEW_FAST                DATASTRUCT._V34_BE0_SLEW_FAST
#define pcm_bulk_delay_input_last        DATASTRUCT._pcm_bulk_delay_input_last
#define parm__voip_g723_high_rate_enable DATASTRUCT._parm__voip_g723_high_rate_enable
#define ph2_tx_Lx_offset                 DATASTRUCT._ph2_tx_Lx_offset
#define convert_log__gain                DATASTRUCT._convert_log__gain
#define lec__nlp_sid_enable              DATASTRUCT._lec__nlp_sid_enable
#define parm__sart_binary_prev_data      DATASTRUCT._parm__sart_binary_prev_data
#define v92_rx_decoder_ep_coefs          DATASTRUCT._v92_rx_decoder_ep_coefs
#define v34_delay_forced_routine         DATASTRUCT._v34_delay_forced_routine
#define dpbx_led_pattern_queue           DATASTRUCT._dpbx_led_pattern_queue
#define parm__ipbx_reconnect_debounce    DATASTRUCT._parm__ipbx_reconnect_debounce
#define v34h_rx_AMP_value                DATASTRUCT._v34h_rx_AMP_value
#define stat__vppn_ringing_on            DATASTRUCT._stat__vppn_ringing_on
#define speech_direct_record_data        DATASTRUCT._speech_direct_record_data
#define phone_key_repeat_count           DATASTRUCT._phone_key_repeat_count
#define parm__mgcp_rsip_keepalive_interval DATASTRUCT._parm__mgcp_rsip_keepalive_interval
#define ANSam_trace_magphase_max_real    DATASTRUCT._ANSam_trace_magphase_max_real
#define v92_MH_retrain_routine           DATASTRUCT._v92_MH_retrain_routine
#define nat_pkt_payload_ptr              DATASTRUCT._nat_pkt_payload_ptr
#define asm_encode_rtp_ans_send_cnt      DATASTRUCT._asm_encode_rtp_ans_send_cnt
#define parm__lec_delay_length           DATASTRUCT._parm__lec_delay_length
#define ec_very_slow_shift_slew_remote   DATASTRUCT._ec_very_slow_shift_slew_remote
#define hsflag_sint15_exchange_buffer    DATASTRUCT._hsflag_sint15_exchange_buffer
#define v34_resync_perfect_imag          DATASTRUCT._v34_resync_perfect_imag
#define dt_status_bit                    DATASTRUCT._dt_status_bit
#define parm__speech_rtp_sequence_number DATASTRUCT._parm__speech_rtp_sequence_number
#define parm__net_ddns_user_name         DATASTRUCT._parm__net_ddns_user_name
#define xq_s                             DATASTRUCT._xq_s
#define v32_timeout_margin               DATASTRUCT._v32_timeout_margin
#define test_1_ext                       DATASTRUCT._test_1_ext
#define pcm_ctl_disable_whiten           DATASTRUCT._pcm_ctl_disable_whiten
#define sonitrol_v34_spp_state           DATASTRUCT._sonitrol_v34_spp_state
#define eqout_lagging_real               DATASTRUCT._eqout_lagging_real
#define parm__ata_configuration_update_error_retry_delay DATASTRUCT._parm__ata_configuration_update_error_retry_delay
#define v32_rx_trellis_best_score        DATASTRUCT._v32_rx_trellis_best_score
#define phroll_convergence_threshold     DATASTRUCT._phroll_convergence_threshold
#define dcd_energy_inc                   DATASTRUCT._dcd_energy_inc
#define prev_con_s                       DATASTRUCT._prev_con_s
#define pcm_rx_offset                    DATASTRUCT._pcm_rx_offset
#define pcm_rx_8K0_data_routine_in       DATASTRUCT._pcm_rx_8K0_data_routine_in
#define pcm_equalizer_ff_coefs32         DATASTRUCT._pcm_equalizer_ff_coefs32
#define v90n_tx_Jd_body                  DATASTRUCT._v90n_tx_Jd_body
#define picp_offset                      DATASTRUCT._picp_offset
#define parm__sip_remote_user_parm       DATASTRUCT._parm__sip_remote_user_parm
#define lec__xx_results                  DATASTRUCT._lec__xx_results
#define v90n_rx_v90_override             DATASTRUCT._v90n_rx_v90_override
#define v34h_tx_process_enable           DATASTRUCT._v34h_tx_process_enable
#define v34_slew_neg_BE                  DATASTRUCT._v34_slew_neg_BE
#define faxdet_data_sum_ansam            DATASTRUCT._faxdet_data_sum_ansam
#define dec_lsp_old                      DATASTRUCT._dec_lsp_old
#define stat_sms_message_received        DATASTRUCT._stat_sms_message_received
#define amrEnc_struct                    DATASTRUCT._amrEnc_struct
#define DIL_probing_pad_gain_log         DATASTRUCT._DIL_probing_pad_gain_log
#define l_lpres_delin                    DATASTRUCT._l_lpres_delin
#define sample_overflow_count            DATASTRUCT._sample_overflow_count
#define demod_lagging_imag               DATASTRUCT._demod_lagging_imag
#define p18_bit_delay_buffer             DATASTRUCT._p18_bit_delay_buffer
#define detect_demod_imag                DATASTRUCT._detect_demod_imag
#define cc_rx_S                          DATASTRUCT._cc_rx_S
#define v34_rx_predicted_V0_m_Px2_counter DATASTRUCT._v34_rx_predicted_V0_m_Px2_counter
#define parm__sip_info_authentication    DATASTRUCT._parm__sip_info_authentication
#define localflag                        DATASTRUCT._localflag
#define v90_rx_ph34_state                DATASTRUCT._v90_rx_ph34_state
#define lec__data_size                   DATASTRUCT._lec__data_size
#define orig_v8_CM_sent                  DATASTRUCT._orig_v8_CM_sent
#define v90_tx_t_frame                   DATASTRUCT._v90_tx_t_frame
#define lec__enr_inve                    DATASTRUCT._lec__enr_inve
#define lec__enr_invg                    DATASTRUCT._lec__enr_invg
#define tmp_baud_UVW_imag                DATASTRUCT._tmp_baud_UVW_imag
#define CORRELATOR_FIT_THRESHOLD         DATASTRUCT._CORRELATOR_FIT_THRESHOLD
#define sync_ack_state                   DATASTRUCT._sync_ack_state
#define parm__ipbx_dialed_number         DATASTRUCT._parm__ipbx_dialed_number
#define asm_extra_frame_just_sent        DATASTRUCT._asm_extra_frame_just_sent
#define tonemute_decimate                DATASTRUCT._tonemute_decimate
#define cc_rx_PP                         DATASTRUCT._cc_rx_PP
#define ig_mem                           DATASTRUCT._ig_mem
#define equalizer_buffer_real            DATASTRUCT._equalizer_buffer_real
#define sart_rx_hybrid_packed_mode       DATASTRUCT._sart_rx_hybrid_packed_mode
#define v90h_tx_state                    DATASTRUCT._v90h_tx_state
#define encode_frame_size                DATASTRUCT._encode_frame_size
#define pcm_equalizer_ff_sum40           DATASTRUCT._pcm_equalizer_ff_sum40
#define pcm_bulk_delay_buffer            DATASTRUCT._pcm_bulk_delay_buffer
#define v34_frame_rx_bit_offset          DATASTRUCT._v34_frame_rx_bit_offset
#define g711a_plc_pointer_in             DATASTRUCT._g711a_plc_pointer_in
#define lec__rx_cng_frame_buffer         DATASTRUCT._lec__rx_cng_frame_buffer
#define tick_irq                         DATASTRUCT._tick_irq
#define sonitrol_audio_Lpt_response_recvd DATASTRUCT._sonitrol_audio_Lpt_response_recvd
#define v34_BE_modify_Gn_gain            DATASTRUCT._v34_BE_modify_Gn_gain
#define control_value                    DATASTRUCT._control_value
#define saved_scrambler_output           DATASTRUCT._saved_scrambler_output
#define l_firsttime                      DATASTRUCT._l_firsttime
#define v90_shape_2_min                  DATASTRUCT._v90_shape_2_min
#define ipod_iface_rx_size               DATASTRUCT._ipod_iface_rx_size
#define edge_m1200_imag32                DATASTRUCT._edge_m1200_imag32
#define parm__ipbx_fc_call_waiting_caller_id_disable DATASTRUCT._parm__ipbx_fc_call_waiting_caller_id_disable
#define sms_index                        DATASTRUCT._sms_index
#define v34_temp_lo_pre_emph_adjust_table DATASTRUCT._v34_temp_lo_pre_emph_adjust_table
#define v92n_rxtx_apcm_data_rate_max     DATASTRUCT._v92n_rxtx_apcm_data_rate_max
#define mark_idle_tx_active              DATASTRUCT._mark_idle_tx_active
#define keep_alive_flag                  DATASTRUCT._keep_alive_flag
#define parm__codec_ring_detect_period_maximum DATASTRUCT._parm__codec_ring_detect_period_maximum
#define ph2n_probing_frequency_buffer    DATASTRUCT._ph2n_probing_frequency_buffer
#define ORIG_LEN_MS_RLSD_TURNON_DELAY    DATASTRUCT._ORIG_LEN_MS_RLSD_TURNON_DELAY
#define v92_rx_yn_tilde_poffset          DATASTRUCT._v92_rx_yn_tilde_poffset
#define report_tx_packet_flag            DATASTRUCT._report_tx_packet_flag
#define v90_rx_spectrum_offset_buffer    DATASTRUCT._v90_rx_spectrum_offset_buffer
#define v92_rx_sign                      DATASTRUCT._v92_rx_sign
#define asm_vad_currently_off            DATASTRUCT._asm_vad_currently_off
#define DIL_probing_pad_type             DATASTRUCT._DIL_probing_pad_type
#define v34_rx_xn_tilde_real             DATASTRUCT._v34_rx_xn_tilde_real
#define v90_shape_store_offset           DATASTRUCT._v90_shape_store_offset
#define parm__sip_info_hookflash         DATASTRUCT._parm__sip_info_hookflash
#define stat__ipod_dth_vfd               DATASTRUCT._stat__ipod_dth_vfd
#define v24_dsr                          DATASTRUCT._v24_dsr
#define V34S_LEN_8K0_PHROLL_PASS         DATASTRUCT._V34S_LEN_8K0_PHROLL_PASS
#define ph2p_anal_variance_04_table      DATASTRUCT._ph2p_anal_variance_04_table
#define v90n_rx_constel_codec_pointer    DATASTRUCT._v90n_rx_constel_codec_pointer
#define parm__ata_finalize_domain_name   DATASTRUCT._parm__ata_finalize_domain_name
#define stat__ipbx_state                 DATASTRUCT._stat__ipbx_state
#define v90n_rxtx_dpcm_data_rate_max     DATASTRUCT._v90n_rxtx_dpcm_data_rate_max
#define Gain_global                      DATASTRUCT._Gain_global
#define parm__net_dhcp_server_starting_ip_address DATASTRUCT._parm__net_dhcp_server_starting_ip_address
#define parm__ipbx_call_back_duration    DATASTRUCT._parm__ipbx_call_back_duration
#define l_prev_uv                        DATASTRUCT._l_prev_uv
#define phone_lock_bypass                DATASTRUCT._phone_lock_bypass
#define v90_frame_tx_dil_body_ref        DATASTRUCT._v90_frame_tx_dil_body_ref
#define monitor_sample_fast              DATASTRUCT._monitor_sample_fast
#define lec__best_lin_poffset            DATASTRUCT._lec__best_lin_poffset
#define scramb_msb                       DATASTRUCT._scramb_msb
#define prev_fsmag_low_rate_chn_read     DATASTRUCT._prev_fsmag_low_rate_chn_read
#define mgcp_timer_proc                  DATASTRUCT._mgcp_timer_proc
#define agc_2_feedback_slew              DATASTRUCT._agc_2_feedback_slew
#define stat__sms_response               DATASTRUCT._stat__sms_response
#define v92_system_ID_in_poffset         DATASTRUCT._v92_system_ID_in_poffset
#define special_train_counter            DATASTRUCT._special_train_counter
#define g722_2_tx_state                  DATASTRUCT._g722_2_tx_state
#define rf_rx_dc_qoffset                 DATASTRUCT._rf_rx_dc_qoffset
#define g600q_s                          DATASTRUCT._g600q_s
#define detect_count                     DATASTRUCT._detect_count
#define v34_equalizer_btrec_enabled      DATASTRUCT._v34_equalizer_btrec_enabled
#define baud_rx_data_dlvd                DATASTRUCT._baud_rx_data_dlvd
#define last_interrupt_count             DATASTRUCT._last_interrupt_count
#define gpf_fine_match                   DATASTRUCT._gpf_fine_match
#define parm__ffsk_enc_gain              DATASTRUCT._parm__ffsk_enc_gain
#define v90_rx_k_value                   DATASTRUCT._v90_rx_k_value
#define pcm_artificial_echo_flag         DATASTRUCT._pcm_artificial_echo_flag
#define ph2_tx_baud_shift_register       DATASTRUCT._ph2_tx_baud_shift_register
#define parm__net_isp_password           DATASTRUCT._parm__net_isp_password
#define fg_event_dsp_uses_background     DATASTRUCT._fg_event_dsp_uses_background
#define tempword                         DATASTRUCT._tempword
#define parm__rtp_transfer_channels      DATASTRUCT._parm__rtp_transfer_channels
#define ac97_major_number                DATASTRUCT._ac97_major_number
#define dtmf_on_start                    DATASTRUCT._dtmf_on_start
#define gain_pitch                       DATASTRUCT._gain_pitch
#define stat__phone_key_code             DATASTRUCT._stat__phone_key_code
#define ipod_msg_rx_dom                  DATASTRUCT._ipod_msg_rx_dom
#define v34_rx_predicted_V0_m_Jx2_counter DATASTRUCT._v34_rx_predicted_V0_m_Jx2_counter
#define pspr_y1_hi                       DATASTRUCT._pspr_y1_hi
#define V34S_LEN_8K0_1RT_MIN_1ST_SHORT   DATASTRUCT._V34S_LEN_8K0_1RT_MIN_1ST_SHORT
#define phasedet_rnd_complex_value       DATASTRUCT._phasedet_rnd_complex_value
#define edge_p1200_imag                  DATASTRUCT._edge_p1200_imag
#define v92n_rxtx_apcm_data_rate_option32 DATASTRUCT._v92n_rxtx_apcm_data_rate_option32
#define FAX_test_error_limit             DATASTRUCT._FAX_test_error_limit
#define parm__codec_message_waiting_mode DATASTRUCT._parm__codec_message_waiting_mode
#define constel_symmetric_table_nrm      DATASTRUCT._constel_symmetric_table_nrm
#define tx_rate_double_poffset           DATASTRUCT._tx_rate_double_poffset
#define ANSAM_UPPER_THRESHOLD            DATASTRUCT._ANSAM_UPPER_THRESHOLD
#define v90_tx_dil_tp_cnt                DATASTRUCT._v90_tx_dil_tp_cnt
#define saved_bit_pattern                DATASTRUCT._saved_bit_pattern
#define short_train_resynchronization_active DATASTRUCT._short_train_resynchronization_active
#define stat__phone_key_matrix           DATASTRUCT._stat__phone_key_matrix
#define eqout_lagging_delay_imag         DATASTRUCT._eqout_lagging_delay_imag
#define parm__mgcp_public_external_rtp_port_min DATASTRUCT._parm__mgcp_public_external_rtp_port_min
#define line_rx_buffer_element           DATASTRUCT._line_rx_buffer_element
#define sart_rx_read_index               DATASTRUCT._sart_rx_read_index
#define asm_encode_packed_length         DATASTRUCT._asm_encode_packed_length
#define mgcp_next_transaction_id         DATASTRUCT._mgcp_next_transaction_id
#define parm__ipbx_fxo_autoanswer_enable DATASTRUCT._parm__ipbx_fxo_autoanswer_enable
#define ph2_INFOMARKS_one_count          DATASTRUCT._ph2_INFOMARKS_one_count
#define parm__mf_tone_off_time           DATASTRUCT._parm__mf_tone_off_time
#define priority_generator_buffer        DATASTRUCT._priority_generator_buffer
#define V34_RESYNC_MEASURE_LENGTH        DATASTRUCT._V34_RESYNC_MEASURE_LENGTH
#define rxs_out_vxxmod_remote            DATASTRUCT._rxs_out_vxxmod_remote
#define v34n_parm_precoder_option        DATASTRUCT._v34n_parm_precoder_option
#define parm__sdp_g711u_codec_name       DATASTRUCT._parm__sdp_g711u_codec_name
#define remote_ec_sum                    DATASTRUCT._remote_ec_sum
#define dgi_pad_loss                     DATASTRUCT._dgi_pad_loss
#define p18_demodulator_phase            DATASTRUCT._p18_demodulator_phase
#define gpf_lpointer                     DATASTRUCT._gpf_lpointer
#define sdt_delta_energy_threshold       DATASTRUCT._sdt_delta_energy_threshold
#define mpi_debounce                     DATASTRUCT._mpi_debounce
#define dtmf_last_row_level              DATASTRUCT._dtmf_last_row_level
#define v90n_rx_reference_point          DATASTRUCT._v90n_rx_reference_point
#define PH2S_LEN_T_DATA_TIMEOUT          DATASTRUCT._PH2S_LEN_T_DATA_TIMEOUT
#define THD_measurement_variance         DATASTRUCT._THD_measurement_variance
#define v34n_parm_asymmetric_option      DATASTRUCT._v34n_parm_asymmetric_option
#define v34h_tx_residue_hi               DATASTRUCT._v34h_tx_residue_hi
#define V90_RX_R_DETECT_EVENT            DATASTRUCT._V90_RX_R_DETECT_EVENT
#define pcm_rx_8K0_divisor_flag          DATASTRUCT._pcm_rx_8K0_divisor_flag
#define rf_transmit_enabled              DATASTRUCT._rf_transmit_enabled
#define stat__nat_wan_translated         DATASTRUCT._stat__nat_wan_translated
#define g729_prm                         DATASTRUCT._g729_prm
#define g_bitNum12                       DATASTRUCT._g_bitNum12
#define parm__ipbx_fc_one_digit_speed_dial_program DATASTRUCT._parm__ipbx_fc_one_digit_speed_dial_program
#define v90n_rx_saved_parameters         DATASTRUCT._v90n_rx_saved_parameters
#define parm__codec_parallel_in_use_debounce DATASTRUCT._parm__codec_parallel_in_use_debounce
#define lspSid_q                         DATASTRUCT._lspSid_q
#define pcm_slot_counter                 DATASTRUCT._pcm_slot_counter
#define THD_measurement_relative         DATASTRUCT._THD_measurement_relative
#define lec__data_poffset                DATASTRUCT._lec__data_poffset
#define parm__pump_diag_count_msw        DATASTRUCT._parm__pump_diag_count_msw
#define lec__datamax_full_counter        DATASTRUCT._lec__datamax_full_counter
#define PH2P_POWR_LX_PROCESS_LENGTH      DATASTRUCT._PH2P_POWR_LX_PROCESS_LENGTH
#define parm__dm_v34_ptt_carrier_mask    DATASTRUCT._parm__dm_v34_ptt_carrier_mask
#define v92n_rx_CP_body_cm               DATASTRUCT._v92n_rx_CP_body_cm
#define v34h_rx_I1ij_m                   DATASTRUCT._v34h_rx_I1ij_m
#define jitter_jitter_real               DATASTRUCT._jitter_jitter_real
#define cc_rx_ANAL_AGC2_log              DATASTRUCT._cc_rx_ANAL_AGC2_log
#define pick_max_stat                    DATASTRUCT._pick_max_stat
#define equalizer_leading_real           DATASTRUCT._equalizer_leading_real
#define ANSW_LEN_MS_CJ_TIMEOUT           DATASTRUCT._ANSW_LEN_MS_CJ_TIMEOUT
#define fg_state_list                    DATASTRUCT._fg_state_list
#define ata_need_code                    DATASTRUCT._ata_need_code
#define sense_silence_threshold          DATASTRUCT._sense_silence_threshold
#define baud_tx_parity_used              DATASTRUCT._baud_tx_parity_used
#define cp_status_bit                    DATASTRUCT._cp_status_bit
#define v34_resync_phase_correction      DATASTRUCT._v34_resync_phase_correction
#define stat__nat_snd_frag_created       DATASTRUCT._stat__nat_snd_frag_created
#define parm__codec_disconnect_reversals_answer DATASTRUCT._parm__codec_disconnect_reversals_answer
#define g_bitNum24                       DATASTRUCT._g_bitNum24
#define l_top_lpc                        DATASTRUCT._l_top_lpc
#define ata_random_delay_code            DATASTRUCT._ata_random_delay_code
#define rx_lpf_poffset                   DATASTRUCT._rx_lpf_poffset
#define v34n_tx_primary_channel_maxrate  DATASTRUCT._v34n_tx_primary_channel_maxrate
#define lookback_update_base             DATASTRUCT._lookback_update_base
#define lec__probe_tx_input              DATASTRUCT._lec__probe_tx_input
#define silence_passband_poffset         DATASTRUCT._silence_passband_poffset
#define ANSam_trace_offset               DATASTRUCT._ANSam_trace_offset
#define v34_rx_yn_hat_imag               DATASTRUCT._v34_rx_yn_hat_imag
#define parm__ipbx_disturb_accept_list   DATASTRUCT._parm__ipbx_disturb_accept_list
#define ec_medium_shift_slew_local       DATASTRUCT._ec_medium_shift_slew_local
#define baud_tx_bit_cnt                  DATASTRUCT._baud_tx_bit_cnt
#define parm__sip_public_external_sip_port DATASTRUCT._parm__sip_public_external_sip_port
#define v34_MSE_N_value                  DATASTRUCT._v34_MSE_N_value
#define parm__slac_ring_transition       DATASTRUCT._parm__slac_ring_transition
#define v92n_tx_constel_size             DATASTRUCT._v92n_tx_constel_size
#define cc_rx_lpf_buffer_real            DATASTRUCT._cc_rx_lpf_buffer_real
#define agc_2_exponent                   DATASTRUCT._agc_2_exponent
#define lec__slew                        DATASTRUCT._lec__slew
#define parm__nat_timeout_tcp_open       DATASTRUCT._parm__nat_timeout_tcp_open
#define g168_err_floor                   DATASTRUCT._g168_err_floor
#define gled_pattern_index               DATASTRUCT._gled_pattern_index
#define b202_ans_tx_passband_coefs_buffer_internal DATASTRUCT._b202_ans_tx_passband_coefs_buffer_internal
#define v34_temp_lo_carrier              DATASTRUCT._v34_temp_lo_carrier
#define V90_RX_ALL_ENERGY_THRESHOLD      DATASTRUCT._V90_RX_ALL_ENERGY_THRESHOLD
#define clock_rx                         DATASTRUCT._clock_rx
#define lec__dc_offset_sum32             DATASTRUCT._lec__dc_offset_sum32
#define ph4n_rx_trained_maxrate          DATASTRUCT._ph4n_rx_trained_maxrate
#define parm__dpbx_led_or_mask           DATASTRUCT._parm__dpbx_led_or_mask
#define parm__codec_disconnect_silence_duration DATASTRUCT._parm__codec_disconnect_silence_duration
#define v34s_special_local_decor_option  DATASTRUCT._v34s_special_local_decor_option
#define v34h_rx_V0_m                     DATASTRUCT._v34h_rx_V0_m
#define v34_BE_jam_baud_agc              DATASTRUCT._v34_BE_jam_baud_agc
#define fax_v21_CED_pause                DATASTRUCT._fax_v21_CED_pause
#define uicp_size_of                     DATASTRUCT._uicp_size_of
#define v90_rx_s_frame                   DATASTRUCT._v90_rx_s_frame
#define v27_tx_guard_count               DATASTRUCT._v27_tx_guard_count
#define parm__codec_initialization_commands DATASTRUCT._parm__codec_initialization_commands
#define parm__data_storage_level_crossed DATASTRUCT._parm__data_storage_level_crossed
#define pcm_rx_slot_counter_xtr          DATASTRUCT._pcm_rx_slot_counter_xtr
#define parm__ata_logo_url               DATASTRUCT._parm__ata_logo_url
#define pspr_y1_lo                       DATASTRUCT._pspr_y1_lo
#define cc_rx_PP_last_energy_log         DATASTRUCT._cc_rx_PP_last_energy_log
#define det_energy32                     DATASTRUCT._det_energy32
#define g168_err_peak                    DATASTRUCT._g168_err_peak
#define sonitrol_good_message_count      DATASTRUCT._sonitrol_good_message_count
#define pcm_test_disable_outer_rx_rate_double DATASTRUCT._pcm_test_disable_outer_rx_rate_double
#define v92_MH_RT_found_flag             DATASTRUCT._v92_MH_RT_found_flag
#define v34s_reneg_test_resp_variable_S_length DATASTRUCT._v34s_reneg_test_resp_variable_S_length
#define lec__nlp_cng_offset_buffer       DATASTRUCT._lec__nlp_cng_offset_buffer
#define parm__mgcp_hostname              DATASTRUCT._parm__mgcp_hostname
#define sdt_correlator_fit_threshold     DATASTRUCT._sdt_correlator_fit_threshold
#define shadow_line_enabled              DATASTRUCT._shadow_line_enabled
#define v34n_rx_attenuation_option       DATASTRUCT._v34n_rx_attenuation_option
#define current_bg_task_active           DATASTRUCT._current_bg_task_active
#define v90h_rx_control_frame            DATASTRUCT._v90h_rx_control_frame
#define parm__net_isp_user_name          DATASTRUCT._parm__net_isp_user_name
#define l_firstTime_melp_ana             DATASTRUCT._l_firstTime_melp_ana
#define vad_prev_energy                  DATASTRUCT._vad_prev_energy
#define stat__picp_parse_state           DATASTRUCT._stat__picp_parse_state
#define PCM_PEAK_MSE_STACK_COUNT         DATASTRUCT._PCM_PEAK_MSE_STACK_COUNT
#define PH2P_POWR_L1_FINAL_TUNE          DATASTRUCT._PH2P_POWR_L1_FINAL_TUNE
#define ch_seize_data_unit               DATASTRUCT._ch_seize_data_unit
#define tone_pattern_gen_index           DATASTRUCT._tone_pattern_gen_index
#define cc_rx_rate_reduction_ratio       DATASTRUCT._cc_rx_rate_reduction_ratio
#define l_prev_lpc_gain                  DATASTRUCT._l_prev_lpc_gain
#define initial_training                 DATASTRUCT._initial_training
#define v90n_tx_receive_redundancy       DATASTRUCT._v90n_tx_receive_redundancy
#define det_energy40                     DATASTRUCT._det_energy40
#define v34_BE_neg_power_32              DATASTRUCT._v34_BE_neg_power_32
#define ata_sample_record_index          DATASTRUCT._ata_sample_record_index
#define rxs_aux_rx_data                  DATASTRUCT._rxs_aux_rx_data
#define fsk_run_flag_correlator          DATASTRUCT._fsk_run_flag_correlator
#define baud_rx_16_bit_mode              DATASTRUCT._baud_rx_16_bit_mode
#define ipbx_call_current                DATASTRUCT._ipbx_call_current
#define parm__net_isp_heartbeat_signal_enable DATASTRUCT._parm__net_isp_heartbeat_signal_enable
#define parm__voip_ilbc_high_rate_enable DATASTRUCT._parm__voip_ilbc_high_rate_enable
#define rev_count                        DATASTRUCT._rev_count
#define rate_reduction_ratio             DATASTRUCT._rate_reduction_ratio
#define g723_VadStat                     DATASTRUCT._g723_VadStat
#define v34h_tx_residue_lo               DATASTRUCT._v34h_tx_residue_lo
#define ph2n_sm_INFO0h_end_delay         DATASTRUCT._ph2n_sm_INFO0h_end_delay
#define tx_bpf_coef_pointer              DATASTRUCT._tx_bpf_coef_pointer
#define stat__speech_dec_bad_frame_mtr   DATASTRUCT._stat__speech_dec_bad_frame_mtr
#define parm__ipbx_call_forward_service  DATASTRUCT._parm__ipbx_call_forward_service
#define fax_v21_energy_length            DATASTRUCT._fax_v21_energy_length
#define parm__lec_length                 DATASTRUCT._parm__lec_length
#define v34n_rx_transmit_gain            DATASTRUCT._v34n_rx_transmit_gain
#define ANSam_trace_count_2100_value     DATASTRUCT._ANSam_trace_count_2100_value
#define cp_hysteresis                    DATASTRUCT._cp_hysteresis
#define v92_rx_decoder_ff_input_energy40 DATASTRUCT._v92_rx_decoder_ff_input_energy40
#define test_1_msw                       DATASTRUCT._test_1_msw
#define stat__nat_rcv_alg_discards       DATASTRUCT._stat__nat_rcv_alg_discards
#define parm__sip_user_agent             DATASTRUCT._parm__sip_user_agent
#define v34_MSE_S_stack                  DATASTRUCT._v34_MSE_S_stack
#define g711a_plc_frame_counter          DATASTRUCT._g711a_plc_frame_counter
#define ph2n_probing_L2_log_N_buffer     DATASTRUCT._ph2n_probing_L2_log_N_buffer
#define V92N_RX_PREFILTER_GAIN_x4        DATASTRUCT._V92N_RX_PREFILTER_GAIN_x4
#define ph2n_rx_preemph                  DATASTRUCT._ph2n_rx_preemph
#define stat__sip_local_contact_domain_name DATASTRUCT._stat__sip_local_contact_domain_name
#define g711_rx_vad_peak_kf              DATASTRUCT._g711_rx_vad_peak_kf
#define mpi_debounce_disconnect          DATASTRUCT._mpi_debounce_disconnect
#define p18_delta_energy_threshold       DATASTRUCT._p18_delta_energy_threshold
#define okay_to_turn_off                 DATASTRUCT._okay_to_turn_off
#define lec__nlp_cng_enable              DATASTRUCT._lec__nlp_cng_enable
#define parm__ipbx_block_anonymous_enable DATASTRUCT._parm__ipbx_block_anonymous_enable
#define parm__ipbx_led_pstn_in_use       DATASTRUCT._parm__ipbx_led_pstn_in_use
#define v34_tx_qn_buffer_imag            DATASTRUCT._v34_tx_qn_buffer_imag
#define baud_tx_cntr                     DATASTRUCT._baud_tx_cntr
#define g711_rx_vad_peak_kr              DATASTRUCT._g711_rx_vad_peak_kr
#define g723_WrkRate                     DATASTRUCT._g723_WrkRate
#define prev_qpitch_pitch_vq             DATASTRUCT._prev_qpitch_pitch_vq
#define descrambled_mark_count           DATASTRUCT._descrambled_mark_count
#define parm__nat_port_trigger           DATASTRUCT._parm__nat_port_trigger
#define hdlc_lead_flag_cnt               DATASTRUCT._hdlc_lead_flag_cnt
#define v34h_tx_control_pointer          DATASTRUCT._v34h_tx_control_pointer
#define s1_flags                         DATASTRUCT._s1_flags
#define v90_frame_rx_sync_register       DATASTRUCT._v90_frame_rx_sync_register
#define v90_tx_eye_modulus               DATASTRUCT._v90_tx_eye_modulus
#define new_scores                       DATASTRUCT._new_scores
#define v34_ph2_common_name_values       DATASTRUCT._v34_ph2_common_name_values
#define l_lpc_del                        DATASTRUCT._l_lpc_del
#define parm__dpbx_led_use_and_waiting   DATASTRUCT._parm__dpbx_led_use_and_waiting
#define best_rmt                         DATASTRUCT._best_rmt
#define v34_tx_pn_imag                   DATASTRUCT._v34_tx_pn_imag
#define v92_rx_i_DF_count                DATASTRUCT._v92_rx_i_DF_count
#define v92_tx_send_CPd_flag             DATASTRUCT._v92_tx_send_CPd_flag
#define v90_tx_dil_ucode_ptr             DATASTRUCT._v90_tx_dil_ucode_ptr
#define V92_DECODER_EP_SHIFT             DATASTRUCT._V92_DECODER_EP_SHIFT
#define v90_shape_3_offset               DATASTRUCT._v90_shape_3_offset
#define ptloop_angle_change_limit        DATASTRUCT._ptloop_angle_change_limit
#define stat__vppn_off_hook              DATASTRUCT._stat__vppn_off_hook
#define pcm_disc_slot_match_list         DATASTRUCT._pcm_disc_slot_match_list
#define tst_rx_8K0_transfer_overflow     DATASTRUCT._tst_rx_8K0_transfer_overflow
#define parm__vppn_channel_active_count  DATASTRUCT._parm__vppn_channel_active_count
#define pcm_ctl_ep_nlms_override         DATASTRUCT._pcm_ctl_ep_nlms_override
#define V34S_LEN_8K0_1RT_MAX_1ST_TRAIN   DATASTRUCT._V34S_LEN_8K0_1RT_MAX_1ST_TRAIN
#define v90n_rx_shaping_a1               DATASTRUCT._v90n_rx_shaping_a1
#define parm__codec_disconnect_tone_3_bandwidth DATASTRUCT._parm__codec_disconnect_tone_3_bandwidth
#define parm__voip_fax_processing_rate   DATASTRUCT._parm__voip_fax_processing_rate
#define v90n_rx_shaping_a2               DATASTRUCT._v90n_rx_shaping_a2
#define PCM_TRN2_DATA_MAXRATE_TABLE      DATASTRUCT._PCM_TRN2_DATA_MAXRATE_TABLE
#define detect_energy_lpf2_32            DATASTRUCT._detect_energy_lpf2_32
#define g722_e4h_ah1                     DATASTRUCT._g722_e4h_ah1
#define v34_rx_pn_hat_imag               DATASTRUCT._v34_rx_pn_hat_imag
#define g722_e4h_ah2                     DATASTRUCT._g722_e4h_ah2
#define parm__rtp_dtmf_playout_duration  DATASTRUCT._parm__rtp_dtmf_playout_duration
#define parm__sdp_gsm_efr_codec_dyn_pt   DATASTRUCT._parm__sdp_gsm_efr_codec_dyn_pt
#define ph2_ac_output40                  DATASTRUCT._ph2_ac_output40
#define parm__codec_impedance_commands   DATASTRUCT._parm__codec_impedance_commands
#define ipbx_digit_detected              DATASTRUCT._ipbx_digit_detected
#define ph2_tx_passband_offset           DATASTRUCT._ph2_tx_passband_offset
#define v34_frame_rx_MP_found            DATASTRUCT._v34_frame_rx_MP_found
#define equalized_real                   DATASTRUCT._equalized_real
#define pre_gear_change_period           DATASTRUCT._pre_gear_change_period
#define parm__sdp_t38_codec_name         DATASTRUCT._parm__sdp_t38_codec_name
#define v90_tx_dil_lsp                   DATASTRUCT._v90_tx_dil_lsp
#define v90n_rx_shaping_b1               DATASTRUCT._v90n_rx_shaping_b1
#define pcm_equalizer_fb_buffer          DATASTRUCT._pcm_equalizer_fb_buffer
#define v90n_rx_shaping_b2               DATASTRUCT._v90n_rx_shaping_b2
#define v34_tx_decor_pointer             DATASTRUCT._v34_tx_decor_pointer
#define enc_exc                          DATASTRUCT._enc_exc
#define cc_rx_ANAL_DC_angle              DATASTRUCT._cc_rx_ANAL_DC_angle
#define v34_frame_rx_save_bit_parse_pointer DATASTRUCT._v34_frame_rx_save_bit_parse_pointer
#define V34S_LEN_8K0_2ND_PHASE_CHANGE    DATASTRUCT._V34S_LEN_8K0_2ND_PHASE_CHANGE
#define current_codeword                 DATASTRUCT._current_codeword
#define DIL_calculation_pad_gain_log     DATASTRUCT._DIL_calculation_pad_gain_log
#define pcm_8K0_error                    DATASTRUCT._pcm_8K0_error
#define THD_sum_L2_S_norm                DATASTRUCT._THD_sum_L2_S_norm
#define dtmf_peak_col_level              DATASTRUCT._dtmf_peak_col_level
#define V90_TEST_PARM_LIMIT_SYMBOL       DATASTRUCT._V90_TEST_PARM_LIMIT_SYMBOL
#define rxs_demod_imag                   DATASTRUCT._rxs_demod_imag
#define vppn_encode_packet_list          DATASTRUCT._vppn_encode_packet_list
#define circb_min_shift                  DATASTRUCT._circb_min_shift
#define V90_TRAIN_EC_WITH_RBS            DATASTRUCT._V90_TRAIN_EC_WITH_RBS
#define parm__voip_default_display_name  DATASTRUCT._parm__voip_default_display_name
#define loopback_buffer_length           DATASTRUCT._loopback_buffer_length
#define parm__lec_mode                   DATASTRUCT._parm__lec_mode
#define parm__voip_g722p2_encode_rate    DATASTRUCT._parm__voip_g722p2_encode_rate
#define mbx                              DATASTRUCT._mbx
#define v90_tx_sample_counter            DATASTRUCT._v90_tx_sample_counter
#define equalizer_slew_special           DATASTRUCT._equalizer_slew_special
#define ptloop_phdet_error_fast32        DATASTRUCT._ptloop_phdet_error_fast32
#define parm__dpbx_led_do_not_disturb    DATASTRUCT._parm__dpbx_led_do_not_disturb
#define gpf_RRadj                        DATASTRUCT._gpf_RRadj
#define fsk_TONE_started                 DATASTRUCT._fsk_TONE_started
#define ph4n_tx_receive_shaping          DATASTRUCT._ph4n_tx_receive_shaping
#define threshold_fsk                    DATASTRUCT._threshold_fsk
#define v90_tx_dil_ltp                   DATASTRUCT._v90_tx_dil_ltp
#define v34n_sm_INFO0h_end_delay         DATASTRUCT._v34n_sm_INFO0h_end_delay
#define ptloop_phdet_state               DATASTRUCT._ptloop_phdet_state
#define v90_successive_reneg_count       DATASTRUCT._v90_successive_reneg_count
#define decode_byte_counter              DATASTRUCT._decode_byte_counter
#define parm__sdp_NSE_codec_name         DATASTRUCT._parm__sdp_NSE_codec_name
#define ph2p_powr_dmod_rx_offset32       DATASTRUCT._ph2p_powr_dmod_rx_offset32
#define v92_system_ID_max_spacing        DATASTRUCT._v92_system_ID_max_spacing
#define parm__slac_port_impedance        DATASTRUCT._parm__slac_port_impedance
#define parm__ipbx_answer_hangup_delay   DATASTRUCT._parm__ipbx_answer_hangup_delay
#define v34_local_echo_value             DATASTRUCT._v34_local_echo_value
#define V34S_INIT_8K0_2RT_S_SN_to_Edet   DATASTRUCT._V34S_INIT_8K0_2RT_S_SN_to_Edet
#define chwordsize                       DATASTRUCT._chwordsize
#define pcm_bulk_delay_input_flag        DATASTRUCT._pcm_bulk_delay_input_flag
#define lec__cng_data                    DATASTRUCT._lec__cng_data
#define ata_led_use_mask_update          DATASTRUCT._ata_led_use_mask_update
#define stat__speech_dec_default_sample_cnt DATASTRUCT._stat__speech_dec_default_sample_cnt
#define parm__slac_ring_generator        DATASTRUCT._parm__slac_ring_generator
#define pcm_ec_type                      DATASTRUCT._pcm_ec_type
#define Dec_Inst                         DATASTRUCT._Dec_Inst
#define comn_v8_TONEq_send               DATASTRUCT._comn_v8_TONEq_send
#define vppn_device_command_queue_out    DATASTRUCT._vppn_device_command_queue_out
#define parm__sip_incoming_reregister_interval DATASTRUCT._parm__sip_incoming_reregister_interval
#define parm__net_dhcp_server_wins_address DATASTRUCT._parm__net_dhcp_server_wins_address
#define parm__ipbx_fc_no_answer_forward_enable DATASTRUCT._parm__ipbx_fc_no_answer_forward_enable
#define nat_pkt_udp_ptr                  DATASTRUCT._nat_pkt_udp_ptr
#define g168_nf_data                     DATASTRUCT._g168_nf_data
#define stat__nat_snd_ipsec              DATASTRUCT._stat__nat_snd_ipsec
#define stat__nat_snd_create             DATASTRUCT._stat__nat_snd_create
#define stat__nat_wan_frag_forward       DATASTRUCT._stat__nat_wan_frag_forward
#define g711a_plc_pitch                  DATASTRUCT._g711a_plc_pitch
#define ANSAM_2100_MAX                   DATASTRUCT._ANSAM_2100_MAX
#define lec__average_activity_counter    DATASTRUCT._lec__average_activity_counter
#define parm__dest_rtp_address           DATASTRUCT._parm__dest_rtp_address
#define special_data_counter             DATASTRUCT._special_data_counter
#define v92n_tx_v92_override             DATASTRUCT._v92n_tx_v92_override
#define parm__ata_web_server_language    DATASTRUCT._parm__ata_web_server_language
#define v90_dpcm_dil_length              DATASTRUCT._v90_dpcm_dil_length
#define parm_dec                         DATASTRUCT._parm_dec
#define l_lpfsp_delin                    DATASTRUCT._l_lpfsp_delin
#define l_mem1                           DATASTRUCT._l_mem1
#define l_mem2                           DATASTRUCT._l_mem2
#define ph2p_anal_log_N_buffer           DATASTRUCT._ph2p_anal_log_N_buffer
#define v34_equalized_imag               DATASTRUCT._v34_equalized_imag
#define stat__dtmf_detect                DATASTRUCT._stat__dtmf_detect
#define lec__datamax_full_size           DATASTRUCT._lec__datamax_full_size
#define baud_rx_flag                     DATASTRUCT._baud_rx_flag
#define v34n_rx_INFO1a_body              DATASTRUCT._v34n_rx_INFO1a_body
#define parm__codec_caller_id_type_1_mode DATASTRUCT._parm__codec_caller_id_type_1_mode
#define stat__sip_local_contact_port     DATASTRUCT._stat__sip_local_contact_port
#define chan_start_flag                  DATASTRUCT._chan_start_flag
#define stat__nat_snd_pppoe              DATASTRUCT._stat__nat_snd_pppoe
#define nat_private_table                DATASTRUCT._nat_private_table
#define dgidet_ec_energy40               DATASTRUCT._dgidet_ec_energy40
#define DIL_probing_slot_counter_xtr     DATASTRUCT._DIL_probing_slot_counter_xtr
#define fsk_rx_clock_phase               DATASTRUCT._fsk_rx_clock_phase
#define local__voip_silence_supression_enable DATASTRUCT._local__voip_silence_supression_enable
#define v34_rx_yn_imag                   DATASTRUCT._v34_rx_yn_imag
#define sonitrol_remote_control_port     DATASTRUCT._sonitrol_remote_control_port
#define parm__net_dhcp_server_short_lease_time DATASTRUCT._parm__net_dhcp_server_short_lease_time
#define parm__rtp_session_timeout_interval DATASTRUCT._parm__rtp_session_timeout_interval
#define sync_prev_data                   DATASTRUCT._sync_prev_data
#define parm__data_storage_level         DATASTRUCT._parm__data_storage_level
#define stat__nat_rcv_ip_forward         DATASTRUCT._stat__nat_rcv_ip_forward
#define gci_indication                   DATASTRUCT._gci_indication
#define s1_detector_num_tones            DATASTRUCT._s1_detector_num_tones
#define selected_rate                    DATASTRUCT._selected_rate
#define rx_interpolator_pointer_adjust   DATASTRUCT._rx_interpolator_pointer_adjust
#define ph2n_rx_receive_CME              DATASTRUCT._ph2n_rx_receive_CME
#define prev_prev_phase_roll_second      DATASTRUCT._prev_prev_phase_roll_second
#define parm__net_dhcp_server_gateway_address DATASTRUCT._parm__net_dhcp_server_gateway_address
#define v34_rx_qn_perfect_poffset        DATASTRUCT._v34_rx_qn_perfect_poffset
#define v34n_tx_preemph_value            DATASTRUCT._v34n_tx_preemph_value
#define parm__ipbx_bridge_autoanswer_anonymous_enable DATASTRUCT._parm__ipbx_bridge_autoanswer_anonymous_enable
#define ANSam_trace_magphase_min_imag    DATASTRUCT._ANSam_trace_magphase_min_imag
#define ph2p_anal_variance_10_table      DATASTRUCT._ph2p_anal_variance_10_table
#define v90_frame_rx_save_bit_count      DATASTRUCT._v90_frame_rx_save_bit_count
#define parm__ipbx_input_pattern_voip    DATASTRUCT._parm__ipbx_input_pattern_voip
#define tx_rate_double_buffer            DATASTRUCT._tx_rate_double_buffer
#define faxdet_ced_cnt                   DATASTRUCT._faxdet_ced_cnt
#define wiznet_interrupt_process         DATASTRUCT._wiznet_interrupt_process
#define PCM_TRN2_MSE_REPORT_RATE         DATASTRUCT._PCM_TRN2_MSE_REPORT_RATE
#define dev_rx_frame                     DATASTRUCT._dev_rx_frame
#define PH2P_FEFO_GAIN_MARGIN            DATASTRUCT._PH2P_FEFO_GAIN_MARGIN
#define tone_generator_buffer            DATASTRUCT._tone_generator_buffer
#define cc_rx_PP_BEp_save_energy_log     DATASTRUCT._cc_rx_PP_BEp_save_energy_log
#define l_memt                           DATASTRUCT._l_memt
#define parm__radio_receiver_monitor_enable DATASTRUCT._parm__radio_receiver_monitor_enable
#define lec__td_hold_1st_flag            DATASTRUCT._lec__td_hold_1st_flag
#define ANSam_trace_max_imag             DATASTRUCT._ANSam_trace_max_imag
#define stat__symlist_checksum           DATASTRUCT._stat__symlist_checksum
#define monitor_input_raw_status         DATASTRUCT._monitor_input_raw_status
#define echo_canceller_error_sum         DATASTRUCT._echo_canceller_error_sum
#define ipbx_announce_ip_address         DATASTRUCT._ipbx_announce_ip_address
#define parm__ipbx_call_conference_tone  DATASTRUCT._parm__ipbx_call_conference_tone
#define rd_laston_cnt                    DATASTRUCT._rd_laston_cnt
#define parm__net_lan_user_name          DATASTRUCT._parm__net_lan_user_name
#define v34_rx_trellis_old_scores        DATASTRUCT._v34_rx_trellis_old_scores
#define asm_encode_rtp_start             DATASTRUCT._asm_encode_rtp_start
#define equalizer_slew_slow              DATASTRUCT._equalizer_slew_slow
#define parm__ipbx_distinctive_ring_list DATASTRUCT._parm__ipbx_distinctive_ring_list
#define ph2n_probing_Gr_exponent         DATASTRUCT._ph2n_probing_Gr_exponent
#define v92n_rx_prefilter_exponent       DATASTRUCT._v92n_rx_prefilter_exponent
#define v90n_tx_receive_silence_option   DATASTRUCT._v90n_tx_receive_silence_option
#define g726_dec_bit_number              DATASTRUCT._g726_dec_bit_number
#define PCM_LEN_8K0_EQC_TRN1A_4TH        DATASTRUCT._PCM_LEN_8K0_EQC_TRN1A_4TH
#define within_bg_state_update           DATASTRUCT._within_bg_state_update
#define v90_rx_rate_reduction_counter    DATASTRUCT._v90_rx_rate_reduction_counter
#define v34_frame_rx_residue             DATASTRUCT._v34_frame_rx_residue
#define V34S_RENEG_INIT_T_S_TO_SN_TIMEOUT DATASTRUCT._V34S_RENEG_INIT_T_S_TO_SN_TIMEOUT
#define l_twid_idx                       DATASTRUCT._l_twid_idx
#define going_down                       DATASTRUCT._going_down
#define fsk_previous_exp                 DATASTRUCT._fsk_previous_exp
#define lec__holding_poffset             DATASTRUCT._lec__holding_poffset
#define v17_diagnostics_mse_sum          DATASTRUCT._v17_diagnostics_mse_sum
#define impedance_monitor_rx_speech_detected DATASTRUCT._impedance_monitor_rx_speech_detected
#define parm__ipbx_no_answer_forward_dial_string DATASTRUCT._parm__ipbx_no_answer_forward_dial_string
#define parm__ata_lcd_menu_protect_enable DATASTRUCT._parm__ata_lcd_menu_protect_enable
#define impedance_monitor_rx_in_offset   DATASTRUCT._impedance_monitor_rx_in_offset
#define noise_generator_bpf_data         DATASTRUCT._noise_generator_bpf_data
#define v34_tx_yn_remote_imag            DATASTRUCT._v34_tx_yn_remote_imag
#define v90n_tx_training_data_rate       DATASTRUCT._v90n_tx_training_data_rate
#define parm__dest_rtp_port              DATASTRUCT._parm__dest_rtp_port
#define parm__net_hardware_mac_address   DATASTRUCT._parm__net_hardware_mac_address
#define p18_baud_UVW_real                DATASTRUCT._p18_baud_UVW_real
#define prev_par_syn                     DATASTRUCT._prev_par_syn
#define parm__radio_receiver_squelch_level DATASTRUCT._parm__radio_receiver_squelch_level
#define retrain_count                    DATASTRUCT._retrain_count
#define shadow_ring_count                DATASTRUCT._shadow_ring_count
#define DELTA_REF_LEVEL                  DATASTRUCT._DELTA_REF_LEVEL
#define ipod_msg_rx_payload_size         DATASTRUCT._ipod_msg_rx_payload_size
#define dt_table                         DATASTRUCT._dt_table
#define vppn_device_update_in_progress   DATASTRUCT._vppn_device_update_in_progress
#define parm__pcm_playback_intro_mode    DATASTRUCT._parm__pcm_playback_intro_mode
#define parm__mgcp_local_port            DATASTRUCT._parm__mgcp_local_port
#define parm__fxpmp_preamble_duration    DATASTRUCT._parm__fxpmp_preamble_duration
#define ANSam_trace_magphase_real        DATASTRUCT._ANSam_trace_magphase_real
#define stat__v8__call_function          DATASTRUCT._stat__v8__call_function
#define V34_TXI_TAPS                     DATASTRUCT._V34_TXI_TAPS
#define notch_datay32_060                DATASTRUCT._notch_datay32_060
#define found_CNG_tone                   DATASTRUCT._found_CNG_tone
#define parm__ffsk_dec_enable            DATASTRUCT._parm__ffsk_dec_enable
#define cc_rx_ANAL_ALL_energy_log        DATASTRUCT._cc_rx_ANAL_ALL_energy_log
#define parm__tone_transmit_level        DATASTRUCT._parm__tone_transmit_level
#define faxdet_data_sum_grl              DATASTRUCT._faxdet_data_sum_grl
#define g729_coder_buffer                DATASTRUCT._g729_coder_buffer
#define parm__ipbx_fc_caller_redial_cancel DATASTRUCT._parm__ipbx_fc_caller_redial_cancel
#define v34s_retrigger_renegotiation     DATASTRUCT._v34s_retrigger_renegotiation
#define debug_host_buffer_throttle       DATASTRUCT._debug_host_buffer_throttle
#define v32bis_nearest_group_table_internal_buffer DATASTRUCT._v32bis_nearest_group_table_internal_buffer
#define output_lock_buffer               DATASTRUCT._output_lock_buffer
#define v32_nearest_group_table_internal_buffer DATASTRUCT._v32_nearest_group_table_internal_buffer
#define v90n_tx_apcm_data_rate_option    DATASTRUCT._v90n_tx_apcm_data_rate_option
#define parm__ipbx_tone_gain             DATASTRUCT._parm__ipbx_tone_gain
#define descrambler_output               DATASTRUCT._descrambler_output
#define parm__sdp_g722p2_codec_name      DATASTRUCT._parm__sdp_g722p2_codec_name
#define pcm_rx_statistics_routine        DATASTRUCT._pcm_rx_statistics_routine
#define PCM_EC_OUTPUT_POST_SHIFT         DATASTRUCT._PCM_EC_OUTPUT_POST_SHIFT
#define phase_roll__second_order_term_32 DATASTRUCT._phase_roll__second_order_term_32
#define ph2p_powr_saved_holdoff_I7_offset DATASTRUCT._ph2p_powr_saved_holdoff_I7_offset
#define sdt_angle_store_imag             DATASTRUCT._sdt_angle_store_imag
#define parm__sip_register_authentication DATASTRUCT._parm__sip_register_authentication
#define v90_frame_rx_cp_body_cm          DATASTRUCT._v90_frame_rx_cp_body_cm
#define faxdet_data_ced                  DATASTRUCT._faxdet_data_ced
#define v34h_rx_SWP_value                DATASTRUCT._v34h_rx_SWP_value
#define v34_tx_remote_use_nonlinear      DATASTRUCT._v34_tx_remote_use_nonlinear
#define special_match_nsw                DATASTRUCT._special_match_nsw
#define sonitrol_v34_spp_len_counter     DATASTRUCT._sonitrol_v34_spp_len_counter
#define orig_v8_found_ANSam              DATASTRUCT._orig_v8_found_ANSam
#define parm__transmitter_gain           DATASTRUCT._parm__transmitter_gain
#define precision_cos_value              DATASTRUCT._precision_cos_value
#define pcm_code_segment                 DATASTRUCT._pcm_code_segment
#define htd_dtmf_semaphore               DATASTRUCT._htd_dtmf_semaphore
#define vppn_device_command_send_retry   DATASTRUCT._vppn_device_command_send_retry
#define v90_tx_k_value                   DATASTRUCT._v90_tx_k_value
#define stat__net_current_dns_secondary_address DATASTRUCT._stat__net_current_dns_secondary_address
#define parm__ipbx_led_descriptor        DATASTRUCT._parm__ipbx_led_descriptor
#define parm__ipbx_bridge_security_code_string DATASTRUCT._parm__ipbx_bridge_security_code_string
#define legacy_binary_download_mode      DATASTRUCT._legacy_binary_download_mode
#define sonitrol_audio_edge_detect       DATASTRUCT._sonitrol_audio_edge_detect
#define PCM_BTR_FREQ32                   DATASTRUCT._PCM_BTR_FREQ32
#define V34S_LEN_8K0_PRE_PHASE_CHANGE    DATASTRUCT._V34S_LEN_8K0_PRE_PHASE_CHANGE
#define v34n_parm_cc_data_rate_option    DATASTRUCT._v34n_parm_cc_data_rate_option
#define parm__sip_send_response_to_src_port DATASTRUCT._parm__sip_send_response_to_src_port
#define parm__ipbx_fc_call_waiting_enable_once DATASTRUCT._parm__ipbx_fc_call_waiting_enable_once
#define btrec_p2400_imag                 DATASTRUCT._btrec_p2400_imag
#define v34f_srce_1st_MPh_flag           DATASTRUCT._v34f_srce_1st_MPh_flag
#define ipbx_rled_mask                   DATASTRUCT._ipbx_rled_mask
#define dtmf_clamp_delay                 DATASTRUCT._dtmf_clamp_delay
#define g711a_plc_history_poffset        DATASTRUCT._g711a_plc_history_poffset
#define parm__voip_dtmf_transmit_method  DATASTRUCT._parm__voip_dtmf_transmit_method
#define v34h_tx_I1ij_m                   DATASTRUCT._v34h_tx_I1ij_m
#define v90_dpcm_dil_ucode               DATASTRUCT._v90_dpcm_dil_ucode
#define rx_packet_count                  DATASTRUCT._rx_packet_count
#define equalizer_slew_medium            DATASTRUCT._equalizer_slew_medium
#define bgkernel_current_event           DATASTRUCT._bgkernel_current_event
#define lec__datamax_full_excess         DATASTRUCT._lec__datamax_full_excess
#define asm_pkt_type                     DATASTRUCT._asm_pkt_type
#define sonitrol_ring_count              DATASTRUCT._sonitrol_ring_count
#define v90_rx_retrain_detect_counter    DATASTRUCT._v90_rx_retrain_detect_counter
#define rf_sample_overflow_count         DATASTRUCT._rf_sample_overflow_count
#define wiznet_poll_process              DATASTRUCT._wiznet_poll_process
#define parm__net_debug_level_mgcp       DATASTRUCT._parm__net_debug_level_mgcp
#define encode_frame                     DATASTRUCT._encode_frame
#define parm__ipbx_hookflash_minimum     DATASTRUCT._parm__ipbx_hookflash_minimum
#define parm__handset_rx_gain            DATASTRUCT._parm__handset_rx_gain
#define parm__sip_remote_domain_name     DATASTRUCT._parm__sip_remote_domain_name
#define stat__nat_wan_delivers           DATASTRUCT._stat__nat_wan_delivers
#define cbk_gain_s                       DATASTRUCT._cbk_gain_s
#define v34_pp_correlate_offset          DATASTRUCT._v34_pp_correlate_offset
#define ANSW_LEN_MS_ANSam_CI_SEARCH      DATASTRUCT._ANSW_LEN_MS_ANSam_CI_SEARCH
#define parm__speech_dec_host_flag       DATASTRUCT._parm__speech_dec_host_flag
#define sonitrol_DNIS                    DATASTRUCT._sonitrol_DNIS
#define V34S_FINAL_MPA_SEND_COUNT        DATASTRUCT._V34S_FINAL_MPA_SEND_COUNT
#define v90_tx_k_input_offset            DATASTRUCT._v90_tx_k_input_offset
#define affine_ptloop_real               DATASTRUCT._affine_ptloop_real
#define V92S_LEN_8K0_CPT_HOLDOFF         DATASTRUCT._V92S_LEN_8K0_CPT_HOLDOFF
#define monitor_be2_threshold            DATASTRUCT._monitor_be2_threshold
#define V34_AB_SIGNAL_C8K0_LIMIT         DATASTRUCT._V34_AB_SIGNAL_C8K0_LIMIT
#define ph1_tx_ANSpcm_double_pointer     DATASTRUCT._ph1_tx_ANSpcm_double_pointer
#define parm__cid_data_buffer            DATASTRUCT._parm__cid_data_buffer
#define ph1_tx_ANSpcm_gain               DATASTRUCT._ph1_tx_ANSpcm_gain
#define conv_bpf_clip                    DATASTRUCT._conv_bpf_clip
#define impedance_monitor_decimated_rx   DATASTRUCT._impedance_monitor_decimated_rx
#define parm__sip_response_code_try_backup DATASTRUCT._parm__sip_response_code_try_backup
#define g726_out_buffer                  DATASTRUCT._g726_out_buffer
#define g711a_plc_pitchblen              DATASTRUCT._g711a_plc_pitchblen
#define coder_rate                       DATASTRUCT._coder_rate
#define maximum_first_trn_length         DATASTRUCT._maximum_first_trn_length
#define dtmf_lpf_biquad_data             DATASTRUCT._dtmf_lpf_biquad_data
#define parm__disconnect_tone_cadence_mask DATASTRUCT._parm__disconnect_tone_cadence_mask
#define echo_canceller_display_lt_counter DATASTRUCT._echo_canceller_display_lt_counter
#define v92_rx_decoder_ff_alpha_exp      DATASTRUCT._v92_rx_decoder_ff_alpha_exp
#define V90_TEST_LOG_INPUT_START         DATASTRUCT._V90_TEST_LOG_INPUT_START
#define picp_service                     DATASTRUCT._picp_service
#define parm__net_debug_level_pmp        DATASTRUCT._parm__net_debug_level_pmp
#define sart_tx_size                     DATASTRUCT._sart_tx_size
#define pcm_rx_clock_phase               DATASTRUCT._pcm_rx_clock_phase
#define lec__datamax_full_holdoff        DATASTRUCT._lec__datamax_full_holdoff
#define lec__xx_detect_activity          DATASTRUCT._lec__xx_detect_activity
#define vppn_device_command_queue_overflow DATASTRUCT._vppn_device_command_queue_overflow
#define ORIG_LEN_MS_SILENCE_DETECT       DATASTRUCT._ORIG_LEN_MS_SILENCE_DETECT
#define v29_gain_adjust                  DATASTRUCT._v29_gain_adjust
#define record_sample_tx_pcm             DATASTRUCT._record_sample_tx_pcm
#define ph2p_powr_N_buffer32             DATASTRUCT._ph2p_powr_N_buffer32
#define v90n_tx_coding_law               DATASTRUCT._v90n_tx_coding_law
#define v34n_tx_carrier_frequency        DATASTRUCT._v34n_tx_carrier_frequency
#define dt_data                          DATASTRUCT._dt_data
#define cc_tx_passband_poffset           DATASTRUCT._cc_tx_passband_poffset
#define L_exc_err                        DATASTRUCT._L_exc_err
#define dprmbx_ack_channel               DATASTRUCT._dprmbx_ack_channel
#define v29_rot_equalized_imag           DATASTRUCT._v29_rot_equalized_imag
#define stat__v8__vpcm_availability      DATASTRUCT._stat__v8__vpcm_availability
#define sip_startup_complete             DATASTRUCT._sip_startup_complete
#define asm_encode_sample_pack_mask      DATASTRUCT._asm_encode_sample_pack_mask
#define cc_rx_ANAL_DC_energy_log         DATASTRUCT._cc_rx_ANAL_DC_energy_log
#define v34n_rx_gain_adjust              DATASTRUCT._v34n_rx_gain_adjust
#define equalizer_output_imag            DATASTRUCT._equalizer_output_imag
#define parm__ata_external_web_server_enable DATASTRUCT._parm__ata_external_web_server_enable
#define parm__ata_current_date           DATASTRUCT._parm__ata_current_date
#define parm__slac_caller_id_type_1_mode DATASTRUCT._parm__slac_caller_id_type_1_mode
#define impedance_monitor_detect_holdoff_counter DATASTRUCT._impedance_monitor_detect_holdoff_counter
#define g168_inp_average                 DATASTRUCT._g168_inp_average
#define differential_data                DATASTRUCT._differential_data
#define v34n_tx_use_nonlinear            DATASTRUCT._v34n_tx_use_nonlinear
#define uicp_index                       DATASTRUCT._uicp_index
#define v90_rx_q_table64                 DATASTRUCT._v90_rx_q_table64
#define decode_frame_active_indication   DATASTRUCT._decode_frame_active_indication
#define orig_v8_allow_ANSam              DATASTRUCT._orig_v8_allow_ANSam
#define perfect_real                     DATASTRUCT._perfect_real
#define parm__speech_rtp_jitter_buffer_lock DATASTRUCT._parm__speech_rtp_jitter_buffer_lock
#define v90_rx_dil_tp_mask               DATASTRUCT._v90_rx_dil_tp_mask
#define v92n_tx_MH_indication            DATASTRUCT._v92n_tx_MH_indication
#define p18_lpf_poffset                  DATASTRUCT._p18_lpf_poffset
#define stat__nat_snd_alg_delivers       DATASTRUCT._stat__nat_snd_alg_delivers
#define parm__ipbx_caller_id_inbound_enable DATASTRUCT._parm__ipbx_caller_id_inbound_enable
#define cp_detected                      DATASTRUCT._cp_detected
#define retrain_counter                  DATASTRUCT._retrain_counter
#define cod_vad_enable                   DATASTRUCT._cod_vad_enable
#define impedance_monitor_decimated_tx   DATASTRUCT._impedance_monitor_decimated_tx
#define parm__sart_tx_mode               DATASTRUCT._parm__sart_tx_mode
#define fsk_TONE_counter                 DATASTRUCT._fsk_TONE_counter
#define lec__best_erl_buffer             DATASTRUCT._lec__best_erl_buffer
#define stat__mgcp_controller_local_contact_port DATASTRUCT._stat__mgcp_controller_local_contact_port
#define pcm_rx_8K0_ph34_routine          DATASTRUCT._pcm_rx_8K0_ph34_routine
#define parm__ata_hardware_revision      DATASTRUCT._parm__ata_hardware_revision
#define postHPFInHis                     DATASTRUCT._postHPFInHis
#define cc_rx_ANAL_coef_imag             DATASTRUCT._cc_rx_ANAL_coef_imag
#define nat_timer                        DATASTRUCT._nat_timer
#define parm__nat_address_port_block     DATASTRUCT._parm__nat_address_port_block
#define parm__sip_options_authentication DATASTRUCT._parm__sip_options_authentication
#define v90_tx_s_frame                   DATASTRUCT._v90_tx_s_frame
#define angle_1st_data_input             DATASTRUCT._angle_1st_data_input
#define v32_rx_lpf_coefs_internal_buffer DATASTRUCT._v32_rx_lpf_coefs_internal_buffer
#define overlay_ph2_to_v34               DATASTRUCT._overlay_ph2_to_v34
#define v34_resync_min_index             DATASTRUCT._v34_resync_min_index
#define v92n_tx_train_8pt_option         DATASTRUCT._v92n_tx_train_8pt_option
#define parm__hw_rx_gain_correction      DATASTRUCT._parm__hw_rx_gain_correction
#define v34f_srce_requests_restart       DATASTRUCT._v34f_srce_requests_restart
#define parm__overall_operating_mode     DATASTRUCT._parm__overall_operating_mode
#define rx_call_to_answer_new_maxrate    DATASTRUCT._rx_call_to_answer_new_maxrate
#define parm__dm_v34_options_mask        DATASTRUCT._parm__dm_v34_options_mask
#define parm__pcm_playback_once_size     DATASTRUCT._parm__pcm_playback_once_size
#define v34_tx_local_gain_adjust         DATASTRUCT._v34_tx_local_gain_adjust
#define v34_rx_yn_perfect_real32         DATASTRUCT._v34_rx_yn_perfect_real32
#define ph4n_tx_receive_qn_coef_imag     DATASTRUCT._ph4n_tx_receive_qn_coef_imag
#define v34_tx_preemph_gain_adjust       DATASTRUCT._v34_tx_preemph_gain_adjust
#define detect_v21_detect_lpf2_32        DATASTRUCT._detect_v21_detect_lpf2_32
#define v34n_tx_symbol_option            DATASTRUCT._v34n_tx_symbol_option
#define dcdelout_hi                      DATASTRUCT._dcdelout_hi
#define v34n_tx_auxiliary_channel        DATASTRUCT._v34n_tx_auxiliary_channel
#define tim_sart_semaphore               DATASTRUCT._tim_sart_semaphore
#define ata_call_record_channel          DATASTRUCT._ata_call_record_channel
#define parm__speech_dec_host_addr       DATASTRUCT._parm__speech_dec_host_addr
#define V34S_LEN_8K0_MIN_LOCAL_TRAIN     DATASTRUCT._V34S_LEN_8K0_MIN_LOCAL_TRAIN
#define parm__dm_v34_data_rate_mask      DATASTRUCT._parm__dm_v34_data_rate_mask
#define v92n_rx_prefilter_gain_x4        DATASTRUCT._v92n_rx_prefilter_gain_x4
#define tonemute_sum_rx                  DATASTRUCT._tonemute_sum_rx
#define parm__audio_input                DATASTRUCT._parm__audio_input
#define lec__nlp_cng_offset_decrement    DATASTRUCT._lec__nlp_cng_offset_decrement
#define stat__disconnect_tone_tone_detect_mask DATASTRUCT._stat__disconnect_tone_tone_detect_mask
#define parm__ipbx_outgoing_block_list   DATASTRUCT._parm__ipbx_outgoing_block_list
#define stat__ipod_debug_enabled         DATASTRUCT._stat__ipod_debug_enabled
#define nat_pkt_mac_ptr                  DATASTRUCT._nat_pkt_mac_ptr
#define cp_change                        DATASTRUCT._cp_change
#define g729_test_uncompressed_data      DATASTRUCT._g729_test_uncompressed_data
#define pcm_rx_TRN2A_log_energy          DATASTRUCT._pcm_rx_TRN2A_log_energy
#define v34_pnt3_MSE_stack               DATASTRUCT._v34_pnt3_MSE_stack
#define ac97_dma_tx_irq                  DATASTRUCT._ac97_dma_tx_irq
#define pcm_rx_sequence_detect_routine   DATASTRUCT._pcm_rx_sequence_detect_routine
#define g711_rx_vad_peak_mean            DATASTRUCT._g711_rx_vad_peak_mean
#define parm__selcall_enc_tone_set       DATASTRUCT._parm__selcall_enc_tone_set
#define parm__ipbx_red_priority_table    DATASTRUCT._parm__ipbx_red_priority_table
#define sart_rx_write_index              DATASTRUCT._sart_rx_write_index
#define stat__nat_rcv_delivers           DATASTRUCT._stat__nat_rcv_delivers
#define ph2p_anal_flatvar                DATASTRUCT._ph2p_anal_flatvar
#define ph2p_anal_variance_03_table      DATASTRUCT._ph2p_anal_variance_03_table
#define ph2n_rx_train_16pt               DATASTRUCT._ph2n_rx_train_16pt
#define stat__mgcp_is_registered         DATASTRUCT._stat__mgcp_is_registered
#define v90_tx_dil_count                 DATASTRUCT._v90_tx_dil_count
#define g729_sync_debug                  DATASTRUCT._g729_sync_debug
#define data_14k4_lookup_internal_buffer DATASTRUCT._data_14k4_lookup_internal_buffer
#define dcd_energy_y_select              DATASTRUCT._dcd_energy_y_select
#define prev_uv_sc_ana                   DATASTRUCT._prev_uv_sc_ana
#define parm__sip_tos_value              DATASTRUCT._parm__sip_tos_value
#define v34_rx_zn_hat_real               DATASTRUCT._v34_rx_zn_hat_real
#define lec__td_update                   DATASTRUCT._lec__td_update
#define parm__dm_v34_mse_fallback        DATASTRUCT._parm__dm_v34_mse_fallback
#define bulk_delay_buffer_size           DATASTRUCT._bulk_delay_buffer_size
#define ata_sample_record_size           DATASTRUCT._ata_sample_record_size
#define v92n_parm_sh2_enable             DATASTRUCT._v92n_parm_sh2_enable
#define V34_MD_LENGTH_INCREMENT          DATASTRUCT._V34_MD_LENGTH_INCREMENT
#define dtmf_unclamp_detect              DATASTRUCT._dtmf_unclamp_detect
#define lpres_delout                     DATASTRUCT._lpres_delout
#define ph2n_tx_preemph                  DATASTRUCT._ph2n_tx_preemph
#define dt_previous                      DATASTRUCT._dt_previous
#define v34_pp_result_ang_table          DATASTRUCT._v34_pp_result_ang_table
#define rx_rd_index                      DATASTRUCT._rx_rd_index
#define pcm_rx_TRN2A_log_energy_ratio    DATASTRUCT._pcm_rx_TRN2A_log_energy_ratio
#define v90_tx_residue_length            DATASTRUCT._v90_tx_residue_length
#define pcm_16K_rx_sample                DATASTRUCT._pcm_16K_rx_sample
#define cc_rx_energy_delay_poffset       DATASTRUCT._cc_rx_energy_delay_poffset
#define parm__ipbx_fxo_cid_after_ring    DATASTRUCT._parm__ipbx_fxo_cid_after_ring
#define delta_t                          DATASTRUCT._delta_t
#define parm__ata_firmware_update_periodic_delay DATASTRUCT._parm__ata_firmware_update_periodic_delay
#define parm__decoder_prev_mode          DATASTRUCT._parm__decoder_prev_mode
#define ph2p_anal_maxrates_15_table      DATASTRUCT._ph2p_anal_maxrates_15_table
#define ph2p_powr_temp_x_buffer          DATASTRUCT._ph2p_powr_temp_x_buffer
#define dt_output                        DATASTRUCT._dt_output
#define parm__speech_rtp_ans_send_cnt    DATASTRUCT._parm__speech_rtp_ans_send_cnt
#define ph2n_rx_3429_option              DATASTRUCT._ph2n_rx_3429_option
#define parm__speech_dec_slot_size       DATASTRUCT._parm__speech_dec_slot_size
#define v34s_special_local_train_shift_slew DATASTRUCT._v34s_special_local_train_shift_slew
#define sonitrol_remote_audio_ip         DATASTRUCT._sonitrol_remote_audio_ip
#define silence_threshold                DATASTRUCT._silence_threshold
#define tmp_lpc                          DATASTRUCT._tmp_lpc
#define ph1n_tx_index_QTS                DATASTRUCT._ph1n_tx_index_QTS
#define stat__vpcm_digital_mode          DATASTRUCT._stat__vpcm_digital_mode
#define v92_rx_decoder_ff_error          DATASTRUCT._v92_rx_decoder_ff_error
#define parm__codec_ring_detect_method   DATASTRUCT._parm__codec_ring_detect_method
#define stat__nat_wan_broadcast          DATASTRUCT._stat__nat_wan_broadcast
#define v90n_tx_train_16pt_option        DATASTRUCT._v90n_tx_train_16pt_option
#define v34_pnt0_MSE_stack               DATASTRUCT._v34_pnt0_MSE_stack
#define v92n_parm_rx_train_8pt_option    DATASTRUCT._v92n_parm_rx_train_8pt_option
#define lec__best_erl_poffset            DATASTRUCT._lec__best_erl_poffset
#define parm__nat_l2tp_enable            DATASTRUCT._parm__nat_l2tp_enable
#define phase_adjust                     DATASTRUCT._phase_adjust
#define ph2p_anal_preemph_index          DATASTRUCT._ph2p_anal_preemph_index
#define vppn_device_firmware_checksum    DATASTRUCT._vppn_device_firmware_checksum
#define v34_slew_sin_BE                  DATASTRUCT._v34_slew_sin_BE
#define datamaxoffset                    DATASTRUCT._datamaxoffset
#define tone_priority_gen_index          DATASTRUCT._tone_priority_gen_index
#define cp_data                          DATASTRUCT._cp_data
#define trcval                           DATASTRUCT._trcval
#define stat__dm_v90_enable              DATASTRUCT._stat__dm_v90_enable
#define p18_lpf_buffer_imag              DATASTRUCT._p18_lpf_buffer_imag
#define v90_frame_rx_parse_routine       DATASTRUCT._v90_frame_rx_parse_routine
#define parm__dtmf_wait_duration         DATASTRUCT._parm__dtmf_wait_duration
#define tone_detector_slew_rate          DATASTRUCT._tone_detector_slew_rate
#define lec__nlp_detect_loose            DATASTRUCT._lec__nlp_detect_loose
#define v34_rx_yn_error_imag_32          DATASTRUCT._v34_rx_yn_error_imag_32
#define v8_rx_state                      DATASTRUCT._v8_rx_state
#define v92n_tx_CPd_body_word            DATASTRUCT._v92n_tx_CPd_body_word
#define ph2p_powr_L1_spectrum_power_buffer32 DATASTRUCT._ph2p_powr_L1_spectrum_power_buffer32
#define v17_diagnostics_mse_log          DATASTRUCT._v17_diagnostics_mse_log
#define current_crc                      DATASTRUCT._current_crc
#define ph2_rx_checker_bpf_coef_pointer  DATASTRUCT._ph2_rx_checker_bpf_coef_pointer
#define v92_system_ID_energy_rbs         DATASTRUCT._v92_system_ID_energy_rbs
#define ph2_tx_rate_conv_9K6_8K0_pointer DATASTRUCT._ph2_tx_rate_conv_9K6_8K0_pointer
#define v90n_rx_INFO0d_body              DATASTRUCT._v90n_rx_INFO0d_body
#define V34_QN_UPDATE_FAST_SLEW          DATASTRUCT._V34_QN_UPDATE_FAST_SLEW
#define parm__speech_audio_frame_cnt     DATASTRUCT._parm__speech_audio_frame_cnt
#define circb_min                        DATASTRUCT._circb_min
#define parm__mgcp_rtp_public_external_ip_address DATASTRUCT._parm__mgcp_rtp_public_external_ip_address
#define parm__ata_am_pm_display_enable   DATASTRUCT._parm__ata_am_pm_display_enable
#define baud_hdlc_frame_start_indicator  DATASTRUCT._baud_hdlc_frame_start_indicator
#define stat__slac_revision              DATASTRUCT._stat__slac_revision
#define first_gear_change_period         DATASTRUCT._first_gear_change_period
#define dcdelout_lo                      DATASTRUCT._dcdelout_lo
#define sdt_hit_counter                  DATASTRUCT._sdt_hit_counter
#define v34_resync_data_offset           DATASTRUCT._v34_resync_data_offset
#define cid_data_seen                    DATASTRUCT._cid_data_seen
#define v90_shape_shift_count            DATASTRUCT._v90_shape_shift_count
#define tone_pattern_gen_count           DATASTRUCT._tone_pattern_gen_count
#define parm__sip_nat_keep_alive_message DATASTRUCT._parm__sip_nat_keep_alive_message
#define sonitrol_unexpected_disconnect   DATASTRUCT._sonitrol_unexpected_disconnect
#define ipod_msg_tx_digit_pair           DATASTRUCT._ipod_msg_tx_digit_pair
#define parm__speech_dec_frame_rate      DATASTRUCT._parm__speech_dec_frame_rate
#define parm__net_debug_level_ata        DATASTRUCT._parm__net_debug_level_ata
#define parm__ipbx_station_call_waiting_tone_default DATASTRUCT._parm__ipbx_station_call_waiting_tone_default
#define monitor_sample_agc_2_target      DATASTRUCT._monitor_sample_agc_2_target
#define TILT_FACTOR0                     DATASTRUCT._TILT_FACTOR0
#define ipod_timer                       DATASTRUCT._ipod_timer
#define fsk_gain_adjust                  DATASTRUCT._fsk_gain_adjust
#define v92n_tx_constel_points           DATASTRUCT._v92n_tx_constel_points
#define l_prev_ncof                      DATASTRUCT._l_prev_ncof
#define vppn_device_firmware_update      DATASTRUCT._vppn_device_firmware_update
#define retrain_imag                     DATASTRUCT._retrain_imag
#define v34_BE_log_Gn_prev               DATASTRUCT._v34_BE_log_Gn_prev
#define pcm_ctl_use_pcm_DC_offset_value  DATASTRUCT._pcm_ctl_use_pcm_DC_offset_value
#define ph2_data_timeout_start           DATASTRUCT._ph2_data_timeout_start
#define decode_frame_concealment_indication DATASTRUCT._decode_frame_concealment_indication
#define ph2p_anal_maxrate_results_pointer DATASTRUCT._ph2p_anal_maxrate_results_pointer
#define nat_triggered_list               DATASTRUCT._nat_triggered_list
#define dcd_diversion                    DATASTRUCT._dcd_diversion
#define g722_e4l_al1                     DATASTRUCT._g722_e4l_al1
#define g722_e4l_al2                     DATASTRUCT._g722_e4l_al2
#define lsd_recovery_rlsd_state          DATASTRUCT._lsd_recovery_rlsd_state
#define l_prev_gain                      DATASTRUCT._l_prev_gain
#define parm__sip_max_forwards           DATASTRUCT._parm__sip_max_forwards
#define ph2s_orig_INFO1_counter          DATASTRUCT._ph2s_orig_INFO1_counter
#define fax_error_mse_limit              DATASTRUCT._fax_error_mse_limit
#define remote_interpolator_buffer_real  DATASTRUCT._remote_interpolator_buffer_real
#define ph2p_fefo_delta_buffer_hertz32   DATASTRUCT._ph2p_fefo_delta_buffer_hertz32
#define ase_del                          DATASTRUCT._ase_del
#define cc_rx_spectrum_result_table32_real DATASTRUCT._cc_rx_spectrum_result_table32_real
#define stat__nat_wan_ip_forward         DATASTRUCT._stat__nat_wan_ip_forward
#define stat__g168_faxdet_detect_value   DATASTRUCT._stat__g168_faxdet_detect_value
#define parm__slac_port_spkr_gain        DATASTRUCT._parm__slac_port_spkr_gain
#define bulk_delay_buffer                DATASTRUCT._bulk_delay_buffer
#define pcm_rx_8K0_divisor_flag_ph3      DATASTRUCT._pcm_rx_8K0_divisor_flag_ph3
#define btrec_rx_phase_first_low         DATASTRUCT._btrec_rx_phase_first_low
#define parm__vppn_device_firmware_address DATASTRUCT._parm__vppn_device_firmware_address
#define line_rx_overflow                 DATASTRUCT._line_rx_overflow
#define stat__speech_dec_mbx_cnt         DATASTRUCT._stat__speech_dec_mbx_cnt
#define v34_yn_error_imag                DATASTRUCT._v34_yn_error_imag
#define bg_kernel                        DATASTRUCT._bg_kernel
#define ph2n_rx_pcm_3429_option          DATASTRUCT._ph2n_rx_pcm_3429_option
#define stat__faxdet_detect_value        DATASTRUCT._stat__faxdet_detect_value
#define parm__ipbx_disturb_accept_last_call_service DATASTRUCT._parm__ipbx_disturb_accept_last_call_service
#define ph2_AB_detect_enable             DATASTRUCT._ph2_AB_detect_enable
#define v34_tx_yn_imag                   DATASTRUCT._v34_tx_yn_imag
#define stat__nat_snd_discards           DATASTRUCT._stat__nat_snd_discards
#define ph2_scale_value                  DATASTRUCT._ph2_scale_value
#define lspSid                           DATASTRUCT._lspSid
#define faxdet_threshold_ced             DATASTRUCT._faxdet_threshold_ced
#define stat__nat_rcv_ttl_discard        DATASTRUCT._stat__nat_rcv_ttl_discard
#define v90n_rx_dpcm_data_rate_option    DATASTRUCT._v90n_rx_dpcm_data_rate_option
#define cc_tx_rate_buffer                DATASTRUCT._cc_tx_rate_buffer
#define v34s_gear_change_period          DATASTRUCT._v34s_gear_change_period
#define v27_tx_guard_flag                DATASTRUCT._v27_tx_guard_flag
#define pcm_digital_pad_table            DATASTRUCT._pcm_digital_pad_table
#define parm__net_syslog_enable          DATASTRUCT._parm__net_syslog_enable
#define parm__codec_disconnect_silence_enable DATASTRUCT._parm__codec_disconnect_silence_enable
#define ph2n_probing_receive_agc2_level  DATASTRUCT._ph2n_probing_receive_agc2_level
#define stat__sip_global_keep_alive_domain_name DATASTRUCT._stat__sip_global_keep_alive_domain_name
#define faxparm_parm__silence_duration   DATASTRUCT._faxparm_parm__silence_duration
#define PH2P_ANAL_CENTER_ENERGY_WEIGHT   DATASTRUCT._PH2P_ANAL_CENTER_ENERGY_WEIGHT
#define encode_gain_linear               DATASTRUCT._encode_gain_linear
#define parm__reset_flag                 DATASTRUCT._parm__reset_flag
#define parm__ipbx_fc_blocked_number_enable DATASTRUCT._parm__ipbx_fc_blocked_number_enable
#define stat__nat_wan_ip_fragment        DATASTRUCT._stat__nat_wan_ip_fragment
#define v34n_rx_trellis_setting          DATASTRUCT._v34n_rx_trellis_setting
#define measured_bulk_delay              DATASTRUCT._measured_bulk_delay
#define impedance_monitor_tx_data        DATASTRUCT._impedance_monitor_tx_data
#define parm__ipbx_three_way_calling_service DATASTRUCT._parm__ipbx_three_way_calling_service
#define ph3n_rx_shaping_lookahead        DATASTRUCT._ph3n_rx_shaping_lookahead
#define V90_RX_Sd_DETECT_LIMIT           DATASTRUCT._V90_RX_Sd_DETECT_LIMIT
#define parm__dm_v92_mse_trn_bias        DATASTRUCT._parm__dm_v92_mse_trn_bias
#define pcm_eq_ep_slews                  DATASTRUCT._pcm_eq_ep_slews
#define v34_rx_yn_perfect_imag32         DATASTRUCT._v34_rx_yn_perfect_imag32
#define parm__speech_mac_src_addr        DATASTRUCT._parm__speech_mac_src_addr
#define bg_event_remove                  DATASTRUCT._bg_event_remove
#define parm__speech_g729octet_bitrev    DATASTRUCT._parm__speech_g729octet_bitrev
#define pcm_rx_8K0_data_routine          DATASTRUCT._pcm_rx_8K0_data_routine
#define stat__v8__modulation_modes       DATASTRUCT._stat__v8__modulation_modes
#define parm__radio_channel_selection    DATASTRUCT._parm__radio_channel_selection
#define parm__tone_generators            DATASTRUCT._parm__tone_generators
#define picp_history                     DATASTRUCT._picp_history
#define stat__speech_dec_mode            DATASTRUCT._stat__speech_dec_mode
#define sonitrol_panel_group_id          DATASTRUCT._sonitrol_panel_group_id
#define v34_temp_lo_hi_pre_equalizer_coefs DATASTRUCT._v34_temp_lo_hi_pre_equalizer_coefs
#define phone_handset_tx_volume          DATASTRUCT._phone_handset_tx_volume
#define gpf_LLadj                        DATASTRUCT._gpf_LLadj
#define v92_rx_slot_counter              DATASTRUCT._v92_rx_slot_counter
#define v90_rx_shaper_state              DATASTRUCT._v90_rx_shaper_state
#define tone_pattern_flag                DATASTRUCT._tone_pattern_flag
#define v34_TRN2_MSE_rate_value          DATASTRUCT._v34_TRN2_MSE_rate_value
#define stat__speech_rtp_generic_info    DATASTRUCT._stat__speech_rtp_generic_info
#define line_tx_buffer_element           DATASTRUCT._line_tx_buffer_element
#define g711_rx_dtx_counter              DATASTRUCT._g711_rx_dtx_counter
#define mgcp_parser_message              DATASTRUCT._mgcp_parser_message
#define demod_leading_half_real          DATASTRUCT._demod_leading_half_real
#define v34_frame_rx_bit_parse_pointer_bits DATASTRUCT._v34_frame_rx_bit_parse_pointer_bits
#define data_7k2_lookup_internal_buffer  DATASTRUCT._data_7k2_lookup_internal_buffer
#define stat__phone_zeroize_state        DATASTRUCT._stat__phone_zeroize_state
#define v90_rx_S_send_flag               DATASTRUCT._v90_rx_S_send_flag
#define rd_period_cnt                    DATASTRUCT._rd_period_cnt
#define parm__sart_rx_release_threshold  DATASTRUCT._parm__sart_rx_release_threshold
#define tone_pattern_series              DATASTRUCT._tone_pattern_series
#define op_state                         DATASTRUCT._op_state
#define parm__ipbx_bridge_autoanswer_any_enable DATASTRUCT._parm__ipbx_bridge_autoanswer_any_enable
#define vala                             DATASTRUCT._vala
#define valb                             DATASTRUCT._valb
#define current_bg_state_active          DATASTRUCT._current_bg_state_active
#define valc                             DATASTRUCT._valc
#define vald                             DATASTRUCT._vald
#define parm__melp_rate                  DATASTRUCT._parm__melp_rate
#define double_echo0                     DATASTRUCT._double_echo0
#define double_echo1                     DATASTRUCT._double_echo1
#define asm_encode_within_frame          DATASTRUCT._asm_encode_within_frame
#define ata_sample_record_channel        DATASTRUCT._ata_sample_record_channel
#define v34s_apply_agc_1                 DATASTRUCT._v34s_apply_agc_1
#define parm__ipbx_call_back_ring_tone   DATASTRUCT._parm__ipbx_call_back_ring_tone
#define dcdelin                          DATASTRUCT._dcdelin
#define ORIG_V8_CJ_COUNT_MIN             DATASTRUCT._ORIG_V8_CJ_COUNT_MIN
#define parm__speech_ip_fragment_offset  DATASTRUCT._parm__speech_ip_fragment_offset
#define shadow_franchise_label           DATASTRUCT._shadow_franchise_label
#define sonitrol_v34_plus_counter        DATASTRUCT._sonitrol_v34_plus_counter
#define parm__report_status_mask         DATASTRUCT._parm__report_status_mask
#define parm__ipbx_bridge_autoanswer_enable DATASTRUCT._parm__ipbx_bridge_autoanswer_enable
#define parm__ipbx_outgoing_block_enable DATASTRUCT._parm__ipbx_outgoing_block_enable
#define faxdet_ansam_dropout_count       DATASTRUCT._faxdet_ansam_dropout_count
#define phasedet_complex_value           DATASTRUCT._phasedet_complex_value
#define DIL_probing_pad_mse_log          DATASTRUCT._DIL_probing_pad_mse_log
#define equalizer_buffer_complex         DATASTRUCT._equalizer_buffer_complex
#define circb                            DATASTRUCT._circb
#define fsk_processing_mode              DATASTRUCT._fsk_processing_mode
#define stat__speech_ip_header_checksum  DATASTRUCT._stat__speech_ip_header_checksum
#define parm__net_unique_device_id       DATASTRUCT._parm__net_unique_device_id
#define send__v8__modulation_modes       DATASTRUCT._send__v8__modulation_modes
#define parm__mgcp_sdp_session_owner     DATASTRUCT._parm__mgcp_sdp_session_owner
#define equalizer_coef_imag              DATASTRUCT._equalizer_coef_imag
#define ph2n_rx_carrier_s3429            DATASTRUCT._ph2n_rx_carrier_s3429
#define oicp_saved_digit                 DATASTRUCT._oicp_saved_digit
#define parm__ata_firmware_update_error_retry_delay DATASTRUCT._parm__ata_firmware_update_error_retry_delay
#define v34h_tx_state                    DATASTRUCT._v34h_tx_state
#define v34n_parm_trellis_option         DATASTRUCT._v34n_parm_trellis_option
#define ph2n_probing_L1_SE_power_adjust  DATASTRUCT._ph2n_probing_L1_SE_power_adjust
#define dtmf_mode_semaphore              DATASTRUCT._dtmf_mode_semaphore
#define g_rate                           DATASTRUCT._g_rate
#define v90_frame_rx_dil_body_ref        DATASTRUCT._v90_frame_rx_dil_body_ref
#define v34n_parm_nonlinear_option       DATASTRUCT._v34n_parm_nonlinear_option
#define v34h_rx_Qn_1st_2D                DATASTRUCT._v34h_rx_Qn_1st_2D
#define parm__ipbx_default_feature_code_service DATASTRUCT._parm__ipbx_default_feature_code_service
#define g722_d4h_ah1                     DATASTRUCT._g722_d4h_ah1
#define g722_d4h_ah2                     DATASTRUCT._g722_d4h_ah2
#define res2                             DATASTRUCT._res2
#define v34n_tx_train_16pt               DATASTRUCT._v34n_tx_train_16pt
#define parm__ipbx_bridge_fxs_call_enable DATASTRUCT._parm__ipbx_bridge_fxs_call_enable
#define parm__audio_sync_enable          DATASTRUCT._parm__audio_sync_enable
#define PH2P_POWR_RX_CLEAR_INIT          DATASTRUCT._PH2P_POWR_RX_CLEAR_INIT
#define g_next                           DATASTRUCT._g_next
#define v90_rx_dil_sp_cnt                DATASTRUCT._v90_rx_dil_sp_cnt
#define v34h_rx_buffer_load_pointer      DATASTRUCT._v34h_rx_buffer_load_pointer
#define sample_conversion_control        DATASTRUCT._sample_conversion_control
#define fsk_TONE_phase                   DATASTRUCT._fsk_TONE_phase
#define legacy_SPP_nack_count            DATASTRUCT._legacy_SPP_nack_count
#define v24_txd                          DATASTRUCT._v24_txd
#define cp_average_counter               DATASTRUCT._cp_average_counter
#define stat__speech_ip_identifier       DATASTRUCT._stat__speech_ip_identifier
#define v34_resync_min_value             DATASTRUCT._v34_resync_min_value
#define parm__disconnect_tone_cadence_repeat DATASTRUCT._parm__disconnect_tone_cadence_repeat
#define g711_rx_vad_level_mean_lsw       DATASTRUCT._g711_rx_vad_level_mean_lsw
#define parm__vppn_device_temporary_id   DATASTRUCT._parm__vppn_device_temporary_id
#define v90n_tx_reference_point          DATASTRUCT._v90n_tx_reference_point
#define v90_frame_rx_bit_pointer         DATASTRUCT._v90_frame_rx_bit_pointer
#define pcm_8K0_equalized                DATASTRUCT._pcm_8K0_equalized
#define parm__ipbx_pstn_not_available    DATASTRUCT._parm__ipbx_pstn_not_available
#define parm__cp_rd_decimate_cnt         DATASTRUCT._parm__cp_rd_decimate_cnt
#define ipod_tx_v34_status               DATASTRUCT._ipod_tx_v34_status
#define parm__ipbx_visual_message_waiting_service DATASTRUCT._parm__ipbx_visual_message_waiting_service
#define g722_e4h_oldrh                   DATASTRUCT._g722_e4h_oldrh
#define mean_square_error                DATASTRUCT._mean_square_error
#define v92n_rx_v92_enable               DATASTRUCT._v92n_rx_v92_enable
