# MSI Search

Windows caches MSI files at `C:\Windows\Installer\` with randomized filenames consisting of letters and numbers followed by the ".msi" extension. This tool simplifies the task for red team operators to identify which MSI files correspond to which software and enables them to download the relevant file to investigate local privilege escalation vulnerabilities through MSI repairs. Read more *here* on how to identify privilege escalation vulnerabilities via MSI repairs.

Author: Andrew Oliveau (@AndrewOliveau)

## Compile

```
x86_64-w64-mingw32-gcc -c msi_search.c -o msi_search.x64.o
i686-w64-mingw32-gcc -c msi_search.c -o msi_search.x86.o
```

## Usage

Aggressor script included. Import it and run `msi_search`. Alternatively, run the PowerShell script `msi_search.ps1`.

![til](/demo.png "Demo")

![til](/demo2.png "Demo2")
