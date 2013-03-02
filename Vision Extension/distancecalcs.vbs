list = GetArrayVariable("MEQ_COORDINATES")
if isArray(list) then
  if ubound(list) > 0 then

    righty = list(1)
    rightyy = list(7)
    lefty = list(3)
    leftyy = list(5)


	verticalPixelDisplacement = ((leftyy + rightyy)/2)
	
		SetVariable "underneathH", verticalPixelDisplacement
		SetVariable "targetH", (list(1) - list(7) + list(3) - list(5))
		SetVariable "hi", (list(6) + list(4))/2

	end if
end if
