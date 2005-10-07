(*
 * The contents of this file are subject to the Interbase Public
 * License Version 1.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy
 * of the License at http://www.Inprise.com/IPL.html
 * 
 * Software distributed under the License is distributed on an
 * "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express
 * or implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The content of this file was generated by the Firebird project
 * using the program jrd/codes.epp
 *)
(*
 * 
 * *** WARNING *** - This file is automatically generated by codes.epp - do not edit!
 * 
 *)

const
	gds_facility		= 20;
	gds_err_base		= 335544320;
	gds_err_factor		= 1;
	gds_arg_end		= 0;	(* end of argument list *)
	gds_arg_gds		= 1;	(* generic DSRI status value *)
	gds_arg_string		= 2;	(* string argument *)
	gds_arg_cstring		= 3;	(* count & string argument *)
	gds_arg_number		= 4;	(* numeric argument (long) *)
	gds_arg_interpreted	= 5;	(* interpreted status code (string) *)
	gds_arg_vms		= 6;	(* VAX/VMS status code (long) *)
	gds_arg_unix		= 7;	(* UNIX error code *)
	gds_arg_domain		= 8;	(* Apollo/Domain error code *)
	gds_arg_dos		= 9;	(* MSDOS/OS2 error code *)

	gds_arith_except                     = 335544321;
	gds_bad_dbkey                        = 335544322;
	gds_bad_db_format                    = 335544323;
	gds_bad_db_handle                    = 335544324;
	gds_bad_dpb_content                  = 335544325;
	gds_bad_dpb_form                     = 335544326;
	gds_bad_req_handle                   = 335544327;
	gds_bad_segstr_handle                = 335544328;
	gds_bad_segstr_id                    = 335544329;
	gds_bad_tpb_content                  = 335544330;
	gds_bad_tpb_form                     = 335544331;
	gds_bad_trans_handle                 = 335544332;
	gds_bug_check                        = 335544333;
	gds_convert_error                    = 335544334;
	gds_db_corrupt                       = 335544335;
	gds_deadlock                         = 335544336;
	gds_excess_trans                     = 335544337;
	gds_from_no_match                    = 335544338;
	gds_infinap                          = 335544339;
	gds_infona                           = 335544340;
	gds_infunk                           = 335544341;
	gds_integ_fail                       = 335544342;
	gds_invalid_blr                      = 335544343;
	gds_io_error                         = 335544344;
	gds_lock_conflict                    = 335544345;
	gds_metadata_corrupt                 = 335544346;
	gds_not_valid                        = 335544347;
	gds_no_cur_rec                       = 335544348;
	gds_no_dup                           = 335544349;
	gds_no_finish                        = 335544350;
	gds_no_meta_update                   = 335544351;
	gds_no_priv                          = 335544352;
	gds_no_recon                         = 335544353;
	gds_no_record                        = 335544354;
	gds_no_segstr_close                  = 335544355;
	gds_obsolete_metadata                = 335544356;
	gds_open_trans                       = 335544357;
	gds_port_len                         = 335544358;
	gds_read_only_field                  = 335544359;
	gds_read_only_rel                    = 335544360;
	gds_read_only_trans                  = 335544361;
	gds_read_only_view                   = 335544362;
	gds_req_no_trans                     = 335544363;
	gds_req_sync                         = 335544364;
	gds_req_wrong_db                     = 335544365;
	gds_segment                          = 335544366;
	gds_segstr_eof                       = 335544367;
	gds_segstr_no_op                     = 335544368;
	gds_segstr_no_read                   = 335544369;
	gds_segstr_no_trans                  = 335544370;
	gds_segstr_no_write                  = 335544371;
	gds_segstr_wrong_db                  = 335544372;
	gds_sys_request                      = 335544373;
	gds_stream_eof                       = 335544374;
	gds_unavailable                      = 335544375;
	gds_unres_rel                        = 335544376;
	gds_uns_ext                          = 335544377;
	gds_wish_list                        = 335544378;
	gds_wrong_ods                        = 335544379;
	gds_wronumarg                        = 335544380;
	gds_imp_exc                          = 335544381;
	gds_random                           = 335544382;
	gds_fatal_conflict                   = 335544383;
	gds_badblk                           = 335544384;
	gds_invpoolcl                        = 335544385;
	gds_nopoolids                        = 335544386;
	gds_relbadblk                        = 335544387;
	gds_blktoobig                        = 335544388;
	gds_bufexh                           = 335544389;
	gds_syntaxerr                        = 335544390;
	gds_bufinuse                         = 335544391;
	gds_bdbincon                         = 335544392;
	gds_reqinuse                         = 335544393;
	gds_badodsver                        = 335544394;
	gds_relnotdef                        = 335544395;
	gds_fldnotdef                        = 335544396;
	gds_dirtypage                        = 335544397;
	gds_waifortra                        = 335544398;
	gds_doubleloc                        = 335544399;
	gds_nodnotfnd                        = 335544400;
	gds_dupnodfnd                        = 335544401;
	gds_locnotmar                        = 335544402;
	gds_badpagtyp                        = 335544403;
	gds_corrupt                          = 335544404;
	gds_badpage                          = 335544405;
	gds_badindex                         = 335544406;
	gds_dbbnotzer                        = 335544407;
	gds_tranotzer                        = 335544408;
	gds_trareqmis                        = 335544409;
	gds_badhndcnt                        = 335544410;
	gds_wrotpbver                        = 335544411;
	gds_wroblrver                        = 335544412;
	gds_wrodpbver                        = 335544413;
	gds_blobnotsup                       = 335544414;
	gds_badrelation                      = 335544415;
	gds_nodetach                         = 335544416;
	gds_notremote                        = 335544417;
	gds_trainlim                         = 335544418;
	gds_notinlim                         = 335544419;
	gds_traoutsta                        = 335544420;
	gds_connect_reject                   = 335544421;
	gds_dbfile                           = 335544422;
	gds_orphan                           = 335544423;
	gds_no_lock_mgr                      = 335544424;
	gds_ctxinuse                         = 335544425;
	gds_ctxnotdef                        = 335544426;
	gds_datnotsup                        = 335544427;
	gds_badmsgnum                        = 335544428;
	gds_badparnum                        = 335544429;
	gds_virmemexh                        = 335544430;
	gds_blocking_signal                  = 335544431;
	gds_lockmanerr                       = 335544432;
	gds_journerr                         = 335544433;
	gds_keytoobig                        = 335544434;
	gds_nullsegkey                       = 335544435;
	gds_sqlerr                           = 335544436;
	gds_wrodynver                        = 335544437;
	gds_funnotdef                        = 335544438;
	gds_funmismat                        = 335544439;
	gds_bad_msg_vec                      = 335544440;
	gds_bad_detach                       = 335544441;
	gds_noargacc_read                    = 335544442;
	gds_noargacc_write                   = 335544443;
	gds_read_only                        = 335544444;
	gds_ext_err                          = 335544445;
	gds_non_updatable                    = 335544446;
	gds_no_rollback                      = 335544447;
	gds_bad_sec_info                     = 335544448;
	gds_invalid_sec_info                 = 335544449;
	gds_misc_interpreted                 = 335544450;
	gds_update_conflict                  = 335544451;
	gds_unlicensed                       = 335544452;
	gds_obj_in_use                       = 335544453;
	gds_nofilter                         = 335544454;
	gds_shadow_accessed                  = 335544455;
	gds_invalid_sdl                      = 335544456;
	gds_out_of_bounds                    = 335544457;
	gds_invalid_dimension                = 335544458;
	gds_rec_in_limbo                     = 335544459;
	gds_shadow_missing                   = 335544460;
	gds_cant_validate                    = 335544461;
	gds_cant_start_journal               = 335544462;
	gds_gennotdef                        = 335544463;
	gds_cant_start_logging               = 335544464;
	gds_bad_segstr_type                  = 335544465;
	gds_foreign_key                      = 335544466;
	gds_high_minor                       = 335544467;
	gds_tra_state                        = 335544468;
	gds_trans_invalid                    = 335544469;
	gds_buf_invalid                      = 335544470;
	gds_indexnotdefined                  = 335544471;
	gds_login                            = 335544472;
	gds_invalid_bookmark                 = 335544473;
	gds_bad_lock_level                   = 335544474;
	gds_relation_lock                    = 335544475;
	gds_record_lock                      = 335544476;
	gds_max_idx                          = 335544477;
	gds_jrn_enable                       = 335544478;
	gds_old_failure                      = 335544479;
	gds_old_in_progress                  = 335544480;
	gds_old_no_space                     = 335544481;
	gds_no_wal_no_jrn                    = 335544482;
	gds_num_old_files                    = 335544483;
	gds_wal_file_open                    = 335544484;
	gds_bad_stmt_handle                  = 335544485;
	gds_wal_failure                      = 335544486;
	gds_walw_err                         = 335544487;
	gds_logh_small                       = 335544488;
	gds_logh_inv_version                 = 335544489;
	gds_logh_open_flag                   = 335544490;
	gds_logh_open_flag2                  = 335544491;
	gds_logh_diff_dbname                 = 335544492;
	gds_logf_unexpected_eof              = 335544493;
	gds_logr_incomplete                  = 335544494;
	gds_logr_header_small                = 335544495;
	gds_logb_small                       = 335544496;
	gds_wal_illegal_attach               = 335544497;
	gds_wal_invalid_wpb                  = 335544498;
	gds_wal_err_rollover                 = 335544499;
	gds_no_wal                           = 335544500;
	gds_drop_wal                         = 335544501;
	gds_stream_not_defined               = 335544502;
	gds_wal_subsys_error                 = 335544503;
	gds_wal_subsys_corrupt               = 335544504;
	gds_no_archive                       = 335544505;
	gds_shutinprog                       = 335544506;
	gds_range_in_use                     = 335544507;
	gds_range_not_found                  = 335544508;
	gds_charset_not_found                = 335544509;
	gds_lock_timeout                     = 335544510;
	gds_prcnotdef                        = 335544511;
	gds_prcmismat                        = 335544512;
	gds_wal_bugcheck                     = 335544513;
	gds_wal_cant_expand                  = 335544514;
	gds_codnotdef                        = 335544515;
	gds_xcpnotdef                        = 335544516;
	gds_except                           = 335544517;
	gds_cache_restart                    = 335544518;
	gds_bad_lock_handle                  = 335544519;
	gds_jrn_present                      = 335544520;
	gds_wal_err_rollover2                = 335544521;
	gds_wal_err_logwrite                 = 335544522;
	gds_wal_err_jrn_comm                 = 335544523;
	gds_wal_err_expansion                = 335544524;
	gds_wal_err_setup                    = 335544525;
	gds_must_have_phys_field             = 335544526;
	gds_wal_err_ww_start                 = 335544527;
	gds_shutdown                         = 335544528;
	gds_existing_priv_mod                = 335544529;
	gds_primary_key_ref                  = 335544530;
	gds_primary_key_notnull              = 335544531;
	gds_ref_cnstrnt_notfound             = 335544532;
	gds_foreign_key_notfound             = 335544533;
	gds_ref_cnstrnt_update               = 335544534;
	gds_check_cnstrnt_update             = 335544535;
	gds_check_cnstrnt_del                = 335544536;
	gds_integ_index_seg_del              = 335544537;
	gds_integ_index_seg_mod              = 335544538;
	gds_integ_index_del                  = 335544539;
	gds_integ_index_mod                  = 335544540;
	gds_check_trig_del                   = 335544541;
	gds_check_trig_update                = 335544542;
	gds_cnstrnt_fld_del                  = 335544543;
	gds_cnstrnt_fld_rename               = 335544544;
	gds_rel_cnstrnt_update               = 335544545;
	gds_constaint_on_view                = 335544546;
	gds_invld_cnstrnt_type               = 335544547;
	gds_primary_key_exists               = 335544548;
	gds_systrig_update                   = 335544549;
	gds_not_rel_owner                    = 335544550;
	gds_grant_obj_notfound               = 335544551;
	gds_grant_fld_notfound               = 335544552;
	gds_grant_nopriv                     = 335544553;
	gds_nonsql_security_rel              = 335544554;
	gds_nonsql_security_fld              = 335544555;
	gds_wal_cache_err                    = 335544556;
	gds_shutfail                         = 335544557;
	gds_check_constraint                 = 335544558;
	gds_bad_svc_handle                   = 335544559;
	gds_shutwarn                         = 335544560;
	gds_wrospbver                        = 335544561;
	gds_bad_spb_form                     = 335544562;
	gds_svcnotdef                        = 335544563;
	gds_no_jrn                           = 335544564;
	gds_transliteration_failed           = 335544565;
	gds_start_cm_for_wal                 = 335544566;
	gds_wal_ovflow_log_required          = 335544567;
	gds_text_subtype                     = 335544568;
	gds_dsql_error                       = 335544569;
	gds_dsql_command_err                 = 335544570;
	gds_dsql_constant_err                = 335544571;
	gds_dsql_cursor_err                  = 335544572;
	gds_dsql_datatype_err                = 335544573;
	gds_dsql_decl_err                    = 335544574;
	gds_dsql_cursor_update_err           = 335544575;
	gds_dsql_cursor_open_err             = 335544576;
	gds_dsql_cursor_close_err            = 335544577;
	gds_dsql_field_err                   = 335544578;
	gds_dsql_internal_err                = 335544579;
	gds_dsql_relation_err                = 335544580;
	gds_dsql_procedure_err               = 335544581;
	gds_dsql_request_err                 = 335544582;
	gds_dsql_sqlda_err                   = 335544583;
	gds_dsql_var_count_err               = 335544584;
	gds_dsql_stmt_handle                 = 335544585;
	gds_dsql_function_err                = 335544586;
	gds_dsql_blob_err                    = 335544587;
	gds_collation_not_found              = 335544588;
	gds_collation_not_for_charset        = 335544589;
	gds_dsql_dup_option                  = 335544590;
	gds_dsql_tran_err                    = 335544591;
	gds_dsql_invalid_array               = 335544592;
	gds_dsql_max_arr_dim_exceeded        = 335544593;
	gds_dsql_arr_range_error             = 335544594;
	gds_dsql_trigger_err                 = 335544595;
	gds_dsql_subselect_err               = 335544596;
	gds_dsql_crdb_prepare_err            = 335544597;
	gds_specify_field_err                = 335544598;
	gds_num_field_err                    = 335544599;
	gds_col_name_err                     = 335544600;
	gds_where_err                        = 335544601;
	gds_table_view_err                   = 335544602;
	gds_distinct_err                     = 335544603;
	gds_key_field_count_err              = 335544604;
	gds_subquery_err                     = 335544605;
	gds_expression_eval_err              = 335544606;
	gds_node_err                         = 335544607;
	gds_command_end_err                  = 335544608;
	gds_index_name                       = 335544609;
	gds_exception_name                   = 335544610;
	gds_field_name                       = 335544611;
	gds_token_err                        = 335544612;
	gds_union_err                        = 335544613;
	gds_dsql_construct_err               = 335544614;
	gds_field_aggregate_err              = 335544615;
	gds_field_ref_err                    = 335544616;
	gds_order_by_err                     = 335544617;
	gds_return_mode_err                  = 335544618;
	gds_extern_func_err                  = 335544619;
	gds_alias_conflict_err               = 335544620;
	gds_procedure_conflict_error         = 335544621;
	gds_relation_conflict_err            = 335544622;
	gds_dsql_domain_err                  = 335544623;
	gds_idx_seg_err                      = 335544624;
	gds_node_name_err                    = 335544625;
	gds_table_name                       = 335544626;
	gds_proc_name                        = 335544627;
	gds_idx_create_err                   = 335544628;
	gds_wal_shadow_err                   = 335544629;
	gds_dependency                       = 335544630;
	gds_idx_key_err                      = 335544631;
	gds_dsql_file_length_err             = 335544632;
	gds_dsql_shadow_number_err           = 335544633;
	gds_dsql_token_unk_err               = 335544634;
	gds_dsql_no_relation_alias           = 335544635;
	gds_indexname                        = 335544636;
	gds_no_stream_plan                   = 335544637;
	gds_stream_twice                     = 335544638;
	gds_stream_not_found                 = 335544639;
	gds_collation_requires_text          = 335544640;
	gds_dsql_domain_not_found            = 335544641;
	gds_index_unused                     = 335544642;
	gds_dsql_self_join                   = 335544643;
	gds_stream_bof                       = 335544644;
	gds_stream_crack                     = 335544645;
	gds_db_or_file_exists                = 335544646;
	gds_invalid_operator                 = 335544647;
	gds_conn_lost                        = 335544648;
	gds_bad_checksum                     = 335544649;
	gds_page_type_err                    = 335544650;
	gds_ext_readonly_err                 = 335544651;
	gds_sing_select_err                  = 335544652;
	gds_psw_attach                       = 335544653;
	gds_psw_start_trans                  = 335544654;
	gds_invalid_direction                = 335544655;
	gds_dsql_var_conflict                = 335544656;
	gds_dsql_no_blob_array               = 335544657;
	gds_dsql_base_table                  = 335544658;
	gds_duplicate_base_table             = 335544659;
	gds_view_alias                       = 335544660;
	gds_index_root_page_full             = 335544661;
	gds_dsql_blob_type_unknown           = 335544662;
	gds_req_max_clones_exceeded          = 335544663;
	gds_dsql_duplicate_spec              = 335544664;
	gds_unique_key_violation             = 335544665;
	gds_srvr_version_too_old             = 335544666;
	gds_drdb_completed_with_errs         = 335544667;
	gds_dsql_procedure_use_err           = 335544668;
	gds_dsql_count_mismatch              = 335544669;
	gds_blob_idx_err                     = 335544670;
	gds_array_idx_err                    = 335544671;
	gds_key_field_err                    = 335544672;
	gds_no_delete                        = 335544673;
	gds_del_last_field                   = 335544674;
	gds_sort_err                         = 335544675;
	gds_sort_mem_err                     = 335544676;
	gds_version_err                      = 335544677;
	gds_inval_key_posn                   = 335544678;
	gds_no_segments_err                  = 335544679;
	gds_crrp_data_err                    = 335544680;
	gds_rec_size_err                     = 335544681;
	gds_dsql_field_ref                   = 335544682;
	gds_req_depth_exceeded               = 335544683;
	gds_no_field_access                  = 335544684;
	gds_no_dbkey                         = 335544685;
	gds_jrn_format_err                   = 335544686;
	gds_jrn_file_full                    = 335544687;
	gds_dsql_open_cursor_request         = 335544688;
	gds_ib_error                         = 335544689;
	gds_cache_redef                      = 335544690;
	gds_cache_too_small                  = 335544691;
	gds_log_redef                        = 335544692;
	gds_log_too_small                    = 335544693;
	gds_partition_too_small              = 335544694;
	gds_partition_not_supp               = 335544695;
	gds_log_length_spec                  = 335544696;
	gds_precision_err                    = 335544697;
	gds_scale_nogt                       = 335544698;
	gds_expec_short                      = 335544699;
	gds_expec_long                       = 335544700;
	gds_expec_ushort                     = 335544701;
	gds_like_escape_invalid              = 335544702;
	gds_svcnoexe                         = 335544703;
	gds_net_lookup_err                   = 335544704;
	gds_service_unknown                  = 335544705;
	gds_host_unknown                     = 335544706;
	gds_grant_nopriv_on_base             = 335544707;
	gds_dyn_fld_ambiguous                = 335544708;
	gds_dsql_agg_ref_err                 = 335544709;
	gds_complex_view                     = 335544710;
	gds_unprepared_stmt                  = 335544711;
	gds_expec_positive                   = 335544712;
	gds_dsql_sqlda_value_err             = 335544713;
	gds_invalid_array_id                 = 335544714;
	gds_extfile_uns_op                   = 335544715;
	gds_svc_in_use                       = 335544716;
	gds_err_stack_limit                  = 335544717;
	gds_invalid_key                      = 335544718;
	gds_net_init_error                   = 335544719;
	gds_loadlib_failure                  = 335544720;
	gds_network_error                    = 335544721;
	gds_net_connect_err                  = 335544722;
	gds_net_connect_listen_err           = 335544723;
	gds_net_event_connect_err            = 335544724;
	gds_net_event_listen_err             = 335544725;
	gds_net_read_err                     = 335544726;
	gds_net_write_err                    = 335544727;
	gds_integ_index_deactivate           = 335544728;
	gds_integ_deactivate_primary         = 335544729;
	gds_cse_not_supported                = 335544730;
	gds_tra_must_sweep                   = 335544731;
	gds_unsupported_network_drive        = 335544732;
	gds_io_create_err                    = 335544733;
	gds_io_open_err                      = 335544734;
	gds_io_close_err                     = 335544735;
	gds_io_read_err                      = 335544736;
	gds_io_write_err                     = 335544737;
	gds_io_delete_err                    = 335544738;
	gds_io_access_err                    = 335544739;
	gds_udf_exception                    = 335544740;
	gds_lost_db_connection               = 335544741;
	gds_no_write_user_priv               = 335544742;
	gds_token_too_long                   = 335544743;
	gds_max_att_exceeded                 = 335544744;
	gds_login_same_as_role_name          = 335544745;
	gds_reftable_requires_pk             = 335544746;
	gds_usrname_too_long                 = 335544747;
	gds_password_too_long                = 335544748;
	gds_usrname_required                 = 335544749;
	gds_password_required                = 335544750;
	gds_bad_protocol                     = 335544751;
	gds_dup_usrname_found                = 335544752;
	gds_usrname_not_found                = 335544753;
	gds_error_adding_sec_record          = 335544754;
	gds_error_modifying_sec_record       = 335544755;
	gds_error_deleting_sec_record        = 335544756;
	gds_error_updating_sec_db            = 335544757;
	gds_sort_rec_size_err                = 335544758;
	gds_bad_default_value                = 335544759;
	gds_invalid_clause                   = 335544760;
	gds_too_many_handles                 = 335544761;
	gds_optimizer_blk_exc                = 335544762;
	gds_invalid_string_constant          = 335544763;
	gds_transitional_date                = 335544764;
	gds_read_only_database               = 335544765;
	gds_must_be_dialect_2_and_up         = 335544766;
	gds_blob_filter_exception            = 335544767;
	gds_exception_access_violation       = 335544768;
	gds_exception_datatype_missalignment = 335544769;
	gds_exception_array_bounds_exceeded  = 335544770;
	gds_exception_float_denormal_operand = 335544771;
	gds_exception_float_divide_by_zero   = 335544772;
	gds_exception_float_inexact_result   = 335544773;
	gds_exception_float_invalid_operand  = 335544774;
	gds_exception_float_overflow         = 335544775;
	gds_exception_float_stack_check      = 335544776;
	gds_exception_float_underflow        = 335544777;
	gds_exception_integer_divide_by_zero = 335544778;
	gds_exception_integer_overflow       = 335544779;
	gds_exception_unknown                = 335544780;
	gds_exception_stack_overflow         = 335544781;
	gds_exception_sigsegv                = 335544782;
	gds_exception_sigill                 = 335544783;
	gds_exception_sigbus                 = 335544784;
	gds_exception_sigfpe                 = 335544785;
	gds_ext_file_delete                  = 335544786;
	gds_ext_file_modify                  = 335544787;
	gds_adm_task_denied                  = 335544788;
	gds_extract_input_mismatch           = 335544789;
	gds_insufficient_svc_privileges      = 335544790;
	gds_file_in_use                      = 335544791;
	gds_service_att_err                  = 335544792;
	gds_ddl_not_allowed_by_db_sql_dial   = 335544793;
	gds_cancelled                        = 335544794;
	gds_unexp_spb_form                   = 335544795;
	gds_sql_dialect_datatype_unsupport   = 335544796;
	gds_svcnouser                        = 335544797;
	gds_depend_on_uncommitted_rel        = 335544798;
	gds_svc_name_missing                 = 335544799;
	gds_too_many_contexts                = 335544800;
	gds_datype_notsup                    = 335544801;
	gds_dialect_reset_warning            = 335544802;
	gds_dialect_not_changed              = 335544803;
	gds_database_create_failed           = 335544804;
	gds_inv_dialect_specified            = 335544805;
	gds_valid_db_dialects                = 335544806;
	gds_sqlwarn                          = 335544807;
	gds_dtype_renamed                    = 335544808;
	gds_extern_func_dir_error            = 335544809;
	gds_date_range_exceeded              = 335544810;
	gds_inv_client_dialect_specified     = 335544811;
	gds_valid_client_dialects            = 335544812;
	gds_optimizer_between_err            = 335544813;
	gds_service_not_supported            = 335544814;
	gds_generator_name                   = 335544815;
	gds_udf_name                         = 335544816;
	gds_bad_limit_param                  = 335544817;
	gds_bad_skip_param                   = 335544818;
	gds_io_32bit_exceeded_err            = 335544819;
	gds_invalid_savepoint                = 335544820;
	gds_dsql_column_pos_err              = 335544821;
	gds_dsql_agg_where_err               = 335544822;
	gds_dsql_agg_group_err               = 335544823;
	gds_dsql_agg_column_err              = 335544824;
	gds_dsql_agg_having_err              = 335544825;
	gds_dsql_agg_nested_err              = 335544826;
	gds_exec_sql_invalid_arg             = 335544827;
	gds_exec_sql_invalid_req             = 335544828;
	gds_exec_sql_invalid_var             = 335544829;
	gds_exec_sql_max_call_exceeded       = 335544830;
	gds_conf_access_denied               = 335544831;
	gds_wrong_backup_state               = 335544832;
	gds_wal_backup_err                   = 335544833;
	gds_cursor_not_open                  = 335544834;
	gds_bad_shutdown_mode                = 335544835;
	gds_concat_overflow                  = 335544836;
	gds_bad_substring_offset             = 335544837;
	gds_foreign_key_target_doesnt_exist  = 335544838;
	gds_foreign_key_references_present   = 335544839;
	gds_no_update                        = 335544840;
	gds_cursor_already_open              = 335544841;
	gds_stack_trace                      = 335544842;
	gds_ctx_var_not_found                = 335544843;
	gds_ctx_namespace_invalid            = 335544844;
	gds_ctx_too_big                      = 335544845;
	gds_ctx_bad_argument                 = 335544846;
	gds_identifier_too_long              = 335544847;
	gds_except2                          = 335544848;
	gds_malformed_string                 = 335544849;
	gds_prc_out_param_mismatch           = 335544850;
	gds_command_end_err2                 = 335544851;
	gds_partner_idx_incompat_type        = 335544852;
	gds_bad_substring_length             = 335544853;
	gds_charset_not_installed            = 335544854;
	gds_collation_not_installed          = 335544855;
	gds_att_shutdown                     = 335544856;
	gds_gfix_db_name                     = 335740929;
	gds_gfix_invalid_sw                  = 335740930;
	gds_gfix_incmp_sw                    = 335740932;
	gds_gfix_replay_req                  = 335740933;
	gds_gfix_pgbuf_req                   = 335740934;
	gds_gfix_val_req                     = 335740935;
	gds_gfix_pval_req                    = 335740936;
	gds_gfix_trn_req                     = 335740937;
	gds_gfix_full_req                    = 335740940;
	gds_gfix_usrname_req                 = 335740941;
	gds_gfix_pass_req                    = 335740942;
	gds_gfix_subs_name                   = 335740943;
	gds_gfix_wal_req                     = 335740944;
	gds_gfix_sec_req                     = 335740945;
	gds_gfix_nval_req                    = 335740946;
	gds_gfix_type_shut                   = 335740947;
	gds_gfix_retry                       = 335740948;
	gds_gfix_retry_db                    = 335740951;
	gds_gfix_exceed_max                  = 335740991;
	gds_gfix_corrupt_pool                = 335740992;
	gds_gfix_mem_exhausted               = 335740993;
	gds_gfix_bad_pool                    = 335740994;
	gds_gfix_trn_not_valid               = 335740995;
	gds_gfix_unexp_eoi                   = 335741012;
	gds_gfix_recon_fail                  = 335741018;
	gds_gfix_trn_unknown                 = 335741036;
	gds_gfix_mode_req                    = 335741038;
	gds_gfix_opt_SQL_dialect             = 335741039;
	gds_gfix_pzval_req                   = 335741042;
	gds_dsql_dbkey_from_non_table        = 336003074;
	gds_dsql_transitional_numeric        = 336003075;
	gds_dsql_dialect_warning_expr        = 336003076;
	gds_sql_db_dialect_dtype_unsupport   = 336003077;
	gds_isc_sql_dialect_conflict_num     = 336003079;
	gds_dsql_warning_number_ambiguous    = 336003080;
	gds_dsql_warning_number_ambiguous1   = 336003081;
	gds_dsql_warn_precision_ambiguous    = 336003082;
	gds_dsql_warn_precision_ambiguous1   = 336003083;
	gds_dsql_warn_precision_ambiguous2   = 336003084;
	gds_dsql_ambiguous_field_name        = 336003085;
	gds_dsql_udf_return_pos_err          = 336003086;
	gds_dsql_invalid_label               = 336003087;
	gds_dsql_datatypes_not_comparable    = 336003088;
	gds_dsql_cursor_invalid              = 336003089;
	gds_dsql_cursor_redefined            = 336003090;
	gds_dsql_cursor_not_found            = 336003091;
	gds_dsql_cursor_exists               = 336003092;
	gds_dsql_cursor_rel_ambiguous        = 336003093;
	gds_dsql_cursor_rel_not_found        = 336003094;
	gds_dsql_cursor_not_open             = 336003095;
	gds_dsql_type_not_supp_ext_tab       = 336003096;
	gds_dyn_role_does_not_exist          = 336068796;
	gds_dyn_no_grant_admin_opt           = 336068797;
	gds_dyn_user_not_role_member         = 336068798;
	gds_dyn_delete_role_failed           = 336068799;
	gds_dyn_grant_role_to_user           = 336068800;
	gds_dyn_inv_sql_role_name            = 336068801;
	gds_dyn_dup_sql_role                 = 336068802;
	gds_dyn_kywd_spec_for_role           = 336068803;
	gds_dyn_roles_not_supported          = 336068804;
	gds_dyn_domain_name_exists           = 336068812;
	gds_dyn_field_name_exists            = 336068813;
	gds_dyn_dependency_exists            = 336068814;
	gds_dyn_dtype_invalid                = 336068815;
	gds_dyn_char_fld_too_small           = 336068816;
	gds_dyn_invalid_dtype_conversion     = 336068817;
	gds_dyn_dtype_conv_invalid           = 336068818;
	gds_dyn_zero_len_id                  = 336068820;
	gds_gbak_unknown_switch              = 336330753;
	gds_gbak_page_size_missing           = 336330754;
	gds_gbak_page_size_toobig            = 336330755;
	gds_gbak_redir_ouput_missing         = 336330756;
	gds_gbak_switches_conflict           = 336330757;
	gds_gbak_unknown_device              = 336330758;
	gds_gbak_no_protection               = 336330759;
	gds_gbak_page_size_not_allowed       = 336330760;
	gds_gbak_multi_source_dest           = 336330761;
	gds_gbak_filename_missing            = 336330762;
	gds_gbak_dup_inout_names             = 336330763;
	gds_gbak_inv_page_size               = 336330764;
	gds_gbak_db_specified                = 336330765;
	gds_gbak_db_exists                   = 336330766;
	gds_gbak_unk_device                  = 336330767;
	gds_gbak_blob_info_failed            = 336330772;
	gds_gbak_unk_blob_item               = 336330773;
	gds_gbak_get_seg_failed              = 336330774;
	gds_gbak_close_blob_failed           = 336330775;
	gds_gbak_open_blob_failed            = 336330776;
	gds_gbak_put_blr_gen_id_failed       = 336330777;
	gds_gbak_unk_type                    = 336330778;
	gds_gbak_comp_req_failed             = 336330779;
	gds_gbak_start_req_failed            = 336330780;
	gds_gbak_rec_failed                  = 336330781;
	gds_gbak_rel_req_failed              = 336330782;
	gds_gbak_db_info_failed              = 336330783;
	gds_gbak_no_db_desc                  = 336330784;
	gds_gbak_db_create_failed            = 336330785;
	gds_gbak_decomp_len_error            = 336330786;
	gds_gbak_tbl_missing                 = 336330787;
	gds_gbak_blob_col_missing            = 336330788;
	gds_gbak_create_blob_failed          = 336330789;
	gds_gbak_put_seg_failed              = 336330790;
	gds_gbak_rec_len_exp                 = 336330791;
	gds_gbak_inv_rec_len                 = 336330792;
	gds_gbak_exp_data_type               = 336330793;
	gds_gbak_gen_id_failed               = 336330794;
	gds_gbak_unk_rec_type                = 336330795;
	gds_gbak_inv_bkup_ver                = 336330796;
	gds_gbak_missing_bkup_desc           = 336330797;
	gds_gbak_string_trunc                = 336330798;
	gds_gbak_cant_rest_record            = 336330799;
	gds_gbak_send_failed                 = 336330800;
	gds_gbak_no_tbl_name                 = 336330801;
	gds_gbak_unexp_eof                   = 336330802;
	gds_gbak_db_format_too_old           = 336330803;
	gds_gbak_inv_array_dim               = 336330804;
	gds_gbak_xdr_len_expected            = 336330807;
	gds_gbak_open_bkup_error             = 336330817;
	gds_gbak_open_error                  = 336330818;
	gds_gbak_missing_block_fac           = 336330934;
	gds_gbak_inv_block_fac               = 336330935;
	gds_gbak_block_fac_specified         = 336330936;
	gds_gbak_missing_username            = 336330940;
	gds_gbak_missing_password            = 336330941;
	gds_gbak_missing_skipped_bytes       = 336330952;
	gds_gbak_inv_skipped_bytes           = 336330953;
	gds_gbak_err_restore_charset         = 336330965;
	gds_gbak_err_restore_collation       = 336330967;
	gds_gbak_read_error                  = 336330972;
	gds_gbak_write_error                 = 336330973;
	gds_gbak_db_in_use                   = 336330985;
	gds_gbak_sysmemex                    = 336330990;
	gds_gbak_restore_role_failed         = 336331002;
	gds_gbak_role_op_missing             = 336331005;
	gds_gbak_page_buffers_missing        = 336331010;
	gds_gbak_page_buffers_wrong_param    = 336331011;
	gds_gbak_page_buffers_restore        = 336331012;
	gds_gbak_inv_size                    = 336331014;
	gds_gbak_file_outof_sequence         = 336331015;
	gds_gbak_join_file_missing           = 336331016;
	gds_gbak_stdin_not_supptd            = 336331017;
	gds_gbak_stdout_not_supptd           = 336331018;
	gds_gbak_bkup_corrupt                = 336331019;
	gds_gbak_unk_db_file_spec            = 336331020;
	gds_gbak_hdr_write_failed            = 336331021;
	gds_gbak_disk_space_ex               = 336331022;
	gds_gbak_size_lt_min                 = 336331023;
	gds_gbak_svc_name_missing            = 336331025;
	gds_gbak_not_ownr                    = 336331026;
	gds_gbak_mode_req                    = 336331031;
	gds_gbak_just_data                   = 336331033;
	gds_gbak_data_only                   = 336331034;
	gds_dsql_too_many_values             = 336397041;
	gds_dsql_no_dup_name                 = 336397042;
	gds_dsql_unknown_pos                 = 336397043;
	gds_dsql_line_col_error              = 336397044;
	gds_dsql_view_not_found              = 336397047;
	gds_dsql_table_not_found             = 336397048;
	gds_dsql_too_old_ods                 = 336397058;
	gds_gsec_cant_open_db                = 336723983;
	gds_gsec_switches_error              = 336723984;
	gds_gsec_no_op_spec                  = 336723985;
	gds_gsec_no_usr_name                 = 336723986;
	gds_gsec_err_add                     = 336723987;
	gds_gsec_err_modify                  = 336723988;
	gds_gsec_err_find_mod                = 336723989;
	gds_gsec_err_rec_not_found           = 336723990;
	gds_gsec_err_delete                  = 336723991;
	gds_gsec_err_find_del                = 336723992;
	gds_gsec_err_find_disp               = 336723996;
	gds_gsec_inv_param                   = 336723997;
	gds_gsec_op_specified                = 336723998;
	gds_gsec_pw_specified                = 336723999;
	gds_gsec_uid_specified               = 336724000;
	gds_gsec_gid_specified               = 336724001;
	gds_gsec_proj_specified              = 336724002;
	gds_gsec_org_specified               = 336724003;
	gds_gsec_fname_specified             = 336724004;
	gds_gsec_mname_specified             = 336724005;
	gds_gsec_lname_specified             = 336724006;
	gds_gsec_inv_switch                  = 336724008;
	gds_gsec_amb_switch                  = 336724009;
	gds_gsec_no_op_specified             = 336724010;
	gds_gsec_params_not_allowed          = 336724011;
	gds_gsec_incompat_switch             = 336724012;
	gds_gsec_inv_username                = 336724044;
	gds_gsec_inv_pw_length               = 336724045;
	gds_gsec_db_specified                = 336724046;
	gds_gsec_db_admin_specified          = 336724047;
	gds_gsec_db_admin_pw_specified       = 336724048;
	gds_gsec_sql_role_specified          = 336724049;
	gds_license_no_file                  = 336789504;
	gds_license_op_specified             = 336789523;
	gds_license_op_missing               = 336789524;
	gds_license_inv_switch               = 336789525;
	gds_license_inv_switch_combo         = 336789526;
	gds_license_inv_op_combo             = 336789527;
	gds_license_amb_switch               = 336789528;
	gds_license_inv_parameter            = 336789529;
	gds_license_param_specified          = 336789530;
	gds_license_param_req                = 336789531;
	gds_license_syntx_error              = 336789532;
	gds_license_dup_id                   = 336789534;
	gds_license_inv_id_key               = 336789535;
	gds_license_err_remove               = 336789536;
	gds_license_err_update               = 336789537;
	gds_license_err_convert              = 336789538;
	gds_license_err_unk                  = 336789539;
	gds_license_svc_err_add              = 336789540;
	gds_license_svc_err_remove           = 336789541;
	gds_license_eval_exists              = 336789563;
	gds_gstat_unknown_switch             = 336920577;
	gds_gstat_retry                      = 336920578;
	gds_gstat_wrong_ods                  = 336920579;
	gds_gstat_unexpected_eof             = 336920580;
	gds_gstat_open_err                   = 336920605;
	gds_gstat_read_err                   = 336920606;
	gds_gstat_sysmemex                   = 336920607;
