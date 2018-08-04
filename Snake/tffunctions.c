#include "tffunctions.h"


point_t MakePoint(int x, int y)
{
	point_t pt;
	
	pt.x = x;
	pt.y = y;
	return pt;
}

sizetype MakeSize(int w, int h)
{
	sizetype s;
	
	s.width = w;
	s.height = h;
	return s;
}

rect_t MakeRect(int x, int y, int w, int h)
{
	rect_t r;
	
	r.origin = MakePoint(x, y);
	r.size = MakeSize(w, h);
	return r;
}

#pragma mark -



//
// TFRectToSDL
// Converts a rect_t to SDL_Rect
//
void TFRectToSDL(SDL_Rect *dest, rect_t *src)
{
	dest->x = src->origin.x;
	dest->y = src->origin.y;
	dest->w = src->size.width;
	dest->h = src->size.height;
}




//
//	TFBoxFromRect
///	Make a bounding box from given rect_t
//
void TFBoxFromRect(box_t *destbox, rect_t const *srcrect)
{
	destbox->left = srcrect->origin.x;
	destbox->right = srcrect->origin.x + srcrect->size.width;
	destbox->top = srcrect->origin.y;
	destbox->bottom = srcrect->origin.y + srcrect->size.height;
}




//
//	TFPointsAreEqual
//
bool TFPointsAreEqual(point_t *pt1, point_t *pt2)
{
	if (pt1->x == pt2->x && pt1->y == pt2->y)
		return true;
	return false;
}




bool TFRectsCollide(rect_t *aRect, rect_t *bRect)
{
	box_t abox, bbox;
	bool xaligned, yaligned;
	
	TFBoxFromRect(&abox, aRect);
	TFBoxFromRect(&bbox, bRect);
	xaligned = !(abox.top > bbox.bottom || abox.bottom < bbox.top);
	yaligned = !(abox.left > bbox.right || abox.right < bbox.left);
	
	if (xaligned && yaligned)
		return true;
	
	return false;
}
