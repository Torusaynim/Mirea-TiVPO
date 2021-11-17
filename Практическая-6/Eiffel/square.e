note
	description: "Summary description for {SQUARE}."
	date: "$Date$"
	revision: "$Revision$"

class
	SQUARE
inherit
	POLYGON
create
	make

	feature
		side:REAL

	feature{ANY}
		make(size:REAL)
	require else size>=0
	do
		side:=size
		print("New SQUARE created");
	end

	feature{ANY}
		getArea:REAL
	do
		Result:=side*side

	ensure then
		Result>=0
	end

	feature{ANY}
		getPerimeter:REAL
	do
		Result:=side*4
	ensure then
		Result>=0
	end

end
