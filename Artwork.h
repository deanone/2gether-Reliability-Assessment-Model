#ifndef ARTWORK_H
#define ARTWORK_H

#include <vector>

#include "Rating.h"

class Artwork
{
	/*! The id of the Artwork object. */
	int id;
	/*! The id of the Artist who owns the Artwork object. */
	int ownerId;
	/*! The list of Rating objects received for the Artwork object. */
	std::vector<Rating*> ratings;
	/*! The average of all ratings received for the Artwork object from other artists of the platform. */
	double averageRating;

public:

	/*!
	 * Default constructor.
	 */
	Artwork();

	/*!
	 * Constructor.
	 * @param id the ID of the Artwork object.
	 * @param ownerId the ID of the Artist who owns the Artwork object.
	 */
	Artwork(int id, int ownerId);

	/*!
	 * Destructor.
	 */
	~Artwork();

	/*! 
	 * Sets the ID of the Artwork object.
     * @param id the ID of the Artwork object.
     */
	void setID(int id);

	/*!
	 * Returns the ID of the Artwork object.
	 * @return the ID of the Artwork object.
	 */
	int getID() const;

	/*! 
	 * Sets the ID of the Artist who owns the Artwork object.
     * @param id the ID of the Artist who owns the Artwork object.
     */
	void setOwnerID(int ownerId);

	/*!
	 * Returns the ID of the Artist who owns the Artwork object.
	 * @return the ID of the Artist who owns the Artwork object.
	 */
	int getOwnerID() const;

	/*! 
	 * Adds a new Rating object (i.e., pointer to Rating object) to the vector of Rating objects (i.e., vector of pointers to rating objects).
	 * @param rating the new Rating object.
	 */
	void addRating(Rating* rating);

	/*! 
	 * Computes the average of all ratings received for the Artwork object from other artists of the platform.
	 */
	void computeAverageRating();

	/*! 
	 * Returns the average of all ratings received for the Artwork object from other artists of the platform.
	 * @return the average of all ratings received for the Artwork object from other artists of the platform.
	 */
	double getAverageRating() const;

};

#endif	//	ARTWORK_H