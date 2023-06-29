<#
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
#>

$folderPath = "C:\Windows\Installer"
$msiFiles = Get-ChildItem -Path $folderPath -Filter "*.msi" -File

foreach ($file in $msiFiles) {
    Write-Host "-----------------------------"
    Write-Host "File: $($file.FullName)"

    try {
        $database = (New-Object -ComObject WindowsInstaller.Installer).OpenDatabase($file.FullName, 0)
        $view = $database.OpenView("SELECT `Value` FROM `Property` WHERE `Property`='Manufacturer'")
        $view.Execute()
        $record = $view.Fetch()
        if ($record -ne $null) {
            $manufacturer = $record.StringData(1)
            Write-Host "Manufacturer: $manufacturer"
        }
        

        $view = $database.OpenView("SELECT `Value` FROM `Property` WHERE `Property`='ProductName'")
        $view.Execute()
        $record = $view.Fetch()
        if ($record -ne $null) {
            $productName = $record.StringData(1)
            Write-Host "ProductName: $productName"
        }
        

        $view = $database.OpenView("SELECT `Value` FROM `Property` WHERE `Property`='ProductVersion'")
        $view.Execute()
        $record = $view.Fetch()
        if ($record -ne $null) {
            $productVersion = $record.StringData(1)
            Write-Host "ProductVersion: $productVersion"
        }
    
    
    }
    catch {
        Write-Host "Error: $($_.Exception.Message)"
    }
}
