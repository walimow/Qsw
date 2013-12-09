project(TestStepWork)
cmake_minimum_required(VERSION 2.6)

set ( CMAKE_BUILD_TYPE Debug )
add_definitions ( -Wall -std=c++0x )

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)


enable_testing()

include_directories(
${Qt5Core_INCLUDE_DIRS}  ${CMAKE_CURRENT_BINARY_DIR}
..

)

#set (LIBRARY_OUTPUT_PATH /opt/ys/64/lib )
#set (EXECUTABLE_OUTPUT_PATH /opt/ys/64/bin )
set (QT_USE_QTTEST TRUE)


set(TestStepWork_SRCS TestStepWorkTest.cpp )

set (TestStepWork_MOC_HDR  TestStepWorkTest.h)

QT5_WRAP_CPP(TestStepWork_MOC_SRCS ${TestStepWork_MOC_HDR} ${TestStepWork_MOC_SRCS} )

#qt4_automoc(${TestStepWork_SRCS})

add_executable(TestStepWork ${TestStepWork_SRCS} ${TestStepWork_MOC_SRCS})

target_link_libraries(TestStepWork  ${Qt5Test_LIBRARIES} ${Qt5Core_LIBRARIES}  ${Qt5Test_LIBRARIES} ${Qt5Core_LIBRARIES} Qsw 	xsxp  )


