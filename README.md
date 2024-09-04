
![Windows](https://github.com/barry-ran/QtScrcpy/workflows/Windows/badge.svg)
![Ubuntu](https://github.com/barry-ran/QtScrcpy/workflows/Ubuntu/badge.svg)
[![Qt](https://img.shields.io/badge/Qt-6.x-66cc00.svg)](https://www.qt.io/)
[![C++](https://img.shields.io/badge/C%2B%2B-17.0-4c979e.svg)](https://isocpp.org/)

# QT-Animated-Switch
A visually appealing and interactive switch widget that can be turned on or off with a smooth animation.

![switch](gitResources/standartSwitch.gif)

## Features
- Animated switch with a toggle button
- Smooth and visually appealing animation
- Interactive and responsive to user input
- Customizable animation duration and style

## QSS properties
The switch class has a set of properties with which you can use your own style sheet to customize the style and speed of animations


### Style properties
```css
ToggleSwitch{
    //Color switch
    qproperty-colorSwitch: rgb(65, 80, 255);
    //Setting blue in rgb on hover
    qproperty-colorHover: 0;
    //Minimum opacity switch
    qproperty-minOpacity: 0;
    //Maximum opacity switch
    qproperty-maxOpacity: 255;
    //min Setting blue in rgb on hover
    qproperty-mincolorHover: 180;
    //min Setting blue in rgb on hover
    qproperty-maxcolorHover: 222;
    //Maximum opacity switch on hover
    qproperty-maxHoverOpacity: 50;
}
```

### Duration properties
```css
ToggleSwitch{
    //Slider movement speed 
    qproperty-durationToggledProcces_sliderPos: 300;
    //Duration change blue rgb setting on Toggled status
    qproperty-durationToggledHovered: 120;
    //Duration change blue rgb setting on UnToggled status
    qproperty-durationUnToggledHovered: 20;
    //Duration change opacity rgb setting on UnToggled status
    qproperty-durationToggledHovered_opacity: 120;
    //Duration change opacity switch rgb setting 
    qproperty-durationToggledProcces_opacity: 300;
}
```

# Build Windows (msvc)
```
mkdir build
cd build
cmake ..
cmake --build . --config Release -j 10
```
# Build Linux (clang , gcc)
```
mkdir build
cd build
cmake ..
make -j 10
```
