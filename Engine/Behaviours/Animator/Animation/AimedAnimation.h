#ifndef AIMEDANIMATION_H
#define AIMEDANIMATION_H

#include <Animation.h>

#include <vector>

struct ALLEGRO_BITMAP;
class Frame;

class AimedAnimation : public Animation
{
	protected:
		double m_currDirection;

		std::vector<Frame*> m_frames;

		virtual void clearFrames();

	public:
		AimedAnimation();
		AimedAnimation(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h, int nb);
		virtual ~AimedAnimation();

		//Creates from sheet, an animation with nb frames.
		virtual void createFromSheet(ALLEGRO_BITMAP* sheet,
								int x, int y, int w, int h, int nb);
		
		virtual void addFrames(ALLEGRO_BITMAP *sheet,
								int x, int y, int w, int h, int nb);

		///the number of frames of the animation for the current direction
		virtual unsigned nbFrames();

		///the current sprite to render
		virtual Frame* getFrame(unsigned frameNumber);

		virtual void draw(double destx, double desty, unsigned frameNumber);

		virtual double currDirection() const { return m_currDirection; }

		/// set the direction. Will chose the closest available if there are no
		// frames for val direction
		virtual void setDirection(double orientation);
};

#endif // AIMEDANIMATION_H
