#################################################
# FILE: Makefile
# 
# IMS 2022/23 -- 11. Model pomocí celulárního automatu
# 
# author: Vojtech Kucera (xkucer0h)
# date:   2022-12-04
# 
#################################################

CXX = g++
CXXFLAGS = -std=c++17 -MMD -Wall -Wextra -pedantic
LDLIBS = -lGL -lGLU -lglut

TARGET = cancersim
PACK_TARGET = 11_xsouku15_xkucer0h.zip

.PHONY: all clean pack run

#################################################

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
DEPS = $(patsubst %.cpp, %.d, $(SRCS))

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

-include $(DEPS)

#################################################

pack: *.cpp *.h Makefile zprava.pdf
	@rm -f $(PACK_TARGET)
	zip $(PACK_TARGET) $^

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

#################################################
# END OF FILE: Makefile
#################################################
