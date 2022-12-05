// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

using namespace std;


void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw runtime_error("init():" + string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             string(IMG_GetError()));
}

namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Surface* load_surface_for(const string& path,
                              SDL_Surface* window_surface_ptr) {
    return IMG_Load(path.c_str());
  // Helper function to load a png for a specific surface
  // See SDL_ConvertSurface
}
} // namespace

bool collisionMurHauteur(int x_, int l_)
{
    if (x_ < frame_boundary || (x_ + l_) > (frame_width - frame_boundary))
    {
        return true;
    }
    return false;
}

bool collisionMurLargeur(int y_, int h_)
{
    if (y_ < frame_boundary || (y_ + h_) > (frame_height - frame_boundary))
    {
        return true;
    }
    return false;
}

bool collision(int x1, int y1, int h1, int l1, int x2, int y2, int h2, int l2)
{
    int gaucheA = x1;
    int droiteA = x1 + l1;
    int hautA = y1;
    int basA = y1 + h1;

    int gaucheB = x2;
    int droiteB = x2 + l2;
    int hautB = y2;
    int basB = y2 + h2;

    if (basA <= hautB || hautA >= basB || droiteA <= gaucheB || gaucheA >= droiteB)
    {
        return false;
    }
    return true;
}

bool collision(animal* A, animal* B)
{
    int x1, y1, h1, l1 = A->getPos();
    int x2, y2, h2, l2 = B->getPos();

    return collision(x1, y1, h1, l1, x2, y2, h2, l2);
}

animal::animal(const string& file_path, SDL_Surface* window_surface_ptr)
{
	isPrey = false;
	isPredator = false;
	female = false;
    alive = true;
	berg = false;
	isdog = false;
	
	image_ptr_ = IMG_Load(file_path.data());
	if (!image_ptr_)
		throw runtime_error("Could not load image");
	window_surface_ptr_ = window_surface_ptr;
	
    x_ = rand() % 1000;
    y_ = rand() % 500;
    dirx_ = (rand() % 2);
    diry_ = (rand() % 2);
	if (dirx_ ==0) {
		dirx_ = -1;
	}
	if (diry_ ==0) {
		diry_ = -1;
	}
	
}

animal::~animal()
{
    SDL_FreeSurface(window_surface_ptr_);
}



void sheep::move()
{
    if (alive)
    {   
        x_ += dirx_;
        y_ += diry_;
        if (collisionMurHauteur(x_, l_))
        {
            dirx_ = -dirx_;
            x_ += dirx_;
        }
        if (collisionMurLargeur(y_, h_))
        {
            diry_ = -diry_;
            y_ += diry_;
        }
    }
}



void wolf::move()
{
    if (alive)
    {
        x_ += dirx_;
        y_ += diry_;
        if (collisionMurHauteur(x_, l_))
        {
            dirx_ = -dirx_;
            x_ += dirx_;
        }
        if (collisionMurLargeur(y_, h_))
        {
            diry_ = -diry_;
            y_ += diry_;
        }
    }
}


void berger::move()
{
    if (alive)
    {
        x_ += dirx_;
        y_ += diry_;
        if (collisionMurHauteur(x_, l_))
        {
            dirx_ = -dirx_;
            x_ += dirx_;
        }
        if (collisionMurLargeur(y_, h_))
        {
            diry_ = -diry_;
            y_ += diry_;
        }
    }
};


void dog::move() 
{
    if (alive)
    {
        double m = angle / (20 * 3.141);
		setX(cos(m) * 50 + bergX);
		setY(sin(m) * 50 + bergY);
		angle = (angle + 1) % 360;
    }
    
}
 

ground::ground(SDL_Surface* window_surface_ptr, int n_sheep, int n_wolf)
{
    window_surface_ptr = window_surface_ptr; 
    animal* berg(new berger("berger.png", window_surface_ptr));
    animals_.push_back(berg);
    for (int i = 0; i < n_sheep; i++) {
        animal* s(new sheep("sheep.png",window_surface_ptr));
        animals_.push_back(s);
    }
    for (int i = 0; i < n_wolf; i++) {
        animal* w(new wolf("wolf.png", window_surface_ptr));
        animals_.push_back(w);
    }
    animal* d(new dog("dog.png", window_surface_ptr));
    animals_.push_back(d);
}

