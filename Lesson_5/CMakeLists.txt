cmake_minimum_required( VERSION 2.8 )
PROJECT( Lesson_5_Inheritance )

# -----------------------------------------------------------------------------
INCLUDE_DIRECTORIES( include )
ADD_DEFINITIONS( -std=c++11 )

# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY( inheritance )
ADD_SUBDIRECTORY( polymorphism )
ADD_SUBDIRECTORY( abstract )
ADD_SUBDIRECTORY( c_style )

