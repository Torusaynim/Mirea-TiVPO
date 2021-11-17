note
	description: "poligoni application root class"
	date: "$Date$"
	revision: "$Revision$"

class
	APPLICATION

inherit
	ARGUMENTS

create
	make
feature
	mySquare:SQUARE
	myRectangle:RECTANGLE

feature {NONE}
	make
		local
			index:INTEGER
			returned:DOUBLE
		do
			print ("%N%NLet's try Eiffel lang!%N----------------------%N%N")
			create mySquare.make(10)

				print("%NArea: ")
					io.put_real (mySquare.getArea)
					print("%N")
				print("Perimeter: ")
					io.put_real (mySquare.getPerimeter)
					print("%N")

			create myRectangle.make(20,5)

				print("%NArea: ")
					io.put_real (myRectangle.getArea)
					print("%N")
				print("Perimeter: ")
					io.put_real (myRectangle.getPerimeter)
					print("%N%N")


			print("Now I'm gonna create 10 different squares in a loop%N")

			from
				index:=0
			until
				index>=10
			loop
				mySquare.make (index)
					print(" with side: ")
						io.put_real(index)
						print("%N")
				index:=index+1
			end

			print("%NLet's see some fractions%N")
			print("1/10 of a RECTANGLE with base=20 and height=5 is: ")
				-- getFraction is a feature, don't call it outside another
				-- feature or without assigning the Result value,
				-- it will raise a compilation error
				io.put_double (myrectangle.getfraction (10))
			print("%N1/0 of a RECTANGLE with base=20 and height=5 is: ")
				returned := myrectangle.getfraction (0)

		end

end
