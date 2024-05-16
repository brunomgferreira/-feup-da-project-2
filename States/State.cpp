#include "State.h"

// Function to wait for user to press Enter to continue
void State::PressEnterToContinue(int numPresses) {
    cout << "Press ENTER to continue... "; // Prompt user to press Enter

    for (int i = 0; i < numPresses; ++i)
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore input up to newline character
}
