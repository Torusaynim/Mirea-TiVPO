note
	description: "Summary description for {SOFA}."
	date: "$Date$"
	revision: "$Revision$"

class
	SOFA

create
	make

feature {NONE} -- Initialization

	make (a_size :INTEGER)
			-- Initialize with `a_size' as size
		do
			size := a_size
			waiting := 0

			current_ticket := -1
			next_ticket := a_size

			-- Create and initialize the tickets array
			create allowed_tickets.make_filled (0, 0, a_size)

			across (0 |..| a_size) as it loop
				allowed_tickets.put(it.item,it.item)
			end

		end

feature {CUSTOMER}-- Implementation

	-- Sofa size

	size : INTEGER  -- current size of the sofa
	waiting : INTEGER -- number of customer sat on the sofa

	-- FIFO ordering

	current_ticket : INTEGER -- value of the current ticket to assign
	next_ticket: INTEGER -- value of the next ticket to assign
	allowed_tickets: ARRAY[INTEGER] -- valid tickets to sit on sofa

feature -- Access

	has_room: BOOLEAN
		-- is there any sit available?
		do
			Result := size - waiting > 0
		end

	is_empty: BOOLEAN
		-- is the sofa empty?
		do
			Result := waiting = 0
		end

feature {CUSTOMER} -- Basic Operations

	sit_down: INTEGER
		-- Allows a customer to sit on the sofa
		require
			max_size: size - waiting > 0
		do
			waiting := waiting + 1
			current_ticket := current_ticket + 1
			Result := current_ticket
		ensure
			new_size: waiting = old waiting + 1
		end

	stand_up
		-- Allows a customer to stand up from the sofa
		require
			not_empty: waiting > 0
		do
			waiting := waiting - 1
		ensure
			new_size: waiting = old waiting - 1
		end

feature

	allowed(customer_ticket : INTEGER): BOOLEAN
		-- Returns TRUE if a ticket is allowed to sit yet, FALSE otherwise
		do
			Result := allowed_tickets.has (customer_ticket)
		end

	update(customer_ticket : INTEGER)
		-- Substitutes the ticket to the last sat customer to the next allowed one
		require
			allowed: allowed (customer_ticket)
		do
			across (0 |..| size) as it loop
				 if allowed_tickets.item (it.item) = customer_ticket then
				 	allowed_tickets.put(next_ticket, it.item)
					next_ticket := next_ticket + 1
				 end
			end


		ensure
			expired: not allowed (customer_ticket)
			new_allowed: allowed (next_ticket - 1)
			update_next: next_ticket = old next_ticket + 1
		end

invariant
	size: size > 0
	waiting: waiting >= 0
end
