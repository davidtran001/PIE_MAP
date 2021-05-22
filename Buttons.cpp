/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Buttons.cpp
 * Author: Raymond
 *
 * Created on March 10, 2021, 7:12 PM
 */

#include "Buttons.h"


//Object instantiation for structs defined in Buttons.h
ChooseMapButtonData choose_map_button_data;
FindButtonData find_button_data;
FindIntersectionButtonData find_intersection_button_data; 
std::vector<std::string> vectorOfMapNames;

//implemetation of the struct method
void FindButtonData::loadFindButtonNamesToVector() {
    initialVector.resize(3);
    initialVector[0] = "Find Intersection of Two Streets";
    initialVector[1] = "Find POI (coming soon)";
    initialVector[2] = "Find Features (coming soon)";
}
void turnAllButtonsOff() {
    choose_map_button_data.open = false;
    find_button_data.open = false;
    find_intersection_button_data.open = false;
    find_intersection_button_data.firstIntButtonOpen = false;
    find_intersection_button_data.streetNamesInsertSuccess = false;
    find_intersection_button_data.multipleNames = false;
    DirectionUI::open = false;
    DirectionUI::firstSearchBarOn = false;
    DirectionUI::secondSearchBarOn = false;
    DirectionUI::firstClearButtonOn = false;
    DirectionUI::secondClearButtonOn = false;
    //DirectionUI::vectorTextsSearchInput.clear();
    //DirectionUI::vectorTextsSearchInput.resize(2);
    DirectionUI::firstSearchInputValid = false;
    DirectionUI::secondSearchInputValid = false;
    DirectionUI::intSelected = false;
    int_data.vectorIntPositionXY[DirectionUI::firstIntersectionID].highlight = false;
    int_data.vectorIntPositionXY[DirectionUI::secondIntersectionID].highlight = false;
}
void turnStatesOffExceptHighlight() {
    choose_map_button_data.open = false;
    find_button_data.open = false;
    find_intersection_button_data.open = false;
    find_intersection_button_data.firstIntButtonOpen = false;
    find_intersection_button_data.streetNamesInsertSuccess = false;
    find_intersection_button_data.multipleNames = false;
    DirectionUI::open = false;
    DirectionUI::firstSearchBarOn = false;
    DirectionUI::secondSearchBarOn = false;
    DirectionUI::firstClearButtonOn = false;
    DirectionUI::secondClearButtonOn = false;
    
}

void makeManyButtonsAlgorithm(ezgl::renderer *g,
        void(*drawButtonFunc)(double, double, float, float, std::string, ezgl::renderer*, int),
        std::vector<Buttons> &buttonVector, //pass in a Vector of Button Structs
        std::vector<std::string> &nameVector,//pass in a vector containing the names you want to put onto the buttons
        int horizontalNum, 
        float buttonWidth, //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
        float buttonHeight, //height of each button
        float buttonXSpacing, //horizontal space between the middle point of each button
        float buttonYSpacing, //vertical space between the middle point of each button
        int fontSize,       //font size of text on the buttons
        int numConstraint, //put negative value if unneeded
        float xInitial,    //x location of the leftmost button. Set to negative if you want buttons to be horizontally centered on screen
        float yInitial) { //y location of the topmost button. Set to negative if you want buttons to be vertically centered on screen
        

    ezgl::rectangle rec = g->get_visible_screen();
    
    //Set number of Buttons
    int numButtons;
    if (numConstraint < 0 || numConstraint > nameVector.size()) 
        numButtons = nameVector.size();
    else 
        numButtons = numConstraint;
    
    
    //Set number of vertical buttons
    int verticalNum;
    if (numButtons % horizontalNum == 0) 
        verticalNum = numButtons / horizontalNum;
    else 
        verticalNum = numButtons / horizontalNum + 1;
    
    
    //set button width
    float ratio = 0;
    if (buttonWidth < 0 && buttonWidth >= -1) { //you want width to change according to screen size
        ratio = buttonWidth * -1;
         //get ratio of the screen
        buttonWidth = rec.width() * ratio;
    }
    
    //set Xmin and Ymin
    float xmin, ymin;
    float canvasCenterX = rec.width() / 2;
    float canvasCenterY = rec.height() / 2;
    float temp = (1.0 - ratio) / 2;
    if (xInitial < 0) {//this means we want the buttons centered horizontally 
        if (buttonWidth < 0 && buttonWidth >= -1)
            xmin = temp * rec.width();
        else 
            xmin = canvasCenterX - buttonXSpacing *  horizontalNum / 2;  
    }
    else 
        xmin = xInitial;
    
    if (yInitial < 0) //this means we want the buttons centered vertically 
        ymin = canvasCenterY - buttonYSpacing * verticalNum / 2;
    else 
        ymin = yInitial;
    
    
    
    //use for loop to make many buttons and store their data in a vector of buttons
    int counter = 0;
    buttonVector.resize(numButtons);
    for (int i = 0; i < verticalNum; i++) {
        for (int j = 0; j < horizontalNum; j++) {
            if (counter < numButtons) {
                //make button
                std::string name = nameVector[counter];
                float x = xmin + buttonXSpacing * j;
                float y = ymin + buttonYSpacing * i;
                (*drawButtonFunc)(x, y, buttonWidth, buttonHeight, name, g, fontSize);
                buttonVector[counter].buttonName = name;
                buttonVector[counter].xmin = x;
                buttonVector[counter].ymin = y;
                buttonVector[counter].xmax = x + buttonWidth;
                buttonVector[counter].ymax = y + buttonHeight;
       
                counter++;    
            }
        }
        
    }    
}

