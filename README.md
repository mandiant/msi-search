# MSI Search

Windows caches MSI files at `C:\Windows\Installer\` with randomized filenames consisting of letters and numbers followed by the ".msi" extension. This tool simplifies the task for red team operators to identify which MSI files correspond to which software and enables them to download the relevant file to investigate local privilege escalation vulnerabilities through MSI repairs. Read more at [Elevating Privileges via Third-Party Windows Installers] on how to identify privilege escalation vulnerabilities via MSI repairs.

Author: Andrew Oliveau (@AndrewOliveau)

## Compile

```
x86_64-w64-mingw32-gcc -c msi_search.c -o msi_search.x64.o
i686-w64-mingw32-gcc -c msi_search.c -o msi_search.x86.o
```

## Usage

Aggressor script included. Import it into Cobalt Strike and run `msi_search`. Alternatively, run the PowerShell script `msi_search.ps1`.

![image](https://github.com/googlestaging/msi-search/assets/32691065/e45c1257-d385-4ae3-9bc9-7d39d19800b0)

![image](https://github.com/googlestaging/msi-search/assets/32691065/ee64d129-58f2-4bc3-aa00-738f710b1748)

[Elevating Privileges via Third-Party Windows Installers]: https://www.mandiant.com/resources/blog/privileges-third-party-windows-installers?auHash=0SnaFvuqMHadnw4az4gYD06-fMn6xaWSSXg1FwY92IU
