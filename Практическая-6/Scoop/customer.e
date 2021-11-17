note
	description: "Summary description for {CUSTOMER}."
	date: "$Date$"
	revision: "$Revision$"

class
	CUSTOMER

create
	make

feature {NONE} -- Initialization

	make (a_id: INTEGER; a_haircuts: INTEGER; a_shop: separate BARBERSHOP; a_sofa: separate SOFA;  a_barbers: separate BARBER_LIST;  a_cash_desk: separate CASHDESK)
		-- Initialize with `a_id' as is
		-- a_haircuts as haircuts
		-- a_shop as shop
		-- a_sofa as sofa
		-- a_barbers as barbers
		-- a_cash_desk as cash_desk

		require
			haircuts: a_haircuts > 0
			id: a_id > 0
		do
			id := a_id
			haircuts := a_haircuts
			shop := a_shop
			sofa := a_sofa
			barbers := a_barbers
			cash_desk := a_cash_desk
		ensure
			haircuts = a_haircuts
			id = a_id
		end

feature {CASHDESK, BARBER}
	id: INTEGER

feature {NONE}

	haircuts: INTEGER
	shop : separate BARBERSHOP
	sofa : separate SOFA
	barbers : separate BARBER_LIST
	cash_desk : separate CASHDESK
	my_ticket : INTEGER assign set_ticket

	over: BOOLEAN
		do
			Result := haircuts <= 0
		end

	set_ticket (i: INTEGER)
		do
			my_ticket := i
		end



feature {APPLICATION}
	live
		do
			wait (shop)
			from
			until
				over
			loop
				print ("Customer "+id.out+" is alive %N")
				step
			end
		end

feature {NONE} -- Synchronization

	wait (s: separate BARBERSHOP)
		-- Workaround to synchronize the process start
		require
			s.open
		do
		end

feature {NONE} -- Life actions

	enter (s: separate BARBERSHOP): BOOLEAN
		-- Enter the shop, i.e. the waiting room
		do
			print ("Customer "+id.out+" enters the shop%N")
			if s.has_room then
				my_ticket := s.enter
				Result := True
			else
				Result := False
			end
		end

	sit_on_sofa (s: separate SOFA)
		-- sit on the shop sofa if there is room, otherwise it waits in the waiting room
		--
		require
			s.has_room and s.allowed (my_ticket)
		do
			separate shop as sh do
				sh.leave_room
			end

			s.update (my_ticket)
			my_ticket := s.sit_down
			print ("Customer "+id.out+" sits on sofa with ticket "+my_ticket.out+"%N")
		end

	stand_up_sofa (s:separate SOFA)
		do
			print ("Customer "+id.out +" stands up from the sofa %N")
			s.stand_up
		end

	sit_on_chair (c: separate BARBER_LIST): separate BARBER
		-- gets a free barber from the barber array with FIFO ordering
		-- and remove the customer from the sofa
		require
			c.has_room  and c.allowed(my_ticket)
		local
			b: separate BARBER
		do
			b := c.head

			stand_up_sofa (sofa) -- moved here because I want the customer to stand before it releases the lock on barbers

			separate b as barb do
				print ("Customer "+id.out+" sits on Barber "+barb.id.out+" s chair %N")
			end
			c.update(my_ticket)


			Result := b
		end

	ask_for_checkout (c: separate BARBER_LIST): separate BARBER
		-- gets a free barber from the barber array, no FIFO guaranteed
		require
			c.has_room
		local
			b: separate BARBER
		do
			b := c.head
			separate b as barb do
				print ("Customer "+id.out+" will pay Barber "+barb.id.out+"%N")
			end
			Result := b
		end

	free_barber (b: separate BARBER; bs: separate BARBER_LIST)
		do
			bs.sit (b)
		end


	get_hair_cut (b: separate BARBER)
		-- allows to interact with the barber to get an haircut
		do
			b.cut_hair (Current)
			haircuts := haircuts - 1

			print ("Customer "+id.out+" got an haircut%N")

			free_barber (b, barbers)
		end

	pay (b: separate BARBER; cd: separate CASHDESK)
		-- allows to pay, no FIFO ordering guaranteed
		require
			cd.has_room
		do
			cd.open
			b.accept_payment (Current)

		end

	checkout (b: separate BARBER; cd: separate CASHDESK)
		require
			not_empty: not cd.is_empty
		do
			cd.close
			free_barber (b, barbers)
		end

	leave (s: separate BARBERSHOP)
		-- remove the customer from the shop
		require
			not s.empty
		do
			print ("Customer "+id.out+" leaves the shop%N")
			s.leave
		end

	step
		-- a cycle of life
		local
			barber: separate BARBER
		do
			if enter (shop) then

				sit_on_sofa (sofa) -- if there is no room it will wait in the room (queue); FIFO

				barber := sit_on_chair (barbers) -- if one is available

				get_hair_cut (barber) -- from the assigned barber

				barber := ask_for_checkout (barbers) -- if one is available

				pay (barber, cash_desk) -- to the assigned barber

				checkout (barber, cash_desk) -- to the assigned barber

				leave (shop)

			else
				print ("Customer " + id.out + " will come back later.%N")
				(create {EXECUTION_ENVIRONMENT}).sleep ({INTEGER_64} 10_000_000)
			end
		end

invariant
	id > 0
	haircuts >= 0
end
