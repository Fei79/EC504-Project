#ifndef IG_HPP
#define IG_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <time.h>

using namespace std;

class IG {
    
    public:
        IG(string imgPath);
        cv::Mat image;
        vector<map<int, array<int,2>>> flow_graph;
        array<int, 2> sourceNode;
        array<int, 2> sinkNode;
        int graph_source;
        int graph_sink;
        void Image_To_Flow_Graph(int src_x, int src_y, int sink_x, int sink_y);
        float Weight(int i, int j, int u, int v);
        void addEdge(int node1, int node2, int edge_weight);
        void addInterPixelEdges(int i, int j);
        void makeEdge(int i, int j, int u, int v);
        bool BoundryCheck(int i, int j);
        void saveImage(vector<int> segmentedImage, string img_output);
};
#endif


IG::IG(string imgPath) {
    image = cv::imread(imgPath, 0);

}

void IG::Image_To_Flow_Graph(int src_x, int src_y, int sink_x, int sink_y) {

    int img_rows = image.rows;
    int img_cols = image.cols;
    int no_of_vertex = (img_rows * img_cols) + 2;
    graph_source = no_of_vertex - 2;
    graph_sink = no_of_vertex - 1;
    flow_graph.resize((image.rows * image.cols) + 2);
    sourceNode[0] = src_x;
    sourceNode[1] = src_y;
    sinkNode[0] = sink_x;
    sinkNode[1] = sink_y;
    for (int i = 0; i < img_rows; i++) {
        for (int j = 0; j < img_cols; j++) {
            float source_to_pixel_weight = Weight(i, j, sourceNode[0], sourceNode[1]);
            int pixelLinearValue = i * img_cols + j;
            addEdge(graph_source, pixelLinearValue, source_to_pixel_weight);
            float sink_to_pixel_weight = Weight(i, j, sinkNode[0], sinkNode[1]);
            addEdge(pixelLinearValue, graph_sink, sink_to_pixel_weight);
            addInterPixelEdges(i, j);
        }
    }
}

float IG::Weight(int i, int j, int u, int v) {
    int sigma = 30;
    int intensity_difference = std::abs(image.at<uint8_t>(i, j) - image.at<uint8_t>(u, v));
    float w = 100 * exp(-pow(intensity_difference, 2) / (2 * pow(sigma, 2)));
    return w;
}

void IG::addEdge(int node1, int node2, int edge_weight) {
    flow_graph[node1][node2] = array<int, 2>({ static_cast<int>(edge_weight),static_cast<int>(0) });
}

void IG::addInterPixelEdges(int i, int j) {
    makeEdge(i, j, i + 1, j);
    makeEdge(i, j, i, j - 1);
    makeEdge(i, j, i - 1, j);
    makeEdge(i, j, i, j + 1);
}

void IG::makeEdge(int i, int j, int u, int v) {
    if (BoundryCheck(i, j) && BoundryCheck(u, v)) {
        float inter_pixel_weight = Weight(i, j, u, v);
        int pixel1_linearValue = i * image.cols + j;
        int pixel2_linearValue = u * image.cols + v;
        addEdge(pixel1_linearValue, pixel2_linearValue, inter_pixel_weight);
    }
}

bool IG::BoundryCheck(int i, int j) {
    if (i >= 0 && i < image.rows && j >= 0 && j < image.cols) {
        return true;
    }
    return false;
}

void IG::saveImage(vector<int> segmentedImage, string img_output) {
    cv::Mat segmentedIMG(image.rows, image.cols, CV_8UC1);

    for (int i = 0; i < segmentedImage.size() - 2; ++i) {
        int u = floor(i / image.cols);
        int v = i % image.cols;
        if (segmentedImage[i] == true)
        {
            segmentedIMG.at<uint8_t>(u, v) = 255;
        }
        else if (segmentedImage[i] == false)
        {
            segmentedIMG.at<uint8_t>(u, v) = 0;
        }

    }
    cv::namedWindow(img_output, 0);
    cv::imshow(img_output, segmentedIMG);
    cv::imwrite(img_output, segmentedIMG);
    cv::waitKey(0);
}