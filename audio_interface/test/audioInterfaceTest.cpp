// Library Includes
#include <gtest/gtest.h>

// C++ Includes
#include <algorithm>
#include <cfenv>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>

using float32_t = float;
using float64_t = double;
using float80_t = long double;

template < typename F_t = float80_t >
constexpr size_t bitsToBytes( size_t bitDepth ) {
  return static_cast< size_t >( std::ceil( static_cast< F_t >( bitDepth ) / F_t{ 8 } ) );
}

template < typename F_t = float80_t >
F_t roundTiesZero( F_t x ) {
  F_t integral;
  F_t fractional = std::modf( x, &integral );
  if( std::abs( fractional ) <= F_t{ 0.5 } ) {
    return integral;
  }
  return integral + std::copysign< F_t, F_t >( F_t{ 1 }, x );
}

template < typename T_t, typename F_t = float80_t >
F_t normalizeSigned( T_t value, size_t bitDepth ) {
  size_t byteDepth = bitsToBytes< F_t >( bitDepth );
  T_t tMin = std::numeric_limits< T_t >::min();
  T_t tMax = std::numeric_limits< T_t >::max();
  T_t mask = ~T_t{ 0 };
  if( ( byteDepth * 8 ) == bitDepth ) {
    // no bitshifting needed
  } else {
    // bitshifting needed
    size_t offset = ( byteDepth * 8 ) - bitDepth;
    for( size_t i = 0; i < offset; i++ ) {
      mask = mask ^ ( T_t{ 1 } << i );
      tMin = tMin ^ ( T_t{ 1 } << i );
      tMax = tMax ^ ( T_t{ 1 } << i );
    }
    value = value & mask;
  }
  F_t retFloat = F_t{ 0 };
  if( value < T_t{ 0 } ) {
    retFloat = -F_t( value ) / F_t( tMin );
  } else if( value > T_t{ 0 } ) {
    retFloat = F_t( value ) / F_t( tMax );
  }
  return std::clamp( retFloat, F_t{ -1 }, F_t{ 1 } );
}

template < typename T_t, typename F_t = float80_t >
F_t normalizeUnsigned( T_t value, size_t bitDepth ) {
  size_t byteDepth = bitsToBytes< F_t >( bitDepth );
  T_t tMin = std::numeric_limits< T_t >::min();
  T_t tMax = std::numeric_limits< T_t >::max();
  T_t mask = ~T_t{ 0 };
  if( ( byteDepth * 8 ) == bitDepth ) {
    // no bitshifting needed
  } else {
    // bitshifting needed
    size_t offset = ( byteDepth * 8 ) - bitDepth;
    for( size_t i = 0; i < offset; i++ ) {
      mask = mask ^ ( T_t{ 1 } << i );
      tMin = tMin ^ ( T_t{ 1 } << i );
      tMax = tMax ^ ( T_t{ 1 } << i );
    }
    value = value & mask;
  }
  F_t retFloat = F_t{ 0 };
  T_t halfWayPoint = ( T_t( tMax / T_t{ 2 } ) + T_t{ 1 } ) & mask;
  if( value < halfWayPoint ) {
    retFloat = -F_t( halfWayPoint - value ) / F_t( halfWayPoint );
  } else if( value > halfWayPoint ) {
    retFloat = F_t( value - halfWayPoint ) / F_t( tMax - halfWayPoint );
  }
  return std::clamp( retFloat, F_t{ -1 }, F_t{ 1 } );
}

template < typename T_t, typename F_t = float80_t >
T_t quantizeSigned( F_t value, size_t bitDepth ) {
  // scale to [0.0, 1.0]
  value = ( value + F_t{ 1 } ) / F_t{ 2 };
  F_t powerOf2 = std::pow< F_t, F_t >( F_t{ 2 }, F_t( bitDepth ) );
  F_t powerOf2Offset = powerOf2 / F_t{ 2 };
  F_t ret = ( value * powerOf2 ) - powerOf2Offset;
  F_t minVal = -powerOf2Offset;
  F_t maxVal = powerOf2 - F_t{ 1 } - powerOf2Offset;
  ret = roundTiesZero< F_t >( ret - F_t{ 0.5 } );
  ret = std::clamp< F_t >( ret, minVal, maxVal );
  return static_cast< T_t >( ret ) << ( ( bitsToBytes( bitDepth ) * 8 ) - bitDepth );
}

