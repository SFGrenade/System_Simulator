#include "SFG/SystemSimulator/LuigiInterface/Models/ModLinksXmlModel.h"

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
