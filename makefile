CXX = g++
CXXFLAGS = -std=c++17
SRCDIR = src
INCDIR = headers
LIBINCDIR = lib/include
OBJDIR = obj
BINDIR = bin

SRCS = $(SRCDIR)/main.cpp $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TARGET = $(BINDIR)/vm.exe

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -I$(LIBINCDIR) -c $< -o $@