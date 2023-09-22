/** Change these values as necessary to handle a variety of flights */
/* ---------------------------------------------------------------- */

// Computer Mode {0: Systems Test (Disarmed), 1: Pyro Channel Test (Armed), 2: Active Flight Mode (Armed)}
// (Currently only supports Computer Mode 0)
#define COMP_MODE 0

// Set data-logging baud rate
#define BAUD_RATE 115200

// Set barometric "zero" pressure so the altitude readings correspond to the current altitude 
#define BARO_ZERO_PRESSURE 1013.2

// 0 -> Rocket detects external launch mechanism
// 1 -> Rocket activates channel to launch itself (Currently not supported)
#define LAUNCH_METHOD 0

// True or False based on if there is a backup pyro for the chute 
#define PYRO_CHUTE_BACKUP_EN false

// Customize Pyro Channel Mappings to Digital I/O Ports
#define PYRO_CHUTE 4
/*note that PYRO_CHUTE_BACKUP_EN (above) must be set to "true" if you are using a backup channel */ 
#define PYRO_CHUTE_BACKUP 9 
/* other mappings to be used as necessary */
// #define PYRO_LAUNCH 2 
// #define PYRO_MISC 3 

// true or false based on if Thrust Vector Control (TVC) is enabled or not (currently only "false" is supported)
#define TVC false

// true or false based on if Active Fin Control (AFC) is enabled or not (currently only "false" is supported)
#define AFC false 
