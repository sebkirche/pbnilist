$PBExportHeader$listdemo125.sra
$PBExportComments$Generated Application Object
forward
global type listdemo125 from application
end type
global transaction sqlca
global dynamicdescriptionarea sqlda
global dynamicstagingarea sqlsa
global error error
global message message
end forward

global type listdemo125 from application
string appname = "listdemo125"
end type
global listdemo125 listdemo125

on listdemo125.create
appname="listdemo125"
message=create message
sqlca=create transaction
sqlda=create dynamicdescriptionarea
sqlsa=create dynamicstagingarea
error=create error
end on

on listdemo125.destroy
destroy(sqlca)
destroy(sqlda)
destroy(sqlsa)
destroy(error)
destroy(message)
end on

event open;
open(w_test)
end event

