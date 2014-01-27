#include "SpriteManager.h"
#include "../../constants.h"
#include <easysocket/tools.h>

using namespace std ;

SpriteManager* SpriteManager::Singleton = 0 ;
sem_t SpriteManager::Access ;
map<string, ALLEGRO_BITMAP*> SpriteManager::Sprites ;

SpriteManager::SpriteManager() {
    assert(sem_init(&Access, 0, 1) == 0) ;
}

SpriteManager::~SpriteManager() throw() {
    sem_destroy(&Access) ;
}


SpriteManager* SpriteManager::getInstance() {
    if (Singleton == 0)
        Singleton = new SpriteManager() ;

    return Singleton ;
}


/**
 * @brief   Load a sprite if not already existing and return a
 *          pointer on it.
 */
ALLEGRO_BITMAP* SpriteManager::addSprite(const std::string& path) {
    ALLEGRO_BITMAP* sprite ;

    sem_wait(&Access) ;
    if (Sprites.count(path) == 0) {
        std::string fullpath = string(PATH_TO_MEDIA) + "media/img/" + path + ".png" ;
        #ifdef DEBUG
        Logger::print("Load sprite: " + fullpath) ;
        #endif
        sprite = al_load_bitmap(fullpath.c_str()) ;
        Sprites[path] = sprite ;
    }
    else {
        sprite = Sprites[path] ;
    }
    sem_post(&Access) ;

    return sprite ;
}
