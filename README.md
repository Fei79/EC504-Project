# Image Foreground/Background Segmentation using Max-Flow
This a Course project for EC504. It's aims to using Maxflow algorithms and others clustering algorithm(Kmeans and Gaussian Mixture) to solve the image segmentation problem.

### Group member:
Chengeng Liu  
Shaowei Lin  
Fei Gao  
Siyuan Zhang  
Runchuan Feng  

## Maxflow Algorithm
Edmonds-Karp algorithm is implemented by c.The role of the main.cpp file is to run.  
The function of the EK.hpp file is to initiate. The function of initiate is the core function to cut the flow graph with maxflow.  
The core function of IG.hpp is to convert the gray value matrix into a network flow graph, and use the weight= formula (gray value difference)  

## Others Clustering Algorithm
### K-means Algorithm
K-means algorithm is implemented by python. The code file is kmeans.ipynb and it can be run in Google colab directly by click “Open in Colab” button on the top left concern.  
Download the image samples from Input file and upload them to the Google colab. Please make sure that the image you upload is in the same category as the code.   
On the first code segment, there is one line called image = cv2.imread('xxx.jpg'), which is used to read the image. You can change the different image names to test different image results.

### Gaussian Mixture Algorithm
Simply run the ec504_GMM.ipynb in cluster algorithm file.  
To change picture: change the line image_path = 'horse.jfif' to your own image paths.  
To change the number of clusters: change the line ncomp=5 to a number between 2 to 5. If you want to enable more clusters, you should also change the color labels COLORS[] in the second code block.

## Result
### Image segementation by Maxflow:
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Output/Flower%20output.jpg?raw=true)
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Output/Man%20output.jpg?raw=true)

### Image segementation by Kmeans:
Original image:  
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Input/dog.jpg?raw=true)
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Input/flowers.jpg?raw=true)  


Result:  
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Output/dog-kmeans.png?raw=true)
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Output/flowers-kmeans.png?raw=true)

### Image segementation by Gaussian Mixture:
Original image: 
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Input/horse.jpg?raw=true)  
Result:
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Output/Picture1.png?raw=true)
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Output/Picture2.png?raw=true)
![Image text](https://github.com/Fei79/EC504-Project/blob/main/Output/Picture3.png?raw=true)
