CREATE DATABASE airport_database;

USE airport_database;

CREATE TABLE Passenger
(
	Passenger_ID INT UNIQUE,
	Name VARCHAR(100) NOT NULL,
	Date_of_Birth date,
	Contact_No BIGINT,
	PRIMARY KEY (Passenger_ID)
);


CREATE TABLE flights
(
	Flight_No VARCHAR(6),
	Depart_IATA VARCHAR(3),
	Arrival_IATA VARCHAR(3),
	Flight_Date date,
	Depart_Time VARCHAR(5),
	Arrival_Time VARCHAR(5),
	Price BIGINT,
	PRIMARY KEY (Flight_No)
);


CREATE TABLE tickets
(
	Ticket_No INT UNIQUE,
	Seat VARCHAR(3),
	Passenger_ID INT,
	Flight_No VARCHAR(6),
	PRIMARY KEY (Ticket_No),
	FOREIGN KEY (Passenger_ID) references Passenger(Passenger_ID),
	FOREIGN KEY (Flight_No) references flights (Flight_No)
);

CREATE TABLE employee
(
	Employee_ID VARCHAR(50) UNIQUE,
	Employee_Pass VARCHAR(25),
	Status VARCHAR(2),
	PRIMARY KEY (Employee_ID)
);



INSERT INTO employee (Employee_ID, Employee_Pass, Status) VALUES
("Sasuke","itachi", "Ad"),
("Naruto","sasuke", "Ad"),
("Sakura","sasuke", "Ad"),
("Kakashi Hatake","noname", "Re"),
("Jiraiya","tsunade", "Re"),
("Tsunade","noname", "Re"),
("Gaara","sand", "Ad"),
("Minato Namikaze","kushina", "Re"),
("Oruchimaru","windysasuke", "Re"),
("Shikamaru","temari", "Ad");



-- INSERT INTO receptionist (Recept_ID, Recept_Pass) VALUES
-- ("Goku","chichi"),
-- ("Bulma","vegeta"),
-- ("Vegeta","goku"),
-- ("Gohan","videl"),
-- ("Satan","buu"),
-- ("Piccolo","gohan"),
-- ("Krillin","18"),
-- ("Dende","gohan"),
-- ("Yamcha","bulma"),
-- ("Master Roshi","everyone");



INSERT INTO Passenger (Passenger_ID ,Name, Date_of_Birth, Contact_No) VALUES 
("1", "Shehsawar Ali","1998/02/14","03713661550"),
("2", "Taha Maqbool","1994/03/26","03721234567"),
("3", "Shayan Amjad","1999/01/02","03708910110"),
("4", "Shariq Ghazi","1972/09/14","03701213140"),
("5", "Usama -","1981/12/15","03741516170"), 
("6", "Balaj Khalid","1956/05/24","03701819200"),
("7", "Haider Ali","1945/06/18","03702122230"),
("8", "Atayab Naeem","1977/07/07","03702425260"),
("9", "Muzzamil Hussain","1988/08/08","03702728290"),
("10", "Farhad Ahmed","2003/03/03","03703031320");


INSERT INTO flights (Flight_No, Depart_IATA, Arrival_IATA, Flight_Date, Depart_Time, Arrival_Time, Price) VALUES
("PKR004","KHI","DXB","2019/11/01","11:00", "12:15", "15000"),
("RGR005","KHI","LDN","2019/11/02","12:30", "01:45", "13545"),
("SDF013","KHI","BKK","2019/11/03","09:00", "10:50", "5156"),
("EMS009","KHI","LHR","2019/11/04","11:00", "12:15", "54546"),
("ERE001","LHR","DXB","2019/11/05","09:30", "10:45", "151654"),
("ASD023","LHR","LDN","2019/11/06","11:00", "12:15", "12614"),
("GRE034","LDN","WDC","2019/11/07","12:30", "01:45", "65454"),
("SAT008","WDC","NYK","2019/11/08","09:30", "10:45", "54545"),
("ACCA52","PKT","BEJ","2019/11/09","17:45", "23:50", "154654"),
("CIE029","NAG","WW2","2019/11/10","18:50", "21:15", "126787");


INSERT INTO tickets (Seat, Ticket_No, Passenger_ID, Flight_No) VALUES
("12B", "9434719","1","PKR004"),
("15C", "6517648","2","GRE034"),
("9A", "1674187","3","SAT008"),
("32A", "9412478","4","CIE029"),
("62D","5419549","5","ASD023"),
("12C","6546549","6","ERE001"),
("13B","8798549","7","EMS009"),
("12A", "6549848","8","EMS009"),
("24D", "1635348","9","PKR004"),
("5E", "6489849","10","SDF013");
