#include "Utility.h"

#include <iostream>
#include <fstream>
#include <string>

std::string get_file_content(const char* filename){
    std::cout<<"READING FROM: "<<filename<<"\n";

    std::string content = "", tmp = "";

    std::ifstream data(filename);
    if(data.is_open()){
        // Use a while loop together with the getline() function to read the file line by line
        while (std::getline (data, tmp)) {
            // Output the text from the file
            content += tmp;
            content += '\n';
            printToConsole(tmp);
        }
    }
    else{
        std::cout<<filename<<" is not open!\n";
    }
    // Close the file
    data.close(); 

    return content;
}

ColorRGB::ColorRGB() {
};
ColorRGB::ColorRGB(int r, int g, int b) {
    if(r > 255)
        r = 255;
    else if(r<0)
        r = 0;

    if(g > 255)
        g = 255;
    else if(g<0)
        g = 0;

    if(b > 255)
        b = 255;
    else if(b<0)
        b = 0;
        
    R = (r)/255.0f;
    G = (g)/255.0f;
    B = (b)/255.0f;
}
ColorRGB::ColorRGB(const ColorRGB& obj) : R(obj.R), G(obj.G), B(obj.B) {
}
ColorRGB& ColorRGB::operator=(const ColorRGB& obj){
    R = obj.R;
    G = obj.G;
    B = obj.B;
    return *this;
}
ColorRGB::~ColorRGB(){
    
}