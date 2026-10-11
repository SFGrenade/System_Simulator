#pragma once

/*
 * Application interface library for the ALSA driver
 *
 *
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation; either version 2.1 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

// C++ Includes
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#if defined( _WIN32 ) || defined( _WIN64 )
using ssize_t = intmax_t;
#endif

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary::ALSA_detail {

#pragma region global.h

using snd_asoundlib_version = const char* (*)( void );

#if defined( _WIN32 ) || defined( _WIN64 )
#define __snd_alloca( ptr, type )                 \
  do {                                            \
    *ptr = (type##_t*)_alloca( type##_sizeof() ); \
    memset( *ptr, 0, type##_sizeof() );           \
  } while( 0 )
#elif defined( __APPLE__ ) || defined( __linux__ )
#define __snd_alloca( ptr, type )                \
  do {                                           \
    *ptr = (type##_t*)alloca( type##_sizeof() ); \
    memset( *ptr, 0, type##_sizeof() );          \
  } while( 0 )
#endif

#if defined( _WIN32 ) || defined( _WIN64 )
#define snd_alloca_better( ptr, tType, tSizeof ) \
  do {                                           \
    *ptr = (SFG::SystemSimulator::AudioInterface::DynamicLibrary::ALSA_detail::tType##_t*)_alloca( tSizeof##tType##_sizeof() );     \
    memset( *ptr, 0, tSizeof##tType##_sizeof() );                \
  } while( 0 )
#elif defined( __APPLE__ ) || defined( __linux__ )
#define snd_alloca_better( ptr, tType, tSizeof ) \
  do {                                           \
    *ptr = (SFG::SystemSimulator::AudioInterface::DynamicLibrary::ALSA_detail::tType##_t*)alloca( tSizeof##tType##_sizeof() );      \
    memset( *ptr, 0, tSizeof##tType##_sizeof() );                \
  } while( 0 )
#endif

struct snd_async_handler_t;

using snd_async_callback_t = void (*)( snd_async_handler_t* handler );

using snd_async_add_handler = int (*)( snd_async_handler_t** handler, int fd, snd_async_callback_t callback, void* private_data );
using snd_async_del_handler = int (*)( snd_async_handler_t* handler );
using snd_async_handler_get_fd = int (*)( snd_async_handler_t* handler );
using snd_async_handler_get_signo = int (*)( snd_async_handler_t* handler );
using snd_async_handler_get_callback_private = void* (*)( snd_async_handler_t * handler );

// using snd_shm_area_create = snd_shm_area* (*)( int shmid, void* ptr );
// using snd_shm_area_share = snd_shm_area* (*)( snd_shm_area * area );
// using snd_shm_area_destroy = int (*)( snd_shm_area* area );

using snd_user_file = int (*)( const char* file, char** result );

#ifdef __GLIBC__
#if !defined( _POSIX_C_SOURCE ) && !defined( _POSIX_SOURCE )
struct timeval {
  time_t tv_sec;
  long tv_usec;
};

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};
#endif
#endif

using snd_timestamp_t = struct timeval;
using snd_htimestamp_t = struct timespec;

#pragma endregion global.h

#pragma region error.h

using snd_strerror = const char* (*)( int errnum );

// type
using snd_lib_log_handler_t = void (*)( int prio, int interface, const char* file, int line, const char* function, int errcode, const char* fmt, ... );
using snd_lib_log_set_handler = snd_lib_log_handler_t (*)( snd_lib_log_handler_t handler );
using snd_lib_log_set_local = snd_lib_log_handler_t (*)( snd_lib_log_handler_t handler );

// type
using snd_lib_error_handler_t = void (*)( const char* file, int line, const char* function, int errcode, const char* fmt, ... ) /* __attribute__ ((format (printf, 5, 6))) */;
using snd_lib_error_set_handler = int (*)( snd_lib_error_handler_t handler );

// type
using snd_local_error_handler_t = void (*)( const char* file, int line, const char* func, int errcode, const char* fmt, ... );
using snd_lib_error_set_local = snd_local_error_handler_t (*)( snd_local_error_handler_t func );

#pragma endregion error.h

#pragma region pcm.h

struct snd_pcm_info_t;
struct snd_pcm_hw_params_t;
struct snd_pcm_sw_params_t;
struct snd_pcm_status_t;
struct snd_pcm_access_mask_t;
struct snd_pcm_format_mask_t;
struct snd_pcm_subformat_mask_t;

