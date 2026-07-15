#include "SFG/SystemSimulator/LuigiInterface/Models/ModLinksModel.h"

// Project includes
#include <SFG/SystemSimulator/Logger/scopedLogger.h>
#include <SFG/SystemSimulator/LuigiInterface/FileDownloader.h>

// Library includes
#include <rfl/xml.hpp>

// C++ includes
#include <stdexcept>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

std::string const ModLinksModel::SERVER_ADDRESS = "https://raw.githubusercontent.com";
std::string const ModLinksModel::SERVER_PATH = "/hk-modding/modlinks/refs/heads/main/ModLinks.xml";

ModLinksModel::ModLinksModel() : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "ModLinksModel" ) ) {
  logger_->trace( fmt::runtime( "ModLinksModel()" ) );

  uiToAbstract_.insert( { uiModel_, this } );

  logger_->trace( fmt::runtime( "ModLinksModel()~" ) );
}

ModLinksModel::~ModLinksModel() {
  logger_->trace( fmt::runtime( "~ModLinksModel()" ) );

  logger_->trace( fmt::runtime( "~ModLinksModel()~" ) );
}

AbstractModel::index_t ModLinksModel::columnCount() const {
  return 7;
}

uiTableValueType ModLinksModel::columnType( AbstractModel::index_t column ) const {
  switch( column ) {
    case 0:
      // Name
      return uiTableValueTypeString;
    case 1:
      // Description
      return uiTableValueTypeString;
    case 2:
      // Version
      return uiTableValueTypeString;
    case 3:
      // Dependencies
      return uiTableValueTypeString;
    case 4:
      // Integrations
      return uiTableValueTypeString;
    case 5:
      // Tags
      return uiTableValueTypeString;
    case 6:
      // Authors
      return uiTableValueTypeString;
    default:
      return uiTableValueTypeString;
  }
}

AbstractModel::index_t ModLinksModel::rowCount() const {
  return dataList_.size();
}

uiTableValue* ModLinksModel::getCell( AbstractModel::index_t row, AbstractModel::index_t column ) const {
  if( ( 0 <= row ) && ( row < rowCount() ) ) {
    ModLinksModel::Data const& item = dataList_[row];
    if( ( column < 0 ) || ( columnCount() <= column ) ) {
      return nullptr;
    }
    std::string ret;
    if( column == 0 ) {
      if( item.DisplayName.has_value() )
        return uiNewTableValueString( item.DisplayName.value().c_str() );
      return uiNewTableValueString( item.Name.value().c_str() );
    } else if( column == 1 ) {
      return uiNewTableValueString( item.Description.c_str() );
    } else if( column == 2 ) {
      return uiNewTableValueString( item.Version.value().c_str() );
    } else if( column == 3 ) {
      return uiNewTableValueString( fmt::format( fmt::runtime( "{}" ), fmt::join( item.Dependencies.Dependency, ", " ) ).c_str() );
    } else if( column == 4 ) {
      std::string tmp = item.Integrations.has_value() ? fmt::format( fmt::runtime( "{}" ), fmt::join( item.Integrations.value().Integration, ", " ) ) : "";
      return uiNewTableValueString( tmp.c_str() );
    } else if( column == 5 ) {
      std::string tmp = item.Tags.has_value() ? fmt::format( fmt::runtime( "{}" ), fmt::join( item.Tags.value().Tag, ", " ) ) : "";
      return uiNewTableValueString( tmp.c_str() );
    } else if( column == 6 ) {
      std::string tmp = item.Authors.has_value() ? fmt::format( fmt::runtime( "{}" ), fmt::join( item.Authors.value().Author, ", " ) ) : "";
      return uiNewTableValueString( tmp.c_str() );
    }
  }
  return nullptr;
}

