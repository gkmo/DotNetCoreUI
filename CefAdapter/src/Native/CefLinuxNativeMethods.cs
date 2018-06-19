﻿using System;
using System.Runtime.InteropServices;

namespace CefAdapter.Native
{    
    internal static class CefLinuxNativeMethods
    {
        [DllImport("CefAdapter.Browser")]
        public static extern int Opa(int value);

        [DllImport("CefAdapter.Browser")]
        public static extern bool CreateApplication(string url, string subprocessPath, string logPath,
            OnBrowserCreatedCallback onBrowserCreatedCallback, OnBrowserClosingCallback browserClosingCallback, 
            OnContextCreatedCallback contextCreatedCallback, JavaScriptRequestCallback queryCallback);

        [DllImport("CefAdapter.Browser")]
        public static extern void RunMessageLoop();

        [DllImport("CefAdapter.Browser")]
        public static extern void Shutdown();

        [DllImport("CefAdapter.Browser")]
        public static extern bool ExecuteJavaScript(int browserId, string code);

        [DllImport("CefAdapter.Browser")]
        public static extern bool ShowDeveloperTools(int browserId);

        [DllImport("CefAdapter.Browser")]
        public static extern void CreateJsGlobalFunction(int browserId, string name);
    }
}
