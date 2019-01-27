# Presentation
The library used for presenting visual elements for NEWorld project.

## Quick Build Guide
As we are still at the very early stage of the development process, currently the toolset is not able to automate the bootstrap process, so you have to do this manually for now.

1. Clone the master project NEWorldProject/Project to wherever you want

2. Clone the dependency project NEWorldProject/Math, NEWorldProject/task and this repo NEWorldProject/Presentation into the Libs directory under the master project

3. Remember to install the third-party dependency boost-context, boost-stacktrace, libgit2, zlib, SDL2 and the vulkan SDK (please tell me if I am missing anything here) with your favourate package manager

4. Config the CMake under the master project. If all above is done correctly and all necessary path is fed into cmake, the cmake script should do rest of the job

If anyone who is interested in helping me with this project and get stuck with the process above, please feel free to contact me. 

Also, it will be very nice if anyone can contribute the automatic bootstraping script for the platforms you are familiar with. Improving the tools under the master project is also welcomed.

Thank you for your attention (by developer DWVoid)