template <typename buttonStructs>
void OldMakeManyButtonsAlgorithm(ezgl::renderer *g,
        buttonStructs &a, //pass in a struct/class containing a Vector of Button Structs
        std::vector<std::string> &buttonVector,
        int horizontalNum, //pass in a vector containing the names you want to put onto the buttons
        float buttonWidth, //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
        float buttonHeight, 
        float buttonXSpacing, //horizontal space between the middle point of each button
        float buttonYSpacing, //vertical space between the middle point of each button
        int fontSize,
        int numConstraint, //put negative value if unneeded
        int yInitial) { //set to negative if you want buttons to be vertically centered in the screen
    
    //create a list of boxes and text of the various cities
    ezgl::rectangle rec = g->get_visible_screen();
    
    int numButtons;
    if (numConstraint < 0 || numConstraint > buttonVector.size()) 
        numButtons = buttonVector.size();
    else {
        numButtons = numConstraint;
    }
    
    int verticalNum;
    if (numButtons % horizontalNum == 0) {
        verticalNum = numButtons / horizontalNum;
    }
    else verticalNum = numButtons / horizontalNum + 1;
    
    float ratio;
    if (buttonWidth < 0 && buttonWidth >= -1) { //you want it to change according to screen size
        ratio = buttonWidth * -1;
         //get ratio of the screen
        buttonWidth = rec.width() * ratio;
    }
    
    float xmin, ymin;
    float canvasCenterX = rec.width() / 2;
    float canvasCenterY = rec.height() / 2;
    
    
    float temp = (1.0 - ratio) / 2;
    if (buttonXSpacing == 0) { //don't copy this in the new version
        xmin = temp * rec.width(); //std::cout<< buttonWidth << std:: endl;
    }
    else {
        xmin = canvasCenterX - buttonXSpacing *  horizontalNum / 2;
    }
    
    
    if (yInitial < 0) //this means we want the buttons centered vertically 
        ymin = canvasCenterY - buttonYSpacing * verticalNum / 2;
    else ymin = yInitial;
    
    
        //use for loop to make many buttons
    int counter = 0;
    a.vectorButtons.resize(numButtons);
    for (int i = 0; i < verticalNum; i++) {
        for (int j = 0; j < horizontalNum; j++) {
            if (counter < numButtons) {
                //make button
                std::string name = buttonVector[counter];
                float x = xmin + buttonXSpacing * j;
                float y = ymin + buttonYSpacing * i;
                makeButton(x, y, buttonWidth, buttonHeight, name, g, fontSize);
                a.vectorButtons[counter].buttonName = name;
                a.vectorButtons[counter].xmin = x;
                a.vectorButtons[counter].ymin = y;
                a.vectorButtons[counter].xmax = x + buttonWidth;
                a.vectorButtons[counter].ymax = y + buttonHeight;
       
                counter++;    
            }
        }
        
    }    
}

