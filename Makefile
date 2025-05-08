CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -Wall -Wextra -pthread
SRC_DIR := src
BUILD_DIR := build
DATA_DIR := data

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
EXEC := omnicore_hack

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

setup:
	@mkdir -p $(DATA_DIR)
	@echo "admin\npassword\n0mn1C0r3_P@ss" > $(DATA_DIR)/passwords.txt
	@echo "OmniCore secret data packet" > $(DATA_DIR)/traffic.pcap

clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: all clean setup