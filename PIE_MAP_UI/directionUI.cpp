/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   directionUI.cpp
 * Author: Raymond
 * 
 * Created on March 30, 2021, 10:47 PM
 */



#include "directionUI.h"



//Initialization of variables and function Implementations of the namespace DirectionUI
namespace direction_ui {
    bool open = false;
    bool firstSearchBarOn = false;
    bool secondSearchBarOn = false;
    bool firstClearButtonOn = false;
    bool secondClearButtonOn = false;
    bool firstSearchInputValid = false;
    bool secondSearchInputValid = false;
    bool intSelected = false;
    
    int firstIntersectionID = 0;
    int secondIntersectionID = 0;
    int tempIntID;
    int maxDropDownListSize = 10;
    
    double panelWidth = 400;
    double clearButtonWidth = 30;
    double searchBarYMin = 60;
    double searchBarYSpacing = 60;
    double searchBarFont = 11;
    
    std::vector<Buttons> vectorButtonsSearch;
    std::vector<Buttons> vectorButtonsClear;
    std::vector<Buttons> vectorButtonsDirections;    
    std::vector<Buttons> vectorButtonsDropDownList;
    std::vector<std::string> vectorTextsSearchPrompt {
            "Enter starting point, or click map",
            "Enter destination, or click map"};
    std::vector<std::string> vectorTextsSearchInput(2);
    std::vector<std::string> vectorTextsClear {"X", "X"};
    std::vector<std::string> DropDownIntNameVector;

}

void direction_ui::draw_panel(ezgl::renderer* g) {
    //set coordinate system to screen
    g->set_coordinate_system(ezgl::SCREEN);
    //set background colour of the interface
    g->set_color(ezgl::color(25, 0, 50, 250)); 
    //std:: cout<< "ok" << std::endl;
    double offset = 25;
    ezgl::rectangle rec = g->get_visible_screen();
    
    g->fill_rectangle({rec.width()-panelWidth, 0}, {rec.width(), rec.height() - offset}); 

    if (firstSearchInputValid && secondSearchInputValid) {
        drawDirectionsOnPanel(g);
    } 
    
    
    //draw Directions sign
    g->set_color(ezgl::WHITE);
    g->set_text_rotation(0);
    g->set_font_size(20);
    g->draw_text({rec.width()-panelWidth+80, 30}, "Directions");
    
    
    //draw clear buttons
    drawClearButtons(g);
    
    //draw search bars
    drawSearchBarsHelper(g);
    
    //draw outline of panel
    g->set_color(ezgl::BLACK);
    g->draw_rectangle({rec.width()-panelWidth, 0}, {rec.width(), rec.height()- offset});
    
    

    
    g->set_coordinate_system(ezgl::WORLD);
}

