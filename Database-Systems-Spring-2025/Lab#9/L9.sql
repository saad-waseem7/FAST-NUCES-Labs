-- Create the database if it does not exist
IF NOT EXISTS (SELECT name FROM sys.databases WHERE name = 'CursedTitansDB')
BEGIN
    CREATE DATABASE CursedTitansDB;
END
GO

-- Use the database
USE CursedTitansDB;
GO

-- Drop existing tables if they exist (for rerun safety)
DROP TABLE IF EXISTS Battle_Participants, Character_Techniques, Battle_Techniques, Mission_Assignments, Character_Artifacts;
DROP TABLE IF EXISTS Characters, Battles, Locations, Techniques, Artifacts, Missions, Prophecies;

-- Table for Characters (Titan-shifters, Jujutsu sorcerers, or both)
CREATE TABLE Characters (
    character_id INT IDENTITY(1,1) PRIMARY KEY,
    name NVARCHAR(100) NOT NULL,
    faction NVARCHAR(50) CHECK (faction IN ('Titan-shifter', 'Jujutsu Sorcerer', 'Hybrid')),
    titan_form NVARCHAR(100) NULL, -- Null if not a Titan-shifter
    cursed_technique NVARCHAR(100) NULL, -- Null if not a Sorcerer
    rank NVARCHAR(50), -- e.g., "Elite", "Captain"
    backstory TEXT,
    created_at DATETIME DEFAULT GETDATE()
);

-- Table for Locations (Walls, cursed shrines, battlefields)
CREATE TABLE Locations (
    location_id INT IDENTITY(1,1) PRIMARY KEY,
    name NVARCHAR(100) NOT NULL UNIQUE,
    type NVARCHAR(50) CHECK (type IN ('Wall', 'Cursed Shrine', 'Battlefield')),
    cursed_contamination_level INT CHECK (cursed_contamination_level BETWEEN 0 AND 100),
    historical_significance TEXT,
    created_at DATETIME DEFAULT GETDATE()
);

-- Table for Battles (events where characters fought)
CREATE TABLE Battles (
    battle_id INT IDENTITY(1,1) PRIMARY KEY,
    location_id INT NOT NULL,
    battle_date DATETIME NOT NULL,
    outcome NVARCHAR(100), -- e.g., "Victory", "Defeat", "Stalemate"
    summary TEXT,
    FOREIGN KEY (location_id) REFERENCES Locations(location_id) ON DELETE CASCADE
);

-- Many-to-Many: Characters participating in Battles
CREATE TABLE Battle_Participants (
    battle_id INT,
    character_id INT,
    PRIMARY KEY (battle_id, character_id),
    FOREIGN KEY (battle_id) REFERENCES Battles(battle_id) ON DELETE CASCADE,
    FOREIGN KEY (character_id) REFERENCES Characters(character_id) ON DELETE CASCADE
);

-- Table for Techniques (Titan abilities & Jujutsu techniques)
CREATE TABLE Techniques (
    technique_id INT IDENTITY(1,1) PRIMARY KEY,
    name NVARCHAR(100) NOT NULL UNIQUE,
    type NVARCHAR(50) CHECK (type IN ('Titan Ability', 'Jujutsu Technique')),
    power_level INT CHECK (power_level BETWEEN 1 AND 100),
    description TEXT,
    created_at DATETIME DEFAULT GETDATE()
);

-- Many-to-Many: Characters mastering Techniques
CREATE TABLE Character_Techniques (
    character_id INT,
    technique_id INT,
    mastery_level INT CHECK (mastery_level BETWEEN 1 AND 100),
    last_updated DATETIME DEFAULT GETDATE(),
    PRIMARY KEY (character_id, technique_id),
    FOREIGN KEY (character_id) REFERENCES Characters(character_id) ON DELETE CASCADE,
    FOREIGN KEY (technique_id) REFERENCES Techniques(technique_id) ON DELETE CASCADE
);

-- Many-to-Many: Techniques used in Battles
CREATE TABLE Battle_Techniques (
    battle_id INT,
    technique_id INT,
    PRIMARY KEY (battle_id, technique_id),
    FOREIGN KEY (battle_id) REFERENCES Battles(battle_id) ON DELETE CASCADE,
    FOREIGN KEY (technique_id) REFERENCES Techniques(technique_id) ON DELETE CASCADE
);

