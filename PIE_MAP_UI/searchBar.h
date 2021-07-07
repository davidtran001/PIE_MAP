/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   searchBar.h
 * Author: Raymond
 *
 * Created on May 7, 2021, 8:01 PM
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <functional>
#include <map>
#include <set>
#include <regex>
#include "Buttons.h"



#ifndef SEARCHBAR_H
#define SEARCHBAR_H



//void drawDropDownList (ezgl::renderer* g);
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
        void (*actOnReturnFunc) (ezgl::application *app, std::vector<int> dropDownIDsVector, std::vector<std::string> dropDownNamesVector));

std::vector<std::string> getDropDownNames(std::string (*getSingleNameFunc) (int ID), std::vector<int> &dropDownIDsVector, int vecSizeConstraint);

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
        float yInitial); //y location of the topmost point. Set to negative if you want buttons to be vertically centered on screen

void drawASearchBar(double xMin, double yMin, float boxWidth, float boxHeight, std::string name, ezgl::renderer *g, int fontSize);

void drawAClearButton(double xMin, double yMin, float boxWidth, float boxHeight, std::string name, ezgl::renderer *g, int fontSize);

#endif /* SEARCHBAR_H */

