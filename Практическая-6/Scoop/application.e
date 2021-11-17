note
	description: "project2 application root class"
	date: "$Date$"
	revision: "$Revision$"

class
	APPLICATION

inherit
  ARGUMENTS

create
	make

feature
	make
		local
			customer: separate CUSTOMER
			barber : separate BARBER

			barbers : separate BARBER_LIST
			cash_desk: separate CASHDESK
			sofa: separate SOFA
			shop: separate BARBERSHOP

			temp_str: detachable STRING_8
		do
			temp_str := separate_word_option_value ("help")
			if attached temp_str as l_temp_str then

				print("-cd : Number of cash desks (1 by default)%N")
				print("-b : Number of barbers in the barbershop (3 by default)%N")
				print("-c : Number of customers involved in the execution (10 by default)%N")
				print("-h : Number of haircuts per customer (1 by default)%N")
				print("-s : Size of the sofa (4 by default)%N")
				print("-w : Size of the standing waiting room (16 by default)%N")
				print("%N")

      else
				temp_str := separate_word_option_value ("cd")
				if attached temp_str as l_temp_str then
	        cash_desks_num :=  temp_str.to_integer
	      else
	      	cash_desks_num := 1
	      end

				temp_str := separate_word_option_value ("b")
				if attached temp_str as l_temp_str then
	        barbers_num :=  temp_str.to_integer
	      else
	      	barbers_num := 3
	      end

	      temp_str := separate_word_option_value ("c")
				if attached temp_str as l_temp_str then
	        customer_num :=  temp_str.to_integer
	      else
	      	customer_num := 10
	      end

	      temp_str := separate_word_option_value ("h")
				if attached temp_str as l_temp_str then
	        haircuts :=  temp_str.to_integer
	      else
	      	haircuts := 1
	      end

	      temp_str := separate_word_option_value ("s")
				if attached temp_str as l_temp_str then
	        sofa_size :=  temp_str.to_integer
	      else
	      	sofa_size := 4
	      end

	      temp_str := separate_word_option_value ("w")
				if attached temp_str as l_temp_str then
	        waiting_room_size :=  temp_str.to_integer
	      else
	      	waiting_room_size := 16
	      end

				create cash_desk.make (cash_desks_num)
				create barbers.make (barbers_num)
				create sofa.make (sofa_size)
				create shop.make (waiting_room_size)

				print("Number of cash desk: " + cash_desks_num.out + "%N")
				print("Number of barbers: " + barbers_num.out + "%N")
				print("Number of customers: " + customer_num.out + "%N")
				print("Number of haircuts per customer: " + haircuts.out + "%N")
				print("Number of waiting sits on sofa : " + sofa_size.out + "%N")
				print("Number of waiting place in standing room :" + waiting_room_size.out + "%N")
				print("%N")

				across (1 |..| barbers_num) as ib loop
					print("Creating barber "+ ib.item.out +"%N")
					create barber.make (ib.item)
					separate barbers as c do
						c.sit (barber)
					end
				end

				across (1 |..| customer_num) as ic loop
					print("Creating customer "+ ic.item.out +"%N")
					create customer.make (ic.item, haircuts, shop, sofa, barbers, cash_desk)
					separate customer as c do
						c.live
					end
				end


				separate shop as s
					do
						s.open_shop
					end
			end
		end

feature
	cash_desks_num: INTEGER
	customer_num: INTEGER
	barbers_num: INTEGER
	haircuts: INTEGER
	sofa_size: INTEGER
	waiting_room_size: INTEGER
end
