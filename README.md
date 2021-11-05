# MNXB01ProjectE
Cleaning data:
Open Cleaner.sh and change the name from DATA to the path of the file you want to clean. Run Cleaner.sh in the same directory as your input file if you do not want to provide a path and only the file name. 
You now have a Cleaneddata file with specific format depending on how you have commented out lines in the Cleaner.sh file.

Rootlogon.C:
Change the include path to your include directory in the skeleton file ex: -I/home/name/folder/to/include

Producing Results generally:
In git there exists both the basic root macros for each result and a code skeleton with all the functions iside. Either run the macros from root or run the skeleton via the rootlogon file. To use the rootlogon you must change the include folder path and make sure that a cleaneddata file is availible. 

To produce result 3.1:
Run root int the folder where the skeleton exists with the temponday functions not commented out in project.cpp.
Type project()

To produce result 3.3:
Run root int the folder where the skeleton exists with the extremetemps() function not commented out in project.cpp.
Type project()
To produce 3d graph result:
CHnage the line taking out times in the cleaner to only 12.00
Then insert Cleaneddata into skeleton folder
Start root
Type project()
