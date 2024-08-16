#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>

struct PointVar {
    double x;
    double y;
};

double computeDistance(const PointVar& p1, const PointVar& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::floor(std::sqrt(dx * dx + dy * dy));
}

bool verifyTriangleInequality(const std::vector<std::vector<double>>& graph) {
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (graph[i][j] + graph[j][k] < graph[i][k]) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::vector<PointVar> generateRandomPoints(int numPoints, double maxCoordinate) {
    std::vector<PointVar> points;
    std::srand(std::time(0));
    for (int i = 0; i < numPoints; i++) {
        PointVar p;
        p.x = static_cast<double>(std::rand()) / RAND_MAX * maxCoordinate;
        p.y = static_cast<double>(std::rand()) / RAND_MAX * maxCoordinate;
        points.push_back(p);
    }
    return points;
}

std::vector<std::vector<double>> createGraph(const std::vector<PointVar>& points) {
    int n = points.size();
    std::vector<std::vector<double>> graph(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = computeDistance(points[i], points[j]);
            graph[i][j] = dist;
            graph[j][i] = dist;
        }
    }
    return graph;
}

void printGraph(const std::vector<std::vector<double>>& graph, int numPoints) {
    std::ofstream samplecase("sample.txt");
    samplecase << numPoints<< std::endl;
    samplecase << numPoints*(numPoints - 1)/2 << std::endl;
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = graph[i][j];
            std::cout << "Distance between Vertex " << i << " and Vertex " << j << ": " << dist << std::endl;
            samplecase << i << " "<< j << " "<< dist << std::endl;
        }
    }
    samplecase.close();

}

void updateGraph(std::vector<std::vector<double>>& graph) {
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (graph[i][j] + graph[j][k] < graph[i][k]) {
                    // Update the distance to satisfy the triangle inequality
                    graph[i][k] = graph[i][j] + graph[j][k];
                }
            }
        }
    }
}

int main() {
    // Total number of vertices
    int numPoints = 50; 

    // max coordinate value
    double maxCoordinate = 100; 

    // random point generation
    std::vector<PointVar> points = generateRandomPoints(numPoints, maxCoordinate);

    // generate graph using Euclidean distance as weights
    std::vector<std::vector<double>> graph = createGraph(points);

    // verify if the generated graph satisfies the triangle inequality
    if (verifyTriangleInequality(graph)) {
        std::cout << "The generated graph satisfies the triangle inequality." << std::endl;
    } else {
        std::cout << "The generated graph does not satisfy the triangle inequality." << std::endl;

        // Update the graph to satisfy the triangle inequality
        updateGraph(graph);

        std::cout << "Updated graph satisfying triangle inequality." << std::endl;
    }

    printGraph(graph, numPoints);

    return 0;
}
