/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2016                                    */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
	NONE_CMD = -2,
	COMMENT_CMD = -1,
	INIT_CMD = 0,
	ADDTROLL_CMD = 1,
	PUBLISHPOST_CMD = 2,
	DELETEPOST_CMD = 3,
	FEEDTROLL_CMD = 4,
	GETTOPPOST_CMD = 5,
	GETALLPOSTS_CMD = 6,
	UPDATE_CMD = 7,
	QUIT_CMD = 8
} commandType;

static const int numActions = 9;
static const char *commandStr[] = { "Init", "AddTroll", "PublishPost",
		"DeletePost", "FeedTroll",
		"GetTopPost", "GetAllPostsByLikes", "UpdateLikes", "Quit" };

static const char* ReturnValToStr(int val) {
	switch (val) {
	case SUCCESS:
		return "SUCCESS";
	case ALLOCATION_ERROR:
		return "ALLOCATION_ERROR";
	case FAILURE:
		return "FAILURE";
	case INVALID_INPUT:
		return "INVALID_INPUT";
	default:
		return "";
	}
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
	error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
	char buffer[MAX_STRING_INPUT_SIZE];

	// Reading commands
	while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
		fflush(stdout);
		if (parser(buffer) == error)
			break;
	};
	return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
		const char** const command_arg) {
	if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
		return (NONE_CMD);
	if (StrCmp("#", command)) {
		if (strlen(command) > 1)
			printf("%s", command);
		return (COMMENT_CMD);
	};
	for (int index = 0; index < numActions; index++) {
		if (StrCmp(commandStr[index], command)) {
			*command_arg = command + strlen(commandStr[index]) + 1;
			return ((commandType) index);
		};
	};
	return (NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddTroll(void* DS, const char* const command);
static errorType OnPublishPost(void* DS, const char* const command);
static errorType OnDeletePost(void* DS, const char* const command);
static errorType OnFeedTroll(void* DS, const char* const command);
static errorType OnGetTopPost(void* DS, const char* const command);
static errorType OnGetAllPostsByLikes(void* DS, const char* const command);
static errorType OnUpdateLikes(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
	static void *DS = NULL; /* The general data structure */
	const char* command_args = NULL;
	errorType rtn_val = error;

	commandType command_val = CheckCommand(command, &command_args);

	switch (command_val) {

	case (INIT_CMD):
		rtn_val = OnInit(&DS, command_args);
		break;
	case (ADDTROLL_CMD):
		rtn_val = OnAddTroll(DS, command_args);
		break;
	case (PUBLISHPOST_CMD):
		rtn_val = OnPublishPost(DS, command_args);
		break;
	case (DELETEPOST_CMD):
		rtn_val = OnDeletePost(DS, command_args);
		break;
	case (FEEDTROLL_CMD):
		rtn_val = OnFeedTroll(DS, command_args);
		break;
	case (GETTOPPOST_CMD):
		rtn_val = OnGetTopPost(DS, command_args);
		break;
	case (GETALLPOSTS_CMD):
		rtn_val = OnGetAllPostsByLikes(DS, command_args);
		break;
	case (UPDATE_CMD):
		rtn_val = OnUpdateLikes(DS, command_args);
		break;
	case (QUIT_CMD):
		rtn_val = OnQuit(&DS, command_args);
		break;

	case (COMMENT_CMD):
		rtn_val = error_free;
		break;
	case (NONE_CMD):
		rtn_val = error;
		break;
	default:
		assert(false);
		break;
	};
	return (rtn_val);
}

/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if (isInit) {
		printf("Init was already called.\n");
		return (error_free);
	};
	isInit = true;

	*DS = Init();
	if (*DS == NULL) {
		printf("Init failed.\n");
		return error;
	};
	printf("Init done.\n");

	return error_free;
}

/***************************************************************************/
/* OnAddTroll                                                             */
/***************************************************************************/
static errorType OnAddTroll(void* DS, const char* const command) {
	int trollID;
	ValidateRead(sscanf(command, "%d", &trollID), 1, "AddTroll failed.\n");
	StatusType res = AddTroll(DS, trollID);

	if (res != SUCCESS) {
		printf("AddTroll: %s\n", ReturnValToStr(res));
		return error_free;
	} else {
		printf("AddTroll: %s\n", ReturnValToStr(res));
	}

	return error_free;
}

/***************************************************************************/
/* OnPublishPost                                                          */
/***************************************************************************/
static errorType OnPublishPost(void* DS, const char* const command) {
	int postID;
	int trollID;
	int likesCount;
	ValidateRead(
			sscanf(command, "%d %d %d", &postID, &trollID, &likesCount),
			3, "PublishPost failed.\n");
	StatusType res = PublishPost(DS, postID, trollID, likesCount);

	if (res != SUCCESS) {
		printf("PublishPost: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("PublishPost: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnDeletePost                                                            */
/***************************************************************************/
static errorType OnDeletePost(void* DS, const char* const command) {
	int postID;
	ValidateRead(sscanf(command, "%d", &postID), 1,
			"DeletePost failed.\n");
	StatusType res = DeletePost(DS, postID);

	if (res != SUCCESS) {
		printf("DeletePost: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("DeletePost: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnFeedTroll                                                         */
/***************************************************************************/
static errorType OnFeedTroll(void* DS, const char* const command) {
	int postID;
	int likesIncrease;
	ValidateRead(sscanf(command, "%d %d", &postID, &likesIncrease), 2,
			"FeedTroll failed.\n");
	StatusType res = FeedTroll(DS, postID, likesIncrease);

	if (res != SUCCESS) {
		printf("FeedTroll: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("FeedTroll: %s\n", ReturnValToStr(res));
	return error_free;
}


/***************************************************************************/
/* OnGetTopPost                                                         */
/***************************************************************************/
static errorType OnGetTopPost(void* DS, const char* const command) {
	int trollID;
	ValidateRead(sscanf(command, "%d", &trollID), 1, "GetTopPost failed.\n");
	int postID;
	StatusType res = GetTopPost(DS, trollID, &postID);

	if (res != SUCCESS) {
		printf("GetTopPost: %s\n", ReturnValToStr(res));
		return error_free;
	}

	cout << "Post with maximal likes is: " << postID << endl;
	return error_free;
}

/***************************************************************************/
/* OnGetAllGames                                                        */
/***************************************************************************/

void PrintAll(int *posts, int numOfPosts) {
	if (numOfPosts > 0) {
		cout << "Rank	||	Post" << endl;
	}

	for (int i = 0; i < numOfPosts; i++) {
		cout << i + 1 << "\t||\t" << posts[i] << endl;
	}
	cout << "and there are no more posts!" << endl;

	free (posts);
}

static errorType OnGetAllPostsByLikes(void* DS, const char* const command) {
	int trollID;
	ValidateRead(sscanf(command, "%d", &trollID), 1,
			"GetAllPostsByLikes failed.\n");
	int* posts;
	int numOfPosts;
	StatusType res = GetAllPostsByLikes(DS, trollID, &posts, &numOfPosts);

	if (res != SUCCESS) {
		printf("GetAllPostsByLikes: %s\n", ReturnValToStr(res));
		return error_free;
	}

	PrintAll(posts, numOfPosts);
	return error_free;
}

/***************************************************************************/
/* OnUpdateLikes                                                           */
/***************************************************************************/
static errorType OnUpdateLikes(void* DS, const char* const command) {
	int postsCode;
	int postsFactor;
	ValidateRead(sscanf(command, "%d %d", &postsCode, &postsFactor), 2,
			"UpdateLikes failed.\n");
	StatusType res = UpdateLikes(DS, postsCode, postsFactor);

	if (res != SUCCESS) {
		printf("UpdateLikes: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("UpdateLikes: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	Quit(DS);
	if (*DS != NULL) {
		printf("Quit failed.\n");
		return error;
	};

	isInit = false;
	printf("Quit done.\n");

	return error_free;
}

#ifdef __cplusplus
}
#endif
