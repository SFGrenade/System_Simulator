#include "SFG/SystemSimulator/LuigiInterface/Models/ModLinksModel.h"

// Project includes
#include <SFG/SystemSimulator/Logger/scopedLogger.h>
#include <SFG/SystemSimulator/LuigiInterface/FileDownloader.h>

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
      return uiNewTableValueString( item.displayName.c_str() );
    } else if( column == 1 ) {
      return uiNewTableValueString( item.description.c_str() );
    } else if( column == 2 ) {
      return uiNewTableValueString( item.version.toString().c_str() );
    } else if( column == 3 ) {
      return uiNewTableValueString( fmt::format( fmt::runtime( "{}" ), fmt::join( item.dependencies, ", " ) ).c_str() );
    } else if( column == 4 ) {
      return uiNewTableValueString( fmt::format( fmt::runtime( "{}" ), fmt::join( item.integrations, ", " ) ).c_str() );
    } else if( column == 5 ) {
      return uiNewTableValueString( fmt::format( fmt::runtime( "{}" ), fmt::join( item.tags, ", " ) ).c_str() );
    } else if( column == 6 ) {
      return uiNewTableValueString( fmt::format( fmt::runtime( "{}" ), fmt::join( item.authors, ", " ) ).c_str() );
    }
  }
  return nullptr;
}

