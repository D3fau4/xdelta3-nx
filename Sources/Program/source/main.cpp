// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Helper.h"


// Include the main libnx system header, for Switch development
#include <switch.h>

// Main program entrypoint
int main(int argc, char* argv[])
{
    // This example uses a text console, as a simple way to output text to the screen.
    // If you want to write a software-rendered graphics application,
    //   take a look at the graphics/simplegfx example, which uses the libnx Framebuffer API instead.
    // If on the other hand you want to write an OpenGL based application,
    //   take a look at the graphics/opengl set of examples, which uses EGL instead.
    consoleInit(NULL);

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);
    // Init Performance management
    apmInitialize();

    // Other initialization goes here. As a demonstration, we print hello world.
    printf("Welcome to xdelta3-nx!\n");
    Result rc = romfsInit();
    if (R_FAILED(rc))
        printf("romfsInit: %08X\n", rc);
    else
    {
        printf("romfs Init Successful!\n");
        // Set the Cpu boost mode on (This is recommended as it reduces the patching time of a 10mb file from 47 sec to 14 sec)
        appletSetCpuBoostMode(ApmCpuBoostMode_FastLoad);
        int res = patch("romfs:/Orifile/myfile.dat", "sdmc:/mod.dat", "romfs:/patch/patch.xdelta3");
        if (res == 0)
            printf("Patched Successful!\n");
        else
            printf("Patched Failed!: %i\n", res);

        // Set the Cpu boost mode off
        appletSetCpuBoostMode(ApmCpuBoostMode_Normal);
    }

    // Main loop
    while (appletMainLoop())
    {
        // Scan the gamepad. This should be done once for each frame
        padUpdate(&pad);

        // padGetButtonsDown returns the set of buttons that have been
        // newly pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus)
            break; // break in order to return to hbmenu

        // Your code goes here

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);

    // Close Performance management
    apmExit();

    return 0;
}