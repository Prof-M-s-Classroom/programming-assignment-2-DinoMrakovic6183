#include "Story.h"

// Default constructor initializes description as empty, eventNumber as 0,
// and both left and right event numbers as -1 (indicating no subsequent events).
Story::Story() : description(""), eventNumber(0), leftEventNumber(-1), rightEventNumber(-1) {}

// Parameterized constructor initializes all members based on provided values.
Story::Story(string desc, int num, int leftNum, int rightNum)
    : description(desc), eventNumber(num), leftEventNumber(leftNum), rightEventNumber(rightNum) {}