void ModLinksModel::setupFromOnline() {
  Logger::ScopedLogger _( logger_, fmt::format( fmt::runtime( "setupFromOnline()" ) ), fmt::format( fmt::runtime( "setupFromOnline()~" ) ) );

  FileDownloader fileDownloader;
  std::optional< std::ifstream > file = fileDownloader.downloadFile( SERVER_ADDRESS, SERVER_PATH, std::filesystem::temp_directory_path() / "ModLinks.xml" );
  if( !file.has_value() ) {
    return setupFromCache();
  }

  try {
    file.value().seekg( 0, std::ios::beg );
    auto modLinks = rfl::xml::read< mm::ModLinks >( file.value() ).value();

    logger_->debug( fmt::runtime( "setupFromOnline - {:d} Manifests" ), modLinks.Manifest.size() );

    integrateNewList( modLinks.Manifest );
  } catch( std::exception& e ) {
    logger_->error( fmt::runtime( "setupFromOnline - Error when deserializing: {:s}" ), e.what() );
  }
}

void ModLinksModel::setupFromCache() {
  Logger::ScopedLogger _( logger_, fmt::format( fmt::runtime( "setupFromCache()" ) ), fmt::format( fmt::runtime( "setupFromCache()~" ) ) );

  std::vector< mm::Manifest > tmp;
  tmp.push_back(mm::Manifest {
    .Name = R"(Double Enemies)",
    .Description = R"(Duplicates most enemies in the game, and shares hp between duplicate bosses.)",
    .Version = R"(1.0.0.0)",
    .Link = mm::LinkBase {
      .xml_content = R"(https://github.com/Genio250/Double-Enemies/releases/download/v1.0/Double.Enemies.zip)",
      .SHA256 = R"(771e8cb3717f69928b8dc8d62c6cea29cb7374ed7f4c101d7562aaabb092ce7d)",
    },
    .Dependencies = mm::Dependencies {
      .Dependency = {
        R"(Satchel)",
        R"(Invincibility Monitor)",
        R"(DoubleRadiance)",
      }
    },
    .Repository = R"(https://github.com/Genio250/Double-Enemies)",
    .Issues = R"(https://github.com/Genio250/Double-Enemies/issues)",
    .Authors = mm::AuthorsBase {
      .Author = {
        R"(Genio250)",
      }
    },
  } );
  tmp.push_back(mm::Manifest {
    .Name = R"(Pale Court)",
    .Description = R"(Challenge Hallownest's mightiest champions in grand combat!
  come your opponents with powerful new charms!
  over new secrets and stories!
  with an incredible new soundtrack!)",
    .Version = R"(1.1.1.7)",
    .Links = mm::LinksBase {
      .Linux = mm::SingleLinkType {
        .xml_content = R"(https://github.com/PaleCourt/PaleCourt/releases/download/1.1.1.7/PaleCourt-Lin.zip)",
        .SHA256 = R"(32328DA0903CDE25173DC4C885B068A1EBC91329506D63BE863A24EB35E72945)",
      },
      .Mac = mm::SingleLinkType {
        .xml_content = R"(https://github.com/PaleCourt/PaleCourt/releases/download/1.1.1.7/PaleCourt-Mac.zip)",
        .SHA256 = R"(57B81A833E2EEA8C6D63AF50144A71D2F2A9FC97423F5CCDA4B513EC49F112E0)",
      },
      .Windows = mm::SingleLinkType {
        .xml_content = R"(https://github.com/PaleCourt/PaleCourt/releases/download/1.1.1.7/PaleCourt-Win.zip)",
        .SHA256 = R"(1646CE8DB5B16A49A04B7DF13D3B15BBCFD8034809EB8974A2455D6BA1ED1855)",
      },
    },
    .Dependencies = mm::Dependencies {
      .Dependency = {
        R"(FrogCore)",
        R"(SFCore)",
        R"(Vasi)",
      }
    },
    .Repository = R"(https://github.com/PaleCourt/PaleCourt)",
    .Integrations = mm::IntegrationsBase {
      .Integration = {
        R"(GodSeekerPlus)",
        R"(Enemy HP Bar)",
      }
    },
    .Tags = mm::TagsBase {
      .Tag = {
        mm::Tag::Boss,
        mm::Tag::Expansion,
        mm::Tag::Gameplay,
      }
    },
    .Authors = mm::AuthorsBase {
      .Author = {
        R"(MEBI)",
        R"(Zaliant)",
        R"(Saleh)",
        R"(HooKnows)",
        R"(RiverRobot)",
        R"(RedFrog)",
        R"(SFGrenade)",
        R"(Clazex)",
        R"(Jngo102)",
        R"(TheGreatGallus)",
        R"(56)",
        R"(Link459)",
        R"(Chaktis)",
        R"(KitsuneMedia)",
        R"(FoldingPapers)",
        R"(Gauthier)",
        R"(CarsonComposes)",
        R"(MAT)",
        R"(SovereignElise)",
        R"(Rotten Legacy)",
        R"(mossbag)",
        R"(Sarart)",
        R"(JoSeBach)",
        R"(RocketFire20)",
        R"(Manno Stone)",
        R"(HelenSB)",
        R"(Azerod)",
        R"(Whisky)",
        R"(Croissant)",
        R"(HuntHussle)",
        R"(General Milky)",
        R"(Knightmere)",
        R"(Erie)",
        R"(Spoonsei)",
        R"(Pan)",
        R"(DwarfWoot)",
        R"(Schy)",
        R"(Alprechim)",
        R"(ygsbzr)",
        R"(Yisrael)",
        R"(KamaKiller)",
        R"(Piquant Trobbio)",
        R"(WaxOcelot)",
        R"(Plush)",
        R"(ShadicD20)",
        R"(Chrome)",
        R"(Exempt-Medic)",
        R"(CrankyTemplar)",
        R"(MyPetCactus)",
        R"(Mulhima)",
        R"(Frunobulaxian)",
        R"(AshtinPeaks)",
        R"(PizzaBox)",
        R"(Bluevooid)",
        R"(TheBlueVirus)",
        R"(Dark_Prelate)",
        R"(Hotspring)",
        R"(Lethal_Vessel)",
        R"(Risto The Chicken)",
      }
    },
  } );
  integrateNewList( tmp );
}

