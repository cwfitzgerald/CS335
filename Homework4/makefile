CXXFLAGS := -Wall -Wextra -Wpedantic $(CXXFLAGS)
DEPS = -MMD -MF $(patsubst obj/%.o,dep/%.d,$@)
OBJS = $(patsubst %.cpp,obj/%.o,$1)

.DEFAULT: all
.PHONY: all

bin/CreateGraphAndTest: obj/main.o obj/adjacency_graph.o | bin
	$(CXX) -o $@ $(CXXFLAGS) $^

obj/%.o: %.cpp | obj dep
	$(CXX) -c -o $@ $(CXXFLAGS) $(DEPS) $^

bin:
	mkdir -p bin

obj:
	mkdir -p obj

dep:
	mkdir -p dep

all: bin/CreateGraphAndTest

clean:
	rm -rf bin obj dep

-include $(wildcard *.d)
