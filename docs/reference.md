# Main
Checks for correct arguments and starts the emulator. It also handles the cleanup of the emulator process when the script is terminated.
Keeps stepping the emulator in a loop as long as the emulator is `State::RUNNING`.

# Emulator Class
The emulator class provides a convenient interface for running and managing the emulator. It allows you to start, stop, and interact with the emulator in a more user-friendly way.
By-default emulator is initialized in the `Model::DMG` mode.

