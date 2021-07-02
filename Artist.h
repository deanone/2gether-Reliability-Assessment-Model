#ifndef ARTIST_H
#define ARTIST_H

#include "Artwork.h"
#include "Rating.h"
#include <map>
#include <vector>

class Artist
{
	/*! The id of the Artist object. */
	int id;
	/*! The list of artworks of the artist. */
	std::map<int, Artwork*> artworks;
	/*! The list of rating given by the artist. */
	std::vector<Rating*> ratings;
	/*! A flag indicating if the user is malicious or not. */
	bool malicious;
	/*! The average of the ratings received for all the artworks of the artist. */
	double averageRatingReceived;
	/*! the average of all ratings given by the artist for the artworks of other artists */
	double averageRatingGiven;
	/*! the vector of RAM reputation values. */
	std::vector<double> RAMreps;
	/*! the vector of benchmark reputation values. */
	std::vector<double> BENreps;

public:

	/*!
	 * Default constructor.
	 */
	Artist();

	/*!
	 * Constructor.
	 * @param id the ID of the Artist object.
	 */
	Artist(int id);

	/*!
	 * Destructor.
	 */
	~Artist();

    /*! 
	 * Sets the ID of the Artist object.
     * @param id the ID of the Artist object.
     */
	void setID(int id);

	/*!
	 * Returns the ID of the Artist object.
	 * @return the ID of the Artist object.
	 */
	int getID() const;

	/*! 
	 * Adds a new RAM reputation value in the vector of RAM reputation values.
	 * @param RAMrep the RAM reputation value to be added.
	 */
	void addRAMrep(double RAMrep);
	
	/*! 
	 * Adds a new benchmark reputation value in the vector of benchmark reputation values.
     * @param BENrep the benchmark reputation value to be added.
     */
	void addBENrep(double BENrep);

	/*! 
	 * Saves the vector of RAM reputation values into a file.
	 */
	void saveRAMreps();

	/*! 
	 * Saves the vector of benchmark reputation values into a file.
	 */
	void saveBENreps();

	/*! 
	 * Sets the Artist as malicious.
	 * @param malicious flag (true) to set Artist as malicious.
	 */
	void setMalicious(bool malicious);

	/*! 
	 * Returns the status of Artist (i.e., malicious, non-malicious).
	 * @return a flag indicating if the Artist is malicious or not.
	 */
	bool isMalicious() const;

	/*! 
	 * Adds a new Rating object (i.e., pointer to Rating object) to the vector of Rating objects (i.e., vector of pointers to rating objects).
	 * @param rating the new Rating object.
	 */
	void addRating(Rating* rating);

	/*! 
	 * Computes the average of the ratings received for all the artworks of the Artist.
	 */
	void computeAverageRatingReceived();
	
	/*! 
	 * Returns the average of the ratings received for all the artworks of the Artist.
	 * @return the average of the ratings received for all the artworks of the Artist.
	 */
	double getAverageRatingReceived() const;

	/*! 
	 * Computes the average of all ratings given by the Artist for the artworks of other artists.
	 */
	void computeAverageRatingGiven();

	/*! 
	 * Returns the average of all ratings given by the Artist for the artworks of other artists.
	 * @return the average of all ratings given by the Artist for the artworks of other artists.
	 */
	double getAverageRatingGiven() const;

	/*! 
	 * Adds a new Artwork object in the list of Artwork objects of the artist.
	 * @param artworkID the ID of the Artwork object.
	 * @param artwork the Artwork object.
	 */
	void addArtwork(int artworkID, Artwork* artwork);
	
	/*! 
	 * Returns an Artwork object from the list of Artwork objects of the Artist.
	 * @param artworkID the ID of the Artwork object.
	 * @return the Artwork object.
	 */
	Artwork* getArtwork(int artworkID);

	/*! 
	 * Returns the list of Artwork objects of the Artist.
	 * @return the list of Artwork objects of the Artist.
	 */
	std::map<int, Artwork*>* getArtworks();

	/*! 
	 * Returns the number of Artwork objects of the Artist.
	 * @return the number of Artwork objects of the Artist.
	 */
	int getNumOfArtworks();

	/*! 
	 * Checks if an Artwork object with specific ID exists in the list of Artwork objects of the Artist.
	 * @param artworkID the ID of the Artwork object.
	 * @return true if the Artwork object belongs to the Artist, false otherwise.
	 */
	bool artworkExists(int artworkID);
	
	/*! 
	 * Prints the IDs of the Artwork objects of the Artist.
	 */
	void printArtworksIDs();

};

#endif	//	ARTIST_H