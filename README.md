# CS-300_DataStructures
#### Summary
Develop a program that will load a data file into a specific data structure and display them in alphanumaric order

#### Problem to solve:
The client, ABCU, has requested a system to house their courses library for the computer science departmart by loading a data file that will be stored in a data structure that will allow them to print all of the available courses in alphanumaric order and search for a specific course that will display the course information to include the course number, course name and any prerequisite courses associated with it. The design problem to solve was to select the best data structure for the system that would execute at a reasonable speed to operate when loading, searching, and printing the course information. 

This effort was completed by developing Pseudocode for the system based on three different Data Structures (Vector, Hash Table, and Binary Search Tree). Once completed, a Big-O analysis was done on the different data strutures before selecting one and building the system.

#### My approach:
When appraching this design system, I reviewed the plus-delta's of each of the three data structures, which can be found in the evaluation document. After identifing the pros and cons to each structure, I reviewed the end goal of the system and how it would be utilized to identify which of the three would execute the best and most effective, in this case, a vector data structure. I selected this data structure based on the assumption that the data being loaded would be close to alphabetical already, removing the benefits that would have been found utilizing a BST (Binary Search Tree). If not for that assumption, I would have utilized the BST instead of the vector data structure. 

#### Roadblocks overcame:
The largest roadblock that I encountered was the Big-O analysist of the three different data structure methods. As this was my first time completing this type of anaylist, I was second guessing my work at all times. After completing the work, I spent a large amount of time reviewing Big-O theroy and study materials to ensure that I had completed the work accurately. 

#### What I've learned when approaching designing software and developing programs:
After completing this work, I have developed a better understanding and appreciatation for the importance of developing a system with runtime and memory management considerations being built into the development process. 

#### How my skills to write maintainable, readable, and adaptable code has grown:
Through the many exercises involved in this project, I have honed my ability to write easy to interperate pseudocode that can be translated into functioning code. By developing pseudocode in this manner, developing the working code is streamlined and easy to follow, reducing the coding time needed. Additionally, I am able to visually see fucntions/methods that can be utilized across a system by multiple other methods, allowing for reuse and removing the need to rewrite code over and over. This allows the development of pseudocode that can be adapted to multiple different uses in multiple different programs. 
