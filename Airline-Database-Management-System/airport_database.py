# frontend
from prettytable import prettytable

import mysql.connector
mydb = mysql.connector.connect(
host="localhost",
user="root",
passwd="password",
database = "airport_database"
)
print(mydb)
cursor = mydb.cursor()

print("WELCOME TO SHEHSU AIRLINE. NOW FINALLY OPEN!")

def Admode():
	print("Logged in as Admin")
	print("1. Add a new flight record")
	print("2. Update details of an existing flight")
	print("3. Cancel a flight")
	print("4. View all flights for a particular airport on a date")
	print("5. View database")
	print("")

	choice = int(input("Enter your choice: "))
	while(choice < 1 or choice > 5):
		choice = int(input("Invalid operation. Enter again: "))

	if choice == 1:
		flightno = input("Enter Flight_No: ")
		sql = "SELECT Flight_No FROM flights WHERE Flight_No = %s"
		par = (flightno, )
		cursor.execute(sql, par)
		result = cursor.fetchone()
		if result != None:
			print("Flight_No already exists")
		else:
			dep = input("Enter Departure_IATA: ")
			arr = input("Enter Arrival_IATA: ")
			dat = input("Enter flight data (YYYY/MM/DD): ")
			t1 = input("Enter depature time (HH:MM): ")
			t2 = input("Enter arrival time (HH:MM): ")
			price =  input("Enter flight price: ")
			sql = "INSERT INTO flights (Flight_No, Depart_IATA, Arrival_IATA, Flight_Date, Depart_Time, Arrival_Time, Price) VALUES (%s,%s,%s,%s,%s,%s,%s)"
			par = (flightno, dep, arr, dat, t1, t2, price)
			cursor.execute(sql, par)
			print("Flight added to database")

	if choice == 2:
		ID = input("Enter Flight_No: ")
		sql = "SELECT Flight_No FROM flights WHERE Flight_No = %s"
		par = (ID, )
		cursor.execute(sql, par)
		result = cursor.fetchone()
		if result == None:
			print("Flight_No does not exist")
		else:
			print("1. Departure_IATA")
			print("2. Arrival_IATA")
			print("3. Flight_Date")
			print("4. Depart_Time")
			print("5. Arrival_Time")
			print("6. Price")

			select = int(input("Select: "))
			if(select == 1):
				dep = input("Enter new Depart_IATA: ")
				sql = ("UPDATE flights SET Depart_IATA = %s WHERE Flight_No = %s")
				par = (dep, ID)
				cursor.execute(sql, par)
			elif(select == 2):
				arr = input("Enter new Arrival_IATA: ")
				sql = ("UPDATE flights SET Arrival_IATA = %s WHERE Flight_No = %s")
				par = (arr, ID)
				cursor.execute(sql, par)
			elif(select == 3):
				dat = input("Enter new Flight_Date (YYYY/MM/DD): ")
				sql = ("UPDATE flights SET Flight_Date = %s WHERE Flight_No = %s")
				par = (dat, ID)
				cursor.execute(sql, par)
			elif(select == 4):
				dpt = input("Enter new Depart_Time (HH:MM): ")
				sql = ("UPDATE flights SET Depart_Time = %s WHERE Flight_No = %s")
				par = (dpt, ID)
				cursor.execute(sql, par)
			elif(select == 5):
				at = input("Enter new Arrival_Time (HH:MM): ")
				sql = ("UPDATE flights SET Arrival_Time = %s WHERE Flight_No = %s")
				par = (at, ID)
				cursor.execute(sql, par)
			elif(select == 6):
				price = int(input("Enter new Price (PKR): "))
				sql = ("UPDATE flights SET Price = %s WHERE Flight_No = %s")
				par = (price, ID)
				cursor.execute(sql, par)

	if choice == 3:
		ID = input("Enter Flight_No: ")
		sql = "SELECT Flight_No FROM flights WHERE Flight_No = %s"
		par = (ID, )
		cursor.execute(sql, par)
		result = cursor.fetchone()
		if result == None:
			print("Flight_No does not exist")
		else:
			sql = "DELETE FROM flights WHERE Flight_No = %s"
			cursor.execute(sql, par)
			sql = "DELETE FROM tickets WHERE Flight_No = %s"
			cursor.execute(sql, par)

	if choice == 4:
		port = input("Enter IATA: ")
		dat = input("Enter date (YYYY/MM/DD): ")
		sql = "SELECT * from flights WHERE (Depart_IATA = %s or Arrival_IATA = %s) AND Flight_Date = %s"
		par = (port, port, dat)
		cursor.execute(sql, par)
		result = cursor.fetchall()
		if result == None:
			print("No such flights")
		else:
			for x in result:
				print(x)

	if choice == 5:
		table = PrettyTable()
		table.field_names =  ["Passenger_ID" , "Name", "Date_of_Birth", "Contact_No"]
		# table.set_field_align("Passenger_ID", "l")
		# table.set_padding_width(1)
		cursor.execute("SELECT * FROM passenger")
		result = cursor.fetchall()

		for x in result:
			table.add_row(x)

		print(table)




