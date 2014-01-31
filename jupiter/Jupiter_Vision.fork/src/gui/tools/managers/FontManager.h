#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include <easysocket/tools.h>
#include <assert.h>
#include <map>
#include <string>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/**
 * @brief   Load fonts at a given size only once.
 * @author  Denis CARLUS
 */
class FontManager : private NoCopy {
    private:
        /** @brief Singleton of the FontManager handler. */
        static FontManager* Singleton ;

        /** @brief  Fonts. */
         std::map< std::string, std::map<unsigned char, ALLEGRO_FONT*> > m_fonts ;


                                            /** CONSTRUCTION AND DESTRUCTION **/
        /** @brief Construction of a FontManager handler. */
        FontManager() ;

        /** @brief Destruction of the FontManager handler. */
        ~FontManager() throw() ;


    public:
        /**
         * @brief Get the unique instance of FontManager.
         * @return  The unique instance of FontManager.
         */
        static FontManager* getInstance() ;


        /**
         * @brief   Add a new font from a path and its size.
         * @param   filename    Name of the font file.
         * @param   size        Size of the font on screen.
         * @return  The loaded font.
         */
        ALLEGRO_FONT* addFont(const std::string& filename, unsigned char size) ;


        /**
         * @brief   Get a font with the given name and size.
         * @param   filename    Name of the font file.
         * @param   size        Size of the font on screen.
         * @return  The wanted font, NULL if not found.
         */
        ALLEGRO_FONT* getFont(const std::string& filename, unsigned char size) ;
} ;

#endif