void ModLinksModel::setupFromOnline() {
  Logger::ScopedLogger _( logger_, fmt::format( fmt::runtime( "setupFromOnline()" ) ), fmt::format( fmt::runtime( "setupFromOnline()~" ) ) );

  std::optional< std::ifstream > file = FileDownloader::downloadFile( SERVER_ADDRESS, SERVER_PATH, std::filesystem::temp_directory_path() / "ModLinks.xml" );
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

void ModLinksModel::integrateNewList( std::vector< mm::Manifest >& manifestList ) {
  Logger::ScopedLogger _( logger_,
                          fmt::format( fmt::runtime( "integrateNewList( manifestList: [{:d} items] )" ), manifestList.size() ),
                          fmt::format( fmt::runtime( "integrateNewList()~" ) ) );

  std::sort( manifestList.begin(), manifestList.end(), []( mm::Manifest const& a, mm::Manifest const& b ) {
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
    bool isStillInFolder = std::any_of( manifestList.begin(), manifestList.end(), [iter]( mm::Manifest const& item ) { return iter->name == item.Name; } );
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
  for( auto iter = manifestList.begin(); iter != manifestList.end(); iter++, row++ ) {
    bool isAlreadyInList = std::any_of( dataList_.begin(), dataList_.end(), [iter]( ModLinksModel::Data const& item ) { return iter->Name == item.name; } );
    if( !isAlreadyInList ) {
      // todo: fixme: actually insertion at the correct spot
      ModLinksModel::Data newData = fromXml( *iter );
      dataList_.push_back( newData );
      uiTableModelRowInserted( uiModel_, dataList_.size() - 1 );
    }
  }
  // check for changed items
  row = 0;
  for( auto iter = dataList_.begin(); iter != dataList_.end(); iter++, row++ ) {
    bool changedItem = std::any_of( manifestList.begin(), manifestList.end(), [iter]( mm::Manifest const& item ) {
      return ( iter->name == item.Name ) && isDifferent( *iter, item );
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

SFG::SystemSimulator::LuigiInterface::Models::ModLinksModel::Data fromXml( mm::Manifest const& manifest ) {
  SFG::SystemSimulator::LuigiInterface::Models::ModLinksModel::Data ret;
  ret.name = manifest.Name.value();
  if( manifest.DisplayName.has_value() ) {
    ret.displayName = manifest.DisplayName.value();
  } else {
    ret.displayName = ret.name;
  }
  ret.description = manifest.Description;
  ret.version = SFG::SystemSimulator::LuigiInterface::Types::Version::fromString( manifest.Version.value() );
  if( manifest.Links.has_value() ) {
    // platform links found
    ret.links.linux.sha = manifest.Links.value().Linux.SHA256.value().value();
    ret.links.linux.link = manifest.Links.value().Linux.xml_content.value();
    ret.links.mac.sha = manifest.Links.value().Mac.SHA256.value().value();
    ret.links.mac.link = manifest.Links.value().Mac.xml_content.value();
    ret.links.windows.sha = manifest.Links.value().Windows.SHA256.value().value();
    ret.links.windows.link = manifest.Links.value().Windows.xml_content.value();
  } else if( manifest.Link.has_value() ) {
    // universal link found
    ret.links.linux.sha = manifest.Link.value().SHA256.value().value();
    ret.links.linux.link = manifest.Link.value().xml_content.value();
    ret.links.mac.sha = manifest.Link.value().SHA256.value().value();
    ret.links.mac.link = manifest.Link.value().xml_content.value();
    ret.links.windows.sha = manifest.Link.value().SHA256.value().value();
    ret.links.windows.link = manifest.Link.value().xml_content.value();
  }
  for( auto const& dependency : manifest.Dependencies.Dependency ) {
    ret.dependencies.push_back( dependency.value() );
  }
  ret.repository = manifest.Repository.value();
  // if( manifest.ReadMe.has_value() ) {
  //   ret.readme = manifest.ReadMe.value().value();
  // }
  if( manifest.Issues.has_value() ) {
    ret.issues = manifest.Issues.value().value();
  }
  if( manifest.Integrations.has_value() ) {
    for( auto const& integration : manifest.Integrations.value().Integration ) {
      ret.integrations.push_back( integration.value() );
    }
  }
  if( manifest.Tags.has_value() ) {
    for( auto const& tag : manifest.Tags.value().Tag ) {
      ret.tags.push_back( tag );
    }
  }
  if( manifest.Authors.has_value() ) {
    for( auto const& author : manifest.Authors.value().Author ) {
      ret.authors.push_back( author );
    }
  }
  return ret;
}

bool isDifferent( SFG::SystemSimulator::LuigiInterface::Models::ModLinksModel::Data const& a, mm::Manifest const& b ) {
  if( a.name != b.Name ) {
    return true;
  }
  if( b.DisplayName.has_value() ) {
    if( a.displayName != b.DisplayName.value() ) {
      return true;
    }
  }
  if( a.description != b.Description ) {
    return true;
  }
  if( a.version.toString() != b.Version ) {
    return true;
  }
  if( b.Links.has_value() ) {
    if( a.links.linux.link != b.Links.value().Linux.xml_content ) {
      return true;
    }
    if( a.links.linux.sha != b.Links.value().Linux.SHA256.value() ) {
      return true;
    }
    if( a.links.mac.link != b.Links.value().Mac.xml_content ) {
      return true;
    }
    if( a.links.mac.sha != b.Links.value().Mac.SHA256.value() ) {
      return true;
    }
    if( a.links.windows.link != b.Links.value().Windows.xml_content ) {
      return true;
    }
    if( a.links.windows.sha != b.Links.value().Windows.SHA256.value() ) {
      return true;
    }
  }
  if( b.Link.has_value() ) {
    if( a.links.linux.link != b.Link.value().xml_content ) {
      return true;
    }
    if( a.links.linux.sha != b.Link.value().SHA256.value() ) {
      return true;
    }
  }
  if( a.dependencies.size() != b.Dependencies.Dependency.size() ) {
    return true;
  } else {
    for( size_t i = 0; i < a.dependencies.size(); i++ ) {
      if( a.dependencies[i] != b.Dependencies.Dependency[i] ) {
        return true;
      }
    }
  }
  if( a.repository != b.Repository ) {
    return true;
  }
  // if( b.ReadMe.has_value() ) {
  //   if( a.readme != b.ReadMe.value() ) {
  //     return true;
  //   }
  // }
  if( b.Issues.has_value() ) {
    if( a.issues != b.Issues.value() ) {
      return true;
    }
  }
  if( b.Integrations.has_value() ) {
    if( a.integrations.size() != b.Integrations.value().Integration.size() ) {
      return true;
    } else {
      for( size_t i = 0; i < a.integrations.size(); i++ ) {
        if( a.integrations[i] != b.Integrations.value().Integration[i] ) {
          return true;
        }
      }
    }
  } else if( a.integrations.size() > 0 ) {
    return true;
  }
  if( b.Tags.has_value() ) {
    if( a.tags.size() != b.Tags.value().Tag.size() ) {
      return true;
    } else {
      for( size_t i = 0; i < a.tags.size(); i++ ) {
        if( a.tags[i] != b.Tags.value().Tag[i] ) {
          return true;
        }
      }
    }
  } else if( a.tags.size() > 0 ) {
    return true;
  }
  if( b.Authors.has_value() ) {
    if( a.authors.size() != b.Authors.value().Author.size() ) {
      return true;
    } else {
      for( size_t i = 0; i < a.authors.size(); i++ ) {
        if( a.authors[i] != b.Authors.value().Author[i] ) {
          return true;
        }
      }
    }
  } else if( a.authors.size() > 0 ) {
    return true;
  }
  return false;
}
