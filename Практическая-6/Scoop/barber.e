note
	description: "Summary description for {BARBER}."
	date: "$Date$"
	revision: "$Revision$"

class
	BARBER

create
	make

feature {NONE} -- Initialization

  rnd: RANDOM

	make (a_id: INTEGER)
			-- Initialize with `a_id' as id
		require
			a_id > 0
		local
			l_time: TIME
  		l_seed: INTEGER
		do
			id := a_id
			create l_time.make_now
      l_seed := l_time.milli_second
      create rnd.set_seed (l_seed)
		ensure
			id = a_id
		end

feature {CUSTOMER} -- Operations

	cut_hair (c: separate CUSTOMER)
		do
			print ("Barber "+id.out+ " is cutting Customer "+ c.id.out +" s hairs.%N")
			(create {EXECUTION_ENVIRONMENT}).sleep ((rnd.item \\ 10) * 1000)
		end

	accept_payment (c: separate CUSTOMER)
		do
			print ("Customer "+ c.id.out +" is paying Barber " + id.out +	"%N")
			(create {EXECUTION_ENVIRONMENT}).sleep ((rnd.item \\ 10) * 1000)
		end

feature -- Implementation

	id: INTEGER -- Unique Id

invariant
	valid_id: id > 0
end
