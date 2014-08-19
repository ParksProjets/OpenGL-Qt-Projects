cmake_minimum_required(VERSION 2.8.11)
set(PROJECT_NAME_STR SurfaceSubdivider)
project(${PROJECT_NAME_STR} C CXX)

set(CMAKE_CXX_FLAGS "-g -Wall -Werror")
set(CMAKE_AUTOMOC ON)

# Look for required installed packages.
find_package(Threads)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(OpenGL)

# Build application
set(COMMON_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/src)
set(MAIN_FILE ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE LIBRARY_FILES ${PROJECT_SOURCE_DIR}/src/*.h 
    ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM LIBRARY_FILES ${MAIN_FILE})

set(PROJECT_LIB lib${PROJECT_NAME_STR})

add_library(${PROJECT_LIB} ${LIBRARY_FILES})
qt5_use_modules(${PROJECT_LIB} Widgets 3D OpenGL)
target_link_libraries(${PROJECT_LIB} 
	${QT_LIBRARIES} 
	${OPENGL_LIBRARIES}
)

add_executable(${PROJECT_NAME_STR} ${MAIN_FILE})
qt5_use_modules(${PROJECT_NAME_STR} Widgets 3D OpenGL)
target_link_libraries(${PROJECT_NAME_STR} 
	${PROJECT_LIB}
	${QT_LIBRARIES} 
	${OPENGL_LIBRARIES}
)

# Build tests
set(VENDOR_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/vendor)
add_subdirectory(${VENDOR_PROJECTS_DIR}/gtest)

enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)

include_directories(${gtest_SOURCE_DIR}/include 
					${gtest_SOURCE_DIR}
					${COMMON_INCLUDES_DIR})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
qt5_use_modules(${PROJECT_TEST_NAME} Widgets 3D OpenGL)

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_TEST_NAME}
	gtest
	gtest_main
)
target_link_libraries(${PROJECT_TEST_NAME}
	${QT_LIBRARIES}
	${OPENGL_LIBRARIES}
)
target_link_libraries(${PROJECT_TEST_NAME}
	${PROJECT_LIB}
)

add_test(tests ${PROJECT_TEST_NAME})
