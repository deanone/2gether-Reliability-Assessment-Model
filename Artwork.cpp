#include "Artwork.h"

#include <cstddef>

Artwork::Artwork()
{
	id = -1;
	ownerId = -1;
	averageRating = -1.0;
}

Artwork::Artwork(int id, int ownerId)
{
	this->id = id;
	this->ownerId = ownerId;
	averageRating = -1.0;
}

Artwork::~Artwork()
{
	if (!ratings.empty())
	{
		for (size_t i = 0; i < ratings.size(); ++i)
		{
			delete ratings[i];
		}
		ratings.clear();
	}
}

void Artwork::setID(int id)
{
	this->id = id;
}

int Artwork::getID() const
{
	return id;
}

void Artwork::setOwnerID(int ownerId)
{
	this->ownerId = ownerId;
}

int Artwork::getOwnerID() const
{
	return ownerId;
}

void Artwork::addRating(Rating* rating)
{
	ratings.push_back(rating);
}

void Artwork::computeAverageRating()
{
	averageRating = 0.0;
	for (size_t i = 0; i < ratings.size(); ++i)
	{
		averageRating += static_cast<double>(ratings[i]->getStars());
	}
	averageRating /= static_cast<double>(ratings.size());
}

double Artwork::getAverageRating() const
{
	return averageRating;
}