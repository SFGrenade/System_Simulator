#include "SFG/SystemSimulator/LuigiInterface/Models/ModLinksXmlModel.h"

auto fmt::formatter< mm::TagEnum >::format( mm::TagEnum in, format_context& ctx ) const -> format_context::iterator {
  std::string ret = "##-UNKNOWN-##";
  switch( in ) {
    case mm::TagEnum::Accessibility:
      ret = "Accessibility";
      break;
    case mm::TagEnum::Boss:
      ret = "Boss";
      break;
    case mm::TagEnum::Charm:
      ret = "Charm";
      break;
    case mm::TagEnum::Cosmetic:
      ret = "Cosmetic";
      break;
    case mm::TagEnum::Expansion:
      ret = "Expansion";
      break;
    case mm::TagEnum::Gameplay:
      ret = "Gameplay";
      break;
    case mm::TagEnum::Joke:
      ret = "Joke";
      break;
    case mm::TagEnum::Library:
      ret = "Library";
      break;
    case mm::TagEnum::Optimization:
      ret = "Optimization";
      break;
    case mm::TagEnum::Utility:
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

#pragma region Comparisons

bool operator==( mm::Author const& a, mm::Author const& b ) {
  return a.xml_content == b.xml_content;
}

bool operator==( mm::AuthorsType const& a, mm::AuthorsType const& b ) {
  if( a.Author.size() != b.Author.size() )
    return false;
  for( size_t i = 0; i < a.Author.size(); i++ )
    if( a.Author[i] != b.Author[i] )
      return false;
  return true;
}

bool operator==( mm::Tag const& a, mm::Tag const& b ) {
  return a.xml_content == b.xml_content;
}

bool operator==( mm::TagsType const& a, mm::TagsType const& b ) {
  if( a.Tag.size() != b.Tag.size() )
    return false;
  for( size_t i = 0; i < a.Tag.size(); i++ )
    if( a.Tag[i] != b.Tag[i] )
      return false;
  return true;
}

bool operator==( mm::Integration const& a, mm::Integration const& b ) {
  return a.xml_content.get() == b.xml_content.get();
}

bool operator==( mm::IntegrationsType const& a, mm::IntegrationsType const& b ) {
  if( a.Integration.size() != b.Integration.size() )
    return false;
  for( size_t i = 0; i < a.Integration.size(); i++ )
    if( a.Integration[i] != b.Integration[i] )
      return false;
  return true;
}

bool operator==( mm::IssuesBase const& a, mm::IssuesBase const& b ) {
  return a.xml_content.get() == b.xml_content.get();
}

bool operator==( mm::ReadMeBase const& a, mm::ReadMeBase const& b ) {
  return a.xml_content.get() == b.xml_content.get();
}

bool operator==( mm::Repository const& a, mm::Repository const& b ) {
  return a.xml_content.get() == b.xml_content.get();
}

bool operator==( mm::Dependency const& a, mm::Dependency const& b ) {
  return a.xml_content.get() == b.xml_content.get();
}

bool operator==( mm::DependenciesType const& a, mm::DependenciesType const& b ) {
  if( a.Dependency.size() != b.Dependency.size() )
    return false;
  for( size_t i = 0; i < a.Dependency.size(); i++ )
    if( a.Dependency[i] != b.Dependency[i] )
      return false;
  return true;
}

bool operator==( mm::SingleLinkType const& a, mm::SingleLinkType const& b ) {
  return ( a.SHA256.get() == b.SHA256.get() ) && ( a.xml_content.get() == b.xml_content.get() );
}

bool operator==( mm::LinksType const& a, mm::LinksType const& b ) {
  return ( a.Linux == b.Linux ) && ( a.Mac == b.Mac ) && ( a.Windows == b.Windows );
}

bool operator==( mm::Version const& a, mm::Version const& b ) {
  return a.xml_content.get() == b.xml_content.get();
}

bool operator==( mm::Description const& a, mm::Description const& b ) {
  return a.xml_content == b.xml_content;
}

bool operator==( mm::DisplayNameType const& a, mm::DisplayNameType const& b ) {
  return a.xml_content == b.xml_content;
}

bool operator==( mm::Name const& a, mm::Name const& b ) {
  return a.xml_content.get() == b.xml_content.get();
}

bool operator==( mm::Manifest const& a, mm::Manifest const& b ) {
  if( a.Name != b.Name )
    return false;
  if( a.DisplayName.has_value() != b.DisplayName.has_value() )
    return false;
  else if( a.DisplayName.has_value() && b.DisplayName.has_value() )
    if( a.DisplayName.value() != b.DisplayName.value() )
      return false;
  if( a.Description != b.Description )
    return false;
  if( a.Version != b.Version )
    return false;
  if( a.Links.has_value() != b.Links.has_value() )
    return false;
  else if( a.Links.has_value() && b.Links.has_value() )
    if( a.Links.value() != b.Links.value() )
      return false;
  if( a.Link.has_value() != b.Link.has_value() )
    return false;
  else if( a.Link.has_value() && b.Link.has_value() )
    if( a.Link.value() != b.Link.value() )
      return false;
  if( a.Dependencies != b.Dependencies )
    return false;
  if( a.Repository != b.Repository )
    return false;
  if( a.ReadMe.has_value() != b.ReadMe.has_value() )
    return false;
  else if( a.ReadMe.has_value() && b.ReadMe.has_value() )
    if( a.ReadMe.value() != b.ReadMe.value() )
      return false;
  if( a.Issues.has_value() != b.Issues.has_value() )
    return false;
  else if( a.Issues.has_value() && b.Issues.has_value() )
    if( a.Issues.value() != b.Issues.value() )
      return false;
  if( a.Integrations.has_value() != b.Integrations.has_value() )
    return false;
  else if( a.Integrations.has_value() && b.Integrations.has_value() )
    if( a.Integrations.value() != b.Integrations.value() )
      return false;
  if( a.Tags.has_value() != b.Tags.has_value() )
    return false;
  else if( a.Tags.has_value() && b.Tags.has_value() )
    if( a.Tags.value() != b.Tags.value() )
      return false;
  if( a.Authors.has_value() != b.Authors.has_value() )
    return false;
  else if( a.Authors.has_value() && b.Authors.has_value() )
    if( a.Authors.value() != b.Authors.value() )
      return false;
  return true;
}

bool operator==( mm::ModLinks const& a, mm::ModLinks const& b ) {
  if( a.Manifest.size() != b.Manifest.size() )
    return false;
  for( size_t i = 0; i < a.Manifest.size(); i++ )
    if( a.Manifest[i] != b.Manifest[i] )
      return false;
  return true;
}

bool operator!=( mm::Author const& a, mm::Author const& b ) {
  return !( a == b );
}

bool operator!=( mm::AuthorsType const& a, mm::AuthorsType const& b ) {
  return !( a == b );
}

bool operator!=( mm::Tag const& a, mm::Tag const& b ) {
  return !( a == b );
}

bool operator!=( mm::TagsType const& a, mm::TagsType const& b ) {
  return !( a == b );
}

bool operator!=( mm::Integration const& a, mm::Integration const& b ) {
  return !( a == b );
}

bool operator!=( mm::IntegrationsType const& a, mm::IntegrationsType const& b ) {
  return !( a == b );
}

bool operator!=( mm::IssuesBase const& a, mm::IssuesBase const& b ) {
  return !( a == b );
}

bool operator!=( mm::ReadMeBase const& a, mm::ReadMeBase const& b ) {
  return !( a == b );
}

bool operator!=( mm::Repository const& a, mm::Repository const& b ) {
  return !( a == b );
}

bool operator!=( mm::Dependency const& a, mm::Dependency const& b ) {
  return !( a == b );
}

bool operator!=( mm::DependenciesType const& a, mm::DependenciesType const& b ) {
  return !( a == b );
}

bool operator!=( mm::SingleLinkType const& a, mm::SingleLinkType const& b ) {
  return !( a == b );
}

bool operator!=( mm::LinksType const& a, mm::LinksType const& b ) {
  return !( a == b );
}

bool operator!=( mm::Version const& a, mm::Version const& b ) {
  return !( a == b );
}

bool operator!=( mm::Description const& a, mm::Description const& b ) {
  return !( a == b );
}

bool operator!=( mm::DisplayNameType const& a, mm::DisplayNameType const& b ) {
  return !( a == b );
}

bool operator!=( mm::Name const& a, mm::Name const& b ) {
  return !( a == b );
}

bool operator!=( mm::Manifest const& a, mm::Manifest const& b ) {
  return !( a == b );
}

bool operator!=( mm::ModLinks const& a, mm::ModLinks const& b ) {
  return !( a == b );
}

#pragma endregion Comparisons