-- Table for Ancient Artifacts
CREATE TABLE Artifacts (
    artifact_id INT IDENTITY(1,1) PRIMARY KEY,
    name NVARCHAR(100) NOT NULL UNIQUE,
    effect TEXT,
    rarity NVARCHAR(50) CHECK (rarity IN ('Common', 'Rare', 'Legendary')),
    discovered_at DATETIME DEFAULT GETDATE()
);

-- Many-to-Many: Characters possessing Artifacts
CREATE TABLE Character_Artifacts (
    character_id INT,
    artifact_id INT,
    PRIMARY KEY (character_id, artifact_id),
    FOREIGN KEY (character_id) REFERENCES Characters(character_id) ON DELETE CASCADE,
    FOREIGN KEY (artifact_id) REFERENCES Artifacts(artifact_id) ON DELETE CASCADE
);

-- Table for Prophecies (foreshadowing events)
CREATE TABLE Prophecies (
    prophecy_id INT IDENTITY(1,1) PRIMARY KEY,
    title NVARCHAR(200) NOT NULL,
    content TEXT,
    predicted_outcome TEXT,
    created_at DATETIME DEFAULT GETDATE()
);

-- Table for Missions (team-based operations)
CREATE TABLE Missions (
    mission_id INT IDENTITY(1,1) PRIMARY KEY,
    objective TEXT NOT NULL,
    status NVARCHAR(50) CHECK (status IN ('Pending', 'Ongoing', 'Completed', 'Failed')),
    success_criteria TEXT,
    discovered_clues TEXT,
    mission_date DATETIME NOT NULL,
    created_at DATETIME DEFAULT GETDATE()
);

-- Many-to-Many: Characters assigned to Missions
CREATE TABLE Mission_Assignments (
    mission_id INT,
    character_id INT,
    PRIMARY KEY (mission_id, character_id),
    FOREIGN KEY (mission_id) REFERENCES Missions(mission_id) ON DELETE CASCADE,
    FOREIGN KEY (character_id) REFERENCES Characters(character_id) ON DELETE CASCADE
);

-- Use the database
USE CursedTitansDB;
GO

-- Insert data into Characters
INSERT INTO Characters (name, faction, titan_form, cursed_technique, rank, backstory)
VALUES 
('Eren Yeager', 'Hybrid', 'Attack Titan', 'Binding Vows', 'Elite', 'Once a soldier, now a revolutionary.'),
('Gojo Satoru', 'Jujutsu Sorcerer', NULL, 'Limitless', 'Captain', 'Strongest sorcerer of his time.'),
('Levi Ackerman', 'Titan-shifter', 'Beast Titan', NULL, 'Elite', 'Legendary fighter with lightning-fast strikes.'),
('Yuji Itadori', 'Hybrid', 'War Hammer Titan', 'Divergent Fist', 'Elite', 'A host of Sukuna with Titan abilities.'),
('Mikasa Ackerman', 'Jujutsu Sorcerer', NULL, 'Heavenly Restriction', 'Elite', 'A warrior with immense physical prowess.');

-- Insert data into Locations
INSERT INTO Locations (name, type, cursed_contamination_level, historical_significance)
VALUES 
('Wall Maria', 'Wall', 30, 'The first major Titan breach occurred here.'),
('Cursed Shrine of Ryomen Sukuna', 'Cursed Shrine', 95, 'The resting place of the King of Curses.'),
('Shiganshina District', 'Battlefield', 60, 'Site of multiple Titan invasions.'),
('Hidden Village of Sorcery', 'Cursed Shrine', 80, 'A lost stronghold of ancient jujutsu masters.'),
('Titan Forest', 'Battlefield', 50, 'A dense area where Titan battles frequently take place.');

