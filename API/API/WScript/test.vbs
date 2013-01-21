
' DON'T FORGET TO regsvr32 \path\API\RR_COM_API.dll before running!!
' You can run this script using
' cscript test.vbs
' from the cmd.exe (console) prompt

set rr=CreateObject("RoboRealm.API.1") 

' open RoboRealm if not already running
rr.Open "c:\www\RoboRealm\bin\RoboRealm.exe", 6060

if not rr.Connect("localhost") then
  WScript.Echo "Could not connect to RoboRealm Server"
  WScript.Quit(EXIT_INVALID_INPUT)
else

  rr.MaximizeWindow()

  Dim width, height

  ' get the image dimension
  rr.GetDimension width, height

  ' show it to the user
  WScript.Echo "Width: " & width & " Height:" & height

  ' set a custom variable .. will appear in RR
  rr.SetVariable "test", "this"

  'get a variable from RR
  WScript.Echo "Image_Count: " & rr.GetVariable("IMAGE_COUNT")

  ' set more than one variable
  Dim names(2)
  Dim values(2)
  names(0) = "my_first_custom_var"
  names(1) = "my_second_custom_var"
  values(0) = "test1"
  values(1) = "test2"
  rr.SetVariables names, values

  ' read more than one variable at a time
  list = rr.GetVariables("my_first_custom_var,my_second_custom_var")
  if isArray(list) then
    WScript.Echo list(0) & ", " & list(1)
  end if

  ' get the current processed image
  rr.GetImage "", pixels, width, height
  
  ' save that image to a local ppm file
  rr.SavePPM "c:\temp\test.ppm", pixels, width, height 

  WScript.Echo "Saved Processed Image to c:\temp\test.ppm"

  ' turn off live camera
  rr.setCamera "off"

  ' load an image for experimentation
  rr.loadPPM "c:\www\RoboRealm\bin\remo.ppm", image, width, height

  ' change the current image
  rr.setImage "", image, width, height

  ' could also load an image from disk if image is on same machine as RoboRealm
  'rr.loadImage "", "c:\www\RoboRealm\bin\remo.gif"

  WScript.Echo "Changed Image in RoboRealm to Remo"
  
  ' add a marker image called mt_new_image
  rr.setImage "my_new_image", image, width, height

  ' execute a RGB filter on the loaded image
  rr.execute "<head><version>1.50</version></head><RGB_Filter><min_value>40</min_value><channel>3</channel></RGB_Filter>"

  WScript.Echo "Added Red Green Filter in RoboRealm"

  ' run a .robo program
  rr.loadProgram "c:\www\RoboRealm\scripts\red.robo"

  WScript.Echo "Ran the red.robo script"

  ' save that image back to disk .. note that we can switch extensions
  rr.saveImage "", "c:\temp\remo.jpg"

  WScript.Echo "Saved Remo.ppm to c:\temp\remo.jpg"

  rr.Close()
  ' or use rr.Disconnect() if you want to keep RoboRealm running

end if


 