void direction_ui::drawSearchBarsHelper(ezgl::renderer *g) {
    drawSearchBars(g);
    
    //check if 1st searchBar is on
    if (firstSearchBarOn) {
        drawFirstSearchBarWhenItsOn(g); 
        //drawFirstSearchBarWhenItsOn(g);
    }
    
    if (secondSearchBarOn) {
        drawSecondSearchBarWhenItsOn(g);
    }
}
extern std::vector<std::string> write_directions(IntersectionIdx , IntersectionIdx);
void direction_ui::drawDirectionsOnPanel(ezgl::renderer *g) {
    ezgl::rectangle rec = g->get_visible_screen();
    int horizontalNum = 1; //number of buttons horizontally
    float buttonWidth = panelWidth-panelWidth; //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
    float buttonHeight = 30;
    float buttonXSpacing = 0; //horizontal space between the middle point of each button (set to 0 if you want it to be 
    float buttonYSpacing = buttonHeight ; //vertical space between the middle point of each button
    int fontSize = 13;	
    int numConstraint = 30; //set to negative if you don't have a maximum number constraint on how many buttons to show
    float xInitial = rec.width()-panelWidth/2;	//set to negative if you want buttons to be horizontally centered on the screen 
    float yInitial = rec.height()/3;
    
    
    std::vector<std::string> tempVecStr = write_directions(firstIntersectionID, secondIntersectionID);
    makeManyButtonsAlgorithm(g,
        drawADirectionButton,
        vectorButtonsDirections, //pass in a Vector of Button structs
        tempVecStr,
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

void direction_ui::drawFirstSearchBarWhenItsOn(ezgl::renderer *g) {
    ezgl::rectangle rec = g->get_visible_screen();
    //draw highlight around search bar
    g->set_color(ezgl::YELLOW);
    g->draw_rectangle({rec.width()-panelWidth+3, vectorButtonsSearch[0].ymin}, {rec.width(), vectorButtonsSearch[0].ymax});

}

void direction_ui::drawSecondSearchBarWhenItsOn(ezgl::renderer *g) {
    ezgl::rectangle rec = g->get_visible_screen();
    //draw highlight around search bar
    g->set_color(ezgl::YELLOW);
    g->draw_rectangle({rec.width()-panelWidth+3, vectorButtonsSearch[1].ymin}, {rec.width(), vectorButtonsSearch[1].ymax});

}

void direction_ui::drawSearchBars(ezgl::renderer *g) {
    ezgl::rectangle rec = g->get_visible_screen();
    
    //decide what texts to draw on searchBar
    std::vector<std::string> vectorSearchBarText;
    vectorSearchBarText.resize(2);
    if (vectorTextsSearchInput[0].size() == 0) {
        vectorSearchBarText[0] = vectorTextsSearchPrompt[0];
    }
    else if (vectorTextsSearchInput[0].size() > 0) {
        vectorSearchBarText[0] = vectorTextsSearchInput[0];
    }
    if (vectorTextsSearchInput[1].size() == 0) {
        vectorSearchBarText[1] = vectorTextsSearchPrompt[1];
    }
    else if (vectorTextsSearchInput[1].size() > 0) {
        vectorSearchBarText[1] = vectorTextsSearchInput[1];
    }
    //first call algorithm to make many buttons
    int horizontalNum = 1; //number of buttons horizontally
    float buttonWidth = panelWidth-clearButtonWidth; //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
    float buttonHeight = 35;
    float buttonXSpacing = 0; //horizontal space between the middle point of each button (set to 0 if you want it to be 
    float buttonYSpacing = searchBarYSpacing; //vertical space between the middle point of each button
    int fontSize = searchBarFont;	
    int numConstraint = -1; //set to negative if you don't have a maximum number constraint on how many buttons to show
    float xInitial = rec.width()-panelWidth;	//set to negative if you want buttons to be horizontally centered on the screen 
    float yInitial = searchBarYMin;
    makeManyButtonsAlgorithm(g,
        drawASearchBar,
        vectorButtonsSearch, //pass in a Vector of Button structs
        vectorSearchBarText,
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

void direction_ui::drawDropDownListHelper(ezgl::renderer *g, int searchBarIdx) {
    
    ezgl::rectangle rec = g->get_visible_screen();
    
    //first call algorithm to make many buttons
    int horizontalNum = 1; //number of buttons horizontally
    float buttonWidth = panelWidth - clearButtonWidth; //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
    float buttonHeight = 35;
    float buttonXSpacing = 0; //horizontal space between the middle point of each button (set to 0 if you want it to be 
    float buttonYSpacing = buttonHeight; //vertical space between the middle point of each button
    int fontSize = searchBarFont;	
    int numConstraint = -1; //set to negative if you don't have a maximum number constraint on how many buttons to show
    float xInitial = rec.width()-panelWidth;	//set to negative if you want buttons to be horizontally centered on the screen 
    float yInitial;
    if (searchBarIdx == 0) {
       yInitial = searchBarYMin+buttonHeight;
    }
    else {
        yInitial = searchBarYMin + searchBarYSpacing + buttonHeight;
    }
    
    makeManyButtonsAlgorithm(g,
        drawAClearButton,
        vectorButtonsDropDownList, //pass in a Vector of Button structs
        DropDownIntNameVector,
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

void direction_ui::drawDropDownListA(ezgl::renderer *g) {
    
    ezgl::rectangle rec = g->get_visible_screen();
    
    //first call algorithm to make many buttons
    int horizontalNum = 1; //number of buttons horizontally
    float buttonWidth = panelWidth - clearButtonWidth; //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
    float buttonHeight = 35;
    float buttonXSpacing = 0; //horizontal space between the middle point of each button (set to 0 if you want it to be 
    float buttonYSpacing = buttonHeight; //vertical space between the middle point of each button
    int fontSize = searchBarFont;	
    int numConstraint = -1; //set to negative if you don't have a maximum number constraint on how many buttons to show
    float xInitial = rec.width()-panelWidth;	//set to negative if you want buttons to be horizontally centered on the screen 
    float yInitial = searchBarYMin+buttonHeight;
  
    
    makeManyButtonsAlgorithm(g,
        drawAClearButton,
        vectorButtonsDropDownList, //pass in a Vector of Button structs
        DropDownIntNameVector,
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

void direction_ui::drawDropDownListB(ezgl::renderer *g) {
    
    ezgl::rectangle rec = g->get_visible_screen();
    
    //first call algorithm to make many buttons
    int horizontalNum = 1; //number of buttons horizontally
    float buttonWidth = panelWidth - clearButtonWidth; //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
    float buttonHeight = 35;
    float buttonXSpacing = 0; //horizontal space between the middle point of each button (set to 0 if you want it to be 
    float buttonYSpacing = buttonHeight; //vertical space between the middle point of each button
    int fontSize = searchBarFont;	
    int numConstraint = -1; //set to negative if you don't have a maximum number constraint on how many buttons to show
    float xInitial = rec.width()-panelWidth;	//set to negative if you want buttons to be horizontally centered on the screen 
    float yInitial = searchBarYMin + searchBarYSpacing + buttonHeight;
  
    
    makeManyButtonsAlgorithm(g,
        drawAClearButton,
        vectorButtonsDropDownList, //pass in a Vector of Button structs
        DropDownIntNameVector,
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

void direction_ui::drawClearButtons(ezgl::renderer *g) {
    ezgl::rectangle rec = g->get_visible_screen();
    //first call algorithm to make many buttons
    int horizontalNum = 1; //number of buttons horizontally
    float buttonWidth = clearButtonWidth; //you can type in negative (ex:-0.3 if you want it fixed to 30 percent of screen width)
    float buttonHeight = 35;
    float buttonXSpacing = 0; //horizontal space between the middle point of each button (set to 0 if you want it to be 
    float buttonYSpacing = searchBarYSpacing; //vertical space between the middle point of each button
    int fontSize = searchBarFont;	
    int numConstraint = -1; //set to negative if you don't have a maximum number constraint on how many buttons to show
    float xInitial = rec.width()-clearButtonWidth;	//set to negative if you want buttons to be horizontally centered on the screen 
    float yInitial = searchBarYMin;
    makeManyButtonsAlgorithm(g,
        drawAClearButton,
        vectorButtonsClear, //pass in a Vector of Button structs
        vectorTextsClear,
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


void direction_ui::drawADirectionButton(double xMin, double yMin, float boxWidth, float boxHeight, std::string name, ezgl::renderer *g, int fontSize) {
    g->set_coordinate_system(ezgl::SCREEN);
    g->set_color(ezgl::WHITE);
    g->set_text_rotation(0);
    g->set_font_size(fontSize);
    g->draw_text({xMin+boxWidth/2, yMin+boxHeight/2}, name); 
}

std::vector<std::string> DirectionUI:: getDropDownIntNameVector(std::vector<int> &dropDownIDsVector) {
    int loopCount; 
    if (dropDownIDsVector.size() > maxDropDownListSize)
        loopCount = maxDropDownListSize;
    else loopCount = dropDownIDsVector.size();
    
    DropDownIntNameVector.resize(loopCount);
    for (int i = 0; i < loopCount; i++) {
        int tempIdx = dropDownIDsVector[i];
        DropDownIntNameVector[i] = getIntersectionName(tempIdx);
    } 
    return DropDownIntNameVector;
}
void direction_ui::actOnReturnPressed (ezgl::application *app, std::vector<int> dropDownIDsVector, std::vector<std::string> dropDownNamesVector) {
    if (vectorTextsSearchInput[0].length() > 0) {
        if (dropDownNamesVector.size() == 0 || dropDownIDsVector.size() == 0) {
            return;
        }
        generalSetIntersectionValidity(dropDownIDsVector[0], dropDownNamesVector[0]);   
        app->refresh_drawing();
    }    
}

extern std::vector<StreetIdx> findIntersectionIdsFromPartialStreetName(std::string int_prefix);
void direction_ui::reactToKeyboard(ezgl::application *app, char *key_name){
    //first process the key input and put in string
    std::string keyName = key_name;
    ezgl::renderer *g = app->get_renderer();
    
    if (firstSearchBarOn) {
        searchBarReactToKeyboard(
        maxDropDownListSize,
        app, 
        key_name,
        vectorTextsSearchInput[0],
        DropDownIntNameVector,
        findIntersectionIdsFromPartialStreetName,
        getDropDownNames,
        getIntersectionName,
        draw_panel,
        drawDropDownListA,
        actOnReturnPressed);
    }
    if (secondSearchBarOn) {
        searchBarReactToKeyboard(
        maxDropDownListSize,
        app, 
        key_name,
        vectorTextsSearchInput[1],
        DropDownIntNameVector,
        findIntersectionIdsFromPartialStreetName,
        getDropDownNames,
        getIntersectionName,
        draw_panel,
        drawDropDownListB,
        actOnReturnPressed);
    } 
}

void direction_ui::setTextInputValidity(int searchBarIndex) {
		//unnecessary atm
}



void direction_ui::reactToMouseClick(ezgl::application* app, GdkEventButton* event, double worldX, double worldY) {
    ezgl::renderer* g = app->get_renderer();
    g->set_coordinate_system(ezgl::SCREEN);
    ezgl::rectangle rec = g->get_visible_screen();

    double x = event->x; //std:: cout << x << std::endl;
    double y = event->y;    
    double panelXMin = rec.width()-panelWidth; //std:: cout << "xmin" << rec.width() << std::endl;
    
    //check if searchBar 1 or 2 is clicked
    int numButtons = vectorButtonsSearch.size();
    for (int i = 0; i < numButtons; i++) {
        if (x > vectorButtonsSearch[i].xmin && x < vectorButtonsSearch[i].xmax) {
            if (y > vectorButtonsSearch[i].ymin && y < vectorButtonsSearch[i].ymax) {
                
                //the following you should replace depending on your own logic
                if (i == 0) {
                    turnStatesOffExceptHighlight(); //set all states to false which ensures only the next state can be open
                    
                    open = true;
                    //secondSearchBarOn = false;
                    firstSearchBarOn = true; //set the state you want to enter to be open
                }
                if (i == 1) { 
                    turnStatesOffExceptHighlight();
                    //std::cout<<"secondButtonClicked" << std::endl;
                    open = true; 
                    //firstSearchBarOn = false;
                    secondSearchBarOn = true; //set the state you want to enter to be open
                }    
                
                return;
            }
        }
    }
    numButtons = vectorButtonsClear.size();
    for (int i = 0; i < numButtons; i++) {
        if (x > vectorButtonsClear[i].xmin && x < vectorButtonsClear[i].xmax) {
            if (y > vectorButtonsClear[i].ymin && y < vectorButtonsClear[i].ymax) {
                if (i == 0) {
                    vectorTextsSearchInput[i].clear();
                    secondSearchBarOn = false;
                    int_data.vectorIntPositionXY[firstIntersectionID].highlight = false;
                    firstSearchInputValid = false;
                    firstSearchBarOn = true;
                }
                if (i == 1) {
                    firstSearchBarOn = false;
                    vectorTextsSearchInput[i].clear();
                    secondSearchInputValid = false;
                    int_data.vectorIntPositionXY[secondIntersectionID].highlight = false;
                    secondSearchBarOn = true;
                }
                app->refresh_drawing();
                return;
            }
        }
    }
    ////if search bar is on
    
    //else it is the standby state
    //unhighlight searchBar if necessary
    if (firstSearchBarOn || secondSearchBarOn) {
        //setPrevHighlightFalse();
        
        //if user is clicking on map, must react accordingly
        if (x < panelXMin) { 
            setStateOfHighlightsWhenSearchBarOn(app, worldX, worldY); //for future
            //intSelected == true; 
            if (intSelected) {
                setIntersectionSelectValidity(app, worldX, worldY); //std::cout<< panelXMin << std::endl;
                app->refresh_drawing();
                return;
            }
            
            //if POISelected ...
            //return;
        }
        else if (x > panelXMin) {
            //will let user free roam map
            //turnAllButtonsOff();
            turnStatesOffExceptHighlight();
            open = true;
            setStateOfIntPOI(app, worldX, worldY); //std::cout<< panelXMin << std::endl;
            app->refresh_drawing();
            return;
        }
        //app->refresh_drawing();
        //return;
        
    } 
    //will let user free roam map
    //turnAllButtonsOff();
    turnStatesOffExceptHighlight();
    open = true;
    setStateOfIntPOI(app, worldX, worldY); //std::cout<< panelXMin << std::endl;
    app->refresh_drawing();
}
extern int getIntersectionIDAndHighlight( double x, double y);

void direction_ui::setIntersectionSelectValidity(ezgl::application* app, double x, double y) {
    
    app->get_renderer(); //not used
    if (DirectionUI::firstSearchInputValid && DirectionUI::secondSearchInputValid) {
        //if both are valid we must set one of the intersection highlight to false
        if (firstSearchBarOn) {
            //must erase the original highlight
            int_data.vectorIntPositionXY[firstIntersectionID].highlight = false;
            
        }
        else if(secondSearchBarOn) {
            int_data.vectorIntPositionXY[secondIntersectionID].highlight = false;
        }
    }
    
    
    //call function to set global highlight to true for the clicked intersection and return its ID
    //ex: int ID = getIntersectionIDAndHighlight(app, x, y);
    
    int ID = getIntersectionIDAndHighlight(x, y);
        
    //call function to get the name of the intersection
    //ex: std::string intName = getIntersectionName(ID);
    std::string intName = getIntersectionName(ID);
    
    generalSetIntersectionValidity(ID, intName);
        
} 

void direction_ui::generalSetIntersectionValidity(int ID, std::string intName) {

    //if no intersection has been chosen
    if (DirectionUI::firstSearchInputValid == false && DirectionUI::secondSearchInputValid == false) {
        //store ID and name into the class depending on whether first or second search bar is on
        if (DirectionUI::firstSearchBarOn) {           
            turnAllButtonsOff();
            DirectionUI::open = true;
            DirectionUI::firstSearchInputValid = true;
            DirectionUI::secondSearchBarOn = true;
            DirectionUI::firstIntersectionID = ID;
            DirectionUI::vectorTextsSearchInput[0] = intName;
            int_data.vectorIntPositionXY[ID].highlight = true; 
        }
        else if (DirectionUI::secondSearchBarOn) {   
            turnAllButtonsOff();
            DirectionUI::open = true;
            DirectionUI::secondSearchInputValid = true;
            DirectionUI::firstSearchBarOn = true;
            DirectionUI::secondIntersectionID = ID;
            DirectionUI::vectorTextsSearchInput[1] = intName;
            int_data.vectorIntPositionXY[ID].highlight = true; 
        }
    }         
    
    else if (DirectionUI::secondSearchBarOn) {       
        //first set previous highlight to false
        int_data.vectorIntPositionXY[DirectionUI::secondIntersectionID].highlight = false;
        
        DirectionUI::secondSearchInputValid = true;
        DirectionUI::secondSearchBarOn = false;
        DirectionUI::secondIntersectionID = ID;
        DirectionUI::vectorTextsSearchInput[1] = intName;
        //set new highlight to true
        int_data.vectorIntPositionXY[ID].highlight = true; 
    }
    
    else if (DirectionUI::firstSearchBarOn) {
        int_data.vectorIntPositionXY[DirectionUI::firstIntersectionID].highlight = false;
        DirectionUI::firstSearchInputValid = true;
        DirectionUI::firstSearchBarOn = false;
        DirectionUI::firstIntersectionID = ID;
        DirectionUI::vectorTextsSearchInput[0] = intName;
        int_data.vectorIntPositionXY[ID].highlight = true; 
    }
}




void direction_ui::setStateOfIntPOI(ezgl::application* app, /*GdkEventButton* event ,*/ double x, double y) {
    ezgl::renderer* g = app->get_renderer();
        g->set_coordinate_system(ezgl::WORLD);

    
    
    //Declaring Latlon positions for user input, POIs, and Intersections
    //Declaring IDs for position and intersections
    //Calculating the distance between mouse and POI vs mouse and intersection
    LatLon pos = LatLon(y, x);
    LatLon mouse_pos = LatLon(getLatFromY(pos.latitude()), getLonFromX(pos.longitude()));
    int POI_id = findClosestPOINoName(pos);
    int inter_id = findClosestIntersection(mouse_pos);
    LatLon inter_pos = int_data.vectorIntPosition[inter_id];
    LatLon POI_pos = vectorPOI[POI_id].position;
    auto mousePOI = std::make_pair (mouse_pos, POI_pos);
    auto mouseIntersection = std::make_pair (mouse_pos, inter_pos);
    double POIDistance = findDistanceBetweenTwoPoints(mousePOI);
    double IntersectionDistance = findDistanceBetweenTwoPoints(mouseIntersection);
    
    //std::cout<<"yes" << std:: endl;
    //If statements determine which entities to highlight and which not to
    //Inside If statement checks if previous markings were clicked and un-highlights them
    if(POIDistance < IntersectionDistance && POIDistance < 25 && vectorPOI[POI_id].highlight == true){
        if(highlightChecker(POIOn, interOn)){ 
            vectorPOI[prevId].highlight = false;
            int_data.vectorIntPositionXY[prevId].highlight = false;
        }
        vectorPOI[POI_id].highlight = false;
        prevId = POI_id;
        POIOn = false;
    }else if(POIDistance < IntersectionDistance && POIDistance < 25 && vectorPOI[POI_id].highlight ==  false){ 
        if(highlightChecker(POIOn, interOn)){ 
            vectorPOI[prevId].highlight = false;
            int_data.vectorIntPositionXY[prevId].highlight = false;
        }
        vectorPOI[POI_id].highlight = true;
        prevId = POI_id;
        POIOn = true;
    }else if(IntersectionDistance < POIDistance && IntersectionDistance < 10 && int_data.vectorIntPositionXY[inter_id].highlight == true){
        if(highlightChecker(POIOn, interOn)){ 
            vectorPOI[prevId].highlight = false;
            int_data.vectorIntPositionXY[prevId].highlight = false;
        }
        int_data.vectorIntPositionXY[inter_id].highlight = false;
        prevId = inter_id;
        interOn = false;     
    }else if(IntersectionDistance < POIDistance && IntersectionDistance < 10 && int_data.vectorIntPositionXY[inter_id].highlight == false){
        if(highlightChecker(POIOn, interOn)){ 
            vectorPOI[prevId].highlight = false;
            int_data.vectorIntPositionXY[prevId].highlight = false;
        }
        int_data.vectorIntPositionXY[inter_id].highlight = true; 
        //std::cout<<"interOn" << std:: endl;
        prevId = inter_id;
        interOn = true;
    }
}

void direction_ui::setPrevHighlightFalse() {
    
  
    /*if (POIOn) {
        vectorPOI[prevId].highlight = false;
        POIOn = false;
    } */
    
    if (interOn) {
        int_data.vectorIntPositionXY[prevId].highlight = false;
        interOn = false;
    }
}

void direction_ui::setStateOfHighlightsWhenSearchBarOn(ezgl::application* app, double x, double y) {
    ezgl::renderer* g = app->get_renderer();
        g->set_coordinate_system(ezgl::WORLD);

        

        intSelected = false; 
    
    //Declaring Latlon positions for user input, POIs, and Intersections
    //Declaring IDs for position and intersections
    //Calculating the distance between mouse and POI vs mouse and intersection
    LatLon pos = LatLon(y, x);
    LatLon mouse_pos = LatLon(getLatFromY(pos.latitude()), getLonFromX(pos.longitude()));
    int inter_id = findClosestIntersection(mouse_pos);
    LatLon inter_pos = int_data.vectorIntPosition[inter_id];
    auto mouseIntersection = std::make_pair (mouse_pos, inter_pos);
    double IntersectionDistance = findDistanceBetweenTwoPoints(mouseIntersection);

    //check if int selected
    if (IntersectionDistance < 60 && int_data.vectorIntPositionXY[inter_id].highlight == false) {
        
        intSelected = true;
    }
    
}



