CXXFLAGS := -Wall -Wextra -Wpedantic $(CXXFLAGS)
DEPS = -MMD -MF $(patsubst obj/%.o,dep/%.d,$@)

.DEFAULT_GOAL := all
.PHONY: all

CreateGraphAndTest: obj/adjacency_graph.o obj/create_graph_and_test.o
	$(CXX) -o $@ $(CXXFLAGS) $^
FindPaths: obj/adjacency_graph.o obj/find_paths.o
	$(CXX) -o $@ $(CXXFLAGS) $^
TestRandomGraph: obj/adjacency_graph.o obj/union_find.o obj/test_random_graph.o
	$(CXX) -o $@ $(CXXFLAGS) $^

obj/%.o: %.cpp | obj dep
	$(CXX) -c -o $@ $(CXXFLAGS) $(DEPS) $^

obj:
	mkdir -p obj

dep:
	mkdir -p dep

all: CreateGraphAndTest FindPaths TestRandomGraph

clean:
	rm -rf obj dep CreateGraphAndTest FindPaths TestRandomGraph

-include $(wildcard *.d)
