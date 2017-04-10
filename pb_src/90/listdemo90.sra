$PBExportHeader$listdemo90.sra
$PBExportComments$Generated Application Object
forward
global type listdemo90 from application
end type
global transaction sqlca
global dynamicdescriptionarea sqlda
global dynamicstagingarea sqlsa
global error error
global message message
end forward

global variables

end variables

global type listdemo90 from application
string appname = "listdemo90"
end type
global listdemo90 listdemo90

type prototypes
SUBROUTINE OutputDebugString (String lpszOutputString)  LIBRARY "kernel32.dll" ALIAS FOR "OutputDebugStringA";

end prototypes

type variables


end variables
on listdemo90.create
appname="listdemo90"
message=create message
sqlca=create transaction
sqlda=create dynamicdescriptionarea
sqlsa=create dynamicstagingarea
error=create error
end on

on listdemo90.destroy
destroy(sqlca)
destroy(sqlda)
destroy(sqlsa)
destroy(error)
destroy(message)
end on

event open;
open(w_test)

end event

