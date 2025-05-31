#include <conio.h>          //for _getch() which will pause until any key is pressed
#include "src/grenadier.h"
#include "src/SFML_Application.h"
#include "src/soldier.h"

int main()
{
    SFML_Application window(1920, 1080, false);
    window.run();

    return 0;
}