//this function will draw the interface and provide functionality for choosing map
void drawChooseMapCanvas(ezgl::renderer *g) {
    //set coordinate system to screen
    g->set_coordinate_system(ezgl::SCREEN);
    g->set_color(ezgl::color(0, 0, 0, 185));
    //set background colour of the interface
    ezgl::rectangle rec = g->get_visible_screen();
    g->fill_rectangle({0,0}, {rec.width(), rec.height()});
    
    //draw city list
    //create a list of boxes and text of the various cities
    int horizontalNum = 4;
    float buttonWidth = 160;
    float buttonHeight = 35;
    float buttonXSpacing = 170;
    float buttonYSpacing = 50;
    int fontSize = 10.5;
    int numConstraint = -1; //set to negative since unneeded here
    int yInitial = -1;      //set to negative if you want the buttons to be centered
    OldMakeManyButtonsAlgorithm (g,
        choose_map_button_data,
        vectorOfMapNames,
        horizontalNum, 
        buttonWidth, 
        buttonHeight, 
        buttonXSpacing, 
        buttonYSpacing,
        fontSize,
        numConstraint,
        yInitial);    
    // Set the coordinate system back to WORLD
    g->set_coordinate_system(ezgl::WORLD);
}

void drawFindCanvas(ezgl::renderer *g) {
    //set coordinate system to screen
    g->set_coordinate_system(ezgl::SCREEN);
    g->set_color(ezgl::color(0, 0, 0, 185));
    //set background colour of the interface
    ezgl::rectangle rec2 = g->get_visible_screen();
    g->fill_rectangle({0,0}, {rec2.width(), rec2.height()});
    
    //find_button_data.loadFindButtonNamesToVector();

    //create a list of boxes and text of the various buttons
    int horizontalNum = 1;
    float buttonWidth = 400;
    float buttonHeight = 75;
    float buttonXSpacing = 300; //if horizontalNum = 1 , use this to control shift left (higher->more shift left))
    float buttonYSpacing = 110;
    int fontSize = 14;
    int numConstraint = -1; //set to negative since unneeded here
    int yInitial = -1;      //set to negative if you want the buttons to be centered
    OldMakeManyButtonsAlgorithm (g,
        find_button_data,
        find_button_data.initialVector,
        horizontalNum, 
        buttonWidth, 
        buttonHeight, 
        buttonXSpacing, 
        buttonYSpacing,
        fontSize,
        numConstraint,
        yInitial);    
    
    // Set the coordinate system back to WORLD
    g->set_coordinate_system(ezgl::WORLD); 
}

void makeButton(double xMin, double yMin, float boxWidth, float boxHeight, std::string name, ezgl::renderer *g, int fontSize) {
    g->set_coordinate_system(ezgl::SCREEN);
    
    g->set_color(ezgl::color(65, 73, 82, 255));    
    g->fill_rectangle({xMin, yMin}, {xMin + boxWidth, yMin + boxHeight});
    g->set_color(ezgl::WHITE);
    g->draw_rectangle({xMin, yMin}, {xMin + boxWidth, yMin + boxHeight});
    //g->set_color(ezgl::WHITE);
    g->set_text_rotation(0);
    g->set_font_size(fontSize);
    g->draw_text({xMin+boxWidth/2, yMin+boxHeight/2}, name);
    
}

void reactIfChooseMapIsOn(ezgl::application* app, GdkEventButton* event) {
    //search through vector of Buttons to see if the user has clicked on one of them
    float x = event->x;
    float y = event->y;
    int numButtons = choose_map_button_data.vectorButtons.size();
    for (int i = 0; i < numButtons; i++) {
        if (x > choose_map_button_data.vectorButtons[i].xmin && x < choose_map_button_data.vectorButtons[i].xmax) {
            if (y > choose_map_button_data.vectorButtons[i].ymin && y < choose_map_button_data.vectorButtons[i].ymax) {
                turnAllButtonsOff(); 
                choose_map_button_data.open = false;
                POIOn = false;
                interOn = false;
                changeMap(app, i);
                return;

            }
        }
    }
}

void reactIfFindIsOn(ezgl::application* app, GdkEventButton* event) {
    //search through vector of Buttons to see if the user has clicked on one of them
    
    float x = event->x;
    float y = event->y;
    int numButtons = find_button_data.vectorButtons.size();
    //int numButtons = 1;
    for (int i = 0; i < numButtons; i++) {
        if (x > find_button_data.vectorButtons[i].xmin && x < find_button_data.vectorButtons[i].xmax) {
            if (y > find_button_data.vectorButtons[i].ymin && y < find_button_data.vectorButtons[i].ymax) {
                if (i == 0) { //means the button clicked is Find intersection of two streets
                    turnAllButtonsOff();
                    find_intersection_button_data.open = true;
                    app->refresh_drawing();
                }
                    

            }
        }
    }
}

