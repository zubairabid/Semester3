#!/usr/bin/python
import MySQLdb

# Open database connection
db = MySQLdb.connect("localhost","root","password","COLLEGE")

# prepare a cursor object using cursor() method
# abstraction meant for data set traversal
cursor1 = db.cursor()
cursor2 = db.cursor()

try:
   	# Execute the SQL command
	print "\nQuery: SELECT * FROM COURSE;\n"
	cursor1.execute("""SELECT * FROM COURSE;""")
	cursor2.execute("""SELECT * FROM COURSE;""")
	# Commit your changes in the database
   	db.commit()

	###########################################################
	###########################################################

	# Fetch all rows using fetchone() method.
	row = cursor1.fetchone()
	print "Cursor 1:"
	while row is not None:
	    print row
	    row = cursor1.fetchone()
	print "\n"
    
	# Fetch all rows using fetchall() method.
	print "Cursor 2:"
	data_all = cursor2.fetchall()
	for tup in data_all :
		print tup

	###########################################################
	###########################################################

	rc1 = cursor1.rowcount
	print "\nRow count 1: ", rc1
	rc2 = cursor2.rowcount
	print "Row count 2: ", rc2

except:
   	# Rollback in case there is any error
   	db.rollback()

#close the cursors
cursor1.close()
cursor2.close()

# close the connection
db.close()
