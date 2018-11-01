#!/usr/bin/python
import MySQLdb

# Open database connection
db = MySQLdb.connect("localhost","root","password","COLLEGE")

# prepare a cursor object using cursor() method
# abstraction meant for data set traversal
# one cursor per connection
cursor = db.cursor()

try:
   	# Execute the SQL command
	print "\nQuery: SELECT * FROM COURSE;\n"
	cursor.execute("""SELECT * FROM COURSE;""")
	# Commit your changes in the database
   	db.commit()

	###########################################################
	###########################################################

	# Fetch a single row using fetchone() method.
	data_1 = cursor.fetchone()
	print data_1

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