void reactIfFindIntButtonOpen(ezgl::application* application, GdkEventButton* event) {
    float x = event->x;
    float y = event->y;
    int numButtons = find_intersection_button_data.vectorButtons.size();
    //int numButtons = 1;
    for (int i = 0; i < numButtons; i++) {
        if (x > find_intersection_button_data.vectorButtons[i].xmin && x < find_intersection_button_data.vectorButtons[i].xmax) {
            if (y > find_intersection_button_data.vectorButtons[i].ymin && y < find_intersection_button_data.vectorButtons[i].ymax) {
                turnAllButtonsOff();
                find_intersection_button_data.firstIntButtonOpen = true;
                find_intersection_button_data.firstStreet = find_intersection_button_data.partialStreetNameVector[0];
                std::cout << "first street entered: " << find_intersection_button_data.firstStreet << std::endl;
                application->refresh_drawing();

            }
        }
    }
}

void reactIfFirstIntButtonOpen(ezgl::application* application, GdkEventButton* event) {
    float x = event->x;
    float y = event->y;
    int numButtons = find_intersection_button_data.vectorButtons.size();
    //int numButtons = 1;
    for (int i = 0; i < numButtons; i++) {
        if (x > find_intersection_button_data.vectorButtons[i].xmin && x < find_intersection_button_data.vectorButtons[i].xmax) {
            if (y > find_intersection_button_data.vectorButtons[i].ymin && y < find_intersection_button_data.vectorButtons[i].ymax) {
                turnAllButtonsOff();
                find_intersection_button_data.streetNamesInsertSuccess = true;
                find_intersection_button_data.secondStreet = find_intersection_button_data.partialStreetNameVector[0];
                std::cout << "second street entered: " << find_intersection_button_data.secondStreet << std::endl;
                //highlight_intersectionOfTwoStreets(application);
                application->refresh_drawing();

            }
        }
    }
}   





void changeMap(ezgl::application* application, int buttonID) {
    std::string mapName = choose_map_button_data.vectorButtons[buttonID].buttonName;
    std::cout<<"Loading" << " " << mapName << std::endl;
    std::cout<< "Please Wait ... " << std::endl;
    
    
    closeMap(); std::cout<< "map closed" << std:: endl;
    loadMapNamesToVector();
    //create map path
    choose_map_button_data.mapName = mapName;
    std::string mapPath;
    std::string lowerCase = mapName;
    //create mapPath from mapName
    std::transform (lowerCase.begin(), lowerCase.end(), lowerCase.begin(), ::tolower);
    mapPath = mapPathFirst + lowerCase + mapPathLast;
    std::cout << mapPath << std::endl;
    choose_map_button_data.mapPath = mapPath;
    
     bool success = loadMap(mapPath);
     if (!success) std::cout << "Unable to Change Map" << std::endl;
     
 
    ezgl::rectangle new_world({getXFromLon(min_lon), getYFromLat(min_lat)}, {getXFromLon(max_lon), getYFromLat(max_lat)});
    application->change_canvas_world_coordinates("MainCanvas", new_world);

    application->update_message(choose_map_button_data.mapName);
    //draw new map
    application->refresh_drawing();
}

