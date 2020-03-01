CXXFLAGS += -g -std=c++17 -I ./Include

all: JsonMain

JsonMain:JsonMain.o
	$(CXX) $^ -o $@

clean:
	$(RM) *.o JsonMain

run:
	@./JsonMain