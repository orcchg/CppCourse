SET( TARGET cmake_1 )
SET( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_1.cpp
)
ADD_EXECUTABLE( ${TARGET} ${SOURCES} )  # compile all sources
TARGET_LINK_LIBRARIES( ${TARGET} print )  # link to libprint.so

