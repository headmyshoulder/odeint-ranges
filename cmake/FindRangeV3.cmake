# - Finds RangeV3
#
# It sets the following variables:
#  RangeV3_FOUND       - Set to false, or undefined, if RangeV3 isn't found.
#  RangeV3_INCLUDE_DIR - The RangeV3 include directory.

if ( NOT DEFINED RangeV3_ROOT )
    set( RangeV3_ROOT $ENV{RANGEV3_ROOT} ) 
endif ()    

find_path ( RangeV3_INCLUDE_DIR range/v3/all.hpp ${RangeV3_ROOT}/include )

if ( RangeV3_INCLUDE_DIR )
    set ( RangeV3_FOUND TRUE )
else ()
    set ( RangeV3_FOUND FALSE )
endif ()


if ( RangeV3_FOUND )

   # show which RangeV3 Directory was found only if not quiet
   if ( NOT RangeV3_FIND_QUIETLY )
      message ( STATUS "Found RangeV3 include directory : ${RangeV3_INCLUDE_DIR}" )
   endif ( NOT RangeV3_FIND_QUIETLY )

else ()

   # fatal error if RangeV3 is required but not found

   set( ERROR_MESSAGE "Could not find RangeV3. Make sure RangeV3 can be found in ${RangeV3_ROOT}." )
   set( ERROR_MESSAGE "${ERROR_MESSAGE} Note: The environment variable RANGEV3_ROOT is ignorded if the cmake variable RangeV3_ROOT has been set." )

   if ( RangeV3_FIND_REQUIRED )
      message ( FATAL_ERROR ${ERROR_MESSAGE} )
   else ()
      message ( STATUS ${ERROR_MESSAGE} )
   endif ()

endif ()
