use cs332t10;

-- Professors
INSERT INTO Professor (SSN, PFName, PLName, AreaCode, PPhone, Sex, Title, Salary, PStreetAddress, PCity, PState, PZip)
    VALUES 
        (123121234, "John", "Chan", 562, 1234567, 'Male', "Professor", 80000, "1212 Teaching Street", "Fullerton", "California", 90621), 
        (222334444, "Maria", "Valasquez", 562, 2223333, 'Female', "Doctor", 90000, "200 Doctor Road", "Fullerton", "California", 90621),
        (555667777, "Pasquale", "Garibaldi", 951, 1234567, 'Nonbinary', "Professor", 65000, "42133 Santino Court", "San Diego", "California", 22400);


-- Degrees
INSERT INTO Degree (DegreeName, PSSN) 
    VALUES 
        ("Master's Degree in Computer Science", 123121234), 
        ("Master's Degree in Computer Science", 555667777), 
        ("Doctorate of Biochemistry", 222334444);


-- Departments
INSERT INTO Department (DNum, DName, DPhone, ChairSSN, DLocation) 
    VALUES 
        (1, "Computer Science", 5626667777, 123121234, "Computer Science Building"), 
        (2, "Chemistry and Biochemistry", 5267778888, 222334444, "McCarthy Hall");


-- Courses
INSERT INTO Course (CNum, CTitle, Textbook, Units, DNum) 
    VALUES 
        (1, "Intro to Computer Science", "Computer Science Fundementals by Jimmy John", 3, 1),
        (2, "Object Oriented Programming", "Object Orientation by Susie Lane", 3, 1),
        (3, "General Chemistry", "Chem for Dummies by Doctor Science", 4, 2),
        (4, "Organic Chemistry", "OChem for Masochists by Your Mom", 5, 2);


-- Sections
INSERT INTO Section (SecNum, BegTime, EndTime, NoOfSeats, ClassRoom, TeacherSSN, CNum)
    VALUES 
        (1, "2:30", "3:30", 25, "Computer Science Building 201", 123121234, 1),
        (2, "3:30", "4:30", 25, "Computer Science Building 201", 123121234, 1),
        (1, "1:30", "2:45", 22, "McCarthy 101", 555667777, 2),
        (2, "3:00", "4:15", 22, "McCarthy 101", 555667777, 2),
        (1, "3:00", "4:15", 40, "McCarthy 408", 222334444, 3),
        (2, "4:30", "5:45", 40, "McCarthy 408", 222334444, 3),
        (1, "6:30", "7:45", 40, "McCarthy 505", 222334444, 4),
        (2, "8:30", "9:45", 40, "McCarthy 505", 222334444, 4);


-- Meetings
INSERT INTO Meeting (MeetDay, SecNum, CNum)
    VALUES 
        ("Monday", 1, 1),
        ("Friday", 2, 1),
        ("Monday", 1, 2),
        ("Tuesday", 2, 2),
        ("Wednesday", 1, 3),
        ("Saturday", 2, 3),
        ("Tuesday", 1, 4),
        ("Thursday", 2, 4);


-- Prerequisites
INSERT INTO Prerequisite (PrereqNum, CourseNum)
    VALUES 
        (1, 2),
        (3, 4);