enum snd_pcm_class_t { SND_PCM_CLASS_GENERIC = 0, SND_PCM_CLASS_MULTI, SND_PCM_CLASS_MODEM, SND_PCM_CLASS_DIGITIZER, SND_PCM_CLASS_LAST = SND_PCM_CLASS_DIGITIZER };
enum snd_pcm_subclass_t { SND_PCM_SUBCLASS_GENERIC_MIX = 0, SND_PCM_SUBCLASS_MULTI_MIX, SND_PCM_SUBCLASS_LAST = SND_PCM_SUBCLASS_MULTI_MIX };
enum snd_pcm_stream_t { SND_PCM_STREAM_PLAYBACK = 0, SND_PCM_STREAM_CAPTURE, SND_PCM_STREAM_LAST = SND_PCM_STREAM_CAPTURE };
enum snd_pcm_access_t { SND_PCM_ACCESS_MMAP_INTERLEAVED = 0, SND_PCM_ACCESS_MMAP_NONINTERLEAVED, SND_PCM_ACCESS_MMAP_COMPLEX, SND_PCM_ACCESS_RW_INTERLEAVED, SND_PCM_ACCESS_RW_NONINTERLEAVED, SND_PCM_ACCESS_LAST = SND_PCM_ACCESS_RW_NONINTERLEAVED };
enum snd_pcm_format_t {
  SND_PCM_FORMAT_UNKNOWN = -1,
  SND_PCM_FORMAT_S8 = 0,
  SND_PCM_FORMAT_U8,
  SND_PCM_FORMAT_S16_LE,
  SND_PCM_FORMAT_S16_BE,
  SND_PCM_FORMAT_U16_LE,
  SND_PCM_FORMAT_U16_BE,
  SND_PCM_FORMAT_S24_LE,
  SND_PCM_FORMAT_S24_BE,
  SND_PCM_FORMAT_U24_LE,
  SND_PCM_FORMAT_U24_BE,
  SND_PCM_FORMAT_S32_LE,
  SND_PCM_FORMAT_S32_BE,
  SND_PCM_FORMAT_U32_LE,
  SND_PCM_FORMAT_U32_BE,
  SND_PCM_FORMAT_FLOAT_LE,
  SND_PCM_FORMAT_FLOAT_BE,
  SND_PCM_FORMAT_FLOAT64_LE,
  SND_PCM_FORMAT_FLOAT64_BE,
  SND_PCM_FORMAT_IEC958_SUBFRAME_LE,
  SND_PCM_FORMAT_IEC958_SUBFRAME_BE,
  SND_PCM_FORMAT_MU_LAW,
  SND_PCM_FORMAT_A_LAW,
  SND_PCM_FORMAT_IMA_ADPCM,
  SND_PCM_FORMAT_MPEG,
  SND_PCM_FORMAT_GSM,
  SND_PCM_FORMAT_S20_LE,
  SND_PCM_FORMAT_S20_BE,
  SND_PCM_FORMAT_U20_LE,
  SND_PCM_FORMAT_U20_BE,
  SND_PCM_FORMAT_SPECIAL = 31,
  SND_PCM_FORMAT_S24_3LE = 32,
  SND_PCM_FORMAT_S24_3BE,
  SND_PCM_FORMAT_U24_3LE,
  SND_PCM_FORMAT_U24_3BE,
  SND_PCM_FORMAT_S20_3LE,
  SND_PCM_FORMAT_S20_3BE,
  SND_PCM_FORMAT_U20_3LE,
  SND_PCM_FORMAT_U20_3BE,
  SND_PCM_FORMAT_S18_3LE,
  SND_PCM_FORMAT_S18_3BE,
  SND_PCM_FORMAT_U18_3LE,
  SND_PCM_FORMAT_U18_3BE,
  SND_PCM_FORMAT_G723_24,
  SND_PCM_FORMAT_G723_24_1B,
  SND_PCM_FORMAT_G723_40,
  SND_PCM_FORMAT_G723_40_1B,
  SND_PCM_FORMAT_DSD_U8,
  SND_PCM_FORMAT_DSD_U16_LE,
  SND_PCM_FORMAT_DSD_U32_LE,
  SND_PCM_FORMAT_DSD_U16_BE,
  SND_PCM_FORMAT_DSD_U32_BE,
  SND_PCM_FORMAT_LAST = SND_PCM_FORMAT_DSD_U32_BE,
#if __BYTE_ORDER == __LITTLE_ENDIAN
  SND_PCM_FORMAT_S16 = SND_PCM_FORMAT_S16_LE,
  SND_PCM_FORMAT_U16 = SND_PCM_FORMAT_U16_LE,
  SND_PCM_FORMAT_S24 = SND_PCM_FORMAT_S24_LE,
  SND_PCM_FORMAT_U24 = SND_PCM_FORMAT_U24_LE,
  SND_PCM_FORMAT_S32 = SND_PCM_FORMAT_S32_LE,
  SND_PCM_FORMAT_U32 = SND_PCM_FORMAT_U32_LE,
  SND_PCM_FORMAT_FLOAT = SND_PCM_FORMAT_FLOAT_LE,
  SND_PCM_FORMAT_FLOAT64 = SND_PCM_FORMAT_FLOAT64_LE,
  SND_PCM_FORMAT_IEC958_SUBFRAME = SND_PCM_FORMAT_IEC958_SUBFRAME_LE,
  SND_PCM_FORMAT_S20 = SND_PCM_FORMAT_S20_LE,
  SND_PCM_FORMAT_U20 = SND_PCM_FORMAT_U20_LE,
#elif __BYTE_ORDER == __BIG_ENDIAN
  SND_PCM_FORMAT_S16 = SND_PCM_FORMAT_S16_BE,
  SND_PCM_FORMAT_U16 = SND_PCM_FORMAT_U16_BE,
  SND_PCM_FORMAT_S24 = SND_PCM_FORMAT_S24_BE,
  SND_PCM_FORMAT_U24 = SND_PCM_FORMAT_U24_BE,
  SND_PCM_FORMAT_S32 = SND_PCM_FORMAT_S32_BE,
  SND_PCM_FORMAT_U32 = SND_PCM_FORMAT_U32_BE,
  SND_PCM_FORMAT_FLOAT = SND_PCM_FORMAT_FLOAT_BE,
  SND_PCM_FORMAT_FLOAT64 = SND_PCM_FORMAT_FLOAT64_BE,
  SND_PCM_FORMAT_IEC958_SUBFRAME = SND_PCM_FORMAT_IEC958_SUBFRAME_BE,
  SND_PCM_FORMAT_S20 = SND_PCM_FORMAT_S20_BE,
  SND_PCM_FORMAT_U20 = SND_PCM_FORMAT_U20_BE,
#else
#error "Unknown endian"
#endif
};
enum snd_pcm_subformat_t { SND_PCM_SUBFORMAT_UNKNOWN = -1, SND_PCM_SUBFORMAT_STD = 0, SND_PCM_SUBFORMAT_MSBITS_MAX = 1, SND_PCM_SUBFORMAT_MSBITS_20 = 2, SND_PCM_SUBFORMAT_MSBITS_24 = 3, SND_PCM_SUBFORMAT_LAST = SND_PCM_SUBFORMAT_MSBITS_24 };
enum snd_pcm_state_t { SND_PCM_STATE_OPEN = 0, SND_PCM_STATE_SETUP, SND_PCM_STATE_PREPARED, SND_PCM_STATE_RUNNING, SND_PCM_STATE_XRUN, SND_PCM_STATE_DRAINING, SND_PCM_STATE_PAUSED, SND_PCM_STATE_SUSPENDED, SND_PCM_STATE_DISCONNECTED, SND_PCM_STATE_LAST = SND_PCM_STATE_DISCONNECTED, SND_PCM_STATE_PRIVATE1 = 1024 };
enum snd_pcm_start_t { SND_PCM_START_DATA = 0, SND_PCM_START_EXPLICIT, SND_PCM_START_LAST = SND_PCM_START_EXPLICIT };
enum snd_pcm_xrun_t { SND_PCM_XRUN_NONE = 0, SND_PCM_XRUN_STOP, SND_PCM_XRUN_LAST = SND_PCM_XRUN_STOP };
enum snd_pcm_tstamp_t { SND_PCM_TSTAMP_NONE = 0, SND_PCM_TSTAMP_ENABLE, SND_PCM_TSTAMP_MMAP = SND_PCM_TSTAMP_ENABLE, SND_PCM_TSTAMP_LAST = SND_PCM_TSTAMP_ENABLE };
enum snd_pcm_tstamp_type_t {
  SND_PCM_TSTAMP_TYPE_GETTIMEOFDAY = 0,
  SND_PCM_TSTAMP_TYPE_MONOTONIC,
  SND_PCM_TSTAMP_TYPE_MONOTONIC_RAW,
  SND_PCM_TSTAMP_TYPE_LAST = SND_PCM_TSTAMP_TYPE_MONOTONIC_RAW,
};
enum snd_pcm_audio_tstamp_type_t { SND_PCM_AUDIO_TSTAMP_TYPE_COMPAT = 0, SND_PCM_AUDIO_TSTAMP_TYPE_DEFAULT = 1, SND_PCM_AUDIO_TSTAMP_TYPE_LINK = 2, SND_PCM_AUDIO_TSTAMP_TYPE_LINK_ABSOLUTE = 3, SND_PCM_AUDIO_TSTAMP_TYPE_LINK_ESTIMATED = 4, SND_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED = 5, SND_PCM_AUDIO_TSTAMP_TYPE_LAST = SND_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED };
struct snd_pcm_audio_tstamp_config_t {
  unsigned int type_requested : 4;
  unsigned int report_delay : 1;
};
struct snd_pcm_audio_tstamp_report_t {
  unsigned int valid : 1;
  unsigned int actual_type : 4;
  unsigned int accuracy_report : 1;
  unsigned int accuracy;
};

