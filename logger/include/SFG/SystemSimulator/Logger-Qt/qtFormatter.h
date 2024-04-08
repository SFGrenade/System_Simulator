#ifndef LOGGER_QTFORMATTER_H_
#define LOGGER_QTFORMATTER_H_

#include <QModelIndex>
#include <QString>

#include "SFG/SystemSimulator/Logger/_spdlog.h"

void logger_qtformatter_unused();

template <>
struct fmt::formatter< QModelIndex > {
  // "{:qmi}"
  constexpr auto parse( format_parse_context& ctx ) -> decltype( ctx.begin() ) {
    auto it = ctx.begin(), end = ctx.end();
    if( it != end && ( *it == 'q' ) )
      *it++;
    if( it != end && ( *it == 'm' ) )
      *it++;
    if( it != end && ( *it == 'i' ) )
      *it++;

    if( it != end && *it != '}' )
      throw format_error( "invalid format" );

    return it;
  }

  template < typename FormatContext >
  auto format( QModelIndex const& p, FormatContext& ctx ) const -> decltype( ctx.out() ) {
    return fmt::format_to( ctx.out(), "({:d}, {:d})", p.row(), p.column() );
  }
};

template <>
struct fmt::formatter< QString > {
  // "{:qs}"
  constexpr auto parse( format_parse_context& ctx ) -> decltype( ctx.begin() ) {
    auto it = ctx.begin(), end = ctx.end();
    if( it != end && ( *it == 'q' ) )
      *it++;
    if( it != end && ( *it == 's' ) )
      *it++;

    if( it != end && *it != '}' )
      throw format_error( "invalid format" );

    return it;
  }

  template < typename FormatContext >
  auto format( QString const& p, FormatContext& ctx ) const -> decltype( ctx.out() ) {
    return fmt::format_to( ctx.out(), "{:s}", p.toLocal8Bit().constData() );
  }
};

#endif /* LOGGER_QTFORMATTER_H_ */
