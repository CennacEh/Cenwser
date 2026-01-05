CXX = g++
SDL_PATH = C:/Users/achto/Documents/CppProjects/Cenwser

CXXFLAGS = -Wextra -Wall -Dmain=SDL_main -g
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows -lcurl -g 

target = build/app.exe
src = $(shell find src/ -name "*.cpp")
obj = $(patsubst src/%.cpp, build/%.o, $(src))

all: $(target)

$(target): $(obj)
	$(CXX) $^ $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< $(CXXFLAGS) -o $@
	cp -r ./src/resources ./build/

run:
	build/app.exe

clean:
	rm -rf build/
