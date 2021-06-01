/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   searchBar.cpp
 * Author: Raymond
 *
 * Created on May 7, 2021, 8:01 PM
 */
#include "searchBar.h"

//This function allows a search bar printed on canvas to react to user key presses
//It will modify the string to be printed onto the search bar depending on key presses
//Then it calls various functions which will help draw a drop down list as well as checking for input validity
//The functions to be called must be written by the programmer and must be passed into this function as arguments
void searchBarReactToKeyboard(
        int nameVecSizeCap,
        ezgl::application *app, 
        std::string keyName,
        std::string &searchInput,
        std::vector<std::string> &dropDownNamesVector,
        std::vector<int> (*getIDsFunct) (std::string searchInput),
        std::vector<std::string> (*getDropDownNamesFunc)(std::string (*getSingleNameFunc) (int ID), std::vector<int> &dropDownIDsVector, int NameVecSizeCap),
        std::string (*getSingleNameFunc) (int ID),
        void (*drawPanelFunc) (ezgl::renderer *g),
        void (*drawDropDownFunc) (ezgl::renderer *g),
        void (*actOnReturnFunc) (ezgl::application *app, std::vector<int> dropDownIDsVector, std::vector<std::string> dropDownNamesVector)) 
{
    //first get renderer
    ezgl::renderer *g = app->get_renderer();
    
    //react depending on the key inputs
    if (keyName.length() == 1) {
        searchInput += keyName; 
    }
    if (keyName == "space") {
        searchInput += " ";
    }
    if (keyName == "BackSpace") {
        if (searchInput.length() > 0) {
            searchInput.pop_back();
            if (searchInput.length() == 0) {
                app->refresh_drawing();
                return;
            }
        }
    }
    if (keyName == "ampersand") {
        searchInput += "&";
    }
    
    std::vector<int> dropDownIDsVector;
    if (searchInput.length() > 0) {
        dropDownIDsVector = (*getIDsFunct)(searchInput);
        dropDownNamesVector = (*getDropDownNamesFunc)(getSingleNameFunc, dropDownIDsVector, nameVecSizeCap);

        (*drawPanelFunc)(g);
        (*drawDropDownFunc) (g);
        app->flush_drawing();

    }

    if (keyName == "Return") { 
        (*actOnReturnFunc) (app, dropDownIDsVector, dropDownNamesVector);
    }
}

//This function returns a vector of dropDownNames from a vector of dropDownIDs
//Replicate names will be removed in the vector
std::vector<std::string> getDropDownNames(std::string (*getSingleNameFunc) (int ID), std::vector<int> &dropDownIDsVector, int vecSizeConstraint) {
    int loopCount; 
    if (dropDownIDsVector.size() > vecSizeConstraint)
        loopCount = vecSizeConstraint;
    else loopCount = dropDownIDsVector.size();
    
    std::vector<std::string> dropDownNamesVector;
    dropDownNamesVector.resize(loopCount);
    for (int i = 0; i < loopCount; i++) {
        int tempIdx = dropDownIDsVector[i];
        dropDownNamesVector[i] = (*getSingleNameFunc)(tempIdx);
    } 
    //remove the duplicates in the name vector (method 1)
    /*std::sort(dropDownNamesVector.begin(), dropDownNamesVector.end());
    auto it = std::unique(dropDownNamesVector.begin(), dropDownNamesVector.end());
    dropDownNamesVector.erase(it, dropDownNamesVector.end()); */
    
    //remove the duplicates in the name vector (method 2)
    std::set<std::string> tempSet(dropDownNamesVector.begin(), dropDownNamesVector.end());
    dropDownNamesVector.assign(tempSet.begin(), tempSet.end());
    
    return dropDownNamesVector;
}

