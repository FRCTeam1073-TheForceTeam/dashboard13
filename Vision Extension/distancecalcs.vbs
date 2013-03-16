list = GetArrayVariable("MEQ_COORDINATES")
if isArray(list) then
  if ubound(list) > 0 then

    rightTopY = list(1)
    rightBottomY = list(7)
    leftTopY = list(3)
    leftBottomY = list(5)
	rightTopX = list(0)
    rightBottomX = list(6)
    leftTopX = list(2)
    leftBottomX = list(4)
	
		SetVariable "underneathHY", ((rightBottomY + leftBottomY)/2)
		SetVariable "underneathHX", ((rightBottomX + leftBottomX)/2)
		SetVariable "rightUnderneathHY", rightBottomY
		SetVariable "rightUnderneathHX", rightBottomX
		SetVariable "targetRatio", (rightTopX - leftTopx + rightBottomX - leftBottomX)/(rightTopY - rightBottomY + leftTopY - leftBottomY)

	end if
end if
