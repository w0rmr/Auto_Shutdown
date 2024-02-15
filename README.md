# Auto Shutdown Tool

Simple C program for scheduling system shutdowns, reboots, or screen locks on Linux systems.

## Features

- Schedule shutdowns, reboots, or screen locks
- Flexible time specification options

## Usage

auto_shutdown [OPTION] [TIME]


Options:

    -h, --help: Display help message
    -s, --shutdown: Schedule a system shutdown
    -l, --lock: Lock the screen
    -r, --reboot: Schedule a system reboot

Time Specification:

    Specify time in minutes or use:
        -now for immediate action
        -X for X minutes from now
        -at for a specific 24-hour time (e.g., 18:30)
## Install
    chmod +X install.sh
    ./install.sh
       
