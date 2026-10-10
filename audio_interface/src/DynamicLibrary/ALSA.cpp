// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/ALSA.h"

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary {

ALSA::ALSA() {
  library_ = loadLibrary( "libasound.so.2" );

  snd_asoundlib_version_ = loadSymbol< decltype( snd_asoundlib_version_ ) >( library_, "snd_asoundlib_version" );
  snd_async_add_handler_ = loadSymbol< decltype( snd_async_add_handler_ ) >( library_, "snd_async_add_handler" );
  snd_async_del_handler_ = loadSymbol< decltype( snd_async_del_handler_ ) >( library_, "snd_async_del_handler" );
  snd_async_handler_get_fd_ = loadSymbol< decltype( snd_async_handler_get_fd_ ) >( library_, "snd_async_handler_get_fd" );
  snd_async_handler_get_signo_ = loadSymbol< decltype( snd_async_handler_get_signo_ ) >( library_, "snd_async_handler_get_signo" );
  snd_async_handler_get_callback_private_ = loadSymbol< decltype( snd_async_handler_get_callback_private_ ) >( library_, "snd_async_handler_get_callback_private" );
  // snd_shm_area_create_ = loadSymbol< decltype( snd_shm_area_create_ ) >( library_, "snd_shm_area_create" );
  // snd_shm_area_share_ = loadSymbol< decltype( snd_shm_area_share_ ) >( library_, "snd_shm_area_share" );
  // snd_shm_area_destroy_ = loadSymbol< decltype( snd_shm_area_destroy_ ) >( library_, "snd_shm_area_destroy" );
  snd_user_file_ = loadSymbol< decltype( snd_user_file_ ) >( library_, "snd_user_file" );
  snd_pcm_open_ = loadSymbol< decltype( snd_pcm_open_ ) >( library_, "snd_pcm_open" );
  // snd_pcm_open_lconf_ = loadSymbol< decltype( snd_pcm_open_lconf_ ) >( library_, "snd_pcm_open_lconf" );
  // snd_pcm_open_fallback_ = loadSymbol< decltype( snd_pcm_open_fallback_ ) >( library_, "snd_pcm_open_fallback" );
  snd_pcm_close_ = loadSymbol< decltype( snd_pcm_close_ ) >( library_, "snd_pcm_close" );
  snd_pcm_name_ = loadSymbol< decltype( snd_pcm_name_ ) >( library_, "snd_pcm_name" );
  snd_pcm_type_ = loadSymbol< decltype( snd_pcm_type_ ) >( library_, "snd_pcm_type" );
  snd_pcm_stream_ = loadSymbol< decltype( snd_pcm_stream_ ) >( library_, "snd_pcm_stream" );
  snd_pcm_poll_descriptors_count_ = loadSymbol< decltype( snd_pcm_poll_descriptors_count_ ) >( library_, "snd_pcm_poll_descriptors_count" );
  // snd_pcm_poll_descriptors_ = loadSymbol< decltype( snd_pcm_poll_descriptors_ ) >( library_, "snd_pcm_poll_descriptors" );
  // snd_pcm_poll_descriptors_revents_ = loadSymbol< decltype( snd_pcm_poll_descriptors_revents_ ) >( library_, "snd_pcm_poll_descriptors_revents" );
  snd_pcm_nonblock_ = loadSymbol< decltype( snd_pcm_nonblock_ ) >( library_, "snd_pcm_nonblock" );
  snd_pcm_abort_ = loadSymbol< decltype( snd_pcm_abort_ ) >( library_, "snd_pcm_abort" );
  snd_async_add_pcm_handler_ = loadSymbol< decltype( snd_async_add_pcm_handler_ ) >( library_, "snd_async_add_pcm_handler" );
  snd_async_handler_get_pcm_ = loadSymbol< decltype( snd_async_handler_get_pcm_ ) >( library_, "snd_async_handler_get_pcm" );
  snd_pcm_info_ = loadSymbol< decltype( snd_pcm_info_ ) >( library_, "snd_pcm_info" );
  snd_pcm_hw_params_current_ = loadSymbol< decltype( snd_pcm_hw_params_current_ ) >( library_, "snd_pcm_hw_params_current" );
  snd_pcm_hw_params_ = loadSymbol< decltype( snd_pcm_hw_params_ ) >( library_, "snd_pcm_hw_params" );
  snd_pcm_hw_free_ = loadSymbol< decltype( snd_pcm_hw_free_ ) >( library_, "snd_pcm_hw_free" );
  snd_pcm_sw_params_current_ = loadSymbol< decltype( snd_pcm_sw_params_current_ ) >( library_, "snd_pcm_sw_params_current" );
  snd_pcm_sw_params_ = loadSymbol< decltype( snd_pcm_sw_params_ ) >( library_, "snd_pcm_sw_params" );
  snd_pcm_prepare_ = loadSymbol< decltype( snd_pcm_prepare_ ) >( library_, "snd_pcm_prepare" );
  snd_pcm_reset_ = loadSymbol< decltype( snd_pcm_reset_ ) >( library_, "snd_pcm_reset" );
  snd_pcm_status_ = loadSymbol< decltype( snd_pcm_status_ ) >( library_, "snd_pcm_status" );
  snd_pcm_start_ = loadSymbol< decltype( snd_pcm_start_ ) >( library_, "snd_pcm_start" );
  snd_pcm_drop_ = loadSymbol< decltype( snd_pcm_drop_ ) >( library_, "snd_pcm_drop" );
  snd_pcm_drain_ = loadSymbol< decltype( snd_pcm_drain_ ) >( library_, "snd_pcm_drain" );
  snd_pcm_pause_ = loadSymbol< decltype( snd_pcm_pause_ ) >( library_, "snd_pcm_pause" );
  snd_pcm_state_ = loadSymbol< decltype( snd_pcm_state_ ) >( library_, "snd_pcm_state" );
  snd_pcm_hwsync_ = loadSymbol< decltype( snd_pcm_hwsync_ ) >( library_, "snd_pcm_hwsync" );
  snd_pcm_delay_ = loadSymbol< decltype( snd_pcm_delay_ ) >( library_, "snd_pcm_delay" );
  snd_pcm_resume_ = loadSymbol< decltype( snd_pcm_resume_ ) >( library_, "snd_pcm_resume" );
  snd_pcm_htimestamp_ = loadSymbol< decltype( snd_pcm_htimestamp_ ) >( library_, "snd_pcm_htimestamp" );
  snd_pcm_avail_ = loadSymbol< decltype( snd_pcm_avail_ ) >( library_, "snd_pcm_avail" );
  snd_pcm_avail_update_ = loadSymbol< decltype( snd_pcm_avail_update_ ) >( library_, "snd_pcm_avail_update" );
  snd_pcm_avail_delay_ = loadSymbol< decltype( snd_pcm_avail_delay_ ) >( library_, "snd_pcm_avail_delay" );
  snd_pcm_rewindable_ = loadSymbol< decltype( snd_pcm_rewindable_ ) >( library_, "snd_pcm_rewindable" );
  snd_pcm_rewind_ = loadSymbol< decltype( snd_pcm_rewind_ ) >( library_, "snd_pcm_rewind" );
  snd_pcm_forwardable_ = loadSymbol< decltype( snd_pcm_forwardable_ ) >( library_, "snd_pcm_forwardable" );
  snd_pcm_forward_ = loadSymbol< decltype( snd_pcm_forward_ ) >( library_, "snd_pcm_forward" );
  snd_pcm_writei_ = loadSymbol< decltype( snd_pcm_writei_ ) >( library_, "snd_pcm_writei" );
  snd_pcm_readi_ = loadSymbol< decltype( snd_pcm_readi_ ) >( library_, "snd_pcm_readi" );
  snd_pcm_writen_ = loadSymbol< decltype( snd_pcm_writen_ ) >( library_, "snd_pcm_writen" );
  snd_pcm_readn_ = loadSymbol< decltype( snd_pcm_readn_ ) >( library_, "snd_pcm_readn" );
  snd_pcm_wait_ = loadSymbol< decltype( snd_pcm_wait_ ) >( library_, "snd_pcm_wait" );
  snd_pcm_link_ = loadSymbol< decltype( snd_pcm_link_ ) >( library_, "snd_pcm_link" );
  snd_pcm_unlink_ = loadSymbol< decltype( snd_pcm_unlink_ ) >( library_, "snd_pcm_unlink" );
  snd_pcm_query_chmaps_ = loadSymbol< decltype( snd_pcm_query_chmaps_ ) >( library_, "snd_pcm_query_chmaps" );
  snd_pcm_query_chmaps_from_hw_ = loadSymbol< decltype( snd_pcm_query_chmaps_from_hw_ ) >( library_, "snd_pcm_query_chmaps_from_hw" );
  snd_pcm_free_chmaps_ = loadSymbol< decltype( snd_pcm_free_chmaps_ ) >( library_, "snd_pcm_free_chmaps" );
  snd_pcm_get_chmap_ = loadSymbol< decltype( snd_pcm_get_chmap_ ) >( library_, "snd_pcm_get_chmap" );
  snd_pcm_set_chmap_ = loadSymbol< decltype( snd_pcm_set_chmap_ ) >( library_, "snd_pcm_set_chmap" );
  snd_pcm_chmap_type_name_ = loadSymbol< decltype( snd_pcm_chmap_type_name_ ) >( library_, "snd_pcm_chmap_type_name" );
  snd_pcm_chmap_name_ = loadSymbol< decltype( snd_pcm_chmap_name_ ) >( library_, "snd_pcm_chmap_name" );
  snd_pcm_chmap_long_name_ = loadSymbol< decltype( snd_pcm_chmap_long_name_ ) >( library_, "snd_pcm_chmap_long_name" );
  snd_pcm_chmap_print_ = loadSymbol< decltype( snd_pcm_chmap_print_ ) >( library_, "snd_pcm_chmap_print" );
  snd_pcm_chmap_from_string_ = loadSymbol< decltype( snd_pcm_chmap_from_string_ ) >( library_, "snd_pcm_chmap_from_string" );
  snd_pcm_chmap_parse_string_ = loadSymbol< decltype( snd_pcm_chmap_parse_string_ ) >( library_, "snd_pcm_chmap_parse_string" );
  snd_pcm_recover_ = loadSymbol< decltype( snd_pcm_recover_ ) >( library_, "snd_pcm_recover" );
  snd_pcm_set_params_ = loadSymbol< decltype( snd_pcm_set_params_ ) >( library_, "snd_pcm_set_params" );
  snd_pcm_get_params_ = loadSymbol< decltype( snd_pcm_get_params_ ) >( library_, "snd_pcm_get_params" );
  snd_pcm_info_sizeof_ = loadSymbol< decltype( snd_pcm_info_sizeof_ ) >( library_, "snd_pcm_info_sizeof" );
  snd_pcm_info_malloc_ = loadSymbol< decltype( snd_pcm_info_malloc_ ) >( library_, "snd_pcm_info_malloc" );
  snd_pcm_info_free_ = loadSymbol< decltype( snd_pcm_info_free_ ) >( library_, "snd_pcm_info_free" );
  snd_pcm_info_copy_ = loadSymbol< decltype( snd_pcm_info_copy_ ) >( library_, "snd_pcm_info_copy" );
  snd_pcm_info_get_device_ = loadSymbol< decltype( snd_pcm_info_get_device_ ) >( library_, "snd_pcm_info_get_device" );
  snd_pcm_info_get_subdevice_ = loadSymbol< decltype( snd_pcm_info_get_subdevice_ ) >( library_, "snd_pcm_info_get_subdevice" );
  snd_pcm_info_get_stream_ = loadSymbol< decltype( snd_pcm_info_get_stream_ ) >( library_, "snd_pcm_info_get_stream" );
  snd_pcm_info_get_card_ = loadSymbol< decltype( snd_pcm_info_get_card_ ) >( library_, "snd_pcm_info_get_card" );
  snd_pcm_info_get_id_ = loadSymbol< decltype( snd_pcm_info_get_id_ ) >( library_, "snd_pcm_info_get_id" );
  snd_pcm_info_get_name_ = loadSymbol< decltype( snd_pcm_info_get_name_ ) >( library_, "snd_pcm_info_get_name" );
  snd_pcm_info_get_subdevice_name_ = loadSymbol< decltype( snd_pcm_info_get_subdevice_name_ ) >( library_, "snd_pcm_info_get_subdevice_name" );
  snd_pcm_info_get_class_ = loadSymbol< decltype( snd_pcm_info_get_class_ ) >( library_, "snd_pcm_info_get_class" );
  snd_pcm_info_get_subclass_ = loadSymbol< decltype( snd_pcm_info_get_subclass_ ) >( library_, "snd_pcm_info_get_subclass" );
  snd_pcm_info_get_subdevices_count_ = loadSymbol< decltype( snd_pcm_info_get_subdevices_count_ ) >( library_, "snd_pcm_info_get_subdevices_count" );
  snd_pcm_info_get_subdevices_avail_ = loadSymbol< decltype( snd_pcm_info_get_subdevices_avail_ ) >( library_, "snd_pcm_info_get_subdevices_avail" );
  snd_pcm_info_get_sync_ = loadSymbol< decltype( snd_pcm_info_get_sync_ ) >( library_, "snd_pcm_info_get_sync" );
  snd_pcm_info_set_device_ = loadSymbol< decltype( snd_pcm_info_set_device_ ) >( library_, "snd_pcm_info_set_device" );
  snd_pcm_info_set_subdevice_ = loadSymbol< decltype( snd_pcm_info_set_subdevice_ ) >( library_, "snd_pcm_info_set_subdevice" );
  snd_pcm_info_set_stream_ = loadSymbol< decltype( snd_pcm_info_set_stream_ ) >( library_, "snd_pcm_info_set_stream" );
  snd_pcm_hw_params_any_ = loadSymbol< decltype( snd_pcm_hw_params_any_ ) >( library_, "snd_pcm_hw_params_any" );
  snd_pcm_hw_params_can_mmap_sample_resolution_ = loadSymbol< decltype( snd_pcm_hw_params_can_mmap_sample_resolution_ ) >( library_, "snd_pcm_hw_params_can_mmap_sample_resolution" );
  snd_pcm_hw_params_is_double_ = loadSymbol< decltype( snd_pcm_hw_params_is_double_ ) >( library_, "snd_pcm_hw_params_is_double" );
  snd_pcm_hw_params_is_batch_ = loadSymbol< decltype( snd_pcm_hw_params_is_batch_ ) >( library_, "snd_pcm_hw_params_is_batch" );
  snd_pcm_hw_params_is_block_transfer_ = loadSymbol< decltype( snd_pcm_hw_params_is_block_transfer_ ) >( library_, "snd_pcm_hw_params_is_block_transfer" );
  snd_pcm_hw_params_is_monotonic_ = loadSymbol< decltype( snd_pcm_hw_params_is_monotonic_ ) >( library_, "snd_pcm_hw_params_is_monotonic" );
  snd_pcm_hw_params_can_overrange_ = loadSymbol< decltype( snd_pcm_hw_params_can_overrange_ ) >( library_, "snd_pcm_hw_params_can_overrange" );
  snd_pcm_hw_params_can_pause_ = loadSymbol< decltype( snd_pcm_hw_params_can_pause_ ) >( library_, "snd_pcm_hw_params_can_pause" );
  snd_pcm_hw_params_can_resume_ = loadSymbol< decltype( snd_pcm_hw_params_can_resume_ ) >( library_, "snd_pcm_hw_params_can_resume" );
  snd_pcm_hw_params_is_half_duplex_ = loadSymbol< decltype( snd_pcm_hw_params_is_half_duplex_ ) >( library_, "snd_pcm_hw_params_is_half_duplex" );
  snd_pcm_hw_params_is_joint_duplex_ = loadSymbol< decltype( snd_pcm_hw_params_is_joint_duplex_ ) >( library_, "snd_pcm_hw_params_is_joint_duplex" );
  snd_pcm_hw_params_can_sync_start_ = loadSymbol< decltype( snd_pcm_hw_params_can_sync_start_ ) >( library_, "snd_pcm_hw_params_can_sync_start" );
  snd_pcm_hw_params_can_disable_period_wakeup_ = loadSymbol< decltype( snd_pcm_hw_params_can_disable_period_wakeup_ ) >( library_, "snd_pcm_hw_params_can_disable_period_wakeup" );
  snd_pcm_hw_params_is_perfect_drain_ = loadSymbol< decltype( snd_pcm_hw_params_is_perfect_drain_ ) >( library_, "snd_pcm_hw_params_is_perfect_drain" );
  snd_pcm_hw_params_supports_audio_wallclock_ts_ = loadSymbol< decltype( snd_pcm_hw_params_supports_audio_wallclock_ts_ ) >( library_, "snd_pcm_hw_params_supports_audio_wallclock_ts" );
  snd_pcm_hw_params_supports_audio_ts_type_ = loadSymbol< decltype( snd_pcm_hw_params_supports_audio_ts_type_ ) >( library_, "snd_pcm_hw_params_supports_audio_ts_type" );
  snd_pcm_hw_params_get_rate_numden_ = loadSymbol< decltype( snd_pcm_hw_params_get_rate_numden_ ) >( library_, "snd_pcm_hw_params_get_rate_numden" );
  snd_pcm_hw_params_get_sbits_ = loadSymbol< decltype( snd_pcm_hw_params_get_sbits_ ) >( library_, "snd_pcm_hw_params_get_sbits" );
  snd_pcm_hw_params_get_fifo_size_ = loadSymbol< decltype( snd_pcm_hw_params_get_fifo_size_ ) >( library_, "snd_pcm_hw_params_get_fifo_size" );
  snd_pcm_hw_params_get_sync_ = loadSymbol< decltype( snd_pcm_hw_params_get_sync_ ) >( library_, "snd_pcm_hw_params_get_sync" );
  snd_pcm_hw_params_sizeof_ = loadSymbol< decltype( snd_pcm_hw_params_sizeof_ ) >( library_, "snd_pcm_hw_params_sizeof" );
  snd_pcm_hw_params_malloc_ = loadSymbol< decltype( snd_pcm_hw_params_malloc_ ) >( library_, "snd_pcm_hw_params_malloc" );
  snd_pcm_hw_params_free_ = loadSymbol< decltype( snd_pcm_hw_params_free_ ) >( library_, "snd_pcm_hw_params_free" );
  snd_pcm_hw_params_copy_ = loadSymbol< decltype( snd_pcm_hw_params_copy_ ) >( library_, "snd_pcm_hw_params_copy" );
  snd_pcm_hw_params_get_access_ = loadSymbol< decltype( snd_pcm_hw_params_get_access_ ) >( library_, "snd_pcm_hw_params_get_access" );
  snd_pcm_hw_params_test_access_ = loadSymbol< decltype( snd_pcm_hw_params_test_access_ ) >( library_, "snd_pcm_hw_params_test_access" );
  snd_pcm_hw_params_set_access_ = loadSymbol< decltype( snd_pcm_hw_params_set_access_ ) >( library_, "snd_pcm_hw_params_set_access" );
  snd_pcm_hw_params_set_access_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_access_first_ ) >( library_, "snd_pcm_hw_params_set_access_first" );
  snd_pcm_hw_params_set_access_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_access_last_ ) >( library_, "snd_pcm_hw_params_set_access_last" );
  snd_pcm_hw_params_set_access_mask_ = loadSymbol< decltype( snd_pcm_hw_params_set_access_mask_ ) >( library_, "snd_pcm_hw_params_set_access_mask" );
  snd_pcm_hw_params_get_access_mask_ = loadSymbol< decltype( snd_pcm_hw_params_get_access_mask_ ) >( library_, "snd_pcm_hw_params_get_access_mask" );
  snd_pcm_hw_params_get_format_ = loadSymbol< decltype( snd_pcm_hw_params_get_format_ ) >( library_, "snd_pcm_hw_params_get_format" );
  snd_pcm_hw_params_test_format_ = loadSymbol< decltype( snd_pcm_hw_params_test_format_ ) >( library_, "snd_pcm_hw_params_test_format" );
  snd_pcm_hw_params_set_format_ = loadSymbol< decltype( snd_pcm_hw_params_set_format_ ) >( library_, "snd_pcm_hw_params_set_format" );
  snd_pcm_hw_params_set_format_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_format_first_ ) >( library_, "snd_pcm_hw_params_set_format_first" );
  snd_pcm_hw_params_set_format_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_format_last_ ) >( library_, "snd_pcm_hw_params_set_format_last" );
  snd_pcm_hw_params_set_format_mask_ = loadSymbol< decltype( snd_pcm_hw_params_set_format_mask_ ) >( library_, "snd_pcm_hw_params_set_format_mask" );
  snd_pcm_hw_params_get_format_mask_ = loadSymbol< decltype( snd_pcm_hw_params_get_format_mask_ ) >( library_, "snd_pcm_hw_params_get_format_mask" );
  snd_pcm_hw_params_get_subformat_ = loadSymbol< decltype( snd_pcm_hw_params_get_subformat_ ) >( library_, "snd_pcm_hw_params_get_subformat" );
  snd_pcm_hw_params_test_subformat_ = loadSymbol< decltype( snd_pcm_hw_params_test_subformat_ ) >( library_, "snd_pcm_hw_params_test_subformat" );
  snd_pcm_hw_params_set_subformat_ = loadSymbol< decltype( snd_pcm_hw_params_set_subformat_ ) >( library_, "snd_pcm_hw_params_set_subformat" );
  snd_pcm_hw_params_set_subformat_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_subformat_first_ ) >( library_, "snd_pcm_hw_params_set_subformat_first" );
  snd_pcm_hw_params_set_subformat_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_subformat_last_ ) >( library_, "snd_pcm_hw_params_set_subformat_last" );
  snd_pcm_hw_params_set_subformat_mask_ = loadSymbol< decltype( snd_pcm_hw_params_set_subformat_mask_ ) >( library_, "snd_pcm_hw_params_set_subformat_mask" );
  snd_pcm_hw_params_get_subformat_mask_ = loadSymbol< decltype( snd_pcm_hw_params_get_subformat_mask_ ) >( library_, "snd_pcm_hw_params_get_subformat_mask" );
  snd_pcm_hw_params_get_channels_ = loadSymbol< decltype( snd_pcm_hw_params_get_channels_ ) >( library_, "snd_pcm_hw_params_get_channels" );
  snd_pcm_hw_params_get_channels_min_ = loadSymbol< decltype( snd_pcm_hw_params_get_channels_min_ ) >( library_, "snd_pcm_hw_params_get_channels_min" );
  snd_pcm_hw_params_get_channels_max_ = loadSymbol< decltype( snd_pcm_hw_params_get_channels_max_ ) >( library_, "snd_pcm_hw_params_get_channels_max" );
  snd_pcm_hw_params_test_channels_ = loadSymbol< decltype( snd_pcm_hw_params_test_channels_ ) >( library_, "snd_pcm_hw_params_test_channels" );
  snd_pcm_hw_params_set_channels_ = loadSymbol< decltype( snd_pcm_hw_params_set_channels_ ) >( library_, "snd_pcm_hw_params_set_channels" );
  snd_pcm_hw_params_set_channels_min_ = loadSymbol< decltype( snd_pcm_hw_params_set_channels_min_ ) >( library_, "snd_pcm_hw_params_set_channels_min" );
  snd_pcm_hw_params_set_channels_max_ = loadSymbol< decltype( snd_pcm_hw_params_set_channels_max_ ) >( library_, "snd_pcm_hw_params_set_channels_max" );
  snd_pcm_hw_params_set_channels_minmax_ = loadSymbol< decltype( snd_pcm_hw_params_set_channels_minmax_ ) >( library_, "snd_pcm_hw_params_set_channels_minmax" );
  snd_pcm_hw_params_set_channels_near_ = loadSymbol< decltype( snd_pcm_hw_params_set_channels_near_ ) >( library_, "snd_pcm_hw_params_set_channels_near" );
  snd_pcm_hw_params_set_channels_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_channels_first_ ) >( library_, "snd_pcm_hw_params_set_channels_first" );
  snd_pcm_hw_params_set_channels_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_channels_last_ ) >( library_, "snd_pcm_hw_params_set_channels_last" );
  snd_pcm_hw_params_get_rate_ = loadSymbol< decltype( snd_pcm_hw_params_get_rate_ ) >( library_, "snd_pcm_hw_params_get_rate" );
  snd_pcm_hw_params_get_rate_min_ = loadSymbol< decltype( snd_pcm_hw_params_get_rate_min_ ) >( library_, "snd_pcm_hw_params_get_rate_min" );
  snd_pcm_hw_params_get_rate_max_ = loadSymbol< decltype( snd_pcm_hw_params_get_rate_max_ ) >( library_, "snd_pcm_hw_params_get_rate_max" );
  snd_pcm_hw_params_test_rate_ = loadSymbol< decltype( snd_pcm_hw_params_test_rate_ ) >( library_, "snd_pcm_hw_params_test_rate" );
  snd_pcm_hw_params_set_rate_ = loadSymbol< decltype( snd_pcm_hw_params_set_rate_ ) >( library_, "snd_pcm_hw_params_set_rate" );
  snd_pcm_hw_params_set_rate_min_ = loadSymbol< decltype( snd_pcm_hw_params_set_rate_min_ ) >( library_, "snd_pcm_hw_params_set_rate_min" );
  snd_pcm_hw_params_set_rate_max_ = loadSymbol< decltype( snd_pcm_hw_params_set_rate_max_ ) >( library_, "snd_pcm_hw_params_set_rate_max" );
  snd_pcm_hw_params_set_rate_minmax_ = loadSymbol< decltype( snd_pcm_hw_params_set_rate_minmax_ ) >( library_, "snd_pcm_hw_params_set_rate_minmax" );
  snd_pcm_hw_params_set_rate_near_ = loadSymbol< decltype( snd_pcm_hw_params_set_rate_near_ ) >( library_, "snd_pcm_hw_params_set_rate_near" );
  snd_pcm_hw_params_set_rate_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_rate_first_ ) >( library_, "snd_pcm_hw_params_set_rate_first" );
  snd_pcm_hw_params_set_rate_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_rate_last_ ) >( library_, "snd_pcm_hw_params_set_rate_last" );
  snd_pcm_hw_params_set_rate_resample_ = loadSymbol< decltype( snd_pcm_hw_params_set_rate_resample_ ) >( library_, "snd_pcm_hw_params_set_rate_resample" );
  snd_pcm_hw_params_get_rate_resample_ = loadSymbol< decltype( snd_pcm_hw_params_get_rate_resample_ ) >( library_, "snd_pcm_hw_params_get_rate_resample" );
  snd_pcm_hw_params_set_export_buffer_ = loadSymbol< decltype( snd_pcm_hw_params_set_export_buffer_ ) >( library_, "snd_pcm_hw_params_set_export_buffer" );
  snd_pcm_hw_params_get_export_buffer_ = loadSymbol< decltype( snd_pcm_hw_params_get_export_buffer_ ) >( library_, "snd_pcm_hw_params_get_export_buffer" );
  snd_pcm_hw_params_set_period_wakeup_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_wakeup_ ) >( library_, "snd_pcm_hw_params_set_period_wakeup" );
  snd_pcm_hw_params_get_period_wakeup_ = loadSymbol< decltype( snd_pcm_hw_params_get_period_wakeup_ ) >( library_, "snd_pcm_hw_params_get_period_wakeup" );
  snd_pcm_hw_params_set_drain_silence_ = loadSymbol< decltype( snd_pcm_hw_params_set_drain_silence_ ) >( library_, "snd_pcm_hw_params_set_drain_silence" );
  snd_pcm_hw_params_get_drain_silence_ = loadSymbol< decltype( snd_pcm_hw_params_get_drain_silence_ ) >( library_, "snd_pcm_hw_params_get_drain_silence" );
  snd_pcm_hw_params_get_period_time_ = loadSymbol< decltype( snd_pcm_hw_params_get_period_time_ ) >( library_, "snd_pcm_hw_params_get_period_time" );
  snd_pcm_hw_params_get_period_time_min_ = loadSymbol< decltype( snd_pcm_hw_params_get_period_time_min_ ) >( library_, "snd_pcm_hw_params_get_period_time_min" );
  snd_pcm_hw_params_get_period_time_max_ = loadSymbol< decltype( snd_pcm_hw_params_get_period_time_max_ ) >( library_, "snd_pcm_hw_params_get_period_time_max" );
  snd_pcm_hw_params_test_period_time_ = loadSymbol< decltype( snd_pcm_hw_params_test_period_time_ ) >( library_, "snd_pcm_hw_params_test_period_time" );
  snd_pcm_hw_params_set_period_time_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_time_ ) >( library_, "snd_pcm_hw_params_set_period_time" );
  snd_pcm_hw_params_set_period_time_min_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_time_min_ ) >( library_, "snd_pcm_hw_params_set_period_time_min" );
  snd_pcm_hw_params_set_period_time_max_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_time_max_ ) >( library_, "snd_pcm_hw_params_set_period_time_max" );
  snd_pcm_hw_params_set_period_time_minmax_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_time_minmax_ ) >( library_, "snd_pcm_hw_params_set_period_time_minmax" );
  snd_pcm_hw_params_set_period_time_near_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_time_near_ ) >( library_, "snd_pcm_hw_params_set_period_time_near" );
  snd_pcm_hw_params_set_period_time_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_time_first_ ) >( library_, "snd_pcm_hw_params_set_period_time_first" );
  snd_pcm_hw_params_set_period_time_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_time_last_ ) >( library_, "snd_pcm_hw_params_set_period_time_last" );
  snd_pcm_hw_params_get_period_size_ = loadSymbol< decltype( snd_pcm_hw_params_get_period_size_ ) >( library_, "snd_pcm_hw_params_get_period_size" );
  snd_pcm_hw_params_get_period_size_min_ = loadSymbol< decltype( snd_pcm_hw_params_get_period_size_min_ ) >( library_, "snd_pcm_hw_params_get_period_size_min" );
  snd_pcm_hw_params_get_period_size_max_ = loadSymbol< decltype( snd_pcm_hw_params_get_period_size_max_ ) >( library_, "snd_pcm_hw_params_get_period_size_max" );
  snd_pcm_hw_params_test_period_size_ = loadSymbol< decltype( snd_pcm_hw_params_test_period_size_ ) >( library_, "snd_pcm_hw_params_test_period_size" );
  snd_pcm_hw_params_set_period_size_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_size_ ) >( library_, "snd_pcm_hw_params_set_period_size" );
  snd_pcm_hw_params_set_period_size_min_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_size_min_ ) >( library_, "snd_pcm_hw_params_set_period_size_min" );
  snd_pcm_hw_params_set_period_size_max_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_size_max_ ) >( library_, "snd_pcm_hw_params_set_period_size_max" );
  snd_pcm_hw_params_set_period_size_minmax_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_size_minmax_ ) >( library_, "snd_pcm_hw_params_set_period_size_minmax" );
  snd_pcm_hw_params_set_period_size_near_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_size_near_ ) >( library_, "snd_pcm_hw_params_set_period_size_near" );
  snd_pcm_hw_params_set_period_size_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_size_first_ ) >( library_, "snd_pcm_hw_params_set_period_size_first" );
  snd_pcm_hw_params_set_period_size_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_size_last_ ) >( library_, "snd_pcm_hw_params_set_period_size_last" );
  snd_pcm_hw_params_set_period_size_integer_ = loadSymbol< decltype( snd_pcm_hw_params_set_period_size_integer_ ) >( library_, "snd_pcm_hw_params_set_period_size_integer" );
  snd_pcm_hw_params_get_periods_ = loadSymbol< decltype( snd_pcm_hw_params_get_periods_ ) >( library_, "snd_pcm_hw_params_get_periods" );
  snd_pcm_hw_params_get_periods_min_ = loadSymbol< decltype( snd_pcm_hw_params_get_periods_min_ ) >( library_, "snd_pcm_hw_params_get_periods_min" );
  snd_pcm_hw_params_get_periods_max_ = loadSymbol< decltype( snd_pcm_hw_params_get_periods_max_ ) >( library_, "snd_pcm_hw_params_get_periods_max" );
  snd_pcm_hw_params_test_periods_ = loadSymbol< decltype( snd_pcm_hw_params_test_periods_ ) >( library_, "snd_pcm_hw_params_test_periods" );
  snd_pcm_hw_params_set_periods_ = loadSymbol< decltype( snd_pcm_hw_params_set_periods_ ) >( library_, "snd_pcm_hw_params_set_periods" );
  snd_pcm_hw_params_set_periods_min_ = loadSymbol< decltype( snd_pcm_hw_params_set_periods_min_ ) >( library_, "snd_pcm_hw_params_set_periods_min" );
  snd_pcm_hw_params_set_periods_max_ = loadSymbol< decltype( snd_pcm_hw_params_set_periods_max_ ) >( library_, "snd_pcm_hw_params_set_periods_max" );
  snd_pcm_hw_params_set_periods_minmax_ = loadSymbol< decltype( snd_pcm_hw_params_set_periods_minmax_ ) >( library_, "snd_pcm_hw_params_set_periods_minmax" );
  snd_pcm_hw_params_set_periods_near_ = loadSymbol< decltype( snd_pcm_hw_params_set_periods_near_ ) >( library_, "snd_pcm_hw_params_set_periods_near" );
  snd_pcm_hw_params_set_periods_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_periods_first_ ) >( library_, "snd_pcm_hw_params_set_periods_first" );
  snd_pcm_hw_params_set_periods_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_periods_last_ ) >( library_, "snd_pcm_hw_params_set_periods_last" );
  snd_pcm_hw_params_set_periods_integer_ = loadSymbol< decltype( snd_pcm_hw_params_set_periods_integer_ ) >( library_, "snd_pcm_hw_params_set_periods_integer" );
  snd_pcm_hw_params_get_buffer_time_ = loadSymbol< decltype( snd_pcm_hw_params_get_buffer_time_ ) >( library_, "snd_pcm_hw_params_get_buffer_time" );
  snd_pcm_hw_params_get_buffer_time_min_ = loadSymbol< decltype( snd_pcm_hw_params_get_buffer_time_min_ ) >( library_, "snd_pcm_hw_params_get_buffer_time_min" );
  snd_pcm_hw_params_get_buffer_time_max_ = loadSymbol< decltype( snd_pcm_hw_params_get_buffer_time_max_ ) >( library_, "snd_pcm_hw_params_get_buffer_time_max" );
  snd_pcm_hw_params_test_buffer_time_ = loadSymbol< decltype( snd_pcm_hw_params_test_buffer_time_ ) >( library_, "snd_pcm_hw_params_test_buffer_time" );
  snd_pcm_hw_params_set_buffer_time_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_time_ ) >( library_, "snd_pcm_hw_params_set_buffer_time" );
  snd_pcm_hw_params_set_buffer_time_min_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_time_min_ ) >( library_, "snd_pcm_hw_params_set_buffer_time_min" );
  snd_pcm_hw_params_set_buffer_time_max_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_time_max_ ) >( library_, "snd_pcm_hw_params_set_buffer_time_max" );
  snd_pcm_hw_params_set_buffer_time_minmax_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_time_minmax_ ) >( library_, "snd_pcm_hw_params_set_buffer_time_minmax" );
  snd_pcm_hw_params_set_buffer_time_near_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_time_near_ ) >( library_, "snd_pcm_hw_params_set_buffer_time_near" );
  snd_pcm_hw_params_set_buffer_time_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_time_first_ ) >( library_, "snd_pcm_hw_params_set_buffer_time_first" );
  snd_pcm_hw_params_set_buffer_time_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_time_last_ ) >( library_, "snd_pcm_hw_params_set_buffer_time_last" );
  snd_pcm_hw_params_get_buffer_size_ = loadSymbol< decltype( snd_pcm_hw_params_get_buffer_size_ ) >( library_, "snd_pcm_hw_params_get_buffer_size" );
  snd_pcm_hw_params_get_buffer_size_min_ = loadSymbol< decltype( snd_pcm_hw_params_get_buffer_size_min_ ) >( library_, "snd_pcm_hw_params_get_buffer_size_min" );
  snd_pcm_hw_params_get_buffer_size_max_ = loadSymbol< decltype( snd_pcm_hw_params_get_buffer_size_max_ ) >( library_, "snd_pcm_hw_params_get_buffer_size_max" );
  snd_pcm_hw_params_test_buffer_size_ = loadSymbol< decltype( snd_pcm_hw_params_test_buffer_size_ ) >( library_, "snd_pcm_hw_params_test_buffer_size" );
  snd_pcm_hw_params_set_buffer_size_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_size_ ) >( library_, "snd_pcm_hw_params_set_buffer_size" );
  snd_pcm_hw_params_set_buffer_size_min_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_size_min_ ) >( library_, "snd_pcm_hw_params_set_buffer_size_min" );
  snd_pcm_hw_params_set_buffer_size_max_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_size_max_ ) >( library_, "snd_pcm_hw_params_set_buffer_size_max" );
  snd_pcm_hw_params_set_buffer_size_minmax_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_size_minmax_ ) >( library_, "snd_pcm_hw_params_set_buffer_size_minmax" );
  snd_pcm_hw_params_set_buffer_size_near_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_size_near_ ) >( library_, "snd_pcm_hw_params_set_buffer_size_near" );
  snd_pcm_hw_params_set_buffer_size_first_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_size_first_ ) >( library_, "snd_pcm_hw_params_set_buffer_size_first" );
  snd_pcm_hw_params_set_buffer_size_last_ = loadSymbol< decltype( snd_pcm_hw_params_set_buffer_size_last_ ) >( library_, "snd_pcm_hw_params_set_buffer_size_last" );
  snd_pcm_hw_params_get_min_align_ = loadSymbol< decltype( snd_pcm_hw_params_get_min_align_ ) >( library_, "snd_pcm_hw_params_get_min_align" );
  snd_pcm_sw_params_sizeof_ = loadSymbol< decltype( snd_pcm_sw_params_sizeof_ ) >( library_, "snd_pcm_sw_params_sizeof" );
  snd_pcm_sw_params_malloc_ = loadSymbol< decltype( snd_pcm_sw_params_malloc_ ) >( library_, "snd_pcm_sw_params_malloc" );
  snd_pcm_sw_params_free_ = loadSymbol< decltype( snd_pcm_sw_params_free_ ) >( library_, "snd_pcm_sw_params_free" );
  snd_pcm_sw_params_copy_ = loadSymbol< decltype( snd_pcm_sw_params_copy_ ) >( library_, "snd_pcm_sw_params_copy" );
  snd_pcm_sw_params_get_boundary_ = loadSymbol< decltype( snd_pcm_sw_params_get_boundary_ ) >( library_, "snd_pcm_sw_params_get_boundary" );
  snd_pcm_sw_params_set_tstamp_mode_ = loadSymbol< decltype( snd_pcm_sw_params_set_tstamp_mode_ ) >( library_, "snd_pcm_sw_params_set_tstamp_mode" );
  snd_pcm_sw_params_get_tstamp_mode_ = loadSymbol< decltype( snd_pcm_sw_params_get_tstamp_mode_ ) >( library_, "snd_pcm_sw_params_get_tstamp_mode" );
  snd_pcm_sw_params_set_tstamp_type_ = loadSymbol< decltype( snd_pcm_sw_params_set_tstamp_type_ ) >( library_, "snd_pcm_sw_params_set_tstamp_type" );
  snd_pcm_sw_params_get_tstamp_type_ = loadSymbol< decltype( snd_pcm_sw_params_get_tstamp_type_ ) >( library_, "snd_pcm_sw_params_get_tstamp_type" );
  snd_pcm_sw_params_set_avail_min_ = loadSymbol< decltype( snd_pcm_sw_params_set_avail_min_ ) >( library_, "snd_pcm_sw_params_set_avail_min" );
  snd_pcm_sw_params_get_avail_min_ = loadSymbol< decltype( snd_pcm_sw_params_get_avail_min_ ) >( library_, "snd_pcm_sw_params_get_avail_min" );
  snd_pcm_sw_params_set_period_event_ = loadSymbol< decltype( snd_pcm_sw_params_set_period_event_ ) >( library_, "snd_pcm_sw_params_set_period_event" );
  snd_pcm_sw_params_get_period_event_ = loadSymbol< decltype( snd_pcm_sw_params_get_period_event_ ) >( library_, "snd_pcm_sw_params_get_period_event" );
  snd_pcm_sw_params_set_start_threshold_ = loadSymbol< decltype( snd_pcm_sw_params_set_start_threshold_ ) >( library_, "snd_pcm_sw_params_set_start_threshold" );
  snd_pcm_sw_params_get_start_threshold_ = loadSymbol< decltype( snd_pcm_sw_params_get_start_threshold_ ) >( library_, "snd_pcm_sw_params_get_start_threshold" );
  snd_pcm_sw_params_set_stop_threshold_ = loadSymbol< decltype( snd_pcm_sw_params_set_stop_threshold_ ) >( library_, "snd_pcm_sw_params_set_stop_threshold" );
  snd_pcm_sw_params_get_stop_threshold_ = loadSymbol< decltype( snd_pcm_sw_params_get_stop_threshold_ ) >( library_, "snd_pcm_sw_params_get_stop_threshold" );
  snd_pcm_sw_params_set_silence_threshold_ = loadSymbol< decltype( snd_pcm_sw_params_set_silence_threshold_ ) >( library_, "snd_pcm_sw_params_set_silence_threshold" );
  snd_pcm_sw_params_get_silence_threshold_ = loadSymbol< decltype( snd_pcm_sw_params_get_silence_threshold_ ) >( library_, "snd_pcm_sw_params_get_silence_threshold" );
  snd_pcm_sw_params_set_silence_size_ = loadSymbol< decltype( snd_pcm_sw_params_set_silence_size_ ) >( library_, "snd_pcm_sw_params_set_silence_size" );
  snd_pcm_sw_params_get_silence_size_ = loadSymbol< decltype( snd_pcm_sw_params_get_silence_size_ ) >( library_, "snd_pcm_sw_params_get_silence_size" );
  snd_pcm_access_mask_sizeof_ = loadSymbol< decltype( snd_pcm_access_mask_sizeof_ ) >( library_, "snd_pcm_access_mask_sizeof" );
  snd_pcm_access_mask_malloc_ = loadSymbol< decltype( snd_pcm_access_mask_malloc_ ) >( library_, "snd_pcm_access_mask_malloc" );
  snd_pcm_access_mask_free_ = loadSymbol< decltype( snd_pcm_access_mask_free_ ) >( library_, "snd_pcm_access_mask_free" );
  snd_pcm_access_mask_copy_ = loadSymbol< decltype( snd_pcm_access_mask_copy_ ) >( library_, "snd_pcm_access_mask_copy" );
  snd_pcm_access_mask_none_ = loadSymbol< decltype( snd_pcm_access_mask_none_ ) >( library_, "snd_pcm_access_mask_none" );
  snd_pcm_access_mask_any_ = loadSymbol< decltype( snd_pcm_access_mask_any_ ) >( library_, "snd_pcm_access_mask_any" );
  snd_pcm_access_mask_test_ = loadSymbol< decltype( snd_pcm_access_mask_test_ ) >( library_, "snd_pcm_access_mask_test" );
  snd_pcm_access_mask_empty_ = loadSymbol< decltype( snd_pcm_access_mask_empty_ ) >( library_, "snd_pcm_access_mask_empty" );
  snd_pcm_access_mask_set_ = loadSymbol< decltype( snd_pcm_access_mask_set_ ) >( library_, "snd_pcm_access_mask_set" );
  snd_pcm_access_mask_reset_ = loadSymbol< decltype( snd_pcm_access_mask_reset_ ) >( library_, "snd_pcm_access_mask_reset" );
  snd_pcm_format_mask_sizeof_ = loadSymbol< decltype( snd_pcm_format_mask_sizeof_ ) >( library_, "snd_pcm_format_mask_sizeof" );
  snd_pcm_format_mask_malloc_ = loadSymbol< decltype( snd_pcm_format_mask_malloc_ ) >( library_, "snd_pcm_format_mask_malloc" );
  snd_pcm_format_mask_free_ = loadSymbol< decltype( snd_pcm_format_mask_free_ ) >( library_, "snd_pcm_format_mask_free" );
  snd_pcm_format_mask_copy_ = loadSymbol< decltype( snd_pcm_format_mask_copy_ ) >( library_, "snd_pcm_format_mask_copy" );
  snd_pcm_format_mask_none_ = loadSymbol< decltype( snd_pcm_format_mask_none_ ) >( library_, "snd_pcm_format_mask_none" );
  snd_pcm_format_mask_any_ = loadSymbol< decltype( snd_pcm_format_mask_any_ ) >( library_, "snd_pcm_format_mask_any" );
  snd_pcm_format_mask_test_ = loadSymbol< decltype( snd_pcm_format_mask_test_ ) >( library_, "snd_pcm_format_mask_test" );
  snd_pcm_format_mask_empty_ = loadSymbol< decltype( snd_pcm_format_mask_empty_ ) >( library_, "snd_pcm_format_mask_empty" );
  snd_pcm_format_mask_set_ = loadSymbol< decltype( snd_pcm_format_mask_set_ ) >( library_, "snd_pcm_format_mask_set" );
  snd_pcm_format_mask_reset_ = loadSymbol< decltype( snd_pcm_format_mask_reset_ ) >( library_, "snd_pcm_format_mask_reset" );
  snd_pcm_subformat_mask_sizeof_ = loadSymbol< decltype( snd_pcm_subformat_mask_sizeof_ ) >( library_, "snd_pcm_subformat_mask_sizeof" );
  snd_pcm_subformat_mask_malloc_ = loadSymbol< decltype( snd_pcm_subformat_mask_malloc_ ) >( library_, "snd_pcm_subformat_mask_malloc" );
  snd_pcm_subformat_mask_free_ = loadSymbol< decltype( snd_pcm_subformat_mask_free_ ) >( library_, "snd_pcm_subformat_mask_free" );
  snd_pcm_subformat_mask_copy_ = loadSymbol< decltype( snd_pcm_subformat_mask_copy_ ) >( library_, "snd_pcm_subformat_mask_copy" );
  snd_pcm_subformat_mask_none_ = loadSymbol< decltype( snd_pcm_subformat_mask_none_ ) >( library_, "snd_pcm_subformat_mask_none" );
  snd_pcm_subformat_mask_any_ = loadSymbol< decltype( snd_pcm_subformat_mask_any_ ) >( library_, "snd_pcm_subformat_mask_any" );
  snd_pcm_subformat_mask_test_ = loadSymbol< decltype( snd_pcm_subformat_mask_test_ ) >( library_, "snd_pcm_subformat_mask_test" );
  snd_pcm_subformat_mask_empty_ = loadSymbol< decltype( snd_pcm_subformat_mask_empty_ ) >( library_, "snd_pcm_subformat_mask_empty" );
  snd_pcm_subformat_mask_set_ = loadSymbol< decltype( snd_pcm_subformat_mask_set_ ) >( library_, "snd_pcm_subformat_mask_set" );
  snd_pcm_subformat_mask_reset_ = loadSymbol< decltype( snd_pcm_subformat_mask_reset_ ) >( library_, "snd_pcm_subformat_mask_reset" );
  snd_pcm_status_sizeof_ = loadSymbol< decltype( snd_pcm_status_sizeof_ ) >( library_, "snd_pcm_status_sizeof" );
  snd_pcm_status_malloc_ = loadSymbol< decltype( snd_pcm_status_malloc_ ) >( library_, "snd_pcm_status_malloc" );
  snd_pcm_status_free_ = loadSymbol< decltype( snd_pcm_status_free_ ) >( library_, "snd_pcm_status_free" );
  snd_pcm_status_copy_ = loadSymbol< decltype( snd_pcm_status_copy_ ) >( library_, "snd_pcm_status_copy" );
  snd_pcm_status_get_state_ = loadSymbol< decltype( snd_pcm_status_get_state_ ) >( library_, "snd_pcm_status_get_state" );
  snd_pcm_status_get_trigger_tstamp_ = loadSymbol< decltype( snd_pcm_status_get_trigger_tstamp_ ) >( library_, "snd_pcm_status_get_trigger_tstamp" );
  snd_pcm_status_get_trigger_htstamp_ = loadSymbol< decltype( snd_pcm_status_get_trigger_htstamp_ ) >( library_, "snd_pcm_status_get_trigger_htstamp" );
  snd_pcm_status_get_tstamp_ = loadSymbol< decltype( snd_pcm_status_get_tstamp_ ) >( library_, "snd_pcm_status_get_tstamp" );
  snd_pcm_status_get_htstamp_ = loadSymbol< decltype( snd_pcm_status_get_htstamp_ ) >( library_, "snd_pcm_status_get_htstamp" );
  snd_pcm_status_get_audio_htstamp_ = loadSymbol< decltype( snd_pcm_status_get_audio_htstamp_ ) >( library_, "snd_pcm_status_get_audio_htstamp" );
  snd_pcm_status_get_driver_htstamp_ = loadSymbol< decltype( snd_pcm_status_get_driver_htstamp_ ) >( library_, "snd_pcm_status_get_driver_htstamp" );
  snd_pcm_status_get_audio_htstamp_report_ = loadSymbol< decltype( snd_pcm_status_get_audio_htstamp_report_ ) >( library_, "snd_pcm_status_get_audio_htstamp_report" );
  snd_pcm_status_set_audio_htstamp_config_ = loadSymbol< decltype( snd_pcm_status_set_audio_htstamp_config_ ) >( library_, "snd_pcm_status_set_audio_htstamp_config" );
  snd_pcm_pack_audio_tstamp_config_ = loadSymbol< decltype( snd_pcm_pack_audio_tstamp_config_ ) >( library_, "snd_pcm_pack_audio_tstamp_config" );
  snd_pcm_unpack_audio_tstamp_report_ = loadSymbol< decltype( snd_pcm_unpack_audio_tstamp_report_ ) >( library_, "snd_pcm_unpack_audio_tstamp_report" );
  snd_pcm_status_get_delay_ = loadSymbol< decltype( snd_pcm_status_get_delay_ ) >( library_, "snd_pcm_status_get_delay" );
  snd_pcm_status_get_avail_ = loadSymbol< decltype( snd_pcm_status_get_avail_ ) >( library_, "snd_pcm_status_get_avail" );
  snd_pcm_status_get_avail_max_ = loadSymbol< decltype( snd_pcm_status_get_avail_max_ ) >( library_, "snd_pcm_status_get_avail_max" );
  snd_pcm_status_get_overrange_ = loadSymbol< decltype( snd_pcm_status_get_overrange_ ) >( library_, "snd_pcm_status_get_overrange" );
  snd_pcm_type_name_ = loadSymbol< decltype( snd_pcm_type_name_ ) >( library_, "snd_pcm_type_name" );
  snd_pcm_stream_name_ = loadSymbol< decltype( snd_pcm_stream_name_ ) >( library_, "snd_pcm_stream_name" );
  snd_pcm_access_name_ = loadSymbol< decltype( snd_pcm_access_name_ ) >( library_, "snd_pcm_access_name" );
  snd_pcm_format_name_ = loadSymbol< decltype( snd_pcm_format_name_ ) >( library_, "snd_pcm_format_name" );
  snd_pcm_format_description_ = loadSymbol< decltype( snd_pcm_format_description_ ) >( library_, "snd_pcm_format_description" );
  snd_pcm_subformat_name_ = loadSymbol< decltype( snd_pcm_subformat_name_ ) >( library_, "snd_pcm_subformat_name" );
  snd_pcm_subformat_description_ = loadSymbol< decltype( snd_pcm_subformat_description_ ) >( library_, "snd_pcm_subformat_description" );
  snd_pcm_subformat_value_ = loadSymbol< decltype( snd_pcm_subformat_value_ ) >( library_, "snd_pcm_subformat_value" );
  snd_pcm_format_value_ = loadSymbol< decltype( snd_pcm_format_value_ ) >( library_, "snd_pcm_format_value" );
  snd_pcm_tstamp_mode_name_ = loadSymbol< decltype( snd_pcm_tstamp_mode_name_ ) >( library_, "snd_pcm_tstamp_mode_name" );
  snd_pcm_state_name_ = loadSymbol< decltype( snd_pcm_state_name_ ) >( library_, "snd_pcm_state_name" );
  // snd_pcm_dump_ = loadSymbol< decltype( snd_pcm_dump_ ) >( library_, "snd_pcm_dump" );
  // snd_pcm_dump_hw_setup_ = loadSymbol< decltype( snd_pcm_dump_hw_setup_ ) >( library_, "snd_pcm_dump_hw_setup" );
  // snd_pcm_dump_sw_setup_ = loadSymbol< decltype( snd_pcm_dump_sw_setup_ ) >( library_, "snd_pcm_dump_sw_setup" );
  // snd_pcm_dump_setup_ = loadSymbol< decltype( snd_pcm_dump_setup_ ) >( library_, "snd_pcm_dump_setup" );
  // snd_pcm_hw_params_dump_ = loadSymbol< decltype( snd_pcm_hw_params_dump_ ) >( library_, "snd_pcm_hw_params_dump" );
  // snd_pcm_sw_params_dump_ = loadSymbol< decltype( snd_pcm_sw_params_dump_ ) >( library_, "snd_pcm_sw_params_dump" );
  // snd_pcm_status_dump_ = loadSymbol< decltype( snd_pcm_status_dump_ ) >( library_, "snd_pcm_status_dump" );
  snd_pcm_mmap_begin_ = loadSymbol< decltype( snd_pcm_mmap_begin_ ) >( library_, "snd_pcm_mmap_begin" );
  snd_pcm_mmap_commit_ = loadSymbol< decltype( snd_pcm_mmap_commit_ ) >( library_, "snd_pcm_mmap_commit" );
  snd_pcm_mmap_writei_ = loadSymbol< decltype( snd_pcm_mmap_writei_ ) >( library_, "snd_pcm_mmap_writei" );
  snd_pcm_mmap_readi_ = loadSymbol< decltype( snd_pcm_mmap_readi_ ) >( library_, "snd_pcm_mmap_readi" );
  snd_pcm_mmap_writen_ = loadSymbol< decltype( snd_pcm_mmap_writen_ ) >( library_, "snd_pcm_mmap_writen" );
  snd_pcm_mmap_readn_ = loadSymbol< decltype( snd_pcm_mmap_readn_ ) >( library_, "snd_pcm_mmap_readn" );
  snd_pcm_format_signed_ = loadSymbol< decltype( snd_pcm_format_signed_ ) >( library_, "snd_pcm_format_signed" );
  snd_pcm_format_unsigned_ = loadSymbol< decltype( snd_pcm_format_unsigned_ ) >( library_, "snd_pcm_format_unsigned" );
  snd_pcm_format_linear_ = loadSymbol< decltype( snd_pcm_format_linear_ ) >( library_, "snd_pcm_format_linear" );
  snd_pcm_format_float_ = loadSymbol< decltype( snd_pcm_format_float_ ) >( library_, "snd_pcm_format_float" );
  snd_pcm_format_little_endian_ = loadSymbol< decltype( snd_pcm_format_little_endian_ ) >( library_, "snd_pcm_format_little_endian" );
  snd_pcm_format_big_endian_ = loadSymbol< decltype( snd_pcm_format_big_endian_ ) >( library_, "snd_pcm_format_big_endian" );
  snd_pcm_format_cpu_endian_ = loadSymbol< decltype( snd_pcm_format_cpu_endian_ ) >( library_, "snd_pcm_format_cpu_endian" );
  snd_pcm_format_width_ = loadSymbol< decltype( snd_pcm_format_width_ ) >( library_, "snd_pcm_format_width" );
  snd_pcm_format_physical_width_ = loadSymbol< decltype( snd_pcm_format_physical_width_ ) >( library_, "snd_pcm_format_physical_width" );
  snd_pcm_build_linear_format_ = loadSymbol< decltype( snd_pcm_build_linear_format_ ) >( library_, "snd_pcm_build_linear_format" );
  snd_pcm_format_size_ = loadSymbol< decltype( snd_pcm_format_size_ ) >( library_, "snd_pcm_format_size" );
  snd_pcm_format_silence_ = loadSymbol< decltype( snd_pcm_format_silence_ ) >( library_, "snd_pcm_format_silence" );
  snd_pcm_format_silence_16_ = loadSymbol< decltype( snd_pcm_format_silence_16_ ) >( library_, "snd_pcm_format_silence_16" );
  snd_pcm_format_silence_32_ = loadSymbol< decltype( snd_pcm_format_silence_32_ ) >( library_, "snd_pcm_format_silence_32" );
  snd_pcm_format_silence_64_ = loadSymbol< decltype( snd_pcm_format_silence_64_ ) >( library_, "snd_pcm_format_silence_64" );
  snd_pcm_format_set_silence_ = loadSymbol< decltype( snd_pcm_format_set_silence_ ) >( library_, "snd_pcm_format_set_silence" );
  snd_pcm_bytes_to_frames_ = loadSymbol< decltype( snd_pcm_bytes_to_frames_ ) >( library_, "snd_pcm_bytes_to_frames" );
  snd_pcm_frames_to_bytes_ = loadSymbol< decltype( snd_pcm_frames_to_bytes_ ) >( library_, "snd_pcm_frames_to_bytes" );
  snd_pcm_bytes_to_samples_ = loadSymbol< decltype( snd_pcm_bytes_to_samples_ ) >( library_, "snd_pcm_bytes_to_samples" );
  snd_pcm_samples_to_bytes_ = loadSymbol< decltype( snd_pcm_samples_to_bytes_ ) >( library_, "snd_pcm_samples_to_bytes" );
  snd_pcm_area_silence_ = loadSymbol< decltype( snd_pcm_area_silence_ ) >( library_, "snd_pcm_area_silence" );
  snd_pcm_areas_silence_ = loadSymbol< decltype( snd_pcm_areas_silence_ ) >( library_, "snd_pcm_areas_silence" );
  snd_pcm_area_copy_ = loadSymbol< decltype( snd_pcm_area_copy_ ) >( library_, "snd_pcm_area_copy" );
  snd_pcm_areas_copy_ = loadSymbol< decltype( snd_pcm_areas_copy_ ) >( library_, "snd_pcm_areas_copy" );
  snd_pcm_areas_copy_wrap_ = loadSymbol< decltype( snd_pcm_areas_copy_wrap_ ) >( library_, "snd_pcm_areas_copy_wrap" );
  snd_pcm_channel_area_addr_ = loadSymbol< decltype( snd_pcm_channel_area_addr_ ) >( library_, "snd_pcm_channel_area_addr" );
  snd_pcm_channel_area_step_ = loadSymbol< decltype( snd_pcm_channel_area_step_ ) >( library_, "snd_pcm_channel_area_step" );
  snd_pcm_hook_func_t_ = loadSymbol< decltype( snd_pcm_hook_func_t_ ) >( library_, "snd_pcm_hook_func_t" );
  snd_pcm_hook_get_pcm_ = loadSymbol< decltype( snd_pcm_hook_get_pcm_ ) >( library_, "snd_pcm_hook_get_pcm" );
  snd_pcm_hook_get_private_ = loadSymbol< decltype( snd_pcm_hook_get_private_ ) >( library_, "snd_pcm_hook_get_private" );
  snd_pcm_hook_set_private_ = loadSymbol< decltype( snd_pcm_hook_set_private_ ) >( library_, "snd_pcm_hook_set_private" );
  snd_pcm_hook_add_ = loadSymbol< decltype( snd_pcm_hook_add_ ) >( library_, "snd_pcm_hook_add" );
  snd_pcm_hook_remove_ = loadSymbol< decltype( snd_pcm_hook_remove_ ) >( library_, "snd_pcm_hook_remove" );
  snd_pcm_meter_get_bufsize_ = loadSymbol< decltype( snd_pcm_meter_get_bufsize_ ) >( library_, "snd_pcm_meter_get_bufsize" );
  snd_pcm_meter_get_channels_ = loadSymbol< decltype( snd_pcm_meter_get_channels_ ) >( library_, "snd_pcm_meter_get_channels" );
  snd_pcm_meter_get_rate_ = loadSymbol< decltype( snd_pcm_meter_get_rate_ ) >( library_, "snd_pcm_meter_get_rate" );
  snd_pcm_meter_get_now_ = loadSymbol< decltype( snd_pcm_meter_get_now_ ) >( library_, "snd_pcm_meter_get_now" );
  snd_pcm_meter_get_boundary_ = loadSymbol< decltype( snd_pcm_meter_get_boundary_ ) >( library_, "snd_pcm_meter_get_boundary" );
  snd_pcm_meter_add_scope_ = loadSymbol< decltype( snd_pcm_meter_add_scope_ ) >( library_, "snd_pcm_meter_add_scope" );
  snd_pcm_meter_search_scope_ = loadSymbol< decltype( snd_pcm_meter_search_scope_ ) >( library_, "snd_pcm_meter_search_scope" );
  snd_pcm_scope_malloc_ = loadSymbol< decltype( snd_pcm_scope_malloc_ ) >( library_, "snd_pcm_scope_malloc" );
  snd_pcm_scope_set_ops_ = loadSymbol< decltype( snd_pcm_scope_set_ops_ ) >( library_, "snd_pcm_scope_set_ops" );
  snd_pcm_scope_set_name_ = loadSymbol< decltype( snd_pcm_scope_set_name_ ) >( library_, "snd_pcm_scope_set_name" );
  snd_pcm_scope_get_name_ = loadSymbol< decltype( snd_pcm_scope_get_name_ ) >( library_, "snd_pcm_scope_get_name" );
  snd_pcm_scope_get_callback_private_ = loadSymbol< decltype( snd_pcm_scope_get_callback_private_ ) >( library_, "snd_pcm_scope_get_callback_private" );
  snd_pcm_scope_set_callback_private_ = loadSymbol< decltype( snd_pcm_scope_set_callback_private_ ) >( library_, "snd_pcm_scope_set_callback_private" );
  snd_pcm_scope_s16_open_ = loadSymbol< decltype( snd_pcm_scope_s16_open_ ) >( library_, "snd_pcm_scope_s16_open" );
  snd_pcm_scope_s16_get_channel_buffer_ = loadSymbol< decltype( snd_pcm_scope_s16_get_channel_buffer_ ) >( library_, "snd_pcm_scope_s16_get_channel_buffer" );
  snd_spcm_init_ = loadSymbol< decltype( snd_spcm_init_ ) >( library_, "snd_spcm_init" );
  snd_spcm_init_duplex_ = loadSymbol< decltype( snd_spcm_init_duplex_ ) >( library_, "snd_spcm_init_duplex" );
  snd_spcm_init_get_params_ = loadSymbol< decltype( snd_spcm_init_get_params_ ) >( library_, "snd_spcm_init_get_params" );
}

