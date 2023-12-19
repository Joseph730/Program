#include <iostream>
using namespace std;

int** createAdjacencyList(int numVertices, const pair<int, int>* edges, int numEdges, bool isDirected) {
    int** adjacencyList = new int* [numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjacencyList[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            adjacencyList[i][j] = 0;
        }
    }
    for (int i = 0; i < numEdges; ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        adjacencyList[u][v] = 1;
        if (!isDirected) {
            adjacencyList[v][u] = 1;
        }
    }
    return adjacencyList;
}

int** createAdjacencyMatrix(int numVertices, int** adjacencyList, int numEdges) {
    int** adjacencyMatrix = new int* [numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjacencyMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            adjacencyMatrix[i][j] = adjacencyList[i][j];
        }
    }
    return adjacencyMatrix;
}

int** createIncidenceMatrix(int numVertices, const pair<int, int>* edges, int numEdges, bool isDirected) {
    int** incidenceMatrix = new int* [numVertices];
    for (int i = 0; i < numVertices; ++i) {
        incidenceMatrix[i] = new int[numEdges];
        for (int j = 0; j < numEdges; ++j) {
            incidenceMatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < numEdges; ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        if (isDirected) {
            incidenceMatrix[u][i] = -1;
            incidenceMatrix[v][i] = 1;
        }
        else {
            incidenceMatrix[u][i] = 1;
            incidenceMatrix[v][i] = 1;
        }
    }
    return incidenceMatrix;
}

int main() {
    int numVertices, numEdges;
    bool isDirected;
    setlocale(LC_ALL, "Rus");
    cout << "������� ���������� ������: ";
    cin >> numVertices;
    cout << "������� ���������� ����: ";
    cin >> numEdges;
    cout << "���� ���������������? (1 - ��, 0 - ���): ";
    cin >> isDirected;
    pair<int, int>* edges = new pair<int, int>[numEdges];
    cout << "������� ���� ������ ��� ���� (��������, 0 1 ��� ����� 0->1):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = make_pair(u, v);
    }
    int** adjacencyList = createAdjacencyList(numVertices, edges, numEdges, isDirected);
    int** adjacencyMatrix = createAdjacencyMatrix(numVertices, adjacencyList, numEdges);
    int** incidenceMatrix = createIncidenceMatrix(numVertices, edges, numEdges, isDirected);

    // ����� ������ ���������
    cout << "������ ���������:" << endl;
    for (int u = 0; u < numVertices; ++u) {
        cout << "������� " << u << ": ";
        for (int v = 0; v < numVertices; ++v) {
            if (adjacencyList[u][v] == 1) {
                cout << v << " ";
            }
        }
        cout << endl;
    }

    // ����� ������� ���������
    cout << "������� ���������:" << endl;
    for (int u = 0; u < numVertices; ++u) {
        for (int v = 0; v < numVertices; ++v) {
            cout << adjacencyMatrix[u][v] << " ";
        }
        cout << endl;
    }

    // ����� ������� �������������
    cout << "������� �������������:" << endl;
    for (int u = 0; u < numVertices; ++u) {
        for (int i = 0; i < numEdges; ++i) {
            cout << incidenceMatrix[u][i] << " ";
        }
        cout << endl;
    }

    // ������������ ������
    for (int i = 0; i < numVertices; ++i) {
        delete[] adjacencyList[i];
        delete[] adjacencyMatrix[i];
        delete[] incidenceMatrix[i];
    }
    delete[] adjacencyList;
    delete[] adjacencyMatrix;
    delete[] incidenceMatrix;
    delete[] edges;

    return 0;
}