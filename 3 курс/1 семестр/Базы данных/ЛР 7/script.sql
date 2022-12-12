CREATE TABLE ST (
    ID_S  INTEGER NOT NULL,
    FIO   VARCHAR(40)
);



/******************************************************************************/
/***                              Primary keys                              ***/
/******************************************************************************/

ALTER TABLE ST ADD CONSTRAINT PK_ST PRIMARY KEY (ID_S);


/******************************************************************************/
/***                                Triggers                                ***/
/******************************************************************************/



SET TERM ^ ;



/******************************************************************************/
/***                          Triggers for tables                           ***/
/******************************************************************************/



/* Trigger: ST_BI */
CREATE OR ALTER TRIGGER ST_BI FOR ST
ACTIVE BEFORE INSERT POSITION 0
as
begin
  select coalesce(max(id_s),0)+1
  from st
  into new.id_s;
end
^
SET TERM ; ^

INSERT INTO ST (ID_S, FIO)
        VALUES (1, 'Воробьев Юрий Викторович');
INSERT INTO ST (ID_S, FIO)
        VALUES (2, 'Гурьев Александр Сергеевич');
INSERT INTO ST (ID_S, FIO)
        VALUES (3, 'Еремичева Яна');
INSERT INTO ST (ID_S, FIO)
        VALUES (4, 'Иванов Роман Викторович');
INSERT INTO ST (ID_S, FIO)
        VALUES (5, 'Костин Сергей Александрович');
INSERT INTO ST (ID_S, FIO)
        VALUES (6, 'Крастынь Алексей Валерьевич');
INSERT INTO ST (ID_S, FIO)
        VALUES (7, 'Мальцев Станислав Игоревич');
INSERT INTO ST (ID_S, FIO)
        VALUES (8, 'Михайлов Сергей Александрович');
INSERT INTO ST (ID_S, FIO)
        VALUES (9, 'Найкин Тимур Игоревич');
INSERT INTO ST (ID_S, FIO)
        VALUES (11, 'Раевский Максим Александрович');
INSERT INTO ST (ID_S, FIO)
        VALUES (12, 'Ревтов Андрей Владимирович');
INSERT INTO ST (ID_S, FIO)
        VALUES (13, 'Санин Алексей Петрович');
INSERT INTO ST (ID_S, FIO)
        VALUES (14, 'Симонов Дмитрий Константинович');
INSERT INTO ST (ID_S, FIO)
        VALUES (15, 'Скуратовский Дмитрий Юрьевич');
INSERT INTO ST (ID_S, FIO)
        VALUES (16, 'Толмачева Анастасия Александровна');
INSERT INTO ST (ID_S, FIO)
        VALUES (17, 'Фролов Павел Николаевич');
INSERT INTO ST (ID_S, FIO)
        VALUES (18, 'Чудеснов Денис Евгеньевич');
INSERT INTO ST (ID_S, FIO)
        VALUES (19, 'Чуфрин Андрей Геннадьевич');
INSERT INTO ST (ID_S, FIO)
        VALUES (20, 'Шафигуллин Владимир Айдарович');


COMMIT WORK;

