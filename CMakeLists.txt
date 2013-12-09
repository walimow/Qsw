project(Qsw)
cmake_minimum_required(VERSION 2.6)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
FIND_PACKAGE(Boost REQUIRED )

add_definitions ( -Wall -std=c++0x )

#set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-fPIC")

set (EXECUTABLE_OUTPUT_PATH /opt/ys/64/bin )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widget_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR}
#${BOOST_ROOT}
../Bracket/

)

set(QswShell_SRCS   QswShell.cpp Console.cpp main.cpp)



set ( QswShell_MOC_HDR   QswShell.h Console.h)

set (QswShell_UIS   QswShellForm.ui )

QT5_WRAP_CPP(QswShell_MOC_SRCS ${QswShell_MOC_HDR}  )
QT5_WRAP_UI( QswShell_UIS_H  ${QswShell_UIS} )


add_executable(QswShell ${QswShell_SRCS} ${QswShell_MOC_SRCS}  ${QswShell_UIS_H} )

target_link_libraries(QswShell ${QT_LIBRARIES}  ${Qt5Widgets_LIBRARIES} Qsw  )

install(TARGETS QswShell RUNTIME DESTINATION bin)

add_subdirectory(QStepWork)

