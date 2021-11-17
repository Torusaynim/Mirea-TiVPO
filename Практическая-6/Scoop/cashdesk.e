note
	description: "Summary description for {CASHDESK}."
	date: "$Date$"
	revision: "$Revision$"

class
	CASHDESK

create
	make

feature {NONE} -- Initialization

	make (a_size: INTEGER)
		-- Initialize with `a_size' as size
		do
			size := a_size
		end

feature {NONE} -- Implementation
	size : INTEGER -- number of concurrent checkouts
	waiting : INTEGER  --  number of customer waiting to pay

feature {CUSTOMER} -- Access

	has_room: BOOLEAN
		-- is there any sit available?
		local
			available : INTEGER
		do
			available := size - waiting
			print (available.out +" Available cash desks %N")
			Result := size - waiting > 0
		end

	is_empty: BOOLEAN
		-- is the sofa empty?
		do
			Result := waiting = 0
		end

feature {CUSTOMER} -- Basic Operations

	open
		-- occupies one cash desk
		do
			waiting := waiting + 1
		ensure
			waiting = old waiting + 1
		end

	close
		-- frees one cash desk
		do
			waiting := waiting - 1
		ensure
			waiting = old waiting - 1

		end

invariant
	positive_size: size > 0 -- size must be greater than zero
	non_negative_line: waiting >= 0	-- waiting line must be non negative
end
