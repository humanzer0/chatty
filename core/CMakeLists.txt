project(core)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
    include/chatty/core/peer.h
    src/peer.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
