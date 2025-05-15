# Удаляет указанные подмодули Git: деинициализация, удаление из индекса и файловой системы.
# Пример использования: .\remove-submodule-windows.ps1 external/SDL external/boost

$ErrorActionPreference = "Continue"

if ($args.Count -lt 1) {
    Write-Host "Usage: remove-submodule.ps1 <submodule-path1> [<submodule-path2> ...]" -ForegroundColor Yellow
    exit 1
}

foreach ($SubmodulePath in $args) {
    $GitPath = $SubmodulePath -replace '\\', '/'

    try {
        git submodule deinit -f -- $GitPath                 > $null 2>&1
        git rm -f $GitPath                                  > $null 2>&1

        $ModuleDir = ".git\modules\$SubmodulePath"
        $LocalDir = $SubmodulePath

        if (Test-Path $ModuleDir) {
            Remove-Item -Recurse -Force $ModuleDir           > $null 2>&1
        }

        if (Test-Path $LocalDir) {
            Remove-Item -Recurse -Force $LocalDir            > $null 2>&1
        }

        Write-Host "Submodule '$SubmodulePath' removed successfully." -ForegroundColor Green

    } catch {
        Write-Host "Error while removing submodule '$SubmodulePath': $_" -ForegroundColor Red
    }
}
