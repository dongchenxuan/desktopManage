# desktopManage
## Directory structure
- |——bin (configuration file)
- |
- |——images (Pictures resources)
- |————controls (Control icon)
- |————filewin (File action Icon)
- |————gif (Animation)
- |————monitor (Monitor picture resources)
- |————traymenu (Tray menu icon)
- |————readme 
- |——testFile 
- |——testImsges
## Architecture diagram
In the design process, it is mainly divided into two parts: basic function and extended function. The specific architecture is shown in the figure.
- Ⅰ.Basic functions include basic operations on files (folders), such as creating and moving files (folders).
In the application icon function, it is divided into icon resizing, icon sorting and document classification.
-- i.When resizing the icon, you can use the function of viewing file information in windows to zoom in or out the file display icon. At the same time, you can also add the way of list display to give users more choices
-- ii. In the icon sorting function, the files (folders) are sorted in the form of file (folder) name, modification date, size, type, etc.
-- iii.Document classification is the core of the tool, which can be simply classified by judging the file type. The final goal is to archive and classify the files (folders) created by users in time. (provided that the user has agreed that the software automatically classifies documents (folders)).
- Ⅱ.Extended functions include innovative functions and additional functions
-- i. Among the innovative functions, according to the current needs of desktop management software, it has been basically met on the windows platform. However, there are some shortcomings. For example, in the document column, users can choose whether to add a sub document column (sub window) to divide word, PPT, Excel and other files. Of course, the name of the form can be changed and selected by the user. Secondly, it is not well supported on other operating platforms. Therefore, desktop management software needs to have good compatibility and good scalability.
-- ii.In the additional functions, the functions of real-time performance monitor and weather forecast are added, and an extended interface is provided for software update. When using real-time performance monitor, you can view the use of computer resources without entering commands, which is a friendly way for most ordinary users to obtain such information. Real time update of computer resource usage can also let users know the current state of the computer. In the application market, most desktop management tools add many functions according to the needs of users, among which weather forecast is the most typical example. Therefore, it is necessary to add a weather forecast module for users. Users can also choose to turn it on and off according to their needs.
![Architecture diagram](/images/readme/Architecture diagram(en).png)
## Use case diagram

![Architecture diagram](/images/readme/Use case diagram(en).png)
## Project description
- 
