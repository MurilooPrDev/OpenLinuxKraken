# Nome do executável final
TARGET = kraken_linux

# Compilador e flags
CXX = g++
CXXFLAGS = -O3 -march=native -Wall -Iinclude

# Diretórios de origem e objetos
SRCDIR = src
OBJDIR = build

# Localização dos arquivos fonte
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/kraken.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Regra principal (o que acontece quando você digita apenas 'make')
all: prepare $(TARGET)

# Cria a pasta build se ela não existir
prepare:
	@mkdir -p $(OBJDIR)

# Linkagem do executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Compilação dos arquivos .cpp para .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos temporários e do binário
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all prepare clean