bool ALSA::isAvailable() const {
  return true
      && library_
      && snd_asoundlib_version_
      && snd_async_add_handler_
      && snd_async_del_handler_
      && snd_async_handler_get_fd_
      && snd_async_handler_get_signo_
      && snd_async_handler_get_callback_private_
      // && snd_shm_area_create_
      // && snd_shm_area_share_
      // && snd_shm_area_destroy_
      && snd_user_file_
      && snd_pcm_open_
      // && snd_pcm_open_lconf_
      // && snd_pcm_open_fallback_
      && snd_pcm_close_
      && snd_pcm_name_
      && snd_pcm_type_
      && snd_pcm_stream_
      && snd_pcm_poll_descriptors_count_
      // && snd_pcm_poll_descriptors_
      // && snd_pcm_poll_descriptors_revents_
      && snd_pcm_nonblock_
      && snd_pcm_abort_
      && snd_async_add_pcm_handler_
      && snd_async_handler_get_pcm_
      && snd_pcm_info_
      && snd_pcm_hw_params_current_
      && snd_pcm_hw_params_
      && snd_pcm_hw_free_
      && snd_pcm_sw_params_current_
      && snd_pcm_sw_params_
      && snd_pcm_prepare_
      && snd_pcm_reset_
      && snd_pcm_status_
      && snd_pcm_start_
      && snd_pcm_drop_
      && snd_pcm_drain_
      && snd_pcm_pause_
      && snd_pcm_state_
      && snd_pcm_hwsync_
      && snd_pcm_delay_
      && snd_pcm_resume_
      && snd_pcm_htimestamp_
      && snd_pcm_avail_
      && snd_pcm_avail_update_
      && snd_pcm_avail_delay_
      && snd_pcm_rewindable_
      && snd_pcm_rewind_
      && snd_pcm_forwardable_
      && snd_pcm_forward_
      && snd_pcm_writei_
      && snd_pcm_readi_
      && snd_pcm_writen_
      && snd_pcm_readn_
      && snd_pcm_wait_
      && snd_pcm_link_
      && snd_pcm_unlink_
      && snd_pcm_query_chmaps_
      && snd_pcm_query_chmaps_from_hw_
      && snd_pcm_free_chmaps_
      && snd_pcm_get_chmap_
      && snd_pcm_set_chmap_
      && snd_pcm_chmap_type_name_
      && snd_pcm_chmap_name_
      && snd_pcm_chmap_long_name_
      && snd_pcm_chmap_print_
      && snd_pcm_chmap_from_string_
      && snd_pcm_chmap_parse_string_
      && snd_pcm_recover_
      && snd_pcm_set_params_
      && snd_pcm_get_params_
      && snd_pcm_info_sizeof_
      && snd_pcm_info_malloc_
      && snd_pcm_info_free_
      && snd_pcm_info_copy_
      && snd_pcm_info_get_device_
      && snd_pcm_info_get_subdevice_
      && snd_pcm_info_get_stream_
      && snd_pcm_info_get_card_
      && snd_pcm_info_get_id_
      && snd_pcm_info_get_name_
      && snd_pcm_info_get_subdevice_name_
      && snd_pcm_info_get_class_
      && snd_pcm_info_get_subclass_
      && snd_pcm_info_get_subdevices_count_
      && snd_pcm_info_get_subdevices_avail_
      && snd_pcm_info_get_sync_
      && snd_pcm_info_set_device_
      && snd_pcm_info_set_subdevice_
      && snd_pcm_info_set_stream_
      && snd_pcm_hw_params_any_
      && snd_pcm_hw_params_can_mmap_sample_resolution_
      && snd_pcm_hw_params_is_double_
      && snd_pcm_hw_params_is_batch_
      && snd_pcm_hw_params_is_block_transfer_
      && snd_pcm_hw_params_is_monotonic_
      && snd_pcm_hw_params_can_overrange_
      && snd_pcm_hw_params_can_pause_
      && snd_pcm_hw_params_can_resume_
      && snd_pcm_hw_params_is_half_duplex_
      && snd_pcm_hw_params_is_joint_duplex_
      && snd_pcm_hw_params_can_sync_start_
      && snd_pcm_hw_params_can_disable_period_wakeup_
      && snd_pcm_hw_params_is_perfect_drain_
      && snd_pcm_hw_params_supports_audio_wallclock_ts_
      && snd_pcm_hw_params_supports_audio_ts_type_
      && snd_pcm_hw_params_get_rate_numden_
      && snd_pcm_hw_params_get_sbits_
      && snd_pcm_hw_params_get_fifo_size_
      && snd_pcm_hw_params_get_sync_
      && snd_pcm_hw_params_sizeof_
      && snd_pcm_hw_params_malloc_
      && snd_pcm_hw_params_free_
      && snd_pcm_hw_params_copy_
      && snd_pcm_hw_params_get_access_
      && snd_pcm_hw_params_test_access_
      && snd_pcm_hw_params_set_access_
      && snd_pcm_hw_params_set_access_first_
      && snd_pcm_hw_params_set_access_last_
      && snd_pcm_hw_params_set_access_mask_
      && snd_pcm_hw_params_get_access_mask_
      && snd_pcm_hw_params_get_format_
      && snd_pcm_hw_params_test_format_
      && snd_pcm_hw_params_set_format_
      && snd_pcm_hw_params_set_format_first_
      && snd_pcm_hw_params_set_format_last_
      && snd_pcm_hw_params_set_format_mask_
      && snd_pcm_hw_params_get_format_mask_
      && snd_pcm_hw_params_get_subformat_
      && snd_pcm_hw_params_test_subformat_
      && snd_pcm_hw_params_set_subformat_
      && snd_pcm_hw_params_set_subformat_first_
      && snd_pcm_hw_params_set_subformat_last_
      && snd_pcm_hw_params_set_subformat_mask_
      && snd_pcm_hw_params_get_subformat_mask_
      && snd_pcm_hw_params_get_channels_
      && snd_pcm_hw_params_get_channels_min_
      && snd_pcm_hw_params_get_channels_max_
      && snd_pcm_hw_params_test_channels_
      && snd_pcm_hw_params_set_channels_
      && snd_pcm_hw_params_set_channels_min_
      && snd_pcm_hw_params_set_channels_max_
      && snd_pcm_hw_params_set_channels_minmax_
      && snd_pcm_hw_params_set_channels_near_
      && snd_pcm_hw_params_set_channels_first_
      && snd_pcm_hw_params_set_channels_last_
      && snd_pcm_hw_params_get_rate_
      && snd_pcm_hw_params_get_rate_min_
      && snd_pcm_hw_params_get_rate_max_
      && snd_pcm_hw_params_test_rate_
      && snd_pcm_hw_params_set_rate_
      && snd_pcm_hw_params_set_rate_min_
      && snd_pcm_hw_params_set_rate_max_
      && snd_pcm_hw_params_set_rate_minmax_
      && snd_pcm_hw_params_set_rate_near_
      && snd_pcm_hw_params_set_rate_first_
      && snd_pcm_hw_params_set_rate_last_
      && snd_pcm_hw_params_set_rate_resample_
      && snd_pcm_hw_params_get_rate_resample_
      && snd_pcm_hw_params_set_export_buffer_
      && snd_pcm_hw_params_get_export_buffer_
      && snd_pcm_hw_params_set_period_wakeup_
      && snd_pcm_hw_params_get_period_wakeup_
      && snd_pcm_hw_params_set_drain_silence_
      && snd_pcm_hw_params_get_drain_silence_
      && snd_pcm_hw_params_get_period_time_
      && snd_pcm_hw_params_get_period_time_min_
      && snd_pcm_hw_params_get_period_time_max_
      && snd_pcm_hw_params_test_period_time_
      && snd_pcm_hw_params_set_period_time_
      && snd_pcm_hw_params_set_period_time_min_
      && snd_pcm_hw_params_set_period_time_max_
      && snd_pcm_hw_params_set_period_time_minmax_
      && snd_pcm_hw_params_set_period_time_near_
      && snd_pcm_hw_params_set_period_time_first_
      && snd_pcm_hw_params_set_period_time_last_
      && snd_pcm_hw_params_get_period_size_
      && snd_pcm_hw_params_get_period_size_min_
      && snd_pcm_hw_params_get_period_size_max_
      && snd_pcm_hw_params_test_period_size_
      && snd_pcm_hw_params_set_period_size_
      && snd_pcm_hw_params_set_period_size_min_
      && snd_pcm_hw_params_set_period_size_max_
      && snd_pcm_hw_params_set_period_size_minmax_
      && snd_pcm_hw_params_set_period_size_near_
      && snd_pcm_hw_params_set_period_size_first_
      && snd_pcm_hw_params_set_period_size_last_
      && snd_pcm_hw_params_set_period_size_integer_
      && snd_pcm_hw_params_get_periods_
      && snd_pcm_hw_params_get_periods_min_
      && snd_pcm_hw_params_get_periods_max_
      && snd_pcm_hw_params_test_periods_
      && snd_pcm_hw_params_set_periods_
      && snd_pcm_hw_params_set_periods_min_
      && snd_pcm_hw_params_set_periods_max_
      && snd_pcm_hw_params_set_periods_minmax_
      && snd_pcm_hw_params_set_periods_near_
      && snd_pcm_hw_params_set_periods_first_
      && snd_pcm_hw_params_set_periods_last_
      && snd_pcm_hw_params_set_periods_integer_
      && snd_pcm_hw_params_get_buffer_time_
      && snd_pcm_hw_params_get_buffer_time_min_
      && snd_pcm_hw_params_get_buffer_time_max_
      && snd_pcm_hw_params_test_buffer_time_
      && snd_pcm_hw_params_set_buffer_time_
      && snd_pcm_hw_params_set_buffer_time_min_
      && snd_pcm_hw_params_set_buffer_time_max_
      && snd_pcm_hw_params_set_buffer_time_minmax_
      && snd_pcm_hw_params_set_buffer_time_near_
      && snd_pcm_hw_params_set_buffer_time_first_
      && snd_pcm_hw_params_set_buffer_time_last_
      && snd_pcm_hw_params_get_buffer_size_
      && snd_pcm_hw_params_get_buffer_size_min_
      && snd_pcm_hw_params_get_buffer_size_max_
      && snd_pcm_hw_params_test_buffer_size_
      && snd_pcm_hw_params_set_buffer_size_
      && snd_pcm_hw_params_set_buffer_size_min_
      && snd_pcm_hw_params_set_buffer_size_max_
      && snd_pcm_hw_params_set_buffer_size_minmax_
      && snd_pcm_hw_params_set_buffer_size_near_
      && snd_pcm_hw_params_set_buffer_size_first_
      && snd_pcm_hw_params_set_buffer_size_last_
      && snd_pcm_hw_params_get_min_align_
      && snd_pcm_sw_params_sizeof_
      && snd_pcm_sw_params_malloc_
      && snd_pcm_sw_params_free_
      && snd_pcm_sw_params_copy_
      && snd_pcm_sw_params_get_boundary_
      && snd_pcm_sw_params_set_tstamp_mode_
      && snd_pcm_sw_params_get_tstamp_mode_
      && snd_pcm_sw_params_set_tstamp_type_
      && snd_pcm_sw_params_get_tstamp_type_
      && snd_pcm_sw_params_set_avail_min_
      && snd_pcm_sw_params_get_avail_min_
      && snd_pcm_sw_params_set_period_event_
      && snd_pcm_sw_params_get_period_event_
      && snd_pcm_sw_params_set_start_threshold_
      && snd_pcm_sw_params_get_start_threshold_
      && snd_pcm_sw_params_set_stop_threshold_
      && snd_pcm_sw_params_get_stop_threshold_
      && snd_pcm_sw_params_set_silence_threshold_
      && snd_pcm_sw_params_get_silence_threshold_
      && snd_pcm_sw_params_set_silence_size_
      && snd_pcm_sw_params_get_silence_size_
      && snd_pcm_access_mask_sizeof_
      && snd_pcm_access_mask_malloc_
      && snd_pcm_access_mask_free_
      && snd_pcm_access_mask_copy_
      && snd_pcm_access_mask_none_
      && snd_pcm_access_mask_any_
      && snd_pcm_access_mask_test_
      && snd_pcm_access_mask_empty_
      && snd_pcm_access_mask_set_
      && snd_pcm_access_mask_reset_
      && snd_pcm_format_mask_sizeof_
      && snd_pcm_format_mask_malloc_
      && snd_pcm_format_mask_free_
      && snd_pcm_format_mask_copy_
      && snd_pcm_format_mask_none_
      && snd_pcm_format_mask_any_
      && snd_pcm_format_mask_test_
      && snd_pcm_format_mask_empty_
      && snd_pcm_format_mask_set_
      && snd_pcm_format_mask_reset_
      && snd_pcm_subformat_mask_sizeof_
      && snd_pcm_subformat_mask_malloc_
      && snd_pcm_subformat_mask_free_
      && snd_pcm_subformat_mask_copy_
      && snd_pcm_subformat_mask_none_
      && snd_pcm_subformat_mask_any_
      && snd_pcm_subformat_mask_test_
      && snd_pcm_subformat_mask_empty_
      && snd_pcm_subformat_mask_set_
      && snd_pcm_subformat_mask_reset_
      && snd_pcm_status_sizeof_
      && snd_pcm_status_malloc_
      && snd_pcm_status_free_
      && snd_pcm_status_copy_
      && snd_pcm_status_get_state_
      && snd_pcm_status_get_trigger_tstamp_
      && snd_pcm_status_get_trigger_htstamp_
      && snd_pcm_status_get_tstamp_
      && snd_pcm_status_get_htstamp_
      && snd_pcm_status_get_audio_htstamp_
      && snd_pcm_status_get_driver_htstamp_
      && snd_pcm_status_get_audio_htstamp_report_
      && snd_pcm_status_set_audio_htstamp_config_
      && snd_pcm_pack_audio_tstamp_config_
      && snd_pcm_unpack_audio_tstamp_report_
      && snd_pcm_status_get_delay_
      && snd_pcm_status_get_avail_
      && snd_pcm_status_get_avail_max_
      && snd_pcm_status_get_overrange_
      && snd_pcm_type_name_
      && snd_pcm_stream_name_
      && snd_pcm_access_name_
      && snd_pcm_format_name_
      && snd_pcm_format_description_
      && snd_pcm_subformat_name_
      && snd_pcm_subformat_description_
      && snd_pcm_subformat_value_
      && snd_pcm_format_value_
      && snd_pcm_tstamp_mode_name_
      && snd_pcm_state_name_
      // && snd_pcm_dump_
      // && snd_pcm_dump_hw_setup_
      // && snd_pcm_dump_sw_setup_
      // && snd_pcm_dump_setup_
      // && snd_pcm_hw_params_dump_
      // && snd_pcm_sw_params_dump_
      // && snd_pcm_status_dump_
      && snd_pcm_mmap_begin_
      && snd_pcm_mmap_commit_
      && snd_pcm_mmap_writei_
      && snd_pcm_mmap_readi_
      && snd_pcm_mmap_writen_
      && snd_pcm_mmap_readn_
      && snd_pcm_format_signed_
      && snd_pcm_format_unsigned_
      && snd_pcm_format_linear_
      && snd_pcm_format_float_
      && snd_pcm_format_little_endian_
      && snd_pcm_format_big_endian_
      && snd_pcm_format_cpu_endian_
      && snd_pcm_format_width_
      && snd_pcm_format_physical_width_
      && snd_pcm_build_linear_format_
      && snd_pcm_format_size_
      && snd_pcm_format_silence_
      && snd_pcm_format_silence_16_
      && snd_pcm_format_silence_32_
      && snd_pcm_format_silence_64_
      && snd_pcm_format_set_silence_
      && snd_pcm_bytes_to_frames_
      && snd_pcm_frames_to_bytes_
      && snd_pcm_bytes_to_samples_
      && snd_pcm_samples_to_bytes_
      && snd_pcm_area_silence_
      && snd_pcm_areas_silence_
      && snd_pcm_area_copy_
      && snd_pcm_areas_copy_
      && snd_pcm_areas_copy_wrap_
      && snd_pcm_channel_area_addr_
      && snd_pcm_channel_area_step_
      && snd_pcm_hook_func_t_
      && snd_pcm_hook_get_pcm_
      && snd_pcm_hook_get_private_
      && snd_pcm_hook_set_private_
      && snd_pcm_hook_add_
      && snd_pcm_hook_remove_
      && snd_pcm_meter_get_bufsize_
      && snd_pcm_meter_get_channels_
      && snd_pcm_meter_get_rate_
      && snd_pcm_meter_get_now_
      && snd_pcm_meter_get_boundary_
      && snd_pcm_meter_add_scope_
      && snd_pcm_meter_search_scope_
      && snd_pcm_scope_malloc_
      && snd_pcm_scope_set_ops_
      && snd_pcm_scope_set_name_
      && snd_pcm_scope_get_name_
      && snd_pcm_scope_get_callback_private_
      && snd_pcm_scope_set_callback_private_
      && snd_pcm_scope_s16_open_
      && snd_pcm_scope_s16_get_channel_buffer_
      && snd_spcm_init_
      && snd_spcm_init_duplex_
      && snd_spcm_init_get_params_
  ;
}

