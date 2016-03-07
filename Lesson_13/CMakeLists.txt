cmake_minimum_required( VERSION 2.8 )
PROJECT( Lesson_13_Network )

# -----------------------------------------------------------------------------
# --------------------------- Common header -----------------------------------
# -----------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )  # for config.h
INCLUDE_DIRECTORIES( include tinyxml )

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )
endif()

# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY( http )
ADD_SUBDIRECTORY( client )
ADD_SUBDIRECTORY( server )
ADD_SUBDIRECTORY( tinyxml )

