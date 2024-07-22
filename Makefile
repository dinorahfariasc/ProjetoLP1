# Nome do executável a ser gerado
TARGET = app

# Diretórios
SRC_DIR = src
BUILD_DIR = bin
INCLUDE_DIR = sfml/include
LIB_DIR = sfml/lib

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -g
LDFLAGS = -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system
INC = -I$(INCLUDE_DIR)

# Listar todos os arquivos fonte .cpp
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Gerar nomes de arquivos .o correspondentes
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Comando para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)

# Regra genérica para compilar arquivos .cpp em arquivos .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

# Limpar arquivos intermediários e o executável
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(TARGET)

# Comando padrão ao digitar apenas `make`
all: $(TARGET)

# Informações adicionais de depuração
print-%:
	@echo $* = $($*)

.PHONY: clean all