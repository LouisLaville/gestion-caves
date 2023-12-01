-- MySQL dump 10.13  Distrib 8.2.0, for macos14.0 (arm64)
--
-- Host: localhost    Database: gestion
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Cave`
--

DROP TABLE IF EXISTS `Cave`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Cave` (
  `idCave` int NOT NULL,
  `nom` varchar(255) DEFAULT NULL,
  `adresse` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`idCave`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Cave`
--

LOCK TABLES `Cave` WRITE;
/*!40000 ALTER TABLE `Cave` DISABLE KEYS */;
/*!40000 ALTER TABLE `Cave` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CaveFournisseur`
--

DROP TABLE IF EXISTS `CaveFournisseur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `CaveFournisseur` (
  `idCave` int NOT NULL,
  `idFournisseur` int NOT NULL,
  PRIMARY KEY (`idCave`,`idFournisseur`),
  KEY `idFournisseur` (`idFournisseur`),
  CONSTRAINT `cavefournisseur_ibfk_1` FOREIGN KEY (`idCave`) REFERENCES `Cave` (`idCave`),
  CONSTRAINT `cavefournisseur_ibfk_2` FOREIGN KEY (`idFournisseur`) REFERENCES `Fournisseur` (`idFournisseur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CaveFournisseur`
--

LOCK TABLES `CaveFournisseur` WRITE;
/*!40000 ALTER TABLE `CaveFournisseur` DISABLE KEYS */;
/*!40000 ALTER TABLE `CaveFournisseur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Fournisseur`
--

DROP TABLE IF EXISTS `Fournisseur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Fournisseur` (
  `idFournisseur` int NOT NULL,
  `nom` varchar(255) DEFAULT NULL,
  `adresse` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`idFournisseur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Fournisseur`
--

LOCK TABLES `Fournisseur` WRITE;
/*!40000 ALTER TABLE `Fournisseur` DISABLE KEYS */;
/*!40000 ALTER TABLE `Fournisseur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Fournit`
--

DROP TABLE IF EXISTS `Fournit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Fournit` (
  `idFournisseur` int NOT NULL,
  `idVin` int NOT NULL,
  `prixBase` decimal(10,2) DEFAULT NULL,
  `reductions` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`idFournisseur`,`idVin`),
  KEY `idVin` (`idVin`),
  CONSTRAINT `fournit_ibfk_1` FOREIGN KEY (`idFournisseur`) REFERENCES `Fournisseur` (`idFournisseur`),
  CONSTRAINT `fournit_ibfk_2` FOREIGN KEY (`idVin`) REFERENCES `Vin` (`idVin`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Fournit`
--

LOCK TABLES `Fournit` WRITE;
/*!40000 ALTER TABLE `Fournit` DISABLE KEYS */;
/*!40000 ALTER TABLE `Fournit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Gere`
--

DROP TABLE IF EXISTS `Gere`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Gere` (
  `idVin` int NOT NULL,
  `dureeMinGarde` int DEFAULT NULL,
  `anneeConsommation` int DEFAULT NULL,
  PRIMARY KEY (`idVin`),
  CONSTRAINT `gere_ibfk_1` FOREIGN KEY (`idVin`) REFERENCES `Vin` (`idVin`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Gere`
--

LOCK TABLES `Gere` WRITE;
/*!40000 ALTER TABLE `Gere` DISABLE KEYS */;
/*!40000 ALTER TABLE `Gere` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Propose`
--

DROP TABLE IF EXISTS `Propose`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Propose` (
  `idCave` int NOT NULL,
  `idVin` int NOT NULL,
  `prixBase` decimal(10,2) DEFAULT NULL,
  `marge` decimal(5,2) DEFAULT NULL,
  PRIMARY KEY (`idCave`,`idVin`),
  KEY `idVin` (`idVin`),
  CONSTRAINT `propose_ibfk_1` FOREIGN KEY (`idCave`) REFERENCES `Cave` (`idCave`),
  CONSTRAINT `propose_ibfk_2` FOREIGN KEY (`idVin`) REFERENCES `Vin` (`idVin`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Propose`
--

LOCK TABLES `Propose` WRITE;
/*!40000 ALTER TABLE `Propose` DISABLE KEYS */;
/*!40000 ALTER TABLE `Propose` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Vin`
--

DROP TABLE IF EXISTS `Vin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Vin` (
  `idVin` int NOT NULL,
  `region` varchar(50) DEFAULT NULL,
  `cru` varchar(50) DEFAULT NULL,
  `nom` varchar(100) DEFAULT NULL,
  `millesime` int DEFAULT NULL,
  `stock` int DEFAULT NULL,
  `type` enum('vin de garde','vin à consommer') DEFAULT NULL,
  PRIMARY KEY (`idVin`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Vin`
--

LOCK TABLES `Vin` WRITE;
/*!40000 ALTER TABLE `Vin` DISABLE KEYS */;
/*!40000 ALTER TABLE `Vin` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-12-01 17:39:22
