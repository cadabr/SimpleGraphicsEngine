$ErrorActionPreference = "Continue"

git submodule deinit -f -- external/boost                 > $null 2>&1
git rm -f external/boost                                  > $null 2>&1

Remove-Item -Recurse -Force .git\modules\external\boost   > $null 2>&1
Remove-Item -Recurse -Force external\boost                > $null 2>&1

Write-Host "Ok" -ForegroundColor Green
