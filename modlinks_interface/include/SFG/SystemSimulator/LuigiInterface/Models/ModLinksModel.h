#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LuigiInterface/libui_all.h>
#include <SFG/SystemSimulator/LuigiInterface/models/AbstractModel.h>

// C++ includes
#include <rfl.hpp>
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

using IssuesBase = std::string;
using Issues = std::optional< mm::IssuesBase >;

using Repository = std::string;

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
  mm::Issues Issues{};
  mm::Integrations Integrations{};
  mm::Tags Tags{};
  mm::Authors Authors{};
};
struct ModLinks {
  std::vector< mm::Manifest > Manifest{};
};
}  // namespace mm

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

class ModLinksModel : public AbstractModel {
  static std::string const SERVER_ADDRESS;
  static std::string const SERVER_PATH;

  public:
  using Data = mm::Manifest;

  public:
  explicit ModLinksModel();
  ~ModLinksModel();

  public:
  AbstractModel::index_t columnCount() const override;
  uiTableValueType columnType( AbstractModel::index_t column ) const override;
  AbstractModel::index_t rowCount() const override;
  uiTableValue* getCell( AbstractModel::index_t row, AbstractModel::index_t column ) const override;

  void setupFromOnline();
  void setupFromCache();

  private:
  void integrateNewList( std::vector< ModLinksModel::Data >& dataList );

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  std::vector< ModLinksModel::Data > dataList_;
};

}  // namespace Models
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG

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
