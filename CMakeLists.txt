cmake_minimum_required(VERSION 3.0.2)
project(bezier_curves)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(OpenCV REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(
	include
	src
	${OpenCV_INCLUDE_DIRS}
	${Eigen3_INCLUDE_DIRS}
)

add_executable(main src/main.cpp)

target_link_libraries(main
	${OpenCV_LIBRARIES}
	Eigen3::Eigen	
)

