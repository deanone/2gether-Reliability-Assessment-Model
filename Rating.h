#ifndef RATING_H
#define RATING_H

class Rating
{
	/*! The id of the Artist object that made the Rating. */
	int fromArtist;
	/*! The id of the Artwork object that received the Rating. */
	int forArtwork;
	/*! The actual rating value (integer in [1, 5]). */
	int stars;

public:
	/*!
	 * Default constructor.
	 */
	Rating();

	/*!
	 * Constructor.
	 * @param fromArtist the id of the Artist object that made the Rating.
	 * @param forArtwork the id of the Artwork object that received the Rating.
	 * @param stars the actual rating value (integer in [1, 5]).
	 */
	Rating(int fromArtist, int forArtwork, int stars);

	/*!
	 * Destructor.
	 */
	~Rating();

	/*! 
	 * Sets the ID of the Artist object that made the Rating.
     * @param id the ID of the Artist object that made the Rating.
     */
	void setFromArtist(int fromArtist);

	/*! 
	 * Returns the ID of the Artist object that made the Rating.
     * @return the ID of the Artist object that made the Rating.
     */
	int getFromArtist() const;

	/*! 
	 * Sets the ID of the Artwork object that received the Rating.
     * @param id the ID of the Artwork object that received the Rating.
     */
	void setForArtwork(int forArtwork);

	/*! 
	 * Returns the ID of the Artwork object that received the Rating.
     * @return the ID of the Artwork object that received the Rating.
     */
	int getForArtwork() const;

	/*! 
	 * Sets the actual rating value (integer in [1, 5]).
     * @param stars the actual rating value (integer in [1, 5]).
     */
	void setStars(int stars);

	/*! 
	 * Returns the actual rating value (integer in [1, 5]).
     * @return the actual rating value (integer in [1, 5]).
     */
	int getStars() const;
	
};

#endif	//	RATING_H