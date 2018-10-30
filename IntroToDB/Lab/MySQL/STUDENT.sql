-- MySQL dump 10.13  Distrib 5.7.23, for Linux (x86_64)
--
-- Host: localhost    Database: STUDENT
-- ------------------------------------------------------
-- Server version	5.7.23-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `COURSE`
--
DROP DATABASE IF EXISTS `STUDENT`;
CREATE SCHEMA `STUDENT`;
USE `STUDENT`;
DROP TABLE IF EXISTS `COURSE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `COURSE` (
  `Course_name` varchar(40) DEFAULT NULL,
  `Course_number` varchar(20) NOT NULL,
  `Credit_hours` int(11) DEFAULT NULL,
  `Department` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`Course_number`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `COURSE`
--

LOCK TABLES `COURSE` WRITE;
/*!40000 ALTER TABLE `COURSE` DISABLE KEYS */;
INSERT INTO `COURSE` VALUES ('Intro to Computer Science','CS1310',4,'CS'),('Data Structures','CS3320',4,'CS'),('Database','CS3380',3,'CS'),('Discrete Mathematics','MATH2410',3,'MATH');
/*!40000 ALTER TABLE `COURSE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `GRADE_REPORT`
--

DROP TABLE IF EXISTS `GRADE_REPORT`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `GRADE_REPORT` (
  `Student_number` int(11) NOT NULL,
  `Section_identifier` int(11) NOT NULL,
  `Grade` char(1) DEFAULT NULL,
  PRIMARY KEY (`Student_number`,`Section_identifier`),
  KEY `Section_identifier` (`Section_identifier`),
  CONSTRAINT `GRADE_REPORT_ibfk_1` FOREIGN KEY (`Student_number`) REFERENCES `STUDENT` (`Student_number`),
  CONSTRAINT `GRADE_REPORT_ibfk_2` FOREIGN KEY (`Section_identifier`) REFERENCES `SECTION` (`Section_identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `GRADE_REPORT`
--

LOCK TABLES `GRADE_REPORT` WRITE;
/*!40000 ALTER TABLE `GRADE_REPORT` DISABLE KEYS */;
INSERT INTO `GRADE_REPORT` VALUES (8,85,'A'),(8,92,'A'),(8,102,'B'),(8,135,'A'),(17,112,'B'),(17,119,'C');
/*!40000 ALTER TABLE `GRADE_REPORT` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PREREQUISITE`
--

DROP TABLE IF EXISTS `PREREQUISITE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PREREQUISITE` (
  `Course_number` varchar(20) NOT NULL,
  `Prerequisite_number` varchar(20) NOT NULL,
  PRIMARY KEY (`Course_number`,`Prerequisite_number`),
  KEY `Prerequisite_number` (`Prerequisite_number`),
  CONSTRAINT `PREREQUISITE_ibfk_1` FOREIGN KEY (`Course_number`) REFERENCES `COURSE` (`Course_number`),
  CONSTRAINT `PREREQUISITE_ibfk_2` FOREIGN KEY (`Prerequisite_number`) REFERENCES `COURSE` (`Course_number`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PREREQUISITE`
--

LOCK TABLES `PREREQUISITE` WRITE;
/*!40000 ALTER TABLE `PREREQUISITE` DISABLE KEYS */;
INSERT INTO `PREREQUISITE` VALUES ('CS3320','CS1310'),('CS3380','CS3320'),('CS3380','MATH2410');
/*!40000 ALTER TABLE `PREREQUISITE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SECTION`
--

DROP TABLE IF EXISTS `SECTION`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SECTION` (
  `Section_identifier` int(11) NOT NULL,
  `Course_number` varchar(20) DEFAULT NULL,
  `Semester` varchar(15) DEFAULT NULL,
  `Year` int(11) DEFAULT NULL,
  `Instructor` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`Section_identifier`),
  KEY `Course_number` (`Course_number`),
  CONSTRAINT `SECTION_ibfk_1` FOREIGN KEY (`Course_number`) REFERENCES `COURSE` (`Course_number`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SECTION`
--

LOCK TABLES `SECTION` WRITE;
/*!40000 ALTER TABLE `SECTION` DISABLE KEYS */;
INSERT INTO `SECTION` VALUES (85,'MATH2410','Fall',7,'King'),(92,'CS1310','Fall',7,'Anderson'),(102,'CS3320','Spring',8,'Knuth'),(112,'MATH2410','Fall',8,'Chang'),(119,'CS1310','Fall',8,'Anderson'),(135,'CS3380','Fall',8,'Stone');
/*!40000 ALTER TABLE `SECTION` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `STUDENT`
--

DROP TABLE IF EXISTS `STUDENT`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `STUDENT` (
  `Name` varchar(20) NOT NULL,
  `Student_number` int(11) NOT NULL,
  `Class` int(11) DEFAULT NULL,
  `Major` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`Student_number`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `STUDENT`
--

LOCK TABLES `STUDENT` WRITE;
/*!40000 ALTER TABLE `STUDENT` DISABLE KEYS */;
INSERT INTO `STUDENT` VALUES ('Brown',8,2,'CS'),('Smith',17,1,'CS');
/*!40000 ALTER TABLE `STUDENT` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-08-28 11:54:01
