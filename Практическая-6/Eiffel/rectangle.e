note
	description: "Summary description for {RECTANGLE}."
	date: "$Date$"
	revision: "$Revision$"

class
	RECTANGLE
inherit
	POLYGON
create
	make

	feature
		base:REAL
		height:REAL
		ispositive_infinity:BOOLEAN

	feature{ANY}
		make(b:REAL; h:REAL)
	require else
		base>=0
		height>=0
	do
		base:=b
		height:=h
		print("New RECTANGLE created");
	end
	feature{ANY}
		getArea:REAL
		do
			Result:=(base*height)
		ensure then
			Result>=0
		end

	feature{ANY}
		getPerimeter:REAL
		do
			Result:=(base*2 )+(height*2)

		ensure then
			Result>=0
		end
	feature{ANY}
		getFraction(fract:INTEGER):DOUBLE
		local
			retried:BOOLEAN
		do

			if not retried then
				Result:=(base*height)/fract
			else
				Result:=0
			end

			ispositive_infinity:=Result.is_positive_infinity

		ensure
			Result>=0 and not ispositive_infinity
		rescue
			print("Caught division by zero%N")
			retried:=true
			retry
		end

	invariant
		RectangleInvariant: base/=height
		-- A polygon with base=height is a rectangle but in this case
		-- the square class is the correct class to to this.

end
