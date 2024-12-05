This project is my first usage of the [Qt ('cute') framework](https://www.qt.io/product/framework) and [Qt creator](https://www.qt.io/product/development-tools).
It started off as a sandbox for me to familiarize with the platform, but once I grasped the main concepts, I quickly repurposed it as a UX frontend for my [Steganography](https://github.com/LuisMSuarez/Steganography) command-based application.  I had architected the Steganography C++ project to be decoupled from any presentation layer (such as command-based, UX-based or web-based), and I was pleased to see that I could just drop the CPP files from my Steganography project into the Qt project and get it all wired up with zero changes.

Below is a screenshot of the resulting application, and I must say I was quite pleased with the result.

![image](https://github.com/user-attachments/assets/ec9abdaf-4593-43b5-a6bf-41542b7d6753)

The Qt framework is a cross-platform software development framework for application development, supporting Windows, Linux, Mac, Android amongst others.
I had significant prior experience building UX applications on Windows using Borland C++ builder, Borland Delphi, Javax Swing, and Windows Forms applications with Visual Studio, but never before had I build UX-based applications for Linux.  My development environment for this project was SuSE Linux Tumbleweed with Qt Creator and C++ as language.

Overall the experience was remarkably smooth.  Qt provides all of the controls you would expect, just had to familiarize myself with the paradigm of 'Signals and Slots' it provides, but beyond that, I was able to drop the C++ files from my Steganography project with no changes, and get a UX wired up very easily.  I did experience a few bugs with Qt Creator though, such as new controls in the form not being readily available via autocomplete on the IDE.

One aspect I particularly liked about UX design in Qt is the various form layouts that are provided out of the box.  These allow for designing responsive user interfaces, that will render correctly regardless of the screen form factor, resolution or window resizing.  I must say that this project reminded me of how much I enjoy working on GUI applications.

As to-do items I'd like to recompile the application in Windows and verify how much effort would be required and if I observe any significant differences in the UX or behavior of the application.

Controls/utilities used:
- QMainWindow
- QPushButton
- QGraphicsView
- QLabel
- QPlainTextEdit
- QSpinBox
- QStatusBar
- QFileDialog
- QMessageBox

Layouts:
- QFormLayout
- QGridLayout
