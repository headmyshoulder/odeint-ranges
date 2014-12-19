# CMakeLists.txt
# Date: 2014-12-19
# Author: Karsten Ahnert (karsten.ahnert@gmx.de)
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or
# copy at http://www.boost.org/LICENSE_1_0.txt)
#


project ( odeint-ranges )

cmake_minimum_required ( VERSION 2.8 )

set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

find_package ( Boost REQUIRED )
find_package ( RangeV3 REQUIRED )


if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -Wno-unused-function -Wno-unused-local-typedefs")
elseif( CMAKE_COMPILER_IS_GNUCXX )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -Wno-unused-function -Wno-unused-local-typedefs")
# else()
#   message(FATAL_ERROR "Unknown compiler.")
endif()


include_directories ( ${Boost_INCLUDE_DIRS} )
include_directories ( ${RangeV3_INCLUDE_DIR} )
include_directories ( include )

add_subdirectory ( examples )
# add_subdirectory ( test )

