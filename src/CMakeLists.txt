cmake_minimum_required(VERSION 2.8)
set(CMAKE_INSTALL_PREFIX $ENV{HOME})
project(FaceFinder)
add_definitions(-std=c++11 -Wall -Wextra -Weffc++)

# -Weffc++


# enable_testing()
# add_test( testname Exename arg1 arg2 ... )
#
# Or, in its longer form:
#
#   add_test(NAME <name> [CONFIGURATIONS [Debug|Release|...]]
#            [WORKING_DIRECTORY dir]
#            COMMAND <command> [arg1 [arg2 ...]])
#
# http://www.cmake.org/Wiki/CMake/Testing_With_CTest



set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
LINK_DIRECTORIES( ${LINK_DIRECTORIES} $ENV{HOME}/lib)
include_directories($ENV{HOME}/include)

add_executable(facefinder facefinder.cpp)
target_link_libraries (facefinder LINK_PUBLIC opencv_core opencv_imgproc opencv_highgui opencv_ml opencv_video opencv_features2d opencv_calib3d opencv_objdetect opencv_contrib opencv_legacy opencv_stitching )

