project(QsPrime)
cmake_minimum_required(VERSION 2.6)
find_package(Qt5Core REQUIRED)
add_definitions ( -Wall )



set ( CMAKE_BUILD_TYPE Debug )

#set(CMAKE_CXX_FLAGS "-fPIC")

set (LIBRARY_OUTPUT_PATH /opt/ys/64/lib )

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} 
  ..
  .
)

set (QsPrime_SRCS QsOut.cpp )
set (QsPrime_MOC_HDR QsOut.h )

QT5_WRAP_CPP(QsPrime_MOC_SRCS ${QsPrime_MOC_HDR}  )

add_library( QsPrime SHARED ${QsPrime_MOC_SRCS} ${QsPrime_SRCS} )

TARGET_LINK_LIBRARIES( QsPrime ${Qt5Core_LIBRARIES} )  
