note
	description: "Summary description for {BARBERSHOP}."
	date: "$Date$"
	revision: "$Revision$"

class
	BARBERSHOP

create
	make

feature {NONE} -- Initialization

	make (a_size :INTEGER)
		-- Initialize with `a_size' as size
		require
			initial_size: a_size > 0
		do
			size := a_size
			waiting := 0
			in_shop := 0
			open := False
			current_ticket := -1
		ensure
			waiting = 0
			in_shop = 0
			open = False
			current_ticket = -1
			size = a_size
		end

feature {CUSTOMER}
	in_shop: INTEGER -- number of customers in the shop
	open : BOOLEAN -- assert the shop to be open or closed

	waiting : INTEGER -- number of customers waiting in the room
	size : INTEGER  -- size of the waiting room
	current_ticket: INTEGER -- current ticket to assign for the sofa

feature {CUSTOMER} -- Access

	has_room: BOOLEAN
		do
			Result := size - waiting > 0
		end

	empty: BOOLEAN
		do
			Result := in_shop = 0
		end

feature {CUSTOMER} -- Basic Operations

	enter: INTEGER
		-- allows to enter the room
	    require
	      max_size: size - waiting > 0
	    do
	      waiting := waiting + 1
	      in_shop := in_shop + 1
	      current_ticket := current_ticket + 1
	      Result := current_ticket
	    ensure
	      waiting_size: waiting = old waiting + 1
	      new_size: in_shop = old in_shop + 1
    	end

	leave_room
		-- decreases the number of customers in the room
    	require
      		waiting_ne: waiting > 0
    	do
      		waiting := waiting - 1
    	ensure
      		waiting_size: waiting = old waiting - 1
   		 end

 	leave
 		-- decreases the number of customers in the shop
    	require
     		in_shop_ne: in_shop > 0
    	do
        	in_shop := in_shop - 1
   		ensure
      		new_size: in_shop = old in_shop - 1
    	end

feature {APPLICATION} -- Access
	open_shop
		do
			open := True
		end
invariant
	positive_size: size > 0
	non_negative_waiting_room: waiting >= 0
	shop_overall_size: in_shop <= 100 -- TODO separate a shop class

end
