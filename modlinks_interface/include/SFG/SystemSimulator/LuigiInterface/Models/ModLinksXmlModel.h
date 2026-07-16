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

using Author = mm::CollapsedString;
struct AuthorsType {
  std::vector< mm::Author > Author{};
};
using AuthorsBase = mm::AuthorsType;
using Authors = std::optional< mm::AuthorsBase >;

enum struct Tag {
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
struct TagsType {
  std::vector< mm::Tag > Tag{};
};
using TagsBase = mm::TagsType;
using Tags = std::optional< mm::TagsBase >;

using Integration = mm::NameStringType;
struct IntegrationsType {
  std::vector< mm::Integration > Integration{};
};
using IntegrationsBase = mm::IntegrationsType;
using Integrations = std::optional< mm::IntegrationsBase >;

using IssuesBase = LinkStringType;
using Issues = std::optional< mm::IssuesBase >;

using ReadMeBase = LinkStringType;
using ReadMe = std::optional< mm::ReadMeBase >;

using Repository = LinkStringType;

using Dependency = mm::NameStringType;
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
using LinkBase = mm::SingleLinkType;
using Link = std::optional< mm::LinkBase >;
using LinksBase = mm::LinksType;
using Links = std::optional< mm::LinksBase >;

using Version = mm::VersionStringType;
using Description = std::string;
using DisplayName = std::optional< mm::CollapsedString >;
using Name = mm::NameStringType;

struct Manifest {
  mm::Name Name{};
  mm::DisplayName DisplayName{};
  mm::Description Description{};
  mm::Version Version{};
  mm::Links Links{};
  mm::Link Link{};
  mm::Dependencies Dependencies{};
  mm::Repository Repository{};
  // mm::ReadMe ReadMe{};
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
struct fmt::formatter< mm::Tag > : formatter< std::string > {
  auto format( mm::Tag in, format_context& ctx ) const -> format_context::iterator;
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

/* COMPARISONS */
bool isDifferent( mm::Manifest const& a, mm::Manifest const& b );
