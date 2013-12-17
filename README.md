Odyssey Project
===============

Project of robot looking for objects in a room. The robot uses a Raspberry Pi connected to a camera (RaspiCam). This RPi is used to both control a PIC microcontroller and communicate with a PC. The PC performs the image processing required to detect objects and obstacles. All the communications are secured.


Mercury branch
--------------

Mercury is the Roman God of travelers (among other stuff!).
In our project, Mercury branch concerns the robot itself. It embeds a PIC microcontroller that manages servo-motors and battery life time. Moreover, it is connected to a Raspberry Pi module by a serial link (UART).


Polyphemus branch
------------------

Polyphemus is a Cyclope described in the Homer's Odyssey.
It is the combination of both Raspberry Pi module and RaspiCam (webcam). This branch is used to get frames from the webcam and send them to a PC, and thus perform image processing. Moreover, it is used to control the Mercury branch : the path to follow is determined by the PC, sent to the RPi module and then to the PIC microcontroller.


Jupiter branch
--------------

Jupiter is the chief of Roman deity.
For our project, he represents the PC system. It manages the image processing to discover obstacles and items. So, it decides which way the robot must follow.
