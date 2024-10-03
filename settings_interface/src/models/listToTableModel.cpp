#include "SFG/SystemSimulator/SettingsInterface/models/listToTableModel.h"

#include <SFG/SystemSimulator/Logger-Qt/qtFormatter.h>
#include <SFG/SystemSimulator/Logger/scopedLogger.h>
#include <algorithm>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

ListToTableModel::ListToTableModel( QObject *parent )
    : QAbstractTableModel( parent ), logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "ListToTableModel" ) ), model_( nullptr ) {
  this->logger_->trace( fmt::runtime( "ListToTableModel( parent: {:p} )" ), static_cast< void * >( parent ) );

  this->logger_->trace( fmt::runtime( "ListToTableModel()~" ) );
}

ListToTableModel::~ListToTableModel() {
  this->logger_->trace( fmt::runtime( "~ListToTableModel()" ) );

  this->logger_->trace( fmt::runtime( "~ListToTableModel()~" ) );
}

void ListToTableModel::setSourceModel( QAbstractListModel *model ) {
  this->logger_->trace( fmt::runtime( "setSourceModel( model: {:p} )" ), static_cast< void * >( model ) );

  if( this->model_ ) {
    this->disconnect( this->model_, nullptr, nullptr, nullptr );
  }
  this->model_ = model;
  this->beginResetModel();
  if( this->model_ ) {
    this->connect( this->model_,
                   &QAbstractListModel::dataChanged,
                   [this]( const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector< int > &roles = QVector< int >() ) {
                     emit this->dataChanged( topLeft, this->index( bottomRight.row(), columnCount() ) );
                   } );
    this->connect( this->model_, &QAbstractListModel::headerDataChanged, [this]( Qt::Orientation orientation, int first, int last ) {
      emit this->headerDataChanged( orientation, first, last );
    } );
  }
  this->endResetModel();

  this->logger_->trace( fmt::runtime( "setSourceModel()~" ) );
}

QHash< int, QByteArray > ListToTableModel::roleNames() const {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "roleNames()" ) ),
                                                      fmt::format( fmt::runtime( "roleNames()~" ) ) );
  if( !this->model_ ) {
    return QHash< int, QByteArray >();
  }
  return this->model_->roleNames();
}

int ListToTableModel::columnCount( QModelIndex const &parent ) const {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "columnCount( parent: {:qmi} )" ), parent ),
                                                      fmt::format( fmt::runtime( "columnCount()~" ) ) );
  if( !this->model_ ) {
    return 0;
  }

  if( parent.isValid() ) {
    return 0;
  }
  return this->roleNames().size();
}

int ListToTableModel::rowCount( QModelIndex const &parent ) const {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "rowCount( parent: {:qmi} )" ), parent ),
                                                      fmt::format( fmt::runtime( "rowCount()~" ) ) );
  if( !this->model_ ) {
    return 0;
  }

  if( parent.isValid() ) {
    return 0;
  }
  return this->model_->rowCount( parent );
}

Qt::ItemFlags ListToTableModel::flags( QModelIndex const &index ) const {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "flags( index: {:qmi} )" ), index ),
                                                      fmt::format( fmt::runtime( "flags()~" ) ) );
  if( !this->model_ ) {
    return Qt::ItemFlag::NoItemFlags;
  }

  if( !index.isValid() ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  if( index.column() < 0 ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  if( index.column() >= columnCount() ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  if( index.row() < 0 ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  if( index.row() >= rowCount() ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  return this->model_->flags( this->model_->index( index.row() ) );
}

QVariant ListToTableModel::data( QModelIndex const &index, int role ) const {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "data( index: {:qmi}, role: {:d} )" ), index, role ),
                                                      fmt::format( fmt::runtime( "data()~" ) ) );
  if( !this->model_ ) {
    return QVariant();
  }

  if( !index.isValid() ) {
    return QVariant();
  }
  if( index.column() < 0 ) {
    return QVariant();
  }
  if( index.column() >= columnCount() ) {
    return QVariant();
  }
  if( index.row() < 0 ) {
    return QVariant();
  }
  if( index.row() >= rowCount() ) {
    return QVariant();
  }
  return this->model_->data( this->model_->index( index.row() ), Qt::ItemDataRole::UserRole + 1 + index.column() );
}

QVariant ListToTableModel::headerData( int section, Qt::Orientation orientation, int role ) const {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "headerData( section: {:d}, orientation: {:d}, role: {:d} )" ),
                                                                   section,
                                                                   static_cast< int >( orientation ),
                                                                   role ),
                                                      fmt::format( fmt::runtime( "headerData()~" ) ) );
  if( !this->model_ ) {
    return QVariant();
  }
  if( orientation == Qt::Orientation::Horizontal && section < 0 ) {
    return QVariant();
  }
  if( orientation == Qt::Orientation::Horizontal && section >= columnCount() ) {
    return QVariant();
  }
  if( orientation == Qt::Orientation::Vertical && section < 0 ) {
    return QVariant();
  }
  if( orientation == Qt::Orientation::Vertical && section >= rowCount() ) {
    return QVariant();
  }
  if( orientation == Qt::Orientation::Vertical ) {
    // row number
    return QVariant::fromValue( section );
  }
  return this->model_->headerData( 0, Qt::Orientation::Vertical, Qt::ItemDataRole::UserRole + 1 + section );
}

