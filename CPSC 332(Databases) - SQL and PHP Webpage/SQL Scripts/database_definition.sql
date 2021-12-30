USE cs332t10;

CREATE TABLE Professor (
    SSN int PRIMARY KEY,
    PFName varchar(255),
    PLName varchar(255),
    AreaCode int,
    PPhone int,
    Sex enum('Male', 'Female', 'Nonbinary'),
    Title varchar(255),
    Salary int,
    PStreetAddress varchar(255),
    PCity varchar(255),
    PState varchar(255),
    PZip int
);

CREATE TABLE Degree (
    DegreeName varchar(255),
    PSSN int,
    FOREIGN KEY (PSSN)
        REFERENCES Professor(SSN), 
    PRIMARY KEY (DegreeName, PSSN)
);

CREATE TABLE Department (
    DNum int PRIMARY KEY,
    DName varchar(255),
    DPhone bigint,
    ChairSSN int,
    DLocation varchar(255),
    FOREIGN KEY (ChairSSN)
        REFERENCES Professor(SSN)
);

CREATE TABLE Course (
    CNum int PRIMARY KEY,
    CTitle varchar(255),
    Textbook varchar(255),
    Units int,
    DNum int,
    FOREIGN KEY (DNum)
        REFERENCES Department(DNum)
);

CREATE TABLE Section (
    SecNum int,
    BegTime varchar(255),
    EndTime varchar(255),
    NoOfSeats int,
    ClassRoom varchar(255),
    TeacherSSN int,
    CNum int,
    FOREIGN KEY (TeacherSSN)
        REFERENCES Professor(SSN),
    FOREIGN KEY (CNum)
        REFERENCES Course(CNum),
    PRIMARY KEY (SecNum, CNum)
);

CREATE TABLE Meeting (
    MeetDay enum('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'),
    SecNum int,
    CNum int,
    FOREIGN KEY (SecNum)
        REFERENCES Section(SecNum),
    FOREIGN Key (CNum)
        REFERENCES Section(CNum),
    PRIMARY KEY (MeetDay, SecNum, CNum)
);

CREATE TABLE Prerequisite (
    PrereqNum int,
    CourseNum int,
    FOREIGN KEY (PrereqNum)
        REFERENCES Course(CNum),
    FOREIGN KEY (CourseNum)
        REFERENCES Course(CNum),
    PRIMARY KEY (PrereqNum, CourseNum)
);

CREATE TABLE Student (
    CWID int PRIMARY KEY,
    SFName varchar(255),
    SLName varchar(255),
    SAddress varchar(255),
    SPhone bigint,
    MajorNum int,
    FOREIGN KEY (MajorNum)
        REFERENCES Department(DNum)
);

CREATE TABLE Enrollment (
    Grade enum('A+', 'A', 'A-', 'B+', 'B', 'B-', 'C+', 'C', 'C-', 'D', 'F'),  
    SecNo int,
    ClassNo int,
    SCWID int,
    FOREIGN KEY (SecNo)
        REFERENCES Section(SecNum),
    FOREIGN KEY (ClassNo)
        REFERENCES Section(CNum),
    FOREIGN KEY (SCWID)
        REFERENCES Student(CWID),
    PRIMARY KEY (SecNo, ClassNo, SCWID)
);