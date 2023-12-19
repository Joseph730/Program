#include <iostream>
using namespace std;
#include <cstdlib>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
//графы
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
void runGraphOperations() {
    int numVertices, numEdges;
    bool isDirected;
    setlocale(LC_ALL, "Rus");
    cout << "Введите количество вершин: ";
    cin >> numVertices;
    cout << "Введите количество рёбер: ";
    cin >> numEdges;
    cout << "Граф ориентированный? (1 - да, 0 - нет): ";
    cin >> isDirected;
    pair<int, int>* edges = new pair<int, int>[numEdges];
    cout << "Введите пары вершин для рёбер (например, 0 1 для ребра 0->1):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = make_pair(u, v);
    }
    int** adjacencyList = createAdjacencyList(numVertices, edges, numEdges, isDirected);
    int** adjacencyMatrix = createAdjacencyMatrix(numVertices, adjacencyList, numEdges);
    int** incidenceMatrix = createIncidenceMatrix(numVertices, edges, numEdges, isDirected);

    // Вывод списка смежности
    cout << "Список смежности:" << endl;
    for (int u = 0; u < numVertices; ++u) {
        cout << "Вершина " << u << ": ";
        for (int v = 0; v < numVertices; ++v) {
            if (adjacencyList[u][v] == 1) {
                cout << v << " ";
            }
        }
        cout << endl;
    }

    // Вывод матрицы смежности
    cout << "Матрица смежности:" << endl;
    for (int u = 0; u < numVertices; ++u) {
        for (int v = 0; v < numVertices; ++v) {
            cout << adjacencyMatrix[u][v] << " ";
        }
        cout << endl;
    }

    // Вывод матрицы инцидентности
    cout << "Матрица инцидентности:" << endl;
    for (int u = 0; u < numVertices; ++u) {
        for (int i = 0; i < numEdges; ++i) {
            cout << incidenceMatrix[u][i] << " ";
        }
        cout << endl;
    }

    // Освобождение памяти
    for (int i = 0; i < numVertices; ++i) {
        delete[] adjacencyList[i];
        delete[] adjacencyMatrix[i];
        delete[] incidenceMatrix[i];
    }
    delete[] adjacencyList;
    delete[] adjacencyMatrix;
    delete[] incidenceMatrix;
    delete[] edges;
}
//бинарное дерево поиска
struct Node {
    int value;
    Node* left;
    Node* right;
};
class BinaryTree {
private:
    Node* root;
    Node* createNode(int value) {
        Node* newNode = new Node();
        if (newNode) {
            newNode->value = value;
            newNode->left = newNode->right = nullptr;
        }
        return newNode;
    }
    Node* insertNode(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return createNode(value);
        }
        if (value < currentNode->value) {
            currentNode->left = insertNode(currentNode->left, value);
        }
        else if (value > currentNode->value) {
            currentNode->right = insertNode(currentNode->right, value);
        }
        return currentNode;
    }
    Node* minValueNode(Node* currentNode) {
        Node* current = currentNode;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    Node* deleteNode(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return currentNode;
        }
        if (value < currentNode->value) {
            currentNode->left = deleteNode(currentNode->left, value);
        }
        else if (value > currentNode->value) {
            currentNode->right = deleteNode(currentNode->right, value);
        }
        else {
            if (currentNode->left == nullptr) {
                Node* temp = currentNode->right;
                delete currentNode;
                return temp;
            }
            else if (currentNode->right == nullptr) {
                Node* temp = currentNode->left;
                delete currentNode;
                return temp;
            }
            Node* temp = minValueNode(currentNode->right);
            currentNode->value = temp->value;
            currentNode->right = deleteNode(currentNode->right, temp->value);
        }
        return currentNode;
    }
    void inorderTraversal(Node* currentNode) {
        if (currentNode != nullptr) {
            inorderTraversal(currentNode->left);
            cout << currentNode->value << " ";
            inorderTraversal(currentNode->right);
        }
    }
    void preorderTraversal(Node* currentNode) {
        if (currentNode != nullptr) {
            cout << currentNode->value << " ";
            preorderTraversal(currentNode->left);
            preorderTraversal(currentNode->right);
        }
    }
    void postorderTraversal(Node* currentNode) {
        if (currentNode != nullptr) {
            postorderTraversal(currentNode->left);
            postorderTraversal(currentNode->right);
            cout << currentNode->value << " ";
        }
    }
public:
    BinaryTree() : root(nullptr) {}
    void insert(int value) {
        root = insertNode(root, value);
    }
    void remove(int value) {
        root = deleteNode(root, value);
    }
    void inorder() {
        inorderTraversal(root);
    }
    void preorder() {
        preorderTraversal(root);
    }
    void postorder() {
        postorderTraversal(root);
    }
    void breadthFirst() {
        if (root == nullptr)
            return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* currentNode = q.front();
            cout << currentNode->value << " ";
            q.pop();
            if (currentNode->left != nullptr)
                q.push(currentNode->left);
            if (currentNode->right != nullptr)
                q.push(currentNode->right);
        }
    }
};

