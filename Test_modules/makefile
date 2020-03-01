
# -------------------- env ------------#
GTEST_DIR = ../googletest-release-1.10.0
GTEST_LIB_DIR = $(GTEST_DIR)/build/lib
GTEST_LIB_LINK = -lgtest -lgtest_main -lgmock -lgmock_main

SOURCE_DIR = ../Source
INCLUDE_DIR = ../Include
# -------------------------------------#


#-------------------flags--------------#
VPATH += $(SOURCE_DIR)


CXXFLAGS += -g -std=c++17
CXXFLAGS += -I $(INCLUDE_DIR) -I $(GTEST_DIR)/googletest/include -I $(GTEST_DIR)/googlemock/include 
# -------------------------------------#


SOURCE_OBJS += JsonParser.o
TEST_OBJS += JsonParserTestSuite.o

all:TestSuiteMain

TestSuiteMain:$(TEST_OBJS) $(SOURCE_OBJS)
	$(CXX) $^ -L$(GTEST_LIB_DIR) $(GTEST_LIB_LINK) -pthread -o $@

run:
	@./TestSuiteMain

clean:
	$(RM) *.o TestSuiteMain 