list = GetArrayVariable("MEQ_COORDINATES")
if isArray(list) then
  if ubound(list) > 0 then

	'	targetPixelHeight = 0
   ' targetSamples = 0

    ' calibrated for an Axis camera
    ' imageHeight = GetVariable("IMAGE_HEIGHT")
  ' 	cameraFieldOfView = 34.9
	' 	cameraAngle = 8.5
	' targetHeight = 29
	' deltaH = 37
	' theta1 = (3.141592/180)*(cameraAngle/2)
	' theta2 = ((3.141592/180)*(cameraFieldOfView/2)) - theta1

    ' grab list of coordinates from blob_replace
	 	' note the array is sorted by previous module in a specific order
    righty = list(1)
    rightyy = list(7)
    lefty = list(3)
    leftyy = list(5)

		' based on these two side lines get the center line height
		' the center line is used since we want to aim to the center
  	' of the target. This also removes any perspective distortion
	  ' where the right or left size may be a couple inches closer
		' or futher away from the camera
  	' targetPixelHeight = ((lefty - leftyy) + (righty - rightyy)) / 2

	verticalPixelDisplacement = ((leftyy + rightyy)/2)
	targetRatio = (list(0) - list(2) + list(6) - list(4))/(list(1) - list(7) + list(3) - list(5))
	'alpha = atn((verticalPixelDisplacement - (imageHeight/2))*(tan(theta1+theta2)/240))

' write targetPixelHeight 

    ' we can use a known distance to determine FOV if we don't know it
	  ' measuredDistance = 10.0*12.0
 	  ' write "Calculated FOV " & (((atan((((targetHeight*imageHeight)/targetPixelHeight)/2)/measuredDistance)*2.0)*180.0)/3.14159) & vbCRLF

    ' determine distance in inches
    ' totalDistance = (((targetHeight*imageHeight)/targetPixelHeight)/2)/tan(((cameraFieldOfView*3.14159)/180.0)/2.0)
		'  totalDistance = deltaH/(tan(alpha+theta2-theta1))
	
		' SetVariable "distance", ((totalDistance*100)/12)/100
		' SetVariable "targetH", targetPixelHeight
		SetVariable "underneathH", verticalPixelDisplacement
		SetVariable "targetRatio", targetRatio
		SetVariable "targetH", (list(1) - list(7) + list(3) - list(5))
		'SetVariable "width", (list(0) - list(2) + list(6) - list(4))/2
		'SetVariable "height", (list(1) - list(7) + list(3) - list(5))/2
		'SetVariable "list1", list(1)
		'SetVariable "list3", list(3)
		'SetVariable "list5", list(5)
		'SetVariable "list7 ", list(7)

	end if
end if
