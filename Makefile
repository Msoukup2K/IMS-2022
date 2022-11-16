#################################################
# FILE: Makefile
# 
# IMS 2022/23 -- 11. Model pomocí celulárního automatu
# 
# author: Vojtech Kucera (xkucer0h)
# date:   2022-11-16
# 
#################################################

CXX = g++
CXXFLAGS = -std=c++17 -MMD -Wall -Wextra -pedantic

TARGET = run

.PHONY: all clean pack

#################################################

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
DEPS = $(patsubst %.cpp, %.d, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

-include $(DEPS)

#################################################

pack: *.cpp *.h Makefile README.md
	zip 11_xsouku15_xkucer0h.zip $^

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

#################################################
# END OF FILE: Makefile
#################################################
