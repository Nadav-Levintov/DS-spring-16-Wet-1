/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library1.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET1_
#define _234218_WET1_

#ifdef __cplusplus
extern "C" {
#endif

/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

/* Required Interface for the Data Structure
 * -----------------------------------------*/

/* Description:   Initiates the data structure.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void* Init();

/* Description:   Adds a new troll.
 * Input:         DS - A pointer to the data structure.
 *                trollID - The ID of the troll to add.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or if trollID <= 0.
 *                FAILURE - If trollID is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType AddTroll(void *DS, int trollID);

/* Description:   Adds a new post to the system.
 * Input:         DS - A pointer to the data structure.
 *                postID - ID of the post to add.
 *                trollID - The ID of the post's troll
 *                LikesCount - The post's initial number of likes.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if postID <=0, or if trollID <=0, or if LikesCount < 0
 *                FAILURE - If postID is already in the DS, or trollID isn't in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType PublishPost(void *DS, int postID, int trollID, int LikesCount);

/* Description:   Removes an existing post.
 * Input:         DS - A pointer to the data structure.
 *                postID - The ID of the post to remove.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or if postID <= 0.
 *                FAILURE - If postID isn't in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType DeletePost(void *DS, int postID);

/* Description:   Increases the LikesCount of a post.
 * Input:         DS - A pointer to the data structure.
 *                postID - The ID of the post.
 *		            LikesIncrease - The increase in LikesCount.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if postID<=0, or if LikesIncrease<=0
 *                FAILURE - If postID isn't in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType FeedTroll(void *DS, int postID, int LikesIncrease);

/* Description:   Returns the post with the highest LikesCount from trollID
 * 			If trollID < 0, returns the top post in the entire DS.
 * Input:         DS - A pointer to the data structure.
 *                trollID - The troll that we'd like to get the data for.
 * Output:        postID - A pointer to a variable that should be updated to the ID of the top post.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if postID == NULL, or if trollID == 0.
 *                SUCCESS - Otherwise.
 */
StatusType GetTopPost(void *DS, int trollID, int *postID);

/* Description:   Returns all the posts from trollID sorted by their LikesCount.
 *           			If trollID < 0, returns all the posts in the entire DS sorted by their LikesCount.
 * Input:         DS - A pointer to the data structure.
 *                trollID - The troll that we'd like to get the data for.
 * Output:        posts - A pointer to a to an array that you should update with the posts' IDs sorted by their LikesCount,
 *			          in case two posts have same LikesCount they should be sorted by their ID.
 *                numOfPost - A pointer to a variable that should be updated to the number of posts.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If any of the arguments is NULL or if trollID == 0.
 *                SUCCESS - Otherwise.
 */
StatusType GetAllPostsByLikes(void *DS, int trollID, int **posts, int *numOfPost);

/* Description:   Updates the LikesCount of the posts where postID % postsCode == 0.
 * 			          For each matching post, multiplies its' LikesCount by postsFactor.
 * Input:         DS - A pointer to the data structure.
 *                postsCode - The basis that the posts works on
 *          		  postsFactor - The multiply factor of the LikesCount
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or if postsCode < 1 or if postsFactor <1
 *                SUCCESS - Otherwise.
 */
StatusType UpdateLikes(void *DS, int postsCode, int postsFactor);


/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void Quit(void** DS);

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1_ */
