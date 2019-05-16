CXXFLAGS := -Wall -Wextra -Wpedantic $(CXXFLAGS)
DEPS = -MMD -MF $(patsubst obj/%.o,dep/%.d,$@)

.DEFAULT: all
.PHONY: all

optimal_multplications: obj/optimal_multplications.o
	$(CXX) -o $@ $(CXXFLAGS) $^

obj/%.o: %.cpp | obj dep
	$(CXX) -c -o $@ $(CXXFLAGS) $(DEPS) $^

obj:
	mkdir -p obj

dep:
	mkdir -p dep

all: optimal_multplications 

clean:
	rm -rf obj dep optimal_multplications 

-include $(wildcard *.d)
