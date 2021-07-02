#include "Artist.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include <cmath>
#include <algorithm>
#include <time.h>

int main(int argc, char** argv)
{
	if (argc == 3)	// generate data
	{
		// initialize random seed
		srand (time(NULL));

		std::string arg1(argv[1]);
		int numUsers = stoi(arg1);

		std::string arg2(argv[2]);
		int maxNumArtworksPerUser = stoi(arg2);
		
		std::ofstream out("data.csv");

		int overallArtworksCounter = 0;
		for (int i = 0; i < numUsers; ++i)
		{
			int artistID = i;

			// an artist can have at least 1 and at maximum maxNumArtworksPerUser artworks
			int numArtworksOfUser = 1 + ( std::rand() % ( maxNumArtworksPerUser - 1 + 1 ) );
			for (int j = 0; j < numArtworksOfUser; ++j)
			{
				int artworkID = overallArtworksCounter;
				out << artistID << "," << artworkID;
				out << std::endl;
				overallArtworksCounter++;
				
				// an artwork is rate by at least 1 and at maximum all artists of the platform
				// int lowerThreshold = 1;
				// int upperThreshold = numUsers;
				// int numOfRatings = lowerThreshold + ( std::rand() % ( upperThreshold - lowerThreshold + 1 ) );
				
				// for (int k = 0; k < numOfRatings; ++k)
				// {
				// 	int rating = 1 + ( std::rand() % ( 5 - 1 + 1 ) );
				// 	out << artistID << "," << artworkID << "," << rating;
				// 	out << std::endl;
				// }

			}
		}
		out.close();

		return 0;
	}
	else if (argc == 5)	// simulation
	{

		// initialize random seed
		srand (time(NULL));

		std::string arg1(argv[1]);
		double w1 = stod(arg1);

		std::string arg2(argv[2]);
		double w2 = stod(arg2);

		std::string arg3(argv[3]);
		double w3 = stod(arg3);

		double sum = w1 + w2 + w3;
		if (sum != 1.0)
		{
			w1 /= sum;
			w2 /= sum;
			w3 /= sum;
		} 

		std::string arg4(argv[4]);
		double ratersPerc = stod(arg4);

		// load data
		std::map<int, Artist*> artists;
		std::string dataFilename = "data.csv";
		std::ifstream in(dataFilename);
		std::string dataline = "";
		if (in.is_open())
		{
			while (std::getline(in, dataline))
			{
				std::istringstream ss(dataline);
				std::string item;
				std::vector<std::string> items;
				while (std::getline(ss, item, ','))	// comma-separated values
				{
					items.push_back(item);
				}

				int artistID = stoi(items[0]);
				int artworkID = stoi(items[1]);

				auto it = artists.find(artistID);
				if (it != artists.end())	// artist exists
				{
					Artist* artist = it->second;
					if (!artist->artworkExists(artworkID))	// artwork of artist does not exist
					{
						Artwork* artwork = new Artwork(artworkID, artistID);
						artist->addArtwork(artworkID, artwork);
					}
				}
				else	// artist does not exist
				{
					Artist* artist = new Artist(artistID);
					Artwork* artwork = new Artwork(artworkID, artistID);
					artist->addArtwork(artworkID, artwork);
					artists.insert(std::make_pair(artistID, artist));
				}
			}
		}
		in.close();

		// simulation code
		int numArtists = artists.size();
		int numOfRaters = std::ceil(static_cast<double>(numArtists) * ratersPerc / 100.0);
		int numCycles = 11;
		for (int cycle = 0; cycle < numCycles; ++cycle)
		{
			// 1. set numOfMaliciousUsers malicious artists from the total pool of artists
			int numOfMaliciousUsers = std::ceil(static_cast<double>(numArtists) * ((static_cast<double>(cycle) * 10.0) / 100.0));
			for (int i = 0; i < numOfMaliciousUsers; ++i)
			{
				if (!artists[i]->isMalicious())
				{
					artists[i]->setMalicious(true);
				}
			}

			// 2. Generate ratings
			for (auto artistIterator = artists.begin(); artistIterator != artists.end(); ++artistIterator)	// for all artists
			{
				Artist* artist = artistIterator->second;
				int artistID = artist->getID();
				std::map<int, Artwork*>* artworks = artist->getArtworks();
				for (auto artworkIterator = artworks->begin(); artworkIterator != artworks->end(); ++artworkIterator)
				{
					Artwork* artwork = artworkIterator->second;
					int artworkID = artwork->getID();

					// in each simulation cycle each artwork of each artist is rated by a percentage of all other artists
					std::vector<int> raters;
					while (raters.size() != numOfRaters)
					{
						int raterID = 0 + ( std::rand() % ( (numArtists - 1) - 0 + 1 ) );
						if (std::find(raters.begin(), raters.end(), raterID) != raters.end())
						{
							continue;
						}
						else
						{
							if (raterID == artistID)
							{
								continue;
							}
							else
							{
								Artist* otherArtist = artists[raterID];
								
								// new rating
								int fromArtist = raterID;
								int forArtwork = artworkID;

								int stars = -1;
								if (otherArtist->isMalicious())
								{
									stars = 1;
								}
								else
								{
									stars = 1 + ( std::rand() % ( 5 - 1 + 1 ) );	// random uniform value from interval [1, 5]
								}

								Rating* rating = new Rating(fromArtist, forArtwork, stars);
								artwork->addRating(rating);
								otherArtist->addRating(rating);

								raters.push_back(raterID);
							}
						}
					}
					raters.clear();		
				}
			}

			// 3. Compute reputations (both 2gether's Reliability Assessment Model and Simple Average Model)
			int totalNumOfArtworks = 0;
			for (auto artistIterator = artists.begin(); artistIterator != artists.end(); ++artistIterator)	// for all artists
			{
				Artist* artist = artistIterator->second;
				int numOfArtworks = artist->getNumOfArtworks();
				totalNumOfArtworks += numOfArtworks;
			}

			for (auto artistIterator = artists.begin(); artistIterator != artists.end(); ++artistIterator)	// for all artists
			{
				Artist* artist = artistIterator->second;
				
				// F1 factor
				int numOfArtworks = artist->getNumOfArtworks();
				double F1 = static_cast<double>(numOfArtworks) / static_cast<double>(totalNumOfArtworks);

				// F2 factor
				artist->computeAverageRatingReceived();
				double averageRatingReceived = artist->getAverageRatingReceived();
				double F2 = averageRatingReceived / 5.0;

				// F3 factor
				artist->getAverageRatingGiven();
				double averageRatingGiven = artist->getAverageRatingGiven();
				double F3 = averageRatingGiven / 5.0;

				double RAMrep = (w1 * F1) + (w2 * F2) + (w3 * F3);
				artist->addRAMrep(RAMrep);
				
				double BENrep = averageRatingReceived / 5.0;
				artist->addBENrep(BENrep);
			}
		}

		for (auto artistIterator = artists.begin(); artistIterator != artists.end(); ++artistIterator)
		{
			Artist* artist = artistIterator->second;
			artist->saveRAMreps();
			artist->saveBENreps();
		}

		// clear artists data structure
		if (!artists.empty())
		{
			for (auto it = artists.begin(); it != artists.end(); ++it)
			{
				delete it->second;
			}
			artists.clear();
		}

		return 0;

	} else
	{
		std::cout << "Usage:\n";
		std::cout << "./RAM.out <numUsers> <maxNumArtworksPerUser>\n";
		std::cout << "or\n";
		std::cout << "./RAM.out <w1> <w2> <w3>\n";

		return 0;
	}
}