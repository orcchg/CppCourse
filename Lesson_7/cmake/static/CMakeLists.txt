cmake_minimum_required( VERSION 2.8 )
PROJECT( Lesson_7_CMake_static_linking )

# -----------------------------------------------------------------------------
# --------------------------- Common header -----------------------------------
# -----------------------------------------------------------------------------
INCLUDE_DIRECTORIES( include )

if( (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )  # compiler flags
endif()

# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY( lib )
ADD_SUBDIRECTORY( src )

