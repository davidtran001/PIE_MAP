/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChooseMap.h
 * Author: Raymond
 *
 * Created on March 10, 2021, 7:12 PM
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>


extern::std::vector<std::string> vectorOfMapNames;
extern::std::string mapPathFirst;
extern::std::string mapPathLast;
extern std::vector<StreetIdx> partialStreetNameVector;


void loadPartialStreetNameVector();

struct Buttons {
    //we can also put make buttons algorithm here
    std::string buttonName;
    bool on = false;
    double xmin;
    double ymin; 
    double xmax;
    double ymax;
};

struct ChooseMapButtonData {
    std::string mapName = "Toronto_Canada";
    std::string mapPath = "/cad2/ece297s/public/maps/toronto_canada.streets.bin";
    //set default to load Toronto initially (needed by OSMData.cpp)
    std::string osmPath = "/cad2/ece297s/public/maps/toronto_canada.osm.bin";
    bool open = false;
    std::vector<Buttons> vectorButtons;
    void reactToMouseClick() {}
};


struct FindButtonData {

    bool open = false;
    //initial vector stores the names of the buttons that should appear when findButton is clicked
    //these names are loaded from loadMap
    std::vector<std::string> initialVector;
    void loadFindButtonNamesToVector();
    
    //array of Buttons structs indexed by the Button idx
    std::vector<Buttons> vectorButtons;
};

struct FindIntersectionButtonData {
    bool open = false;
    bool firstIntButtonOpen = false;
    bool streetNamesInsertSuccess = false;
    bool wrongInput = false;
    bool multipleNames = false;
    bool keyPressed = false;
    bool checkIfStreetNameCorrect(std::string textInput);
    std::vector<Buttons> vectorButtons;
    std::vector<int>partialStreetIdxVector;
    std::vector<std::string> partialStreetNameVector;
    std::string firstStreet;
    std::string secondStreet;
    //void find 
    
};

extern ChooseMapButtonData choose_map_button_data;
extern FindButtonData find_button_data;
extern FindIntersectionButtonData find_intersection_button_data; 


//this function will draw the choose map interface and provide functionality for choosing maps
void drawChooseMapCanvas(ezgl::renderer *g);

//this function will draw the Find interface and provide functionality
void drawFindCanvas(ezgl::renderer *g);

//draws the canvas for finding intersection of two streets and provide functionality
void drawFindIntersectionOfTwoStreetsCanvas(ezgl::renderer *g);

//this function draws a button on the screen
void makeButton(double xMin, double yMin, float boxWidth, float boxHeight, std::string name, ezgl::renderer *g, int fontSize);

//If mapName is clicked this function will closeMap and load the new map
void reactIfChooseMapIsOn(ezgl::application* app, GdkEventButton* event);

void reactIfFindIsOn(ezgl::application* app, GdkEventButton* event);

void reactIfFindIntButtonOpen(ezgl::application* app, GdkEventButton* event);

void reactIfFirstIntButtonOpen(ezgl::application* app, GdkEventButton* event);

void turnAllButtonsOff();
void turnStatesOffExceptHighlight();

void changeMap(ezgl::application* app, int buttonID); 

std::vector<std::string> returnPartialStreetNameVector(std::vector<int> &partialStreetIdxVector);

void makeManyButtonsAlgorithm(ezgl::renderer *g,
        void(*drawButtonFunc)(double, double, float, float, std::string, ezgl::renderer*, int),
        std::vector<Buttons> &buttonVector, //pass in a Vector of Button Structs
        std::vector<std::string> &nameVector,
        int horizontalNum, //pass in a vector containing the names you want to put onto the buttons
        float buttonWidth, //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
        float buttonHeight, //height of each button
        float buttonXSpacing, //horizontal space between the middle point of each button
        float buttonYSpacing, //vertical space between the middle point of each button
        int fontSize,       //font size of text on the buttons
        int numConstraint, //put negative value if unneeded
        float xInitial,    //x location of the leftmost button. Set to negative if you want buttons to be horizontally centered on screen
        float yInitial); //y location of the topmost button. Set to negative if you want buttons to be vertically centered on screen

template <typename buttonStructs> 
void OldMakeManyButtonsAlgorithm (ezgl::renderer *g,
        buttonStructs &a, 
        std::vector<std::string> &buttonVector,
        int horizontalNum, 
        float buttonWidth, 
        float buttonHeight, 
        float buttonXSpacing, //if horizontalNum = 1 , use this to control shift left (higher->more shift left)
        float buttonYSpacing,
        int fontSize,
        int numConstraint, //set to negative if not needed
        int yInitial); //set to negative if you want the buttons to be centered
#endif /* BUTTONS_H */

