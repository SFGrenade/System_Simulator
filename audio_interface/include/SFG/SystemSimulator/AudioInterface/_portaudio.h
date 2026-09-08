#pragma once

// Library Includes
#include <portaudio.h>

// C++ Includes
#include <string>

namespace PA {

constexpr PaDeviceIndex const noDevice = paNoDevice;
constexpr PaDeviceIndex const useHostApiSpecificDeviceSpecification = paUseHostApiSpecificDeviceSpecification;

constexpr PaSampleFormat const float32 = paFloat32;
constexpr PaSampleFormat const int32 = paInt32;
constexpr PaSampleFormat const int24 = paInt24;
constexpr PaSampleFormat const int16 = paInt16;
constexpr PaSampleFormat const int8 = paInt8;
constexpr PaSampleFormat const uInt8 = paUInt8;
constexpr PaSampleFormat const customFormat = paCustomFormat;
constexpr PaSampleFormat const nonInterleaved = paNonInterleaved;

constexpr PaError const formatIsSupported = paFormatIsSupported;

constexpr int const framesPerBufferUnspecified = paFramesPerBufferUnspecified;

constexpr PaStreamFlags const noFlag = paNoFlag;
constexpr PaStreamFlags const clipOff = paClipOff;
constexpr PaStreamFlags const ditherOff = paDitherOff;
constexpr PaStreamFlags const neverDropInput = paNeverDropInput;
constexpr PaStreamFlags const primeOutputBuffersUsingStreamCallback = paPrimeOutputBuffersUsingStreamCallback;
constexpr PaStreamFlags const platformSpecificFlags = paPlatformSpecificFlags;

constexpr PaStreamCallbackFlags const inputUnderflow = paInputUnderflow;
constexpr PaStreamCallbackFlags const inputOverflow = paInputOverflow;
constexpr PaStreamCallbackFlags const outputUnderflow = paOutputUnderflow;
constexpr PaStreamCallbackFlags const outputOverflow = paOutputOverflow;
constexpr PaStreamCallbackFlags const primingOutput = paPrimingOutput;

void ListInfo();
PaDeviceIndex GetDevice( std::string const& deviceName, std::string const& apiName );

}  // namespace PA
