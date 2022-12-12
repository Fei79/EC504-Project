#ifndef EK_HPP
#define EK_HPP

#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <set>
#include <stack>
#include <assert.h>

using namespace std;

class EK {
    public:
        EK(vector<map<int, array<int,2>>> flow_graph);
        
        int graph_source;
        int graph_sink;
        vector<int> segmentedImage;
        vector<map<int, array<int,2>>> image_flow_graph;

        int initiate_algorithm();
        void getAugmentingPaths(vector<int>& path, set<int>& accessibleNodes);
        void getFlowInAugmentingPath(vector<int>& path, int& flow_p);
        void augmentFlow(vector<int>& path, int& flow_p);
        void getPath(vector<int>& path,const std::map<int,int>& visited);
        void makeSegmentation(set<int> accessibleNodes);
};

#endif

EK::EK(vector<map<int, array<int, 2>>> flow_graph) {
    image_flow_graph = flow_graph;
    segmentedImage.resize(flow_graph.size());
    graph_source = flow_graph.size() - 2;
    graph_sink = flow_graph.size() - 1;
    fill(segmentedImage.begin(), segmentedImage.end(), false);
}

int EK::initiate_algorithm() {
    int flow = 0;
    int flow_p = 0;
    int iter = 0;
    while (true) {
        vector<int> path;
        set<int> accessibleNodes;
        getAugmentingPaths(path, accessibleNodes);
        if (path.size() == 0) {
            makeSegmentation(accessibleNodes);
            break;
        }
        else {
            getFlowInAugmentingPath(path, flow_p);
            augmentFlow(path, flow_p);
            flow += flow_p;
        }
        iter++;
    }
    return iter;
}

void EK::getAugmentingPaths(vector<int>& path, set<int>& accessibleNodes) {
    stack<int> s;
    map<int, int> visited;

    s.push(graph_source);
    visited.insert({ graph_source, graph_source });

    while (!s.empty()) {

        int current = s.top();
        s.pop();
        if (current == graph_sink) {
            path.reserve(visited.size());
            getPath(path, visited);
            break;
        }

        for (auto& next_node_values : image_flow_graph[current]) {
            if (visited.find(next_node_values.first) == visited.end()) {
                if ((next_node_values.second[0] - next_node_values.second[1]) > 0) {
                    s.push(next_node_values.first);
                    visited.emplace(next_node_values.first, current);
                }
            }
        }
    }
    for (auto& visited_node : visited) {
        accessibleNodes.insert(visited_node.first);
    }
}

void EK::getPath(vector<int>& path, const std::map<int, int>& visited) {
    int next_node = graph_sink;
    path.emplace_back(next_node);
    while (next_node != graph_source) {
        auto temp = visited.find(next_node);
        next_node = temp->second;
        path.emplace_back(next_node);
    }
}

void EK::getFlowInAugmentingPath(vector<int>& path, int& flow_p) {
    assert(path.front() == graph_sink && path.back() == graph_source);
    flow_p = image_flow_graph[path[path.size() - 1]][path[path.size() - 2]][0];
    for (int i = path.size() - 1; i > 0; --i) {
        int u = path[i];
        int v = path[i - 1];
        flow_p = std::min(flow_p, image_flow_graph[u][v][0] - image_flow_graph[u][v][1]);
    }
}

void EK::augmentFlow(vector<int>& path, int& flow_p) {
    int i = path.size() - 1;
    while (path[i] != graph_sink) {
        int u = path[i];
        int v = path[i - 1];
        image_flow_graph[u][v][1] += flow_p;
        image_flow_graph[v][u][1] -= flow_p;
        i -= 1;
    }
}

void EK::makeSegmentation(set<int> accessibleNodes) {
    for (auto node : accessibleNodes) {
        segmentedImage[node] = true;
    }
}