def Recmode():
	print("Logged in as receptionist")
	print("1. Create a new passenger record") #done
	print("2. Update details of an existing passenger") #done
	print("3. Check flights in particular time period")
	print("4. Get ticket record for a passenger for a particular flight") #done
	print("5. View cheapest flight") #done
	print("6. View passenger flight history") #semidone
	print("7. Cancel a ticket") #done
	print("")

	choice = int(input("Enter your choice: "))
	while(choice < 1 or choice > 7):
		choice = int(input("Invalid option. Enter again: "))

	if choice == 1:
		ID = int(input("Enter passenger ID: "))
		sql = "SELECT Passenger_ID FROM Passenger WHERE Passenger_ID = %s"
		par = (ID, )
		cursor.execute(sql, par)
		result = cursor.fetchone()
		if result != None:
			for x in result:
				if x == ID:
					print("Passenger ID already exists")
		else:
			name = input("Enter passenger name: ")
			contact = int(input("Enter passenger contact number: "))
			dob = input("Enter passenger date of birth (YYYY/MM/DD): ")
			sql = "INSERT INTO Passenger (Passenger_ID ,Name, Date_of_Birth, Contact_No) VALUES (%s,%s,%s,%s)"
			par = (ID, name, dob, contact)
			cursor.execute(sql, par)
			print("Passenger added to  database")

	elif choice == 2:
		ID = int(input("Enter passenger ID: "))
		sql = "SELECT Passenger_ID FROM Passenger WHERE Passenger_ID = %s"
		par = (ID, )
		cursor.execute(sql, par)
		result = cursor.fetchone()
		if result == None:
			print("Passenger_ID does not exist")
		else:
			print("1. Contact_No")
			print("2. Date_of_Birth")
			print("3. Name")
			select = int(input("Select: "))
			if(select == 1):
				contact = int(input("Enter new contact number: "))
				sql = ("UPDATE Passenger SET Contact_No = %s WHERE Passenger_ID = %s")
				par = (contact, ID)
				cursor.execute(sql, par)
			elif(select == 2):
				dob = input("Enter new DOB YYYY/MM/DD: ")
				sql = ("UPDATE Passenger SET Date_of_Birth = %s WHERE Passenger_ID = %s")
				par = (dob, ID)
				cursor.execute(sql, par)
			elif(select == 3):
				name = input("Enter new name: ")
				sql = ("UPDATE Passenger SET Name = %s WHERE Passenger_ID = %s")
				par = (name, ID)
				cursor.execute(sql, par)

	elif choice == 7:
		ID = int(input("Enter ticket ID: "))
		sql = "SELECT Ticket_No FROM tickets WHERE Ticket_No = %s"
		par = (ID, )
		cursor.execute(sql, par)
		result = cursor.fetchone()
		if result == None:
			print("Ticket does not exist")
		else:
			sql = "DELETE FROM tickets WHERE Ticket_No = %s"
			cursor.execute(sql, par)

	elif choice == 6:
		ID = int(input("Enter Passenger_ID: "))
		sql = "SELECT Passenger_ID FROM Passenger WHERE Passenger_ID = %s"
		par = (ID, )
		cursor.execute(sql, par)
		result = cursor.fetchone()
		if result == None:
			print("Passenger does not exist")
		else:
			sql = "SELECT \
				  tickets.Passenger_ID AS Passenger, \
				  flights.Flight_No AS flights \
				  FROM tickets \
				  WHERE Passenger_ID = %s \
				  INNER JOIN flights ON tickets.Flight_No = flights.Flight_No"
			cursor.execute(sql, par)
			ret = cursor.fetchall()

			for x in ret:
				print(x)

	elif choice == 4:
		ID = int(input("Enter Passenger_ID: "))
		sql = "SELECT Passenger_ID FROM Passenger WHERE Passenger_ID = %s"
		par = (ID, )
		cursor.execute(sql, par)
		result = cursor.fetchone()
		if result == None:
			print("Passenger does not exist")
		else:
			flight = input("Enter Flight_No: ")
			sql = "SELECT Flight_No FROM flights WHERE Flight_No = %s"
			par = (flight, )
			cursor.execute(sql, par)
			result2 = cursor.fetchone()
			if result2 == None:
				print("Flight does not exist")
			else:
				sql = "SELECT * FROM tickets WHERE Passenger_ID = %s AND Flight_No  =  %s"
				par = (ID, flight)
				cursor.execute(sql, par)
				ret = cursor.fetchall()
				if ret == None:
					print("No matches")
				else:
					for x in ret:
						print(x)

	elif choice == 5:
		dep = input("Enter Departure IATA: ")
		arr = input("Enter Arrival IATA: ")
		sql = "SELECT MIN(Price) FROM flights WHERE Depart_IATA = %s AND Arrival_IATA = %s"
		par = (dep, arr)
		cursor.execute(sql, par)
		result2 = cursor.fetchone()
		if result2 == None:
			print("Flight does not exist")
		else:
			for x in result2:
				print(x)

	elif choice == 3:
		dep = input("Enter Departure IATA: ")
		arr = input("Enter Arrival IATA: ")
		t1 = input("Time period start date: ")
		t2 = input("Time period end date: ")
		if t2 < t1:
			print("Invalid time period")
		else:
			sql = "SELECT * FROM flights WHERE Depart_IATA = %s AND Arrival_IATA = %s AND Flight_Date >= %s AND Flight_Date <= %s"
			par = (dep, arr, t1, t2)
			cursor.execute(sql, par)
			result2 = cursor.fetchall()
			if result2 == None:
				print("Such flights does not exist for the specified period")
			else:
				for x in result2:
					print(x)




employeename = input("Enter your ID: ")
employeepass = input("Enter your password: ")

sql = "SELECT Employee_Pass FROM employee WHERE Employee_ID = %s AND Employee_Pass = %s"
par = (employeename, employeepass)
cursor.execute(sql, par)
result = cursor.fetchone()
if result == None:
	print("ERROR. INCORRECT ID OR PASSWORD")
else:
	sql = "SELECT Status FROM employee WHERE Employee_ID = %s"
	par = (employeename, )
	cursor.execute(sql, par)
	result2 = cursor.fetchone()
	for x in result2:
		if x == "Ad":
			Admode()
		elif x == "Re":
			Recmode()