-- Insert data into Battles
INSERT INTO Battles (location_id, battle_date, outcome, summary)
VALUES 
(1, '2025-02-14', 'Victory', 'The Survey Corps managed to push back the Titans.'),
(2, '2025-03-01', 'Defeat', 'Sukuna’s cursed energy overwhelmed the forces.'),
(3, '2025-03-10', 'Stalemate', 'Both sides suffered heavy losses.'),
(4, '2025-04-05', 'Victory', 'A secret jujutsu technique banished multiple Titans.'),
(5, '2025-04-20', 'Defeat', 'A new unknown curse emerged, forcing retreat.');

-- Insert data into Battle_Participants
INSERT INTO Battle_Participants (battle_id, character_id)
VALUES 
(1, 1), (1, 3), (2, 2), (2, 4), (3, 5),
(3, 1), (4, 2), (4, 3), (5, 4), (5, 5);

-- Insert data into Techniques
INSERT INTO Techniques (name, type, power_level, description)
VALUES 
('Hardening', 'Titan Ability', 85, 'Allows a Titan to reinforce its body with hardened skin.'),
('Infinite Void', 'Jujutsu Technique', 95, 'Traps enemies in an infinite state of perception.'),
('War Hammer Strike', 'Titan Ability', 90, 'Forms weapons from Titan flesh.'),
('Black Flash', 'Jujutsu Technique', 88, 'Enhances physical attacks with cursed energy.'),
('Beast Roar', 'Titan Ability', 80, 'A devastating roar that paralyzes enemies.');

-- Insert data into Character_Techniques
INSERT INTO Character_Techniques (character_id, technique_id, mastery_level)
VALUES 
(1, 1, 90), (2, 2, 100), (3, 5, 85), (4, 3, 92), (5, 4, 88);

-- Insert data into Battle_Techniques
INSERT INTO Battle_Techniques (battle_id, technique_id)
VALUES 
(1, 1), (2, 2), (3, 3), (4, 4), (5, 5);

-- Insert data into Artifacts
INSERT INTO Artifacts (name, effect, rarity, discovered_at)
VALUES 
('Cursed Dagger', 'Can pierce through Titan flesh with ease.', 'Rare', '2025-01-10'),
('War Hammer Core', 'Boosts War Hammer Titan abilities.', 'Legendary', '2025-02-22'),
('Seal of Binding', 'Restricts a Titan’s transformation.', 'Legendary', '2025-03-05'),
('Infinity Orb', 'Enhances jujutsu techniques.', 'Rare', '2025-03-15'),
('Beast Pendant', 'Strengthens Beast Titan’s control.', 'Common', '2025-04-01');

-- Insert data into Character_Artifacts
INSERT INTO Character_Artifacts (character_id, artifact_id)
VALUES 
(1, 1), (2, 4), (3, 5), (4, 2), (5, 3);

-- Insert data into Prophecies
INSERT INTO Prophecies (title, content, predicted_outcome)
VALUES 
('The Fall of the Walls', 'A great Titan infused with cursed energy will bring destruction.', 'A cataclysmic war.'),
('The Sorcerer’s Sacrifice', 'A powerful sorcerer must be sacrificed to break the curse.', 'A new era of balance.'),
('The Forbidden Transformation', 'A Titan-shifter who masters jujutsu will become unstoppable.', 'A godlike warrior.'),
('The Lost Ritual', 'A secret technique exists to permanently sever the Titan curse.', 'The end of the Titan age.'),
('The Eternal War', 'As long as hatred exists, the Titans and curses will never vanish.', 'A never-ending cycle.');

-- Insert data into Missions
INSERT INTO Missions (objective, status, success_criteria, discovered_clues, mission_date)
VALUES 
('Recover the War Hammer Core.', 'Completed', 'Retrieve the artifact.', 'It was hidden in a cursed shrine.', '2025-02-22'),
('Investigate the Titan-Curse Fusion.', 'Ongoing', 'Determine the origin of the hybrid forms.', 'A sorcerer-Titan connection found.', '2025-03-10'),
('Defend Wall Maria from invasion.', 'Completed', 'Prevent breach.', 'Titans with cursed energy are stronger.', '2025-02-14'),
('Find the Lost Ritual.', 'Pending', 'Locate ancient texts.', 'The ritual might be hidden in a sorcerer’s vault.', '2025-04-01'),
('Assassinate a rogue Titan-shifter.', 'Ongoing', 'Eliminate the target.', 'He has mastered both Titan and jujutsu abilities.', '2025-03-20');

