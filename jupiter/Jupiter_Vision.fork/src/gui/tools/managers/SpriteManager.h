#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include <easysocket/tools.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <assert.h>
#include <semaphore.h>
#include <string>
#include <map>

/**
 * @brief   Sprite manager to load only once each picture. If already loaded,
 *          it just returns a pointer on the corresponding memory structure.
 * @author  Denis CARLUS
 */
class SpriteManager : private NoCopy {
    private:
        /** @brief Singleton of the SpriteManager handler. */
        static SpriteManager* Singleton ;

        /**
         * @brief Regulate the access to the singleton to avoid concurrency
         *        problems.
         */
        static sem_t Access ;

        /** List of the loaded sprites. */
        static std::map<std::string, ALLEGRO_BITMAP*> Sprites ;


                                            /** CONSTRUCTION AND DESTRUCTION **/
        /** @brief Construction of a SpriteManager handler. */
        SpriteManager() ;

        /** @brief Destruction of the SpriteManager handler. */
        ~SpriteManager() throw() ;

    public:
        /**
         * @brief Get the unique instance of SpriteManager.
         * @return  The unique instance of SpriteManager.
         */
        static SpriteManager* getInstance() ;


        /**
         * @brief   Load a sprite if not already existing and return a
         *          pointer on it.
         */
        ALLEGRO_BITMAP* addSprite(const std::string& path) ;
} ;

#endif