void drawFindIntersectionOfTwoStreetsCanvas(ezgl::renderer *g) {
    
    //set coordinate system to screen
    g->set_coordinate_system(ezgl::SCREEN);
    g->set_color(ezgl::color(25, 25, 25));
    //set background colour of the interface
    ezgl::rectangle rec2 = g->get_visible_screen();
    g->fill_rectangle({0,0}, {rec2.width(), rec2.height()});
    
    
    
    if (find_intersection_button_data.keyPressed) {
        //call the generate button algorithm
        //create a drop down list
        int horizontalNum = 1;
        float buttonWidth = -0.6;  //we can set this to -0.3  if we want it to be as wide as 70 percent of screen
        float buttonHeight = 35;
        float buttonXSpacing = 0; //if horizontalNum = 1 , use 0
        float buttonYSpacing = 35;
        int fontSize = 10.5;
        int numConstraint = 15; //set to negative if unneeded here
        int yInitial = 0; //set to negative if unneeded here
        OldMakeManyButtonsAlgorithm (g,
            find_intersection_button_data,
            find_intersection_button_data.partialStreetNameVector,
            horizontalNum, 
            buttonWidth, 
            buttonHeight, 
            buttonXSpacing, 
            buttonYSpacing,
            fontSize,
            numConstraint,
            yInitial = 0);
    }
    
    //check other conditions and act accordingly
    if(find_intersection_button_data.multipleNames == true) {
        if (find_intersection_button_data.partialStreetNameVector.size() > 1) {   
            g->set_color(ezgl::ORANGE);
            g->set_text_rotation(0);
            g->set_font_size(16);
            g->draw_text({100, 180}, "Multiple streets found");
            g->draw_text({100, 210}, "Pick a specific street");  
        }
        
        find_intersection_button_data.multipleNames = false;
    } 
   
    if (find_intersection_button_data.open) {
        //tell user instructions
        g->set_color(ezgl::WHITE);
        g->set_text_rotation(0);
        g->set_font_size(16);
        g->draw_text({110, 20}, "Type first street above");
        g->draw_text({85, 50}, "then press Enter.");
        
        if (find_intersection_button_data.wrongInput == true) {
            g->set_color(ezgl::ORANGE);
            g->draw_text({95, 80}, "Wrong Name!");
            find_intersection_button_data.wrongInput = false;
        }
        
    }
    if (find_intersection_button_data.firstIntButtonOpen) {
        //tell user instructions
        g->set_color(ezgl::WHITE);
        g->set_text_rotation(0);
        g->set_font_size(16);
        g->draw_text({120, 20}, "Type second street above");
        g->draw_text({85, 50}, "then press Enter.");
        if (find_intersection_button_data.wrongInput == true) {
            g->set_color(ezgl::ORANGE);
            g->draw_text({85, 150}, "Wrong Name!");
            find_intersection_button_data.wrongInput = false;
        }
        g->set_color(ezgl::WHITE);
        g->draw_text({85, 80}, "First street is:");
        g->draw_text({85, 110}, find_intersection_button_data.firstStreet);
        
    } 
    
    g->set_coordinate_system(ezgl::SCREEN);

}

std::vector<std::string> returnPartialStreetNameVector(std::vector<int> &partialStreetIdxVector) {
     
    int loopCount = 20; //restrict how long the nameVector will be to not slow down program
    //store the necessary partialStreetId's corresponding names into a vector 
    std::vector<std::string> partialNameVector;
    partialNameVector.resize(loopCount);
    for (int i = 0; i < loopCount; i++) {
        int tempIdx = partialStreetIdxVector[i];
        partialNameVector[i] = st_data.vectorStreetName[tempIdx];
    } 
    //remove the duplicates in the name vector
    std::sort(partialNameVector.begin(), partialNameVector.end());
    auto it = std::unique(partialNameVector.begin(), partialNameVector.end());
    partialNameVector.erase(it, partialNameVector.end());
    return partialNameVector;
}


void loadPartialStreetNameVector() {
    //determine how many streetNames to load into data
    //std::cout << "yes";
    int maxButtons = 20;
    int loopCount; 
    if (find_intersection_button_data.partialStreetIdxVector.size() > maxButtons)
        loopCount = maxButtons;
    else loopCount = find_intersection_button_data.partialStreetIdxVector.size();
    
    //store the necessary partialStreetId's corresponding names into a vector 
    find_intersection_button_data.partialStreetNameVector.resize(loopCount);
    for (int i = 0; i < loopCount; i++) {
        int tempIdx = find_intersection_button_data.partialStreetIdxVector[i];
        find_intersection_button_data.partialStreetNameVector[i] = st_data.vectorStreetName[tempIdx];
    } 
    //remove the duplicates in the name vector
    std::sort(find_intersection_button_data.partialStreetNameVector.begin(), find_intersection_button_data.partialStreetNameVector.end());
    auto it = std::unique(find_intersection_button_data.partialStreetNameVector.begin(), find_intersection_button_data.partialStreetNameVector.end());
    find_intersection_button_data.partialStreetNameVector.erase(it, find_intersection_button_data.partialStreetNameVector.end());
    
    loopCount = find_intersection_button_data.partialStreetNameVector.size();
    //std:: cout << loopCount; 
}


bool FindIntersectionButtonData:: checkIfStreetNameCorrect(std::string textInput) {
    std::vector<std::string> temp = find_intersection_button_data.partialStreetNameVector;
    std::transform (textInput.begin(), textInput.end(), textInput.begin(), ::tolower);
    std::remove(textInput.begin(), textInput.end(), ' '); 


    for (int i = 0; i < temp.size(); i++) {
        std::transform (temp[i].begin(), temp[i].end(), temp[i].begin(), ::tolower);
        std::remove(temp[i].begin(), temp[i].end(), ' '); 
        if (temp[i].compare(textInput) == 0) {
            //std::cout << "yes";
            return true;
        }
    }
    return false;
}

