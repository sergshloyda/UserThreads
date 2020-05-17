SELECT     СпрН.CODE, СпрН.DESCR AS name, Цены.Цена as price,СпрН.ISFOLDER , СпрН.ID, СпрН.PARENTID, Единицы.SP80 as barcode
FROM         dbo.SC84 СпрН RIGHT  JOIN
                      dbo.SC75 Единицы ON СпрН.ID = Единицы.PARENTEXT LEFT  JOIN
                      dbo.SC319 СпрЦ ON СпрЦ.PARENTEXT = СпрН.ID AND СпрЦ.SP327 = '     3   ' LEFT  JOIN
                          (SELECT     Период.objid AS objid, Период.value AS Цена
                            FROM          _1sconst AS Период
                            WHERE      Период.date IN
                                                        (SELECT     MAX(Константа.date)
                                                         FROM          _1sconst AS Константа
                                                         WHERE      (Константа.date <= '05/25/09') 
                                                         AND (Константа.id = ' 324') 
                                                         AND (Константа.objid = Период.objid)) 
                           AND Период.id = ' 324') 

Цены ON Цены.objid = СпрЦ.ID
WHERE     (СпрН.CODE = '00000232') AND (СпрН.ID = '     9   ')
