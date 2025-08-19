# Sequence Set – Sistema de Gerenciamento de Conjuntos de Sequências

Este projeto implementa uma estrutura **Sequence Set** em **C++**, responsável por:  
- Converter um arquivo CSV em um arquivo binário organizado em blocos.  
- Realizar operações de **inserção, remoção, busca e listagem** de registros.  
- Demonstrar conceitos de **organização de arquivos**, **ordenamento por blocos** e **armazenamento eficiente em disco**.  

---

## ✨ Funcionalidades
- Converter um arquivo CSV em um arquivo binário com blocos ordenados.  
- Inserir novos registros no conjunto de sequências (sem permitir duplicação de IDs).  
- Remover registros pelo **ID**.  
- Pesquisar registros específicos pelo **ID**.  
- Listar todos os registros armazenados.  
- Manipular grandes conjuntos de dados de forma eficiente usando blocos e ordenação.  

---

## ⚙️ Pré-requisitos
- **Compilador C++** compatível com C++11 ou superior. Exemplos:  
  - GCC (Linux/MacOS) ou MinGW (Windows)  
  - MSVC (Microsoft Visual Studio)  
- **Editor/IDE** recomendado: VS Code, CLion, Code::Blocks ou outro de sua preferência.  

---

## 📥 Instalação e Configuração
1. **Clone o repositório**  
   ```bash
   git clone https://github.com/SEU_USUARIO/SEU_REPOSITORIO.git
   cd SEU_REPOSITORIO
   ```

2. **Prepare o arquivo CSV**  
   Crie um arquivo chamado `dadosSequenceSet_id.csv` com o seguinte cabeçalho:  
   ```csv
   id,series_reference,period,data_value,status,units,magnitude,subject,periodicity,group,series_title_1,series_title_2,series_title_3,series_title_4,series_title_5
   ```

3. **Compile o projeto**  
   ```bash
   g++ -o SequenceSet PROJETO_FINAL.cpp
   ```

4. **Execute o programa**  
   ```bash
   ./SequenceSet
   ```

---

## ▶️ Como Usar
Após rodar o programa, o menu principal será exibido:

```
Menu:
1. Inserir dado
2. Remover dado
3. Buscar dado
4. Sair
5. Imprimir todos os dados
```

- **1. Inserir dado** → Adiciona um novo registro (ID único).  
- **2. Remover dado** → Remove um registro pelo ID.  
- **3. Buscar dado** → Procura e exibe o registro pelo ID.  
- **4. Sair** → Fecha o programa.  
- **5. Imprimir todos os dados** → Lista todos os registros armazenados.  

> Obs.: O arquivo CSV (`dadosSequenceSet_id.csv`) é convertido automaticamente em binário (`data.bin`) na primeira execução.  

---

## 🔑 Detalhes de Implementação
- **Armazenamento em blocos:**  
  - Cada bloco contém até 100 registros.  
  - Se exceder a capacidade, é criado um novo arquivo binário (`data2.bin`, etc.).  

- **Ordenação:**  
  - Cada bloco é ordenado por `id` usando **Insertion Sort**.  

- **Operações em arquivo binário:**  
  - Leitura e gravação binária para eficiência.  
  - IDs duplicados não são permitidos.  

- **Tratamento de erros:**  
  - Verificação de falha na abertura de arquivos.  
  - Bloqueio de inserção de registros com IDs já existentes.  

---

## 📂 Estrutura do Projeto
```
.
├── PROJETO_FINAL.cpp   # Código fonte principal
├── dadosSequenceSet_id.csv   # Arquivo de entrada (exemplo)
├── data.bin            # Arquivo binário gerado
└── README.md           # Documentação do projeto
```

---

## 📜 Licença
Este projeto está sob a licença **MIT** – veja o arquivo [LICENSE](LICENSE) para mais detalhes.  
