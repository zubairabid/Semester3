#!/usr/bin/python
import MySQLdb

# Open database connection
db = MySQLdb.connect("localhost","root","password","COLLEGE")

# prepare a cursor object using cursor() method
# abstraction meant for data set traversal
cursor = db.cursor()

try:
   	# Execute the SQL command
	print "\nQuery: SELECT Fname,Lname FROM STUDENT WHERE YoJ < 2013\n"
	max_year = 2013	
	cursor.execute("""SELECT Fname,Lname FROM STUDENT WHERE YoJ < %s;""", (max_year,))
	# Commit your changes in the database
   	db.commit()

	###########################################################
	###########################################################

	# Fetch all rows using fetchall() method.
	data_all = cursor.fetchall()
	for tup in data_all :
		print tup

	###########################################################
	###########################################################

	rc = cursor.rowcount
	print "\nRow count: ", rc

except:
   	# Rollback in case there is any error
   	db.rollback()

#close the cursor
cursor.close()

# close the connection
db.close()
