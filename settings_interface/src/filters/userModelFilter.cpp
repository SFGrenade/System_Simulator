#include "SFG/SystemSimulator/SettingsInterface/filters/userModelFilter.h"

#include <SFG/SystemSimulator/Logger-Qt/qtFormatter.h>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

UserModelFilter::UserModelFilter( QObject *parent )
    : QAbstractListModel( parent ), logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "UserModelFilter" ) ) {
  this->logger_->trace( fmt::runtime( "UserModelFilter( parent: {:p} )" ), static_cast< void * >( parent ) );

  this->logger_->trace( fmt::runtime( "UserModelFilter()~" ) );
}

UserModelFilter::~UserModelFilter() {
  this->logger_->trace( fmt::runtime( "~UserModelFilter()" ) );

  this->logger_->trace( fmt::runtime( "~UserModelFilter()~" ) );
}

bool UserModelFilter::lessThan( QModelIndex const &sourceIndexLeft, QModelIndex const &sourceIndexRight ) const {
  this->logger_->trace( fmt::runtime( "lessThan( sourceIndexLeft: {:qmi}, sourceIndexRight: {:qmi} )" ), sourceIndexLeft, sourceIndexRight );

  QVariant leftData = sourceModel()->data( sourceIndexLeft );
  QVariant rightData = sourceModel()->data( sourceIndexRight );
  this->logger_->trace( fmt::runtime( "lessThan - leftData: '{:qs}'" ), leftData.toString() );
  this->logger_->trace( fmt::runtime( "lessThan - rightData: '{:qs}'" ), rightData.toString() );

  this->logger_->trace( fmt::runtime( "lessThan()~" ) );
  return false;
}

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG
