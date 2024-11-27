# 编译器和编译选项
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# 目标文件和可执行文件
TARGET = main
SOURCES = main.cc board.cc data.cc link.cc player.cc serverports.cc subject.cc unit.cc virus.cc wall.cc window.cc
OBJECTS = $(SOURCES:.cc=.o)

# 默认目标
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# 编译每个 .cc 文件到 .o 文件
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)
