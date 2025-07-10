#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>

using namespace std;

// Classe que representa o grafo de sensores
class SensorGraph {
private:
    // Estrutura de dados para armazenar a lista de adjacência dos sensores
    unordered_map<string, vector<string>> adjacencia;

    // Função auxiliar para fazer busca em profundidade (DFS) recursiva
    void dfs(const string& sensor, set<string>& visitado) {
        visitado.insert(sensor);  // Marca o sensor como visitado
        cout << "Visitando sensor: " << sensor << endl;

        // Visita recursivamente todos os sensores conectados (vizinhos)
        for (const string& vizinho : adjacencia[sensor]) {
            if (visitado.find(vizinho) == visitado.end()) {
                dfs(vizinho, visitado);
            }
        }
    }

public:
    // Adiciona um novo sensor (vértice) à rede
    void adicionarSensor(const string& nome) {
        if (adjacencia.find(nome) == adjacencia.end()) {
            adjacencia[nome] = {};  // Cria uma entrada vazia para o sensor
            cout << "Sensor adicionado: " << nome << endl;
        }
    }

    // Conecta dois sensores (arestas não direcionadas)
    void conectarSensores(const string& s1, const string& s2) {
        adjacencia[s1].push_back(s2);  // Adiciona s2 como vizinho de s1
        adjacencia[s2].push_back(s1);  // Adiciona s1 como vizinho de s2
        cout << "Conectado: " << s1 << " <--> " << s2 << endl;
    }

    // Mostra a estrutura completa da rede (lista de adjacência)
    void mostrarConexoes() const {
        cout << "\n--- Rede de Sensores ---\n";
        for (const auto& par : adjacencia) {
            cout << par.first << ": ";
            for (const auto& vizinho : par.second) {
                cout << vizinho << " ";
            }
            cout << endl;
        }
    }

    // Verifica se todos os sensores estão conectados, iniciando a partir de um sensor inicial
    void verificarConectividade(const string& sensorInicial) {
        set<string> visitado;  // Conjunto para armazenar sensores visitados
        cout << "\n--- Verificando conectividade a partir de " << sensorInicial << " ---\n";
        dfs(sensorInicial, visitado);  // Inicia a DFS

        // Compara o número de sensores visitados com o total existente
        if (visitado.size() == adjacencia.size()) {
            cout << " A rede de sensores está conectada.\n";
        } else {
            cout << " A rede de sensores está desconectada. Sensores não alcançados:\n";
            for (const auto& par : adjacencia) {
                if (visitado.find(par.first) == visitado.end()) {
                    cout << "- " << par.first << endl;
                }
            }
        }
    }
};

// Função principal (main) para demonstrar o uso da classe SensorGraph
int main() {
    SensorGraph rede;

    // Adiciona sensores à rede
    rede.adicionarSensor("Sensor_A");
    rede.adicionarSensor("Sensor_B");
    rede.adicionarSensor("Sensor_C");
    rede.adicionarSensor("Sensor_D");
    rede.adicionarSensor("Sensor_E");

    // Conecta os sensores entre si
    rede.conectarSensores("Sensor_A", "Sensor_B");
    rede.conectarSensores("Sensor_B", "Sensor_C");
    rede.conectarSensores("Sensor_C", "Sensor_D");
    // Sensor_E fica propositalmente desconectado para simular um caso de falha

    // Mostra as conexões atuais entre os sensores
    rede.mostrarConexoes();

    // Verifica se a rede é totalmente conectada a partir de Sensor_A
    rede.verificarConectividade("Sensor_A");

    return 0;
}
