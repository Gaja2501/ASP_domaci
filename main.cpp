#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Graph
{
private:
    int numberOfNodes;
    int numberOfEdges;
    string *nodesNames;
    double **matrix;

public:
    Graph(string fileName)
    {
        // open file
        ifstream file(fileName);
        if (!file.is_open())
        {
            cout << "Error opening file";
            return;
        }

        // read file
        string line;

        getline(file, line);
        numberOfNodes = stoi(line);

        getline(file, line);
        numberOfEdges = stoi(line);

        // alocate matrix
        matrix = new double *[numberOfNodes];
        for (int i = 0; i < numberOfNodes; i++)
        {
            matrix[i] = new double[numberOfNodes];
        }

        for (int i = 0; i < numberOfNodes; i++)
        {
            for (int j = 0; j < numberOfNodes; j++)
            {
                matrix[i][j] = -1;
            }
        }

        // make arrray of names for nodes
        string allNodesNames;
        getline(file, allNodesNames);

        nodesNames = new string[numberOfNodes];

        int index = 0;

        // add nodes to array
        for (int i = 0; i < allNodesNames.length() - 1; i++)
        {
            if (allNodesNames[i] != ' ')
            {
                nodesNames[index] += allNodesNames[i];
            }
            else
            {
                index++;
            }
        }

        // add edges to matrix (node1 node2 weight)
        for (int i = 0; i < numberOfEdges; i++)
        {
            getline(file, line);
            string node1;
            string node2;
            double weight = -1;
            for (int j = 0; j < line.length(); j++)
            {
                if (line[j] != ' ')
                {
                    node1 += line[j];
                }
                else
                {
                    for (int k = j + 1; k < line.length(); k++)
                    {
                        if (line[k] != ' ')
                        {
                            node2 += line[k];
                        }
                        else
                        {
                            weight = stod(line.substr(k + 1, line.length()));
                            break;
                        }
                    }
                    break;
                }
            }

            for (int i = 0; i < numberOfNodes; i++)
            {
                if (nodesNames[i] == node1)
                {
                    for (int j = 0; j < numberOfNodes + 1; j++)
                    {
                        if (nodesNames[j] == node2)
                        {
                            matrix[i][j] = weight;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        file.close();
    }

    Graph()
    {
        string line;

        cout << "Enter number of nodes: ";
        cin >> numberOfNodes;

        cout << "Enter number of edges: ";
        cin >> numberOfEdges;

        // alocate matrix
        matrix = new double *[numberOfNodes];
        for (int i = 0; i < numberOfNodes; i++)
        {
            matrix[i] = new double[numberOfNodes];
        }

        for (int i = 0; i < numberOfNodes; i++)
        {
            for (int j = 0; j < numberOfNodes; j++)
            {
                matrix[i][j] = -1;
            }
        }

        // make arrray of names for nodes

        nodesNames = new string[numberOfNodes];

        // add nodes to array
        for (int i = 0; i < numberOfNodes; i++)
        {
            cin >> nodesNames[i];
        }

        // add edges to matrix (node1 node2 weight)
        for (int i = 0; i < numberOfEdges; i++)
        {
            string node1;
            string node2;
            double weight = -1;
            cin >> node1 >> node2 >> weight;

            for (int i = 0; i < numberOfNodes; i++)
            {
                if (nodesNames[i] == node1)
                {
                    for (int j = 0; j < numberOfNodes + 1; j++)
                    {
                        if (nodesNames[j] == node2)
                        {
                            matrix[i][j] = weight;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }

    ~Graph()
    {
        delete[] nodesNames;
        for (int i = 0; i < numberOfNodes; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void printMatrix()
    {
        for (int i = 0; i < numberOfNodes; i++)
        {
            for (int j = 0; j < numberOfNodes; j++)
            {
                if (matrix[i][j] == -1)
                {
                    cout << "  X   ";
                }
                else
                {
                    if (int(matrix[i][j] * 100) % 10 == 0)
                    {
                        cout << matrix[i][j] << "0  ";
                    }
                    else
                    {
                        cout << matrix[i][j] << "  ";
                    }
                }
            }
            cout << endl;
        }
    }

    void addNode(string newNode)
    {
        string *newNodesNames = new string[numberOfNodes + 1];
        for (int i = 0; i < numberOfNodes; i++)
        {
            newNodesNames[i] = nodesNames[i];
        }
        newNodesNames[numberOfNodes] = newNode;
        delete[] nodesNames;
        numberOfNodes++;
        nodesNames = newNodesNames;

        double **newMatrix = new double *[numberOfNodes];
        for (int i = 0; i < numberOfNodes - 1; i++)
        {
            newMatrix[i] = new double[numberOfNodes];
            for (int j = 0; j < numberOfNodes - 1; j++)
            {
                newMatrix[i][j] = matrix[i][j];
            }
            newMatrix[i][numberOfNodes - 1] = -1;
        }
        newMatrix[numberOfNodes - 1] = new double[numberOfNodes];
        for (int i = 0; i < numberOfNodes; i++)
        {
            newMatrix[numberOfNodes - 1][i] = -1;
        }
        delete[] matrix;
        matrix = newMatrix;
    }

    void printNodes()
    {
        for (int i = 0; i < numberOfNodes; i++)
        {
            cout << nodesNames[i] << " ";
        }
        cout << endl;
    }

    void deleteNode(string name)
    {
        int index = -1;
        for (int i = 0; i < numberOfNodes; i++)
        {
            if (nodesNames[i] == name)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "Node not found" << endl;
            return;
        }

        string *newNodesNames = new string[numberOfNodes - 1];
        for (int i = 0; i < index; i++)
        {
            newNodesNames[i] = nodesNames[i];
        }
        for (int i = index; i < numberOfNodes - 1; i++)
        {
            newNodesNames[i] = nodesNames[i + 1];
        }
        delete[] nodesNames;
        numberOfNodes--;
        nodesNames = newNodesNames;

        double **newMatrix = new double *[numberOfNodes];
        for (int i = 0; i < index; i++)
        {
            newMatrix[i] = new double[numberOfNodes];
            for (int j = 0; j < index; j++)
            {
                newMatrix[i][j] = matrix[i][j];
            }
            for (int j = index; j < numberOfNodes; j++)
            {
                newMatrix[i][j] = matrix[i][j + 1];
            }
        }
        for (int i = index; i < numberOfNodes; i++)
        {
            newMatrix[i] = new double[numberOfNodes];
            for (int j = 0; j < index; j++)
            {
                newMatrix[i][j] = matrix[i + 1][j];
            }
            for (int j = index; j < numberOfNodes; j++)
            {
                newMatrix[i][j] = matrix[i + 1][j + 1];
            }
        }
        delete[] matrix;
        matrix = newMatrix;
    }

    void addEdge(string node1, string node2, double weight)
    {
        int index1 = -1;
        int index2 = -1;
        if (weight < 0 || weight > 1)
        {
            cout << "Weight must be between 0.0 and 1.0" << endl;
            return;
        }
        for (int i = 0; i < numberOfNodes; i++)
        {
            if (nodesNames[i] == node1)
            {
                index1 = i;
            }
            if (nodesNames[i] == node2)
            {
                index2 = i;
            }
        }
        if (index1 == -1 || index2 == -1)
        {
            cout << "Node not found" << endl;
            return;
        }
        matrix[index1][index2] = weight;
    }

    void deleteEdge(string node1, string node2)
    {
        int index1 = -1;
        int index2 = -1;
        for (int i = 0; i < numberOfNodes; i++)
        {
            if (nodesNames[i] == node1)
            {
                index1 = i;
            }
            if (nodesNames[i] == node2)
            {
                index2 = i;
            }
        }
        if (index1 == -1 || index2 == -1)
        {
            cout << "Node not found" << endl;
            return;
        }
        matrix[index1][index2] = -1;
    }

    void findSimilar(string word, int k) {
        int index = -1;
        for (int i = 0; i < numberOfNodes; i++)
        {
            if (nodesNames[i] == word)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "Node not found" << endl;
            return;
        }

        double *similarities = new double[numberOfNodes];
        string *similaritiesNames = new string[numberOfNodes];

        for (int i = 0; i < numberOfNodes; i++)
        {
            similarities[i] = matrix[index][i];
            similaritiesNames[i] = nodesNames[i];
        }

        for (int i = 0; i < numberOfNodes; i++)
        {
            for (int j = 0; j < numberOfNodes - 1; j++)
            {
                if (similarities[j] < similarities[j + 1])
                {
                    double temp = similarities[j];
                    similarities[j] = similarities[j + 1];
                    similarities[j + 1] = temp;
                    string tempName = similaritiesNames[j];
                    similaritiesNames[j] = similaritiesNames[j + 1];
                    similaritiesNames[j + 1] = tempName;
                }
            }
        }

        for (int i = 0; i < k; i++)
        {
            if (similarities[i] == -1)
            {
                break;
            }
            cout << similaritiesNames[i] << " ";
        }
        
        cout << endl;

        delete[] similarities;
        delete[] similaritiesNames;
    }

    void findClosestPath(string begin, string end) {

    }
};

int main()
{
    Graph graph("graf1.txt");

    // Graph graph2;

    //graph2.printMatrix();

    // graph.addNode("D");

    // graph.deleteNode("ETF");

    // graph.addEdge("algoritam", "podaci", 0.4);

    // graph.deleteEdge("artikl", "proizvod");

    // graph.printNodes();

    graph.printMatrix();

    // graph.findSimilar("proizvod", 5);

    return 0;
}