void ModLinksModel::integrateNewList( std::vector< ModLinksModel::Data >& dataList ) {
  Logger::ScopedLogger _( logger_,
                          fmt::format( fmt::runtime( "integrateNewList( dataList: [{:d} items] )" ), dataList.size() ),
                          fmt::format( fmt::runtime( "integrateNewList()~" ) ) );

  std::sort( dataList.begin(), dataList.end(), []( ModLinksModel::Data const& a, ModLinksModel::Data const& b ) {
    std::string aName = a.Name.value();
    std::string bName = b.Name.value();
    std::transform( aName.begin(), aName.end(), aName.begin(), []( unsigned char c ) { return std::tolower( c ); } );
    std::transform( bName.begin(), bName.end(), bName.begin(), []( unsigned char c ) { return std::tolower( c ); } );
    return aName < bName;
  } );

  size_t row;

  // check for removed items
  row = 0;
  for( auto iter = dataList_.begin(); iter != dataList_.end(); ) {
    bool isStillInFolder = std::any_of( dataList.begin(), dataList.end(), [iter]( ModLinksModel::Data const& item ) { return iter->Name == item.Name; } );
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
  for( auto iter = dataList.begin(); iter != dataList.end(); iter++, row++ ) {
    bool isAlreadyInList = std::any_of( dataList_.begin(), dataList_.end(), [iter]( ModLinksModel::Data const& item ) { return iter->Name == item.Name; } );
    if( !isAlreadyInList ) {
      dataList_.push_back( *iter );
      uiTableModelRowInserted( uiModel_, dataList_.size() - 1 );
    }
  }
  // check for changed items
  row = 0;
  for( auto iter = dataList_.begin(); iter != dataList_.end(); iter++, row++ ) {
    bool changedItem = std::any_of( dataList.begin(), dataList.end(), [iter]( ModLinksModel::Data const& item ) {
      return ( iter->Name == item.Name ) && isDifferent( *iter, item );
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

auto fmt::formatter< mm::Tag >::format( mm::Tag in, format_context& ctx ) const -> format_context::iterator {
  std::string ret = "##-UNKNOWN-##";
  switch( in ) {
    case mm::Tag::Accessibility:
      ret = "Accessibility";
      break;
    case mm::Tag::Boss:
      ret = "Boss";
      break;
    case mm::Tag::Charm:
      ret = "Charm";
      break;
    case mm::Tag::Cosmetic:
      ret = "Cosmetic";
      break;
    case mm::Tag::Expansion:
      ret = "Expansion";
      break;
    case mm::Tag::Gameplay:
      ret = "Gameplay";
      break;
    case mm::Tag::Joke:
      ret = "Joke";
      break;
    case mm::Tag::Library:
      ret = "Library";
      break;
    case mm::Tag::Optimization:
      ret = "Optimization";
      break;
    case mm::Tag::Utility:
      ret = "Utility";
      break;
  }
  return formatter< std::string >::format( ret, ctx );
}

auto fmt::formatter< mm::SingleLinkType >::format( mm::SingleLinkType in, format_context& ctx ) const -> format_context::iterator {
  std::string ret = fmt::format( fmt::runtime( "{:s} ({:s})" ), in.xml_content.value(), in.SHA256.value().value() );
  return formatter< std::string >::format( ret, ctx );
}

auto fmt::formatter< mm::LinksType >::format( mm::LinksType in, format_context& ctx ) const -> format_context::iterator {
  std::string ret = fmt::format( fmt::runtime( "Linux: {}, Mac: {}, Windows: {}" ), in.Linux, in.Mac, in.Windows );
  return formatter< std::string >::format( ret, ctx );
}

auto fmt::formatter< mm::NameStringType >::format( mm::NameStringType in, format_context& ctx ) const -> format_context::iterator {
  std::string ret = fmt::format( fmt::runtime( "{}" ), in.value() );
  return formatter< std::string >::format( ret, ctx );
}

bool isDifferent( mm::Manifest const& a, mm::Manifest const& b ) {
  if( a.Name != b.Name ) {
    return true;
  }
  if( a.DisplayName != b.DisplayName ) {
    return true;
  }
  if( a.Description != b.Description ) {
    return true;
  }
  if( a.Version != b.Version ) {
    return true;
  }
  if( a.Links.has_value() != b.Links.has_value() ) {
    return true;
  } else if( a.Links.has_value() && b.Links.has_value() ) {
    if( a.Links.value().Linux.xml_content != b.Links.value().Linux.xml_content ) {
      return true;
    }
    if( a.Links.value().Linux.SHA256.value() != b.Links.value().Linux.SHA256.value() ) {
      return true;
    }
    if( a.Links.value().Mac.xml_content != b.Links.value().Mac.xml_content ) {
      return true;
    }
    if( a.Links.value().Mac.SHA256.value() != b.Links.value().Mac.SHA256.value() ) {
      return true;
    }
    if( a.Links.value().Windows.xml_content != b.Links.value().Windows.xml_content ) {
      return true;
    }
    if( a.Links.value().Windows.SHA256.value() != b.Links.value().Windows.SHA256.value() ) {
      return true;
    }
  }
  if( a.Link.has_value() != b.Link.has_value() ) {
    return true;
  } else if( a.Link.has_value() && b.Link.has_value() ) {
    if( a.Link.value().xml_content != b.Link.value().xml_content ) {
      return true;
    }
    if( a.Link.value().SHA256.value() != b.Link.value().SHA256.value() ) {
      return true;
    }
  }
  if( a.Dependencies.Dependency != b.Dependencies.Dependency ) {
    return true;
  }
  if( a.Repository != b.Repository ) {
    return true;
  }
  if( a.Issues != b.Issues ) {
    return true;
  }
  if( a.Integrations.has_value() != b.Integrations.has_value() ) {
    return true;
  } else if( a.Integrations.has_value() && b.Integrations.has_value() ) {
    if( a.Integrations.value().Integration != b.Integrations.value().Integration ) {
      return true;
    }
  }
  if( a.Tags.has_value() != b.Tags.has_value() ) {
    return true;
  } else if( a.Tags.has_value() && b.Tags.has_value() ) {
    if( a.Tags.value().Tag != b.Tags.value().Tag ) {
      return true;
    }
  }
  if( a.Authors.has_value() != b.Authors.has_value() ) {
    return true;
  } else if( a.Authors.has_value() && b.Authors.has_value() ) {
    if( a.Authors.value().Author != b.Authors.value().Author ) {
      return true;
    }
  }
  return false;
}
