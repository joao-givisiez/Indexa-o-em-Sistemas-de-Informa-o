#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

const int MAX_BLOCKS = 5; // Defina o número máximo de blocos por arquivo
const int MAX_RECORDS_PER_BLOCK = 100; // Agora cada bloco terá 100 registros

// Estrutura para armazenar os registros do CSV
struct Record {
    int id;
    char series_reference[30]; // Identificador único
    char period[10];           // Período
    char data_value[20];       // Valor dos dados
    char status[20];           // Status dos dados
    char units[10];            // Unidade de medida
    char magnitude[5];         // Magnitude
    char subject[50];          // Assunto
    char periodicity[50];      // Periodicidade
    char group[50];            // Grupo
    char series_title_1[100];  // Título 1
    char series_title_2[100];  // Título 2
    char series_title_3[100];  // Título 3
    char series_title_4[100];  // Título 4
    char series_title_5[100];  // Título 5

    // Método para imprimir os campos do registro
    void print() const {
        cout << "ID: " << id << endl;
        cout << "Series Reference: " << series_reference << endl;
        cout << "Period: " << period << endl;
        cout << "Data Value: " << data_value << endl;
        cout << "Status: " << status << endl;
        cout << "Units: " << units << endl;
        cout << "Magnitude: " << magnitude << endl;
        cout << "Subject: " << subject << endl;
        cout << "Periodicity: " << periodicity << endl;
        cout << "Group: " << group << endl;
        cout << "Series Title 1: " << series_title_1 << endl;
        cout << "Series Title 2: " << series_title_2 << endl;
        cout << "Series Title 3: " << series_title_3 << endl;
        cout << "Series Title 4: " << series_title_4 << endl;
        cout << "Series Title 5: " << series_title_5 << endl;
    }
};

// Função para comparar registros por ID
bool compareRecords(const Record& a, const Record& b) {
    return a.id < b.id;
}

// Função para ordenar o bloco de registros usando insertion sort
void insertionSort(Record block[], int n) {
    for (int i = 1; i < n; i++) {
        Record key = block[i];
        int j = i - 1;

        while (j >= 0 && block[j].id > key.id) {
            block[j + 1] = block[j];
            j--;
        }
        block[j + 1] = key;
    }
}

class SequenceSet {
private:
    const char *binaryFileName;
    int currentBlock; // Bloco atual para escrita

public:
    SequenceSet(const char *fileName) : binaryFileName(fileName), currentBlock(0) {}

    // Conversão de CSV para binário com blocos ordenados
    void convertCsvToBinary(const char* csvFileName) {
        ifstream csvFile(csvFileName);
        ofstream binaryFile(binaryFileName, ios::binary);

        if (!csvFile.is_open() || !binaryFile.is_open()) {
            cerr << "Erro ao abrir o arquivo CSV ou binário." << endl;
            return;
        }

        string line;
        getline(csvFile, line); // Ignorar o cabeçalho do CSV

        Record block[MAX_RECORDS_PER_BLOCK]; // Bloco de registros
        int recordCount = 0; // Contador de registros no bloco atual

        // Ler registros do CSV e preencher o bloco
        while (getline(csvFile, line)) {
            stringstream ss(line);
            Record record;
            string field;

            getline(ss, field, ','); record.id = stoi(field);
            getline(ss, field, ','); strncpy(record.series_reference, field.c_str(), sizeof(record.series_reference));
            getline(ss, field, ','); strncpy(record.period, field.c_str(), sizeof(record.period));
            getline(ss, field, ','); strncpy(record.data_value, field.c_str(), sizeof(record.data_value));
            getline(ss, field, ','); strncpy(record.status, field.c_str(), sizeof(record.status));
            getline(ss, field, ','); strncpy(record.units, field.c_str(), sizeof(record.units));
            getline(ss, field, ','); strncpy(record.magnitude, field.c_str(), sizeof(record.magnitude));
            getline(ss, field, ','); strncpy(record.subject, field.c_str(), sizeof(record.subject));
            getline(ss, field, ','); strncpy(record.periodicity, field.c_str(), sizeof(record.periodicity));
            getline(ss, field, ','); strncpy(record.group, field.c_str(), sizeof(record.group));
            getline(ss, field, ','); strncpy(record.series_title_1, field.c_str(), sizeof(record.series_title_1));
            getline(ss, field, ','); strncpy(record.series_title_2, field.c_str(), sizeof(record.series_title_2));
            getline(ss, field, ','); strncpy(record.series_title_3, field.c_str(), sizeof(record.series_title_3));
            getline(ss, field, ','); strncpy(record.series_title_4, field.c_str(), sizeof(record.series_title_4));
            getline(ss, field, ','); strncpy(record.series_title_5, field.c_str(), sizeof(record.series_title_5));

            // Inserir o registro no bloco e ordenar
            block[recordCount++] = record;
            insertionSort(block, recordCount);

            // Se o bloco estiver cheio, gravar no arquivo
            if (recordCount == MAX_RECORDS_PER_BLOCK) {
                binaryFile.write(reinterpret_cast<const char*>(block), sizeof(Record) * MAX_RECORDS_PER_BLOCK);
                recordCount = 0;
                currentBlock++;

                // Se o número de blocos exceder o limite, criar um novo arquivo
                if (currentBlock >= MAX_BLOCKS) {
                    cerr << "Número máximo de blocos atingido. Criando novo arquivo..." << endl;
                    currentBlock = 0;
                    binaryFile.close();
                    binaryFile.open("data2.bin", ios::binary | ios::out);
                }
            }
        }

        // Se sobrou algum registro no bloco, escrever o restante
        if (recordCount > 0) {
            binaryFile.write(reinterpret_cast<const char*>(block), sizeof(Record) * recordCount);
        }

        csvFile.close();
        binaryFile.close();
        cout << "Arquivo binário gerado com sucesso a partir do CSV." << endl;
    }