using snd_pcm_uframes_t = unsigned long;
using snd_pcm_sframes_t = long;

constexpr inline int32_t const SND_PCM_NONBLOCK = 0x00000001;
constexpr inline int32_t const SND_PCM_ASYNC = 0x00000002;
constexpr inline int32_t const SND_PCM_EINTR = 0x00000080;
constexpr inline int32_t const SND_PCM_ABORT = 0x00008000;
constexpr inline int32_t const SND_PCM_NO_AUTO_RESAMPLE = 0x00010000;
constexpr inline int32_t const SND_PCM_NO_AUTO_CHANNELS = 0x00020000;
constexpr inline int32_t const SND_PCM_NO_AUTO_FORMAT = 0x00040000;
constexpr inline int32_t const SND_PCM_NO_SOFTVOL = 0x00080000;

struct snd_pcm_t;

enum _snd_pcm_type { SND_PCM_TYPE_HW = 0, SND_PCM_TYPE_HOOKS, SND_PCM_TYPE_MULTI, SND_PCM_TYPE_FILE, SND_PCM_TYPE_NULL, SND_PCM_TYPE_SHM, SND_PCM_TYPE_INET, SND_PCM_TYPE_COPY, SND_PCM_TYPE_LINEAR, SND_PCM_TYPE_ALAW, SND_PCM_TYPE_MULAW, SND_PCM_TYPE_ADPCM, SND_PCM_TYPE_RATE, SND_PCM_TYPE_ROUTE, SND_PCM_TYPE_PLUG, SND_PCM_TYPE_SHARE, SND_PCM_TYPE_METER, SND_PCM_TYPE_MIX, SND_PCM_TYPE_DROUTE, SND_PCM_TYPE_LBSERVER, SND_PCM_TYPE_LINEAR_FLOAT, SND_PCM_TYPE_LADSPA, SND_PCM_TYPE_DMIX, SND_PCM_TYPE_JACK, SND_PCM_TYPE_DSNOOP, SND_PCM_TYPE_DSHARE, SND_PCM_TYPE_IEC958, SND_PCM_TYPE_SOFTVOL, SND_PCM_TYPE_IOPLUG, SND_PCM_TYPE_EXTPLUG, SND_PCM_TYPE_MMAP_EMUL, SND_PCM_TYPE_LAST = SND_PCM_TYPE_MMAP_EMUL };

enum snd_pcm_type_t;

struct snd_pcm_channel_area_t {
  void* addr;
  unsigned int first;
  unsigned int step;
};

union snd_pcm_sync_id_t {
  unsigned char id[16];
  unsigned short id16[8];
  unsigned int id32[4];
};

constexpr inline int32_t const SND_PCM_HW_PARAMS_SYNC_SIZE = 16;
constexpr inline int32_t const SND_PCM_WAIT_INFINITE = -1;
constexpr inline int32_t const SND_PCM_WAIT_IO = -10001;
constexpr inline int32_t const SND_PCM_WAIT_DRAIN = -10002;

struct snd_pcm_scope_t;

using snd_pcm_open = int (*)( snd_pcm_t** pcm, const char* name, snd_pcm_stream_t stream, int mode );
// using snd_pcm_open_lconf = int (*)( snd_pcm_t** pcm, const char* name, snd_pcm_stream_t stream, int mode, snd_config_t* lconf );
// using snd_pcm_open_fallback = int (*)( snd_pcm_t** pcm, snd_config_t* root, const char* name, const char* orig_name, snd_pcm_stream_t stream, int mode );

using snd_pcm_close = int (*)( snd_pcm_t* pcm );
using snd_pcm_name = const char* (*)( snd_pcm_t * pcm );
using snd_pcm_type = snd_pcm_type_t (*)( snd_pcm_t* pcm );
using snd_pcm_stream = snd_pcm_stream_t (*)( snd_pcm_t* pcm );
using snd_pcm_poll_descriptors_count = int (*)( snd_pcm_t* pcm );
// using snd_pcm_poll_descriptors = int (*)( snd_pcm_t* pcm, pollfd* pfds, unsigned int space );
// using snd_pcm_poll_descriptors_revents = int (*)( snd_pcm_t* pcm, pollfd* pfds, unsigned int nfds, unsigned short* revents );
using snd_pcm_nonblock = int (*)( snd_pcm_t* pcm, int nonblock );
using snd_pcm_abort = int (*)( snd_pcm_t* pcm );
using snd_async_add_pcm_handler = int (*)( snd_async_handler_t** handler, snd_pcm_t* pcm, snd_async_callback_t callback, void* private_data );
using snd_async_handler_get_pcm = snd_pcm_t* (*)( snd_async_handler_t * handler );
using snd_pcm_info = int (*)( snd_pcm_t* pcm, snd_pcm_info_t* info );
using snd_pcm_hw_params_current = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params );
using snd_pcm_hw_params = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params );
using snd_pcm_hw_free = int (*)( snd_pcm_t* pcm );
using snd_pcm_sw_params_current = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params );
using snd_pcm_sw_params = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params );
using snd_pcm_prepare = int (*)( snd_pcm_t* pcm );
using snd_pcm_reset = int (*)( snd_pcm_t* pcm );
using snd_pcm_status = int (*)( snd_pcm_t* pcm, snd_pcm_status_t* status );
using snd_pcm_start = int (*)( snd_pcm_t* pcm );
using snd_pcm_drop = int (*)( snd_pcm_t* pcm );
using snd_pcm_drain = int (*)( snd_pcm_t* pcm );
using snd_pcm_pause = int (*)( snd_pcm_t* pcm, int enable );
using snd_pcm_state = snd_pcm_state_t (*)( snd_pcm_t* pcm );
using snd_pcm_hwsync = int (*)( snd_pcm_t* pcm );
using snd_pcm_delay = int (*)( snd_pcm_t* pcm, snd_pcm_sframes_t* delayp );
using snd_pcm_resume = int (*)( snd_pcm_t* pcm );
using snd_pcm_htimestamp = int (*)( snd_pcm_t* pcm, snd_pcm_uframes_t* avail, snd_htimestamp_t* tstamp );
using snd_pcm_avail = snd_pcm_sframes_t (*)( snd_pcm_t* pcm );
using snd_pcm_avail_update = snd_pcm_sframes_t (*)( snd_pcm_t* pcm );
using snd_pcm_avail_delay = int (*)( snd_pcm_t* pcm, snd_pcm_sframes_t* availp, snd_pcm_sframes_t* delayp );
using snd_pcm_rewindable = snd_pcm_sframes_t (*)( snd_pcm_t* pcm );
using snd_pcm_rewind = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, snd_pcm_uframes_t frames );
using snd_pcm_forwardable = snd_pcm_sframes_t (*)( snd_pcm_t* pcm );
using snd_pcm_forward = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, snd_pcm_uframes_t frames );
using snd_pcm_writei = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, const void* buffer, snd_pcm_uframes_t size );
using snd_pcm_readi = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, void* buffer, snd_pcm_uframes_t size );
using snd_pcm_writen = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, void** bufs, snd_pcm_uframes_t size );
using snd_pcm_readn = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, void** bufs, snd_pcm_uframes_t size );
using snd_pcm_wait = int (*)( snd_pcm_t* pcm, int timeout );

