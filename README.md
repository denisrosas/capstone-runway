# capstone-runway
This is my Capstone project for the Capstone Runway detection Project made by EIT Digital available on Coursera

https://www.coursera.org/learn/autonomous-runway-detection

The purporse is to create a FreeRTOS project that: 
1) Get images from an Airplane camera that captures images of the runway during landing
2) Use the canny algorith to generate an image with only the Edges
3) encrypt that image using the RSA algorithm
4) send the encrypted file to a server by TCP connection

Instructions – How to Run the project
Pre-requirements:
1. You must have Visual Studio Communuity 2019 Installed. If you don’t install it from this link
2. You must have Python 3.X or later installed and mapped in your Windows PATH. You can download from this link

Steps to run the project:
1. Uncompress the Capstone project
2. First step is to open the FreeRTOS Client on Visual Studio. Go to the folder ..\freertos_capstone_project2\FreeRTOS-Plus\Demo\FreeRTOS_Plus_TCP_and_FAT_Windows_Simulator
3. Double click the “WIN32.vcxproj” file to open the project
4. First start the server. Just double click on the
5. Right click in RTOSDemo and click in “Compile”
6. Now lets start the server. Go to the folder ..\capstone\tcp_server
7. Double click on the runme.bat script. You should see the command line
8. Now to start the FreeRTOS Client to start the simulation click on the “Start Debugging button”

Please read the report PDF file to see the screenshots.
