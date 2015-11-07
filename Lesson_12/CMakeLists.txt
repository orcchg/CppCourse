cmake_minimum_required( VERSION 2.8 )
PROJECT( Lesson_12_Threads )

# -----------------------------------------------------------------------------
# --------------------------- Common header -----------------------------------
# -----------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )  # for config.h
INCLUDE_DIRECTORIES( include )
SET( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )

if( CMAKE_COMPILER_IS_MINGW )
elseif( (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW )
    ADD_DEFINITIONS( -fPIC )
    ADD_DEFINITIONS( -fvisibility=hidden -Wall )
    ADD_DEFINITIONS( -std=c++11 )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )
elseif( MSVC )
    ADD_DEFINITIONS( /MP )  # multi-core compilation with MSVC
endif()
if( CMAKE_COMPILER_IS_GNUCXX )
    SET( LIBSTDC++_LIBRARIES -lstdc++ )
endif()
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    ADD_DEFINITIONS( -Wno-missing-braces )
    ADD_DEFINITIONS( -Wno-enum-compare )
    ADD_DEFINITIONS( -Wno-deprecated )
    ADD_DEFINITIONS( -Wno-deprecated-declarations )
    ADD_DEFINITIONS( -Wno-deprecated-register )
endif()

# If this is an in-source build (CMAKE_SOURCE_DIR == CMAKE_BINARY_DIR),
# write the library/executable files to the respective directories in the
# source tree. During an out-of-source build, however, do not litter this
# directory, since that is probably what the user wanted to avoid.
if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )
    SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib" )
    SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib" )
    SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin" )
endif( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )

# Allow the user to build a shared or static library
OPTION ( BUILD_SHARED_LIBS "Build a shared version of the library" ON )

# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY( asynchronous )
ADD_SUBDIRECTORY( atomic )
ADD_SUBDIRECTORY( condition_variable )
ADD_SUBDIRECTORY( event_listener )
ADD_SUBDIRECTORY( mutex )
ADD_SUBDIRECTORY( threads )

