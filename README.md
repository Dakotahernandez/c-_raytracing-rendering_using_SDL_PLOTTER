# c-_raytracing-rendering_using_SDL_PLOTTER

#GOALS
Using SDL2 create an application that displays a 2d sphere but using a moving light source give it the effect of looking 3d
The light will follow the location of the mouse


Requirements

SDL2

##### How to add and set up SDL2 on xcode on mac(confirmed working on m2 macbook air ,and m2 pro, and apple intel)
1)if you dont have homebrew download in your terminal using the following command <br />

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)
<br /> <br />

2)download SDL2  in your terminal using homebrew use the following command <br />
brew install sdl2  <br /> <br />


3)Create a new xcode project:set as a command line tool using c++ <br /> <br />


4)Link SDL2 Binary Libraries in Xcode <br />
You need to link the SDL2  binary libraries to your Xcode project. <br />
In Xcode, select your project from the Project Navigator (left panel). <br />
Under Targets, select your project target (usually the same name as your project). <br />
Go to the Build Phases tab. <br />
In the Link Binary With Libraries section, click the + button. <br />
Choose Add Other <br />
once the tab comes up use the keybind command + shift + G <br />
then search  <br />    <br /> 
/opt/homebrew/opt/sdl2/lib    <br /> 
Add libSDL2-2.0.0.dylib to your project(it will say open instead of add but it will add) <br /><br />


5)Set Up Header Search Paths <br />
Select your project in the Project Navigator (left-hand side). <br />
Go to the Build Settings tab. <br />
In the search bar, type Header Search Paths. <br />
Double-click on Header Search Paths and add the following paths: <br />
Add debug and release <br />
For SDL2: /opt/homebrew/include  <br />
/opt/homebrew/include/SDL2 <br />
leave both as non recursive <br /> <br />



6)Set Up Library Search Paths <br />
In Build Settings, search for Library Search Paths. <br />
if it says inherited you dont need to add anything leave it as is <br />
Double-click Library Search Paths and add  <br />
For SDL2: /opt/homebrew/include  <br />
/opt/homebrew/include/SDL2 <br />
non recursive again <br /> <br />


7)finally theres been a recent update to the SDL libraies so their signauture is diffrent <br />
and flagged by apple security so you must turn off signature checking  <br />
Select your project in the Project Navigator (the left panel). <br />
Go to the "Signing & Capabilities" Tab: <br />
Add the "Disable Library Validation" Entitlement: <br />
Scroll down to see if the "App Sandbox" capability is enabled.  <br />
If not, add it by clicking the + button in the upper-left corner and selecting App Sandbox. <br />
Once App Sandbox is added, click on it to expand the entitlement options. <br />
Under Security, you’ll find the Disable Library Validation option. <br />
Enable it by checking the box next to Disable Library Validation. <br />
 <br />
the SDL is now properlly connected <br />
now clean your build (shift + command + k) <br />
try and build (shift + command + b)it before running to try and make sure there are no error <br />
if it builds safely run it(command + r) <br /> <br />


additional notes  <br />
if you cant find your paths for the search paths you can search for your search paths in your console with  <br />
find / -name "SDL2" 2>/dev/null <br />