void binaryTreeTraversal() {
    BinaryTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);
    cout << "Inorder Traversal: ";
    bst.inorder();
    cout << endl;
    cout << "Preorder Traversal: ";
    bst.preorder();
    cout << endl;
    cout << "Postorder Traversal: ";
    bst.postorder();
    cout << endl;
    cout << "Breadth First Traversal: ";
    bst.breadthFirst();
    cout << endl;
    bst.remove(20);
    bst.remove(30);
    cout << "Inorder Traversal after removing nodes: ";
    bst.inorder();
    cout << endl;
}
//Метод сжатия информации Хаффмана
struct HuffmanNode {
    char data; // символ
    int frequency; // частота
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator() (HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* buildHuffmanTree(map<char, int> frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto entry : frequencies) {
        pq.push(new HuffmanNode(entry.first, entry.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();
        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, string code, map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }
    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

void huffmanCode() {
    map<char, int> frequencies;
    string inputString = "Hello, World!";
    cout << inputString << endl;
    // Вычисление частот символов во входной строке
    for (char c : inputString) {
        frequencies[c]++;
    }

    // Построение дерева Хаффмана
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Генерация кодов Хаффмана для символов
    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Вывод символов и их кодов Хаффмана
    cout << "Символ\tЧастота\tКод Хаффмана" << endl;
    for (auto entry : huffmanCodes) {
        cout << entry.first << "\t" << frequencies[entry.first] << "\t" << entry.second << endl;
    }
}

//Метод сжатия информации Шеннона-Фано
struct Node1 {
    char data;
    float probability;
    string code;
    Node1* left, * right;
};

void shannonFano(std::vector<Node1>& nodes, int start, int end) {
    if (start >= end - 1) {
        return;
    }
    float totalProb = 0;
    for (int i = start; i < end; ++i) {
        totalProb += nodes[i].probability;
    }
    float currProb = 0;
    int splitIndex = start;
    float minDiff = std::numeric_limits<float>::max();
    for (int i = start; i < end; ++i) {
        currProb += nodes[i].probability;
        float diff = std::abs(currProb - (totalProb - currProb));
        if (diff < minDiff) {
            minDiff = diff;
            splitIndex = i;
        }
    }
    for (int i = start; i < end; ++i) {
        if (i <= splitIndex) {
            nodes[i].code += "0";
        }
        else {
            nodes[i].code += "1";
        }
    }
    shannonFano(nodes, start, splitIndex + 1);
    shannonFano(nodes, splitIndex + 1, end);
}
void shannonFanoEncoding() {
    std::vector<Node1> nodes;
    // Добавим свои данные о вероятностях и символах вектора nodes
    nodes.push_back({ 'a', 0.3, "", nullptr, nullptr });
    nodes.push_back({ 'b', 0.2, "", nullptr, nullptr });
    nodes.push_back({ 'c', 0.25, "", nullptr, nullptr });
    nodes.push_back({ 'd', 0.25, "", nullptr, nullptr });
    nodes.push_back({ 'e', 0.35, "", nullptr, nullptr });
    nodes.push_back({ 'f', 0.15, "", nullptr, nullptr });
    nodes.push_back({ 'g', 0.4, "", nullptr, nullptr });
    shannonFano(nodes, 0, nodes.size());
    cout << "Символ\tВероятность\tКод" << std::endl;
    for (const auto& node : nodes) {
        cout << node.data << "\t" << node.probability << "\t\t" << node.code << std::endl;
    }
}
//LZ77
void lz77() {
    string dictionary, buffer, input;
    int i = 0;
    int CheckCounter = 0;
    int Skip = 0;
    int MatchIndex = 0;
    bool MatchFound = false;

    setlocale(LC_ALL, "ru");
    dictionary.resize(8);
    buffer.resize(5);
    input = "КРАСНАЯ КРАСКА";

    for (int i = 0; i < buffer.length() - 1; i++) {
        input += " ";
    }

    dictionary = "********";

    for (int i = 0; i < 5; i++) {
        buffer[i] = input[i];
    }

    cout << "Словарь\t" << "Буффер\t" << "Код" << endl;
    cout << dictionary << "\t" << buffer << "  ";

    for (int i = 0; i < input.length() - 5; i++) {
        MatchFound = false;

        for (int Check = 0; Check < dictionary.length(); Check++) {
            if (dictionary[Check] == buffer[0]) {
                MatchFound = true;
                if (Skip == 0) {
                    MatchIndex = Check;
                }
            }
        }

        if (i == (input.length() - 6)) {
            MatchFound = false;
        }

        if (MatchFound == true) {
            Skip++;
        }

        for (int step = 0; step < 7; step++) {
            dictionary[step] = dictionary[step + 1];
            if (step == 6) {
                dictionary[step + 1] = buffer[0];
            }
        }

        if (MatchFound == false) {
            cout << MatchIndex << " " << Skip << " " << buffer[0] << endl;
            cout << dictionary << "\t";
            Skip = 0;
            MatchIndex = 0;
        }

        for (int step = 0; step < 4; step++) {
            buffer[step] = buffer[step + 1];
            if (step == 3) {
                buffer[step + 1] = input[i + 5];
                if (MatchFound == false) {
                    cout << buffer << "  ";
                }
            }
        }
    }

    cout << "" << 0 << " " << 0 << " " << buffer[0];
}

//LZ78
void lz78() {
    setlocale(LC_ALL, "ru");
    string input, buffer;
    input = "КИБЕРНЕТИКИ";
    buffer.resize(input.length());
    int Count = 1;
    cout << "Словарь\tКод\tПозиция в словаре" << endl;
    cout << "\t\t0" << endl;
    for (int i = 0; i < input.length(); i++) {
        char Match = ' ';
        int MatchIndex = -1;
        for (int Check = 0; Check < buffer.length(); Check++) {
            if (input[i] == buffer[Check]) {
                MatchIndex = Check;
                Match = buffer[Check];
                break;
            }
        }
        if (MatchIndex == -1) {
            buffer[i] = input[i];
            cout << input[i] << "\t <0, " << input[i] << ">\t" << Count << endl;
            Count++;
        }
        else {
            i++;
            cout << Match << input[i] << "\t <" << MatchIndex + 1 << ", " << input[i] << ">\t " << Count << endl;
            Count++;
        }
    }
}
//lzss
void lzss() {
    string dictionary, buffer, input;
    int i = 0;
    int CheckCounter = 0;
    int Skip = 0;
    int Byte = 8;
    int MatchIndex = 0;
    bool MatchIndexFound;
    bool MatchFound;
    setlocale(LC_ALL, "ru");
    dictionary.resize(8);
    buffer.resize(5);
    input = "КРАСНАЯ КРАСКА";
    dictionary = "********";
    for (int i = 0; i < buffer.length(); i++) {
        input += " ";
    }
    for (int i = 0; i < 5; i++) {
        buffer[i] = input[i];
    }
    cout << "Словарь\t" << "Буффер\t" << "Код\t" << "Длина кода" << endl;
    cout << dictionary << "\t" << buffer << "  " << "0 " << buffer[0] << " " << Byte + 1 << endl;;
    for (int i = 0; i < input.length() - 6; i++) {
        Byte = 8;
        MatchIndex = -1;
        MatchIndexFound = false;
        for (int step = 0; step < 7; step++) {
            dictionary[step] = dictionary[step + 1];
            if (step == 6) {
                dictionary[step + 1] = buffer[0];
            }
        }
        for (int step = 0; step < 4; step++) {
            buffer[step] = buffer[step + 1];
            if (step == 3) {
                buffer[step + 1] = input[i + 5];
            }
        }
        if (buffer[0] != dictionary[0]) {
            cout << dictionary << "\t" << buffer << "  ";
            MatchFound = false;
            for (int Check1 = 0; Check1 < dictionary.length(); Check1++) {
                if (dictionary[Check1] == buffer[0]) {
                    MatchIndex = Check1;
                    break;
                }
            }
            if (MatchIndex != -1)
                cout << "1<" << MatchIndex << " " << "1> " << Byte - 1 << endl;
            else cout << "0 " << buffer[0] << " " << Byte + 1 << endl;
        }
        if (buffer[0] == dictionary[0] && MatchFound == false) {
            for (int Check1 = 0; Check1 < buffer.length(); Check1++)
            {
                if (buffer[Check1] == dictionary[Check1])
                    Skip++;
                else break;
            }
            MatchFound = true;
            MatchIndex = 0;
            cout << dictionary << "\t" << buffer << "  1<" << MatchIndex << " " << Skip << "> " << Byte - 1 << endl;
            Skip = 0;
        }
    }
}
int main()
{
    setlocale(LC_ALL, "ru");
    cout << "Теория информации, 5 семестр\n";
    cout << "-------------------------------------------------------------------\n";
    while (1)
    {
        cout << "Введите номер программы:\n\t 1. Графы (пр.1)\n\t 2. Бинарное дерево поиска(пр.2)\n\t 3. Метод сжатия информации Хаффмана(пр.3-1)\n\t 4. Метод сжатия информации Шеннон-Фано(пр. 3-2)\n\t 5. LZ77(пр.4-1)\n\t 6. LZ78(пр.4-2)\n\t 7. LZSS(пр.4-3)\n\t";
        int num;
        cin >> num;
        switch (num)
        {
        case 1:
            runGraphOperations();
            cout << "-------------------------------------------------------------------\n";
            break;
        case 2:
            binaryTreeTraversal();
            cout << "-------------------------------------------------------------------\n";
            break;
        case 3:
            huffmanCode();
            cout << "-------------------------------------------------------------------\n";
            break;
        case 4:
            shannonFanoEncoding();
            cout << "-------------------------------------------------------------------\n";
            break;
        case 5:
            lz77();
            cout << "-------------------------------------------------------------------\n";
            break;
        case 6:
            lz78();
            cout << "-------------------------------------------------------------------\n";
            break;
        case 7:
            lzss();
            cout << "-------------------------------------------------------------------\n";
            break;
        default:
            cout << "Неверный номер, попробуйте ещё раз!";
            cout << "-------------------------------------------------------------------\n";
            break;
        }
    }
    return 0;
}
