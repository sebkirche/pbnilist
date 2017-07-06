$PBExportHeader$anyiterator.sru
forward
global type anyiterator from nonvisualobject
end type
end forward

global type anyiterator from nonvisualobject autoinstantiate
end type

type variables
any ia_array[]
long il_next = 0
end variables

forward prototypes
public subroutine _add (any aa_item)
public function any getnext ()
public function boolean hasnext ()
public function long count ()
end prototypes

public subroutine _add (any aa_item);ia_array[ upperbound( ia_array[] ) + 1 ] = aa_item
il_next = lowerbound( ia_array[] )
end subroutine

public function any getnext ();long ll_next 
ll_next = il_next
il_next++
if il_next>upperbound( ia_array[] ) then il_next = 0
return ia_array[ ll_next ]
end function

public function boolean hasnext ();return il_next <> 0
end function

public function long count ();return upperbound( ia_array[] )
end function

event constructor;/*
Author:	GeNi
Date: 		30/01/09
--------------------
Class AnyIterator
*/

end event

on anyiterator.create
call super::create
TriggerEvent( this, "constructor" )
end on

on anyiterator.destroy
TriggerEvent( this, "destructor" )
call super::destroy
end on