const char* ALSA::snd_asoundlib_version( void ) const {
  return snd_asoundlib_version_();
}
int ALSA::snd_async_add_handler( ALSA_detail::snd_async_handler_t** handler, int fd, ALSA_detail::snd_async_callback_t callback, void* private_data ) const {
  return snd_async_add_handler_( handler, fd, callback, private_data );
}
int ALSA::snd_async_del_handler( ALSA_detail::snd_async_handler_t* handler ) const {
  return snd_async_del_handler_( handler );
}
int ALSA::snd_async_handler_get_fd( ALSA_detail::snd_async_handler_t* handler ) const {
  return snd_async_handler_get_fd_( handler );
}
int ALSA::snd_async_handler_get_signo( ALSA_detail::snd_async_handler_t* handler ) const {
  return snd_async_handler_get_signo_( handler );
}
void* ALSA::snd_async_handler_get_callback_private( ALSA_detail::snd_async_handler_t* handler ) const {
  return snd_async_handler_get_callback_private_( handler );
}
// ALSA_detail::snd_shm_area* ALSA::snd_shm_area_create( int shmid, void* ptr ) const {
//   return snd_shm_area_create_( shmid, ptr );
// }
// ALSA_detail::snd_shm_area* ALSA::snd_shm_area_share( ALSA_detail::snd_shm_area * area ) const {
//   return snd_shm_area_share_( area );
// }
// int ALSA::snd_shm_area_destroy( ALSA_detail::snd_shm_area* area ) const {
//   return snd_shm_area_destroy_( area );
// }
int ALSA::snd_user_file( const char* file, char** result ) const {
  return snd_user_file_( file, result );
}
int ALSA::snd_pcm_open( ALSA_detail::snd_pcm_t** pcm, const char* name, ALSA_detail::snd_pcm_stream_t stream, int mode ) const {
  return snd_pcm_open_( pcm, name, stream, mode );
}
// int ALSA::snd_pcm_open_lconf( ALSA_detail::snd_pcm_t** pcm, const char* name, ALSA_detail::snd_pcm_stream_t stream, int mode, ALSA_detail::snd_config_t* lconf ) const {
//   return snd_pcm_open_lconf_( pcm, name, stream, mode, lconf );
// }
// int ALSA::snd_pcm_open_fallback( ALSA_detail::snd_pcm_t** pcm, ALSA_detail::snd_config_t* root, const char* name, const char* orig_name, ALSA_detail::snd_pcm_stream_t stream, int mode ) const {
//   return snd_pcm_open_fallback_( pcm, root, name, orig_name, stream, mode );
// }
int ALSA::snd_pcm_close( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_close_( pcm );
}
const char* ALSA::snd_pcm_name( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_name_( pcm );
}
ALSA_detail::snd_pcm_type_t ALSA::snd_pcm_type( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_type_( pcm );
}
ALSA_detail::snd_pcm_stream_t ALSA::snd_pcm_stream( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_stream_( pcm );
}
int ALSA::snd_pcm_poll_descriptors_count( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_poll_descriptors_count_( pcm );
}
// int ALSA::snd_pcm_poll_descriptors( ALSA_detail::snd_pcm_t* pcm, pollfd* pfds, unsigned int space ) const {
//   return snd_pcm_poll_descriptors_( pcm, pfds, space );
// }
// int ALSA::snd_pcm_poll_descriptors_revents( ALSA_detail::snd_pcm_t* pcm, pollfd* pfds, unsigned int nfds, unsigned short* revents ) const {
//   return snd_pcm_poll_descriptors_revents_( pcm, pfds, nfds, revents );
// }
int ALSA::snd_pcm_nonblock( ALSA_detail::snd_pcm_t* pcm, int nonblock ) const {
  return snd_pcm_nonblock_( pcm, nonblock );
}
int ALSA::snd_pcm_abort( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_abort_( pcm );
}
int ALSA::snd_async_add_pcm_handler( ALSA_detail::snd_async_handler_t** handler, ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_async_callback_t callback, void* private_data ) const {
  return snd_async_add_pcm_handler_( handler, pcm, callback, private_data );
}
ALSA_detail::snd_pcm_t* ALSA::snd_async_handler_get_pcm( ALSA_detail::snd_async_handler_t* handler ) const {
  return snd_async_handler_get_pcm_( handler );
}
int ALSA::snd_pcm_info( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_info_t* info ) const {
  return snd_pcm_info_( pcm, info );
}
int ALSA::snd_pcm_hw_params_current( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_current_( pcm, params );
}
int ALSA::snd_pcm_hw_params( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_( pcm, params );
}
int ALSA::snd_pcm_hw_free( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_hw_free_( pcm );
}
int ALSA::snd_pcm_sw_params_current( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params ) const {
  return snd_pcm_sw_params_current_( pcm, params );
}
int ALSA::snd_pcm_sw_params( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params ) const {
  return snd_pcm_sw_params_( pcm, params );
}
int ALSA::snd_pcm_prepare( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_prepare_( pcm );
}
int ALSA::snd_pcm_reset( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_reset_( pcm );
}
int ALSA::snd_pcm_status( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_status_t* status ) const {
  return snd_pcm_status_( pcm, status );
}
int ALSA::snd_pcm_start( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_start_( pcm );
}
int ALSA::snd_pcm_drop( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_drop_( pcm );
}
int ALSA::snd_pcm_drain( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_drain_( pcm );
}
int ALSA::snd_pcm_pause( ALSA_detail::snd_pcm_t* pcm, int enable ) const {
  return snd_pcm_pause_( pcm, enable );
}
ALSA_detail::snd_pcm_state_t ALSA::snd_pcm_state( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_state_( pcm );
}
int ALSA::snd_pcm_hwsync( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_hwsync_( pcm );
}
int ALSA::snd_pcm_delay( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sframes_t* delayp ) const {
  return snd_pcm_delay_( pcm, delayp );
}
int ALSA::snd_pcm_resume( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_resume_( pcm );
}
int ALSA::snd_pcm_htimestamp( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_uframes_t* avail, ALSA_detail::snd_htimestamp_t* tstamp ) const {
  return snd_pcm_htimestamp_( pcm, avail, tstamp );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_avail( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_avail_( pcm );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_avail_update( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_avail_update_( pcm );
}
int ALSA::snd_pcm_avail_delay( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sframes_t* availp, ALSA_detail::snd_pcm_sframes_t* delayp ) const {
  return snd_pcm_avail_delay_( pcm, availp, delayp );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_rewindable( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_rewindable_( pcm );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_rewind( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_uframes_t frames ) const {
  return snd_pcm_rewind_( pcm, frames );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_forwardable( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_forwardable_( pcm );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_forward( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_uframes_t frames ) const {
  return snd_pcm_forward_( pcm, frames );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_writei( ALSA_detail::snd_pcm_t* pcm, const void* buffer, ALSA_detail::snd_pcm_uframes_t size ) const {
  return snd_pcm_writei_( pcm, buffer, size );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_readi( ALSA_detail::snd_pcm_t* pcm, void* buffer, ALSA_detail::snd_pcm_uframes_t size ) const {
  return snd_pcm_readi_( pcm, buffer, size );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_writen( ALSA_detail::snd_pcm_t* pcm, void** bufs, ALSA_detail::snd_pcm_uframes_t size ) const {
  return snd_pcm_writen_( pcm, bufs, size );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_readn( ALSA_detail::snd_pcm_t* pcm, void** bufs, ALSA_detail::snd_pcm_uframes_t size ) const {
  return snd_pcm_readn_( pcm, bufs, size );
}
int ALSA::snd_pcm_wait( ALSA_detail::snd_pcm_t* pcm, int timeout ) const {
  return snd_pcm_wait_( pcm, timeout );
}
int ALSA::snd_pcm_link( ALSA_detail::snd_pcm_t* pcm1, ALSA_detail::snd_pcm_t* pcm2 ) const {
  return snd_pcm_link_( pcm1, pcm2 );
}
int ALSA::snd_pcm_unlink( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_unlink_( pcm );
}
ALSA_detail::snd_pcm_chmap_query_t** ALSA::snd_pcm_query_chmaps( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_query_chmaps_( pcm );
}
ALSA_detail::snd_pcm_chmap_query_t** ALSA::snd_pcm_query_chmaps_from_hw( int card, int dev, int subdev, ALSA_detail::snd_pcm_stream_t stream ) const {
  return snd_pcm_query_chmaps_from_hw_( card, dev, subdev, stream );
}
void ALSA::snd_pcm_free_chmaps( ALSA_detail::snd_pcm_chmap_query_t** maps ) const {
  return snd_pcm_free_chmaps_( maps );
}
ALSA_detail::snd_pcm_chmap_t* ALSA::snd_pcm_get_chmap( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_get_chmap_( pcm );
}
int ALSA::snd_pcm_set_chmap( ALSA_detail::snd_pcm_t* pcm, const ALSA_detail::snd_pcm_chmap_t* map ) const {
  return snd_pcm_set_chmap_( pcm, map );
}
const char* ALSA::snd_pcm_chmap_type_name( ALSA_detail::snd_pcm_chmap_query_t::snd_pcm_chmap_type val ) const {
  return snd_pcm_chmap_type_name_( val );
}
const char* ALSA::snd_pcm_chmap_name( ALSA_detail::snd_pcm_chmap_position val ) const {
  return snd_pcm_chmap_name_( val );
}
const char* ALSA::snd_pcm_chmap_long_name( ALSA_detail::snd_pcm_chmap_position val ) const {
  return snd_pcm_chmap_long_name_( val );
}
int ALSA::snd_pcm_chmap_print( const ALSA_detail::snd_pcm_chmap_t* map, size_t maxlen, char* buf ) const {
  return snd_pcm_chmap_print_( map, maxlen, buf );
}
unsigned int ALSA::snd_pcm_chmap_from_string( const char* str ) const {
  return snd_pcm_chmap_from_string_( str );
}
ALSA_detail::snd_pcm_chmap_t* ALSA::snd_pcm_chmap_parse_string( const char* str ) const {
  return snd_pcm_chmap_parse_string_( str );
}
int ALSA::snd_pcm_recover( ALSA_detail::snd_pcm_t* pcm, int err, int silent ) const {
  return snd_pcm_recover_( pcm, err, silent );
}
int ALSA::snd_pcm_set_params( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_format_t format, ALSA_detail::snd_pcm_access_t access, unsigned int channels, unsigned int rate, int soft_resample, unsigned int latency ) const {
  return snd_pcm_set_params_( pcm, format, access, channels, rate, soft_resample, latency );
}
int ALSA::snd_pcm_get_params( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_uframes_t* buffer_size, ALSA_detail::snd_pcm_uframes_t* period_size ) const {
  return snd_pcm_get_params_( pcm, buffer_size, period_size );
}
size_t ALSA::snd_pcm_info_sizeof( void ) const {
  return snd_pcm_info_sizeof_();
}
int ALSA::snd_pcm_info_malloc( ALSA_detail::snd_pcm_info_t** ptr ) const {
  return snd_pcm_info_malloc_( ptr );
}
void ALSA::snd_pcm_info_free( ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_free_( obj );
}
void ALSA::snd_pcm_info_copy( ALSA_detail::snd_pcm_info_t* dst, const ALSA_detail::snd_pcm_info_t* src ) const {
  return snd_pcm_info_copy_( dst, src );
}
unsigned int ALSA::snd_pcm_info_get_device( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_device_( obj );
}
unsigned int ALSA::snd_pcm_info_get_subdevice( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_subdevice_( obj );
}
ALSA_detail::snd_pcm_stream_t ALSA::snd_pcm_info_get_stream( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_stream_( obj );
}
int ALSA::snd_pcm_info_get_card( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_card_( obj );
}
const char* ALSA::snd_pcm_info_get_id( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_id_( obj );
}
const char* ALSA::snd_pcm_info_get_name( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_name_( obj );
}
const char* ALSA::snd_pcm_info_get_subdevice_name( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_subdevice_name_( obj );
}
ALSA_detail::snd_pcm_class_t ALSA::snd_pcm_info_get_class( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_class_( obj );
}
ALSA_detail::snd_pcm_subclass_t ALSA::snd_pcm_info_get_subclass( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_subclass_( obj );
}
unsigned int ALSA::snd_pcm_info_get_subdevices_count( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_subdevices_count_( obj );
}
unsigned int ALSA::snd_pcm_info_get_subdevices_avail( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_subdevices_avail_( obj );
}
ALSA_detail::snd_pcm_sync_id_t ALSA::snd_pcm_info_get_sync( const ALSA_detail::snd_pcm_info_t* obj ) const {
  return snd_pcm_info_get_sync_( obj );
}
void ALSA::snd_pcm_info_set_device( ALSA_detail::snd_pcm_info_t* obj, unsigned int val ) const {
  return snd_pcm_info_set_device_( obj, val );
}
void ALSA::snd_pcm_info_set_subdevice( ALSA_detail::snd_pcm_info_t* obj, unsigned int val ) const {
  return snd_pcm_info_set_subdevice_( obj, val );
}
void ALSA::snd_pcm_info_set_stream( ALSA_detail::snd_pcm_info_t* obj, ALSA_detail::snd_pcm_stream_t val ) const {
  return snd_pcm_info_set_stream_( obj, val );
}
int ALSA::snd_pcm_hw_params_any( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_any_( pcm, params );
}
int ALSA::snd_pcm_hw_params_can_mmap_sample_resolution( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_can_mmap_sample_resolution_( params );
}
int ALSA::snd_pcm_hw_params_is_double( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_is_double_( params );
}
int ALSA::snd_pcm_hw_params_is_batch( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_is_batch_( params );
}
int ALSA::snd_pcm_hw_params_is_block_transfer( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_is_block_transfer_( params );
}
int ALSA::snd_pcm_hw_params_is_monotonic( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_is_monotonic_( params );
}
int ALSA::snd_pcm_hw_params_can_overrange( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_can_overrange_( params );
}
int ALSA::snd_pcm_hw_params_can_pause( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_can_pause_( params );
}
int ALSA::snd_pcm_hw_params_can_resume( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_can_resume_( params );
}
int ALSA::snd_pcm_hw_params_is_half_duplex( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_is_half_duplex_( params );
}
int ALSA::snd_pcm_hw_params_is_joint_duplex( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_is_joint_duplex_( params );
}
int ALSA::snd_pcm_hw_params_can_sync_start( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_can_sync_start_( params );
}
int ALSA::snd_pcm_hw_params_can_disable_period_wakeup( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_can_disable_period_wakeup_( params );
}
int ALSA::snd_pcm_hw_params_is_perfect_drain( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_is_perfect_drain_( params );
}
int ALSA::snd_pcm_hw_params_supports_audio_wallclock_ts( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_supports_audio_wallclock_ts_( params );
}
int ALSA::snd_pcm_hw_params_supports_audio_ts_type( const ALSA_detail::snd_pcm_hw_params_t* params, int type ) const {
  return snd_pcm_hw_params_supports_audio_ts_type_( params, type );
}
int ALSA::snd_pcm_hw_params_get_rate_numden( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* rate_num, unsigned int* rate_den ) const {
  return snd_pcm_hw_params_get_rate_numden_( params, rate_num, rate_den );
}
int ALSA::snd_pcm_hw_params_get_sbits( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_get_sbits_( params );
}
int ALSA::snd_pcm_hw_params_get_fifo_size( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_get_fifo_size_( params );
}
const unsigned char* ALSA::snd_pcm_hw_params_get_sync( const ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_get_sync_( params );
}
size_t ALSA::snd_pcm_hw_params_sizeof( void ) const {
  return snd_pcm_hw_params_sizeof_();
}
int ALSA::snd_pcm_hw_params_malloc( ALSA_detail::snd_pcm_hw_params_t** ptr ) const {
  return snd_pcm_hw_params_malloc_( ptr );
}
void ALSA::snd_pcm_hw_params_free( ALSA_detail::snd_pcm_hw_params_t* obj ) const {
  return snd_pcm_hw_params_free_( obj );
}
void ALSA::snd_pcm_hw_params_copy( ALSA_detail::snd_pcm_hw_params_t* dst, const ALSA_detail::snd_pcm_hw_params_t* src ) const {
  return snd_pcm_hw_params_copy_( dst, src );
}
int ALSA::snd_pcm_hw_params_get_access( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_access_t* _access ) const {
  return snd_pcm_hw_params_get_access_( params, _access );
}
int ALSA::snd_pcm_hw_params_test_access( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_access_t _access ) const {
  return snd_pcm_hw_params_test_access_( pcm, params, _access );
}
int ALSA::snd_pcm_hw_params_set_access( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_access_t _access ) const {
  return snd_pcm_hw_params_set_access_( pcm, params, _access );
}
int ALSA::snd_pcm_hw_params_set_access_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_access_t* _access ) const {
  return snd_pcm_hw_params_set_access_first_( pcm, params, _access );
}
int ALSA::snd_pcm_hw_params_set_access_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_access_t* _access ) const {
  return snd_pcm_hw_params_set_access_last_( pcm, params, _access );
}
int ALSA::snd_pcm_hw_params_set_access_mask( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_access_mask_t* mask ) const {
  return snd_pcm_hw_params_set_access_mask_( pcm, params, mask );
}
int ALSA::snd_pcm_hw_params_get_access_mask( ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_access_mask_t* mask ) const {
  return snd_pcm_hw_params_get_access_mask_( params, mask );
}
int ALSA::snd_pcm_hw_params_get_format( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_format_t* val ) const {
  return snd_pcm_hw_params_get_format_( params, val );
}
int ALSA::snd_pcm_hw_params_test_format( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_format_t val ) const {
  return snd_pcm_hw_params_test_format_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_format( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_format_t val ) const {
  return snd_pcm_hw_params_set_format_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_format_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_format_t* format ) const {
  return snd_pcm_hw_params_set_format_first_( pcm, params, format );
}
int ALSA::snd_pcm_hw_params_set_format_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_format_t* format ) const {
  return snd_pcm_hw_params_set_format_last_( pcm, params, format );
}
int ALSA::snd_pcm_hw_params_set_format_mask( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_format_mask_t* mask ) const {
  return snd_pcm_hw_params_set_format_mask_( pcm, params, mask );
}
void ALSA::snd_pcm_hw_params_get_format_mask( ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_format_mask_t* mask ) const {
  return snd_pcm_hw_params_get_format_mask_( params, mask );
}
int ALSA::snd_pcm_hw_params_get_subformat( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_subformat_t* subformat ) const {
  return snd_pcm_hw_params_get_subformat_( params, subformat );
}
int ALSA::snd_pcm_hw_params_test_subformat( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_subformat_t subformat ) const {
  return snd_pcm_hw_params_test_subformat_( pcm, params, subformat );
}
int ALSA::snd_pcm_hw_params_set_subformat( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_subformat_t subformat ) const {
  return snd_pcm_hw_params_set_subformat_( pcm, params, subformat );
}
int ALSA::snd_pcm_hw_params_set_subformat_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_subformat_t* subformat ) const {
  return snd_pcm_hw_params_set_subformat_first_( pcm, params, subformat );
}
int ALSA::snd_pcm_hw_params_set_subformat_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_subformat_t* subformat ) const {
  return snd_pcm_hw_params_set_subformat_last_( pcm, params, subformat );
}
int ALSA::snd_pcm_hw_params_set_subformat_mask( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_subformat_mask_t* mask ) const {
  return snd_pcm_hw_params_set_subformat_mask_( pcm, params, mask );
}
void ALSA::snd_pcm_hw_params_get_subformat_mask( ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_subformat_mask_t* mask ) const {
  return snd_pcm_hw_params_get_subformat_mask_( params, mask );
}
int ALSA::snd_pcm_hw_params_get_channels( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_get_channels_( params, val );
}
int ALSA::snd_pcm_hw_params_get_channels_min( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_get_channels_min_( params, val );
}
int ALSA::snd_pcm_hw_params_get_channels_max( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_get_channels_max_( params, val );
}
int ALSA::snd_pcm_hw_params_test_channels( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val ) const {
  return snd_pcm_hw_params_test_channels_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_channels( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val ) const {
  return snd_pcm_hw_params_set_channels_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_channels_min( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_set_channels_min_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_channels_max( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_set_channels_max_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_channels_minmax( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* min, unsigned int* max ) const {
  return snd_pcm_hw_params_set_channels_minmax_( pcm, params, min, max );
}
int ALSA::snd_pcm_hw_params_set_channels_near( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_set_channels_near_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_channels_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_set_channels_first_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_channels_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_set_channels_last_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_get_rate( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_rate_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_rate_min( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_rate_min_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_rate_max( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_rate_max_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_test_rate( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val, int dir ) const {
  return snd_pcm_hw_params_test_rate_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_rate( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val, int dir ) const {
  return snd_pcm_hw_params_set_rate_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_rate_min( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_rate_min_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_rate_max( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_rate_max_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_rate_minmax( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* min, int* mindir, unsigned int* max, int* maxdir ) const {
  return snd_pcm_hw_params_set_rate_minmax_( pcm, params, min, mindir, max, maxdir );
}
int ALSA::snd_pcm_hw_params_set_rate_near( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_rate_near_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_rate_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_rate_first_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_rate_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_rate_last_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_rate_resample( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val ) const {
  return snd_pcm_hw_params_set_rate_resample_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_get_rate_resample( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_get_rate_resample_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_export_buffer( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val ) const {
  return snd_pcm_hw_params_set_export_buffer_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_get_export_buffer( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_get_export_buffer_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_period_wakeup( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val ) const {
  return snd_pcm_hw_params_set_period_wakeup_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_get_period_wakeup( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_get_period_wakeup_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_drain_silence( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val ) const {
  return snd_pcm_hw_params_set_drain_silence_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_get_drain_silence( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val ) const {
  return snd_pcm_hw_params_get_drain_silence_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_get_period_time( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_period_time_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_period_time_min( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_period_time_min_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_period_time_max( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_period_time_max_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_test_period_time( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val, int dir ) const {
  return snd_pcm_hw_params_test_period_time_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_time( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val, int dir ) const {
  return snd_pcm_hw_params_set_period_time_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_time_min( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_time_min_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_time_max( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_time_max_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_time_minmax( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* min, int* mindir, unsigned int* max, int* maxdir ) const {
  return snd_pcm_hw_params_set_period_time_minmax_( pcm, params, min, mindir, max, maxdir );
}
int ALSA::snd_pcm_hw_params_set_period_time_near( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_time_near_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_time_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_time_first_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_time_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_time_last_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_period_size( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* frames, int* dir ) const {
  return snd_pcm_hw_params_get_period_size_( params, frames, dir );
}
int ALSA::snd_pcm_hw_params_get_period_size_min( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* frames, int* dir ) const {
  return snd_pcm_hw_params_get_period_size_min_( params, frames, dir );
}
int ALSA::snd_pcm_hw_params_get_period_size_max( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* frames, int* dir ) const {
  return snd_pcm_hw_params_get_period_size_max_( params, frames, dir );
}
int ALSA::snd_pcm_hw_params_test_period_size( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t val, int dir ) const {
  return snd_pcm_hw_params_test_period_size_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_size( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t val, int dir ) const {
  return snd_pcm_hw_params_set_period_size_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_size_min( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_size_min_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_size_max( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_size_max_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_size_minmax( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* min, int* mindir, ALSA_detail::snd_pcm_uframes_t* max, int* maxdir ) const {
  return snd_pcm_hw_params_set_period_size_minmax_( pcm, params, min, mindir, max, maxdir );
}
int ALSA::snd_pcm_hw_params_set_period_size_near( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_size_near_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_size_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_size_first_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_size_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val, int* dir ) const {
  return snd_pcm_hw_params_set_period_size_last_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_period_size_integer( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_set_period_size_integer_( pcm, params );
}
int ALSA::snd_pcm_hw_params_get_periods( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_periods_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_periods_min( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_periods_min_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_periods_max( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_periods_max_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_test_periods( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val, int dir ) const {
  return snd_pcm_hw_params_test_periods_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_periods( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val, int dir ) const {
  return snd_pcm_hw_params_set_periods_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_periods_min( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_periods_min_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_periods_max( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_periods_max_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_periods_minmax( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* min, int* mindir, unsigned int* max, int* maxdir ) const {
  return snd_pcm_hw_params_set_periods_minmax_( pcm, params, min, mindir, max, maxdir );
}
int ALSA::snd_pcm_hw_params_set_periods_near( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_periods_near_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_periods_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_periods_first_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_periods_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_periods_last_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_periods_integer( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params ) const {
  return snd_pcm_hw_params_set_periods_integer_( pcm, params );
}
int ALSA::snd_pcm_hw_params_get_buffer_time( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_buffer_time_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_buffer_time_min( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_buffer_time_min_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_buffer_time_max( const ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_get_buffer_time_max_( params, val, dir );
}
int ALSA::snd_pcm_hw_params_test_buffer_time( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val, int dir ) const {
  return snd_pcm_hw_params_test_buffer_time_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_buffer_time( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int val, int dir ) const {
  return snd_pcm_hw_params_set_buffer_time_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_buffer_time_min( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_buffer_time_min_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_buffer_time_max( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_buffer_time_max_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_buffer_time_minmax( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* min, int* mindir, unsigned int* max, int* maxdir ) const {
  return snd_pcm_hw_params_set_buffer_time_minmax_( pcm, params, min, mindir, max, maxdir );
}
int ALSA::snd_pcm_hw_params_set_buffer_time_near( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_buffer_time_near_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_buffer_time_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_buffer_time_first_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_set_buffer_time_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, unsigned int* val, int* dir ) const {
  return snd_pcm_hw_params_set_buffer_time_last_( pcm, params, val, dir );
}
int ALSA::snd_pcm_hw_params_get_buffer_size( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_get_buffer_size_( params, val );
}
int ALSA::snd_pcm_hw_params_get_buffer_size_min( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_get_buffer_size_min_( params, val );
}
int ALSA::snd_pcm_hw_params_get_buffer_size_max( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_get_buffer_size_max_( params, val );
}
int ALSA::snd_pcm_hw_params_test_buffer_size( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t val ) const {
  return snd_pcm_hw_params_test_buffer_size_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_buffer_size( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t val ) const {
  return snd_pcm_hw_params_set_buffer_size_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_buffer_size_min( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_set_buffer_size_min_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_buffer_size_max( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_set_buffer_size_max_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_buffer_size_minmax( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* min, ALSA_detail::snd_pcm_uframes_t* max ) const {
  return snd_pcm_hw_params_set_buffer_size_minmax_( pcm, params, min, max );
}
int ALSA::snd_pcm_hw_params_set_buffer_size_near( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_set_buffer_size_near_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_buffer_size_first( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_set_buffer_size_first_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_set_buffer_size_last( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_set_buffer_size_last_( pcm, params, val );
}
int ALSA::snd_pcm_hw_params_get_min_align( const ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_hw_params_get_min_align_( params, val );
}
size_t ALSA::snd_pcm_sw_params_sizeof( void ) const {
  return snd_pcm_sw_params_sizeof_();
}
int ALSA::snd_pcm_sw_params_malloc( ALSA_detail::snd_pcm_sw_params_t** ptr ) const {
  return snd_pcm_sw_params_malloc_( ptr );
}
void ALSA::snd_pcm_sw_params_free( ALSA_detail::snd_pcm_sw_params_t* obj ) const {
  return snd_pcm_sw_params_free_( obj );
}
void ALSA::snd_pcm_sw_params_copy( ALSA_detail::snd_pcm_sw_params_t* dst, const ALSA_detail::snd_pcm_sw_params_t* src ) const {
  return snd_pcm_sw_params_copy_( dst, src );
}
int ALSA::snd_pcm_sw_params_get_boundary( const ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_sw_params_get_boundary_( params, val );
}
int ALSA::snd_pcm_sw_params_set_tstamp_mode( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_tstamp_t val ) const {
  return snd_pcm_sw_params_set_tstamp_mode_( pcm, params, val );
}
int ALSA::snd_pcm_sw_params_get_tstamp_mode( const ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_tstamp_t* val ) const {
  return snd_pcm_sw_params_get_tstamp_mode_( params, val );
}
int ALSA::snd_pcm_sw_params_set_tstamp_type( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_tstamp_type_t val ) const {
  return snd_pcm_sw_params_set_tstamp_type_( pcm, params, val );
}
int ALSA::snd_pcm_sw_params_get_tstamp_type( const ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_tstamp_type_t* val ) const {
  return snd_pcm_sw_params_get_tstamp_type_( params, val );
}
int ALSA::snd_pcm_sw_params_set_avail_min( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t val ) const {
  return snd_pcm_sw_params_set_avail_min_( pcm, params, val );
}
int ALSA::snd_pcm_sw_params_get_avail_min( const ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_sw_params_get_avail_min_( params, val );
}
int ALSA::snd_pcm_sw_params_set_period_event( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params, int val ) const {
  return snd_pcm_sw_params_set_period_event_( pcm, params, val );
}
int ALSA::snd_pcm_sw_params_get_period_event( const ALSA_detail::snd_pcm_sw_params_t* params, int* val ) const {
  return snd_pcm_sw_params_get_period_event_( params, val );
}
int ALSA::snd_pcm_sw_params_set_start_threshold( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t val ) const {
  return snd_pcm_sw_params_set_start_threshold_( pcm, params, val );
}
int ALSA::snd_pcm_sw_params_get_start_threshold( const ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_sw_params_get_start_threshold_( params, val );
}
int ALSA::snd_pcm_sw_params_set_stop_threshold( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t val ) const {
  return snd_pcm_sw_params_set_stop_threshold_( pcm, params, val );
}
int ALSA::snd_pcm_sw_params_get_stop_threshold( const ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_sw_params_get_stop_threshold_( params, val );
}
int ALSA::snd_pcm_sw_params_set_silence_threshold( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t val ) const {
  return snd_pcm_sw_params_set_silence_threshold_( pcm, params, val );
}
int ALSA::snd_pcm_sw_params_get_silence_threshold( const ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_sw_params_get_silence_threshold_( params, val );
}
int ALSA::snd_pcm_sw_params_set_silence_size( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t val ) const {
  return snd_pcm_sw_params_set_silence_size_( pcm, params, val );
}
int ALSA::snd_pcm_sw_params_get_silence_size( const ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_pcm_uframes_t* val ) const {
  return snd_pcm_sw_params_get_silence_size_( params, val );
}
size_t ALSA::snd_pcm_access_mask_sizeof( void ) const {
  return snd_pcm_access_mask_sizeof_();
}
int ALSA::snd_pcm_access_mask_malloc( ALSA_detail::snd_pcm_access_mask_t** ptr ) const {
  return snd_pcm_access_mask_malloc_( ptr );
}
void ALSA::snd_pcm_access_mask_free( ALSA_detail::snd_pcm_access_mask_t* obj ) const {
  return snd_pcm_access_mask_free_( obj );
}
void ALSA::snd_pcm_access_mask_copy( ALSA_detail::snd_pcm_access_mask_t* dst, const ALSA_detail::snd_pcm_access_mask_t* src ) const {
  return snd_pcm_access_mask_copy_( dst, src );
}
void ALSA::snd_pcm_access_mask_none( ALSA_detail::snd_pcm_access_mask_t* mask ) const {
  return snd_pcm_access_mask_none_( mask );
}
void ALSA::snd_pcm_access_mask_any( ALSA_detail::snd_pcm_access_mask_t* mask ) const {
  return snd_pcm_access_mask_any_( mask );
}
int ALSA::snd_pcm_access_mask_test( const ALSA_detail::snd_pcm_access_mask_t* mask, ALSA_detail::snd_pcm_access_t val ) const {
  return snd_pcm_access_mask_test_( mask, val );
}
int ALSA::snd_pcm_access_mask_empty( const ALSA_detail::snd_pcm_access_mask_t* mask ) const {
  return snd_pcm_access_mask_empty_( mask );
}
void ALSA::snd_pcm_access_mask_set( ALSA_detail::snd_pcm_access_mask_t* mask, ALSA_detail::snd_pcm_access_t val ) const {
  return snd_pcm_access_mask_set_( mask, val );
}
void ALSA::snd_pcm_access_mask_reset( ALSA_detail::snd_pcm_access_mask_t* mask, ALSA_detail::snd_pcm_access_t val ) const {
  return snd_pcm_access_mask_reset_( mask, val );
}
size_t ALSA::snd_pcm_format_mask_sizeof( void ) const {
  return snd_pcm_format_mask_sizeof_();
}
int ALSA::snd_pcm_format_mask_malloc( ALSA_detail::snd_pcm_format_mask_t** ptr ) const {
  return snd_pcm_format_mask_malloc_( ptr );
}
void ALSA::snd_pcm_format_mask_free( ALSA_detail::snd_pcm_format_mask_t* obj ) const {
  return snd_pcm_format_mask_free_( obj );
}
void ALSA::snd_pcm_format_mask_copy( ALSA_detail::snd_pcm_format_mask_t* dst, const ALSA_detail::snd_pcm_format_mask_t* src ) const {
  return snd_pcm_format_mask_copy_( dst, src );
}
void ALSA::snd_pcm_format_mask_none( ALSA_detail::snd_pcm_format_mask_t* mask ) const {
  return snd_pcm_format_mask_none_( mask );
}
void ALSA::snd_pcm_format_mask_any( ALSA_detail::snd_pcm_format_mask_t* mask ) const {
  return snd_pcm_format_mask_any_( mask );
}
int ALSA::snd_pcm_format_mask_test( const ALSA_detail::snd_pcm_format_mask_t* mask, ALSA_detail::snd_pcm_format_t val ) const {
  return snd_pcm_format_mask_test_( mask, val );
}
int ALSA::snd_pcm_format_mask_empty( const ALSA_detail::snd_pcm_format_mask_t* mask ) const {
  return snd_pcm_format_mask_empty_( mask );
}
void ALSA::snd_pcm_format_mask_set( ALSA_detail::snd_pcm_format_mask_t* mask, ALSA_detail::snd_pcm_format_t val ) const {
  return snd_pcm_format_mask_set_( mask, val );
}
void ALSA::snd_pcm_format_mask_reset( ALSA_detail::snd_pcm_format_mask_t* mask, ALSA_detail::snd_pcm_format_t val ) const {
  return snd_pcm_format_mask_reset_( mask, val );
}
size_t ALSA::snd_pcm_subformat_mask_sizeof( void ) const {
  return snd_pcm_subformat_mask_sizeof_();
}
int ALSA::snd_pcm_subformat_mask_malloc( ALSA_detail::snd_pcm_subformat_mask_t** ptr ) const {
  return snd_pcm_subformat_mask_malloc_( ptr );
}
void ALSA::snd_pcm_subformat_mask_free( ALSA_detail::snd_pcm_subformat_mask_t* obj ) const {
  return snd_pcm_subformat_mask_free_( obj );
}
void ALSA::snd_pcm_subformat_mask_copy( ALSA_detail::snd_pcm_subformat_mask_t* dst, const ALSA_detail::snd_pcm_subformat_mask_t* src ) const {
  return snd_pcm_subformat_mask_copy_( dst, src );
}
void ALSA::snd_pcm_subformat_mask_none( ALSA_detail::snd_pcm_subformat_mask_t* mask ) const {
  return snd_pcm_subformat_mask_none_( mask );
}
void ALSA::snd_pcm_subformat_mask_any( ALSA_detail::snd_pcm_subformat_mask_t* mask ) const {
  return snd_pcm_subformat_mask_any_( mask );
}
int ALSA::snd_pcm_subformat_mask_test( const ALSA_detail::snd_pcm_subformat_mask_t* mask, ALSA_detail::snd_pcm_subformat_t val ) const {
  return snd_pcm_subformat_mask_test_( mask, val );
}
int ALSA::snd_pcm_subformat_mask_empty( const ALSA_detail::snd_pcm_subformat_mask_t* mask ) const {
  return snd_pcm_subformat_mask_empty_( mask );
}
void ALSA::snd_pcm_subformat_mask_set( ALSA_detail::snd_pcm_subformat_mask_t* mask, ALSA_detail::snd_pcm_subformat_t val ) const {
  return snd_pcm_subformat_mask_set_( mask, val );
}
void ALSA::snd_pcm_subformat_mask_reset( ALSA_detail::snd_pcm_subformat_mask_t* mask, ALSA_detail::snd_pcm_subformat_t val ) const {
  return snd_pcm_subformat_mask_reset_( mask, val );
}
size_t ALSA::snd_pcm_status_sizeof( void ) const {
  return snd_pcm_status_sizeof_();
}
int ALSA::snd_pcm_status_malloc( ALSA_detail::snd_pcm_status_t** ptr ) const {
  return snd_pcm_status_malloc_( ptr );
}
void ALSA::snd_pcm_status_free( ALSA_detail::snd_pcm_status_t* obj ) const {
  return snd_pcm_status_free_( obj );
}
void ALSA::snd_pcm_status_copy( ALSA_detail::snd_pcm_status_t* dst, const ALSA_detail::snd_pcm_status_t* src ) const {
  return snd_pcm_status_copy_( dst, src );
}
ALSA_detail::snd_pcm_state_t ALSA::snd_pcm_status_get_state( const ALSA_detail::snd_pcm_status_t* obj ) const {
  return snd_pcm_status_get_state_( obj );
}
void ALSA::snd_pcm_status_get_trigger_tstamp( const ALSA_detail::snd_pcm_status_t* obj, ALSA_detail::snd_timestamp_t* ptr ) const {
  return snd_pcm_status_get_trigger_tstamp_( obj, ptr );
}
void ALSA::snd_pcm_status_get_trigger_htstamp( const ALSA_detail::snd_pcm_status_t* obj, ALSA_detail::snd_htimestamp_t* ptr ) const {
  return snd_pcm_status_get_trigger_htstamp_( obj, ptr );
}
void ALSA::snd_pcm_status_get_tstamp( const ALSA_detail::snd_pcm_status_t* obj, ALSA_detail::snd_timestamp_t* ptr ) const {
  return snd_pcm_status_get_tstamp_( obj, ptr );
}
void ALSA::snd_pcm_status_get_htstamp( const ALSA_detail::snd_pcm_status_t* obj, ALSA_detail::snd_htimestamp_t* ptr ) const {
  return snd_pcm_status_get_htstamp_( obj, ptr );
}
void ALSA::snd_pcm_status_get_audio_htstamp( const ALSA_detail::snd_pcm_status_t* obj, ALSA_detail::snd_htimestamp_t* ptr ) const {
  return snd_pcm_status_get_audio_htstamp_( obj, ptr );
}
void ALSA::snd_pcm_status_get_driver_htstamp( const ALSA_detail::snd_pcm_status_t* obj, ALSA_detail::snd_htimestamp_t* ptr ) const {
  return snd_pcm_status_get_driver_htstamp_( obj, ptr );
}
void ALSA::snd_pcm_status_get_audio_htstamp_report( const ALSA_detail::snd_pcm_status_t* obj, ALSA_detail::snd_pcm_audio_tstamp_report_t* audio_tstamp_report ) const {
  return snd_pcm_status_get_audio_htstamp_report_( obj, audio_tstamp_report );
}
void ALSA::snd_pcm_status_set_audio_htstamp_config( ALSA_detail::snd_pcm_status_t* obj, ALSA_detail::snd_pcm_audio_tstamp_config_t* audio_tstamp_config ) const {
  return snd_pcm_status_set_audio_htstamp_config_( obj, audio_tstamp_config );
}
void ALSA::snd_pcm_pack_audio_tstamp_config( unsigned int* data, ALSA_detail::snd_pcm_audio_tstamp_config_t* config ) const {
  return snd_pcm_pack_audio_tstamp_config_( data, config );
}
void ALSA::snd_pcm_unpack_audio_tstamp_report( unsigned int data, unsigned int accuracy, ALSA_detail::snd_pcm_audio_tstamp_report_t* report ) const {
  return snd_pcm_unpack_audio_tstamp_report_( data, accuracy, report );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_status_get_delay( const ALSA_detail::snd_pcm_status_t* obj ) const {
  return snd_pcm_status_get_delay_( obj );
}
ALSA_detail::snd_pcm_uframes_t ALSA::snd_pcm_status_get_avail( const ALSA_detail::snd_pcm_status_t* obj ) const {
  return snd_pcm_status_get_avail_( obj );
}
ALSA_detail::snd_pcm_uframes_t ALSA::snd_pcm_status_get_avail_max( const ALSA_detail::snd_pcm_status_t* obj ) const {
  return snd_pcm_status_get_avail_max_( obj );
}
ALSA_detail::snd_pcm_uframes_t ALSA::snd_pcm_status_get_overrange( const ALSA_detail::snd_pcm_status_t* obj ) const {
  return snd_pcm_status_get_overrange_( obj );
}
const char* ALSA::snd_pcm_type_name( ALSA_detail::snd_pcm_type_t type ) const {
  return snd_pcm_type_name_( type );
}
const char* ALSA::snd_pcm_stream_name( const ALSA_detail::snd_pcm_stream_t stream ) const {
  return snd_pcm_stream_name_( stream );
}
const char* ALSA::snd_pcm_access_name( const ALSA_detail::snd_pcm_access_t _access ) const {
  return snd_pcm_access_name_( _access );
}
const char* ALSA::snd_pcm_format_name( const ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_name_( format );
}
const char* ALSA::snd_pcm_format_description( const ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_description_( format );
}
const char* ALSA::snd_pcm_subformat_name( const ALSA_detail::snd_pcm_subformat_t subformat ) const {
  return snd_pcm_subformat_name_( subformat );
}
const char* ALSA::snd_pcm_subformat_description( const ALSA_detail::snd_pcm_subformat_t subformat ) const {
  return snd_pcm_subformat_description_( subformat );
}
ALSA_detail::snd_pcm_subformat_t ALSA::snd_pcm_subformat_value( const char* name ) const {
  return snd_pcm_subformat_value_( name );
}
ALSA_detail::snd_pcm_format_t ALSA::snd_pcm_format_value( const char* name ) const {
  return snd_pcm_format_value_( name );
}
const char* ALSA::snd_pcm_tstamp_mode_name( const ALSA_detail::snd_pcm_tstamp_t mode ) const {
  return snd_pcm_tstamp_mode_name_( mode );
}
const char* ALSA::snd_pcm_state_name( const ALSA_detail::snd_pcm_state_t state ) const {
  return snd_pcm_state_name_( state );
}
// int ALSA::snd_pcm_dump( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_output_t* out ) const {
//   return snd_pcm_dump_( pcm, out );
// }
// int ALSA::snd_pcm_dump_hw_setup( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_output_t* out ) const {
//   return snd_pcm_dump_hw_setup_( pcm, out );
// }
// int ALSA::snd_pcm_dump_sw_setup( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_output_t* out ) const {
//   return snd_pcm_dump_sw_setup_( pcm, out );
// }
// int ALSA::snd_pcm_dump_setup( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_output_t* out ) const {
//   return snd_pcm_dump_setup_( pcm, out );
// }
// int ALSA::snd_pcm_hw_params_dump( ALSA_detail::snd_pcm_hw_params_t* params, ALSA_detail::snd_output_t* out ) const {
//   return snd_pcm_hw_params_dump_( params, out );
// }
// int ALSA::snd_pcm_sw_params_dump( ALSA_detail::snd_pcm_sw_params_t* params, ALSA_detail::snd_output_t* out ) const {
//   return snd_pcm_sw_params_dump_( params, out );
// }
// int ALSA::snd_pcm_status_dump( ALSA_detail::snd_pcm_status_t* status, ALSA_detail::snd_output_t* out ) const {
//   return snd_pcm_status_dump_( status, out );
// }
int ALSA::snd_pcm_mmap_begin( ALSA_detail::snd_pcm_t* pcm, const ALSA_detail::snd_pcm_channel_area_t** areas, ALSA_detail::snd_pcm_uframes_t* offset, ALSA_detail::snd_pcm_uframes_t* frames ) const {
  return snd_pcm_mmap_begin_( pcm, areas, offset, frames );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_mmap_commit( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_uframes_t offset, ALSA_detail::snd_pcm_uframes_t frames ) const {
  return snd_pcm_mmap_commit_( pcm, offset, frames );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_mmap_writei( ALSA_detail::snd_pcm_t* pcm, const void* buffer, ALSA_detail::snd_pcm_uframes_t size ) const {
  return snd_pcm_mmap_writei_( pcm, buffer, size );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_mmap_readi( ALSA_detail::snd_pcm_t* pcm, void* buffer, ALSA_detail::snd_pcm_uframes_t size ) const {
  return snd_pcm_mmap_readi_( pcm, buffer, size );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_mmap_writen( ALSA_detail::snd_pcm_t* pcm, void** bufs, ALSA_detail::snd_pcm_uframes_t size ) const {
  return snd_pcm_mmap_writen_( pcm, bufs, size );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_mmap_readn( ALSA_detail::snd_pcm_t* pcm, void** bufs, ALSA_detail::snd_pcm_uframes_t size ) const {
  return snd_pcm_mmap_readn_( pcm, bufs, size );
}
int ALSA::snd_pcm_format_signed( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_signed_( format );
}
int ALSA::snd_pcm_format_unsigned( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_unsigned_( format );
}
int ALSA::snd_pcm_format_linear( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_linear_( format );
}
int ALSA::snd_pcm_format_float( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_float_( format );
}
int ALSA::snd_pcm_format_little_endian( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_little_endian_( format );
}
int ALSA::snd_pcm_format_big_endian( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_big_endian_( format );
}
int ALSA::snd_pcm_format_cpu_endian( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_cpu_endian_( format );
}
int ALSA::snd_pcm_format_width( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_width_( format );
}
int ALSA::snd_pcm_format_physical_width( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_physical_width_( format );
}
ALSA_detail::snd_pcm_format_t ALSA::snd_pcm_build_linear_format( int width, int pwidth, int unsignd, int big_endian ) const {
  return snd_pcm_build_linear_format_( width, pwidth, unsignd, big_endian );
}
ssize_t ALSA::snd_pcm_format_size( ALSA_detail::snd_pcm_format_t format, size_t samples ) const {
  return snd_pcm_format_size_( format, samples );
}
uint8_t ALSA::snd_pcm_format_silence( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_silence_( format );
}
uint16_t ALSA::snd_pcm_format_silence_16( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_silence_16_( format );
}
uint32_t ALSA::snd_pcm_format_silence_32( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_silence_32_( format );
}
uint64_t ALSA::snd_pcm_format_silence_64( ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_format_silence_64_( format );
}
int ALSA::snd_pcm_format_set_silence( ALSA_detail::snd_pcm_format_t format, void* buf, unsigned int samples ) const {
  return snd_pcm_format_set_silence_( format, buf, samples );
}
ALSA_detail::snd_pcm_sframes_t ALSA::snd_pcm_bytes_to_frames( ALSA_detail::snd_pcm_t* pcm, ssize_t bytes ) const {
  return snd_pcm_bytes_to_frames_( pcm, bytes );
}
ssize_t ALSA::snd_pcm_frames_to_bytes( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_sframes_t frames ) const {
  return snd_pcm_frames_to_bytes_( pcm, frames );
}
long ALSA::snd_pcm_bytes_to_samples( ALSA_detail::snd_pcm_t* pcm, ssize_t bytes ) const {
  return snd_pcm_bytes_to_samples_( pcm, bytes );
}
ssize_t ALSA::snd_pcm_samples_to_bytes( ALSA_detail::snd_pcm_t* pcm, long samples ) const {
  return snd_pcm_samples_to_bytes_( pcm, samples );
}
int ALSA::snd_pcm_area_silence( const ALSA_detail::snd_pcm_channel_area_t* dst_channel, ALSA_detail::snd_pcm_uframes_t dst_offset, unsigned int samples, ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_area_silence_( dst_channel, dst_offset, samples, format );
}
int ALSA::snd_pcm_areas_silence( const ALSA_detail::snd_pcm_channel_area_t* dst_channels, ALSA_detail::snd_pcm_uframes_t dst_offset, unsigned int channels, ALSA_detail::snd_pcm_uframes_t frames, ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_areas_silence_( dst_channels, dst_offset, channels, frames, format );
}
int ALSA::snd_pcm_area_copy( const ALSA_detail::snd_pcm_channel_area_t* dst_channel, ALSA_detail::snd_pcm_uframes_t dst_offset, const ALSA_detail::snd_pcm_channel_area_t* src_channel, ALSA_detail::snd_pcm_uframes_t src_offset, unsigned int samples, ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_area_copy_( dst_channel, dst_offset, src_channel, src_offset, samples, format );
}
int ALSA::snd_pcm_areas_copy( const ALSA_detail::snd_pcm_channel_area_t* dst_channels, ALSA_detail::snd_pcm_uframes_t dst_offset, const ALSA_detail::snd_pcm_channel_area_t* src_channels, ALSA_detail::snd_pcm_uframes_t src_offset, unsigned int channels, ALSA_detail::snd_pcm_uframes_t frames, ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_areas_copy_( dst_channels, dst_offset, src_channels, src_offset, channels, frames, format );
}
int ALSA::snd_pcm_areas_copy_wrap( const ALSA_detail::snd_pcm_channel_area_t* dst_channels, ALSA_detail::snd_pcm_uframes_t dst_offset, const ALSA_detail::snd_pcm_uframes_t dst_size, const ALSA_detail::snd_pcm_channel_area_t* src_channels, ALSA_detail::snd_pcm_uframes_t src_offset, const ALSA_detail::snd_pcm_uframes_t src_size, const unsigned int channels, ALSA_detail::snd_pcm_uframes_t frames, const ALSA_detail::snd_pcm_format_t format ) const {
  return snd_pcm_areas_copy_wrap_( dst_channels, dst_offset, dst_size, src_channels, src_offset, src_size, channels, frames, format );
}
void* ALSA::snd_pcm_channel_area_addr( const ALSA_detail::snd_pcm_channel_area_t* area, ALSA_detail::snd_pcm_uframes_t offset ) const {
  return snd_pcm_channel_area_addr_( area, offset );
}
unsigned int ALSA::snd_pcm_channel_area_step( const ALSA_detail::snd_pcm_channel_area_t* area ) const {
  return snd_pcm_channel_area_step_( area );
}
int ALSA::snd_pcm_hook_func_t( ALSA_detail::snd_pcm_hook_t* hook ) const {
  return snd_pcm_hook_func_t_( hook );
}
ALSA_detail::snd_pcm_t* ALSA::snd_pcm_hook_get_pcm( ALSA_detail::snd_pcm_hook_t* hook ) const {
  return snd_pcm_hook_get_pcm_( hook );
}
void* ALSA::snd_pcm_hook_get_private( ALSA_detail::snd_pcm_hook_t* hook ) const {
  return snd_pcm_hook_get_private_( hook );
}
void ALSA::snd_pcm_hook_set_private( ALSA_detail::snd_pcm_hook_t* hook, void* private_data ) const {
  return snd_pcm_hook_set_private_( hook, private_data );
}
int ALSA::snd_pcm_hook_add( ALSA_detail::snd_pcm_hook_t** hookp, ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_hook_type_t type, ALSA_detail::snd_pcm_hook_func_t func, void* private_data ) const {
  return snd_pcm_hook_add_( hookp, pcm, type, func, private_data );
}
int ALSA::snd_pcm_hook_remove( ALSA_detail::snd_pcm_hook_t* hook ) const {
  return snd_pcm_hook_remove_( hook );
}
ALSA_detail::snd_pcm_uframes_t ALSA::snd_pcm_meter_get_bufsize( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_meter_get_bufsize_( pcm );
}
unsigned int ALSA::snd_pcm_meter_get_channels( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_meter_get_channels_( pcm );
}
unsigned int ALSA::snd_pcm_meter_get_rate( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_meter_get_rate_( pcm );
}
ALSA_detail::snd_pcm_uframes_t ALSA::snd_pcm_meter_get_now( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_meter_get_now_( pcm );
}
ALSA_detail::snd_pcm_uframes_t ALSA::snd_pcm_meter_get_boundary( ALSA_detail::snd_pcm_t* pcm ) const {
  return snd_pcm_meter_get_boundary_( pcm );
}
int ALSA::snd_pcm_meter_add_scope( ALSA_detail::snd_pcm_t* pcm, ALSA_detail::snd_pcm_scope_t* scope ) const {
  return snd_pcm_meter_add_scope_( pcm, scope );
}
ALSA_detail::snd_pcm_scope_t* ALSA::snd_pcm_meter_search_scope( ALSA_detail::snd_pcm_t* pcm, const char* name ) const {
  return snd_pcm_meter_search_scope_( pcm, name );
}
int ALSA::snd_pcm_scope_malloc( ALSA_detail::snd_pcm_scope_t** ptr ) const {
  return snd_pcm_scope_malloc_( ptr );
}
void ALSA::snd_pcm_scope_set_ops( ALSA_detail::snd_pcm_scope_t* scope, const ALSA_detail::snd_pcm_scope_ops_t* val ) const {
  return snd_pcm_scope_set_ops_( scope, val );
}
void ALSA::snd_pcm_scope_set_name( ALSA_detail::snd_pcm_scope_t* scope, const char* val ) const {
  return snd_pcm_scope_set_name_( scope, val );
}
const char* ALSA::snd_pcm_scope_get_name( ALSA_detail::snd_pcm_scope_t* scope ) const {
  return snd_pcm_scope_get_name_( scope );
}
void* ALSA::snd_pcm_scope_get_callback_private( ALSA_detail::snd_pcm_scope_t* scope ) const {
  return snd_pcm_scope_get_callback_private_( scope );
}
void ALSA::snd_pcm_scope_set_callback_private( ALSA_detail::snd_pcm_scope_t* scope, void* val ) const {
  return snd_pcm_scope_set_callback_private_( scope, val );
}
int ALSA::snd_pcm_scope_s16_open( ALSA_detail::snd_pcm_t* pcm, const char* name, ALSA_detail::snd_pcm_scope_t** scopep ) const {
  return snd_pcm_scope_s16_open_( pcm, name, scopep );
}
int16_t* ALSA::snd_pcm_scope_s16_get_channel_buffer( ALSA_detail::snd_pcm_scope_t* scope, unsigned int channel ) const {
  return snd_pcm_scope_s16_get_channel_buffer_( scope, channel );
}
int ALSA::snd_spcm_init( ALSA_detail::snd_pcm_t* pcm, unsigned int rate, unsigned int channels, ALSA_detail::snd_pcm_format_t format, ALSA_detail::snd_pcm_subformat_t subformat, ALSA_detail::snd_spcm_latency_t latency, ALSA_detail::snd_pcm_access_t _access, ALSA_detail::snd_spcm_xrun_type_t xrun_type ) const {
  return snd_spcm_init_( pcm, rate, channels, format, subformat, latency, _access, xrun_type );
}
int ALSA::snd_spcm_init_duplex( ALSA_detail::snd_pcm_t* playback_pcm, ALSA_detail::snd_pcm_t* capture_pcm, unsigned int rate, unsigned int channels, ALSA_detail::snd_pcm_format_t format, ALSA_detail::snd_pcm_subformat_t subformat, ALSA_detail::snd_spcm_latency_t latency, ALSA_detail::snd_pcm_access_t _access, ALSA_detail::snd_spcm_xrun_type_t xrun_type, ALSA_detail::snd_spcm_duplex_type_t duplex_type ) const {
  return snd_spcm_init_duplex_( playback_pcm, capture_pcm, rate, channels, format, subformat, latency, _access, xrun_type, duplex_type );
}
int ALSA::snd_spcm_init_get_params( ALSA_detail::snd_pcm_t* pcm, unsigned int* rate, ALSA_detail::snd_pcm_uframes_t* buffer_size, ALSA_detail::snd_pcm_uframes_t* period_size ) const {
  return snd_spcm_init_get_params_( pcm, rate, buffer_size, period_size );
}

#undef DO_STUFF

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary
