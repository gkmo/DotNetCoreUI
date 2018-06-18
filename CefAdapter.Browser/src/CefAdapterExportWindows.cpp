
#include <iostream>

#include "include/cef_base.h"
#include "include/cef_browser_process_handler.h"
#include "include/cef_command_line.h"
#include "include/cef_render_process_handler.h"
#include "include/cef_resource_bundle_handler.h"
#include "include/cef_scheme.h"

#include "CefAdapterDefinitions.h"
#include "CefAdapterBrowserApplication.h"
#include "CefAdapterEventHandler.h"

extern "C"
{
	EXPORT bool CreateApplication(HINSTANCE hInstance, const char* url, const char* subprocessPath, const char* logPath,
		BrowserCreatedCallback browserCreatedCallback, ContextCreatedCallback contextCreatedCallback, 
		ExecuteJsFunctionCallback executeJsFunctionCallback, QueryCallback queryCallback)
	{
		CefEnableHighDPISupport();

		void* sandbox_info = NULL;

		CefMainArgs args(hInstance);
		CefSettings settings;
		
		settings.no_sandbox = true;
		
		CefString(&settings.log_file).FromASCII(logPath);		

		CefRefPtr<CefAdapterBrowserApplication> app(new CefAdapterBrowserApplication(url, browserCreatedCallback, 
			contextCreatedCallback, executeJsFunctionCallback, queryCallback));

		if (subprocessPath) 
		{
			CefString(&settings.browser_subprocess_path).FromASCII(subprocessPath);
		}
		else
		{
			settings.single_process = true;

			if (CefExecuteProcess(args, app.get(), sandbox_info) >= 0)
			{
				return false;
			}
		}
					
		return CefInitialize(args, settings, app.get(), NULL);
	}	
}