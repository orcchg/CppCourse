cmake_minimum_required( VERSION 2.8 )
PROJECT( Lesson_4_STL )

# -----------------------------------------------------------------------------
# --------------------------- Common header -----------------------------------
# -----------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )  # for config.h
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} include )

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY( algorithms )
ADD_SUBDIRECTORY( containers )
ADD_SUBDIRECTORY( hashing )
ADD_SUBDIRECTORY( templates )

