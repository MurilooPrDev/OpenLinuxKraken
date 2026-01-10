# OpenLinuxKraken

Uma implementação de alto desempenho do algoritmo de descompressão **Oodle Kraken**, desenvolvida especificamente para ambientes Linux. O **OpenLinuxKraken** é voltado para pesquisadores de segurança, desenvolvedores de ferramentas de preservação de jogos e entusiastas de engenharia reversa de sistemas embarcados.

---

## 🚀 Funcionalidades

* **Motor de Descompressão rANS:** Implementação otimizada do decodificador de entropia (Range Asymmetric Numeral Systems).
* **LZ-Based Decompression:** Suporte para o motor de janelas deslizantes (Sliding Window) utilizado em arquiteturas de nova geração.
* **Otimização Nativa:** Compilação otimizada para o conjunto de instruções do seu processador específico via flags `-march=native`.
* **Minimalista:** Sem dependências externas; utiliza apenas C++ padrão (STL).

## 🛠️ Como Compilar

Certifique-se de ter o `g++` e o `make` instalados (No Ubuntu/Debian: `sudo apt install build-essential`).

1. No terminal, acesse a pasta do projeto.
2. Compile usando o Makefile:
   ```bash
   make
Isso gerará o executável kraken_linux na raiz do diretório.

📂 Como Usar
A ferramenta opera via linha de comando (CLI). Ela espera um arquivo de entrada (comprimido) e gera um arquivo de saída (descomprimido).

Bash

./kraken_linux <arquivo_entrada.bin> <arquivo_saida.dec>
Exemplo prático:
Bash

./kraken_linux firmware_segment.bin firmware_segment.raw
🔍 Dicas para Engenharia Reversa
Ao analisar Kernels ou pacotes de jogos (.pak, .psarc), procure pela assinatura hexadecimal da família Oodle:

Assinatura: 8C 0A ou 0x8C no início do bloco.

Se o arquivo estiver criptografado (ex: Kernel do PS5 em repouso), você deve realizar a descriptografia AES antes de utilizar o OpenLinuxKraken, pois o algoritmo atua na camada de compressão de dados puros (plaintext).

⚠️ Avisos e Isenção de Responsabilidade
Uso Educacional: Este projeto foi criado estritamente para fins educacionais. O autor não incentiva a pirataria.

Propriedade Intelectual: O algoritmo Oodle Kraken é de propriedade da RAD Game Tools (Epic Games). Esta é uma implementação independente e não contém código-fonte original ou proprietário da referida empresa.

Garantia: Este software é fornecido "como está", sem garantias de qualquer tipo.

OpenLinuxKraken - Desenvolvido para ambientes Linux x86_64.



OpenKrakenLinux - coded and written by muriloopr