bool ListToTableModel::setData( QModelIndex const &index, QVariant const &value, int role ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "setData( index: {:qmi}, value: '{:qs}', role: {:d} )" ),
                                                                   index,
                                                                   value.toString(),
                                                                   role ),
                                                      fmt::format( fmt::runtime( "setData()~" ) ) );
  if( !this->model_ ) {
    return false;
  }

  if( !index.isValid() ) {
    return false;
  }
  if( index.column() < 0 ) {
    return false;
  }
  if( index.column() >= columnCount() ) {
    return false;
  }
  if( index.row() < 0 ) {
    return false;
  }
  if( index.row() >= rowCount() ) {
    return false;
  }
  return this->model_->setData( this->model_->index( index.row() ), value, Qt::ItemDataRole::UserRole + 1 + index.column() );
}

bool ListToTableModel::setHeaderData( int section, Qt::Orientation orientation, QVariant const &value, int role ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime(
                                                                       "setHeaderData( section: {:d}, orientation: {:d}, value: '{:qs}', role: {:d} )" ),
                                                                   section,
                                                                   static_cast< int >( orientation ),
                                                                   value.toString(),
                                                                   role ),
                                                      fmt::format( fmt::runtime( "setHeaderData()~" ) ) );
  if( !this->model_ ) {
    return false;
  }

  // fixme: who knows
  return this->model_->setHeaderData( section, orientation, value, role );
}

bool ListToTableModel::insertColumns( int column, int count, QModelIndex const &parent ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "insertColumns( column: {:d}, count: {:d}, parent: {:qmi} )" ),
                                                                   column,
                                                                   count,
                                                                   parent ),
                                                      fmt::format( fmt::runtime( "insertColumns()~" ) ) );
  if( !this->model_ ) {
    return false;
  }
  // We can't add more columns
  return false;
}

bool ListToTableModel::insertRows( int row, int count, QModelIndex const &parent ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "insertRows( row: {:d}, count: {:d}, parent: {:qmi} )" ), row, count, parent ),
                                                      fmt::format( fmt::runtime( "insertRows()~" ) ) );
  if( !this->model_ ) {
    return false;
  }
  return this->model_->insertRows( row, count, parent );
}

bool ListToTableModel::removeColumns( int column, int count, QModelIndex const &parent ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "removeColumns( column: {:d}, count: {:d}, parent: {:qmi} )" ),
                                                                   column,
                                                                   count,
                                                                   parent ),
                                                      fmt::format( fmt::runtime( "removeColumns()~" ) ) );
  if( !this->model_ ) {
    return false;
  }
  // We can't remove columns
  return false;
}

bool ListToTableModel::removeRows( int row, int count, QModelIndex const &parent ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "removeRows( row: {:d}, count: {:d}, parent: {:qmi} )" ), row, count, parent ),
                                                      fmt::format( fmt::runtime( "removeRows()~" ) ) );
  if( !this->model_ ) {
    return false;
  }

  return this->model_->removeRows( row, count, parent );
}

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG
