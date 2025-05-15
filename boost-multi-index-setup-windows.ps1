$ErrorActionPreference = "Stop"

$BOOST_DIR = "external/boost"
$OriginalLocation = Get-Location

$SparseCheckoutContent = @"
    libs/assert/
    libs/bind/
    libs/config/
    libs/container_hash/
    libs/core/
    libs/describe/
    libs/integer/
    libs/iterator/
    libs/move/
    libs/mp11/
    libs/mpl/
    libs/multi_index/
    libs/preprocessor/
    libs/static_assert/
    libs/throw_exception/
    libs/tuple/
    libs/type_traits/
    libs/utility/
"@

try {
    if (-not (Test-Path "$BOOST_DIR/.git")) {
        Write-Host "Initializing Boost as a submodule..."
        git submodule add --force https://github.com/boostorg/boost.git $BOOST_DIR
    }

    Set-Location $BOOST_DIR

    git sparse-checkout init --no-cone

    if (-not (Test-Path ".git")) {
        throw "The .git directory does not exist. Ensure the submodule is initialized correctly."
    }

    if (-not (Test-Path ".git\info")) {
        New-Item -ItemType Directory -Path ".git\info" -Force | Out-Null
    }

    $GitDir = git rev-parse --git-dir
    $SparseCheckoutPath = Join-Path $GitDir "info\sparse-checkout"
    $SparseCheckoutContent | Out-File -Encoding ASCII $SparseCheckoutPath

    git sparse-checkout set $($SparseCheckoutContent -split "`r`n")

    git checkout master

    $SparseCheckoutContent -split "`r`n" | ForEach-Object {
        git submodule update --init $_
    }

    Write-Host "Boost setup completed successfully." -ForegroundColor Green

} catch {
    Write-Host "An error occurred: $_" -ForegroundColor Red
    throw
} finally {
    Set-Location $OriginalLocation
}
