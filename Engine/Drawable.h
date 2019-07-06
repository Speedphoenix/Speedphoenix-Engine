#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <list>

/// drawable interface. Inherit from this if you want to make something that is visible on screen
class Drawable
{
	// non-statics
	private:

	protected:
		bool m_ready;

	public:
		Drawable();
		virtual ~Drawable();

		virtual void draw() = 0;
		bool isReady() { return (m_ready); }
};

#endif // DRAWABLE_H
