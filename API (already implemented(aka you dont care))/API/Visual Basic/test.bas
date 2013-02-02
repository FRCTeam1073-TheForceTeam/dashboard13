Attribute VB_Name = "Module1"
 Option Explicit

 ' DON'T FORGET TO regsvr32 \path\API\RR_COM_API.dll before running!!
 Dim rr

 Public Sub Main()
 
    Set rr = CreateObject("RoboRealm.API.1")
    
    ' open RoboRealm if not already running
    rr.Open "c:\www\RoboRealm\bin\RoboRealm.exe", 6060
    
    If Not rr.Connect("localhost") Then
        MsgBox "OK", vbOKOnly, "Could not connect to RoboRealm Server"
        Exit Sub
    Else
    
        Dim width, height, pixels, image
    
        ' get the image dimension
        rr.GetDimension width, height
    
        ' show it to the user
        MsgBox "Width: " & width & " Height:" & height, vbOKOnly, "RoboRealm API"
    
        ' set a custom variable .. will appear in RR
        rr.SetVariable "test", "this"
    
        'get a variable from RR
        MsgBox "Image_Count: " & rr.GetVariable("IMAGE_COUNT"), vbOKOnly, "RoboRealm API"
    
        Dim names(2)
        Dim values(2)
        names(0) = "my_first_custom_var"
        names(1) = "my_second_custom_var"
        values(0) = "test1"
        values(1) = "test2"
        rr.SetVariables names, values

        ' set a custom variable .. will appear in RR
        Dim List
        List = rr.GetVariables("my_first_custom_var,my_second_custom_var")
        If IsArray(List) Then
            MsgBox List(0) & ", " & List(1)
        End If
    
        ' get the current processed image
        rr.GetImage "", pixels, width, height
        
        ' save that image to a local ppm file
        rr.SavePPM "c:\temp\test.ppm", pixels, width, height
    
        MsgBox "Saved Processed Image to c:\temp\test.ppm", vbOKOnly, "RoboRealm API"
    
        ' turn off live camera
        rr.setCamera "off"
    
        ' load an image for experimentation
        rr.loadPPM "c:\www\RoboRealm\bin\remo.ppm", image, width, height
    
        '   change the current image
        rr.setImage "", image, width, height
    
        ' could also load an image from disk if image is on same machine as RoboRealm
        'rr.loadImage "", "c:\www\RoboRealm\bin\remo.gif"
    
        MsgBox "Changed Image in RoboRealm to Remo", vbOKOnly, "RoboRealm API"
        
        '   add a marker image called mt_new_image
        rr.setImage "my_new_image", image, width, height
    
        ' execute a RGB filter on the loaded image
        rr.execute "<head><version>1.50</version></head><RGB_Filter><min_value>40</min_value><channel>3</channel></RGB_Filter>"
        
        ' wait for processing to be complete
        rr.waitImage
    
        MsgBox "Added Red Green Filter in RoboRealm", vbOKOnly, "RoboRealm API"
    
        ' run a .robo program
        rr.loadProgram "c:\www\RoboRealm\scripts\red.robo"
    
        MsgBox "Ran the red.robo script", vbOKOnly, "RoboRealm API"
    
        ' save that image back to disk .. note that we can switch extensions
        rr.saveImage "", "c:\temp\remo.jpg"
    
        MsgBox "Saved Remo.ppm to c:\temp\remo.jpg", vbOKOnly, "RoboRealm API"
    
        rr.Close
        ' or use rr.Disconnect() if you want to keep RoboRealm running
    
    End If

 End Sub

 
