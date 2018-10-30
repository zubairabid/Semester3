# 1
# Insert a new Employee ('Richard','K','Martini', '653298653', '1964-03-09', '98 Oak,Forest,Katy,TX', 'M', 37000,'987654321', 4 )
INSERT   INTO  	EMPLOYEE
	VALUES ('Richard','K','Martini', '653298653', '1964-03-09', '98 Oak,Forest,Katy,TX', 'M', 37000,'987654321', 4 );

# 2
# Select Fname of the employees who don't work on any project
SELECT Ssn, Fname
FROM EMPLOYEE JOIN WORKS_ON
WHERE Essn = Ssn AND Pno = 20;

# 3
# Select (Essn and fname) of all employees Working on Project number 20
# Use Nested (Not Join)
SELECT Ssn, Fname
FROM EMPLOYEE
WHERE Ssn IN
      (SELECT Essn FROM WORKS_ON WHERE Pno = 20);

# 4
# Select (Essn and fname) of all employees Working on Project number 20
# Use Join (Not Nested)
SELECT Fname
FROM EMPLOYEE
WHERE NOT EXISTS
(SELECT * FROM WORKS_ON WHERE Essn = Ssn);

# 5
# Increment the salary of  all Employees who are working on Project: ProductX by 10%
UPDATE EMPLOYEE
SET Salary = Salary*1.1
WHERE Ssn IN
      (SELECT t1.Essn
       FROM WORKS_ON AS t1 JOIN PROJECT AS t2
       WHERE t1.Pno = t2.Pnumber AND t2.Pname = 'ProductX');