void generateSearchBarWClear(ezgl::renderer *g,
        void(*drawSearchBarFunc)(double, double, float, float, std::string, ezgl::renderer*, int),
        void(*drawClearButtonFunc)(double, double, float, float, std::string, ezgl::renderer*, int),
        std::vector<Buttons> &searchButtonVector, //pass in a Vector of Button Structs
        std::vector<Buttons> &clearButtonVector,
        std::vector<std::string> &searchNameVector,//pass in a vector containing the names you want to put onto the buttons
        std::vector<std::string> &ClearNameVector,
        float searchBarWidth, //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
        float SearchBarHeight, //height of each button
        int fontSize,       //font size of text on the buttons
        float xInitial,    //x location of the leftmost point. Set to negative if you want buttons to be horizontally centered on screen
        float yInitial) { //y location of the topmost point. Set to negative if you want buttons to be vertically centered on screen

    ezgl::rectangle rec = g->get_visible_screen();
    
    //Call generate buttons algorithm on searchBar
    int horizontalNum = 1; //number of buttons horizontally
    float buttonWidth = searchBarWidth; //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
    float buttonHeight = SearchBarHeight;
    float buttonXSpacing = 0; //horizontal space between the middle point of each button (set to 0 if you want it to be 1 column)
    float buttonYSpacing = 0; //vertical space between the middle point of each button
    	
    int numConstraint = -1; //set to negative if you don't have a maximum number constraint on how many buttons to show
    
    makeManyButtonsAlgorithm(g,
        drawASearchBar,
        searchButtonVector, //pass in a Vector of Button structs
        searchNameVector,
        horizontalNum, //pass in a vector containing the names you want to put onto the buttons
        buttonWidth, //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
        buttonHeight, 
        buttonXSpacing, //horizontal space between the middle point of each button
        buttonYSpacing, //vertical space between the middle point of each button
        fontSize,
        numConstraint, //put negative value if unneeded
        xInitial,
        yInitial);  //set to negative if you want buttons to be vertically centered on screen    

    //Call generate buttons algorithm on searchBar
    horizontalNum = 1; //number of buttons horizontally
    buttonWidth = buttonHeight; //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)

    xInitial = searchButtonVector[0].xmax;	//set to negative if you want buttons to be horizontally centered on the screen 
    
    makeManyButtonsAlgorithm(g,
        drawAClearButton,
        clearButtonVector, //pass in a Vector of Button structs
        ClearNameVector,
        horizontalNum, //pass in a vector containing the names you want to put onto the buttons
        buttonWidth, //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
        buttonHeight, 
        buttonXSpacing, //horizontal space between the middle point of each button
        buttonYSpacing, //vertical space between the middle point of each button
        fontSize,
        numConstraint, //put negative value if unneeded
        xInitial,
        yInitial);  //set to negative if you want buttons to be vertically centered on screen    
    
}

void drawASearchBar(double xMin, double yMin, float boxWidth, float boxHeight, std::string name, ezgl::renderer *g, int fontSize) {
    g->set_coordinate_system(ezgl::SCREEN);
    
    g->set_color(ezgl::color(103, 204, 255, 255));    
    g->fill_rectangle({xMin, yMin}, {xMin + boxWidth, yMin + boxHeight});
    //g->set_color(ezgl::GREY_75);
    //g->set_color(ezgl::color(0, 25, 51, 255));
    g->draw_rectangle({xMin, yMin}, {xMin + boxWidth, yMin + boxHeight});
    g->set_color(ezgl::BLACK);
    g->set_text_rotation(0);
    g->set_font_size(fontSize);
    g->draw_text({xMin+boxWidth/2, yMin+boxHeight/2}, name);    
}

void drawAClearButton(double xMin, double yMin, float boxWidth, float boxHeight, std::string name, ezgl::renderer *g, int fontSize) {
    g->set_coordinate_system(ezgl::SCREEN);
    
    g->set_color(ezgl::color(55, 63, 72, 255));    
    //g->set_color(ezgl::color(0, 0, 0, 255));
    //g->set_color(ezgl::color(0, 25, 51, 255));
    
    g->fill_rectangle({xMin, yMin}, {xMin + boxWidth, yMin + boxHeight});
    //g->set_color(ezgl::GREY_75);
    //g->set_color(ezgl::color(110, 150, 230, 255));    
    g->draw_rectangle({xMin, yMin}, {xMin + boxWidth, yMin + boxHeight});
    g->set_color(ezgl::WHITE);
    g->set_text_rotation(0);
    g->set_font_size(fontSize);
    g->draw_text({xMin+boxWidth/2, yMin+boxHeight/2}, name);    
}
