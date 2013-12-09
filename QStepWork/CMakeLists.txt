project(Qsw)
cmake_minimum_required(VERSION 2.6)
find_package(Qt5Core REQUIRED)
FIND_PACKAGE(Boost REQUIRED )
add_definitions ( -Wall )



set ( CMAKE_BUILD_TYPE Debug )

#set(CMAKE_CXX_FLAGS "-fPIC")

# set (LIBRARY_OUTPUT_PATH /opt/ys/64/lib )

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} 
  ${Boost_INCLUDE_DIRS}
  ../../BText/
)


#link_directories (
#/opt/ys/64/lib
#) 

set (Qsw_SRCS QstwBTextParser.cpp QstwRepl.cpp QstwSxprCmdProcessor.cpp QstwMessageAutomat.cpp QstwDataForm.cpp QstwMessage.cpp  QstwProcessor.cpp QstwStepObjectBase.cpp  QstwEnvironment.cpp QstwEnvironmentData.cpp QswXSxprSupport.cpp)

set (Qsw_MOC_HDR  QstwBTextParser.h QstwRepl.h QstwEnvironment.h QstwEnvironmentData.h  QstwStepObjectBase.h QstwMessageAutomat.h   QstwProcessor.h QswXSxprSupport.h )

QT5_WRAP_CPP(Qsw_MOC_SRCS ${Qsw_MOC_HDR}  )

add_library( Qsw SHARED ${Qsw_MOC_SRCS} ${Qsw_SRCS} )

TARGET_LINK_LIBRARIES( Qsw ${Qt5Core_LIBRARIES} )  


add_subdirectory(TestStepWork)
add_subdirectory(QswPrime)