ground::~ground() {
    free(window_surface_ptr_);
} 

void ground::add_animal(animal* ptr_animal) {
    ground::animals_.push_back(ptr_animal);
}


bool interRect(int a_x, int a_y, int b_x, int b_y) {
    if (a_x >= b_x && a_x <= b_x + 50 && a_y >= b_y && a_y <= b_y + 50) { return true; }
	
    if (a_x + 50 >= b_x && a_x + 50 <= b_x + 50 && a_y >= b_y && a_y <= b_y + 50) { return true; }
	
	if (a_x + 50 >= b_x && a_x + 50 <= b_x + 50 && a_y+50 >= b_y && a_y+50 <= b_y + 50) { return true; }
		
    if (a_x >= b_x && a_x <= b_x + 50 && a_y+50 >= b_y && a_y+50 <= b_y + 50) { return true;}

	return false;
}

void ground::moveAll() {

    int bergX = 0;
    int bergY = 0;

    for (int i = 0; i < animals_.size(); i++) {
        if (animals_[i]->getPredator() == true) {
            double dogDistance = 300;
            int idog = 0;
            double preyDistance = 10000000;
            int prey = 0;
            double distX = 0;
            double distY = 0;
            double dist = 0;

            for (int j = 0; j < animals_.size(); j++) {
                distX = sqrt((animals_[j]->getX() - animals_[i]->getX()) * (animals_[j]->getX() - animals_[i]->getX()));
                distY = sqrt((animals_[j]->getY() - animals_[i]->getY()) * (animals_[j]->getY() - animals_[i]->getY()));
                dist = distX + distY;

                if (animals_[j]->getDog() == true) {
                    if (dist < dogDistance) {
                        dogDistance = dist;
                        idog = j;
                    }
                }

                if (animals_[j]-> getPrey() == true) {
                    cout << animals_[i]->getX() << " " << animals_[j]->getX() << "  " << animals_[i]->getY() << " " << animals_[j]->getY() << "\n";
                    if (interRect(animals_[i]->getX(),animals_[i]->getY(), animals_[j]->getX(),animals_[j]->getY())) {
                        cout << "manger\n";
                        vector < animal*> it = iterator; 
                        it = animals_.begin()+j; 
                        animals_.erase(it);
                    }
                    else if (dist < preyDistance) {
                        preyDistance = dist;
                        prey = j;
                    }
                }
            }
            if (dogDistance < 200) {
                distX = animals_[idog]->getX() - animals_[i]->getX();
                distY = animals_[idog]->getY() - animals_[i]->getY();
                if (distX == 0) {
                    distX = 1;
                }
                if (distY == 0) {
                    distY = 1;
                }
                animals_[i]->setDirX(-(distX / sqrt(distX * distX)));
                animals_[i]->setDirY(-(distY / sqrt(distY * distY)));
            }
            else if (dogDistance >= 300) {
                distX = animals_[prey]->getX() - animals_[i]->getX();
                distY = animals_[prey]->getY() - animals_[i]->getY();
                if (distX == 0) {
                    distX = 1;
                }
                if (distY == 0) {
                    distY = 1;
                }
                animals_[i]->setDirX((distX / sqrt(distX * distX)));
                animals_[i]->setDirY((distY / sqrt(distY * distY)));
            }
        }

        else if (animals_[i]->getPrey() == true) {
            if (animals_[i]->getRepos() > 0) {
                animals_[i]->setRepos(animals_[i]->getRepos() - 1);
            }

            double predatorDistance = 10000000;
            int predator = 0;
            double distX = 0;
            double distY = 0;
            double dist = 0;

            for (int j = 0; j < animals_.size(); j++) {
                if (animals_[j]->getPrey()) {
                    if (interRect(animals_[i]->getX(), animals_[i]->getY(), animals_[j]->getX(), animals_[j]->getY())) {
                        if ((animals_[j]->getFemale() && animals_[i]->getFemale() == false && animals_[j]->getRepos() == 0) || (animals_[i]->getFemale() && animals_[j]->getFemale() == false && animals_[i]->getRepos() == 0)) {
                            animals_[i]->setRepos(1500);
                            animals_[j]->setRepos(1500);
                            animal* s(new sheep("sheep.png",window_surface_ptr_));
                            animals_.push_back(s);
                        }
                    }
                }
                distX = sqrt((animals_[j]->getX() - animals_[i]->getX()) * (animals_[j]->getX() - animals_[i]->getX()));
                distY = sqrt((animals_[j]->getY() - animals_[i]->getY()) * (animals_[j]->getY() - animals_[i]->getY()));
                dist = distX + distY;

                if (animals_[j]->getPredator() == true) {
                    if (dist < predatorDistance) {
                        predatorDistance = dist;
                        predator = j;
                    }
                }
            }
            if (predatorDistance < 300) {
                distX = animals_[predator]->getX() - animals_[i]->getX();
                distY = animals_[predator]->getY() - animals_[i]->getY();
                if (distX == 0) {
                    distX = 1;
                }
                if (distY == 0) {
                    distY = 1;
                }
                animals_[i]->setDirX(-(distX / sqrt(distX * distX)) * 3);
                animals_[i]->setDirY(-(distY / sqrt(distY * distY)) * 3);
            }
            if (predatorDistance > 400) {
                animals_[i]->setDirX(animals_[i]->getDirX() % 2);
                animals_[i]->setDirY(animals_[i]->getDirY() % 2);
            }
        }

        if (animals_[i]->getBerg()) {

            bergX = animals_[i]->getX();
            bergY = animals_[i]->getY();

            const Uint8* key = SDL_GetKeyboardState(nullptr);
            animals_[i]->setDirX(0);
            animals_[i]->setDirY(0);
            if (key[SDL_SCANCODE_UP]) {
                animals_[i]->setDirY(-1);
            }
            if (key[SDL_SCANCODE_DOWN]) {
                animals_[i]->setDirY(1);
            }
            if (key[SDL_SCANCODE_RIGHT]) {
                animals_[i]->setDirX(1);
            }
            if (key[SDL_SCANCODE_LEFT]) {
                animals_[i]->setDirX(-1);
            }
        }

        if (animals_[i]->getDog()) {
            animals_[i]->setBergX(bergX);
            animals_[i]->setBergY(bergY);
        }

        animals_[i]->move();
    }
}


