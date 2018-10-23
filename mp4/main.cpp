
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

#include "cs225/HSLAPixel.h"

using namespace cs225;

int main() {
    PNG hanzo;    hanzo.readFromFile("hanzo.png");

    FloodFilledImage image(hanzo);
    
    DFS dfs1(hanzo, Point(0, 0), 0.1);
    DFS dfs2(hanzo, Point(1199, 0), 0.1);
    DFS dfs3(hanzo, Point(0, 1446), 0.1);
    DFS dfs4(hanzo, Point(600, 550), 0.1);
    DFS dfs5(hanzo, Point(1000, 650), 0.1);
    DFS dfs6(hanzo, Point(200, 900), 0.1);
    DFS dfs7(hanzo, Point(835, 737), 0.1);

    BFS bfs1(hanzo, Point(0, 0), 0.1);
    BFS bfs2(hanzo, Point(1199, 0), 0.1);
    BFS bfs3(hanzo, Point(0, 1446), 0.1);
    BFS bfs4(hanzo, Point(600, 550), 0.1);
    BFS bfs5(hanzo, Point(1000, 650), 0.1);
    BFS bfs6(hanzo, Point(200, 900), 0.1);
    BFS bfs7(hanzo, Point(835, 737), 0.1);

    MyColorPicker hanult("hanzoult.png");
    SolidColorPicker blue(HSLAPixel(200, 1, .5));

    image.addFloodFill(dfs1, blue);
    image.addFloodFill(dfs2, blue);
    image.addFloodFill(dfs3, blue);
    image.addFloodFill(dfs4, blue);
    image.addFloodFill(dfs5, blue);
    image.addFloodFill(dfs6, blue);
    image.addFloodFill(dfs7, blue);
  
    image.addFloodFill(bfs1, hanult);
    image.addFloodFill(bfs2, hanult);
    image.addFloodFill(bfs3, hanult);
    image.addFloodFill(bfs4, hanult);
    image.addFloodFill(bfs5, hanult);
    image.addFloodFill(bfs6, hanult);
    image.addFloodFill(bfs7, hanult);

    Animation animation = image.animate(80000);

    PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
    lastFrame.writeToFile("myFloodFill.png");
    animation.write("myFloodFill.gif");

    return 0;
}
