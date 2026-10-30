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
F_t normalize( T_t value, size_t bitDepth ) {
  value = value >> ( ( bitsToBytes< F_t >( bitDepth ) * 8 ) - bitDepth );
  F_t maxValue = std::pow< F_t, F_t >( F_t{ 2 }, F_t( bitDepth ) );
  F_t retFloat = F_t{ 0 };
  if( value < T_t{ 0 } ) {
    retFloat = -F_t( value ) / ( -( maxValue / F_t{ 2 } ) );
  } else if( value > T_t{ 0 } ) {
    retFloat = F_t( value ) / ( ( maxValue / F_t{ 2 } ) - F_t{ 1 } );
  }
  return std::clamp( retFloat, F_t{ -1 }, F_t{ 1 } );
}
template <>
float80_t normalize< uint8_t, float80_t >( uint8_t value, size_t bitDepth ) {
  return normalize< int8_t, float80_t >( static_cast< int8_t >( value - uint8_t{ 0x80 } ), bitDepth );
}
template <>
float80_t normalize< uint16_t, float80_t >( uint16_t value, size_t bitDepth ) {
  return normalize< int16_t, float80_t >( static_cast< int16_t >( value - uint16_t{ 0x8000 } ), bitDepth );
}
template <>
float80_t normalize< uint32_t, float80_t >( uint32_t value, size_t bitDepth ) {
  return normalize< int32_t, float80_t >( static_cast< int32_t >( value - uint32_t{ 0x80000000 } ), bitDepth );
}
template <>
float80_t normalize< uint64_t, float80_t >( uint64_t value, size_t bitDepth ) {
  return normalize< int64_t, float80_t >( static_cast< int64_t >( value - uint64_t{ 0x8000000000000000 } ), bitDepth );
}

template < typename T_t, typename F_t = float80_t >
T_t quantize( F_t value, size_t bitDepth ) {
  // scale to [0.0, 1.0]
  value = ( value + F_t{ 1 } ) / F_t{ 2 };

  F_t powerOf2 = std::pow< F_t, F_t >( F_t{ 2 }, F_t( bitDepth ) );
  F_t powerOf2HalfWay = powerOf2 / F_t{ 2 };
  F_t ret = ( value * powerOf2 ) - powerOf2HalfWay - F_t{ 0.5 };
  F_t minVal = -powerOf2HalfWay;
  F_t maxVal = powerOf2 - F_t{ 1 } - powerOf2HalfWay;
  ret = roundTiesZero< F_t >( ret );
  ret = std::clamp< F_t >( ret, minVal, maxVal );
  return static_cast< T_t >( ret ) << ( ( bitsToBytes< F_t >( bitDepth ) * 8 ) - bitDepth );
}
template <>
uint8_t quantize< uint8_t, float80_t >( float80_t value, size_t bitDepth ) {
  return quantize< int8_t, float80_t >( value, bitDepth ) + uint8_t{ 0x80 };
}
template <>
uint16_t quantize< uint16_t, float80_t >( float80_t value, size_t bitDepth ) {
  return quantize< int16_t, float80_t >( value, bitDepth ) + uint16_t{ 0x8000 };
}
template <>
uint32_t quantize< uint32_t, float80_t >( float80_t value, size_t bitDepth ) {
  return quantize< int32_t, float80_t >( value, bitDepth ) + uint32_t{ 0x80000000 };
}
template <>
uint64_t quantize< uint64_t, float80_t >( float80_t value, size_t bitDepth ) {
  return quantize< int64_t, float80_t >( value, bitDepth ) + uint64_t{ 0x8000000000000000 };
}

template < typename T_t, typename F_t = float80_t >
void testSingleAndBitDepth( T_t tmp0, F_t fVal, size_t bitDepth ) {
  float80_t tmp1 = normalize< T_t, F_t >( tmp0, bitDepth );
  EXPECT_EQ( tmp1, fVal );
  T_t tmp2 = quantize< T_t, F_t >( tmp1, bitDepth );
  EXPECT_EQ( tmp0, tmp2 );
}

TEST( AudioInterface, Test_Uint_2 ) {
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 2 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1100'0000 }, float80_t{ 1 }, 2 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 2 );
}

TEST( AudioInterface, Test_Uint_3 ) {
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 3 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1110'0000 }, float80_t{ 1 }, 3 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 3 );
}

TEST( AudioInterface, Test_Uint_4 ) {
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 4 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1111'0000 }, float80_t{ 1 }, 4 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 4 );
}

TEST( AudioInterface, Test_Uint_5 ) {
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 5 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1111'1000 }, float80_t{ 1 }, 5 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 5 );
}

TEST( AudioInterface, Test_Uint_6 ) {
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 6 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1111'1100 }, float80_t{ 1 }, 6 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 6 );
}

TEST( AudioInterface, Test_Uint_7 ) {
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 7 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1111'1110 }, float80_t{ 1 }, 7 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 7 );
}

TEST( AudioInterface, Test_Uint_8 ) {
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1000'0000 }, float80_t{ 0 }, 8 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b1111'1111 }, float80_t{ 1 }, 8 );
  testSingleAndBitDepth< uint8_t, float80_t >( uint8_t{ 0b0000'0000 }, float80_t{ -1 }, 8 );
}

TEST( AudioInterface, Test_Int_16 ) {
  testSingleAndBitDepth< int16_t, float80_t >( int16_t{ 0 }, float80_t{ 0 }, 16 );
  testSingleAndBitDepth< int16_t, float80_t >( std::numeric_limits< int16_t >::max(), float80_t{ 1 }, 16 );
  testSingleAndBitDepth< int16_t, float80_t >( std::numeric_limits< int16_t >::min(), float80_t{ -1 }, 16 );
}

TEST( AudioInterface, Test_Int_32 ) {
  testSingleAndBitDepth< int32_t, float80_t >( int32_t{ 0 }, float80_t{ 0 }, 32 );
  testSingleAndBitDepth< int32_t, float80_t >( std::numeric_limits< int32_t >::max(), float80_t{ 1 }, 32 );
  testSingleAndBitDepth< int32_t, float80_t >( std::numeric_limits< int32_t >::min(), float80_t{ -1 }, 32 );
}

TEST( AudioInterface, Test_Int_64 ) {
  testSingleAndBitDepth< int64_t, float80_t >( int64_t{ 0 }, float80_t{ 0 }, 64 );
  testSingleAndBitDepth< int64_t, float80_t >( std::numeric_limits< int64_t >::max(), float80_t{ 1 }, 64 );
  testSingleAndBitDepth< int64_t, float80_t >( std::numeric_limits< int64_t >::min(), float80_t{ -1 }, 64 );
}

TEST( AudioInterface, Example ) {
  EXPECT_TRUE( true );
}
