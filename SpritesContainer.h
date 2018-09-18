#ifndef SPRITESCONTAINER_H
#define SPRITESCONTAINER_H

#include <string>
#include <map>

struct ALLEGRO_BITMAP;

//this class could be made with a template but oh well...
class SpritesContainer
{
    ///FOR TESTING PURPOSES
    public:
        void maketest();

    //statics
    protected:
        static SpritesContainer * m_instance;
    public:
        static SpritesContainer * instance() { return m_instance; }


    protected:
        std::map<std::string, ALLEGRO_BITMAP*> m_sprites;

    public:
        SpritesContainer();
        virtual ~SpritesContainer();

        ALLEGRO_BITMAP* at(std::string theKey) { return m_sprites.at(theKey); }
};

#endif // SPRITESCONTAINER_H
