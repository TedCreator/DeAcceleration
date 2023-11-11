// Copyright 2023 Ted Akahori

// Returns boolean corresponding to if Mouse Acceleration is on.
bool AccelStatus();
// Returns a string of values from the SPI_GETMOUSE input parameter.
string RegistryString(const int pvParam[3]);
// Disables Mouse Acceleration using SPI_SETMOUSE & SPIF_SENDCHANGE.
void disableMouseAccel();