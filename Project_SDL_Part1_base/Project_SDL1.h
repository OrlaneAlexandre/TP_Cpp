// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <ctime>

using namespace std;

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

class animal {
protected:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
  // todo: Attribute(s) to define its position
  int x_;
  int y_;
  int dirx_;
  int diry_;
  int h_;
  int l_;
  bool isPrey;
  bool isPredator;
  bool female;
  bool alive;
  bool berg;
  bool isdog;
  int rep;
  

public:
  animal(const string& file_path, SDL_Surface* window_surface_ptr);
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
  ~animal(); // todo: Use the destructor to release memory and "clean up
               // behind you"

  void draw() {
	  if (alive)
	  {
		  auto rect = SDL_Rect{ x_, y_, h_, l_ };
		  if (SDL_BlitSurface(image_ptr_, NULL, window_surface_ptr_, &rect))
			  throw runtime_error("Could not apply texture");
	  }
  } // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

  virtual void move() {
	  cout << "move animal\n";	  
  }
  // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
  
  virtual void setBergX(int x) {}
  virtual void setBergY(int y) {}
							 
  int getX() { return x_;}
  int getY() { return y_;}
  void setX(int x) { x_ = x;}
  void setY(int y) { y_ = y;}
  int getDirX() { return dirx_;}
  int getDirY() { return diry_;}
  void setDirX(int dirx) {  dirx_ = dirx;}
  void setDirY(int diry) { diry_ = diry;}
  bool getPrey() const { return isPrey; }
  void setIsPrey() { isPrey = ! isPrey;}
  bool getPredator() const { return isPredator; }
  void setIsPredator() { isPredator = ! isPredator;}
  bool getFemale() const { return female; }
  void SetFemale() { female = !female;}
  bool getIsAlive() const { return alive; }
  void setAlive() { alive = !alive; }
  bool getBerg() const { return berg; }
  void setBerg() { berg = !berg; }
  bool getDog() const { return isdog; }
  void setDog() { isdog = !isdog; }
  int getRepos() { return rep; }
  void setRepos( int repos) { rep = repos; }
  int getPos() { return x_, y_, h_, l_; }
  
  void setWindow_surface_ptr_(SDL_Surface* window_surface_ptr) {
	  window_surface_ptr_ = window_surface_ptr;
  }
};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {
private:

	int h_ = 67;
    int l_ = 71;
 
public:
	sheep(const string& file_path, SDL_Surface* window_surface_ptr) :
		animal(file_path, window_surface_ptr) {
		x_ = rand()%1000;
		y_ = rand() % 500;
		dirx_ = 2;
		diry_ = 2;
		alive = true;
		if (rand() % 2 == 1) {
			female = true;
		}
		else {
			female = false;
		} 
		isPrey = true;
		isPredator = false;
		berg = false;
		isdog = false;
		rep = 0;
	}
    
	~sheep();
  
    void move();
  // implement functions that are purely virtual in base class
};



// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves
class wolf : public animal {
private:

	int h_ = 62;
    int l_ = 42;

public:
    wolf(const string& file_path, SDL_Surface* window_surface_ptr):
	animal(file_path, window_surface_ptr) {
		x_ = rand() % 1000;
		y_ = rand() % 500;
		dirx_ = 1;
		diry_ = 1;
		alive = true;
		isPrey = false;
		isPredator = true;
		berg = false;
		isdog = false;
		rep = 0;
	}
    // Ctor
	~wolf();

    void move();
        // implement functions that are purely virtual in base class
};

class berger : public animal {

private:

	int h_ = 42;
    int l_ = 62;

public:

    berger(const string& file_path, SDL_Surface* window_surface_ptr):
	animal(file_path, window_surface_ptr) {
		x_ = rand() % 1000;
		y_ = rand() % 500;
		dirx_ = 2;
		diry_ = 2;
		alive = true;
		isPrey = false;
		isPredator = false;
		berg = true;
		isdog = false;
		rep = 0;
	}

	~berger();

    void move(); 

};

class dog : public animal {
private:

    int h_ = 62;
    int l_ = 42;
	int angle;
	int bergX;
	int bergY;

public: 
    dog(const string& file_path, SDL_Surface* window_surface_ptr):
	animal(file_path, window_surface_ptr) {
		x_ = rand() % 1000;
		y_ = rand() % 500;
		dirx_ = 2;
		diry_ = 2;
		alive = true;
		bergX = 0;
		bergY = 0; 
		angle = 0;
		isPrey = false;
		isPredator = false;
		berg = false;
		isdog = true;
		rep = 0;
	}

    void move();
	
	void setBergX(int x) {
		bergX = x;
	}
	
	void setBergY(int y) {
		bergY = y;
	}
};

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;
  vector<animal*>& animals_;
  unsigned framerate_;

  // Some attribute to store all the wolves and sheep
  // here

public:
  ground(SDL_Surface* window_surface_ptr, int n_sheep, int n_wolf); // todo: Ctor
  
  ~ground();
   // todo: Dtor, again for clean up (if necessary)

  void add_animal(animal* ptr_animal); // todo: Add an animal

  void update(SDL_Window* window_ptr_);
  // todo: "refresh the screen": Move animals and draw them
  // Possibly other methods, depends on your implementation
  void moveAll();
  void drawAll();

  void setWindow_surface_ptr_(SDL_Surface* window_surface_ptr)
  {
      window_surface_ptr = window_surface_ptr;
  }

  void setW_(SDL_Surface* setWindow_surface_ptr, int n)
  {
      this->animals_[n]->setWindow_surface_ptr_(setWindow_surface_ptr);
  }

  int getN() {
      return animals_.size();
  }
};

// The application class, which is in charge of generating the window
class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;

  // Other attributes here, for example an instance of ground
  ground* ground_;


public:
    application(unsigned n_sheep, unsigned n_wolf); //ctor
    ~application();// dtor

    int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                            // 'period' seconds
  
};