using snd_pcm_link = int (*)( snd_pcm_t* pcm1, snd_pcm_t* pcm2 );
using snd_pcm_unlink = int (*)( snd_pcm_t* pcm );

constexpr inline int32_t const SND_CHMAP_API_VERSION = ( ( 1 << 16 ) | ( 0 << 8 ) | 1 );

enum snd_pcm_chmap_type {
  SND_CHMAP_TYPE_NONE = 0,
  SND_CHMAP_TYPE_FIXED,
  SND_CHMAP_TYPE_VAR,
  SND_CHMAP_TYPE_PAIRED,
  SND_CHMAP_TYPE_LAST = SND_CHMAP_TYPE_PAIRED,
};
enum snd_pcm_chmap_position {
  SND_CHMAP_UNKNOWN = 0,
  SND_CHMAP_NA,
  SND_CHMAP_MONO,
  SND_CHMAP_FL,
  SND_CHMAP_FR,
  SND_CHMAP_RL,
  SND_CHMAP_RR,
  SND_CHMAP_FC,
  SND_CHMAP_LFE,
  SND_CHMAP_SL,
  SND_CHMAP_SR,
  SND_CHMAP_RC,
  SND_CHMAP_FLC,
  SND_CHMAP_FRC,
  SND_CHMAP_RLC,
  SND_CHMAP_RRC,
  SND_CHMAP_FLW,
  SND_CHMAP_FRW,
  SND_CHMAP_FLH,
  SND_CHMAP_FCH,
  SND_CHMAP_FRH,
  SND_CHMAP_TC,
  SND_CHMAP_TFL,
  SND_CHMAP_TFR,
  SND_CHMAP_TFC,
  SND_CHMAP_TRL,
  SND_CHMAP_TRR,
  SND_CHMAP_TRC,
  SND_CHMAP_TFLC,
  SND_CHMAP_TFRC,
  SND_CHMAP_TSL,
  SND_CHMAP_TSR,
  SND_CHMAP_LLFE,
  SND_CHMAP_RLFE,
  SND_CHMAP_BC,
  SND_CHMAP_BLC,
  SND_CHMAP_BRC,
  SND_CHMAP_LAST = SND_CHMAP_BRC,
};

constexpr inline int32_t const SND_CHMAP_POSITION_MASK = 0xffff;
constexpr inline int32_t const SND_CHMAP_PHASE_INVERSE = ( 0x01 << 16 );
constexpr inline int32_t const SND_CHMAP_DRIVER_SPEC = ( 0x02 << 16 );

struct snd_pcm_chmap_t {
  unsigned int channels;
  unsigned int pos[0];
};
struct snd_pcm_chmap_query_t {
  enum snd_pcm_chmap_type;
  snd_pcm_chmap_type type;
  snd_pcm_chmap_t map;
};

using snd_pcm_query_chmaps = snd_pcm_chmap_query_t** (*)( snd_pcm_t * pcm );
using snd_pcm_query_chmaps_from_hw = snd_pcm_chmap_query_t** (*)( int card, int dev, int subdev, snd_pcm_stream_t stream );
using snd_pcm_free_chmaps = void (*)( snd_pcm_chmap_query_t** maps );
using snd_pcm_get_chmap = snd_pcm_chmap_t* (*)( snd_pcm_t * pcm );
using snd_pcm_set_chmap = int (*)( snd_pcm_t* pcm, const snd_pcm_chmap_t* map );

using snd_pcm_chmap_type_name = const char* (*)( snd_pcm_chmap_query_t::snd_pcm_chmap_type val );
using snd_pcm_chmap_name = const char* (*)( snd_pcm_chmap_position val );
using snd_pcm_chmap_long_name = const char* (*)( snd_pcm_chmap_position val );
using snd_pcm_chmap_print = int (*)( const snd_pcm_chmap_t* map, size_t maxlen, char* buf );
using snd_pcm_chmap_from_string = unsigned int (*)( const char* str );
using snd_pcm_chmap_parse_string = snd_pcm_chmap_t* (*)( const char* str );

using snd_pcm_recover = int (*)( snd_pcm_t* pcm, int err, int silent );
using snd_pcm_set_params = int (*)( snd_pcm_t* pcm, snd_pcm_format_t format, snd_pcm_access_t access, unsigned int channels, unsigned int rate, int soft_resample, unsigned int latency );
using snd_pcm_get_params = int (*)( snd_pcm_t* pcm, snd_pcm_uframes_t* buffer_size, snd_pcm_uframes_t* period_size );

using snd_pcm_info_sizeof = size_t (*)( void );

