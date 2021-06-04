/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   directionUI.h
 * Author: Raymond
 *
 * Created on March 30, 2021, 10:47 PM
 */

#ifndef DIRECTIONUI_H
#define DIRECTIONUI_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <functional>
#include <map>
#include <set>
#include <regex>


//This header file declares the variables and functions of the DirectionUI namespace
//DirectionUI stores the variables and functions necessary for the User Interface related to direction search
namespace direction_ui {
    
    extern bool open ;
    extern bool firstSearchBarOn;
    extern bool secondSearchBarOn;
    extern bool firstClearButtonOn;
    extern bool secondClearButtonOn;
    extern bool firstSearchInputValid;
    extern bool secondSearchInputValid;
    extern bool intSelected;
    
    extern int firstIntersectionID;
    extern int secondIntersectionID;
    extern int tempIntID;
    extern int maxDropDownListSize;
    
    extern double panelWidth;
    extern double clearButtonWidth;
    extern double searchBarYMin;
    extern double searchBarYSpacing;
    extern double searchBarFont;
    
    extern std::vector<Buttons> vectorButtonsSearch;
    extern std::vector<Buttons> vectorButtonsClear;
    extern std::vector<Buttons> vectorButtonsDirections;    
    extern std::vector<Buttons> vectorButtonsDropDownList;
    extern std::vector<std::string> vectorTextsSearchPrompt;
            
    extern std::vector<std::string> vectorTextsSearchInput;
    extern std::vector<std::string> vectorTextsClear;
    extern std::vector<std::string> DropDownIntNameVector;
    
    extern int getIntersectionID(std::string streetName1, std::string streetName2);
    
    extern void reactToMouseClick(ezgl::application* app, GdkEventButton* event, double, double);
    extern void reactToKeyboard(ezgl::application *app, char *key_name);
    
    extern void setStateOfIntPOI(ezgl::application* app, /*GdkEventButton* event,*/ double, double);
    extern void setStateOfHighlightsWhenSearchBarOn(ezgl::application* app, double x, double y);
    extern void setPrevHighlightFalse();
    extern void setTextInputValidity(int searchBarIndex);   
    extern void setIntersectionSelectValidity(ezgl::application* app, double worldX, double worldY);
    extern void generalSetIntersectionValidity(int ID, std::string intName);
    extern std::vector<std::string> getDropDownIntNameVector(std::vector<int> &dropDownIDsVector);
    
    extern void draw_panel(ezgl::renderer *g);
    extern void drawSearchBars(ezgl::renderer *g);
    extern void drawClearButtons(ezgl::renderer *g);
    extern void drawDirectionsOnPanel(ezgl::renderer *g);    
    extern void drawADirectionButton(double xMin, double yMin, float boxWidth, float boxHeight, std::string name, ezgl::renderer *g, int fontSize);
    extern void drawFirstSearchBarWhenItsOn(ezgl::renderer *g);
    extern void drawSecondSearchBarWhenItsOn(ezgl::renderer *g);
    extern void drawSearchBarsHelper(ezgl::renderer *g);
    extern void drawDropDownListHelper(ezgl::renderer *g, int searchBarID);
    extern void drawDropDownListA(ezgl::renderer *g);
    extern void drawDropDownListB(ezgl::renderer *g);
    extern void actOnReturnPressed(ezgl::application *app, std::vector<int> dropDownIDsVector, std::vector<std::string> dropDownNamesVector);
}



#endif /* DIRECTIONUI_H */

