#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

struct ALLEGRO_BITMAP;


class Frame
{
    private:
        ALLEGRO_BITMAP* m_parentImg;
        ALLEGRO_BITMAP* m_sprite;
        int m_takenX;
        int m_takenY;
        int m_width;
        int m_height;

    public:
        Frame(ALLEGRO_BITMAP* _img, int _takenX, int _takenY, int _width, int _height);
        Frame(ALLEGRO_BITMAP* _img);
        ~Frame();

        virtual void draw(double destx, double desty);

        bool operator==(const Frame& cmp) const;
        bool operator==(ALLEGRO_BITMAP* cmp) const;

        ALLEGRO_BITMAP* parentImg() const { return m_sprite; }
        ALLEGRO_BITMAP* sprite() const { return m_sprite; }
        int takenX() const { return m_takenX; }
        int takenY() const { return m_takenY; }
        int width() const { return m_width; }
        int height() const { return m_height; }
};


#endif // FRAME_H_INCLUDED