-- Insert data into Mission_Assignments
INSERT INTO Mission_Assignments (mission_id, character_id)
VALUES 
(1, 4), (1, 5), (2, 2), (2, 1), (3, 3),
(3, 1), (4, 5), (4, 2), (5, 3), (5, 4);

-- Sample Queries:

-- 1. Retrieve top 3 characters who have combined Titan transformation with high-level jujutsu techniques in battle
SELECT TOP 3 c.name,
    COUNT(bt.battle_id) AS battle_count
FROM Characters c
    JOIN Character_Techniques ct ON c.character_id = ct.character_id
    JOIN Techniques t ON ct.technique_id = t.technique_id
    JOIN Battle_Participants bp ON c.character_id = bp.character_id
    JOIN Battle_Techniques bt ON bp.battle_id = bt.battle_id
    AND bt.technique_id = t.technique_id
WHERE c.faction = 'Hybrid'
    AND t.power_level > 80
GROUP BY c.name
ORDER BY battle_count DESC;

-- 2. Retrieve all missions that resulted in significant artifact recoveries
SELECT m.mission_id,
    m.objective,
    a.name AS artifact_name
FROM Missions m
    JOIN Mission_Assignments ma ON m.mission_id = ma.mission_id
    JOIN Character_Artifacts ca ON ma.character_id = ca.character_id
    JOIN Artifacts a ON ca.artifact_id = a.artifact_id
WHERE a.rarity = 'Legendary';

-- 3. Find all battles fought at cursed locations with contamination level above 70
SELECT b.battle_id,
    b.battle_date,
    l.name AS location_name,
    l.cursed_contamination_level
FROM Battles b
    JOIN Locations l ON b.location_id = l.location_id
WHERE l.cursed_contamination_level > 70;

-- 4. Identify the number of battles each character has participated in
SELECT c.name,
    COUNT(bp.battle_id) AS battles_fought
FROM Characters c
    LEFT JOIN Battle_Participants bp ON c.character_id = bp.character_id
GROUP BY c.name
ORDER BY battles_fought DESC;

-- 5. Get all characters who have mastered a jujutsu technique with power level above 90
SELECT c.name,
    t.name AS technique_name,
    ct.mastery_level
FROM Characters c
    JOIN Character_Techniques ct ON c.character_id = ct.character_id
    JOIN Techniques t ON ct.technique_id = t.technique_id
WHERE t.type = 'Jujutsu Technique'
    AND t.power_level > 90
ORDER BY ct.mastery_level DESC;

-- Triggers

-- T1
-- Create the Characters_Log table
CREATE TABLE Characters_Log (
    log_id INT IDENTITY(1,1) PRIMARY KEY,
    character_id INT,
    name NVARCHAR(100),
    faction NVARCHAR(50),
    log_time DATETIME DEFAULT GETDATE()
);

-- Trigger to log new character insertions
CREATE TRIGGER trg_CharacterInsertLog
ON Characters
AFTER INSERT
AS
BEGIN
    INSERT INTO Characters_Log (character_id, name, faction)
    SELECT character_id, name, faction
    FROM inserted
    WHERE faction IN ('Titan-shifter', 'Jujutsu Sorcerer', 'Hybrid');
END;

-- T2
-- Create Rank_Log table
CREATE TABLE Rank_Log (
    log_id INT IDENTITY(1,1) PRIMARY KEY,
    character_id INT,
    old_rank NVARCHAR(50),
    new_rank NVARCHAR(50),
    change_time DATETIME DEFAULT GETDATE()
);

-- Trigger to capture rank changes
CREATE TRIGGER trg_RankChangeLog
ON Characters
AFTER UPDATE
AS
BEGIN
    IF UPDATE(rank)
    BEGIN
        INSERT INTO Rank_Log (character_id, old_rank, new_rank)
        SELECT 
            d.character_id,
            d.rank,
            i.rank
        FROM deleted d
        INNER JOIN inserted i ON d.character_id = i.character_id
        WHERE d.rank <> i.rank;
    END
END;

