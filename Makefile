CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Ilib -D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN
SRCS     = src/main.cpp src/client.cpp src/caisse.cpp \
           src/supermarche.cpp src/serveur.cpp
TARGET   = supermarche.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lws2_32 -lpthread -static-libgcc -static-libstdc++

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)