void ground::drawAll()
{
    SDL_FillRect(window_surface_ptr_, NULL, SDL_MapRGB(window_surface_ptr_->format, 0, 200, 0));
    for (int i = 0; i < getN(); i++) {
        animals_[i]->draw();
    }
}


void ground::update(SDL_Window* window_ptr_)
{
    moveAll();
    drawAll();
    SDL_UpdateWindowSurface(window_ptr_);
    
}

application::application(unsigned n_sheep, unsigned n_wolf)
{
    window_ptr_ = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        frame_width, frame_height, 0);
    if (NULL == window_ptr_)
        throw runtime_error("application(.) : SDL_CreateWindow could not initialize! "
            "SDL_image Error: " + string(SDL_GetError()));

    auto window_surface_ptr = SDL_GetWindowSurface(window_ptr_);

    if (!window_surface_ptr)
        throw std::runtime_error(std::string(SDL_GetError()));

    g.setWindow_surfaceptr(window_surface_ptr);

    for (int i = 0; i < g.getN(); i++)
    {
        g.setW_(window_surface_ptr);
    }

}

application::~application() 
{
    SDL_DestroyWindow(window_ptr_);
}

int application::loop(unsigned period)
{
    auto start = SDL_GetTicks();

    SDL_Event e;
    bool quit = false;
    while (!quit && (SDL_GetTicks() - start < period)) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
    }
    return 0;
}

