#include "Rating.h"

Rating::Rating()
{
	fromArtist = -1;
	forArtwork = -1;
	stars = -1;
}

Rating::Rating(int fromArtist, int forArtwork, int stars)
{
	this->fromArtist = fromArtist;
	this->forArtwork = forArtwork;
	this->stars = stars;
}

Rating::~Rating()
{
}

void Rating::setFromArtist(int fromArtist)
{
	this->fromArtist = fromArtist;
}

int Rating::getFromArtist() const
{
	return fromArtist;
}

void Rating::setForArtwork(int forArtwork)
{
	this->forArtwork = forArtwork;
}

int Rating::getForArtwork() const
{
	return forArtwork;
}

void Rating::setStars(int stars)
{
	this->stars = stars;
}

int Rating::getStars() const
{
	return stars;
}