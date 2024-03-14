#include "SFG/SystemSimulator/SettingsInterface/models/userModel.h"

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

UserModel::UserModel( QObject *parent ) : QAbstractListModel( parent ), logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "UserModel" ) ) {
  this->logger_->trace( fmt::runtime( "UserModel( parent: {:p} )" ), static_cast< void * >( parent ) );

  this->logger_->trace( fmt::runtime( "UserModel()~" ) );
}

UserModel::~UserModel() {
  this->logger_->trace( fmt::runtime( "~UserModel()" ) );

  this->logger_->trace( fmt::runtime( "~UserModel()~" ) );
}

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG
