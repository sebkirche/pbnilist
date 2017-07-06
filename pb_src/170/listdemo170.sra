$PBExportHeader$listdemo170.sra
$PBExportComments$Generated Application Object
forward
global type listdemo170 from application
end type
global transaction sqlca
global dynamicdescriptionarea sqlda
global dynamicstagingarea sqlsa
global error error
global message message
end forward

global type listdemo170 from application
string appname = "listdemo170"
end type
global listdemo170 listdemo170

on listdemo170.create
appname="listdemo170"
message=create message
sqlca=create transaction
sqlda=create dynamicdescriptionarea
sqlsa=create dynamicstagingarea
error=create error
end on

on listdemo170.destroy
destroy(sqlca)
destroy(sqlda)
destroy(sqlsa)
destroy(error)
destroy(message)
end on

event open;
open(w_test)
end event