#define snd_pcm_info_alloca( ptr ) __snd_alloca( ptr, snd_pcm_info )
#define snd_pcm_info_alloc( ptr, tSizeof ) snd_alloca_better( ptr, snd_pcm_info, tSizeof )
using snd_pcm_info_malloc = int (*)( snd_pcm_info_t** ptr );
using snd_pcm_info_free = void (*)( snd_pcm_info_t* obj );
using snd_pcm_info_copy = void (*)( snd_pcm_info_t* dst, const snd_pcm_info_t* src );
using snd_pcm_info_get_device = unsigned int (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_subdevice = unsigned int (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_stream = snd_pcm_stream_t (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_card = int (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_id = const char* (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_name = const char* (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_subdevice_name = const char* (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_class = snd_pcm_class_t (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_subclass = snd_pcm_subclass_t (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_subdevices_count = unsigned int (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_subdevices_avail = unsigned int (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_get_sync = snd_pcm_sync_id_t (*)( const snd_pcm_info_t* obj );
using snd_pcm_info_set_device = void (*)( snd_pcm_info_t* obj, unsigned int val );
using snd_pcm_info_set_subdevice = void (*)( snd_pcm_info_t* obj, unsigned int val );
using snd_pcm_info_set_stream = void (*)( snd_pcm_info_t* obj, snd_pcm_stream_t val );

using snd_pcm_hw_params_any = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params );

using snd_pcm_hw_params_can_mmap_sample_resolution = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_is_double = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_is_batch = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_is_block_transfer = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_is_monotonic = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_can_overrange = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_can_pause = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_can_resume = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_is_half_duplex = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_is_joint_duplex = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_can_sync_start = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_can_disable_period_wakeup = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_is_perfect_drain = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_supports_audio_wallclock_ts = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_supports_audio_ts_type = int (*)( const snd_pcm_hw_params_t* params, int type );
using snd_pcm_hw_params_get_rate_numden = int (*)( const snd_pcm_hw_params_t* params, unsigned int* rate_num, unsigned int* rate_den );
using snd_pcm_hw_params_get_sbits = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_get_fifo_size = int (*)( const snd_pcm_hw_params_t* params );
using snd_pcm_hw_params_get_sync = const unsigned char* (*)( const snd_pcm_hw_params_t* params );

using snd_pcm_hw_params_sizeof = size_t (*)( void );
#define snd_pcm_hw_params_alloca( ptr ) __snd_alloca( ptr, snd_pcm_hw_params )
#define snd_pcm_hw_params_alloc( ptr, tSizeof ) snd_alloca_better( ptr, snd_pcm_hw_params, tSizeof )
using snd_pcm_hw_params_malloc = int (*)( snd_pcm_hw_params_t** ptr );
using snd_pcm_hw_params_free = void (*)( snd_pcm_hw_params_t* obj );
using snd_pcm_hw_params_copy = void (*)( snd_pcm_hw_params_t* dst, const snd_pcm_hw_params_t* src );

using snd_pcm_hw_params_get_access = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_access_t* _access );
using snd_pcm_hw_params_test_access = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_access_t _access );
using snd_pcm_hw_params_set_access = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_access_t _access );
using snd_pcm_hw_params_set_access_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_access_t* _access );
using snd_pcm_hw_params_set_access_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_access_t* _access );
using snd_pcm_hw_params_set_access_mask = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_access_mask_t* mask );
using snd_pcm_hw_params_get_access_mask = int (*)( snd_pcm_hw_params_t* params, snd_pcm_access_mask_t* mask );

using snd_pcm_hw_params_get_format = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_format_t* val );
using snd_pcm_hw_params_test_format = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_format_t val );
using snd_pcm_hw_params_set_format = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_format_t val );
using snd_pcm_hw_params_set_format_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_format_t* format );
using snd_pcm_hw_params_set_format_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_format_t* format );
using snd_pcm_hw_params_set_format_mask = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_format_mask_t* mask );
using snd_pcm_hw_params_get_format_mask = void (*)( snd_pcm_hw_params_t* params, snd_pcm_format_mask_t* mask );

using snd_pcm_hw_params_get_subformat = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_subformat_t* subformat );
using snd_pcm_hw_params_test_subformat = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_subformat_t subformat );
using snd_pcm_hw_params_set_subformat = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_subformat_t subformat );
using snd_pcm_hw_params_set_subformat_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_subformat_t* subformat );
using snd_pcm_hw_params_set_subformat_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_subformat_t* subformat );
using snd_pcm_hw_params_set_subformat_mask = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_subformat_mask_t* mask );
using snd_pcm_hw_params_get_subformat_mask = void (*)( snd_pcm_hw_params_t* params, snd_pcm_subformat_mask_t* mask );

using snd_pcm_hw_params_get_channels = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_get_channels_min = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_get_channels_max = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_test_channels = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val );
using snd_pcm_hw_params_set_channels = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val );
using snd_pcm_hw_params_set_channels_min = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_set_channels_max = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_set_channels_minmax = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* min, unsigned int* max );
using snd_pcm_hw_params_set_channels_near = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_set_channels_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_set_channels_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );

using snd_pcm_hw_params_get_rate = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_get_rate_min = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_get_rate_max = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_test_rate = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val, int dir );
using snd_pcm_hw_params_set_rate = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val, int dir );
using snd_pcm_hw_params_set_rate_min = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_rate_max = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_rate_minmax = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* min, int* mindir, unsigned int* max, int* maxdir );
using snd_pcm_hw_params_set_rate_near = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_rate_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_rate_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_rate_resample = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val );
using snd_pcm_hw_params_get_rate_resample = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_set_export_buffer = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val );
using snd_pcm_hw_params_get_export_buffer = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_set_period_wakeup = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val );
using snd_pcm_hw_params_get_period_wakeup = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );
using snd_pcm_hw_params_set_drain_silence = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val );
using snd_pcm_hw_params_get_drain_silence = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val );

using snd_pcm_hw_params_get_period_time = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_get_period_time_min = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_get_period_time_max = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_test_period_time = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val, int dir );
using snd_pcm_hw_params_set_period_time = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val, int dir );
using snd_pcm_hw_params_set_period_time_min = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_period_time_max = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_period_time_minmax = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* min, int* mindir, unsigned int* max, int* maxdir );
using snd_pcm_hw_params_set_period_time_near = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_period_time_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_period_time_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );

using snd_pcm_hw_params_get_period_size = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_uframes_t* frames, int* dir );
using snd_pcm_hw_params_get_period_size_min = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_uframes_t* frames, int* dir );
using snd_pcm_hw_params_get_period_size_max = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_uframes_t* frames, int* dir );
using snd_pcm_hw_params_test_period_size = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t val, int dir );
using snd_pcm_hw_params_set_period_size = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t val, int dir );
using snd_pcm_hw_params_set_period_size_min = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val, int* dir );
using snd_pcm_hw_params_set_period_size_max = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val, int* dir );
using snd_pcm_hw_params_set_period_size_minmax = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* min, int* mindir, snd_pcm_uframes_t* max, int* maxdir );
using snd_pcm_hw_params_set_period_size_near = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val, int* dir );
using snd_pcm_hw_params_set_period_size_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val, int* dir );
using snd_pcm_hw_params_set_period_size_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val, int* dir );
using snd_pcm_hw_params_set_period_size_integer = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params );

using snd_pcm_hw_params_get_periods = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_get_periods_min = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_get_periods_max = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_test_periods = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val, int dir );
using snd_pcm_hw_params_set_periods = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val, int dir );
using snd_pcm_hw_params_set_periods_min = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_periods_max = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_periods_minmax = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* min, int* mindir, unsigned int* max, int* maxdir );
using snd_pcm_hw_params_set_periods_near = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_periods_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_periods_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_periods_integer = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params );

using snd_pcm_hw_params_get_buffer_time = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_get_buffer_time_min = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_get_buffer_time_max = int (*)( const snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_test_buffer_time = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val, int dir );
using snd_pcm_hw_params_set_buffer_time = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val, int dir );
using snd_pcm_hw_params_set_buffer_time_min = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_buffer_time_max = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_buffer_time_minmax = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* min, int* mindir, unsigned int* max, int* maxdir );
using snd_pcm_hw_params_set_buffer_time_near = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_buffer_time_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );
using snd_pcm_hw_params_set_buffer_time_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir );

