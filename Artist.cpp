#include "Artist.h"
#include "GenericFunc.h"

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <fstream>

Artist::Artist()
{
	id = -1;
	malicious = false;
	averageRatingReceived = -1.0;
	averageRatingGiven = -1.0;
}

Artist::Artist(int id)
{
	this->id = id;
	malicious = false;
	averageRatingReceived = -1.0;
	averageRatingGiven = -1.0;
}

Artist::~Artist()
{
	if (!artworks.empty())
	{
		for (auto artworkIterator = artworks.begin(); artworkIterator != artworks.end(); ++artworkIterator)
		{
			delete artworkIterator->second;
		}
		artworks.clear();
	}
	ratings.clear();

	if (!RAMreps.empty())
	{
		RAMreps.clear();
	}

	if (!BENreps.empty())
	{
		BENreps.clear();
	}
}

void Artist::setID(int id)
{
	this->id = id;
}

int Artist::getID() const
{
	return id;
}

void Artist::addRAMrep(double RAMrep)
{
	RAMreps.push_back(RAMrep);
}

void Artist::addBENrep(double BENrep)
{
	BENreps.push_back(BENrep);
}

void Artist::saveRAMreps()
{
	std::string RAMrepsFilename = gnfnc::getExecutablePathAndMatchItWithFilename("RAMreps/");
	std::stringstream ss;
	ss << id;
	RAMrepsFilename += "RAMreps_";
	RAMrepsFilename += ss.str();
	RAMrepsFilename += ".csv";
	std::ofstream out(RAMrepsFilename.c_str());
	for (size_t i = 0; i < RAMreps.size(); ++i)
	{
		out << (i * 10) << "," << RAMreps[i] << "\n";
	}
	out.close();
}

void Artist::saveBENreps()
{
	std::string BENrepsFilename = gnfnc::getExecutablePathAndMatchItWithFilename("BENreps/");
	std::stringstream ss;
	ss << id;
	BENrepsFilename += "BENreps_";
	BENrepsFilename += ss.str();
	BENrepsFilename += ".csv";
	std::ofstream out(BENrepsFilename);
	for (size_t i = 0; i < BENreps.size(); ++i)
	{
		out << (i * 10) << "," << BENreps[i] << "\n";
	}
	out.close();
}

void Artist::setMalicious(bool malicious)
{
	this->malicious = malicious;
}

bool Artist::isMalicious() const
{
	return malicious;
}

void Artist::addRating(Rating* rating)
{
	ratings.push_back(rating);
}

void Artist::computeAverageRatingReceived()
{
	averageRatingReceived = 0.0;
	for (auto artworkIterator = artworks.begin(); artworkIterator != artworks.end(); ++artworkIterator)
	{
		artworkIterator->second->computeAverageRating();
		averageRatingReceived += artworkIterator->second->getAverageRating();
	}
	averageRatingReceived /= static_cast<double>(artworks.size());
}

double Artist::getAverageRatingReceived() const
{
	return averageRatingReceived;
}

void Artist::computeAverageRatingGiven()
{
	averageRatingGiven = 0.0;
	for (size_t i = 0; i < ratings.size(); ++i)
	{
		averageRatingGiven += ratings[i]->getStars();
	}
	averageRatingGiven /= static_cast<double>(ratings.size());
}

double Artist::getAverageRatingGiven() const
{
	return averageRatingGiven;
}

bool Artist::artworkExists(int artworkID)
{
	auto it = artworks.find(artworkID);
	return (it != artworks.end());
}

void Artist::addArtwork(int artworkID, Artwork* artwork)
{
	if (!artworkExists(artworkID))
	{
		artworks.insert(std::make_pair(artworkID, artwork));
	}
}

Artwork* Artist::getArtwork(int artworkID)
{
	if (artworkExists(artworkID))
	{
		return artworks[artworkID];
	}
	else
	{
		nullptr;
	}
}

void Artist::printArtworksIDs()
{
	for (auto artworkIterator = artworks.begin(); artworkIterator != artworks.end(); ++artworkIterator)
	{
		std::cout << artworkIterator->second->getID() << " ";
	}
	std::cout << std::endl;
}

std::map<int, Artwork*>* Artist::getArtworks()
{
	return &artworks;
}

int Artist::getNumOfArtworks()
{
	return static_cast<int>(artworks.size());
}