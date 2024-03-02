#ifndef AUDIO_INTERFACE_PORTAUDIO_H_
#define AUDIO_INTERFACE_PORTAUDIO_H_

namespace PortAudio {

#include <portaudio.h>

PaDeviceIndex const noDevice = paNoDevice;
PaDeviceIndex const useHostApiSpecificDeviceSpecification = paUseHostApiSpecificDeviceSpecification;

PaSampleFormat const float32 = paFloat32;
PaSampleFormat const int32 = paInt32;
PaSampleFormat const int24 = paInt24;
PaSampleFormat const int16 = paInt16;
PaSampleFormat const int8 = paInt8;
PaSampleFormat const uInt8 = paUInt8;
PaSampleFormat const customFormat = paCustomFormat;
PaSampleFormat const nonInterleaved = paNonInterleaved;

PaError const formatIsSupported = paFormatIsSupported;

int const framesPerBufferUnspecified = paFramesPerBufferUnspecified;

PaStreamFlags const noFlag = paNoFlag;
PaStreamFlags const clipOff = paClipOff;
PaStreamFlags const ditherOff = paDitherOff;
PaStreamFlags const neverDropInput = paNeverDropInput;
PaStreamFlags const primeOutputBuffersUsingStreamCallback = paPrimeOutputBuffersUsingStreamCallback;
PaStreamFlags const platformSpecificFlags = paPlatformSpecificFlags;

PaStreamCallbackFlags const inputUnderflow = paInputUnderflow;
PaStreamCallbackFlags const inputOverflow = paInputOverflow;
PaStreamCallbackFlags const outputUnderflow = paOutputUnderflow;
PaStreamCallbackFlags const outputOverflow = paOutputOverflow;
PaStreamCallbackFlags const primingOutput = paPrimingOutput;

void unused();

}  // namespace PortAudio

#endif /* AUDIO_INTERFACE_PORTAUDIO_H_ */