using snd_pcm_hw_params_get_buffer_size = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_hw_params_get_buffer_size_min = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_hw_params_get_buffer_size_max = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_hw_params_test_buffer_size = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t val );
using snd_pcm_hw_params_set_buffer_size = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t val );
using snd_pcm_hw_params_set_buffer_size_min = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_hw_params_set_buffer_size_max = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_hw_params_set_buffer_size_minmax = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* min, snd_pcm_uframes_t* max );
using snd_pcm_hw_params_set_buffer_size_near = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_hw_params_set_buffer_size_first = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_hw_params_set_buffer_size_last = int (*)( snd_pcm_t* pcm, snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );

using snd_pcm_hw_params_get_min_align = int (*)( const snd_pcm_hw_params_t* params, snd_pcm_uframes_t* val );

using snd_pcm_sw_params_sizeof = size_t (*)( void );
#define snd_pcm_sw_params_alloca( ptr ) __snd_alloca( ptr, snd_pcm_sw_params )
#define snd_pcm_sw_params_alloc( ptr, tSizeof ) snd_alloca_better( ptr, snd_pcm_sw_params, tSizeof )
using snd_pcm_sw_params_malloc = int (*)( snd_pcm_sw_params_t** ptr );
using snd_pcm_sw_params_free = void (*)( snd_pcm_sw_params_t* obj );
using snd_pcm_sw_params_copy = void (*)( snd_pcm_sw_params_t* dst, const snd_pcm_sw_params_t* src );
using snd_pcm_sw_params_get_boundary = int (*)( const snd_pcm_sw_params_t* params, snd_pcm_uframes_t* val );

using snd_pcm_sw_params_set_tstamp_mode = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params, snd_pcm_tstamp_t val );
using snd_pcm_sw_params_get_tstamp_mode = int (*)( const snd_pcm_sw_params_t* params, snd_pcm_tstamp_t* val );
using snd_pcm_sw_params_set_tstamp_type = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params, snd_pcm_tstamp_type_t val );
using snd_pcm_sw_params_get_tstamp_type = int (*)( const snd_pcm_sw_params_t* params, snd_pcm_tstamp_type_t* val );
using snd_pcm_sw_params_set_avail_min = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params, snd_pcm_uframes_t val );
using snd_pcm_sw_params_get_avail_min = int (*)( const snd_pcm_sw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_sw_params_set_period_event = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params, int val );
using snd_pcm_sw_params_get_period_event = int (*)( const snd_pcm_sw_params_t* params, int* val );
using snd_pcm_sw_params_set_start_threshold = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params, snd_pcm_uframes_t val );
using snd_pcm_sw_params_get_start_threshold = int (*)( const snd_pcm_sw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_sw_params_set_stop_threshold = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params, snd_pcm_uframes_t val );
using snd_pcm_sw_params_get_stop_threshold = int (*)( const snd_pcm_sw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_sw_params_set_silence_threshold = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params, snd_pcm_uframes_t val );
using snd_pcm_sw_params_get_silence_threshold = int (*)( const snd_pcm_sw_params_t* params, snd_pcm_uframes_t* val );
using snd_pcm_sw_params_set_silence_size = int (*)( snd_pcm_t* pcm, snd_pcm_sw_params_t* params, snd_pcm_uframes_t val );
using snd_pcm_sw_params_get_silence_size = int (*)( const snd_pcm_sw_params_t* params, snd_pcm_uframes_t* val );

using snd_pcm_access_mask_sizeof = size_t (*)( void );
#define snd_pcm_access_mask_alloca( ptr ) __snd_alloca( ptr, snd_pcm_access_mask )
#define snd_pcm_access_mask_alloc( ptr, tSizeof ) snd_alloca_better( ptr, snd_pcm_access_mask, tSizeof )
using snd_pcm_access_mask_malloc = int (*)( snd_pcm_access_mask_t** ptr );
using snd_pcm_access_mask_free = void (*)( snd_pcm_access_mask_t* obj );
using snd_pcm_access_mask_copy = void (*)( snd_pcm_access_mask_t* dst, const snd_pcm_access_mask_t* src );
using snd_pcm_access_mask_none = void (*)( snd_pcm_access_mask_t* mask );
using snd_pcm_access_mask_any = void (*)( snd_pcm_access_mask_t* mask );
using snd_pcm_access_mask_test = int (*)( const snd_pcm_access_mask_t* mask, snd_pcm_access_t val );
using snd_pcm_access_mask_empty = int (*)( const snd_pcm_access_mask_t* mask );
using snd_pcm_access_mask_set = void (*)( snd_pcm_access_mask_t* mask, snd_pcm_access_t val );
using snd_pcm_access_mask_reset = void (*)( snd_pcm_access_mask_t* mask, snd_pcm_access_t val );

using snd_pcm_format_mask_sizeof = size_t (*)( void );
#define snd_pcm_format_mask_alloca( ptr ) __snd_alloca( ptr, snd_pcm_format_mask )
#define snd_pcm_format_mask_alloc( ptr, tSizeof ) snd_alloca_better( ptr, snd_pcm_format_mask, tSizeof )
using snd_pcm_format_mask_malloc = int (*)( snd_pcm_format_mask_t** ptr );
using snd_pcm_format_mask_free = void (*)( snd_pcm_format_mask_t* obj );
using snd_pcm_format_mask_copy = void (*)( snd_pcm_format_mask_t* dst, const snd_pcm_format_mask_t* src );
using snd_pcm_format_mask_none = void (*)( snd_pcm_format_mask_t* mask );
using snd_pcm_format_mask_any = void (*)( snd_pcm_format_mask_t* mask );
using snd_pcm_format_mask_test = int (*)( const snd_pcm_format_mask_t* mask, snd_pcm_format_t val );
using snd_pcm_format_mask_empty = int (*)( const snd_pcm_format_mask_t* mask );
using snd_pcm_format_mask_set = void (*)( snd_pcm_format_mask_t* mask, snd_pcm_format_t val );
using snd_pcm_format_mask_reset = void (*)( snd_pcm_format_mask_t* mask, snd_pcm_format_t val );

using snd_pcm_subformat_mask_sizeof = size_t (*)( void );
#define snd_pcm_subformat_mask_alloca( ptr ) __snd_alloca( ptr, snd_pcm_subformat_mask )
#define snd_pcm_subformat_mask_alloc( ptr, tSizeof ) snd_alloca_better( ptr, snd_pcm_subformat_mask, tSizeof )
using snd_pcm_subformat_mask_malloc = int (*)( snd_pcm_subformat_mask_t** ptr );
using snd_pcm_subformat_mask_free = void (*)( snd_pcm_subformat_mask_t* obj );
using snd_pcm_subformat_mask_copy = void (*)( snd_pcm_subformat_mask_t* dst, const snd_pcm_subformat_mask_t* src );
using snd_pcm_subformat_mask_none = void (*)( snd_pcm_subformat_mask_t* mask );
using snd_pcm_subformat_mask_any = void (*)( snd_pcm_subformat_mask_t* mask );
using snd_pcm_subformat_mask_test = int (*)( const snd_pcm_subformat_mask_t* mask, snd_pcm_subformat_t val );
using snd_pcm_subformat_mask_empty = int (*)( const snd_pcm_subformat_mask_t* mask );
using snd_pcm_subformat_mask_set = void (*)( snd_pcm_subformat_mask_t* mask, snd_pcm_subformat_t val );
using snd_pcm_subformat_mask_reset = void (*)( snd_pcm_subformat_mask_t* mask, snd_pcm_subformat_t val );

