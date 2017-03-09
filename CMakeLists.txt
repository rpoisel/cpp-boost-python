cmake_minimum_required(VERSION 2.8)

find_package(Boost)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "Unable to find Boost. Did you set BOOST_ROOT?")
endif ()

if (NOT USE_PYTHON_VERSION)
    set(BOOST_PYTHON_LIB python-py27)
    find_package(PythonInterp 2.7 REQUIRED)
    find_package(PythonLibs 2.7 REQUIRED)
elseif (USE_PYTHON_VERSION STREQUAL "3.5")
    set(BOOST_PYTHON_LIB python-py35)
    find_package(PythonInterp 3.5 REQUIRED)
    find_package(PythonLibs 3.5 REQUIRED)

else ()
    message(FATAL_ERROR "Unsupported Python version.")
endif ()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS ${BOOST_PYTHON_LIB} REQUIRED)

if (TRUE)
    PYTHON_ADD_MODULE(mymodule mymodule.cpp)
    target_include_directories(mymodule PRIVATE ${PYTHON_INCLUDE_PATH})
endif ()

add_executable(yay yay.cpp mymodule.cpp)
target_link_libraries(yay ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(yay PRIVATE "${Boost_INCLUDE_DIRS}" "${PYTHON_INCLUDE_DIR}")

if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(yay PRIVATE "-Wall")
else ()
  message (FATAL_ERROR "CMakeLists.txt has not been tested/written for your compiler.")
endif ()

file(COPY embedding.py DESTINATION ${CMAKE_BINARY_DIR})
