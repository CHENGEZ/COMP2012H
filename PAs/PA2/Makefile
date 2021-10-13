OUT := gitlite
SRCS := Commit.cpp gitlite.cpp main.cpp Repository.cpp Tester.cpp Utils.cpp
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude

ifeq (Windows_NT, $(OS))
RM := rm
else
RM := rm -f
endif

.PHONY: all
all: $(OUT)


$(OUT): $(OBJS)
	$(CXX) -o $@ $^ -static

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(OUT) $(OBJS)