using snd_pcm_status_sizeof = size_t (*)( void );
#define snd_pcm_status_alloca( ptr ) __snd_alloca( ptr, snd_pcm_status )
#define snd_pcm_status_alloc( ptr, tSizeof ) snd_alloca_better( ptr, snd_pcm_status, tSizeof )
using snd_pcm_status_malloc = int (*)( snd_pcm_status_t** ptr );
using snd_pcm_status_free = void (*)( snd_pcm_status_t* obj );
using snd_pcm_status_copy = void (*)( snd_pcm_status_t* dst, const snd_pcm_status_t* src );
using snd_pcm_status_get_state = snd_pcm_state_t (*)( const snd_pcm_status_t* obj );
using snd_pcm_status_get_trigger_tstamp = void (*)( const snd_pcm_status_t* obj, snd_timestamp_t* ptr );
using snd_pcm_status_get_trigger_htstamp = void (*)( const snd_pcm_status_t* obj, snd_htimestamp_t* ptr );
using snd_pcm_status_get_tstamp = void (*)( const snd_pcm_status_t* obj, snd_timestamp_t* ptr );
using snd_pcm_status_get_htstamp = void (*)( const snd_pcm_status_t* obj, snd_htimestamp_t* ptr );
using snd_pcm_status_get_audio_htstamp = void (*)( const snd_pcm_status_t* obj, snd_htimestamp_t* ptr );
using snd_pcm_status_get_driver_htstamp = void (*)( const snd_pcm_status_t* obj, snd_htimestamp_t* ptr );
using snd_pcm_status_get_audio_htstamp_report = void (*)( const snd_pcm_status_t* obj, snd_pcm_audio_tstamp_report_t* audio_tstamp_report );
using snd_pcm_status_set_audio_htstamp_config = void (*)( snd_pcm_status_t* obj, snd_pcm_audio_tstamp_config_t* audio_tstamp_config );

using snd_pcm_pack_audio_tstamp_config = void (*)( unsigned int* data, snd_pcm_audio_tstamp_config_t* config );
using snd_pcm_unpack_audio_tstamp_report = void (*)( unsigned int data, unsigned int accuracy, snd_pcm_audio_tstamp_report_t* report );

using snd_pcm_status_get_delay = snd_pcm_sframes_t (*)( const snd_pcm_status_t* obj );
using snd_pcm_status_get_avail = snd_pcm_uframes_t (*)( const snd_pcm_status_t* obj );
using snd_pcm_status_get_avail_max = snd_pcm_uframes_t (*)( const snd_pcm_status_t* obj );
using snd_pcm_status_get_overrange = snd_pcm_uframes_t (*)( const snd_pcm_status_t* obj );

using snd_pcm_type_name = const char* (*)( snd_pcm_type_t type );
using snd_pcm_stream_name = const char* (*)( const snd_pcm_stream_t stream );
using snd_pcm_access_name = const char* (*)( const snd_pcm_access_t _access );
using snd_pcm_format_name = const char* (*)( const snd_pcm_format_t format );
using snd_pcm_format_description = const char* (*)( const snd_pcm_format_t format );
using snd_pcm_subformat_name = const char* (*)( const snd_pcm_subformat_t subformat );
using snd_pcm_subformat_description = const char* (*)( const snd_pcm_subformat_t subformat );
using snd_pcm_subformat_value = snd_pcm_subformat_t (*)( const char* name );
using snd_pcm_format_value = snd_pcm_format_t (*)( const char* name );
using snd_pcm_tstamp_mode_name = const char* (*)( const snd_pcm_tstamp_t mode );
using snd_pcm_state_name = const char* (*)( const snd_pcm_state_t state );

// using snd_pcm_dump = int (*)( snd_pcm_t* pcm, snd_output_t* out );
// using snd_pcm_dump_hw_setup = int (*)( snd_pcm_t* pcm, snd_output_t* out );
// using snd_pcm_dump_sw_setup = int (*)( snd_pcm_t* pcm, snd_output_t* out );
// using snd_pcm_dump_setup = int (*)( snd_pcm_t* pcm, snd_output_t* out );
// using snd_pcm_hw_params_dump = int (*)( snd_pcm_hw_params_t* params, snd_output_t* out );
// using snd_pcm_sw_params_dump = int (*)( snd_pcm_sw_params_t* params, snd_output_t* out );
// using snd_pcm_status_dump = int (*)( snd_pcm_status_t* status, snd_output_t* out );

using snd_pcm_mmap_begin = int (*)( snd_pcm_t* pcm, const snd_pcm_channel_area_t** areas, snd_pcm_uframes_t* offset, snd_pcm_uframes_t* frames );
using snd_pcm_mmap_commit = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, snd_pcm_uframes_t offset, snd_pcm_uframes_t frames );
using snd_pcm_mmap_writei = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, const void* buffer, snd_pcm_uframes_t size );
using snd_pcm_mmap_readi = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, void* buffer, snd_pcm_uframes_t size );
using snd_pcm_mmap_writen = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, void** bufs, snd_pcm_uframes_t size );
using snd_pcm_mmap_readn = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, void** bufs, snd_pcm_uframes_t size );

using snd_pcm_format_signed = int (*)( snd_pcm_format_t format );
using snd_pcm_format_unsigned = int (*)( snd_pcm_format_t format );
using snd_pcm_format_linear = int (*)( snd_pcm_format_t format );
using snd_pcm_format_float = int (*)( snd_pcm_format_t format );
using snd_pcm_format_little_endian = int (*)( snd_pcm_format_t format );
using snd_pcm_format_big_endian = int (*)( snd_pcm_format_t format );
using snd_pcm_format_cpu_endian = int (*)( snd_pcm_format_t format );
using snd_pcm_format_width = int (*)( snd_pcm_format_t format );
using snd_pcm_format_physical_width = int (*)( snd_pcm_format_t format );
using snd_pcm_build_linear_format = snd_pcm_format_t (*)( int width, int pwidth, int unsignd, int big_endian );
using snd_pcm_format_size = ssize_t (*)( snd_pcm_format_t format, size_t samples );
using snd_pcm_format_silence = uint8_t (*)( snd_pcm_format_t format );
using snd_pcm_format_silence_16 = uint16_t (*)( snd_pcm_format_t format );
using snd_pcm_format_silence_32 = uint32_t (*)( snd_pcm_format_t format );
using snd_pcm_format_silence_64 = uint64_t (*)( snd_pcm_format_t format );
using snd_pcm_format_set_silence = int (*)( snd_pcm_format_t format, void* buf, unsigned int samples );

