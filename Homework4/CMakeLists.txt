cmake_minimum_required(VERSION 3.13)

project(project4)

file(GLOB SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp")
file(GLOB HEADERS LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.hpp")

add_executable(CreateGraphAndTest ${SOURCES} ${HEADERS})
