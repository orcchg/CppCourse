SET( TARGET_NAME database_1 )
SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )
SET( SOURCES 
  ${SOURCE_DIR}/person.cpp
  ${SOURCE_DIR}/image_person.cpp
  ${SOURCE_DIR}/image.cpp
  ${SOURCE_DIR}/database_v2.cpp
  ${SOURCE_DIR}/main_1.cpp 
)

SET( PATH_libPNG
  ${PROJECT_SOURCE_DIR}/libpng/build/.libs/libpng16.so
)

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/sqlite ${PROJECT_SOURCE_DIR}/include/blobs )

ADD_DEFINITIONS( -std=c++11 -fPIC )

ADD_EXECUTABLE( ${TARGET_NAME} ${SOURCES} )
TARGET_LINK_LIBRARIES( ${TARGET_NAME} sqlite dl pthread ${PATH_libPNG} )

