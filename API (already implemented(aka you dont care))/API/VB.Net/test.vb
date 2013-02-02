Option Strict Off
Option Explicit On

Imports System.Text.Encoding

Module Module1

    ' DON'T FORGET TO regsvr32 \path\API\RR_COM_API.dll before running!!
    Dim rr As Object

    Public Sub Main()

        rr = CreateObject("RoboRealm.API.1")

        ' open RoboRealm if not already running
        rr.Open("c:\www\RoboRealm\bin\RoboRealm.exe", 6060)

        Dim pixels(230400) As Byte
        Dim width, height As Integer
        Dim image As Object
        Dim names(2) As Object
        Dim values(2) As Object
        Dim List As Array
        If Not rr.Connect("localhost") Then
            MsgBox("OK", MsgBoxStyle.OkOnly, "Could not connect to RoboRealm Server")
            Exit Sub
        Else

            ' get the image dimension
            width = 0
            height = 0
            rr.GetDimension(width, height)

            ' show it to the user
            MsgBox("Width: " & width & " Height:" & height, MsgBoxStyle.OkOnly, "RoboRealm API")

            ' set a custom variable .. will appear in RR
            rr.SetVariable("test", "this")

            'get a variable from RR
            MsgBox("Image_Count: " & rr.GetVariable("IMAGE_COUNT"), MsgBoxStyle.OkOnly, "RoboRealm API")

            names(0) = "my_first_custom_var"
            names(1) = "my_second_custom_var"
            values(0) = "test1"
            values(1) = "test2"
            rr.SetVariables(names, values)

            List = rr.GetVariables("my_first_custom_var,my_second_custom_var")
            If IsArray(List) Then
                MsgBox(List(0) & ", " & List(1))
            End If

            ' get the current processed image
            rr.GetImage("", pixels, width, height)

            ' save that image to a local ppm file
            rr.SavePPM("c:\temp\test.ppm", pixels, width, height)

            MsgBox("Saved Processed Image to c:\temp\test.ppm", MsgBoxStyle.OkOnly, "RoboRealm API")

            ' turn off live camera
            rr.setCamera("off")

            ' load an image for experimentation
            rr.loadPPM("c:\www\RoboRealm\bin\remo.ppm", pixels, width, height)

            '   change the current image
            rr.setImage("", pixels, width, height)

            ' could also load an image from disk if image is on same machine as RoboRealm
            'rr.loadImage "", "c:\www\RoboRealm\bin\remo.gif"

            MsgBox("Changed Image in RoboRealm to Remo", MsgBoxStyle.OkOnly, "RoboRealm API")

            '   add a marker image called mt_new_image
            rr.setImage("my_new_image", pixels, width, height)

            ' execute a RGB filter on the loaded image
            rr.execute("<head><version>1.50</version></head><RGB_Filter><min_value>40</min_value><channel>3</channel></RGB_Filter>")

            MsgBox("Added Red Green Filter in RoboRealm", MsgBoxStyle.OkOnly, "RoboRealm API")

            ' run a .robo program
            rr.loadProgram("c:\www\RoboRealm\scripts\red.robo")

            MsgBox("Ran the red.robo script", MsgBoxStyle.OkOnly, "RoboRealm API")

            ' save that image back to disk .. note that we can switch extensions
            rr.saveImage("", "c:\temp\remo.jpg")

            MsgBox("Saved Remo.ppm to c:\temp\remo.jpg", MsgBoxStyle.OkOnly, "RoboRealm API")

            rr.Close()
            ' or use rr.Disconnect() if you want to keep RoboRealm running

            ' other examples
            ' rr.MinimizeWindow()
            ' rr.MaximizeWindow()
            ' rr.MoveWindow(100,100)
            ' rr.ResizeWindow(200,200)
            ' rr.PositionWindow(100,100,200,200)


        End If

    End Sub
End Module