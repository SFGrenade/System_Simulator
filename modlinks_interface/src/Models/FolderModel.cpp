#include "SFG/SystemSimulator/LuigiInterface/Models/FolderModel.h"

// Project includes
#include <SFG/SystemSimulator/Logger/scopedLogger.h>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

FolderModel::FolderModel() : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "FolderModel" ) ) {
  this->logger_->trace( fmt::runtime( "FolderModel()" ) );

  uiToAbstract_.insert( { uiModel_, this } );

  this->logger_->trace( fmt::runtime( "FolderModel()~" ) );
}

FolderModel::~FolderModel() {
  this->logger_->trace( fmt::runtime( "~FolderModel()" ) );

  this->logger_->trace( fmt::runtime( "~FolderModel()~" ) );
}

AbstractModel::index_t FolderModel::columnCount() const {
  return 3;
}

uiTableValueType FolderModel::columnType( AbstractModel::index_t column ) const {
  switch( column ) {
    case 0:
      // Name
      // fallthrough
    case 1:
      // Permissions/Status
      return uiTableValueTypeString;
    case 2:
      // Size
      return uiTableValueTypeInt;
    default:
      return uiTableValueTypeString;
  }
}

AbstractModel::index_t FolderModel::rowCount() const {
  return AbstractModel::index_t( dataList_.size() );
}

uiTableValue* FolderModel::getCell( AbstractModel::index_t row, AbstractModel::index_t column ) const {
  if( ( 0 <= row ) && ( row < rowCount() ) ) {
    FolderModel::Data const& item = dataList_[row];
    if( ( column < 0 ) || ( columnCount() <= column ) ) {
      return nullptr;
    }
    if( column == 0 ) {
      return uiNewTableValueString( item.path.filename().string().c_str() );
    } else if( column == 1 ) {
      return uiNewTableValueString(
          fmt::format( fmt::runtime( "{:x} {:x}" ), static_cast< uintmax_t >( item.status.type() ), static_cast< uintmax_t >( item.status.permissions() ) )
              .c_str() );
    } else {
      return uiNewTableValueInt( item.size );
    }
  }
  return nullptr;
}

void FolderModel::setRootFolder( std::filesystem::path const& root ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "setRootFolder( root: {:?} )" ), root.string() ),
                                                      fmt::format( fmt::runtime( "setRootFolder()~" ) ) );

  std::filesystem::path canonicalRoot = std::filesystem::canonical( root );
  if( std::filesystem::exists( canonicalRoot ) && std::filesystem::is_directory( canonicalRoot ) ) {
    root_ = canonicalRoot;

    refresh();
  }
}

void FolderModel::refresh() {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_, fmt::format( fmt::runtime( "refresh()" ) ), fmt::format( fmt::runtime( "refresh()~" ) ) );

  std::vector< FolderModel::Data > tmpEntries;
  for( auto const& dir_entry : std::filesystem::directory_iterator( root_ ) ) {
    FolderModel::Data tmp;
    tmp.path = dir_entry.path();
    tmp.status = dir_entry.status();
    tmp.size = dir_entry.file_size();
    tmpEntries.push_back( tmp );
  }
  std::sort( tmpEntries.begin(), tmpEntries.end(), []( FolderModel::Data const& a, FolderModel::Data const& b ) {
    if( ( a.status.type() == std::filesystem::file_type::directory ) && ( b.status.type() != std::filesystem::file_type::directory ) )
      return true;
    if( a.path.filename().string() < b.path.filename().string() )
      return true;
    return false;
  } );

  size_t row;

  // check for removed items
  row = 0;
  for( auto iter = dataList_.begin(); iter != dataList_.end(); ) {
    bool isStillInFolder = std::any_of( tmpEntries.begin(), tmpEntries.end(), [iter]( FolderModel::Data const& item ) { return iter->path == item.path; } );
    if( !isStillInFolder ) {
      iter = dataList_.erase( iter );
      uiTableModelRowDeleted( uiModel_, row );
      continue;
    }
    iter++;
    row++;
  }
  // check for added items
  row = 0;
  for( auto iter = tmpEntries.begin(); iter != tmpEntries.end(); iter++, row++ ) {
    bool isAlreadyInList = std::any_of( dataList_.begin(), dataList_.end(), [iter]( FolderModel::Data const& item ) { return iter->path == item.path; } );
    if( !isAlreadyInList ) {
      dataList_.push_back( *iter );
      uiTableModelRowInserted( uiModel_, dataList_.size() - 1 );
    }
  }
  // check for changed items
  row = 0;
  for( auto iter = dataList_.begin(); iter != dataList_.end(); iter++, row++ ) {
    bool changedItem = std::any_of( tmpEntries.begin(), tmpEntries.end(), [iter]( FolderModel::Data const& item ) {
      return ( iter->path == item.path ) && ( ( iter->status != item.status ) || ( iter->size != item.size ) );
    } );
    if( changedItem ) {
      uiTableModelRowChanged( uiModel_, row );
    }
  }
}

}  // namespace Models
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