template < typename T_t, typename F_t = float80_t >
T_t quantizeUnsigned( F_t value, size_t bitDepth ) {
  // scale to [0.0, 1.0]
  value = ( value + F_t{ 1 } ) / F_t{ 2 };
  F_t powerOf2 = std::pow< F_t, F_t >( F_t{ 2 }, F_t( bitDepth ) );
  F_t ret = value * powerOf2;
  F_t minVal = F_t{ 0 };
  F_t maxVal = powerOf2 - F_t{ 1 };
  ret = roundTiesZero< F_t >( ret );
  ret = std::clamp< F_t >( ret, minVal, maxVal );
  return static_cast< T_t >( ret ) << ( ( bitsToBytes( bitDepth ) * 8 ) - bitDepth );
}

template < typename T_t, typename F_t = float80_t >
void testSingleIntAndBitDepth( T_t tmp0, F_t fVal, size_t bitDepth ) {
  float80_t tmp1 = normalizeSigned< T_t, F_t >( tmp0, bitDepth );
  EXPECT_EQ( tmp1, fVal );
  T_t tmp2 = quantizeSigned< T_t, F_t >( tmp1, bitDepth );
  EXPECT_EQ( tmp0, tmp2 );
}

template < typename T_t, typename F_t = float80_t >
void testSingleUintAndBitDepth( T_t tmp0, F_t fVal, size_t bitDepth ) {
  float80_t tmp1 = normalizeUnsigned< T_t, F_t >( tmp0, bitDepth );
  EXPECT_EQ( tmp1, fVal );
  T_t tmp2 = quantizeUnsigned< T_t, F_t >( tmp1, bitDepth );
  EXPECT_EQ( tmp0, tmp2 );
}

TEST( AudioInterface, Test_Uint_2 ) {
  testSingleUintAndBitDepth( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 2 );
  testSingleUintAndBitDepth( uint8_t{ 0b1100'0000 }, float80_t{ 1 }, 2 );
  testSingleUintAndBitDepth( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 2 );
}

TEST( AudioInterface, Test_Uint_3 ) {
  testSingleUintAndBitDepth( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 3 );
  testSingleUintAndBitDepth( uint8_t{ 0b1110'0000 }, float80_t{ 1 }, 3 );
  testSingleUintAndBitDepth( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 3 );
}

TEST( AudioInterface, Test_Uint_4 ) {
  testSingleUintAndBitDepth( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 4 );
  testSingleUintAndBitDepth( uint8_t{ 0b1111'0000 }, float80_t{ 1 }, 4 );
  testSingleUintAndBitDepth( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 4 );
}

TEST( AudioInterface, Test_Uint_5 ) {
  testSingleUintAndBitDepth( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 5 );
  testSingleUintAndBitDepth( uint8_t{ 0b1111'1000 }, float80_t{ 1 }, 5 );
  testSingleUintAndBitDepth( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 5 );
}

TEST( AudioInterface, Test_Uint_6 ) {
  testSingleUintAndBitDepth( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 6 );
  testSingleUintAndBitDepth( uint8_t{ 0b1111'1100 }, float80_t{ 1 }, 6 );
  testSingleUintAndBitDepth( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 6 );
}

TEST( AudioInterface, Test_Uint_7 ) {
  testSingleUintAndBitDepth( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 7 );
  testSingleUintAndBitDepth( uint8_t{ 0b1111'1110 }, float80_t{ 1 }, 7 );
  testSingleUintAndBitDepth( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 7 );
}

TEST( AudioInterface, Test_Uint_8 ) {
  testSingleUintAndBitDepth( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 8 );
  testSingleUintAndBitDepth( uint8_t{ 0b1111'1111 }, float80_t{ 1 }, 8 );
  testSingleUintAndBitDepth( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 8 );
}

TEST( AudioInterface, Test_Int_16 ) {
  testSingleIntAndBitDepth( int16_t{ 0 }, float80_t{ 0 }, 16 );
  testSingleIntAndBitDepth( std::numeric_limits< int16_t >::max(), float80_t{ 1 }, 16 );
  testSingleIntAndBitDepth( std::numeric_limits< int16_t >::min(), float80_t{ -1 }, 16 );
}

TEST( AudioInterface, Test_Int_32 ) {
  testSingleIntAndBitDepth( int32_t{ 0 }, float80_t{ 0 }, 32 );
  testSingleIntAndBitDepth( std::numeric_limits< int32_t >::max(), float80_t{ 1 }, 32 );
  testSingleIntAndBitDepth( std::numeric_limits< int32_t >::min(), float80_t{ -1 }, 32 );
}

TEST( AudioInterface, Test_Int_64 ) {
  testSingleIntAndBitDepth( int64_t{ 0 }, float80_t{ 0 }, 64 );
  testSingleIntAndBitDepth( std::numeric_limits< int64_t >::max(), float80_t{ 1 }, 64 );
  testSingleIntAndBitDepth( std::numeric_limits< int64_t >::min(), float80_t{ -1 }, 64 );
}

TEST( AudioInterface, Example ) {
  EXPECT_TRUE( true );
}