-- T3
CREATE TRIGGER trg_PreventGojoDeletion
ON Characters
INSTEAD OF DELETE
AS
BEGIN
    IF EXISTS (SELECT 1 FROM deleted WHERE name = 'Gojo Satoru')
    BEGIN
        RAISERROR ('Cannot delete Gojo Satoru! He is critical to the universe.', 16, 1);
        ROLLBACK TRANSACTION;
    END
    ELSE
    BEGIN
        DELETE FROM Characters
        WHERE character_id IN (SELECT character_id FROM deleted);
    END
END;

-- T4
CREATE TRIGGER trg_PreventWeakSorcerer
ON Character_Techniques
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM inserted i
        JOIN Techniques t ON i.technique_id = t.technique_id
        JOIN Characters c ON i.character_id = c.character_id
        WHERE c.faction IN ('Jujutsu Sorcerer', 'Hybrid') AND t.type = 'Jujutsu Technique' AND t.power_level < 30
    )
    BEGIN
        RAISERROR ('Cannot assign a low-power Jujutsu Technique to Sorcerers (below 30)!', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;

-- T5
CREATE TRIGGER trg_PreventMasteryReduction
ON Character_Techniques
AFTER UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM inserted i
        JOIN deleted d ON i.character_id = d.character_id AND i.technique_id = d.technique_id
        WHERE i.mastery_level < d.mastery_level
    )
    BEGIN
        RAISERROR ('Cannot reduce mastery level once achieved!', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;

-- T6
CREATE TRIGGER trg_PreventCharacterTableDrop
ON DATABASE
FOR DROP_TABLE
AS
BEGIN
    IF EXISTS (
        SELECT * 
        FROM EVENTDATA()
        WHERE EVENTDATA().value('(/EVENT_INSTANCE/ObjectName)[1]', 'NVARCHAR(100)') = 'Characters'
    )
    BEGIN
        RAISERROR('Dropping the Characters table is forbidden!', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;

-- T7
-- Create a Table_Changes_Log table
CREATE TABLE Table_Changes_Log (
    change_id INT IDENTITY(1,1) PRIMARY KEY,
    event_type NVARCHAR(50),
    object_name NVARCHAR(100),
    change_time DATETIME DEFAULT GETDATE()
);

-- DDL Trigger for tracking schema changes
CREATE TRIGGER trg_TrackDDLChanges
ON DATABASE
FOR CREATE_TABLE, ALTER_TABLE, DROP_TABLE
AS
BEGIN
    DECLARE @event XML = EVENTDATA();
    INSERT INTO Table_Changes_Log (event_type, object_name)
    VALUES (
        @event.value('(/EVENT_INSTANCE/EventType)[1]', 'NVARCHAR(50)'),
        @event.value('(/EVENT_INSTANCE/ObjectName)[1]', 'NVARCHAR(100)')
    );
END;

-- T8
-- (Just for code sample, DO NOT execute this on production without careful testing)
CREATE TRIGGER trg_LimitLoginTimes
ON ALL SERVER
FOR LOGON
AS
BEGIN
    IF (DATEPART(HOUR, GETDATE()) NOT BETWEEN 9 AND 18)
    BEGIN
        ROLLBACK;
    END
END;

-- T9
-- Create table to store strongest Hybrid per battle
CREATE TABLE Battle_Strongest_Hybrid (
    battle_id INT PRIMARY KEY,
    character_name NVARCHAR(100),
    mastery_level INT,
    captured_at DATETIME DEFAULT GETDATE()
);

-- Trigger to insert strongest Hybrid after a battle
CREATE TRIGGER trg_RecordStrongestHybrid
ON Battle_Participants
AFTER INSERT
AS
BEGIN
    DECLARE @battle_id INT;
    SELECT TOP 1 @battle_id = battle_id FROM inserted;

    INSERT INTO Battle_Strongest_Hybrid (battle_id, character_name, mastery_level)
    SELECT TOP 1 
        @battle_id,
        c.name,
        ct.mastery_level
    FROM inserted i
    JOIN Characters c ON i.character_id = c.character_id
    JOIN Character_Techniques ct ON c.character_id = ct.character_id
    WHERE c.faction = 'Hybrid'
    ORDER BY ct.mastery_level DESC;
END;
