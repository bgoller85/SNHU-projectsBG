# SNHU-projectsBG
//Software Test Automation & QA//

\\Reflection\\
1. How can I ensure that my code, program, or software is functional and secure?

Testing: Comprehensive testing is key. Employ various testing types, such as unit testing, integration testing, and end-to-end testing. This will help you identify and rectify bugs, ensuring your software functions as intended.
Security Scanning: Regularly scan your code and applications for security vulnerabilities. Utilize security tools and follow best practices for secure coding, such as input validation and access control.
Code Reviews: Collaborate with peers for code reviews. Fresh perspectives often uncover issues that might be overlooked by the original developer.
Documentation: Properly document your code and software. This not only aids in understanding but also helps in maintaining security through clear code architecture.
Security Principles: Apply security principles like the Principle of Least Privilege and Defense in Depth to ensure your software is resilient to attacks.
Security Updates: Stay updated with security patches and updates for libraries and dependencies. Timely updates can patch known vulnerabilities.

2. How do I interpret user needs and incorporate them into a program?
User Research: Begin with user research. Engage with end-users, stakeholders, or use surveys and interviews to understand their requirements and expectations.
User Stories: Create user stories to capture user needs and functionalities from their perspective. These should be clear, concise, and specific.
Prioritization: Prioritize user needs based on their importance and impact. Use techniques like MoSCoW (Must-haves, Should-haves, Could-haves, and Won't-haves) to prioritize features.
Prototyping: Develop prototypes or mockups to visualize the user interface and gather feedback early in the process.
User Acceptance Testing (UAT): Involve users in UAT to ensure that the program aligns with their needs. Their feedback is invaluable for refining the software.
Iterative Development: Embrace an iterative development process, where you continuously gather feedback and make improvements based on user input.
Clear Communication: Maintain open lines of communication with users and stakeholders throughout the development process to address changing needs and expectations.
Incorporating user needs is an ongoing process. User needs can evolve, so it's vital to stay engaged with users and adapt to their changing requirements.

3. How do I approach designing software?
Requirements Analysis: Start by understanding the requirements thoroughly. Engage with stakeholders, users, and consider non-functional requirements.
System Architecture: Design the overall system architecture. Decide on the system's components, their interactions, and data flow.
Modular Design: Break down the software into smaller, manageable modules or components. Each module should have a specific function and interface with other modules.
Data Design: Plan how data will be stored, accessed, and processed. This includes designing databases and data structures.
User Interface (UI) Design: Create a user-friendly interface that aligns with user needs and provides an intuitive user experience.
Coding Standards: Establish coding standards and guidelines to maintain consistency and quality in the codebase.
Testing Strategy: Develop a comprehensive testing strategy, including unit testing, integration testing, and end-to-end testing to ensure the software functions correctly.
Documentation: Document the software design, code, and user manuals comprehensively. This helps with future maintenance and onboarding.
Version Control: Utilize version control systems (e.g., Git) to track changes and collaborate effectively with a team.
Iterative Approach: Design is not a one-time activity. Embrace an iterative approach, where you refine the design based on feedback and changing requirements.

//Analysis and Design//

\\Journal\\
1. What was the problem you were solving in the projects for this course?
    The goal was to create a program that can load course data from a file, store it in a suitable data structure, and provide various functionalities like listing all courses, displaying specific course         
    information, and handling prerequisites.
2. How did you approach the problem? Consider why data structures are important to understand.
    The approach involved reading data from a file, parsing it into meaningful course objects, and storing these objects in a data structure. The program then offered different operations on this data, such as   
    displaying course lists and information. Understanding data structures is crucial for solving such problems because they provide a way to efficiently organize and access data, which directly impacts the 
    performance and usability of the program. The choice of data structure can significantly affect the efficiency of various operations like insertion, retrieval, and searching.
3.How did you overcome any roadblocks you encountered while going through the activities or project?
    Through careful testing, debugging and some help from drop-in tutoring I was able to overcome all roadblocks that I ran into.
4. How has your work on this project expanded your approach to designing software and developing programs?
    Working on this project expanded my approach to designing software by emphasizing the importance of data structure selection based on the requirements of the problem. It highlighted the trade-offs between 
    different data structures and how they impact performance. Additionally, I gained experience in designing user-friendly interfaces, handling user input, and managing program flow.
5. How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
    This project helped me develop skills in writing maintainable, readable, and adaptable programs. The code in project two demonstrates good practices such as using meaningful variable and function names, 
    modularizing code into functions, and providing comments for clarity. These practices enhance code readability and maintainability. Additionally, the program's structure allows for easy adaptation to future 
    changes or enhancements, showcasing the flexibility of my design.

//Operating Platforms//

\\The Gaming Room reflection\\
1. Briefly summarize The Gaming Room client and their software requirements. Who was the client? What type of software did they want you to design? What did you do particularly well in developing this documentation?

The client was The Gaming Room. They currently had a game called Draw It or Lost It for Android. The Gaming Room wanted to improve the software functionality and to expand to other platforms. I kept this document clear, concise, and to the point.

2. What did you do particularly well in developing this documentation?

My description of the domain model and the server/client side descriptions for different operating platforms was well desinged and written.

3. What about the process of working through a design document did you find helpful when developing the code?

It helps to keep you focused on the task at hand and to decide on what tasks are important and which ones don't need time and focus on.

4. If you could choose one part of your work on these documents to revise, what would you pick? How would you improve it?

Recomendations were hard for me, I haven't had a ton of experience in programming before beginning my computer science degree. After I have had more in field experience, I would revise my recommendations based off what I have been successful with.

5. How did you interpret the user’s needs and implement them into your software design? Why is it so important to consider the user’s needs when designing?

I took what was needed for the functionallity of the game and then split it up so that there would be less work and time spent expanding to other operating platforms. All while still keeping the game the same. Your client may be the one to ask you to do the work, but it's the users who truely control the product. If they don't trust the software or have problems with it, then they won't use it.

6. How did you approach designing software? What techniques or strategies would you use in the future to analyze and design a similar software application?

I put my focus on clear documentation and game functionality to allow easier updates and maintenence. I believe that in the future I will be part of a team, so I would take my experiences and those of my peers, and find the best solution to complete the project.

//Programming Languages//

\\Corner Grocer App Reflection\\

1. Summarize the project and what problem it was solving.
  This project was for a grocery store to see what items their customers purchased the most. It took an input file and read items to see how many times each item appeared. It then outputted the item name and frequency using menu options for the user to choose from that allowed them to either pick an item and see it's frequency, print the full list of items with their numerical frequency, print the list in histogram form and an option to exit the menu. This also output a text file with item names and their frequency.
  
2. What did you do particularly well?
My code utilized classes and functions very well so that the only code in my main function was to call the other functions.

3. Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
I could maybe make the classes in different header files so that if I needed to grow the program I could just include those header files and inherit from the function classes to create new specific functions like lableling the items into seperate categories so that the user could see the frequency of fruits or vegetables etc. 

4. Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
The map function was new to me and I had to flip back through the zybooks lecture on the matter and I referenced some examples in stackoverflow.

5. What skills from this project will be particularly transferable to other projects or course work?
Many programming languages are similar, so the skills from this project could help with java or python projects as well

6. How did you make this program maintainable, readable, and adaptable?
I used switch cases instead of if-else statements for my menu functions for a cleaner code appearance and faster functionality. It would also be easier to make changes the menu this way. I added in-line comments to help with understanding the funciton of my code.


//Software Development Lifecycle//

1. How do I interpret user needs and implement them into a program? How does creating “user stories” help with this?

  I receive customer feedback for features that are wanted and create user stories that reflect the customer's needs. I develop user stories with specific requirements so that a tester can build cases that will implement the features into a program. These stories are labeled with their priority and what actions the user will take to get results. Once the stories are laid out and a tester creates test cases, the developer can implement the features into the program. Once the code is implemented the tester can refer to the cases and user stories to see if they meet the requirements.

2. How do I approach developing programs? What agile processes do I hope to incorporate into my future development work?

  I approach development with the user stories and test cases in mind so that I know what features to implement and in what order. I can use agile planning to setup a board with what stories I will implement during each sprint along with practices like poker-planning to decide value and order of stories to implement. I can use agile methodology when changes are made to the product backlog and adapt the program as needed. I would use the daily scrum meetings to communicate what I did the day before, what I will do next, and what impediments I have run into.
  
3. What does it mean to be a good team member in software development?

  -Be respectful of others
  -Commit to the project
  -Accept responsibility and be accountable
  -Work collaboratively and make decisions with the team
  -Recognize and celebrate individual and team accomplishments
  -Provide feedback in a constructive manner and don't take offense to constructive feedback
  -Abide by the agile manifesto values
  -Be on time and productive
