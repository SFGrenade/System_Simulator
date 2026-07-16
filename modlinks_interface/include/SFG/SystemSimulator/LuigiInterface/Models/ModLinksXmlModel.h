#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// Library includes
#include <rfl.hpp>
#include <rfl/xml.hpp>

// C++ includes
#include <string>
#include <vector>

namespace mm {
using CollapsedString = std::string;     // todo: base xs:string with whitespace=collapse
using CollapsedHexBinary = std::string;  // todo: base xs:hexBinary with whitespace=collapse

using VersionStringType = rfl::Pattern< R"((\d+\.){3}\d+)", "VersionStringType" >;
using LinkStringType = rfl::Pattern< R"(https?://.*)", "LinkStringType" >;
using ShaStringType = rfl::Pattern< R"([0-9a-fA-F]{64})", "ShaStringType" >;
using NameStringType = rfl::Pattern< R"([a-zA-Z][^\\/:*?<>"|]+)", "NameStringType" >;

struct Author {
  mm::CollapsedString xml_content{};
};
struct AuthorsType {
  std::vector< mm::Author > Author{};
};
using AuthorsBase = mm::AuthorsType;
using Authors = std::optional< mm::AuthorsBase >;

enum struct TagEnum {
  Accessibility,
  Boss,
  Charm,
  Cosmetic,
  Expansion,
  Gameplay,
  Joke,
  Library,
  Optimization,
  Utility,
};
struct Tag {
  mm::TagEnum xml_content{};
};
struct TagsType {
  std::vector< mm::Tag > Tag{};
};
using Tags = std::optional< mm::TagsType >;

struct Integration {
  mm::NameStringType xml_content{};
};
struct IntegrationsType {
  std::vector< mm::Integration > Integration{};
};
using Integrations = std::optional< mm::IntegrationsType >;

struct IssuesBase {
  mm::LinkStringType xml_content{};
};
using Issues = std::optional< mm::IssuesBase >;

struct ReadMeBase {
  mm::LinkStringType xml_content{};
};
using ReadMe = std::optional< mm::ReadMeBase >;

struct Repository {
  mm::LinkStringType xml_content{};
};

struct Dependency {
  mm::NameStringType xml_content{};
};
struct DependenciesType {
  std::vector< mm::Dependency > Dependency{};
};
using Dependencies = mm::DependenciesType;

struct SingleLinkType {
  mm::LinkStringType xml_content{};
  rfl::Attribute< mm::ShaStringType > SHA256{};
};
struct LinksType {
  mm::SingleLinkType Linux{};
  mm::SingleLinkType Mac{};
  mm::SingleLinkType Windows{};
};
// choice between then, so make both optional
using Link = std::optional< mm::SingleLinkType >;
using Links = std::optional< mm::LinksType >;

struct Version {
  mm::VersionStringType xml_content{};
};
struct Description {
  std::string xml_content{};
};
struct DisplayNameType {
  mm::CollapsedString xml_content{};
};
using DisplayName = std::optional< mm::DisplayNameType >;
struct Name {
  mm::NameStringType xml_content{};
};

struct Manifest {
  mm::Name Name{};
  mm::DisplayName DisplayName{};
  mm::Description Description{};
  mm::Version Version{};
  mm::Links Links{};
  mm::Link Link{};
  mm::Dependencies Dependencies{};
  mm::Repository Repository{};
  mm::ReadMe ReadMe{};
  mm::Issues Issues{};
  mm::Integrations Integrations{};
  mm::Tags Tags{};
  mm::Authors Authors{};
};
struct ModLinks {
  std::vector< mm::Manifest > Manifest{};
};
}  // namespace mm

/* FORMATTING */
template <>
struct fmt::formatter< mm::TagEnum > : formatter< std::string > {
  auto format( mm::TagEnum in, format_context& ctx ) const -> format_context::iterator;
};
template <>
struct fmt::formatter< mm::SingleLinkType > : formatter< std::string > {
  auto format( mm::SingleLinkType in, format_context& ctx ) const -> format_context::iterator;
};
template <>
struct fmt::formatter< mm::LinksType > : formatter< std::string > {
  auto format( mm::LinksType in, format_context& ctx ) const -> format_context::iterator;
};
template <>
struct fmt::formatter< mm::NameStringType > : formatter< std::string > {
  auto format( mm::NameStringType in, format_context& ctx ) const -> format_context::iterator;
};

#pragma region Comparisons

bool operator==( mm::Author const& a, mm::Author const& b );
bool operator==( mm::AuthorsType const& a, mm::AuthorsType const& b );
bool operator==( mm::Tag const& a, mm::Tag const& b );
bool operator==( mm::TagsType const& a, mm::TagsType const& b );
bool operator==( mm::Integration const& a, mm::Integration const& b );
bool operator==( mm::IntegrationsType const& a, mm::IntegrationsType const& b );
bool operator==( mm::IssuesBase const& a, mm::IssuesBase const& b );
bool operator==( mm::ReadMeBase const& a, mm::ReadMeBase const& b );
bool operator==( mm::Repository const& a, mm::Repository const& b );
bool operator==( mm::Dependency const& a, mm::Dependency const& b );
bool operator==( mm::DependenciesType const& a, mm::DependenciesType const& b );
bool operator==( mm::SingleLinkType const& a, mm::SingleLinkType const& b );
bool operator==( mm::LinksType const& a, mm::LinksType const& b );
bool operator==( mm::Version const& a, mm::Version const& b );
bool operator==( mm::Description const& a, mm::Description const& b );
bool operator==( mm::DisplayNameType const& a, mm::DisplayNameType const& b );
bool operator==( mm::Name const& a, mm::Name const& b );
bool operator==( mm::Manifest const& a, mm::Manifest const& b );
bool operator==( mm::ModLinks const& a, mm::ModLinks const& b );

bool operator!=( mm::Author const& a, mm::Author const& b );
bool operator!=( mm::AuthorsType const& a, mm::AuthorsType const& b );
bool operator!=( mm::Tag const& a, mm::Tag const& b );
bool operator!=( mm::TagsType const& a, mm::TagsType const& b );
bool operator!=( mm::Integration const& a, mm::Integration const& b );
bool operator!=( mm::IntegrationsType const& a, mm::IntegrationsType const& b );
bool operator!=( mm::IssuesBase const& a, mm::IssuesBase const& b );
bool operator!=( mm::ReadMeBase const& a, mm::ReadMeBase const& b );
bool operator!=( mm::Repository const& a, mm::Repository const& b );
bool operator!=( mm::Dependency const& a, mm::Dependency const& b );
bool operator!=( mm::DependenciesType const& a, mm::DependenciesType const& b );
bool operator!=( mm::SingleLinkType const& a, mm::SingleLinkType const& b );
bool operator!=( mm::LinksType const& a, mm::LinksType const& b );
bool operator!=( mm::Version const& a, mm::Version const& b );
bool operator!=( mm::Description const& a, mm::Description const& b );
bool operator!=( mm::DisplayNameType const& a, mm::DisplayNameType const& b );
bool operator!=( mm::Name const& a, mm::Name const& b );
bool operator!=( mm::Manifest const& a, mm::Manifest const& b );
bool operator!=( mm::ModLinks const& a, mm::ModLinks const& b );

#pragma endregion Comparisons
