/*
Copyright 2023 Google LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <stdio.h>
#include <windows.h>
#include <msiquery.h>
#include "third_party/beacon.h"

DECLSPEC_IMPORT UINT WINAPI MSI$MsiOpenDatabaseA(LPCSTR, LPCSTR, MSIHANDLE*);
DECLSPEC_IMPORT UINT WINAPI MSI$MsiDatabaseOpenViewA(MSIHANDLE, LPCSTR, MSIHANDLE*);
DECLSPEC_IMPORT UINT WINAPI MSI$MsiViewExecute(MSIHANDLE, MSIHANDLE);
DECLSPEC_IMPORT UINT WINAPI MSI$MsiViewFetch(MSIHANDLE, MSIHANDLE*);
DECLSPEC_IMPORT UINT WINAPI MSI$MsiCloseHandle(MSIHANDLE);
DECLSPEC_IMPORT UINT WINAPI MSI$MsiRecordGetStringA(MSIHANDLE, unsigned int, LPSTR, unsigned int*);
WINBASEAPI HANDLE WINAPI KERNEL32$FindFirstFileA(LPCSTR, LPWIN32_FIND_DATAA);
WINBASEAPI HANDLE WINAPI KERNEL32$FindNextFileA(LPCSTR, LPWIN32_FIND_DATAA);
WINBASEAPI WINBOOL WINAPI KERNEL32$FindClose(HANDLE hFindFile);
WINBASEAPI int __cdecl MSVCRT$sprintf(char *__stream, const char *__format, ...);

void go(int argc, char* argv[]) {
    WIN32_FIND_DATA fileData;
    HANDLE hFind;
    char searchPath[MAX_PATH];
    MSVCRT$sprintf(searchPath, "%s\\*.msi", "C:\\Windows\\Installer");

    hFind = KERNEL32$FindFirstFileA(searchPath, &fileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            	BeaconPrintf(CALLBACK_OUTPUT, "\n-----------------------------\n");
                BeaconPrintf(CALLBACK_OUTPUT, "File: C:\\Windows\\Installer\\%s\n", fileData.cFileName);

                char filePath[MAX_PATH];
                MSVCRT$sprintf(filePath, "%s\\%s", "C:\\Windows\\Installer", fileData.cFileName);
                MSIHANDLE hDatabase = NULL;
                if (MSI$MsiOpenDatabaseA(filePath, MSIDBOPEN_READONLY, &hDatabase) != ERROR_SUCCESS) {
                    BeaconPrintf(CALLBACK_OUTPUT, "Error: could not open MSI database\n");
                    continue;
                }
                
		MSIHANDLE hView = NULL;
		MSIHANDLE hRecord = NULL;
		
                if (MSI$MsiDatabaseOpenViewA(hDatabase, "SELECT `Value` FROM `Property` WHERE `Property`='Manufacturer'", &hView) == ERROR_SUCCESS) {
                    if (MSI$MsiViewExecute(hView, NULL) == ERROR_SUCCESS) {
                        if (MSI$MsiViewFetch(hView, &hRecord) == ERROR_SUCCESS) {
                            char manufacturer[256];
                            DWORD manufacturerLen = sizeof(manufacturer);
                            if (MSI$MsiRecordGetStringA(hRecord, 1, manufacturer, &manufacturerLen) == ERROR_SUCCESS) {
                                BeaconPrintf(CALLBACK_OUTPUT, "Manufacturer: %s\n", manufacturer);
                            }
                            MSI$MsiCloseHandle(hRecord);
                        }
                    }
                    MSI$MsiCloseHandle(hView);
                }

                if (MSI$MsiDatabaseOpenViewA(hDatabase, "SELECT `Value` FROM `Property` WHERE `Property`='ProductName'", &hView) == ERROR_SUCCESS) {
                    if (MSI$MsiViewExecute(hView, NULL) == ERROR_SUCCESS) {
                        if (MSI$MsiViewFetch(hView, &hRecord) == ERROR_SUCCESS) {
                            char productName[MAX_PATH];
                            DWORD productNameLen = sizeof(productName);
                            if (MSI$MsiRecordGetStringA(hRecord, 1, productName, &productNameLen) == ERROR_SUCCESS) {
                                BeaconPrintf(CALLBACK_OUTPUT, "ProductName: %s\n", productName);
                            }
                            MSI$MsiCloseHandle(hRecord);
                        }
                    }
                    MSI$MsiCloseHandle(hView);
                }

                if (MSI$MsiDatabaseOpenViewA(hDatabase, "SELECT `Value` FROM `Property` WHERE `Property`='ProductVersion'", &hView) == ERROR_SUCCESS) {
                    if (MSI$MsiViewExecute(hView, NULL) == ERROR_SUCCESS) {
                        if (MSI$MsiViewFetch(hView, &hRecord) == ERROR_SUCCESS) {
                            char productVersion[33];
                            DWORD productVersionLen = sizeof(productVersion);
                            if (MSI$MsiRecordGetStringA(hRecord, 1, productVersion, &productVersionLen) == ERROR_SUCCESS) {
                                BeaconPrintf(CALLBACK_OUTPUT, "ProductVersion: %s\n", productVersion);
                            }
                            MSI$MsiCloseHandle(hRecord);
                        }
                    }
                    MSI$MsiCloseHandle(hView);
                }
                MSI$MsiCloseHandle(hDatabase);
            }
        } while (KERNEL32$FindNextFileA(hFind, &fileData));
        KERNEL32$FindClose(hFind);
    }
}

