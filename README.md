# MNXB01ProjectE
Cleaning data:
Open Cleaner.sh and change the name from DATA to the path of the file you want to clean. Run Cleaner.sh in the same directory as your input file if you do not want to provide a path and only the file name. 
You now have a Cleaneddata file with specific format depending on how you have commented out lines in the Cleaner.sh file.
For specific instructions on which commands to use in the cleaner, see each result part in this file.

Rootlogon.C:
Change the include path to your include directory in the skeleton file ex: -I/home/name/folder/to/include

Producing Results generally:
In git there exists both the basic root macros for each result and a code skeleton with all the functions iside. Either run the macros from root or run the skeleton via the rootlogon file. To use the rootlogon you must change the include folder path and make sure that a cleaneddata file is availible. 

To produce result 3.1:
Cleaner settings:
Make sure to take out both 12:00 and 13:00 in the same sed command:Line 7 sed -i '/12:00\|13:00/!d'
Do not include picking out a specific year
Do not inculde the third and fourth commands in the section: #Cleanes the dashes separating the dates
Now run Cleaner.sh with the path to your data file and either provide the cleaneddata path in the code for result 3.1 or move the cleaneddata to the same directory as the skeleton.
Run root in the folder where the skeleton exists with the temponday functions not commented out in project.cpp.
Type project()

To produce result 3.3:
Run root int the folder where the skeleton exists with the extremetemps() function not commented out in project.cpp.
Type project()

To produce 3d graph result:
Change the line taking out times in the cleaner(Line 7) to only 12.00
Include removing times loop
Do not include picking out a single year
Include everything in section: 
#Cleanes the dashes separating the dates
Run the cleaner with the provided path to the data file for Karlstad or another one you want to plot
Then insert Cleaneddata into skeleton folder or provide its path in the code for 3d plotting(AvgTemp3D)
Start root
Type project()
