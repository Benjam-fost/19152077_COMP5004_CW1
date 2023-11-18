//
// Created by DrMark on 10/4/2017.
//

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>

// ROOM STRINGS
const std::string r1name = "Crossroad";
const std::string r1desc = "It's really quite boring here, but then, it's just for testing really. A strangled whisper scratches at your psyche. \nThere's a passage to the North, South, East and West.";
const std::string r2name = "Blue Room";
const std::string r2desc = "It's blue. That's about all though. \nThere's a passage to the south.";
const std::string r3name = "Red Room";
const std::string r3desc = "It's red. That's about all though. \nThere's a passage to the north.";
const std::string r4name = "Green Room";
const std::string r4desc = "It's green. That's about all though. \nThere's a passage to the west.";
const std::string r5name = "Purple Room";
const std::string r5desc = "It's purple. \nThat's about all though, except from some fluffy pillows. \nThere's a passage to the east.";

// large cup
const std::string largeCupName = "Large cup";
const std::string largeCupKey = "large cup";
const std::string largeCupDesc = "A rather sizable cup that draws the eye.\nIt feels as if it calls to you to pick it up.";

// shiny bowl
const std::string shinyBowlName = "Shiny bowl";
const std::string shinyBowlKey = "shiny bowl";
const std::string shinyBowlDesc = "A very shiny bowl that seems to be glaring at you.\nLight seems the warp around it; that doesn't seem very utilitarian.";

// fluffy bowl
const std::string fluffyPillowName = "Fluffy pillow";
const std::string fluffyPillowKey = "fluffy pillow";
const std::string fluffyPillowDesc = "A scrumptiously fluffy pillow.\nYou can't tell if your hunger is yours or the pillow's\nAs you look at it you feel a bone-deep weariness permeate your being.";

// silver spoon
const std::string silverSpoonName = "Silver spoon";
const std::string silverSpoonKey = "silver spoon";
const std::string silverSpoonDesc = "A spoon made of solid silver.\nYou wonder if someone rich came through here.";

// ERROR MESSAGES
const std::string inRoom = "The object is already in the room";
const std::string notInRoom = "You could not find the object in the room.";
const std::string inInventory = "You cannot get an object from within your inventory";
const std::string notInInventory = "You couldn't find the object within your inventory";
const std::string emptyInventory = "Your inventory is empty.";
const std::string noObject = "You don't know what you're looking for.";
const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that.";

// COMPLETION MESSAGES
const std::string dropped = "You dropped the object";
const std::string got = "You picked up the object";

#endif //TEXTADV_STRINGS_H
