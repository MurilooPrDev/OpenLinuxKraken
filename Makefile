# Nome do executável final
TARGET = kraken_linux

# Compilador e flags
CXX = g++
CXXFLAGS = -O3 -march=native -Wall

# Arquivos fonte e objetos
SOURCES = main.cpp kraken.cpp
OBJDIR = build
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Regra principal
all: prepare $(TARGET)

# Cria a pasta de objetos se não existir
prepare:
	@mkdir -p $(OBJDIR)

# Linkagem do executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Compilação dos arquivos .cpp (Garante que o TAB seja usado aqui)
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all prepare clean
