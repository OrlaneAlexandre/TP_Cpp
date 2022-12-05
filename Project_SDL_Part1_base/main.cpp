#include "Project_SDL1.h"
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

  cout << "Starting up the application" << endl;

  if (argc != 4)
    throw runtime_error("Need three arguments - "
                             "number of sheep, number of wolves, "
                             "simulation time\n");

  init();

  cout << "Done with initilization" << endl;

  application my_app(stoul(argv[1]), stoul(argv[2]));

  cout << "Created window" << endl;

  int retval = my_app.loop(stoul(argv[3]));

  cout << "Exiting application with code " << retval << endl;

  SDL_Quit();

  return retval;
}