using snd_pcm_bytes_to_frames = snd_pcm_sframes_t (*)( snd_pcm_t* pcm, ssize_t bytes );
using snd_pcm_frames_to_bytes = ssize_t (*)( snd_pcm_t* pcm, snd_pcm_sframes_t frames );
using snd_pcm_bytes_to_samples = long (*)( snd_pcm_t* pcm, ssize_t bytes );
using snd_pcm_samples_to_bytes = ssize_t (*)( snd_pcm_t* pcm, long samples );

using snd_pcm_area_silence = int (*)( const snd_pcm_channel_area_t* dst_channel, snd_pcm_uframes_t dst_offset, unsigned int samples, snd_pcm_format_t format );
using snd_pcm_areas_silence = int (*)( const snd_pcm_channel_area_t* dst_channels, snd_pcm_uframes_t dst_offset, unsigned int channels, snd_pcm_uframes_t frames, snd_pcm_format_t format );
using snd_pcm_area_copy = int (*)( const snd_pcm_channel_area_t* dst_channel, snd_pcm_uframes_t dst_offset, const snd_pcm_channel_area_t* src_channel, snd_pcm_uframes_t src_offset, unsigned int samples, snd_pcm_format_t format );
using snd_pcm_areas_copy = int (*)( const snd_pcm_channel_area_t* dst_channels, snd_pcm_uframes_t dst_offset, const snd_pcm_channel_area_t* src_channels, snd_pcm_uframes_t src_offset, unsigned int channels, snd_pcm_uframes_t frames, snd_pcm_format_t format );
using snd_pcm_areas_copy_wrap = int (*)( const snd_pcm_channel_area_t* dst_channels, snd_pcm_uframes_t dst_offset, const snd_pcm_uframes_t dst_size, const snd_pcm_channel_area_t* src_channels, snd_pcm_uframes_t src_offset, const snd_pcm_uframes_t src_size, const unsigned int channels, snd_pcm_uframes_t frames, const snd_pcm_format_t format );

using snd_pcm_channel_area_addr = void* (*)( const snd_pcm_channel_area_t* area, snd_pcm_uframes_t offset );

using snd_pcm_channel_area_step = unsigned int (*)( const snd_pcm_channel_area_t* area );

enum snd_pcm_hook_type_t { SND_PCM_HOOK_TYPE_HW_PARAMS = 0, SND_PCM_HOOK_TYPE_HW_FREE, SND_PCM_HOOK_TYPE_CLOSE, SND_PCM_HOOK_TYPE_LAST = SND_PCM_HOOK_TYPE_CLOSE };

struct snd_pcm_hook_t;
using snd_pcm_hook_func_t = int (*)( snd_pcm_hook_t* hook );
using snd_pcm_hook_get_pcm = snd_pcm_t* (*)( snd_pcm_hook_t * hook );
using snd_pcm_hook_get_private = void* (*)( snd_pcm_hook_t * hook );
using snd_pcm_hook_set_private = void (*)( snd_pcm_hook_t* hook, void* private_data );
using snd_pcm_hook_add = int (*)( snd_pcm_hook_t** hookp, snd_pcm_t* pcm, snd_pcm_hook_type_t type, snd_pcm_hook_func_t func, void* private_data );
using snd_pcm_hook_remove = int (*)( snd_pcm_hook_t* hook );

struct snd_pcm_scope_ops_t {
  int ( *enable )( snd_pcm_scope_t* scope );
  void ( *disable )( snd_pcm_scope_t* scope );
  void ( *start )( snd_pcm_scope_t* scope );
  void ( *stop )( snd_pcm_scope_t* scope );
  void ( *update )( snd_pcm_scope_t* scope );
  void ( *reset )( snd_pcm_scope_t* scope );
  void ( *close )( snd_pcm_scope_t* scope );
};

using snd_pcm_meter_get_bufsize = snd_pcm_uframes_t (*)( snd_pcm_t* pcm );
using snd_pcm_meter_get_channels = unsigned int (*)( snd_pcm_t* pcm );
using snd_pcm_meter_get_rate = unsigned int (*)( snd_pcm_t* pcm );
using snd_pcm_meter_get_now = snd_pcm_uframes_t (*)( snd_pcm_t* pcm );
using snd_pcm_meter_get_boundary = snd_pcm_uframes_t (*)( snd_pcm_t* pcm );
using snd_pcm_meter_add_scope = int (*)( snd_pcm_t* pcm, snd_pcm_scope_t* scope );
using snd_pcm_meter_search_scope = snd_pcm_scope_t* (*)( snd_pcm_t * pcm, const char* name );
using snd_pcm_scope_malloc = int (*)( snd_pcm_scope_t** ptr );
using snd_pcm_scope_set_ops = void (*)( snd_pcm_scope_t* scope, const snd_pcm_scope_ops_t* val );
using snd_pcm_scope_set_name = void (*)( snd_pcm_scope_t* scope, const char* val );
using snd_pcm_scope_get_name = const char* (*)( snd_pcm_scope_t * scope );
using snd_pcm_scope_get_callback_private = void* (*)( snd_pcm_scope_t * scope );
using snd_pcm_scope_set_callback_private = void (*)( snd_pcm_scope_t* scope, void* val );
using snd_pcm_scope_s16_open = int (*)( snd_pcm_t* pcm, const char* name, snd_pcm_scope_t** scopep );
using snd_pcm_scope_s16_get_channel_buffer = int16_t* (*)( snd_pcm_scope_t * scope, unsigned int channel );

enum snd_spcm_latency_t { SND_SPCM_LATENCY_STANDARD = 0, SND_SPCM_LATENCY_MEDIUM, SND_SPCM_LATENCY_REALTIME };
enum snd_spcm_xrun_type_t { SND_SPCM_XRUN_IGNORE = 0, SND_SPCM_XRUN_STOP };
enum snd_spcm_duplex_type_t { SND_SPCM_DUPLEX_LIBERAL = 0, SND_SPCM_DUPLEX_PEDANTIC };

using snd_spcm_init = int (*)( snd_pcm_t* pcm, unsigned int rate, unsigned int channels, snd_pcm_format_t format, snd_pcm_subformat_t subformat, snd_spcm_latency_t latency, snd_pcm_access_t _access, snd_spcm_xrun_type_t xrun_type );

using snd_spcm_init_duplex = int (*)( snd_pcm_t* playback_pcm, snd_pcm_t* capture_pcm, unsigned int rate, unsigned int channels, snd_pcm_format_t format, snd_pcm_subformat_t subformat, snd_spcm_latency_t latency, snd_pcm_access_t _access, snd_spcm_xrun_type_t xrun_type, snd_spcm_duplex_type_t duplex_type );

using snd_spcm_init_get_params = int (*)( snd_pcm_t* pcm, unsigned int* rate, snd_pcm_uframes_t* buffer_size, snd_pcm_uframes_t* period_size );

#pragma endregion pcm.h

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary::ALSA_detail
