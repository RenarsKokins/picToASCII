# picToASCII
Convert your images to ASCII text! 
You can use any picture format you want and you can define the size of your ASCII image to suit your needs!
# How to use
1. Open your command prompt
2. Change current directory to ```.../picToASCII/x64/Debug``` (write the path to that debug folder)
3. Execute exe file using this command: ```picToASCII.exe "starting images/1.jpg" "converted images/text.txt" 45```
4. It should print out an ASCII image in cmd and save it to a text file!

If you want to change the image to be converted, add the path of that image in place of ```starting images/1.jpg``` (double quotes MUST be added).
If you want to change the path, where the text is saved, change the path of ```converted images/text.txt``` (double quotes MUST be added).
If you want to change the size of your ascii image, write your own width instead of ```45``` (it will calculate height on it's own). If you enter ```120 60``` for example, then it will make an ascii image with width: 120 and height: 60.
