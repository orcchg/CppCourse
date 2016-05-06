cmake_minimum_required( VERSION 2.8 )
PROJECT( Lesson_1_Basics )

# -----------------------------------------------------------------------------
# --------------------------- Common header -----------------------------------
# -----------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )  # for config.h
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} logging )

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY( arrays )
ADD_SUBDIRECTORY( functions )
ADD_SUBDIRECTORY( pointers )
ADD_SUBDIRECTORY( sortings )
ADD_SUBDIRECTORY( statements )
ADD_SUBDIRECTORY( visibility_scope )

