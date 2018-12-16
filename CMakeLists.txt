cmake_minimum_required(VERSION 2.8.3)
project(pixy2_ros)
include(FindPkgConfig)
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
    roscpp
    image_transport
)

if (PKG_CONFIG_FOUND)
    pkg_check_modules(LIBUSB QUIET libusb-1.0)
    if (LIBUSB_INCLUDE_DIRS)
	    MESSAGE("*** libusb FOUND")
	    SET(DEPS "${DEPS} libusb-1.0-0")
    else()
	    MESSAGE("*** libusb NOT FOUND")
    endif()

endif()
find_package(OpenCV REQUIRED)

FIND_PACKAGE( Boost 1.40 COMPONENTS thread REQUIRED )

catkin_package()

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )

include_directories(${LIBUSB_INCLUDE_DIRS})
link_directories( ${LIBUSB_LIBRARY_DIRS})

add_executable( pixy2_cam
    src/erle_pixy.cpp
    src/helpFunctions.cpp
    src/pixycam.cpp
    src/usblink.cpp 
    src/chirpmon.cpp 
    src/common/chirp.cpp

)

target_link_libraries(pixy2_cam
	${LIBUSB_LIBRARIES}
    ${OpenCV_LIBRARIES}
    ${catkin_LIBRARIES}
    ${Boost_LIBRARIES}
)

install(TARGETS pixy2_cam
DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)