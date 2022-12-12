#include "IG.hpp"
#include "EK.hpp"

int main()
{
    int src_x = 0;
    int src_y = 0;
    int sink_x = 25;
    int sink_y = 25;

    string imageName = "c.jpg";
    
    IG img(imageName);
    cv::Mat dest;
    cv::resize(img.image,dest,cv::Size(50,50),0,0,cv::INTER_CUBIC);
    img.image = dest;
    img.Image_To_Flow_Graph(src_x, src_y, sink_x, sink_y);

    string outfile("output.jpg");
    cout << outfile << endl;

    EK ek(img.flow_graph);
    ek.initiate_algorithm();
    
    img.saveImage(ek.segmentedImage, outfile);
    return 0;
}