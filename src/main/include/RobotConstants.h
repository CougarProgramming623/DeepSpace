
#define BOT_SAMUS
//#define BOT_HAMBONE
//#define BOT_RAFIKI

#define SAMUS_LEFT_FRONT_ID  15
#define SAMUS_RIGHT_FRONT_ID  4
#define SAMUS_LEFT_BACK_ID    3
#define SAMUS_RIGHT_BACK_ID   7
#define SAMUS_BOT_NAME "Samus"

#define HAMBONE_LEFT_FRONT_ID  -1
#define HAMBONE_RIGHT_FRONT_ID -1
#define HAMBONE_LEFT_BACK_ID   -1
#define HAMBONE_RIGHT_BACK_ID  -1
#define HAMBONE_BOT_NAME "Hambone"

#define RAFIKI_LEFT_FRONT_ID  -1
#define RAFIKI_RIGHT_FRONT_ID -1
#define RAFIKI_LEFT_BACK_ID   -1
#define RAFIKI_RIGHT_BACK_ID  -1
#define RAFIKI_BOT_NAME "Rafiki"


//Actual definitions of general ID's and names
#ifdef BOT_SAMUS

#define LEFT_FRONT_ID SAMUS_LEFT_FRONT_ID
#define RIGHT_FRONT_ID SAMUS_RIGHT_FRONT_ID
#define LEFT_BACK_ID SAMUS_LEFT_BACK_ID
#define RIGHT_BACK_ID SAMUS_RIGHT_BACK_ID
#define BOT_NAME SAMUS_BOT_NAME

#elif BOT_HAMBONE

#define LEFT_FRONT_ID HAMBONE_LEFT_FRONT_ID
#define RIGHT_FRONT_ID HAMBONE_RIGHT_FRONT_ID
#define LEFT_BACK_ID HAMBONE_LEFT_BACK_ID
#define RIGHT_BACK_ID HAMBONE_RIGHT_BACK_ID
#define BOT_NAME HAMBONE_BOT_NAME

#elif BOT_RAFIKI

#define LEFT_FRONT_ID RAFIKI_LEFT_FRONT_ID
#define RIGHT_FRONT_ID RAFIKI_RIGHT_FRONT_ID
#define LEFT_BACK_ID RAFIKI_LEFT_BACK_ID
#define RIGHT_BACK_ID RAFIKI_RIGHT_BACK_ID
#define BOT_NAME RAFIKI_BOT_NAME

#else

#error No Bot Selected!

#endif

#if !defined(LEFT_FRONT_ID) || !defined(LEFT_FRONT_ID) || !defined(LEFT_FRONT_ID) || !defined(LEFT_FRONT_ID) || !defined(BOT_NAME)
#error you must specity a robot to compile for!
#endif
