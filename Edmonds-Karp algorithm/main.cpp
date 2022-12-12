#include "IG.hpp"
#include "EK.hpp"

int main()
{
    int src_x = 0;
    int src_y = 0;
    int sink_x = 25;
    int sink_y = 25;

    string imageName = "C:\Users\85422\Desktop\EC504project\EC504project";
    
    IG img(imageName);
    cv::Mat dest;
    cv::resize(img.image,dest,cv::Size(50,50),0,0,cv::INTER_CUBIC);
    img.image = dest;
    img.Image_To_Flow_Graph(src_x, src_y, sink_x, sink_y);

    string outfile("E:/desktop/project2/output/output2.png");
    cout << outfile << endl;

    EK ek(img.flow_graph);
    ek.initiate_algorithm();
    
    img.saveImage(ek.segmentedImage, outfile);
    return 0;
}