    // Inserir um novo registro
    void insertFromInput() {
        Record record;
        cout << "Digite os dados do novo registro:\n";

        cout << "ID: ";
        cin >> record.id;

        // Verificar se o ID já existe
        ifstream binaryFileCheck(binaryFileName, ios::binary);
        if (!binaryFileCheck) {
            cerr << "Erro ao abrir o arquivo binário para verificação." << endl;
            return;
        }

        Record existingRecord;
        while (binaryFileCheck.read(reinterpret_cast<char*>(&existingRecord), sizeof(Record))) {
            if (existingRecord.id == record.id) {
                cout << "Erro: Um registro com o ID " << record.id << " já existe." << endl;
                binaryFileCheck.close();
                return; // Não permite inserir o registro duplicado
            }
        }
        binaryFileCheck.close();

        // Continuar inserindo os outros campos se o ID for único
        cout << "Series Reference: ";
        cin >> record.series_reference;
        cout << "Period: ";
        cin >> record.period;
        cout << "Data Value: ";
        cin >> record.data_value;
        cout << "Status: ";
        cin >> record.status;
        cout << "Units: ";
        cin >> record.units;
        cout << "Magnitude: ";
        cin >> record.magnitude;
        cout << "Subject: ";
        cin >> record.subject;
        cout << "Periodicity: ";
        cin >> record.periodicity;
        cout << "Group: ";
        cin >> record.group;
        cout << "Series Title 1: ";
        cin >> record.series_title_1;
        cout << "Series Title 2: ";
        cin >> record.series_title_2;
        cout << "Series Title 3: ";
        cin >> record.series_title_3;
        cout << "Series Title 4: ";
        cin >> record.series_title_4;
        cout << "Series Title 5: ";
        cin >> record.series_title_5;

        // Encontrar o bloco correto para inserir o registro
        int blockIndex = record.id / MAX_RECORDS_PER_BLOCK;

        // Abrir o arquivo binário para o bloco correto
        ofstream binaryFile(binaryFileName, ios::binary | ios::app);
        if (!binaryFile) {
            cerr << "Erro ao abrir o arquivo binário." << endl;
            return;
        }

        // Buscar a posição correta dentro do bloco
        binaryFile.seekp(blockIndex * MAX_RECORDS_PER_BLOCK * sizeof(Record));

        // Inserir o registro no bloco
        binaryFile.write(reinterpret_cast<const char*>(&record), sizeof(Record));
        binaryFile.close();

        cout << "Novo registro inserido com sucesso!" << endl;
    }

    // Buscar um registro por ID
    void search(int id) {
        ifstream binaryFile(binaryFileName, ios::binary);
        if (!binaryFile) {
            perror("Erro ao abrir o arquivo binário");
            return;
        }

        Record record;
        int blockIndex = id / MAX_RECORDS_PER_BLOCK;
        binaryFile.seekg(blockIndex * MAX_RECORDS_PER_BLOCK * sizeof(Record));

        while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
            if (record.id == id) {
                cout << "Registro encontrado:\n";
                record.print();
                binaryFile.close();
                return;
            }
        }

        cout << "Registro não encontrado." << endl;
        binaryFile.close();
    }

    // Remover um registro por ID
    void remove(int id) {
        ifstream binaryFile(binaryFileName, ios::binary);
        ofstream tempFile("temp.bin", ios::binary);

        if (!binaryFile || !tempFile) {
            cerr << "Erro ao abrir os arquivos." << endl;
            return;
        }

        Record record;
        bool found = false;

        while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
            if (record.id != id) {
                tempFile.write(reinterpret_cast<const char*>(&record), sizeof(Record));
            } else {
                found = true;
            }
        }

        binaryFile.close();
        tempFile.close();

        std::remove(binaryFileName);
        std::rename("temp.bin", binaryFileName);

        if (found) {
            cout << "Registro removido com sucesso." << endl;
        } else {
            cout << "Registro não encontrado." << endl;
        }
    }

    // Imprimir todos os registros
    void printAllRecords() {
        ifstream binaryFile(binaryFileName, ios::binary);
        if (!binaryFile) {
            cerr << "Erro ao abrir o arquivo binário." << endl;
            return;
        }

        Record record;
        cout << "Todos os registros armazenados:\n";
        while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
            record.print();
            cout << "-----------------------" << endl;
        }

        binaryFile.close();
    }
};

int main() {
    const char* csvFileName = "dadosSequenceSet_id.csv";
    const char* binaryFileName = "data.bin";

    SequenceSet set(binaryFileName);

    // Converter CSV para binário
    set.convertCsvToBinary(csvFileName);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Inserir dado\n";
        cout << "2. Remover dado\n";
        cout << "3. Buscar dado\n";
        cout << "4. Sair\n";
        cout << "5. Imprimir todos os dados\n";
        cout << "Escolha: ";
        cin >> choice;

        switch (choice) {
            case 1:
                set.insertFromInput();
                break;
            case 2: {
                int id;
                cout << "Digite o ID do registro a ser removido: ";
                cin >> id;
                set.remove(id);
                break;
            }
            case 3: {
                int id;
                cout << "Digite o ID do registro a ser buscado: ";
                cin >> id;
                set.search(id);
                break;
            }
            case 4:
                cout << "Saindo..." << endl;
                break;
            case 5:
                set.printAllRecords();
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while (choice != 4);

    return 0;
}
