cmake_minimum_required( VERSION 2.8 )
PROJECT( Lesson_10_Functional )

# -----------------------------------------------------------------------------
# --------------------------- Common header -----------------------------------
# -----------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )  # for config.h
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} include )

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY( class_member_ptr )
ADD_SUBDIRECTORY( functors )
ADD_SUBDIRECTORY( binders )
ADD_SUBDIRECTORY( adapters )
