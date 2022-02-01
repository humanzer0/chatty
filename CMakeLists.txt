cmake_minimum_required(VERSION 3.16)
project(chatty)

#add_executable(${PROJECT_NAME} main.cpp)

find_package(Boost)
find_package(Threads)

#target_link_libraries(${PROJECT_NAME} Boost::boost Threads::Threads)


add_subdirectory(core)
add_subdirectory(main)