-- Students
INSERT INTO Student (CWID, SFName, SLName, SAddress, SPhone, MajorNum) 
    VALUES 
        (111999888, "Aaron", "Cope", "42190 Fullerton Road, Murrieta, CA", 9518136692, 1),
        (888555666, "Jarod", "Sandoval", "5312 Pizza Lane, La Habra, CA", 9514673728, 1),
        (898098767, "Fiorella", "Ghisolfi", "342 Spaghetti Court, Los Angeles, CA", 9512345432, 1),
        (364786204, "Chance", "Nguyen", "9890 Jefferson Avenue, Carlsbad, CA", 5646547867, 1),
        (947283002, "Samson", "Mbene", "7294 Cherry Road, El Monte, CA", 5641237384, 2),
        (119283948, "Jedediah", "Gooberman", "7223 Let Me Die Circle, Victorville, CA", 8742930593, 2),
        (808808808, "Pierce", "Brosnan", "5 Ponte Trucha Street, CA", 9673849203, 2),
        (345234748, "Jenson", "Mbene", "64532 Commonwealth Road, Fullerton, CA", 6784561821, 2),

        (111999889, "Faron", "Fope", "43190 Fullertin Road, Burrieta, CA", 8518136692, 1),
        (888555668, "Farod", "Fandoval", "2312 Pizza Lane, Da Habra, CA", 8514673728, 1),
        (898098768, "Diorella", "Fhisolfi", "442 Spaghetti Court, Dos Angeles, CA", 8512345432, 1),
        (364786208, "Dhance", "Dguyen", "3890 Pefferson Avenue, Snarlsbad, CA", 9646547867, 1),
        (947283008, "Famson", "Fbene", "8294 Cherry Road, Del Monte, CA", 8641237384, 2),
        (119283949, "Fedediah", "Fooberman", "3223 Let Me Die Smircle, Pictorville, CA", 2742930593, 2),
        (808908804, "Fierce", "Frosnan", "5 Monte Crucha Street, CA", 2673849203, 2),
        (345234754, "Fenson", "Fbene", "34532 Dommonwealth Road, Pullerton, CA", 8784561821, 2);


-- Enrollment Records
INSERT INTO Enrollment (Grade, SecNo, ClassNo, SCWID)
    VALUES 
        ('A+', 1, 1, 111999888),
        ('A', 1, 2, 111999888), 
        ('C-', 1, 3, 111999888), 
        ('F', 1, 4, 111999888), 

        ('C-', 1, 1, 888555666),
        ('D', 1, 2, 888555666), 
        ('B+', 1, 3, 888555666), 
        ('A', 1, 4, 888555666), 

        ('A', 1, 1, 898098767),
        ('C-', 1, 2, 898098767), 
        ('B+', 1, 3, 898098767), 
        ('D', 1, 4, 898098767), 

        ('F', 1, 1, 364786204),
        ('A+', 1, 2, 364786204), 
        ('B-', 1, 3, 364786204), 
        ('C', 1, 4, 364786204), 

        ('A', 1, 1, 947283002),
        ('A-', 1, 2, 947283002), 
        ('B', 1, 3, 947283002), 
        ('B+', 1, 4, 947283002), 

        ('D', 1, 1, 119283948),
        ('B+', 1, 2, 119283948), 
        ('A', 1, 3, 119283948), 
        ('D', 1, 4, 119283948), 

        ('B-', 2, 1, 808808808),
        ('A-', 2, 2, 808808808), 
        ('B', 2, 3, 808808808), 
        ('C+', 2, 4, 808808808), 

        ('B+', 2, 1, 345234748),
        ('B', 2, 2, 345234748), 
        ('D', 2, 3, 345234748), 
        ('C-', 2, 4, 345234748), 

        ('A+', 2, 1, 111999889),
        ('A', 2, 2, 111999889), 
        ('B+', 2, 3, 111999889), 
        ('B', 2, 4, 111999889), 

        ('A', 2, 1, 888555668),
        ('C', 2, 2, 888555668), 
        ('A', 2, 3, 888555668), 
        ('F', 2, 4, 888555668), 

        ('D', 2, 1, 898098768),
        ('C-', 2, 2, 898098768), 
        ('A+', 2, 3, 898098768), 
        ('B+', 2, 4, 898098768), 

        ('A+', 2, 1, 364786208),
        ('D', 2, 2, 364786208), 
        ('A+', 2, 3, 364786208), 
        ('B', 2, 4, 364786208), 

        ('B-', 2, 1, 947283008),
        ('B+', 2, 2, 947283008), 
        ('A+', 2, 3, 947283008), 
        ('B-', 2, 4, 947283008), 

        ('A+', 2, 1, 119283949),
        ('C-', 2, 2, 119283949), 
        ('D', 2, 3, 119283949), 
        ('C+', 2, 4, 119283949), 

        ('D', 2, 1, 808908804),
        ('B+', 2, 2, 808908804), 
        ('A-', 2, 3, 808908804), 
        ('C-', 2, 4, 808908804), 

        ('C+', 2, 1, 345234754),
        ('C', 2, 2, 345234754), 
        ('A-', 2, 3, 345234754), 
        ('C+', 2, 4, 345234754);