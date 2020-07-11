class cuckoo:

	def __init__(self, n):
		self.max = n
		self.count = 0
		self.table1 = [None]*n
		self.table2 = [None]*n
		self.cycle = 0

	def hash1(self, key):
		return int(key % self.max) + self.cycle

	def hash2(self, key):
		return (int(key/self.max) % self.max) + self.cycle

	def delete(self, key):
		node1 = self.table1[self.hash1(key)]
		node2 = self.table2[self.hash2(key)]

		if node1 != None and node1.getval() == key:
			self.table1[self.hash1(key)] = None
			self.count -= 1
			print("Element", key, "deleted succesfully")

		elif node2 != None and node2.getval() == key:
			self.table2[self.hash2(key)] = None
			self.count -= 1
			print("Element", key, "deleted succesfully")

		else:
			print("Element", key, "not found")

	def search(self, key):
		node1 = self.table1[self.hash1(key)]
		node2 = self.table2[self.hash2(key)]

		if node1 != None and node1.getval() == key:
			code =  self.hash1(key)
			print(key, "found in table1[",code,"]")

		elif node2 != None and node2.getval() == key:
			code =  self.hash2(key)
			print(key, "found in table1[", code ,"]")

		else:
			print(key, "not found")

	def insert(self, key, ite, tnum):
		if ite == 0 and self.count >= self.max:
			print("Tables are full")
			return

		if(ite >= self.max):
			for x in range(self.max):
				code1 = self.hash1(key) + x
				code2 = self.hash2(key) + x
				node1 = self.table1[code1]
				node2 = self.table2[code2]

				if node1 ==  None:
					self.table1[code1] = node(key, code1)
					self.count += 1
					print(key, "added succesfully")
					return
				if node1 ==  None:
					self.table1[code2] = node(key, code2)
					self.count += 1
					print(key, "added succesfully")
					return

		if tnum == 0:
			node1 = self.table1[self.hash1(key)]
			node2 = self.table2[self.hash2(key)]
			if node1 == None:
				self.table1[self.hash1(key)] = node(key, self.hash1(key))
				self.count += 1
				print(key, "added succesfully")
			elif node2 == None:
				self.table2[self.hash2(key)] = node(key, self.hash2(key))
				self.count += 1
				print(key, "added succesfully")
			else:
				self.table1[self.hash1(key)].setval(key)
				self.insert(node1.getval(), ite + 1, 1)
				self.count += 1
				print(key, "added succesfully")

		elif tnum == 1:
			node2 = self.table2[self.hash2(key)]
			if node2 == None:
				self.table2[self.hash2(key)] =  node(key, self.hash2(key))
			else:
				val =  node2.getval()
				self.insert(val, ite + 1, 2)

		elif tnum == 2:
			node1 = self.table1[self.hash1(key)]
			if node1 == None:
				self.table1[self.hash1(key)] =  node(key, self.hash1(key))
			else:
				val =  node1.getval()
				self.insert(val, ite + 1, 1)

	def printtable(self):
		# count1 = 0
		# count2 = 0
		print("TABLE 1")
		for x in self.table1:
			if x != None:
				print(x.getval(), "at index", x.getcode())
				# count1 += 1
			else:
				print("empty")

		# if count1 == 0:
		# 	print("empty")

		print("\nTABLE 2")
		for y in self.table2:
			if y != None:
				print(y.getval(), "at index", y.getcode())
				# count2 += 1
			else:
				print("empty")
		# if count2 == 0:
		# 	print("empty")




class node:
	def __init__(self, value, code):
		self.val =  value
		self.code = code

	def getval(self):
		return self.val

	def setval(self, value):
		self.val = value

	def getcode(self):
		return self.code


magic = cuckoo(11)
print("Tables initialized")
print("")

print("1. Insert value")
print("2. Search value")
print("3. Delete value")
print("4. Print tables")
print("5. Quit")

while(True):
	print("")
	choice = int(input("Select: "))

	while(choice < 1 or choice > 5):
		choice = int(input("Invalid operation. Enter again: "))

	if choice == 1:
		value = int(input("Enter value to be inserted: "))
		magic.insert(value, 0, 0)
	elif choice == 2:
		value = int(input("Enter value to be searched: "))
		magic.search(value)
	elif choice == 3:
		value = int(input("Enter value to be searched: "))
		magic.delete(value)
	elif choice == 4:
		magic.printtable()
	elif choice == 5:
		print("Goodbye :)")
		break