SELECT     ����.CODE, ����.DESCR AS name, ����.���� as price,����.ISFOLDER , ����.ID, ����.PARENTID, �������.SP80 as barcode
FROM         dbo.SC84 ���� RIGHT  JOIN
                      dbo.SC75 ������� ON ����.ID = �������.PARENTEXT LEFT  JOIN
                      dbo.SC319 ���� ON ����.PARENTEXT = ����.ID AND ����.SP327 = '     3   ' LEFT  JOIN
                          (SELECT     ������.objid AS objid, ������.value AS ����
                            FROM          _1sconst AS ������
                            WHERE      ������.date IN
                                                        (SELECT     MAX(���������.date)
                                                         FROM          _1sconst AS ���������
                                                         WHERE      (���������.date <= '05/25/09') 
                                                         AND (���������.id = ' 324') 
                                                         AND (���������.objid = ������.objid)) 
                           AND ������.id = ' 324') 

���� ON ����.objid = ����.ID
WHERE     (����.CODE = '00000232') AND (����.ID = '     9   ')
