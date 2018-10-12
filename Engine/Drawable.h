#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <list>

class Animator;
class TransformBase;

/// drawable interface. Inherit from this if you want to make something that is visible on screen
class Drawable
{
	// statics
	protected:
		// make the inheriting class use this function
		virtual void draw(Animator& what, const TransformBase& where);

	// non-statics
	private:
		std::list<Drawable *>::iterator m_containerIterator;

	public:
		Drawable();
		virtual ~Drawable();

		virtual void draw() = 0;
};

#endif // DRAWABLE_H
