
RR_COM_APIps.dll: dlldata.obj RR_COM_API_p.obj RR_COM_API_i.obj
	link /dll /out:RR_COM_APIps.dll /def:RR_COM_APIps.def /entry:DllMain dlldata.obj RR_COM_API_p.obj RR_COM_API_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del RR_COM_APIps.dll
	@del RR_COM_APIps.lib
	@del RR_COM_APIps.exp
	@del dlldata.obj
	@del RR_COM_API_p.obj
	@del RR_COM_API_i.obj
