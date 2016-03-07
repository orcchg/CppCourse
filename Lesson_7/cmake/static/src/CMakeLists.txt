SET( TARGET cmake_0 )
SET( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_0.cpp
)
ADD_EXECUTABLE( ${TARGET} ${SOURCES} )  # compile all sources
TARGET_LINK_LIBRARIES( ${TARGET} print )  # link to libprint.a

