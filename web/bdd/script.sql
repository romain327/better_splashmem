DROP DATABASE IF EXISTS better_splashmem;
CREATE DATABASE IF NOT EXISTS better_splashmem;
USE better_splashmem;
DROP TABLE IF EXISTS sp_user;
DROP TABLE IF EXISTS sp_score;
CREATE TABLE IF NOT EXISTS sp_user (
    user_name VARCHAR(50) PRIMARY KEY NOT NULL,
    passwd VARCHAR(50),
    ranking INT NOT NULL
)ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS sp_score (
    id_score INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
    score INT NOT NULL,
    user_name VARCHAR(50) NOT NULL,
    FOREIGN KEY (user_name) REFERENCES sp_user(user_name)
)ENGINE=InnoDB;