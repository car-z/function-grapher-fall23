
#include <cassert>
#include "fill.h"
#include "func.h"

//deletes dynamically allocated color for fill
Fill::~Fill() {
    if(color){
        delete color;
    }
}

//member function to fill the area specified as determined by the function bounds
void Fill::fill_color(Color* img_pixels, Bounds* bounds) const{
    //iterating through rows of pixels of image (i)
    for(int i = 0; i < bounds->get_height(); i++){
        //iterating through columns of pixels of image (j)
        for(int j = 0; j < bounds->get_width(); j++){
            //calculating x coordinate with respect to this pixel location (i,j)
            double x = bounds->get_xmin() + (j/(double) bounds->get_width()) * (bounds->get_xmax() - bounds->get_xmin());
            //if the calculated x is beyond the bounds of the image, jump to next pixel in image
            if(x > bounds->get_xmax() || x < bounds->get_xmin()){
                continue;
            }
            //calculate y coordinate with respect to this pixel location (i,j)
            double y = bounds->get_ymin() + ((bounds->get_height()-1-i)/(double) bounds->get_height()) * (bounds->get_ymax() - bounds->get_ymin());
            //if calculated y is beyond bounds of image, jump to next pixel in image
            if(y > bounds->get_ymax() || y < bounds->get_ymin()){
                continue;
            }
            Color fill_color = img_pixels[i*bounds->get_width() + j]; //original color of pixel at this location
            fill_color.blend_colors(opacity,color); //blending the original color of pixel with color of fill
            //depending on type of Fill, perform different operations
            switch(type){
                case ABOVE:
                    //Calculating result of function for this x location. Check to see location of pixel with respect to this result and fill accordingly 
                    if(((func1->get_expr()->eval(x))) < y){
                        img_pixels[i*bounds->get_width() + j] = fill_color;
                    }
                    break;
                case BELOW:
                    if(((func1->get_expr()->eval(x))) > y){
                        img_pixels[i*bounds->get_width() + j] = fill_color;
                    }
                    break;
                case BETWEEN:
                
                     if((((func1->get_expr()->eval(x))) > y && ((func2->get_expr()->eval(x))) < y) || ((func1->get_expr()->eval(x)) < y && (func2->get_expr()->eval(x)) > y)){
                        img_pixels[i * bounds->get_width() + j] = fill_color;
                    }
                
                   
                    break;
            }
        }
    }
}
