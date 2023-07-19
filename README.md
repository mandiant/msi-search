# MSI Search

Windows caches MSI files at `C:\Windows\Installer\` with randomized filenames consisting of letters and numbers followed by the ".msi" extension. This tool simplifies the task for red team operators and security teams to identify which MSI files correspond to which software and enables them to download the relevant file to investigate local privilege escalation vulnerabilities through MSI repairs. Read more about MSI repair vulnerabilities at [Escalating Privileges via Third-Party Windows Installers].

Author: Andrew Oliveau (@AndrewOliveau)

## Compile

```
x86_64-w64-mingw32-gcc -c msi_search.c -o msi_search.x64.o
i686-w64-mingw32-gcc -c msi_search.c -o msi_search.x86.o
```

## Usage

Aggressor script included. Import it into Cobalt Strike and run `msi_search`. Alternatively, run the PowerShell script `msi_search.ps1`.


<img src="https://github.com/mandiant/msi-search/assets/32691065/a83752e5-52ac-4137-8dad-6d76b5a30fcf" width="360" height="456">


<br>


<img src="https://github.com/mandiant/msi-search/assets/32691065/2e486fc1-8184-40d1-80b5-85b7b794cf12" width="360" height="280">


[Escalating Privileges via Third-Party Windows Installers]: https://www.mandiant.com/resources/blog/privileges-third-party-windows-installers
