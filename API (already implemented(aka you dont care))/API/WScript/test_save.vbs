
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

  ' run a .robo program
  rr.saveProgram "c:\temp\red.robo"

end if


 