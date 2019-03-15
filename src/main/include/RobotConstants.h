
#define BOT_SAMUS
//#define BOT_HAMBONE
//#define BOT_RAFIKI

#define SAMUS_LEFT_FRONT_ID  15
#define SAMUS_RIGHT_FRONT_ID  4
#define SAMUS_LEFT_BACK_ID    3
#define SAMUS_RIGHT_BACK_ID   7
#define SAMUS_ARM_TALON_ID   17
#define SAMUS_WRIST_TALON_ID 11
#define SAMUS_VACUUM_TALON_ID 22
#define SAMUS_BOT_NAME "Samus"

#define HAMBONE_LEFT_FRONT_ID   6
#define HAMBONE_RIGHT_FRONT_ID  2
#define HAMBONE_LEFT_BACK_ID    1
#define HAMBONE_RIGHT_BACK_ID   5
#define HAMBONE_ARM_TALON_ID   13
#define HAMBONE_WRIST_TALON_ID 21
#define HAMBONE_BOT_NAME "Hambone"

#define RAFIKI_LEFT_FRONT_ID  -1
#define RAFIKI_RIGHT_FRONT_ID -1
#define RAFIKI_LEFT_BACK_ID   -1
#define RAFIKI_RIGHT_BACK_ID  -1
#define RAFIKI_BOT_NAME "Rafiki"

//TICK_PER_INCH Values
#ifdef BOT_SAMUS

#define TICKS_PER_INCH 19.33570146
#define S_TICKS_PER_INCH 27.83584539

#else
#define TICKS_PER_INCH 0.0000
#define S_TICKS_PER_INCH 0.0000

#endif

//Actual definitions of general ID's and names
#ifdef BOT_SAMUS

#define LEFT_FRONT_ID SAMUS_LEFT_FRONT_ID
#define RIGHT_FRONT_ID SAMUS_RIGHT_FRONT_ID
#define LEFT_BACK_ID SAMUS_LEFT_BACK_ID
#define RIGHT_BACK_ID SAMUS_RIGHT_BACK_ID
#define ARM_TALON_ID SAMUS_ARM_TALON_ID
#define FORK_ID 0
#define CLIMB_ID 0
#define WRIST_ID SAMUS_WRIST_TALON_ID
#define VACUUM_ID SAMUS_VACUUM_TALON_ID

#define BOT_NAME SAMUS_BOT_NAME

#elif defined(BOT_HAMBONE)

#define LEFT_FRONT_ID HAMBONE_LEFT_FRONT_ID
#define RIGHT_FRONT_ID HAMBONE_RIGHT_FRONT_ID
#define LEFT_BACK_ID HAMBONE_LEFT_BACK_ID
#define RIGHT_BACK_ID HAMBONE_RIGHT_BACK_ID
#define ARM_TALON_ID HAMBONE_ARM_TALON_ID
#define FORK_ID 14
#define CLIMB_ID 18 
#define WRIST_ID HAMBONE_WRIST_TALON_ID
#define VACUUM_ID 16
#define BOT_NAME HAMBONE_BOT_NAME

#elif defined(BOT_RAFIKI)

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


//#define map(value, sourceMin, sourceMax, destMin, destMax) lerp(destMin, destMax, normalize(sourceMin, sourceMax, value))

#ifdef BOT_SAMUS

#define kMAX_VELOCITY 322

#else

#define kMAX_VELOCITY 643

#endif

#define kFRONT_LEFT 0
#define kFRONT_RIGHT 1
#define kREAR_LEFT 2
#define kREAR_RIGHT 3

#define UP_kP_ARM 30
#define DOWN_kP_ARM 10

#define DOWN_kP_WRIST 5
#define UP_kP_WRIST 20
#define ALL_IN_kP_WRIST 5

#define AIR_OFF_SERVO 0.8
#define HATCH_AIR_SERVO 0.45
#define CARGO_AIR_SERVO 0.25

#define lerpValues(a, b, f) a + f * (b - a)

#define normalizeValues(min, max, value) (value - min) / (max - min)

#define mapValues(value, sourceMin, sourceMax, destMin, destMax) lerpValues(destMin, destMax, normalizeValues(sourceMin, sourceMax, value))


