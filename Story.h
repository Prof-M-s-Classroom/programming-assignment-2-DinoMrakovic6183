#ifndef STORY_H
#define STORY_H

#include <string>
using namespace std;

class Story {
public:
    string description;      // Text representing what happens at this point in the game
    int eventNumber;         // Unique identifier for each event
    int leftEventNumber;     // Event number if the player chooses the left path
    int rightEventNumber;    // Event number if the player chooses the right path

    // Default constructor
    Story();

    // Parameterized constructor
    Story(string desc, int num, int leftNum, int rightNum);
};

#endif // STORY_H