HA$PBExportHeader$listdemo105.sra
$PBExportComments$Generated Application Object
forward
global type listdemo105 from application
end type
global transaction sqlca
global dynamicdescriptionarea sqlda
global dynamicstagingarea sqlsa
global error error
global message message
end forward

global type listdemo105 from application
string appname = "listdemo105"
end type
global listdemo105 listdemo105

on listdemo105.create
appname="listdemo105"
message=create message
sqlca=create transaction
sqlda=create dynamicdescriptionarea
sqlsa=create dynamicstagingarea
error=create error
end on

on listdemo105.destroy
destroy(sqlca)
destroy(sqlda)
destroy(sqlsa)
destroy(error)
destroy(message)
end on

event open;
open(w_test)

end event

