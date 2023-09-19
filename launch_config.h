/** Change these values as necessary to handle a variety of flights */

// Computer Mode {0: Systems Test (Disarmed), 1: Pyro Channel Test (Armed), 2: Active Flight Mode (Armed)}
// (Currently only supports Computer Mode 0)
#define COMP_MODE 0

// Set barometric "zero" pressure so the altitude readings correspond to the current altitude 
#define BARO_ZERO_PRESSURE 1014.10

// 0 -> Rocket detects external launch mechanism
// 1 -> Rocket activates channel to launch itself (Currently not supported)
#define LAUNCH_METHOD 0

// 0 -> TVC support disabled
// 1 -> TVC support enabled (Currently not supported)
#define TVC 0 

// 0 -> Active Fin Control (AFC) disabled
// 1 -> AFC enabled (Currently not supported)
#define AFC 0 

// 0 -> No Pyro Channel Backup 
// 1 -> Pyro Channel Backup 
#define PYRO_BACKUP_EN 0


 


