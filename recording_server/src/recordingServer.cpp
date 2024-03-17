#include "SFG/SystemSimulator/RecordingServer/recordingServer.h"

#include <fstream>

namespace SFG {
namespace SystemSimulator {
namespace RecordingServer {

template < typename T >
void writeLittleEndian( T value, std::fstream& file ) {
  for( int i = 0; i < sizeof( T ); i++ ) {
    file << static_cast< char >( ( value >> ( 8 * i ) ) & 0xFF );
  }
}

template < typename T >
T readLittleEndian( std::fstream& file ) {
  T ret;
  for( int i = 0; i < sizeof( T ); i++ ) {
    char value;
    file >> value;
    ret += static_cast< T >( value << ( 8 * i ) );
  }
  return ret;
}

RecordingServer::RecordingServer()
    : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "RecordingServer" ) ),
      config_( "config/recording_server.ini" ),
      exportPath_( this->config_.get< std::string >( "Export", "Path" ) ) {
  this->logger_->trace( fmt::runtime( "RecordingServer" ) );

  this->logger_->trace( fmt::runtime( "RecordingServer~" ) );
}

RecordingServer::~RecordingServer() {
  this->logger_->trace( fmt::runtime( "~RecordingServer" ) );

  this->logger_->trace( fmt::runtime( "~RecordingServer~" ) );
}

void RecordingServer::setupAudioGenerator( std::string const& generatorId, uint16_t channels, uint32_t sampleRate, uint16_t bitsPerSample ) {
  this->logger_->trace( fmt::runtime( "setupAudioGenerator( generatorId = '{:s}', channels: {:d}, sampleRate: {:d}, bitsPerSample: {:d} )" ),
                        generatorId,
                        channels,
                        sampleRate,
                        bitsPerSample );

  std::fstream wavFile( fmt::format( fmt::runtime( "{:s}/export_{:s}.wav" ), this->exportPath_, generatorId ),
                        std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );
  if( !wavFile.is_open() ) {
    this->logger_->error( fmt::runtime( "setupAudioGenerator - file 'export_{:s}.wav' couldn't be opened!" ), generatorId );
  } else {
    // idx: 0
    wavFile << "RIFF";
    // idx: 4
    writeLittleEndian< uint32_t >( 0, wavFile );
    // idx: 8
    wavFile << "WAVE";
    // idx: 12
    wavFile << "fmt ";
    // idx: 16
    writeLittleEndian< uint32_t >( sizeof( uint16_t ) + sizeof( uint16_t ) + sizeof( uint32_t ) + sizeof( uint32_t ) + sizeof( uint16_t ) + sizeof( uint16_t ),
                                   wavFile );  // "fmt " block size
    // idx: 20
    writeLittleEndian< uint16_t >( 1, wavFile );  // 1 = pcm
    // idx: 22
    writeLittleEndian< uint16_t >( channels, wavFile );
    // idx: 24
    writeLittleEndian< uint32_t >( sampleRate, wavFile );
    // idx: 28
    writeLittleEndian< uint32_t >( sampleRate * channels * ( bitsPerSample / 8 ), wavFile );  // byte rate
    // idx: 32
    writeLittleEndian< uint16_t >( channels * ( bitsPerSample / 8 ), wavFile );  // block align
    // idx: 34
    writeLittleEndian< uint16_t >( bitsPerSample, wavFile );
    // idx: 36
    wavFile << "data";
    // idx: 40
    writeLittleEndian< uint32_t >( 0, wavFile );

    wavFile.close();
  }

  this->logger_->trace( fmt::runtime( "setupAudioGenerator~" ) );
}

void RecordingServer::streamAudioFrame( std::string const& generatorId, std::list< char > data ) {
  // std::stringstream audioDataStream;
  // for( char byte : data ) {
  //   audioDataStream << std::to_string( byte ) << ", ";
  // }
  this->logger_->trace( fmt::runtime( "streamAudioFrame( generatorId = '{:s}', data = {:d} bytes )" ),
                        generatorId,
                        /* audioDataStream.str(), */
                        data.size() );

  std::fstream wavFile( fmt::format( fmt::runtime( "{:s}/export_{:s}.wav" ), this->exportPath_, generatorId ),
                        std::ios_base::in | std::ios_base::out | std::ios_base::binary );
  if( !wavFile.is_open() ) {
    this->logger_->error( fmt::runtime( "streamAudioFrame - file 'export_{:s}.wav' couldn't be opened!" ), generatorId );
  } else {
    // RIFF chunk
    wavFile.seekg( 4, std::ios_base::beg );
    uint32_t fileChunkSize = readLittleEndian< uint32_t >( wavFile );
    wavFile.seekp( 4, std::ios_base::beg );
    writeLittleEndian< uint32_t >( fileChunkSize + data.size(), wavFile );
    this->logger_->trace( fmt::runtime( "streamAudioFrame - changing file size from {:d} to {:d}" ), fileChunkSize, fileChunkSize + data.size() );

    // data chunk
    wavFile.seekg( 40, std::ios_base::beg );
    uint32_t dataChunkSize = readLittleEndian< uint32_t >( wavFile );
    wavFile.seekp( 40, std::ios_base::beg );
    writeLittleEndian< uint32_t >( dataChunkSize + data.size(), wavFile );
    this->logger_->trace( fmt::runtime( "streamAudioFrame - changing data size from {:d} to {:d}" ), dataChunkSize, dataChunkSize + data.size() );

    wavFile.seekg( 0, std::ios_base::end );
    wavFile.seekp( 0, std::ios_base::end );
    for( char byte : data ) {
      wavFile << byte;
    }

    wavFile.close();
  }

  this->logger_->trace( fmt::runtime( "streamAudioFrame~" ) );
}

}  // namespace RecordingServer
}  // namespace SystemSimulator
}  // namespace SFG
