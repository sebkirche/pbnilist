HA$PBExportHeader$nv_benchmark.sru
forward
global type nv_benchmark from nonvisualobject
end type
end forward

global type nv_benchmark from nonvisualobject autoinstantiate
end type

type variables
private:

	string is_operation = "Operation"
	long il_start
	boolean ib_start = false
	dec idec_last_delay
end variables

forward prototypes
public subroutine set (string as_operation)
public subroutine start ()
public subroutine start (string as_operation)
public subroutine mark (string as_operation)
public function decimal stop ()
public function decimal stop (string as_operation)
public function decimal mark ()
end prototypes

public subroutine set (string as_operation);this.is_operation = as_operation
end subroutine

public subroutine start ();il_start = cpu()
ib_start = true
end subroutine

public subroutine start (string as_operation);set( as_operation )
start()
end subroutine

public subroutine mark (string as_operation);set(as_operation)
mark()
end subroutine

public function decimal stop ();if ib_start then
	long ll_end
	ll_end = cpu()
	ib_start = false
	idec_last_delay = dec( ll_end - il_start ) / 1000.0
	debug_message( classname(), is_operation + " take " + string( idec_last_delay, "0.0000" ) + " second(s)" )
end if

return idec_last_delay
end function

public function decimal stop (string as_operation);set(as_operation)
return stop()
end function

public function decimal mark ();dec ldec_val
ldec_val = stop()
start()

return ldec_val
end function

event constructor;start()
end event

event destructor;stop()
end event

on nv_benchmark.create
call super::create
TriggerEvent( this, "constructor" )
end on

on nv_benchmark.destroy
TriggerEvent( this, "destructor" )
call super::destroy
end on

