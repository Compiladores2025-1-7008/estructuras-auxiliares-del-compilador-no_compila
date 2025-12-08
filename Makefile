CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./src -I./external/googletest/googletest/include
LDFLAGS = -pthread

SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

GTEST_LIB = external/googletest/build/lib/libgtest.a external/googletest/build/lib/libgtest_main.a

TARGET_TEST = runTests

.PHONY: all test clean gtest

all: test

# -------------------------
# Build GoogleTest
# -------------------------
gtest:
	@if [ ! -d "external/googletest" ]; then \
		echo "Clonando GoogleTest..."; \
		mkdir -p external; \
		cd external; \
		git clone https://github.com/google/googletest.git; \
	fi
	@mkdir -p external/googletest/build
	@cd external/googletest/build && cmake .. && make

# -------------------------
# Build Tests
# -------------------------
test: $(TARGET_TEST)
	./$(TARGET_TEST)

$(TARGET_TEST): gtest $(OBJS) $(TEST_OBJS)
	$(CXX) -o $@ $(OBJS) $(TEST_OBJS) $(GTEST_LIB) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# -------------------------
# Clean
# -------------------------
clean:
	rm -rf $(BUILD_DIR) $(TARGET_TEST) external/googletest

