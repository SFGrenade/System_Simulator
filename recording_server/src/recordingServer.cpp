#include "SFG/SystemSimulator/RecordingServer/recordingServer.h"

namespace SFG {
namespace SystemSimulator {
namespace RecordingServer {

RecordingServer::RecordingServer()
    : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "RecordingServer" ) ), config_( "config/recording_server.ini" ) {
  this->logger_->trace( fmt::runtime( "RecordingServer" ) );

  this->logger_->trace( fmt::runtime( "RecordingServer~" ) );
}

RecordingServer::~RecordingServer() {
  this->logger_->trace( fmt::runtime( "~RecordingServer" ) );

  this->logger_->trace( fmt::runtime( "~RecordingServer~" ) );
}

void RecordingServer::setupAudioGenerator( std::string const& generatorId,
                                           AudioFormatType format,
                                           uint16_t channels,
                                           uint32_t sampleRate,
                                           uint16_t bitsPerSample ) {
  this->logger_->trace( fmt::runtime( "setupAudioGenerator( generatorId = '{:s}', format: {:d}, channels: {:d}, sampleRate: {:d}, bitsPerSample: {:d} )" ),
                        generatorId,
                        static_cast< uint16_t >( format ),
                        channels,
                        sampleRate,
                        bitsPerSample );

  if( this->audioMap_.contains( generatorId ) ) {
    this->logger_->error( fmt::runtime( "setupAudioGenerator - Generator '{:s}' already existing" ), generatorId );
  } else {
    this->audioMap_[generatorId]
        = AudioInformation{ .type = format, .channels = channels, .sampleRate = sampleRate, .bitsPerSample = bitsPerSample, .audioData = std::list< BYTE >() };
  }

  this->logger_->trace( fmt::runtime( "setupAudioGenerator~" ) );
}

void RecordingServer::streamAudioFrame( std::string const& generatorId, std::list< BYTE > data ) {
  std::stringstream audioDataStream;
  for( BYTE byte : data ) {
    audioDataStream << std::to_string( byte ) << ", ";
  }
  this->logger_->trace( fmt::runtime( "streamAudioFrame( generatorId = '{:s}', data = [{:s}], ({:d} bytes) )" ),
                        generatorId,
                        audioDataStream.str(),
                        data.size() );

  if( !this->audioMap_.contains( generatorId ) ) {
    this->logger_->error( fmt::runtime( "streamAudioFrame - Generator '{:s}' doesn't exist" ), generatorId );
  } else {
    for( BYTE byte : data ) {
      this->audioMap_[generatorId].audioData.push_back( byte );
    }
  }

  this->logger_->trace( fmt::runtime( "streamAudioFrame~" ) );
}

std::list< BYTE > int16ToLittleBytes( int16_t val ) {
  std::list< BYTE > ret;
  ret.push_back( val & 0xFF );
  ret.push_back( ( val >> 8 ) & 0xFF );
  return ret;
}

std::list< BYTE > uint16ToLittleBytes( uint16_t val ) {
  std::list< BYTE > ret;
  ret.push_back( val & 0xFF );
  ret.push_back( ( val >> 8 ) & 0xFF );
  return ret;
}

std::list< BYTE > int32ToLittleBytes( int32_t val ) {
  std::list< BYTE > ret;
  ret.push_back( val & 0xFF );
  ret.push_back( ( val >> 8 ) & 0xFF );
  ret.push_back( ( val >> 16 ) & 0xFF );
  ret.push_back( ( val >> 32 ) & 0xFF );
  return ret;
}

std::list< BYTE > uint32ToLittleBytes( uint32_t val ) {
  std::list< BYTE > ret;
  ret.push_back( val & 0xFF );
  ret.push_back( ( val >> 8 ) & 0xFF );
  ret.push_back( ( val >> 16 ) & 0xFF );
  ret.push_back( ( val >> 32 ) & 0xFF );
  return ret;
}

void RecordingServer::saveAudioGenerator( std::string const& generatorId ) {
  this->logger_->trace( fmt::runtime( "saveAudioGenerator( generatorId = '{:s}' )" ), generatorId );

  if( !this->audioMap_.contains( generatorId ) ) {
    this->logger_->error( fmt::runtime( "saveAudioGenerator - Generator '{:s}' doesn't exist" ), generatorId );
  } else {
    auto audioStructData = this->audioMap_[generatorId];
    FILE* wavFile = fopen( fmt::format( fmt::runtime( "{:s}.wav" ), generatorId ).c_str(), "wb" );
    if( !wavFile ) {
      this->logger_->error( fmt::runtime( "saveAudioGenerator - Generator '{:s}' couldn't be saved!" ), generatorId );
    } else {
      uint32_t dataBlockSize = audioStructData.audioData.size();
      uint32_t fmtBlockSize = 16;
      // "WAVE" + "fmt " + fmt size + fmt block + "data" + data size + data block
      uint32_t entireFileSize = 4 + 4 + 4 + fmtBlockSize + 4 + 4 + dataBlockSize;

      uint32_t byteRate = ( audioStructData.sampleRate * audioStructData.channels ) * ( audioStructData.bitsPerSample / 8 );
      uint16_t blockAlign = ( audioStructData.channels ) * ( audioStructData.bitsPerSample / 8 );

      fputs( "RIFF", wavFile );
      for( BYTE byte : uint32ToLittleBytes( entireFileSize ) ) {
        fputc( byte, wavFile );
      }
      fputs( "WAVE", wavFile );
      fputs( "fmt ", wavFile );
      for( BYTE byte : uint32ToLittleBytes( fmtBlockSize ) ) {
        fputc( byte, wavFile );
      }
      for( BYTE byte : uint16ToLittleBytes( static_cast< uint16_t >( audioStructData.type ) ) ) {
        fputc( byte, wavFile );
      }
      for( BYTE byte : uint16ToLittleBytes( audioStructData.channels ) ) {
        fputc( byte, wavFile );
      }
      for( BYTE byte : uint32ToLittleBytes( audioStructData.sampleRate ) ) {
        fputc( byte, wavFile );
      }
      for( BYTE byte : uint32ToLittleBytes( byteRate ) ) {
        fputc( byte, wavFile );
      }
      for( BYTE byte : uint16ToLittleBytes( blockAlign ) ) {
        fputc( byte, wavFile );
      }
      for( BYTE byte : uint16ToLittleBytes( audioStructData.bitsPerSample ) ) {
        fputc( byte, wavFile );
      }
      fputs( "data", wavFile );
      for( BYTE byte : uint32ToLittleBytes( dataBlockSize ) ) {
        fputc( byte, wavFile );
      }
      for( BYTE byte : audioStructData.audioData ) {
        fputc( byte, wavFile );
      }

      if( !fclose( wavFile ) ) {
        this->logger_->error( fmt::runtime( "saveAudioGenerator - file '{:s}.wav' couldn't be closed!" ), generatorId );
      }
    }
  }

  this->logger_->trace( fmt::runtime( "saveAudioGenerator~" ) );
}

void RecordingServer::printDebugInfo() {
  this->logger_->trace( fmt::runtime( "printDebugInfo" ) );

  this->logger_->info( fmt::runtime( "Audio streams:" ) );
  for( auto const& pair : this->audioMap_ ) {
    this->logger_->info( fmt::runtime( "- '{:s}':" ), pair.first );
    this->logger_->info( fmt::runtime( "  - type: {:d}" ), static_cast< uint16_t >( pair.second.type ) );
    this->logger_->info( fmt::runtime( "  - Channels: {:d}" ), pair.second.channels );
    this->logger_->info( fmt::runtime( "  - Sample rate: {:d}" ), pair.second.sampleRate );
    this->logger_->info( fmt::runtime( "  - Bits per sample: {:d}" ), pair.second.bitsPerSample );
    std::stringstream audioDataStream;
    for( BYTE byte : pair.second.audioData ) {
      audioDataStream << std::to_string( byte ) << ", ";
    }
    this->logger_->info( fmt::runtime( "  - Audio data: [{:s}] ({:d} bytes)" ), audioDataStream.str(), pair.second.audioData.size() );
  }

  this->logger_->trace( fmt::runtime( "printDebugInfo~" ) );
}

}  // namespace RecordingServer
}  // namespace SystemSimulator
}  // namespace SFG
