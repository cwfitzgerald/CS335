cmake_minimum_required(VERSION 3.13)

project(project4)

add_executable(CreateGraphAndTest adjacency_graph.cpp adjacency_graph.hpp create_graph_and_test.cpp)
add_executable(FindPaths adjacency_graph.cpp adjacency_graph.hpp find_paths.cpp)
add_executable(TestRandomGraph adjacency_graph.cpp adjacency_graph.hpp union-find.hpp union-find.cpp test_random_graph.cpp)
